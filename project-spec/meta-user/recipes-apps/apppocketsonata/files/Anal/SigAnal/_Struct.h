// Struct.h: interface for the 탐지분석판 소프트웨어의 구조체
//
//////////////////////////////////////////////////////////////////////

#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../INC/PDW.h"
#include "../INC/AetIPL.h"

#include "../EmitterMerge/ELStringDefn.h"

struct FREQ_RESOL {
	// frequency band code를 위한 구조체
	unsigned int uiMin;       // min frequency
	unsigned int uiMax;       // max frequency
	int iOffset;       // max frequency
	float fRes;			// 각 구간에 따른 resolution
};

#include "../Collect/DataFile/DataFile.h"




// PDW  펄스열 플레그
enum PULSE_MARK {
    enUnMark=0,
    enSTABLE_MARK,
    enREFSTB_MARK,
    enREFJIT_MARK,

    enJITTER_MARK,
    enDWELL_MARK,
    enUNKNOWN_MARK,
    enEXTRACT_MARK,

    enLIBRARY_MARK,

} ;

enum ENUM_HOPPINGDWELL {
    enFREQ_HOPPING = 0,
    enPRI_DWELL
};

/**
    @typedef PDWINDEX
    @brief   PDWINDEX 데이터 정의 입니다. 속도를 위해서는 unsigned int 로 정의흘 해야 되지 않을까...
**/
typedef USHORT PDWINDEX;

/**
    @struct STR_PDWINDEX
    @brief  탐지 PDW Index
**/
struct STR_PDWINDEX {
    unsigned int uiCount;
    PDWINDEX *pIndex;

} ;

/**
    @struct STR_FRQAOAPWHISTOGRAM
    @brief  히스토그램
**/
struct STR_FRQAOAPWHISTOGRAM {
	PDWINDEX hist[ TOTAL_FRQAOAPWBIN ];
	unsigned int uiBinCount;

} ;


// DTOA 히스토그램 구조체
struct STR_DTOA_HISTOGRAM {
    unsigned int uiItems;
	unsigned int uiBinCount;
	PDWINDEX hist[ DTOA_BIN ];

	STR_LOWHIGH bin_range;

	int bin_peak_count;
	UINT uiBinPeak[ MAX_PEAK_DTOAHISTOGRAM+1 ];

	int dtoa_peak_count;
	_TOA tDTOAPeak[ MAX_PEAK_DTOAHISTOGRAM+1 ];	// Dwell 스텝을 분석하기 위한 변수

} ;

// 주파수 호핑 분석 구조체
struct STR_HOPPING_DATA {
    UINT uiBinCount[FREQ_BIN];
    PDWINDEX hist[FREQ_BIN][MAX_PDW];
    UINT pt_count;
    UINT pt_pdw_count[MAX_PDW];
    PDWINDEX pt_pdw_idx[MAX_PDW][MAX_PDW];
    UINT hop_level_cnt;
    int hop_level[MAX_HOPPING_LEVEL_POSITION];

} ;

/**
    @struct SHoppingSteps
    @brief  호핑/드웰 분석 구조체
**/
struct SHoppingDwell {
    unsigned int uiAccumulated;

    unsigned int uiSampleDataIndex;

    unsigned int uiCoSteps;
    int iSteps[NEW_COLLECT_PDW/ HOP_LEVEL_MIN_CNT];

    bool IsValid()
    {
        return uiCoSteps >= 2;
    }

    void AddSteps( int iStep )
    {
        unsigned int uiMax = NEW_COLLECT_PDW / HOP_LEVEL_MIN_CNT;
        if( uiCoSteps < uiMax && iStep != 0 ) {
            iSteps[uiCoSteps] = iStep;
            ++ uiCoSteps;
        }
    }

    bool operator==( const SHoppingDwell &c )
    {
        bool bRet = false;

        if( c.uiCoSteps == uiCoSteps ) {
            unsigned int i;

            for( i = 0; i < uiCoSteps ; ++i ) {
                if( iSteps[i] != c.iSteps[i] ) {
                    break;
                }
            }
            if( i == uiCoSteps ) {
                bRet = true;
            }

        }
        return bRet;
    }

