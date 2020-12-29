// _Define.h: interface for the 분석 소프트웨어의 정의
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEFINE_H__553E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_)
#define AFX_DEFINE_H__553E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../INC/system.h"

#define	RAD2DEG			(180./M_PI)		// 57.295779513082320876798154814114

//enum NUMBER_DEF { _spZero=0, _spOne, _spTwo, _spThree } ;
#define _spZero		(0)
#define _spOne		(1)
#define _spTwo		(2)
#define _spThree	(3)

enum { _spAnalFail=1, _spInsuPul, _spInsuExt, _spAnalSuc, _spReCol, _spModWc, _spReqAnalScn, _spDetTyp } ;

//##ModelId=452B0C550263
enum PULSE_EXTRACT_PRI_STEP { STEP1=0, STEP2, STEP_WIDE, STEP_BY_STEP } ;

//##ModelId=452B0C550277
enum SEG_MARK { NORMAL_SEG=0, DELETE_SEG, MERGED_SEG, CHECKED_SEG } ;

//##ModelId=452B0C550295
enum EMITTER_MARK { NORMAL_EMITTER=0, DELETE_EMITTER } ;

//##ModelId=452B0C550295
enum AET_MARK { NORMAL_AET=0, DELETE_AET } ;

// 주파수 그룹화
//##ModelId=452B0C5502A9
enum FREQ_GROUP_STEP { NARROW=0, _WIDE, _FULL } ;

#define _spTrue									(1)
#define _spFalse								(0)

static const char on_off[2][4] = { "OFF" , "ON" } ;

#define	_spMaxEMTNum						(256)								// Before value is 256

//////////////////////////////////////////////////////////////////////////
//
#ifdef _ELINT_
#define _spTimeNsRes						(25)
#define _spTimeres              (1000000000/_spTimeNsRes)					// 1 sec / 50 ns */

#elif defined(_POCKETSONATA_)
#define _spTimeNsRes						(25)
#define _spTimeres              (1000000000/_spTimeNsRes)					// 1 sec / 50 ns */

#elif defined(_SONATA_)
#define _spTimeNsRes						(25)
#define _spTimeres              (1000000000/_spTimeNsRes)					// 1 sec / 50 ns */

#else
#define ONE_SEC									(20000000)					// 1 sec  / 25 ns */
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



#ifdef _ELINT_
#define   _spPAoffset       (-75)	// amplitude initial value */
#else
#define   _spPAoffset       (-70)       // amplitude initial value */
#endif

//////////////////////////////////////////////////////////////////////
//

// 탐지분석판 소프트웨어에서 수집할 수 있는 최대 PDW 개수
#ifdef _ELINT_
#define NSP_MAX_PDW					NEW_COLLECT_PDW
#define	KSP_MAX_PDW					KWN_COLLECT_PDW
#define	SAP_MAX_PDW					SCN_COLLECT_PDW
#define	MAX_PDW							NEW_COLLECT_PDW

#else
#define NSP_MAX_PDW					(256)
#define	KSP_MAX_PDW					(512)
#define	MAX_PDW							(10000)		// NSP_MAX_PDW 와 KSP_MAX_PDW 값 중에서 가장 큰 값으로 한다.
#define	SAP_MAX_PDW					(1024)

#endif

/*! \bug  탐지 분석에 기본 지터율 추출을 최대 53% 까지 추출하게 함.
    \date 2008-10-25 18:01:37, 조철희
*/
#define	MAX_JITTER_P				53				// 이전 값은 55
#define MAX_JITTER_R				(float) ( MAX_JITTER_P / 100. )

//////////////////////////////////////////////////////////////////////
//
// 펄스열 추출 PRI 범위 테이블
#define	MAX_PRI_RANGE				(17)

// 신호 펄스열 최대 개수
// Jitter, Stagger 기준 펄스열의 최소 펄스수 (Min. Jitter Stagger Pulse Count)
#define RJGPC								(5)

// 펄스열 최대 개수 및 가상 에미터 최대 개수
//#define	MAX_PT      				(UINT)( 50 + 17 + 50 )  // 최대 펄스열 수, 17은 stagger 펄스열을 추출하기 위한 버퍼
#define	MAX_PT      				(UINT)( NSP_MAX_PDW )  // 최대 펄스열 수, 17은 stagger 펄스열을 추출하기 위한 버퍼
#define	MAX_AET     				(100)		// 최대 AET 수, 04-04-12 -> 50


// 그룹화 히스트그램 최대 개수


