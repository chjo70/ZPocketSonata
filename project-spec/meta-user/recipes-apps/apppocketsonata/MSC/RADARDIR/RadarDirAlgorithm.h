#pragma once

#ifdef _MSC_VER
#ifdef MATHFUNCSDLL_EXPORTS
#define MATHFUNCSDLL_API __declspec(dllexport)

#else
#define MATHFUNCSDLL_API __declspec(dllimport)
#endif

#else
#define HWND				unsigned int
#define MATHFUNCSDLL_API

#endif


#include "Anal/NewSigAnal/NewSigAnal.h"
#include "Anal/ScanSigAnal/ScanSigAnal.h"
#include "Anal/SigAnal/_CED_Define.h"
#include "Anal/SigAnal/_Define.h"
#include "Anal/SigAnal/SysPara.h"

#define WM_USER_LOGMSG				(7011)


#ifdef _USRDLL

#include "Anal/SigAnal/_CED_Define.h"
#include "Anal/SigAnal/_Define.h"
#include "Anal/SigAnal/SysPara.h"

#else

//#include "./_CED_Define.h"

#ifndef ENUM_BOARDID
#define ENUM_BOARDID
enum ENUM_BoardID {
    enPRC_Unknown = 0,

    enPRC1 = 1,
    enPRC2,
    enPRC3,
    enPRC4,
    enPRC5,
    enMAXPRC,

    enMaster = enPRC3

};
#endif

// 수집 뱅크 종류 정의
#ifndef _ENUM_COLLECTBANK
#define _ENUM_COLLECTBANK
enum ENUM_COLLECTBANK : unsigned int {
    enUnknownCollectBank = 0,

    enDetectCollectBank = 1,
    enTrackCollectBank,
    enScanCollectBank,
    enUserCollectBank,

};
#endif

#endif


//
// RADARDIR 프로젝트 내에서 최소 내용만 구조체 정의를 복사한 것임.


#define LENGTH_OF_TASK_ID			(19+1)		//과제ID 문자열 길이 (TBD)



#ifndef _ENUM_DataType
#define _ENUM_DataType
typedef enum {
    en_UnknownData = 0,

    en_PDW_DATA,
	en_PDW_DATA_CSV,
    en_IQ_DATA,
    en_IF_DATA,

} ENUM_DataType;
#endif

#ifndef _ENUM_UnitType
#define _ENUM_UnitType
typedef enum {
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

} ENUM_UnitType;
#endif


#ifndef _MAIN_GLOBALS_
#ifndef _ENUNIT_TYPE
#define _ENUNIT_TYPE
extern __declspec(dllimport) ENUM_UnitType g_enUnitType;
#endif
#endif

#pragma pack( push, 1 )

#ifndef _STR_STAT_BITMAP
#define _STR_STAT_BITMAP
struct STR_STAT_BITMAP {
    unsigned int CwPulse : 1;
    unsigned int Pmop : 1;
    unsigned int Fmop : 1;
    unsigned int FalsePdw : 1;
    unsigned int FmopDir : 2;
};
#endif

#ifndef _UNI_PDW_ETC
#define _UNI_PDW_ETC
union UNI_PDW_ETC {
    unsigned int uiCh[5];

#if defined(_GRAPH_) || defined(_XBAND_)
    struct {
        float fPh1;
        float fPh2;
        float fPh3;
        float fPh4;
        float fPh5;
    } xb;
#endif

#if defined(_GRAPH_) || defined(_ELINT_)
    struct {
        float fPh1;
        float fPh2;
        float fPh3;
        float fPh4;

    } el;
#endif

#if defined(_GRAPH_) || ( defined(_POCKETSONATA_) || defined(_712_) )
    struct {
        int iChannel;

        union UNI_STAT {
            // unsigned int uixWord;

            STR_STAT_BITMAP stStrBitMap;

        } x;

    } ps;
#endif

#if defined(_GRAPH_) || defined(_701_)
    struct {
        int iChannel;
        int iDirectionValid;

    } _701;
#endif
};

#endif

#ifndef _PDW_STRUCT
#define _PDW_STRUCT
struct _PDW {
    int iStat;

