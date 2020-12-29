/****************************************************************************************
 파 일 명 : _aetipl.h
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 목    적 :
 가    정 :
 저 자 명 : Jo Churl-hee
 변 경 자 :
 변경내용 : (목적)
 변경일시 : 99-04-06 1:52오후
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 입력정의 :
 출력정의 :
 관련모듈 :
 자료구조 : (전역변수)
 에러처리/복귀순서:
 컴파일 일시 :
*****************************************************************************************/

#ifndef _AETIPL_H_
#define _AETIPL_H_

#include <time.h>
#include <sys/types.h>

#include "../SigAnal/_Type.h"

#include "system.h"

#ifdef _MIDAS_
#else
#include "../EmitterMerge/ELMsgDefn.h"
#endif

// #include "Structs.h"

//#define   Unknown   0
//#define   UNKNOWN   Unknown



///////////////////////       AET DEFINES      /////////////////////////////////////////////


//##ModelId=452B0C51000F
#ifdef _ELINT_
enum FREQ_BAND
{
    BAND0=0,
	//##ModelId=452B0C510038
    BAND1,
	//##ModelId=452B0C510041
    BAND2,
	//##ModelId=452B0C51004B
    BAND3,
	//##ModelId=452B0C51005F
	BAND4,
	BAND5,
    TOTAL_BAND
};

#elif defined(_POCKETSONATA_)

// 아래는 밴드가 없는 것을 의미합니다.
enum FREQ_BAND
{
    BAND0=0,
    //##ModelId=452B0C510038
    BAND1=0,
    //##ModelId=452B0C510041
    BAND2=0,
    //##ModelId=452B0C51004B
    BAND3=0,
    //##ModelId=452B0C51005F
    BAND4=0,
    BAND5=0,

    TOTAL_BAND
};

#else
enum FREQ_BAND
{
    BAND0=0,
	//##ModelId=452B0C510038
    BAND1         = 0,
	//##ModelId=452B0C510041
    BAND2,
	//##ModelId=452B0C51004B
    BAND3,
	//##ModelId=452B0C51005F
    TOTAL_BAND
};
#endif

// 신호 형태 정의값
enum SIGNAL_TYPE
{
    ST_NORMAL_PULSE = 1,
    ST_CW,
    ST_DOPPLER,
    ST_HIGHPRF,

	ST_FMOP,
	ST_CW_FMOP,
	ST_SHORT,
	ST_ALL,
	ST_MAX
} ;


#ifdef _ELINT_
const char aet_signal_type[7][3] = { "NP" , "CW" , "DP" , "FM" , "CF", "SH", "AL" };
#elif defined(_POCKETSONATA_)
static const char aet_signal_type[ST_MAX][3] = { "UK" , "NP" , "CW" , "DP" , "HP" };
#else
static const char aet_signal_type[5][3] = { "UK" , "NP" , "CW" , "DP" , "HP" };
#endif


//##ModelId=452B0C5100B9
enum FREQ_TYPE
{
     _FIXED              = 0,
     _HOPPING,
    _RANDOM_AGILE,
    _PATTERN_AGILE,

    _UNKNOWN_FT,

    _IGNORE_FREQ,

    MAX_FRQTYPE
} ;

#ifdef _ELINT_
const char aet_freq_type[6][3] = { "--", "F_" , "HP" , "RA" , "PA", "UK" };
#elif defined(_POCKETSONATA_)
static const char aet_freq_type[8][3] = { "F_" , "RA" , "PA", "HP", "C+", "C-", "pM" };
#elif defined(_SONATA_)
static const char aet_freq_type[8][3] = { "F_" , "RA" , "PA", "HP", "C+", "C-", "pM" };
#else
static const char aet_freq_type[8][3] = { "F_" , "RA" , "PA", "HP", "C+", "C-", "pM" };
#endif

//##ModelId=452B0C510131
enum PRI_TYPE
{
    _STABLE               = 0,
    _JITTER_RANDOM,
    _DWELL,
    _STAGGER,
    _JITTER_PATTERN,

    _IGNORE_PRI,

    MAX_PRITYPE,

    _REFSTABLE,

