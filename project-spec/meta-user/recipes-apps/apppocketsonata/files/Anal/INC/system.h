﻿/*!
  \file     System.h
  \brief    interface for the 시스템 관련 정의문
	\version  0.0.1
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEM_H__F88C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_)
#define AFX_SYSTEM_H__F88C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



//////////////////////////////////////////////////////////////////////////
#define VERSION_LOGO									"09.00"
#define VERSION_LOGO_MESSAGE_X				CENTER_WIDTH
#define VERSION_LOGO_MESSAGE_Y				(124)


#define AIRCRAFT_TYPE									"A50"
#define AIRCRAFT_TYPE_MESSAGE_X				CENTER_WIDTH
#define AIRCRAFT_TYPE_MESSAGE_Y				(180)


#define SYSTEM_WARM_UP								"LIGNEX1"
#define WARM_UP_MESSAGE_X							CENTER_WIDTH
#define WARM_UP_MESSAGE_Y							(70)

// Handoff 메시지 위치
#define	HANDOFF_MESSAGE_X							CENTER_WIDTH
#define	HANDOFF_MESSAGE_Y							(8)

// System Text 메시지 위치
#define	SYSTEST_X											(90)
#define	SYSTEST_Y											(190)

// TARGET_SEPERATE_SYMBOL_INDEX
#define	TARGET_SEPERATE_X							(0xfd)
#define	TARGET_SEPERATE_Y							(0x88)

// UNKNOWN_SYMBOL_INDEX
#define	UNKNOWN_X											(0xf5)
#define	UNKNOWN_Y											(0x88)

// OPEN_PRIORITY_INDEX
#define	OPEN_PRIORITY_X								(0xed)
#define	OPEN_PRIORITY_Y								(0x88)

// ALTITUDE_INDEX
#define	ALTITUDE_X										(0xfd)
#define	ALTITUDE_Y										(0x78)

// ACTVITY_INDEX
#define	ACTVITY_X											(0xf5)
#define	ACTVITY_Y											(0x78)

// HANDOFF_INDEX
#define	HANDOFF_X											(0xed)
#define	HANDOFF_Y											(0x78)

// SYSTEST_INDEX
#define	STYTEST_X											(0x04)
#define	STYTEST_Y											(0x88)

// CBIT_INDEX
#define	CBIT_X												(0x04)
#define	CBIT_Y												(0x78)

// MISSILE_INDEX
#define	MISSILE_X											(0x12)
#define	MISSILE_Y											(0x88)

// OP_MODE_INDEX
#define	OP_MODE_X											(0x12)
#define	OP_MODE_Y											(0x78)



//////////////////////////////////////////////////////////////////////////
//
// 신호측정 발생판 초기화 관련 설정값
#define INIT_CHANNEL_MODE						(NORMAL_MODE)	// 정상 모드로 설정함.
#define INIT_CHANNEL_COMPENSATION		(USE_CHANNEL_COMPENSATION)			// 채널 보정 사용 여부를 정함.
#define	INIT_PA_THRESHOLD_BAND1			(-65) //(-67.0)				// 단위는 dB, -74.6875 부터 +5 이어야 함.
#define	INIT_PA_THRESHOLD_BAND2			(-60) //(-67.0)				// 단위는 dB, -74.6875 부터 +5 이어야 함.
#define	INIT_PA_THRESHOLD_BAND3			(-60) //(-67.0)				// 단위는 dB, -74.6875 부터 +5 이어야 함.
#define	INIT_PA_THRESHOLD_BAND4			(-60) //(-67.0)				// 단위는 dB, -74.6875 부터 +5 이어야 함.
#define	INIT_PA_THRESHOLD_CD_BAND		(-50) //(-67.0)				// 단위는 dB, -74.6875 부터 +5 이어야 함.
#define INIT_CW_CHOPPING_COUNT			(30)	// (18)					// 단위는 개수, 0 개 부터 255 개
#define INIT_FMOP_THRESHOLD_CD_BAND	(5.0)									// 단위는 MHz, 0 MHz 부터 78.75 MHz
#define INIT_FMOP_THRESHOLD					(10.0)								// 단위는 MHz, 0 MHz 부터 78.75 MHz
#define INIT_CW_PULSEWIDTH					(130.0)								// 단위는 usec, 0 us 부터 204.6 us
#define INIT_BLANKING_MODE					(NOTUSE_BLANKING_MODE)// 블랭킹 사용함.
#define INIT_AUTO_RX_THRESHOLD_MODE	(MANUAL_RX_MODE)			// 자동 수신 임계값 모드 설정함.


//////////////////////////////////////////////////////////////////////////
//
// 비트 수행시간 정의
#define CBIT_RUN_PERIOD							(30)			// 단위는 초.


//////////////////////////////////////////////////////////////////////////
// 신호분석 관련 초기화 관련 설정값

// 비트 수행시의 펄스 개수 및 시간 정의
#define BIT_PDW_COUNT									(10)
#define BIT_PDW_COLLECT_TIMEOUT				(200 * PG_ONE_MILLISEC)

// 비트 수행시의 PDW 제원 정보
#define BIT_AOA												(0x1111)
#define BIT_FREQ											(0x1111)
#define BIT_PA												(0x1111)
#define BIT_PW												(0x1111)

// 비트 수행시의 여유 범위
#define BIT_AOA_MARGIN								(0x11)
#define BIT_FREQ_MARGIN								(0x11)
#define BIT_PA_MARGIN									(0x11)
#define BIT_PW_MARGIN									(0x11)

// 추적 분석판 설정시의 펄스 개수 정의
// CW 신호에 대한 펄스 개수 정의
#define CW_PULSECOUNT									(50)				// CW 일때의 신호 수집 개수

// 펄스정보 생성판의 신호에 따른 설정값 정의
#define DEFAULT_COLLECTION_TIME				(200*PG_ONE_MILLISEC)
#define DEFAULT_CO_COLLECTION					(200)
#define SCAN_CO_COLLEC

// 스캔 분석을 하기 위한 펄스 개수 정의
#define SCN_NORM_PULSE_COUNT					(1024)

// 스캔 신호에 대한 펄스 개수 정의
#define KWN_NORM_PULSE_COUNT					(100)				// 스캔 실패일 때의 펄스 개수
#define KWN_NO_SCAN_PULSE_COUNT				(200)				// 스캔 분석 중일 때의 펄스 개수
#define KWN_CIRCULAR_PULSE_COUNT			(100)				// 원형 스캔인 경우의 펄스 개수
#define KWN_STEADY_PULSE_COUNT				(50)				// 고정 또는 원추형일때의 펄스 개수

#define MAX_EMITTER_NO								(256)				// 최대 에미터 개수

#define MAX_THREAT_NO									(256)				// 최대 위협 개수


// 추적필터판을 사용하지 않은 에미터 관리 주기
#define MANAET_RUN_PERIOD							(1)					// 단위는 초.


// 수집용 펄스 개수
#define NEW_COLLECT_PDW								(4096)			// 탐지 분석용 최대 수집 개수
#define KWN_COLLECT_PDW								(200)				// 추적 분석용 최대 수집 개수
#define SCN_COLLECT_PDW								(2000)			// 스캔 분석용 최대 수집 개수


// 한번에 수집한 최대 개수
#define PDW_ONE_BLOCK_SIZE						(256)			// NEW_COLLECT_PDW, KWN_COLLECT_PDW, SCN_COLLECT_PDW 중에서 가장 큰것

// 비트 수집용 버퍼 크기
#define MAX_BIT_COLLECT_COUNT					(20)				// NEW_COLLECT_PDW, KWN_COLLECT_PDW, SCN_COLLECT_PDW 중에서 가장 큰것

// 소프트웨어 필터 개수
#define	NEW_NO_BANK										(5)
#define KNOWN_NO_FILTER								(32)
#define SCAN_NO_FILTER								(32)

#define	MAX_FIRE_INFO_ITEM						(200)

// 소프트웨어 필터 시간 단위
#define	FILTER_ONE_SEC								(1000)				// 단위는 ms

//
#define KWN_TIMEOUT_NORMAL						(20*FILTER_ONE_SEC)
#define KWN_TIMEOUT_STEADY						(3*FILTER_ONE_SEC)
#define DEFAULT_DELETE_AET_TIME				(2*FILTER_ONE_SEC)		// 기본 에미터 삭제 시간
#define DEFAULT_DELETE_CW_AET_TIME		(10*FILTER_ONE_SEC)		// CW 에미터 삭제 시간


// 신호 식별 밴드 그룹화 정의
#define	MAX_FREQ_HZ										18398750			//!< 주파수 최대 값, Hz
#define MIN_FREQ_HZ 									500						//!< 주파수 최소 값

#define	NO_FEID_BAND									32						// 주파수 밴드 개수
#define FEID_FREQ_RES_HZ							90000					// 90 KHz 의 Histogram res.



// Jitter 와 Jitter 식별시의 지터율 고려한 식별
#define _spUDFMaxJitPerOver						(5)


// 식별 테이블을 위한 식별 최대 종류 개수 정의
#define MAX_HOWTO_ID									(20)


// Priority Mode 일때의 심벌 개수
#define MAX_SYMBOL_IN_PRIORITY_MODE		(5)


// 거리 추정 관련 정의
#define	MIN_ESTIMATED_DISTANCE				(0)
#define	MAX_ESTIMATED_DISTANCE				(129640)		// km


// 최대 로그 크기
// 최소 크기는 STR_QUEUE_LOG_MESSAGE 크기(3568바이트) 보다 커야 한다.
#define MAX_LOGBUFFER_SIZE						sizeof(STR_QUEUE_LOG_MESSAGE)		// 10KB씩 로그 데이터를 압축해서 저장한다.


//
// 대역별 주파수 경계값 정의

// CD 대역의 주파수 경계값 정의
#define FREQ_BORDER_BAND5_1_LOW					(500)
#define FREQ_BORDER_BAND5_1_HGH					(600)

// 대역1의 주파수 경계값 정의
#define FREQ_BORDER_BAND1_2_LOW					(500)
#define FREQ_BORDER_BAND1_2_HGH					(600)

#define FREQ_BORDER_BAND1_5_LOW					(500)
#define FREQ_BORDER_BAND1_5_HGH					(600)

// 대역2의 주파수 경계값 정의
#define FREQ_BORDER_BAND2_1_LOW					(500)
#define FREQ_BORDER_BAND2_1_HGH					(600)

#define FREQ_BORDER_BAND2_3_LOW					(9800)
#define FREQ_BORDER_BAND2_3_HGH					(10000)

// 대역3의 주파수 경계값 정의
#define FREQ_BORDER_BAND3_2_LOW					(500)
#define FREQ_BORDER_BAND3_2_HGH					(600)

#define FREQ_BORDER_BAND3_4_LOW					(500)
#define FREQ_BORDER_BAND3_4_HGH					(600)

// 대역4의 주파수 경계값 정의
#define FREQ_BORDER_BAND4_3_LOW					(500)
#define FREQ_BORDER_BAND4_3_HGH					(600)

/////////////////////////////////////////////////////////////////////////////////////////
//  for RSA configuration definition
//
#define   _spScnLev					6

/////////////////////////////////////////////////////////////////////////////////////////
//  for RXDF configuration definition
//
//  Band 1
#define   _spBd1LvlThr      IDIV( ( -54 - _spPAoffset ), _spAMPres )    // -54 dB
#define   _spBd1FmpThr      0x60
#define   _spBd1PmpThr      0x60
#define   _spBd1AntOffLeft  0x60
#define   _spBd1AntOffRght  0x60
#define   _spBd1BlkAnt      0x9090
#define   _spBd1NotFlt      0x60
#define   _spBd1PinAtt      0x60
#define   _spBd1BandEn      0x1

//  Band 2
#define   _spBd2LvlThr      IDIV( ( -53 - _spPAoffset ), _spAMPres )    // -53 dB
#define   _spBd2FmpThr      0x60
#define   _spBd2PmpThr      0x60
#define   _spBd2AntOffLeft  0x60
#define   _spBd2AntOffRght  0x60
#define   _spBd2BlkAnt      0x9090
#define   _spBd2NotFlt      0x60
#define   _spBd2PinAtt      0x60
#define   _spBd2BandEn      0x1

//  Band 3
#define   _spBd3LvlThr      IDIV( ( -52 - _spPAoffset ), _spAMPres )  // -52 dB
#define   _spBd3FmpThr      0x60
#define   _spBd3PmpThr      0x60
#define   _spBd3AntOffLeft  0x60
#define   _spBd3AntOffRght  0x60
#define   _spBd3BlkAnt      0x9090
#define   _spBd3NotFlt      0x60
#define   _spBd3PinAtt      0x60
#define   _spBd3BandEn      0x1

/////////////////////////////////////////////////////////////////////////////////////////
//  
//  RXDF Direction & Freq Error
#ifdef _ELINT_
#define   _spRxdfAoa				(UDIV( 8, _spAOAres ))      // 14( 8 deg. )
#define   _spRxdfFrq				4     // about 5(=4*1.25)MHz, 

#elif defined(_POCKETSONATA_)
#define   _spRxdfAoa				(UDIV( 8, _spAOAres ))      // 14( 8 deg. )
#define   _spRxdfFrq				4     // about 5(=4*1.25)MHz,

#else

#define   _spRxdfAoaLow     (UDIV( 8, _spAOAres ))      // 14( 8 deg. )
#define   _spRxdfAoaMid     (UDIV( 5., _spAOAres ))     // 9 ( 5 deg. )
#define   _spRxdfAoaHgh     (UDIV( 3.5, _spAOAres ))    // 6 ( 3.5 deg. )

#define   _spRxdfFrqLow     2     // about 1.25(2*0.625)MHz
#define   _spRxdfFrqMid     2     // about 2.5(2*1.25)MHz
#define   _spRxdfFrqHgh     2     // 3(2*1.5) MHz

#endif

/////////////////////////////////////////////////////////////////////////////////////////
//  
//  Stable Toa Tolerance
#define   _spSpriTol        10      // 500 ns

/////////////////////////////////////////////////////////////////////////////////////////
//  for Identify, system parameter definition
//  Identify for Freq.
// debug, 99-12-09 19:44:46
#define     _spIdFixFrqLow	_spRxdfFrqLow 
#define     _spIdFixFrqMid  _spRxdfFrqMid 
#define     _spIdFixFrqHgh  _spRxdfFrqHgh 

#define     _spIdAgileFrqLow    100     /* 0 dB */
#define     _spIdAgileFrqMid    100     /* 0 dB */
#define     _spIdAgileFrqHgh    100     /* 0 dB */