    unsigned int uiAOA;
    unsigned int uiFreq;
    unsigned int uiPA;
    unsigned int uiPW;

    unsigned int uiIndex;

    UNI_PDW_ETC x;

    unsigned long long int ullTOA;

#if defined( _POCKETSONATA_ ) || defined( _712_ )
    int iChannel;
#endif

    unsigned long long int GetTOA() {
        return ullTOA;
    }

    int GetChannel() {
#if defined(_POCKETSONATA_) || defined(_712_)
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
        return iStat;
    }

} ;
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

namespace _701 {
#ifndef _701_ENUM_BANDWIDTH_
#define _701_ENUM_BANDWIDTH_
	typedef enum {
		enNARROW_BW = 0,
		enWIDE_BW,

		enUnknown_BW = 2,

	} ENUM_BANDWIDTH;
#endif
}

#ifndef _STR_COMMON_HEADER_
#define _STR_COMMON_HEADER_
// 아래는 공용 정보
struct STR_COMMON_HEADER {
	UINT uiTotalPDW;
    unsigned int uiColTime;
	UINT uiColTimeMs;
	UINT uiPDWID;

	void CheckColTime() {
		if( uiColTime < 0 ) {
			uiColTime = 0;
		}

		if( uiColTimeMs > 1000 ) {
			uiColTimeMs = 0;
		}
	}

}  ;
#endif

#ifndef _EN_RADARCOLLECTORID_
#define _EN_RADARCOLLECTORID_
enum EN_RADARCOLLECTORID { RADARCOL_Unknown=0, RADARCOL_1=1, RADARCOL_2, RADARCOL_3, RADARCOL_MAX };

#endif

#ifndef _STR_ELINT_HEADER_
#define _STR_ELINT_HEADER_
struct STR_ELINT_HEADER {
	char aucTaskID[LENGTH_OF_TASK_ID];
	unsigned int uiIsStorePDW;
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
		uiIsStorePDW = isStorePDW;
	}

	void CheckColTime() {
		stCommon.CheckColTime();
	}

}  ;
#endif

#ifndef _STR_701_HEADER_
#define _STR_701_HEADER_
struct STR_701_HEADER {
	char aucTaskID[LENGTH_OF_TASK_ID];
	unsigned int uiIsStorePDW;
	EN_RADARCOLLECTORID enCollectorID;
	_701::ENUM_BANDWIDTH enBandWidth;

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
		uiIsStorePDW = isStorePDW;
	}

	void CheckColTime() {
		stCommon.CheckColTime();
	}

} ;

#endif

#ifndef _STR_XBAND_HEADER_
#define _STR_XBAND_HEADER_
struct STR_XBAND_HEADER {
    char aucTaskID[LENGTH_OF_TASK_ID];
    unsigned int uiIsStorePDW;
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
        uiIsStorePDW = isStorePDW;
    }

    void CheckColTime() {
        stCommon.CheckColTime();
    }

} ;
#endif

#ifndef _POCKETSONATA_HEADER_
#define _POCKETSONATA_HEADER_
struct STR_POCKETSONATA_HEADER {
	unsigned int uiBoardID;
    ENUM_COLLECTBANK enCollectBank;
	unsigned int uiBand;                // 주파수 대역
	unsigned int uiIsStorePDW;

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
		uiIsStorePDW = isStorePDW;
	}

	void CheckColTime() {
		stCommon.CheckColTime();

	}

}  ;
#endif


#ifndef _SONATA_HEADER_
#define _SONATA_HEADER_
struct STR_SONATA_HEADER {
	unsigned int uiBand;
	unsigned int uiIsStorePDW;

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
		uiIsStorePDW = isStorePDW;
	}

}  ;
#endif

