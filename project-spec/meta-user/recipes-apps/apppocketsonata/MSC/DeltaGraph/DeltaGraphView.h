
// DeltaGraphView.h : CDeltaGraphView 클래스의 인터페이스
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

protected: // serialization에서만 만들어집니다.
	CDeltaGraphView();
	DECLARE_DYNCREATE(CDeltaGraphView)

public:
	enum{ IDD = IDD_DELTAGRAPH_FORM };

// 특성입니다.
public:
	CDeltaGraphDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
public:
	virtual ~CDeltaGraphView();
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
	CCBSpeedListCtrl m_CListRawData;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButtonPrevious();
	afx_msg void OnBnClickedButtonNext();
	CNumSpinCtrl m_CSpinPage;
	afx_msg void OnLvnGetdispinfoListPdw(NMHDR *pNMHDR, LRESULT *pResult);
};

#ifndef _DEBUG  // DeltaGraphView.cpp의 디버그 버전
inline CDeltaGraphDoc* CDeltaGraphView::GetDocument() const
   { return reinterpret_cast<CDeltaGraphDoc*>(m_pDocument); }
#endif

