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

#pragma once


#include "../SigAnal/_Type.h"
#include "../SigAnal/_Define.h"

#define LENGTH_OF_TASK_ID			(19+1)		//과제ID 문자열 길이 (TBD)


enum ENUM_ANAL_TYPE : unsigned int {
    enCLEAR_ANAL = 0x00,

    enDET_ANAL = 0x01,
    enTRK_ANAL = 0x02,
    enDETTRK_ANAL = 0x03,
    enSCN_ANAL = 0x04,
    enDETSCN_ANAL = 0x05,
    enTRKSCN_ANAL = 0x06,
    enDETTRKSCN_ANAL = 0x07,

    enCOL = 0x8,                    // 수집 타스크

    enCOL_DET_ANAL = 0x9,
    enCOL_TRK_ANAL = 0x0A,
    enCOL_DETTRK_ANAL = 0x0B,
    enCOL_SCN_ANAL = 0x0C,
    enCOL_DETSCN_ANAL = 0x0D,
    enCOL_TRKSCN_ANAL = 0x0E,
    enCOL_DETTRKSCN_ANAL = 0x0F,

    enETC_ANAL = 0x10,

    enALL = enDET_ANAL | enTRK_ANAL | enSCN_ANAL | enCOL,

};



#ifndef ENUM_BOARDID
#define ENUM_BOARDID
enum ENUM_BoardID : unsigned int {
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


#ifdef _MAIN_GLOBALS_
// 장치 타입으로 이 값을 확인해서 장치에 맞게 실행하도록 한다.
#ifndef _ENUNIT_TYPE
#define _ENUNIT_TYPE
#ifdef _MSC_VER
__declspec( dllexport ) ENUM_UnitType g_enUnitType;
#else
ENUM_UnitType g_enUnitType;
#endif
#endif

#else

#ifndef _ENUNIT_TYPE
#define _ENUNIT_TYPE
#ifdef _MSC_VER
extern __declspec( dllexport ) ENUM_UnitType g_enUnitType;
#else
extern ENUM_UnitType g_enUnitType;
#endif
#endif

#endif


#ifndef _TOA_
#ifdef __VXWORKS__
typedef unsigned long long int _TOA;
#else
#ifdef _SONATA_
typedef unsigned int _TOA;
#else
typedef unsigned long long int _TOA;
#endif

#endif

#endif

typedef unsigned int _TOA2;

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

//////////////////////////////////////////////////////////////////////////

#pragma pack( push, 1 )


#ifdef _MSC_VER
struct UZPOCKETPDW_PDWWORD {
    // 1-1번 : 32비트
    unsigned long long int CwPulse : 1;
    unsigned long long int Pmop : 1;
    unsigned long long int Fmop : 1;
    unsigned long long int FalsePdw : 1;
    unsigned long long int FmopDir : 2;
    unsigned long long int PpfCh : 4;
    unsigned long long int BoardId : 4;
    unsigned long long int Reserved1 : 2;
    unsigned long long int FmopBw : 16;

    // 1-2번 : 32비트
    unsigned long long int uiAOA : 12;
    unsigned long long int Di : 1;
    unsigned long long int Reserved2 : 3;
    unsigned long long int uiPA : 16;

    // 2번 : 64비트
    unsigned long long int uiPW : 24;
    unsigned long long int uiFreq : 28;
    unsigned long long int Reserved3 : 12;

    // 3번 : 64비트
    unsigned long long int ullTOA : 44;
    unsigned long long int Edge : 1;
    unsigned long long int Reserved4 : 3;
    unsigned long long int Index : 16;

    // 4번 : 64비트
    unsigned long long int uiReserved5 : 32;
    unsigned long long int uiReserved6 : 32;

} ;

#else
    struct UZPOCKETPDW_PDWWORD {
    // 1-2번 : 32비트
    unsigned long long int uiPA : 16;
    unsigned long long int Reserved2 : 3;
    unsigned long long int Di : 1;
    unsigned long long int uiAOA : 12;         // Doa

    // 1-1번 : 32비트
    unsigned long long int FmopBw : 16;
    unsigned long long int Reserved1 : 2;
    unsigned long long int BoardId : 4;		// +
    unsigned long long int PpfCh : 4;
    unsigned long long int FmopDir : 2;
    unsigned long long int FalsePdw : 1;
    unsigned long long int Fmop : 1;
    unsigned long long int Pmop : 1;
    unsigned long long int CwPulse : 1;

    // 2번 : 64비트
    unsigned long long int Reserved3 : 12;
    unsigned long long int uiFreq : 28;		            // 16 --> 36 (IF --> RF) --> 28, Freq
    unsigned long long int uiPW : 24;


    // 3번 : 64비트
    unsigned long long int Index : 16;
    unsigned long long int Reserved4 : 3;
    unsigned long long int Edge : 1;
    unsigned long long int ullTOA : 44;

