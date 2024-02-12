// _Define.h: interface for the 분석 소프트웨어의 정의
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEFINE_H__553E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_)
#define AFX_DEFINE_H__553E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../INC/system.h"


#define _max(a,b)               ( ( (a) > (b) ) ? (a) : (b) )
#define _min(a,b)               ( ( (a) < (b) ) ? (a) : (b) )


#define _spZero		(0)
#define _spOne		(1)
#define _spTwo		(2)
#define _spThree	(3)
#define _spFour	    (4)

enum EN_SCANRESULT {
    _spAnalFail=1,
    _spInsuPul,
    _spInsuExt,
    _spAnalSuc,
    _spReCol,
    _spModWc,
    //_spReqAnalScn,
    //_spDetTyp,
    _spScanUnkown
} ;

enum PULSE_EXTRACT_PRI_STEP { STEP1=0, STEP2, STEP_WIDE, STEP_BY_STEP } ;

// 펄스열 마킹 정의 값
enum SEG_MARK { NORMAL_SEG=0,
                DELETE_SEG,
                MERGED_SEG,
                CHECKED_SEG,         // 에미터로 생성된 펄스열 마킹
                OVERLAPPED_SEG,
                LIBRARY_SEG,        // 위협 라이브러리로 마킹한 펄스열 추출
} ;

// 에미터 마킹 정의 값
enum EMITTER_MARK {
    NORMAL_EMITTER=0,
    DELETE_EMITTER,

    _SIZE_EMITTER_MARK
} ;

// 에미터 마킹 정의 값
enum AET_MARK { NORMAL_AET=0, DELETE_AET } ;

// 주파수 그룹화
enum FREQ_GROUP_STEP { NARROW=0, _WIDE, _FULL } ;

#define _spTrue									(1)
#define _spFalse								(0)

static const char on_off[2][4] = { "OFF" , "ON" } ;

#define	_spMaxEMTNum						(256)								// Before value is 256

//////////////////////////////////////////////////////////////////////////
//
#if defined(_ELINT_) || defined(_XBAND_)
#define _spTimeNsRes						(25)
#define _spTimeres              (1000000000/_spTimeNsRes)					// 1 sec / 50 ns */

#elif defined(_POCKETSONATA_) || defined(_712_)
//#define _spTimeNsRes						(25)
//#define _spTimeres                          (1000000000/_spTimeNsRes)					// 1 sec / 50 ns */

#elif defined(_SONATA_)
#define _spTimeNsRes						(25)
#define _spTimeres              (1000000000/_spTimeNsRes)					// 1 sec / 50 ns */

#else
//#define ONE_SEC									(20000000)					// 1 sec  / 25 ns */
#define _spTimeres              (20000000)					// 1 sec / 50 ns */
#define _spTimeNsRes						(20)

//#define _spOneSec               (_spTimeres)				// 1 sec  / 50 ns */
//#define _spOneMilli             (_spOneSec/1000)		// 1 msec / 50 ns */
//#define _spOneMicrosec          (_spOneMilli/1000)
//#define _spOneNanosec						(_spOneMicrosec/1000)

#endif

#define _spDeltimeres						(10L)


/////////////////////////////////////////////////////////////////////////////////////////
//   PDW 시스템 제원 범위
//



//////////////////////////////////////////////////////////////////////
//

#if defined(_ELINT_) || defined(_XBAND_)
#define   _spPAoffset               (-75)	// amplitude initial value */

#define NEW_COLLECT_PDW				(512)			// 탐지 분석용 최대 수집 개수
#define KWN_COLLECT_PDW				(256)			// 추적 분석용 최대 수집 개수
#define SCN_COLLECT_PDW				(1024*2)		// 스캔 분석용 최대 수집 개수

#elif defined(_POCKETSONATA_)

#define NEW_COLLECT_PDW				(256)			// 탐지 분석용 최대 수집 개수

#ifdef _MSC_VER
#define KWN_COLLECT_PDW				(200)			// 추적 분석용 최대 수집 개수
#define SCN_COLLECT_PDW				(1024-1)        // 스캔 분석용 최대 수집 개수

