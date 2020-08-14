#include "stdafx.h"

#include <windows.h>
#include <process.h> //_beginthreadex()

#include "LIGCondition.h"
//#include "LIGLock.h"
#include <string.h> //memset

#ifdef _DEBUG
#define new DEBUG_NEW
#define CRTDBG_MAP_ALLOC
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

LIGCondition::LIGCondition(bool isAutoCreate)
	: isInit(false)	
{	
	m_hEvent = NULL;
	if (isAutoCreate)
	{
		CreateLIGEvent();
	}
}

LIGCondition::~LIGCondition()
{
	CloseHandle(m_hEvent);
	m_hEvent = NULL;
}

//* @param[in]	bManualReset : TRUE(수동리셋), FALSE(기본값:자동리셋)
//*               bInitialState : TRUE(시그널상태), FALSE(기본값:언시그널상태)
bool LIGCondition::CreateLIGEvent(bool bManualReset) //#FA_Q_4020_T1
{
	//ScopedLock lock(&m_isInitLock);

	if (isInit == true) //이미 이벤트가 생성된 경우
	{
		return false;
	}
	m_hEvent = ::CreateEvent(NULL,
		(BOOL)bManualReset/*기본값:자동리셋*/,
		FALSE/*기본값:언시그널상태*/,
		NULL);
	isInit = true;
	return true;
}

//bool LIGCondition::DestroyEvent()
//{
//	ScopedLock lock(&m_isInitLock);
//
//	if (isInit == false) //이벤트가 생성되어 있지 않은 경우
//	{
//		return false;
//	}
//
//	::SetEvent(m_hEvent);
//	CloseHandle(m_hEvent);
//	m_hEvent = NULL;
//
//	isInit = false;
//	return true;
//}

bool LIGCondition::Wait(unsigned int dwMilliseconds) //#FA_Q_4020_T1
{
	{
		//ScopedLock lock(&m_isInitLock);
		if (isInit == false) //이벤트가 생성되어 있지 않은 경우
		{
			return false;
		}
	}

		switch (::WaitForSingleObject(m_hEvent, (DWORD)dwMilliseconds))
		{
		case WAIT_OBJECT_0:
			return true;
		case WAIT_TIMEOUT:
			return false;
		default:
			{//EX_DTEC_Else
				return false;
			}		
		}
	

}
//
//bool LIGCondition::Wait(LIGLock* unlock, unsigned int dwMilliseconds)
//{
//	{
//		ScopedLock lock(&m_isInitLock);
//		if (isInit == false) //이벤트가 생성되어 있지 않은 경우
//		{
//			return false;
//		}
//	}
//
//	unlock->unlock();
//
//	/*if (dwMilliseconds == -1)
//		dwMilliseconds = INFINITE;*/
//
//	::WaitForSingleObject(m_hEvent, (DWORD)dwMilliseconds);		
//
//	unlock->lock();
//	return true;
//}

///*bool LIGCondition::Wait(LIGLock* unlock, unsigned int dwMilliseconds)
//{
//	{
//		ScopedLock lock(&m_isInitLock);
//		if (isInit == false) //이벤트가 생성되어 있지 않은 경우
//			return false;
//	}
//
//	unlock->unlock();
//
//	/*if (dwMilliseconds == -1)
//		dwMilliseconds = INFINITE;*/
//
//	::WaitForSingleObject(m_hEvent, (DWORD)dwMilliseconds);		
//
//	unlock->lock();
//	return true;
//}*/

bool LIGCondition::LIGSetEvent() //#FA_Q_4020_T1
{
	{
		//ScopedLock lock(&m_isInitLock);
		if (isInit == false) //이벤트가 생성되어 있지 않은 경우
		{
			return false;
		}
	}
	::SetEvent(m_hEvent);
	return true;
}

bool LIGCondition::LIGResetEvent() //#FA_Q_4020_T1
{
	{
		//ScopedLock lock(&m_isInitLock);
		if (isInit == false) //이벤트가 생성되어 있지 않은 경우
		{
			return false;
		}
	}
	::ResetEvent(m_hEvent);
	return true;
}

