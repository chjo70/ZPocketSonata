#ifndef CFILE_H
#define CFILE_H


class CFile
{
private:
    int m_iFile;

public:
    static int shareDenyNone;
    static int typeBinary;
    static int modeRead;

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