    _STAGGER_DWELL,


} ; // Id...
#ifdef _ELINT_
const char aet_pri_type[6][3] = { "ST" , "JT", "DW" , "SG" , "PT" } ;
#elif defined(_POCKETSONATA_)
static const char aet_pri_type[6][3] = { "ST" , "SG" , "JT" , "PT", "DW" } ;
#elif defined(_SONATA_)
static const char aet_pri_type[6][3] = { "ST" , "SG" , "JT" , "PT", "DW" } ;
#else
static const char aet_pri_type[6][3] = { "ST" , "SG" , "JT" , "PT", "DW" } ;
#endif

//##ModelId=452B0C5101C7
enum PATTERN_TYPE
{
    //##ModelId=452B0C5101DC
    UNK         = 1,
    //##ModelId=452B0C5101EF
    SINE,
    //##ModelId=452B0C5101F9
    SAW_INC,
    //##ModelId=452B0C51020D
    SAW_DEC,
    TRI,
    //##ModelId=452B0C510221
    MAX_FRQPATTYPE
} ;   // same with PRI pattern type



//enum EBUM_FREQ_TYPE { FP_UNKNOWN=0, FP_FIXED, FP_ } ;
//enum ENUM_FREQ_TYPE { FT_FIXED=0 } ;

// 에미터 목록 정의
enum { CAT_MIX=0x80, CAT_UNKNOWN=0, CAT_UNK, CAT_AIR, CAT_SHP, CAT_SMR, CAT_GRD, CAT_BASE, CAT_MSL, CAT_MSS, CAT_MAX } ;

// 에미터 적아 정의
enum { FOF_MIX=0x80, FOF_CLEAR=0, FOF_ENEMY, FOF_NEUTRAL, FOF_FRIEND, FOF_OUR, FOF_UNK, FOF_UNKNOWN, FOF_MAX } ;


/*! \bug  AdvSiganal 과 기존 RSA 와 호환을 위해서
    \date 2007-12-20 12:14:41, 조철희
*/
#define	FIXED_ (_FIXED)
#define STABLE	(_STABLE)
#define DWELL (_DWELL)
#define HOPPING (_HOPPING)
#define STAGGER (_STAGGER)
#define JITTER (_JITTER)
#define PATTERN_ (_PATTERN)
#define RANDOM_AGILE (_RANDOM_AGILE)
#define PATTERN_AGILE (_PATTERN_AGILE)
#define CHIRP_UP (_CHIRP_UP)
#define CHIRP_DN (_CHIRP_DN)
// #define PMOP (_PMOP)
#define PATTERN_STABLE (_PATTERN_STABLE)
#define PATTERN_DWELL (_PATTERN_DWELL)
#define PATTERN_STAGGER (_PATTERN_STAGGER)

#define	_spUnknown	0


/////////////////////////////////////////////////////////////////////////////////////////
// 안테나 스캔 형태 정의값
//##ModelId=452B0C51022C
enum SCAN_TYPE
{
	//##ModelId=452B0C510241
  CIRCULAR            = 1,
	//##ModelId=452B0C51024A
  UNI_DIRECTIONAL,
	//##ModelId=452B0C510254
  BI_DIRECTIONAL,
	//##ModelId=452B0C51025E
  CONICAL,
	//##ModelId=452B0C510268
  STEADY,
	//##ModelId=452B0C510286
  UFO,
	MAX_SCANTYPE,
	//##ModelId=452B0C510287
  DetType,
	//##ModelId=452B0C510290
  TYPE_UNKNOWN,
} ;

#ifdef _ELINT_
const char aet_asp_type_ch[7][3] = { "UK" , "CR" , "UD" , "BD" , "CO" , "ST" , "UF" } ;

#elif defined(_POCKETSONATA_)
static const char aet_asp_type_ch[7][3] = { "UK" , "CR" , "SC" , "TW" , "CO" , "ST" , "MA" } ;
#elif defined(_SONATA_)
static const char aet_asp_type_ch[7][3] = { "UK" , "CR" , "SC" , "TW" , "CO" , "ST" , "MA" } ;
#else
static const char aet_asp_type_ch[7][3] = { "UK" , "CR" , "SC" , "TW" , "CO" , "ST" , "MA" } ;
#endif

//##ModelId=452B0C5102A4
enum SCAN_STAT
{
	//##ModelId=452B0C5102B9
  NO_PROCESS        = 0,
	//##ModelId=452B0C5102C2
  SELF_SUCCESS,
	//##ModelId=452B0C5102CC
  SELF_FAIL,
	//##ModelId=452B0C5102D6
  REQ_SUCCESS,
	//##ModelId=452B0C5102EA
  REQ_FAIL,
	//##ModelId=452B0C5102F4
  All_Sucess        = 1,
	//##ModelId=452B0C5102FE
  All_Fail          = 6
} ;

