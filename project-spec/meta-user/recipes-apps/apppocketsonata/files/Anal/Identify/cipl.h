#ifndef CIPL_H
#define CIPL_H

#include <string.h>

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
        pIPL->iSigType -= 1;

        // 주파수 형태
        if( pIPL->stFreq.uiType == (UINT) IPL_FIXED ) {
            pIPL->stFreq.uiType = RadarModeFreqType::enumFIXED;
        }
        else if( pIPL->stFreq.uiType == (UINT) IPL_RANDOM_AGILE ) {
            pIPL->stFreq.uiType = RadarModeFreqType::enumAGILE;
        }
        else if( pIPL->stFreq.uiType == (UINT) IPL_PATTERN_AGILE ) {
            pIPL->stFreq.uiType = RadarModeFreqType::enumPATTERN;
        }
        else if( pIPL->stFreq.uiType == (UINT) IPL_HOPPING ) {
            pIPL->stFreq.uiType = RadarModeFreqType::enumHOPPING;
        }
        else {

        }

        // 주파수 값
        pIPL->stFreq.iLow /= 1000;
        pIPL->stFreq.iHigh /= 1000;

        // 주파수 레벨값
        for( i=0 ; i < MAX_FREQ_PRI_STEP ; ++i ) {
            pIPL->stFreq.swtValLow[i] /= 1000;
            pIPL->stFreq.swtValHgh[i] /= 1000;
        }

        // PRI 형태
        if( pIPL->stPRI.uiType == (UINT) IPL_STABLE ) {
            pIPL->stPRI.uiType = RadarModePRIType::enumStable;
        }
        else if( pIPL->stPRI.uiType == (UINT) IPL_STAGGER ) {
            pIPL->stPRI.uiType = RadarModePRIType::enumSTAGGER;
        }
        else if( pIPL->stPRI.uiType == (UINT) IPL_JITTER ) {
            pIPL->stPRI.uiType = RadarModePRIType::enumJITTER;
        }
        else if( pIPL->stPRI.uiType == (UINT) IPL_PATTERN ) {
            pIPL->stPRI.uiType = RadarModePRIType::enumPATTERN;
        }
        else if( pIPL->stPRI.uiType == (UINT) IPL_DWELL ) {
            pIPL->stPRI.uiType = RadarModePRIType::enumDwellSWITCH;
        }
        else {

        }

        // PRI 값 
        pIPL->stPRI.iLow /= 1000;
        pIPL->stPRI.iHigh /= 1000;

        // PRI 레벨 값
        for( i=0 ; i < MAX_FREQ_PRI_STEP ; ++i ) {
            pIPL->stPRI.swtValLow[i] /= 1;
            pIPL->stPRI.swtValHgh[i] /= 1;
        }

        // 스캔 형태
        switch( pIPL->stAS.type ) {
        case E_AET_SCAN_STEADY :
            pIPL->stAS.type = ScanType::enumD_Non_Scanning;
            break;

        case E_AET_SCAN_UNI_DIRECTIONAL :
            pIPL->stAS.type = ScanType::enumU_Uni_Directional_Sector_Plane_Undertermined;
            break;

        case E_AET_SCAN_BI_DIRECTIONAL :
            pIPL->stAS.type = ScanType::enumV_Bi_Directional_Sector_Plane_Undetermined;
            break;

        case E_AET_SCAN_CONICAL :
            pIPL->stAS.type = ScanType::enumF_Conical;
            break;

        case E_AET_SCAN_CIRCULAR :
            pIPL->stAS.type = ScanType::enumA_Circular;
            break;

        default :
            pIPL->stAS.type = ScanType::enumUndefinedScanType;
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
