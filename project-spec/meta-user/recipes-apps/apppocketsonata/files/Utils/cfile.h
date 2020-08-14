#ifndef CFILE_H
#define CFILE_H

#include <fcntl.h>


class CFile
{
private:
    int m_iFile;

public:
    static unsigned int shareDenyNone;
    static unsigned int typeBinary;
    static unsigned int modeRead;
    static unsigned int modeReadWrite;
    static unsigned int modeCreate;

public:
    CFile();
    virtual ~CFile();

    bool Open( const char *pstPathname, int iMode );
    int Read( void *pstBuffer, int iLength );
    int Write( void *pstBuffer, int iLength );
    void Close();
    unsigned int GetFileLength();
};

#endif // CFILE_H