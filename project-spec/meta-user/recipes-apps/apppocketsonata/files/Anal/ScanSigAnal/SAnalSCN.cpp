// SAnalScan.cpp: implementation of the CSAnalScan class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#define _USE_MATH_DEFINES


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
CSAnalScan::CSAnalScan( void *pParent, int coMaxPdw ) : CAnalPRI( coMaxPdw ), CMakeAET( coMaxPdw )
{
	m_pScanSigAnal = ( CScanSigAnal * ) pParent;

    INIT_ANAL_VAR2_( CAnalPRI, m_pScanSigAnal);
    INIT_ANAL_VAR2_( CMakeAET, m_pScanSigAnal);

    m_uiMaxPdw = coMaxPdw;

}

/**
 * @brief CSAnalScan::~CSAnalScan
 */
CSAnalScan::~CSAnalScan()
{

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CSAnalScan::Init
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-02-15 16:13:31
//
void CSAnalScan::Init( int noEMT, int noCh )
{

	m_nScnTyp = _spUnknown;
    m_nScnPrd = _spZero;

	m_noEMT = noEMT; // m_pScanSigAnal->GetScanNoEMT();

	m_noCh = noCh;

    m_pScnAet = m_pScanSigAnal->GetScnAET();
    m_pScanPt = & stScanPt;

    //m_pSeg = GetPulseSeg();

    //m_nAnalSeg = 0;
    m_CoSeg = GetCoSeg();

	//memset( & m_nCoModWc, _spZero, sizeof( m_nCoModWc ) );

	// 스캔 결과 초기화
	//memset( & stScnRes, _spZero, sizeof( stScnRes ) );

    CAnalPRI::Init();
    CMakeAET::Init();

}

/**
 * @brief CSAnalScan::GetPulseSeg
 * @return
 */
STR_PULSE_TRAIN_SEG *CSAnalScan::GetPulseSeg()
{
    return m_pScanSigAnal->GetPulseSeg();
}

/**
 * @brief CSAnalScan::GetCoSeg
 * @return
 */
int CSAnalScan::GetCoSeg()
{
    return m_pScanSigAnal->GetCoSeg();
}

/**
 * @brief CSAnalScan::KnownAnalysis
 * @return
 */
BOOL CSAnalScan::KnownAnalysis()
{

    m_CoSeg = GetCoSeg();

    // 타입에 따라서 펄스열 분석을 달리한다.
    switch( m_pScnAet->iPRIType ) {
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

        case _JITTER_PATTERN :
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

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CSAnalScan::AnalScan
// 반환되는 형  : UINT
// 함 수 인 자  : int preAnalStat
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-02-15 19:05:46
//
EN_SCANRESULT CSAnalScan::AnalScan( int preAnalStat )
{
    SRxLOBData *pLOBData;
    EN_SCANRESULT enScanResult=_spAnalFail;

	UINT bthreat;
    UINT paMean;

    m_pEmitter = TakeTheScanMainEmitter();

    /*! \bug  샘플링 개수가 10개 이하이면 스캔 분석 실패로 한다.
        \date 2006-05-12 14:08:48, 조철희
    */
    if( m_pEmitter == NULL ) {
        m_nScnTyp = E_AET_SCAN_UNKNOWN;
        m_nScnPrd = _spZero;

    }
    else {
        SaveScanPulse( & m_pEmitter->pdw );

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

        m_nSample.meanY = Normalize( & m_nSample.pa[0], m_nSample.co, & m_nSample.normPa[0] );

        // debug, 99-12-15 14:14:32 -> 00-01-13 13:12:56
        paMean = (int) ( MeanInArray( & m_pScanPt->pa[0], m_pScanPt->co ) + 0.5 );

        if( CheckSteadySignal( & m_nSample, paMean ) == true ) {
            m_nScnTyp = E_AET_SCAN_STEADY;
            m_nScnPrd = _spZero;

            m_nCoModWc[m_noEMT] = _spZero;
            enScanResult = _spAnalSuc;
        }
        else {
            AutoCorerelation( & m_nSample, & m_nAutoCor );

            m_nScnPrd = FindPeak( & m_nAutoCor );
            // printf( "\n Period : %d(%d) ms" , UDIV( m_nScnPrd, ONE_MILLISEC ), m_nScnPrd );

            bthreat = ScanTypeDecision2( & m_nSample, & m_nAutoCor );

            // printf( "\n bthreat=%d" , bthreat );

            if( m_nScnPrd == (UINT) -1 ) {
                m_nScnTyp = E_AET_SCAN_SCANFAIL;
                m_nCoModWc[m_noEMT] = _spZero;
                enScanResult = _spAnalFail;
            }
            else {
                enScanResult = _spAnalSuc;
            }

            if( bthreat == _spAnalFail && CheckControlWc(m_noEMT) == _spTrue ) {
                WhereIs;

                ++ m_nCoModWc[m_noEMT];
                enScanResult = _spModWc;
            }

            if( bthreat == _spAnalSuc ) {
                m_nCoModWc[m_noEMT] = _spZero;
            }
        }

        MakeAETfromEmitter( m_pEmitter, 0 );
    }

    // 스캔 정보 저장
    pLOBData = GetLOBData();
    pLOBData->iScanType = m_nScnTyp;
    pLOBData->fScanPeriod = TOAmsCNV( m_nScnPrd );

    return enScanResult;
}

/**
 * @brief CSAnalScan::SaveScanPulse
 * @param pPdwIndex
 */
void CSAnalScan::SaveScanPulse( STR_PDWINDEX *pPdwIndex )
{
    int i, count=0, pdw_count;

    PDWINDEX *pIndex;
    _TOA *pScanTOA;
    UINT *pScanPA;

    pScanPA = & m_pScanPt->pa[0];
    pScanTOA = & m_pScanPt->toa[0];
    pIndex = pPdwIndex->pIndex;
    pdw_count = pPdwIndex->count;
    for( i=0 ; i < m_uiMaxPdw && i < pdw_count ; ++i ) {
        int idx;

        idx = *pIndex++;
        *pScanTOA++ = CAnalPRI::m_pTOA[idx];
        *pScanPA++ = CAnalPRI::m_pPA[idx];
        ++ count;

    }

    m_pScanPt->co = count;

}

/**
 * @brief CSAnalScan::TakeTheScanMainEmitter
 * @return
 */
STR_EMITTER *CSAnalScan::TakeTheScanMainEmitter()
{
    STR_EMITTER *pEmitter;

    pEmitter = CAnalPRI::GetEmitter();
    if( CAnalPRI::m_CoEmitter == _spOne && pEmitter[0].pdw.count > 10 ) {

    }
    else {
        pEmitter = NULL;
    }

    return pEmitter;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CSAnalScan::CalcSamplingTime
// 반환되는 형  : oid
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-02-15 16:19:07
//
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
	m_nSampleTime = CalcSamplingTime2( m_noEMT, (UINT) priMean );

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CSAnalScan::CalcSamplingTime2
// 반환되는 형  : UINT
// 함 수 인 자  : UINT noEMT
// 함 수 인 자  : UINT priMean
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-02-15 16:21:42
//
UINT CSAnalScan::CalcSamplingTime2( UINT noEMT, UINT priMean ) 
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

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CSAnalScan::CalcSamplingTime
// 반환되는 형  : UINT
// 함 수 인 자  : UINT priMean
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-02-15 16:23:43
//
UINT CSAnalScan::CalcSamplingTime( UINT priMean )
{
    UINT uiSampleTime;

    _TOA ullSpanTime;
    UINT sampleTimeByPulse;
    UINT sampleTimeByPri;

    PDWINDEX *pPDWIndex;
    //UINT uiLastIndex;

    pPDWIndex = m_pEmitter->pdw.pIndex;
    //uiLastIndex = pPDWIndex[ m_pEmitter->pdw.count-1 ];

    // 수집 총 시간 측정
    //ullSpanTime = m_pTOA[ uiLastIndex ] - m_pTOA[0];
    if( m_pScanPt->co >= 1 && m_pScanPt->co <= sizeof(m_pScanPt->toa) ) {
        ullSpanTime = m_pScanPt->toa[ m_pScanPt->co-1 ] - m_pScanPt->toa[0];
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

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CSAnalScan::SamplingProcess
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-02-15 16:34:25
//
void CSAnalScan::SamplingProcess()
{
	UINT i;
	UINT inpulse;
	UINT sumY, maxY;
	_TOA *px, *psx;
	UINT *py, *psy;

	_TOA dShgh;
 
	// Search maximum and minimum X of pulse train
    SearchLowHghInArray( m_pScanPt->pa, m_pScanPt->co, & m_pScanPt->_pa );

	m_nSample.co = _spZero;
    // memset( & m_nSample, _spZero, sizeof( m_nSample ) );

    px = & m_pScanPt->toa[0];
    py = & m_pScanPt->pa[0];

    psx = & m_nSample.toa[0];
    psy = & m_nSample.pa[0];

    _EQUALS3( sumY, maxY, _spZero );
    inpulse = _spZero;
    dShgh = *px + m_nSampleTime;

	for( i=0 ; i < m_pScanPt->co ; ) {
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
			if( m_nSample.co >= _spMaxSample ) {
				// WhereIs;
				break;
			}

			*psx = dShgh - m_nSampleTime;
			if( inpulse != _spZero ) {
				*psy = UDIV( sumY, inpulse );       // Sampling 구간내의 평균치로 계산
			}
			else {
				*psy = (UINT) -1;					// marking none sampling pulse
			}
			dShgh += m_nSampleTime;

			++ psx;
			++ psy;
			_EQUALS3( sumY, maxY, _spZero );
			inpulse = _spZero;

			++ m_nSample.co;

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
void CSAnalScan::SearchLowHghInArray( UINT *series, UINT co, STR_LOWHIGH *lh ) 
{
    UINT i;
 
    lh->hgh = *series;
    lh->low = *series;
    for( i=0 ; i < co ; ++i ) {
		if( (int) *series > lh->hgh )
			lh->hgh = *series;

		if( (int) *series < lh->low )
			lh->low = *series;

		++ series;
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

	_EQUALS3( MaxOffVal, missing, _spZero );
	for( i=0 ; i < pSample->co ; ++i ) {
		if( pSample->pa[i] == (UINT) -1 ) {
			++ missing;
			if( missing > stOffPdw ) {
				CoOffVal = _spZero;
				for( j=i ; j < pSample->co && pSample->pa[j] == (UINT) -1 ; ++j ) {
					// 신호 세기가 가장 작은 값인 0 으로 설정 한다.
					//-- 조철희 2006-05-09 17:06:44 --//
					// pSample->pa[j] = pScanPt->_pa.low;
					pSample->pa[j] = 0;
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
	UINT *pPa;

	pPa = ( UINT * ) & pSample->pa[0];
	for( i=0 ; i < pSample->co ; ++i ) {
		if( *pPa == (UINT) -1 ) {

			for( j=i+1 ; j < pSample->co ; ++j ) {
				// 셈플링 신호가 일정 구간내에 존재하지 않는 것을 체크
				if( pSample->pa[j] != (UINT) -1 ) {
					if( pSample->pa[j] == _spZero ) {
						/*! \bug  수집된 신호 세기 값이 존재하지 않으면 샘플링 값을 0 으로 취한다.
						    \date 2006-05-12 11:43:15, 조철희
						*/
						*pPa = pScanPt->_pa.low;
					}
					else {
                        if( ( i >= 1 && i < sizeof(pSample->pa) ) && j >= 0 ) {
						    *pPa = DivideBy2( pSample->pa[i-1], pSample->pa[j] );
                        }
                    }
					break;
				}
			}

			if( *pPa == (UINT) -1 ) {
                if( i >= 1 && i <= sizeof(pSample->pa) ) {
				    *pPa = pSample->pa[i-1];
                }
				pSample->co = i;
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
float CSAnalScan::Normalize( UINT *series, UINT co, float *norm )
{
    UINT i;
	float	mean;
 
    mean = MeanInArray( series, co );

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

	UINT *pPa;
    UINT thPa=IPACNV(3);			// 3dBm 이하 허용하게 함.

	pPa = ( UINT * ) & pSample->pa[0];
	cleanPa = _spZero;
	for( i=0 ; i < pSample->co ; ++i ) {

		// debug, 00-07-27 11:00:55
		if( CompMeanDiff( *pPa++, meanY, thPa ) == _spFalse ) {
			++ cleanPa;
		}
	}
	
	// debug, 99-12-22 19:18:14, debug, 00-04-07 14:51:06
	pSample->sdevY = SDevInArray( pSample->pa, pSample->co, pSample->meanY );
	// if( ( FDIV( cleanPa, pSample->co ) < 0.01 ) && pSample->sdevY < UDIV( 1.0, _spAMPres ) ||
    if( ( ( FDIV( cleanPa, pSample->co ) < 0.01 ) && ( pSample->sdevY < UDIV( 1.0, _spAMPres ) ) ) || cleanPa <= 2 ) {
		SearchLowHghInArray( & pSample->pa[0], pSample->co, & pSample->_pa );
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

    _EQUALS3( co, pAutoCor->co, pSample->co );
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
	if( refAcf != 0.0 ) {
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
    UINT i, j;

    float	*pAcf;
    float maxY;

    UINT k;
    UINT co;

    BOOL bMatch;

    m_nCoCanPeak = _spZero;

    maxY = -10000.0;			// debug, 00-07-27 15:53:42
    pAcf = & pAutoCor->acf[_spMinPrd];

	k = _spZero;
	co = pAutoCor->co;
  for( i=_spMinPrd ; i < co-_spMinPrd ; ++i ) {
		if( *pAcf > 0.1 && ( *(pAcf-2) <= *(pAcf-1) && *(pAcf-1) <= *pAcf &&
        *pAcf >= *(pAcf+1) && *(pAcf+1) >= *(pAcf+2) ) ) {
			m_nCanPeak[ m_nCoCanPeak ] = i;
			++ m_nCoCanPeak;

			// debug, 00-02-10 22:46:36
      if(	*pAcf > maxY ) {				// debug, 00-09-01 12:10:39
				k = i;				// toa index
        maxY = *pAcf;
      }
    }

    ++ pAcf;
  }

	// printf( "\n 피크 후보 개수[%d]" , m_nCoCanPeak );

	if( m_nCoCanPeak <= _spOne ) {
		return (UINT) -1;
	}
	else if( m_nCoCanPeak == _spTwo ) {
		return UMUL( m_nCanPeak[0], m_nSampleTime );
	}

	// 피크 검증
	// 최대 피크 값은 하한값(0.4) 이상 이어야 하며
	// 피크에 대한 주기성이 존재해야 한다. 
	//-- 조철희 2006-05-02 10:46:20 --//
	if( pAutoCor->acf[ m_nCanPeak[0] ] < 0.4 ) {
		// printf( "\n 제일 큰 ACF 값이 0.4(%f) 이하여서 주기가 없는 것으로 간주합니다." , pAutoCor->acf[ m_nCanPeak[0] ] );
		return (UINT) -1;
	}

	// 주기 반복성 체크해서 존재해야 주기값을 인정한다.
	/*! \bug  N번 건너띄어서 주기성을 체크하는 기능을 추가함.
	    \date 2006-08-16 14:47:28, 조철희
	*/
	// UINT peakMargin = _max( 2, UDIV( m_nCanPeak[0], 5 ) );

	k = 0;
	int jump=1;
	for( i=0 ; i < m_nCoCanPeak && (UINT) jump < m_nCoCanPeak ; ++i ) {
		int offset;

		bMatch = TRUE;
		offset = m_nCanPeak[i];
		for( j=jump ; j < m_nCoCanPeak ; j += jump ) {
			int diff;

			diff = m_nCanPeak[j] - m_nCanPeak[j-jump];
			if( TRUE != CompMeanDiff( diff, offset, 4 ) ) {
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
			k = m_nCanPeak[jump] - m_nCanPeak[0];
			break;

		}

		++ jump;
	}


	pAutoCor->inPeak = k;

	if( k == _spZero ) {
		// debug, 00-07-27 14:41:04
        //Printf( "\n 주기를 못 찾았습니다." );
		return (UINT) -1;
	}
	else {
        //Printf( "\n 주기 [%d], k=%d" , UMUL( k, m_nSampleTime ), k );
		return UMUL( k, m_nSampleTime );
	}

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CSAnalScan::ScanTypeDecision2
// 반환되는 형  : UINT
// 함 수 인 자  : STR_SAMPLE *pSample
// 함 수 인 자  : STR_AUTOCOR *pAcf
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-02-15 19:23:37
//
UINT CSAnalScan::ScanTypeDecision2( STR_SAMPLE *pSample, STR_AUTOCOR *pAcf )
{
    UINT uiRet=_spAnalSuc;
	UINT ScnType;

	UINT prdVer;

	_EQUALS3( pAcf->idPeak, prdVer, PeriodVerify() );

	ScnType = HighIllustrationTest2( pSample, pAcf );
 	KurtosisSkewness( pSample );		// debug, 00-07-26 22:36:44

	// printf( "\n 스캔형태[%d]" , ScnType );
	if( m_nScnPrd != (UINT) -1 && m_nScnPrd <= _sp.sc.thtrkprd ) {
		switch( ScnType ) {
            case E_AET_SCAN_STEADY :
				// prdVer는 피크 주기성이 있는 것만 해당하는 개수이다.
				// m_nCoCanPeak 값은 피크값이 존재한 개수를 의미한다.
				//-- 조철희 2006-05-09 17:16:11 --//
				if( m_nCoCanPeak /* prdVer */ >= _spOne ) {		// _spOne -> _spThree
					m_nScnTyp = TrackUnknown;
				}
				else {
					/*! \bug  스캔 형태가 Steady 라고 할 때 Kurtosis 값은 5.0 이하이어야 한다.
							\date 2006-05-12 11:55:00, 조철희
					*/
					if( m_nSample.kurtosis <= 5.0 ) {
                        m_nScnTyp = E_AET_SCAN_STEADY;
						m_nScnPrd = _spZero;
					}
				}
				break;

            case E_AET_SCAN_CONICAL :
				// printf( "\n CONICAL1[%d]" , UDIV( m_nScnPrd, _spOneMilli) );
				if( prdVer >= _spOne ) {		// _spOne -> _spThree
					/*! \bug  Conical 일때 대칭성을 참조해서 0.7 이내에 들어야 하는 것을 추가함.
					    \date 2008-11-03 22:34:32, 조철희
					*/
					if( pSample->skewness < 0.7 )
                        m_nScnTyp = E_AET_SCAN_CONICAL;
					else
						m_nScnTyp = TrackUnknown;
				}
				else {
					m_nScnTyp = TrackUnknown;
				}
				break;

			/*! \bug  Unknown 인 형태를 추가해서 Unknown 이면 스캔 분석을 실패로 한다.
			    \date 2006-05-12 11:59:19, 조철희
			*/
			case TYPE_UNKNOWN :
				uiRet = _spAnalFail;
                break;

			default :
				printf( "\n\t [W] Invalid Steady or Conical Decision[%d] !" , ScnType );	
				WhereIs;
				break;
		}

	}
	else {
		switch( ScnType ) {
            case E_AET_SCAN_STEADY :
				if( prdVer >= _spOne ) {
					m_nScnTyp = DetectUnknown;
				}
				else {
					if( fabs( pSample->skewness ) <= 1.0 ) {	// debug, 00-04-17 20:38:23
                        m_nScnTyp = E_AET_SCAN_STEADY;
						m_nScnPrd = _spZero;
					}
					else {
						m_nScnTyp = DetectUnknown;
					}
				}
				break;

            case E_AET_SCAN_CONICAL :
				printf( "\n CONICAL2[%d]" , UDIV( m_nScnPrd, _spOneMilli) );
				if( prdVer >= _spOne ) {
					m_nScnTyp = LowIllustrationTest;
				}
                else {
                    m_nScnTyp = DetectUnknown;
                }
				break;

			/*! \bug  Unknown 인 형태를 추가해서 Unknown 이면 스캔 분석을 실패로 한다.
			    \date 2006-05-12 11:59:19, 조철희
			*/
			case TYPE_UNKNOWN :
                uiRet = _spAnalFail;
                break;

            default:
				printf( "\n\t [W] Invalid Steady or Conical Decision[%d] !" , m_nScnTyp );   
				WhereIs;
				break;

		}  
	}

    if( uiRet != _spAnalFail ) {
	    // TurnOnLED( prc_SAP, LED1 );		// debug, 00-06-05 09:39:34

	    // KurtosisSkewness( & gSample );
	    if( m_nScnTyp == LowIllustrationTest || m_nScnTyp == DetectUnknown ) {
		    if( prdVer >= _spTwo ) {
			    m_nScnTyp = DetectNonTrackScanPattern( pSample, pAcf );

			    // 최소 스캔 주기 체크함.
			    if( (UINT) m_nScnPrd <= UMUL( 300, _spOneMilli ) ) {
				    /*! \bug  스캔 분석 실패이더라도 타입 정보가 표시될 수 있음.
						    \date 2009-09-28 17:44:14, 조철희
				    */
                    m_nScnTyp = E_AET_SCAN_SCANFAIL;
				    uiRet = _spAnalFail;
			    }


			    switch( m_nScnTyp ) {
				    case _spUnknown :
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

	    else if( m_nScnTyp == TrackUnknown ) {
		    uiRet = _spAnalFail;
	    }

	    else {
		    // 최소 스캔 주기 체크함.
		    if( (UINT) m_nScnPrd <= UMUL( 7, _spOneMilli ) ) {
			    /*! \bug  스캔 분석 실패이더라도 타입 정보가 표시될 수 있음.
					    \date 2009-09-28 17:44:14, 조철희
			    */
                m_nScnTyp = E_AET_SCAN_SCANFAIL;
			    uiRet = _spAnalFail;
		    }

		    // printf( "\n SCAN[%d/%d ms]" , m_nScnTyp, UDIV( m_nScnPrd, _spOneMilli) );
		    // uiRet = _spAnalSuc;
	    }
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
BOOL CSAnalScan::CheckControlWc( UINT noEMT )
{
    BOOL bRet=FALSE;
#if defined(_A50_RWR)
	
#else    

    UINT    coCol;
	UINT	scStep;
 
  // spanTime = m_pScanPt->toa[ m_pScanPt->co-1 ] - m_pScanPt->toa[0];
  coCol = 0; //stScnAet.sap.noCol;
    scStep = 0; //stScnAet.sap.fScStep;

	if( m_nCoModWc[noEMT] <= _spOne &&			// Total count of Wonctrol Wc
        ( ( coCol >= (SCN_COLLECT_PDW-100) && scStep >= _spTwo && m_nAutoCor.idPeak <= _spTwo ) || 
        ( scStep >= _spTwo && ( fabs( m_nSample.skewness ) > 1.0 ) ) ) ) {
		bRet = TRUE;
	}
	else {
		// bRet =_spFalse;
	}
    
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

	for( i=0 ; i < pSample->co ; ++i ) {
		// pSample->pa[i] = i;
		sum += pSample->pa[i];
	}
	pSample->meanY = (float) sum / pSample->co;

 
	pSample->sdevY = SDevInArray( pSample->pa, pSample->co, pSample->meanY );

	/*! \bug  샘플링 계수에 대한 최소 값 설정
	    \date 2008-11-03 22:29:18, 조철희
	*/
	if( pSample->sdevY == _spZero || pSample->co <= 3 ) {
        _EQUALS3( pSample->kurtosis, pSample->skewness, _spZero );
		co = UINT_MAX;
	}
	else {
        N = (double) pSample->co;
        A = ( N * ( N + 1 ) ) / ( ( N - 1 ) * ( N - 2 ) * ( N - 3 ) );
        C = ( 3 * ( N - 1 ) * ( N - 1 ) ) / ( ( N - 2 ) * ( N - 3 ) );

        _EQUALS3( B3, B4, 0. );

        co = pSample->co; 
        for( i=0 ; i < co ; ++i ) {
            mds = (double) pSample->pa[i] - pSample->meanY;
            B = mds * mds * mds;

            B3 += ( B / pSample->sdevY );
            B4 += ( ( B * mds ) / pSample->sdevY );
		}

        pSample->kurtosis = (float) ( ( A * B4 ) - C );
        pSample->skewness = (float) ( B3 / N );

	}

	// printf( "\n N[%d], Kurtosis[%f], Skewness[%f]" , co, pSample->kurtosis, pSample->skewness );

	return;

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CSAnalScan::SDevInArray
// 반환되는 형  : float
// 함 수 인 자  : UINT *series
// 함 수 인 자  : int co
// 함 수 인 자  : float mean
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-02-15 19:28:26
//
float CSAnalScan::SDevInArray( UINT *series, int co, float mean )
{
  register int i;

  double sdiff;

  float diff;

  if( co <= _spOne )
		return _spZero;

  sdiff = _spZero;
  for( i=0 ; i < co ; ++i ) {
		diff = *series++ - mean;
		sdiff += ( (float) diff * (float) diff / (float) co );
  }

  return (float) sqrt( sdiff );
 
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

	if( m_nScnPrd == _spZero || m_nScnPrd == (UINT) -1 ) {
		coSamePeakDtoa = _spZero;
	}
    else {
	    _EQUALS3( virPeak, prdPeak, UDIV( m_nScnPrd, m_nSampleTime ) );

	    scnErr = UDIV( UDIV( m_nScnPrd * 5, 100 ), m_nSampleTime );
	    offErr = UDIV( stOffPdw, 1.5 );
	    maxErr = _max( 1, _min( _max( scnErr, offErr ), virPeak/2 ) );

	    coSamePeakDtoa = _spZero;

	    for( i=0 ; i < m_nCoCanPeak ; ++i ) {
		    //-- 조철희 2006-04-26 12:29:19 --//
		    // 마진 을 고려해서 피크 검증해야 함.
		    if( virPeak < m_nCanPeak[m_nCoCanPeak-1]+maxErr ) {
			    if( CompMeanDiff<int>( virPeak, m_nCanPeak[i], maxErr ) == _spTrue ) {
				    virPeak = virPeak + prdPeak;
				    ++ coSamePeakDtoa;
			    }
			    else if( virPeak < m_nCanPeak[i] ) {
				    virPeak = virPeak + prdPeak;
				    break;
			    }
		    }
		    else {
			    break;
		    }
	    }
    }

	return coSamePeakDtoa;

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CSAnalScan::HighIllustrationTest2
// 반환되는 형  : UINT
// 함 수 인 자  : STR_SAMPLE *pSample
// 함 수 인 자  : STR_AUTOCOR *pAcf
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-02-15 19:42:43
//
UINT CSAnalScan::HighIllustrationTest2( STR_SAMPLE *pSample, STR_AUTOCOR *pAcf )
{
  UINT i;
  UINT ihPeriod;

  double diff;
  float *pacf;

  double Rk;
  double dCo;

  double ccfSteady;
  double ccfConical;

  // Steady CCF 비교
  if( m_nScnPrd != _spZero && m_nScnPrd != (UINT) -1 )		ihPeriod = ( UDIV(m_nScnPrd, m_nSampleTime) + 1 );
  else                            								ihPeriod = pAcf->co;

	if( ihPeriod == 0 ) {
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
  dCo = pAcf->co;
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
        return E_AET_SCAN_CONICAL;
    }
    else {
        return E_AET_SCAN_STEADY;
    }
 
}


//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CSAnalScan::DetectNonTrackScanPattern
// 반환되는 형  : UINT
// 함 수 인 자  : STR_SAMPLE *pSample
// 함 수 인 자  : STR_AUTOCOR *pAutocf
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-02-15 19:50:55
//
UINT CSAnalScan::DetectNonTrackScanPattern( STR_SAMPLE *pSample, STR_AUTOCOR *pAutocf )
{
	UINT i;
  UINT inHalfPeriod;

	UINT coPeak;
 
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

	_EQUALS3( sum1, sum2, 0. );

	// Make function of Threshold
	inHalfPeriod = DivideBy2( _spZero, pAutocf->inPeak );
	pAcf = ( float * ) & pAutocf->acf[0];
	for( i=0 ; i < pAutocf->co ; ++i ) {
		sum1 += *pAcf;
		sum2 += ( *pAcf * *pAcf );
		++ pAcf;
	}

	mean = FDIV( sum1, pAutocf->co );
	vari = FDIV( sum2, pAutocf->co ) - ( mean * mean );

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

	if( coPeak == _spZero )
        return E_AET_SCAN_CIRCULAR;
	else if( coPeak == _spOne )
        return E_AET_SCAN_BI_DIRECTIONAL;
	else
		return _spUnknown;

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
float CSAnalScan::MeanInArray(UINT *series, UINT co)
{
    UINT i;
    UINT sum;

    sum = _spZero;
    for( i=0 ; i < co ; ++i ) {
		sum += *series++;
    }

	return ( (float) sum / (float) co );
}

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
void CSAnalScan::MakeAETfromEmitter( STR_EMITTER *pEmitter, int idxEmitter )
{

    // 기본 LOB 형태 저장
    CMakeAET::MakeAETfromEmitter( pEmitter, idxEmitter );

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
UINT CSAnalScan::MedianFreq( STR_TYPEMINMAX *pMinMax, PDWINDEX *pPdwIndex, int count )
{
    return m_pScanSigAnal->MedianFreq( pMinMax, pPdwIndex, count );
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
_TOA CSAnalScan::VerifyPRI( PDWINDEX *pPdwIndex, int count )
{
    return m_pScanSigAnal->VerifyPRI( pPdwIndex, count );
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
int CSAnalScan::FindPeakInHist( int count, PDWINDEX *pPdwIndex )
{
    return 0; //m_pScanSigAnal->FindPeakInHist( count, pPdwIndex );
}

/**
 * @brief CKAnalPRI::SaveEmitterPdwFile
 * @param pEmitter
 * @param index
 */
void CSAnalScan::SaveEmitterPdwFile(STR_EMITTER *pEmitter, int index )
{
    m_pScanSigAnal->SaveEmitterPdwFile( pEmitter, index );

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
    return m_pScanSigAnal->MedianFreq( NULL, pSeg->pdw.pIndex, pSeg->pdw.count );
}

/**
 * @brief CSAnalScan::CalcPAMean
 * @param pPdwIndex
 * @param count
 * @return
 */
int CSAnalScan::CalcPAMean(PDWINDEX *pPdwIndex, int count )
{
    return m_pScanSigAnal->CalcPAMean( pPdwIndex, count );
}

/**
 * @brief CSAnalScan::VerifyPW
 * @param pPdwIndex
 * @param count
 * @return
 */
int CSAnalScan::VerifyPW( PDWINDEX *pPdwIndex, int count )
{
    return m_pScanSigAnal->VerifyPW( pPdwIndex, count );
}

/**
 * @brief CSAnalScan::IsStorePDW
 * @return
 */
unsigned int CSAnalScan::IsStorePDW()
{
    return m_pScanSigAnal->IsStorePDW();
}

