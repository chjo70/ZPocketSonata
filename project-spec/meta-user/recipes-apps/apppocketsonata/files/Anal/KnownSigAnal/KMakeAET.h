// KMakeAET.h: interface for the CKMakeAET class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KMAKEAET_H__0B6C1D4B_0545_4DD1_9E8C_1FDB63EDF929__INCLUDED_)
#define AFX_KMAKEAET_H__0B6C1D4B_0545_4DD1_9E8C_1FDB63EDF929__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../SigAnal/MakeAET.h"

#include "../Identify/ELUtil.h"

#include "KnownSigAnal.h"

#ifdef __cplusplus

typedef struct {
    float fKnownSuccessRatio;   // 추적 성공율 [%]
    int iIdxEmitter;            // PRI Emitter Index   

} STR_KWNINFO;

typedef struct {
    SRxLOBData stLOBData;
    STR_KWNINFO stKnownInfo;

} STR_KWNLOB;

class CKMakeAET : public CMakeAET
{
private :
    STR_KWNLOB m_KwnLOB[MAX_AET + 1];       // 추적 성공하면 첫번째 LOB 데이터는 추적 성공한 LOB 정보 임.

    SRxABTData *m_pTrkABT;

protected :
    CKnownSigAnal *m_pKnownSigAnal;

    //##ModelId=452B0C5203DC
    int m_iCoNewAet;
    int m_IdxUpdAet;

    STR_EMITTER *m_pEmitter;

public:
    void UpdatePRI( SRxLOBData *pUpdAetPri );
    void UpdateFreq( SRxLOBData *pUpdAetFrq );

    SRxLOBData *GetLOBData(int iIndex) {
        return &m_KwnLOB[iIndex].stLOBData;
    }

    STR_KWNINFO *GetKnownInfo(int iIndex) {
        return &m_KwnLOB[iIndex].stKnownInfo;
    }

    //##ModelId=452B0C53000D
    inline void SetCoNewAet( int iCount ) { m_iCoNewAet=iCount; }
    //##ModelId=452B0C53000F
    inline void ClearCoAet() { m_iCoLOB=0; }
    
    /**
     * @brief     GetCoLOB
     * @return    int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-09, 10:53
     * @warning
     */
    inline int GetCoLOB() { 
        return m_iCoLOB; 
    }

    /**
     * @brief     SetKnownSuccessRatio
     * @param     int iIndex
     * @param     float fValue
     * @return    void
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-09, 10:53
     * @warning
     */
    inline void SetKnownSuccessRatio(int iIndex, float fValue) {
		if (iIndex <= MAX_AET) {
			m_KwnLOB[iIndex].stKnownInfo.fKnownSuccessRatio = fValue;
		}
		else {
		}
    }

    /**
     * @brief     GetKnownSuccessRatio
     * @param     int iIndex
     * @return    float
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-09, 10:53
     * @warning
     */
    inline float GetKnownSuccessRatio(int iIndex) {
        return m_KwnLOB[iIndex].stKnownInfo.fKnownSuccessRatio;
    }

    /**
     * @brief     SetKnownIndexEmitter
     * @param     int iIndex
     * @param     int iIdxEmitter
     * @return    void
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-09, 10:53
     * @warning
     */
    inline void SetKnownIndexEmitter(unsigned int uiIndex, int iIdxEmitter) {
		if ( uiIndex <= MAX_AET) {
			m_KwnLOB[uiIndex].stKnownInfo.iIdxEmitter = iIdxEmitter;
		}
		else {

		}
    }

    /**
     * @brief     GetKnownIndexEmitter
     * @param     unsigned int uiIndex
     * @return    unsigned int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-09, 10:53
     * @warning
     */
    inline unsigned int GetKnownIndexEmitter(unsigned int uiIndex) {
		unsigned int uiRet=0;

		if (uiIndex <= MAX_AET) {
			uiRet = m_KwnLOB[uiIndex].stKnownInfo.iIdxEmitter;
		}
		return uiRet;
    }

    /**
     * @brief     GetEmitterFromKnownIndex
     * @param     unsigned int uiIndex
     * @return    STR_EMITTER *
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-09, 10:53
     * @warning
     */
    inline STR_EMITTER *GetEmitterFromKnownIndex(unsigned int uiIndex) {
        unsigned int iIdxEmitter=GetKnownIndexEmitter( uiIndex );
        return & m_pEmitter[iIdxEmitter];
    }