#ifndef _UNION_HEADER_
#define _UNION_HEADER_
union UNION_HEADER {
#if defined(_GRAPH_) || defined(_ELINT_)
    // 인천공항 ELINT 구조체
    STR_ELINT_HEADER el;
#endif

#if defined(_GRAPH_) || defined(_XBAND_)
    // X대역탐지기 구조체
    STR_XBAND_HEADER xb;
#endif

#if defined(_GRAPH_) || ( defined(_POCKETSONATA_) || defined(_712_) )
    // 소형 전자전장비 구조체
    STR_POCKETSONATA_HEADER ps;
#endif

#if defined(_GRAPH_) || defined(_SONATA_)
    // SONATA 전자전장비 구조체
    STR_SONATA_HEADER so;
#endif

#if defined(_GRAPH_) || defined(_701_)
    // 701-ELINT 전자전장비 구조체
    STR_701_HEADER e7;
#endif

	char *GetTaskID( ENUM_UnitType enUnitType ) {
		char *pTaskID;

		switch( enUnitType ) {
		case en_ZPOCKETSONATA :
			pTaskID = ( char *) NULL;
			break;

#if defined(_GRAPH_) || defined(_ELINT_)
		case en_ELINT :
			pTaskID = & el.aucTaskID[0];
			break;
#endif
#if defined(_GRAPH_) || defined(_XBAND_)
        case en_XBAND:
            pTaskID = &xb.aucTaskID[0];
            break;
#endif

		case en_SONATA :
			pTaskID = ( char *) NULL;
			break;

		default:
			pTaskID = NULL;
			break;

		}
		return pTaskID;

	}

	unsigned int GetTotalPDW( ENUM_UnitType enUnitType ) {
		unsigned int uiTotalPDW;

		switch( enUnitType ) {
		case en_ZPOCKETSONATA :
			uiTotalPDW = ps.stCommon.uiTotalPDW;
			break;

#if defined(_GRAPH_) || defined(_ELINT_)
		case en_ELINT :
			uiTotalPDW = el.stCommon.uiTotalPDW;
			break;
#endif

#if defined(_GRAPH_) || defined(_XBAND_)
        case en_XBAND:
            uiTotalPDW = xb.stCommon.uiTotalPDW;
            break;
#endif

#if defined(_GRAPH_) || defined(_701_)
        case en_701:
            uiTotalPDW = e7.stCommon.uiTotalPDW;
            break;
#endif

#if defined(_GRAPH_) || defined(_SONATA_)
		case en_SONATA :
            uiTotalPDW = (UINT)-1;	// SONATA용 헤더는 없기 때문에 (-1)로 리턴함.
			break;
#endif

		default:
			uiTotalPDW = 0;
			break;

		}
		return uiTotalPDW;

	}

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

} ;
#endif

#ifndef _STR_PDWDATA
#define _STR_PDWDATA
struct STR_PDWDATA {
    UNION_HEADER x;

    _PDW *pstPDW;

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

#if defined( _POCKETSONATA_ ) || defined( _712_ )
        uiTotalPDW = x.ps.stCommon.uiTotalPDW;

#elif defined(_ELINT_)
        uiTotalPDW = x.el.stCommon.uiTotalPDW;

#elif defined(_XBAND_)
        uiTotalPDW = x.xb.stCommon.uiTotalPDW;

#elif defined(_SONATA_)
        uiTotalPDW = x.so.stCommon.uiTotalPDW;

#else

#endif

