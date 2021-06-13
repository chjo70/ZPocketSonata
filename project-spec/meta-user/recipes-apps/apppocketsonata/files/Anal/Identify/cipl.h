#ifndef CIPL_H
#define CIPL_H

#include <string.h>

#include "../../Include/system.h"

#include "../../System/csysconfig.h"

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

        GP_SYSCFG->SetIPLVersion( m_strIPLStart.uiIPLVersion );

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

                    // 스캔 정보 변경
                    switch( m_strIPL[m_iTotalIPL].as.type ) {
                        case E_AET_SCAN_STEADY :
                            m_strIPL[m_iTotalIPL].as.type = ScanType::enumD_Non_Scanning;
                            break;

                        case E_AET_SCAN_UNI_DIRECTIONAL :
                            m_strIPL[m_iTotalIPL].as.type = ScanType::enumU_Uni_Directional_Sector_Plane_Undertermined;
                            break;

                        case E_AET_SCAN_BI_DIRECTIONAL :
                            m_strIPL[m_iTotalIPL].as.type = ScanType::enumV_Bi_Directional_Sector_Plane_Undetermined;
                            break;

                        case E_AET_SCAN_CONICAL :
                            m_strIPL[m_iTotalIPL].as.type = ScanType::enumF_Conical;
                            break;

                        case E_AET_SCAN_CIRCULAR :
                            m_strIPL[m_iTotalIPL].as.type = ScanType::enumA_Circular;
                            break;

                        default :
                            m_strIPL[m_iTotalIPL].as.type = ScanType::enumUndefinedScanType;
                            break;

                    }
                    ++ m_iTotalIPL;
                }
                else {

                }
            }
        }
    } ;


};

#endif // CIPL_H
