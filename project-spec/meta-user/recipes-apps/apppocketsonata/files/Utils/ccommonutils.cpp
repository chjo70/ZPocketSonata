
#include "stdafx.h"

#ifdef _MSC_VER

#include <io.h>
#include <direct.h>
#include <sys/timeb.h>

#include <limits.h>


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
 * @brief ?앹꽦?먮? ?섑뻾?⑸땲??
 */
CCommonUtils::CCommonUtils()
{

}

#ifndef _GRAPH_

/**
 * @brief opcode, data 瑜??낅젰諛쏆븘???쒖쑝濡??≪떊?쒕떎.
 * @param uiOpCode
 * @param uiLength
 * @param pData
 */
void CCommonUtils::SendLan( UINT uiOpCode, void *pData, UINT uiLength )
{
#if defined(_ELINT_) || defined(_XBAND_)

#elif _POCKETSONATA_
#ifndef _CGI_LIST_
    // 留덉뒪??蹂대뱶?먯꽌????硫붿떆吏瑜?CCU ?μ튂濡??꾩넚?쒕떎.
    if( g_enBoardId == enMaster ) {
        if( g_pTheCCUSocket != NULL ) {
            g_pTheCCUSocket->SendLan( uiOpCode, pData, uiLength );

        }

        // EA 寃쎌슦??AET 愿??硫붿꽭吏瑜??꾨떖?쒕떎.
        if( g_pThePMCSocket != NULL ) { //&& ( uiOpCode == esAET_NEW_CCU || uiOpCode == esAET_UPD_CCU || uiOpCode == esAET_DEL_CCU ) ) {
            g_pThePMCSocket->SendLan( uiOpCode, pData, uiLength );
        }

    }
    // ?대씪?댁뼵??蹂대뱶 ??寃쎌슦?먮뒗 ??硫붿떆吏瑜?留덉뒪??蹂대뱶???꾨떖?쒕떎.
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

/**
 * @brief     gettimeofday
 * @param     struct timeval * tp
 * @param     struct timezone * tzp
 * @return    int
 * @exception
 * @author    議곗쿋??(churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-05, 14:51
 * @warning
 */
int gettimeofday(struct timeval * tp, struct timezone * tzp)
{
    // Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
    // This magic number is the number of 100 nanosecond intervals since January 1, 1601 (UTC)
    // until 00:00:00 January 1, 1970 
    static const uint64_t EPOCH = ((uint64_t) 116444736000000000ULL);

    SYSTEMTIME  system_time;
    FILETIME    file_time;
    uint64_t    uiTime;

    GetSystemTime( &system_time );
    SystemTimeToFileTime( &system_time, &file_time );
    uiTime =  ((uint64_t)file_time.dwLowDateTime )      ;
    uiTime += ((uint64_t)file_time.dwHighDateTime) << 32;

    tp->tv_sec  = (long) ((uiTime - EPOCH) / 10000000L);
    tp->tv_usec = (long) (system_time.wMilliseconds * 1000);
    return 0;

}

/**
 * @brief     clock_gettime
 * @param     int X
 * @param     struct timeval * tv
 * @return    int
 * @exception
 * @author    議곗쿋??(churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-02-09, 17:34
 * @warning
 */
int clock_gettime(int X, struct timeval *tv)
{
    gettimeofday( tv, NULL );

    return (0);
} 




#endif

/**
 * @brief     getStringPresentTime
 * @param     char * pString
 * @return    void
 * @exception
 * @author    議곗쿋??(churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-06-30, 17:27
 * @warning
 */
void CCommonUtils::getStringPresentTime( char *pString, size_t szString ) 
{
    struct tm *pstTime;
    time_t nowTime=time(NULL);

    pstTime = localtime( & nowTime );
    strftime(pString, szString, "%Y-%m-%d %H:%M:%S", pstTime);
//     if( pstTime != NULL ) {
//         strftime( pString, szString, "%Y-%m-%d %H:%M:%S", pstTime );
//     }
//     else {
//         strcpy_s( pString, szString, "1970-01-01 00:00:00" );
//     }

}

/**
 * @brief     getStringDesignatedTime
 * @param     char * pString
 * @param     size_t szString
 * @param     __time32_t tiTime
 * @return    void
 * @exception
 * @author    議곗쿋??(churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-05, 11:09
 * @warning
 */
void CCommonUtils::getStringDesignatedTime( char *pString, size_t szString, __time32_t tiTime ) 
{
    struct tm *pstTime;

#ifdef _MSC_VER    
    strcpy_s( pString, szString, "1970-01-01 00:00:00" );
#else
    strcpy( pString, "1970-01-01 00:00:00" );    
#endif

    pstTime = localtime( & tiTime );
    strftime(pString, szString, "%Y-%m-%d %H:%M:%S", pstTime);

}

/**
 * @brief     GetCollectTime
 * @param     struct timespec * pTimeSpec
 * @param     __time32_t tColTime
 * @param     unsigned int m_tColTimeMs
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-18, 11:36
 * @warning
 */
void CCommonUtils::GetCollectTime(struct timespec *pTimeSpec, __time32_t tColTime, unsigned int tColTimeMs )
{
    if (tColTime == 0) {
        clock_gettime(CLOCK_REALTIME, pTimeSpec);
    }
    else {
        pTimeSpec->tv_sec = tColTime;
#ifdef _MSC_VER
        pTimeSpec->tv_usec = tColTimeMs * 1000;
#else
        pTimeSpec->tv_nsec = tColTimeMs * 1000000;
#endif

    }

    return;

}

void CCommonUtils::GetCollectTime( struct timeval *pTimeSpec )
{
    clock_gettime( CLOCK_REALTIME, pTimeSpec );

    return;

}

/**
 * @brief     CopyFile
 * @param     const char * src_file
 * @param     const char * dest_file
 * @param     int overwrite
 * @param     int copy_attr
 * @return    int
 * @exception
 * @author    議곗쿋??(churlhee.jo@lignex1.com)
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
    int iSize;

#if defined(__linux__) || defined(__VXWORKS__)
    src_fd = open(src_file, O_RDONLY | O_BINARY, 0644 );
#else
    src_fd = open(src_file, O_RDONLY | O_BINARY );
    
#endif
    
    if( src_fd != -1) {
        memset( & sts, 0, sizeof(sts) );

        /* ?먮낯 file???띿꽦???쎌뒿?덈떎. */
        fstat(src_fd, &sts);

        if(overwrite) { /* ?대? ?뚯씪???덉쑝硫?overwrite瑜??섍쿋?ㅻ㈃... */
            dest_fd = open(dest_file, O_WRONLY | O_CREAT | O_TRUNC | O_BINARY, sts.st_mode);
        } else {        /* ?뚯씪???덉쑝硫? ?앹꽦?섏? 留먮씪怨??ㅼ젙??寃쎌슦 */
            dest_fd = open(dest_file, O_WRONLY | O_CREAT | O_EXCL | O_BINARY , sts.st_mode);
        }

        if(dest_fd == -1) {
            tmp_errno = errno; 
            _close(src_fd);  
            errno = tmp_errno; // close媛 珥덇린?뷀븳 errno瑜?蹂듦뎄??
            WhereIs;
            //return -1;
        }
        else {
            do {
                iSize = read(src_fd, data_buf, 4096);
                if( iSize <= 0 ) {
                    break;
                }
                iRet += iSize;

                while(write(dest_fd, data_buf, (unsigned int) iSize ) == -1) {
                    if(errno == EINTR) {
                        /* signal??諛쒖깮??寃쎌슦?먮뒗 ?ъ옉??*/
                        continue;
                    } else {
                        /* disk媛 full?ш굅??臾댁뒯 ?쇱씠 ?덉쓬. */
                        tmp_errno = errno;
                        _close(src_fd);
                        _close(dest_fd);
                        errno = tmp_errno;
                    }
                }
            }
            while( true );

            _close(src_fd);
            _close(dest_fd);
        }
    
        /* ?먮낯 ?뚯씪???띿꽦??蹂듭썝?댁빞 ?쒕떎硫?.. */
        if(copy_attr && dest_fd != -1 ) {
            /* ?먮낯 ?뚯씪???뚯씪 沅뚰븳??蹂듭썝?섍린 
            * open?쒖뿉 ?뚯씪沅뚰븳???ㅼ젙?섏?吏留? 
            * ?대? 議댁옱?덈뜕 ?뚯씪? ?뚯씪沅뚰븳??湲곗〈 ?뚯씪??沅뚰븳?대?濡?
            * ?뚯씪??沅뚰븳??蹂듦뎄?⑸땲??
            */
            chmod(dest_file, sts.st_mode);

#ifdef __VXWORKS__        		
  
#elif __linux__

#else 		
        	struct  utimbuf attr;
    			
            /* last access ?쒓컙, last modify ?쒓컙 蹂듦뎄 */
            attr.actime  = sts.st_atime;
            attr.modtime = sts.st_mtime;
            utime(dest_file, &attr);            
#endif            
        
        }
    }

    return iRet;
}

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
                CPOCKETSONATAPDW::DecodeDOA( (int) pPDW->uiAOA), \
                CPOCKETSONATAPDW::DecodeFREQMHz( (int) pPDW->uiFreq), pPDW->uiFreq,
                CPOCKETSONATAPDW::DecodePW( (int) pPDW->uiPW), pPDW->uiPW );
        ++ pPDW;
    }