        return uiTotalPDW;

    }

	void SetTotalPDW( unsigned int uiTotalPDW ) {
#if defined(_POCKETSONATA_) || defined(_712_)
		x.ps.stCommon.uiTotalPDW = uiTotalPDW;

#elif defined(_ELINT_)
		x.el.stCommon.uiTotalPDW = uiTotalPDW;

#elif defined(_XBAND_)
        x.xb.stCommon.uiTotalPDW = uiTotalPDW;

#elif defined(_SONATA_)
		x.so.stCommon.uiTotalPDW = uiTotalPDW;

#else

#endif

		return;

	}

    /**
     * @brief     SetColTime
     * @param     time_t tColTime
     * @param     UINT uiColTimeMs
     * @return    void
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-03-03, 13:48
     * @warning
     */
    void SetColTime( unsigned int uiColTime, UINT uiColTimeMs ) {

#if defined(_POCKETSONATA_) || defined(_712_)
		x.ps.stCommon.uiColTime = uiColTime;
		x.ps.stCommon.uiColTimeMs = uiColTimeMs;

#elif defined(_ELINT_)
		x.el.stCommon.uiColTime = uiColTime;
		x.el.stCommon.uiColTimeMs = uiColTimeMs;

#elif defined(_XBAND_)
        x.xb.stCommon.uiColTime = uiColTime;
        x.xb.stCommon.uiColTimeMs = uiColTimeMs;

#elif defined(_SONATA_)
		x.so.stCommon.uiColTime = uiColTime;
		x.so.stCommon.uiColTimeMs = uiColTimeMs;
#endif

        return;

    }

    /**
     * @brief     GetColTime
     * @return    time_t
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-03-03, 13:48
     * @warning
     */
	time_t GetColTime() {
		time_t retTime;

#if defined( _POCKETSONATA_ ) || defined( _712_ )
		retTime = x.ps.stCommon.uiColTime;

#elif defined(_ELINT_)
        retTime = x.el.stCommon.uiColTime;

#elif defined(_XBAND_)
        retTime = x.xb.stCommon.uiColTime;

#elif defined(_SONATA_)
        retTime = x.so.stCommon.uiColTime;

#endif

        return retTime;

    }


}  ;
#endif

#ifndef _ENUM_MOP_TYPE
#define _ENUM_MOP_TYPE
enum ENUM_MOP_TYPE : unsigned char {
    E_MOP_UNKNOWN = 0,
    E_MOP_FMOP,
    E_MOP_PMOP,
};

#endif

#ifndef MAX_FREQ_PRI_STEP
#define MAX_FREQ_PRI_STEP				(32)
#endif

//////////////////////////////////////////////////////////////////////////
//
#if defined(_POCKETSONATA_) || defined(_712_)

// 주파수 형태 정의
#ifndef _ENUM_AET_FRQ_TYPE
#define _ENUM_AET_FRQ_TYPE
enum class ENUM_AET_FRQ_TYPE : unsigned char {
    E_AET_FRQ_FIXED = 0,
    E_AET_FRQ_HOPPING,
    E_AET_FRQ_AGILE,
    E_AET_FRQ_PATTERN,

    E_AET_FRQ_UNKNOWN,
    E_AET_FRQ_IGNORE,

    E_AET_MAX_FRQ_TYPE
};
#endif

// PRI 형태 정의
#ifndef _ENUM_AET_PRI_TYPE
#define _ENUM_AET_PRI_TYPE
enum class ENUM_AET_PRI_TYPE : unsigned char {
    E_AET_PRI_FIXED = 0,
    E_AET_PRI_JITTER,
    E_AET_PRI_DWELL_SWITCH,
    E_AET_PRI_STAGGER,
    E_AET_PRI_PATTERN,

    E_AET_PRI_UNKNOWN,

    E_AET_MAX_PRI_TYPE,

    //E_AET_PRI_BEACON, // 2015.4.12. 추가. 현재 ICD에 반영되어 있지 않음.
};
#endif

#ifndef _ENUM_AET_FREQ_PRI_PATTERN_TYPE
#define _ENUM_AET_FREQ_PRI_PATTERN_TYPE
enum class ENUM_AET_FREQ_PRI_PATTERN_TYPE : unsigned char {
    E_AET_FREQ_PRI_UNKNOWN = 0,
    E_AET_FREQ_PRI_SINE,
    E_AET_FREQ_PRI_SLIDE_INC,
    E_AET_FREQ_PRI_SLIDE_DEC,
    E_AET_FREQ_PRI_SAW_TRI,

    E_AET_MAX_FREQ_PRI_PATTERN_TYPE,

};
#endif

#else
#ifndef _ENUM_AET_FRQ_TYPE
#define _ENUM_AET_FRQ_TYPE
enum class ENUM_AET_FRQ_TYPE : unsigned int {
    E_AET_FRQ_FIXED = 0,
    E_AET_FRQ_HOPPING,
    E_AET_FRQ_AGILE,
    E_AET_FRQ_PATTERN,

    E_AET_FRQ_UNKNOWN,
    E_AET_FRQ_IGNORE,

    E_AET_MAX_FRQ_TYPE
};
#endif

