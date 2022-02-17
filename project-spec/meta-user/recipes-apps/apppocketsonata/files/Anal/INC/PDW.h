/****************************************************************************************
 파 일 명 : _pdw.h
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 목    적 : PDW 정의
 가    정 :
 저 자 명 : 조철희
 변 경 자 :
 변경내용 : (목적)
 변경일시 : 2007-12-28 10:05:31
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 입력정의 :
 출력정의 :
 관련모듈 :
 자료구조 : (전역변수)
 에러처리/복귀순서:
 컴파일 일시 :
*****************************************************************************************/

#ifndef _PDW12_H_
#define _PDW12_H_

#include "../SigAnal/_Type.h"
#include "../SigAnal/_Define.h"

#define LENGTH_OF_TASK_ID			(19+1)		//과제ID 문자열 길이 (TBD)

#ifndef _TOA_
#ifdef _VXWORKS_
typedef unsigned long long _TOA;
#else
typedef unsigned long long int _TOA;
#endif

#endif

//////////////////////////////////////////////////////////////////////////

union UZPOCKETPDW {

    struct PDWWORD {
        //
        // 마지막 구조체 : 방위, 신호세기
        union {
            unsigned int pdw_status;
            struct {
                unsigned int cw_pulse		: 1; // '0' - pulse, '1' - CW
                unsigned int pmop_flag		: 1; // '0' - No-mop, '1'-mop
                unsigned int fmop_flag		: 1; // '0' - No-mop, '1'-mop
                unsigned int false_pdw		: 1; // '0' - ture, '1'-false
                unsigned int fmop_dir		: 2; // '0' - tri, '1' - up, '2' - down, '3' - unknown
                unsigned int reserved		: 10;

                unsigned int fmop_bw		: 16; // res = 1.953125 MHz
            } stPdw_status;
        } uniPdw_status;

        //
        // 마지막 구조체 : 방위, 신호세기
        union {
            unsigned int	pdw_dir_pa;
            struct {
                unsigned int doa			: 12; // res = 0.087890625 deg
                unsigned int di				: 1; // '0' - Valid, '1' - invalid
                unsigned int reserved		: 3;
                unsigned int pa				: 16; // res = 0 ~ 65536 (linear scale)
            } stPdw_dir_pa;
        } uniPdw_dir_pa;

        //
        // 마지막 구조체 : 펄스폭, 주파수
        union {
            unsigned int pdw_pw_freq;
            struct {
                unsigned int pulse_width	: 24;
                unsigned int frequency_L	: 8;
            } stPdw_pw_freq;
        } uniPdw_pw_freq;

        //
        // 마지막 구조체 : 상위 주파수 와 TOA
        union {
            unsigned int pdw_freq_toa;
            struct {
                unsigned int frequency_H	: 8;
                unsigned int pdw_phch		: 8;
                unsigned int toa_L			: 16;
            } stPdw_freq_toa;
        } uniPdw_freq_toa;

        //
        // 마지막 구조체 : 상위 TOA
        union {
            unsigned int pdw_toa_edge;
            struct {
                unsigned int toa_H			: 28;
                unsigned int edge			: 1;
                unsigned int reserved		: 3;
            } stPdw_toa_edge;
        } uniPdw_toa_edge;

        //
        // 마지막 구조체 : PDw
        union {
            unsigned int pdw_index;
            struct {
                unsigned int index          : 16;
                unsigned int reserved       : 16;
            } stPdw_index;
        } uniPdw_index;

    } x ;

    unsigned char chData[24];

} ;

union DMAPDW {
    char chData[32];
    union UZPOCKETPDW uPDW;

    _TOA GetTOA() {
        _TOA ullTOA;

        ullTOA = uPDW.x.uniPdw_freq_toa.stPdw_freq_toa.toa_L | ( (_TOA) uPDW.x.uniPdw_toa_edge.stPdw_toa_edge.toa_H << 16 );

        return ullTOA;
    }

    int GetChannel() {
        int iCh;

        iCh = uPDW.x.uniPdw_freq_toa.stPdw_freq_toa.pdw_phch;
        iCh = ( 16 + ( iCh - 8 ) ) % 16;

        return iCh;
    }

