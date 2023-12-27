//////////////////////////////////////////////////////////////////////////
/*!
 * @file      RawFile.cpp
 * @brief     RawData 파일을 억세스 하여 데이터 읽기, 쓰기 등을 수행한다.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-07-02 오전 10:47
 * @warning
 */

#include "pch.h"

#ifdef __linux__

#elif _MSC_VER
#include <io.h>

#elif defined(__VXWORKS__)
#include <ioLib.h>
#include <nfs/nfsCommon.h>

#else
#include <io.h>
#endif


#include <fcntl.h>
#include <string.h>
#include <stdint.h>
#include <sys/stat.h>

#include "RawFile.h"

// #include "../SigAnal/_Type.h"


//////////////////////////////////////////////////////////////////////////
/*!
 * @brief
 * @param     void
 * @return    void
 * @version   0.0.1
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-07-02 오전 10:38
 * @warning
 */
CRawFile::CRawFile(void)
{

	m_fid = 0;
}


//////////////////////////////////////////////////////////////////////////
/*!
 * @brief     객체가 소멸시 파일 오픈된 것이 있으면 해지한다.
 * @param     void
 * @return    void
 * @version   0.0.1
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-07-02 오전 11:24
 * @warning
 */
CRawFile::~CRawFile(void)
{

	if( m_fid > 0 ) {
        _close( m_fid );
    }

}


//////////////////////////////////////////////////////////////////////////
/*!
 * @brief
 * @param     char * filename
 * @return    bool
 * @version   0.0.1
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-07-02 오후 2:49
 * @warning
 */
// bool CRawFile::LoadFile( char *filename )
// {
//
// #ifdef _MSC_VER
// 	m_fid = _open( filename, _O_RDONLY | _O_BINARY ); // , 0644 );
//
// #else
// 	m_fid = open( filename, O_RDONLY, 0644 );
//
// 	if( m_fid == -1 ) {
// 		return false;
// 	}
// #endif
//
// 	if( m_fid == -1 ) {
// 		return false;
// 	}
// 	else {
// 		strcpy_s( m_fullname, sizeof(m_fullname), filename );
// 		GetFilename( m_fullname );
//
// 		m_posFid = 0;
// 	}
//
// 	return true;
//
// }

//////////////////////////////////////////////////////////////////////////
/*!
 * @brief     확장자를 포함한 파일명에서 파일명만 읽어 온다.
 * @param     char * pFilename
 * @return    void
 * @version   0.0.1
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-07-18 오후 7:21
 * @warning
 */
void CRawFile::GetFilename( char *pFilename )
{
	// 파일명 얻기
	/*! \bug  	음수값을 unsigned type으로 변환을 자제해야 한다.
	    \author 조철희 (churlhee.jo@lignex1.com)
	    \date 	2014-01-24 16:46:40
	*/
	int nLen = (int) strlen(pFilename);

    if( nLen >= 1 ) {
        char* pEndStr = &pFilename[nLen - 1];
        char* pTempStr = pEndStr;
        char* pOutStr = NULL;
        char ch;

        while( nLen > 0 ) {
            ch = *pTempStr;

            if( ch == '/' || ch == '\\' || ch == ':' ) {
                break;
            }

            pOutStr = pTempStr;

            //
            pTempStr--;
            nLen--;
        }

        // 파일명에 파일명을 복사한다.
        if( pOutStr != NULL ) {
#if defined(__linux__) || defined(__VXWORKS__)
            strcpy( m_filename, pOutStr );
#else
            strcpy_s( m_filename, sizeof( m_filename ), pOutStr );

#endif

        }
    }
    else {
        strcpy( m_filename, "invalid_filename" );
    }

}

//////////////////////////////////////////////////////////////////////////
/*!
 * @brief     파일 포인터가 마지막인지 체크하여 반환한다.
 * @param     void
 * @return    bool
 * @version   0.0.1
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-07-17 오전 11:50
 * @warning
 */
// bool CRawFile::IsEndOfFile()
// {
// 	if( m_pfile == NULL )
// 		return true;
//
// 	return feof( m_pfile) != 0;
// }

//////////////////////////////////////////////////////////////////////////
/*!
 * @brief
 * @param     void * pData
 * @param     int size
 * @return    bool
 * @version   0.0.1
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-07-02 오후 2:50
 * @warning
 */
