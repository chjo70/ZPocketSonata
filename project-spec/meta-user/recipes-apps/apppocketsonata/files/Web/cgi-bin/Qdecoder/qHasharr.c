/*
 * Copyright 2008 The qDecoder Project. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE QDECODER PROJECT ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE QDECODER PROJECT BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file qHasharr.c Array based Hash-table Data Structure API
 *
 * @note
 * This Aarray-hash-table does not support thread-safe feature because this table is designed for statically assigned array like shared memory
 * and most of this cases use fork() & semaphore based program model.
 * In case of multiple access of this table, you should provide some kind of lock mechanism to prevent multiple modification of table at same time.
 * qDecoder also have thread-safe Dynamic Hash-table, please refer qHashtbl().
 *
 * In this array hash-table, we use some technics to effectively use memory. To verify key we use two way,
 * if the key is smaller than (_Q_HASHARR_MAX_KEYSIZE - 1), we compare key itself. But if the key is bigger than
 * (_Q_HASHARR_MAX_KEYSIZE - 1), we compare md5 of key and key length. If the key length and md5 of key are same
 * we consider it's same key. So we don't need to store full key string. Actually it's not necessary to keep
 * original key string, but we keep this because of two reasons. 1) if the length of the key is smaller than 16,
 * it will be little bit quicker to compare key. 2) debugging reason.
 *
 * Basically this hash-table based on array defines small size slot then it can links several slot for one data.
 * This mechanism can save some wastes of memory. You can adjust default slot size to modify _Q_HASHARR_DEF_VALUESIZE.
 *
 * @code
 *   int maxkeys = 1000;
 *
 *   // calculate how many memory do we need
 *   size_t memsize = qHasharrSize(maxkeys * 2); // generally allocate double size of max to decrease hash collision
 *
 *   // allocate memory
 *   Q_HASHARR *hasharr = (Q_HASHARR *)malloc(memsize);
 *
 *   // initialize hash-table
 *   if(qHasharr(hasharr, memsize) == 0) return -1;
 *
 *   // put some sample data
 *   if(hasharr->put(hasharr, "sample1", "binary", 6) == false) return -1; // hash-table full
 *   if(hasharr->putStr(hasharr, "sample2", "string") == false) return -1; // hash-table full
 *   if(hasharr->putInt(hasharr, "sample3", 3) == false) return -1; // hash-table full
 *
 *   // fetch data
 *   int size;
 *   char *sample_bin = hasharr->get(hasharr, "sample1", &size);
 *   char *sample_str = hasharr->getStr(hasharr, "sample2");
 *   int  sample_int  = hasharr->getInt(hasharr, "sample3");
 * @endcode
 *
 * Another simple way to initialize hash-table.
 *
 * @code
 *   // define data memory as much as you needed.
 *   char datamem[10 * 1024];
 *
 *   // just set the Q_HASHARR points to data memory.
 *   Q_HASHARR *hasharr = (Q_HASHARR *)datamem;
 *
 *   // initialize hash-table.
 *   if(qHasharr(hasharr, sizeof(datamem)) == 0) return -1;
 *
 *   (...your codes here...)
 *
 *   // no need to free unless you use malloc()
 * @endcode
 *
 * You can create hash table on shared memory like below.
 *
 * @code
 *   int maxkeys = 1000;
 *   int memsize = qHasharrSize(maxkeys * 2);
 *
 *   // create shared memory
 *   int shmid = qShmInit(g_conf.szEgisdavdPidfile, 's', memsize, true);
 *   if(shmid < 0) return -1; // creation failed
 *   Q_HASHARR *tbl = (Q_HASHARR *)qShmGet(shmid);
 *
 *   // initialize hash-table
 *   if(qHasharr(tbl, memsize) == 0) return -1;
 *
 *   (...your codes here...)
 *
 *   // destroy shared memory
 *   qShmFree(shmid);
 * @endcode
 */

#ifndef DISABLE_DATASTRUCTURE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "qDecoder.h"
#include "qInternal.h"

#ifndef _DOXYGEN_SKIP