    unsigned int GetFrequency( int iCh ) {
        unsigned int uiFrequency;

        uiFrequency = ( uPDW.x.uniPdw_pw_freq.stPdw_pw_freq.frequency_L ) | ( uPDW.x.uniPdw_freq_toa.stPdw_freq_toa.frequency_H << 8 );
        uiFrequency = ( 0x10000 + ( uiFrequency - 0x8000 ) ) % 0x10000;

        uiFrequency = uiFrequency + ( iCh * 0x10000 );

        return uiFrequency;

    }

    unsigned int GetPulsewidth() {
        unsigned int uiPulsewidth;

        uiPulsewidth = uPDW.x.uniPdw_pw_freq.stPdw_pw_freq.pulse_width;
        return uiPulsewidth;

    }

    unsigned int GetAOA() {
        unsigned int uiAOA;

        uiAOA = uPDW.x.uniPdw_dir_pa.stPdw_dir_pa.doa;
        return uiAOA;

    }

    unsigned int GetPulseamplitude() {
        unsigned int uiPA;

        uiPA = uPDW.x.uniPdw_dir_pa.stPdw_dir_pa.pa;
        return uiPA;

    }

    int GetPulsetype() {
        int iSignaltype = STAT_NORMAL;

        if( uPDW.x.uniPdw_status.stPdw_status.cw_pulse == 1 )
            iSignaltype = STAT_CW;
        else {
            if( uPDW.x.uniPdw_status.stPdw_status.pmop_flag == 1 )
                iSignaltype = STAT_PMOP;
            else if( uPDW.x.uniPdw_status.stPdw_status.fmop_flag == 1 ) {                    
                if( uPDW.x.uniPdw_status.stPdw_status.fmop_dir == 1 )
                    iSignaltype = STAT_CHIRPUP;
                else 
                    iSignaltype = STAT_CHIRPDN;
            }

        }

        return iSignaltype;
    }

};

//////////////////////////////////////////////////////////////////////////

#define PDW_WORD_LEN        4
#define PDW_WORD_CNT        4

// PDW 파일, Platform이 어떤 것이냐에 따라 UNIX 로 정의하여 컴파일 또는 없이 컴파일함.
#ifndef _WIN32
//##ModelId=452B0C500266
typedef union
{
    UCHAR bpdw[ PDW_WORD_CNT ][ PDW_WORD_LEN ];
    UINT wpdw[ PDW_WORD_CNT ];
    struct
    {
        UCHAR phase1 : 2; /* Phase 1 */
        UCHAR stat : 4;
        UCHAR direction_h : 2;
        UCHAR direction_l : 8;
        UCHAR dv : 1;
        UCHAR band : 2;
        UCHAR frequency_h : 5;
        UCHAR frequency_l : 8;

        UCHAR phase2 : 2; /* Phase 2 */
        UCHAR fil1 : 2;
        UCHAR pq : 1;
        UCHAR pulse_width_h : 3;
        UCHAR pulse_width_l : 8;
        UCHAR toa_1 : 8;
        UCHAR amplitude : 8;

        UCHAR phase3 : 2; /* Phase 3 */
        UCHAR fil2 : 6;
        UCHAR toa_2 : 8;
        UCHAR toa_3 : 8;
        UCHAR toa_4 : 8;

        UCHAR phase4 : 2; /* Phase 4 */
        UCHAR fil3 : 5;
        UCHAR chlp : 1;
        UCHAR channel : 8;
        UCHAR pmop : 8;
        UCHAR freq_diff : 8;
    } item;
} TNEW_PDW;

#else /* dos */

typedef union
{
    UCHAR bpdw[ PDW_WORD_CNT ][ PDW_WORD_LEN ];
    UINT wpdw[ PDW_WORD_CNT ];
    struct
    {
        UCHAR direction_h : 2;  /* Phase 1 */
        UCHAR stat : 4;
        UCHAR phase1 : 2;
        UCHAR direction_l : 8;
        UCHAR frequency_h : 5;
        UCHAR band : 2;
        UCHAR dv : 1;

        UCHAR frequency_l : 8;  /* Phase 2 */
        UCHAR pulse_width_h : 3;
        UCHAR pq : 1;
        UCHAR fil1 : 2;
        UCHAR phase2 : 2;
        UCHAR pulse_width_l : 8;
        UCHAR toa_4 : 8;

        UCHAR amplitude : 8;  /* Phase 3 */
        UCHAR fil2 : 6;
        UCHAR phase3 : 2;
        UCHAR toa_3 : 8;
        UCHAR toa_2 : 8;
        UCHAR toa_1 : 8;

        UCHAR chlp : 1; /* Phase 4 */
        UCHAR fil3 : 5;
        UCHAR phase4 : 2;
        UCHAR channel : 8;
        UCHAR pmop : 8;
        UCHAR freq_diff : 8;
    } item ;
} TNEW_PDW;