#else
#define KWN_COLLECT_PDW				(200)			// 추적 분석용 최대 수집 개수
#define SCN_COLLECT_PDW				(1024-1)        // 스캔 분석용 최대 수집 개수

#endif

#define USR_COLLECT_PDW				(1024*2)		// 사용자 분석용 최대 수집 개수

#elif defined(_712_)
#define NEW_COLLECT_PDW				(1024)			// 탐지 분석용 최대 수집 개수
#define KWN_COLLECT_PDW				(256)			// 추적 분석용 최대 수집 개수
#define SCN_COLLECT_PDW				(1024*2)		// 스캔 분석용 최대 수집 개수

#define USR_COLLECT_PDW				(1024*2)		// 사용자 분석용 최대 수집 개수

#else
#define   _spPAoffset               (-70)           // amplitude initial value */

#define NEW_COLLECT_PDW				(256)			// 탐지 분석용 최대 수집 개수
#define KWN_COLLECT_PDW				(256)			// 추적 분석용 최대 수집 개수
#define SCN_COLLECT_PDW				(1024*2)		// 스캔 분석용 최대 수집 개수

#endif

// NSP_MAX_PDW 와 KSP_MAX_PDW 값 중에서 가장 큰 값으로 한다.
//#define	MAX_PDW                     ( _max( _max(NEW_COLLECT_PDW, KWN_COLLECT_PDW), SCN_COLLECT_PDW ) )
#if NEW_COLLECT_PDW < KWN_COLLECT_PDW
#define MAX_PDW		(KWN_COLLECT_PDW)

#else
#define MAX_PDW		(NEW_COLLECT_PDW)

#endif

#if MAX_PDW < SCN_COLLECT_PDW
#undef MAX_PDW
#define MAX_PDW		(SCN_COLLECT_PDW)
#else

#endif


// 메시지 크기 계산하기
#define _DETECT_BUFFER_     ( sizeof( union UNION_HEADER ) + sizeof( _PDW ) * NEW_COLLECT_PDW )
#define _TRACK_BUFFER_      ( sizeof( struct SRxABTData ) + ( sizeof( _PDW ) * TRK_COLLECT_PDW ) + sizeof( UNION_HEADER ) )
#define _SCAN_BUFFER_       ( sizeof( struct SRxABTData ) + ( sizeof( _PDW ) * SCN_COLLECT_PDW ) + sizeof( UNION_HEADER ) )

#define _MAX_LANDATA        _SCAN_BUFFER_


// #if _DETECT_BUFFER_ < _TRACK_BUFFER_
// #define _MAX_LANDATA _TRACK_BUFFER_
//
// #else
// #define _MAX_LANDATA  _SCAN_BUFFER_
//
// #endif

#define _MAX_LOBDATA        (_MAX_LANDATA/sizeof(struct SRxLOBData))


/*! \bug  탐지 분석에 기본 지터율 추출을 최대 54% 까지 추출하게 함.
    \date 2008-10-25 18:01:37, 조철희
*/
#define	MAX_JITTER_P				(27)				// +- 지터율 입니다.
#define	MAX_JITTER_P_FOR_PT			(MAX_JITTER_P+3)	// 최대 54% 까지 존재
//#define MAX_JITTER_R				(float) ( MAX_JITTER_P / 100. )

//////////////////////////////////////////////////////////////////////
//
// 펄스열 추출 PRI 범위 테이블
//! #추후 자동으로 설정
#define	MAX_PRI_RANGE				(14)        // 최대 PRI 까지 설정해야함.

// 신호 펄스열 최대 개수
// Jitter, Stagger 기준 펄스열의 최소 펄스수 (Min. Jitter Stagger Pulse Count)
#define RJGPC						(5)

