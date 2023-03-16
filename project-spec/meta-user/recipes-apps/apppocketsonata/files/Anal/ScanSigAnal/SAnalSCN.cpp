// SAnalScan.cpp: implementation of the CSAnalScan class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "../OFP_Main.h"




#include <math.h>
#include <stdio.h>
#include <string.h>

#include "ScanSigAnal.h"

#include "SAnalSCN.h"
#include "../Identify/ELUtil.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CSAnalScan::CSAnalScan
// 함 수 인 자  : void *pParent
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-02-15 16:09:34
//
CSAnalScan::CSAnalScan( void *pParent, UINT uiCoMaxPdw ) : CAnalPRI(uiCoMaxPdw), CMakeAET(uiCoMaxPdw)
{
	m_pScanSigAnal = ( CScanSigAnal * ) pParent;

    INIT_ANAL_VAR2_( CAnalPRI, m_pScanSigAnal)
    INIT_ANAL_VAR2_( CMakeAET, m_pScanSigAnal)

    m_uiMaxPdw = uiCoMaxPdw;

}

/**
 * @brief     스캔 객체를 해지한다.
 * @return    
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-11-22 17:57:51
 * @warning
 */
CSAnalScan::~CSAnalScan()
{

}

/**
 * @brief     Init
 * @param     unsigned int uinoEMT
 * @param     int noCh
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2006-02-15 16:13:31
 * @warning
 */
void CSAnalScan::Init( unsigned int uinoEMT, int noCh )
{

	m_ucScnTyp = E_AET_SCAN_UNKNOWN;
    m_uiScnPrd = _spZero;

	m_uinoEMT = uinoEMT; // m_pScanSigAnal->GetScanNoEMT();

	m_noCh = noCh;

    m_pScnAet = m_pScanSigAnal->GetScnAET();
    m_pScanPt = & stScanPt;

    //m_pSeg = GetPulseSeg();

    //m_nAnalSeg = 0;
    m_uiCoSeg = GetCoSeg();

	//memset( & m_nCoModWc, _spZero, sizeof( m_nCoModWc ) );

	// 스캔 결과 초기화
	//memset( & stScnRes, _spZero, sizeof( stScnRes ) );

    CAnalPRI::Init();
    CMakeAET::Init();

}

/**
 * @brief     펄스열 포인터를 리턴한다.
 * @return    STR_PULSE_TRAIN_SEG *
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-11-22 18:06:37
 * @warning
 */
STR_PULSE_TRAIN_SEG *CSAnalScan::GetPulseSeg()
{
    return m_pScanSigAnal->GetPulseSeg();
}

/**
 * @brief     펄스열 개수를 리턴한다.
 * @return    unsigned int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-11-22 18:06:59
 * @warning
 */
unsigned int CSAnalScan::GetCoSeg()
{
    return m_pScanSigAnal->GetCoSeg();
}

/**
 * @brief CSAnalScan::KnownAnalysis
 * @return
 */
