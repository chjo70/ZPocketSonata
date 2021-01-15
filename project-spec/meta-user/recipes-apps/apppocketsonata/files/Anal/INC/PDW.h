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

//////////////////////////////////////////////////////////////////////////

union UZPOCKETPDW
{
//#define uint32_t unsigned int

    struct {
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

    } ;

    unsigned char chData[24];

} ;

union DMAPDW {
    char chData[32];
    union UZPOCKETPDW uPDW;

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

// 아래는 MIDAS 변환을 하기 위해서 각 장치별로 변환 구조체 필요....

#ifndef _PDW_STRUCT
#define _PDW_STRUCT
struct _PDW {
    _TOA ullTOA;

	int iFreq;
	int iPulseType;
	int iPA;
	int iPW;
	int iPFTag;
	int iAOA;

#ifdef _ELINT_
	float fPh1;
	float fPh2;
	float fPh3;
	float fPh4;
#endif

} ;
#endif

//#define _MAX_PDW					(4096)

#ifndef _STR_PDWDATA
#define _STR_PDWDATA
struct STR_PDWDATA {
    union UNION_HEADER {
        struct STR_ELINT_HEADER {
            unsigned char aucTaskID[LENGTH_OF_TASK_ID];
            unsigned int iIsStorePDW;
            int iCollectorID;
            ENUM_BANDWIDTH enBandWidth;
        } el ;

        struct POCKETSONATA_HEADER {
            unsigned int iBoardID;
            unsigned int iBank;
            unsigned int iIsStorePDW;
        } ps ;

        struct SONATA_HEADER {
            unsigned int uiBand;
            unsigned int iIsStorePDW;
        } so ;
    } x;

    UINT uiTotalPDW;

    _PDW stPDW[MAX_PDW];

}  ;

#endif


#ifdef _ELINT_

#ifndef _PDW_STRUCT
#define _PDW_STRUCT
typedef struct {
    long long int llTOA;

    int iFreq;
    int iPulseType;
    int iPA;
    int iPW;
    int iPFTag;
    int iAOA;

    float fPh1;
    float fPh2;
    float fPh3;
    float fPh4;

} _PDW;
#endif

#ifndef ENUM_BANDWIDTH_ENUM
#define ENUM_BANDWIDTH_ENUM
typedef enum {
    en5MHZ_BW=0,
    en50MHZ_BW,

} ENUM_BANDWIDTH ;
#endif

#elif defined(_POCKETSONATA_)

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

// #ifndef _STR_PDWDATA
// #define _STR_PDWDATA
// struct STR_PDWDATA {
// #ifdef _ELINT_
//     unsigned char aucTaskID[LENGTH_OF_TASK_ID];
//     unsigned int iIsStorePDW;
//     int iCollectorID;
//     ENUM_BANDWIDTH enBandWidth;
// 
// #elif defined(_POCKETSONATA_)
//     unsigned int iBoardID;
//     unsigned int iBank;
//     unsigned int iIsStorePDW;
// #elif defined(_SONATA_)
//     unsigned int uiBand;
//     unsigned int iIsStorePDW;
// #else
// 
// #endif
// 
//     UINT uiTotalPDW;
// 
//     _PDW stPDW[MAX_PDW];
// 
// }  ;
//#endif

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

#ifndef _PDW_STRUCT
#define _PDW_STRUCT
struct _PDW {
    long long int llTOA;

    int iFreq;
    int iPulseType;
    int iPA;
    int iPW;
    int iPFTag;
    int iAOA;

    float fPh1;
    float fPh2;
    float fPh3;
    float fPh4;

} ;
#endif

#ifndef _ENUM_BANDWIDTH_
#define _ENUM_BANDWIDTH_
typedef enum {
    en5MHZ_BW=0,
    en50MHZ_BW,

} ENUM_BANDWIDTH ;
#endif

#ifndef _STR_PDWDATA
#define _STR_PDWDATA
struct STR_PDWDATA {
#ifdef _ELINT_
    unsigned char aucTaskID[LENGTH_OF_TASK_ID];
    unsigned int iIsStorePDW;
    int iCollectorID;
    ENUM_BANDWIDTH enBandWidth;

#elif defined(_POCKETSONATA_)
    unsigned int uiBand;
    unsigned int iIsStorePDW;
#elif defined(_SONATA_)
    unsigned int uiBand;
    unsigned int iIsStorePDW;
#else

#endif

    UINT uiTotalPDW;

    _PDW stPDW[MAX_PDW];

}  ;
#endif

#ifndef _ENUM_BANDWIDTH_
#define _ENUM_BANDWIDTH_
typedef enum {
    en5MHZ_BW=0,
    en50MHZ_BW,

} ENUM_BANDWIDTH ;
#endif

#else
// 수퍼헷 수신장치 개발한 것의 PDW 포멧
struct TNEW_SPDW
{
	float Freq ;
	float PA ;
	float PW ;
	unsigned int TOA ;
	int Ref_Phase3 ;

} ;
#endif

//////////////////////////////////////////////////////////////////////////
// PDW 신호 상태

#ifdef _ELINT_
#define PDW_DV				(1)

#define PDW_NORMAL          (1)
#define PDW_CW              (0)


#elif defined(_POCKETSONATA_)

#define PDW_NORMAL          (0)
#define PDW_CW              (1)

#define PDW_DV				(1)
#elif defined(_SONATA_)
#define PDW_CW              4
#define PDW_CHIRPUP         2
#define PDW_CHIRPDN         3
#define PDW_PMOP            1
#define PDW_NORMAL          0

#define PDW_DV				(1)

#else
#define PDW_DV				(1)

//PDW 상태 별 정의 값
#define PDW_NORMAL          (1)
#define PDW_CW              (2)
#define PDW_FMOP						(5)
#define PDW_CW_FMOP					(6)
#define PDW_SHORTP          (7)
#define PDW_ALL							(8)

#endif

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//

#define _701_LENGTH_OF_TASK_ID			(20)		//과제ID 문자열 길이 (TBD)

#pragma pack(push, 1)

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

#pragma pack(pop)

/**
 * @brief KFX 데이터애 저장된 헤더 파일
 */
struct STR_PDWFILE_HEADER {
    unsigned int uiSearchBandNo;
    unsigned int uiSignalDeletingStatus;
    unsigned int uiSignalCount;

    unsigned int uiBoardID;

} ;


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


#endif  // #ifndef _PDW_H_