//  Period of Freq.
#define   _spIdFrqPrd           50
#define   _spIdPriPrd           50

//  Identify for PRI.
#define   _spIdPri              10    // PRI tolerance of Id.
#define   _spIplMaxJitPer       15    // Jitter PRI tolerance of Id.

#define   _spIplMaxHopJitPer		20      // Hopping일때 최대 Jitter 율 허용값

//  Identify for scan period
#define   _spIdScnPrd       0     // Scan period tolerance of Id.

/////////////////////////////////////////////////////////////////////////////////////////
//  for Merge, system parameter definition
//  Merge for direction
//  debug, 1 -> 3, 00-09-20 09:43:31
#ifdef _ELINT_
#define   _spMgAoaEJ					IAOACNV( 15 )					// UMUL(15,_spAOAres)		// 15도
#define   _spMgAoaCD					IAOACNV( 30 )					// UMUL(30,_spAOAres)		// 30도
#define   _spMgFixFrqEJ				IFRQMhzCNV( 0, 10 )			// UMUL(3,1.25)					// res. 1.25 MHz
#define   _spMgFixFrqCD				IFRQMhzCNV( 0, 10 )			// UMUL(5,1.25)					// res. 1.25 MHz
#define   _spMgFixFrqBoundEJ	IFRQMhzCNV( 0, 10 )			// UMUL(6,1.25)					// res. 1.25 MHz
#define   _spMgFixFrqBoundCD	IFRQMhzCNV( 0, 10 )			// UMUL(10,1.25)					// res. 1.25 MHz