    /**
     * @brief     GetPulseCountFromKnownIndex
     * @param     unsigned int uiIndex
     * @return    unsigned int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-09, 10:53
     * @warning
     */
    inline unsigned int GetPulseCountFromKnownIndex(unsigned int uiIndex ) {
        unsigned int uiIdxEmitter = GetKnownIndexEmitter(uiIndex);
        return m_pEmitter[uiIdxEmitter].stPDW.uiCount;
    }



#if defined(_ELINT_) || defined(_XBAND_)
	EN_RADARCOLLECTORID GetCollectorID();
	char *GetTaskID();
#endif

    STR_PDWPARAM* GetPdwParam();
    //##ModelId=452B0C530013
    void Init();
    //##ModelId=452B0C530014
    void MakeAET();

    void MarkToEmitterPdwIndex( STR_EMITTER *pEmitter, USHORT usMarkType );

    //##ModelId=452B0C53001D
    UINT CalcFreqMedian( STR_PULSE_TRAIN_SEG *pSeg );
    //##ModelId=452B0C53001F
    int GetIndexNewAet();
    //##ModelId=452B0C530030
    BOOL CompPRI( SRxLOBData *pNewPri, SRxABTData *pTrkPri );
    //##ModelId=452B0C530033
    STR_PULSE_TRAIN_SEG *GetPulseSeg();
    //##ModelId=452B0C530034
    int CalcAoaMeanByHistAoa( STR_PDWINDEX *pSrcIndex );
    //##ModelId=452B0C53003B
    int GetColPdw();
    //##ModelId=452B0C53003C
    int CalcPAMean(PDWINDEX *pPdwIndex, unsigned int uiCount);
    //##ModelId=452B0C530044
    int VerifyPW( PDWINDEX *pPdwIndex, unsigned int uiCount );

    //##ModelId=452B0C530050
    void SaveEmitterPdwFile(STR_EMITTER *pEmitter, int iPLOBID, bool bSaveFile );
    //##ModelId=452B0C530058
    unsigned int GetCoSeg();
    //##ModelId=452B0C530059
    int GetCoEmitter();
    //##ModelId=452B0C53005A
    STR_EMITTER *GetEmitter();
    //##ModelId=452B0C53005B
    SRxLOBData *GetNewLOB();
    //##ModelId=452B0C53005C
    SRxLOBData *GetUpdLOB();
    //##ModelId=452B0C530064
    int GetCoNewAet();

	void GetCollectTime( struct timespec *pTimeSpec );

    unsigned int GetPDWID();
	unsigned int GetOpInitID();


    template <typename T>
    UINT CheckPRIHarmonic( T *pPri1, SRxLOBData *pPri2 ) {
        int overlap_ratio;
        float fOverlap_space;
        int exp_pri_min, exp_pri_max;

        float fdiv_jitter_ratio;

        //STR_PRI *pMaxPri, *pMinPri;

        if( pPri1->fPRIMean > pPri2->fPRIMean ) {
            fdiv_jitter_ratio = FDIV( pPri1->fPRIMean, pPri2->fPRIMean );
            exp_pri_min = UMUL( fdiv_jitter_ratio, pPri2->fPRIMin );
            exp_pri_max = UMUL( fdiv_jitter_ratio, pPri2->fPRIMax );

            fOverlap_space = CalOverlapSpace<float>( pPri1->fPRIMin, pPri1->fPRIMax, (float) exp_pri_min, (float) exp_pri_max );
            if( fOverlap_space != 0 ) {
                overlap_ratio = UDIV( fOverlap_space * 100 , pPri1->fPRIMax - pPri1->fPRIMin );
                if( overlap_ratio < 80 ) {
                    overlap_ratio = UDIV( ( pPri1->fPRIMax - pPri1->fPRIMin ) * 100 , fOverlap_space );
                    if( overlap_ratio >= 80 ) {
                        return (int) ( fdiv_jitter_ratio + 0.5 );
                    }
                }
                else {
                    return (int) ( fdiv_jitter_ratio + 0.5 );
                }
            }

        }
        else {
            fdiv_jitter_ratio = FDIV( pPri1->fPRIMean, pPri2->fPRIMean );
            exp_pri_min = UMUL( fdiv_jitter_ratio, pPri1->fPRIMin );
            exp_pri_max = UMUL( fdiv_jitter_ratio, pPri1->fPRIMax );
        }

        return 0;
    }


