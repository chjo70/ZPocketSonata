// NMakeAET.cpp: implementation of the NMakeAET class.
//
//////////////////////////////////////////////////////////////////////

#include "../SigAnal/stdafx.h"

#ifdef _WIN32
// PC용 상위 클래스에 전달하기 위한 선언
//#include "../../A50SigAnal/stdafx.h"

#endif

#include "../OFP_Main.h"

#include <sys/timeb.h>
#include <stdio.h>

#include "NMakeAET.h"
#include "NewSigAnal.h"


#ifdef _ELINT_
const char aet_signal_type[ST_MAX][3] = { "NP" , "CW" , "DP" , "FM" , "CF", "SH", "AL" };
const char aet_freq_type[MAX_FRQTYPE][3] = { "--", "F_" , "HP" , "RA" , "PA", "UK" };
const char aet_pri_type[MAX_PRITYPE][3] = { "ST" , "JT", "DW" , "SG" , "PT" } ;
const char aet_asp_type_ch[MAX_SCANTYPE][3] = { "UK" , "CR" , "UD" , "BD" , "CO" , "ST" , "UF" } ;
const char aet_stat[MAX_EMITTER_STAT] = { 'N', 'U', 'M', 'L', 'D' } ;

#else
const char aet_signal_type[5][3] = { "UK" , "NP" , "CW" , "DP" , "HP" };
const char aet_freq_type[8][3] = { "UK" , "F_" , "RA" , "PA", "HP", "C+", "C-", "pM" };
const char aet_pri_type[6][3] = { "UK" , "ST" , "SG" , "JT" , "PT", "DW" } ;
const char aet_asp_type_ch[7][3] = { "UK" , "CR" , "SC" , "TW" , "CO" , "ST" , "MA" } ;

