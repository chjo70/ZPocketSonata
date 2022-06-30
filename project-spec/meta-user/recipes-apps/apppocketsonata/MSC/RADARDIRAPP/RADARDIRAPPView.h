
// RADARDIRAPPView.h : CRADARDIRAPPView 클래스의 인터페이스
//

#pragma once

#include "resource.h"

//#include "../RadarDIR/RadarDirAlgorithm.h"


class CRADARDIRAPPView : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CRADARDIRAPPView();
	DECLARE_DYNCREATE(CRADARDIRAPPView)

public:
	enum{ IDD = IDD_RADARDIRAPP_FORM };

private:

// 특성입니다.
public:
	CRADARDIRAPPDoc* GetDocument() const;

// 작업입니다.
public:
	

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
private:
//	UINT m_CoListItems;

public:
	void InitView();

public:
	virtual ~CRADARDIRAPPView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
public:
	void UpdateLOBData( int nCoLOB, SRxLOBData *pLOB );

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	int m_CoListItems;

	unsigned int m_uiTotalLOB;

	CListCtrl m_CListLOB;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // RADARDIRAPPView.cpp의 디버그 버전
inline CRADARDIRAPPDoc* CRADARDIRAPPView::GetDocument() const
   { return reinterpret_cast<CRADARDIRAPPDoc*>(m_pDocument); }
#endif

