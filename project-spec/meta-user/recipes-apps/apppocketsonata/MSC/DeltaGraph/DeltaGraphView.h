
// DeltaGraphView.h : CDeltaGraphView Ŭ������ �������̽�
//

#pragma once

#include "resource.h"
#include "afxcmn.h"

#include "../ShuDeltaGraph/ListCtrl/ReportCtrl.h"
#include "../ShuDeltaGraph/ListCtrl/CBSpeedListCtrl.h"

#include "../ShuDeltaGraph/EasySize/EasySize.h"

#include "../ShuDeltaGraph/SpinCtrl/NumSpinCtrl.h"

#include "Show.h"



class CDeltaGraphView : public CFormView, public CShow
{
	DECLARE_EASYSIZE;
private:
	CString m_strPathName;

	CDeltaGraphDoc *m_pDoc;

public:

private:
	void InitListCtrl( bool bInit=true );
	void InitButton();
	void InitSpinCtrl();

public:
	void ShowGraph( ENUM_SUB_GRAPH enSubGraph=enUnselectedSubGraph, int iFileIndex=0 );

public:
	inline void SetWindowTitle( CString strWindowTitle ) { m_strPathName=strWindowTitle; }

protected: // serialization������ ��������ϴ�.
	CDeltaGraphView();
	DECLARE_DYNCREATE(CDeltaGraphView)

public:
	enum{ IDD = IDD_DELTAGRAPH_FORM };

// Ư���Դϴ�.
public:
	CDeltaGraphDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.

// �����Դϴ�.
public:
	virtual ~CDeltaGraphView();
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
	CCBSpeedListCtrl m_CListRawData;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButtonPrevious();
	afx_msg void OnBnClickedButtonNext();
	CNumSpinCtrl m_CSpinPage;
	afx_msg void OnLvnGetdispinfoListPdw(NMHDR *pNMHDR, LRESULT *pResult);
};

#ifndef _DEBUG  // DeltaGraphView.cpp�� ����� ����
inline CDeltaGraphDoc* CDeltaGraphView::GetDocument() const
   { return reinterpret_cast<CDeltaGraphDoc*>(m_pDocument); }
#endif

