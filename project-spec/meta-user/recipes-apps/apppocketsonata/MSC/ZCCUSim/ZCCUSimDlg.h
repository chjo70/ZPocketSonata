
// ZCCUSimDlg.h: 헤더 파일
//

#pragma once

#include <queue>
#include <stack>

#include "../../files/Utils/cmultiserver.h"


struct STR_LIST {
    unsigned int uiID;

    unsigned int uiRow;
};

struct STR_BUTTON_COUNT {
    unsigned int uiCoStartButton;
    unsigned int uiCoRestartButton;

    unsigned int uiCoDownloadButton;

    unsigned int uiCoRequestConfigButton;
    unsigned int uiCoRequestButton;

    unsigned int uiCoRequestUserScanButton;
    unsigned int uiCoRequestDeleteButton;

};

struct STR_RESULT_MESSAGE {
    unsigned int uiCoStart;
    unsigned int uiCoRestartButton;

    unsigned int uiCoDownload;

    unsigned int uiCoReqOpVarSetting;
    unsigned int uiCoRequestOpVar;

    unsigned int uiCoRequestUserScanButton;
    unsigned int uiCoRequestDeleteButton;

};



// CZCCUSimDlg 대화 상자
class CZCCUSimDlg : public CDialogEx
{
private:
	CBitmap m_bmpLampBigOff;
	CBitmap m_bmpLampBigOn;
	CBitmap m_bmpLampConnect[6];

	CWinThread* m_pThread;

	stack<int> m_QBoard;					///< StaticText 행 위치

    STR_LAN_HEADER m_strLanHeader;
    UNI_LAN_DATA m_uniLanData;

	ENUM_MODE m_enMode;

    vector <unsigned int> m_vecAETID;
    vector <STR_LIST> m_vecABTID;
    vector <STR_LIST> m_vecLOBID;

    unsigned int m_uiCoAETListItems;
    unsigned int m_uiCoABTListItems;
    unsigned int m_uiCoLOBListItems;

    CFont m_font;

    CMultiServer *m_pTheMULSRV;

    std::vector<STR_CLIENT_SOCKET> m_vClientSock;

    STR_BUTTON_COUNT m_stCountOfButton;

    STR_RESULT_MESSAGE m_stResultMessage;

// 생성입니다.
public:
	CZCCUSimDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ZCCUSIM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
private:
	void Init();
	void InitView();
	void Free();

    void InitViewVariable();


    // 메시지 처리

    // 방사체 삭제
    void DeleteThreatData( UNI_LAN_DATA *pLanData );
    void DeleteThreatData( UINT uiAETID, UINT uiABTID=0 );

    // 빔 삭제
    void DeleteBeamData( UNI_LAN_DATA *pLanData );

	// CMultiServer 연결하기 위한 함수 연결
	//void Send( void *pData, unsigned int uiLength );

	// 제어 도구 업데이트
	void UpdateStaticMessage( STR_CLIENT_SOCKET* pClientSocket, bool bInsert );
	void UpdateLEDSwitch( );
	void UpdateReqStartButton();

	void AllButtonEnable( BOOL bEnable );

    // 화면 관련 함수 모음
    void ClearErrorMessage();

    // 랜 메시지 전송
	void Send( void *pLanData=NULL, BOOL bSwap=TRUE );

    int ManageAETID( unsigned int uiAETID );
    unsigned int GetRows( unsigned int uiAETID );
    unsigned int GetRows( unsigned int uiAETID, unsigned int uiABTID );
    void UpdateAETList( unsigned int uiItems, UNI_LAN_DATA *pLanData );
    void UpdateABTList( unsigned int uiItems, UNI_LAN_DATA *pLanData );

    void InsertLOBList( UNI_LAN_DATA *pLanData );


    void AddClientSocket( STR_CLIENT_SOCKET *pClientSocket );
    void RemoveClientSocket( STR_CLIENT_SOCKET *pClientSocket );

    void DisplayButtonCount();

public:
    // CMultiServer 연결하기 위한 함수 연결
    void ConnectMessage( STR_CLIENT_SOCKET *pClientSocket );
    void DisConnectMessage( STR_CLIENT_SOCKET *pClientSocket );
    void ProcessLANMessage( STR_LAN_DATA *pLanMessage );

    // 운용 제어
    void ResultOfOPStart( UNI_MSG_DATA *pLanData );
    void ResultOfOPShutdown( UNI_MSG_DATA *pLanData );
    void ResultOfOPRestart( UNI_MSG_DATA *pLanData );

    // 위협 라이브러리
    void ResultOfReloadLibrary( UNI_MSG_DATA *pLanData );

    // 위협 정보
    void ResultOfThreatData( UNI_LAN_DATA *pLanData );

    ///////////////////////////////////////////////////////////////////////////////////
    // 운용 설정 변수
    // 신호 분석 변수 설정 요청
    void ResultOfSetSys( UNI_MSG_DATA *pLanData );

    // 신호 분석 변수 요청
    void ResultOfSys( UNI_LAN_DATA *pLanData, unsigned int uiDataLength );

    ///////////////////////////////////////////////////////////////////////////////////
    //
    void ResultOfUserScan( UNI_MSG_DATA *pLanData );
    void ResultOfScanData( UNI_MSG_DATA *pLanData );

    //
    void ResultOfDelete( UNI_MSG_DATA *pLanData );
    void ResultOfDeleteThreatData( UNI_MSG_DATA *pLanData );
    void ResultOfUserDeleteThreatData( UNI_MSG_DATA *pLanData );
    void ResultOfDeleteBeamData( UNI_MSG_DATA *pLanData );

    // 에러 메시지
    void ResultOfSysError( UNI_LAN_DATA *pLanData );


protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedButtonReqStart();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	CStatic m_CStaticConnectMessage[MAX_CLIENTS];
	CStatic m_CStaticLED;
	CButton m_CButtonReqStart;
	afx_msg void OnBnClickedButtonReqRestart();
	afx_msg void OnBnClickedButtonReqOpvar();
	afx_msg void OnBnClickedButtonReqDisconnect();
	afx_msg void OnBnClickedButtonReqDownload();
    afx_msg void OnBnClickedButtonReqOpvarSetting();
    afx_msg void OnBnClickedButtonReqDelete();
    CListCtrl m_CListCtrlAET;
    CListCtrl m_CListCtrlABT;
    CListCtrl m_CListCtrlLOB;

    afx_msg void OnBnClickedButtonReqScan();
    afx_msg void OnNMClickListAet( NMHDR *pNMHDR, LRESULT *pResult );
    afx_msg void OnNMClickListAbt( NMHDR *pNMHDR, LRESULT *pResult );
    CStatic m_CStaticError;
    CListCtrl m_ListCtrlLOB;
    afx_msg void OnIDClose();
};