// 펄스열 최대 개수 및 가상 에미터 최대 개수
//#define	MAX_PT      				(UINT)( 50 + 17 + 50 )  // 최대 펄스열 수, 17은 stagger 펄스열을 추출하기 위한 버퍼
#define	MAX_SEG      				(UINT)( NEW_COLLECT_PDW )  // 최대 펄스열 수, 17은 stagger 펄스열을 추출하기 위한 버퍼
//#define	MAX_LOB     				(100)		// 최대 AET 수, 04-04-12 -> 50
#define MAX_LOB                     ( ( _MAX_LANDATA / sizeof( SRxLOBData ) ) - 1 )     // 97개

#define PRI_MAX                     (20000)             // [us]


#define DTOA_HISTOGRAM_RES_US       (2)
#define DTOA_BIN					(PRI_MAX/DTOA_HISTOGRAM_RES_US)

//////////////////////////////////////////////////////////////////////////
// 방위/주파수/펄스폭 그룹화
#if defined(_ELINT_) || defined(_XBAND_)
#define _spRxdfAoa				    (IAOACNV( 2 ))      // 8 도
#define _spRxdfFrq				    (4)                 // about 5(=4*1.25)MHz,

#define KHARM_AOA_MAR				(_spRxdfAoa)		// 하모닉 방위 마진 (Band1)

#define TOTAL_FRQAOAPWBIN			(91000)			//(1024*4)											// 전체 히스토그램 BIN수

// DTOA 히스트그램 최대 개수
#define	DTOA_HISTOGRAM_RES					ITOAusCNV(DTOA_HISTOGRAM_RES_US)								// ( 10 * _spOneMicrosec )

#define MAX_AOA_BIT       			    (36000)			// 최대 방위값 2^10 (360도/1023)
#define MAX_FREQ_BIT      			    IFRQMhzCNV( 0, 18000)		// 최대 주파수sms 5000 MHz로 함.
#define	FREQ_NARR_MHZ			    IFRQMhzCNV( 0, 20 )			// 20 MHz
#define	FREQ_WIDE_MHZ			    IFRQMhzCNV( 0, 100 )		// 100 MHz

#define	MAX_FREQ_DEVIATION		    (500)	// MHz, 이웃한 PDW의 최대 주파수 편차, WSA-423의 레이더 신호를 참조해서 정함.

#define AOA_SHIFT_COUNT             (9)     // 5도 것의 log2(500) 으로 계산한 값으로 한다.

#define STABLE_MARGIN				ITOAusCNV( 2 ) // ( 1 * _spOneMicrosec )	// 1 us

#define	MAX_PW_BIT						(1024*16)

#elif defined(_701_)
#define _spRxdfAoa				    (IAOACNV( 2 ))      // 8 도
#define _spRxdfFrq				    (4)                 // about 5(=4*1.25)MHz,

#define KHARM_AOA_MAR				(_spRxdfAoa)		// 하모닉 방위 마진 (Band1)

#define TOTAL_FRQAOAPWBIN			(91000)			//(1024*4)											// 전체 히스토그램 BIN수

// DTOA 히스트그램 최대 개수
#define	DTOA_HISTOGRAM_RES					ITOAusCNV(DTOA_HISTOGRAM_RES_US)								// ( 10 * _spOneMicrosec )

#define MAX_AOA_BIT       			    (3600)			// 최대 방위값 2^10 (360도/1023)
#define MAX_FREQ_BIT      			    IFRQMhzCNV( 0, 18000)		// 최대 주파수sms 5000 MHz로 함.
#define	FREQ_NARR_MHZ			    IFRQMhzCNV( 0, 20 )			// 20 MHz
#define	FREQ_WIDE_MHZ			    IFRQMhzCNV( 0, 100 )		// 100 MHz

#define	MAX_FREQ_DEVIATION		    (500)	// MHz, 이웃한 PDW의 최대 주파수 편차, WSA-423의 레이더 신호를 참조해서 정함.

#define AOA_SHIFT_COUNT             (4)     // 5도 것의 log2(500) 으로 계산한 값으로 한다.

#define STABLE_MARGIN				ITOAusCNV( 2 ) // ( 1 * _spOneMicrosec )	// 1 us

#define	MAX_PW_BIT						(1024*16)