    void operator=( const int &i )
    {

        if( uiCoSteps == 0 || iSteps[0] != i ) {
            AddSteps( i );
        }
        return ;
    }

};

// 방위(AOA) 그룹
struct STR_AOA_GROUP {
	UINT uiBand;
    UINT uiStat;
    PDWINDEX *pPDWIndex;
    int iCount;
    bool bCrossDOA0;
    int iFromAOA;
    int iToAOA;
    UINT uiFromBin;
    UINT uiToBin;

}  ;

// 방위 그룹화 구조체
struct STR_AOA_GROUPS {
    STR_AOA_GROUP stAOA[ MAX_AGRT ];
    unsigned int uiCount;
	unsigned int uiCoAnal;

}  ;

// 주파수 그룹범위 테이블
struct STR_FRQ_GROUP {
	int	iIdxAOA;			// 방위 그룹화 인덱스

	UINT uiFromFRQ;
	UINT uiToFRQ;

    UINT uiFromBIN;
    UINT uiToBIN;
	char narrow_wide;
	char end_of_aoagroup;

}  ;

// 주파수 그룹범위 테이블
struct STR_FRQ_GROUPS {
	STR_FRQ_GROUP stFreq[ MAX_FGRT ];
	unsigned int uiCount;
	unsigned int uiCoAnal;

}  ;

struct STR_PW_GROUP {
    int	frq_idx;			// 주파수 그룹화 인덱스

    UINT uiFromPW;
    UINT uiToPW;
    UINT uiFromBin;
    UINT uiToBin;

}  ;

// 주파수 그룹범위 테이블
struct STR_PW_GROUPS {
	STR_PW_GROUP pw[ MAX_PGRT ];
	unsigned int uiCount;
	int coAnal;

}  ;

#ifdef SCN_COLLECT_PDW
// ISODATA 클러스터링 테이블
struct STR_CLUSTER {
	int iCount;
    PDWINDEX pIndex[SCN_COLLECT_PDW];
    UINT uiValue[SCN_COLLECT_PDW];

    bool bSplit;

	int iCenter;
	float fDeviation;
	float fDistance;
	STR_LOWHIGH stAOA;

}  ;
#endif

// 탐지의 펄스열이 존재함에도 분석이 되지 않는 문제
struct STR_FIRST_FRQAOA_PEAK {
	STR_LOWHIGH	stAOA;
	STR_LOWHIGH	stFrq;
	UINT band;
	UINT tot_cnt;
	UINT uiCount;
	UINT enable;

}  ;

/**
    @struct STR_PULSE_TRAIN_SEG
    @brief  펄스열 단 정보
**/
struct STR_PULSE_TRAIN_SEG {
    UINT uiID;                          // 펄스열 고유 ID
	STR_PDWINDEX stPDW;				    // 펄스열 인덱스, 이 구조체는 제일 앞에 있어야 함.

	UINT uiMiss;					    // missing 개수, <- 이 앞에 변수를 삽입하지 말아야함. CPulExt::MemcpySeg() 때문임.
	UINT uiPRI_Band;				    // 펄스열 추출할 때의 PRI 밴드
	UINT uiExtractStep;			        // 기준 펄스열, STABLE, Jitter PRI

    PDWINDEX *pPDWIndex;                // 기준 펄스의 인덱스 위치

	PDWINDEX idxGrRef;				    // 기준펄스, 기준펄스열 최초 펄스
	PDWINDEX idxGrFirst;			    // 펄스열 최초 펄스 인덱스, pdw.pIndex의 인덱스를 가리킨다.
	PDWINDEX idxGrLast;			        // 펄스열 최후 펄스, pdw.pIndex의 인덱스를 가리킨다.
    PDWINDEX idxGrRefLast;			    // 펄스열 최후 펄스, pdw.pIndex의 인덱스를 가리킨다.

	_TOA tFirst;					    // 펄스열 첫번째 TOA
	_TOA tLast;					        // 펄스열 마지막 TOA
    //_TOA tStaggerTOA;                   // Normalize된 TOA 값(framePIR로 모듈화한 값)
	UINT uiStat;						// PDW 상태

