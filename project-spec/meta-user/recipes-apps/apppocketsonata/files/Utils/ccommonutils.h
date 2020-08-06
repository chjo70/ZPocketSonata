#ifndef CCOMMONUTILS_H
#define CCOMMONUTILS_H

#include "../Include/system.h"
#include "../Utils/cthread.h"

class CCommonUtils
{
public:
    CCommonUtils();

public:
    static void SendLan( UINT uiOpCode, void *pData, UINT uiLength );
    static bool IsValidLanData( STR_MessageData *pMsg );
    static bool IsValidThread( STR_MessageData *pMsg );

};

#endif // CCOMMONUTILS_H