static bool	_put(Q_HASHARR *tbl, const char *key, const void *value, int size);
static bool	_putStr(Q_HASHARR *tbl, const char *key, const char *str);
static bool	_putInt(Q_HASHARR *tbl, const char *key, int num);

static void*	_get(Q_HASHARR *tbl, const char *key, int *size);
static char*	_getStr(Q_HASHARR *tbl, const char *key);
static int	_getInt(Q_HASHARR *tbl, const char *key);

static const char* _getNext(Q_HASHARR *tbl, int *idx);
static bool	_remove(Q_HASHARR *tbl, const char *key);
static bool	_truncate(Q_HASHARR *tbl);

static bool	_print(Q_HASHARR *tbl, FILE *out);
static int	_getNum(Q_HASHARR *tbl);
static int	_getMax(Q_HASHARR *tbl);

// internal usages
static int	_findEmpty(Q_HASHARR *tbl, int startidx);
static int	_getIdx(Q_HASHARR *tbl, const char *key, int hash);
static bool	_putData(Q_HASHARR *tbl, int idx, int hash, const char *key, const void *value, int size, int count);
static bool	_copySlot(Q_HASHARR *tbl, int idx1, int idx2);
static bool	_removeSlot(Q_HASHARR *tbl, int idx);
static bool	_removeData(Q_HASHARR *tbl, int idx);

#endif

/**
 * Get how much memory is needed for N entries
 *
 * @param max		a number of maximum internal slots
 *
 * @return		memory size needed
 *
 * @note
 * This is useful when you decide how much memory(shared-memory) required for N object entries.
 * Be sure, a single object can be stored in several slots. So you need to consider additional
 * slots if some data is bigger than _Q_HASHARR_DEF_VALUESIZE.
 * By default, _Q_HASHARR_DEF_VALUESIZE is 32. This means if the size of object is bigger than
 * 32 bytes it will use another slot.
 */
size_t qHasharrSize(int max) {
	size_t memsize = sizeof(Q_HASHARR) * (max + 1);
	return memsize;
}

/**
 * Initialize array-hash table
 *
 * @param tbl		a pointer of Q_HASHARR
 * @param memsize	actual size of Q_HASHARR
 *
 * @return		maximum number of available slots if successful, otherwise returns 0
 *
 * @code
 *   // allocate memory
 *   size_t memsize = qHasharrSize(100);
 *   Q_HASHARR *hasharr = (Q_HASHARR *)malloc(memsize);
 *
 *   // initialize hash-table
 *   if(qHasharr(hasharr, memsize) == 0) return -1;
 * @endcode
 *
 * @code
 *   int maxkeys = 1000;
 *   int memsize = qHasharrSize(maxkeys * 2);
 *
 *   // create shared memory
 *   int shmid = qShmInit(g_conf.szEgisdavdPidfile, 's', memsize, true);
 *   if(shmid < 0) return -1; // creation failed
 *   Q_HASHARR *tbl = (Q_HASHARR *)qShmGet(shmid);
 *
 *   // initialize hash-table
 *   if(qHasharr(tbl, memsize) == 0) return -1;
 *
 *   (...your codes here...)
 *
 *   // destroy shared memory
 *   qShmFree(shmid);
 * @endcode
 */
int qHasharr(Q_HASHARR *tbl, size_t memsize) {
	// calculate max
	int max = (memsize / sizeof(Q_HASHARR)) - 1;
	if(max < 1) return 0;

	// clear memory
	memset((void *)tbl, 0, memsize);

	// slot 0 is used for special purpose
	tbl[0].count = 0;	// number of used slot
	tbl[0].keylen = max;	// number of slots

	// assign methods
	tbl->put		= _put;
	tbl->putStr		= _putStr;
	tbl->putInt		= _putInt;

	tbl->get		= _get;
	tbl->getStr		= _getStr;
	tbl->getInt		= _getInt;
	tbl->getNext		= _getNext;

	tbl->remove		= _remove;
	tbl->truncate		= _truncate;

	tbl->print		= _print;
	tbl->getNum		= _getNum;
	tbl->getMax		= _getMax;

	return max;
}

