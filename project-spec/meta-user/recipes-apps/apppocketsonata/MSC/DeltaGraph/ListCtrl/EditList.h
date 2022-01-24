#if !defined(AFX_EDITLIST_H__834127E6_9297_11D5_8AFA_DAC6E5A1C54B__INCLUDED_)
#define AFX_EDITLIST_H__834127E6_9297_11D5_8AFA_DAC6E5A1C54B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditList.h : header file
//
typedef int (* fGetType) (int);

/////////////////////////////////////////////////////////////////////////////
// CEditList window
class CEditList : public CListCtrl
{
	// Construction
public:
	CEditList();

// Attributes
public:
	enum eType{
		eEdit,
		eCombo,
		eLast	
	};

	fGetType m_fGetType;

	CStringList m_strList;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditList)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetColumnType(fGetType func) { m_fGetType = func;}
	virtual ~CEditList();

	// Generated message map functions
protected:

	CComboBox * ComboItem( int nItem,  int nSubItem);
	CEdit * EditItem( int nItem, int nSubItem);
	//{{AFX_MSG(CEditList)
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydown(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITLIST_H__834127E6_9297_11D5_8AFA_DAC6E5A1C54B__INCLUDED_)
