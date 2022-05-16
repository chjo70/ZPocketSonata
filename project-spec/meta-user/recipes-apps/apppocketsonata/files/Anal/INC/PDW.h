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


#ifdef _MAIN_GLOBALS_
// 장치 타입으로 이 값을 확인해서 장치에 맞게 실행하도록 한다.
#ifdef _MSC_VER
__declspec(dllexport) ENUM_UnitType g_enUnitType;
#else
ENUM_UnitType g_enUnitType;
#endif

#else

#ifndef _ENUNIT_TYPE
#define _ENUNIT_TYPE
#ifdef _MSC_VER
extern __declspec(dllexport) ENUM_UnitType g_enUnitType;
#else
extern ENUM_UnitType g_enUnitType;
#endif
#endif

#endif


#ifndef _TOA_
#ifdef __VXWORKS__
typedef unsigned long long int _TOA;
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

typedef union {
    char chData[32];
    union UZPOCKETPDW uPDW;

    /**
     * @brief     GetTOA
     * @return    _TOA
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-06, 10:54
     * @warning
     */
    _TOA GetTOA() {
        _TOA ullTOA;

        ullTOA = uPDW.x.uniPdw_freq_toa.stPdw_freq_toa.toa_L | ( (_TOA) uPDW.x.uniPdw_toa_edge.stPdw_toa_edge.toa_H << 16 );

        return ullTOA;
    }

    /**
     * @brief     GetChannel
     * @return    int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-06, 10:54
     * @warning
     */
    int GetChannel() {
        int iCh;

        iCh = uPDW.x.uniPdw_freq_toa.stPdw_freq_toa.pdw_phch;
        //iCh = ( 16 + ( iCh - 8 ) ) % 16;

        return iCh;
    }

    /**
     * @brief     GetFrequency
     * @param     int iCh
     * @return    unsigned int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-06, 10:54
     * @warning
     */
    unsigned int GetFrequency( int iCh ) {
        unsigned int uiFrequency, uiCh;

        uiCh = (16 + (iCh - 8)) % 16;

        uiFrequency = ( uPDW.x.uniPdw_pw_freq.stPdw_pw_freq.frequency_L ) | ( uPDW.x.uniPdw_freq_toa.stPdw_freq_toa.frequency_H << 8 );
        uiFrequency = ( 0x10000 + ( uiFrequency - 0x8000 ) ) % 0x10000;

        uiFrequency = uiFrequency + ( uiCh * 0x10000 );

        return uiFrequency;

    }

    /**
     * @brief     GetPulsewidth
     * @return    unsigned int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-06, 10:53
     * @warning
     */
    unsigned int GetPulsewidth() {
        unsigned int uiPulsewidth;

        uiPulsewidth = uPDW.x.uniPdw_pw_freq.stPdw_pw_freq.pulse_width;
        return uiPulsewidth;

    }

    /**
     * @brief     GetAOA
     * @return    unsigned int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-06, 10:54
     * @warning
     */
    unsigned int GetAOA() {
        unsigned int uiAOA;

        uiAOA = uPDW.x.uniPdw_dir_pa.stPdw_dir_pa.doa;
        return uiAOA;

    }

    /**
     * @brief     GetPulseamplitude
     * @return    unsigned int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-06, 10:54
     * @warning
     */
    unsigned int GetPulseamplitude() {
        unsigned int uiPA;

        uiPA = uPDW.x.uniPdw_dir_pa.stPdw_dir_pa.pa;
        return uiPA;

    }

    /**
     * @brief     GetPulsetype
     * @return    int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-06, 10:54
     * @warning
     */
    int GetPulsetype() {
        int iSignaltype = STAT_NORMAL;

        if( uPDW.x.uniPdw_status.stPdw_status.cw_pulse == 1 ) {
            iSignaltype = STAT_CW;
        }
        else {
            if( uPDW.x.uniPdw_status.stPdw_status.pmop_flag == 1 ) {
                iSignaltype = STAT_PMOP;
            }
            else if( uPDW.x.uniPdw_status.stPdw_status.fmop_flag == 1 ) {                    
                if( uPDW.x.uniPdw_status.stPdw_status.fmop_dir == 1 ) {
                    iSignaltype = STAT_CHIRPUP;
                }
                else {
                    iSignaltype = STAT_CHIRPDN;
                }
            }
            else {

            }

        }

        return iSignaltype;
    }

} DMAPDW ;

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

