
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
        CRADARDIRAPPView * pView;

        RadarDirAlgotirhm::RadarDirAlgotirhm::Init( pMainFrame->GetOutputWnd()->GetSafeHwnd(), true );

        RadarDirAlgotirhm::RadarDirAlgotirhm::LoadCEDLibrary();

	    // TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
        m_theDataFile.ReadDataFile( (char*)(LPCTSTR) ar.m_strFileName, NULL, enPDWToPDW );

        pstPDWData = ( STR_PDWDATA * ) m_theDataFile.GetData();
        RadarDirAlgotirhm::RadarDirAlgotirhm::Start( pstPDWData );        

        int nCoLOB=RadarDirAlgotirhm::RadarDirAlgotirhm::GetCoLOB();

        pLOBData=RadarDirAlgotirhm::RadarDirAlgotirhm::GetLOBData();

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
 * @author    ��ö�� (churlhee.jo@lignex1.com)
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

	printf( "\n �м��� LOB ���� : %d", nCoLOB );

	// ���α׷� ����� �ѹ��� ȣ���ϸ� �˴ϴ�.
	//RadarDirAlgotirhm::RadarDirAlgotirhm::Close();

}
