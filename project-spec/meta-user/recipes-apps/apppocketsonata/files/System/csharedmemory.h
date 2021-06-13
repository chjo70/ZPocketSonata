#ifndef CSHAREDMEMORY_H
#define CSHAREDMEMORY_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

#ifdef __linux__
#include <sys/ipc.h>
#include <sys/shm.h>

#elif _MSC_VER
#define SHARED_NAME _T("Shared_Memory")
#else
#include <unistd.h>

#endif

#include <string>

#include "../Include/system.h"

using namespace std;



class CSharedMemroy
{

private :
    void *m_shared_memory;
    int m_iSize;

#ifdef _MSC_VER
    HANDLE m_hHandle;

#else
    int m_shmid;
    key_t m_key;

#endif


public :
    CSharedMemroy();
    CSharedMemroy( key_t key, int iSize );
    CSharedMemroy( key_t key );
    ~CSharedMemroy();

    void setShmId( int key );
    int getShmId();
    void setKey( key_t key );

    void setupSharedMemory( int iSize );
    void attachSharedMemory();
    bool copyToSharedMemroy( void *pData );
    bool copyToLocalMemroy( void *pData, int iSize );
    void close();
};

#endif // CSHAREDMEMORY_H