#if TOOL==diab 
#pragma pack( 1 )
#else
#pragma pack( push, 1 )
#endif


#ifndef _UNI_PDW_ETC
#define _UNI_PDW_ETC
typedef union {
    unsigned int uiCh[5];

    struct {
        float fPh1;
        float fPh2;
        float fPh3;
        float fPh4;
        float fPh5;
    } xb;

    struct {
        float fPh1;
        float fPh2;
        float fPh3;
        float fPh4;

        //////////////////////////////////////////////////////////////////////////
        //int _dummy;
    } el;

    struct {
        int iPMOP;
        int iFMOP;

        int iChannel;

        //////////////////////////////////////////////////////////////////////////
        //int _dummy[2];
    } ps;

} UNI_PDW_ETC ;

#endif

#ifndef _PDW_STRUCT
#define _PDW_STRUCT

struct _PDW {
    _TOA ullTOA;

    int iPulseType;

    unsigned int uiAOA;
	unsigned int uiFreq;
	unsigned int uiPA;
	unsigned int uiPW;

	int iPFTag;

    UNI_PDW_ETC x;    

    /**
     * @brief     _PDW 구조체에서 TOA 값을 리턴한다.
     * @return    _TOA
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-09, 17:12
     * @warning
     */
    _TOA GetTOA() {
        return ullTOA;
    }

    /**
     * @brief     해당 장치에 따라서 채널 정보를 얻는다.
     * @return    int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-09, 17:11
     * @warning
     */
    int GetChannel() {
        int iRet=-1;

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            iRet = x.ps.iChannel;
        }
        else {
        }

        return iRet;

    }

    /**
     * @brief     해당 장치에 따라서 채널 정보를 저장한다.
     * @param     int iCh
     * @return    void
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-09, 17:11
     * @warning
     */
    void SetChannel( int iCh ) {
        if( g_enUnitType == en_ZPOCKETSONATA ) {
            x.ps.iChannel = iCh;
        }
        else {
        }
    }

    /**
     * @brief     주파수 정보를 환산하여 계산한다.
     * @param     int iCh
     * @return    unsigned int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-09, 17:31
     * @warning
     */
    unsigned int GetFrequency( int iCh=-1 ) {
        unsigned int uiFrequency, uiCh;

        if( iCh == -1 ) {
            uiFrequency = uiFreq;
            //fFreq = FRQMhzCNV( g_enBoardId, uiFreq );
            //FDIV( (FMUL( gFreqRes[(A)].fRes, (B) ) + gFreqRes[(A)].iOffset), 1000 )  //CPOCKETSONATAPDW::DecodeFREQMHz( B )
        }
        else {
            uiCh = (16 + (iCh - 8)) % 16;

            uiFrequency = (0x10000 + (uiFreq - 0x8000)) % 0x10000;

            uiFrequency = uiFrequency + (uiCh * 0x10000);
        }

        return uiFrequency;
    }

    unsigned int GetPulsewidth() {
        return uiPW;
    }

    /**
     * @brief     방위 값을 리턴한다.
     * @return    unsigned int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-10, 15:19
     * @warning
     */
    unsigned int GetAOA() {
        return uiAOA;
    }

    /**
     * @brief     신호세기 값을 리턴한다.
     * @return    unsigned int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-10, 15:19
     * @warning
     */
    unsigned int GetPulseamplitude() {
        return uiPA;

    }

    int GetPulsetype() {
        return iPulseType;
    }


} ;
#endif

#if TOOL==diab 
#pragma pack( 4 )
#else
#pragma pack( pop )
#endif



namespace ELINT {
#ifndef _ELINT_ENUM_BANDWIDTH_
#define _ELINT_ENUM_BANDWIDTH_
    typedef enum {
        en5MHZ_BW = 0,
        en50MHZ_BW,

        enUnknown_BW = 2,

    } ENUM_BANDWIDTH;
#endif
}

namespace XBAND {
#ifndef _XBAND_ENUM_BANDWIDTH_
#define _XBAND_ENUM_BANDWIDTH_
    typedef enum {
        en5MHZ_BW = 0,
        en120MHZ_BW,

        enUnknown_BW = 2,

    } ENUM_BANDWIDTH;
#endif
}

// 장비별로 대역폭을 정의 한다.
#if defined(_ELINT_)


#elif defined(_XBAND_)


