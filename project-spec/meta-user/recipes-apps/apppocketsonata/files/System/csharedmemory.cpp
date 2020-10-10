#include "csharedmemory.h"

CSharedMemroy::CSharedMemroy()
{

}

CSharedMemroy::CSharedMemroy( key_t key, int iSize )
{
    setKey( key );

    setupSharedMemory( iSize );
    attachSharedMemory();

}

CSharedMemroy::CSharedMemroy( key_t key )
{
    setKey( key );

    setupSharedMemory( 0 );
    attachSharedMemory();

}

CSharedMemroy::~CSharedMemroy()
{

}


void CSharedMemroy::setShmId( int id )
{
    m_shmid = id;
}


void CSharedMemroy::setKey( key_t key )
{
    m_key = key;
}


void CSharedMemroy::setupSharedMemory( int iSize )
{
   // Setup shared memory, 11 is the size

    if ( ( m_shmid = shmget(m_key, iSize , IPC_CREAT | 0666 )) < 0 )
    {
        if ( ( m_shmid = shmget(m_key, 0 , 0)) < 0 ) {
            perror( "Error getting shared memory id" );
        }
    }

    m_iSize = iSize;
}

void CSharedMemroy::attachSharedMemory()
{
   // Attached shared memory
   if ( ( m_shared_memory = shmat( m_shmid , NULL , 0 ) ) == (char *)-1)
   {
      perror("Error attaching shared memory id");
   }
}


void CSharedMemroy::copyToSharedMemroy( void *pData )
{
   // copy string to shared memory
    if( m_shared_memory != (void *) -1 ) {
        memcpy( m_shared_memory, pData , m_iSize );
    }
   //sleep( 10 );
}

void CSharedMemroy::copyToLocalMemroy( void *pData, int iSize )
{
   // copy string to shared memory
    if( m_shared_memory != (void *) -1 ) {
        memcpy( pData, m_shared_memory, iSize );
    }
   //sleep( 10 );
}

void CSharedMemroy::close()
{
   sleep(10);

   // Detach and remove shared memory
   shmdt( m_shared_memory );
   shmctl( m_shmid , IPC_RMID, NULL );

}



