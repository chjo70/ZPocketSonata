
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
        STR_PDWDATA *pstPDWData;
        SRxLOBData *pLOBData;

        CMainFrame *pMainFrame=( CMainFrame * ) AfxGetMainWnd();
        CRADARDIRAPPView * pView;

        RadarDirAlgotirhm::RadarDirAlgotirhm::Init( pMainFrame->GetOutputWnd()->GetSafeHwnd(), true );

        RadarDirAlgotirhm::RadarDirAlgotirhm::LoadCEDLibrary();

	    // TODO: 여기에 로딩 코드를 추가합니다.
        m_theDataFile.ReadDataFile( (char*)(LPCTSTR) ar.m_strFileName, NULL, enPDWToPDW );

        pstPDWData = ( STR_PDWDATA * ) m_theDataFile.GetData();
        RadarDirAlgotirhm::RadarDirAlgotirhm::Start( pstPDWData );        

        int nCoLOB=RadarDirAlgotirhm::RadarDirAlgotirhm::GetCoLOB();

        pLOBData=RadarDirAlgotirhm::RadarDirAlgotirhm::GetLOBData();

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

    ReadDataFile();

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
	SRxLOBData *pLOBData;
	STR_PDWDATA *pstPDWData;

	CRADARDIRAPPView *pView;
	CMainFrame *pMainFrame;

    m_theDataFile.ReadDataFile( (char*)(LPCTSTR) m_strPathname, NULL, enPDWToPDW );
    pstPDWData = m_theDataFile.GetPDWData();

	RadarDirAlgotirhm::RadarDirAlgotirhm::Start( pstPDWData );        

	int nCoLOB=RadarDirAlgotirhm::RadarDirAlgotirhm::GetCoLOB();

	pLOBData=RadarDirAlgotirhm::RadarDirAlgotirhm::GetLOBData();

	pMainFrame = (CMainFrame *) AfxGetApp()->m_pMainWnd;
	pView = (CRADARDIRAPPView *) pMainFrame->GetActiveView();

	pView->UpdateLOBData( nCoLOB, pLOBData );

	printf( "\n 분석된 LOB 개수 : %d", nCoLOB );

	// 프로그램 종료시 한번만 호출하면 됩니다.
	//RadarDirAlgotirhm::RadarDirAlgotirhm::Close();

}
