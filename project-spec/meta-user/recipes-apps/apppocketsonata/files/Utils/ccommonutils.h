#ifndef CCOMMONUTILS_H
#define CCOMMONUTILS_H

#include "../Include/system.h"
#include "../Utils/cthread.h"

#ifdef _MSC_VER
int clock_gettime(int X, struct timeval *tv);
LARGE_INTEGER getFILETIMEoffset();
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

    static void GetStringBand( char *pBuffer, int iBand );

    static ENUM_COLLECTBANK GetEnumCollectBank( unsigned int uiCh );

    static void Disp_FinePDW( STR_PDWDATA *pPDWData );

};

#endif // CCOMMONUTILS_H