/**
 * Q_HASHARR->put(): Put object into hash table
 *
 * @param tbl		a pointer of Q_HASHARR
 * @param key		key string
 * @param value		value object data
 * @param size		size of value
 *
 * @return		true if successful, otherwise returns false
 */
static bool _put(Q_HASHARR *tbl, const char *key, const void *value, int size) {
	if(tbl == NULL || key == NULL || value == NULL) return false;

	// check full
	//if (tbl[0].count >= tbl[0].keylen) return false;

	// get hash integer
	int hash = ((int)qHashFnv32(tbl[0].keylen, key, strlen(key))) + 1; // 0���� �Ⱦ��Ƿ�

	// check, is slot empty
	if (tbl[hash].count == 0) { // empty slot
		// put data
		if(_putData(tbl, hash, hash, key, value, size, 1) == false) {
			DEBUG("hasharr: FAILED put(new) %s", key);
			return false;
		}
		DEBUG("hasharr: put(new) %s (idx=%d,hash=%d,tot=%d)", key, hash, hash, tbl[0].count);
	} else if (tbl[hash].count > 0) { // same key exists or hash collision
		// check same key;
		int idx = _getIdx(tbl, key, hash);
		if (idx >= 0) { // same key
			// remove and recall
			_remove(tbl, key);
			return _put(tbl, key, value, size);
		} else { // no same key, just hash collision
			// find empty slot
			int idx = _findEmpty(tbl, hash);
			if (idx < 0) return false;

			// put data. -1 is used for collision resolution (idx != hash);
			if(_putData(tbl, idx, hash, key, value, size, -1) == false) {
				DEBUG("hasharr: FAILED put(col) %s", key);
				return false;
			}

			// increase counter from leading slot
			tbl[hash].count++;

			DEBUG("hasharr: put(col) %s (idx=%d,hash=%d,tot=%d)", key, idx, hash, tbl[0].count);
		}
	} else { // in case of -1 or -2. used for collision resolution or oversized value data, move it

		// find empty slot
		int idx = _findEmpty(tbl, hash);
		if (idx < 0) return false;

		// move dup slot to empty
		_copySlot(tbl, idx, hash);
		_removeSlot(tbl, hash);

		// in case of -2, adjust link of mother
		if(tbl[hash].count == -2) {
			tbl[ tbl[idx].hash ].link = idx;
		}

		// store data
		if(_putData(tbl, hash, hash, key, value, size, 1) == false) {
			DEBUG("hasharr: FAILED put(swp) %s", key);
			return false;
		}

		DEBUG("hasharr: put(swp) %s (idx=%d,hash=%d,tot=%d)", key, hash, hash, tbl[0].count);
	}

	return true;
}

/**
 * Q_HASHARR->putStr(): Put string into hash table
 *
 * @param tbl		a pointer of Q_HASHARR
 * @param key		key string
 * @param value		value string
 *
 * @return		true if successful, otherwise returns false
 */
static bool _putStr(Q_HASHARR *tbl, const char *key, const char *str) {
	int size = (str != NULL) ? (strlen(str) + 1) : 0;
	return _put(tbl, key, (void *)str, size);
}

/**
 * Q_HASHARR->putInt(): Put integer into hash table
 *
 * @param tbl		a pointer of Q_HASHARR
 * @param key		key string
 * @param value		value integer
 *
 * @return		true if successful, otherwise returns false
 */
static bool _putInt(Q_HASHARR *tbl, const char *key, int num) {
	char data[10+1];
	sprintf(data, "%d", num);
	return _put(tbl, key, (void *)data, -1);
}

/**
 * Q_HASHARR->get(): Get object from hash table
 *
 * @param tbl		a pointer of Q_HASHARR
 * @param key		key string
 * @param size		if not NULL, oject size will be stored
 *
 * @return		malloced object pointer if successful, otherwise(not found) returns NULL
 *
 * @note
 * returned object must be freed after done using.
 */