	UINT uiFreqType;					// 주파수 타입
	STR_MINMAX stAOA;					// 방위 제원
	STR_MINMAX_MEDIAN stFreq;			// 주파수 제원
	STR_MINMAX stPA;					// 신호세기 제원
	STR_MINMAX stPW;					// 펄스폭 제원
    enANL_PRI_TYPE enPriType;			// PRI 타입
	STR_MINMAX_TOA stPRI;				// PRI 제원

#ifdef _DEBUG
    STR_MINMAX_TOA stExtPRI;			// PRI 제원

#endif

	_TOA tMinDtoa;					    // DTOA 간격 중에서 최소가 되는 값
	float fJitterPercent;					// 지터율
	UINT uiContinuity;				    // 펄스열 연속성(%)
	UINT uiBand;						// 주파수 Band Code
	UINT peak_idx;					    // peak PA의 펄스 index

	SEG_MARK enSegMark;					// 펄스열의 상태
										// 삭제=0, 정상상태=1, 에미터로 체크된 상태=2
	UINT uiPRIPatternPeriod;		    // PRI  패턴 주기
	UINT uiFreqPatternPeriod;		    // FREQ 패턴 주기

}  ;

// PRI Table
struct STR_PRI_RANGE_TABLE {
	_TOA tMinPRI;		// 하한 범위
	_TOA tMaxPRI;		// 상한 범위

}  ;

/**
    @enum  ENUM_SAMPLING_OPTION
    @brief 샘플링 옵션
**/
enum ENUM_SAMPLING_OPTION {
    enAVERAGE = 0,
    enMAXHOLD,
    enVALUE

};

struct STR_STAGGER_SEG {
    _TOA tStaggerTOA;
    STR_PULSE_TRAIN_SEG *pSeg;

} ;

// 에미터 정보
#ifndef _GRAPH_
struct STR_EMITTER {
	unsigned int uiID;					// ID : 인덱스 번호

	ENUM_SIGNAL_TYPE enSignalType;
    unsigned int uiStat;

    UINT uiSegIdx[ MAX_SEG ];			// 펄스열 index, 파라메터 저장

    //STR_PULSE_TRAIN_SEG stSeg[ MAX_SEG ];			// 펄스열 저장

	unsigned int uiCoSeg;							// seg[] 수, 펄스열 수, seg_count

    enANL_FREQ_TYPE enFreqType;
    ENUM_AET_FREQ_PRI_PATTERN_TYPE enFreqPatternType;
    STR_MINMAX stFreq;				// 에미터 간의 병합시에 판단할 주파수 통계량
    float fFreqPeriod;

    unsigned int uiFreqLevelCount;					// Hop level 수
    unsigned int uiFreqLevel[MAX_FREQ_PRI_STEP];					// Hopping level

	enANL_PRI_TYPE enPRIType;							// PRI 형태
	_TOA tFramePRI;								// 스태거일 때의 frmae PRI 값
    STR_MINMAX_TOA stPRI;							// 에미터 펄스열의 PRI 범위
    ENUM_AET_FREQ_PRI_PATTERN_TYPE enPRIPatternType;
	float fPRIPeriod;

	//unsigned int uiStagDwellElementCount;					// stagger level 수
	//_TOA tStaggerDwellElement[ MAX_FREQ_PRI_STEP ];		// Stagger level

	unsigned int uiCoStagDwellLevelCount;					// stagger level 수
	_TOA tStaggerDwellLevel[ MAX_FREQ_PRI_STEP ];		// Stagger level

    //unsigned int uiFreqElementCount;
    //unsigned int uiFreqElement[MAX_FREQ_PRI_STEP];					// Hopping level

	STR_MINMAX stPW;							// 에미터 펄스열의 PRI 범위

    STR_MINMAX stFMOPFreq;

	UINT uiMainSeg;							// 분석에 성공한 seg index
    EMITTER_MARK enMark;

	int iDIRatio;

    STR_PDWINDEX stPDW;						// PDW 버퍼

} ;

// 펄스열의 제원을 계산하기 위한 변수
struct STR_PDWPARAM {
	_TOA *pTOAParam;
	UINT *puiParam;
	int *piParam;

	unsigned int uiCount;

} ;



/////////////////////////////////////////////////////////////////////////////////////////
//  RF AOA margin
//