    // 4번 : 64비트
    unsigned long long int uiReserved5 : 32;
    unsigned long long int uiReserved6 : 32;

} ;

#endif

typedef union unUZPOCKETPDW {
    unsigned char chData[32];
    unsigned int wdData[8];
    unsigned long long int dwData[4];

    UZPOCKETPDW_PDWWORD stHwPdwDataRf;

} UZPOCKETPDW;



typedef union unDMAPDW {
    char chData[32];
    UZPOCKETPDW uPDW;

    /**
     * @brief     GetTOA
     * @return    _TOA
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-06, 10:54
     * @warning
     */
    _TOA GetTOA()
    {
        _TOA ullTOA;

        ullTOA = uPDW.stHwPdwDataRf.ullTOA;

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
    int GetChannel()
    {
        int iCh;

        iCh = uPDW.stHwPdwDataRf.PpfCh;
        //iCh = ( 16 + ( iCh - 8 ) ) % 16;

        return iCh;
    }

    /**
     * @brief     채널 값을 이용해서 주파수 값[kHZ]을 변환한다.
     * @param     int iCh
     * @return    unsigned int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-06, 10:54
     * @warning
     */
    unsigned int GetFrequency()
    {
        unsigned int uiFrequency;

        uiFrequency = uPDW.stHwPdwDataRf.uiFreq;

        return uiFrequency;

    }

    /**
     * @brief     펄스폭을 리턴한다.
     * @return    unsigned int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-06, 10:53
     * @warning
     */
    unsigned int GetPulsewidth()
    {
        unsigned int uiPulsewidth;

        uiPulsewidth = uPDW.stHwPdwDataRf.uiPW;
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
    unsigned int GetAOA()
    {
        unsigned int uiAOA;

        uiAOA = uPDW.stHwPdwDataRf.uiAOA;
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
    unsigned int GetPulseamplitude()
    {
        unsigned int uiPA;

        uiPA = uPDW.stHwPdwDataRf.uiPA;
        return uiPA;

    }

    /**
     * @brief     GetIndex
     * @return    unsigned int
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-05-08 18:05:00
     * @warning
     */
    unsigned int GetIndex()
    {
        return uPDW.stHwPdwDataRf.Index;
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
    int GetPulsetype()
    {
        int iPulsetype;

        if( uPDW.stHwPdwDataRf.CwPulse == 0 ) {
            iPulsetype = STAT_NORMAL;

            if( uPDW.stHwPdwDataRf.Pmop == 1 ) {
                iPulsetype = STAT_PMOP;
            }
            else if( uPDW.stHwPdwDataRf.Fmop == 1 ) {
                if( uPDW.stHwPdwDataRf.FmopDir == 1 ) {
                    iPulsetype = STAT_CHIRPUP;
                }
                else if( uPDW.stHwPdwDataRf.FmopDir == 2 ) {
                    iPulsetype = STAT_CHIRPDN;
                }
                else {
                    iPulsetype = STAT_CHIRPUK;
                }
            }
            else {

            }
        }
        else {
            iPulsetype = STAT_CW;

            if( uPDW.stHwPdwDataRf.Pmop == 1 ) {
                iPulsetype = STAT_CW_PMOP;
            }
            else if( uPDW.stHwPdwDataRf.Fmop == 1 ) {
                if( uPDW.stHwPdwDataRf.FmopDir == 1 ) {
                    iPulsetype = STAT_CW_CHIRPUP;
                }
                else if( uPDW.stHwPdwDataRf.FmopDir == 2 ) {
                    iPulsetype = STAT_CW_CHIRPDN;
                }
                else {
                    iPulsetype = STAT_CW_CHIRPUK;
                }
            }
            else {

            }
        }

        return iPulsetype;
    }

} DMAPDW;

//////////////////////////////////////////////////////////////////////////

#if defined(_GRAPH_) || defined(_SONATA_)

#define PDW_WORD_LEN        4
#define PDW_WORD_CNT        4

// PDW 파일, Platform이 어떤 것이냐에 따라 UNIX 로 정의하여 컴파일 또는 없이 컴파일함.
#ifndef _WIN32
//##ModelId=452B0C500266
typedef union {
    UCHAR bpdw[PDW_WORD_CNT][PDW_WORD_LEN];
    UINT wpdw[PDW_WORD_CNT];
    struct {
        UCHAR phase1 : 2; /* Phase 1 */
        UCHAR istat : 4;
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

    UINT GetTOA()
    {
        UINT uiTOA;

        uiTOA = item.toa_4;              /* toa의 첫번째 바이트를 move       */
        uiTOA <<= 8;                           /* toa를 왼쪽으로 8비트 shift       */
        uiTOA |= item.toa_3;              /* toa의 두번째 바이트를 더한다.    */
        uiTOA <<= 8;                           /* toa를 왼쪽으로 8비트 shift       */
        uiTOA |= item.toa_2;              /* toa의 세번째 바이트를 더한다.    */
        uiTOA <<= 8;                           /* toa를 왼쪽으로 8비트 shift       */
        uiTOA |= item.toa_1;              /* toa의 네번째 바이트를 더한다.    */

        return uiTOA;
    }

    UINT GetAOA()
    {
        UINT uiAOA;

        uiAOA = item.direction_h;  /* direction의 상위 바이트를 move   */
        uiAOA <<= 8;                     /* direction을 왼쪽으로 8비트 shift */
        uiAOA |= item.direction_l;  /* direction의 하위 바이트를 더한다 */

        return uiAOA;
    }

    UINT GetFrequency()
    {
        UINT uiFreq;

        uiFreq = item.frequency_h;   /* frequency의 상위 바이트를 move   */
        uiFreq <<= 8;                      /* frequency를 왼쪽으로 8비트 shift */
        uiFreq |= item.frequency_l;   /* frequency의 하위 바이트를 더한다 */

        return uiFreq;
    }

    UINT GetPulsewidth()
    {
        UINT uiPW;

        uiPW = item.pulse_width_h;  /* pulse_width의 상위 바이트를 move    */
        uiPW <<= 8;                       /* pulse_width를 왼쪽으로 8비트 shift  */
        uiPW |= item.pulse_width_l;  /* pulse_width의 하위 바이트를 더한다. */

        return uiPW;
    }

    UINT GetPulseamplitude()
    {
        return item.amplitude;
    }

    UINT GetPulsetype()
    {
        return item.istat;
    }

    UINT GetDirectionValid()
    {
        return item.dv;
    }

    UINT GetBand()
    {
        return item.band;
    }


} TNEW_PDW;

#else /* dos */

union TNEW_PDW {
    UCHAR bpdw[PDW_WORD_CNT][PDW_WORD_LEN];
    UINT wpdw[PDW_WORD_CNT];
    struct {
        UCHAR direction_h : 2;	/* Phase 1 */
        UCHAR istat : 4;
        UCHAR phase1 : 2;
        UCHAR direction_l : 8;
        UCHAR frequency_h : 5;
        UCHAR band : 2;
        UCHAR dv : 1;

        UCHAR frequency_l : 8;	/* Phase 2 */
        UCHAR pulse_width_h : 3;
        UCHAR pq : 1;
        UCHAR fil1 : 2;
        UCHAR phase2 : 2;
        UCHAR pulse_width_l : 8;
        UCHAR toa_4 : 8;

        UCHAR amplitude : 8;	/* Phase 3 */
        UCHAR fil2 : 6;
        UCHAR phase3 : 2;
        UCHAR toa_3 : 8;
        UCHAR toa_2 : 8;
        UCHAR toa_1 : 8;

        UCHAR chlp : 1;	/* Phase 4 */
        UCHAR fil3 : 5;
        UCHAR phase4 : 2;
        UCHAR channel : 8;
        UCHAR pmop : 8;
        UCHAR freq_diff : 8;
    } item;


    UINT GetTOA()
    {
        UINT uiTOA;

        uiTOA = item.toa_4;              /* toa의 첫번째 바이트를 move       */
        uiTOA <<= 8;                           /* toa를 왼쪽으로 8비트 shift       */
        uiTOA |= item.toa_3;              /* toa의 두번째 바이트를 더한다.    */
        uiTOA <<= 8;                           /* toa를 왼쪽으로 8비트 shift       */
        uiTOA |= item.toa_2;              /* toa의 세번째 바이트를 더한다.    */
        uiTOA <<= 8;                           /* toa를 왼쪽으로 8비트 shift       */
        uiTOA |= item.toa_1;              /* toa의 네번째 바이트를 더한다.    */

        return uiTOA;
    }

    UINT GetAOA()
    {
        UINT uiAOA;

        uiAOA = item.direction_h;  /* direction의 상위 바이트를 move   */
        uiAOA <<= 8;                     /* direction을 왼쪽으로 8비트 shift */
        uiAOA |= item.direction_l;  /* direction의 하위 바이트를 더한다 */

        return uiAOA;
    }

    UINT GetFrequency()
    {
        UINT uiFreq;

        uiFreq = item.frequency_h;   /* frequency의 상위 바이트를 move   */
        uiFreq <<= 8;                      /* frequency를 왼쪽으로 8비트 shift */
        uiFreq |= item.frequency_l;   /* frequency의 하위 바이트를 더한다 */

        return uiFreq;
    }

    UINT GetPulsewidth()
    {
        UINT uiPW;

        uiPW = item.pulse_width_h;  /* pulse_width의 상위 바이트를 move    */
        uiPW <<= 8;                       /* pulse_width를 왼쪽으로 8비트 shift  */
        uiPW |= item.pulse_width_l;  /* pulse_width의 하위 바이트를 더한다. */

        return uiPW;
    }

    UINT GetPulseamplitude()
    {
        return item.amplitude;
    }

    int GetPulsetype()
    {
        return item.istat;
    }

    int GetDirectionValid()
    {
        return item.dv;
    }

    int GetBand()
    {
        return item.band;
    }



};

#endif

#endif


// 수퍼헷 수신장치 개발한 것의 PDW 포멧
struct TNEW_SPDW {
    float Freq;
    float PA;
    float PW;
    unsigned int TOA;
    int Ref_Phase3;

};



// 아래는 MIDAS 변환을 하기 위해서 각 장치별로 변환 구조체 필요....
#ifndef _STR_STAT_BITMAP
#define _STR_STAT_BITMAP

#ifdef _MSC_VER
struct STR_STAT_BITMAP {
    unsigned int CwPulse : 1;
    unsigned int Pmop : 1;
    unsigned int Fmop : 1;
    unsigned int DI : 1;
    unsigned int FalsePdw : 1;
    unsigned int FmopDir : 2;
    unsigned int Edge : 1;

    unsigned int _dummy : 8;

    unsigned int FMOPBW : 16;


};
#else
struct STR_STAT_BITMAP {
    unsigned int FMOPBW : 16;

    unsigned int _dummy : 8;

    unsigned int Edge : 1;
    unsigned int FmopDir : 2;
    unsigned int FalsePdw : 1;
    unsigned int DI : 1;
    unsigned int Fmop : 1;
    unsigned int Pmop : 1;
    unsigned int CwPulse : 1;

};

#endif

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

        union {
            unsigned int uiValue;
            STR_STAT_BITMAP stStrBitMap;
        } x ;

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

typedef struct _stPDW {
    int iStat;

    unsigned int uiAOA;
    unsigned int uiFreq;
    unsigned int uiPA;
    unsigned int uiPW;

    unsigned int uiIndex;

    UNI_PDW_ETC x;

    _TOA tTOA;

    /**
     * @brief     _PDW 구조체에서 TOA 값을 리턴한다.
     * @return    _TOA
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-09, 17:12
     * @warning
     */
    _TOA GetTOA()
    {
        return tTOA;

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
    int GetChannel()
    {
        int iRet;

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            iRet = x.ps.iChannel;
        }
        else {
            iRet = -1;
        }

        return iRet;

    }

    /**
     * @brief     GetCWPulse
     * @return    int
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-10-08 15:33:13
     * @warning
     */
    int GetCWPulse()
    {
        int iRet;

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            iRet = x.ps.x.stStrBitMap.CwPulse;
        }
        else {
            iRet = -1;
        }

        return iRet;

    }

    /**
     * @brief     GetPMOP
     * @return    int
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-10-08 15:33:51
     * @warning
     */
    int GetPMOP()
    {
        int iRet;

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            iRet = x.ps.x.stStrBitMap.Pmop;
        }
        else {
            iRet = -1;
        }

        return iRet;

    }

    /**
     * @brief     GetFMOP
     * @return    int
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-10-08 15:34:07
     * @warning
     */
    int GetFMOP()
    {
        int iRet;

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            iRet = x.ps.x.stStrBitMap.Fmop;
        }
        else {
            iRet = -1;
        }

        return iRet;

    }

    /**
     * @brief     GetFMOPDir
     * @return    int
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-10-08 15:34:25
     * @warning
     */
    int GetFMOPDir()
    {
        int iRet;

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            iRet = x.ps.x.stStrBitMap.FmopDir;
        }
        else {
            iRet = -1;
        }

        return iRet;

    }

    /**
     * @brief     GetDI
     * @return    int
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-10-08 15:41:03
     * @warning
     */
    int GetDI()
    {
        int iRet;

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            iRet = x.ps.x.stStrBitMap.DI;
        }
        else {
            iRet = -1;
        }

        return iRet;

    }

    /**
     * @brief     GetFalsePDW
     * @return    int
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-10-08 15:41:31
     * @warning
     */
    int GetFalsePDW()
    {
        int iRet;

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            iRet = x.ps.x.stStrBitMap.FalsePdw;
        }
        else {
            iRet = -1;
        }

        return iRet;

    }

