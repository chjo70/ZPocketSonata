
// RADARDIRAPPDoc.cpp : CRADARDIRAPPDoc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "RADARDIRAPP.h"
#endif

#include "MainFrm.h"

#include "../RadarDIR/RadarDirAlgorithm.h"


#include "RADARDIRAPPDoc.h"
#include "RADARDIRAPPView.h"



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
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
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
	// 
	// 	// ������ �б�
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
	// 	// Ÿ��Ʋ �� ����
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
	unsigned int i;
	SRxLOBData *pLOBData;
	STR_PDWDATA stPDWData;

	UINT uiByte, uiHeader, uiData;

	CFile theRawDataFile;

	__int64 file_size = 0; 

	HANDLE h_file = CreateFile( m_strPathname, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL); 
	if( INVALID_HANDLE_VALUE != h_file ) { 
		
		// ������ ũ�⸦ ��´�. 4GBytes���� ū ũ�⸦ ó���ϱ� ���ؼ� �� �Լ��� 64��Ʈ 
		// ũ��� ���� ũ�� ������ �����Ѵ�. �� �Լ��� ��ȯ ���� 64��Ʈ �߿��� ���� 32��Ʈ 
		// ���̰� �Լ��� �� ��° �Ű������� ���޵Ǵ� ���� ���� 32��Ʈ ���̴�. 
		DWORD temp_size = ::GetFileSize(h_file, (DWORD *)&file_size + 1); 
		// �׷��� ��ȯ�� temp_size ���� file_size�� ���� 32��Ʈ�� �߰��ؾ� �Ѵ�. 
		file_size = file_size | temp_size; 
		// ������ �ݴ´�. 
		CloseHandle(h_file);
	}

	uiHeader = sizeof(STR_ELINT_HEADER); //; // - sizeof(stPDWData.stPDW);

	if (theRawDataFile.Open( m_strPathname.GetBuffer(), CFile::shareDenyNone | CFile::typeBinary) == TRUE) {
		uiByte = theRawDataFile.Read( & stPDWData, uiHeader );

        // ��ġ ���� PDW ������ �� ������ �����ؾ� �Ѵ�.
        //stPDWData.uiTotalPDW = stPDWData.x.el.uiCount;

		if( uiHeader + ( stPDWData.uiTotalPDW * sizeof(_PDW) ) == file_size ) {
			uiByte = theRawDataFile.Read( stPDWData.stPDW, stPDWData.uiTotalPDW * sizeof(_PDW) );
		}
		else {
			uiData = sizeof(STR_PDWDATA) - sizeof(stPDWData.stPDW);
			for( i=0 ; i < stPDWData.uiTotalPDW ; ++i ) {
				uiByte = theRawDataFile.Read( & stPDWData.stPDW[i], sizeof(_PDW)-sizeof(float)*4 );
			}
		}

		// �м� ���α׷� ȣ��� �Ʒ� �Լ��� ���ϸ� �˴ϴ�.
		if( stPDWData.x.el.aucTaskID[0] == NULL ) {
			strcpy_s( (char *) stPDWData.x.el.aucTaskID, sizeof(stPDWData.x.el.aucTaskID), "RADARDIRAPP" );		// pEPDW->m_aucTaskID );
		}

		// ���۽� �ѹ��� ȣ���ϸ� �˴ϴ�.
		//RadarDirAlgotirhm::RadarDirAlgotirhm::Init();

		printf( "\n EPDW ��θ� : %s" , m_strPathname.GetBuffer() );
		//RadarDirAlgotirhm::RadarDirAlgotirhm::Log( enNormal, "EPDW ��θ� : %s" , m_strPathname.GetBuffer() );

		CRADARDIRAPPView *pView;
		CMainFrame *pMainFrame;

        RadarDirAlgotirhm::RadarDirAlgotirhm::LoadCEDLibrary();
		RadarDirAlgotirhm::RadarDirAlgotirhm::Start( & stPDWData );
        

		int nCoLOB=RadarDirAlgotirhm::RadarDirAlgotirhm::GetCoLOB();

		pLOBData=RadarDirAlgotirhm::RadarDirAlgotirhm::GetLOBData();

		pMainFrame = (CMainFrame *) AfxGetApp()->m_pMainWnd;
		pView = (CRADARDIRAPPView *) pMainFrame->GetActiveView();

		pView->UpdateLOBData( nCoLOB, pLOBData );

		printf( "\n �м��� LOB ���� : %d", nCoLOB );

		// ���α׷� ����� �ѹ��� ȣ���ϸ� �˴ϴ�.
		//RadarDirAlgotirhm::RadarDirAlgotirhm::Close();
	}

}