#ifdef _ELINT_
//const char aet_asp_stat_ch[7][3] = { "UK" , "CR" , "UD" , "BD" , "CO" , "ST" , "UF" } ;
#elif defined(_POCKETSONATA_)
static const char aet_asp_stat_ch[7][3] = { "NO" , "SS" , "SF" , "RS" , "CO" , "RF" , "__" } ;
#elif defined(_SONATA_)
static const char aet_asp_stat_ch[7][3] = { "NO" , "SS" , "SF" , "RS" , "CO" , "RF" , "__" } ;
#else
static const char aet_asp_stat_ch[7][3] = { "NO" , "SS" , "SF" , "RS" , "CO" , "RF" , "__" } ;
#endif

/////////////////////////////////////////////////////////////////////////////////////////
// 기본 AET 구조
//

#define     _spMaxSwtLev            16      // 주파수, PRI Stagger 단 개수
#define     _spMaxCoSysAmbi         5				// IPL의 Ambiguity 개수

#define			_spMaxAoaQueue										(10)

/////////////////////////////////////////////////////////////////////////////////////////
//  LowHigh, MinMax 구조체
//
//##ModelId=452B0C510308
#ifndef _STR_LOWHIGH
#define _STR_LOWHIGH
struct STR_LOWHIGH
{
  int iLow;
  int iHgh;
} ;
#endif

#ifndef _STR_LOWHIGH_TOA
#define _STR_LOWHIGH_TOA
struct STR_LOWHIGH_TOA
{
    _TOA iLow;
    _TOA iHgh;
} ;
#endif

//##ModelId=452B0C510326
struct STR_LHBAND {
  int low;
  int hgh;
  int band;
} ;

//##ModelId=452B0C51033A
struct STR_MINMAX {
  int mean;
  int min;
  int max;
  // int sdev;
} ;

struct STR_MINMAX_SDEV {
  int mean;
  int min;
  int max;

  float fsdev;
} ;

struct STR_MINMAX_MEDIAN {
	int mean;
	int min;
	int max;
	int median;
} ;

struct STR_MINMAX_TOA {
	_TOA mean;
	_TOA min;
	_TOA max;
} ;

struct STR_F_MINMAX {
	float fmean;
	float fmin;
	float fmax;
} ;

//##ModelId=452B0C51034F
struct STR_TYPEMINMAX {
  int type;
  int mean;
  int min;
  int max;
} ;

/* AET용 주파수 구조체 */
//##ModelId=452B0C510363
struct STR_FRQ {
  int band;
  int type;
  int mean;
  int min;
  int max;
  int patType;
  int swtLev;
  int swtVal[ _spMaxSwtLev ];
  int patPrd;
}  ;

/* AET용 PRI 구조체 */
//##ModelId=452B0C510377
struct STR_PRI {
  int type;
  _TOA mean;
  _TOA min;
  _TOA max;
  int patType;
  float jtrPer;
  int swtLev;
  _TOA swtVal[ _spMaxSwtLev ];
  int patPrd;
} ;

/* AET용 SCAN 구조체 */
//##ModelId=452B0C510394
struct STR_AS {
  int stat;
  int type;
  int prd;
} ;

/* AET용 SEEN TIME 구조체 */
//##ModelId=452B0C5103A8
struct STR_SEEN_TIME {
  unsigned int frst;
  unsigned int last;
} ;

/* AET용 식별 구조체 */
//##ModelId=452B0C5103C7
struct STR_SYSID {
  int coAmbi;
  UINT noIPL[ _spMaxCoSysAmbi ];
} ;

#define SZ_MAX_ELNOT			8		// Elint notation 길이
#define SZ_MAX_EMITTERNAME		8		// 에미터명 길이
#define SZ_MAX_THREATNAME		8		// 위협명 길이


