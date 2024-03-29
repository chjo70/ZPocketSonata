﻿/**

    @file      System.h
    @brief
    @details   ~
    @author    조철희
    @date      17.04.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

#pragma once

#include "../../BootShell/BootShell.h"

/////////////////////////////////////////////////////////////////////////
#ifdef __ZYNQ_BOARD__
#define SD_CARD                     (const char *) "/run/media/mmcblk0p1/SYSTEM"
#elif defined(__linux__)
#define SD_CARD                     (const char *) "/home/chjo70" // "/var/log/LOG"
#elif defined(__VXWORKS__)
#define SD_CARD                     (const char *) "/RAMDRV:0/"
#else
#define SD_CARD                     (const char *) "E:\\SONATA2\\Dev\\PocketSONATA\\dev"               // getcwd( m_szPresentDirectory, sizeof(m_szPresentDirectory) );
#endif


#ifdef __ZYNQ_BOARD__
#define HOME_ID                     (const char *) "root"
#else
#define HOME_ID                     (const char *) "chjo70"
#endif

#ifdef __ZYNQ_BOARD__
#define SHARED_DATA_DIRECTORY       (const char *) "/var/rawdata"
#elif _WIN32

#ifdef _XBAND_
#define SHARED_DATA_DIRECTORY       (const char *) "D:/PDW_RAW"
#elif defined(_701_)
#define SHARED_DATA_DIRECTORY       (const char *) "D:/PDW_RAW"
#else
#define SHARED_DATA_DIRECTORY       (const char *) "d:/rawdata_sim"
#endif


#elif defined(__VXWORKS__)
#define SHARED_DATA_DIRECTORY       (const char *) "/d/rawdata" // "/var/log/LOG"
#else
//#define SHARED_DATA_DIRECTORY     (const char *) "/run/user/1000/gvfs/smb-share:server=192.168.1.245,share=shared/rawdata"
#define SHARED_DATA_DIRECTORY       (const char *) "/run/user/1000/gvfs/smb-share:server=192.168.10.245,share=shared,user=ELS/rawdata"
#endif

// CED/EOB 폴더 위치
#ifdef __ZYNQ_BOARD__
#define CEDEOB_SQLITE_FOLDER        SHARED_DATA_DIRECTORY
#elif defined(__linux__)
#define CEDEOB_SQLITE_FOLDER        (const char *) "/home/chjo70"

#elif defined(__VXWORKS__)
#if defined( _POCKETSONATA_ )
#define CEDEOB_SQLITE_FOLDER        (const char *) "/RAMDRV:0/LIB"

#elif defined( _712_ )
#ifdef _WRS_CONFIG_LP64
#define CEDEOB_SQLITE_FOLDER        (const char *) "/ata0/LIB"
#else
#define CEDEOB_SQLITE_FOLDER        (const char *) "/ata0:0/LIB"
#endif

#else
#define CEDEOB_SQLITE_FOLDER        (const char *) "/RAMDRV:0/LIB"
#endif

#else
#define CEDEOB_SQLITE_FOLDER        (const char *) "d:/rawdata_sim"  // "\\\\192.168.0.168/ea_sjp_test/sqlite3"

#endif
#define SQLITE_DIRECTORY			(const char *) "LIB"
#define CEDEOB_SQLITE_FILENAME      (const char *) "cedeob.sqlite3"

#define CEDEOB_TEST_SQLITE_FILENAME (const char *) "cedeob_test.sqlite3"

#define BLK_CEDEOB_SQLITE_FILENAME	(const char *) "cedeob_blank.sqlite3"


// 위협정보 폴더 위치
#ifdef __ZYNQ_BOARD__
#define EMITTER_SQLITE_FOLDER       (const char *) "/home/root"
#elif defined(__linux__)
#define EMITTER_SQLITE_FOLDER       (const char *) "/home/chjo70"
#elif defined(__VXWORKS__)
#define EMITTER_SQLITE_FOLDER       (const char *) "/RAMDRV:0/LIB"
#else
#define EMITTER_SQLITE_FOLDER       (const char *) "d:/rawdata_sim"
#endif
#define EMITTER_SQLITE_FILEEXTNAME  (const char *) "emitter.sqlite3"

#define EMITTER_SQLITE_FILENAME     (const char *) "emitter"

// 위협정보 원본 파일
#define BLK_EMITTER_SQLITE_FILENAME (const char *) "emitter_blank.sqlite3"

// INI 폴더 위치
#ifdef __ZYNQ_BOARD__
#define INI_FOLDER                  (const char *) "/home/root"
#define INI_BOARDID_FOLDER          (const char *) "/home/root"
#elif defined(__VXWORKS__)

#ifdef _WRS_CONFIG_LP64
#define INI_FOLDER                  (const char *) "/ata0/INI"
#define INI_BOARDID_FOLDER          (const char *) "/ata0"
#else
#define INI_FOLDER                  (const char *) "/ata0:0/INI"
#define INI_BOARDID_FOLDER          (const char *) "/ata0:0"
#endif

#elif defined(__linux__)
#define INI_FOLDER                  (const char *) "/home/chjo70"
#define INI_BOARDID_FOLDER          (const char *) "/home/chjo70"

#else
#define INI_FOLDER                  (const char *) "d:/rawdata_sim"
#define INI_BOARDID_FOLDER          (const char *) "d:/rawdata_sim"

#endif


#define INI_FILENAME                (const char *) "sysconfig.ini"

#define INI_FILENAME_BOARDID        (const char *) "boardid"
#define INI_BOARDID_DIRECTORY       (const char *) "_EW #"     // ATA 드라이브에 폴더명 접두사 정의, 한글 때문에 단순화 함.

#define INI_DIRECTORY               (const char *) "INI"

// qDecoder 폴더 위치
#define QDECODER_LOG_FOLDER         (const char *) "/tmp/LOG"
#define QDECODER_LOG_FILENAME       (const char *) "/qDecoder.log"

#define QDECODER_UPLOAD_FOLDER      (const char *) "/tmp/LOG/UPLOAD"

#ifdef __linux__
#define PROGRAM_LOG_FOLDER          (const char *) "/tmp/LOG"
#else
#define PROGRAM_LOG_FOLDER          (const char *) "c:"
#endif

// 실행 파일이 있는 위치에서 로그 디렉토리
#ifdef __linux__
#define LOG_FOLDER               (const char *) "/tmp/LOG"
#elif _MSC_VER
#define LOG_FOLDER               (const char *) "\\Debug\\LOG"
#elif defined(__VXWORKS__)
#define LOG_FOLDER               (const char *) "/RAMDRV:0/LOG"
#else
#define LOG_FOLDER               (const char *) "c:/temp"
#endif


#define LOG_DIRECTORY            (const char *) "/LOG"
#define LOG_FILENAME            (const char *) "LOG.log"


#define DDR_DIRECTORY            (const char *) "/DDR"

//#define INIT_CW_PULSEWIDTH					(130.0)



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

#define MAX_THREAT_NO								(256)			// 최대 위협 개수


// 추적필터판을 사용하지 않은 에미터 관리 주기
#define MANAET_RUN_PERIOD							(1)				// 단위는 초.



// 한번에 수집한 최대 개수
//#define PDW_ONE_BLOCK_SIZE                          (256)           // NEW_COLLECT_PDW, KWN_COLLECT_PDW, SCN_COLLECT_PDW 중에서 가장 큰것

// 비트 수집용 버퍼 크기
//#define MAX_BIT_COLLECT_COUNT                       (20)            // NEW_COLLECT_PDW, KWN_COLLECT_PDW, SCN_COLLECT_PDW 중에서 가장 큰것

// 소프트웨어 필터 개수
#define	NEW_NO_BANK									(5)
#define KNOWN_NO_FILTER								(32)
#define SCAN_NO_FILTER								(32)

#define	MAX_FIRE_INFO_ITEM                          (200)

// 소프트웨어 필터 시간 단위
#define	FILTER_ONE_SEC								(1000)				// 단위는 ms

//
#define KWN_TIMEOUT_NORMAL						(20*FILTER_ONE_SEC)
#define KWN_TIMEOUT_STEADY						(3*FILTER_ONE_SEC)
#define DEFAULT_DELETE_AET_TIME				(2*FILTER_ONE_SEC)		// 기본 에미터 삭제 시간
#define DEFAULT_DELETE_CW_AET_TIME		(10*FILTER_ONE_SEC)		// CW 에미터 삭제 시간


#define	NO_FEID_BAND									32						// 주파수 밴드 개수
#define FEID_FREQ_RES_HZ							90000					// 90 KHz 의 Histogram res.



// Jitter 와 Jitter 식별시의 지터율 고려한 식별
#define _spUDFMaxJitPerOver						(5)


// 식별 테이블을 위한 식별 최대 종류 개수 정의
#define MAX_HOWTO_ID									(50)


// Priority Mode 일때의 심벌 개수
#define MAX_SYMBOL_IN_PRIORITY_MODE		(5)


// 거리 추정 관련 정의
#define	MIN_ESTIMATED_DISTANCE				(0)
#define	MAX_ESTIMATED_DISTANCE				(129640)		// km


// 최대 로그 크기
// 최소 크기는 STR_QUEUE_LOG_MESSAGE 크기(3568바이트) 보다 커야 한다.
//#define MAX_LOGBUFFER_SIZE						sizeof(STR_QUEUE_LOG_MESSAGE)		// 10KB씩 로그 데이터를 압축해서 저장한다.


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
// #define   _spBd1LvlThr      IDIV( ( -54 - _spPAoffset ), _spAMPres )    // -54 dB
// #define   _spBd1FmpThr      0x60
// #define   _spBd1PmpThr      0x60
// #define   _spBd1AntOffLeft  0x60
// #define   _spBd1AntOffRght  0x60
// #define   _spBd1BlkAnt      0x9090
// #define   _spBd1NotFlt      0x60
// #define   _spBd1PinAtt      0x60
// #define   _spBd1BandEn      0x1
//
// //  Band 2
// #define   _spBd2LvlThr      IDIV( ( -53 - _spPAoffset ), _spAMPres )    // -53 dB
// #define   _spBd2FmpThr      0x60
// #define   _spBd2PmpThr      0x60
// #define   _spBd2AntOffLeft  0x60
// #define   _spBd2AntOffRght  0x60
// #define   _spBd2BlkAnt      0x9090
// #define   _spBd2NotFlt      0x60
// #define   _spBd2PinAtt      0x60
// #define   _spBd2BandEn      0x1
//
// //  Band 3
// #define   _spBd3LvlThr      IDIV( ( -52 - _spPAoffset ), _spAMPres )  // -52 dB
// #define   _spBd3FmpThr      0x60
// #define   _spBd3PmpThr      0x60
// #define   _spBd3AntOffLeft  0x60
// #define   _spBd3AntOffRght  0x60
// #define   _spBd3BlkAnt      0x9090
// #define   _spBd3NotFlt      0x60
// #define   _spBd3PinAtt      0x60
// #define   _spBd3BandEn      0x1

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
#if defined(_ELINT_) || defined(_XBAND_)
#define	MAX_FREQ_MHZ					    (18000)			            //!< 주파수 최대 값, Hz
#define MIN_FREQ_MHZ 					    (500)					    //!< 주파수 최소 값

#define _spMgAoaEJ					        IAOACNV( 15 )				// UMUL(15,_spAOAres)		// 15도
#define _spMgAoaCD					        IAOACNV( 30 )				// UMUL(30,_spAOAres)		// 30도
#define _spMgFixFrqEJ				        IFRQMhzCNV( 0, 10 )			// UMUL(3,1.25)					// res. 1.25 MHz
#define _spMgFixFrqCD				        IFRQMhzCNV( 0, 10 )			// UMUL(5,1.25)					// res. 1.25 MHz
#define _spMgFixFrqBoundEJ	                IFRQMhzCNV( 0, 10 )			// UMUL(6,1.25)					// res. 1.25 MHz
#define _spMgFixFrqBoundCD	                IFRQMhzCNV( 0, 10 )			// UMUL(10,1.25)					// res. 1.25 MHz

#elif defined(_POCKETSONATA_) || defined(_712_)
#define	MAX_FREQ_MHZ					    (18000)                     //!< 주파수 최대 값, Hz
#define MIN_FREQ_MHZ 					    (500)						//!< 주파수 최소 값

//#define _spMgAoaEJ					        IAOACNV( 15 )				// UMUL(15,_spAOAres)		// 15도
//#define _spMgAoaCD					        IAOACNV( 30 )				// UMUL(30,_spAOAres)		// 30도
#define _spMgFixFrqEJ                       IFRQMhzCNV( 0, 10 )			// UMUL(3,1.25)					// res. 1.25 MHz
#define _spMgFixFrqCD                       IFRQMhzCNV( 0, 10 )			// UMUL(5,1.25)					// res. 1.25 MHz
#define _spMgFixFrqBoundEJ                  IFRQMhzCNV( 0, 10 )			// UMUL(6,1.25)					// res. 1.25 MHz
#define _spMgFixFrqBoundCD                  IFRQMhzCNV( 0, 10 )			// UMUL(10,1.25)					// res. 1.25 MHz

#elif defined(_SONATA_)
#define	MAX_FREQ_MHZ					    (18000)			            //!< 주파수 최대 값, Hz
#define MIN_FREQ_MHZ 					    (500)					    //!< 주파수 최소 값

#define _spMgAoaEJ					        IAOACNV( 15 )				// UMUL(15,_spAOAres)		// 15도
#define _spMgAoaCD					        IAOACNV( 30 )				// UMUL(30,_spAOAres)		// 30도
#define _spMgFixFrqEJ                       IFRQMhzCNV( 0, 10 )			// UMUL(3,1.25)					// res. 1.25 MHz
#define _spMgFixFrqCD				        IFRQMhzCNV( 0, 10 )			// UMUL(5,1.25)					// res. 1.25 MHz
#define _spMgFixFrqBoundEJ	                IFRQMhzCNV( 0, 10 )			// UMUL(6,1.25)					// res. 1.25 MHz
#define _spMgFixFrqBoundCD	                IFRQMhzCNV( 0, 10 )			// UMUL(10,1.25)					// res. 1.25 MH


#elif defined(_701_)
#define	MAX_FREQ_MHZ					    (40000)                     //!< 주파수 최대 값, Hz
#define MIN_FREQ_MHZ 					    (500)						//!< 주파수 최소 값

#define _spMgAoaEJ					        IAOACNV( 15 )				// UMUL(15,_spAOAres)		// 15도
#define _spMgAoaCD					        IAOACNV( 30 )				// UMUL(30,_spAOAres)		// 30도
#define _spMgFixFrqEJ                       IFRQMhzCNV( 0, 5 )			// UMUL(3,1.25)					// res. 1.25 MHz
#define _spMgFixFrqCD                       IFRQMhzCNV( 0, 5 )			// UMUL(5,1.25)					// res. 1.25 MHz
#define _spMgFixFrqBoundEJ                  IFRQMhzCNV( 0, 5 )			// UMUL(6,1.25)					// res. 1.25 MHz
#define _spMgFixFrqBoundCD                  IFRQMhzCNV( 0, 5 )			// UMUL(10,1.25)					// res. 1.25 MHz


#else
//#error "컴파일러에 DEFINE 을 추가해야 합니다."
#define	MAX_FREQ_MHZ					    (18000)                     //!< 주파수 최대 값, Hz
#define MIN_FREQ_MHZ 					    (500)						//!< 주파수 최소 값

#endif



// 수집 히스토그램
// 주파수 폭
#define COLHISTO_WIDTH_MHZ              (500)                       // [MHz]
#define COLHISTO_TIME                   (10)                        // 탐지 횟수 깊이

#define COLHISTO_CELLS                  ((MAX_FREQ_MHZ-MIN_FREQ_MHZ)/COLHISTO_WIDTH_MHZ)



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
#if defined(_ELINT_) || defined(_XBAND_)
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

//#define   _spIncThr             UDIV( 8, _spAMPres )    // 02-08-11

/////////////////////////////////////////////////////////////////////////////////////////
// 펄스열 추출 정의
#define     _spContiThresholdMinPulseCount    10

// Stable 에미터 최소 펄스 개수(누락 및 스캔 신호를 고려한)
/*! \bug  20 개에서 10개로 수정함.
    \date 2006-07-27 09:28:10, 조철희
*/
#define _spAnalMinPulseStableEmitter        (5)
#define _spAnalMinPulseJitterEmitter        (10)
#define _spAnalMin2PulseJitterEmitter		(7)

