
// RADARDIRAPPDoc.cpp : CRADARDIRAPPDoc Ŭ������ ����
//

#include "stdafx.h"


// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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


// CRADARDIRAPPDoc ����/�Ҹ�

CRADARDIRAPPDoc::CRADARDIRAPPDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.
    m_uiPDWID = 1;

}

CRADARDIRAPPDoc::~CRADARDIRAPPDoc()
{
}

BOOL CRADARDIRAPPDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CRADARDIRAPPDoc serialization

void CRADARDIRAPPDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
        
	}
	else {
        STR_PDWDATA *pstPDWData;
        SRxLOBData *pLOBData;

        CMainFrame *pMainFrame=( CMainFrame * ) AfxGetMainWnd();
		CRADARDIRAPPView *pView;
        //CRADARDIRAPPView * pView;

        RadarDirAlgotirhm::RadarDirAlgotirhm::Init( pMainFrame->GetOutputWnd()->GetSafeHwnd(), true );

        RadarDirAlgotirhm::RadarDirAlgotirhm::LoadCEDLibrary();

	    // TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
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
			AfxMessageBox(_T("�м����� ���� ���� ���� �Դϴ�."));
		}

	}
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void CRADARDIRAPPDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
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

// �˻� ó���⸦ �����մϴ�.
void CRADARDIRAPPDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
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

// CRADARDIRAPPDoc ����

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


// CRADARDIRAPPDoc ���

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

		//TRACE( "\n �м��� LOB ���� : %d", nCoLOB );

		// ���α׷� ����� �ѹ��� ȣ���ϸ� �˴ϴ�.
		//RadarDirAlgotirhm::RadarDirAlgotirhm::Close();
	}
	else {
		AfxMessageBox(_T("�м����� ���� ���� ���� �Դϴ�."));
	}

	//strMainTitle.Format( "%s" , m_strPathname );
	//m_pMainFrame->SetWindowText( strMainTitle );

	return true;
}

/**
 * @brief     ReadDataFile
 * @param     char * pStrFileName
 * @return    bool
 * @exception ���ܻ����� �Է����ְų� '�ش���� ����' ���� ���ּ���.
 * @author    ��ö�� (churlhee.jo@lignex1.com)
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

		// CSV ���� �������� ���� ������ ���ϸ����� ������.
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