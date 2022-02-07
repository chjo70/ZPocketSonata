/*
 * 본 문서는 시스템을 정의하는 테이블과 운영체계 또는 컴파일러에 의존하여 정의한다.
 * */

#ifndef _GLOBALS_H
#define _GLOBALS_H

#include "../Utils/cmultiserver.h"
#include "../Utils/csingleserver.h"
#include "../Utils/csingleclient.h"

#include "../Thread/cemittermerge.h"
#include "../Thread/ctaskmngr.h"
#include "../Thread/curbit.h"
#include "../Thread/cusercollect.h"
#include "../Thread/csignalcollect.h"
#include "../Thread/cdetectanalysis.h"
#include "../Thread/ctrackanalysis.h"
#include "../Thread/cscananalysis.h"

#include "../Utils/clog.h"



// 전역 변수를 정의한다.
#ifdef _MAIN_GLOBALS_

// 신호 분석 관련 쓰레드
CTaskMngr *g_pTheTaskMngr;
CUrBit *g_pTheUrBit;
CUserCollect *g_pTheUserCollect;
CEmitterMerge *g_pTheEmitterMerge;
CSignalCollect *g_pTheSignalCollect;
CDetectAnalysis *g_pTheDetectAnalysis;
CTrackAnalysis *g_pTheTrackAnalysis;
CScanAnalysis *g_pTheScanAnalysis;

// 통신 관련 쓰레드
CMultiServer *g_pTheZYNQSocket;
CSingleClient *g_pTheCCUSocket;
CSingleClient *g_pThePMCSocket;

// 기타 객체
CLog *g_pTheLog;
CSysConfig *g_pTheSysConfig;

// 위협 관리 시스템 변수 값
CELEnvironVariable *g_pTheELEnvironVariable;


// 타스크 및 쓰레드 포인터
vector<CThread *> g_vecThis;


#if defined(_ELINT_) || defined(_XBAND_)
LONG g_lOpInitID;

#elif _POCKETSONATA_


#elif _SONATA_

#else


#endif


#else
extern CTaskMngr *g_pTheTaskMngr;
extern CUrBit *g_pTheUrBit;
extern CUserCollect *g_pTheUserCollect;
extern CEmitterMerge *g_pTheEmitterMerge;
extern CSignalCollect *g_pTheSignalCollect;
extern CDetectAnalysis *g_pTheDetectAnalysis;
extern CTrackAnalysis *g_pTheTrackAnalysis;
extern CScanAnalysis *g_pTheScanAnalysis;

extern CLog *g_pTheLog;
extern CSysConfig *g_pTheSysConfig;

extern CMultiServer *g_pTheZYNQSocket;
extern CSingleClient *g_pTheCCUSocket;
extern CSingleClient *g_pThePMCSocket;

// 신호 분석 관련 정보
extern CELEnvironVariable *g_pTheELEnvironVariable;

// 쓰레드 관련 정보
extern vector<CThread *> g_vecThis;

#if defined(_ELINT_) || defined(_XBAND_)



#elif _POCKETSONATA_


#elif _SONATA_

#else


#endif

#endif


#ifdef __cplusplus
extern "C"
{
#endif

extern void _ShowProgramTitle( void );
extern char *_GetProgramVersion();

#ifdef __cplusplus
}
#endif

class GlobalMemberFunction {

public:
	static SEnvironVariable *GetEnvrionVariable()
	{
		if( g_pTheELEnvironVariable != NULL ) {
		}
		else {
			g_pTheELEnvironVariable = new CELEnvironVariable();
			//TRACE( "Hellow The g_pTheELEnvironVariable is null pointer !!" );
		}

        return g_pTheELEnvironVariable->GetEnvrionVariable();
	}

};





#define LOG_LINEFEED                    g_pTheLog->LogMsg( enLineFeed, __FUNCTION__, __FILE__, __LINE__, "" )

#define LOGMSG( A, B )                  g_pTheLog->LogMsg( A, __FUNCTION__, __FILE__, __LINE__, B )
#define LOGMSG1( A, B, C )              g_pTheLog->LogMsg( A, __FUNCTION__, __FILE__, __LINE__, B, C )
#define LOGMSG2( A, B, C, D )           g_pTheLog->LogMsg( A, __FUNCTION__, __FILE__, __LINE__, B, C, D )
#define LOGMSG3( A, B, C, D, E )        g_pTheLog->LogMsg( A, __FUNCTION__, __FILE__, __LINE__, B, C, D, E )
#define LOGMSG4( A, B, C, D, E, F )     g_pTheLog->LogMsg( A, __FUNCTION__, __FILE__, __LINE__, B, C, D, E, F )
#define LOGMSG5( A, B, C, D, E, F, G )  g_pTheLog->LogMsg( A, __FUNCTION__, __FILE__, __LINE__, B, C, D, E, F, G )


#define Log                             g_pTheLog->LogMsg


#define LOGENTRY                        g_pTheLog->LogMsg( enNormal, __FUNCTION__, __FILE__, __LINE__, NULL )


#endif // _SYSTEM_H
