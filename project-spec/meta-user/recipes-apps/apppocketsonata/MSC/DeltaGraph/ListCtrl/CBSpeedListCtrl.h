#if !defined(AFX_CBSPEEDLISTCTRL_H__E191A160_D10D_4C06_A08B_2A904A50CC73__INCLUDED_)
#define AFX_CBSPEEDLISTCTRL_H__E191A160_D10D_4C06_A08B_2A904A50CC73__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CBSpeedListCtrl.h : header file
//

#include <afxtempl.h>

class CLabelItem : public CObject  
{
public:
	CArray<CString, CString> sItem;

public:
	CLabelItem() 
	{
		sItem.SetSize(50);
	};

	CLabelItem(const CLabelItem& ci)
	{
		sItem.Copy(ci.sItem);
	};

	const CLabelItem& operator=(const CLabelItem& ci)
	{
		sItem.Copy(ci.sItem);
		return *this;
	}

	virtual ~CLabelItem() 
	{
	};
};

/////////////////////////////////////////////////////////////////////////////
// CCBSpeedListCtrl window

class CCBSpeedListCtrl : public CListCtrl
{
// Construction
public:
	CCBSpeedListCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCBSpeedListCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCBSpeedListCtrl();
	virtual int AddItem(LPCTSTR lpszItem);
	virtual BOOL SetItemText(int nItem, int nSubItem, LPCTSTR lpszText);
	void Complete();

	BOOL DeleteAllItems();
	BOOL DeleteItem(int nItem);

	// Generated message map functions
protected:
	BOOL hColumn[50];
	CArray <CLabelItem, CLabelItem> m_arLabels;
	unsigned int m_LabelCount;
	virtual int InsertItem(UINT nMask, int nItem, LPCTSTR lpszItem, UINT nState, UINT nStateMask, int nImage, LPARAM lParam);
	void SortByCol(const int ColIndex);

	//{{AFX_MSG(CCBSpeedListCtrl)
	afx_msg void OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CBSPEEDLISTCTRL_H__E191A160_D10D_4C06_A08B_2A904A50CC73__INCLUDED_)
