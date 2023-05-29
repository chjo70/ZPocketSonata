/**

    @file      FileTar.cpp
    @brief
    @details   ~
    @author    조철희
    @date      18.04.2023
    //Author :- Nish [nishforever@vsnl.com]

**/

#include "pch.h"


// #ifdef _WIN32
// #include "../../A50SigAnal/stdafx.h"
// #else
//
// #endif


#include "FileTar.h"

//#include <io.h>
#include <string.h>
#include <stdio.h>

//#include "../../Anal/SigAnal/_Type.h"

#ifdef __VXWORKS__
IMPORT CFileTar *theFileTar;
#endif

#ifdef __cplusplus
extern "C" {
#endif

void untar( char *filename, char *destfolder );

#ifdef __cplusplus
}
#endif

/**
 * @brief     strlastfind
 * @param     char * s
 * @param     char * t
 * @return    char *
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-18 09:18:52
 * @warning
 */
char *strlastfind(char *s, char *t)
{
    int i, j;
    int len_str, len_target;

    // 두 문자열의 길이를 구한다.
    for (len_str = 0; s[len_str] != '\0'; len_str++) ;
    for (len_target = 0; t[len_target] != '\0'; len_target++) ;

    // 원본 문자열의 길이에서 찾을 문자열의 길이를 뺀 만큼만 루프를 돌면 된다.
    for (i = len_str - len_target ; i >= 0 ; i--) {
        // 찾을 문자열의 길이만큼 for문을 돈다.
        for ( j = 0; j < len_target; j++) {
            if (s[i + j] != t[j])   // 위치의 문자들이 같지 않다면 loop를 빠진다.
                break;
        }

        // 만약 j가 len_target과 같다면, 즉 앞의 for문이 중간에
        // break가 되지 않고 끝까지 다 돌았다면 문자열을 찾은 것이다.
        if (j == len_target)
            return (s + i);       // 찾은 문자열의 시작 주소를 리턴한다.
    }

    // 문자열을 못찾았다면 NULL을 반환한다.
    return (NULL);
}


