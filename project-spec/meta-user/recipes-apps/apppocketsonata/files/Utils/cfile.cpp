#include "cfile.h"

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int CFile::shareDenyNone=4;
int CFile::typeBinary=1;
int CFile::modeRead=8;

/**
 * @brief CFile::CFile
 */
CFile::CFile()
{
    m_iFile = -1;
}

/**
 * @brief CFile::~CFile
 */
CFile::~CFile()
{
    if( m_iFile > 0 ) {
        close( m_iFile );

    }

}

/**
 * @brief CFile::Open
 * @param pstPathname
 * @param iMode
 */
bool CFile::Open( const char *pstPathname, int iMode )
{
    bool bRet=true;

    m_iFile = open( pstPathname, O_RDONLY );

    if( m_iFile < 0 ) {
        bRet = false;
    }

    return true;

}

/**
 * @brief CFile::Read
 * @param pstBuffer
 * @param iLength
 * @return
 */
int CFile::Read( void *pstBuffer, int iLength )
{
    int iRead;

    iRead = read( m_iFile, pstBuffer, iLength );
    return iRead;

}

/**
 * @brief CFile::Close
 */
void CFile::Close()
{
    close( m_iFile );
}


unsigned int CFile::GetFileLength()
{
    unsigned int uiSize;

    uiSize = lseek( m_iFile, 0, SEEK_END );

    lseek( m_iFile, 0, SEEK_SET );
    return uiSize;
}