#elif defined(_POCKETSONATA_) || defined(_712_)
#define TOTAL_FRQAOAPWBIN               (91000)				//(1024*4), 전체 히스토그램 BIN수

#define	DTOA_HISTOGRAM_RES              UTOAusCNV((_TOA) DTOA_HISTOGRAM_RES_US)

#define	FREQ_WIDE_VALUE_MHZ             (2000)

#define	FREQ_NARR_MHZ                   IFRQMhz(0,20)            // 20 MHz


//! #추후: 동일 방위의 위협 레이더 주파수 경계를 결정
//!
#define	FREQ_WIDE_MHZ                   IFRQMhz(0, 100 )         // BIN 폭을 500 MHz 로 설정, 500 -> 100

#define	MAX_FREQ_DEVIATION		        IFRQMhz(0, 1000)         // 1000 MHz, [MHz], 이웃한 PDW의 최대 주파수 편차, WSA-423의 레이더 신호를 참조해서 정함.


// 아래는 PDW의 해당 항목의 비트 수를 고려해서 값을 설정해야 한다.
// 이 값으로 그룹화 최대 BIN 수를 결정합니다.
#define MAX_FREQ_BIT                    (0x10000000)            // 주파수 최대 비트
#define MAX_FREQ_VALUE                  (18000000)              // 주파수 최대 값

#define MAX_AOA_BIT       			    (3600) // (0x1000)                // 방위 최대 값
#define	MAX_PW_BIT					    (0x1000000)             // 펄스폭 최대 값
#define	MAX_PA_BIT					    (0x10000)               // 신호세기 최대 값



#elif defined(_SONATA_)
#define _spAOAmax                   0x400
#define _spAmpmax                   0xFF

#define   _spRxdfAoa				(UDIV( 8, _spAOAres ))      // 14( 8 deg. )
#define   _spRxdfFrq				4     // about 5(=4*1.25)MHz,

#define	MAX_FREQ_DEVIATION				(500)	// MHz, 이웃한 PDW의 최대 주파수 편차, WSA-423의 레이더 신호를 참조해서 정함.

#define TOTAL_FRQAOAPWBIN					(1024)

#define STABLE_MARGIN				(_TOA) ( 1 * _spOneMicrosec )	// 1 us
#define MAX_AOA_BIT       			    1024    // 최대 방위값 2^10 (360도/1023)STABLE_MARGIN
#define MAX_FREQ_BIT      			8192    // 최대 주파수값 2^13 (?/8191)

#define KHARM_AOA_MAR				(14)		// 하모닉 방위 마진 (Band1)

#define	DTOA_HISTOGRAM_RES					(_TOA) ( (_TOA)DTOA_HISTOGRAM_RES_US * (_TOA) _spOneMicrosec )


#define   _spRxdfAoaLow     (UDIV( 8, _spAOAres ))      // 14( 8 deg. )
#define   _spRxdfAoaMid     (UDIV( 5., _spAOAres ))     // 9 ( 5 deg. )
#define   _spRxdfAoaHgh     (UDIV( 3.5, _spAOAres ))    // 6 ( 3.5 deg. )

// 주파수 방위 마진
#define KHARM_AOA_MAR_LOW			(_spRxdfAoaLow)		// 하모닉 방위 마진 (Band1)
#define KHARM_AOA_MAR_MID			(_spRxdfAoaMid)		// 하모닉 방위 마진 (Band2)
#define KHARM_AOA_MAR_HGH			(_spRxdfAoaHgh)		// 하모닉 방위 마진 (Band3)

#define	MAX_PW_BIT							(1024*2)

#define	FREQ_WIDE_MHZ				80			// 100 MHz
#define	FREQ_NARR_MHZ				20			// 20 MHz
#define AOA_SHIFT_COUNT             (10)     // 5도 것의 log2(500) 으로 계산한 값으로 한다.

#else
#define KHARM_AOA_MAR							(14)		// 하모닉 방위 마진 (Band1)
#define KHARM_FRQ_MAR							14			// 하모닉 주파수 마진 (Band1)

