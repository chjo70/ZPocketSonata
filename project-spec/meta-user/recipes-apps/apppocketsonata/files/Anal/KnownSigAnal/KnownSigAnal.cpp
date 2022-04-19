﻿// KnownSigAnal.cpp: implementation of the CKnownSigAnal class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include <stdio.h>
#include <string.h>

#include "../OFP_Main.h"

#include "KnownSigAnal.h"

#include "../../Include/globals.h"

#include "../../Utils/ccommonutils.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKMakeAET
// 반환되는 형  : CKnownSigAnal::CKnownSigAnal(int coMaxPdw) : CKGroup(coMaxPdw), CKPulExt(coMaxPdw), CKAnalPRI(coMaxPdw),
// 함 수 인 자  : int coMaxPdw
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-06-24 15:41:08
//
//##ModelId=429A5BDA0153
CKnownSigAnal::CKnownSigAnal(unsigned int uiCoMaxPdw, bool bDBThread, const char *pFileName) : CSigAnal(uiCoMaxPdw, bDBThread, pFileName)
{
	InitVar();

	m_theGroup = new CKGroup( this, uiCoMaxPdw);
	m_thePulExt = new CKPulExt( this, uiCoMaxPdw);
	m_theAnalPRI = new CKAnalPRI( this, uiCoMaxPdw);
	m_theMakeAET = new CKMakeAET( this, uiCoMaxPdw);

	m_nMaxPdw = uiCoMaxPdw;

	m_pSeg = GetPulseSeg();

	m_pGrPdwIndex = GetFrqAoaGroupedPdwIndex();

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKnownSigAnal::~CKnownSigAnal
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-06-24 15:38:44
//
//##ModelId=429A5BDA0154
CKnownSigAnal::~CKnownSigAnal()
{
	_SAFE_DELETE( m_theGroup )
	_SAFE_DELETE( m_thePulExt )
	_SAFE_DELETE( m_theAnalPRI )
	_SAFE_DELETE( m_theMakeAET )

}

/**
 * @brief CKnownSigAnal::Init
 */
void CKnownSigAnal::Init()
{

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CKnownSigAnal::Start
		\author   조철희
		\param    pPdwBank 인자형태 STR_PDWBANK *
		\param    pKwnAet 인자형태 STR_MANAET *
		\return   void
		\version  0.0.29
		\date     2008-07-10 12:43:16
		\warning
*/
void CKnownSigAnal::Start( STR_STATIC_PDWDATA *pstPDWData, SRxABTData *pTrkAet )
{
    Log( enLineFeed, "" );

    PrintFunction;

	BOOL bRet;

	// 추적할 에미터를 복사한다.
    m_pTrkAet = pTrkAet;

    NextStep();

	// 신호 분석 관련 초기화.
    Init( pstPDWData );

    Log( enNormal, "#### 추적 분석 시작[%dth, Co:%d] ####" , GetStep(), m_uiCoPdw );

    InsertRAWData( & m_stSavePDWData, _spZero );

	// 펄스열 인덱스를 참조하여 행렬 값에 저장한다.
    m_theGroup->MakePDWArray( & pstPDWData->stPDW[0], (int) m_uiCoPdw, pstPDWData->GetBand() );

    // 수집한 PDW 파일 만들기...
    //m_pMidasBlue->SaveRawDataFile( SHARED_DATA_DIRECTORY, E_EL_SCDT_PDW, pPDWData );

	// 그룹화 만들기
	// 기존에 추출 기능을 그대로 이용하기 위한 초기 설정함.
	m_theGroup->MakeGroup();

	// 그룹화 만들기
    if( TRUE == m_theGroup->MakeGrIndex() ) {
        // 펄스열 추출
        m_thePulExt->KnownPulseExtract();
        
        // PRI 분석
        m_theAnalPRI->KnownAnalysis();
        
        // 에미터 분석
        bRet = m_theMakeAET->KnownMakeAET();
        
        //////////////////////////////////////////////////////////////////////////
        // printf( "\n 새로운 에미터 분석 시작" );

        // 추적 추출이 성공이면 나머지 잔여 펄스들에 대해서 펄스열 추출해서 에미터를 분석한다.
        if( bRet == TRUE ) {
            // 그룹화 만들기
            m_theGroup->MakeFreqAoaPwGroup();
            m_theGroup->MakeGrIndex();
        }
        else {
            /*! \bug  추적이 실패가 되면 수집된 펄스열로부터 새로운 탐지 분석을 하게 한다.
                \date 2006-06-27 12:19:01, 조철희
            */

            memset( MARK, 0, sizeof( MARK ) );

            // 펄스열 추출 초기화
            m_thePulExt->CPulExt::Init();

            // PRI 분석 초기화
            m_theAnalPRI->CAnalPRI::Init();

            // AET 생성 초기화
            m_theMakeAET->CMakeAET::Init();
        }

        ////////////////////////////////////////////////////////////////////
        // 새로운 에미터 분석

        ////////////////////////////////////////////////////////////////////
        // 잔여 펄스들에 대해서 새로운 에미터 분석
        // 1) 처음부터 다시 새로운 에미터 분석 ?
        // 2) 추출한 펄스열은 제거한 상태에서 분석 ?
        m_thePulExt->PulseExtract();

        // 나머지 잔여 펄스들은 Unknown 펄스열 추출에 저장한다.
        // m_thePulExt->CPulExt::UnknownExtract();

        // PRI 분석을 실시한다.
        m_theAnalPRI->Analysis();

        // 상속클래스의 에미터 분석
        m_theMakeAET->MakeAET();

#ifdef _POCKETSONATA_
#elif defined(_ELINT) || defined(_XBAND_)
#else
        // 추적 에미터와 새로운 에미터와 상관성을 확인하여 추적 에미터 여부를 결정한다.
        m_theMakeAET->MakeUpAET();

        // 그룹화된 펄스열 저장하기
        SaveGroupPdwFile();

        // 수집 개수 초기화
        // 에미터 전송 전에 수집 버퍼 초기화를 한다.
        ClearColBuffer();

        SendAllAet();
#endif

        // printf( "\n !!!! End of Known Signal Analysis !!!!" );
    }

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKnownSigAnal::ClearColBuffer
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-08-30 09:20:30
//
void CKnownSigAnal::ClearColBuffer()
{
#ifdef __GNUC__
    //m_pPdwBank->count = 0;
#elif _POCKETSONATA_

#elif defined(_ELINT) || defined(_XBAND_)
#else
    m_pPdwBank-> = 0;
#endif

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CKnownSigAnal::InitVar
		\author   조철희
		\return   void
		\version  0.0.52
		\date     2008-10-25 15:59:18
		\warning
*/
void CKnownSigAnal::InitVar()
{
    // m_uiStep = 0;

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CKnownSigAnal::Init
		\author   조철희
		\param    pPdwBank 인자형태 STR_PDWBANK *
		\return   void
		\version  0.0.29
		\date     2005-06-24 16:03:22
		\warning
*/
void CKnownSigAnal::Init( STR_STATIC_PDWDATA *pstPDWData )
{
    
    // 시간 초기화
    SetColTime(_spZero);
    SetColTimeMs(_spZero);

	// 추적은 실패로 초기화 한다.
	m_CoUpdAet = 0;
	m_CoNewAet = 0;

	// 수집 버퍼 정의
    m_pstPDWData = pstPDWData;

	// 신호 수집 개수 정의
    if( pstPDWData != NULL ) {
        memcpy( & m_stSavePDWData.x, & pstPDWData->x, sizeof(UNION_HEADER) );

        // PDW 데이터로부터 정보를 신규 분석을 하기 위해 저장한다.
        SetPDWID( m_pstPDWData->GetPDWID());

        m_uiCoPdw = m_pstPDWData->GetTotalPDW();

        m_tColTime = m_pstPDWData->GetColTime();

        m_iIsStorePDW = m_pstPDWData->x.ps.iIsStorePDW;
    }
    else {
        // m_CoPdw = _spZero;

    }

    m_uiABTID = m_pTrkAet->uiABTID;

	/*! \bug  클래스별 클리어를 하게 한다.
	    \date 2008-07-30 13:22:13, 조철희
	*/

	// 그룹화 초기화
	m_theGroup->CKGroup::Init();

	// 펄스열 추출 초기화
	m_thePulExt->CKPulExt::Init();

	// PRI 분석 초기화
	m_theAnalPRI->CKAnalPRI::Init();

	// AET 생성 초기화
	m_theMakeAET->CKMakeAET::Init();

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKnownSigAnal::MarkToPdwIndex
// 반환되는 형  : void
// 함 수 인 자  : PDWINDEX *pPdwIndex
// 함 수 인 자  : int count
// 함 수 인 자  : int mark_type
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-07-28 11:49:37
//
//##ModelId=42E85F3401B8
void CKnownSigAnal::MarkToPdwIndex( PDWINDEX *pPdwIndex, unsigned int uiCount, USHORT usMarkType)
{
    for (unsigned int i = 0; i < uiCount; ++i) {
        MARK[*pPdwIndex++] = usMarkType;
    }
}

#ifdef _POCKETSONATA_
#elif defined(_ELINT)
#else
//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKnownSigAnal::SendAllAet
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-07-29 09:49:57
//
//##ModelId=42E98F2E01E5
void CKnownSigAnal::SendAllAet()
{
	int i, count;

	m_CoNewAet = 0;

    SRxLOBData *pNewAet;
    SRxLOBData *pUpdAet;
    SRxLOBData *pDstAet;

	// 추적 성공 또는 실패인지를 검사한다.
	pUpdAet = m_theMakeAET->GetUpdLOB();
	if( pUpdAet != NULL ) {
		SendUpdAet( pUpdAet );
		m_CoUpdAet = 1;
	}
	else {
		SendLostAet();
		m_CoUpdAet = 0;
	}

// 	if( CO_MAX_KSP_NEW_AET >= 0 ) {
// 		// m_theMakeAET->SetCoNewAet( 0 );
// 		return;
// 	}
// 
// 	// 두개 이상의 추적 성공 에미터 제외한다.
// 	count = m_theMakeAET->GetCoNewAet();
// 
//     pNewAet = m_theMakeAET->GetLOBData();
// 
// 	int inEMT;
// 
// 	inEMT = m_theMakeAET->GetIndexNewAet();
// 
// 	/*! \bug  새로운 에미터에 대한 포인터
// 	    \date 2008-07-30 13:06:51, 조철희
// 	*/
// 	pDstAet = pNewAet + inEMT;
// 
// 	for( i=0 ; i < count ; ++i ) {
// 		if( pUpdAet == NULL ||
//             ( pUpdAet != NULL && m_theMakeAET->CheckHarmonic<SRxLOBData>( pUpdAet, (pNewAet+inEMT) ) == 0 ) ) {
// 			// CheckHarmonic() 에서는 PRI 값으로 펄스열 병합을 수행하고
// 			// 실패된 펄스열에 대해서 이제는 펄스열 인덱스를 비교해서 두 펄스열간의 병합을 최종 판단한다.
// 			//-- 조철희 2005-10-31 13:59:43 --//
// 			//if( TRUE == CheckPdwHarmonic( pUpdAet, pNewAet ) )
// 			{
// 				SendNewAet( pNewAet, inEMT );
// 
// 				memcpy( pDstAet, & pNewAet[inEMT], sizeof( STR_NEWAET ) );
// 				++ pDstAet;
// 
// 				// 추적에서 새로운 에미터 개수를 제한한다.
// 				++ m_CoNewAet;
// 				if( m_CoNewAet >= CO_MAX_KSP_NEW_AET ) {
// 					// m_theMakeAET->SetCoNewAet( m_CoNewAet );
// 					return;
// 				}
// 			}
// 		}
// 
// 		++ inEMT;
// 	}

	// m_theMakeAET->SetCoNewAet( CoNewAet );

}
#endif

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKnownSigAnal::SendUpdAet
// 반환되는 형  : void
// 함 수 인 자  : STR_UPDAET *pUpdAet
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-07-29 10:46:25
//
//##ModelId=42E98F2E0131
void CKnownSigAnal::SendUpdAet( SRxLOBData *pUpdAet )
{
	// m_theMakeAET->DISP_FineAet( pUpdAet );

#ifdef _WIN32

#else
	// SendKSPUpdAet( pUpdAet );

#endif


}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKnownSigAnal::SendLostAet
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-07-29 10:49:25
//
//##ModelId=42E98F2E00FF
void CKnownSigAnal::SendLostAet()
{
#ifdef _WIN321
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CAdvSigAnalView *pView = ( CAdvSigAnalView * ) pFrame->GetActiveView();

	gUpdAet[m_KwnAet.aet.noEMT].aet.noEMT = 0;
	pView->UpdateUpdAetInfo( & gUpdAet[stTrkAet.aet.noEMT], m_pPdwBank );
	SendKSPLostAet( & stTrkAet, _spInsuPul );
#else
	// SendKSPLostAet( & stTrkAet, _spInsuPul );

#endif

#if defined(_ELINT_) || defined(_XBAND_)
	//Log( enNormal, "Lost[%d]" , stTrkAet.aet.noEMT );
#else
#endif

    //if( stTrkAet.aet.noEMT == -1 ) {
    //	while( true );
    //}

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKnownSigAnal::SendNewAet
// 반환되는 형  : void
// 함 수 인 자  : STR_NEWAET *pNewAet
// 함 수 인 자  : int inEMT
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-07-29 10:50:28
//
//##ModelId=42E98F2E004B
void CKnownSigAnal::SendNewAet(SRxLOBData *pNewAet, int inEMT )
{

	// m_theMakeAET->DISP_FineAet( pNewAet+inEMT );

#ifdef _WIN32

#else
	// SendKSPNewAet( pNewAet, inEMT );

#endif


}