// PRI 형태 정의
#ifndef _ENUM_AET_PRI_TYPE
#define _ENUM_AET_PRI_TYPE
enum class ENUM_AET_PRI_TYPE : unsigned int {
    E_AET_PRI_FIXED = 0,
    E_AET_PRI_JITTER,
    E_AET_PRI_DWELL_SWITCH,
    E_AET_PRI_STAGGER,
    E_AET_PRI_PATTERN,

    E_AET_PRI_UNKNOWN,

    E_AET_MAX_PRI_TYPE,

    //E_AET_PRI_BEACON, // 2015.4.12. 추가. 현재 ICD에 반영되어 있지 않음.
};
#endif

#ifndef _ENUM_AET_FREQ_PRI_PATTERN_TYPE
#define _ENUM_AET_FREQ_PRI_PATTERN_TYPE
enum class ENUM_AET_FREQ_PRI_PATTERN_TYPE : unsigned int {
    E_AET_FREQ_PRI_UNKNOWN = 0,
    E_AET_FREQ_PRI_SINE,
    E_AET_FREQ_PRI_SLIDE_INC,
    E_AET_FREQ_PRI_SLIDE_DEC,
    E_AET_FREQ_PRI_SAW_TRI,

    E_AET_MAX_FREQ_PRI_PATTERN_TYPE,

};
#endif

#endif


#ifndef _ENUM_AET_SCAN_TYPE
#define _ENUM_AET_SCAN_TYPE

#if defined(_ELINT_) || defined(_XBAND_)
/////////////////////////////////////////////////////////////////////////////////////////
// 안테나 스캔 형태 정의값
enum ENUM_AET_SCAN_TYPE : unsigned int {
    E_AET_SCAN_UNKNOWN = 0,
    E_AET_SCAN_CIRCULAR = 1,
    E_AET_SCAN_UNI_DIRECTIONAL,
    E_AET_SCAN_BI_DIRECTIONAL,
    E_AET_SCAN_CONICAL,
    E_AET_SCAN_STEADY,

    E_AET_SCAN_SCANFAIL,
    UFO,
    MAX_SCANTYPE,
    DetType,

    TYPE_UNKNOWN,
};
static const char aet_asp_type_ch[7][3] = { "UK" , "CR" , "SC" , "TW" , "CO" , "ST" , "MA" };

#elif defined(_POCKETSONATA_) || defined(_712_)
/////////////////////////////////////////////////////////////////////////////////////////
// 안테나 스캔 형태 정의값
enum class ENUM_AET_SCAN_TYPE : unsigned char {
    E_AET_SCAN_UNKNOWN = 0,
    E_AET_SCAN_CIRCULAR,
    E_AET_SCAN_UNI_DIRECTIONAL,
    E_AET_SCAN_BI_DIRECTIONAL,
    E_AET_SCAN_CONICAL,
    E_AET_SCAN_STEADY,

    E_AET_SCAN_SCANFAIL,

    E_AET_TRACKUNKNOWN,
    E_AET_DETECTUNKNOWN,
    E_AET_LOWILLUSTRATION,

    E_AET_MAX_SCAN_TYPE,

};
//static const char aet_asp_type_ch[7][3] = { "UK" , "CR" , "SC" , "TW" , "CO" , "ST" , "MA" } ;
#elif defined(_SONATA_)
//static const char aet_asp_type_ch[7][3] = { "UK" , "CR" , "SC" , "TW" , "CO" , "ST" , "MA" } ;

// 기본형
enum ENUM_AET_SCAN_TYPE {
    E_AET_SCAN_UNKNOWN = 0,
    E_AET_SCAN_CIRCULAR,
    E_AET_SCAN_UNI_DIRECTIONAL,
    E_AET_SCAN_BI_DIRECTIONAL,
    E_AET_SCAN_CONICAL,
    E_AET_SCAN_STEADY,

    E_AET_SCAN_SCANFAIL,

    UFO,
    MAX_SCANTYPE,

    DetType,

    TYPE_UNKNOWN,
};


#else
//static const char aet_asp_type_ch[7][3] = { "UK" , "CR" , "SC" , "TW" , "CO" , "ST" , "MA" } ;

