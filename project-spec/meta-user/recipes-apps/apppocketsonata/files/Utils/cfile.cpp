#ifdef _MSC_VER
#include "stdafx.h"

#include <io.h>

#else
#include <unistd.h>
#endif

#include "cfile.h"

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


unsigned int CMyFile::shareDenyNone=0;
unsigned int CMyFile::typeBinary=0;
unsigned int CMyFile::modeReadWrite=0;
unsigned int CMyFile::modeRead=O_RDONLY;
unsigned int CMyFile::modeCreate=O_CREAT;

/**
 * @brief CMyFile::CMyFile
 */
CMyFile::CMyFile()
{
    m_iFile = -1;
}

/**
 * @brief CMyFile::~CMyFile
 */
CMyFile::~CMyFile()
{
    if( m_iFile > 0 ) {
        close( m_iFile );

    }

}

/**
 * @brief CMyFile::Open
 * @param pstPathname
 * @param iMode
 */
bool CMyFile::Open( const char *pstPathname, int iMode )
{
    bool bRet=true;

#ifdef _MSC_VER
    m_iFile = open( pstPathname, iMode );
#else
    m_iFile = open( pstPathname, iMode, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH );
#endif

    if( m_iFile < 0 ) {
        bRet = false;
    }

    return true;

}

/**
 * @brief CMyFile::Read
 * @param pstBuffer
 * @param iLength
 * @return
 */
int CMyFile::Read( void *pstBuffer, int iLength )
{
    int iRead;

    iRead = read( m_iFile, pstBuffer, iLength );
    return iRead;

}

/**
 * @brief CMyFile::Write
 * @param pstBuffer
 * @param iLength
 * @return
 */
int CMyFile::Write( void *pstBuffer, int iLength )
{
    int iRead;

    iRead = write( m_iFile, pstBuffer, iLength );
    return iRead;

}

/**
 * @brief CMyFile::Close
 */
void CMyFile::Close()
{
    close( m_iFile );
}


unsigned int CMyFile::GetFileLength()
{
    unsigned int uiSize;

    uiSize = lseek( m_iFile, 0, SEEK_END );

    lseek( m_iFile, 0, SEEK_SET );
    return uiSize;
}
