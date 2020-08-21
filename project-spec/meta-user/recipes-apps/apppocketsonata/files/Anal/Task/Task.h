// Task.h: interface for the CTask class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TASK_H__030A12DD_9634_452D_AAC8_CA7D6F7C5B42__INCLUDED_)
#define AFX_TASK_H__030A12DD_9634_452D_AAC8_CA7D6F7C5B42__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef _WIN32
#include <queue>
using namespace std;

#include <time.h>

#include "LIGCondition.h"
#include "LIGThread.h"
#include "./ThreadLib/LIGLock.h"

#include "../INC/OS.h"
#include "../../OFP/EmitterMerge/PositionEstimationAlg.h"
#include "../../OFP/EmitterMerge/ELEmitterDataType.h"
#include "../INC/structs.h"
//#include "../OFP_Main.h"
#define MSG_Q_ID				UINT

#elif defined(__linux__)

#else
#include <msgQLib.h>
#include <semLib.h>
#include <rngLib.h>
#include <taskLib.h>


#endif

#ifdef __cplusplus

#define MSG_Q_BUFFER				(100000)

// 위협 처리에서 20개 이상일 때 큐 버퍼 사이즈 출력
#define MAX_QUEUE_SIZE_OF_LOBMNGR_							(100)				// (20)

#define MAX_LIMIT_QUEUE_SIZE_OF_LOBMNGR_				(10000)					// (10000)


typedef struct 
{
	unsigned int uiOpcode;
	unsigned short usSize;

	union {
		unsigned char buf[MSG_Q_BUFFER];

		// 수집 과제
		SCollectingList stCollectingList;

		// PDW 데이터
		STR_PDWDATA stPDWData;

		// LOB 데이터
		STR_LOBDATAEXT stLOBDataExt;

		// ABT 데이터
		STR_ABTDATAEXT stABTDataExt;

	} x;

} SQMsg ;

class CTask : public LIGThread
{
private:
	char *m_pqMsg;

#ifndef _WIN32
	timer_t m_TimerId;
#endif

protected:
	int m_TaskId;
	int m_QueueSize;
	int m_RingSize;

	bool m_bDangerOfQueueBufferFull;

	char m_taskName[10];
	UINT m_uTimer;
	int m_SecTmier;
	int m_MillisecTimer;

	std::queue<SQMsg> m_queMsg;	

	LIGLock m_QLock;

#ifdef _WIN32
	LIGCondition m_cond;

#else
	SEM_ID m_semEcho;
	RING_ID m_ringId;
	

#endif

	MSG_Q_ID m_msgQId;

public:
	void SendMessageWaitEcho( void *pMsg, int time_out );
	void RequestSetupTime();
	void Suspend();
	void Resume();
	void EmptyQueue();
	void CreateTimer( UINT tv_sec=0, UINT tv_millisec=0 );
	void RequestSetupTime( UINT tv_sec, UINT tv_millisec=0 );
	void MallocBuffer();
	void FreeBuffer();
	void MsgQShow();

	void SendEchoMessage();
	BOOL WaitEchoMessage( int timeout=WAIT_FOREVER );
	void SendMessage( MSG_Q_ID msgQId, void *pMsg );
	void SendMessage( MSG_Q_ID msgQId, void *pMsg, int options );
	void SendMessage( MSG_Q_ID msgQId, void *pMsg, int options, int size );
	void SendMessage( SQMsg *psqMsg );
	void ReceiveMessage( MSG_Q_ID msgQId, void *pMsg, int timeout=WAIT_FOREVER );
	void ReceiveMessage();

	void TaskSpawn( char* name, int priority=100, int options = VX_FP_TASK, int stack = 20 * 1024 );
	void InitVar();
	void InitTask();

	inline void ResetTimerCounter() { m_uTimer=1; }
	inline void *GetQueueMessage() { return m_pqMsg; }

#ifdef _WIN32
	bool GetMsgFromQ(SQMsg& i_stMsg);
	void PushMsg(SQMsg& i_stMsg);
	void DeleteAllQData();
	void CheckQueueMsg();

	inline void SendMessage( void *pMsg) { SendMessage(m_msgQId, pMsg); }
	inline void SendMessage( void *pMsg, int options ) { SendMessage( m_msgQId, pMsg, options ); }
	inline void SendMessage( void *pMsg, int options, int size ) { SendMessage( m_msgQId, pMsg, options, size ); }
	inline void SendMessage() { SendMessage( m_msgQId, m_pqMsg ); }

	inline void SetTimer( struct itimerspec *pTime ) { }
	inline void StopTimer() { }
	virtual BOOL ParseMessage( SQMsg *psqMsg )=0;

#else
	inline void SetTimer( struct itimerspec *pTime ) { timer_settime( m_TimerId, CLOCK_REALTIME, pTime, NULL); }
	inline void StopTimer() { timer_cancel( m_TimerId ); }

	inline void SendMessage( void *pMsg ) { SendMessage( m_msgQId, pMsg ); }
	inline void SendMessage( void *pMsg, int options ) { SendMessage( m_msgQId, pMsg, options ); }
	inline void SendMessage( void *pMsg, int options, int size ) { SendMessage( m_msgQId, pMsg, options, size ); }
	inline void SendMessage() { SendMessage( m_msgQId, m_pqMsg ); }

#endif

	virtual void Run()=0;
	virtual void Timer()=0;

	static void Instance( CTask *pSelf ) { pSelf->Run(); }
	static void TimerInstance( void *tTimer, int arg );

	//CTask( int queue_size=sizeof(STR_QUEUE_MESSAGE), int ring_size=0 );
	CTask();
	virtual ~CTask();

};

#endif

#endif // !defined(AFX_TASK_H__030A12DD_9634_452D_AAC8_CA7D6F7C5B42__INCLUDED_)