#elif defined(_POCKETSONATA_)
#define   _spMgAoaEJ					IAOACNV( 15 )					// UMUL(15,_spAOAres)		// 15도
#define   _spMgAoaCD					IAOACNV( 30 )					// UMUL(30,_spAOAres)		// 30도
#define   _spMgFixFrqEJ				IFRQMhzCNV( 0, 10 )			// UMUL(3,1.25)					// res. 1.25 MHz
#define   _spMgFixFrqCD				IFRQMhzCNV( 0, 10 )			// UMUL(5,1.25)					// res. 1.25 MHz
#define   _spMgFixFrqBoundEJ	IFRQMhzCNV( 0, 10 )			// UMUL(6,1.25)					// res. 1.25 MHz
#define   _spMgFixFrqBoundCD	IFRQMhzCNV( 0, 10 )			// UMUL(10,1.25)					// res. 1.25 MHz

#else
#error "컴파일러에 DEFINE 을 추가해야 합니다."


#endif



//  Merge for Agile freq.
#define   _spMgAgileFrqMean   50      // 10% of (mean-mean) -> 50
#define   _spMgAgileFrqIn     60      // 20% of (min-min)
#define   _spMgAgileFrqOut    40      // 10% of (max-max)
#define   _spMgAgileFrqLowPat   (3*_spRxdfFrqLow) // 10% of freq. low
#define   _spMgAgileFrqMidPat   (3*_spRxdfFrqMid) // 10% of freq. mid
#define   _spMgAgileFrqHghPat   (3*_spRxdfFrqHgh) // 10% of freq. hgh

