
// RADARDIRAPPView.cpp : CRADARDIRAPPView Ŭ������ ����
//

#include "stdafx.h"

#define _MAIN_
#define _MAIN_GLOBALS_


// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "RADARDIRAPP.h"
#endif



#include "../../files/Anal/OFP_Main.h"
#include "../RadarDIR/RadarDirAlgorithm.h"

#include "RADARDIRAPPDoc.h"
#include "RADARDIRAPPView.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRADARDIRAPPView

IMPLEMENT_DYNCREATE(CRADARDIRAPPView, CFormView)

BEGIN_MESSAGE_MAP(CRADARDIRAPPView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CRADARDIRAPPView ����/�Ҹ�

CRADARDIRAPPView::CRADARDIRAPPView()
	: CFormView(CRADARDIRAPPView::IDD)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

	m_CoListItems = 0;

}

CRADARDIRAPPView::~CRADARDIRAPPView()
{
}

void CRADARDIRAPPView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LOB, m_CListLOB);
	DDX_Control(pDX, IDC_LIST_LOB, m_CListLOB);
}

BOOL CRADARDIRAPPView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CFormView::PreCreateWindow(cs);
}

void CRADARDIRAPPView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	InitView();
}

void CRADARDIRAPPView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CRADARDIRAPPView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CRADARDIRAPPView ����

#ifdef _DEBUG
void CRADARDIRAPPView::AssertValid() const
{
	CFormView::AssertValid();
}

void CRADARDIRAPPView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CRADARDIRAPPDoc* CRADARDIRAPPView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRADARDIRAPPDoc)));
	return (CRADARDIRAPPDoc*)m_pDocument;
}
#endif //_DEBUG


// CRADARDIRAPPView �޽��� ó����

#define _TEXT_WIDTH								(10)
#define	_COLUMNS_OF_LIST_					(9)
static char szList[_COLUMNS_OF_LIST_][20] = { "����", "����[��]", "��ȣ����", "����", "���ļ�[MHz]", "P��", "PRI[us]", "��ȣ����[dBm]", "�޽���[ns]" } ;
void CRADARDIRAPPView::InitView()
{
 	int i;
// 	CRect rtChildWindow;
// 	GetClientRect( rtChildWindow );
// 
// 
// 	m_CListLOB..Create( WS_VISIBLE | WS_BORDER | LVS_REPORT, rtChildWindow, this, 100 );
// 
 	for( i=0 ; i < _COLUMNS_OF_LIST_ ; ++i ) {
 		m_CListLOB.InsertColumn( i, szList[i], LVCFMT_LEFT, _TEXT_WIDTH*strlen(szList[i]) );
 	}
 
 	m_CoListItems = 0;

}

/**
 * @brief     UpdateLOBData
 * @param     int nCoLOB
 * @param     SRxLOBData * pLOB
 * @return    void
 * @exception
 * @author    ��ö�� (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-03-14, 22:17
 * @warning
 */
void CRADARDIRAPPView::UpdateLOBData( int nCoLOB, SRxLOBData *pLOB )
{
	int i, j;
	char buffer[100];


	for( i=0 ; i < nCoLOB ; ++i ) {
		sprintf_s( buffer, sizeof(buffer), "%d" , m_CoListItems );
		m_CListLOB.InsertItem( m_CoListItems, buffer );

		j = 1;
		sprintf_s( buffer, sizeof(buffer), " %4.1f(%4.1f,%4.1f)" , pLOB->fDOAMean, pLOB->fDOAMin, pLOB->fDOAMax );
		m_CListLOB.SetItemText( m_CoListItems, j++, buffer );

		sprintf_s( buffer, sizeof(buffer), "%s" , g_szAetSignalType[pLOB->iSignalType] );
		m_CListLOB.SetItemText( m_CoListItems, j++, buffer );

		sprintf_s( buffer, sizeof(buffer), "%s" , g_szAetFreqType[pLOB->iFreqType] );
		m_CListLOB.SetItemText( m_CoListItems, j++, buffer );

		sprintf_s( buffer, sizeof(buffer), " %.3f[%.3f, %.3f]" , pLOB->fFreqMean, pLOB->fFreqMin, pLOB->fFreqMax );
		m_CListLOB.SetItemText( m_CoListItems, j++, buffer );

		sprintf_s( buffer, sizeof(buffer), " %s    " , g_szAetPriType[pLOB->iPRIType] );
		m_CListLOB.SetItemText( m_CoListItems, j++, buffer );

		sprintf_s( buffer, sizeof(buffer), "%0.1f(%.1f,%.1f), %2d" , pLOB->fPRIMean, pLOB->fPRIMin, pLOB->fPRIMax, pLOB->iPRIPositionCount );
		m_CListLOB.SetItemText( m_CoListItems, j++, buffer );

		sprintf_s( buffer, sizeof(buffer), " %.2f(%.2f,%.2f)" , pLOB->fPAMean, pLOB->fPAMin, pLOB->fPAMax );
		m_CListLOB.SetItemText( m_CoListItems, j++, buffer );

		sprintf_s( buffer, sizeof(buffer), " %.2f(%.2f,%.2f)" , pLOB->fPWMean, pLOB->fPWMin, pLOB->fPWMax );
		m_CListLOB.SetItemText( m_CoListItems, j++, buffer );


		++ pLOB;

		++ m_CoListItems;

	}

	m_CListLOB.InsertItem( m_CoListItems, "" );
	++ m_CoListItems;

	Invalidate();

}


/**
 * @brief     OnCreate
 * @param     LPCREATESTRUCT lpCreateStruct
 * @return    int
 * @exception
 * @author    ��ö�� (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-03-14, 22:17
 * @warning
 */
int CRADARDIRAPPView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.

	return 0;
}