/* AET */
//##ModelId=452B0C5103E4
struct STR_AET {
    int noEMT;      // Emitter no.
    int sigType;    // 1:PULSE, 2:CW, 3:DOPPLER, 4:HIGHPRF
    STR_FRQ frq;        // 주파수 1:FIXED, 2:RANDOM_AGILE, 3:PATTERN_AGILE, 4:HOPPING, 5:CHIRP_UP, 6:CHIRP_DN, 7:PMOP
    STR_PRI pri;        // PRI    1:STABLE, 2:STAGGER, 3:JITTER, 4:PATTERN, 5:DWELL
    STR_MINMAX pw;         // 펄스폭
    STR_MINMAX pa;      // moved the upper line on asp.
    STR_AS as;         // 안테나 스캔
    int aoa;        // 방향
    STR_SEEN_TIME seen;       // 시간
    UINT priLev;     // 위협 레벨
    STR_SYSID id;         // 식별 결과
    UINT autoWarn;   //
    UCHAR elintNotation[ SZ_MAX_ELNOT ]; //
    UCHAR emitterName[ SZ_MAX_EMITTERNAME ];
    UCHAR threatName[ SZ_MAX_THREATNAME];
    UINT cat;
    UINT fof;

} ;

struct stEmitterNo {
	unsigned char	Class;						// 구분(N/U/D, 적아)
	unsigned char	AETNo;						// AET 번호
	unsigned short BeamNo;					// 빔 번호(EID)

} ;

// 접촉 시간
struct stContactTime {
	unsigned int	FirstSeenTime	: 17;			// 최초 접촉 시간
	unsigned int	LastSeenTime	: 15;			// 최근 접촉 시간

} ;

struct STR_CVIAET {
	stEmitterNo EmitterNo;								// 에미터 번호
	unsigned short SigType		: 7 ;				// 신호 형태
	unsigned short Brg				: 9 ;				// 방위 - 0.703125
	unsigned short Level			: 5 ;				// 레벨
	unsigned short PW					: 11;				// PW - 1ns
	unsigned char	PA;											// 신호 세기 - 0.3125
	unsigned char	FreqType;								// 주파수 형태
	unsigned short Freq;									// 주파수 - 1MHz
	unsigned char	PRIType;								// PRI 형태
	unsigned char	JitterRate;							// 지터율 - 0.1%
	unsigned short PRI;										// PRI - 10ns
	unsigned short ScanRate;							// 스캔 주기 - 1ms
	unsigned char ScanType;								// 스캔 형태
	unsigned char	Platform;								// Platform
	unsigned short Prt;										// 우선순위
	unsigned char	Range;									// 개략거리
        char ELNote[SZ_MAX_ELNOT];						// ELNOTE
	char EmitterName[SZ_MAX_EMITTERNAME];	// 에미터명
	char ThreatName[SZ_MAX_THREATNAME];		// 위협명
	stContactTime	ContactTime;						// 접촉 시간

} ;



//##ModelId=452B0C520010
struct STR_REF
{
  UINT coEMT;   // count of emitter
  UINT inEMT[ 16 ]; // index of emitter
} ;

/////////////////////////////////////////////////////////////////////////////////////////
//   셀별 추적 정보  및 에미터 할당 정보
//
//##ModelId=452B0C520024
struct STR_CHINFTAB {
  BOOL valid;              // Is this channel valid or invcalid ?, only use gKsfInfo

  UINT noEMT;              // Emitter #
  UINT stAnal;             // Status of Analysis
  UINT priority;
  UINT noCh;               /* 할당된 추적기 번호 */
  UINT noFLT;
  UINT noPrc;
  UINT fAnal;       // Scan Lock-on,Coni/Cir.

  UINT coOvAET;       // counter of overlapped AET
  //UINT inOvAET[ _spOverlapCoEMT ];

  UINT coAET;
  //UINT ioAET[ _spOverlapCoEMT ];

  UINT coPrvPDW;           /* 이전 펄스 수집 요구 갯수 */
  UINT coCurPDW;           /* 현재 펄스 수집 요구 갯수 */
  UINT tmPrvTout;          /* 이전 펄스 수집 한계 시간 */
  UINT tmCurTout;          /* 현재 펄스 수집 한계 시간 */

  // CELL_WORDS winCellword;   // in Cell_Word

  time_t t_update;   // Present time of update track filter
  time_t t_track;    // Duration time of tracking...
  time_t t_sleep;    // Duration time in track fail ...
  time_t t_prdTrack; // Track Sucess period
  time_t t_prdSleep; // Track Fail period

