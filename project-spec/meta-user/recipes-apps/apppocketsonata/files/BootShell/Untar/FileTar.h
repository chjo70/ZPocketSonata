//Author :- Nish [nishforever@vsnl.com]

#ifdef _WIN32
#include <io.h>
#include <direct.h>
#include <stdbool.h>
#include <sys/utime.h>

#else
#include <ioLib.h>
#include <string.h>
#include <stdio.h>
#include <utime.h>
#endif

#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

#ifdef __VXWORKS__

#include "types/vxTypesOld.h"

//#define unsigned long ULONG

#define _write write
//#define _open(A,B) open(A,B,0666)
#define _read read
#define _close close
#define _utime utime
#define _fstat fstat
#define _mkdir mkdir

#define _utimbuf utimbuf
#define _stat stat

#define HANDLE int
#define CloseHandle close
#define CreateFile(A,B,C,D,E,F,G) open(A,O_CREAT,0666)
#define INVALID_HANDLE_VALUE 0
#define GetFileSize _GetFileSize

#define _O_RDONLY O_RDONLY
#define _O_CREAT O_CREAT
#define _O_WRONLY O_WRONLY
#define _O_BINARY 0
#define _O_TRUNC 0
#define _S_IWRITE 0

#elif _MFC_VER
#define open _open

#endif

#ifdef _WIN32
#define	FOLDER_DELIMETER	(\)
#else
#define	FOLDER_DELIMETER	/
#endif



/* Log base 2 of common values.  */
#define LG_8 3



#define TAR_MAX_FILES 1024
#define NBUFFSIZE 8092

#ifndef _MAX_PATH
#define _MAX_PATH   1024 /* max. length of full pathname */
#endif

#define _MAX_DRIVE  3   /* max. length of drive component */
#define _MAX_DIR    256 /* max. length of path component */
#define _MAX_FNAME  256 /* max. length of file name component */



#define ISDIGIT(c) ((unsigned) (c) - '0' <= 9)
#define ISODIGIT(c) ((unsigned) (c) - '0' <= 7)



/* Values used in typeflag field.  */
#define REGTYPE  '0'            /* regular file */
#define AREGTYPE '\0'           /* regular file */
#define LNKTYPE  '1'            /* link */
#define SYMTYPE  '2'            /* reserved */
#define CHRTYPE  '3'            /* character special */
#define BLKTYPE  '4'            /* block special */
#define DIRTYPE  '5'            /* directory */
#define FIFOTYPE '6'            /* FIFO special */
#define CONTTYPE '7'            /* reserved */

#define TAR_HEADER	(512)

//////////////////////////////////////////////////////////////////////////
/* POSIX header.  */
struct posix_header
{												/* byte offset */
  char name[100];				/*   0 */
  char mode[8];					/* 100 */
  char uid[8];					/* 108 */
  char gid[8];					/* 116 */
  char size[12];				/* 124 */
  char mtime[12];				/* 136 */
  char chksum[8];				/* 148 */
  char typeflag;				/* 156 */
  char linkname[100];		/* 157 */
  char magic[6];				/* 257 */
  char version[2];			/* 263 */
  char uname[32];				/* 265 */
  char gname[32];				/* 297 */
  char devmajor[8];			/* 329 */
  char devminor[8];			/* 337 */
  char prefix[155];			/* 345 */
												/* 500 */
};

struct star_header
{				/* byte offset */
  char name[100];		/*   0 */
  char mode[8];			/* 100 */
  char uid[8];			/* 108 */
  char gid[8];			/* 116 */
  char size[12];		/* 124 */
  char mtime[12];		/* 136 */
  char chksum[8];		/* 148 */
  char typeflag;		/* 156 */
  char linkname[100];		/* 157 */
  char magic[6];		/* 257 */
  char version[2];		/* 263 */
  char uname[32];		/* 265 */
  char gname[32];		/* 297 */
  char devmajor[8];		/* 329 */
  char devminor[8];		/* 337 */
  char prefix[131];		/* 345 */
  char atime[12];               /* 476 */
  char ctime[12];               /* 488 */
                                /* 500 */
};

/* Sparse files are not supported in POSIX ustar format.  For sparse files
   with a POSIX header, a GNU extra header is provided which holds overall
   sparse information and a few sparse descriptors.  When an old GNU header
   replaces both the POSIX header and the GNU extra header, it holds some
   sparse descriptors too.  Whether POSIX or not, if more sparse descriptors
   are still needed, they are put into as many successive sparse headers as
   necessary.  The following constants tell how many sparse descriptors fit
   in each kind of header able to hold them.  */

#define SPARSES_IN_EXTRA_HEADER  16
#define SPARSES_IN_OLDGNU_HEADER 4
#define SPARSES_IN_SPARSE_HEADER 21

/* tar Header Block, GNU extensions.  */

/* In GNU tar, SYMTYPE is for to symbolic links, and CONTTYPE is for
   contiguous files, so maybe disobeying the `reserved' comment in POSIX
   header description.  I suspect these were meant to be used this way, and
   should not have really been `reserved' in the published standards.  */