#endif


// 수퍼헷 수신장치 개발한 것의 PDW 포멧
struct TNEW_SPDW
{
    float Freq ;
    float PA ;
    float PW ;
    unsigned int TOA ;
    int Ref_Phase3 ;

} ;



// 아래는 MIDAS 변환을 하기 위해서 각 장치별로 변환 구조체 필요....

#ifndef _PDW_STRUCT
#define _PDW_STRUCT
struct _PDW {
    unsigned long long int ullTOA;

    int iPulseType;

    unsigned int uiAOA;
	unsigned int uiFreq;
	unsigned int uiPA;
	unsigned int uiPW;

	int iPFTag;	

#ifdef _GRAPH_
	float fPh1;
	float fPh2;
	float fPh3;
	float fPh4;

#else
#if defined(_ELINT_) || defined(_XBAND_)
	float fPh1;
	float fPh2;
	float fPh3;
	float fPh4;

#elif _POCKETSONATA_
    int iPMOP;
    int iFMOP;

    int iChannel;
#endif
#endif

    _TOA GetTOA() {
        return ullTOA;
    }

    int GetChannel() {
#ifdef _POCKETSONATA_
        return iChannel;
#else
        return 0;
#endif
    }

    unsigned int GetFrequency( int iCh=0 ) {
        return uiFreq;
    }

    unsigned int GetPulsewidth() {
        return uiPW;
    }

    unsigned int GetAOA() {
        return uiAOA;
    }

    unsigned int GetPulseamplitude() {
        return uiPA;

    }

    int GetPulsetype() {
        return iPulseType;
    }


} ;
#endif


#if defined(_ELINT_) || defined(_XBAND_)

#ifndef _ENUM_BANDWIDTH_
#define _ENUM_BANDWIDTH_
typedef enum {
    en5MHZ_BW=0,
    en50MHZ_BW,

} ENUM_BANDWIDTH ;
#endif



#elif defined(_POCKETSONATA_)



//#define LENGTH_OF_TASK_ID			(19+1)		//과제ID 문자열 길이 (TBD)

#ifndef _ENUM_BANDWIDTH_
#define _ENUM_BANDWIDTH_
typedef enum {
    en5MHZ_BW=0,
    en50MHZ_BW,

} ENUM_BANDWIDTH ;
#endif


#ifndef _ENUM_BANDWIDTH_
#define _ENUM_BANDWIDTH_
typedef enum {
    en5MHZ_BW=0,
    en50MHZ_BW,

} ENUM_BANDWIDTH ;
#endif

#elif defined(_SONATA_)

#ifndef _ENUM_BANDWIDTH_
#define _ENUM_BANDWIDTH_
typedef enum {
    en5MHZ_BW=0,
    en50MHZ_BW,

} ENUM_BANDWIDTH ;
#endif

// 수퍼헷 수신장치 개발한 것의 PDW 포멧
struct TNEW_SPDW
{
    float Freq ;
    float PA ;
    float PW ;
    unsigned int TOA ;
    int Ref_Phase3 ;

} ;

//#define LENGTH_OF_TASK_ID			(19+1)		//과제ID 문자열 길이 (TBD)

#ifndef _ENUM_BANDWIDTH_
#define _ENUM_BANDWIDTH_
typedef enum {
    en5MHZ_BW=0,
    en50MHZ_BW,

} ENUM_BANDWIDTH ;
#endif



#ifndef _ENUM_BANDWIDTH_
#define _ENUM_BANDWIDTH_
typedef enum {
    en5MHZ_BW=0,
    en50MHZ_BW,

} ENUM_BANDWIDTH ;
#endif

#else



#endif

//////////////////////////////////////////////////////////////////////////
// PDW 신호 상태

