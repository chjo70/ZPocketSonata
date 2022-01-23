
// DeltaGraphView.h : CDeltaGraphView 클래스의 인터페이스
//

#pragma once

#include "resource.h"

#include "Show.h"
#include "afxwin.h"

#include "EasySize/EasySize.h"

#include "Pegrpapi.h"

#include "XColorStatic/XColorStatic.h"
#include "ToolTip/XInfoTip.h"

#include <vector>


class CDeltaGraphView2 : public CFormView, public CShow
{
DECLARE_EASYSIZE;

private:
	CString m_strPathName;

	HWND m_hPE;			// the proessentials control object

	CDeltaGraphDoc *m_pDoc;

	CChildFrame *m_pChild;

	bool m_bX;
	float m_fX1;
	float m_fX2;

	CXInfoTip *m_pTip;
	HICON m_hToolTipIcon;

	STR_FILTER_SETUP m_strFilterSetup;

	vector<STR_ZOOM_INFO> m_VecZoomInfo;

	ENUM_SUB_GRAPH m_enSubGraph;

public:

private:
	void InitVar();
	void InitStatic();
	void InitGraph( ENUM_SUB_GRAPH enSubGraph=enUnselectedSubGraph );
	void InitCombo();
	void InitButton();
	void InitToolTip();
	void FreeBuffer();

	void SetCombo( ENUM_SUB_GRAPH enSubGraph );
	void CloseGraph();
	void DrawGraph( ENUM_SUB_GRAPH enSubGraph );
	void ClearGraph();
	void SetData( HOTSPOTDATA *pHSD );
	float SetXUnit( float fValue, ENUM_DataType enDataType );

	void UpdateToolTip( TCHAR *pszBuffer, CWnd *pDlgItem );
	void UpdateFilterToolTip();
	void ClearFilterSetup( STR_FILTER_SETUP *pstrFilterSetup=NULL );
	void ClearZoomInfo();

	void AddZoomInfo();

	void SetGraphPointsize();
	void UpdateZoomButton();

	void GetFilterSetup( STR_FILTER_SETUP *pstrFilterSetup, ENUM_SUB_GRAPH enSubGraph, ENUM_DataType enDataType );

public:
	void ShowGraph( ENUM_SUB_GRAPH enSubGraph=enUnselectedSubGraph, int iFileIndex=0 );

	inline void SetWindowTitle( CString strWindowTitle ) { m_strPathName=strWindowTitle; }

protected: // serialization에서만 만들어집니다.
	CDeltaGraphView2();
	DECLARE_DYNCREATE(CDeltaGraphView2)

public:
	enum{ IDD = IDD_DELTAGRAPH_FORM2 };

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
	virtual ~CDeltaGraphView2();
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
	CStatic m_CStaticGraph;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CComboBox m_CComboYAxis;
	afx_msg void OnCbnSelchangeComboYaxis();
	CComboBox m_CComboLineType;
	afx_msg void OnCbnSelchangeComboLinetype();
	afx_msg void OnBnClickedButtonFilterApply();
	afx_msg void OnBnClickedButtonFilterDeapply();
	CStatic m_CStaticDataItems;
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	CComboBox m_CComboPointSize;
	afx_msg void OnCbnSelchangeComboPointsize();
	CXColorStatic m_CStaticX1;
	CXColorStatic m_CStaticX2;
	CXColorStatic m_CStaticDTOA;
	CXColorStatic m_CStaticX1Unit;
	CXColorStatic m_CStaticX2Unit;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonFilterZoomout();
	afx_msg void OnBnClickedButtonRunSigAnal();
	CComboBox m_CComboDV;
	afx_msg void OnCbnSelchangeComboDv();
};

#ifndef _DEBUG  // DeltaGraphView.cpp의 디버그 버전
inline CDeltaGraphDoc* CDeltaGraphView2::GetDocument() const
   { return reinterpret_cast<CDeltaGraphDoc*>(m_pDocument); }
#endif