    /**
     * @brief     GetFMOPBW
     * @return    int
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-10-08 15:38:59
     * @warning
     */
    int GetFMOPBW()
    {
        int iRet;

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            iRet = x.ps.x.stStrBitMap.FMOPBW;
        }
        else {
            iRet = 0;
        }

        return iRet;

    }

    /**
     * @brief     GetEdge
     * @return    int
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-10-08 15:27:34
     * @warning
     */
    int GetEdge()
    {
        int iRet;

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            iRet = x.ps.x.stStrBitMap.Edge;
        }
        else {
            iRet = -1;
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
    void SetChannel( int iCh )
    {
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
    unsigned int GetFrequency( int iCh = -1 )
    {
        unsigned int uiFrequency;

        if( iCh == -1 ) {
            uiFrequency = uiFreq;
            //fFreq = FRQMhzCNV( g_enBoardId, uiFreq );
            //FDIV( (FMUL( gFreqRes[(A)].fRes, (B) ) + gFreqRes[(A)].iOffset), 1000 )  //CPOCKETSONATAPDW::DecodeFREQMHz( B )
        }
        else {
            int iiCh;

            iiCh = ( 16 + ( iCh - 8 ) ) % 16;

            uiFrequency = ( 0x10000 + ( uiFreq - 0x8000 ) ) % 0x10000;

            uiFrequency = uiFrequency + ( UINT ) ( iiCh * 0x10000 );
        }

        return uiFrequency;
    }

    /**
     * @brief     펄스폭 값을 리턴한다.
     * @return    unsigned int
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2022-11-02 10:23:29
     * @warning
     */
    unsigned int GetPulsewidth()
    {
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
    unsigned int GetAOA()
    {
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
    unsigned int GetPulseamplitude()
    {
        return uiPA;

    }


    /**
     * @brief     GetPulsetype
     * @return    int
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-04-04 15:06:00
     * @warning
     */
    int GetPulsetype()
    {
        return iStat;
    }

    unsigned int GetIndex()
    {
        return uiIndex;
    }

    /**
     * @brief     GetDirectionValid
     * @return    unsigned int
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-04-04 15:06:02
     * @warning
     */
    unsigned int GetDirectionValid()
    {
        unsigned int uiRet=(unsigned int ) -1;

        if( g_enUnitType == en_701 ) {
#if defined(_GRAPH_) || defined(_701_)
            uiRet = ( unsigned int ) x._701.iDirectionValid;
#endif
        }
        else {
        }

        return uiRet;
    }


} _PDW ;

#endif

#pragma pack( pop )



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

// 장비별로 대역폭을 정의 한다.
#if defined(_ELINT_)


#elif defined(_XBAND_)


#elif defined(_POCKETSONATA_) || defined(_712_)
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


#ifndef _ENUM_DataType
#define _ENUM_DataType
enum ENUM_DataType {
    en_UnknownData = 0,

    en_PDW_DATA,
    en_PDW_DATA_CSV,
    en_IQ_DATA,
    en_IF_DATA,

};
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


#pragma pack( push, 1 )

#define swapUINTOrder(X)	((X >> 24) | ((X << 8) & 0x00FF0000) | ((X >> 8) & 0x0000FF00) | (X << 24))
#define swapULLOrder(X)		( (X >> 56) | ((X << 40) & 0x00FF000000000000) | ((X << 24) & 0x0000FF0000000000) | ((X << 8) & 0x000000FF00000000) | \
							  ((X >> 8) & 0x00000000FF000000) | ((X >> 24) & 0x0000000000FF0000) | ((X >> 40) & 0x000000000000FF00) | (X << 56) )


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

    void CheckColTime()
    {

    }

};

typedef struct stSRxPDWDataRGroup {
    _TOA ullTOA;
    unsigned int uiPulseType;
    unsigned int uiPolFlag;
    unsigned int uiFMOPFlag;
    unsigned int uiPMOPFlag;
    unsigned int uiBlankingTag;
    unsigned int uiIsChannelChangePOP;
    unsigned int uiBLK;

    unsigned int uiDirectionVaild;
    unsigned int uiAcqDirectionLimit;
    unsigned int uiChannelNumber;
    unsigned int uiPA;
    unsigned int uiFreq;
    unsigned int uiDirection;
    unsigned int uiPolization;
    unsigned int uiPFTag;
    unsigned int uiPW;
    UINT uiPDWID;

    /**
     * @brief     GetTOA
     * @return    _TOA
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-01-08 11:54:36
     * @warning
     */
    _TOA GetTOA( ENUM_DataType enDataType )
    {
        _TOA tTemp;

        if( enDataType == en_PDW_DATA_CSV ) {
            tTemp = ullTOA;
        }
        else {
#ifdef _SONATA_
            tTemp = swapUINTOrder( ullTOA );
#else
            tTemp = swapULLOrder( ullTOA );
#endif
        }

        return tTemp;

    }

    /**
     * @brief     GetChannel
     * @return    int
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-01-08 11:54:32
     * @warning
     */
    int GetChannel( ENUM_DataType enDataType )
    {
        int iTemp;

        if( enDataType == en_PDW_DATA_CSV ) {
            iTemp = ( int ) uiChannelNumber;
        }
        else {
            iTemp = ( int ) swapUINTOrder( uiChannelNumber );
        }
        return iTemp;
    }

    /**
     * @brief     SetChannel
     * @param     int iCh
     * @return    void
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-01-08 11:55:48
     * @warning
     */
    void SetChannel( int iCh )
    {
        uiChannelNumber = ( unsigned int ) iCh;
    }

    /**
     * @brief     GetFrequency
     * @param     int iCh
     * @return    unsigned int
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-01-08 11:55:41
     * @warning
     */
    unsigned int GetFrequency( ENUM_DataType enDataType )
    {
        unsigned int uiTemp;

        if( enDataType == en_PDW_DATA_CSV ) {
            uiTemp = uiFreq;
        }
        else {
            uiTemp = swapUINTOrder( uiFreq );
        }

        return uiTemp;
    }

    /**
     * @brief     GetPulsewidth
     * @return    unsigned int
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-01-08 11:55:37
     * @warning
     */
    unsigned int GetPulsewidth( ENUM_DataType enDataType )
    {
        unsigned int uiTemp;

        if( enDataType == en_PDW_DATA_CSV ) {
            uiTemp = uiPW;
        }
        else {
            uiTemp = swapUINTOrder( uiPW );
        }

        return uiTemp;
    }

    /**
     * @brief     GetAOA
     * @return    unsigned int
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-01-08 13:12:23
     * @warning
     */
    unsigned int GetAOA( ENUM_DataType enDataType )
    {
        unsigned int uiTemp;

        if( enDataType == en_PDW_DATA_CSV ) {
            uiTemp = uiDirection;
        }
        else {
            uiTemp = swapUINTOrder( uiDirection );
        }

        return uiTemp;
    }

    /**
     * @brief     GetPulseamplitude
     * @return    unsigned int
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-01-08 11:55:30
     * @warning
     */
    unsigned int GetPulseamplitude( ENUM_DataType enDataType )
    {
        unsigned int uiTemp;

        if( enDataType == en_PDW_DATA_CSV ) {
            uiTemp = uiPA;
        }
        else {
            uiTemp = swapUINTOrder( uiPA );
        }
        return uiTemp;

    }

    /**
     * @brief     GetPulsetype
     * @return    int
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-01-08 11:55:54
     * @warning
     */
    int GetPulsetype( ENUM_DataType enDataType )
    {
        int iTemp;

        if( enDataType == en_PDW_DATA_CSV ) {
            iTemp = ( int ) uiPulseType;
        }
        else {
            iTemp = ( int ) swapUINTOrder( uiPulseType );
        }

        return iTemp;
    }

    /**
     * @brief     GetDirectionValid
     * @param     ENUM_DataType enDataType
     * @return    unsigned int
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-01-18 13:01:57
     * @warning
     */
    unsigned int  GetDirectionValid( ENUM_DataType enDataType )
    {
        unsigned int uiTemp;

        if( enDataType == en_PDW_DATA_CSV ) {
            uiTemp = uiPulseType;
        }
        else {
            uiTemp = swapUINTOrder( uiPulseType );
        }

        return uiTemp;
    }

} SRxPDWDataRGroup;

#pragma pack( pop )

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


struct STR_IQ_HEADER {
    //ENUM_COL_MODE enMode;
    float fCenterFreq;
    float fColTime;
    UINT uiColNumber;
    float fThreshold;

};

typedef struct stTNEW_IQ {
    short sI;
    short sQ;
} TNEW_IQ;

#ifndef _STR_COMMON_HEADER_
#define _STR_COMMON_HEADER_
// 아래는 공용 정보
typedef struct stSTR_COMMON_HEADER {
    UINT uiTotalPDW;
    unsigned int uiColTime;
    UINT uiColTimeMs;
    UINT uiPDWID;

    void CheckColTime()
    {
        if( uiColTimeMs > 1000 ) {
            uiColTimeMs = 0;
        }
    }

} STR_COMMON_HEADER;
#endif

#ifndef _STR_ELINT_HEADER_
#define _STR_ELINT_HEADER_
typedef struct stSTR_ELINT_HEADER {
    char aucTaskID[LENGTH_OF_TASK_ID];
    unsigned int uiIsStorePDW;
    EN_RADARCOLLECTORID enCollectorID;
    ELINT::ENUM_BANDWIDTH enBandWidth;

    // 아래는 공용 정보
    STR_COMMON_HEADER stCommon;

    EN_RADARCOLLECTORID GetCollectorID()
    {
        return enCollectorID;
    }

    void SetCollectorID( EN_RADARCOLLECTORID i_enCollectorID )
    {
        enCollectorID = i_enCollectorID;
    }

    unsigned int GetTotalPDW()
    {
        return stCommon.uiTotalPDW;
    }

    unsigned int GetPDWID()
    {
        return stCommon.uiPDWID;
    }

    void SetTotalPDW( unsigned int uiTotalPDW )
    {
        stCommon.uiTotalPDW = uiTotalPDW;
    }

    void SetIsStorePDW( unsigned int isStorePDW )
    {
        uiIsStorePDW = isStorePDW;
    }

    void CheckColTime()
    {
        stCommon.CheckColTime();
    }

} STR_ELINT_HEADER;

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

    EN_RADARCOLLECTORID GetCollectorID()
    {
        return enCollectorID;
    }

    void SetCollectorID( EN_RADARCOLLECTORID i_enCollectorID )
    {
        enCollectorID = i_enCollectorID;
    }

    unsigned int GetTotalPDW()
    {
        return stCommon.uiTotalPDW;
    }

    unsigned int GetPDWID()
    {
        return stCommon.uiPDWID;
    }

    void SetTotalPDW( unsigned int uiTotalPDW )
    {
        stCommon.uiTotalPDW = uiTotalPDW;
    }

    void SetIsStorePDW( unsigned int isStorePDW )
    {
        uiIsStorePDW = isStorePDW;
    }

    void CheckColTime()
    {
        stCommon.CheckColTime();
    }

};