    template <typename T>
    UINT CheckHarmonic( T *pAet1, SRxLOBData *pAet2 ) {
        //int i;
        unsigned int uRet=0;

        int nHarmonic;

        if( pAet1 == NULL || pAet2 == NULL ) {
            printf( "\n\t [W] Invalid comparion of AET !" );
        }

        // 추적할 것이 STAGGER 일때 새로운 에미터가 Jitter라고 하면 새로운 에미터를 송신하지 않는다.
        else { 
            if( pAet1->iPRIType == _STAGGER && pAet2->iPRIType == _JITTER_RANDOM ) {
                if( TRUE == CompMeanDiff<float>( pAet2->fPRIMin, pAet1->fPRIMin, (float) STABLE_MARGIN ) &&
                    TRUE == CompMeanDiff<float>( pAet2->fPRIMax, pAet1->fPRIMax, (float) STABLE_MARGIN ) ) {
                    uRet = 1;
                }

                /*! \bug  Jitter 신호는 하모닉 체크해서 최대한 없앤다.
                    \date 2006-08-25 09:37:36, 조철희
                */
        // 사례 1번
        // 추적할 에미터 타입이 지터인데 추적에서 지터 추출이 안되고
        // 새로운 에미터 분석에서 스태거 분석이 될 경우에 새로운 에미터로 보고하게 한다.
        //
        // 재현
        // 파일명: D:\RSA-TFT\소나타 ES TFT\해상 신호\A00_소나타OT 해상신호\광명함\WM-423\wm-423_s333_scans.pdw 파일을
        //

        // 사례 2번
        // 추적할 에미터 타입이 스태거인데 추적에서 스태거 추출이 안되고
        // 새로운 에미터 분석에서 지터로 분석된다면 하모닉 체크로 해서 추적 성공으로 할 수 있다.
        // 재현
        // 파일명: D:\RSA-TFT\소나타 ES TFT\해상 신호\A15-noAnal\sps-64.pdw 파일을
        //

        // 사례 2번
        // 추적할 에미터 타입이 스태거인데 추적에서 스태거 추출이 안되고
        // 새로운 에미터 분석에서 지터로 분석된다면 하모닉 체크로 해서 추적 성공으로 할 수 있다.
        // 재현
        // 파일명: D:\RSA-TFT\소나타 ES TFT\해상 신호\A20-2Step\jitter_2step.pdw 파일을 참조함.
        //

/*
                if( pAet1->pri.mean > pAet2->pri.mean )
                        return _max( 1, UDIV( pAet1->pri.mean, pAet2->pri.mean ) );
                else {
                        // Stagger & Jitter 인 경유에는 PRI 범위가 일치 해야 한다.
                        //-- 조철희 2005-12-14 17:32:32 --//
                        // return _max( 1, UDIV( pAet2->pri.mean, pAet1->pri.mean ) );

                        return CheckHarmonic( & pAet1->pri, & pAet2->pri ) == 1;
                }
                */
            }
            else if( pAet1->iPRIType == _JITTER_RANDOM && pAet2->iPRIType == _JITTER_RANDOM ) {
                nHarmonic = CheckPRIHarmonic( pAet1, pAet2 );
                if( nHarmonic >= 2 && 0 == CalOverlapSpace<float>( pAet1->fPWMin, pAet1->fPWMax, pAet2->fPWMin, pAet2->fPWMax ) ) {
                    return 0;
                }
                return nHarmonic;
            }
            /*! \bug  지터와 Stable 비교는 무시한다.
                \date 2006-09-05 08:51:47, 조철희
            */
            else if( pAet1->iPRIType == _JITTER_RANDOM && pAet2->iPRIType == _STABLE ) {
                 return 0;
                    // return CheckHarmonic( pAet1->pri.mean, pAet2->pri.mean );
            }
            /*! \bug  지터와 Stable 비교는 무시한다.
                \date 2006-09-05 08:51:47, 조철희
            */
            else if( pAet1->iPRIType == _STABLE && pAet2->iPRIType == _JITTER_RANDOM ) {
                uRet = 0;
                    // return CheckHarmonic( pAet1->pri.mean, pAet2->pri.mean );
            }


            /*
            else if( pAet1->iPRIType == _STAGGER && pAet2->iPRIType == _STABLE ) {
                unsigned int uiFramePri;

                if( CompMeanDiff<float>( pAet1->fPRIMean, pAet2->fPRIMean, STABLE_MARGIN ) ) {
                    return 1;
                }

                uiFramePri = 0;
                for( int i=0 ; i < pAet1->iPRIPositionCount ; ++i ) {
                    uiFramePri += pAet1->fPRISeq[i];
                }

                return CheckHarmonic( framePri, pAet2->fPRIMean, 2*_spOneMicrosec );
            }
            else if( pAet1->iPRIType == _STABLE && pAet2->iPRIType == _STAGGER ) {
                unsigned int uiFramePri;

                if( CompMeanDiff<float>( pAet1->fPRIMean, pAet2->fPRIMean, STABLE_MARGIN ) ) {
                    return 1;
                }
                else {
                    framePri = 0;
                    for( int i=0 ; i < pAet1->iPRIPositionCount ; ++i ) {
                        framePri += pAet1->fPRISeq[i];
                    }

                    return CheckHarmonic( framePri, pAet1->fPRIMean, 2*_spOneMicrosec );
                }
            }
            else if( pAet1->iPRIType == _STABLE && pAet2->iPRIType == _STABLE ) {
                return CheckHarmonic<float>( pAet1->fPRIMean, pAet2->fPRIMean, 2*_spOneMicrosec );
            }
            else if( pAet1->iPRIType == _DWELL && pAet2->iPRIType == _STABLE ) {
                for( i=0 ; i < pAet1->iPRIPositionCount ; ++i ) {
                    BOOL bRet;

                    bRet = CheckHarmonic( pAet1->fPRISeq[i], pAet2->fPRIMin, 2*_spOneMicrosec );
                    if( bRet != 0 ) {
                        return bRet;
                    }
                }
            }
            else if( pAet1->iPRIType == _STAGGER && pAet2->iPRIType == _STAGGER ) {
                return CheckStaggerHarmonic<T>( pAet1, pAet2 );
            }

            */

            /*! \bug
                \date 2006-09-26 18:34:38, 조철희
            */
            /*
            else if( pAet1->pri.type == _JITTER && pAet2->pri.type == _PATTERN ) {
            nHarmonic = CheckPRIHarmonic( & pAet1->pri, & pAet2->pri );

                    if( nHarmonic >= 2 && 0 == CalOverlapSpace<float>( pAet1->pw.min, pAet1->pw.max, pAet2->pw.min, pAet2->pw.max ) )
                            return 0;
                    return nHarmonic;
            }
            else if( pAet1->pri.type == _PATTERN && pAet2->pri.type == _JITTER ) {
            nHarmonic = CheckPRIHarmonic( & pAet1->pri, & pAet2->pri );

                    if( nHarmonic >= 2 && 0 == CalOverlapSpace<float>( pAet1->pw.min, pAet1->pw.max, pAet2->pw.min, pAet2->pw.max ) )
                            return 0;
                    return nHarmonic;
            }
            */
        }

        return uRet;

    }

    void DISP_FineLOB( SRxLOBData *pLOB );
    unsigned int IsStorePDW();

    //##ModelId=452B0C530078
    BOOL IsUpdateAet();
    //##ModelId=452B0C530079
    void MakeUpAET();

    int SelectKnownSuccessLOB();
    void CalcAllKnownSucessRatio();
    float CalcFreqSuccessRatio(SRxLOBData *pLOBData);
    float CalcPRISuccessRatio(SRxLOBData *pLOBData);
    //##ModelId=452B0C530080
    BOOL KnownMakeAET();


    //##ModelId=452B0C530081
    CKMakeAET( void *pParent, unsigned int uiCoMaxPdw );
    //##ModelId=452B0C530084
    virtual ~CKMakeAET();

    int GetIdxUpdAet() const { return m_IdxUpdAet; }
};

#endif

#endif // !defined(AFX_KMAKEAET_H__0B6C1D4B_0545_4DD1_9E8C_1FDB63EDF929__INCLUDED_)
