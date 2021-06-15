
#include "stdafx.h"

#ifdef _MSC_VER
#include <sys/timeb.h>
#endif


#include "ccommonutils.h"

#include "../System/csysconfig.h"

#include "../Anal/Collect/DataFile/DataFile.h"

#include "../Utils/csingleserver.h"
#include "../Utils/csingleclient.h"
#include "../Utils/cmultiserver.h"

extern CMultiServer *g_pTheZYNQSocket;
extern CSingleClient *g_pTheCCUSocket;
extern CSingleClient *g_pThePMCSocket;

/**
 * @brief 생성자를 수행합니다.
 */
CCommonUtils::CCommonUtils()
{

}

/**
 * @brief opcode, data 를 입력받아서 랜으로 송신한다.
 * @param uiOpCode
 * @param uiLength
 * @param pData
 */
void CCommonUtils::SendLan( UINT uiOpCode, void *pData, UINT uiLength )
{
#ifndef _CGI_LIST_
    // 마스터 보드에서는 랜 메시지를 CCU 장치로 전송한다.
    if( g_enBoardId == enMaster ) {
        if( g_pTheCCUSocket != NULL ) {
            g_pTheCCUSocket->SendLan( uiOpCode, pData, uiLength );

        }

        // EA 경우에 AET 관련 메세지를 전달한다.
        if( g_pThePMCSocket != NULL && ( uiOpCode == esAET_NEW_CCU || uiOpCode == esAET_UPD_CCU || uiOpCode == esAET_DEL_CCU ) ) {

        }

    }
    // 클라이언트 보드 인 경우에는 랜 메시지를 마스터 보드에 전달한다.
    else {
        if( g_pTheZYNQSocket != NULL ) {
            //g_pTheZYNQSocket->SendLan( uiOpCode, pData, uiLength );
        }
        else {

        }
    }
#endif

}

/**
 * @brief CCommonUtils::CloseSocket
 */
void CCommonUtils::CloseSocket()
{
#ifndef _CGI_LIST_
    if( g_enBoardId == enMaster ) {
        if( g_pTheCCUSocket != NULL ) {
            g_pTheCCUSocket->CloseSocket();
        }

    }
    else {

    }
#endif

}

/**
 * @brief CCommonUtils::IsValid
 * @param pMsg
 * @return
 */
bool CCommonUtils::IsValidLanData( STR_MessageData *pMsg )
{
    bool bRet=true;

#ifndef _CGI_LIST_
    ENUM_MODE enMode, enModeOfMessage;

    enMode = GP_SYSCFG->GetMode();
    switch( pMsg->uiOpCode ) {
        case enREQ_MODE :
            enModeOfMessage = (ENUM_MODE) pMsg->x.szData[0];

            if( enMode == enREADY_MODE && enMode == enModeOfMessage  ) {
                // bRet = false;
            }
            break;
        case enREQ_ANAL_START :
            if( enMode == enES_MODE || enMode == enEW_MODE  ) {
            }
            else {
                bRet = false;
            }
            break;

        case enREQ_IBIT :
        case enREQ_UBIT :
//             if( enMode == enES_MODE || enMode == enEW_MODE  ) {
//                 
//             }
//             else {
//                 bRet = false;
//             }
            bRet = true;
            break;

        case enREQ_CBIT :
            break;

        case enREQ_SBIT :
            if( enMode == enES_MODE || enMode == enEW_MODE  ) {
            }
            else {
                bRet = false;
            }
            break;

        case enREQ_SIM_PDWDATA :
            if( enMode == enREADY_MODE ) {
                bRet = false;
            }
            break;

        case enREQ_IPL_START :
        case enREQ_IPL_DOWNLOAD :
        case enREQ_IPL_END :
            if( enMode == enES_MODE || enMode == enEW_MODE || enMode == enREADY_MODE ) {
            }
            else {
                //bRet = false;
            }
            break;

        case enREQ_RELOAD_LIBRARY :
        case enREQ_IPL_VERSION :
            break;

        case enREQ_INIT :
        case enREQ_SET_CONFIG :
        case enREQ_STOP :
            break;

        default:
            break;

    }
#endif

    return bRet;
}

#ifdef _MSC_VER
LARGE_INTEGER getFILETIMEoffset()
{
    SYSTEMTIME s;
    FILETIME f;
    LARGE_INTEGER t;

    s.wYear = 1970;
    s.wMonth = 1;
    s.wDay = 1;
    s.wHour = 0;
    s.wMinute = 0;
    s.wSecond = 0;
    s.wMilliseconds = 0;
    SystemTimeToFileTime(&s, &f);
    t.QuadPart = f.dwHighDateTime;
    t.QuadPart <<= 32;
    t.QuadPart |= f.dwLowDateTime;
    return (t);
}

int clock_gettime(int X, struct timeval *tv)
{
    LARGE_INTEGER           t;
    FILETIME            f;
    double                  microseconds;
    static LARGE_INTEGER    offset;
    static double           frequencyToMicroseconds;
    static int              initialized = 0;
    static BOOL             usePerformanceCounter = 0;

    if (!initialized) {
        LARGE_INTEGER performanceFrequency;
        initialized = 1;
        usePerformanceCounter = QueryPerformanceFrequency(&performanceFrequency);
        if (usePerformanceCounter) {
            QueryPerformanceCounter(&offset);
            frequencyToMicroseconds = (double)performanceFrequency.QuadPart / 1000000.;
        } else {
            offset = getFILETIMEoffset();
            frequencyToMicroseconds = 10.;
        }
    }
    if (usePerformanceCounter) QueryPerformanceCounter(&t);
    else {
        GetSystemTimeAsFileTime(&f);
        t.QuadPart = f.dwHighDateTime;
        t.QuadPart <<= 32;
        t.QuadPart |= f.dwLowDateTime;
    }

    t.QuadPart -= offset.QuadPart;
    microseconds = (double)t.QuadPart / frequencyToMicroseconds;
    t.QuadPart = microseconds;
    tv->tv_sec = t.QuadPart / 1000000;
    tv->tv_usec = t.QuadPart % 1000000;
    return (0);
} 
#endif

