
// RADARANLAPPView.h : CRADARANLAPPView 클래스의 인터페이스
//

#pragma once

#include "LOBTableView.h"


class CRADARANLAPPView : public CView
{
protected: // serialization에서만 만들어집니다.
	CRADARANLAPPView();
	DECLARE_DYNCREATE(CRADARANLAPPView)

// 특성입니다.
public:
	CRADARANLAPPDoc* GetDocument() const;

// 작업입니다.
public:
	void InitView();
	void AllocMemory();
	void FreeMemory();

	void OnFileOpen();

private:
	static int g_iView;

	CLOBTableView *m_pLOBTableView;

	CListCtrl *m_pListCrtrl;
	CRADARANLAPPDoc *m_pDoc;
	char **m_pszField;
	char **m_pszValue;

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CRADARANLAPPView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // RADARANLAPPView.cpp의 디버그 버전
inline CRADARANLAPPDoc* CRADARANLAPPView::GetDocument() const
   { return reinterpret_cast<CRADARANLAPPDoc*>(m_pDocument); }
#endif