// When modify the AET's freq and PRI, the tolerance freq. and pri value.
#define   _spMdAgileFrq     1000    // 1GHz(the difference of freq's max and min

//  Merge for PRI
#define   _spMgFixPri					(4*_spSpriTol)  // each Stable PRIs, merge, 1->4, debug, 00-09-20 09:43:31
#define   _spMgAgilePriMean   50      // 10% of (mean-mean) -> 50, debug 
#define   _spMgAgilePriIn     20      // 20% of (min-min)
#define   _spMgAgilePriOut    10      // 10% of (max-max)
#define   _spMgAgilePriPat    (4*_spSpriTol)  // 10% of freq. low

//  Merge for Period each Freq, PRI, and scan 
#define   _spMgFrqPrd						5     // 5% of period
#define   _spMgPriPrd						5     // 5% of period
#define   _spMgScnPrd						5     // 5% of period

//  Merge for Pattern Period
#define   _spMgJtrPer       4     // not use, from 99-07-23 13:37:55

// 펄스폭 병합 범위
#ifdef _ELINT_
#define   _spMgPW						ITOAusCNV( 100 )			//(100*_spOneMicrosec)
#else
#define   _spMgPW						(100*_spOneMicrosec)
#endif


#define   _spMdyMethod      2     // 2 -> 3

