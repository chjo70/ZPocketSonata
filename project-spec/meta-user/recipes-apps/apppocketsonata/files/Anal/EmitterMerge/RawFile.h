//////////////////////////////////////////////////////////////////////////
/*!
 * @file      RawFile.h
 * @brief     파일 접근에 대한 기본 클래스를 생성한다.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-07-02 오전 10:01 
 * @warning   
 */

#pragma once

#include <stdio.h>

#define ERROR_OF_MEMORY_ALLOC	(-100)
#define ERROR_OF_FILE_WRITE		(-1)
#define ERROR_OF_FILE_READ		(-2)

/**
* [식별자 : CLS-GMU-EL-L-AcCM]
*
* [추적성 : SRS-G-SCFR-002]
*
* @class	CRawFile
* @brief	파일 열기, 쓰기 등을 처리하기 위한 클래스
*
* (1) 클래스 설명
* - 본 클래스는 파일 관련 읽기, 쓰기, 닫기 등을 처리해주는 클래스이다.
*
* (2) 설계결정사항
* - 해당사항 없음
*
* (3) 제한 및 예외처리
* - 해당사항 없음
*/
class CRawFile
{
protected:
	FILE *m_pfile;

	int m_fid;
	unsigned int m_posFid;
	char m_fullname[300];
	char m_filename[300];

public:
	CRawFile(void);
	virtual ~CRawFile(void);

	bool ReadN( void *pData, int size );
	bool LoadFile( char *filename );

	bool FileOpen( const char *filename, char *file_mode );
	int Write( void *pData, int c_size, int count );
	void FileClose();
	long LGetFileSize();
	__int64 IGetFileSize( char *pPathFileName );
	void GetFilename( char *pFilename );

	inline char *GetFullname() { return m_fullname; }
	inline char *GetFilename() { return m_filename; }

	//bool IsEndOfFile();

};