// 기본형
/////////////////////////////////////////////////////////////////////////////////////////
// 안테나 스캔 형태 정의값
enum ENUM_AET_SCAN_TYPE {
    E_AET_SCAN_UNKNOWN = 0,
    E_AET_SCAN_CIRCULAR,
    E_AET_SCAN_UNI_DIRECTIONAL,
    E_AET_SCAN_BI_DIRECTIONAL,
    E_AET_SCAN_CONICAL,
    E_AET_SCAN_STEADY,

    E_AET_SCAN_SCANFAIL,

    E_AET_MAX_SCAN_TYPE,

};

#endif
#endif


#ifndef _ENUM_AET_SCAN_STAT
#define _ENUM_AET_SCAN_STAT
enum class ENUM_AET_SCAN_STAT : unsigned char {
    E_AET_UNANALYZED = 0,

    E_AET_SELF_SCAN_SUCCESS,
    E_AET_SELF_SCAN_FAIL,
    E_AET_USER_SCAN_SUCCESS,
    E_AET_USER_SCAN_FAIL,

};
#endif


///////////////////////////////////////////////////////////////////////////////////
// RadarDirAlgorithm.h

#ifndef _SRxLOBData_STRUCT
#define _SRxLOBData_STRUCT
struct SRxLOBData {
	unsigned int uiPDWID;

	unsigned int uiPLOBID;

	unsigned int uiLOBID;
	unsigned int uiABTID;
	unsigned int uiAETID;

	unsigned int tiContactTime;			// _USE_32BIT_TIME_T 로 선언하면 32비트, 없으면 64비트로 설정됨.

#if defined(_POCKETSONATA_) || defined(_712_)
	unsigned short tiContactTimems;
#else
	unsigned int tiContactTimems;
#endif

	char szPrimaryELNOT[_MAX_ELNOT_STRING_SIZE_];
	char szPrimaryModeCode[_MAX_SIZE_OF_MODECODE];								// 1번째 ELNOT

	char szSecondaryELNOT[_MAX_ELNOT_STRING_SIZE_];
	char szSecondaryModeCode[_MAX_SIZE_OF_MODECODE];							// 2번째 ELNOT

	char szTertiaryELNOT[_MAX_ELNOT_STRING_SIZE_];												// 3번째 ELNOT
	char szTertiaryModeCode[_MAX_SIZE_OF_MODECODE];

	char szModulationCode[_MAX_MODECODE_STRING_SIZE_];

#if defined(_XBAND_) || defined(_ELINT_)
	char szRadarName[_MAX_RADARMODE_NAME_SIZE];
	char szFuncCode[_MAX_FUNCTIONCODE_STRING_SIZE_];
#endif

	char szNickName[_MAX_NICKNAME_STRING_SIZE_];

#ifdef _ELINT_
	int iPolarization;          // 극성
	int iRatioOfPOL;            // 극성 신뢰도

#endif

#if defined(_POCKETSONATA_) || defined(_712_)
	unsigned char vSignalType;
#else
	unsigned int vSignalType;
#endif

	float fDOAMean;             // [0.1도]
	float fDOAMax;
	float fDOAMin;
	float fDOADeviation;		// [0.1도]
	float fDOAMode;             // DOA 최빈수

	unsigned int uiDIRatio;					// [1 %]

	ENUM_AET_FRQ_TYPE vFreqType;
	ENUM_AET_FREQ_PRI_PATTERN_TYPE vFreqPatternType;

	float fFreqPatternPeriod;                       // [us]
	float fFreqMean;				// [10KHz]
	float fFreqMax;
	float fFreqMin;
	float fFreqDeviation;
	float fFreqMode;            // Freq 최빈수

#if defined(_POCKETSONATA_) || defined(_712_)
	unsigned char vFreqPositionCount;
	unsigned char vFreqElementCount;
#else
	int vFreqPositionCount;
	int vFreqElementCount;
#endif

	float fFreqSeq[MAX_FREQ_PRI_STEP];	// 주파수 단값

	ENUM_AET_PRI_TYPE vPRIType;
	ENUM_AET_FREQ_PRI_PATTERN_TYPE vPRIPatternType;

