#ifndef CIPL_H
#define CIPL_H

#include <string.h>

#include "../../Include/system.h"

#define MAX_IPL                 (2000)

class CIPL
{
private:
    // IPL 관련 정보
    STR_IPL_START m_strIPLStart;

    STR_IPL m_strIPL[MAX_IPL];

    int m_iTotalIPL;

private:
    void InitVar();

public:
    CIPL();

    STR_IPL_START *getIPLStart() { return & m_strIPLStart; } ;
    void setIPLStart( STR_IPL_START *pIPLStart ) {
        memcpy( & m_strIPLStart, pIPLStart, sizeof(STR_IPL_START) );

        m_iTotalIPL = 0;
    } ;

    STR_IPL *getIPL( int iIndex ) { return & m_strIPL[iIndex]; }
    void setIPL( STR_IPL *pIPL, int iIndex=-1 ) {
        if( iIndex >= 0 ) {
            memcpy( & m_strIPL[iIndex], pIPL, sizeof(STR_IPL) );
        }
        else {
            if( m_iTotalIPL < MAX_IPL ) {
                memcpy( & m_strIPL[m_iTotalIPL], pIPL, sizeof(STR_IPL) );
                ++ m_iTotalIPL;
            }
            else {

            }
        }
    } ;


};

#endif // CIPL_H
