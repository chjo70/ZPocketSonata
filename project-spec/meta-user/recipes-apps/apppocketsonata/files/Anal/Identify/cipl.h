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
    void trIPL( STR_IPL *pIPL ) {
        int i;

        pIPL->sigType -= 1;

        if( pIPL->frq.type == IPL_FIXED ) {
            pIPL->frq.type = RadarModeFreqType::enumFIXED;
        }
        else if( pIPL->frq.type == IPL_RANDOM_AGILE ) {
            pIPL->frq.type = RadarModeFreqType::enumAGILE;
        }
        else if( pIPL->frq.type == IPL_PATTERN_AGILE ) {
            pIPL->frq.type = RadarModeFreqType::enumPATTERN;
        }
        else if( pIPL->frq.type == IPL_HOPPING ) {
            pIPL->frq.type = RadarModeFreqType::enumHOPPING;
        }
        else {

        }

        pIPL->frq.low /= 1000;
        pIPL->frq.hgh /= 1000;

        for( i=0 ; i < _spMaxSwtLev ; ++i ) {
            pIPL->frq.swtValLow[i] /= 1000;
            pIPL->frq.swtValHgh[i] /= 1000;
        }

        if( pIPL->pri.type == IPL_STABLE ) {
            pIPL->pri.type = RadarModePRIType::enumStable;
        }
        else if( pIPL->pri.type == IPL_STAGGER ) {
            pIPL->pri.type = RadarModePRIType::enumSTAGGER;
        }
        else if( pIPL->pri.type == IPL_JITTER ) {
            pIPL->pri.type = RadarModePRIType::enumJITTER;
        }
        else if( pIPL->pri.type == IPL_PATTERN ) {
            pIPL->pri.type = RadarModePRIType::enumPATTERN;
        }
        else if( pIPL->pri.type == IPL_DWELL ) {
            pIPL->pri.type = RadarModePRIType::enumDwellSWITCH;
        }
        else {

        }


        pIPL->pri.low /= 1000;
        pIPL->pri.hgh /= 1000;

        for( i=0 ; i < _spMaxSwtLev ; ++i ) {
            pIPL->pri.swtValLow[i] /= 1;
            pIPL->pri.swtValHgh[i] /= 1;
        }



    }

    void setIPL( STR_IPL *pIPL, int iIndex=-1 ) {
        if( pIPL != NULL ) {
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
        }
    } ;


};

#endif // CIPL_H
