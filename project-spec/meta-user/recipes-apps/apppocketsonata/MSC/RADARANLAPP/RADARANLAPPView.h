
// RADARANLAPPView.h : CRADARANLAPPView Ŭ������ �������̽�
//

#pragma once

#include "LOBTableView.h"


class CRADARANLAPPView : public CView
{
protected: // serialization������ ��������ϴ�.
	CRADARANLAPPView();
	DECLARE_DYNCREATE(CRADARANLAPPView)

// Ư���Դϴ�.
public:
	CRADARANLAPPDoc* GetDocument() const;

// �۾��Դϴ�.
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

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CRADARANLAPPView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // RADARANLAPPView.cpp�� ����� ����
inline CRADARANLAPPDoc* CRADARANLAPPView::GetDocument() const
   { return reinterpret_cast<CRADARANLAPPDoc*>(m_pDocument); }
#endif

