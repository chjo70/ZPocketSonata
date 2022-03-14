#ifndef CCOMMONUTILS_H
#define CCOMMONUTILS_H

//#include "../Include/system.h"
#include "../Utils/cthread.h"

#ifdef _MSC_VER
int clock_gettime(int X, struct timeval *tv);
LARGE_INTEGER getFILETIMEoffset();
int gettimeofday(struct timeval * tp, struct timezone * tzp);
#endif


class CCommonUtils
{
private:
    ENUM_MODE m_enMode;

public:
    CCommonUtils();

public:
    static void SendLan( UINT uiOpCode, void *pData, UINT uiLength );
    static void CloseSocket();

    static bool IsValidLanData( STR_MessageData *pMsg );
    static bool IsValidThread( STR_MessageData *pMsg );
    static void DiffTimespec(struct timespec *result, struct timespec *start, struct timespec *stop=NULL );

    static void AllSwapData32( void *pData, int iLength );
    static void swapByteOrder( unsigned int& ui );
    static void swapByteOrder(double & d);
    static void swapByteOrder(double *p, int iSize );
    static void swapByteOrder( unsigned short & us);

    static ENUM_COLLECTBANK GetEnumCollectBank( unsigned int uiCh );

    static void Disp_FinePDW( STR_PDWDATA *pPDWData );

    static void getStringPresentTime( char *pString );

    static int CopyFile( const char *src_file, const char *dest_file, int overwrite, int copy_attr );

    static void SetUnitType();

    static const char *strcasestr( const char *haystack, const char *needle );

};

#endif // CCOMMONUTILS_H
