//////////////////////////////////////////////////////////////////////////
/*!
 * @file      RawFile.h
 * @brief     파일 접근에 대한 기본 클래스를 생성한다.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-07-02 오전 10:01 
 * @warning   
 */

#pragma once

#include "../SigAnal/_Type.h"

#ifdef __linux__
#include <sys/types.h>
#include <unistd.h>

#else
#include <io.h>
#endif

#include <stdio.h>

#define ERROR_OF_MEMORY_ALLOC	(-100)
#define ERROR_OF_FILE_WRITE		(-1)
#define ERROR_OF_FILE_READ		(-2)

#ifdef __linux__
#define O_BINARY                (0)
#endif

//////////////////////////////////////////////////////////////////////////
/*!
 * [식별자 : D-EL-SDD-XXX]
 * [추적성 : R-EL-SDD-XXX]
 * 
 * @class     CRawFile
 * @brief     파일에 대한 기본 기능에 대한 클래스를 선언한다.
 * 
 * (1) 클래스 설명
 *  - 파일 관리에 대한 기본적인 기능을 구현한다.
 * 
 * (2) 설계결정사항
 *  - 설계결정사항을 입력하고 없을 때는 '해당사항 없음' 으로 표시함
 * 
 * (3) 제한 및 예외처리
 *  - 제한 및 예외 처리사항을 입력하고 없을 때는 '해당사항 없음' 으로 표시함
 * 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-07-02 오전 10:02 
 * @warning   
 */
class CRawFile
{
protected:
	// FILE *m_pfile;

	int m_fid;
	unsigned int m_posFid;
    char m_fullname[500];
    char m_filename[500];

public:
	CRawFile(void);
	virtual ~CRawFile(void);

	bool ReadN( void *pData, int size );
	bool LoadFile( char *filename );

	//FILE *GetFileHandler() { return m_pfile; }
	int GetFileHandler() { return m_fid; }
	bool FileOpen( char *filename, int iMode );
	int Read( void *pData, int c_size, int iOffset=0 );
	int Write( void *pData, int c_size );
	void FileClose();
    unsigned long long int GetFileSize();
    unsigned long long int GetFileSize( char *pPathFileName );
	void GetFilename( char *pFilename );

    bool CreateDir( TCHAR *pPath );

	inline char *GetFullname() { return m_fullname; }
	inline char *GetFilename() { return m_filename; }

	inline void SeekToStart() { if( m_fid != 0 ) _lseek(m_fid, 0, SEEK_SET ); }

	//bool IsEndOfFile();

};