/////////////////////////////////////////////////////////////////////////////////////////
//  system parameter data structure
//
struct STR_CT {
  UINT mode;
}  ;

struct STR_SP {
  UINT aoadiff[ ALL_BAND ];
  UINT frqdiff[ ALL_BAND ];
} ;

struct STR_ID {
	// 주파수 고정 임계값
  UINT fixfrq[ ALL_BAND ];

	// 주파수 변경 임계값
  UINT agifrq[ ALL_BAND ];
  UINT pri;     // pri tol.
  UINT prd;     // scan tol.

  UINT frqPrd;      // When Pattern Agile, comparative period val.
  UINT priPrd;      // When PRI Pattern, comparative period val.

}  ;

struct STR_MG {
    //  UINT  mode;
    UINT aoa[ ALL_BAND ];

    UINT fixfrq[ ALL_BAND ];
    UINT fixfrq_boundary[ ALL_BAND ];

    UINT agifrqmean;    // agile/agile, agile/pattern
    UINT agifrqin;    // agile/agile, agile/pattern
    UINT agifrqout;   // agile/agile, agile/pattern
    UINT agifrqpat[ ALL_BAND ];  // pattern/pattern
    UINT md_agifrq[ ALL_BAND ];  // debug, 00-01-31 16:35:43

    UINT fixpri;      // stable PRI.
    UINT agiprimean;    // agile/agile, agile/pattern
    UINT agipriin;    // agile/agile, agile/pattern
    UINT agipriout;   // agile/agile, agile/pattern
    UINT agipripat; // pattern/pattern

    UINT frqPrd;      // When Pattern Agile, comparative period val.
    UINT priPrd;      // When PRI Pattern, comparative period val.

    UINT scnPrd;      // When scan is sucessful, comparative period val.

    UINT jtrper;      // PRI jitter %

    UINT pw;        // PRI jitter %

    UINT mdyMethod;   // Method of modify parameter, debug, 00-08-31 10:19:35
}  ;

struct STR_FT {
    UINT aoa[ ALL_BAND ];

    UINT fixfrq[ ALL_BAND ];
    UINT agifrq[ ALL_BAND ];
    UINT agiratio;    //  debug, 00-04-19 17:46:13

    //  UINT  pw;       // PW
    //  UINT  pa;

    UINT CWTo;
    UINT CWPc;

    UINT normPc;
    UINT abnormPc;

    UINT chirpTo;
    UINT chirpPc;

    float maxTim;     // as times as scan period for collecting time out
    UINT timPrd;      // as times as scan period for collecting pulse count

    //STR_LOWHIGH tkto;   // Track Timeout
    //STR_LOWHIGH tkpc;   // Track Pulse count

    UINT scto[ _spMaxTryScan + 1 ];

}  ;

//#ModelId=452B0C4E037D
struct STR_FG {
    STR_LOWHIGH frq[ ALL_BAND ];

}  ;

//##ModelId=452B0C4E039A
struct STR_NP {
    UINT Pdw_Max;                                     // 수집 PDW 최대수
    //UINT Aoa_Shift_Cnt;                             // 방위 히스토 BIN 크기 = 2^N
    UINT Aoa_Peak_Thr;                                // 방위 히스토그램 PEAK 임계값, 00.02.09
    UINT Aoa_Hist_Thr;                                // 방위 히스토그램 범위 임계값, 00.02.09
    UINT Aoa_Range_Margin;                            // 방위 그룹 범위 margin

    UINT Freq_Shift_Cnt;                              // 주파수 히스토 BIN 크기 = 2^N
    UINT Freq_Peak_Thr;                               // 주파수 히스토그램 PEAK 임계값, 00.02.09
    UINT Freq_Hist_Thr;                               // 주파수 히스토그램 범위 임계값, 00.02.09
    UINT Freq_Range_Margin;                           // 주파수 그룹 범위 margin

    UINT Rpt_Aet_Cnt;                                 // 탐지; 하나의 그룹에서 REPORT될 AET의 개수를 선언
}  ;