/**
 * @brief CCommonUtils::timespec_diff
 * @param result
 * @param start
 * @param stop
 */
void CCommonUtils::DiffTimespec(struct timespec *result, struct timespec *start, struct timespec *stop )
{
    struct timespec tsNow;

    if( stop != NULL ) {
        tsNow.tv_sec = stop->tv_sec;
#ifdef _MSC_VER
        tsNow.tv_usec = stop->tv_usec;
#else
        tsNow.tv_nsec = stop->tv_nsec;
#endif
    }
    else {
        clock_gettime( CLOCK_REALTIME, & tsNow );
    }



#ifdef _MSC_VER
    if ((tsNow.tv_usec - start->tv_usec) < 0) {
        result->tv_sec = tsNow.tv_sec - start->tv_sec - 1;
        result->tv_usec = tsNow.tv_usec - start->tv_usec + 1000000;
    } else {
        result->tv_sec = tsNow.tv_sec - start->tv_sec;
        result->tv_usec = tsNow.tv_usec - start->tv_usec;
    }
#else
    if ((tsNow.tv_nsec - start->tv_nsec) < 0) {
        result->tv_sec = tsNow.tv_sec - start->tv_sec - 1;
        result->tv_nsec = tsNow.tv_nsec - start->tv_nsec + 1000000000;
    } else {
        result->tv_sec = tsNow.tv_sec - start->tv_sec;
        result->tv_nsec = tsNow.tv_nsec - start->tv_nsec;
    }

#endif

    return;
}

/**
 * @brief CCommonUtils::AllSwapData32
 * @param pData
 * @param iLength
 */
void CCommonUtils::AllSwapData32( void *pData, int iLength )
{
    int i;
    UINT *pWord;

    pWord = (UINT *) pData;
    for( i=0 ; i < iLength ; i+=sizeof(int) ) {
        swapByteOrder( *pWord );
        ++ pWord;
    }

}

/**
 * @brief CCommonUtils::swapByteOrder
 * @param ull
 */
void CCommonUtils::swapByteOrder(unsigned int& ui)
{
    ui = (ui >> 24) |
        ((ui<<8) & 0x00FF0000) |
        ((ui>>8) & 0x0000FF00) |
        (ui << 24);
}

/**
 * @brief CCommonUtils::GetStringBand
 * @param pBuffer
 * @param iBand
 */
void CCommonUtils::GetStringBand( char *pBuffer, int iBand )
{
    pBuffer[0] = 0;
    if( iBand & 0x02 ) {
        strcat( pBuffer, "1, " );
    }
    if( iBand & 0x01 ) {
        strcat( pBuffer, "2, " );
    }
    if( iBand & 0x02 ) {
        strcat( pBuffer, "3, " );
    }
    if( iBand & 0x04 ) {
        strcat( pBuffer, "4, " );
    }
    if( iBand & 0x08 ) {
        strcat( pBuffer, "5, " );
    }
    if( iBand & 0x10 ) {
        strcat( pBuffer, "6, " );
    }
    pBuffer[ strlen(pBuffer)-2 ] = 0;

}

/**
 * @brief CCommonUtils::Disp_FinePDW
 * @param pPDWData
 */
void CCommonUtils::Disp_FinePDW( STR_PDWDATA *pPDWData )
{

#ifdef __ZYNQ_BOARD__
    return;
#else
    unsigned int i;
    _PDW *pPDW;
    _TOA ullfirstTOA;

    pPDW = & pPDWData->stPDW[0];
    ullfirstTOA = pPDW->ullTOA;
    for( i=0 ; i < pPDWData->uiTotalPDW ; ++i ) {
        printf( "[%4d]\t%012llX(%.1f[us]) %5.1f %.3fMHz[0x%X] %.3fns[0x%X] \n" , i+1, \
                pPDW->ullTOA, CPOCKETSONATAPDW::DecodeTOAus( pPDW->ullTOA-ullfirstTOA ), \
                CPOCKETSONATAPDW::DecodeDOA(pPDW->iAOA), \
                CPOCKETSONATAPDW::DecodeFREQMHz(pPDW->iFreq), pPDW->iFreq,
                CPOCKETSONATAPDW::DecodePW(pPDW->iPW), pPDW->iPW );

        ++ pPDW;
    }

    return;

#endif

}

/**
 * @brief CCommonUtils::GetEnumCollectBank
 * @param uiCh
 * @return
 */
ENUM_COLLECTBANK CCommonUtils::GetEnumCollectBank( unsigned int uiCh )
{
    ENUM_COLLECTBANK enCollectBank=enUnknownCollectBank;

    if( uiCh < DETECT_CHANNEL )
        enCollectBank = enDetectCollectBank;
    else if( uiCh < DETECT_CHANNEL+TRACK_CHANNEL )
        enCollectBank = enTrackCollectBank;
    else if( uiCh < DETECT_CHANNEL+TRACK_CHANNEL+SCAN_CHANNEL )
        enCollectBank = enScanCollectBank;
    else
        enCollectBank = enUserCollectBank;

    return enCollectBank;
}