#endif

#ifndef _STR_XBAND_HEADER_
#define _STR_XBAND_HEADER_
typedef struct stSTR_XBAND_HEADER {
    char aucTaskID[LENGTH_OF_TASK_ID];
    unsigned int uiIsStorePDW;
    EN_RADARCOLLECTORID enCollectorID;
    XBAND::ENUM_BANDWIDTH enBandWidth;

    // 아래는 공용 정보
    STR_COMMON_HEADER stCommon;

    EN_RADARCOLLECTORID GetCollectorID()
    {
        return enCollectorID;
    }

    void SetCollectorID( EN_RADARCOLLECTORID i_enCollectorID )
    {
        enCollectorID = i_enCollectorID;
    }

    unsigned int GetTotalPDW()
    {
        return stCommon.uiTotalPDW;
    }

    unsigned int GetPDWID()
    {
        return stCommon.uiPDWID;
    }

    void SetTotalPDW( unsigned int uiTotalPDW )
    {
        stCommon.uiTotalPDW = uiTotalPDW;
    }

    void SetIsStorePDW( unsigned int isStorePDW )
    {
        uiIsStorePDW = isStorePDW;
    }

    void CheckColTime()
    {
        stCommon.CheckColTime();
    }

} STR_XBAND_HEADER;
#endif

#ifndef _POCKETSONATA_HEADER_
#define _POCKETSONATA_HEADER_
typedef struct _STR_POCKETSONATA_HEADER {
    unsigned int uiBoardID;
    ENUM_COLLECTBANK enCollectBank;
    unsigned int uiBand;                // 주파수 대역
    unsigned int uiIsStorePDW;

    // 아래는 공용 정보
    STR_COMMON_HEADER stCommon;

    unsigned int GetTotalPDW()
    {
        return stCommon.uiTotalPDW;
    }

    unsigned int GetPDWID()
    {
        return stCommon.uiPDWID;
    }

    void SetTotalPDW( unsigned int uiTotalPDW )
    {
        stCommon.uiTotalPDW = uiTotalPDW;
    }

    void SetIsStorePDW( unsigned int isStorePDW )
    {
        uiIsStorePDW = isStorePDW;
    }

    void CheckColTime()
    {
        stCommon.CheckColTime();

    }

} STR_POCKETSONATA_HEADER;
#endif


#ifndef _SONATA_HEADER_
#define _SONATA_HEADER_
typedef struct stSTR_SONATA_HEADER {
    unsigned int uiBand;
    unsigned int uiIsStorePDW;
    ENUM_COLLECTBANK enCollectBank;

    // 아래는 공용 정보
    STR_COMMON_HEADER stCommon;

    unsigned int GetTotalPDW()
    {
        return stCommon.uiTotalPDW;
    }

    unsigned int GetPDWID()
    {
        return stCommon.uiPDWID;
    }

    void SetTotalPDW( unsigned int uiTotalPDW )
    {
        stCommon.uiTotalPDW = uiTotalPDW;
    }

    void SetIsStorePDW( unsigned int isStorePDW )
    {
        uiIsStorePDW = isStorePDW;
    }

    void CheckColTime()
    {

    }


} STR_SONATA_HEADER;
#endif

#ifndef _UNION_HEADER_
#define _UNION_HEADER_

