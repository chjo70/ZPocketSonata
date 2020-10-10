#ifndef CSHAREDMEMORY_H
#define CSHAREDMEMORY_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string>

using namespace std;

#define _SHM_MEMORY_KEY         (333)

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
    void copyToSharedMemroy( void *pData );
    void copyToLocalMemroy( void *pData, int iSize );
    void close();
};

#endif // CSHAREDMEMORY_H