static void *_get(Q_HASHARR *tbl, const char *key, int *size) {
	if(tbl == NULL || key == NULL) return NULL;

	// get hash integer
	int hash = ((int)qHashFnv32(tbl[0].keylen, key, strlen(key))) + 1; // 0���� �Ⱦ��Ƿ�

	int idx = _getIdx(tbl, key, hash);
	if (idx < 0) return NULL;

	int newidx, valsize;
	for(newidx = idx, valsize = 0; ; newidx = tbl[newidx].link) {
		valsize += tbl[newidx].size;
		if(tbl[newidx].link == 0) break;
	}

	void *value, *vp;
	value = (void *)malloc(valsize);
	if(value == NULL) return NULL;

	for(newidx = idx, vp = value; ; newidx = tbl[newidx].link) {
		memcpy(vp, (void *)tbl[newidx].value, tbl[newidx].size);
		vp += tbl[newidx].size;
		if(tbl[newidx].link == 0) break;
	}

	if(size != NULL) *size = valsize;
	return value;
}

/**
 * Q_HASHARR->getStr(): Get string from hash table
 *
 * @param tbl		a pointer of Q_HASHARR
 * @param key		key string
 *
 * @return		string pointer if successful, otherwise(not found) returns NULL
 *
 * @note
 * returned object must be freed after done using.
 */
static char *_getStr(Q_HASHARR *tbl, const char *key) {
	return (char*)_get(tbl, key, NULL);
}

/**
 * Q_HASHARR->getInt(): Get integer from hash table
 *
 * @param tbl		a pointer of Q_HASHARR
 * @param key		key string
 *
 * @return		value integer if successful, otherwise(not found) returns 0
 */
static int _getInt(Q_HASHARR *tbl, const char *key) {
	char *data = _get(tbl, key, NULL);
	if(data == NULL) return 0;

	int value = atoi(data);
	free(data);

	return value;
}

/**
 * Q_HASHARR->getNext(): Get next key name
 *
 * @param tbl		a pointer of Q_HASHARR
 * @param idx		index pointer
 *
 * @return		key name string if successful, otherwise(end of table) returns NULL
 *
 * @code
 *   int idx = 0;
 *   while(tbl->getNext(tbl, &idx) != NULL) {
 *     (... codes ...)
 *   }
 * @endcode
 *
 * @note
 * Do not free returned key string.
 */
static const char *_getNext(Q_HASHARR *tbl, int *idx) {
	if(tbl == NULL || idx == NULL) return NULL;

	for (*idx += 1; *idx <= tbl[0].keylen; (*idx)++) {
		if (tbl[*idx].count == 0 || tbl[*idx].count == -2) continue;
		return tbl[*idx].key;
	}

	*idx = tbl[0].keylen; // set to lastest key number
	return NULL;
}

/**
 * Q_HASHARR->remove(): Remove key from hash table
 *
 * @param tbl		a pointer of Q_HASHARR
 * @param key		key string
 *
 * @return		true if successful, otherwise(not found) returns false
 */
static bool _remove(Q_HASHARR *tbl, const char *key) {
	if(tbl == NULL || key == NULL) return false;

	// get hash integer
	int hash = ((int)qHashFnv32(tbl[0].keylen, key, strlen(key))) + 1; // tbl[0].keylen = maximum number of key space in the table

	int idx = _getIdx(tbl, key, hash);
	if (idx < 0) {
		DEBUG("not found %s", key);
		return false;
	}

	if (tbl[idx].count == 1) {
		// just remove
		_removeData(tbl, idx);

		DEBUG("hasharr: rem %s (idx=%d,tot=%d)", key, idx, tbl[0].count);
	} else if (tbl[idx].count > 1) { // leading slot and has dup
		// find dup
		int idx2;
		for (idx2 = idx + 1; ; idx2++) {
			if (idx2 > tbl[0].keylen) idx2 = 1;
			if (idx2 == idx) {
				DEBUG("BUG: failed to remove dup key %s.", key);
				return false;
			}
			if (tbl[idx2].count == -1 && tbl[idx2].hash == idx) break;
		}

		// move to leading slot
		int backupcount = tbl[idx].count;
		_removeData(tbl, idx); // remove leading data
		_copySlot(tbl, idx, idx2); // copy slot
		tbl[idx].count = backupcount - 1; // adjust collision counter
		_removeSlot(tbl, idx2); // remove moved slot

		DEBUG("hasharr: rem(lead) %s (idx=%d,tot=%d)", key, idx, tbl[0].count);
	} else { // in case of -1. used for collisio resolution
		// decrease counter from leading slot
		if(tbl[ tbl[idx].hash ].count <= 1) {
			DEBUG("hasharr: BUG remove failed %s. counter of leading slot mismatch.", key);
			return false;
		}
		tbl[ tbl[idx].hash ].count--;

		// remove data
		_removeData(tbl, idx);

		DEBUG("hasharr: rem(dup) %s (idx=%d,tot=%d)", key, idx, tbl[0].count);
	}

	return true;
}

