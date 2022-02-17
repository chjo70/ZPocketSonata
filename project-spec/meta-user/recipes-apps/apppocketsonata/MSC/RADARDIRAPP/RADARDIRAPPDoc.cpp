
// RADARDIRAPPDoc.cpp : CRADARDIRAPPDoc 클래스의 구현
//

#include "stdafx.h"


// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "RADARDIRAPP.h"
#endif



#include "MainFrm.h"

#include "RADARDIRAPPDoc.h"
#include "RADARDIRAPPView.h"

#include "../RadarDIR/RadarDirAlgorithm.h"

#include "../../files/Utils/ccommonutils.h"

#include <propkey.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CRADARDIRAPPDoc

IMPLEMENT_DYNCREATE(CRADARDIRAPPDoc, CDocument)

BEGIN_MESSAGE_MAP(CRADARDIRAPPDoc, CDocument)
END_MESSAGE_MAP()


// CRADARDIRAPPDoc 생성/소멸

CRADARDIRAPPDoc::CRADARDIRAPPDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CRADARDIRAPPDoc::~CRADARDIRAPPDoc()
{
}

BOOL CRADARDIRAPPDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CRADARDIRAPPDoc serialization

void CRADARDIRAPPDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
        
	}
	else {
	    // TODO: 여기에 로딩 코드를 추가합니다.
        m_theDataFile.ReadDataFile( & m_stPDWData, ar.m_strFileName.GetBuffer(), -1, NULL, NULL, false );

        CMainFrame *pMainFrame=( CMainFrame * ) AfxGetMainWnd();

        RadarDirAlgotirhm::RadarDirAlgotirhm::Init( pMainFrame->GetOutputWnd()->GetSafeHwnd(), true );

        RadarDirAlgotirhm::RadarDirAlgotirhm::LoadCEDLibrary();

        RadarDirAlgotirhm::RadarDirAlgotirhm::Start( & m_stPDWData );

	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CRADARDIRAPPDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CRADARDIRAPPDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CRADARDIRAPPDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CRADARDIRAPPDoc 진단

#ifdef _DEBUG
void CRADARDIRAPPDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRADARDIRAPPDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CRADARDIRAPPDoc 명령

bool CRADARDIRAPPDoc::OpenFile( CString &strPathname )
{
	CString strMainTitle;

    

	m_pMainFrame=(CMainFrame *) AfxGetApp()->m_pMainWnd;
	// 	map<CString, CData *>::iterator it;
	// 	//CData *pData;
	// 
	//pChild = ( CChildFrame * ) m_pFrame->GetActiveFrame();
	// 
	m_strPathname = strPathname;
	// 
	// 	// 데이터 읽기
	// 	it = m_gMapData.find( m_strPathname );
	// 	if( it == m_gMapData.end() ) {
	ReadDataFile();
	// 
	// 	}
	// 	else {
	// 		m_theDataFile.SetData( it->second );
	// 
	// 	}
	// 
	// 	// 타이틀 바 변경
	strMainTitle.Format( "%s" , m_strPathname );
	m_pMainFrame->SetWindowText( strMainTitle );

	return true;
}

/**
 * @brief     ReadDataFile
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-10-28, 16:51
 * @warning
 */
void CRADARDIRAPPDoc::ReadDataFile()
{
	unsigned int i;
	SRxLOBData *pLOBData;
	STR_PDWDATA stPDWData;

	UINT uiByte, uiHeader, uiData;

	CFile theRawDataFile;

	__int64 file_size = 0;

	HANDLE h_file = CreateFile( m_strPathname, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL); 
	if( INVALID_HANDLE_VALUE != h_file ) { 
		
		// 파일의 크기를 얻는다. 4GBytes보다 큰 크기를 처리하기 위해서 이 함수는 64비트 
		// 크기로 파일 크기 정보를 제공한다. 이 함수의 반환 값은 64비트 중에서 하위 32비트 
		// 값이고 함수의 두 번째 매개변수로 전달되는 값이 상위 32비트 값이다. 
		DWORD temp_size = ::GetFileSize(h_file, (DWORD *)&file_size + 1); 
		// 그래서 반환된 temp_size 값을 file_size의 하위 32비트에 추가해야 한다. 
		file_size = file_size | temp_size; 
		// 파일을 닫는다. 
		CloseHandle(h_file);
	}


	uiHeader = stPDWData.GetHeader();

	if (theRawDataFile.Open( m_strPathname.GetBuffer(), CFile::shareDenyNone | CFile::typeBinary) == TRUE) {
		uiByte = theRawDataFile.Read( & stPDWData, uiHeader );

        // 장치 마다 PDW 개수를 이 변수에 저장해야 한다.
        //stPDWData.uiTotalPDW = stPDWData.x.el.uiCount;

		if( uiHeader + ( stPDWData.GetTotalPDW() * sizeof(_PDW) ) == file_size ) {
			uiByte = theRawDataFile.Read( stPDWData.stPDW, stPDWData.GetTotalPDW() * sizeof(_PDW) );
		}
		else {
			uiData = sizeof(STR_PDWDATA) - sizeof(stPDWData.stPDW);
			for( i=0 ; i < stPDWData.GetTotalPDW() ; ++i ) {
				uiByte = theRawDataFile.Read( & stPDWData.stPDW[i], sizeof(_PDW)-sizeof(float)*4 );
			}
		}

		// 분석 프로그램 호출시 아래 함수를 콜하면 됩니다.
		if( stPDWData.x.el.aucTaskID[0] == NULL ) {
			strcpy_s( (char *) stPDWData.x.el.aucTaskID, sizeof(stPDWData.x.el.aucTaskID), "RADARDIRAPP" );		// pEPDW->m_aucTaskID );
		}

		// 시작시 한번만 호출하면 됩니다.
		//RadarDirAlgotirhm::RadarDirAlgotirhm::Init();

		printf( "\n EPDW 경로명 : %s" , m_strPathname.GetBuffer() );
		//RadarDirAlgotirhm::RadarDirAlgotirhm::Log( enNormal, "EPDW 경로명 : %s" , m_strPathname.GetBuffer() );

		CRADARDIRAPPView *pView;
		CMainFrame *pMainFrame;

        //RadarDirAlgotirhm::RadarDirAlgotirhm::LoadCEDLibrary();
		RadarDirAlgotirhm::RadarDirAlgotirhm::Start( & stPDWData );
        

		int nCoLOB=RadarDirAlgotirhm::RadarDirAlgotirhm::GetCoLOB();

		pLOBData=RadarDirAlgotirhm::RadarDirAlgotirhm::GetLOBData();

		pMainFrame = (CMainFrame *) AfxGetApp()->m_pMainWnd;
		pView = (CRADARDIRAPPView *) pMainFrame->GetActiveView();

		pView->UpdateLOBData( nCoLOB, pLOBData );

		printf( "\n 분석된 LOB 개수 : %d", nCoLOB );

		// 프로그램 종료시 한번만 호출하면 됩니다.
		//RadarDirAlgotirhm::RadarDirAlgotirhm::Close();
	}

}
