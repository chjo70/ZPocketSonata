//Author :- Nish [nishforever@vsnl.com]


#ifdef _WIN32
#include "../../A50SigAnal/stdafx.h"
#else

#endif

#include "FileTar.h"

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

int CFileTar::AddFile(char *fname, char *desc)
{
	char fullpath[_MAX_PATH];
	strcpy(fullpath,FilePath);
	strcat(fullpath,fname);
	HANDLE hFile;
	DWORD size;

	hFile=CreateFile(fullpath,GENERIC_READ,0,NULL,
		OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile==INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFile);
		return 1;
	}
	size=GetFileSize(hFile,NULL);
	if(size==0xFFFFFFFF)
	{
		CloseHandle(hFile);
		return 1;
	}
	
	if(m_TarHeader.IncrementCount()==0)
	{
		CloseHandle(hFile);
		return 1;
	}
	TarIndex *pTarIndex=new TarIndex;
	strcpy(pTarIndex->FileName,fname);
	strcpy(pTarIndex->Description,desc);	
	pTarIndex->Size=size;
	
	m_pTarIndex[m_TarHeader.GetCount()]=pTarIndex;

	CloseHandle(hFile);
	return 0;
}

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
	if((fdout=open(tarfullpath,_O_CREAT|_O_WRONLY|_O_BINARY|_O_TRUNC,
		_S_IWRITE))<0)
	{
		_close(fdout);
		return 1;
	}	
	ret=_write(fdout,(char *) &m_TarHeader,sizeof(UNI_BLOCK));
	int ssize=m_TarHeader.GetCount()*sizeof (TarIndex)+sizeof(UNI_BLOCK);
	for(i=1;i<=m_TarHeader.GetCount();i++)
	{
		m_pTarIndex[i]->Start=ssize;
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
	int len;
	if((fdin=_open(fpath,_O_RDONLY|_O_BINARY))<0)
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
		\return   BOOL
		\version  0.0.99
		\date     2009-09-24 14:42:33
		\warning
*/
BOOL CFileTar::GetTarInfo( char *pTarFile, TarHeader *pTarHeader )
{
	if( m_TarFile < 0 ) {
        printf( "\n pTarFile[%s]" , pTarFile );
		if( ( m_TarFile=_open( pTarFile,_O_BINARY|_O_RDONLY ) ) < 0 ) {
			return FALSE;
		}
	}

	memset( pTarHeader, 0, sizeof(UNI_BLOCK) );
	int nRead=_read( m_TarFile, (char *) pTarHeader, sizeof(UNI_BLOCK) );

	pTarHeader->m_filesize = Octal2Deciaml( pTarHeader->m_block.header.size, sizeof(pTarHeader->m_block.header.size) );
	GetDate( & pTarHeader->m_time, pTarHeader->m_block.header.mtime, sizeof(pTarHeader->m_block.header.mtime) );

	if( nRead <= 0 ) {
		return FALSE;
	}

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CFileTar::UnTar
		\author   ��ö��
		\param    pDestFile �������� char *
		\return   BOOL
		\version  0.0.99
		\date     2009-09-24 15:08:28
		\warning
*/
BOOL CFileTar::UnTar( char *pDestFile, TarHeader *pTarHeader )
{
	int fdout;
	int nRead, nWrite;
	UNI_BLOCK *pBlock;

	struct _stat filestat;

#ifdef _WIN32
	if( ( fdout = _open( pDestFile, _O_CREAT | _O_WRONLY | _O_BINARY | _O_TRUNC, _S_IWRITE ) ) < 0 ) {
#else
	if( ( fdout = _open( pDestFile, _O_CREAT | _O_WRONLY | _O_BINARY | _O_TRUNC ) ) < 0 ) {
#endif
		_close( fdout );
		printf( "\n*can't creat the file(%s)" , pDestFile );
		return FALSE;
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
			return FALSE;
		}

		rem -= sizeof(UNI_BLOCK);
	}

	if( rem > 0 ) {
		nRead = _read( m_TarFile, buff, sizeof(UNI_BLOCK) );
		nWrite = _write( fdout, buff, rem );
		if( nRead != sizeof(UNI_BLOCK) || nRead <= 0 || nWrite != (int) rem ) {
			_close( fdout );
			printf( "\n*can't read or write the file" );
			return FALSE;
		}
	}

	// ���� ������ ��¥�� �����Ѵ�.
	_fstat( fdout, & filestat );
	pTarHeader->m_time.actime = filestat.st_atime;

	_close( fdout );

	_utime( pDestFile, & pTarHeader->m_time );

	printf( "\n*extract the file(%s)" , pDestFile );
	return TRUE;
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
	BOOL bLoop=TRUE;
	char fpath[_MAX_PATH];
	TarHeader th;

	// UNI_BLOCK *pBlock;

	printf( "\n untar %s into %s" , pTarFile, pDestpath );
    bLoop = MkDir( pDestpath );

	while( bLoop ) {

		if( FALSE == GetTarInfo( pTarFile, & th ) ) {
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

	if( bLoop == TRUE )
		printf( "\n*success of all extract files" );

	return bLoop;
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CFileTar::_GetFileSize
		\author   ��ö��
		\param    fd �������� int
		\param    pSize �������� DWORD *
		\return   DWORD
		\version  0.0.98
		\date     2009-09-23 19:29:18
		\warning
*/
DWORD CFileTar::_GetFileSize( int fd, DWORD *pSize )
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

//////////////////////////////////////////////////////////////////////////
/*! \brief    CFileTar::GetDate
		\author   ��ö��
		\param    pTime �������� struct _utimbuf
		\param    pByte �������� char *
		\param    size �������� int
		\return   void
		\version  0.0.99
		\date     2009-09-24 16:17:25
		\warning
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
		\return   BOOL
		\version  0.0.99
		\date     2009-09-24 17:31:13
		\warning
*/
BOOL CFileTar::MkDir( char *directory )
{
	printf( "\n*make directory(%s)" , directory );
	return _mkdir( directory ) == 0;

}
