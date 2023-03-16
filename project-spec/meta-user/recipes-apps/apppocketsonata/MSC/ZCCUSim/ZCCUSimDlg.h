
// ZCCUSimDlg.h: 헤더 파일
//

#pragma once

#include <queue>
#include <stack>

#include "../../files/Utils/cmultiserver.h"


// CZCCUSimDlg 대화 상자
class CZCCUSimDlg : public CDialogEx, public CMultiServer
{
private:
	CBitmap m_bmpLampBigOff;
	CBitmap m_bmpLampBigOn;
	CBitmap m_bmpLampConnect[6];

	//CMultiServer* m_pTheMultiServer;

	CWinThread* m_pThread;

	stack<int> m_QBoard;					///< StaticText 행 위치

    STR_LAN_HEADER m_strLanHeader;
    UNI_LAN_DATA m_uniLanData;

	ENUM_MODE m_enMode;

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

	// CMultiServer 연결하기 위한 함수 연결
	void ConnectMessage( STR_CLIENT_SOCKET* pClientSocket );
	void DisConnectMessage( STR_CLIENT_SOCKET* pClientSocket );
	void ProcessLANMessage( STR_LAN_DATA *pLanMessage );

    // 메시지 처리
	// 운용 제어
    void ResultOPStart( UNI_LAN_DATA *pLanData );
	void ResultOPShutdown( UNI_LAN_DATA *pLanData );
	void ResultOPRestart( UNI_LAN_DATA *pLanData );

	// 위협 정보
	void ReceiveThreatData( UNI_LAN_DATA *pLanData );


	// CMultiServer 연결하기 위한 함수 연결
	void Send( void *pData, unsigned int uiLength );

	// 제어 도구 업데이트
	void UpdateStaticMessage( STR_CLIENT_SOCKET* pClientSocket, bool bInsert );
	void UpdateLEDSwitch( );
	void UpdateReqStartButton();

	void AllButtonEnable( BOOL bEnable );

	void Send();

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
};
