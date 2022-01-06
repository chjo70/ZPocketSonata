
// RADARANLAPPView.cpp : CRADARANLAPPView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CRADARANLAPPView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CRADARANLAPPView 생성/소멸

CRADARANLAPPView::CRADARANLAPPView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	//InitView();
	AllocMemory();

}

CRADARANLAPPView::~CRADARANLAPPView()
{
	FreeMemory();
}

BOOL CRADARANLAPPView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CRADARANLAPPView 그리기

void CRADARANLAPPView::OnDraw(CDC* /*pDC*/)
{
	CRADARANLAPPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CRADARANLAPPView 인쇄


void CRADARANLAPPView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CRADARANLAPPView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CRADARANLAPPView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CRADARANLAPPView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
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


// CRADARANLAPPView 진단

#ifdef _DEBUG
void CRADARANLAPPView::AssertValid() const
{
	CView::AssertValid();
}

void CRADARANLAPPView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRADARANLAPPDoc* CRADARANLAPPView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRADARANLAPPDoc)));
	return (CRADARANLAPPDoc*)m_pDocument;
}
#endif //_DEBUG


// CRADARANLAPPView 메시지 처리기

#define _TEXT_WIDTH			(16)

void CRADARANLAPPView::InitView()
{
	//int i;
	//int nCoField;
	CRect rtChildWindow;

	// int nCoLOBABTData;

// 	char szTable[CHILD_WINDOWS][10] = { "LOBDATA", "ABTDATA" } ;
// 	char szWindowTitel[CHILD_WINDOWS][30] = { "LOB 테이블 목록창", "ABT 테이블 목록창" } ;
// 
// 	AllocMemory();
// 
// 	// 목록창 전시
// 	GetClientRect( rtChildWindow );
// 	m_pListCrtrl->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT, rtChildWindow, this, 100 );
// 
//  	strcpy_s( m_pszField[0], MAX_OF_COLUMN_LENGTH, "순서" );
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

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_pDoc = ( CRADARANLAPPDoc * ) GetDocument();

	CRect rcMainClientRect;				// 사각형 생성
	GetClientRect(&rcMainClientRect);	// 현재 클라이언트 영역 할당

	CCreateContext cc;

	// 새로운 폼뷰 초기화- edit formview
	if( g_iView == 0 ) {
		CView* pViewTemp = (CView*)RUNTIME_CLASS(CLOBTableView)->CreateObject();
		::ZeroMemory(&cc, sizeof(cc));
		//rcMainClientRect.right = 470;
		pViewTemp->Create(NULL, NULL, WS_CHILD, rcMainClientRect, this, IDD_LOBTABLEVIEW, &cc);	// 윈도우 생성
		pViewTemp->OnInitialUpdate();																// 화면 재생성
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