//////////////////////////////////////////////////////////////////////////
// 방위/주파수/펄스폭 그룹화
#ifdef _ELINT_
#define   _spRxdfAoa				(UDIV( 8, _spAOAres ))      // 14( 8 deg. )
#define   _spRxdfFrq				4     // about 5(=4*1.25)MHz,

#define KHARM_AOA_MAR							(_spRxdfAoa)		// 하모닉 방위 마진 (Band1)
#define KHARM_FRQ_MAR							14			// 하모닉 주파수 마진 (Band1)

#define TOTAL_FRQAOAPWBIN					(91000)			//(1024*4)											// 전체 히스토그램 BIN수

// DTOA 히스트그램 최대 개수
#define	DTOA_RES									ITOAusCNV(10)								// ( 10 * _spOneMicrosec )

#define MAX_AOA       			(36000)			// 최대 방위값 2^10 (360도/1023)
#define MAX_FREQ      			IFRQMhzCNV( 0, 5000)		// 최대 주파수sms 5000 MHz로 함.
#define	FREQ_NARR_MHZ			IFRQMhzCNV( 0, 20 )			// 20 MHz
#define	FREQ_WIDE_MHZ			IFRQMhzCNV( 0, 100 )		// 100 MHz

#define	MAX_FREQ_DEVIATION		(500)	// MHz, 이웃한 PDW의 최대 주파수 편차, WSA-423의 레이더 신호를 참조해서 정함.

#define   _spAOAmax       0x1FF
#define		_spAmpmax				0xFF

//#define   _spAOAres       (2*0.351562)		// Degree */
//#define   _spAMPres       (0.25)					// dB */
//#define   _spTOAres       (0.000000025)		// SEC(25 ns) */
//#define   _spPWres        (25.)						// pw res.

#define STABLE_MARGIN				ITOAusCNV( 8 ) // ( 1 * _spOneMicrosec )	// 1 us

#define	MAX_PW							(1024*16)

#elif defined(_POCKETSONATA_)
#define KHARM_AOA_MAR           (int) ( ( 8 * (float) ( 4.*1024. ) / (float) 360. ) + 0.5 )     // 하모닉 방위 마진
#define KHARM_FRQ_MAR           (int) ( ((10.*1000.)/1.953125)+0.5)                  // 하모닉 주파수 마진 (Band1)

#define TOTAL_FRQAOAPWBIN       (91000)			//(1024*4)											// 전체 히스토그램 BIN수
// DTOA 히스트그램 최대 개수
#define	DTOA_RES                ITOAusCNV(10)								// ( 10 * _spOneMicrosec )

#define MAX_FREQ      			((18000.*1000.)*1.953125)   // 최대 주파수sms 5000 MHz로 함.
#define	FREQ_NARR_MHZ			((20.*1000.)/1.953125)		// 20 MHz
#define	FREQ_WIDE_MHZ			((100*1000.)/1.953125)		// 100 MHz

#define	MAX_FREQ_DEVIATION		((500.*1000.)/1.953125)	// MHz, 이웃한 PDW의 최대 주파수 편차, WSA-423의 레이더 신호를 참조해서 정함.


#define STABLE_MARGIN			ITOAusCNV(1)

#define MAX_AOA       			(0x1000)
#define	MAX_PW					(0x1000000)



#elif defined(_SONATA_)
#define _spAOAmax           0x400
#define _spAmpmax           0xFF

#define   _spRxdfAoa				(UDIV( 8, _spAOAres ))      // 14( 8 deg. )
#define   _spRxdfFrq				4     // about 5(=4*1.25)MHz,

#define TOTAL_FRQAOAPWBIN					(1024)	

#else
#define KHARM_AOA_MAR							(14)		// 하모닉 방위 마진 (Band1)
#define KHARM_FRQ_MAR							14			// 하모닉 주파수 마진 (Band1)

#define MAX_AOA       			1024    // 최대 방위값 2^10 (360도/1023)
#define MAX_FREQ      			8192    // 최대 주파수값 2^13 (?/8191)
#define	FREQ_NARR_MHZ				20			// 20 MHz
#define	FREQ_WIDE_MHZ				80			// 100 MHz

#define	MAX_FREQ_DEVIATION				(500)	// MHz, 이웃한 PDW의 최대 주파수 편차, WSA-423의 레이더 신호를 참조해서 정함.

