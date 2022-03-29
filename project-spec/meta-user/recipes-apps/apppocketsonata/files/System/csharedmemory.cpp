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
CSharedMemroy::CSharedMemroy( key_t key, int iSize )
{


    setKey( key );

    setupSharedMemory( iSize );
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
void CSharedMemroy::setupSharedMemory( SIZE_T iSize )
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
            close();

            if ( ( m_shmid = shmget(m_key, iSize , IPC_CREAT | 0666 )) < 0 ) {
                perror( "Error getting shared memory id" );
            }
        }
    }
#elif _MSC_VER
    if( iSize == 0 ) {
        if( m_hHandle == NULL ) {
            m_hHandle = ::OpenFileMapping( FILE_MAP_ALL_ACCESS, NULL, SHARED_NAME );
        }            
        if( m_hHandle != NULL ) {
            m_shared_memory = (void *) ::MapViewOfFile( m_hHandle, FILE_MAP_ALL_ACCESS, 0, 0, iSize );
        }
    }
    else {
        if( m_hHandle == NULL ) {
            m_hHandle = ::CreateFileMapping( INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, iSize, SHARED_NAME );
        }
        if( m_hHandle != NULL ) {
            m_shared_memory = (void *) ::MapViewOfFile( m_hHandle, FILE_MAP_ALL_ACCESS, 0, 0, iSize );
        }
    }

#else
   m_shmid = 0;

#endif


    m_iSize = iSize;
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
        memcpy( m_shared_memory, pData , m_iSize );
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
bool CSharedMemroy::copyToLocalMemroy( void *pData, int iSize )
{
    bool bRet=true;
    // copy string to shared memory
    if( m_shared_memory != (void *) -1 ) {
        memcpy( pData, m_shared_memory, iSize );
    }
    else {
        memset( pData, 0, iSize );
        bRet = false;
        //printf("Error attaching shared memory id");
    }
   //sleep( 10 );
    return bRet;
}

/**
 * @brief CSharedMemroy::close
 */
void CSharedMemroy::close()
{
#ifdef __linux__
   //sleep(10);

   // Detach and remove shared memory
   shmdt( m_shared_memory );
   shmctl( m_shmid , IPC_RMID, NULL );

#endif

}



