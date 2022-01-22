// LOBTableView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "RADARANLAPP.h"
#include "LOBTableView.h"

#include <sstream>

#include "../../files/Anal/OFP_Main.h"

#include "../../files/Anal/EmitterMerge/ELStringDefn.h"

#define	MAX_DB_LOB_DATA				(1000)

// LOB 검색 조회
#define	QUERY_LOB_APPNAME			"LOBQUERY" 
#define	QUERY_LOB_KEYNAME			"OP_INIT_ID"
#define	QUERY_AET_KEYNAME			"AETID"
#define	QUERY_COLLECTOR_ID_KEYNAME	"COLLECTORID"


// CLOBTableView

IMPLEMENT_DYNCREATE(CLOBTableView, CFormView)

CLOBTableView::CLOBTableView()
	: CFormView(CLOBTableView::IDD)
{
	AllocMemory();
}

CLOBTableView::~CLOBTableView()
{
	FreeMemory();
}

void CLOBTableView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LOB, m_CListLOB);
	DDX_Control(pDX, IDC_EDIT_OPINITID, m_CEditOpInitId);
	DDX_Control(pDX, IDC_EDIT_AETID, m_CEditAETID);
	DDX_Control(pDX, IDC_EDIT_COLLECTOR_ID, m_CEditCollectorID);
}

BEGIN_MESSAGE_MAP(CLOBTableView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_QUERY, &CLOBTableView::OnBnClickedButtonQuery)
	ON_WM_DESTROY()
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CLOBTableView::OnHdnItemclickListLob)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_LOB, &CLOBTableView::OnLvnColumnclickListLob)
	ON_WM_SIZE()
	ON_NOTIFY(HDN_ITEMKEYDOWN, 0, &CLOBTableView::OnHdnItemKeyDownListLob)
	ON_NOTIFY(NM_CLICK, IDC_LIST_LOB, &CLOBTableView::OnNMClickListLob)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_LOB, &CLOBTableView::OnNMRClickListLob)
END_MESSAGE_MAP()


// CLOBTableView 진단입니다.

#ifdef _DEBUG
void CLOBTableView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CLOBTableView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


//
void CLOBTableView::AllocMemory()
{
	m_pLOBData = ( SRxLOBData * ) malloc( sizeof(SRxLOBData) * MAX_DB_LOB_DATA );
	m_pLOBExt = ( SELLOBDATA_EXT * ) malloc( sizeof(SELLOBDATA_EXT) * MAX_DB_LOB_DATA );
}

void CLOBTableView::FreeMemory()
{
	free( m_pLOBData );
	free( m_pLOBExt );
}

// CLOBTableView 메시지 처리기입니다.


void CLOBTableView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_pDoc = ( CRADARANLAPPDoc * ) GetDocument();

	CreateListCtrl();

	char szBuffer[100];

	m_pDoc->LoadProfile( szBuffer, sizeof(szBuffer), QUERY_LOB_APPNAME , QUERY_LOB_KEYNAME );
	m_CEditOpInitId.SetWindowText( szBuffer );

	m_pDoc->LoadProfile( szBuffer, sizeof(szBuffer), QUERY_LOB_APPNAME , QUERY_AET_KEYNAME );
	m_CEditAETID.SetWindowText( szBuffer );

	m_pDoc->LoadProfile( szBuffer, sizeof(szBuffer), QUERY_LOB_APPNAME , QUERY_COLLECTOR_ID_KEYNAME );
	m_CEditCollectorID.SetWindowText( szBuffer );
	
}


