#pragma once



// CLOBTableView 폼 뷰입니다.

class CLOBTableView : public CFormView
{
	DECLARE_DYNCREATE(CLOBTableView)

protected:
	CLOBTableView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CLOBTableView();

public:
	enum { IDD = IDD_LOBTABLEVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
private:
	CRADARANLAPPDoc *m_pDoc;

	int m_nField_OPINITID;
    int m_nField_PDWID;
    int m_nField_PLOBID;
	int m_nField_LOBID;
	int m_nField_ABTID;
	int m_nField_AETID;

	int m_nLOB;
	SRxLOBData *m_pLOBData;
	SELLOBDATA_EXT *m_pLOBExt;

public:
	void CreateListCtrl();
	void AllocMemory();
	void FreeMemory();
	int GetFieldIndex( char *pMatch, int nCoField, char **pszField );
	void WriteProfile();
	
	virtual void OnInitialUpdate();
	CListCtrl m_CListLOB;
	afx_msg void OnBnClickedButtonQuery();
	CEdit m_CEditOpInitId;
	afx_msg void OnDestroy();
	afx_msg void OnHdnItemclickListLob(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnColumnclickListLob(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHdnItemKeyDownListLob(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListLob(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit m_CEditAETID;
	afx_msg void OnNMRClickListLob(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit m_CEditCollectorID;
	afx_msg void OnBnClickedButtonInit();
	afx_msg void OnLvnItemchangedListLob(NMHDR *pNMHDR, LRESULT *pResult);
};


