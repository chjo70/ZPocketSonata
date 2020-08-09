// TaskMsg.h: interface for the Ÿ��ũ ���� �޽��� ����
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TASKMSG_H__F88C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_)
#define AFX_TASKMSG_H__F88C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// �ܺ� ��ġ ���� �޽���

// �ʴܼ��ű��� Ÿ��ũ �޽��� ����
// �ý��������� -> �ʴܼ��ű�
#define	VH_REQINITMSG				0x0101
#define	VH_REQIBITMSG				0x0102

//  �ʴܼ��ű� -> �ý���������
#define	VH_RESINITMSG				0x1101
#define	VH_RESIBITMSG				0x1102






//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// ���� �޽���


//////////////////////////////////////////////////////////////////////////
//
// ���� Ÿ��ũ���� �޽���
enum INTER_TASK_MSG {	
								// ��� ����
								REQ_INITBIT=0x01,
								Req_SWVersion,
								Req_PBIT,
								Req_UBIT,
								Req_ChannelCorrection,

								REQ_SENDCOLLECTINGLIST=0x11,


								RX_LOBDATA=0x31,
								RX_PDWDATA,


								// �ý��� ���� �޽��� �ڵ尪 ����
								REQ_POWER_ON_INIT=0xA1,
								REQ_POWER_ON_IBIT, 
								REQ_USER_PBIT, 
								REQ_SELF_CBIT, 
								REQ_CHANEL_COMPENSATION, 
								REQ_TEMPERATURE, 
								REQ_CHANNEL_VERSION, 
								REQ_SWITCH_CONTROL,
								REQ_THRESHOLD,
								REQ_SETUP_CBIT,
								REQ_KEY_PFM,
								REQ_ZERORIZE,
								REQ_DOWNLOAD_UDF,
								REQ_RELOAD_UDF,
								REQ_OP_MODE,

								// ��ȣ ���� ���� �ڵ尪 ����
								REQ_START_COLLECT=0xC1,
								REQ_START_ANAL,
								REQ_STEP_ANAL,						
								REQ_HOLD_ANAL,
								REQ_STOP_ANAL,
								REQ_BACKUP_PDW,
								REQ_REMOVE_PDW,
								REQ_HOLD_COLLECT, 
								REQ_COLLECTING_PDW,
								REQ_COLLECT_FOR_BAND,
								REQ_COLLECTING_PDW_FOR_BAND,
								REQ_PDW_DATA,
								REF_SOFT_RESET,

								// ������ ���� �ڵ尪 ����
								REQ_NEW_AET=0xD1,
								REQ_UPD_AET,
								REQ_LST_AET,
								REQ_DEL_AET,
								REQ_CHK_DEL,
								REQ_UPD_SCN,
								REQ_REFLESH,

								// CRT ȭ�� ���� ���� �ڵ尪 ����
								DISPLAY_CU_INFO=0xE1,
								DISP_PFM,
								REQ_CONTROLLER,
								REQ_START_WARMUP_MESSAGE,
								REQ_END_WARMUP_MESSAGE,
								REQ_A50_DEMO,
								DISP_DOWNLOAD_COMPLETE,
								DISP_ALIVE,
								REQ_MARK,

								// �ý��� �α� ���� �ڵ尪 ����
								REQ_ADD_SYSTEMLOG=0xF1,
								REQ_DOWNLOAD_ALL_SYSTEMLOG,

								// ���� �޽��� ���� �ڵ尪 ����
								REQ_COLLECTING_ERROR=0x91,

								// MFD ���Ǳ⿡�� ������ ����/���� �ϴ� �ڵ尪 ����
								REQ_ALL_THREAT=0x81,

								// �ý��� �α� ���� �ڵ尪 ����
								REQ_NEW_THREAT=0x61,
								REQ_UPD_THREAT,
								REQ_DEL_THREAT,
								REQ_AET_DETAIL,

								// LOB ���� ���� �ڵ尪 ����
								REQ_LOBDATA,		
								REQ_USERMSG,


								} ;

// ���� Ÿ��ũ���� �޽���
enum {	REQ_START_SERVER=0xB001, REQ_LISTEN_LAN, REQ_ACCEPT_LAN, REQ_CHECK_LAN } ;


#endif // !defined(AFX_TASKMSG_H__F88C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_)
