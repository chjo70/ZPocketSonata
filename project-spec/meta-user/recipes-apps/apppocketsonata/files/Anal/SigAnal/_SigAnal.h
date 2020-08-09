// _SigAnal.h: interface for the Ž���м� ����Ʈ������ �������
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIGANAL_H__554E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_)
#define AFX_SIGANAL_H__554E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "_type.h"
#include "_macro.h"

#include "_Define.h"
#include "_Struct.h"

#ifdef _WIN32
// #include "../../AdvSigAnal/Dummy/Dummy.h"
#endif

#include "../INC/System.h"
#include "../ScanSigAnal/SDefine.h"
#include "../ScanSigAnal/SStruct.h"


//////////////////////////////////////////////////////////////////////////
// printf()���� ��ü�ϱ� ���� ����.
// Printf() ���� �Լ��� Ÿ �ҽ����� �̸� �����ؼ� ��� Ư���� �°� ������.

// #define printf printf

// #ifdef __cplusplus
// extern "C" {
// #endif
// 
// int Printf( char *format, ... );
// 
// #ifdef __cplusplus
// }
// #endif

//////////////////////////////////////////////////////////////////////////


#ifdef __cplusplus
extern "C" {
#endif

#ifdef _MAIN_

_TOA TOA[MAX_PDW];					// PDW TOA �Ķ����
UINT AOA[MAX_PDW];					// PDW AOA �Ķ����
UINT FREQ[MAX_PDW];					// PDW FREQUENCY �Ķ����
UINT PW[MAX_PDW];						// PDW PULSE WIDTH �Ķ����
int PA[MAX_PDW];						// PDW PULSE AMPLITUDE �Ķ����
UCHAR PMOP[MAX_PDW];				// PDW PMOP �Ķ����
UCHAR FMOP[MAX_PDW];				// PDW FMOP �Ķ����
USHORT MARK[MAX_PDW];				// PDW MARK ; selected pdw
UCHAR BAND[MAX_PDW];				// ���ļ� ���
UCHAR STAT[MAX_PDW];				// PDW STATUS(Notmal, CW, PMOP, Chirp Up/Dn)
USHORT BKMK[MAX_PDW];				// MARK �����, ���°� �м��ÿ� �����.
USHORT RSMK[MAX_PDW];				// MARK �����, ���°� �м��ÿ� �����.
UCHAR MAXCHANNEL[MAX_PDW];	// PDW�� MaxChannel

// ���ļ� �ػ� ����

// HARMONIC MARGIN
#ifdef _ELINT_
UINT stSigma1Aoa[5] = { KHARM_AOA_MAR, KHARM_AOA_MAR, KHARM_AOA_MAR, KHARM_AOA_MAR, KHARM_AOA_MAR } ;
UINT stSigma1Frq[5] = { KHARM_FRQ_MAR, KHARM_FRQ_MAR, KHARM_FRQ_MAR, KHARM_FRQ_MAR, KHARM_FRQ_MAR } ;

#else
UINT stSigma1Aoa[3] = { KHARM_AOA_MAR_LOW, KHARM_AOA_MAR_MID, KHARM_AOA_MAR_HGH } ;
UINT stSigma1Frq[3] = { KHARM_FRQ_MAR_LOW, KHARM_FRQ_MAR_MID, KHARM_FRQ_MAR_HGH } ;

#endif

STR_MANAET stTrkAet;
STR_SCNAET stScnAet;
STR_SCANPT stScanPt;

UINT stOffPdw;

#else

extern _TOA TOA[MAX_PDW];			// PDW TOA �Ķ����
extern UINT AOA[MAX_PDW];			// PDW AOA �Ķ����
extern UINT FREQ[MAX_PDW];		// PDW FREQUENCY �Ķ����
extern UINT PW[MAX_PDW];			// PDW PULSE WIDTH �Ķ����
extern int PA[MAX_PDW];			// PDW PULSE AMPLITUDE �Ķ����
extern UCHAR PMOP[MAX_PDW];		// PDW PMOP �Ķ����
extern UCHAR FMOP[MAX_PDW];		// PDW FMOP �Ķ����
extern USHORT MARK[MAX_PDW];	// PDW MARK ; selected pdw
extern UCHAR BAND[MAX_PDW];		// ���ļ� ���
extern UCHAR STAT[MAX_PDW];		// ���ļ� ���
extern USHORT BKMK[MAX_PDW];		// Mark �޽����� �����
extern USHORT RSMK[MAX_PDW];	// MARK �����, ���°� �м��ÿ� �����.
extern UCHAR MAXCHANNEL[MAX_PDW];	// PDW�� MaxChannel

#ifdef _A50_RWR
extern UINT stSigma1Aoa[5];
extern UINT stSigma1Frq[5];

#else
extern UINT stSigma1Aoa[3];
extern UINT stSigma1Frq[3];

#endif


extern STR_MANAET stTrkAet;
extern STR_SCNAET stScnAet;
extern STR_SCANPT stScanPt;

extern UINT stOffPdw;

#endif	// _MAIN_

#ifdef __cplusplus
}
#endif

// int Printf( char *format, ... );


#endif // !defined(AFX_SIGANAL_H__554E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_)
