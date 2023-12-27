
// MSIGADlg.h : 헤더 파일
//

#pragma once


// CMSIGADlg 대화 상자
class CMSIGADlg : public CDialogEx
{
// 생성입니다.
private:
	bool m_bReqStart;
    bool m_bStopSigGen;

    unsigned int m_uiCoStart;

    char m_szIniFileName[200];

private:
    void LoadINI( char *pszIniFileName );
    void SaveINI( char *pszIniFileName, int iComboRadarTest );

    void UpdateRadarPDW( int iRadarTest=0 );
    void LoadRadarPDW();

public:
    void OnConnect( struct sockaddr_in *pAddr );
    void OnDisConnect( struct sockaddr_in *pAddr );

public:
	CMSIGADlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MSIGA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnNcDestroy();
    afx_msg void OnBnClickedSimStart();
	afx_msg void OnBnClickedSimLibrary();
    CComboBox m_ComboFreqType;
    CComboBox m_ComboPRIType;
    CComboBox m_ComboDOAType;
    CComboBox m_ComboFreqPatternType;
    CComboBox m_ComboPRIPatternType;
    CComboBox m_ComboFreqLevel;
    CComboBox m_ComboPRILevel;
    afx_msg void OnSelchangeComboFreqType();
    afx_msg void OnSelchangeComboFreqPatternType();
    CComboBox m_ComboPRIJitter;
    afx_msg void OnSelchangeComboPRIType();
    CComboBox m_ComboScanType;
    CEdit m_CEditDOA;
    CEdit m_CEditFreq;
    CEdit m_CEditPRI;
    CEdit m_CEditPW;
    CEdit m_CEditMissingPercent;
    CEdit m_CEditScanPeriod;
    afx_msg void OnSelchangeComboScanType();
    CEdit m_CEditSignalIntensity;
    CEdit m_CEditDDROffset;
    CEdit m_CEditPulsePerLobe;
    CEdit m_CEditAmplitude;
    CEdit m_CEditFreqBW;
    afx_msg void OnEnChangeEditPri();
    CEdit m_CEditPRIPeriod;
    CEdit m_CEditFreqPeriod;
    CEdit m_CEditDOARange;
    CEdit m_CEditFreqPulsePerLobe;
    CEdit m_CEditPRIPulsePerLobe;
    afx_msg void OnSelchangeComboPRIPatternType();
    CComboBox m_ComboRadarTest;
    afx_msg void OnSelchangeComboRadarTest();
    afx_msg void OnBnClickedSave();
    CComboBox m_ComboSignalType;
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedStopSigGen();
    virtual BOOL PreTranslateMessage( MSG *pMsg );
};