  // Track's Anal flag
  UINT fPrecStag; // enum KSP_ANAL { PrecStag=0, PrecFrqPat, PrecPriPat } ;
  UINT fPrecFrqPat;
  UINT fPrecPriPat;

  //
  UINT coPrecStag;
  UINT coPrecFrqPat;
  UINT coPrecPriPat;

  // Scan collecting step
  UINT fScStep;
  UINT paMin;

  //
  // Common var.
  UINT CoTry;       // Total Track try #
  UINT CoFail;      // Total Track fail #
  UINT coTry;       // Track try #
  UINT coFail;      // Track fail #

  UINT noCol;       // collection pulse #
  UINT noExt;       // extration pulse #

  BOOL bEndCol;     // 수집 완료 플레그
} ;

//##ModelId=452B0C520042
struct STR_MERGE {
  UINT coMg;    // count of merge
  UINT coHisto;
  UINT frqHisto[ 5 ];
  UINT priHisto[ 5 ];
} ;

//##ModelId=452B0C520056
struct STR_RSAID {
  UINT coAmbi;
  UINT noIPL[ _spMaxCoRsaAmbi ];
} ;

struct STR_ID_INFO {
	UINT nFoF;
	int iThreatRange;
	UINT iThreatLevel;
	UINT nPlatform;
	int nNoThreat;
	int iDistance;

} ;

//##ModelId=452B0C520061
// 추가 하려면 cmaet.c의 UpdateNewAet() 를 수정해야 함.
struct STR_EXT {
    UINT noCol;				// 펄스 수집 개수
    UINT noExt;				// 펄스 추출 개수

    UINT pt_stat;			// PDW's stat
    UINT pt_maxchannel;	// PDW's max channel

    STR_LOWHIGH aoa;	// 방위 필터링을 하기 위한 범위 정보
    STR_LOWHIGH frq;	// 주파수 Agile을 위한 주파수 필터링을 하기 위한 범위 정보

    int idxEmitter;		// m_Emitter의 인덱스

    int noMergeEMT;		// 병합될 에미터 번호

    // 식별 추가 관련 정보
    UINT bOverId;			// 식별 Over 플레그
    UINT nId;					// 식별 목록 개수

    STR_ID_INFO id;

    BOOL mark;

    int coAlive;			// 시뮬레이션할 에미터 라이프 회수

} ;

// in common memory, structure of extended aet 2
//##ModelId=452B0C520075
struct STR_COMAET {
  UINT noSerial;  // random variable
  UINT noCol;   // collection pulse #

  STR_LOWHIGH pulse;    // pulse # on process the KSP
  STR_REF ref;    // reflect wave info.
  STR_CHINFTAB ksp;   // track info.
  STR_CHINFTAB sap;   // scan info.
  STR_MERGE mg;     // merge info.
  STR_EXT ext;    // paet info.
  STR_RSAID id;

} ;

// Emitter Merge Comparative History Info
//##ModelId=452B0C520088
union STR_MG_HIST {
  UCHAR w08;
  struct
  {
    UINT ft : 1;    // freq. type comparative result flag
    UINT pt : 1;    // pri type comparative result flag
    UINT st : 1;    // scan type comparative result flag
    UINT fm : 1;    // freq. margin comparative flag
    UINT pm : 1;    // pri margin comparative flag
    UINT sm : 1;    // scan margin compartive flag
    UINT am : 1;    // direction margin comparative flag
    UINT wm : 1;    // pulse-width margin comparative flag
  } mg ;
}  ;

//##ModelId=452B0C52009C
struct STR_MG_STAT {
  UINT frqType; // When change the freq. type,
  UINT priType; // When change the pri type,
  // Stable & Stable's IPL type -> dwell
  UINT frqVal;    // Stable becomes the New switch level
  UINT priVal;    // Stable becomes the New switch level

  UINT frqLev;    // Stable becomes the New switch level
  UINT priLev;    // Stable becomes the New switch level
}  ;

//##ModelId=452B0C5200B1
struct STR_LOST {
  UINT coPulse;
  UINT outTime;
  UINT paMin;
}  ;


#ifdef _ELINT_
//##ModelId=452B0C5200D8
struct STR_NEWAET {
    // New AET structure
    // 위협 데이터 구조는 메시지의 최소 데이터 구조로 정의한다.

    STR_AET aet;    // original AET