#define   _spAOAmax       0x3FF   // 359.6484375 Degree
#define		_spAmpmax				0xFF
//#define   _spAOAres       0.351562  // Degree */
//#define   _spAOAres       (0.01)		//0.351562  // Degree */
//#define   _spAMPres       0.3125    // dB */
//#define   _spTOAres       0.000000050 // SEC(50 ns) */
//#define   _spPWres        50.         // pw res.

#define TOTAL_FRQAOAPWBIN					(1024)											// 전체 히스토그램 BIN수
// DTOA 히스트그램 최대 개수
#define	DTOA_RES									( 10 * _spOneMicrosec )

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

#define	MAX_PW							(1024*2)

#endif


#define FREQ_RANGE_MARGIN		0				// 1000 MHz, 주파수 그룹 범위 margin, 이전값 0
#define	FREQ_WIDE_SHIFT_CNT	(2*_sp.np.Freq_Shift_Cnt)
#define	FREQ_NARR_SHIFT_CNT	(_sp.np.Freq_Shift_Cnt)

#define MAX_AGRT						( 30+2 )// 최대 방위 그룹 개수. 최소 개수는 3 이상이다.
#define MAX_FGRT      			( 30 )	// 최대 주파수 그룹 범위 개수(겹침고려 2배)
#define MAX_PGRT      			( 40 )	// 최대 펄스폭 그룹 범위 개수(겹침고려 2배)

#ifdef _ELINT_

#else

#endif

/*! \bug  소청도에서의 강경리 신호가 펄스폭으로 분리되기 때문에 이를 1에서 2로 설정해서 하나의 그룹으로 만들기 위함.
    \date 2008-01-24 14:26:28, 조철희
*/
#ifdef _ELINT_
#define	PW_SHIFT_CNT				(10)			//
#else
#define	PW_SHIFT_CNT				(7)			//
#endif
#define	PW_GROUP_DIFF				(500)

#define	NARROW_FREQ_GROUP		0
#define WIDE_FREQ_GROUP			1000 	// 1GHz 최대 주파수 그룹 범위
#define	MAX_FREQ_DIFF				1000        // 1000 [MHz] 주파수 폭 설정

#define MIN_CONTI_THRESHOLD_AOA	(1)

//////////////////////////////////////////////////////////////////////
// 펄스열 추출
#define MPC         				6    //010109, 이전값은 20개
#define MJPC        				6    //000223 // Jitter 펄스열의 최소 펄스수 (Min. Jitter Pulse Count), 이전값은 20개
/*! \bug  5 이던 것을 연속 4개 펄스로 수정함.
    \date 2008-01-24 19:32:06, 조철희
*/
#define RPC         				4    // 기준 펄스열의 펄스수 (Reference Pule Count), 이전값은 5, 2005-09-28 11:09:29 --//

#define MAX_STB_MISS    		7   	// 최대 허용 STABLE MISS 개수, 이전 값은 6
#define MAX_JIT_MISS    		4   	// 최대 허용 JITTER MISS 개수, 이전 값은 3

#define REFLEX_ZONE     		( 10 * _spOneMicrosec ) // 반사파 처리 구간
#define HPRF_FIRST_PRI  		( 80 * _spOneMicrosec ) // 반사파처리 이전에 High PRF부터 처리



#define	OVERLAP_SEG_THRESHOLD			(60)	// 펄스열 겹쳐지는 정도, 이전 값은 80

#define ALL_MERGE									(-1)

// 추적 또는 스캔 Jitter열 펄스열 추출할 때의 Jitter율 마진
#define	EXTRACT_JITTER_MARGIN						(3)
// #define	EXTRACT_JITTER_MARGIN						(10)

// 에미터 제원
#define PA_MEAN_ITEM										8

// 상세 신호 분석
#define THRESHOLD_PDWCOUNT_FINE_SIGANAL	50





// 주파수 고정, 변경 범위
#define FIXED_FREQ_THRESHOLD			8				// 5에서 8로 변경함.
#define FIXED_MATCH_RATIO				(85)			// 85에서 70으로 변경함.

// 패턴 분석
#define	MAX_SAMPLING_DATA					1024
#define	CO_OFF_SAMPLING_THRESHOLD	(2)

#define	MID_PRI_BAND							7			// 펄스열 추출 중간 밴드

//////////////////////////////////////////////////////////////////////////
// PRI 분석

// Jitter 신호의 하모닉 관계에 사용한 지터율 임계값 정의
#define	HARMONIC_JITTER_P_THRESHOLD	(5)