#define MAX_AOA_BIT       			1024    // 최대 방위값 2^10 (360도/1023)
#define MAX_FREQ_BIT      			8192    // 최대 주파수값 2^13 (?/8191)
#define	FREQ_NARR_MHZ				20			// 20 MHz
#define	FREQ_WIDE_MHZ				80			// 100 MHz

#define	MAX_FREQ_DEVIATION				(500)	// MHz, 이웃한 PDW의 최대 주파수 편차, WSA-423의 레이더 신호를 참조해서 정함.

#define AOA_SHIFT_COUNT             (10)     // 5도 것의 log2(500) 으로 계산한 값으로 한다.

#define   _spAOAmax       0x3FF   // 359.6484375 Degree
#define		_spAmpmax				0xFF


#define TOTAL_FRQAOAPWBIN					(1024)											// 전체 히스토그램 BIN수
// DTOA 히스트그램 최대 개수
#define	DTOA_HISTOGRAM_RES									( DTOA_HISTOGRAM_RES_US * _spOneMicrosec )

#define   _spRxdfAoaLow     (UDIV( 8, _spAOAres ))      // 14( 8 deg. )
#define   _spRxdfAoaMid     (UDIV( 5., _spAOAres ))     // 9 ( 5 deg. )
#define   _spRxdfAoaHgh     (UDIV( 3.5, _spAOAres ))    // 6 ( 3.5 deg. )

#define   _spRxdfFrqLow     2     // about 1.25(2*0.625)MHz
#define   _spRxdfFrqMid     2     // about 2.5(2*1.25)MHz
#define   _spRxdfFrqHgh     2     // 3(2*1.5) MHz

// 주파수 방위 마진
#define KHARM_AOA_MAR_LOW					(_spRxdfAoaLow)		// 하모닉 방위 마진 (Band1)
#define KHARM_AOA_MAR_MID					(_spRxdfAoaMid)		// 하모닉 방위 마진 (Band2)
#define KHARM_AOA_MAR_HGH					(_spRxdfAoaHgh)		// 하모닉 방위 마진 (Band3)

// 주파수 HARMONIC MARGIN
#define KHARM_FRQ_MAR_LOW					14			// 하모닉 주파수 마진 (Band1)
#define KHARM_FRQ_MAR_MID					14			// 하모닉 주파수 마진 (Band2)
#define KHARM_FRQ_MAR_HGH					14			// 하모닉 주파수 마진 (Band3)


#define STABLE_MARGIN				( 1 * _spOneMicrosec )	// 1 us

#define	MAX_PW_BIT							(1024*2)

#endif

#define FREQ_RANGE_MARGIN		0				// 1000 MHz, 주파수 그룹 범위 margin, 이전값 0
#define	FREQ_WIDE_SHIFT_CNT	(2*_sp.np.Freq_Shift_Cnt)
#define	FREQ_NARR_SHIFT_CNT	(_sp.np.Freq_Shift_Cnt)

#ifdef _VECTORCAST_
#define MAX_AGRT                ( 2 )  // 최대 방위 그룹 개수. 최소 개수는 3 이상이다.
#define MAX_FGRT                ( 2 )  // 최대 방위 그룹 개수. 최소 개수는 3 이상이다.
#define MAX_PGRT                ( 2 )  // 최대 방위 그룹 개수. 최소 개수는 3 이상이다.

#else
#define MAX_AGRT                ( 60 )  // 최대 방위 그룹 개수. 최소 개수는 3 이상이다.
#define MAX_FGRT                ( 30 )  // 최대 방위 그룹 개수. 최소 개수는 3 이상이다.
#define MAX_PGRT                ( 10 )  // 최대 방위 그룹 개수. 최소 개수는 3 이상이다.

#endif


#define MAX_MISSING_PULSE_FOR_PULSEEXTRACT		(20)

#define PW_VARIANCE_FOR_VALID_PDW       (10)