#elif defined(_ELINT_) || defined(_XBAND_)
    for( i=0 ; i < pPDWData->GetTotalPDW() ; ++i ) {
        printf( "[%4d]\t%012llX(%.1f[us]) %5.1f %.3fMHz[0x%X] %.3fns[0x%X] \n" , i+1, \
            pPDW->ullTOA, CEPDW::DecodeTOAus( pPDW->ullTOA-ullfirstTOA, pPDWData->x.el.enBandWidth ), \
            CEPDW::DecodeDOA((int)pPDW->uiAOA), \
            CEPDW::DecodeFREQMHz((int)pPDW->uiFreq), pPDW->uiFreq,
            CEPDW::DecodePW( (int) pPDW->uiPW, pPDWData->x.el.enBandWidth ), pPDW->uiPW );
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
ENUM_COLLECTBANK CCommonUtils::GetEnumCollectBank( int iCh )
{
    ENUM_COLLECTBANK enCollectBank=enUnknownCollectBank;

    if( iCh >= 0 ) {
        if( iCh < DETECT_CHANNEL ) {
            enCollectBank = enDetectCollectBank;
        }
        else if( iCh < DETECT_CHANNEL+TRACK_CHANNEL ) {
            enCollectBank = enTrackCollectBank;
        }
        else if( iCh < DETECT_CHANNEL+TRACK_CHANNEL+SCAN_CHANNEL ) {
            enCollectBank = enScanCollectBank;
        }
        else {
            enCollectBank = enUserCollectBank;
        }
    }

    return enCollectBank;
}

#endif	// _GRAPH_

/**
 * @brief CCommonUtils::AllSwapData32
 * @param pData
 * @param iLength
 */
void CCommonUtils::AllSwapData32( void *pData, unsigned int uiLength )
{
    UINT i;
    UINT *pWord;

    pWord = (UINT *) pData;
    for( i=0 ; i < uiLength; i+=sizeof(int) ) {
        swapByteOrder( *pWord );
        ++ pWord;
    }

}

/**
 * @brief		swapByteOrder
 * @param		unsigned short & us
 * @return		void
 * @author		議곗쿋??(churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2021/11/18 19:16:45
 * @warning		
 */
void CCommonUtils::swapByteOrder(unsigned short& us)
{
    us = (us >> 8) | ((us<<8) & (unsigned short) 0xFF00);
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
 * @author		議곗쿋??(churlhee.jo@lignex1.com)
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
 * @author    議곗쿋??(churlhee.jo@lignex1.com)
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
 * @author    議곗쿋??(churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-02-22, 13:18
 * @warning
 */
// void CCommonUtils::SetUnitType()
// {
// #ifdef _POCKETSONATA_
//     g_enUnitType = en_ZPOCKETSONATA;
// #elif defined(_ELINT_)
//     g_enUnitType = en_ELINT;
// #elif defined(_XBAND_)
//     g_enUnitType = en_XBAND;
// #else
//     g_enUnitType = en_UnknownUnit;
// 
// #endif
// }

/**
 * @brief     strcasestr
 * @param     const char * pStr
 * @param     const char * pCompare
 * @return    char *
 * @exception
 * @author    議곗쿋??(churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-03-14, 16:55
 * @warning
 */
const char *CCommonUtils::strcasestr( const char *pStr, const char *pCompare )
{
    size_t i, j;
    const char *pRet;

    const char *pStr2;

    pRet = NULL;

    size_t iLen = strlen( pStr );
    size_t iTo = strlen( pCompare );

    if( iLen >= iTo ) {
        pStr2 = pStr;
        for( i=0 ; i <= iLen-iTo ; ++i ) {
            for( j=0 ; j < iTo ; ++j ) {
                if( Isalpha( pStr2[j] ) >= 1 ) {
                    int iDiff = pStr2[j] - pCompare[j];
                    if( iDiff != 0x20 && iDiff != -0x20 && iDiff != 0 ) {
                        break;
                    }
                }
                else {
                    if( pStr2[j] != pCompare[j] ) {
                        break;
                    }
                }
            }

            if( j >= iTo ) {
                pRet = pStr2;
                break;
            }

            ++ pStr2;
        }
    }

    return pRet;

}

/**
 * @brief     Isalpha
 * @param     int iCh
 * @return    int
 * @exception
 * @author    議곗쿋??(churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-03-29, 11:27
 * @warning
 */
int CCommonUtils::Isalpha( int iCh )
{
    int iRet;

    if( iCh >= 'A' && iCh <= 'Z' )
        iRet = 1;
    else if( iCh >= 'a' && iCh <= 'z' )
        iRet = 2;
    else
        iRet = 0;

    return iRet;
}

/**
 * @brief     IsMultiplyOverflow
 * @param     size_t uiSize
 * @param     size_t uiItems
 * @return    size_t
 * @exception
 * @author    議곗쿋??(churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-03-15, 14:18
 * @warning
 */
size_t CCommonUtils::CheckMultiplyOverflow( int iSize, int iItems )
{
    size_t szSize;

    try {
		if( iItems <= 0 || iItems <= 0 ) {
			throw 0;
		}

//         if( iSize == -1 && iItems == INT_MIN ) {
//             throw 0;
//         }
// 
//         if( iItems == -1 && iSize == INT_MIN ) {
//             throw 0;
//         }

        if( iSize > INT_MAX / iItems ) {
            throw 0;
        }

        if( iSize < INT_MIN / iItems ) {
            throw 0;
        }

        szSize = iSize * iItems;
    }
    catch( int iExp ) {
        szSize = iExp;
    }

    return szSize;

}

/**
 * @brief     INT2UINT
 * @param     int iValue
 * @return    unsigned int
 * @exception
 * @author    議곗쿋??(churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-03-28, 19:22
 * @warning
 */
unsigned int CCommonUtils::INT2UINT( int iValue )
{
    unsigned int iRet=0;

    if( iValue >= 0 ) {
        iRet = iValue;
    }

    return iRet;

}

/**
 * @brief     WhatDataType
 * @param     char * pStrPathname
 * @return    ENUM_DataType
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-28, 13:47
 * @warning
 */
ENUM_DataType CCommonUtils::WhatDataType( char *pStrPathname )
{
    ENUM_DataType enDataType = en_UnknownData;

    if( NULL != CCommonUtils::strcasestr( pStrPathname, ".pdw" ) || NULL != CCommonUtils::strcasestr( pStrPathname, ".npw" ) || NULL != CCommonUtils::strcasestr( pStrPathname, ".spdw" ) ) {
        enDataType = en_PDW_DATA;
    }
    else if( NULL != CCommonUtils::strcasestr( pStrPathname, "e4.dat" ) ) {
        enDataType = en_PDW_DATA;
    }
    else if( NULL != CCommonUtils::strcasestr( pStrPathname, ".kpdw" ) ) {
        enDataType = en_PDW_DATA;
    }
    else if( NULL != CCommonUtils::strcasestr( pStrPathname, ".iq" ) || NULL != CCommonUtils::strcasestr( pStrPathname, ".siq" ) ||
        NULL != CCommonUtils::strcasestr( pStrPathname, "e2.dat" ) || NULL != CCommonUtils::strcasestr( pStrPathname, ".eiq" ) ) {
        enDataType = en_IQ_DATA;
    }
    else if( NULL != CCommonUtils::strcasestr( pStrPathname, ".epdw" ) || NULL != CCommonUtils::strcasestr( pStrPathname, ".enpw" ) || NULL != strstr( pStrPathname, ".zpdw" ) ) {
        enDataType = en_PDW_DATA;
    }
    else if( NULL != CCommonUtils::strcasestr( pStrPathname, ".xpdw" ) ) {
        enDataType = en_PDW_DATA;
    }
    else {
        //LOGMSG1( enError, "잘못된 파일명 입니다. 데이터 형식을 모릅니다." );
        TRACE( "잘못된 파일명 입니다." );
    }

    return enDataType;

}

/**
 * @brief
 * @return    ENUM_UnitType
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/03/12 19:38:24
 * @warning
 */
ENUM_UnitType CCommonUtils::WhatUnitType( char *pStrPathname )
{
    ENUM_UnitType enUnitType;

    if( NULL != CCommonUtils::strcasestr( pStrPathname, ".midas" ) ) {
        enUnitType = en_MIDAS;
    }
    else if( NULL != CCommonUtils::strcasestr( pStrPathname, ".pdw" ) || NULL != CCommonUtils::strcasestr( pStrPathname, ".npw" ) ||
        NULL != CCommonUtils::strcasestr( pStrPathname, ".iq" ) || NULL != CCommonUtils::strcasestr( pStrPathname, ".siq" ) ) {
        enUnitType = en_SONATA;
    }
    else if( NULL != CCommonUtils::strcasestr( pStrPathname, ".spdw" ) ) {
        enUnitType = en_SONATA_SHU;
    }
    else if( NULL != CCommonUtils::strcasestr( pStrPathname, ".dat" ) ) {
        enUnitType = en_701;
    }
    else if( NULL != CCommonUtils::strcasestr( pStrPathname, ".kpdw" ) ) {
        enUnitType = en_KFX;
    }
    else if( NULL != CCommonUtils::strcasestr( pStrPathname, ".epdw" ) || NULL != CCommonUtils::strcasestr( pStrPathname, ".enpw" ) ) {
        enUnitType = en_ELINT;
    }
    else if( NULL != CCommonUtils::strcasestr( pStrPathname, ".zpdw" ) || NULL != CCommonUtils::strcasestr( pStrPathname, ".znpw" ) ) {
        enUnitType = en_ZPOCKETSONATA;
    }
    else if( NULL != CCommonUtils::strcasestr( pStrPathname, ".xpdw" ) ) {
        enUnitType = en_XBAND;
    }

    else {
        enUnitType = en_UnknownUnit;
    }

    return enUnitType;

}