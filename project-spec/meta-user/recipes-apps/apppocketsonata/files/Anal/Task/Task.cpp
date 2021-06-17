// Task.cpp: implementation of the CTask class.
//
//////////////////////////////////////////////////////////////////////

#include <stdio.h>

#include "stdafx.h"

#ifndef _WIN32
#include <usrLib.h>
#include <taskLib.h>
#include <errnoLib.h>
#include <loglib.h>

#endif

#include "Task.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTask::CTask()
{
	//m_QueueSize = queue_size;
	//m_RingSize = ring_size;

	MallocBuffer();

	InitVar();
	InitTask();
}

CTask::~CTask()
{
	FreeBuffer();

#ifdef _WIN32

	// DeleteAllQData();

#else
	// 큐 메시지를 삭제한다.
	if (OK != msgQDelete(m_msgQId)) {
		PrintErr(("\n [W] 큐 메시지를 삭제하지 못했습니다."));
	}

	// 링 메시지를 삭제한다.
	rngDelete(m_ringId);

	// 세마포어를 삭제한다.
	if (OK != semDelete(m_semEcho)) {
		PrintErr(("\n [W] 세마포아 메시지를 삭제하지 못했습니다."));
	}

#endif
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CTask::InitVar
		\author   조철희
		\return   void
		\version  0.0.1
		\date     2008-04-30 13:48:26
		\warning
*/
void CTask::InitVar()
{
#ifdef _WIN32
	m_msgQId = NULL;

#else
	m_semEcho = NULL;
	m_TaskId = -1;
	strcpy( m_taskName, "NO_NAME" );

#endif

	m_SecTmier = m_MillisecTimer = 0;

	m_bDangerOfQueueBufferFull = false;
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CTask::MallocBuffer
		\author   조철희
		\return   void
		\version  0.0.30
		\date     2008-07-18 16:47:24
		\warning
*/
void CTask::MallocBuffer()
{
	m_pqMsg = ( char * ) malloc( m_uiQueueSize * sizeof(char) );
	if( m_pqMsg == NULL ) {
		printf( "\n [W] 메모리를 할당하지 못했습니다." );
	}
}

void CTask::FreeBuffer()
{
	free( m_pqMsg );
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CTask::InitTask
		\author   조철희
		\return   void
		\version  0.0.1
		\date     2008-04-30 13:45:48
		\warning
*/
void CTask::InitTask()
{
#ifndef _WIN32
	// 큐 메시지 생성한다.
	m_msgQId = msgQCreate( MAX_LEN_MSGQ, m_uiQueueSize, MSG_Q_PRIORITY );
	if( NULL == m_msgQId ) {
		PrintErr( ( "\n [W] 큐 메시지를 생성하지 못했습니다." ) );
	}

	m_ringId = rngCreate( m_RingSize );
	if( NULL == m_ringId ) {
		PrintErr( ( "\n [W] 링 메시지를 생성하지 못했습니다." ) );
	}
	else {
		rngFlush( m_ringId );
	}

	// 세마포어를 생성한다.
	m_semEcho = semBCreate( SEM_Q_FIFO, SEM_EMPTY );
	if( NULL == m_semEcho ) {
		PrintErr( ( "\n [W] 세마포아 메시지를 생성하지 못했습니다." ) );
	}

#else
	if (m_cond.CreateLIGEvent(true) == FALSE) // unsignal 인 상태. manual reset 상태로 이벤트를 만든다.
	{
		return;
	}
	this->Start();

#endif
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CTask::TaskSpawn
		\author   조철희
		\param    name 인자형태 char *
		\param    priority 인자형태 int
		\param    options 인자형태 int
		\param    stack 인자형태 int
		\return   void
		\version  0.0.1
		\date     2008-04-30 14:08:58
		\warning
*/
void CTask::TaskSpawn( char *name, int priority, int options, int stack )
{
#ifndef _WIN32
	m_TaskId = taskSpawn( name, priority, options, stack, (FUNCPTR) Instance, (int)this, 0,0,0,0,0,0,0,0,0 );
	if( ERROR == m_TaskId ) {
		int noError = errnoGet();

		printErrno( noError );
	}

	strcpy( m_TaskName, name );

#endif
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CTask::ReceiveMessage
		\author   조철희
		\return   void
		\version  0.0.1
		\date     2008-04-30 15:04:51
		\warning
*/
void CTask::ReceiveMessage()
{
#ifdef _WIN32
#else
	STR_QUEUE_MESSAGE *pQMsg;

	ReceiveMessage( m_msgQId, m_pqMsg );
	pQMsg = ( STR_QUEUE_MESSAGE * ) m_pqMsg;
	//Printf( "\n\n [%s][%02x][%02x][%02x:%02x]" , m_taskName, pQMsg->opCode, pQMsg->opData, pQMsg->address1, pQMsg->address2 );
	Printf( "\n\n [%s][%02x]" , m_taskName, pQMsg->opCode );
#endif
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CTask::ReceiveMessage
		\author   조철희
		\param    m_msgQId 인자형태 MSG_Q_ID
		\param    pMsg 인자형태 void *
		\return   void
		\version  0.0.1
		\date     2008-04-30 15:04:03
		\warning
*/
void CTask::ReceiveMessage( MSG_Q_ID msgQId, void *pMsg, int timeout )
{
#ifndef _WIN32
	if( ERROR == msgQReceive( msgQId, (char *) pMsg, m_uiQueueSize, timeout ) ) {
		int noError = errnoGet();

		if( noError != S_objLib_OBJ_TIMEOUT ) {
			printErrno( noError );
		}
	}
#endif
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CTask::SendMessage
		\author   조철희
		\param    msgQId 인자형태 MSG_Q_ID
		\param    pMsg 인자형태 void *
		\return   void
		\version  0.0.1
		\date     2008-04-30 17:02:19
		\warning
*/
void CTask::SendMessage( MSG_Q_ID msgQId, void *pMsg )
{
#ifndef _WIN32
	if( ERROR == msgQSend( msgQId, (char *) pMsg, m_uiQueueSize, WAIT_FOREVER, MSG_PRI_NORMAL ) ) {
		int noError = errnoGet();
		logMsg("[msgQSend] errno[0x%x]\n", noError,0,0,0,0,0);

		// printErrno( noError );
	}
#else

	m_cond.LIGSetEvent();

#endif
}

void CTask::SendMessage( SQMsg *psqMsg )
{
	SQMsg sqMsg;

	sqMsg.uiOpcode = psqMsg->uiOpcode;
	sqMsg.usSize = psqMsg->usSize;
	memcpy( sqMsg.x.buf, & psqMsg->x.buf, sqMsg.usSize);

	PushMsg(sqMsg); // 쓰레드 처리를 위해 큐에 집어넣고 빠지기.
	m_cond.LIGSetEvent();

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CTask::SendMessage
		\author   조철희
		\param    msgQId 인자형태 MSG_Q_ID
		\param    pMsg 인자형태 void *
		\param    options 인자형태 int
		\return   void
		\version  0.0.27
		\date     2008-06-18 16:35:02
		\warning
*/
void CTask::SendMessage( MSG_Q_ID msgQId, void *pMsg, int options )
{
#ifndef _WIN32
	if( ERROR == msgQSend( msgQId, (char *) pMsg, m_uiQueueSize, options, MSG_PRI_NORMAL ) ) {
		int noError = errnoGet();
		logMsg("[mssQSend] errno[0x%x]\n", noError,0,0,0,0,0);

		// printErrno( noError );
	}
#endif
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CTask::SendMessage
		\author   조철희
		\param    msgQId 인자형태 MSG_Q_ID
		\param    pMsg 인자형태 void *
		\param    options 인자형태 int
		\param    size 인자형태 int
		\return   void
		\version  0.0.35
		\date     2008-08-12 15:21:12
		\warning
*/
void CTask::SendMessage( MSG_Q_ID msgQId, void *pMsg, int options, int size )
{
#ifndef _WIN32
	if( ERROR == msgQSend( msgQId, (char *) pMsg, size, options, MSG_PRI_NORMAL ) ) {
		int noError = errnoGet();
		logMsg("[mssQSend] errno[0x%x]\n", noError,0,0,0,0,0);

		// printErrno( noError );
	}
#else
	memcpy( m_pqMsg, pMsg, size );

	//ParseMessage();

#endif
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CTask::SendMessageWaitEcho
		\author   조철희
		\param    pMsg 인자형태 void *
		\param    time_out 인자형태 int
		\return   void
		\version  0.0.87
		\date     2009-09-01 13:47:27
		\warning
*/
void CTask::SendMessageWaitEcho( void *pMsg, int time_out )
{
	// printf( "\n*Wait until receiving the echo message in %s Task." , m_TaskName );
	SendMessage( m_msgQId, pMsg );
	WaitEchoMessage( time_out );
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CTask::WaitEchoMessage
		\author   조철희
		\param    timeout 인자형태 int
		\return   BOOL
		\version  0.0.1
		\date     2008-05-01 13:10:56
		\warning
*/
BOOL CTask::WaitEchoMessage( int timeout )
{
#ifndef _WIN32
	int noError;

	// 세마포아를 완전히 비운 상태에서 시작하게 함.
	SendEchoMessage();
	if( ERROR == semTake( m_semEcho, 1L ) ) {
		noError = errnoGet();

		if( noError != S_objLib_OBJ_TIMEOUT ) {
			printErrno( noError );
			WhereIs;
		}
	}

	if( ERROR == semTake( m_semEcho, timeout ) ) {
		noError = errnoGet();

		if( noError != S_objLib_OBJ_TIMEOUT ) {
			printErrno( noError );
			WhereIs;
		}

		return FALSE;
	}

#endif

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CTask::SendEchoMessage
		\author   조철희
		\return   void
		\version  0.0.1
		\date     2008-05-01 13:31:41
		\warning
*/
void CTask::SendEchoMessage()
{
#ifndef _WIN32

	//Printf( "S[%s]" , m_taskName );
	if( ERROR == semGive( m_semEcho ) ) {
		int noError = errnoGet();

		printErrno( noError );
	}
#endif
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CTask::MsgQShow
		\author   조철희
		\return   void
		\version  0.0.1
		\date     2008-07-15 16:09:13
		\warning
*/
void CTask::MsgQShow()
{
#ifndef _WIN32
	msgQShow( m_msgQId, 1 );
#endif
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CTask::CreateTimer
		\author   조철희
		\return   void
		\version  0.0.33
		\date     2008-07-23 02:23:48
		\warning
*/
void CTask::CreateTimer( UINT tv_sec, UINT tv_millisec )
{
#ifndef _WIN32
	int stat;
	// 타이머 인터럽트 설정
	/* create a new timer and put its id in timerId */
	stat = timer_create( CLOCK_REALTIME, NULL, & m_TimerId );
	if( stat != 0 ) {
		int noError = errnoGet();
		printErrno( noError );
	}

	/* When the timer goes off we want to call alarmHandle */
	stat = timer_connect( m_TimerId, (VOIDFUNCPTR) CTask::TimerInstance, (int) this );
	if( stat != 0 ) {
		int noError = errnoGet();
		printErrno( noError );
	}

#endif

	m_uTimer = 0;

	// 타이머 값이 있으면 타이머를 바로 설정한다.
	if( tv_sec != 0 || tv_millisec != 0 ) {
		RequestSetupTime( tv_sec, tv_millisec );
	}
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    TimerInstance
		\author   조철희
		\param    tTimer 인자형태 void *
		\param    arg 인자형태 int
		\return   void
		\version  0.0.33
		\date     2008-07-24 16:01:06
		\warning
*/
void CTask::TimerInstance( void *tTimer, int arg )
{
	CTask *pSelf;

	pSelf = ( CTask * ) arg;

	++ ( pSelf->m_uTimer );
	pSelf->Timer();
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CTask::RequestSetupTime
		\author   조철희
		\param    tv_sec 인자형태 UINT
		\param    tv_millisec 인자형태 UINT
		\return   void
		\version  0.0.50
		\date     2008-10-08 11:27:04
		\warning
*/
void CTask::RequestSetupTime( UINT tv_sec, UINT tv_millisec )
{
#ifndef _WIN32
	struct itimerspec tv;

	/* timer expiration */
	tv.it_value.tv_sec = tv_sec;
	tv.it_value.tv_nsec = tv_millisec * 1000000;

	/* timer period (reload value) */
	tv.it_interval.tv_sec = 0;
	tv.it_interval.tv_nsec = 0;

	if( m_SecTmier == 0 && m_MillisecTimer == 0 ) {
		m_SecTmier = tv_sec;
		m_MillisecTimer = tv_millisec;
	}

	SetTimer( & tv );

#endif
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CTask::RequestSetupTime
		\author   조철희
		\return   void
		\version  0.0.86
		\date     2009-08-21 19:14:26
		\warning
*/
void CTask::RequestSetupTime()
{
	RequestSetupTime( m_SecTmier, m_MillisecTimer );
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CTask::EmptyQueue
		\author   조철희
		\return   void
		\version  0.0.41
		\date     2008-08-24 15:47:30
		\warning
*/
void CTask::EmptyQueue()
{
	char *pMsg;

	pMsg = ( char * ) malloc( m_uiQueueSize * sizeof(char) );
#ifndef _WIN32
	while( ERROR != msgQReceive( m_msgQId, (char *) pMsg, m_uiQueueSize, (int)(10*OS_ONE_MILLISEC) ) ) {
		printf( "/" );
	}
#endif

	free( pMsg );
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CTask::Suspend
		\author   조철희
		\return   void
		\version  0.0.55
		\date     2008-11-09 10:00:12
		\warning
*/
void CTask::Suspend()
{
#ifndef _WIN32
	taskSuspend( m_TaskId );

#endif
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CTask::Resume
		\author   조철희
		\return   void
		\version  0.0.87
		\date     2009-08-31 17:09:07
		\warning
*/
void CTask::Resume()
{
#ifndef _WIN32
	taskResume( m_TaskId );

#endif
}

bool CTask::GetMsgFromQ(SQMsg& i_stMsg)
{
	bool bRtn = false;

	if(m_queMsg.size() != 0)
	{		
		ScopedLock lock(&m_QLock);

		i_stMsg = m_queMsg.front();
		m_queMsg.pop();
		lock.unlock();

		bRtn = true;

		TRACE( "\nTASK[%s]...GetMsg OP[0x%2x], Size[%d]" , m_taskName, i_stMsg.uiOpcode, i_stMsg.usSize );
	}
	//TRACE("[link1] 메시지 queue 크기 : %d\n", m_queMsg.size() );
	return bRtn;
}

void CTask::PushMsg(SQMsg& i_stMsg)
{
	ScopedLock lock(&m_QLock);

	m_queMsg.push(i_stMsg);

	//TRACE("[LINK1] QSize = %d\n", m_queMsg.size());
}

void CTask::DeleteAllQData()
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

/**
  * @brief		
  * @return 	void
*/
void CTask::CheckQueueMsg()
{
	UINT qSize;

	qSize = m_queMsg.size();
	if( qSize > MAX_QUEUE_SIZE_OF_LOBMNGR_ ) {
		m_bDangerOfQueueBufferFull = true;
		printf( "[%s]에서 큐 사이즈[%d] 를 초과하고 있습니다.", m_taskName, qSize );

		if( qSize >= MAX_LIMIT_QUEUE_SIZE_OF_LOBMNGR_ ) {
			m_queMsg.empty();
			printf( "[%s]에서 처리할 큐 사이즈[%d] 를 초과하여 큐에 있는 데이터를 삭제했습니다.", m_taskName, qSize );
		}

	}
	else {
		if( m_bDangerOfQueueBufferFull == true ) {
			printf( "[%s]에서 큐 사이즈[%d] 를 풀고 있습니다.", m_taskName, qSize );
		}
		m_bDangerOfQueueBufferFull = false;

	}
}