#elif defined(_POCKETSONATA_)
namespace POCKETSONATA {
#ifndef _ENUM_BANDWIDTH_
#define _ENUM_BANDWIDTH_
    typedef enum {
        en5MHZ_BW = 0,
        en50MHZ_BW,

        enUnknown_BW = 2,

    } ENUM_BANDWIDTH;
}

#endif
#else

#endif


// #elif defined(_SONATA_)
// 
// // 수퍼헷 수신장치 개발한 것의 PDW 포멧
// struct TNEW_SPDW
// {
//     float Freq ;
//     float PA ;
//     float PW ;
//     unsigned int TOA ;
//     int Ref_Phase3 ;
// 
// } ;
// 
// //#define LENGTH_OF_TASK_ID			(19+1)		//과제ID 문자열 길이 (TBD)
// 
// 
// #else
// 
// 

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
    UINT uiPDWID;

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
    char aucTaskID[LENGTH_OF_TASK_ID];
    unsigned int iIsStorePDW;
    EN_RADARCOLLECTORID enCollectorID;
    ELINT::ENUM_BANDWIDTH enBandWidth;

    // 아래는 공용 정보
    STR_COMMON_HEADER stCommon;

    EN_RADARCOLLECTORID GetCollectorID() {
        return enCollectorID;
    }

	void SetCollectorID( EN_RADARCOLLECTORID i_enCollectorID ) {
		enCollectorID = i_enCollectorID;
	}

    unsigned int GetTotalPDW() {
        return stCommon.uiTotalPDW;
    }

    unsigned int GetPDWID() {
        return stCommon.uiPDWID;
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

#ifndef _STR_XBAND_HEADER_
#define _STR_XBAND_HEADER_
typedef struct {
    char aucTaskID[LENGTH_OF_TASK_ID];
    unsigned int iIsStorePDW;
    EN_RADARCOLLECTORID enCollectorID;
    XBAND::ENUM_BANDWIDTH enBandWidth;

    // 아래는 공용 정보
    STR_COMMON_HEADER stCommon;

    EN_RADARCOLLECTORID GetCollectorID() {
        return enCollectorID;
    }

    void SetCollectorID(EN_RADARCOLLECTORID i_enCollectorID) {
        enCollectorID = i_enCollectorID;
    }

    unsigned int GetTotalPDW() {
        return stCommon.uiTotalPDW;
    }

    unsigned int GetPDWID() {
        return stCommon.uiPDWID;
    }

    void SetTotalPDW(unsigned int uiTotalPDW) {
        stCommon.uiTotalPDW = uiTotalPDW;
    }

    void SetIsStorePDW(unsigned int isStorePDW) {
        iIsStorePDW = isStorePDW;
    }

    void CheckColTime() {
        stCommon.CheckColTime();
    }

} STR_XBAND_HEADER;
#endif

#ifndef _POCKETSONATA_HEADER_
#define _POCKETSONATA_HEADER_
typedef struct {
    unsigned int uiBoardID;
    unsigned int uiBank;
    unsigned int uiBand;                // 주파수 대역
    unsigned int iIsStorePDW;

    // 아래는 공용 정보
    STR_COMMON_HEADER stCommon;

    unsigned int GetTotalPDW() {
        return stCommon.uiTotalPDW;
    }
    
    unsigned int GetPDWID() {
        return stCommon.uiPDWID;
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

} STR_POCKETSONATA_HEADER ;
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

    unsigned int GetPDWID() {
        return stCommon.uiPDWID;
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
    // 인천공항 ELINT 구조체
    STR_ELINT_HEADER el;

    // X대역탐지기 구조체
    STR_XBAND_HEADER xb;

    // 소형 전자전장비 구조체
    STR_POCKETSONATA_HEADER ps;

    // SONATA 전자전장비 구조체
    SONATA_HEADER so;

    /**
     * @brief     GetTaskID
     * @param     ENUM_UnitType enUnitType
     * @return    char *
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-04, 14:09
     * @warning
     */
    char *GetTaskID( ENUM_UnitType enUnitType ) {
        char *pTaskID;

        switch( enUnitType ) {
        case en_ZPOCKETSONATA :
            pTaskID = ( char *) NULL;
            break;

        case en_ELINT :
        case en_XBAND :
            pTaskID = & el.aucTaskID[0];
            break;

        case en_SONATA :
            pTaskID = ( char *) NULL;
            break;

        default:
            pTaskID = NULL;
            break;

        }
        return pTaskID;

    }

    /**
     * @brief     GetTotalPDW
     * @param     ENUM_UnitType enUnitType
     * @return    unsigned int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-04, 14:09
     * @warning
     */
    unsigned int GetTotalPDW( ENUM_UnitType enUnitType ) {
        unsigned int uiTotalPDW;

        switch( enUnitType ) {
        case en_ZPOCKETSONATA :
            uiTotalPDW = ps.stCommon.uiTotalPDW;
            break;

        case en_ELINT :
            uiTotalPDW = el.stCommon.uiTotalPDW;
            break;

        case en_XBAND :
            uiTotalPDW = xb.stCommon.uiTotalPDW;
            break;

        case en_SONATA :
            uiTotalPDW = so.stCommon.uiTotalPDW;
            break;

        default:
            uiTotalPDW = 0;
            break;

        }
        return uiTotalPDW;

    }

    /**
     * @brief     해당 장치에 따라서, PDW 개수를 설정한다.
     * @param     unsigned int uiTotalPDW
     * @return    void
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-10, 10:32
     * @warning
     */
    void SetTotalPDW( unsigned int uiTotalPDW ) {

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            ps.stCommon.uiTotalPDW = uiTotalPDW;
        }
        else if( g_enUnitType == en_ELINT ) {
            el.stCommon.uiTotalPDW = uiTotalPDW;
        }
        else if( g_enUnitType == en_XBAND ) {
            xb.stCommon.uiTotalPDW = uiTotalPDW;
        }
        else if( g_enUnitType == en_SONATA ) {
            so.stCommon.uiTotalPDW = uiTotalPDW;
        }
        else {

        }

        return;

    }

    /**
     * @brief     해당 장치에 따라서, PDW 저장여부를 설정한다.
     * @param     unsigned int isStorePDW
     * @return    void
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-10, 10:33
     * @warning
     */
    void SetIsStorePDW( unsigned int isStorePDW ) {

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            ps.SetIsStorePDW( isStorePDW );
        }
        else if( g_enUnitType == en_ELINT ) {
            el.SetIsStorePDW( isStorePDW );
        }
        else if( g_enUnitType == en_XBAND ) {
            xb.SetIsStorePDW( isStorePDW );
        }
        else if( g_enUnitType == en_SONATA ) {
           so.SetIsStorePDW( isStorePDW );
        }
        else {
        }

        return;

    }

    /**
     * @brief     GetBoardID
     * @param     ENUM_UnitType enUnitType
     * @return    int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-04, 14:09
     * @warning
     */
    int GetBoardID( ENUM_UnitType enUnitType ) {
        int uiBoardID;

        switch( enUnitType ) {
        case en_ZPOCKETSONATA :
            uiBoardID = ps.uiBoardID;
            break;

        case en_ELINT :
        case en_XBAND :
            uiBoardID = -1;
            break;

        case en_SONATA :
            uiBoardID = -1;
            break;

        default:
            uiBoardID = -1;
            break;

        }
        return uiBoardID;
    }

    /**
     * @brief     해당 장치에 따라서, 보드ID를 저장한다.
     * @param     unsigned int uiBoardID
     * @return    void
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-10, 10:23
     * @warning
     */
    void SetBoardID( ENUM_UnitType enUnitType, unsigned int uiBoardID ) {

        switch( enUnitType ) {
        case en_ZPOCKETSONATA:
            ps.uiBoardID = uiBoardID;
            break;

        case en_ELINT:
        case en_XBAND:
        case en_SONATA:
            break;

        default:
            break;

        }
        return;
    }

    /**
     * @brief     SetColTime
     * @param     __time32_t tColTime
     * @param     UINT uiColTimeMs
     * @return    void
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-10, 10:30
     * @warning
     */
    void SetColTime( __time32_t tColTime, UINT uiColTimeMs ) {

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            ps.stCommon.tColTime = tColTime;
            ps.stCommon.uiColTimeMs = uiColTimeMs;
        }
        else if( g_enUnitType == en_ELINT ) {
            el.stCommon.tColTime = tColTime;
            el.stCommon.uiColTimeMs = uiColTimeMs;
        }
        else if( g_enUnitType == en_XBAND ) {
            xb.stCommon.tColTime = tColTime;
            xb.stCommon.uiColTimeMs = uiColTimeMs;
        }
        else if( g_enUnitType == en_SONATA ) {
            so.stCommon.tColTime = tColTime;
            so.stCommon.uiColTimeMs = uiColTimeMs;
        }
        else {

        }
        return;

    }

    /**
     * @brief     SetBoardID
     * @param     unsigned int uiBoardID
     * @return    void
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-10, 15:00
     * @warning
     */
    void SetBoardID( unsigned int uiBoardID ) {

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            ps.uiBoardID = uiBoardID;
        }
        else {
            // x.so.stCommon.uiPDWID;
        }

        return;

    }

    /**
     * @brief     SetBand
     * @param     unsigned int uiBand
     * @return    void
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-10, 15:01
     * @warning
     */
    void SetBand( unsigned int uiBand ) {

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            ps.uiBand = uiBand;
        }
        else {
            //x.so.uiBand
        }

        return;

    }
    
    /**
     * @brief     SetCollectorID
     * @param     ENUM_UnitType enUnitType
     * @param     EN_RADARCOLLECTORID enCollectorID
     * @return    void
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-20, 17:03
     * @warning
     */
    void SetCollectorID( EN_RADARCOLLECTORID enCollectorID ) {

        if( g_enUnitType == en_ELINT ) {
            el.enCollectorID = enCollectorID;
        }
        else if( g_enUnitType == en_XBAND ) {
            xb.enCollectorID = enCollectorID;
        }
        else {
        }
    }

    /**
     * @brief     GetBandWidth
     * @return    int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-10, 13:17
     * @warning
     */
    int GetBandWidth()
    {
        int iBandwidth;

        if( g_enUnitType == en_ELINT ) {
            iBandwidth = (int) el.enBandWidth;
        }
        else if( g_enUnitType == en_XBAND ) {
            iBandwidth = ( int ) xb.enBandWidth;
        }
        else {
            iBandwidth = 0;
        }

        return iBandwidth;
    }

    /**
     * @brief     SetBandWidth
     * @param     int iBandWidth
     * @return    void
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-10, 13:17
     * @warning
     */
    void SetBandWidth( int iBandWidth)
    {
        if( g_enUnitType == en_ZPOCKETSONATA ) {
        }
        else if( g_enUnitType == en_ELINT ) {
            el.enBandWidth = (ELINT::ENUM_BANDWIDTH) iBandWidth;
        }
        else if( g_enUnitType == en_XBAND ) {
            xb.enBandWidth = (XBAND::ENUM_BANDWIDTH) iBandWidth;
        }
        else {
        }

        return;
    }

} UNION_HEADER;
#endif