    STR_EXT ext;    // exteded infomation of AET
}  ;
#elif defined(_POCKETSONATA_)
typedef struct SRxLOBData STR_NEWAET;
#elif defined(_SONATA_)
typedef struct SRxLOBData STR_NEWAET;
#else
typedef struct SRxLOBData STR_NEWAET;
#endif

//##ModelId=452B0C5200E3
struct STR_TRKAET {
  STR_AET aet;
  STR_CHINFTAB ksp;        // track info.
}  ;

//##ModelId=452B0C5200F6
#ifdef _A50_RWR
typedef STR_NEWAET STR_SCNAET;    // UPAET와 NEWAET는 동일구조

#else
struct STR_SCNAET
{
  STR_AET aet;
  STR_CHINFTAB sap;        // track info.
}  ;
#endif

//##ModelId=452B0C52010B
struct STR_MGAET
{
  STR_AET oAet;           // orginal AET
  STR_EXT eAet;           // AET's common AET
}  ;


//##ModelId=452B0C520120
typedef STR_NEWAET STR_UPDAET;    // UPAET와 NEWAET는 동일구조

//##ModelId=452B0C520133
struct STR_AETFLT
{
  UINT code;
  STR_AET aet;

}  ;

// 수집 관련 구조체 정의
struct STR_PDWFILTER_INFO {
	BOOL bUse;												// FALSE 이면 사용안함. TRUE 이면 사용함.
	UINT coCollect;										// 수집 개수
	UINT nCollectTime;								// 수집 시간, ms
	BOOL bComplete;										// 수집 완료 플레그

	int noFilter;											// 소프트웨어 필터판으로 사용할 때 정보
	int noEMT;
	time_t tSettingSec;								// 필터판 설정 시간, 단위 초.
	long tSettingNanoSec;							// 필터판 설정 시간, 단위 nano sec.

	int nBand;												// 대역 정보, 대역1은 0x0, 대역2는 0x1, 대역3는 0x2, 대역4는 0x3
	int nPulseType;										// 펄스 형태, 8이면, All; 4이면 FMOP, 2이면 CW, 1이면 Pulse, 7이면 Short Pulse
	int nDV;													// 방위 정보 유효 플레그, 0이면 valid, 1이면 invalid

	STR_LOWHIGH frq;									// 주파수 범위
	STR_LOWHIGH aoa;									// 방위 범위
	STR_LOWHIGH pw;										// 펄스폭 범위
	STR_LOWHIGH sa;										// 신호세기 범위

	// 수집 시간 확인을 위한 저장소-이전 TOA, 지속시간 등.
	UINT preToa;											// 이전 펄스의 TOA
	UINT duration;										// 지속 시간

	UINT nCount;

} ;

enum EMITTER_STATUS { NEW_EMITTER_STAT=0x0, UPDATE_EMITTER_STAT, MERGE_EMITTER_STAT, LOST_EMITTER_STAT, DELETE_EMITTER_STAT, MAX_EMITTER_STAT } ;
enum SCAN_MODE { NO_SCAN=0, READY_SCAN, ON_SCAN, OUT_SCAN } ;

struct STR_LOC {
    UINT coUpd;

    UINT aoaIndex;
    int aoa[_spMaxAoaQueue];

    UINT stat;	// 에미터 상태 정보
    enum SCAN_MODE scanMode;

    STR_PDWFILTER_INFO trackFI;
    STR_PDWFILTER_INFO scanFI;

    int noThreat;
    int nNoGp;

}  ;

struct STR_MANAET {
#ifdef _ELINT_
    STR_AET aet;
#elif defined(_POCKETSONATA_)
    SRxLOBData aet;
#else

#endif
    STR_EXT ext;
    STR_LOC loc;

} ;


/////////////////////////////////////////////////////////////////////////////////////////
// 기본 IPL 구조
//