void CLOBTableView::OnBnClickedButtonQuery()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    UINT i;
	int j, k, opInitId, aetid, collector_id;
	int nList=0, iCnt=0;

	char szWhere[200];
	CString strValue;

	char szBuffer[200];

	SRxLOBData *pLOBData;
	SELLOBDATA_EXT *pLOBExt;

	struct tm timeInfo;

	std::string strAETID;
	std::vector<int> iVect;

	m_CEditOpInitId.GetWindowText( strValue );
	opInitId = atoi( strValue );
	m_CEditCollectorID.GetWindowText( strValue );
	collector_id = atoi( strValue );

	m_CEditAETID.GetWindowText( strValue );
	strAETID = strValue;
	std::stringstream ss(strAETID);

	while( ss >> i ) {
		char ch;

		iVect.push_back(i);

		ch = ss.peek();
		if( ch == ',' || ch ==';' ) {
			ss.ignore();
		}
	}

	m_CListLOB.DeleteAllItems();
	
	for( i=0 ; i < iVect.size() ; ++i ) {
		iCnt = 0;
		aetid = iVect.at(i);
		iCnt += sprintf_s( & szWhere[iCnt], sizeof(szWhere)-iCnt, "where OP_INIT_ID='%d'" , opInitId );
		if( aetid != 0 ) {
			iCnt += sprintf_s( & szWhere[iCnt], sizeof(szWhere)-iCnt, " AND AETID='%d'" , aetid );
		}
		if( collector_id != 0 ) {
			iCnt += sprintf_s( & szWhere[iCnt], sizeof(szWhere)-iCnt, " AND COLLECTOR_ID='%d'" , collector_id );
		}
		m_pDoc->GetDB_LOB( & m_nLOB, m_pLOBData, m_pLOBExt, szWhere, MAX_DB_LOB_DATA );

		pLOBData = m_pLOBData;
		pLOBExt = m_pLOBExt;
		for( j=0 ; j < m_nLOB ; ++j ) {
			sprintf_s( szBuffer, sizeof(szBuffer), "%d", pLOBData->uiSeqNum );
			m_CListLOB.InsertItem( nList, szBuffer );

			k = 3;

			sprintf_s( szBuffer, sizeof(szBuffer), "%d", pLOBData->uiSeqNum );
			m_CListLOB.SetItemText( nList, 1, szBuffer );

			sprintf_s( szBuffer, sizeof(szBuffer), "%d", pLOBExt->aetData.lOpInitID );
			m_CListLOB.SetItemText( nList, 2, szBuffer );

			sprintf_s( szBuffer, sizeof(szBuffer), "%d", pLOBData->uiLOBID );
			m_CListLOB.SetItemText( nList, k++, szBuffer );

			sprintf_s( szBuffer, sizeof(szBuffer), "%d", pLOBData->uiABTID );
			m_CListLOB.SetItemText( nList, k++, szBuffer );

			sprintf_s( szBuffer, sizeof(szBuffer), "%d", pLOBData->uiAETID );
			m_CListLOB.SetItemText( nList, k++, szBuffer );

			sprintf_s( szBuffer, sizeof(szBuffer), "%s", pLOBData->aucTaskID );
			m_CListLOB.SetItemText( nList, k++, szBuffer );

			_localtime32_s( & timeInfo, & pLOBData->tiContactTime );
			sprintf_s( szBuffer, sizeof(szBuffer), "%02d-%02d-%02d %02d:%02d:%02d.%03d", timeInfo.tm_year-100, timeInfo.tm_mon, timeInfo.tm_mday, timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec, pLOBData->tiContactTimems );
			m_CListLOB.SetItemText( nList, k++, szBuffer );

            sprintf_s( szBuffer, sizeof(szBuffer), "%d", pLOBData->tiContactTimems );
            m_CListLOB.SetItemText( nList, k++, szBuffer );

			sprintf_s( szBuffer, sizeof(szBuffer), "%s", g_szAetSignalType[pLOBData->iSignalType] );
			m_CListLOB.SetItemText( nList, k++, szBuffer );

			sprintf_s( szBuffer, sizeof(szBuffer), "%.1f", pLOBData->fDOAMean );
			m_CListLOB.SetItemText( nList, k++, szBuffer );

			sprintf_s( szBuffer, sizeof(szBuffer), "%.1f", pLOBData->fDOAMin );
			m_CListLOB.SetItemText( nList, k++, szBuffer );

			sprintf_s( szBuffer, sizeof(szBuffer), "%.1f", pLOBData->fDOAMax );
			m_CListLOB.SetItemText( nList, k++, szBuffer );

			sprintf_s( szBuffer, sizeof(szBuffer), "%d", pLOBData->iDIRatio );
			m_CListLOB.SetItemText( nList, k++, szBuffer );

			sprintf_s( szBuffer, sizeof(szBuffer), "%s", g_szAetFreqType[pLOBData->iFreqType] );
			m_CListLOB.SetItemText( nList, k++, szBuffer );

			sprintf_s( szBuffer, sizeof(szBuffer), "%s", strAetFreqPRIPatternType[pLOBData->iFreqPatternType] );
			m_CListLOB.SetItemText( nList, k++, szBuffer );

			sprintf_s( szBuffer, sizeof(szBuffer), "%f", pLOBData->fFreqPatternPeriod );
			m_CListLOB.SetItemText( nList, k++, szBuffer );

			sprintf_s( szBuffer, sizeof(szBuffer), "%.3f", pLOBData->fFreqMean );
			m_CListLOB.SetItemText( nList, k++, szBuffer );

			sprintf_s( szBuffer, sizeof(szBuffer), "%.3f", pLOBData->fFreqMin );
			m_CListLOB.SetItemText( nList, k++, szBuffer );

			sprintf_s( szBuffer, sizeof(szBuffer), "%.3f", pLOBData->fFreqMax );
			m_CListLOB.SetItemText( nList, k++, szBuffer );

			sprintf_s( szBuffer, sizeof(szBuffer), "%d", pLOBData->iFreqPositionCount );
			m_CListLOB.SetItemText( nList, k++, szBuffer );

			sprintf_s( szBuffer, sizeof(szBuffer), "%s", g_szAetPriType[pLOBData->iPRIType] );
			m_CListLOB.SetItemText( nList, k++, szBuffer );

			sprintf_s( szBuffer, sizeof(szBuffer), "%s", strAetFreqPRIPatternType[pLOBData->iPRIPatternType] );
			m_CListLOB.SetItemText( nList, k++, szBuffer );

			sprintf_s( szBuffer, sizeof(szBuffer), "%f", pLOBData->fPRIPatternPeriod );
			m_CListLOB.SetItemText( nList, k++, szBuffer );

			sprintf_s( szBuffer, sizeof(szBuffer), "%.3f", pLOBData->fPRIMean );
			m_CListLOB.SetItemText( nList, k++, szBuffer );

			sprintf_s( szBuffer, sizeof(szBuffer), "%.3f", pLOBData->fPRIMin );
			m_CListLOB.SetItemText( nList, k++, szBuffer );

			sprintf_s( szBuffer, sizeof(szBuffer), "%.3f", pLOBData->fPRIMax );
			m_CListLOB.SetItemText( nList, k++, szBuffer );

			sprintf_s( szBuffer, sizeof(szBuffer), "%.1f", pLOBData->fPRIJitterRatio );
			m_CListLOB.SetItemText( nList, k++, szBuffer );

			sprintf_s( szBuffer, sizeof(szBuffer), "%d", pLOBData->iPRIPositionCount );
			m_CListLOB.SetItemText( nList, k++, szBuffer );

			sprintf_s( szBuffer, sizeof(szBuffer), "%.3f", pLOBData->fPWMean );
			m_CListLOB.SetItemText( nList, k++, szBuffer );

			sprintf_s( szBuffer, sizeof(szBuffer), "%.3f", pLOBData->fPWMin );
			m_CListLOB.SetItemText( nList, k++, szBuffer );

			sprintf_s( szBuffer, sizeof(szBuffer), "%.3f", pLOBData->fPWMax );
			m_CListLOB.SetItemText( nList, k++, szBuffer );

			sprintf_s( szBuffer, sizeof(szBuffer), "%.3f", pLOBData->fPAMean );
			m_CListLOB.SetItemText( nList, k++, szBuffer );

			sprintf_s( szBuffer, sizeof(szBuffer), "%.3f", pLOBData->fPAMin );
			m_CListLOB.SetItemText( nList, k++, szBuffer );

			sprintf_s( szBuffer, sizeof(szBuffer), "%.3f", pLOBData->fPAMax );
			m_CListLOB.SetItemText( nList, k++, szBuffer );

			sprintf_s( szBuffer, sizeof(szBuffer), "%d", pLOBData->iIsStoreData );
			m_CListLOB.SetItemText( nList, k++, szBuffer );

			sprintf_s( szBuffer, sizeof(szBuffer), "%d", pLOBData->iNumOfPDW );
			m_CListLOB.SetItemText( nList, k++, szBuffer );

			sprintf_s( szBuffer, sizeof(szBuffer), "%d", pLOBData->iCollectorID );
			m_CListLOB.SetItemText( nList, k++, szBuffer );

			sprintf_s( szBuffer, sizeof(szBuffer), "%.4f", pLOBData->fRadarLatitude );
			m_CListLOB.SetItemText( nList, k++, szBuffer );

			sprintf_s( szBuffer, sizeof(szBuffer), "%.4f", pLOBData->fRadarLongitude );
			m_CListLOB.SetItemText( nList, k++, szBuffer );

			sprintf_s( szBuffer, sizeof(szBuffer), "%s", pLOBData->szRadarModeName );
			m_CListLOB.SetItemText( nList, k++, szBuffer );

			sprintf_s( szBuffer, sizeof(szBuffer), "%d", pLOBData->iRadarModeIndex );
			m_CListLOB.SetItemText( nList, k++, szBuffer );

			//sprintf_s( szBuffer, sizeof(szBuffer), "%d", pLOBData->iThreatIndex );
			//m_CListLOB.SetItemText( nList, k++, szBuffer );

			++ pLOBData;
			++ pLOBExt;
			++ nList;
		}
	}

    // 입력 정보 저장하기
	WriteProfile();

}