#ifndef _STR_PDWDATA
#define _STR_PDWDATA
struct STR_PDWDATA {
    UNION_HEADER x;

    _PDW *pstPDW;

    /**
     * @brief     GetHeader
     * @return    unsigned int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-03-03, 13:48
     * @warning
     */
    unsigned int GetHeader() {
        unsigned int uiHeader;

        if( g_enUnitType == en_ZPOCKETSONATA ) {
			uiHeader = sizeof( STR_POCKETSONATA_HEADER );
        }
        else if( g_enUnitType == en_ELINT ) {
			uiHeader = sizeof( STR_ELINT_HEADER );
        }
        else if( g_enUnitType == en_XBAND ) {
            uiHeader = sizeof( STR_XBAND_HEADER );
        }
        else {
			uiHeader = sizeof( SONATA_HEADER );
        }

        return uiHeader;

    }

    /**
     * @brief     해당 장치에 따라서, PDW 데이터 저장 여부를 저장한다.
     * @param     unsigned int isStorePDW
     * @return    void
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-10, 10:19
     * @warning
     */
    void SetIsStorePDW( unsigned int isStorePDW ) {

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            x.ps.SetIsStorePDW( isStorePDW );
        }
        else if( g_enUnitType == en_ELINT ) {
            x.el.SetIsStorePDW( isStorePDW );
        }
        else if( g_enUnitType == en_XBAND ) {
            x.xb.SetIsStorePDW( isStorePDW );
        }
        else {
            // x.el.SetIsStorePDW( isStorePDW );
        }

