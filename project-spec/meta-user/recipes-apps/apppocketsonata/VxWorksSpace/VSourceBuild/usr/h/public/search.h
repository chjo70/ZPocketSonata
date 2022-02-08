#ifndef __Isearch
#define __Isearch

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct entry {
	char *key, *data;
} ENTRY;

typedef enum { FIND, ENTER } ACTION;

typedef enum { preorder, postorder, endorder, leaf } VISIT;

extern ENTRY *hsearch(ENTRY, ACTION);
extern int hcreate(unsigned int);
extern void hdestroy(void);
extern void *lsearch(const void *, const void *, unsigned int *, int, int (*)());
extern void *lfind(const void *, const void *, unsigned int *, int, int (*)());
extern void *tsearch(const void *, void **, int (*)());
extern void *tfind(const void *, void *const *, int (*)());
extern void *tdelete(const void *, void **, int (*)());
extern void twalk(void *, void (*)());

#ifdef	__cplusplus
}
#endif
#endif