/* *BEWARE* *BEWARE* *BEWARE* that the following information is still
   boiling, and may change.  Even if the OLDGNU format description should be
   accurate, the so-called GNU format is not yet fully decided.  It is
   surely meant to use only extensions allowed by POSIX, but the sketch
   below repeats some ugliness from the OLDGNU format, which should rather
   go away.  Sparse files should be saved in such a way that they do *not*
   require two passes at archive creation time.  Huge files get some POSIX
   fields to overflow, alternate solutions have to be sought for this.  */

/* Descriptor for a single file hole.  */

struct sparse
{				/* byte offset */
  char offset[12];		/*   0 */
  char numbytes[12];		/*  12 */
				/*  24 */
};

/* Extension header for sparse files, used immediately after the GNU extra
   header, and used only if all sparse information cannot fit into that
   extra header.  There might even be many such extension headers, one after
   the other, until all sparse information has been recorded.  */

struct sparse_header
{				/* byte offset */
  struct sparse sp[SPARSES_IN_SPARSE_HEADER];
				/*   0 */
  char isextended;		/* 504 */
				/* 505 */
};

/* The old GNU format header conflicts with POSIX format in such a way that
   POSIX archives may fool old GNU tar's, and POSIX tar's might well be
   fooled by old GNU tar archives.  An old GNU format header uses the space
   used by the prefix field in a POSIX header, and cumulates information
   normally found in a GNU extra header.  With an old GNU tar header, we
   never see any POSIX header nor GNU extra header.  Supplementary sparse
   headers are allowed, however.  */

struct oldgnu_header
{				/* byte offset */
  char unused_pad1[345];	/*   0 */
  char atime[12];		/* 345 Incr. archive: atime of the file */
  char ctime[12];		/* 357 Incr. archive: ctime of the file */
  char offset[12];		/* 369 Multivolume archive: the offset of
				   the start of this volume */
  char longnames[4];		/* 381 Not used */
  char unused_pad2;		/* 385 */
  struct sparse sp[SPARSES_IN_OLDGNU_HEADER];
				/* 386 */
  char isextended;		/* 482 Sparse file: Extension sparse header
				   follows */
  char realsize[12];		/* 483 Sparse file: Real size*/
				/* 495 */
};





#define SPARSES_IN_STAR_HEADER      4
#define SPARSES_IN_STAR_EXT_HEADER  21

struct star_in_header {
  char fill[345];       /*   0  Everything that is before t_prefix */
  char prefix[1];       /* 345  t_name prefix */
  char fill2;           /* 346  */
  char fill3[8];        /* 347  */
  char isextended;      /* 355  */
  struct sparse sp[SPARSES_IN_STAR_HEADER]; /* 356  */
  char realsize[12];    /* 452  Actual size of the file */
  char offset[12];      /* 464  Offset of multivolume contents */
  char atime[12];       /* 476  */
  char ctime[12];       /* 488  */
  char mfill[8];        /* 500  */
  char xmagic[4];       /* 508  "tar" */
};

struct star_ext_header {
  struct sparse sp[SPARSES_IN_STAR_EXT_HEADER];
  char isextended;
};

// �� ����
typedef union {
  char buffer[TAR_HEADER];
  struct posix_header header;
  struct star_header star_header;
  struct oldgnu_header oldgnu_header;
  struct sparse_header sparse_header;
  struct star_in_header star_in_header;
  struct star_ext_header star_ext_header;

} UNI_BLOCK ;

class CFileTar
{
private :
	int m_TarFile;

public:
	struct TarIndex
	{
		long Start;
		long Size;
		char FileName[_MAX_FNAME];
		char Description[256];
	};
	struct TarHeader
	{
	public:
		UNI_BLOCK m_block;

	public :
		unsigned long m_filesize;
		struct _utimbuf m_time;

	public:
		TarHeader();
		int IncrementCount();
		int GetCount();
		const char * GetDescription();
	};

public:
	bool MkDir( char *directory );
	void GetDate( struct _utimbuf *pTime, char *pByte, int size );
	unsigned long Octal2Deciaml( char *pByte, int size );
	unsigned long _GetFileSize( int fd, unsigned long *pSize );
	int UnTar( char *pTarFile, char *pDestpath );
	bool UnTar( char *pDestFile, TarHeader *pTarHeader );
	bool GetTarInfo(char *TarFile,TarHeader *pTarHeader);
	bool SetHeaderDescription(char *strdesc);
	const char * GetHeaderDescription();
	int CreateTar(char *TarFName, char *TarPath = NULL);
	int AddFile(char *fname, char *desc);
	void SetFilePath(char *path);
	CFileTar();
	virtual ~CFileTar();

private:
	TarHeader m_TarHeader;
	TarIndex* m_pTarIndex[TAR_MAX_FILES];
	char FilePath[_MAX_PATH];
	int AppendFile(int fdout, char *fpath);
};