// #if defined(_ELINT_) || defined(_XBAND_)
// #define PDW_DV				(1)
// 
// #define PDW_NORMAL          (1)
// #define PDW_CW              (0)
// 
// 
// #elif defined(_POCKETSONATA_)
// 
// #define PDW_NORMAL          (0)
// #define PDW_CW              (1)
// 
// #define PDW_DV				(1)
// #elif defined(_SONATA_)
// #define PDW_CW              4
// #define PDW_CHIRPUP         2
// #define PDW_CHIRPDN         3
// #define PDW_PMOP            1
// #define PDW_NORMAL          0
// 
// #define PDW_DV				(1)
// 
// #else
// #define PDW_DV				(1)
// 
// //PDW 상태 별 정의 값
// #define PDW_NORMAL          (1)
// #define PDW_CW              (2)
// #define PDW_FMOP						(5)
// #define PDW_CW_FMOP					(6)
// #define PDW_SHORTP          (7)
// #define PDW_ALL							(8)
// 
// #endif

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//

#define _701_LENGTH_OF_TASK_ID			(20)		//과제ID 문자열 길이 (TBD)


#if TOOL==diab 
#pragma pack( 1 )
#else
#pragma pack( push, 1 )
#endif

struct SRxPDWHeader {
    unsigned int uiAcqTime;
    unsigned int uiAcqTimeMilSec;
    int iPDWSetID;
    int iSDFID;
    unsigned char aucTaskID[_701_LENGTH_OF_TASK_ID];
    int iSearchBandID;
    int	iAETID;
    int	iLOBID;
    int	iNumOfPDW;

    void CheckColTime() {
        
    }

} ;

struct SRxPDWDataRGroup {
    unsigned long long int ullTOA;
    int	iSignalType;
    int	iPolFlag;
    int	iFMOPFlag;
    int	iPMOPFlag;
    int	iBlankingTag;
    int	iIsChannelChangePOP;
    int	iBLK;

    int	iDirectionVaild;
    int	iAcqDirectionLimit;
    int	iChannelNumber;
    int	iPA;
    int	iFreq;
    int	iDirection;
    int	iPolization;
    int	iPFTag;
    int	iPW;
    UINT uiPDWID;

} ;



#ifdef _POCKETSONATA_
typedef DMAPDW SIGAPDW;

#elif defined(_ELINT_) || defined(_XBAND_)
typedef _PDW SIGAPDW;

#elif defined(_SONATA_)

#endif



#if TOOL==diab 
#pragma pack( 4 )
#else
#pragma pack( pop )
#endif

/**
 * @brief KFX 데이터애 저장된 헤더 파일
 */
// struct STR_PDWFILE_HEADER {
//     unsigned int uiSearchBandNo;
//     unsigned int uiSignalDeletingStatus;
//     unsigned int uiSignalCount;
// 
//     unsigned int uiBoardID;
// 
// } ;


typedef struct {
	//ENUM_COL_MODE enMode;
	float fCenterFreq;
	float fColTime;
	UINT uiColNumber;
	float fThreshold;

} STR_IQ_HEADER;

struct TNEW_IQ {
	short sI;
	short sQ;
}  ;

#ifndef _STR_COMMON_HEADER_
#define _STR_COMMON_HEADER_
// 아래는 공용 정보
typedef struct {
    UINT uiTotalPDW;
    __time32_t tColTime;
    UINT uiColTimeMs;
    UINT _dummy;

    void CheckColTime() {
        if( tColTime < 0 ) {
            tColTime = 0;
        }

        if( uiColTimeMs > 1000 ) {
            uiColTimeMs = 0;
        }
    }

} STR_COMMON_HEADER ;
#endif

#ifndef _STR_ELINT_HEADER_
#define _STR_ELINT_HEADER_
typedef struct {
    unsigned char aucTaskID[LENGTH_OF_TASK_ID];
    unsigned int iIsStorePDW;
    int iCollectorID;
    ENUM_BANDWIDTH enBandWidth;

    // 아래는 공용 정보
    STR_COMMON_HEADER stCommon;

    unsigned int GetTotalPDW() {
        return stCommon.uiTotalPDW;
    }

    void SetTotalPDW( unsigned int uiTotalPDW ) {
        stCommon.uiTotalPDW = uiTotalPDW;
    }

    void SetIsStorePDW( unsigned int isStorePDW ) {
        iIsStorePDW = isStorePDW;
    }

    void CheckColTime() {
        stCommon.CheckColTime();
    }

} STR_ELINT_HEADER ;
#endif

