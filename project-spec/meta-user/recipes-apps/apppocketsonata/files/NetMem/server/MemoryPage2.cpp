/**

    @file      MemoryPage.cpp
    @brief
    @details   ~
    @author    조철희
    @date      16.04.2023
    @copyright ? Cool Guy, 2023. All right reserved.

**/

#include "pch.h"

#include "../utils/PortableSocket.h"
#include "MemoryPage2.h"

#include <iostream>
#include <cstring>

using namespace std;


MemoryPage::MemoryPage(int length, int version)
{
	data = (unsigned char *)malloc(length);
    memset( data, 0, length );

    this->length=length;
	lockerId=-1;
	this->version=version;

#ifdef _MSC_VER
    m_thePageMutex = new CSingleLock( & m_pageMutex );

#elif defined(__VXWORKS__)
    if( sem_init( & m_thePageMutex, 1, 1 ) < 0 ) {
        perror( "세마포어 실패" );
    }

#endif

}

/**
 * @brief     Lock
 * @param     int callerId
 * @return    unsigned char *
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-21 13:30:43
 * @warning
 */
unsigned char * MemoryPage::Lock( int callerId)
{
#ifdef _MSC_VER
    m_thePageMutex->Lock();
#else
    sem_wait( & m_thePageMutex );

#endif

	lockerId=callerId;

	return data;
}

/**
 * @brief     Read
 * @param     unsigned char * rData
 * @return    int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-21 13:30:46
 * @warning
 */
int MemoryPage::Read(unsigned char * rData)
{
	//boost::mutex::scoped_lock tmpLock(rwMutex);
#ifdef _MSC_VER
    CSingleLock rwMutex( & _rwMutex );
    rwMutex.Lock();
#else
    sem_wait( & rwMutex );

#endif

	memcpy(rData, this->data,length);
	return 1;
}

int MemoryPage::Unlock(unsigned char * newData, int callerId)
{
	//if we can lock it, that means that was not been previously locked, so get out
	
#ifdef _MSC_VER	
	if ( m_thePageMutex->IsLocked() == FALSE )
#elif defined(__VXWORKS__)
	if ( sem_trywait( &m_thePageMutex ) )		
#else
		
#endif

   {
#ifdef _MSC_VER			
        m_thePageMutex->Unlock();
        
#elif defined(__VXWORKS__)
        sem_wait( & m_thePageMutex );
#endif        
		return 0;
	}
	//REFACTOR here we can use something like own_lock()
	if (callerId!=lockerId) return 0;

	if(newData)
	{

		//boost::mutex::scoped_lock tmpLock(rwMutex);
#ifdef _MSC_VER
        CSingleLock rwMutex( & _rwMutex );
        rwMutex.Lock();
        
#elif defined(__VXWORKS__)
        sem_wait( & rwMutex );

#endif
		memcpy(this->data,newData,length);
		version++;
	}
	lockerId=-1;
	if (version < 0 ) version=1;

#ifdef _MSC_VER	
    m_thePageMutex->Unlock();
    
#elif defined(__VXWORKS__)
    sem_wait( & m_thePageMutex );
    
#endif

	return version;
}


/**
 * Update (lock-unlock) the page
 * if the newVersion negative, just increase the version
 */
int MemoryPage::Update(unsigned char * newData, int newVersion, int callerId)
{
#ifdef _MSC_VER	
    if( m_thePageMutex->IsLocked() != TRUE )
	{
		//the page is locked, if the caller is the same with the locker, we permit the update
		//if not, just wait unlocking
		if (callerId!=lockerId)
		{
            m_thePageMutex->Lock();
		}
	}

#elif defined(__VXWORKS__)
	if ( sem_trywait( &m_thePageMutex ) ) {
		//the page is locked, if the caller is the same with the locker, we permit the update
		//if not, just wait unlocking
		if (callerId!=lockerId)
		{
            sem_wait( & m_thePageMutex );
		}
	}
    
#endif    

	//boost::mutex::scoped_lock tmpLock(rwMutex);

#ifdef _MSC_VER
    CSingleLock rwMutex( & _rwMutex );
    rwMutex.Lock();
#elif defined(__VXWORKS__)
    sem_wait( & rwMutex );

#endif

	if(newData)memcpy(this->data,newData,length);
	if (version>=0)version=newVersion;
	else version++;
	if (version < 0 ) version=1;
	
#ifdef _MSC_VER	
    m_thePageMutex->Unlock();

#elif defined(__VXWORKS__)
    sem_wait( & m_thePageMutex );

#endif
    
	return version;
}

MemoryPage::~MemoryPage()
{
	free(data);

#ifdef _MSC_VER	
    delete m_thePageMutex;
    
#elif defined(__VXWORKS__)
    sem_destroy( & m_thePageMutex);
    
#endif
    
}