char *strfind(char *s, char *t)
{
    int i, j;
    int len_str, len_target;

    // 두 문자열의 길이를 구한다.
    for (len_str = 0; s[len_str] != '\0'; len_str++) ;
    for (len_target = 0; t[len_target] != '\0'; len_target++) ;
    // 원본 문자열의 길이에서 찾을 문자열의 길이를 뺀 만큼만 루프를 돌면 된다.
    for (i = 0; i < len_str - len_target; i++) {
        // 찾을 문자열의 길이만큼 for문을 돈다.
        for ( j = 0; j < len_target; j++) {
            if (s[i + j] != t[j])   // 위치의 문자들이 같지 않다면 loop를 빠진다.
                break;
        }

        // 만약 j가 len_target과 같다면, 즉 앞의 for문이 중간에
        // break가 되지 않고 끝까지 다 돌았다면 문자열을 찾은 것이다.
        if (j == len_target)
            return (s + i);       // 찾은 문자열의 시작 주소를 리턴한다.
    }

    // 문자열을 못찾았다면 NULL을 반환한다.
    return (NULL);
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    untar
		\author   ��ö��
		\param    filename �������� char *
		\param    destfolder �������� char *
		\return   void
		\version  0.0.98
		\date     2009-09-23 19:28:59
		\warning
*/
void untar( char *filename, char *destfolder )
{
#ifdef __VXWORKS__
	theFileTar->UnTar(filename, destfolder);
#endif

}


CFileTar::CFileTar()
{
	m_TarFile = -1;
}

CFileTar::~CFileTar()
{
	for(int i=1; i <= m_TarHeader.GetCount();i++)
		delete m_pTarIndex[i];

}

const char * CFileTar::TarHeader::GetDescription()
{
	return m_block.header.name;
}

int CFileTar::TarHeader::GetCount()
{
	return 0;
}

int CFileTar::TarHeader::IncrementCount()
{
	int FileCount=0;
	if( FileCount<TAR_MAX_FILES)
		return ++FileCount;
	else
		return 0;
}

CFileTar::TarHeader::TarHeader()
{
	// FileCount=0;

}

void CFileTar::SetFilePath(char *path)
{
	strcpy(FilePath,path);
	if(path[strlen(path)-1]!='/')
		strcat(FilePath,"/");

}

/**
 * @brief     AddFile
 * @param     char * fname
 * @param     char * desc
 * @return    int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-18 09:23:34
 * @warning
 */
// int CFileTar::AddFile(char *fname, char *desc)
// {
// 	char fullpath[_MAX_PATH];
// 	strcpy(fullpath,FilePath);
// 	strcat(fullpath,fname);
// 	HANDLE hFile;
// 	unsigned long size;
//
// 	hFile=CreateFile(fullpath,GENERIC_READ,0,NULL,
// 		OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
// 	if(hFile==INVALID_HANDLE_VALUE)
// 	{
// 		CloseHandle(hFile);
// 		return 1;
// 	}
// 	size=GetFileSize(hFile,NULL);
// 	if(size==0xFFFFFFFF)
// 	{
// 		CloseHandle(hFile);
// 		return 1;
// 	}
//
// 	if(m_TarHeader.IncrementCount()==0)
// 	{
// 		CloseHandle(hFile);
// 		return 1;
// 	}
// 	TarIndex *pTarIndex=new TarIndex;
// 	strcpy(pTarIndex->FileName,fname);
// 	strcpy(pTarIndex->Description,desc);
// 	pTarIndex->Size=size;
//
// 	m_pTarIndex[m_TarHeader.GetCount()]=pTarIndex;
//
// 	CloseHandle(hFile);
// 	return 0;
// }

/**
 * @brief     CreateTar
 * @param     char * TarFName
 * @param     char * TarPath
 * @return    int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-18 09:23:29
 * @warning
 */
int CFileTar::CreateTar(char *TarFName, char *TarPath)
{
	char tarfullpath[_MAX_PATH];
	if(TarPath==NULL)
		strcpy(tarfullpath,FilePath);
	else
		strcpy(tarfullpath,TarPath);
	if(tarfullpath[strlen(tarfullpath)-1]!='/')
		strcat(tarfullpath,"/");
	strcat(tarfullpath,TarFName);
	int fdout=0;
	int ret;

	int i;
#ifdef __VXWORKS__
	if((fdout=open(tarfullpath,_O_CREAT|_O_WRONLY|_O_BINARY|_O_TRUNC,_S_IWRITE))<0)
#else
    if( ( fdout = _open( tarfullpath, _O_CREAT | _O_WRONLY | _O_BINARY | _O_TRUNC ) ) < 0 )
#endif
	{
		_close(fdout);
		return 1;
	}
	ret=_write(fdout,(char *) &m_TarHeader,sizeof(UNI_BLOCK));
	long ssize=m_TarHeader.GetCount()*sizeof (TarIndex)+sizeof(UNI_BLOCK);
	for(i=1;i<=m_TarHeader.GetCount();i++)
	{
		m_pTarIndex[i]->Start= ssize;
		ret=_write(fdout,(char *) m_pTarIndex[i],sizeof(TarIndex));
		ssize += m_pTarIndex[i]->Size;
	}
	for(i=1;i<=m_TarHeader.GetCount();i++)
	{
		char filetoadd[_MAX_PATH];
		strcpy(filetoadd,FilePath);
		strcat(filetoadd,m_pTarIndex[i]->FileName);
		AppendFile(fdout,filetoadd);
	}

	_close(fdout);
	return 0;
}

int CFileTar::AppendFile(int fdout, char *fpath)
{
	int fdin=0;
	size_t len;

#ifdef __VXWORKS__
	if((fdin=open(fpath,_O_RDONLY|_O_BINARY, 0666))<0)
#else
	if((fdin=_open(fpath,_O_RDONLY|_O_BINARY))<0)
#endif
	{
		_close(fdin);
		return 1;
	}
	char buffer[NBUFFSIZE];
	while((len=_read(fdin,buffer,NBUFFSIZE))>0)
	{
		_write(fdout,buffer,len);
	}
	_close(fdin);
	return 0;
}

const char * CFileTar::GetHeaderDescription()
{
	return m_TarHeader.GetDescription();

}


//////////////////////////////////////////////////////////////////////////
/*! \brief    CFileTar::GetTarInfo
		\author   ��ö��
		\param    pTarFile �������� char *
		\param    pTarHeader �������� TarHeader *
		\return   bool
		\version  0.0.99
		\date     2009-09-24 14:42:33
		\warning
*/
bool CFileTar::GetTarInfo( char *pTarFile, TarHeader *pTarHeader )
{
	if( m_TarFile < 0 ) {
        printf( "\n pTarFile[%s]" , pTarFile );
#ifdef __VXWORKS__
		if( ( m_TarFile=open( pTarFile,_O_BINARY|_O_RDONLY, 0666 ) ) < 0 ) {
#else
		if( ( m_TarFile=_open( pTarFile,_O_BINARY|_O_RDONLY ) ) < 0 ) {
#endif
			printf( "\n Error found !" );
			return false;
		}
	}

	memset( pTarHeader, 0, sizeof(UNI_BLOCK) );
	int nRead=_read( m_TarFile, (char *) pTarHeader, sizeof(UNI_BLOCK) );

	pTarHeader->m_filesize = Octal2Deciaml( pTarHeader->m_block.header.size, sizeof(pTarHeader->m_block.header.size) );
	GetDate( & pTarHeader->m_time, pTarHeader->m_block.header.mtime, sizeof(pTarHeader->m_block.header.mtime) );

	if( nRead <= 0 ) {
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CFileTar::UnTar
		\author   ��ö��
		\param    pDestFile �������� char *
		\return   bool
		\version  0.0.99
		\date     2009-09-24 15:08:28
		\warning
*/
bool CFileTar::UnTar( char *pDestFile, TarHeader *pTarHeader )
{
	int fdout;
	int nRead, nWrite;
	UNI_BLOCK *pBlock;

	struct _stat filestat;

#ifdef _WIN32
	if( ( fdout = _open( pDestFile, _O_CREAT | _O_WRONLY | _O_BINARY | _O_TRUNC, _S_IWRITE ) ) < 0 ) {
#elif defined(__VXWORKS__)
	if( ( fdout = open( pDestFile, _O_CREAT | _O_WRONLY | _O_BINARY | _O_TRUNC, 0666 ) ) < 0 ) {
#else
	if( ( fdout = _open( pDestFile, _O_CREAT | _O_WRONLY | _O_BINARY | _O_TRUNC ) ) < 0 ) {
#endif
		_close( fdout );
		printf( "\n*can't creat the file(%s)" , pDestFile );
		return false;
	}

	pBlock = & pTarHeader->m_block;

	unsigned long rem;
	char buff[sizeof(UNI_BLOCK)];
	rem = pTarHeader->m_filesize;

	while( rem > sizeof(UNI_BLOCK) ) {
		nRead = _read( m_TarFile, buff, sizeof(UNI_BLOCK) );
		nWrite = _write( fdout, buff, nRead );
		if( nRead != sizeof(UNI_BLOCK) || nRead <= 0 || nWrite != nRead ) {
			_close( fdout );
			printf( "\n*can't read or write the file" );
			return false;
		}

		rem -= sizeof(UNI_BLOCK);
	}

	if( rem > 0 ) {
		nRead = _read( m_TarFile, buff, sizeof(UNI_BLOCK) );
		nWrite = _write( fdout, buff, rem );
		if( nRead != sizeof(UNI_BLOCK) || nRead <= 0 || nWrite != (int) rem ) {
			_close( fdout );
			printf( "\n*can't read or write the file" );
			return false;
		}
	}

	// ���� ������ ��¥�� �����Ѵ�.
	_fstat( fdout, & filestat );
	pTarHeader->m_time.actime = filestat.st_atime;

	_close( fdout );

	_utime( pDestFile, & pTarHeader->m_time );

	printf( "\n*extract the file(%s)" , pDestFile );
	return true;
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CFileTar::UnTar
	\author   ��ö��
	\param    pTarFile �������� char *
	\param    pDestpath �������� char *
	\return   int
	\version  0.0.99
	\date     2009-09-24 14:29:53
	\warning
*/
int CFileTar::UnTar( char *pTarFile, char *pDestpath )
{
	bool bLoop=true;
	char fpath[_MAX_PATH];
    char *p;
	TarHeader th;

	printf( "\n untar %s into %s" , pTarFile, pDestpath );
    bLoop = true; // MkDir( pDestpath );

	while( bLoop ) {

		if( false == GetTarInfo( pTarFile, & th ) ) {
			break;
        }

		// ������ ���ϸ� �����
		strcpy( fpath, pDestpath );
#ifdef _WIN32
		if( fpath[strlen( fpath )-1] != '\\' )
			strcat( fpath, "\\" );
#else
		if( fpath[strlen( fpath )-1] != '/' )
			strcat( fpath, "/" );
#endif

		strcat( fpath, th.m_block.header.name );

		switch( th.m_block.header.typeflag ) {
			case REGTYPE :
                if( (p=strfind( th.m_block.header.name, (char *) "/" )) != NULL ) {
                    char fpath2[_MAX_PATH];

                    strcpy( fpath2, fpath );
                    p = strlastfind( fpath2, (char *) "/" );
                    *p = 0;

                    MkDir( fpath2 );
                }

				bLoop = UnTar( fpath, & th );
				break;

			case DIRTYPE :
				bLoop = MkDir( fpath );
				break;

            case AREGTYPE :
                break;

			default :
				printf( "\n [W] Not supported file type[%d] !" , th.m_block.header.typeflag );
				break;

		}

	}

	_close( m_TarFile );

	if( bLoop == true )
		printf( "\n*success of all extract files" );

	return bLoop;
}

/**
 * @brief     _GetFileSize
 * @param     int fd
 * @param     unsigned long * pSize
 * @return    unsigned long
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2009-09-23 19:29:18
 * @warning
 */
unsigned long CFileTar::_GetFileSize( int fd, unsigned long *pSize )
{
    struct stat filestat;

    fstat( fd, &filestat );
    return filestat.st_size;
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CFileTar::Octal2Deciaml
	\author   ��ö��
	\param    pByte �������� char *
	\param    size �������� int
	\return   unsigned long
	\version  0.0.99
	\date     2009-09-24 15:27:35
	\warning
*/
unsigned long CFileTar::Octal2Deciaml( char *pByte, int size )
{
	unsigned long overflow;
	unsigned long value=0;

	while( true ) {
		if( ! ISODIGIT( *pByte ) )
			return (unsigned long) -1;

		value += ( *pByte - '0' );
		if( --size <= 1 )
			break;

		value <<= LG_8;
		overflow |= value ^ (value << LG_8 >> LG_8);
		++ pByte;

	}

	return value;

}

/**
 * @brief     GetDate
 * @param     struct _utimbuf * pTime
 * @param     char * pByte
 * @param     int size
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2009-09-24 16:17:25
 * @warning
 */
void CFileTar::GetDate( struct _utimbuf *pTime, char *pByte, int size )
{
	pTime->modtime = Octal2Deciaml( pByte, size );

	// pTime->actime = Octal2Deciaml( pByte, size );

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CFileTar::MkDir
		\author   ��ö��
		\param    directory �������� char *
		\return   bool
		\version  0.0.99
		\date     2009-09-24 17:31:13
		\warning
*/
bool CFileTar::MkDir( char *directory )
{
	printf( "\n*make directory(%s)" , directory );
	//return _mkdir( directory ) == 0;

    bool bRet;
    char dirName[256];
    char *p=directory;
    char *q=dirName;

    dirName[0] = 0;
    while( *p ) {
        if( ('\\' == *p) || ('/'==*p)) {
            if( ':' != *(p-1) ) {
                if( dirName[0] != 0 && strcmp( dirName, "\\" ) != 0 ) {
                    _mkdir( dirName );
                }
            }
        }

        *q++ = *p++;
        *q = '\0';
    }
    bRet = _mkdir( dirName );

    if( bRet == 0 ) {
        // bRet = ( GetLastError() == ERROR_ALREADY_EXISTS );
    }

    return true;
}
