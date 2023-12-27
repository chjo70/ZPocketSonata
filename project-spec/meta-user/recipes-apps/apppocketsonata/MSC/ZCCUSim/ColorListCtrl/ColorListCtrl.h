#if !defined(AFX_COLORLISTVIEW_H__906AE7B2_0307_47BC_84E2_7B474DF7FC65__INCLUDED_)
#define AFX_COLORLISTVIEW_H__906AE7B2_0307_47BC_84E2_7B474DF7FC65__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
using namespace std;
// ColorListCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorListCtrl view

class CColorListCtrl : public CListCtrl
{
public:
	CColorListCtrl();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CColorListCtrl)

// Attributes
public:
    bool m_bEndScroll;

// Operations
private:
    void ScrollControl( UINT nSBCode, UINT nPos, CScrollBar &pScrollBar );

public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorListCtrl)
	protected:

	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CColorListCtrl();
protected:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorListCtrl)
	afx_msg void OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteallitems(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnInsertitem(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnVScroll( UINT nSBCode, UINT nPos, CScrollBar *pScrollBar );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	afx_msg void CustDraw( NMHDR * pNotifyStruct, LRESULT * result );
	typedef struct {
		COLORREF cf;
		long id;
		long subId;
	}ColorStruct;
	enum RecType {ROW=0,COL,CELL};
	vector<ColorStruct> RowColors;
	vector<ColorStruct> ColColors;
	vector<ColorStruct> CellColors;
	COLORREF Gx;
	COLORREF Gy;
	COLORREF Rx;
	COLORREF Ry;

	bool GridMode;
	bool AltRowMode;
	bool MaskMode;
	long findDetails(long id,RecType rt = ROW,long subId=-1);
	COLORREF InvertColor(COLORREF cf);
public:
	void SetRowColor(COLORREF cf, long row);
	void SetColColor(COLORREF cf, long col);
	void SetCellColor(COLORREF cf, long row, long col);
	void ClrRowColor(long row);
	void ClrColColor(long col);
	void ClrCellColor(long row,long col);
	void SetGridMode(bool TurnOn,COLORREF x=0,COLORREF y=0);
	void SetTextMask(bool TurnOn);
	void SetAltRowColors(bool TurnOn,COLORREF x=0,COLORREF y=0);
	void ResetColors(void);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORLISTVIEW_H__906AE7B2_0307_47BC_84E2_7B474DF7FC65__INCLUDED_)