// bool CRawFile::ReadN( void *pData, int size )
// {
// 	int iRead;
// 	bool bRet = true;
//
// 	/*! \debug  신뢰성: NULL 체크
// 			\author 조철희 (churlhee.jo@lignex1.com)
// 			\date 	2015-10-6 13:41:48
// 	*/
// 	if( pData != NULL ) {
// 		iRead = read( m_fid, (char *) pData, size );
// 		if( iRead <= 0 ) {
// 			bRet = false;
// 		}
// 	}
// 	else {
// 		bRet = false;
// 	}
//
// 	return bRet;
//
// }


//////////////////////////////////////////////////////////////////////////
/*!
 * @brief     입력 매개변수에 파일 옵션을 입력해서 파일 핸들러를 얻는다.
 * @param     char * filename
 * @param     char * file_mode
 * @return    bool
 * @version   0.0.1
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-07-02 오전 11:50
 * @warning
 */
bool CRawFile::RawOpenFile( const char *filename, int iMode )
{
	bool bRet = false;
	//Init();

    if( m_fid > 0 )	{
        _close( m_fid );
    }

#if defined(__linux__)
    m_fid = open( filename , iMode, 0644 );
    if( m_fid == 0 ) { //DTEC_Else
#elif defined(__VXWORKS__)
    //printf( "\n File open[%s]" , filename );
    m_fid = open( filename , iMode, 0644 );
    if( m_fid == ERROR ) { //DTEC_Else
#else
    int iResult = 1;

    unsigned int icMode;

    icMode = ( unsigned int ) ( O_CREAT | O_APPEND );
    if ( ( (unsigned int) iMode & icMode ) == icMode ) {

    }
    else if( ( ( unsigned int ) iMode & O_CREAT ) == O_CREAT ) {
#ifdef _WIN64
        int iFileMode = _chmod( filename, 222 );
        if( iFileMode == 0 ) {
            iResult = remove( filename );
            if( iResult != 0 ) {
                TRACE( "[W] 파일을 삭제할 수 없습니다 !!!" );
            }
        }

#else
        iResult = remove( filename );
        if( iResult != 0 ) {
            TRACE( "[W] 파일을 삭제할 수 없습니다 !!!" );
        }

#endif

    }
    else {

    }

	m_fid = _open( filename , iMode );
    if( iResult == 1 && m_fid <= 0 ) { //DTEC_Else
#endif
        TRACE( "\n[W] 파일[%s]을 생성하지 못합니다 !", filename );
	}
	else {

#ifdef _MSC_VER
#ifdef _WIN64
         _chmod( filename, 222 );
#else


#endif

#endif

#if defined(__linux__) || defined(__VXWORKS__)
        strcpy( m_fullname, filename );
#else
        strcpy_s( m_fullname, sizeof(m_fullname), filename );
#endif

		GetFilename( m_fullname );

		bRet = true;
	}

	/*! \debug  신뢰성: return true 이지만 기존 처리 그대로 수행하게 함.
			\author 조철희 (churlhee.jo@lignex1.com)
			\date 	2015-10-5 15:42:27
	*/

	return bRet;
}

//////////////////////////////////////////////////////////////////////////
/*!
 * @brief     데이터를 사이즈크기 만큼 이진 값으로 저장한다.
 * @param     void * pData
 * @param     int c_size
 * @param     int count
 * @return    int
 * @version   0.0.1
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-07-18 오후 7:45
 * @warning
 */
unsigned int CRawFile::Write( void *pData, unsigned int uiSize )
{
    int iWrite=0;

    //if( uiSize > 0 && pData != NULL && m_fid > 0 ) {
    if( pData != NULL && m_fid > 0 ) {
    	//printf( "\n Write[%p], Size[%d], m_fid[%d]" , pData, c_size, m_fid );
	    iWrite = _write( m_fid, (char *) pData, uiSize );
        if( iWrite > 0 ) {
        }
        else {
            perror("_write()");
            printf( "iWrite= %d" , iWrite );
            iWrite = 0;
        }
    }

	return (unsigned int) iWrite;
}

/**
 * @brief		Read
 * @param		void * pData
 * @param		int c_size
 * @return		int
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2021/01/06 10:05:06
 * @warning
 */
unsigned int CRawFile::Read( void *pData, size_t c_size, int iOffset )
{
	unsigned int uiRead=0;
    int szRead;

    if( m_fid != 0 && iOffset != 0 ) {
        _lseek(m_fid, iOffset, SEEK_SET );
    }

    if( pData != NULL && m_fid > 0 ) {
        szRead = _read( m_fid, (char *) pData, (unsigned int) c_size );
        if( szRead < 0 ) {
			// uiRead = 0;
			//break;
        }
        else {
            uiRead = (unsigned int) szRead;
        }
    }
    else {
		if (pData != NULL) {
			*(char *)pData = NULL;
		}
    }

	return uiRead;
}

//////////////////////////////////////////////////////////////////////////
/*!
 * @brief     읽기 모드를 해지하고 파일을 닫는다.
 * @param     void
 * @return    void
 * @version   0.0.1
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-07-02 오전 11:55
 * @warning
 */
void CRawFile::CloseFile()
{
	if( m_fid > 0 ) {
        struct stat statbuf;

        _close( m_fid );
        m_fid = 0;

        if( stat( m_fullname, &statbuf ) >= 0 ) {
#ifdef _MSC_VER
            statbuf.st_mode ^= (_S_IREAD);
#else
            statbuf.st_mode ^= (S_IROTH);

#endif

#if 0
            if( chmod( m_fullname, statbuf.st_mode ) < 0 ) {
                perror( "파일:" );
            }
#endif

        }

	}
    else {
        perror( "파일:" );
    }

	return;

}

/**
 * @brief     파일의 크기를 리턴한다.
 * @param     void
 * @return    long
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-08-19, 오후 2:36
 * @warning
 */
unsigned long long int CRawFile::GetRawFileSize()
{
    unsigned long long int ullFileSize=0;

	if( m_fid != 0 ) {
        // ullfile_byte = _filelength( m_fid );
        ullFileSize = GetRawFileSize( m_fullname );

	}

	return ullFileSize;
}

/**
 * @brief     파일명을 입력하여 파일 사이즈를 리턴한다.
 * @param     *pPathFileName 파일명
 * @return    __int64
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-10-11, 오전 10:09
 * @warning
 */
unsigned long long int CRawFile::GetRawFileSize( char *pPathFileName )
{
	unsigned long long int ullRet64=0;

#if defined(__linux__) || defined(__VXWORKS__)
	struct stat statbuf;

	if( stat( pPathFileName, & statbuf ) != 0 ) {
	    ullRet64 = ULONGLONG_MAX;
	}
	else {
		ullRet64 = statbuf.st_size;
	}

#else
	struct _stati64 statbuf;

	if( _stati64( pPathFileName, & statbuf ) != 0 ) {
		ullRet64 = 0;
	}
	else {
		ullRet64 = (unsigned long long int) statbuf.st_size;
	}
#endif
	return ullRet64;

}

/**
 * @brief CRawFile::CreateDir
 * @param pPath
 * @return
 */
bool CRawFile::CreateDir( const TCHAR *pPath )
{
	bool bRet=true;
    TCHAR dirName[256];
    const TCHAR *p=pPath;
    TCHAR *q=dirName;

    while( *p ) {
        if( ('\\' == *p) || ('/'==*p)) {
            if( p != pPath && ':' != *(p-1) ) {

#ifdef _MSC_VER
                CreateDirectory( dirName, NULL );

#elif defined(__linux__)
                mkdir( dirName, 0766 );
#else

#ifdef __LP64__
                mkdir( dirName, 666 );
#else
                mkdir( dirName );
#endif


#endif
            }
        }

#ifdef __linux1__
        mkdir( dirName, 0766 );
#endif

        *q++ = *p++;
        *q = '\0';
    }


#ifdef _MSC_VER
    if( ! PathFileExists( dirName ) ) {
        bool bCreate;
        bCreate = CreateDirectory( dirName, NULL );
        if( bCreate != true ) {
            perror( "디렉토리 생성");
            bRet = false;
        }
    }
    else {

    }

#elif defined(__linux__)
    int iRet = mkdir( dirName, 0766 );

    if( iRet == 0 || ( iRet == -1 && errno == EEXIST ) ) {
    }
    else {
        perror( "디렉토리 생성");
        bRet = false;
    }
#else

#ifdef __LP64__
    int iRet = mkdir( dirName, 666 );
#else
    int iRet = mkdir( dirName );
#endif

    //printf( "\n iRet=%d" , iRet );
    if( iRet == 0 || ( iRet == -1 && ( errno == EEXIST || errno == S_nfsLib_NFSERR_EXIST ) ) ) {
    }
    else {
        perror( "디렉토리 생성");
        bRet = false;
    }

#endif

    return bRet;
}
