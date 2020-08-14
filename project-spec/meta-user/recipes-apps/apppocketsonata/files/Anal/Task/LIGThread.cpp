#include "stdafx.h"

#include <windows.h>
#include <process.h> //_beginthreadex()

#include <string.h> //memset
#include "LIGThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#define CRTDBG_MAP_ALLOC
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void LIGThread::InitThread() //각종변수들 초기화
{
  m_ptrRun = NULL;
  m_pRunFunc = NULL;
	m_pRunFuncWithParameter = NULL;
	m_parameter = NULL;

	m_threadStatus = LIGThread::THREAD_STOP;
	m_hThread = NULL;
	m_threadID = 0;
}

LIGThread::LIGThread()
{
	InitThread();
}

LIGThread::~LIGThread()
{
	Stop();
}

bool LIGThread::Start() //#FA_Q_4020_T1
{
	//ScopedLock lock(&m_threadStatusLock);
	if (m_threadStatus == LIGThread::THREAD_STOP)
	{
		m_threadStatus = LIGThread::THREAD_RUNNING;

		//STOP -> RUNNING
		m_hThread = (HANDLE)_beginthreadex(NULL,
										   0,
										   &MainProc,
										   this,
										   0,
										   &m_threadID);

		if (m_hThread == NULL)
		{//DTEC_NullPointCheck
			m_threadStatus = LIGThread::THREAD_STOP;
			return false; //Thread생성 실패
		}
	}
    return true;
}

bool LIGThread::Stop() //#FA_Q_4020_T1
{
	//ScopedLock lock(&m_threadStatusLock);

	if (m_threadStatus == LIGThread::THREAD_RUNNING)
	{
		//RUNNING -> STOPPING
		m_threadStatus = LIGThread::THREAD_KILLED;
		return true;
	}
	else if (m_threadStatus == LIGThread::THREAD_STOP)
	{
		//STOP
		return false;
	}
	else
	{//DTEC_Else
	}
	return true;
}

bool LIGThread::IsRunning()
{
  // ScopedLock lock(&m_threadStatusLock);
  return ((m_threadStatus == LIGThread::THREAD_RUNNING) ? true : false);
}

BOOL LIGThread::SetPriority(int priority) //#FA_Q_4020_T1
{
  if (IsRunning() == false) //thread가 정지상태이면 m_hThread가 없음
	{
        return FALSE;
	}

	BOOL bRtn = ::SetThreadPriority(m_hThread, priority);
	return bRtn;
}

void LIGThread::Run()
{
  if (m_ptrRun != nullptr)
	{
		m_ptrRun->Run();
	}
}

unsigned __stdcall LIGThread::MainProc(void *parameter)
{
  LIGThread *pThis = (LIGThread *)parameter;

	pThis->Run();
//     //ScopedLock lock(&pThis->m_threadStatusLock);
// 		//Stop함수가 호출된 상태면 THREAD_STOPPING인데 이 상태가 아니면 그냥 종료한 것이므로 THREAD_STOP 되게
	pThis->m_threadStatus = LIGThread::THREAD_RUNNING;

  return 0;
}