BOOL CSAnalScan::KnownAnalysis()
{

    m_uiCoSeg = GetCoSeg();

    // 타입에 따라서 펄스열 분석을 달리한다.
#ifdef _POCKETSONATA_
    switch( m_pScnAet->ucPRIType ) {
#else
	switch( m_pScnAet->iPRIType ) {
#endif
        case _STABLE :
            // 추적에서는 로브 조건을 무시하도록 한다.
            GroupingStable( TRUE );
            break;

        case _STAGGER :
            // 추적에서는 로브 조건을 무시하도록 한다.
            GroupingJitter( TRUE );
            break;

        case _JITTER_RANDOM :
            // 추적에서는 로브 조건을 무시하도록 한다.
            GroupingJitter( TRUE );
            break;

        case _JITTER_PATTERN:
            // 추적에서는 로브 조건을 무시하도록 한다.
            GroupingJitter( TRUE );
            break;

        case _DWELL :
            // 추적에서는 로브 조건을 무시하도록 한다.
            // 추적할 에미터의 PRI 정보를 근거로 에미터를 생성한다.
            GroupingStable( TRUE );
            GroupingDwell();
            break;

        default:
            break;
    }

    CAnalPRI::Analysis();

    return TRUE;
}

/**
 * @brief     스캔 분석을 수행한다.
 * @param     int preAnalStat
 * @return    EN_SCANRESULT
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2006-02-15 19:05:46
 * @warning
 */
EN_SCANRESULT CSAnalScan::AnalScan( int preAnalStat )
{
    SRxLOBData *pLOBData;
    EN_SCANRESULT enScanResult=_spAnalFail;

	UINT uiThreat;
    UINT paMean;

    m_pEmitter = TakeTheScanMainEmitter();

    /*! \bug  샘플링 개수가 10개 이하이면 스캔 분석 실패로 한다.
        \date 2006-05-12 14:08:48, 조철희
    */
    if( m_pEmitter == NULL ) {
        m_ucScnTyp = E_AET_SCAN_UNKNOWN;
        m_uiScnPrd = _spZero;

    }
    else {
        SaveScanPulse( & m_pEmitter->stPDW );

        /*! \bug  수집 개수가 5 개 이하이면 스캔 형태 판단을 하지 않게 한다.
            \date 2006-05-09 17:30:28, 조철희
        */
        // 샘플링 타임 계산
        CalcSamplingTime();

        // 샘플링
        SamplingProcess();

        ReplaceOffSampling( & m_nSample, m_pScanPt );

        // Interpolation
        Interpolation( & m_nSample, m_pScanPt );				// debug, 99-12-15 14:14:32
        // Interpolation2( & gSample );			// debug, 0-04-17 10:36오후

        m_nSample.fMeanY = Normalize( & m_nSample.iPA[0], m_nSample.uiCount, & m_nSample.normPa[0] );

        // debug, 99-12-15 14:14:32 -> 00-01-13 13:12:56
        paMean = (unsigned int) ( MeanInArray<int>( & m_pScanPt->iPA[0], m_pScanPt->uiCount ) + 0.5 );

        if( CheckSteadySignal( & m_nSample, paMean ) == true ) {
            m_ucScnTyp = E_AET_SCAN_STEADY;
            m_uiScnPrd = _spZero;

            m_nCoModWc[m_uinoEMT] = _spZero;
            enScanResult = _spAnalSuc;
        }
        else {
            AutoCorerelation( & m_nSample, & m_nAutoCor );

            m_uiScnPrd = FindPeak( & m_nAutoCor );
            // printf( "\n Period : %d(%d) ms" , UDIV( m_nScnPrd, ONE_MILLISEC ), m_nScnPrd );

            uiThreat = ScanTypeDecision( & m_nSample, & m_nAutoCor );

            if( m_uiScnPrd == (UINT) -1 ) {
                m_ucScnTyp = E_AET_SCAN_SCANFAIL;
                m_nCoModWc[m_uinoEMT] = _spZero;
                enScanResult = _spAnalFail;
            }
            else {
                enScanResult = _spAnalSuc;
            }

            if(uiThreat == (unsigned int) _spAnalFail && CheckControlWc(m_uinoEMT) == true ) {
                // WhereIs;

                ++ m_nCoModWc[m_uinoEMT];
                enScanResult = _spModWc;
            }

            if(uiThreat == (unsigned int) _spAnalSuc ) {
                m_nCoModWc[m_uinoEMT] = _spZero;
            }
        }

        MakeLOBDataFromEmitter( m_iCoLOB, m_pEmitter, _spZero );
    }

    // 스캔 정보 저장
    pLOBData = GetLOBData();

#ifndef _XBAND_
    pLOBData->ucScanType = m_ucScnTyp;
    pLOBData->fScanPeriod = TOAmsCNV( m_uiScnPrd );

#endif

    return enScanResult;
}

/**
 * @brief CSAnalScan::SaveScanPulse
 * @param pPdwIndex
 */
void CSAnalScan::SaveScanPulse( STR_PDWINDEX *pPdwIndex )
{
    unsigned int i;
    UINT uiCount = 0, uiPDWCount;

    PDWINDEX *pIndex;
    _TOA *pScanTOA;
    int *pScanPA;

    pScanPA = & m_pScanPt->iPA[0];
    pScanTOA = & m_pScanPt->tTOA[0];
    pIndex = pPdwIndex->pIndex;
    uiPDWCount = pPdwIndex->uiCount;
    for( i=0 ; i < m_uiMaxPdw && i < uiPDWCount; ++i ) {
        PDWINDEX idx;

        idx = *pIndex++;
        *pScanTOA++ = CAnalPRI::m_pTOA[idx];
        *pScanPA++ = CAnalPRI::m_pPA[idx];

        ++uiCount;

    }

    m_pScanPt->uiCount = uiCount;
    
}

/**
 * @brief     TakeTheScanMainEmitter
 * @return    STR_EMITTER *
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-06-15, 11:32
 * @warning
 */
STR_EMITTER *CSAnalScan::TakeTheScanMainEmitter()
{
    STR_EMITTER *pEmitter;

    pEmitter = CAnalPRI::GetEmitter();
    if( CAnalPRI::m_uiCoEmitter == _spOne && pEmitter[0].stPDW.uiCount > 10 ) {

    }
    else {
        pEmitter = NULL;
    }

    return pEmitter;
}

/**
 * @brief     샘플링 계산을 수행한다.
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2006-02-15 16:19:07
 * @warning
 */
void CSAnalScan::CalcSamplingTime()
{
	_TOA priMean;

	// Cal. sampling time
    priMean = ITOAusCNV( m_pScnAet->fPRIMean ); // stScnAet[ m_noEMT ].aet.pri.max;
	// gSampleTime = CalcSamplingTime( priMean );
	// debug, 00-04-07 09:31:50

	/*! \bug  샘플링 타임 제한 조건을 두어야 한다.
	    \date 2006-09-29 15:55:28, 조철희
	*/
	m_nSampleTime = CalcSamplingTime( m_uinoEMT, (UINT) priMean );

}

/**
 * @brief     CalcSamplingTime
 * @param     UINT noEMT
 * @param     UINT priMean
 * @return    UINT
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2006-02-15 16:21:42
 * @warning
 */
UINT CSAnalScan::CalcSamplingTime( UINT noEMT, UINT priMean ) 
{
	UINT samplingTime;

    samplingTime = CalcSamplingTime( priMean );

#if defined(_A50_RWR)


#else
	UINT step;

    step = 0; // stScnAet.sap.fScStep;

    //stOffPdw = _sp.sc.offst[step];           // debug, 00-08-29 20:37:35

#endif

	return samplingTime;

}

/**
 * @brief     샘플링 계산을 수행한다.
 * @param     UINT priMean
 * @return    UINT
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2006-02-15 16:23:43
 * @warning
 */
UINT CSAnalScan::CalcSamplingTime( UINT priMean )
{
    UINT uiSampleTime;

    _TOA ullSpanTime;
    UINT sampleTimeByPulse;
    UINT sampleTimeByPri;

    //PDWINDEX *pPDWIndex;
    //UINT uiLastIndex;

    //pPDWIndex = m_pEmitter->pdw.pIndex;
    //uiLastIndex = pPDWIndex[ m_pEmitter->pdw.count-1 ];

    // 수집 총 시간 측정
    //ullSpanTime = m_pTOA[ uiLastIndex ] - m_pTOA[0];
    if( m_pScanPt->uiCount >= 1 && m_pScanPt->uiCount <= sizeof(m_pScanPt->tTOA) ) {
        ullSpanTime = m_pScanPt->tTOA[ m_pScanPt->uiCount-1 ] - m_pScanPt->tTOA[0];
    }
    else {
        ullSpanTime = 0;
    }

    sampleTimeByPulse = UDIV( ullSpanTime, _spMaxSample );

    sampleTimeByPri = 5 * priMean;		// debug, 00-07-27 12:09:07

    if( sampleTimeByPulse < sampleTimeByPri ) {
        uiSampleTime = sampleTimeByPri;
    }
    else {
        uiSampleTime = sampleTimeByPulse;
    }

    return uiSampleTime;

}

/**
 * @brief     샘플링 처리를 수행한다.
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2006-02-15 16:34:25
 * @warning
 */
void CSAnalScan::SamplingProcess()
{
	UINT i;
	UINT inpulse;
	UINT sumY, maxY;
	_TOA *px, *psx;

	int *py, *psy;

	_TOA dShgh;
 
	// Search maximum and minimum X of pulse train
    SearchLowHghInArray( m_pScanPt->iPA, m_pScanPt->uiCount, & m_pScanPt->_pa );

	m_nSample.uiCount = _spZero;
    // memset( & m_nSample, _spZero, sizeof( m_nSample ) );

    px = & m_pScanPt->tTOA[0];
    py = & m_pScanPt->iPA[0];

    psx = & m_nSample.tTOA[0];
    psy = & m_nSample.iPA[0];

    _EQUALS3( sumY, maxY, _spZero )
    inpulse = _spZero;
    dShgh = *px + m_nSampleTime;

	for( i=0 ; i < m_pScanPt->uiCount ; ) {
		if( *px < dShgh ) {
			sumY += *py;                    // Sampling 구간내의 PA의 전체 합
			if( maxY < *py )                // Sampling 구간내의 PA의 최대 합
				maxY = *py;

			++inpulse;
			++px;
			++py;

			++i;
		}
		else {
			if( m_nSample.uiCount >= _spMaxSample ) {
				// WhereIs;
				break;
			}

			*psx = dShgh - m_nSampleTime;
			if( inpulse != _spZero ) {
				*psy = IDIV( sumY, inpulse );       // Sampling 구간내의 평균치로 계산
			}
			else {
				*psy = -1;					// marking none sampling pulse
			}
			dShgh += m_nSampleTime;

			++ psx;
			++ psy;
			_EQUALS3( sumY, maxY, _spZero )
			inpulse = _spZero;

			++ m_nSample.uiCount;

		}

	}

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CSAnalScan::SearchLowHghInArray
// 반환되는 형  : void
// 함 수 인 자  : UINT *series
// 함 수 인 자  : UINT co
// 함 수 인 자  : STR_LOWHIGH *lh
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-02-15 18:52:57
//
void CSAnalScan::SearchLowHghInArray(int *series, UINT co, STR_LOWHIGH *lh)
{
    UINT i;

    lh->iHgh = *series;
    lh->iLow = *series;
    for (i = 0; i < co; ++i) {
        if ((int)*series > lh->iHgh)
            lh->iHgh = *series;

        if ((int)*series < lh->iLow)
            lh->iLow = *series;

        ++series;
    }

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CSAnalScan::ReplaceOffSampling
// 반환되는 형  : void
// 함 수 인 자  : STR_SAMPLE *pSample
// 함 수 인 자  : STR_SCANPT *pScanPt
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-02-15 18:58:23
//
void CSAnalScan::ReplaceOffSampling( STR_SAMPLE *pSample, STR_SCANPT *pScanPt )
{
	UINT i, j;

	UINT missing;

	UINT CoOffVal;
	UINT MaxOffVal;

	_EQUALS3( MaxOffVal, missing, _spZero )
	for( i=0 ; i < pSample->uiCount ; ++i ) {
		if( pSample->iPA[i] == -1 ) {
			++ missing;
			if( missing > stOffPdw ) {
				CoOffVal = _spZero;
				for( j=i ; j < pSample->uiCount && pSample->iPA[j] == -1 ; ++j ) {
					// 신호 세기가 가장 작은 값인 0 으로 설정 한다.
					//-- 조철희 2006-05-09 17:06:44 --//
					// pSample->pa[j] = pScanPt->_pa.low;
					pSample->iPA[j] = 0;
					++ CoOffVal;
				}

				MaxOffVal = _max( MaxOffVal, CoOffVal );

				if( j != _spZero ) {
					i = j - 1;
				}
				else {
					i = 0;
					WhereIs;
				}

				missing = _spZero;
			}
			
		}
		
	}
			
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CSAnalScan::Interpolation
// 반환되는 형  : void
// 함 수 인 자  : STR_SAMPLE *pSample
// 함 수 인 자  : STR_SCANPT *pScanPt
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-02-15 19:00:08
//
void CSAnalScan::Interpolation( STR_SAMPLE *pSample, STR_SCANPT *pScanPt )
{
	UINT i, j;

	int *pPa;

	pPa = & pSample->iPA[0];
	for( i=0 ; i < pSample->uiCount && i < _spMaxSample ; ++i ) {
		if( *pPa == (UINT) -1 ) {

			for( j=i+1 ; j < pSample->uiCount ; ++j ) {
				// 셈플링 신호가 일정 구간내에 존재하지 않는 것을 체크
				if( pSample->iPA[j] != -1 ) {
					if( pSample->iPA[j] == _spZero ) {
						/*! \bug  수집된 신호 세기 값이 존재하지 않으면 샘플링 값을 0 으로 취한다.
						    \date 2006-05-12 11:43:15, 조철희
						*/
						*pPa = pScanPt->_pa.iLow;
					}
					else {
                        //if( ( i >= _spOne && i < sizeof(pSample->iPA)/sizeof( UINT ) ) /* && j >= 0 */ ) {
						*pPa = DivideBy2( pSample->iPA[i-1], pSample->iPA[j] );
                        //}
                    }
					break;
				}
			}

			if( *pPa == (UINT) -1 ) {
                //if( i >= _spOne && i <= sizeof(pSample->iPA)/sizeof(UINT) ) {
				*pPa = pSample->iPA[i-1];
                //}
				pSample->uiCount = i;
				break;
			}
		}
		++ pPa;
	}

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CSAnalScan::Normalize
// 반환되는 형  : float
// 함 수 인 자  : UINT *series
// 함 수 인 자  : UINT co
// 함 수 인 자  : float *norm
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-02-15 19:11:52
//
float CSAnalScan::Normalize( int *series, UINT co, float *norm )
{
    UINT i;
	float	mean;
 
    mean = MeanInArray<int>( series, co );

  for( i=0 ; i < co ; ++i ) {
		*norm = (float) *series++ - mean;

		//-- 조철희 2006-04-26 12:16:38 --//
		if( *norm < 0 )
			*norm = 0;

		++ norm;
	}

	return mean;
 
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CSAnalScan::CheckSteadySignal
// 반환되는 형  : UINT
// 함 수 인 자  : STR_SAMPLE *pSample
// 함 수 인 자  : UINT meanY
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-02-15 19:12:07
//
bool CSAnalScan::CheckSteadySignal( STR_SAMPLE *pSample, UINT meanY )
{
    bool bRet=false;

    UINT i;
	UINT cleanPa;

	int *pPa;
    int iThPa = (int) ( ( (float) 3. / _spAMPres ) + 0.5 );    // I_IPACNV(3);			// 3dBm 이하 허용하게 함.

	pPa = & pSample->iPA[0];
	cleanPa = _spZero;
	for( i=0 ; i < pSample->uiCount ; ++i ) {

		// debug, 00-07-27 11:00:55
		if( CompMeanDiff<int>( *pPa++, (int)meanY, iThPa) == _spFalse ) {
			++ cleanPa;
		}
	}
	
	// debug, 99-12-22 19:18:14, debug, 00-04-07 14:51:06
	pSample->fSdevY = SDevInArray<int>( pSample->iPA, pSample->uiCount, pSample->fMeanY );
	// if( ( FDIV( cleanPa, pSample->co ) < 0.01 ) && pSample->sdevY < UDIV( 1.0, _spAMPres ) ||
    if( ( ( FDIV( cleanPa, pSample->uiCount ) < 0.01 ) && ( pSample->fSdevY < UDIV( 1.0, _spAMPres ) ) ) || cleanPa <= 2 ) {
		SearchLowHghInArray( & pSample->iPA[0], pSample->uiCount, & pSample->_pa );
		KurtosisSkewness( pSample );
        bRet = _spTrue;

	}

    return bRet;

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CSAnalScan::AutoCorerelation
// 반환되는 형  : void
// 함 수 인 자  : STR_SAMPLE *pSample
// 함 수 인 자  : STR_AUTOCOR *pAutoCor
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-02-15 19:13:55
//
void CSAnalScan::AutoCorerelation( STR_SAMPLE *pSample, STR_AUTOCOR *pAutoCor )
{
    UINT i, j;

	float	refAcf;
	
    float *pAcf;

	UINT co;
    float *pxd1, *pxd2;
 
    memset( pAutoCor, _spZero, sizeof( STR_AUTOCOR ) );

    _EQUALS3( co, pAutoCor->uiCount, pSample->uiCount )
    pxd1 = & pSample->normPa[_spZero];

  for( i=0 ; i < co ; ++i, ++pxd1 ) {
		pxd2 = & pSample->normPa[i];

		// ReverseLED( prc_SAP, LED1 );
		pAcf = & pAutoCor->acf[_spZero];
		for( j=i ; j < co ; ++j ) {
			*pAcf += ( *pxd1 * *pxd2++ );
			++ pAcf;
		}
	}

	refAcf = pAutoCor->acf[0]; 
	pAcf = & pAutoCor->acf[1];
	if( is_not_zero<float>(refAcf) == true ) {
		for( i=1 ; i < co ; ++i ) {
			*pAcf++ /= refAcf;
		}
	}
	else {
		for( i=1 ; i < co ; ++i ) {
			*pAcf++ = 1 - FDIV( i, co );
		}
	}

  pAutoCor->acf[_spZero] = 1.0;

}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CSAnalScan::FindPeak, ACF 값 중에서 피크값을 찾는 기능을 한다.
//!	\author  조철희
//!	\param	 pAutoCor	인자형태 STR_AUTOCOR *
//!	\return	 UINT
//! \version 1.0
//! \date		 2006-02-15 19:16:52
//! \warning 2006-05-11 17:38:02 로브에서 신호가 적을 때를 고려해서 주기 찾기 기능을 수정함. 
//
UINT CSAnalScan::FindPeak( STR_AUTOCOR *pAutoCor )
{
    UINT uiRet;
    UINT i, j;

    float	*pAcf;
    float maxY;

    UINT k;
    UINT co;

    BOOL bMatch;

    m_uiCoCanPeak = _spZero;

    maxY = -10000.0;			// debug, 00-07-27 15:53:42
    pAcf = & pAutoCor->acf[_spMinPrd];

	k = _spZero;
	co = pAutoCor->uiCount;
    if( co >= MIN_CO_ACF+_spMinPrd ) {
        for( i=_spMinPrd ; i < co-_spMinPrd ; ++i ) {
	        if( *pAcf > 0.1 && ( *(pAcf-2) <= *(pAcf-1) && *(pAcf-1) <= *pAcf && *pAcf >= pAcf[1] && pAcf[1] >= pAcf[2] ) ) {
		        m_uiCanPeak[ m_uiCoCanPeak ] = i;
		        ++ m_uiCoCanPeak;

			    // debug, 00-02-10 22:46:36
                if(	*pAcf > maxY ) {				// debug, 00-09-01 12:10:39
	                k = i;				// toa index
                    maxY = *pAcf;
                }
            }

            ++ pAcf;
        }
    }

	// printf( "\n 피크 후보 개수[%d]" , m_nCoCanPeak );

	if( m_uiCoCanPeak <= _spOne ) {
		uiRet = (UINT) -1;
	}
	else if( m_uiCoCanPeak == _spTwo ) {
		uiRet = UMUL( m_uiCanPeak[0], m_nSampleTime );
	}
    else {
	    // 피크 검증
	    // 최대 피크 값은 하한값(0.4) 이상 이어야 하며
	    // 피크에 대한 주기성이 존재해야 한다. 
	    //-- 조철희 2006-05-02 10:46:20 --//
	    if( pAutoCor->acf[ m_uiCanPeak[0] ] < 0.4 ) {
		    // printf( "\n 제일 큰 ACF 값이 0.4(%f) 이하여서 주기가 없는 것으로 간주합니다." , pAutoCor->acf[ m_nCanPeak[0] ] );
		    uiRet = (UINT) -1;
	    }
        else {
	        // 주기 반복성 체크해서 존재해야 주기값을 인정한다.
	        /*! \bug  N번 건너띄어서 주기성을 체크하는 기능을 추가함.
	            \date 2006-08-16 14:47:28, 조철희
	        */
	        // UINT peakMargin = _max( 2, UDIV( m_nCanPeak[0], 5 ) );

	        k = 0;
	        unsigned int jump=1;
	        for( i=0 ; i < m_uiCoCanPeak && jump < m_uiCoCanPeak ; ++i ) {
		        unsigned int offset;

		        bMatch = TRUE;
		        offset = m_uiCanPeak[i];
		        for( j=jump ; j < m_uiCoCanPeak ; j += jump ) {
			        int diff;

			        diff = (int) m_uiCanPeak[j] - (int) m_uiCanPeak[j-jump];
			        if( TRUE != CompMeanDiff<int>( diff, (int) offset, 4 ) ) {
				        bMatch = FALSE;
				        break;
			        }
		        }

		        if( bMatch == TRUE ) {
			        // 피크 값 중에서 주기값이 될만한 값을 찾는다. 
			        // 해상 신호 중에는 메인 로브 마다 가장 큰 신호세기 차가 있을 수 있기 때문에,
			        // 스캔 신호 중에서 1번째 값보다 2번째 값이 클 수 있다.
			        //
			        //-- 조철희 2006-05-11 16:19:31 --//
			        k = m_uiCanPeak[jump] - m_uiCanPeak[0];
			        break;

		        }

		        ++ jump;
	        }


	        pAutoCor->inPeak = k;

	        if( k == _spZero ) {
		        // debug, 00-07-27 14:41:04
                //Printf( "\n 주기를 못 찾았습니다." );
		        uiRet = (UINT) -1;
	        }
	        else {
                //Printf( "\n 주기 [%d], k=%d" , UMUL( k, m_nSampleTime ), k );
		        uiRet = UMUL( k, m_nSampleTime );
	        }
        }
    }

    return uiRet;

}

/**
 * @brief     스캔 형태를 판단한다.
 * @param     STR_SAMPLE * pSample
 * @param     STR_AUTOCOR * pAcf
 * @return    UINT
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2006-02-15 19:23:37
 * @warning
 */
UINT CSAnalScan::ScanTypeDecision( STR_SAMPLE *pSample, STR_AUTOCOR *pAcf )
{
    UINT uiRet=_spAnalSuc;
    ENUM_AET_SCAN_TYPE enScnType;

	UINT uiPrdVer;

	_EQUALS3( pAcf->idPeak, uiPrdVer, PeriodVerify() )

    enScnType = HighIllustrationTest2( pSample, pAcf );
 	KurtosisSkewness( pSample );		// debug, 00-07-26 22:36:44

	// printf( "\n 스캔형태[%d]" , enScnType );
	if( m_uiScnPrd != (UINT) -1 && m_uiScnPrd <= _sp.sc.thtrkprd ) {
		switch(enScnType) {
            case E_AET_SCAN_STEADY :
				// prdVer는 피크 주기성이 있는 것만 해당하는 개수이다.
				// m_nCoCanPeak 값은 피크값이 존재한 개수를 의미한다.
				//-- 조철희 2006-05-09 17:16:11 --//
				if( m_uiCoCanPeak /* prdVer */ >= _spOne ) {		// _spOne -> _spThree
					m_ucScnTyp = TrackUnknown;
				}
				else {
					/*! \bug  스캔 형태가 Steady 라고 할 때 Kurtosis 값은 5.0 이하이어야 한다.
							\date 2006-05-12 11:55:00, 조철희
					*/
					if( m_nSample.fKurtosis <= 5.0 ) {
                        m_ucScnTyp = E_AET_SCAN_STEADY;
						m_uiScnPrd = _spZero;
					}
				}
				break;

            case E_AET_SCAN_CONICAL :
				// printf( "\n CONICAL1[%d]" , UDIV( m_nScnPrd, _spOneMilli) );
				if(uiPrdVer >= _spOne ) {		// _spOne -> _spThree
					/*! \bug  Conical 일때 대칭성을 참조해서 0.7 이내에 들어야 하는 것을 추가함.
					    \date 2008-11-03 22:34:32, 조철희
					*/
					if( pSample->fSkewness < 0.7 )
                        m_ucScnTyp = E_AET_SCAN_CONICAL;
					else
						m_ucScnTyp = TrackUnknown;
				}
				else {
					m_ucScnTyp = TrackUnknown;
				}
				break;


			default :
				printf( "\n\t [W] Invalid Steady or Conical Decision[%d] !" , enScnType);
				WhereIs;
				break;
		}

	}
	else {
		switch(enScnType) {
            case E_AET_SCAN_STEADY :
				if(uiPrdVer >= _spOne ) {
					m_ucScnTyp = DetectUnknown;
				}
				else {
					if( fabs( pSample->fSkewness ) <= 1.0 ) {	// debug, 00-04-17 20:38:23
                        m_ucScnTyp = E_AET_SCAN_STEADY;
						m_uiScnPrd = _spZero;
					}
					else {
						m_ucScnTyp = DetectUnknown;
					}
				}
				break;

            case E_AET_SCAN_CONICAL :
				printf( "\n CONICAL2[%d]" , UDIV( m_uiScnPrd, _spOneMilli) );
				if(uiPrdVer >= _spOne ) {
					m_ucScnTyp = LowIllustrationTest;
				}
                else {
                    m_ucScnTyp = DetectUnknown;
                }
				break;

            default:
				printf( "\n\t [W] Invalid Steady or Conical Decision[%d] !" , m_ucScnTyp );   
				WhereIs;
				break;

		}  
	}

    uiRet = ScanTypeLowDecision(uiPrdVer, pSample, pAcf);
    
    return uiRet;
}

/**
 * @brief     ScanTypeLowDecision
 * @param     STR_SAMPLE * pSample
 * @param     STR_AUTOCOR * pAcf
 * @return    UINT
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-19, 15:41
 * @warning
 */
UINT CSAnalScan::ScanTypeLowDecision(UINT uiPrdVer, STR_SAMPLE *pSample, STR_AUTOCOR *pAcf)
{
    UINT uiRet = _spAnalFail;

	// TurnOnLED( prc_SAP, LED1 );		// debug, 00-06-05 09:39:34
	// KurtosisSkewness( & gSample );

	if( m_ucScnTyp == (UINT) LowIllustrationTest || m_ucScnTyp == (UINT) DetectUnknown ) {
		if(uiPrdVer >= _spTwo ) {
			m_ucScnTyp = DetectNonTrackScanPattern( pSample, pAcf );

			// 최소 스캔 주기 체크함.
			if( (UINT) m_uiScnPrd <= UMUL( 300, _spOneMilli ) ) {
				/*! \bug  스캔 분석 실패이더라도 타입 정보가 표시될 수 있음.
						\date 2009-09-28 17:44:14, 조철희
				*/
                m_ucScnTyp = E_AET_SCAN_SCANFAIL;
				uiRet = _spAnalFail;
			}

			switch( m_ucScnTyp ) {
				case E_AET_SCAN_UNKNOWN:
                    //Printf( "\n	Scan Anal Fail !" );
					uiRet = _spAnalFail;
                    break;
					
                case E_AET_SCAN_CIRCULAR :
                    //Printf( "\n Cir[%d ms]" , UDIV( m_nScnPrd, _spOneMilli) );
					uiRet =  _spAnalSuc;
                    break;

                case E_AET_SCAN_BI_DIRECTIONAL :
                    //Printf( "\n Bi-D[%d ms]" , UDIV( m_nScnPrd, _spOneMilli) );
					uiRet =  _spAnalSuc;
                    break;

                default:
                    break;
			}

		}
		else {
			uiRet = _spAnalFail;
		}
	}

	else if( m_ucScnTyp == (UINT) TrackUnknown ) {
		uiRet = _spAnalFail;
	}

	else {
		// 최소 스캔 주기 체크함.
		if( (UINT) m_uiScnPrd <= UMUL( 7, _spOneMilli ) ) {
			/*! \bug  스캔 분석 실패이더라도 타입 정보가 표시될 수 있음.
					\date 2009-09-28 17:44:14, 조철희
			*/
            m_ucScnTyp = E_AET_SCAN_SCANFAIL;
			uiRet = _spAnalFail;
		}

		// printf( "\n SCAN[%d/%d ms]" , m_nScnTyp, UDIV( m_nScnPrd, _spOneMilli) );
		// uiRet = _spAnalSuc;
	}

	return uiRet;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CSAnalScan::CheckControlWc
// 반환되는 형  : BOOL
// 함 수 인 자  : UINT noEMT
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-02-15 19:23:04
//
bool CSAnalScan::CheckControlWc( UINT noEMT )
{
    bool bRet=false;
#if defined(_A50_RWR)
	
#else    

//     UINT coCol;
//     UINT scStep;
// 
//     float fSkewness;
//  
//     // spanTime = m_pScanPt->toa[ m_pScanPt->co-1 ] - m_pScanPt->toa[0];
//     coCol = 0; //stScnAet.sap.noCol;
//     scStep = 0; //stScnAet.sap.fScStep;
// 
//     fSkewness = fabs( m_nSample.skewness );
// 	if( m_nCoModWc[noEMT] <= _spOne &
//         ( ( coCol >= (SCN_COLLECT_PDW-100) && scStep >= _spTwo && m_nAutoCor.idPeak <= _spTwo ) || 
//         ( scStep >= _spTwo && ( fSkewness > 1.0 ) ) ) ) {
// 		bRet = TRUE;
// 	}
// 	else {
// 		// bRet =_spFalse;
// 	}
    
#endif

    return bRet;

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CSAnalScan::KurtosisSkewness
// 반환되는 형  : void
// 함 수 인 자  : STR_SAMPLE *pSample
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-02-15 19:25:07
//
void CSAnalScan::KurtosisSkewness( STR_SAMPLE *pSample )
{
    UINT i;

	UINT co;
    double mds;
    double A, B, B3, B4, C, N;

	long sum=0;

// 	pSample->co = 10;
// 
// 	_EQUALS6( pSample->pa[0], pSample->pa[2], pSample->pa[4], pSample->pa[6], pSample->pa[8], 10 );
// 	_EQUALS6( pSample->pa[1], pSample->pa[3], pSample->pa[5], pSample->pa[7], pSample->pa[9], 13 );
// 	_EQUALS6( pSample->pa[10], pSample->pa[12], pSample->pa[14], pSample->pa[16], pSample->pa[18], 10 );
// 	_EQUALS6( pSample->pa[11], pSample->pa[13], pSample->pa[15], pSample->pa[17], pSample->pa[19], 10 );
// 	pSample->pa[5] = 10;

	for( i=0 ; i < pSample->uiCount ; ++i ) {
		// pSample->pa[i] = i;
		sum += pSample->iPA[i];
	}
	pSample->fMeanY = (float) sum / pSample->uiCount;

 
	pSample->fSdevY = SDevInArray( pSample->iPA, pSample->uiCount, pSample->fMeanY );

	/*! \bug  샘플링 계수에 대한 최소 값 설정
	    \date 2008-11-03 22:29:18, 조철희
	*/
	if( is_zero<float>( pSample->fSdevY ) == true || is_zero<float>( pSample->uiCount ) == true ) {
        _EQUALS3( pSample->fKurtosis, pSample->fSkewness, _spZero )
		co = UINT_MAX;
	}
	else {
        N = (double) pSample->uiCount;
        A = ( N * ( N + 1 ) ) / ( ( N - 1 ) * ( N - 2 ) * ( N - 3 ) );
        C = ( 3 * ( N - 1 ) * ( N - 1 ) ) / ( ( N - 2 ) * ( N - 3 ) );

        _EQUALS3( B3, B4, 0. )

        co = pSample->uiCount; 
        for( i=0 ; i < co ; ++i ) {
            mds = (double) pSample->iPA[i] - pSample->fMeanY;
            B = mds * mds * mds;

            B3 += ( B / pSample->fSdevY );
            B4 += ( ( B * mds ) / pSample->fSdevY );
		}

        pSample->fKurtosis = (float) ( ( A * B4 ) - C );
        pSample->fSkewness = (float) ( B3 / N );

	}

	// printf( "\n N[%d], Kurtosis[%f], Skewness[%f]" , co, pSample->kurtosis, pSample->skewness );

	return;

}


//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CSAnalScan::PeriodVerify
// 반환되는 형  : UINT
// 함 수 인 자  : void
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-02-15 19:41:16
//
UINT CSAnalScan::PeriodVerify( void )
{
	UINT i;
	UINT virPeak;
	UINT prdPeak;
	UINT coSamePeakDtoa;

	UINT maxErr;
	UINT scnErr, offErr;	// scan period error and off sample error

	if( m_uiScnPrd == _spZero || m_uiScnPrd == (UINT) -1 ) {
		coSamePeakDtoa = _spZero;
	}
    else {
	    _EQUALS3( virPeak, prdPeak, UDIV( m_uiScnPrd, m_nSampleTime ) )

	    scnErr = UDIV( UDIV( m_uiScnPrd * 5, 100 ), m_nSampleTime );
	    offErr = UDIV( stOffPdw, 1.5 );
	    maxErr = _max( 1, _min( _max( scnErr, offErr ), virPeak/2 ) );

	    coSamePeakDtoa = _spZero;

	    for( i=0 ; i < m_uiCoCanPeak ; ++i ) {
		    //-- 조철희 2006-04-26 12:29:19 --//
		    // 마진 을 고려해서 피크 검증해야 함.
		    if( virPeak < m_uiCanPeak[m_uiCoCanPeak-1]+maxErr ) {
			    if( CompMeanDiff<unsigned int>( virPeak, m_uiCanPeak[i], maxErr ) == _spTrue ) {
				    virPeak = virPeak + prdPeak;
				    ++ coSamePeakDtoa;
			    }
			    else if( virPeak < m_uiCanPeak[i] ) {
				    //virPeak = virPeak + prdPeak;
				    break;
			    }
                ELSE;

		    }
		    else {
			    break;
		    }
	    }
    }

	return coSamePeakDtoa;

}

/**
 * @brief     스캔 형태를 계산하여 리턴한다.
 * @param     STR_SAMPLE * pSample
 * @param     STR_AUTOCOR * pAcf
 * @return    ENUM_AET_SCAN_TYPE
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2006-02-15 19:42:43
 * @warning
 */
ENUM_AET_SCAN_TYPE CSAnalScan::HighIllustrationTest2( STR_SAMPLE *pSample, STR_AUTOCOR *pAcf )
{
    UINT i;
    UINT ihPeriod;

    ENUM_AET_SCAN_TYPE enRet;

    double diff;
    float *pacf;

    double Rk;
    double dCo;

    double ccfSteady;
    double ccfConical;

    // Steady CCF 비교
    if( m_uiScnPrd != _spZero && m_uiScnPrd != (UINT) -1 )		ihPeriod = ( UDIV(m_uiScnPrd, m_nSampleTime) + 1 );
    else                            								ihPeriod = pAcf->uiCount;

    if( ihPeriod == _spZero ) {
	    printf( "\n Error of ihPeriod" );
	    ihPeriod = 1;
    }

    ccfSteady = _spZero;
    pacf = & pAcf->acf[_spZero];
    for( i=1 ; i < ihPeriod ; ++i ) {
	    ccfSteady += ( *pacf * * pacf );
	    ++ pacf;

    }
    ccfSteady /= (float) i;

    // Conical CCF 비교
    dCo = pAcf->uiCount;
    ccfConical = _spZero;
    for( i=0 ; i < ihPeriod ; ++i ) {
		double x;

		Rk = ( dCo - i ) / dCo;
#ifdef _FAST_MATH
		int degree;
		degree = UDIV( 360 * i, ihPeriod );
		x = mzapi_cos( degree );
#else
		x = cos( ( 2. * M_PI * ( (double) i / (double) ihPeriod ) ) );
#endif

		/*! \bug  cos(0) 값이 0x3FF00000 값으로 리턴하기 때문에 이값으로 나누어서 수행함.
		    \date 2006-05-25 12:26:13, 조철희
		*/
#ifndef _MSC_VER
		// x = x / (double) ( 0x3FF00000 );
		if( i == 0 ) {
            //Printf( "\n x[0] = %f" , x );
		}

#endif
		Rk *= x;

		// diff = fabs( Rk - (double) ( pAcf->acf[i] ) );
		//-- 조철희 2006-04-26 16:54:44 --//
		// 비교 템플릿 함수를 수정함.
		//diff = Rk - (double) ( pAcf->acf[i] );
		diff = ( Rk / 2. + 0.5 ) - (double) ( pAcf->acf[i] );

		ccfConical += ( diff * diff );

    }
    ccfConical /= (float) i;

    // 패턴 판단
    if( ccfConical <= ccfSteady ) {
        enRet = E_AET_SCAN_CONICAL;
    }
    else {
        enRet = E_AET_SCAN_STEADY;
    }

    return enRet;
 
}


/**
 * @brief     비추적형 스캔형태를 판단한다.
 * @param     STR_SAMPLE * pSample
 * @param     STR_AUTOCOR * pAutocf
 * @return    UINT
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2006-02-15 19:50:55
 * @warning
 */
UINT CSAnalScan::DetectNonTrackScanPattern( STR_SAMPLE *pSample, STR_AUTOCOR *pAutocf )
{
	UINT i;
    UINT inHalfPeriod;

	UINT coPeak;

    UINT uiRet;
 
    float	*pAcf;

	float	sum1, sum2;

	float	mean;
	float	vari;
	float	sigma;
	float	gamma;
	float	beta;
	float	delta;

	float	peakAcf;

	float	*pThreshold;

	_EQUALS3( sum1, sum2, 0. )

	// Make function of Threshold
	inHalfPeriod = DivideBy2( _spZero, pAutocf->inPeak );
	pAcf = ( float * ) & pAutocf->acf[0];
	for( i=0 ; i < pAutocf->uiCount ; ++i ) {
		sum1 += *pAcf;
		sum2 += ( *pAcf * *pAcf );
		++ pAcf;
	}

	mean = FDIV( sum1, pAutocf->uiCount );
	vari = FDIV( sum2, pAutocf->uiCount ) - ( mean * mean );

	sigma = (float) sqrt( vari );

	peakAcf = pAutocf->acf[ pAutocf->inPeak ];
	delta = peakAcf - pAutocf->acf[ inHalfPeriod ];
	pThreshold = & pAutocf->fThreshold[ inHalfPeriod ];
	for( i=inHalfPeriod ; i < pAutocf->inPeak ; ++i ) {
		gamma = FDIV( i, pAutocf->inPeak );
		beta  = FDIV( ( pAutocf->inPeak - i ), pAutocf->inPeak );
		*pThreshold++ = (float) ( sigma * beta * beta ) + (float) ( gamma * gamma * peakAcf * exp( ( pAutocf->acf[i] - peakAcf ) / ( 0.6 * delta ) ) );

	}

	coPeak = _spZero;
	for( i=inHalfPeriod ; i < pAutocf->inPeak ; ++i ) {
		if( ( pAutocf->fThreshold[ i ] < pAutocf->acf[i] ) &&
			( pAutocf->acf[i-2] < pAutocf->acf[i-1] ) &&
			( pAutocf->acf[i-1] < pAutocf->acf[i] ) &&
			( pAutocf->acf[i] > pAutocf->acf[i+1] ) &&
			( pAutocf->acf[i+1] > pAutocf->acf[i+2] ) ) {
			++ coPeak;
		}

	}

    if (coPeak == _spZero) {
        uiRet = E_AET_SCAN_CIRCULAR;
    }
    else if (coPeak == _spOne) {
        uiRet = E_AET_SCAN_BI_DIRECTIONAL;
    }
    else {
        uiRet = E_AET_SCAN_UNKNOWN;
    }

    return uiRet;

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CSAnalScan::GetFlagControlWc
// 반환되는 형  : UINT
// 함 수 인 자  : UINT noEMT
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-02-16 10:27:51
//
UINT CSAnalScan::GetFlagControlWc( UINT noEMT ) 
{

/*
	if( stScnAet.sap.winCellword.w3.saf.lower_pa != _spZero )
		return _spTrue;
	else		*/

		return _spFalse;

}


//////////////////////////////////////////////////////////////////////////
/*! \brief    CSAnalScan::MeanInArray
		\author   조철희
		\param    series 인자형태 UINT *
		\param    co 인자형태 UINT
		\return   float
		\version  0.0.29
		\date     2008-07-10 13:22:51
		\warning
*/
// float CSAnalScan::MeanInArray(UINT *series, UINT co)
// {
//     UINT i;
//     UINT sum;
// 
//     sum = _spZero;
//     for( i=0 ; i < co ; ++i ) {
// 		sum += *series++;
//     }
// 
// 	return ( (float) sum / (float) co );
// }

/**
 * @brief CSAnalScan::CompMeanDiff
 * @param x
 * @param y
 * @param thresh
 * @return
 */
// BOOL CSAnalScan::CompMeanDiff(int x, int y, int thresh)
// {
//   int diff;
//   BOOL bRet;
// 
//   diff = _diffabs( x, y );
// 
//   if( diff <= thresh ) {
//     bRet = TRUE;
//   }
//   else {
//     bRet = FALSE;
//   }
// 
//   return bRet;
// 
// }

/**
 * @brief CSAnalScan::MakeAETfromEmitter
 * @param pEmitter
 * @param idxEmitter
 */
void CSAnalScan::MakeLOBDataFromEmitter( int iLOBData, STR_EMITTER *pEmitter, int idxEmitter )
{

    // 기본 LOB 형태 저장
    CMakeAET::MakeLOBDataFromEmitter(iLOBData, pEmitter, idxEmitter );

}

//////////////////////////////////////////////////////////////////////
//
//! \brief    CKAnalPRI::MedianFreq
//! \author   조철희
//! \param    pMinMax 인자형태 STR_TYPEMINMAX *
//! \param    pPdwIndex 인자형태 PDWINDEX *
//! \param    count 인자형태 int
//! \return   UINT
//! \version  1.00
//! \date     2006-01-23 10:14:02
//! \warning
//
UINT CSAnalScan::MedianFreq( STR_TYPEMINMAX *pMinMax, PDWINDEX *pPdwIndex, unsigned int uiCount )
{
    return m_pScanSigAnal->MedianFreq( pMinMax, pPdwIndex, uiCount );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKAnalPRI::VerifyPRI
// 반환되는 형  : int
// 함 수 인 자  : PDWINDEX *pPdwIndex
// 함 수 인 자  : int count
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-02-06 14:44:01
//
_TOA CSAnalScan::VerifyPRI( PDWINDEX *pPdwIndex, unsigned int uiCount)
{
    return m_pScanSigAnal->VerifyPRI( pPdwIndex, uiCount );
}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CKAnalPRI::FindPeakInHist
//!	\author  조철희
//!	\param	 count	인자형태 int
//!	\param	 pPdwIndex	인자형태 PDWINDEX *
//! \version 1.0
//! \date		 2006-07-06 17:28:14
//! \warning
//
int CSAnalScan::FindPeakInHist( unsigned int uiCount, PDWINDEX *pPdwIndex )
{
    return 0; //m_pScanSigAnal->FindPeakInHist( count, pPdwIndex );
}

/**
 * @brief CKAnalPRI::SaveEmitterPDWFile
 * @param pEmitter
 * @param index
 */
void CSAnalScan::SaveEmitterPDWFile(STR_EMITTER *pEmitter, int iPLOBID, bool bSaveFile )
{
    m_pScanSigAnal->SaveEmitterPDWFile( pEmitter, iPLOBID, bSaveFile );

}

/**
 * @brief CKAnalPRI::GetBand
 * @return
 */
int CSAnalScan::GetBand()
{
    return m_pScanSigAnal->GetBand();
}

/**
 * @brief CSAnalScan::GetLOBData
 * @return
 */
SRxLOBData *CSAnalScan::GetLOBData( int index )
{
    return & m_LOBData[index];
}

/**
 * @brief CSAnalScan::GetPdwParam
 * @return
 */
STR_PDWPARAM *CSAnalScan::GetPdwParam()
{
    return m_pScanSigAnal->GetPdwParam();
}

/**
 * @brief CSAnalScan::CalcAoaMeanByHistAoa
 * @param pSrcIndex
 * @return
 */
int CSAnalScan::CalcAoaMeanByHistAoa( STR_PDWINDEX *pSrcIndex )
{
    return m_pScanSigAnal->CalcAoaMeanByHistAoa( pSrcIndex );
}

/**
 * @brief CSAnalScan::CalcFreqMedian
 * @param pSeg
 * @return
 */
UINT CSAnalScan::CalcFreqMedian( STR_PULSE_TRAIN_SEG *pSeg )
{
    return m_pScanSigAnal->MedianFreq( NULL, pSeg->stPDW.pIndex, pSeg->stPDW.uiCount );
}

/**
 * @brief CSAnalScan::CalcPAMean
 * @param pPdwIndex
 * @param count
 * @return
 */
int CSAnalScan::CalcPAMean(PDWINDEX *pPdwIndex, unsigned int uiCount)
{
    return m_pScanSigAnal->CalcPAMean( pPdwIndex, uiCount );
}

/**
 * @brief CSAnalScan::VerifyPW
 * @param pPdwIndex
 * @param count
 * @return
 */
int CSAnalScan::VerifyPW( PDWINDEX *pPdwIndex, unsigned int uiCount)
{
    return (int) m_pScanSigAnal->VerifyPW( pPdwIndex, uiCount );
}

/**
 * @brief CSAnalScan::IsStorePDW
 * @return
 */
unsigned int CSAnalScan::IsStorePDW()
{
    return m_pScanSigAnal->IsStorePDW();
}

/**
 * @brief     수집 시간을 호출한다.
 * @param     struct timespec * pTimeSpec
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022/01/26 22:00:41
 * @warning
 */
void CSAnalScan::GetCollectTime( struct timespec *pTimeSpec )
{
	m_pScanSigAnal->GetCollectTime( pTimeSpec );
}

/**
 * @brief     규칙성 펄스열을 호출한다.
 * @param     _TOA * pnHarmonic
 * @param     STR_PULSE_TRAIN_SEG * pSeg1
 * @param     STR_PULSE_TRAIN_SEG * pSeg2
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-06-15, 11:37
 * @warning
 */
bool CSAnalScan::CheckStablePT( _TOA *pnHarmonic, STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 )
{
    return m_pScanSigAnal->CheckStablePT( pnHarmonic, pSeg1, pSeg2 );
}

#if defined(_ELINT_) || defined(_XBAND_)
/**
 * @brief     
 * @return    EN_RADARCOLLECTORID
 * @author    조철희(churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022/01/19 20:54:57
 * @warning   
 */
EN_RADARCOLLECTORID CSAnalScan::GetCollectorID()
{ 
	return m_pScanSigAnal->GetCollectorID(); 
}

/**
 * @brief     
 * @return    char *
 * @author    議곗쿋??(churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022/01/19 20:55:02
 * @warning   
 */
char *CSAnalScan::GetTaskID()
{
	return m_pScanSigAnal->GetTaskID(); 
}

#endif