/////////////////////////////////////////////////////////////////////////////////////////
//  COMMON MEMORY Flash-ROM 구성
//
//  AM29F080-90EC( 1 M-Byte )
//  TOTAL SIZE  :  16 MB( 4-column x 4-row )
//  BANK SIZE   :   4 MB( 1MB/CHIP x 4 column )
//  BANK No.    :   4 ( row )
//  SECTOR SIZE : 256 KB( 64KB/CHIP x 4 )
//  SECTOR No.  : 16/BANK, 64/TOTAL
//
//  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//   Name     Address         BLOCK ADDRESS       SECTOR
//        from    to    D31~D24 D23~D16 D15~D8  D7~D0
//  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Bank 0  0x08000000  0x083FFFFF  Chip[0] Chip[1] Chip[2] Chip[3]   #0 ~ 15
//  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Bank 1  0x08400000  0x083FFFFF  Chip[0] Chip[1] Chip[2] Chip[3]   #16 ~ 31
//  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Bank 2  0x08000000  0x083FFFFF  Chip[0] Chip[1] Chip[2] Chip[3]   #32 ~ 47
//  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Bank 3  0x08000000  0x083FFFFF  Chip[0] Chip[1] Chip[2] Chip[3]   #48 ~ 63
//  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
/////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////
//  Flash-ROM Write 용 상수 정의
//
/* Define Flash-ROM VMEbus Base Address */
#if defined(TVME8240) || defined(TVME8245)
#define ahwCMF_PgmBase		(FLASH_BASE_ADRS + 0x200000)		//0x08000000, Use for Program Download
#define ahwCMF_IPLBase		(FLASH_BASE_ADRS + 0x600000)
#define ahwCMF_SYSBase    (FLASH_BASE_ADRS + 0x7F0000)

#define ahwCMF_SLV_SYS		(0xA7000000)
#elif defined(MVME162) || defined(_WIN32)
#define ahwCMF_PgmBase		(ahwVME_CMF + 0x000000)		//0x08000000, Use for Program Download
#define ahwCMF_PgmLast		(ahwVME_CMF + 0xF00000)		//0x08F00000, 15MB
#define ahwCMF_IPLBase		(ahwVME_CMF + 0xF00000)		//0x08F00000, Use for IPL Download
#define ahwCMF_IPLLast		ahwVME_CMS					//0x09000000, 1MB
#define ahwCMF_SYSBase    (ahwVME_CMF + 0xEC0000)     //0x08F00000, Use for IPL Download

// #define ahwCMF_SLV_SYS		(0x07000000)
#elif defined(NEX7410)
#define ahwCMF_PgmBase		(FLASH_BASE_ADRS + 0x200000)		//0x08000000, Use for Program Download
#define ahwCMF_IPLBase		(FLASH_BASE_ADRS + 0x600000)
#define ahwCMF_SYSBase    (FLASH_BASE_ADRS + 0x7F0000)

#else


#endif

/* Define Flash-ROM Bank VMEbus Base Address Pointer */
#define phwCMF_Bank0    (UINT *)(ahwCMF_Bank0)
#define phwCMF_Bank1    (UINT *)(ahwCMF_Bank1)
#define phwCMF_Bank2    (UINT *)(ahwCMF_Bank2)
#define phwCMF_Bank3    (UINT *)(ahwCMF_Bank3)

/* Define Flash-ROM Byte(size 4bytes) Program Command Cycle */
#define FlsBytesProgCmd_1 0xAAAAAAAA
#define FlsBytesProgCmd_2 0x55555555
#define FlsBytesProgCmd_3 0xA0A0A0A0

/* Define Flash-ROM Sector(Size 256kbyte) Erase Command Cycle */
#define FlsSectEraseCmd_1 0xAAAAAAAA
#define FlsSectEraseCmd_2 0x55555555
#define FlsSectEraseCmd_3 0x80808080
#define FlsSectEraseCmd_4 0xAAAAAAAA
#define FlsSectEraseCmd_5 0x55555555
#define FlsSectEraseCmd_6 0x30303030

/* Define Flash-ROM Sector(256 KBytes) Size */
#define FlsSectSize_Byte  0x40000       // debug, for test
#define FlsSectSize_Uint  0x10000

/* Define Flash-ROM Bank(4 MBytes) Size */
#define FlsBankSize_Byte  0x400000
#define FlsBankSize_Uint  0x100000

/* IPL의 Flash-ROM Write Status Report 빈도 상수 정의 : IPL 100개 마다 Status 보고 */
#define _spIplWriteRatio  10      // ratio of inc. write status
#define _spIplWriteStatThr  40
#define _spIplEraseStatThr  40
#define _spIplWriteStatEnd  100

/* Flash ROM Write 후 대기 Loop 회수 정의 : 10, Normal 7 us에 Loop 회 정도면 Write 됨 */
#define _spMaxWriteWait   20

/* Flash ROM Blank Data 정의 */
#define _spBlankFlash   0xFFFFFFFF

