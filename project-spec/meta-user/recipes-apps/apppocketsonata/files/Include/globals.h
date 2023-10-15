/**

    @file      globals.h
    @brief     전역 변수 및 클르스 객체를 선언 합니다.
    @details   ~
    @author    조철희
    @date      15.03.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/
#pragma once


#ifdef _LOG_

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

#include "../Thread/cclocktimer.h"

#else
#include "../System/csysconfig.h"
#include "../Anal/EmitterMerge/ELEnvironVariableMngr.h"

#endif

#include "../Utils/clog.h"


// 전역 변수를 정의한다.
#ifdef _MAIN_GLOBALS_

#ifdef _LOG_
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
//CMultiServer *g_pTheZYNQSocket;
CSingleClient *g_pTheCCUSocket;
//CSingleClient *g_pThePMCSocket;

CClockTimer *g_pTheClockTimer;

#ifdef _SIM_PDW_
STR_RADAR_PDW g_stRadarPDW;
#endif

#else


#endif

// 기타 객체
CLog *g_pTheLog;


#ifdef _MSC_VER
CSysConfig *g_pTheSysConfig;

#else
extern CSysConfig *g_pTheSysConfig;

#endif


// 위협 관리 시스템 변수 값
CELEnvironVariable *g_pTheELEnvironVariable;


//unsigned int _spAnalMinPulseCount;



// 타스크 및 쓰레드 포인터
//vector<CThread *> g_vecThread;




#if defined(_ELINT_) || defined(_XBAND_)
LONG g_lOpInitID;

#elif defined(_POCKETSONATA_) || defined(_712_)


#elif _SONATA_

#else


#endif

// 장치 타입으로 이 값을 확인해서 장치에 맞게 실행하도록 한다.
//#ifndef _ENUNIT_TYPE
//#define _ENUNIT_TYPE
//ENUM_UnitType g_enUnitType;
// #ifdef _MSC_VER
// __declspec( dllexport ) ENUM_UnitType g_enUnitType;
// #else
// ENUM_UnitType g_enUnitType;
// #endif
//#endif


#else
#ifdef _LOG_
extern CTaskMngr *g_pTheTaskMngr;
extern CUrBit *g_pTheUrBit;
extern CUserCollect *g_pTheUserCollect;
extern CEmitterMerge *g_pTheEmitterMerge;
extern CSignalCollect *g_pTheSignalCollect;
extern CDetectAnalysis *g_pTheDetectAnalysis;
extern CTrackAnalysis *g_pTheTrackAnalysis;
extern CScanAnalysis *g_pTheScanAnalysis;

#ifdef _SIM_PDW_
extern STR_RADAR_PDW g_stRadarPDW;
#endif


//extern CMultiServer *g_pTheZYNQSocket;
extern CSingleClient *g_pTheCCUSocket;
extern CSingleClient *g_pThePMCSocket;

extern CClockTimer *g_pTheClockTimer;


// 쓰레드 관련 정보
extern vector<CThread *> g_vecThread;

extern vector<CTimer *> g_vecTimer;

#else


#endif

extern CSysConfig *g_pTheSysConfig;
extern CELEnvironVariable *g_pTheELEnvironVariable;

extern unsigned int _spAnalMinPulseCount;

extern CLog *g_pTheLog;



// 신호 분석 관련 정보





#if defined(_ELINT_) || defined(_XBAND_)



#elif defined(_POCKETSONATA_) || defined(_712_)


#elif _SONATA_

#else


#endif


#endif


#ifdef __cplusplus
extern "C"
{
#endif

extern void _ShowProgramTitle( void );
extern const char *_GetProgramVersion();

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

#ifdef _LOG_

#ifdef __VXWORKS__
#define Log( A, ... )                   if( A ) g_pTheLog->LogMsg( A, __FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__ )

#else

#ifdef _LOG_ANALTYPE_
#define Log( A, ... )                   if( GetLogAnalType() ) g_pTheLog->LogMsg( A, __FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__ )
#else
#define Log( A, ... )                   printf( ##__VA_ARGS__ )

#endif

#endif

#define LOG_LINEFEED                    g_pTheLog->LogMsg( enLineFeed, __FUNCTION__, __FILE__, __LINE__, "" )
#define LOGENTRY                        g_pTheLog->LogMsg( enNormal, __FUNCTION__, __FILE__, __LINE__, NULL )

#else


#define Log( A, ... )                   g_pTheLog->LogMsg( A, __FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__ )

#ifdef _MSC_VER
#define LOG_LINEFEED                    TRACE0( "\n" )
#define LOGMSG( A, B )                  TRACE( B )
#define LOGMSG1( A, B, C )              TRACE( B, C )
#define LOGMSG2( A, B, C, D )           TRACE( B, C, D )
#define LOGMSG3( A, B, C, D, E )        TRACE( B, C, D, E )
#define LOGMSG4( A, B, C, D, E, F )     TRACE( B, C, D, E, F )
#define LOGMSG5( A, B, C, D, E, F, G )  TRACE( B, C, D, E, F, G )



#else


#endif


#endif

