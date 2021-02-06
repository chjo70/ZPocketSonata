#ifndef CSHAREDMEMORY_H
#define CSHAREDMEMORY_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

#ifdef __linux__
#include <sys/ipc.h>
#include <sys/shm.h>
#else
typedef int key_t;

#endif

#include <unistd.h>
#include <string>

#include "../Include/system.h"

using namespace std;



class CSharedMemroy
{

private :

    int m_shmid;
    key_t m_key;
    void *m_shared_memory;
    int m_iSize;


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
