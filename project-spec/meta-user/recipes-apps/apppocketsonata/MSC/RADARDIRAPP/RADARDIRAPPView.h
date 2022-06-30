
// RADARDIRAPPView.h : CRADARDIRAPPView Ŭ������ �������̽�
//

#pragma once

#include "resource.h"

//#include "../RadarDIR/RadarDirAlgorithm.h"


class CRADARDIRAPPView : public CFormView
{
protected: // serialization������ ��������ϴ�.
	CRADARDIRAPPView();
	DECLARE_DYNCREATE(CRADARDIRAPPView)

public:
	enum{ IDD = IDD_RADARDIRAPP_FORM };

private:

// Ư���Դϴ�.
public:
	CRADARDIRAPPDoc* GetDocument() const;

// �۾��Դϴ�.
public:
	

// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.

// �����Դϴ�.
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

// ������ �޽��� �� �Լ�
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

#ifndef _DEBUG  // RADARDIRAPPView.cpp�� ����� ����
inline CRADARDIRAPPDoc* CRADARDIRAPPView::GetDocument() const
   { return reinterpret_cast<CRADARDIRAPPDoc*>(m_pDocument); }
#endif