/*! \bug  소청도에서의 강경리 신호가 펄스폭으로 분리되기 때문에 이를 1에서 2로 설정해서 하나의 그룹으로 만들기 위함.
    \date 2008-01-24 14:26:28, 조철희
*/
#if defined(_ELINT_) || defined(_XBAND_)
#define	PW_SHIFT_CNT				    (10)			//
#else
#define	PW_SHIFT_CNT				    (7)			//
#endif

#define	PW_GROUP_DIFF				    (500)

#define	NARROW_FREQ_GROUP		        0
#define WIDE_FREQ_GROUP			        1000 	// 1GHz 최대 주파수 그룹 범위



// 방위 히스토그램 상에서 _sp.np.Aoa_Hist_Thr 값 이하로 연속 출현 개수
#define AOA_HIST_THR                    (5)
#define MIN_CONTI_THRESHOLD_AOA			(5)

//////////////////////////////////////////////////////////////////////
// 펄스열 추출
#define MPC         				    6    //010109, 이전값은 20개
#define MJPC        				    6    //000223 // Jitter 펄스열의 최소 펄스수 (Min. Jitter Pulse Count), 이전값은 20개
/*! \bug  5 이던 것을 연속 4개 펄스로 수정함.
    \date 2008-01-24 19:32:06, 조철희
*/
#define RPC         				4    // 기준 펄스열의 펄스수 (Reference Pule Count), 이전값은 5, 2005-09-28 11:09:29 --//

#define MAX_STB_MISS    		    (7)   	// 최대 허용 STABLE MISS 개수, 이전 값은 6
#define MAX_JIT_MISS    		    (2)   	// 최대 허용 JITTER MISS 개수, 이전 값은 3

//#define REFLEX_ZONE     		    ( 10 * _spOneMicrosec ) // 반사파 처리 구간
//#define HPRF_FIRST_PRI  		    ( 80 * _spOneMicrosec ) // 반사파처리 이전에 High PRF부터 처리



#define	OVERLAP_SEG_THRESHOLD		(60)	// 펄스열 겹쳐지는 정도, 이전 값은 80

//#define ALL_MERGE									(-1)

// 추적 또는 스캔 Jitter열 펄스열 추출할 때의 Jitter율 마진
#define	EXTRACT_JITTER_MARGIN						(3)
// #define	EXTRACT_JITTER_MARGIN						(10)

// 에미터 제원
#define PA_MEAN_ITEM										8

// 상세 신호 분석
#define THRESHOLD_PDWCOUNT_FINE_SIGANAL	50


// 주파수 고정, 변경 범위
#define FIXED_FREQ_THRESHOLD			        (8)				// 5에서 8로 변경함.
#define FIXED_MATCH_RATIO				        (85)			// 85에서 70으로 변경함.

// 패턴 분석
#define	CO_OFF_SAMPLING_THRESHOLD               (2)

// 최소 ACF 개수
#define MIN_CO_ACF                              (5)

// 최소 ACF 값 : 호핑과 드웰 신호에 대해서...
#define MINIMUM_ACF_FOR_HOPPING                 (0.3)

// PRI 추출 경계
#define	MID_PRI_BAND							(7)			// 펄스열 추출 중간 밴드

//////////////////////////////////////////////////////////////////////////
// PRI 분석

// Jitter 신호의 하모닉 관계에 사용한 지터율 임계값 정의
#define	HARMONIC_JITTER_P_THRESHOLD             (5)

// 스태거 분석 최소 주기 회수
#define MIN_STAGGER_LEVEL_PERIOD                (2)		// 스태거 레벨값 최소 반복 회수
#define MIN_REPEAT_STAGGER_LEVEL	            (6)		// 레벨 체크에서 6주기 이상인 경우는 threshold = ( 100 * ( 2*N-1 ) ) / (2*N) 누락되어도 허용하는 최소 반복

//#define MIN_PRI							ITOAusCNV( 20 ) //( 20 * _spOneMicrosec )				// 최소 분석가능 PRI

//#define FIXED_TYPE_FREQ_MARGIN			        (5)    // [MHz]
//#define FIXED_FREQ_MARGIN				5
#define FREQ_MEAN_MARGIN_THRESHOLD		95