//##ModelId=452B0C4E03AE
struct STR_KP {
  UINT Pdw_Max;                                       // 수집 PDW 최대수
  /*  UINT    Aoa_Shift_Cnt;                          // 방위 히스토 BIN 크기 = 2^N
      UINT    Aoa_Peak_Thr;                           // 방위 히스토그램 PEAK 임계값, 00.02.09
      UINT    Aoa_Hist_Thr;                           // 방위 히스토그램 범위 임계값, 00.02.09
      UINT    Aoa_Range_Margin;                       // 방위 그룹 범위 margin

      UINT    Freq_Shift_Cnt;                         // 주파수 히스토 BIN 크기 = 2^N
      UINT    Freq_Peak_Thr;                          // 주파수 히스토그램 PEAK 임계값, 00.02.09
      UINT    Freq_Hist_Thr;                          // 주파수 히스토그램 범위 임계값, 00.02.09
      UINT    Freq_Range_Margin;                      // 주파수 그룹 범위 margin
  */

  UINT Rpt_Aet_Cnt;                                   // 추적; 하나의 그룹에서 REPORT될 AET의 개수를 선언
}  ;

struct STR_CM
{
  UINT uiCw_Min_Cnt;       // CW신호를 분석하기 위한 최소 CW개수

  UINT Mpc;                //000223 // Stable 펄스열의 최소 펄스수 (Min. Pulse Count)
  UINT Mjpc;               //000223 // Jitter 펄스열의 최소 펄스수 (Min. Jitter Pulse Count)
  UINT Rpc;                // 기준 펄스열의 펄스수 (Reference Pule Count)
  UINT RSpc;               // 기준 펄스열의 펄스수 (Reference Pule Count)

  UINT Rjgpc;              // 000404  Jitter Stagger 기준펄스열의 최소 펄스수 (Min. Jitter Stagger Pulse Count) //!<  //!<

  UINT Stb_Max_Miss;       // 최대 허용 STABLE MISS 개수
  UINT Jit_Max_Miss;       // 최대 허용 JITTER MISS 개수

  UINT Reflex_Zone;        // 반사파 처리 구간
  UINT Hprf_First_Pri;     // 반사파처리 이전에 High PRF부터 처리

  UINT Jitter_P;           // 최대 탐지 jitter %  990226

  UINT Dtoa_Sd;            // 500ns / (50 ns) MEAN ERROR
  UINT Freq_Sd;            // low : 1.5 / (0.5MHz), mid : 3.75 / (1.25MHz), High : 4.5 / (1.5MHz)


  UINT Jstg_Pt_P;          // Jitter Stagger분석에서 Stagger로 추출된 펄스수의 비율 경계, 이상이~면 Stagger로 판정
  UINT Jit_Merge_Miss_Cnt; // 최대 허용 병합 JITTER MISS 개수

  // 패턴 분석
  UINT Pat_Min_Cnt;        // 패턴 분석에 필요한 최소 펄스수
  UINT Lhp;                // Least Half Period 최소 반주기 펄스수
  UINT Cross_Over;         // 패턴에서 LHP동안 평균을 가로지르는 최대 회수
  UINT Lhp_Thresh;         // 패턴 확인에 사용되는 최소반주기의 회수
  UINT Bad_Max;            // 패턴 확인에서 최대 bad 회수
  UINT Filt_Fac;           // Filtering Factor 패턴 파라메터 평균배열(filt[])을 만들때 평균을 취~하는 신호수
  UINT Maxparam_Min;       // 평균배열(filt[])의 최대값의 최소한의 수
  UINT Pp_Max_Margin_P;    // 패턴주기 검증에서 사용되는 최대값의 margin %
  UINT Pp_Match_P;         // 패턴주기 구하기에서 패턴비교에서 성공비율

  // MAKE AET
  UINT Conti_Thr;          // 연속성 최대 지수
  UINT Rpt_Pul_Cnt;        // 이 값 이상의 펄스수의 AET는 무조건 REPORT 대상
} ;

//##ModelId=452B0C4E03CC
struct STR_SC
{
  UINT Pdw_Max;            // 수집 PDW 최대수
  UINT st[ _spMaxTryScan ];
  UINT offst[ _spMaxTryScan ];

  //UINT thtrkprd;
} ;

//##ModelId=452B0C4E03D6
struct STR_SYS
{
  UINT mode;