/**
 * Q_HASHARR->truncate(): Truncate array-hash table
 *
 * @param tbl		a pointer of Q_HASHARR
 *
 * @return		true if successful, otherwise returns false
 */
static bool _truncate(Q_HASHARR *tbl) {
	// calculate max
	int max = tbl[0].keylen;

	// clear memory
	memset((void *)tbl, 0, qHasharrSize(max));

	// 0�� ���̺��� ��ü ���̺��� ������ ����
	tbl[0].count = 0;	// ������� ������ ����
	tbl[0].keylen = max;	// �ִ� ���� ũ��

	return true;
}

/**
 * Q_HASHARR->print(): Print hash table for debugging purpose
 *
 * @param tbl		a pointer of Q_HASHARR
 * @param out		output stream
 *
 * @return		true if successful, otherwise returns false
 */
static bool _print(Q_HASHARR *tbl, FILE *out) {
	if(tbl == NULL || out == NULL) return false;

	int idx, num;
	for (idx = 1, num = 0; idx <= tbl[0].keylen && num < tbl[0].count; idx++) {
		if (tbl[idx].count == 0) continue;
		fprintf(out, "idx=%d,count=%d,hash=%d,key=%s,keylen=%d,size=%d,link=%d\n",
			idx, tbl[idx].count, tbl[idx].hash, tbl[idx].key, tbl[idx].keylen, tbl[idx].size, tbl[idx].link);
		num++;
	}

	return true;
}

/**
 * Q_HASHARR->getNum(): Get number of objects stored
 *
 * @param tbl		a pointer of Q_HASHARR
 *
 * @return		number of objects stored
 */
static int _getNum(Q_HASHARR *tbl) {
	if(tbl == NULL) return false;

	return tbl[0].count;
}
/**
 * Q_HASHARR->getMax(): Get number of object slots
 *
 * @param tbl		a pointer of Q_HASHARR
 *
 * @return		number of object slots
 *
 * @note
 * It is different from dynamic hash-table. In array-hash table, a value object can be stored
 * in several slots if the size of the object is bigger than the size of slot. So used and max
 * slot number is not equal to actual stored and maximum storable objects number.
 */
static int _getMax(Q_HASHARR *tbl) {
	if(tbl == NULL) return false;

	return tbl[0].keylen;
}

#ifndef _DOXYGEN_SKIP

// find empty slot : return empty slow number, otherwise returns -1.
static int _findEmpty(Q_HASHARR *tbl, int startidx) {
	if(startidx > tbl[0].keylen) startidx = 1;

	int idx = startidx;
	while (true) {
		if (tbl[idx].count == 0) return idx;

		idx++;
		if(idx > tbl[0].keylen) idx = 1;
		if(idx == startidx) break;
	}

	return -1;
}