//#define DTOA_BIN									( ( 50 * _spOneMilli ) / DTOA_RES )	// 최대 수집 개수
//#define DTOA_BIN									(11000+10)

// DTOA 히스토그램에서 찾을 수 있는 최대 Stable PRI 개수
// 16단 까지 측정할 수 있게 한다.
#define	MAX_PEAK_DTOAHISTOGRAM		(16)

// 호핑 분석 데이터 관련 정의
#define FREQ_BIN_WIDTH              (10)            // BIN 하나의 주파수 범위(10MHz)
#define FREQ_BIN                    ( MAX_FREQ_MHZ / FREQ_BIN_WIDTH)  // BIN 당 10MHz로 설정
#define MAX_FREQ_MISS_CNT           (5)             // 호핑 레벨 최대 누락 개수
#define HOP_LEVEL_MIN_CNT           (5)                // 호핑 및 드웰 레벨 최소 PDW 개수
#define HOP_RATIO                   (60)                // 호핑 및 드웰 레벨 최소 PDW 개수
#define HOP_LEVEL_MIN_CNT_NONPRD    (2)
#define HOP_PDW_PERCENTAGE          (85.0)            // 호핑 판정을 위한 호핑 PDW 비율

// 패턴 SAW 형 임계값 정의
#define THRESHOLD_SAW_PATTERN			(10)		// 55 에서 550로 낮게 설정합니다 (잡음 고려해서).

//////////////////////////////////////////////////////////////////////////
// 에미터 생성 기준
#define CONTI_THR_LOW_PULSE					86		// 연속성 최대 지수, SPS-64의 LONG MODE인경우를 고려. 8개 중에 7개 허용.
#define CONTI_THR_HIGH_PULSE				60

#define	THRESHOLD_OVERLAP			(60)		// Overlap 율 ( 중첩된 DTOA / 펄스열 총시간 )

// Max Channle 추출하기 위한 최소 펄스 개수
#define MIN_PULSE_FOR_MAXCHANNEL            20

//////////////////////////////////////////////////////////////////////////
// 에미터 구조체의 정의문
#if defined(_ELINT_) || defined(_XBAND_) || defined(_POCKETSONATA_) || defined(_712_)
#define MAX_HOPPING_LEVEL_POSITION           32
#else
#define MAX_HOPPING_LEVEL_POSITION           32
#endif

#define MAX_STAGGER_LEVEL_POSITION           (MAX_HOPPING_LEVEL_POSITION)
#define MAX_HOP_LEVEL_ELEMENT				(MAX_SEG)

//////////////////////////////////////////////////////////////////////////
// 신호 분석 관련 정의문

// 주파수 광대역 주파수 그룹화 설정 정의
//#define _FREQ_WIDE_NARROW_GROUP_

// 방위 그룹화할때 ISODATA 알고리즘을 이용하여 그룹화를 수행한다.
//#define _ISODATA_AOA_GROUP_

//#define _EXTRACT_PULSE_METHOD1_
//#define _EXTRACT_PULSE_METHOD2_
//#define _EXTRACT_PULSE_METHOD3_

//////////////////////////////////////////////////////////////////////////
//
// 기본 규칙성 펄스열을 추출한 정보를 이용해서 규칙성 펄스열을 추출한다.
// 이때 규칙성 펄스열 추출시에 마킹은 하지 않는다.
// 그리고 불규칙성 펄스열 추출을 실시하는데 앞서 구한 규칙성 펄스열들과
// 불규칙성 펄스열들의 관계를 확인해서 제거한다.
// 그런데 규칙성 펄스열들과 불규칙성 펄스열들의 유사 관계를 이용해서
// 제거해야 하는데 이 제거 기능 알고리즘을 추가하는 것이 아직 미구현 상태이다.
//-- 조철희 2006-02-07 15:40:23 --//