  UINT ver[ 2 ];
  UINT date;

  // Control system parameters
  UINT scnLev;    // 6

  STR_SP sp;

  STR_FG pw;      // Antenna Freq. range

  //  STR_ID    id;
  STR_MG mg;
  STR_FT ft;

  // 탐지 system parameters
  STR_NP np;

  // 추적 system parameters
  STR_KP kp;

  // 공통(Common) system parameters
  STR_CM cm;

  // 스캔(SAP) system parameters
  STR_SC sc;
} ;

#endif

#ifndef _PA_RESOL_
#define _PA_RESOL_
struct PA_RESOL {
    UINT uiMin;
    UINT uiMax;
	float fOffset;
    float fRes;			// 각 구간에 따른 resolution
} ;
#endif

struct STR_DWELL_LEVEL {
	int iPulseCount1;
	_TOA dtoa1;
	int iPulseCount2;
	_TOA dtoa2;

	bool bUsed;

} ;


#ifdef _MAIN_

#ifndef _GRAPH_
  STR_SYS _sp;
#endif

  float _spFreqMin;
  float _spFreqMax;


#define DFD_FREQ_OFFSET		(1900)

#if defined(_ELINT_) || defined(_701_)
    //char g_szPulseType[MAX_STAT][3] = { "--" , "NP" , "CW" , "--" , "--", "FM", "--", "SP" };
    char g_szAetSignalType[7][3] = { "NP" , "NP" , "CW" , "FM" , "CF", "SH", "AL" };
    char g_szAetFreqType[E_AET_MAX_FRQ_TYPE][3] = { "F_" , "HP" , "RA" , "PA", "UK", "IF" };
    char g_szAetPriType[MAX_PRITYPE][3] = { "ST" , "JT", "DW" , "SG" , "PJ", "IP" } ;


    FREQ_RESOL gFreqRes[ TOTAL_BAND ] =
    {	// min, max, offset, res
        {     0,     0,				 DFD_FREQ_OFFSET,  1.25 },
        {  2000,  6000,        DFD_FREQ_OFFSET,  1.25 },		/* 저대역		*/
        {  5500, 10000,  12000-DFD_FREQ_OFFSET, -1.25 },		/* 고대역1	*/
        { 10000, 14000,  16000-DFD_FREQ_OFFSET, -1.25 },		/* 고대역2	*/
        { 14000, 18000,  12000+DFD_FREQ_OFFSET,  1.25 },		/* 고대역3	*/
        {     0,  5000,   6300-DFD_FREQ_OFFSET, -1.25 }		/* C/D			*/
    } ;

    PA_RESOL gPaRes[ 6 ] =
    {	// min, max, offset, res
        {     0,     0,  (float) _spPAoffset, _spAMPres },
        {  2000,  6000,  (float) _spPAoffset, _spAMPres },		/* 저대역		*/
        {  5500, 10000,  (float) _spPAoffset, _spAMPres },		/* 고대역1	*/
        { 10000, 14000,  (float) _spPAoffset, _spAMPres },		/* 고대역2	*/
        { 14000, 18000,  (float) _spPAoffset, _spAMPres },		/* 고대역3	*/
        {     0,  5000,  (float) -54.14071, (float) 0.24681 }		/* C/D			*/
    } ;

    double dRCLatitude[RADARCOL_MAX] = { 0.0, 37.485168456889, 37.454452514694, 37.453517913889 } ;
    double dRCLongitude[RADARCOL_MAX] = { 0.0, 126.457916259694, 126.481880188111, 126.423416137778 } ;

