
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
    m_uiPDWID = 1;

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
		CRADARDIRAPPView *pView;
        //CRADARDIRAPPView * pView;

        RadarDirAlgotirhm::RadarDirAlgotirhm::Init( pMainFrame->GetOutputWnd()->GetSafeHwnd(), true );

        RadarDirAlgotirhm::RadarDirAlgotirhm::LoadCEDLibrary();

	    // TODO: 여기에 로딩 코드를 추가합니다.
		if (true == ReadDataFile((char*)(LPCTSTR)ar.m_strFileName, (char*)(LPCTSTR)ar.m_strFileName)) {
			pstPDWData = (STR_PDWDATA *)m_theDataFile.GetData();

			pstPDWData->SetPDWID(m_uiPDWID++);

			RadarDirAlgotirhm::RadarDirAlgotirhm::Start(pstPDWData);

			int nCoLOB = RadarDirAlgotirhm::RadarDirAlgotirhm::GetCoLOB();

			pLOBData = RadarDirAlgotirhm::RadarDirAlgotirhm::GetLOBData();

			//pView = (CRADARDIRAPPView *)pMainFrame->GetActiveView();

			//pView->UpdateLOBData(nCoLOB, pLOBData);

		}
		else {
			AfxMessageBox(_T("분석하지 못할 파일 포멧 입니다."));
		}

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

bool CRADARDIRAPPDoc::OpenFile( CString &strPathname, CString &strFilename )
{
	//CString strMainTitle;    

	//m_pMainFrame=(CMainFrame *) AfxGetApp()->m_pMainWnd;

	m_strPathname = strPathname;

	SRxLOBData *pLOBData;
	STR_PDWDATA *pstPDWData;

	CRADARDIRAPPView *pView;
	CMainFrame *pMainFrame;

	if (true == ReadDataFile((char*)(LPCTSTR) m_strPathname, (char*)(LPCTSTR)strFilename)) {
		pstPDWData = m_theDataFile.GetPDWData();

		RadarDirAlgotirhm::RadarDirAlgotirhm::Start(pstPDWData, true);

		int nCoLOB = RadarDirAlgotirhm::RadarDirAlgotirhm::GetCoLOB();

		pLOBData = RadarDirAlgotirhm::RadarDirAlgotirhm::GetLOBData();

		pMainFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;
		pView = (CRADARDIRAPPView *)pMainFrame->GetActiveView();

		pView->UpdateLOBData(nCoLOB, pLOBData);

		//TRACE( "\n 분석된 LOB 개수 : %d", nCoLOB );

		// 프로그램 종료시 한번만 호출하면 됩니다.
		//RadarDirAlgotirhm::RadarDirAlgotirhm::Close();
	}
	else {
		AfxMessageBox(_T("분석하지 못할 파일 포멧 입니다."));
	}

	//strMainTitle.Format( "%s" , m_strPathname );
	//m_pMainFrame->SetWindowText( strMainTitle );

	return true;
}

/**
 * @brief     ReadDataFile
 * @param     char * pStrFileName
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-01-20 11:07:19
 * @warning
 */
bool CRADARDIRAPPDoc::ReadDataFile( char *pStrPathName, char *pStrFileName )
{
	bool bRet=true;
	STR_PDWDATA *pstPDWData;

	ENUM_DataType enDataType = CCommonUtils::WhatDataType(pStrPathName);

	if (enDataType == en_PDW_DATA) {
		m_theDataFile.ReadDataFile(pStrPathName, NULL, enPDWToPDW);

		pstPDWData = m_theDataFile.GetPDWData();

	}
	else if (enDataType == en_PDW_DATA_CSV) {
		m_theDataFile.ReadDataFile(pStrPathName, NULL, enCSVToPDW);

		// CSV 에는 과제명이 없기 떄문에 파일명으로 설정함.
		pstPDWData = m_theDataFile.GetPDWData();
		pstPDWData->SetTaskID(pStrFileName);
	}
	else {
		bRet = false;
	}

	if (bRet == true) {
		//pstPDWData->SetPDWID(m_uiPDWID++);
		pstPDWData->SetPDWID(0);
		
	}

	return bRet;

}