	float fPRIPatternPeriod;		// [us]
	float fPRIMean;				// [1ns]
	float fPRIMax;
	float fPRIMin;
	float fPRIDeviation;		// [1ns]
	float fPRIMode;             // PRI 최빈수
	float fPRIJitterRatio;		// [%]

#if defined(_POCKETSONATA_) || defined(_712_)
	unsigned char vPRIPositionCount;
	unsigned char vPRIElementCount;
#else
	int vPRIPositionCount;
	int vPRIElementCount;
#endif

	float fPRISeq[MAX_FREQ_PRI_STEP];

	float fPWMean;				// 1ns
	float fPWMax;
	float fPWMin;
	float fPWDeviation;
	float fPWMode;              // 펄스폭 최빈수

	float fPAMean;
	float fPAMax;
	float fPAMin;
	float fPADeviation;
	float fPAMode;              // 신호세기 최빈수

#if defined(_XBAND_) || defined(_ELINT_)
#elif defined(_POCKETSONATA_) || defined(_712_)
	ENUM_AET_SCAN_TYPE vScanType;
	float fMeanScanPeriod;			// [msec]

	ENUM_MOP_TYPE enMOPType;				// 인트라 타입
	unsigned char ucDetailMOPType;			// 인트라 세부 타입.
	float fMOPMaxFreq;
	float fMOPMinFreq;
	float fMOPMeanFreq;
	float fMOPFreqDeviation;

#else
	ENUM_AET_SCAN_TYPE vScanType;
	float fScanPeriod;			// [msec]

	int iMOPType;				// 인트라 타입
	int iDetailMOPType;			// 인트라 세부 타입. 항공에서 줄 수 있는것인지(?)
	float fMOPMaxFreq;			// ??
	float fMOPMinFreq;
	float fMOPMeanFreq;
	float fMOPFreqDeviation;

	float fPitchAngle;
	float fRollAngle;
	float fHeadingAngle;
	float fAltitude;
	int iValidity;

#endif

#if defined(_XBAND_) || defined(_ELINT_)
		int iIsStoreData;
#endif

	unsigned int uiNumOfCollectedPDW;			// 신호 수집 개수
	unsigned int uiNumOfAnalyzedPDW;             // 분석된 PDW 개수

#if defined(_XBAND_) || defined(_ELINT_)
	int iNumOfIQ;

#endif

	char szRadarModeName[_MAX_RADARMODE_NAME_SIZE];
	unsigned int uiRadarModeIndex;

	unsigned int uiRadarIndex;                  // 레이더 인덱스 : ELNOT

	float fCollectLatitude;
	float fCollectLongitude;

#if defined(_POCKETSONATA_) || defined(_712_)

#elif defined(_ELINT_) || defined(_XBAND_) || defined(_701_)
	char aucTaskID[LENGTH_OF_TASK_ID];
	int	iCollectorID;
	unsigned int uiSeqNum;

#else
#endif

#if defined(_ELINT_) || defined(_XBAND_)
	unsigned int uiOpInitID;

#endif


};
#endif

#pragma pack( pop )

//////////////////////////////////////////////////////////////////////////
// 컴파일 방법

/* 이 헤더파일을 프로젝트 폴더에 복사하고 아래 함수를 호출하려고 하는 소스에 아래와 같이 include 한다.

#include "RadarDirAlgorithm.h"

:
:

RadarDirAlgotirhm::RadarDirAlgotirhm::Init();

:
:

RadarDirAlgotirhm::RadarDirAlgotirhm::Close();

*/

//////////////////////////////////////////////////////////////////////////
// 실행 방법