#elif defined(_XBAND_)
	// PDW
	//char g_szPulseType[MAX_STAT][3] = { "CW" , "NP" };

	// LOB & ABT & AET
	char g_szAetSignalType[7][3] = { "CW" , "NP" , "CW" , "FM" , "CF", "SH", "AL" };
	char g_szAetFreqType[E_AET_MAX_FRQ_TYPE][3] = { "F_" , "HP" , "RA" , "PA", "UK", "IF" };
	char g_szAetPriType[E_AET_MAX_PRI_TYPE][3] = { "ST", "JT" , "DW", "SG" , "JP" , "UP" } ;


	FREQ_RESOL gFreqRes[ TOTAL_BAND ] =
	{	// min, max, offset, res
		{     0,     0,				 DFD_FREQ_OFFSET,  1.25 },
		{  2000,  6000,        DFD_FREQ_OFFSET,  1.25 },		/* 저대역		*/
		{  5500, 10000,  12000-DFD_FREQ_OFFSET, -1.25 },		/* 고대역1	*/
		{ 10000, 14000,  16000-DFD_FREQ_OFFSET, -1.25 },		/* 고대역2	*/
		{ 14000, 18000,  12000+DFD_FREQ_OFFSET,  1.25 },		/* 고대역3	*/
		{     0,  5000,   6300-DFD_FREQ_OFFSET, -1.25 }		/* C/D			*/
	} ;

	PA_RESOL gPaRes[ 6 ] =
	{	// min, max, offset, res
		{     0,     0,  (float) _spPAoffset, _spAMPres },
		{  2000,  6000,  (float) _spPAoffset, _spAMPres },		/* 저대역		*/
		{  5500, 10000,  (float) _spPAoffset, _spAMPres },		/* 고대역1	*/
		{ 10000, 14000,  (float) _spPAoffset, _spAMPres },		/* 고대역2	*/
		{ 14000, 18000,  (float) _spPAoffset, _spAMPres },		/* 고대역3	*/
		{     0,  5000,  (float) -54.14071, (float) 0.24681 }		/* C/D			*/
	} ;

	double dRCLatitude[RADARCOL_MAX] = { 0.0, 37.485168456889, 37.454452514694, 37.453517913889 } ;
	double dRCLongitude[RADARCOL_MAX] = { 0.0, 126.457916259694, 126.481880188111, 126.423416137778 } ;

///////////////////////////////////////////////////////////////////////////////////

#elif defined(_POCKETSONATA_) || defined(_712_)
#define PDW_FREQ_RES        (1.953125)
char g_szAetSignalType[ST_MAX][10] = { "NP" , "CW" , "DOPPLER", "H-PRF" };  // { "NP" , "CW" , "FTri" , "FU", "FD", "FUk", "C-FTri", "C-FU", "C-FD", "C-FUk", "PM", "C-PM", "SHP", "DOP", "H-PRF" };
char g_szAetFreqType[(int)ENUM_AET_FRQ_TYPE::E_AET_MAX_FRQ_TYPE][3] = { "F_" , "HP" , "RA" , "PA", "UK" };
char g_szAetPriType[(int)ENUM_AET_PRI_TYPE::E_AET_MAX_PRI_TYPE][3] = { "ST" , "JT", "DW" , "SG" , "PJ", "UK" };

#ifdef _ANAL_LOG_
char g_szAetPatternType[(int)ENUM_AET_FREQ_PRI_PATTERN_TYPE::E_AET_MAX_FREQ_PRI_PATTERN_TYPE][3] = { "UK" , "SI", "S+" , "S-" , "TR" };
#endif
char g_szAetScanType[(int)ENUM_AET_SCAN_TYPE::E_AET_MAX_SCAN_TYPE][3] = { "UK" , "CI", "UN" , "BI" , "CO", "ST", "FA", "TF", "DF", "LF" };
char g_szAetScanStat[( int ) ENUM_AET_SCAN_STAT::E_AET_USER_SCAN_FAIL+1][20] = { "미실시" , "자체성공", "자체실패" , "사용자성공" , "사용자실패" };

FREQ_RESOL gFreqRes[ enMAXPRC ] = {	// min, max, offset, res
        {     0,     0, 0, (float) PDW_FREQ_RES } ,
        {     0,     0, 1984000, (float) PDW_FREQ_RES } ,
        {     0,     0, 1984000, (float) PDW_FREQ_RES } ,
        {     0,     0, 1984000, (float) PDW_FREQ_RES } ,
        {     0,     0, 1984000, (float) PDW_FREQ_RES } ,
        {     0,     0, 1984000, (float) PDW_FREQ_RES } } ;