        return;

    }

    /**
     * @brief     해당 장치에 따라서, 보드ID를 저장한다.
     * @param     unsigned int uiBoardID
     * @return    void
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-20, 15:35
     * @warning
     */
    void SetBoardID( unsigned int uiBoardID ) {

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            x.ps.uiBoardID = uiBoardID;
        }
        else if( g_enUnitType == en_ELINT || g_enUnitType == en_XBAND ) {
            // x.el.uiBoardID = uiBoardID;
        }
        else {
            // x.so.stCommon.uiPDWID;
        }

        return;

    }

    /**
     * @brief     SetBank
     * @param     unsigned int uiBank
     * @return    void
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-04, 14:09
     * @warning
     */
    void SetBank(unsigned int uiBank) {

        if (g_enUnitType == en_ZPOCKETSONATA) {
            x.ps.uiBank = uiBank;
        }
        else if (g_enUnitType == en_ELINT || g_enUnitType == en_XBAND) {
           
        }
        else {
            
        }

        return;

    }

    /**
     * @brief     SetBand
     * @param     unsigned int uiBand
     * @return    void
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-20, 15:35
     * @warning
     */
    void SetBand( unsigned int uiBand ) {

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            x.ps.uiBand = uiBand;
        }
        else if( g_enUnitType == en_ELINT || g_enUnitType == en_XBAND ) {
            //x.el.uiBand = uiBoardID;
        }
        else {
            //x.so.uiBand
        }

        return;

    }

    /**
     * @brief     GetBand
     * @return    unsigned int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-27, 14:46
     * @warning
     */
    unsigned int GetBand() {
        unsigned int uiBand=0;

        if (g_enUnitType == en_ZPOCKETSONATA) {
            uiBand = x.ps.uiBand;
        }
        else if (g_enUnitType == en_ELINT) {
            //uiBand = x.el.uiBand;
        }
        else if ( g_enUnitType == en_XBAND) {
            //uiBand = x.xb.uiBand;
        }
        else {
            uiBand = 0;
        }

        return uiBand;

    }

    /**
     * @brief     GetPDWID
     * @return    unsigned int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-03-08, 20:15
     * @warning
     */
    unsigned int GetPDWID() {
        unsigned int uiPDWID;

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            uiPDWID = x.ps.stCommon.uiPDWID;
        }
        else if( g_enUnitType == en_ELINT ) {
            uiPDWID = x.el.stCommon.uiPDWID;
        }
        else if( g_enUnitType == en_XBAND ) {
            uiPDWID = x.xb.stCommon.uiPDWID;
        }
        else {
            uiPDWID = x.so.stCommon.uiPDWID;
        }

        return uiPDWID;

    }

    /**
     * @brief     SetPDWID
     * @param     unsigned int uiPDWID
     * @return    unsigned int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-03-08, 20:15
     * @warning
     */
    void SetPDWID( unsigned int uiPDWID ) {

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            x.ps.stCommon.uiPDWID = uiPDWID;
        }
        else if( g_enUnitType == en_ELINT ) {
            x.el.stCommon.uiPDWID = uiPDWID;
        }
        else if( g_enUnitType == en_XBAND ) {
            x.xb.stCommon.uiPDWID = uiPDWID;
        }
        else {
            x.so.stCommon.uiPDWID = uiPDWID;
        }

    }

    /**
     * @brief     IncPDWID
     * @return    void
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-20, 15:35
     * @warning
     */
    void IncPDWID() {
        if( g_enUnitType == en_ZPOCKETSONATA ) {
            ++ x.ps.stCommon.uiPDWID;
        }
        else if( g_enUnitType == en_ELINT ) {
            ++ x.el.stCommon.uiPDWID;
        }
        else if( g_enUnitType == en_XBAND ) {
            ++ x.xb.stCommon.uiPDWID;
        }
        else {
            ++ x.so.stCommon.uiPDWID;
        }
    }

    /**
     * @brief     GetCollectorID
     * @return    void
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-20, 15:40
     * @warning
     */
    EN_RADARCOLLECTORID GetCollectorID() {
        EN_RADARCOLLECTORID enCollectorID;

        if (g_enUnitType == en_ZPOCKETSONATA) {
            enCollectorID = RADARCOL_Unknown;
        }
        else if (g_enUnitType == en_ELINT) {
            enCollectorID = x.el.enCollectorID;
        }
        else if (g_enUnitType == en_XBAND) {
            enCollectorID = x.xb.enCollectorID;
        }
        else {
            enCollectorID = RADARCOL_Unknown;
        }

        return enCollectorID;
    }

    /**
     * @brief     GetTotalPDW
     * @return    unsigned int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-03-03, 13:48
     * @warning
     */
    unsigned int GetTotalPDW() {
        unsigned int uiTotalPDW;

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            uiTotalPDW = x.ps.stCommon.uiTotalPDW;
        }
        else if( g_enUnitType == en_ELINT ) {
            uiTotalPDW = x.el.stCommon.uiTotalPDW;
        }
        else if( g_enUnitType == en_XBAND ) {
            uiTotalPDW = x.xb.stCommon.uiTotalPDW;
        }
        else {
            uiTotalPDW = x.so.stCommon.uiTotalPDW;
        }

        return uiTotalPDW;

    }

    /**
     * @brief     SetTotalPDW
     * @param     unsigned int uiTotalPDW
     * @return    void
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-03-03, 13:48
     * @warning
     */
    void SetTotalPDW( unsigned int uiTotalPDW ) {
        if( g_enUnitType == en_ZPOCKETSONATA ) {
            x.ps.stCommon.uiTotalPDW = uiTotalPDW;
        }
        else if( g_enUnitType == en_ELINT ) {
            x.el.stCommon.uiTotalPDW = uiTotalPDW;
        }
        else if ( g_enUnitType == en_XBAND) {
            x.xb.stCommon.uiTotalPDW = uiTotalPDW;
        }
        else {
            x.so.stCommon.uiTotalPDW = uiTotalPDW;
        }

        return;

    }

    /**
     * @brief     SetColTime
     * @param     __time32_t tColTime
     * @param     UINT uiColTimeMs
     * @return    void
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-03-03, 13:48
     * @warning
     */
    void SetColTime( __time32_t tColTime, UINT uiColTimeMs ) {

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            x.ps.stCommon.tColTime = tColTime;
            x.ps.stCommon.uiColTimeMs = uiColTimeMs;
        }
        else if( g_enUnitType == en_ELINT ) {
            x.el.stCommon.tColTime = tColTime;
            x.el.stCommon.uiColTimeMs = uiColTimeMs;
        }
        else if ( g_enUnitType == en_XBAND) {
            x.xb.stCommon.tColTime = tColTime;
            x.xb.stCommon.uiColTimeMs = uiColTimeMs;
        }
        else {
            x.so.stCommon.tColTime = tColTime;
            x.so.stCommon.uiColTimeMs = uiColTimeMs;
        }
        return;

    }

    /**
     * @brief     GetColTime
     * @return    __time32_t
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-03-03, 13:48
     * @warning
     */
    __time32_t GetColTime() {
        __time32_t retTime;

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            retTime = x.ps.stCommon.tColTime;
        }
        else if( g_enUnitType == en_ELINT ) {
            retTime = x.el.stCommon.tColTime;
        }
        else if (g_enUnitType == en_XBAND) {
            retTime = x.xb.stCommon.tColTime;
        }
        else {
            retTime = x.so.stCommon.tColTime;
        }

        return retTime;

    }

    /**
     * @brief     GetStorePDW
     * @return    int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-03-03, 13:48
     * @warning
     */
    int GetStorePDW() {
        int iStorePDW;

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            iStorePDW = x.ps.iIsStorePDW;
        }
        else if( g_enUnitType == en_ELINT ) {
            iStorePDW = x.el.iIsStorePDW;
        }
        else if (g_enUnitType == en_XBAND) {
            iStorePDW = x.xb.iIsStorePDW;
        }
        else {
            iStorePDW = x.so.iIsStorePDW;
        }

        return iStorePDW;

    }

    /**
     * @brief     GetBandWidth
     * @return    ENUM_BANDWIDTH
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-03-03, 13:48
     * @warning
     */
    int GetBandWidth()
    {
        int iBandwidth;

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            iBandwidth = 0;
        }
        else if( g_enUnitType == en_ELINT ) {
            iBandwidth = x.el.enBandWidth;
        }
        else if( g_enUnitType == en_XBAND ) {
            iBandwidth = x.xb.enBandWidth;
        }
        else {
            iBandwidth = 0;
        }

        return iBandwidth;
    }

    /**
     * @brief     GetTaskID
     * @return    char *
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-20, 15:38
     * @warning
     */
    char * GetTaskID() {
        char *pTaskID;

        if (g_enUnitType == en_ZPOCKETSONATA) {
            pTaskID = NULL;
        }
        else if (g_enUnitType == en_ELINT ) {
            pTaskID = x.el.aucTaskID;
        }
        else if (g_enUnitType == en_XBAND) {
            pTaskID = x.xb.aucTaskID;
        }
        else {
            pTaskID = NULL;
        }

        return pTaskID;
    }

    /**
     * @brief     TOA 값이 동일할때는 음의 값을 리턴한다.
     * @param     _TOA tPDW
     * @return    int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-04, 14:42
     * @warning
     */
    int GetIndexByTOA( _TOA tPDW ) {
        _TOA tDiff;
        int iTotalPDW;

        int iIndex=0, iLeft=0, iRight;        

        iTotalPDW = ( int ) GetTotalPDW();
        iRight = iTotalPDW - 1;

        if( iRight >= 0 ) {
            do {
                iIndex = (iLeft + iRight) / 2;

                tDiff = pstPDW[iIndex].ullTOA - tPDW;
                if( tDiff == 0 ) {
                    iLeft = -iIndex - 1;
                    break;
                }
                else if( tDiff < LLONG_MAX ) {
                    iRight = iIndex - 1;
                }
                else {
                    iLeft = iIndex + 1;
                }
                iIndex = (iLeft + iRight) / 2;
            } while( iLeft <= iRight && iRight < iTotalPDW );

            iIndex = iLeft;
        }

        return iIndex;
    }

}  ;


