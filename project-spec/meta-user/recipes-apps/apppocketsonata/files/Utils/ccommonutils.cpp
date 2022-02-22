
#include "stdafx.h"

#ifdef _MSC_VER

#include <io.h>
#include <direct.h>
#include <sys/timeb.h>


#include <stdint.h>

#include <sys/utime.h>

#include <fcntl.h>
#else
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>

#endif


#include "ccommonutils.h"

#ifndef _GRAPH_
#include "../System/csysconfig.h"

#include "../Anal/SigAnal/_Type.h"
#include "../Anal/Collect/DataFile/DataFile.h"

#include "../Include/globals.h"

extern CMultiServer *g_pTheZYNQSocket;
extern CSingleClient *g_pTheCCUSocket;
extern CSingleClient *g_pThePMCSocket;

#endif

/**
 * @brief 생성자를 수행합니다.
 */
CCommonUtils::CCommonUtils()
{

}

#ifndef _GRAPH_

/**
 * @brief opcode, data 를 입력받아서 랜으로 송신한다.
 * @param uiOpCode
 * @param uiLength
 * @param pData
 */
void CCommonUtils::SendLan( UINT uiOpCode, void *pData, UINT uiLength )
{
#if defined(_ELINT_) || defined(_XBAND_)

#elif _POCKETSONATA_
#ifndef _CGI_LIST_
    // 마스터 보드에서는 랜 메시지를 CCU 장치로 전송한다.
    if( g_enBoardId == enMaster ) {
        if( g_pTheCCUSocket != NULL ) {
            g_pTheCCUSocket->SendLan( uiOpCode, pData, uiLength );

        }

        // EA 경우에 AET 관련 메세지를 전달한다.
        if( g_pThePMCSocket != NULL ) { //&& ( uiOpCode == esAET_NEW_CCU || uiOpCode == esAET_UPD_CCU || uiOpCode == esAET_DEL_CCU ) ) {
            g_pThePMCSocket->SendLan( uiOpCode, pData, uiLength );
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
#endif

}

/**
 * @brief CCommonUtils::CloseSocket
 */
void CCommonUtils::CloseSocket()
{
#if defined(_ELINT_) || defined(_XBAND_)

#elif _POCKETSONATA_
#ifndef _CGI_LIST_
    if( g_enBoardId == enMaster ) {
        if( g_pTheCCUSocket != NULL ) {
            g_pTheCCUSocket->CloseSocket();
        }

    }
    else {

    }
#endif
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

    enMode = g_pTheSysConfig->GetMode();
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
            if( enMode == enES_MODE || enMode == enEW_MODE || enMode == enREADY_MODE ) {
            }
            else {
                bRet = false;
            }
            break;

        case enREQ_IPL_VERSION :
            break;

        case enREQ_SYS :
            break;

        case enREQ_INIT :
        case enREQ_SET_CONFIG :
        case enREQ_STOP :
            break;

        case enSYSERROR :
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

int gettimeofday(struct timeval * tp, struct timezone * tzp)
{
    // Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
    // This magic number is the number of 100 nanosecond intervals since January 1, 1601 (UTC)
    // until 00:00:00 January 1, 1970 
    static const uint64_t EPOCH = ((uint64_t) 116444736000000000ULL);

    SYSTEMTIME  system_time;
    FILETIME    file_time;
    uint64_t    time;

    GetSystemTime( &system_time );
    SystemTimeToFileTime( &system_time, &file_time );
    time =  ((uint64_t)file_time.dwLowDateTime )      ;
    time += ((uint64_t)file_time.dwHighDateTime) << 32;

    tp->tv_sec  = (long) ((time - EPOCH) / 10000000L);
    tp->tv_usec = (long) (system_time.wMilliseconds * 1000);
    return 0;

}

/**
 * @brief     clock_gettime
 * @param     int X
 * @param     struct timeval * tv
 * @return    int
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-02-09, 17:34
 * @warning
 */
int clock_gettime(int X, struct timeval *tv)
{
    gettimeofday( tv, NULL );

    return (0);
} 




/**
 * @brief     getStringPresentTime
 * @param     char * pString
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-06-30, 17:27
 * @warning
 */
void CCommonUtils::getStringPresentTime( char *pString ) 
{
    struct tm *pstTime;
    time_t nowTime=time(NULL);

    pstTime = localtime( & nowTime );
    if( pstTime != NULL ) {
        strftime( pString, 100, "%Y-%m-%d %H:%M:%S", pstTime );
    }
    else {
        strcpy( pString, "1970-01-01 00:00:00" );
    }
}

/**
 * @brief     CopyFile
 * @param     const char * src_file
 * @param     const char * dest_file
 * @param     int overwrite
 * @param     int copy_attr
 * @return    int
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-06-30, 17:27
 * @warning
 */
int CCommonUtils::CopyFile( const char *src_file, const char *dest_file, int overwrite, int copy_attr )
{
    int iRet=-1;
    int     src_fd;
    int     dest_fd;
    struct  stat sts;
    char    data_buf[4096];
    int     tmp_errno;
    int     size;

#if defined(__linux__) || defined(__VXWORKS__)
    src_fd = open(src_file, O_RDONLY | O_BINARY, 0644 );
#else
    src_fd = open(src_file, O_RDONLY | O_BINARY );
    
#endif
    
    if( src_fd != -1) {
        memset( & sts, 0, sizeof(sts) );

        /* 원본 file의 속성을 읽습니다. */
        fstat(src_fd, &sts);

        if(overwrite) { /* 이미 파일이 있으면 overwrite를 하겠다면... */
            dest_fd = open(dest_file, O_WRONLY | O_CREAT | O_TRUNC | O_BINARY, sts.st_mode);
        } else {        /* 파일이 있으면, 생성하지 말라고 설정한 경우 */
            dest_fd = open(dest_file, O_WRONLY | O_CREAT | O_EXCL | O_BINARY , sts.st_mode);
        }

        if(dest_fd == -1) {
            tmp_errno = errno; 
            close(src_fd);  
            errno = tmp_errno; // close가 초기화한 errno를 복구함
            return -1;
        }

        do { // while( size = read(src_fd, data_buf, 4096) ) {
            size = read(src_fd, data_buf, 4096);
            if( size <= 0 ) {
                break;
            }

//             if(size == -1) {
//                 if(errno == EINTR) {
//                     continue;
//                 }
//                 tmp_errno = errno;
//                 close(src_fd);
//                 close(dest_fd);
//                 errno = tmp_errno; // close가 초기화한 errno를 복구함
//                 return -1;
//             }

            while(write(dest_fd, data_buf, size) == -1) {
                if(errno == EINTR) {
                    /* signal이 발생한 경우에는 재작업 */
                    continue;
                } else {
                    /* disk가 full났거나 무슨 일이 있음. */
                    tmp_errno = errno;
                    close(src_fd);
                    close(dest_fd);
                    errno = tmp_errno;
                }
            }
        }
        while( true );

        close(src_fd);
        close(dest_fd);
    
        /* 원본 파일의 속성을 복원해야 한다면... */
        if(copy_attr) {
            /* 원본 파일의 파일 권한을 복원하기 
            * open시에 파일권한을 설정하였지만, 
            * 이미 존재했던 파일은 파일권한이 기존 파일의 권한이므로
            * 파일의 권한도 복구합니다.
            */
            chmod(dest_file, sts.st_mode);

#ifdef __VXWORKS__        		
  
#elif __linux__

#else 		
        	struct  utimbuf attr;
    			
            /* last access 시간, last modify 시간 복구 */
            attr.actime  = sts.st_atime;
            attr.modtime = sts.st_mtime;
            utime(dest_file, &attr);            
#endif            
        
        }
    }

    return 0;
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

    pPDW = & pPDWData->pstPDW[0];
    ullfirstTOA = pPDW->ullTOA;

#ifdef _POCKETSONATA_
    for( i=0 ; i < pPDWData->GetTotalPDW() ; ++i ) {
        printf( "[%4d]\t%012llX(%.1f[us]) %5.1f %.3fMHz[0x%X] %.3fns[0x%X] \n" , i+1, \
                pPDW->ullTOA, CPOCKETSONATAPDW::DecodeTOAus( pPDW->ullTOA-ullfirstTOA ), \
                CPOCKETSONATAPDW::DecodeDOA(pPDW->uiAOA), \
                CPOCKETSONATAPDW::DecodeFREQMHz(pPDW->uiFreq), pPDW->uiFreq,
                CPOCKETSONATAPDW::DecodePW(pPDW->uiPW), pPDW->uiPW );
        ++ pPDW;
    }
#elif defined(_ELINT_) || defined(_XBAND_)
    for( i=0 ; i < pPDWData->GetTotalPDW() ; ++i ) {
        printf( "[%4d]\t%012llX(%.1f[us]) %5.1f %.3fMHz[0x%X] %.3fns[0x%X] \n" , i+1, \
            pPDW->ullTOA, CEPDW::DecodeTOAus( pPDW->ullTOA-ullfirstTOA, pPDWData->x.el.enBandWidth ), \
            CEPDW::DecodeDOA(pPDW->uiAOA), \
            CEPDW::DecodeFREQMHz(pPDW->uiFreq), pPDW->uiFreq,
            CEPDW::DecodePW(pPDW->uiPW, pPDWData->x.el.enBandWidth ), pPDW->uiPW );
        ++ pPDW;
    }

#endif

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

#endif	// _GRAPH_

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
 * @brief		swapByteOrder
 * @param		unsigned short & us
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2021/11/18 19:16:45
 * @warning		
 */
void CCommonUtils::swapByteOrder(unsigned short& us)
{
    us = (us >> 8) | ((us<<8) & 0xFF00);
}

/**
 * @brief CCommonUtils::swapByteOrder
 * @param ull
 */
void CCommonUtils::swapByteOrder(unsigned int& ui)
{
    ui = (ui >> 24) | ((ui<<8) & 0x00FF0000) | ((ui>>8) & 0x0000FF00) | (ui << 24);
}

/**
 * @brief		swapByteOrder
 * @param		double & di
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2021/11/18 19:06:02
 * @warning		
 */
void CCommonUtils::swapByteOrder(double & d)
{
    uint64_t um = (uint64_t) & d;
    
    d = (double) ( ( ( um & 0xff00000000000000 ) >> 56 ) |
                   ( ( um & 0x00ff000000000000 ) >> 40 ) |
                   ( ( um & 0x0000ff0000000000 ) >> 24 ) |
                   ( ( um & 0x000000ff00000000 ) >> 8 ) |
                   ( ( um & 0x00000000ff000000 ) << 8 ) |
                   ( ( um & 0x0000000000ff0000 ) << 24 ) |
                   ( ( um & 0x000000000000ff00 ) << 40 ) |
                   ( ( um & 0x00000000000000ff ) << 56 ) );
}

/**
 * @brief     swapByteOrder
 * @param     double * p
 * @param     int iSize
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-01-10, 13:49
 * @warning
 */
void CCommonUtils::swapByteOrder(double *p, int iSize )
{
    int i;

    for( i=0 ; i < iSize ; ++i ) {
        swapByteOrder( p[i] );
    }
}


/**
 * @brief     SetUnitType
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-02-22, 13:18
 * @warning
 */
void CCommonUtils::SetUnitType()
{
#ifdef _POCKETSONATA_
    g_enUnitType = en_ZPOCKETSONATA;
#elif defined(_ELINT_)
    g_enUnitType = en_ELINT;
#elif defined(_XBAND_)
    g_enUnitType = en_XBAND;
#else
    g_enUnitType = en_UnknownUnit;

#endif
}