int CLOBTableView::GetFieldIndex( char *pMatch, int nCoField, char **pszField )
{
	int i, iRet=-1;

	for( i=0 ; i < nCoField ; ++i ) {
		if( strcmp( pMatch, *pszField ) == 0 ) {
			iRet = i;
			break;
		}

		++ pszField;
	}

	return iRet;
}

void CLOBTableView::CreateListCtrl()
{
	int i;
	int nCoField;
	char **pszField;

	CRect rect, rList;

	GetClientRect(&rect);

	pszField = ( char ** ) malloc( sizeof(char *) * MAX_COUNT_OF_FIELD );
	for( i=0 ; i < MAX_COUNT_OF_FIELD ; ++i ) {
		pszField[i] = ( char * ) malloc( sizeof(char) * MAX_OF_COLUMN_LENGTH );
		memset( pszField[i], 0, sizeof(MAX_OF_COLUMN_LENGTH) );
	}

	m_pDoc->GetFieldNameOfTable( & nCoField, & pszField[1], "LOBDATA" );

	m_nField_OPINITID = GetFieldIndex( "OP_INIT_ID", nCoField, & pszField[0] );
	m_nField_LOBID = GetFieldIndex( "LOBID", nCoField, & pszField[0] );
	m_nField_ABTID = GetFieldIndex( "ABTID", nCoField, & pszField[0] );
	m_nField_AETID = GetFieldIndex( "AETID", nCoField, & pszField[0] );

	m_CListLOB.GetWindowRect( & rList );

	m_CListLOB.SetExtendedStyle( m_CListLOB.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT );
	m_CListLOB.SetWindowPos( NULL, 0, 70, rect.right, rect.bottom, SWP_NOZORDER );

	for( i=0 ; i <= nCoField ; ++i ) {
		m_CListLOB.InsertColumn( i, pszField[i], LVCFMT_LEFT, 10*strlen(pszField[i]) );
	}

	for( i=0 ; i < MAX_COUNT_OF_FIELD ; ++i ) {
		free( pszField[i] );
	}
	free( pszField );

}