#ifndef _STR_STATIC_PDWDATA
#define _STR_STATIC_PDWDATA
typedef struct {
    UNION_HEADER x;

    _PDW stPDW[MAX_PDW];

    unsigned int GetBand() {
        unsigned int uiBand;

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            uiBand = x.ps.uiBand;
        }
        else {
            uiBand = 0;
        }

        return uiBand;

    }

    /**
     * @brief     GetTotalPDW
     * @return    unsigned int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-03-03, 13:48
     * @warning
     */
    unsigned int GetTotalPDW() {
        unsigned int uiTotalPDW;

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            uiTotalPDW = x.ps.stCommon.uiTotalPDW;
        }
        else if( g_enUnitType == en_ELINT || g_enUnitType == en_XBAND ) {
            uiTotalPDW = x.el.stCommon.uiTotalPDW;
        }
        else {
            uiTotalPDW = x.so.stCommon.uiTotalPDW;
        }

        return uiTotalPDW;

    }

    /**
     * @brief     GetPDWID
     * @return    unsigned int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-03-15, 10:18
     * @warning
     */
    unsigned int GetPDWID() {
        unsigned int uiPDWID;

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            uiPDWID = x.ps.stCommon.uiPDWID;
        }
        else if( g_enUnitType == en_ELINT || g_enUnitType == en_XBAND ) {
            uiPDWID = x.el.stCommon.uiPDWID;
        }
        else {
            uiPDWID = x.so.stCommon.uiPDWID;
        }

        return uiPDWID;
    }

    void SetPDWID( unsigned int uiPDWID ) {

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            x.ps.stCommon.uiPDWID = uiPDWID;
        }
        else if( g_enUnitType == en_ELINT || g_enUnitType == en_XBAND ) {
            x.el.stCommon.uiPDWID = uiPDWID;
        }
        else {
            x.so.stCommon.uiPDWID = uiPDWID;
        }

        return;
    }

    /**
     * @brief     GetColTime
     * @return    __time32_t
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-03-03, 13:48
     * @warning
     */
    __time32_t GetColTime() {
        __time32_t retTime;

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            retTime = x.ps.stCommon.tColTime;
        }
        else if( g_enUnitType == en_ELINT || g_enUnitType == en_XBAND ) {
            retTime = x.el.stCommon.tColTime;
        }
        else {
            retTime = x.so.stCommon.tColTime;
        }

        return retTime;

    }


}  STR_STATIC_PDWDATA ;

#endif  // _STR_STATIC_PDWDATA

#endif


#ifdef _POCKETSONATA_
// 하드웨어 PDW 맵에 저장한다.
typedef DMAPDW SIGAPDW;
//typedef STR_PDWDATA SIGAPDW;

#elif defined(_ELINT_) || defined(_XBAND_)
// 
typedef _PDW SIGAPDW;
//typedef STR_PDWDATA SIGAPDW;

#elif defined(_SONATA_)
typedef STR_PDWDATA SIGAPDW;

#endif


#endif  // #ifndef _PDW_H_

