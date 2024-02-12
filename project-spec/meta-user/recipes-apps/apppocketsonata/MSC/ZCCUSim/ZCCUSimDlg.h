
// ZCCUSimDlg.h: 헤더 파일
//

#pragma once

#include <queue>
#include <stack>
#include <algorithm>

#include "../../files/Utils/cmultiserver.h"

#include "./ColorListCtrl/ColorListCtrl.h"

enum SCENARIO_MODE {
    enIDLE_SCENARIO=0,

    enREADY_SCENARIO,
    enRUN_SCENARIO

};

enum SCENARIO_COMMAND {
    enSCENARIO_COMMAND_NULL = 0,

    enSCENARIO_COMMAND_RESTART,
    enSCENARIO_COMMAND_DELETE,
    enSCENARIO_COMMAND_USER_SCAN,


};


struct STR_AET_LIST {
    time_t tiTime;
    COLORREF uiColor;

    unsigned int uiAETID;

    STR_AET_LIST()
    {
    }

    STR_AET_LIST( unsigned int i_uiAETID, COLORREF i_uiColor )
    {
        uiAETID = i_uiAETID;
        tiTime = time(NULL);

        uiColor = i_uiColor;
    }
};

struct STR_ABT_LIST {
    time_t tiTime;
    COLORREF uiColor;

    unsigned int uiAETID;
    unsigned int uiABTID;

    STR_ABT_LIST()
    {
    }

    STR_ABT_LIST( unsigned int i_uiAETID, unsigned int i_uiABTID, COLORREF i_uiColor )
    {
        uiAETID = i_uiAETID;
        uiABTID = i_uiABTID;

        tiTime = time(NULL);
        uiColor = i_uiColor;
    }
};

struct Find_AETID {
    STR_AET_LIST stAETID;

    Find_AETID( unsigned int uiAETID )
    {
        stAETID.uiAETID = uiAETID;
    }

    bool operator()( STR_AET_LIST i_stAETID )
    {
        return ( stAETID.uiAETID == i_stAETID.uiAETID );
    }
};

struct Find_ABTID {
    STR_ABT_LIST stABTID;

    Find_ABTID( unsigned int uiAETID, unsigned int uiABTID )
    {
        stABTID.uiAETID = uiAETID;
        stABTID.uiABTID = uiABTID;
    }

    bool operator()( STR_ABT_LIST i_stABTID )
    {
        return ( stABTID.uiAETID == i_stABTID.uiAETID ) && ( stABTID.uiABTID == i_stABTID.uiABTID );
    }
};

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
    SCENARIO_MODE m_enScenarioMode;
    SCENARIO_COMMAND m_enScenarioCommand;

	CBitmap m_bmpLampBigOff;
	CBitmap m_bmpLampBigOn;
	CBitmap m_bmpLampConnect[6];

	CWinThread* m_pThread;

	stack<int> m_QBoard;					///< StaticText 행 위치

    STR_LAN_HEADER m_strLanHeader;
    UNI_LAN_DATA m_uniLanData;

	ENUM_MODE m_enMode;

    vector <STR_AET_LIST> m_vecAETID;
    vector <STR_ABT_LIST> m_vecABTID;

    //vector <STR_LIST> m_vecABTID;
    //vector <STR_LIST> m_vecLOBID;

    unsigned int m_uiCoAETListItems;
    unsigned int m_uiCoABTListItems;
    unsigned int m_uiCoLOBListItems;

    CFont m_font;

    CMultiServer *m_pTheMULSRV;

    std::vector<STR_CLIENT_SOCKET> m_vClientSock;

    STR_BUTTON_COUNT m_stCountOfButton;

    STR_RESULT_MESSAGE m_stResultMessage;

    bool m_bScroll;

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

    int ManageAETID( unsigned int uiAETID, COLORREF uiColor );
    int ManageABTID( unsigned int uiAETID, unsigned int uiABTID, COLORREF uiColor );
    void ClearColorAETID();
    void ClearColorABTID();
    unsigned int GetRows( unsigned int uiAETID );
    unsigned int GetRows( unsigned int uiAETID, unsigned int uiABTID );
    void UpdateAETList( unsigned int uiItems, UNI_LAN_DATA *pLanData, COLORREF uiColor );
    void UpdateABTList( unsigned int uiItems, UNI_LAN_DATA *pLanData, COLORREF uiColor );

    void InsertLOBList( UNI_LAN_DATA *pLanData );


    void AddClientSocket( STR_CLIENT_SOCKET *pClientSocket );
    void RemoveClientSocket( STR_CLIENT_SOCKET *pClientSocket );

    void DisplayButtonCount();

    BOOL UpdateThreatID();

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
    void ResultOfLostBeamData( UNI_MSG_DATA *pLanData );
    void ResultOfDelete( UNI_MSG_DATA *pLanData );
    void ResultOfDeleteThreatData( UNI_MSG_DATA *pLanData, unsigned int uiDataLength );
    void ResultOfUserDeleteThreatData( UNI_MSG_DATA *pLanData );
    void ResultOfDeleteBeamData( UNI_MSG_DATA *pLanData );

    // 에러 메시지
    void ResultOfSysError( UNI_LAN_DATA *pLanData );

    void VectorErase( vector <STR_AET_LIST> &v, unsigned int uiAETID );
    void VectorErase( vector <STR_ABT_LIST> &v, STR_ABT_LIST &stABT );

    void UpdateThreatInfo();

    void AllScenarioButtonEanble( BOOL bEnable );

    void DisplayStatusMessage( const char *format, ... );


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
    CColorListCtrl m_CListCtrlAET;
    CColorListCtrl m_CListCtrlABT;
    CColorListCtrl m_CListCtrlLOB;

    afx_msg void OnBnClickedButtonReqScan();
    afx_msg void OnNMClickListAet( NMHDR *pNMHDR, LRESULT *pResult );
    afx_msg void OnNMClickListAbt( NMHDR *pNMHDR, LRESULT *pResult );
    CStatic m_CStaticError;
    CColorListCtrl m_ListCtrlLOB;
    afx_msg void OnIDClose();
    afx_msg void OnNMCustomdrawListLob( NMHDR *pNMHDR, LRESULT *pResult );
    virtual BOOL PreTranslateMessage( MSG *pMsg );
    afx_msg void OnTimer( UINT_PTR nIDEvent );
    afx_msg void OnLvnItemchangedListAbt( NMHDR *pNMHDR, LRESULT *pResult );
    afx_msg void OnLvnBeginScrollListLob( NMHDR *pNMHDR, LRESULT *pResult );
    afx_msg void OnLvnEndScrollListLob( NMHDR *pNMHDR, LRESULT *pResult );
    afx_msg void OnBnClickedButtonReqRestartScenario();
    afx_msg void OnBnClickedButtonReqDeleteScenario();
    afx_msg void OnBnClickedButtonCancelScenario();
    afx_msg void OnBnClickedButtonReqScanScenario();
    afx_msg void OnBnClickedButtonReqSbcReboot();
};