/////////////////////////////////////////////////////////////////////////////////////////
//  for tracking Info
//
// debug, 00-08-30 14:02:57
#define   _spFtFixFrqLow      (2*_spRxdfFrqLow)   // debug, 1 -> 4, 05년 이전 값은 4로 함. 
#define   _spFtFixFrqMid      (2*_spRxdfFrqMid)   // 연평도에서 Stable, Jitter 운용하는 함정 때문에 
#define   _spFtFixFrqHgh      (2*_spRxdfFrqHgh)   // 4 -> 2로 수정함.

#define   _spFtAgiFrqLow      (3*_spRxdfFrqLow)   // debug, 00-01-31 16:13:18
#define   _spFtAgiFrqMid      (3*_spRxdfFrqMid)   // debug, 00-01-31 16:13:18
#define   _spFtAgiFrqHgh      (3*_spRxdfFrqHgh)   // debug, 00-01-31 16:13:18
#define   _spFtAgiRatio       10                  // debug, 00-04-19 17:46:13

#define   _spFtPw             1000

#define   _spFtPa             5

#define   _spFtAoaLow         (_spRxdfAoaLow*5)
#define   _spFtAoaMid         (_spRxdfAoaMid*5)
#define   _spFtAoaHgh         (_spRxdfAoaHgh*5)

#define   _spMaxTimesAsScan   (1.8)     // 1.5 -> 3 -> 1.8(Lee) times of scan period, 99-10-27 11:08:24
#define   _spTimesAsPulsePerPrd (5)

//  debug, 00-04-12 11:14:06
#define   _spPdwFrqLowLow     0x031c  //  0.49812 GHz
#define   _spPdwFrqLowHgh     0x0c80  //  2.0000 GHz
#define   _spPdwFrqMidLow     0x023d  //  1.9975 GHz
#define   _spPdwFrqMidHgh     0x0ec0  //  6.0000 GHz
#define   _spPdwFrqHghLow     0x0056  //  5.9965 GHz
#define   _spPdwFrqHghHgh     0x1f9a  // 18.00400 GHz

