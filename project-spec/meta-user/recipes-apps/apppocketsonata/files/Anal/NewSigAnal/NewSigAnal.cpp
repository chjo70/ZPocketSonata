/**

    @file      NewSigAnal.cpp
    @brief     탐지 신호 분석 메인 클래스
    @details   ~
    @author    조철희
    @date      15.03.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

#include "stdafx.h"

#ifdef _MSC_VER

#else
#include <unistd.h>

#endif


#ifdef _USRDLL

#else

#endif

#include <string.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "../OFP_Main.h"

#include "NewSigAnal.h"

#include "../../System/csysconfig.h"

#include "../../Include/globals.h"

#include "../../Utils/ccommonutils.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


/**
 * @brief     CNewSigAnal
 * @param     unsigned int uiCoMaxPdw
 * @param     bool bDBThread
 * @param     const char * pFileName
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-02-03 10:40:14
 * @warning
 */
CNewSigAnal::CNewSigAnal(unsigned int uiCoMaxPdw, bool bDBThread, const char *pFileName ) : CSigAnal(uiCoMaxPdw, bDBThread, pFileName )
{

	// 클래스 관련 초기화
	m_uiMaxPdw = uiCoMaxPdw;

	AallocMemory();

	m_pGrPdwIndex = GetFrqAoaGroupedPdwIndex();
	m_pSeg = GetPulseSeg();

    Init();



}

/**
 * @brief     메모리를 할당 합니다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-02-03 10:43:57
 * @warning
 */
void CNewSigAnal::AallocMemory()
{
#ifdef _SQLITE_
	// SQLITE 파일명 생성하기
	char szSQLiteFileName[100];

	strcpy(szSQLiteFileName, CEDEOB_SQLITE_FOLDER);
	strcat(szSQLiteFileName, "/");
	strcat(szSQLiteFileName, CEDEOB_SQLITE_FILENAME);

	m_pIdentifyAlg = new CELSignalIdentifyAlg(szSQLiteFileName);

#elif _MSSQL_
	CODBCDatabase *pMyODBC;
	pMyODBC = GetCODBCDatabase();
	m_pIdentifyAlg = new CELSignalIdentifyAlg(pMyODBC);

#else
	m_pIdentifyAlg = new CELSignalIdentifyAlg(NULL);

#endif

	m_VecMatchRadarMode.reserve(MAX_MATCH_RADARMODE);

	m_theGroup = new CNGroup(this, m_uiMaxPdw);
	m_thePulExt = new CNPulExt(this, m_uiMaxPdw);
	m_theAnalPRI = new CNAnalPRI(this, m_uiMaxPdw);
	m_theMakeAET = new CNMakeAET(this, m_uiMaxPdw);

	m_pTheIntraSigAnal = new CIntraSigAnal();

}

/**
 * @brief     ~CNewSigAnal
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-02-03 10:09:53
 * @warning
 */
CNewSigAnal::~CNewSigAnal()
{
    _SAFE_DELETE( g_pTheELEnvironVariable )

    _SAFE_DELETE( m_pIdentifyAlg )

    _SAFE_DELETE( m_theGroup )
    _SAFE_DELETE( m_thePulExt )
    _SAFE_DELETE( m_theAnalPRI )
    _SAFE_DELETE( m_theMakeAET )

	_SAFE_DELETE( m_pTheIntraSigAnal )

}

/**
 * @brief     LoadCEDLibrary
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-09, 10:01
 * @warning
 */
