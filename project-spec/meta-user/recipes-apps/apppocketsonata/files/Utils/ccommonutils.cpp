
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

#endif


#include "ccommonutils.h"

#include "../System/csysconfig.h"

#include "../Anal/SigAnal/_Type.h"
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

int clock_gettime(int X, struct timeval *tv)
{
    gettimeofday( tv, NULL );

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

void CCommonUtils::getStringPresentTime( char *pString ) 
{
    struct tm *pstTime;
    time_t nowTime=time(NULL);

    pstTime = localtime( & nowTime );
    strftime( pString, 100, "%Y-%m-%d %H:%M:%S", pstTime );
}

int CCommonUtils::CopyFile( const char *src_file, const char *dest_file, int overwrite, int copy_attr )
{
    int iRet=-1;
    int     src_fd;
    int     dest_fd;
    struct  stat sts;
    char    data_buf[4096];
    int     tmp_errno;
    int     size;
    struct  utimbuf attr;

    if((src_fd = _open(src_file, O_RDONLY | O_BINARY )) != -1) {

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

        while(size = read(src_fd, data_buf, 4096)) {
            if(size == -1) {
                if(errno == EINTR) {
                    continue;
                }
                tmp_errno = errno;
                close(src_fd);
                close(dest_fd);
                errno = tmp_errno; // close가 초기화한 errno를 복구함
                return -1;
            }

            while(write(dest_fd, data_buf, size) == -1) {
                if(errno == EINTR) {
                    /* signal이 발생한 경우에는 재작업 */
                    continue;
                } else {
                    /* disk가 full났거나 무슨 일이 있음. */
                    tmp_errno = errno;
                    close(src_fd);
                    close(dest_fd);
                    errno = tmp_errno; // close가 초기화한 errno를 복구함
                }
            }
        }
        close(src_fd);
        close(dest_fd);
    
        /* 원본 파일의 속성을 복원해야 한다면... */
        if(copy_attr) {
            /* last access 시간, last modify 시간 복구 */
            attr.actime  = sts.st_atime;
            attr.modtime = sts.st_mtime;
            utime(dest_file, &attr);  
        
            /* 원본 파일의 파일 권한을 복원하기 
            * open시에 파일권한을 설정하였지만, 
            * 이미 존재했던 파일은 파일권한이 기존 파일의 권한이므로
            * 파일의 권한도 복구합니다.
            */
            chmod(dest_file, sts.st_mode);
        }
    }

    return 0;
}