#ifndef _POCKETSONATA_HEADER_
#define _POCKETSONATA_HEADER_
typedef struct {
    unsigned int iBoardID;
    unsigned int iBank;
    unsigned int uiBand;                // 주파수 대역
    unsigned int iIsStorePDW;

    // 아래는 공용 정보
    STR_COMMON_HEADER stCommon;

    unsigned int GetTotalPDW() {
        return stCommon.uiTotalPDW;
    }
    
    void SetTotalPDW( unsigned int uiTotalPDW ) {
        stCommon.uiTotalPDW = uiTotalPDW;
    }

    void SetIsStorePDW( unsigned int isStorePDW ) {
        iIsStorePDW = isStorePDW;
    }

    void CheckColTime() {
        stCommon.CheckColTime();

    }

} POCKETSONATA_HEADER ;
#endif

#ifndef _SONATA_HEADER_
#define _SONATA_HEADER_
typedef struct {
    unsigned int uiBand;
    unsigned int iIsStorePDW;

    // 아래는 공용 정보
    STR_COMMON_HEADER stCommon;

    unsigned int GetTotalPDW() {
        return stCommon.uiTotalPDW;
    }

    void SetTotalPDW( unsigned int uiTotalPDW ) {
        stCommon.uiTotalPDW = uiTotalPDW;
    }

    void SetIsStorePDW( unsigned int isStorePDW ) {
        iIsStorePDW = isStorePDW;
    }

} SONATA_HEADER ;
#endif

#ifndef _UNION_HEADER_
#define _UNION_HEADER_
typedef union {
    STR_ELINT_HEADER el;

    POCKETSONATA_HEADER ps;

    SONATA_HEADER so;

    unsigned int GetTotalPDW( ENUM_UnitType enUnitType ) {
        unsigned int uiTotalPDW;

        switch( enUnitType ) {
        case en_ZPOCKETSONATA :
            uiTotalPDW = ps.stCommon.uiTotalPDW;
            break;

        case en_ELINT :
        case en_XBAND :
            uiTotalPDW = el.stCommon.uiTotalPDW;
            break;

        case en_SONATA :
            uiTotalPDW = so.stCommon.uiTotalPDW;
            break;

        }
        return uiTotalPDW;

    }

} UNION_HEADER;
#endif

#ifndef _STR_PDWDATA
#define _STR_PDWDATA
struct STR_PDWDATA {
    UNION_HEADER x;

    _PDW stPDW[MAX_PDW];

    unsigned int GetHeader() {
        unsigned int uiHeader;

#ifdef _POCKETSONATA_
        uiHeader = sizeof( POCKETSONATA_HEADER );
#elif defined(_ELINT_) || defined(_XBAND_)
        uiHeader = sizeof( STR_ELINT_HEADER );
#else
        uiHeader = sizeof( SONATA_HEADER );
#endif
        return uiHeader;

    }

    unsigned int GetTotalPDW() {
        unsigned int uiTotalPDW;

#ifdef _POCKETSONATA_
        uiTotalPDW = x.ps.stCommon.uiTotalPDW;
#elif defined(_ELINT_) || defined(_XBAND_)
        uiTotalPDW = x.el.stCommon.uiTotalPDW;
#else
        uiTotalPDW = x.so.stCommon.uiTotalPDW;
#endif
        return uiTotalPDW;

    }

    void SetTotalPDW( unsigned int uiTotalPDW ) {
#ifdef _POCKETSONATA_
        x.ps.stCommon.uiTotalPDW = uiTotalPDW;
#elif defined(_ELINT_) || defined(_XBAND_)
        x.el.stCommon.uiTotalPDW = uiTotalPDW;;
#else
        x.so.stCommon.uiTotalPDW = uiTotalPDW;;
#endif
        return;

    }

    void SetColTime( __time32_t tColTime, UINT uiColTimeMs ) {

#ifdef _POCKETSONATA_
        x.ps.stCommon.tColTime = tColTime;
        x.ps.stCommon.uiColTimeMs = uiColTimeMs;
#elif defined(_ELINT_) || defined(_XBAND_)
        x.el.stCommon.tColTime = tColTime;
        x.el.stCommon.uiColTimeMs = uiColTimeMs;
#else
        x.so.stCommon.tColTime = tColTime;
        x.so.stCommon.uiColTimeMs = uiColTimeMs;
#endif
        return;

    }

}  ;

#endif


#endif  // #ifndef _PDW_H_

