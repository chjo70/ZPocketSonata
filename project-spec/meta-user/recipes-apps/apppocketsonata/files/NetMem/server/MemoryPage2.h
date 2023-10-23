#pragma once
#ifndef MEMORYPAGE_H
#define MEMORYPAGE_H

//#include "sqlite/sqlite3.h"
//#include <boost/thread/mutex.hpp>

#ifdef _MSC_VER
#include <afxmt.h>

#define getcwd  _getcwd
#define mkdir   _mkdir
#define open    _open
#define write   _write
//#define closeSharedMemory   _close

#else
#include <semaphore.h>

#endif

class MemoryPage
{
public:
	MemoryPage(int length, int version);
	~MemoryPage();
	unsigned char * Lock(int callerId);

	int Unlock(unsigned char * data, int callerId);
	int Read(unsigned char * rData);
	int Update(unsigned char * newData, int newVersion, int callerId);
	int version;
	unsigned char * data;


    //boost::mutex pageMutex;
#ifdef _MSC_VER
    CMutex m_pageMutex;
    CSingleLock *m_thePageMutex;

#elif defined(__VXWORKS__)
    sem_t m_thePageMutex;

#endif


    // boost::mutex rwMutex;
#ifdef _MSC_VER
    CMutex _rwMutex;
#else
    sem_t rwMutex;
#endif

	int length;
	int lockerId;

};

#endif /*MEMORYPAGE_H*/
