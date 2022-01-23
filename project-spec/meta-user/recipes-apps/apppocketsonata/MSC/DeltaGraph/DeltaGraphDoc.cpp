
// DeltaGraphDoc.cpp : CDeltaGraphDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "DeltaGraph.h"
#endif

#include "MainFrm.h"
#include "ChildFrm.h"

#include "DeltaGraphDoc.h"
#include "DeltaGraphView.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDeltaGraphDoc

IMPLEMENT_DYNCREATE(CDeltaGraphDoc, CDocument)

BEGIN_MESSAGE_MAP(CDeltaGraphDoc, CDocument)
END_MESSAGE_MAP()


// CDeltaGraphDoc 생성/소멸

CDeltaGraphDoc::CDeltaGraphDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	m_pFrame = ( CMainFrame * ) AfxGetMainWnd();

}

CDeltaGraphDoc::~CDeltaGraphDoc()
{
	theApp.CloseMapData( & m_strPathname );
	
}

BOOL CDeltaGraphDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CDeltaGraphDoc serialization

void CDeltaGraphDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
		m_strPathname = ar.m_strFileName;
		m_strPathname.MakeLower();

	}

	m_enUnitType = WhatUnitType();
	m_enDataType = WhatDataType();

}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CDeltaGraphDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CDeltaGraphDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CDeltaGraphDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
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

// CDeltaGraphDoc 진단

#ifdef _DEBUG
void CDeltaGraphDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDeltaGraphDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CDeltaGraphDoc 명령

/**
 * @brief     
 * @return    ENUM_UnitType
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/03/12 19:42:44
 * @warning   
 */
 ENUM_UnitType CDeltaGraphDoc::WhatUnitType()
{
	return m_theDataFile.WhatUnitType( (LPSTR)(LPCTSTR) m_strPathname );
}

/**
 * @brief     
 * @return    ENUM_DataType
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/03/12 19:42:42
 * @warning   
 */
ENUM_DataType CDeltaGraphDoc::WhatDataType()
{
	return m_theDataFile.WhatDataType( (LPSTR)(LPCTSTR) m_strPathname );
}

 /**
  * @brief		GetDataType
  * @return		ENUM_DataType
  * @author		조철희 (churlhee.jo@lignex1.com)
  * @version		0.0.1
  * @date		2021/01/04 20:12:39
  * @warning		
  */
ENUM_DataType CDeltaGraphDoc::GetDataType() 
{ 
    return m_enDataType; 
}

/**
 * @brief     
 * @param     CString & strPathname
 * @param     STR_FILTER_SETUP * pstFilterSetup
 * @return    bool
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/03/08 22:17:09
 * @warning   
 */
bool CDeltaGraphDoc::OpenFile( CString &strPathname, STR_FILTER_SETUP *pstFilterSetup )
{
	CString strMainTitle;
	map<CString, CData *>::iterator it;
	CChildFrame *pChild;
	//CDeltaGraphView *pView;

	pChild = ( CChildFrame * ) m_pFrame->GetActiveFrame();

	m_strPathname = strPathname;

// 	// 데이터 읽기
// 	it = m_gMapData.find( m_strPathname );
// 	if( it == m_gMapData.end() ) {
// 		ReadDataFile( 0, pstFilterSetup );
// 
// 	}
// 	else {
// 		m_theDataFile.SetData( it->second );
// 
// 	}

	// 타이틀 바 변경
	//strMainTitle.Format( _T("%s:%d") , m_strPathname, m_theDataFile.GetWindowNumber() );
	//pChild->SetWindowText( strMainTitle );

	//pView = (CDeltaGraphView *) pChild->GetActiveView();
	//pView->SetWindowTitle( m_strPathname );

	return true;
}

/**
 * @brief     
 * @param     STR_FILTER_SETUP * pstFilterSetup
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/03/08 22:36:03
 * @warning   
 */
bool CDeltaGraphDoc::ReadDataFile( DWORD dwOffset, STR_FILTER_SETUP *pstFilterSetup, bool bCountOfWindow )
{
	//bool bRet;
	CData *pData, *pFindMapData;
	
	pFindMapData = theApp.FindMapData( & m_strPathname );
	pData = m_theDataFile.ReadDataFile( (LPSTR) (LPCTSTR) m_strPathname, dwOffset, pFindMapData, pstFilterSetup );

	if( pFindMapData == NULL ) {
		theApp.AddMapData( & m_strPathname, pData );
	}
	else {
		if( bCountOfWindow == true ) {
			theApp.IncWindowNumber( pFindMapData );
		}
	}

	return m_theDataFile.GetFileIndex() == -1;

}

/**
 * @brief     
 * @return    UINT
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/03/11 22:19:09
 * @warning   
 */
UINT CDeltaGraphDoc::GetPDWDataItems()
{ 
	STR_PDW_DATA *pPDWData;

	pPDWData = ( STR_PDW_DATA * ) m_theDataFile.GetData();
	return pPDWData->iDataItems; 
}

