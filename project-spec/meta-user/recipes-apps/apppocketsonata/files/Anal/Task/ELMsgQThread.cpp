#include "stdafx.h"

#include "ELMsgQThread.h"

CELMsgQThread::CELMsgQThread(void) //#FA_Q_4020_T1
{	
	if(m_cond.CreateLIGEvent(true) == FALSE ) // unsignal 인 상태. manual reset 상태로 이벤트를 만든다.
	{
		return;
	}
	this->Start();	
}

CELMsgQThread::~CELMsgQThread(void)
{	
	this->Stop();

	DeleteAllQData();

	// 타이머 스레드, Q스레드 등이 모두 멈출 시간을 벌어줘야 한다. 그렇지 않으면 스레드 안에서 사용하는 Critical Section 객체들이 이미 delete
	// 되었음에도 ScopedLock에서 critical section 객체를 통해 lock을 걸기 때문에 프로그램 종료 시 죽는 문제 발생. 2015.05.26. 이정남.
	Sleep(2000); 	
}

void CELMsgQThread::Run()
{
	bool bRslt = true;
	SQMsg stMsg;	

	while( IsRunning() == TRUE) //#FA_C_PotentialUnboundedLoop_T1
	{
		m_cond.Wait(); // 시그널을 기다리는 중이다. 

		bRslt = GetMsgFromQ(stMsg);
		if(bRslt)
		{
			ProcessMsg(stMsg);			
		}
		else // 큐에 더 이상 메시지가 없다는 이야기다.
		{
			m_cond.LIGResetEvent();
		}				
	}
}

void CELMsgQThread::ProcessMsg(SQMsg& i_stMsg)
{	
	// 재정의 필요.
}

bool CELMsgQThread::GetMsgFromQ(SQMsg& i_stMsg)
{
	bool bRtn = false;

	//ScopedLock lock(&m_QLock);
	if(m_queMsg.size() != 0)
	{		
		i_stMsg = m_queMsg.front();
		m_queMsg.pop();
		bRtn = true;
	}
	//TRACE("[link1] 메시지 queue 크기 : %d\n", m_queMsg.size() );
	return bRtn;
}

void CELMsgQThread::PushMsg(SQMsg& i_stMsg)
{
	//ScopedLock lock(&m_QLock);
	m_queMsg.push(i_stMsg);
	//TRACE("[LINK1] QSize = %d\n", m_queMsg.size());
}

void CELMsgQThread::DeleteAllQData()
{
	//ScopedLock lock(&m_QLock);
	UINT nQsize = m_queMsg.size();
	if(nQsize != 0)
	{		
		for(UINT i=0; i< nQsize; ++i)
		{
			m_queMsg.pop();
		}		
	}
}

void CELMsgQThread::PrintTheMsgQueue()
{
	//unsigned int nQueueSize=GetMsgQSize();
	//if( nQueueSize != 0 ) {
	//	//TRACE( "큐 사이즈 : %d\n", nQueueSize );

	//}
}

//==============================