// Track Windwo Cell's pulse count & time out for maximum and minimum
#define   _spPdwTkToLow       0x1
#define   _spPdwTkToHgh       0xf0
#define   _spPdwTkPcLow       50
#define   _spPdwTkPcHgh       500

//#define   _spScToStep1      30      // res. 10 ms, 300 ms
//#define   _spScToStep2      600     // 6.0 sec
//#define   _spScToStep3      1500    // 15 sec
//#define   _spScToStep4      3000    // 30 sec
//#define   _spScToStep5      7000    // 70 sec
// debug, 00-09-02 02:21:39
#define   _spScToStep1      600     // res. 10 ms, 600 ms
#define   _spScToStep2      1500    // 15.0 sec
#define   _spScToStep3      3000    // 30 sec
#define   _spScToStep4      7000    // 70 sec
#define   _spScToStep5      _spMaxVal32   // 70 sec

//#define   _spScToStep1      70      // 
//#define   _spScToStep2      700     // 
//#define   _spScToStep3      7000    // 
//#define   _spScToStep4      7000    // 

#define   _spScMinTimeOutiOfPrd (3.5)   // 3.5 배의 스캔주기 타임 아웃

#define   _spPdwPWLow       0x0000
#define   _spPdwPWHgh       0x07ff

#define   _spPdwPALow       0x0000
#define   _spPdwPAHgh       0x00ff

/////////////////////////////////////////////////////////////////////////////////////////
//  system parameter structure
//
#define   _spDelayScanStart     (1.5)   // times of ?

/////////////////////////////////////////////////////////////////////////////////////////
//  Minimum delete time
//
#define   _spDefaultDelTime     (10)

/////////////////////////////////////////////////////////////////////////////////////////
//  Track Anal Fail Count
//
#define     _spCoPrecStag       5
#define     _spCoPrecFrqPat     5
#define     _spCoPrecPriPat     5

/////////////////////////////////////////////////////////////////////////////////////////
//  Sending update minimum time
//
#define   _spUpdMinTimeTrk      1     // less than 1 sec
#define   _spUpdMinTimeNon      20      // less than 20 sec

/////////////////////////////////////////////////////////////////////////////////////////
//  Scan system parametes
//
#define   _spSampleTimeStep2    UMUL(  10, _spOneMilli )
#define   _spSampleTimeStep3    UMUL(  25, _spOneMilli )
#define   _spSampleTimeStep4    UMUL(  50, _spOneMilli )
#define   _spSampleTimeStep5    UMUL( 100, _spOneMilli )

#define   _spOffSampleStep1     100
#define   _spOffSampleStep2     20
#define   _spOffSampleStep3     8
#define   _spOffSampleStep4     4
#define   _spOffSampleStep5     2

#define   _spThresholdOfTrkSig  UMUL( 500, _spOneMilli )

#define		_spCWMinPulseCount		(10)

#define   _spCoNonWeighted      (10)

#define   _spIncThr             UDIV( 8, _spAMPres )    // 02-08-11

/////////////////////////////////////////////////////////////////////////////////////////
// 펄스열 추출 정의
#define     _spAnalMinPulseCount              (6)
#define     _spContiThresholdMinPulseCount    10

// Stable 에미터 최소 펄스 개수(누락 및 스캔 신호를 고려한)
/*! \bug  20 개에서 10개로 수정함.
    \date 2006-07-27 09:28:10, 조철희
*/
#define     _spAnalMinPulseStableEmitter      10    
#define     _spAnalMinPulseJitterEmitter      20

#define     _spMaxAoaQueueSize                4

/////////////////////////////////////////////////////////////////////////////////////////
// Dwell 단 간의 간격은 이웃한 PRI 합의 배수로 설정한다.
// date : 2013-12-04 14:25:01, 조철희
#define			DWELL_PRI_MARGIN									(1.5)

// 수신기 개수
#define			ALL_BAND													5

// 에미터 구조체 정의
#define	_spOverlapCoEMT     _spMaxEMTNum
#define _spMaxCoRsaAmbi     (30)
#define	_spMaxTryScan				(5)





#endif // !defined(AFX_SYSTEM_H__F88C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_)