void CNewSigAnal::LoadCEDLibrary()
{
    m_pIdentifyAlg->LoadCEDLibrary();
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CNewSigAnal::Init
    \author   조철희
    \param    pPDWData 인자형태 STR_PDWDATA *
    \return   void
    \version  0.0.1
    \date     2008-01-04 09:07:28
    \warning
*/
void CNewSigAnal::Init( STR_PDWDATA *pPDWData )
{

	//////////////////////////////////////////////////////////////////////////////////////////
	// 수집 버퍼 정의
	m_pPDWData = pPDWData;

	InitAllVar();

    // 신호 수집 개수 정의
    if( pPDWData != NULL ) {
        MakeAnalDirectory( &pPDWData->x );
        CCommonUtils::DeleteAllFile( GetAnalDirectory(), 0 );

        memcpy( & m_stSavePDWData.x, & pPDWData->x, sizeof(UNION_HEADER) );

        // PDW 데이터로부터 정보를 신규 분석을 하기 위해 저장한다.
        m_uiCoPdw = pPDWData->GetTotalPDW();

		SetPDWID(pPDWData->GetPDWID());
        SetColTime(pPDWData->GetColTime());
        SetStorePDW( pPDWData->GetStorePDW() );
        SetBandWidth( pPDWData->GetBandWidth () );
        SetTaskID( pPDWData->GetTaskID() );
        SetCollectorID( pPDWData->GetCollectorID() );

    }
    else {
		SetPDWID(_spZero);
		SetStorePDW(_spZero);
		SetBandWidth(_spZero);
		SetCollectorID(RADARCOL_Unknown);

    }

	InitOfNewSigAnal();


}

/**
 * @brief     InitOfNewSigAnal
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-02-10 11:00:23
 * @warning
 */
void CNewSigAnal::InitOfNewSigAnal()
{
	CSigAnal::InitResolution();

	// 그룹화 초기화
	m_theGroup->CNGroup::Init();

	// 펄스열 추출 초기화
	m_thePulExt->CNPulExt::Init();

	// PRI 분석 초기화
	m_theAnalPRI->CNAnalPRI::Init();

	// AET 생성 초기화
	m_theMakeAET->CNMakeAET::Init();
}



//////////////////////////////////////////////////////////////////////////
/*! \brief    CNewSigAnal::Start
    \author   조철희
    \param    pPDWData 인자형태 STR_PDWDATA *
    \return   void
    \version  0.0.1
    \date     2007-12-28 11:53:42
    \warning
*/
void CNewSigAnal::Start( STR_PDWDATA *pPDWData, bool bDBInsert )
{
    DWORD dwTime = CCommonUtils::GetTickCounts();

    Log( enLineFeed, "" );

    PrintFunction

    NextStep();

    // 신호 분석 관련 초기화.
    Init( pPDWData );

    Log( enNormal, "==== 탐지 분석 시작[%dth, Co:%d] ============================" , GetStep(), m_uiCoPdw );

    if( m_uiCoPdw <= RPC /* || m_uiCoPdw > MAX_PDW */ ) {
        Log( enNormal, "PDW(%d/%d) 데이터 개수가 모자랍니다 !!" , m_uiCoPdw, RPC );
    }
    else {
        CheckValidData( m_pPDWData );

        // 수집한 PDW 파일 저장하기...
        InsertRAWData(m_pPDWData, _spZero );

        // PDW 수집 상태 체크를 함.
		_PDW *pPDW = m_pPDWData->pstPDW;
		unsigned int uiBand = m_pPDWData->GetBand();
        if( false == m_theGroup->MakePDWArray( pPDW, m_uiCoPdw, uiBand) ) {
#if defined(_ELINT_) || defined(_XBAND_)
            //printf(" \n [W] [%d] 싸이트에서 수집한 과제[%s]의 PDW 파일[%s]의 TOA 가 어긋났습니다. 확인해보세요.." , m_pPDWData->iCollectorID, m_pPDWData->aucTaskID, m_szPDWFilename );
            Log( enError, "Invalid of PDW Data at the [%s:%d]Site !! Check the file[%s] ..." , m_pPDWData->GetTaskID(), m_pPDWData->GetCollectorID(), m_pMidasBlue->GetRawDataFilename() );
#elif defined(_POCKETSONATA_)
			unsigned int uiBoardID = m_pPDWData->x.ps.uiBoardID;
            //printf(" \n [W] [%d] 보드에서 수집한 PDW 파일[%s]의 TOA 가 어긋났습니다. 확인해보세요.." , uiBoardID, m_pMidasBlue->GetRawDataFilename() );
            Log( enError, "[%d] 보드에서 수집한 PDW 파일[%s]의 TOA 가 어긋났습니다. 확인해보세요..", uiBoardID, m_pMidasBlue->GetRawDataFilename());
#else
            Log( enError, "보드에서 수집한 PDW 파일의 TOA 가 어긋났습니다. 확인해보세요.." );
#endif
        }
        else {
            // 그룹화가 생성되지 않으면 바로 리턴한다.
            if( TRUE == m_theGroup->MakeGroup() ) {

                // 그룹화 만들기
                while( ! m_theGroup->IsLastGroup() ) {
					StartOfSignalAnalysis();

                    // 그룹화 생성 개수 증가
                    ++ m_CoGroup;

                }
            }
        }

        //m_theMakeAET->PrintAllEmitter();
        // 분석되지 못한 나머지 펄스열에 대한 파일 저장.
        SaveRemainedPdwFile();

    }

    InsertToDB_LOB( GetLOBData(0), GetCoLOB(), bDBInsert );

    Log(enNormal, "================ 탐지 분석 종료[%s] : %d[ms] =================" , CSigAnal::GetRawDataFilename(), (int)((CCommonUtils::GetTickCounts() - dwTime)) );

}

/**
 * @brief     StartOfSignalAnalysis
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-02-02 15:58:39
 * @warning
 */
void CNewSigAnal::StartOfSignalAnalysis()
{
	// 협대역 주파수 그룹화
	// 방위/주파수 그룹화에서 결정한 주파수 및 방위 범위에 대해서 필터링해서 PDW 데이터를 정한다.
	m_theGroup->MakeGrIndex();

	SaveGroupPDWFile(m_pGrPdwIndex, m_pPDWData, true);

	// 위협 라이브러리 기반 펄스열 추출하기 위한 라이브러리 검색
	CheckKnownByAnalysis();

	// 규칙성 및 불규칙성 펄스열 추출
	m_thePulExt->PulseExtract(&m_VecMatchRadarMode);

	// 나머지 잔여 펄스들은 Unknown 펄스열 추출에 저장한다.
	// m_thePulExt->UnknownExtract();

	// 하나의 그룹화에서 분석이 끝나면 다시 초기화를 한다.
	ClearAllMark();

	// PRI 분석
	m_theAnalPRI->Analysis();

	// 에미터 분석
	m_theMakeAET->MakeAET();

}


/**
 * @brief     펄스열 추출 정보를 클리어 한다 (CED 라이브러리 기반으로 추출된 펄스열 제외).
 * @param     bool bClear
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-30, 15:19
 * @warning
 */
void CNewSigAnal::ClearAllMark()
{
    unsigned int i;

    USHORT *pMark;

    pMark = & MARK[0];
    for (i = 0; i < m_uiCoPdw; ++i) {
        if (*pMark != enLIBRARY_MARK) {
            *pMark = enUnMark;
        }

        ++pMark;

    }
    // memset( & MARK[0], 0, sizeof( MARK ) );

}

/**
 * @brief     PDW 헤더 정보를 근거로 잘못 입력된 것이 있으면 FALSE 로 리턴한다.
 * @param     STR_PDWDATA * pPDWData
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-10, 14:50
 * @warning
 */
bool CNewSigAnal::CheckValidData( STR_PDWDATA *pPDWData )
{
    bool bRet=true;

#if defined(_XBAND_)
    if( pPDWData->x.xb.aucTaskID[0] == 0 ) {
        Log( enError, "PDW 데이터에 과제 정보가 없습니다. !!"  );
        bRet = false;
    }

    if( !(pPDWData->x.xb.GetCollectorID() >= RADARCOL_1 && pPDWData->x.xb.GetCollectorID() <= RADARCOL_3) ) {
        Log( enError, "수집소 ID[%d]가 잘못됐습니다." , pPDWData->x.el.GetCollectorID() );
        bRet = false;
    }

#elif defined(_ELINT_)
    if( ( pPDWData->x.el.enBandWidth != ELINT::en5MHZ_BW && pPDWData->x.el.enBandWidth != ELINT::en50MHZ_BW ) ) {
        Log( enError, "수집 대역폭[%d]은 0 또는 1이 어야 합니다!!" , pPDWData->x.el.enBandWidth );
        bRet = false;
    }
#else


#endif

    return bRet;
}

/**
 * @brief     탐지 신호분석시 멤버 변수를 초기화 한다.
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2008-01-04 09:51:51
 * @warning
 */
void CNewSigAnal::InitAllVar()
{
	m_uiCoPdw = 0;
	m_CoGroup = 0;

	// 시간 초기화
	SetColTime(0);
	SetColTimeMs(0);

}

/**
 * @brief     대역 밴드를 요청합니다.
 * @param     int freq
 * @return    enum FREQ_BAND
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2009-11-16 11:33:14
 * @warning
 */
enum FREQ_BAND CNewSigAnal::GetBand( int freq )
{
    enum FREQ_BAND enBand;

    if( freq >= 2000 && freq < 6000 ) {
        enBand = BAND1;
    }
    else if( freq >= 6000 && freq < 10000 ) {
        enBand = BAND2;
    }
    else if( freq >= 10000 && freq < 14000 ) {
        enBand = BAND3;
    }
    else if( freq >= 14000 && freq <= 19000 ) {
        enBand = BAND4;
    }
    else {
        enBand = BAND5;
    }

    return enBand;

}

/**
 * @brief     하나의 그룹화 내에서 위협 라이브러리 기반 신호 분석 플레그를 반환한다.
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-15, 12:51
 * @warning
 */
bool CNewSigAnal::CheckKnownByAnalysis()
{
    UINT i;
    UINT uiFreqMax, uiFreqMin;
    bool bRet;

    if( m_theGroup->GetPulseStat() == STAT_CW ) {
        m_VecMatchRadarMode.clear();

        bRet = false;

    }
    else {
        PDWINDEX *pPdwIndex;

        uiFreqMax = 0;
        uiFreqMin = UINT32_MAX;
        pPdwIndex = m_pGrPdwIndex->pIndex;
        for( i = 0 ; i < m_pGrPdwIndex->uiCount ; i++ ) {
            uiFreqMax = max( FREQ[*pPdwIndex], uiFreqMax );
            uiFreqMin = min( FREQ[*pPdwIndex], uiFreqMin );

            ++pPdwIndex;

        }

        bRet = m_pIdentifyAlg->CheckThereFreqRange( & m_VecMatchRadarMode, uiFreqMin, uiFreqMax );
    }

    return bRet;
}