// 스태거 분석 최소 주기 회수
#define MIN_STAGGER_LEVEL_PERIOD	(2)		// 스태거 레벨값 최소 반복 회수
#define MIN_REPEAT_STAGGER_LEVEL	(6)		// 레벨 체크에서 6주기 이상인 경우는 threshold = ( 100 * ( 2*N-1 ) ) / (2*N) 누락되어도 허용하는 최소 반복

#define MIN_PRI										( 20 * _spOneMicrosec )				// 최소 분석가능 PRI

#define FIXED_FREQ_MARGIN				2
#define FREQ_MEAN_MARGIN_THRESHOLD		95




//#define DTOA_BIN									( ( 50 * _spOneMilli ) / DTOA_RES )	// 최대 수집 개수
#define DTOA_BIN									(5000)

// DTOA 히스토그램에서 찾을 수 있는 최대 Stable PRI 개수
// 16단 까지 측정할 수 있게 한다.
#define	MAX_PEAK_DTOAHISTOGRAM		(16)

// 패턴 SAW 형 임계값 정의
#define THRESHOLD_SAW_PATTERN			(60)		// 60 % 이상
#define	THRESHOLD_SAW_PATTERN			(60)		// 60 % 이상

//////////////////////////////////////////////////////////////////////////
// 에미터 생성 기준
#define CONTI_THR_LOW_PULSE					86		// 연속성 최대 지수, SPS-64의 LONG MODE인경우를 고려. 8개 중에 7개 허용.
#define CONTI_THR_HIGH_PULSE				60

#define	THRESHOLD_OVERLAP						80		// Overlap 율 ( 중첩된 DTOA / 펄스열 총시간 )

// Max Channle 추출하기 위한 최소 펄스 개수
#define MIN_PULSE_FOR_MAXCHANNEL		20

//////////////////////////////////////////////////////////////////////////
// 에미터 구조체의 정의문
#define MAX_STAGGER_LEVEL_ELEMENT		(MAX_PT)
#define MAX_HOP_LEVEL_ELEMENT				(MAX_PT)

//////////////////////////////////////////////////////////////////////////
// 신호 분석 관련 정의문

// 주파수 광대역 주파수 그룹화 설정 정의
//#define _FREQ_WIDE_NARROW_GROUP_

// 방위 그룹화할때 ISODATA 알고리즘을 이용하여 그룹화를 수행한다.
#define _ISODATA_AOA_GROUP_

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
#define PA_DEPTH_TO_SELECT	(4*15)		// [PAmax - B * PAresol, PAmax]인 펄스 선택 시 B에 해당
#define N_AOA_ELT			10		// AOA 평균값을 계산하기 위해 사용할 AOA 원소 수

//----- AOA 평균 계산 방안 200505_2 -----
// PA_DEPTH_TO_SELECT, N_AOA_ELT도 사용
#define PW_HISTO_RESOL		2		// PW 히스토 BIN 폭 = PW 해상도 * PW_HISTO_RESOL, 최소 2이상이어야 함.

//----- AOA 평균 계산 방안 200505_3 -----
// PA_DEPTH_TO_SELECT, N_AOA_ELT, PW_HISTO_RESOL도 사용

// 튀는 AOA 판단 시 Q1-K*IQR 또는 Q3+K*IQR보다 바깥에 있는지 여부를 기준으로 한다.
// 이 때 K에 해당하는 상수가 OUTLIER_COEFF이다.
#define OUTLIER_COEFF		0.5

//----- AOA 평균 계산 방안 200505_4 -----
#define AOA_HISTO_RESOL		4		// AOA 히스토 BIN 폭 = AOA 해상도 * AOA_HISTO_RESOL

#define SHIFT_COUNT_BY_HIST (4) // 2


//////////////////////////////////////////////////////////////////////////
// DWELL 펄스열 추출 관련 정의문
#define _DWELL_PULSECOUNT				(3)				// 드웰당 펄스 개수
#define _DWELL_DTOA_MARGIN			(7)				// 드웰 DTOA 마진

#define _MAX_DWELL_LEVEL				(50)

//////////////////////////////////////////////////////////////////////////
//


#define   _spInvAET					(-1)
#define		_spInvThreat			(-1)

#define   _spWarning        (-10)

//////////////////////////////////////////////////////////////////////////
//
// 분석 시뮬레이션
#define		_SIMUL_CO_ANAL_			(16)		// 시뮬레이션 분석 에미터 총 개수
#define		_SIMUL_AVAIL_ANAL_	(4)			// 시뮬레이션 분석 에미터 수

#endif // !defined(AFX_DEFINE_H__553E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_)
