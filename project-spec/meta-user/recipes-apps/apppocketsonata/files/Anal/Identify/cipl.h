#ifndef CIPL_H
#define CIPL_H

#include <string.h>

//#include "../../Include/system.h"

#include "../../System/csysconfig.h"

#define MAX_IPL                 (20000)

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
    void setIPLStart( STR_IPL_START *pIPLStart );

    STR_IPL *getIPL( int iIndex ) { 
        STR_IPL *pIPL;

        if( iIndex < MAX_IPL ) {
            pIPL = & m_strIPL[iIndex];
        }
        else {
            pIPL = & m_strIPL[MAX_IPL-1];
        }
        return pIPL;
    }

    void trIPL( STR_IPL *pIPL ) {
        int i;

        // 신호 형태
        pIPL->sigType -= 1;

        // 주파수 형태
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

        // 주파수 값
        pIPL->frq.low /= 1000;
        pIPL->frq.hgh /= 1000;

        // 주파수 레벨값
        for( i=0 ; i < MAX_FREQ_PRI_STEP ; ++i ) {
            pIPL->frq.swtValLow[i] /= 1000;
            pIPL->frq.swtValHgh[i] /= 1000;
        }

        // PRI 형태
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

        // PRI 값 
        pIPL->pri.low /= 1000;
        pIPL->pri.hgh /= 1000;

        // PRI 레벨 값
        for( i=0 ; i < MAX_FREQ_PRI_STEP ; ++i ) {
            pIPL->pri.swtValLow[i] /= 1;
            pIPL->pri.swtValHgh[i] /= 1;
        }

        // 스캔 형태
        switch( pIPL->as.type ) {
        case E_AET_SCAN_STEADY :
            pIPL->as.type = ScanType::enumD_Non_Scanning;
            break;

        case E_AET_SCAN_UNI_DIRECTIONAL :
            pIPL->as.type = ScanType::enumU_Uni_Directional_Sector_Plane_Undertermined;
            break;

        case E_AET_SCAN_BI_DIRECTIONAL :
            pIPL->as.type = ScanType::enumV_Bi_Directional_Sector_Plane_Undetermined;
            break;

        case E_AET_SCAN_CONICAL :
            pIPL->as.type = ScanType::enumF_Conical;
            break;

        case E_AET_SCAN_CIRCULAR :
            pIPL->as.type = ScanType::enumA_Circular;
            break;

        default :
            pIPL->as.type = ScanType::enumUndefinedScanType;
            break;
        }

    }

    void setIPL( STR_IPL *pIPL, int iIndex=-1 ) {
        if( pIPL != NULL ) {
            if( iIndex >= 0 && iIndex < MAX_IPL ) {
                memcpy( & m_strIPL[iIndex], pIPL, sizeof(STR_IPL) );
            }
            else {
                if( m_iTotalIPL < MAX_IPL ) {
                    memcpy( & m_strIPL[m_iTotalIPL], pIPL, sizeof(STR_IPL) );
                    
                }
                else {

                }

                ++ m_iTotalIPL;
            }
        }
    } ;

    inline int GetTotalIPL() { return m_iTotalIPL; }


};

#endif // CIPL_H
