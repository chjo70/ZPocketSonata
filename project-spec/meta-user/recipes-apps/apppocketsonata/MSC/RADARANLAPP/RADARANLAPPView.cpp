
// RADARANLAPPView.cpp : CRADARANLAPPView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "RADARANLAPP.h"
#endif

#include "RADARANLAPPDoc.h"
#include "RADARANLAPPView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int CRADARANLAPPView::g_iView = 0;


// CRADARANLAPPView

IMPLEMENT_DYNCREATE(CRADARANLAPPView, CView)

BEGIN_MESSAGE_MAP(CRADARANLAPPView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CRADARANLAPPView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CRADARANLAPPView ����/�Ҹ�

CRADARANLAPPView::CRADARANLAPPView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	//InitView();
	AllocMemory();

}

CRADARANLAPPView::~CRADARANLAPPView()
{
	FreeMemory();
}

BOOL CRADARANLAPPView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CRADARANLAPPView �׸���

void CRADARANLAPPView::OnDraw(CDC* /*pDC*/)
{
	CRADARANLAPPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CRADARANLAPPView �μ�


void CRADARANLAPPView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CRADARANLAPPView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CRADARANLAPPView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CRADARANLAPPView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CRADARANLAPPView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CRADARANLAPPView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CRADARANLAPPView ����

#ifdef _DEBUG
void CRADARANLAPPView::AssertValid() const
{
	CView::AssertValid();
}

void CRADARANLAPPView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRADARANLAPPDoc* CRADARANLAPPView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRADARANLAPPDoc)));
	return (CRADARANLAPPDoc*)m_pDocument;
}
#endif //_DEBUG


// CRADARANLAPPView �޽��� ó����

#define _TEXT_WIDTH			(16)

void CRADARANLAPPView::InitView()
{
	//int i;
	//int nCoField;
	CRect rtChildWindow;

	// int nCoLOBABTData;

// 	char szTable[CHILD_WINDOWS][10] = { "LOBDATA", "ABTDATA" } ;
// 	char szWindowTitel[CHILD_WINDOWS][30] = { "LOB ���̺� ���â", "ABT ���̺� ���â" } ;
// 
// 	AllocMemory();
// 
// 	// ���â ����
// 	GetClientRect( rtChildWindow );
// 	m_pListCrtrl->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT, rtChildWindow, this, 100 );
// 
//  	strcpy_s( m_pszField[0], MAX_OF_COLUMN_LENGTH, "����" );
//  	m_pDoc->GetFieldNameOfTable( & nCoField, &m_pszField[1], szTable[g_iView] );
//  
//  	for( i=0 ; i <= nCoField ; ++i ) {
//  		m_pListCrtrl->InsertColumn( i, m_pszField[i], LVCFMT_LEFT, _TEXT_WIDTH*strlen(m_pszField[i]) );
//  	}
// 
// 	SetWindowText( szWindowTitel[g_iView] );
// 
// 	//m_pDoc->GetFieldValueOfTable( & nCoRow, m_pszValue, nCoField, & m_pszField[1], szTable[g_iView] );
// 
// 	++ g_iView;

}

void CRADARANLAPPView::AllocMemory()
{
	int i;

	m_pListCrtrl = new CListCtrl;
	
	m_pszField = ( char ** ) malloc( sizeof(char *) * MAX_COUNT_OF_FIELD );
	for( i=0 ; i < MAX_COUNT_OF_FIELD ; ++i ) {
		m_pszField[i] = ( char * ) malloc( sizeof(char) * MAX_OF_COLUMN_LENGTH );
	}

// 	m_pszValue = ( char ** ) malloc( sizeof(char *) * MAX_COUNT_OF_FIELD );
// 	for( i=0 ; i < MAX_COUNT_OF_FIELD ; ++i ) {
// 		m_pszValue[i] = ( char * ) malloc( sizeof(char) * MAX_OF_COLUMN_LENGTH );
// 		memset( m_pszValue[i], 0, MAX_OF_COLUMN_LENGTH );
// 	}

}

void CRADARANLAPPView::FreeMemory()
{
	int i;

	delete m_pListCrtrl;

	for( i=0 ; i < MAX_COUNT_OF_FIELD ; ++i ) {
		free( m_pszField[i] );
	}
	free( m_pszField );
}

void CRADARANLAPPView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_pDoc = ( CRADARANLAPPDoc * ) GetDocument();

	CRect rcMainClientRect;				// �簢�� ����
	GetClientRect(&rcMainClientRect);	// ���� Ŭ���̾�Ʈ ���� �Ҵ�

	CCreateContext cc;

	// ���ο� ���� �ʱ�ȭ- edit formview
	if( g_iView == 0 ) {
		CView* pViewTemp = (CView*)RUNTIME_CLASS(CLOBTableView)->CreateObject();
		::ZeroMemory(&cc, sizeof(cc));
		//rcMainClientRect.right = 470;
		pViewTemp->Create(NULL, NULL, WS_CHILD, rcMainClientRect, this, IDD_LOBTABLEVIEW, &cc);	// ������ ����
		pViewTemp->OnInitialUpdate();																// ȭ�� �����
		m_pLOBTableView = (CLOBTableView*) pViewTemp;

		m_pLOBTableView->ShowWindow( SW_SHOW );
	}
	else if( g_iView == 1 ) {

	}
	else {

	}

	++ g_iView;

}

void CRADARANLAPPView::OnFileOpen()
{
	m_pDoc->OnFileOpen();
}