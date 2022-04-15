// CSharedMemroy.cpp: implementation of the CSharedMemroy class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "csharedmemory.h"

/**
 * @brief CSharedMemroy::CSharedMemroy
 */
CSharedMemroy::CSharedMemroy()
{
#ifdef _MSC_VER
    m_hHandle = NULL;
#endif

}

/**
 * @brief CSharedMemroy::CSharedMemroy
 * @param key
 * @param iSize
 */
CSharedMemroy::CSharedMemroy( key_t key, SIZE_T szSize )
{

    setKey( key );

    setupSharedMemory( szSize );
    attachSharedMemory();

}

/**
 * @brief CSharedMemroy::CSharedMemroy
 * @param key
 */
CSharedMemroy::CSharedMemroy( key_t key )
{
    setKey( key );

    setupSharedMemory( 0 );
    attachSharedMemory();

}

/**
 * @brief CSharedMemroy::~CSharedMemroy
 */
CSharedMemroy::~CSharedMemroy()
{
    closeSharedMemory();
}

/**
 * @brief CSharedMemroy::setShmId
 * @param id
 */
void CSharedMemroy::setShmId( int id )
{
#ifdef _MSC_VER

#else
    m_shmid = id;
#endif

}

/**
 * @brief CSharedMemroy::setKey
 * @param key
 */
void CSharedMemroy::setKey( key_t key )
{
    
#ifdef _MSC_VER
    m_hHandle = NULL;
#else
    m_key = key;

#endif
}

/**
 * @brief CSharedMemroy::setupSharedMemory
 * @param iSize
 */
void CSharedMemroy::setupSharedMemory( SIZE_T szSize )
{
   // Setup shared memory, 11 is the size
#ifdef __linux__
   if( iSize == 0 ) {
        if ( ( m_shmid = shmget(m_key, 0 , 0)) < 0 ) {
            perror( "Error getting shared memory id\n" );
        }
    }
   else {
        if ( ( m_shmid = shmget(m_key, iSize , IPC_CREAT | 0666 )) < 0 ) {
            if ( ( m_shmid = shmget(m_key, 0 , 0)) < 0 ) {
                perror( "Error getting shared memory id\n" );
            }
            attachSharedMemory();
            closeSharedMemory();

            if ( ( m_shmid = shmget(m_key, iSize , IPC_CREAT | 0666 )) < 0 ) {
                perror( "Error getting shared memory id" );
            }
        }
    }
#elif _MSC_VER
    if( szSize == 0 ) {
        if( m_hHandle == NULL ) {
            m_hHandle = ::OpenFileMapping( FILE_MAP_ALL_ACCESS, NULL, SHARED_NAME );
        }            
        if( m_hHandle != NULL ) {
            m_shared_memory = (void *) ::MapViewOfFile( m_hHandle, FILE_MAP_ALL_ACCESS, 0, 0, szSize );
        }
    }
    else {
        if( m_hHandle == NULL ) {
            m_hHandle = ::CreateFileMapping( INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, szSize, SHARED_NAME );
        }
        if( m_hHandle != NULL ) {
            m_shared_memory = (void *) ::MapViewOfFile( m_hHandle, FILE_MAP_ALL_ACCESS, 0, 0, szSize );
        }
    }

#else
   m_shmid = 0;

#endif


    m_szSize = szSize;
}

/**
 * @brief CSharedMemroy::attachSharedMemory
 */
void CSharedMemroy::attachSharedMemory()
{
#ifdef __linux__
   // Attached shared memory
   if ( ( m_shared_memory = shmat( m_shmid , NULL , 0 ) ) == (char *)-1)
   {
      perror("Error attaching shared memory id");
        //printf( "Error attachSharedMemory !!" );
   }
#elif _MSC_VER

#else
    m_shared_memory = (void *) -1;

#endif

}

/**
 * @brief CSharedMemroy::copyToSharedMemroy
 * @param pData
 * @return
 */
bool CSharedMemroy::copyToSharedMemroy( void *pData )
{
    bool bRet=true;
    // copy string to shared memory
    if( m_shared_memory != (void *) -1 ) {
        memcpy( m_shared_memory, pData , m_szSize );
    }
    else {
        //printf("Error copyToSharedMemroy !!");
        bRet = false;
    }
    //sleep( 10 );

    return bRet;
}

/**
 * @brief CSharedMemroy::copyToLocalMemroy
 * @param pData
 * @param iSize
 */
bool CSharedMemroy::copyToLocalMemroy( void *pData, SIZE_T szSize )
{
    bool bRet=true;
    // copy string to shared memory
    if( m_shared_memory != (void *) -1 ) {
        memcpy( pData, m_shared_memory, szSize );
    }
    else {
        memset( pData, 0, szSize );
        bRet = false;
        //printf("Error attaching shared memory id");
    }
   //sleep( 10 );
    return bRet;
}

/**
 * @brief CSharedMemroy::close
 */
void CSharedMemroy::closeSharedMemory()
{
#ifdef __linux__
   //sleep(10);

   // Detach and remove shared memory
   shmdt( m_shared_memory );
   shmctl( m_shmid , IPC_RMID, NULL );

#endif

}