typedef union unUNION_HEADER {
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

#if defined(_GRAPH_) || defined(_701_)
    void SetTaskID( char *pString )
    {
        switch( g_enUnitType ) {
            case en_ZPOCKETSONATA:
                break;

            case en_ELINT:
            case en_XBAND:
                break;

            case en_SONATA:
                break;


            case en_701:
                strcpy( e7.aucTaskID, pString );
                break;

            default:
                break;

        }

    }

#endif

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
    char *GetTaskID( ENUM_UnitType enUnitType )
    {
        char *pTaskID;

        switch( enUnitType ) {
            case en_ZPOCKETSONATA:
                pTaskID = ( char * ) NULL;
                break;

#if defined(_GRAPH_) || defined(_ELINT_)
            case en_ELINT:
                pTaskID = &el.aucTaskID[0];
                break;
#endif
#if defined(_GRAPH_) || defined(_XBAND_)
            case en_XBAND:
                pTaskID = & xb.aucTaskID[0];
                break;
#endif

            case en_SONATA:
                pTaskID = ( char * ) NULL;
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
    unsigned int GetTotalPDW( ENUM_UnitType enUnitType = g_enUnitType )
    {
        unsigned int uiTotalPDW;

        switch( enUnitType ) {
            case en_ZPOCKETSONATA:
                uiTotalPDW = ps.stCommon.uiTotalPDW;
                break;

#if defined(_GRAPH_) || defined(_ELINT_)
            case en_ELINT:
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
            case en_SONATA:
                uiTotalPDW = ( UINT ) -1;	// SONATA용 헤더는 없기 때문에 (-1)로 리턴함.
                break;
#endif

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
    void SetTotalPDW( unsigned int uiTotalPDW )
    {

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            ps.stCommon.uiTotalPDW = uiTotalPDW;
        }
#if defined(_GRAPH_) || defined(_ELINT_)
        else if( g_enUnitType == en_ELINT ) {
            el.stCommon.uiTotalPDW = uiTotalPDW;
        }
#endif
#if defined(_GRAPH_) || defined(_XBAND_)
        else if( g_enUnitType == en_XBAND ) {
            xb.stCommon.uiTotalPDW = uiTotalPDW;
        }
#endif
#if defined(_GRAPH_) || defined(_SONATA_)
        else if( g_enUnitType == en_SONATA ) {
            so.stCommon.uiTotalPDW = uiTotalPDW;
        }
#endif
#if defined(_GRAPH_) || defined(_701_)
        else if( g_enUnitType == en_701 ) {
            e7.stCommon.uiTotalPDW = uiTotalPDW;
        }
#endif
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
    void SetIsStorePDW( unsigned int isStorePDW )
    {

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            ps.SetIsStorePDW( isStorePDW );
        }
#if defined(_GRAPH_) || defined(_ELINT_)
        else if( g_enUnitType == en_ELINT ) {
            el.SetIsStorePDW( isStorePDW );
        }
#endif
#if defined(_GRAPH_) || defined(_XBAND_)
        else if( g_enUnitType == en_XBAND ) {
            xb.SetIsStorePDW( isStorePDW );
        }
#endif
#if defined(_GRAPH_) || defined(_SONATA_)
        else if( g_enUnitType == en_SONATA ) {
            so.SetIsStorePDW( isStorePDW );
        }
#endif
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
    int GetBoardID( ENUM_UnitType enUnitType )
    {
        int iBoardID;

        switch( enUnitType ) {
            case en_ZPOCKETSONATA:
                iBoardID = ( int ) ps.uiBoardID;
                break;

            case en_ELINT:
            case en_XBAND:
                iBoardID = -1;
                break;

            case en_SONATA:
                iBoardID = -1;
                break;

            default:
                iBoardID = -1;
                break;

        }
        return iBoardID;
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
    void SetBoardID( unsigned int uiBoardID )
    {

        switch( g_enUnitType ) {
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
     * @param     time_t tColTime
     * @param     UINT uiColTimeMs
     * @return    void
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-10, 10:30
     * @warning
     */
    void SetColTime( unsigned int tColTime, UINT uiColTimeMs )
    {

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            ps.stCommon.uiColTime = tColTime;
            ps.stCommon.uiColTimeMs = uiColTimeMs;
        }
#if defined(_GRAPH_) || defined(_ELINT_)
        else if( g_enUnitType == en_ELINT ) {
            el.stCommon.uiColTime = tColTime;
            el.stCommon.uiColTimeMs = uiColTimeMs;
        }
#endif
#if defined(_GRAPH_) || defined(_XBAND_)
        else if( g_enUnitType == en_XBAND ) {
            xb.stCommon.uiColTime = tColTime;
            xb.stCommon.uiColTimeMs = uiColTimeMs;
        }
#endif
#if defined(_GRAPH_) || defined(_SONATA_)
        else if( g_enUnitType == en_SONATA ) {
            so.stCommon.uiColTime = tColTime;
            so.stCommon.uiColTimeMs = uiColTimeMs;
        }
#endif
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
//     void SetBoardID( unsigned int uiBoardID )
//     {
//
//         if( g_enUnitType == en_ZPOCKETSONATA ) {
//             ps.uiBoardID = uiBoardID;
//         }
//         else {
//             // x.so.stCommon.uiPDWID;
//         }
//
//         return;
//
//     }

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
    void SetBand( unsigned int uiBand )
    {

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
    void SetCollectorID( EN_RADARCOLLECTORID enCollectorID )
    {

        if( g_enUnitType == en_ZPOCKETSONATA ) {
        }
#if defined(_GRAPH_) || defined(_ELINT_)
        else if( g_enUnitType == en_ELINT ) {
            el.enCollectorID = enCollectorID;
        }
#endif
#if defined(_GRAPH_) || defined(_XBAND_)
        else if( g_enUnitType == en_XBAND ) {
            xb.enCollectorID = enCollectorID;
        }
#endif
        else {
        }
    }

    /**
     * @brief     수집 과제의 대역폭을 리턴한다.
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

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            iBandwidth = ( int ) ps.uiBand;
        }
#if defined(_GRAPH_) || defined(_ELINT_)
        else if( g_enUnitType == en_ELINT ) {
            iBandwidth = ( int ) el.enBandWidth;
        }
#endif
#if defined(_GRAPH_) || defined(_XBAND_)
        else if( g_enUnitType == en_XBAND ) {
            iBandwidth = ( int ) xb.enBandWidth;
        }
#endif
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
    void SetBandWidth( int iBandWidth )
    {
        if( g_enUnitType == en_ZPOCKETSONATA ) {
        }
#if defined(_GRAPH_) || defined(_ELINT_)
        else if( g_enUnitType == en_ELINT ) {
            el.enBandWidth = ( ELINT::ENUM_BANDWIDTH ) iBandWidth;
        }
#endif
#if defined(_GRAPH_) || defined(_XBAND_)
        else if( g_enUnitType == en_XBAND ) {
            xb.enBandWidth = ( XBAND::ENUM_BANDWIDTH ) iBandWidth;
        }
#endif
        else {
        }

    }

} UNION_HEADER;


#endif


#ifndef _STR_PDWDATA
#define _STR_PDWDATA
typedef struct stSTR_PDWDATA {
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
    unsigned int GetHeader()
    {
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
            uiHeader = sizeof( STR_SONATA_HEADER );
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
    void SetIsStorePDW( unsigned int isStorePDW )
    {

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            x.ps.SetIsStorePDW( isStorePDW );
        }
#if defined(_GRAPH_) || defined(_ELINT_)
        else if( g_enUnitType == en_ELINT ) {
            x.el.SetIsStorePDW( isStorePDW );
        }
#endif
#if defined(_GRAPH_) || defined(_XBAND_)
        else if( g_enUnitType == en_XBAND ) {
            x.xb.SetIsStorePDW( isStorePDW );
        }
#endif
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
    void SetBoardID( ENUM_BoardID enBoardID )
    {

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            x.ps.uiBoardID = ( unsigned int ) enBoardID;
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
    void SetCollectBank( ENUM_COLLECTBANK enBank )
    {

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            x.ps.enCollectBank = enBank;
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
    void SetBand( unsigned int uiBand )
    {

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
    unsigned int GetBand()
    {
        unsigned int uiBand = 0;

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            uiBand = x.ps.uiBand;
        }
        else if( g_enUnitType == en_ELINT ) {
            //uiBand = x.el.uiBand;
        }
        else if( g_enUnitType == en_XBAND ) {
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
    unsigned int GetPDWID()
    {
        unsigned int uiPDWID;

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            uiPDWID = x.ps.stCommon.uiPDWID;
        }
#if defined(_GRAPH_) || defined(_ELINT_)
        else if( g_enUnitType == en_ELINT ) {
            uiPDWID = x.el.stCommon.uiPDWID;
        }
#endif
#if defined(_GRAPH_) || defined(_XBAND_)
        else if( g_enUnitType == en_XBAND ) {
            uiPDWID = x.xb.stCommon.uiPDWID;
        }
#endif
#if defined(_GRAPH_) || defined(_SONATA_)
        else if( g_enUnitType == en_SONATA ) {
            uiPDWID = x.so.stCommon.uiPDWID;
        }
#endif
        else {
            uiPDWID = 0;
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
    void SetPDWID( unsigned int uiPDWID )
    {

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            x.ps.stCommon.uiPDWID = uiPDWID;
        }
#if defined(_GRAPH_) || defined(_ELINT_)
        else if( g_enUnitType == en_ELINT ) {
            x.el.stCommon.uiPDWID = uiPDWID;
        }
#endif
#if defined(_GRAPH_) || defined(_XBAND_)
        else if( g_enUnitType == en_XBAND ) {
            x.xb.stCommon.uiPDWID = uiPDWID;
        }
#endif
#if defined(_GRAPH_) || defined(_SONATA_)
        else if( g_enUnitType == en_SONATA ) {
            x.so.stCommon.uiPDWID = uiPDWID;
        }
#endif

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
    void IncPDWID()
    {
        if( g_enUnitType == en_ZPOCKETSONATA ) {
            ++ x.ps.stCommon.uiPDWID;
        }
#if defined(_GRAPH_) || defined(_ELINT_)
        else if( g_enUnitType == en_ELINT ) {
            ++ x.el.stCommon.uiPDWID;
        }
#endif
#if defined(_GRAPH_) || defined(_XBAND_)
        else if( g_enUnitType == en_XBAND ) {
            ++ x.xb.stCommon.uiPDWID;
        }
#endif
#if defined(_GRAPH_) || defined(_SONATA_)
        else if( g_enUnitType == en_SONATA ) {
            ++ x.so.stCommon.uiPDWID;
        }
#endif
        else {
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
    EN_RADARCOLLECTORID GetCollectorID()
    {
        EN_RADARCOLLECTORID enCollectorID;

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            enCollectorID = RADARCOL_Unknown;
        }
#if defined(_GRAPH_) || defined(_ELINT_)
        else if( g_enUnitType == en_ELINT ) {
            enCollectorID = x.el.enCollectorID;
        }
#endif
#if defined(_GRAPH_) || defined(_XBAND_)
        else if( g_enUnitType == en_XBAND ) {
            enCollectorID = x.xb.enCollectorID;
        }
#endif
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
    unsigned int GetTotalPDW()
    {
        unsigned int uiTotalPDW;

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            uiTotalPDW = x.ps.stCommon.uiTotalPDW;
        }
#if defined(_GRAPH_) || defined(_ELINT_)
        else if( g_enUnitType == en_ELINT ) {
            uiTotalPDW = x.el.stCommon.uiTotalPDW;
        }
#endif
#if defined(_GRAPH_) || defined(_XBAND_)
        else if( g_enUnitType == en_XBAND ) {
            uiTotalPDW = x.xb.stCommon.uiTotalPDW;
        }
#endif
#if defined(_GRAPH_) || defined(_701_)
        else if( g_enUnitType == en_701 ) {
            uiTotalPDW = x.e7.stCommon.uiTotalPDW;
        }
#endif
#if defined(_GRAPH_) || defined(_SONATA_)
        else if( g_enUnitType == en_SONATA ) {
            uiTotalPDW = x.so.stCommon.uiTotalPDW;
        }
#endif
        else {
            uiTotalPDW = 0;
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
    void SetTotalPDW( unsigned int uiTotalPDW )
    {
        if( g_enUnitType == en_ZPOCKETSONATA ) {
            x.ps.stCommon.uiTotalPDW = uiTotalPDW;
        }
#if defined(_GRAPH_) || defined(_ELINT_)
        else if( g_enUnitType == en_ELINT ) {
            x.el.stCommon.uiTotalPDW = uiTotalPDW;
        }
#endif
#if defined(_GRAPH_) || defined(_XBAND_)
        else if( g_enUnitType == en_XBAND ) {
            x.xb.stCommon.uiTotalPDW = uiTotalPDW;
        }
#endif
#if defined(_GRAPH_) || defined(_701_)
        else if( g_enUnitType == en_701 ) {
            x.e7.stCommon.uiTotalPDW = uiTotalPDW;
        }
#endif
#if defined(_GRAPH_) || defined(_SONATA_)
        else if( g_enUnitType == en_SONATA ) {
            x.so.stCommon.uiTotalPDW = uiTotalPDW;
        }
#endif
        else {
        }

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
    void SetColTime( unsigned int tColTime, UINT uiColTimeMs )
    {

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            x.ps.stCommon.uiColTime = tColTime;
            x.ps.stCommon.uiColTimeMs = uiColTimeMs;
        }
#if defined(_GRAPH_) || defined(_ELINT_)
        else if( g_enUnitType == en_ELINT ) {
            x.el.stCommon.uiColTime = tColTime;
            x.el.stCommon.uiColTimeMs = uiColTimeMs;
        }
#endif
#if defined(_GRAPH_) || defined(_XBAND_)
        else if( g_enUnitType == en_XBAND ) {
            x.xb.stCommon.uiColTime = tColTime;
            x.xb.stCommon.uiColTimeMs = uiColTimeMs;
        }
#endif
#if defined(_GRAPH_) || defined(_SONATA_)
        else if( g_enUnitType == en_SONATA ) {
            x.so.stCommon.uiColTime = tColTime;
            x.so.stCommon.uiColTimeMs = uiColTimeMs;
        }
#endif
        else {
        }
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
    unsigned int GetColTime()
    {
        unsigned int retTime;

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            retTime = x.ps.stCommon.uiColTime;
        }
#if defined(_GRAPH_) || defined(_ELINT_)
        else if( g_enUnitType == en_ELINT ) {
            retTime = x.el.stCommon.uiColTime;
        }
#endif
#if defined(_GRAPH_) || defined(_XABND_)
        else if( g_enUnitType == en_XBAND ) {
            retTime = x.xb.stCommon.uiColTime;
        }
#endif
#if defined(_GRAPH_) || defined(_SONATA_)
        else if( g_enUnitType == en_SONATA ) {
            retTime = x.so.stCommon.uiColTime;
        }
#endif
        else {
            retTime = 0;
        }

        return retTime;

    }

    /**
     * @brief     PDW 저장 여부를 리턴한다.
     * @return    int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-03-03, 13:48
     * @warning
     */
    unsigned int GetStorePDW()
    {
        unsigned int uiStorePDW = 0;

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            uiStorePDW = ( unsigned int ) x.ps.uiIsStorePDW;
        }
#if defined(_GRAPH_) || defined(_ELINT_)
        else if( g_enUnitType == en_ELINT ) {
            uiStorePDW = ( unsigned int ) x.el.uiIsStorePDW;
        }
#endif
#if defined(_GRAPH_) || defined(_XBAND_)
        else if( g_enUnitType == en_XBAND ) {
            uiStorePDW = ( unsigned int ) x.xb.uiIsStorePDW;
        }
#endif
#if defined(_GRAPH_) || defined(_SONATA_)
        else if( g_enUnitType == en_SONATA ) {
            uiStorePDW = ( unsigned int ) x.so.uiIsStorePDW;
        }
#endif
        else {

        }

        return uiStorePDW;

    }

    /**
     * @brief     대역폭을 리턴합니다. 대역폭이 없을수도 있다.
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
#if defined(_GRAPH_) || defined(_ELINT_)
        else if( g_enUnitType == en_ELINT ) {
            iBandwidth = x.el.enBandWidth;
        }
#endif
#if defined(_GRAPH_) || defined(_XBAND_)
        else if( g_enUnitType == en_XBAND ) {
            iBandwidth = x.xb.enBandWidth;
        }
#endif
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
    char *GetTaskID()
    {
        char *pTaskID;

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            pTaskID = NULL;
        }
#if defined(_GRAPH_) || defined(_ELINT_)
        else if( g_enUnitType == en_ELINT ) {
            pTaskID = x.el.aucTaskID;
        }
#endif
#if defined(_GRAPH_) || defined(_XBAND_)
        else if( g_enUnitType == en_XBAND ) {
            pTaskID = x.xb.aucTaskID;
        }
#endif
        else {
            pTaskID = NULL;
        }

        return pTaskID;
    }

    /**
     * @brief     SetTaskID
     * @param     char * pString
     * @return    void
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-09-01 16:17:37
     * @warning
     */
    void SetTaskID( char *pString )
    {

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            //strcpy(x.ps.aucTaskID, pString);
        }
#if defined(_GRAPH_) || defined(_ELINT_)
        else if( g_enUnitType == en_ELINT ) {
            strcpy( x.el.aucTaskID, pString );
        }
#endif
#if defined(_GRAPH_) || defined(_XBAND_)
        else if( g_enUnitType == en_XBAND ) {
            strcpy( x.xb.aucTaskID, pString );
        }
#endif
#if defined(_GRAPH_) || defined(_701_)
        else if( g_enUnitType == en_701 ) {
            char *pPtr;

            // 널 문자 전까지 복사해야 함.
            strncpy( x.e7.aucTaskID, pString, strlen( x.e7.aucTaskID ) - 1 );

            pPtr = strchr( x.e7.aucTaskID, ' ' );
            while( pPtr != NULL ) {

                *pPtr = '_';
                pPtr = strchr( x.e7.aucTaskID, ' ' );
            }

        }
#endif
        else {
        }
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
    int GetIndexByTOA( _TOA tPDW )
    {
        _TOA tDiff;
        int iTotalPDW;

        int iIndex = 0, iLeft = 0, iRight;

        iTotalPDW = ( int ) GetTotalPDW();
        iRight = iTotalPDW - 1;

        if( iRight >= 0 ) {
            do {
                iIndex = ( iLeft + iRight ) / 2;

                tDiff = pstPDW[iIndex].tTOA - tPDW;
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
                iIndex = ( iLeft + iRight ) / 2;
            } while( iLeft <= iRight && iRight < iTotalPDW );

            iIndex = iLeft;
        }

        return iIndex;
    }


} STR_PDWDATA;


#ifndef _STR_STATIC_PDWDATA
#define _STR_STATIC_PDWDATA
typedef struct stSTR_STATIC_PDWDATA {
    UNION_HEADER x;

    _PDW stPDW[MAX_PDW];

    unsigned int GetBand()
    {
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
    unsigned int GetTotalPDW()
    {
        unsigned int uiTotalPDW;

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            uiTotalPDW = x.ps.stCommon.uiTotalPDW;
        }
#if defined(_GRAPH_) || defined(_ELINT_)
        else if( g_enUnitType == en_ELINT || g_enUnitType == en_XBAND ) {
            uiTotalPDW = x.el.stCommon.uiTotalPDW;
        }
#endif
#if defined(_GRAPH_) || defined(_XBAND_)
        else if( g_enUnitType == en_XBAND ) {
            uiTotalPDW = x.xb.stCommon.uiTotalPDW;
        }
#endif
#if defined(_GRAPH_) || defined(_SONATA_)
        else if( g_enUnitType == en_SONATA ) {
            uiTotalPDW = x.so.stCommon.uiTotalPDW;
        }
#endif
        else {
            uiTotalPDW = 0;
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
    unsigned int GetPDWID()
    {
        unsigned int uiPDWID;

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            uiPDWID = x.ps.stCommon.uiPDWID;
        }
#if defined(_GRAPH_) || defined(_ELINT_)
        else if( g_enUnitType == en_ELINT ) {
            uiPDWID = x.el.stCommon.uiPDWID;
        }
#endif
#if defined(_GRAPH_) || defined(_XBAND_)
        else if( g_enUnitType == en_XBAND ) {
            uiPDWID = x.xb.stCommon.uiPDWID;
        }
#endif
#if defined(_GRAPH_) || defined(_SONATA_)
        else if( g_enUnitType == en_SONATA ) {
            uiPDWID = x.so.stCommon.uiPDWID;
        }
#endif
        else {
            uiPDWID = 0;
        }

        return uiPDWID;
    }

    /**
     * @brief     SetPDWID
     * @param     unsigned int uiPDWID
     * @return    void
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-02-10 16:32:41
     * @warning
     */
    void SetPDWID( unsigned int uiPDWID )
    {

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            x.ps.stCommon.uiPDWID = uiPDWID;
        }
#if defined(_GRAPH_) || defined(_ELINT_)
        else if( g_enUnitType == en_ELINT ) {
            x.el.stCommon.uiPDWID = uiPDWID;
        }
#endif
#if defined(_GRAPH_) || defined(_XBAND_)
        else if( g_enUnitType == en_XBAND ) {
            x.xb.stCommon.uiPDWID = uiPDWID;
        }
#endif
#if defined(_GRAPH_) || defined(_SONATA_)
        else if( g_enUnitType == en_SONATA ) {
            x.so.stCommon.uiPDWID = uiPDWID;
        }
#endif
        else {
        }

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
    time_t GetColTime()
    {
        time_t retTime;

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            retTime = (time_t) x.ps.stCommon.uiColTime;
        }
#if defined(_GRAPH_) || defined(_ELINT_)
        else if( g_enUnitType == en_ELINT ) {
            retTime = x.el.stCommon.uiColTime;
        }
#endif
#if defined(_GRAPH_) || defined(_XBAND_)
        else if( g_enUnitType == en_XBAND ) {
            retTime = x.el.stCommon.uiColTime;
        }
#endif
#if defined(_GRAPH_) || defined(_SONATA_)
        else if( g_enUnitType == en_SONATA ) {
            retTime = x.so.stCommon.uiColTime;
        }
#endif
        else {
            retTime = 0;
        }

        return retTime;

    }

    unsigned int GetStorePDW()
    {
        unsigned int uiStorePDW = 0;

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            uiStorePDW = ( unsigned int ) x.ps.uiIsStorePDW;
        }
#if defined(_GRAPH_) || defined(_ELINT_)
        else if( g_enUnitType == en_ELINT ) {
            uiStorePDW = ( unsigned int ) x.el.uiIsStorePDW;
        }
#endif
#if defined(_GRAPH_) || defined(_XBAND_)
        else if( g_enUnitType == en_XBAND ) {
            uiStorePDW = ( unsigned int ) x.xb.uiIsStorePDW;
        }
#endif
#if defined(_GRAPH_) || defined(_SONATA_)
        else if( g_enUnitType == en_SONATA ) {
            uiStorePDW = ( unsigned int ) x.so.uiIsStorePDW;
        }
#endif
        else {

        }

        return uiStorePDW;

    }

    int GetBandWidth()
    {
        int iBandwidth;

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            iBandwidth = ( int ) x.ps.uiBand;
        }
#if defined(_GRAPH_) || defined(_ELINT_)
        else if( g_enUnitType == en_ELINT ) {
            iBandwidth = x.el.enBandWidth;
        }
#endif
#if defined(_GRAPH_) || defined(_XBAND_)
        else if( g_enUnitType == en_XBAND ) {
            iBandwidth = x.xb.enBandWidth;
        }
#endif
        else {
            iBandwidth = 0;
        }

        return iBandwidth;
    }

    /**
     * @brief     LoadPDWData
     * @param     unsigned int uiIndex
     * @param     _PDW * o_pstPDW
     * @return    void
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-12-21 14:47:41
     * @warning
     */
    void LoadPDWData( unsigned int uiIndex, _PDW *o_pstPDW )
    {
        _PDW *pstPDWData;

        pstPDWData = & stPDW[uiIndex];

        pstPDWData->tTOA = o_pstPDW->tTOA;
        pstPDWData->uiAOA = o_pstPDW->uiAOA;
        pstPDWData->uiFreq = o_pstPDW->uiFreq;
        pstPDWData->uiPA = o_pstPDW->uiPA;
        pstPDWData->uiPW = o_pstPDW->uiPW;
        pstPDWData->uiIndex = o_pstPDW->uiIndex;
        pstPDWData->iStat = o_pstPDW->iStat;

    }


} STR_STATIC_PDWDATA;

#endif  // _STR_STATIC_PDWDATA

#endif

/**
    @struct STR_UZPOCKETPDW
    @brief
**/
typedef struct stSTR_UZPOCKETPDW {
    UNION_HEADER x;

    UZPOCKETPDW *pstPDW;


    /**
     * @brief     LoadPDWData
     * @param     unsigned int iIndex
     * @param     _PDW * o_pstPDW
     * @return    void
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-04-10 20:13:58
     * @warning
     */
    void LoadPDWData( unsigned int uiIndex, _PDW *o_pstPDW )
    {
        UZPOCKETPDW_PDWWORD *pstHwPdwDataRf = & pstPDW[uiIndex].stHwPdwDataRf;

#if defined(_POCKETSONATA_) || defined(_712_)
        memset( & o_pstPDW->x, 0, sizeof( union UNI_PDW_ETC ) );

        if( pstHwPdwDataRf->CwPulse == 0 ) {
            o_pstPDW->iStat = STAT_NORMAL;
            if( pstHwPdwDataRf->Pmop == 1 ) {
                o_pstPDW->iStat = STAT_PMOP;
                //o_pstPDW->x.ps.stStrBitMap.Pmop = 1;
            }
            if( pstHwPdwDataRf->Fmop == 1 ) {
            	//o_pstPDW->x.ps.x.stStrBitMap.Fmop = 1;
                if( pstHwPdwDataRf->FmopDir == 1 ) {
                    o_pstPDW->iStat = STAT_CHIRPUP;
                }
                else if( pstHwPdwDataRf->FmopDir == 2 ) {
                    o_pstPDW->iStat = STAT_CHIRPDN;
                    //o_pstPDW->x.ps.iFMOP = 1;
                }
                else if( pstHwPdwDataRf->FmopDir == 3 ) {
                    o_pstPDW->iStat = STAT_CHIRPUK;
                    //o_pstPDW->x.ps.iFMOP = 1;
                }
                else {
                    o_pstPDW->iStat = STAT_CHIRPTRI;
                }
                //o_pstPDW->x.ps.x.stStrBitMap.iFMOP = pstHwPdwDataRf->FmopDir;
            }
        }
        else {
            o_pstPDW->iStat = STAT_CW;
            if( pstHwPdwDataRf->Pmop == 1 ) {
                o_pstPDW->iStat = STAT_CW_PMOP;
                //o_pstPDW->x.ps.iPMOP = 1;
            }
            if( pstHwPdwDataRf->Fmop == 1 ) {
                if( pstHwPdwDataRf->FmopDir == 1 ) {
                    o_pstPDW->iStat = STAT_CW_CHIRPUP;
                    //o_pstPDW->x.ps.iFMOP = 1;
                }
                else if( pstHwPdwDataRf->FmopDir == 2 ) {
                    o_pstPDW->iStat = STAT_CW_CHIRPDN;
                    //o_pstPDW->x.ps.iFMOP = 1;
                }
                else if( pstHwPdwDataRf->FmopDir == 3 ) {
                    o_pstPDW->iStat = STAT_CW_CHIRPUK;
                    //o_pstPDW->x.ps.iFMOP = 1;
                }
                else {
                    o_pstPDW->iStat = STAT_CW_CHIRPTRI;
                }
            }
        }

        o_pstPDW->x.ps.iChannel = pstHwPdwDataRf->PpfCh;

        STR_STAT_BITMAP *pStatBitmap;
        pStatBitmap = & o_pstPDW->x.ps.x.stStrBitMap;
        pStatBitmap->CwPulse = pstHwPdwDataRf->CwPulse;
        pStatBitmap->Pmop = pstHwPdwDataRf->Pmop;
        pStatBitmap->Fmop = pstHwPdwDataRf->Fmop;
        pStatBitmap->FmopDir = pstHwPdwDataRf->FmopDir;
        pStatBitmap->DI = pstHwPdwDataRf->Di;
        pStatBitmap->FalsePdw = pstHwPdwDataRf->FalsePdw;
        pStatBitmap->Edge = pstHwPdwDataRf->Edge;
        pStatBitmap->FMOPBW = pstHwPdwDataRf->FmopBw;

#else

#endif
        o_pstPDW->tTOA = pstHwPdwDataRf->ullTOA;
        o_pstPDW->uiAOA = pstHwPdwDataRf->uiAOA;
        o_pstPDW->uiFreq = pstHwPdwDataRf->uiFreq;
        o_pstPDW->uiPA = pstHwPdwDataRf->uiPA;
        o_pstPDW->uiPW = pstHwPdwDataRf->uiPW;

        o_pstPDW->uiIndex = pstHwPdwDataRf->Index;

    }

    /**
     * @brief     SavePDWData
     * @param     unsigned int iIndex
     * @param     _PDW * i_pstPDW
     * @return    void
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-04-10 20:10:35
     * @warning
     */
    void SavePDWData( unsigned int uiIndex, _PDW *i_pstPDW )
    {
        UZPOCKETPDW *puzPDW;

        puzPDW = & pstPDW[uiIndex];
        memset( puzPDW, 0, sizeof( UZPOCKETPDW ) );

        // STAT 값 변환
        STR_STAT_BITMAP *pStatBitmap;
        pStatBitmap = & i_pstPDW->x.ps.x.stStrBitMap;
        puzPDW->stHwPdwDataRf.CwPulse = pStatBitmap->CwPulse;
        puzPDW->stHwPdwDataRf.Pmop = pStatBitmap->Pmop;
        puzPDW->stHwPdwDataRf.Fmop = pStatBitmap->Fmop;
        puzPDW->stHwPdwDataRf.FmopDir = pStatBitmap->FmopDir;
        puzPDW->stHwPdwDataRf.FmopBw = pStatBitmap->FMOPBW;
        puzPDW->stHwPdwDataRf.Di = pStatBitmap->DI;
        puzPDW->stHwPdwDataRf.Edge = pStatBitmap->Edge;
        puzPDW->stHwPdwDataRf.FalsePdw = pStatBitmap->FalsePdw;

        //puzPDW->stHwPdwDataRf.CwPulse = i_pstPDW->iStat;

        // PDW 정보
        puzPDW->stHwPdwDataRf.ullTOA = i_pstPDW->tTOA;
        puzPDW->stHwPdwDataRf.uiAOA = i_pstPDW->uiAOA;
        puzPDW->stHwPdwDataRf.uiFreq = i_pstPDW->uiFreq;
        puzPDW->stHwPdwDataRf.uiPA = i_pstPDW->uiPA;
        puzPDW->stHwPdwDataRf.uiPW = i_pstPDW->uiPW;

        puzPDW->stHwPdwDataRf.Index = i_pstPDW->uiIndex;

    }

    /**
     * @brief     SetPDWID
     * @param     unsigned int uiPDWID
     * @return    void
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-04-10 19:36:03
     * @warning
     */
    void SetPDWID( unsigned int uiPDWID )
    {

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            x.ps.stCommon.uiPDWID = uiPDWID;
        }
#if defined(_GRAPH_) || defined(_ELINT_)
        else if( g_enUnitType == en_ELINT ) {
            x.el.stCommon.uiPDWID = uiPDWID;
        }
#endif
#if defined(_GRAPH_) || defined(_XBAND_)
        else if( g_enUnitType == en_XBAND ) {
            x.xb.stCommon.uiPDWID = uiPDWID;
        }
#endif
#if defined(_GRAPH_) || defined(_SONATA_)
        else if( g_enUnitType == en_SONATA ) {
            x.so.stCommon.uiPDWID = uiPDWID;
        }
#endif

    }


    /**
     * @brief     GetTotalPDW
     * @return    unsigned int
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-04-10 19:31:28
     * @warning
     */
    unsigned int GetTotalPDW()
    {
        unsigned int uiTotalPDW;

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            uiTotalPDW = x.ps.stCommon.uiTotalPDW;
        }
#if defined(_GRAPH_) || defined(_ELINT_)
        else if( g_enUnitType == en_ELINT ) {
            uiTotalPDW = x.el.stCommon.uiTotalPDW;
        }
#endif
#if defined(_GRAPH_) || defined(_XBAND_)
        else if( g_enUnitType == en_XBAND ) {
            uiTotalPDW = x.xb.stCommon.uiTotalPDW;
        }
#endif
#if defined(_GRAPH_) || defined(_701_)
        else if( g_enUnitType == en_701 ) {
            uiTotalPDW = x.e7.stCommon.uiTotalPDW;
        }
#endif
#if defined(_GRAPH_) || defined(_SONATA_)
        else if( g_enUnitType == en_SONATA ) {
            uiTotalPDW = x.so.stCommon.uiTotalPDW;
        }
#endif
        else {
            uiTotalPDW = 0;
        }

        return uiTotalPDW;

    }


    /**
     * @brief     SetColTime
     * @param     time_t tColTime
     * @param     UINT uiColTimeMs
     * @return    void
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-04-10 19:30:54
     * @warning
     */
    void SetColTime( unsigned int uiColTime, UINT uiColTimeMs )
    {

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            x.ps.stCommon.uiColTime = uiColTime;
            x.ps.stCommon.uiColTimeMs = uiColTimeMs;
        }
#if defined(_GRAPH_) || defined(_ELINT_)
        else if( g_enUnitType == en_ELINT ) {
            x.el.stCommon.uiColTime = uiColTime;
            x.el.stCommon.uiColTimeMs = uiColTimeMs;
        }
#endif
#if defined(_GRAPH_) || defined(_XBAND_)
        else if( g_enUnitType == en_XBAND ) {
            x.xb.stCommon.uiColTime = uiColTime;
            x.xb.stCommon.uiColTimeMs = uiColTimeMs;
        }
#endif
#if defined(_GRAPH_) || defined(_SONATA_)
        else if( g_enUnitType == en_SONATA ) {
            x.so.stCommon.uiColTime = uiColTime;
            x.so.stCommon.uiColTimeMs = uiColTimeMs;
        }
#endif
        else {
        }
        return;

    }


    /**
     * @brief     SetBand
     * @param     unsigned int uiBand
     * @return    void
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-04-10 19:30:11
     * @warning
     */
    void SetBand( unsigned int uiBand )
    {

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
     * @brief     SetBoardID
     * @param     ENUM_UnitType enUnitType
     * @param     unsigned int uiBoardID
     * @return    void
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-04-10 19:28:29
     * @warning
     */
    void SetBoardID( ENUM_BoardID enBoardID )
    {

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            x.ps.uiBoardID = ( unsigned int ) enBoardID;
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
     * @brief     SetTotalPDW
     * @param     unsigned int uiTotalPDW
     * @return    void
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-04-10 19:28:32
     * @warning
     */
    void SetTotalPDW( unsigned int uiTotalPDW )
    {
        if( g_enUnitType == en_ZPOCKETSONATA ) {
            x.ps.stCommon.uiTotalPDW = uiTotalPDW;
        }
#if defined(_GRAPH_) || defined(_ELINT_)
        else if( g_enUnitType == en_ELINT ) {
            x.el.stCommon.uiTotalPDW = uiTotalPDW;
        }
#endif
#if defined(_GRAPH_) || defined(_XBAND_)
        else if( g_enUnitType == en_XBAND ) {
            x.xb.stCommon.uiTotalPDW = uiTotalPDW;
        }
#endif
#if defined(_GRAPH_) || defined(_701_)
        else if( g_enUnitType == en_701 ) {
            x.e7.stCommon.uiTotalPDW = uiTotalPDW;
        }
#endif
#if defined(_GRAPH_) || defined(_SONATA_)
        else if( g_enUnitType == en_SONATA ) {
            x.so.stCommon.uiTotalPDW = uiTotalPDW;
        }
#endif
        else {
        }

        return;

    }

    /**
     * @brief     SetCollectBank
     * @param     ENUM_COLLECTBANK enBank
     * @return    void
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-04-10 19:28:34
     * @warning
     */
    void SetCollectBank( ENUM_COLLECTBANK enBank )
    {

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            x.ps.enCollectBank = enBank;
        }
        else {

        }

        return;

    }

    unsigned int GetColDuration()
    {
        unsigned uiTOA=0;
        unsigned int uiColPDW = GetTotalPDW();

        if( uiColPDW >= 1 ) {
            uiTOA = (unsigned int) ( pstPDW[uiColPDW-1].stHwPdwDataRf.ullTOA - pstPDW[0].stHwPdwDataRf.ullTOA );
        }

        return uiTOA;
    }

} STR_UZPOCKETPDW;

#if defined(_POCKETSONATA_) || defined(_712_)
// 하드웨어 PDW 맵에 저장한다.
typedef DMAPDW SIGAPDW;
//typedef STR_PDWDATA SIGAPDW;

#elif defined(_ELINT_) || defined(_XBAND_) || defined(_701_)
typedef _PDW SIGAPDW;
//typedef STR_PDWDATA SIGAPDW;

#elif defined(_SONATA_)
typedef STR_PDWDATA SIGAPDW;

#else
typedef DMAPDW SIGAPDW;

#endif


#ifndef _STR_ELINT_HEADER2_
#define _STR_ELINT_HEADER2_
struct STR_ELINT_HEADER2 {
    char aucTaskID[LENGTH_OF_TASK_ID];
    unsigned int uiIsStorePDW;
    EN_RADARCOLLECTORID enCollectorID;
    ELINT::ENUM_BANDWIDTH enBandWidth;

    // 아래는 공용 정보
    STR_COMMON_HEADER stCommon;

#ifdef _MSC_VER
//     STR_ELINT_HEADER2::STR_ELINT_HEADER2()
//     {
//
//     };
#endif

    EN_RADARCOLLECTORID GetCollectorID()
    {
        return enCollectorID;
    };


};
#endif