/* 1. 시작시 한번만 호출하면 됩니다.
	 응용 프로그램에서 초기화시에 아래 루틴을 한번 호출하면 됩니다.
   RadarDirAlgotirhm::RadarDirAlgotirhm::Init();

	 2. 프로그램 종료시 한번만 호출하면 됩니다.
	 RadarDirAlgotirhm::RadarDirAlgotirhm::Close();


	 3. 신호 분석시 PDWDATA 구조에 아래와 같이 데이터가 있어야 합니다.

typedef struct {
	char aucTaskID[LENGTH_OF_TASK_ID];			<---- 과제 정보
	unsigned int iIsStorePDW;								<---- 저장 여부. 일단 항상 1로 함.
	int iCollectorID;												<---- 수집소 위치. 소방대 분소는 1, 관제 수신소는 2, 신불 레이더#1/신불 레이더#2 은 3/4 로 할당
	ENUM_BANDWIDTH enBandWidth;							<---- 수집한 PDW의 수집과제 에서 대역폭을 저장

	UINT count;															<---- PDW 수집 개수
	_PDW stPDW[_MAX_PDW];										<---- PDW 데이터

} STR_PDWDATA ;

RadarDirAlgotirhm::RadarDirAlgotirhm::Start( & stPDWData );

		4. 분석 결과는 아래 함수를 호출하여 LOB 개수와 데이터를 얻는다.

		int nCoLOB=RadarDirAlgotirhm::RadarDirAlgotirhm::GetCoLOB();							<-- LOB 개수
		SRxLOBData *pLOBData=RadarDirAlgotirhm::RadarDirAlgotirhm::GetLOBData();	<--- LOB 데이터

		pLOBData[0] 로 첫번째 LOB 데이터, pLOBData[1] 로 두번째 LOB 데이터 등으로 사용하면 됩니다.

		*주의 사항 : PDWDATA 구조체에 과제 정보가 없거나 PDW 수집개수가 4096 개 초과되면 Start()에서 바로 리턴한다. LOB 개수는 0 으로 리턴한다.

*/
namespace RadarDirAlgotirhm
{

    static int g_iCoreOfSigAnal;
	static STR_PDWDATA gstPDWData;
	static CSysPara *gpSysPara;
    static CNewSigAnal **gpTheNewSigAnal;
    static CScanSigAnal *gpTheScanSigAnal;

	// This class is exported from the MathFuncsDll.dll
	class RadarDirAlgotirhm
	{
	private:
        static int g_iMax;

	public:
		~RadarDirAlgotirhm() {
			Close();
		}

		static MATHFUNCSDLL_API void Init( int iMaxNewSigAnal=1, HWND hWnd=0, bool bLocal=false );
        static MATHFUNCSDLL_API void SetMute( bool bEnable, int iCoreOfSigAnal = 0 );
        static MATHFUNCSDLL_API void SWInit();

        static MATHFUNCSDLL_API void Close( int iSigANal=0 );
        static MATHFUNCSDLL_API void CloseAll();

        static MATHFUNCSDLL_API void Start( STR_UZPOCKETPDW *pstUZPOCKETPDW, int iSigAnal=0, bool bDBInsert=false );
        static MATHFUNCSDLL_API void Start( STR_PDWDATA *pPDWData, int iSigAnal=0, bool bDBInsert=false );
        static MATHFUNCSDLL_API void Start( STR_PDWDATA *pPDWData, SRxLOBData *pLOBData, unsigned int uiScanStep, unsigned int uiReqScanPeriod, STR_SCANRESULT *pstScanResult );
        static MATHFUNCSDLL_API bool LoadCEDLibrary();
        static MATHFUNCSDLL_API bool LoadEOBLibrary();

        static MATHFUNCSDLL_API int GetCoLOB( int iSigAnal=0 );
        static MATHFUNCSDLL_API SRxLOBData *GetLOBData( int iSigANal=0 );
        static MATHFUNCSDLL_API STR_PDWINDEX *GetLOB2PDWData( unsigned int uiLOBIndex, int iSigANal = 0 );

        static MATHFUNCSDLL_API unsigned int GetOpInitID( int iSigAnal = 0 );

        static MATHFUNCSDLL_API const char *GetThreadName() { return NULL;  };

        static MATHFUNCSDLL_API unsigned int UZPOCKETPDW2PDWData( STR_PDWDATA *pPDWData, STR_UZPOCKETPDW *pstUZPOCKETPDW);

#pragma data_seg( ".ioshare" )
        // static CLog *g_pTheLog;
#pragma data_seg()


	};

}
