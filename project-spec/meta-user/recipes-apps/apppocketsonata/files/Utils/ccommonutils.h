#ifndef CCOMMONUTILS_H
#define CCOMMONUTILS_H

#include "../Include/system.h"


class CCommonUtils
{
public:
    CCommonUtils();

public:
    static void SendLan( UINT uiOpCode, void *pData, UINT uiLength );

};

#endif // CCOMMONUTILS_H
