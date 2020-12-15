﻿//////////////////////////////////////////////////////////////////////////
/*!
 * @file      RawFile.cpp
 * @brief     RawData 파일을 억세스 하여 데이터 읽기, 쓰기 등을 수행한다.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-07-02 오전 10:47 
 * @warning   
 */


#ifdef __linux__
#include <sys/types.h>
#include <unistd.h>

#include "../SigAnal/_Type.h"

#else
#include <io.h>

#endif

#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

#include "RawFile.h"


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
	m_pfile = NULL;
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
	if( m_pfile != NULL ) fclose( m_pfile );
	if( m_fid != 0 ) _close( m_fid );

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
// #ifdef _WIN32
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
	//int nLen = strlen(pFilename);
	int nLen = (int) strlen(pFilename);

	char* pEndStr = pFilename + (nLen-1);
	char* pTempStr = pEndStr;
	char* pOutStr = NULL;
	char ch;

	while( nLen > 0 ) {
		ch = *pTempStr;

		if (ch=='/' || ch=='\\' || ch==':' )
			break;

		pOutStr = pTempStr;

		//
		pTempStr --;
		nLen --;
	}

	// 파일명에 파일명을 복사한다.
	if( pOutStr != NULL ) {
#ifdef __linux__
        strcpy_s( m_filename, pOutStr );
#else
        strcpy_s( m_filename, sizeof(m_filename), pOutStr );
#endif

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
 * @return    BOOL
 * @version   0.0.1
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-07-02 오전 11:50 
 * @warning   
 */
bool CRawFile::FileOpen( char *filename, char *file_mode )
{
	bool bRet = false;
	//Init();

	if( m_pfile != NULL )	fclose( m_pfile );

#ifdef __linux__
    if( ( m_pfile = fopen( filename , file_mode ) ) == 0 ) { //DTEC_Else
#else
    if( 0 != fopen_s( & m_pfile, filename , file_mode ) ) { //DTEC_Else
#endif

		printf( "\n[W] FIle is not exist !!" );
	}
	else {
#ifdef __linux__
        strcpy_s( m_fullname, filename );
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
int CRawFile::Write( void *pData, int c_size, int count )
{
	int nWrite;
	nWrite = fwrite( pData, count, c_size, m_pfile );
	return nWrite;
}

//////////////////////////////////////////////////////////////////////////
/*!
 * @brief     
 * @param     void
 * @return    void
 * @version   0.0.1
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-07-02 오전 11:55 
 * @warning   
 */
void CRawFile::FileClose()
{
	if( m_pfile != NULL ) {
		fclose( m_pfile );
        m_pfile = NULL;
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
unsigned long long int CRawFile::GetFileSize()
{
	long file_byte=0;

	if( m_pfile != NULL ) {
		if( fseek( m_pfile, 0L, SEEK_END ) == 0 ) {
			file_byte = ftell( m_pfile );
			rewind( m_pfile );
		}
		else { //DTEC_Else
			file_byte = -1;
		}
	}

	return file_byte;
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
unsigned long long int CRawFile::GetFileSize( char *pPathFileName )
{
    unsigned long long int iRet=-1;

#ifdef __linux__

#else
	struct _stati64 statbuf;

	if( _stati64( pPathFileName, & statbuf ) != 0 ) {
		iRet = -1;
	}
	else {
		iRet = statbuf.st_size;
	}
#endif
	return iRet;

}

/**
 * @brief CRawFile::CreateDir
 * @param pPath
 * @return
 */
bool CRawFile::CreateDir( char *pPath )
{
    bool bRet=false;
    char dirName[256];
    char *p=pPath;
    char *q=dirName;

    while( *p ) {
        if( ('\\' == *p) || ('/'==*p)) {
            if( ':' != *(p-1) ) {
#ifdef _WIN32
                CreateDirectory( dirName, NULL );
#else
                mkdir( dirName, 0766 );
#endif
            }
        }

        *q++ = *p++;
        *q = '\0';
    }
#ifdef _WIN32
    bRet = CreateDirectory( dirName, NULL );
    if( bRet != true ) {
        perror( "디렉토리 생성");
    }
#else
    int iRet = mkdir( dirName, 0766 );

    if( iRet == 0 || ( iRet == -1 && errno == EEXIST ) ) {
        bRet = true;
    }
    else {
        perror( "디렉토리 생성");
    }

#endif

    return bRet;
}