#elif defined(_SONATA_)
  char g_szAetSignalType[ST_MAX][3] = { "UK" , "NP" , "CW" , "DP" , "HP" };
  char g_szAetFreqType[6][3] = { "--", "F_" , "HP" , "RA" , "PA", "UK" };
  char g_szAetPriType[E_AET_MAX_PRI_TYPE][3] = { "ST" , "JT", "DW" , "SG" , "PT" } ;

  FREQ_RESOL gFreqRes[ 3 ] =
  {
      {    0,  2560, 0, 0.625 },   /* LOW  FREQUENCY */
      { 1280,  6400, 1260, 1.25  },   /* MID  FREQUENCY */
      { 5866, 18740, 5866, 1.5   }
  } ;

#else
  char g_szAetSignalType[5][3] = { "UK" , "NP" , "CW" , "DP" , "HP" };
  char g_szAetFreqType[(int)ENUM_AET_FRQ_TYPE::E_AET_MAX_FRQ_TYPE][3] = { "F_" , "HP" , "RA" , "PA", "UK", "IF" };
  char g_szAetPriType[(int) ENUM_AET_PRI_TYPE::E_AET_MAX_PRI_TYPE][3] = { "ST" , "JT", "DW" , "SG" , "PJ", "IP" } ;

  PA_RESOL gPaRes[ 6 ] =
  {	// min, max, offset, res
      {     0,     0,  (float) _spPAoffset, _spAMPres },
      {  2000,  6000,  (float) _spPAoffset, _spAMPres },		/* 저대역		*/
      {  5500, 10000,  (float) _spPAoffset, _spAMPres },		/* 고대역1	*/
      { 10000, 14000,  (float) _spPAoffset, _spAMPres },		/* 고대역2	*/
      { 14000, 18000,  (float) _spPAoffset, _spAMPres },		/* 고대역3	*/
      {     0,  5000,  (float) -54.14071, (float) 0.24681 }		/* C/D			*/
  } ;

#endif


#else

extern float _spFreqMin;
extern float _spFreqMax;

#ifndef _GRAPH_
extern STR_SYS _sp;

extern char g_szAetFreqType[(int)ENUM_AET_FRQ_TYPE::E_AET_MAX_FRQ_TYPE][3];
extern char g_szAetPriType[( int ) ENUM_AET_PRI_TYPE::E_AET_MAX_PRI_TYPE][3];
#ifdef _ANAL_LOG_
extern char g_szAetPatternType[( int ) ENUM_AET_FREQ_PRI_PATTERN_TYPE::E_AET_MAX_FREQ_PRI_PATTERN_TYPE][3];
#endif

extern char g_szAetScanType[(int)ENUM_AET_SCAN_TYPE::E_AET_MAX_SCAN_TYPE][3];

#endif



#if defined(_ELINT_) || defined(_XBAND_) || defined(_701_)
extern char g_szAetSignalType[7][3];
extern FREQ_RESOL gFreqRes[ TOTAL_BAND ];
extern PA_RESOL gPaRes[ 6 ];

extern double dRCLatitude[RADARCOL_MAX];
extern double dRCLongitude[RADARCOL_MAX];

#elif defined(_POCKETSONATA_) || defined(_712_)
extern char g_szAetSignalType[ST_MAX][10];
extern char g_szAetFreqType[( int ) ENUM_AET_FRQ_TYPE::E_AET_MAX_FRQ_TYPE][3];
extern char g_szAetPriType[( int ) ENUM_AET_PRI_TYPE::E_AET_MAX_PRI_TYPE][3];

extern FREQ_RESOL gFreqRes[ enMAXPRC ];
extern PA_RESOL gPaRes[ 6 ];

#elif defined(_SONATA_)
extern char g_szAetSignalType[ST_MAX][3];
extern char g_szAetFreqType[( int ) ENUM_AET_FRQ_TYPE::E_AET_MAX_FRQ_TYPE][3];
extern char g_szAetPriType[( int ) ENUM_AET_PRI_TYPE::E_AET_MAX_PRI_TYPE][3];

extern FREQ_RESOL gFreqRes[ 3 ];
extern PA_RESOL gPaRes[ 6 ];

#else
//extern PA_RESOL gPaRes[ 6 ];
//extern FREQ_RESOL gFreqRes[ 7 ];

#endif

#endif




// qsort 함수 선언
int pdwindexCompare( const void *arg1, const void *arg2 );