// 지터 신호에 대해서 최소 누락을 정의해서 에미터로 인정한다.
#define _spAnalMinMissPulseJitterEmitter    (1)
#define _spAnalMinMissRatioJitterEmitter    (70)

#define _spMaxAoaQueueSize					(4)

#define _spMinDiffDOA						(IAOACNV(20))

/////////////////////////////////////////////////////////////////////////////////////////
// Dwell 단 간의 간격은 이웃한 PRI 합의 배수로 설정한다.
// date : 2013-12-04 14:25:01, 조철희
#define	DWELL_PRI_MARGIN					(1.5)

// 수신기 개수
#define	ALL_BAND							(enMAXPRC)

// 에미터 구조체 정의
#define	_spOverlapCoEMT     _spMaxEMTNum
#define _spMaxCoRsaAmbi     (30)
#define	_spMaxTryScan				(5)

/////////////////////////////////////////////////////////////////////////////////////////
//
#ifdef _XBAND_

enum PDW_MARK { STAT_CW=0, STAT_NORMAL=1, STAT_FMOP=5, STAT_SHORTP=7, STAT_CHIRPDN, STAT_CHIRPUP, STAT_PMOP, MAX_STAT } ;
const int stStat2GrStat[16] = { STAT_CW, STAT_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

#elif defined(_SONATA_)
2
enum PDW_MARK { STAT_CW = 0, STAT_NORMAL, STAT_CHIRPDN, STAT_CHIRPUP, STAT_PMOP, STAT_BIT, MAX_STAT };
const int stStat2GrStat[16] = { STAT_NORMAL, STAT_CW, 0, 0, STAT_CHIRPDN, STAT_CHIRPUP, STAT_PMOP, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

#elif defined(_POCKETSONATA_) || defined(_712_)
enum PDW_MARK { STAT_NORMAL = 0,
                STAT_CW,

                STAT_CHIRPTRI,
                STAT_CHIRPUP,
                STAT_CHIRPDN,
                STAT_CHIRPUK,

                STAT_CW_CHIRPTRI,
                STAT_CW_CHIRPUP,
                STAT_CW_CHIRPDN,
                STAT_CW_CHIRPUK,

                STAT_PMOP,
                STAT_CW_PMOP,

                STAT_SHORTP,
                STAT_DOPPLER,
                MAX_STAT
};
const int stStat2GrStat[16] = { STAT_NORMAL, STAT_CW, STAT_PMOP, STAT_CW_PMOP, STAT_CHIRPTRI, STAT_CHIRPUK, STAT_CHIRPDN, STAT_CHIRPUP, \
                                STAT_CW_CHIRPTRI, STAT_CW_CHIRPUP, STAT_CW_CHIRPDN, STAT_CW_CHIRPUK, STAT_SHORTP, 0, 0, 0 };

#else
enum PDW_MARK {
    STAT_NORMAL = 0,
    STAT_CW,

    STAT_PMOP = 2,
    STAT_CW_PMOP,

    STAT_CHIRPUK = 4,
    STAT_CHIRPDN,
    STAT_CHIRPUP,
    STAT_CW_CHIRPUK,
    STAT_CW_CHIRPDN,
    STAT_CW_CHIRPUP,

    STAT_SHORTP,
    MAX_STAT
};
const int stStat2GrStat[16] = { STAT_NORMAL, STAT_CW, STAT_PMOP, STAT_CW_PMOP, STAT_CHIRPUK, STAT_CHIRPDN,
                                STAT_CHIRPUP, STAT_CW_CHIRPUK, STAT_CW_CHIRPDN, STAT_CW_CHIRPUP, STAT_SHORTP, 0, 0, 0, 0, 0 };

#endif

/////////////////////////////////////////////////////////////////////////////////////////
// 장치별 정의
#ifndef _ENUM_UnitType
#define _ENUM_UnitType
enum ENUM_UnitType {
    en_UnknownUnit = 0,

    en_SONATA,
    en_SONATA_SHU,
    en_ELINT,
    en_XBAND,
    en_701,
    en_KFX,
    en_ZPOCKETSONATA,

    en_MIDAS,

	en_OTHERS

} ;
#endif


#ifndef _EN_RADARCOLLECTORID_
#define _EN_RADARCOLLECTORID_
enum EN_RADARCOLLECTORID { RADARCOL_Unknown=0, RADARCOL_1=1, RADARCOL_2, RADARCOL_3, RADARCOL_MAX };

#endif