void CLOBTableView::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	WriteProfile();

}

void CLOBTableView::WriteProfile()
{
	CString strValue;

	m_CEditOpInitId.GetWindowText( strValue );
	m_pDoc->WriteProfile( QUERY_LOB_APPNAME , QUERY_LOB_KEYNAME , (LPSTR) (LPCTSTR) strValue );

	m_CEditAETID.GetWindowText( strValue );
	m_pDoc->WriteProfile( QUERY_LOB_APPNAME , QUERY_AET_KEYNAME , (LPSTR) (LPCTSTR) strValue );

	m_CEditCollectorID.GetWindowText( strValue );
	m_pDoc->WriteProfile( QUERY_LOB_APPNAME , QUERY_COLLECTOR_ID_KEYNAME , (LPSTR) (LPCTSTR) strValue );
}


void CLOBTableView::OnHdnItemclickListLob(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CLOBTableView::OnLvnColumnclickListLob(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CLOBTableView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CRect rect;
	GetClientRect(&rect);

	if( m_CListLOB.m_hWnd != NULL ) {
		m_CListLOB.SetWindowPos( NULL, 0, 70, rect.right, rect.bottom-60, SWP_NOZORDER );
	}
}


void CLOBTableView::OnHdnItemKeyDownListLob(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CLOBTableView::OnNMClickListLob(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.


	*pResult = 0;
}


void CLOBTableView::OnNMRClickListLob(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 현재 선택된 항목의 인덱스를 얻는다.
	int index = m_CListLOB.GetSelectionMark();
	CString strValue;

	// 정상적으로 선택한 경우
	if( index != -1 ) {
		int iCnt=0;
		int nLOB, nLOB_Position;
		char szWhere[200];

		// 선택된 항목에서 이름을 얻는다.
		strValue = m_CListLOB.GetItemText( index, m_nField_LOBID );
		iCnt += sprintf_s( & szWhere[iCnt], sizeof(szWhere)-iCnt, "where LOBID='%s'" , (LPSTR) (LPCTSTR) strValue );

		strValue = m_CListLOB.GetItemText( index, m_nField_ABTID );
		iCnt += sprintf_s( & szWhere[iCnt], sizeof(szWhere)-iCnt, " AND ABTID='%s'" , (LPSTR) (LPCTSTR) strValue );

		strValue = m_CListLOB.GetItemText( index, m_nField_AETID );
		iCnt += sprintf_s( & szWhere[iCnt], sizeof(szWhere)-iCnt, " AND AETID='%s'" , (LPSTR) (LPCTSTR) strValue );

		strValue = m_CListLOB.GetItemText( index, m_nField_OPINITID );
		iCnt += sprintf_s( & szWhere[iCnt], sizeof(szWhere)-iCnt, " AND OP_INIT_ID='%s'" , (LPSTR) (LPCTSTR) strValue );

		m_pDoc->GetDB_LOB( & nLOB, m_pLOBData, m_pLOBExt, szWhere, MAX_LOB_DATA );
		m_pDoc->GetDB_LOB_POSITION( & nLOB_Position, m_pLOBData, szWhere, MAX_LOB_DATA );

		if( nLOB == 1 ) {
			m_pDoc->Run( 1, m_pLOBData, m_pLOBExt );


		}

		// 에디트 박스에 이름을 설정한다.
		//SetDlgItemText(IDC_NAME_EDIT, str);

		// ID를 얻는다.
		//str = m_user_list.GetItemText(index, 1);
		// 에디트 박스에 ID를 설정한다.
		//SetDlgItemText(IDC_ID_EDIT, str);     

		// 해당 항목에 설정되어있던 문자열 메모리를 얻는다.
		//char *p_data = (char *)m_user_list.GetItemData(index);
		// 문자열 메모리에 있는 비밀번호를 에디트 박스에 설정한다.
		//SetDlgItemText(IDC_PASSWORD_EDIT, p_data); 
	}
	*pResult = 0;
}