#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CNMakeAET
// 반환되는 형  : CNMakeAET::CNMakeAET(void *pParent, int coMaxPdw) :
// 함 수 인 자  : void *pParent
// 함 수 인 자  : int coMaxPdw
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-01-20 19:04:38
//
CNMakeAET::CNMakeAET( void *pParent, int coMaxPdw ) : CMakeAET( coMaxPdw )
{
    m_pNewSigAnal = ( CNewSigAnal * ) pParent;

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CNMakeAET::~CNMakeAET
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-01-20 19:04:41
//
CNMakeAET::~CNMakeAET()
{

}

//////////////////////////////////////////////////////////////////////
//
//! \brief    CNMakeAET::Init
//! \author   조철희
//! \return   void
//! \version  1.37
//! \date     2006-08-29 10:11:11
//! \warning
//
void CNMakeAET::Init()
{
    /*! \bug  하위 그룹에서 초기화하는 것으로 수정함.
        \date 2008-07-30 13:29:46, 조철희
    */
    m_CoMakeLOB = 0;

    m_enBandWidth = m_pNewSigAnal->GetBandWidth();

    CMakeAET::Init();
}

//////////////////////////////////////////////////////////////////////
//
//! \brief    PRI 분석을 통해서 P-AET를 근더로 에미터를 생성한다.
//! \author   조철희
//! \return   void
//! \version  1.37
//! \date     2006-08-29 10:10:16
//! \warning
//
void CNMakeAET::MakeAET()
{
    // 초기화
    // Init();
    PrintFunction

    CMakeAET::MakeAET();
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : 히스토그램을 이용해서 방위 평균값을 계산한다.
// 반환되는 형  : int
// 함 수 인 자  : STR_PDWINDEX *pSrcIndex
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-01-23 10:17:23
//
int CNMakeAET::CalcAoaMeanByHistAoa( STR_PDWINDEX *pSrcIndex )
{
    return m_pNewSigAnal->CalcAoaMeanByHistAoa( pSrcIndex );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : 신호를 수집한다.
// 반환되는 형  : int
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-01-23 10:17:27
//
int CNMakeAET::GetColPdw()
{
    return m_pNewSigAnal->GetColPdw();
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CNMakeAET::CalcPAMean
// 반환되는 형  : int
// 함 수 인 자  : PDWINDEX *pPdwIndex
// 함 수 인 자  : int count
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-01-23 10:17:30
//
int CNMakeAET::CalcPAMean(PDWINDEX *pPdwIndex, int count )
{
    return m_pNewSigAnal->CalcPAMean( pPdwIndex, count );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CNMakeAET::VerifyPW
// 반환되는 형  : int
// 함 수 인 자  : PDWINDEX *pPdwIndex
// 함 수 인 자  : int count
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-01-23 10:17:32
//
int CNMakeAET::VerifyPW( PDWINDEX *pPdwIndex, int count )
{
    return m_pNewSigAnal->VerifyPW( pPdwIndex, count );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CNMakeAET::MarkToPdwIndex
// 반환되는 형  : void
// 함 수 인 자  : PDWINDEX *pPdwIndex
// 함 수 인 자  : int count
// 함 수 인 자  : int mark_type
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-01-23 10:17:35
//
void CNMakeAET::MarkToPdwIndex( PDWINDEX *pPdwIndex, int count, int mark_type )
{
    m_pNewSigAnal->MarkToPdwIndex( pPdwIndex, count, mark_type );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CNMakeAET::SaveEmitterPdwFile
// 반환되는 형  : void
// 함 수 인 자  : STR_EMITTER *pEmitter
// 함 수 인 자  : int index
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-01-23 10:17:37
//
void CNMakeAET::SaveEmitterPdwFile(STR_EMITTER *pEmitter, int index )
{
    m_pNewSigAnal->SaveEmitterPdwFile( pEmitter, index );

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CNMakeAET::GetCoSeg
// 반환되는 형  : int
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-01-23 10:17:39
//
int CNMakeAET::GetCoSeg()
{
    return m_pNewSigAnal->GetCoSeg();
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CNMakeAET::GetCoEmitter
// 반환되는 형  : int
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-01-23 10:17:42
//
int CNMakeAET::GetCoEmitter()
{
    return m_pNewSigAnal->GetCoLOB();
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : *CNMakeAET::GetPulseSeg
// 반환되는 형  : STR_PULSE_TRAIN_SEG
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-01-23 10:17:44
//
STR_PULSE_TRAIN_SEG *CNMakeAET::GetPulseSeg()
{
    return m_pNewSigAnal->GetPulseSeg();
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : *CNMakeAET::GetEmitter
// 반환되는 형  : STR_EMITTER
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-01-23 10:17:47
//
STR_EMITTER *CNMakeAET::GetEmitter()
{
    return m_pNewSigAnal->GetEmitter();
}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CalcFreqMedian
//!	\author  조철희
//!	\param	 pSeg	인자형태 STR_PULSE_TRAIN_SEG *
//!	\return	 UINT
//! \version 1.0
//! \date		 2006-05-09 14:56:34
//! \bug
//! \warning
//
UINT CNMakeAET::CalcFreqMedian( STR_PULSE_TRAIN_SEG *pSeg )
{
    return m_pNewSigAnal->MedianFreq( NULL, pSeg->pdw.pIndex, pSeg->pdw.count );
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CNMakeAET::GetPdwParam
        \author   조철희
        \return   STR_PDWPARAM*
        \version  0.0.59
        \date     2008-11-19 12:01:44
        \warning
*/
STR_PDWPARAM* CNMakeAET::GetPdwParam()
{
    return m_pNewSigAnal->GetPdwParam();
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CNMakeAET::MarkAllAetToPdwIndex
        \author   조철희
        \return   void
        \version  0.0.1
        \date     2008-01-22 13:13:34
        \warning
*/
void CNMakeAET::MarkAllAetToPdwIndex()
{
    int i;
    //STR_PDWINDEX *pPdwIndex;

    for( i=0 ; i < m_CoAet ; ++i ) {
        //pPdwIndex = & m_pEmitter[ m_Aet[i].ext.idxEmitter ].pdw;
        //MarkToPdwIndex( pPdwIndex->pIndex, pPdwIndex->count, EXTRACT_MARK );
    }

}

/**
  * @brief
  * @param		STR_EMITTER * pEmitter
  * @param		int idxEmitter
  * @return 	void
  * @return		성공시 true, 실패시 false
  * @date			2019/04/03
*/
void CNMakeAET::MakeAETfromEmitter( STR_EMITTER *pEmitter, int idxEmitter )
{
    int i;
    STR_MINMAX stVal;
    SRxLOBData *pLOBData;

    struct __timeb32 timeBuffer;

    STR_FRQ stFrq;
    STR_PRI stPri;

    pLOBData = & m_LOBData[m_CoAet];

    //////////////////////////////////////////////////////////////////////////

    pLOBData->uiLOBID = m_CoAet + 1;
    pLOBData->uiABTID = 0;
    pLOBData->uiAETID = 0;

    // 시간 정보
#ifdef _WIN32
    _ftime32_s( & timeBuffer );
    pLOBData->tiContactTime = timeBuffer.time; // _time32(NULL);
    pLOBData->tiContactTimems = timeBuffer.millitm;
#else
    _ftime32_s( & timeBuffer );
    pLOBData->tiContactTime = timeBuffer.time; // _time32(NULL);
    pLOBData->tiContactTimems = timeBuffer.millitm;

#endif

    // 신호 형태
    pLOBData->iSignalType = pEmitter->signal_type;

    // 방위
    MakeAOAInfoInSeg( & stVal, pEmitter );
    pLOBData->fMeanDOA = FMUL( stVal.mean, _spAOAres );			//FTOAsCNV( stVal.mean );
    pLOBData->fMaxDOA = FMUL( stVal.max, _spAOAres );				//FTOAsCNV( stVal.min );
    pLOBData->fMinDOA = FMUL( stVal.min, _spAOAres );				//FTOAsCNV( stVal.max );

// 	if( RADARCOL_1 == m_pNewSigAnal->GetCollectorID() ) {
// 		pLOBData->fMeanDOA = 180.0;
// 		pLOBData->fMaxDOA = 180.0;
// 		pLOBData->fMinDOA = 180.0;
// 	}
// 	else {
// 		pLOBData->fMeanDOA = 270.0;
// 		pLOBData->fMaxDOA = 270.0;
// 		pLOBData->fMinDOA = 270.0;
// 	}


    // DI 율
    pLOBData->iDIRatio = MakeDIInfoInSeg( pEmitter );							// [0.1%]

    // 주파수 정보 생성
    MakeFrqInfoInSeg( & stFrq, pEmitter );

    pLOBData->iFreqType = stFrq.type;
    pLOBData->iFreqPatternType = stFrq.patType;
    pLOBData->fFreqPatternPeriod = FTOAsCNV( stFrq.patPrd );
    pLOBData->fMeanFreq = FMUL( stFrq.mean, (0.001) );			//FFRQCNV( stFrq.mean );
    pLOBData->fMaxFreq = FMUL( stFrq.max, (0.001) );				//FFRQCNV( stFrq.max );
    pLOBData->fMinFreq = FMUL( stFrq.min, (0.001) );				//FFRQCNV( stFrq.min );
    pLOBData->iFreqPositionCount = stFrq.swtLev;
    memset( pLOBData->fFreqSeq, 0, sizeof(pLOBData->fFreqSeq) );
    for( i=0 ; i < pLOBData->iFreqPositionCount ; ++i ) {
        pLOBData->fFreqSeq[i] = FMUL( stFrq.swtVal[i], (0.001) );		// FFRQCNV( stFrq.swtVal[i] );
    }

    // PRI 정보 생성
    MakePRIInfoInSeg( & stPri, pEmitter );

    pLOBData->iPRIType = stPri.type;
    pLOBData->iPRIPatternType = stPri.patType;
    pLOBData->fPRIPatternPeriod = FTOAsCNV( stPri.patPrd );
    pLOBData->fMeanPRI = FDIV( stPri.mean, _spOneMicrosec );
    pLOBData->fMaxPRI = FDIV( stPri.max, _spOneMicrosec );
    pLOBData->fMinPRI = FDIV( stPri.min, _spOneMicrosec );
    pLOBData->fPRIJitterRatio = stPri.jtrPer;
    pLOBData->iPRIPositionCount = stPri.swtLev;
    memset( pLOBData->fPRISeq, 0, sizeof(pLOBData->fPRISeq) );
    for( i=0 ; i < pLOBData->iPRIPositionCount ; ++i ) {
        pLOBData->fPRISeq[i] = FDIV( stPri.swtVal[i], _spOneMicrosec );
    }

    // 펄스폭 생성
    MakePWInfoInSeg( & stVal, pEmitter );
    pLOBData->fMeanPW = FDIV( stVal.mean*1000., _spOneMicrosec );			//, _spOneMicrosec );
    pLOBData->fMaxPW = FDIV( stVal.max*1000., _spOneMicrosec );				//, _spOneMicrosec );
    pLOBData->fMinPW = FDIV( stVal.min*1000., _spOneMicrosec );				//, _spOneMicrosec );

    // 신호 세기 생성
    MakePAInfoInSeg( & stVal, pEmitter );
    pLOBData->fMeanPA = PACNV( stVal.mean );			//FPACNV( stVal.mean );
    pLOBData->fMaxPA = PACNV( stVal.max );				//FPACNV( stVal.max );
    pLOBData->fMinPA = PACNV( stVal.min );				//FPACNV( stVal.min );

    // 기타 정보 저장
    pLOBData->iIsStorePDW = m_pNewSigAnal->IsStorePDW();
    pLOBData->iNumOfPDW = pEmitter->pdw.count;
#ifdef _ELINT_
    pLOBData->iCollectorID = m_pNewSigAnal->GetCollectorID();
#endif

    // 수집소 위치 정보 저장
#ifdef _ELINT_
    if( pLOBData->iCollectorID >= RADARCOL_1 && pLOBData->iCollectorID <= RADARCOL_3 ) {
        pLOBData->dRadarCollectionLatitude = dRCLatitude[pLOBData->iCollectorID];
        pLOBData->dRadarCollectionLongitude = dRCLongitude[pLOBData->iCollectorID];
    }
    else {
        pLOBData->dRadarCollectionLatitude = 0.0;
        pLOBData->dRadarCollectionLongitude = 0.0;
    }
#else

#endif

    memset( pLOBData->aucRadarName, 0, sizeof(pLOBData->aucRadarName) );
    pLOBData->iRadarModeIndex = _spZero;
    pLOBData->iThreatIndex = _spZero;

    pLOBData->uiSeqNum = 0;

    STR_PDWDATA *pPDWData = m_pNewSigAnal->GetPDWData();

#ifdef _ELINT_
    memcpy( pLOBData->aucTaskID, pPDWData->aucTaskID, sizeof(pPDWData->aucTaskID) );
#elif defined(_POCKETSONATA_)

#else

#endif

    DISP_FineAet( pLOBData );

}

void CNMakeAET::DISP_FineAet( SRxLOBData *pLOB )
{
    char buffer[500];

// 	UINT temp;
//
// 	char buff1[20], buff2[20], buff3[20], buff4[20];
//
// 	printf( "\n" );
//
// 	int noSymbol = 0; //GetNoSymbol( pNewAet->aet.noEMT );
// 	if( pManAet->loc.trackFI.bUse == TRUE ) {
// 		if( noSymbol != -1 )
// 			printf( "%1c%2dT%2d" , aet_stat[pManAet->loc.stat], pManAet->loc.trackFI.noFilter, noSymbol );
// 		else
// 			printf( "%1c%2d-" , aet_stat[pManAet->loc.stat], pManAet->loc.trackFI.noFilter );
// 	}
// 	else {
// 		if( pManAet->loc.noThreat != -1 )
// 			printf( "%1c-T%2d" , aet_stat[pManAet->loc.stat], noSymbol );
// 		else
// 			printf( "%1c--" , aet_stat[pManAet->loc.stat] );
// 	}

    // 신호 정보
    int iCnt=0;
    iCnt += sprintf_s( & buffer[iCnt], "%s", aet_signal_type[pLOB->iSignalType]);

    // 방위
    iCnt += sprintf_s( & buffer[iCnt], " %4.1f(%4.1f,%4.1f)" , pLOB->fMeanDOA, pLOB->fMinDOA, pLOB->fMaxDOA );

    // 주파수
    iCnt += sprintf_s( & buffer[iCnt], " %s" , aet_freq_type[pLOB->iFreqType] );
// 	temp = abs( pManAet->aet.frq.max - pManAet->aet.frq.min );
    iCnt += sprintf_s( & buffer[iCnt], " %.3f[%.3f, %.3f]" , pLOB->fMeanFreq, pLOB->fMinFreq, pLOB->fMaxFreq );
    //sprintf_s( buff1, "%.3f" , pLOB->fMeanFreq );
    //sprintf_s( buff2, "%.3f" , F_FRQCNV( pManAet->aet.frq.band, pManAet->aet.frq.min ) );
    //sprintf_s( buff3, "%5d" , C_FRQCNV( pManAet->aet.frq.band, pManAet->aet.frq.max ) );
    //sprintf_s( buff4, "%3d" , TOAmsCNV( pManAet->aet.frq.patPrd ) );
    if( pLOB->iFreqType == _PATTERN_AGILE ) {
        //printf( "%s(%s,%s)%s" , Comma( buff1 ), Comma( buff2 ), Comma( buff3 ), Comma( buff4 ) );
    }
    else {
        // printf( "%s(%s∼%s)%3d" , Comma( buff1 ), Comma( buff2 ), Comma( buff3 ), FRQCNV( pNewAet->aet.frq.band, temp )-FRQCNV( pNewAet->aet.frq.band, 0 ) );
        //printf( "%s(%s,%s)%3d" , buff1, buff2, buff3, FRQCNV( pManAet->aet.frq.band, temp )-FRQCNV( pManAet->aet.frq.band, 0 ) );
    }

    // PRI
    iCnt += sprintf_s( & buffer[iCnt], " %s    " , aet_pri_type[pLOB->iPRIType] );
    iCnt += sprintf_s( & buffer[iCnt], "%0.1f(%.1f,%.1f), %2d" , pLOB->fMeanPRI, pLOB->fMinPRI, pLOB->fMaxPRI, pLOB->iPRIPositionCount );

    // PW
    iCnt += sprintf_s( & buffer[iCnt], " %.2f(%.2f,%.2f)" , pLOB->fMeanPW, pLOB->fMinPW, pLOB->fMaxPW );

    // PA
    iCnt += sprintf_s( & buffer[iCnt], " %.2f(%.2f,%.2f)" , pLOB->fMeanPA, pLOB->fMinPA, pLOB->fMaxPA );

    // ID
// 	printf( " [%d][%d,%d,%d,%d,%d]" , pManAet->aet.id.coAmbi, pManAet->aet.id.noIPL[0], pManAet->aet.id.noIPL[1], pManAet->aet.id.noIPL[2], pManAet->aet.id.noIPL[3], pManAet->aet.id.noIPL[4] );

    iCnt += sprintf_s( & buffer[iCnt], " [%3d]" , pLOB->iNumOfPDW );

    printf( "\n%s", buffer );
    Log( enNormal, "\t%s", buffer );

}
