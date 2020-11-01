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

#ifndef _PDW_H_
#define _PDW_H_

#include "../SigAnal/_Type.h"

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


#ifdef _ELINT_

#define LENGTH_OF_TASK_ID			(19+1)		//과제ID 문자열 길이 (TBD)

#define _MAX_PDW					(4096)

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

#define LENGTH_OF_TASK_ID			(19+1)		//과제ID 문자열 길이 (TBD)

#define _MAX_PDW					(4096)

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

#ifndef _POCKETSONATA_
    float fPh1;
    float fPh2;
    float fPh3;
    float fPh4;
#endif

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

    _PDW stPDW[_MAX_PDW];

}  ;
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

#define LENGTH_OF_TASK_ID			(19+1)		//과제ID 문자열 길이 (TBD)

#define _MAX_PDW					(4096)

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

    _PDW stPDW[_MAX_PDW];

}  ;
#endif

#ifndef _ENUM_BANDWIDTH_
#define _ENUM_BANDWIDTH_
typedef enum {
    en5MHZ_BW=0,
    en50MHZ_BW,

} ENUM_BANDWIDTH ;
#endif


#endif


#ifdef _ELINT_

#define PDW_NORMAL          (1)
#define PDW_CW              (0)

#define PDW_DV				(1)

#elif defined(_POCKETSONATA_)

#define PDW_NORMAL          (0)
#define PDW_CW              (1)

#define PDW_DV				(1)

/**
 * @brief PDW 구조체 정의
 */
/*
 * struct _PDW
{
    //1
    unsigned int m_LSBTOA :32;

    //2
    unsigned int m_DOA :9;
    unsigned int x1 :3;
    unsigned int m_PA :9;
    unsigned int m_Ovp :1;
    unsigned int m_MSBTOA :10;

    //3
    unsigned int m_freq :21;
    unsigned int m_DI :1;
    unsigned int m_ChChg :2;
    unsigned int m_PMOP :1;
    unsigned int m_FMOP :1;
    unsigned int m_BLK :1;
    unsigned int m_sigType :1;
    unsigned int m_ChNo :4;

    //4
    unsigned int m_PW :22;
    unsigned int m_TOAinvalid :1;
    unsigned int m_PWinvalid :1;
    unsigned int m_ft8 :1;
    unsigned int m_ft7 :1;
    unsigned int m_ft6 :1;
    unsigned int m_ft5 :1;
    unsigned int m_ft4 :1;
    unsigned int m_ft3 :1;
    unsigned int m_ft2 :1;
    unsigned int m_ft1 :1;

    //5
    unsigned int m_PDWNum :32;

    //6
    unsigned int m_FMOPMaxFreq :13;
    unsigned int m_Rsvd3 :3;
    unsigned int m_FMOPMinFreq :13;
    unsigned int m_Rsvd2 :3;

    //7
    unsigned int m_PMOPMode :2;
    unsigned int m_Rsvd4 :2;
    unsigned int m_PMOPCount :8;
    unsigned int m_PMOPRsvdTime :20;

    //8
    unsigned int m_Ant_1st :2;
    unsigned int m_Rsvd5 :2;
    unsigned int m_Ant_2nd :2;
    unsigned int m_Rsvd6 :2;
    unsigned int m_PA_Diff :8;
    unsigned int m_Rsvd7 :16;

} ;
*/
#elif defined(_SONATA_)

#define PDW_NORMAL          (0)
#define PDW_CW              (1)

#define PDW_DV				(1)

#else

//PDW 상태 별 정의 값
#define PDW_NORMAL          (1)
#define PDW_CW              (2)
#define PDW_FMOP						(5)
#define PDW_CW_FMOP					(6)
#define PDW_SHORTP          (7)
#define PDW_ALL							(8)

#ifndef _WIN32
typedef union {
    unsigned int wpdw[4];
    unsigned char bpdw[ 4 ][ 4 ];

    struct pdw_phase {
        // Phase 1
        unsigned toa				 : 32; 	// [0 ~ 4,294,967,295] Res. 20ns (0 ~ 85,899,345.900 us)

        // Phase 2
        unsigned freq				 : 14; 	// [0 ~ 8,191] Res. 1.25 MHz
        unsigned fdiff			 : 3;		// 주파수 최대 변이값 (<- Reserved)
        unsigned blank_tag	 : 1;		// Blanking Tag
        unsigned pw					 : 14; 	// [0 ~ 16,383] Res. 20ns (0 ~ 327.660 us)

        // Phase 3
        unsigned amplitude	 : 8;  	// [0 ~ 255] Res. 0.3125 dBm (-74.6875 ~ + 5 dBm)
        unsigned filter_tag	 : 8;  	// 전처리필터 번호 (<- Reserved)
        unsigned aoa				 : 9;  	// [0 ~ 511] Res. 0.703125 도 (0 ~ 359.297 도)
        unsigned dv					 : 1;  	// [Valid | Invalid ]
        unsigned max_channel : 2;		// Ch1(0x0), Ch2(0x1), Ch3(0x2), Ch4(0x3)
        unsigned stat			   : 4;  	// PMOP(0x8), FMOP(0x4), CW(0x2), Pulse(0x1), Short Pulse(0xF)

        // Phase 4 for dummy
        unsigned flag        : 28;	// 수집 완료 플레그
        unsigned band        : 4;

    } item ;

} _PDW;

#else
typedef union {
    unsigned int word[4];
    unsigned char byte[ 4 ][ 4 ];

    struct pdw_phase {
        // Phase 1
        unsigned toa				 : 32; 	// [0 ~ 4,294,967,295] Res. 20ns (0 ~ 85,899,345.900 us)

        // Phase 2
        unsigned freq				 : 14; 	// [0 ~ 8,191] Res. 1.25 MHz
        unsigned fdiff			 : 3;		// 주파수 최대 변이값 (<- Reserved)
        unsigned blank_tag	 : 1;		// Blanking Tag
        unsigned pw					 : 14; 	// [0 ~ 16,383] Res. 20ns (0 ~ 327.660 us)

        // Phase 3
        unsigned amplitude	 : 8;  	// [0 ~ 255] Res. 0.3125 dBm (-74.6875 ~ + 5 dBm)
        unsigned filter_tag	 : 8;  	// 전처리필터 번호 (<- Reserved)
        unsigned aoa				 : 9;  	// [0 ~ 511] Res. 0.703125 도 (0 ~ 359.297 도)
        unsigned dv					 : 1;  	// [Valid | Invalid ]
        unsigned max_channel : 2;		// Ch1(0x0), Ch2(0x1), Ch3(0x2), Ch4(0x3)
        unsigned stat			   : 4;  	// PMOP(0x8), FMOP(0x4), CW(0x2), Pulse(0x1), Short Pulse(0xF)


        // Phase 4 for dummy
        unsigned flag        : 28;	// 수집 완료 플레그
        unsigned band        : 4;

    } item ;

} _PDW;
#endif


// PDW의 Phase 개수
#define PDW_WORD_LEN        4
#define PDW_WORD_CNT        4
#define SizeOfPDW           16
#define ByteOfPhase         4
#define SizeOfPSEUDO_PDW    ByteOfPhase

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

struct SRXPDWDataRGroup {
    unsigned long long int	llTOA;
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

} ;



#endif  // #ifndef _PDW_H_