// 전 구간에 대해서 참조 규칙성 펄스열들을 추출한다.
// 추출방법은 5개의 펄스로 연속된 규칙성 펄스열을 찾고 이 펄스열을 근거로 전/후 펄스열들을 추출한다.
// 그리고, 각 구간별로 규칙성, 불규칙성 펄스열들을 추출한다.
// 이때 펄스열들 중에서 삭제 마킹 또는 펄스열들의 펄스 개수가 적을 때는 펄스열 저장소를 정리한다.
// 마지막으로 앞에서 추출한 참조 펄스열과 펄스열 추출한 펄스열과 비교해서 유사 펄스열들은 제거한다.
//-- 조철희 2006-05-19 11:15:25 --//

// #define _EXTRACT_PULSE_METHOD3_

// 각 구간별로 규칙성펄스열과 불규칙성 펄스열을 뽑아낸다.
//-- 조철희 2006-02-09 12:14:45 --//
// #define _EXTRACT_PULSE_METHOD4_

/*! \bug  협대역 및 광대역 주파수 그룹화로 펄스열 추출하기 위한
    \date 2006-07-27 17:07:48, 조철희
*/
#define _EXTRACT_PULSE_METHOD5_

// 불규칙성 펄스열 추출 방안
//#define _JITTER_PULSE_EXTRACT_METHOD1_
#define _JITTER_PULSE_EXTRACT_METHOD2_

//////////////////////////////////////////////////////////////////////
//
// 김경석
//----- AOA 평균 계산 방안 선택 -----
//#define _CHJO_AOAMEANALG_200503
//#define _GSKIMF_AOAMEANALG_200505_1
//#define _GSKIMF_AOAMEANALG_200505_2
//#define _GSKIMF_AOAMEANALG_200505_3
//#define _GSKIMF_AOAMEANALG_200505_4
#define _GSKIMF_AOAMEANALG_200505_6


//----- AOA 평균 계산 방안 200505_1 -----
#define MIN_N_SEG_PLS_FOR_AOAMEANALG	11	// AOA 평균 계산 알고리즘 위한 최소 펄스 수
#define PA_DEPTH_TO_SELECT              (4*15)		// [PAmax - B * PAresol, PAmax]인 펄스 선택 시 B에 해당
#define N_AOA_ELT                       10		// AOA 평균값을 계산하기 위해 사용할 AOA 원소 수

//----- AOA 평균 계산 방안 200505_2 -----
// PA_DEPTH_TO_SELECT, N_AOA_ELT도 사용
#define PW_HISTO_RESOL		2		// PW 히스토 BIN 폭 = PW 해상도 * PW_HISTO_RESOL, 최소 2이상이어야 함.

//----- AOA 평균 계산 방안 200505_3 -----
// PA_DEPTH_TO_SELECT, N_AOA_ELT, PW_HISTO_RESOL도 사용

// 튀는 AOA 판단 시 Q1-K*IQR 또는 Q3+K*IQR보다 바깥에 있는지 여부를 기준으로 한다.
// 이 때 K에 해당하는 상수가 OUTLIER_COEFF이다.
#define OUTLIER_COEFF		(0.5)

//----- AOA 평균 계산 방안 200505_4 -----
#define AOA_HISTO_RESOL		4		// AOA 히스토 BIN 폭 = AOA 해상도 * AOA_HISTO_RESOL

#define SHIFT_COUNT_BY_HIST (4) // 2


//////////////////////////////////////////////////////////////////////////
// DWELL 펄스열 추출 관련 정의문
#define _DWELL_PULSECOUNT				(3)				// 드웰당 펄스 개수
#define _DWELL_DTOA_MARGIN              (_TOA) (7)				// 드웰 DTOA 마진

#define _MAX_DWELL_LEVEL				(50)

//////////////////////////////////////////////////////////////////////////
//----- Hopping 병합 변수
#define HOPPING_MERGE_AOA_MARGIN        (15)    //  5도



#define _spInvAET                       (-1)
#define	_spInvThreat                    (-1)

#define _spWarning                      (-10)





// 진행바 스텝수
#define _PROGRESS_STEP												(80)


#include "_CED_Define.h"





#endif // !defined(AFX_DEFINE_H__553E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_)