static int _getIdx(Q_HASHARR *tbl, const char *key, int hash) {
	if (tbl[hash].count > 0) {
		int keylen = strlen(key);
		unsigned char keymd5[16];

		unsigned char *tmpmd5 = qHashMd5(key, keylen);
		strncpy((char*)keymd5, (char*)tmpmd5, 16);
		free(tmpmd5);

		int count, idx;
		for (count = 0, idx = hash; count < tbl[hash].count; ) {
			// find same hash
			while(true) {
				if (idx > tbl[0].keylen) idx = 1;

				if ((tbl[idx].count > 0 || tbl[idx].count == -1) && tbl[idx].hash == hash) {
					// found same hash
					count++;
					break;
				}

				idx++;
				if(idx == hash) return -1;
			}

			// is same key?
			if (keylen == tbl[idx].keylen) {	// first check fast way
				if (keylen <= (_Q_HASHARR_MAX_KEYSIZE - 1)) {	// key is not truncated, use original key
					if (!strcmp(key, tbl[idx].key)) return idx;
				} else {					// key is truncated, use keymd5 instead.
					if (!memcmp(keymd5, tbl[idx].keymd5, 16)) return idx;
				}
			}

			// increase idx
			idx++;
			if(idx > tbl[0].keylen) idx = 1;

			// check loop
			if(idx == hash) break;
		}
	}

	return -1;
}

static bool _putData(Q_HASHARR *tbl, int idx, int hash, const char *key, const void *value, int size, int count) {
	// check if used
	if(tbl[idx].count != 0) {
		DEBUG("hasharr: BUG found.");
		return false;
	}

	int keylen = strlen(key);
	unsigned char *keymd5 = qHashMd5(key, keylen);

	// store key
	tbl[idx].count = count;
	tbl[idx].hash = hash;
	qStrCpy(tbl[idx].key, sizeof(tbl[idx].key), key);
	strncpy((char*)tbl[idx].keymd5, (char*)keymd5, 16);
	tbl[idx].keylen = keylen;
	tbl[idx].link = 0;

	free(keymd5);

	// store value
	int newidx, savesize, copysize;
	for (newidx = idx, savesize = 0, copysize = 0; savesize < size; savesize += copysize) {
		copysize = size - savesize;
		if(copysize > _Q_HASHARR_DEF_VALUESIZE) copysize = _Q_HASHARR_DEF_VALUESIZE;

		if(savesize > 0) { // find next empty slot
			int tmpidx = _findEmpty(tbl, newidx + 1);

			tmpidx = _findEmpty(tbl, newidx + 1);
			if(tmpidx < 0) {
				DEBUG("hasharr: Can't expand slot for key %s.", key);
				_removeData(tbl, idx);
				return false;
			}

			// clear & set
			memset((void *)(&tbl[tmpidx]), 0, sizeof(Q_HASHARR));

			tbl[tmpidx].count = -2;
			tbl[tmpidx].hash = newidx; // prev link
			tbl[tmpidx].link = 0;
			tbl[tmpidx].size = 0;

			tbl[newidx].link = tmpidx; // link chain

			DEBUG("hasharr: slot %d is linked to slot %d for key %s.", tmpidx, newidx, key);
			newidx = tmpidx;
		}

		memcpy(tbl[newidx].value, value + savesize, copysize);
		tbl[newidx].size = copysize;

		// increase used slot counter
		tbl[0].count++;
	}

	return true;
}

static bool _copySlot(Q_HASHARR *tbl, int idx1, int idx2) {
	if(tbl[idx1].count != 0 || tbl[idx2].count == 0) {
		DEBUG("hasharr: BUG found.");
		return false;
	}

	memcpy((void *)(&tbl[idx1]), (void *)(&tbl[idx2]), sizeof(Q_HASHARR));

	// increase used slot counter
	tbl[0].count++;

	return true;
}

static bool _removeSlot(Q_HASHARR *tbl, int idx) {
	if(tbl[idx].count == 0) {
		DEBUG("hasharr: BUG found.");
		return false;
	}

	tbl[idx].count = 0;

	// decrease used slot counter
	tbl[0].count--;

	return true;
}

static bool _removeData(Q_HASHARR *tbl, int idx) {
	if(tbl[idx].count == 0) {
		DEBUG("hasharr: BUG found.");
		return false;
	}

	while(true) {
		int link = tbl[idx].link;
		_removeSlot(tbl, idx);

		if(link == 0) break;
		idx = link;
	}

	return true;
}

#endif /* _DOXYGEN_SKIP */

#endif /* DISABLE_DATASTRUCTURE */