/////////////////////////////////////////////////////////////////////////////////////////
//  IPL용 주파수 구조체
//
//##ModelId=452B0C520147
struct IPL_FRQ {
  UINT type;
  int low;
  int hgh;
  UINT bw;
  UINT patType;
  int swtLev;
  int swtValLow[ _spMaxSwtLev ];
  int swtValHgh[ _spMaxSwtLev ];
  UINT ppLow;
  UINT ppHgh;
} ;

/////////////////////////////////////////////////////////////////////////////////////////
//  IPL용 PRI 구조체
//
//##ModelId=452B0C52015B
struct IPL_PRI {
  UINT type;
  int low;
  int hgh;
  UINT patType;
  UINT jtrPer;
  int swtLev;
  int swtValLow[ _spMaxSwtLev ];
  int swtValHgh[ _spMaxSwtLev ];
  UINT ppLow;
  UINT ppHgh;
} ;

/////////////////////////////////////////////////////////////////////////////////////////
//  IPL용 LowHigh 구조체
//
//##ModelId=452B0C52016F
struct IPL_LOWHGH
{
  int low;
  int hgh;
} ;

/////////////////////////////////////////////////////////////////////////////////////////
//  IPL용 스캔 구조체
//
//##ModelId=452B0C52018D
struct IPL_AS {
  UINT type;
  UINT prdLow;
  UINT prdHgh;
} ;

/////////////////////////////////////////////////////////////////////////////////////////
//  IPL용 platform 구조체
//
//##ModelId=452B0C5201A1
struct IPL_PLAT
{
  UINT noplat;
  UCHAR platName[ 20 ];
} ;   //추가 `98.8.25

/////////////////////////////////////////////////////////////////////////////////////////
//  IPL 구조체
//
#ifdef M68K
//##ModelId=452B0C5201B5
typedef struct
{
  UINT noIPL;
  UINT sigType;
  IPL_FRQ frq;
  IPL_PRI pri;
  IPL_LOWHGH pw;
  IPL_AS as;
  UINT tmoDel;
  UINT thrLev;
  UINT autoWarn;
  UCHAR elintNot[ 8 ];
  UCHAR elintName[ 20 ];
  UINT cat;
  UINT thrERP;
  IPL_PLAT platform[ 5 ]; // Modified `98.8.25

  UINT checksum;
} STR_IPL;

#else
struct STR_IPL {
  UINT noIPL;
  int sigType;
  IPL_FRQ frq;
  IPL_PRI pri;
  IPL_LOWHGH pw;
  IPL_AS as;
  UINT tmoDel;
  UINT thrLev;
  UINT autoWarn;
  UCHAR elintNot[ 8 ];
  UCHAR elintName[ 20 ];
  UINT cat;
  UINT thrERP;
  IPL_PLAT platform[ 5 ];    // Modified `98.8.25
} ;

static const char ipl_signal_type[ST_MAX][10] = { "UK" , "Pulsed" , "CW" };

enum IPL_FREQ_TYPE
{
    //##ModelId=452B0C5100CE
  IPL_FIXED              = 1,
    //##ModelId=452B0C5100D7
  IPL_RANDOM_AGILE,
    //##ModelId=452B0C5100E1
  IPL_PATTERN_AGILE,
    //##ModelId=452B0C5100EB
  IPL_HOPPING,
    //##ModelId=452B0C5100F5
  IPL_CHIRP_UP,
    //##ModelId=452B0C5100FF
  IPL_CHIRP_DN,
    //##ModelId=452B0C510109
  IPL_PMOP,
    //##ModelId=452B0C51011D
  IPL_MaxFRQ
} ;

enum IPL_PRI_TYPE
{
    //##ModelId=452B0C510146
  IPL_STABLE               = 1,
    //##ModelId=452B0C510159
  IPL_STAGGER,
    //##ModelId=452B0C510163
  IPL_JITTER,
    //##ModelId=452B0C51016D
  IPL_PATTERN,
    //##ModelId=452B0C510177
  IPL_DWELL,

  IPL_MaxPRI
} ; // Id...

//static const char ipl_freq_type[ST_MAX][10] = { "UK" , "Pulsed" , "CW" };

//static const char ipl_pri_type[IPL_MaxFRQ][10] = { "UK" , "FX" , "RA", "PA", "HP" };

#endif

#endif
