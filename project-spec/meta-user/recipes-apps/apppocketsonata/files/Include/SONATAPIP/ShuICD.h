#if !defined(AFX_SHUICD_H__166D4120_2F94_4231_AE60_7C719E3EC05C__INCLUDED_)
#define AFX_SHUICD_H__166D4120_2F94_4231_AE60_7C719E3EC05C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SHUICD.h : header file
//


enum _REQ_COMMANDCODE {
	REQ_INIT=1001,
	REQ_SETMODE=1101,

	REQ_SET_CONFIG=9301,
	REQ_STOP=9302,
	REQ_COL_START=9401,
	REQ_RAWDATA=9405,

	REQ_SET_IQCONFIG=1230,

	REQ_PBIT=0x05,
	REQ_IBIT=0x10,
	REQ_CBIT=0x11,
	REQ_STAT=0x14,

};

enum SHUPERHAT_RES_COMMANDCODE {
	RES_INIT = 1002,
	RES_INIT_RES = 0x02,

	RES_SET_CONFIG = 9302,
	RES_COL_START = 9404,
	RES_RAWDATA_PDW=9506,
	RES_RAWDATA_INTRA=9507,

	RES_RAWDATA_IQ=9230,

	RES_PBIT = 0x05,
	RES_IBIT = 0x10,
	RES_CBIT = 0x11,

	RES_STAT = 0x14,

};

// 헤더 데이터 구조체
struct STR_MESSAGE {
	unsigned int uiOpcode;
	unsigned int uiDataLength;

} ;

struct STR_RES_INIT {
	UINT uiReqCode;
	UINT uiErrorCode;

} ;

struct STR_REQ_SETMODE {
	UINT uiMode;
	float fTuneFreq;
	UINT coPulseNum;
	float fColTime;
	float fThreshold;
	UINT uiPAStatus;

} ;


struct STR_REQ_SETMODE_RSA {
    float fAOALow;
    float fAOAHgh;
    float fFreqLow;
    float fFreqHgh;
    float fPALow;
    float fPAHgh;
    float fPWLow;
    float fPWHgh;
    unsigned int coPulseNum;
    float fColTime;

} ;


struct STR_RES_COL_START {
    unsigned int uiStatus;
    unsigned int uiCoPulseNum;
    unsigned int uiPhase3Num;

    unsigned int uiBoardID;

} ;

#ifdef _NNN
struct STR_RES_PDW_DATA_RSA {
	float fAOA;
	float fFreq;
	float fPA;
	float fPW;
	UINT uiTOA;

	UINT uiIndex;

} ;


struct STR_RES_PDW_DATA {
	float fFreq;
	float fPA;
	float fPW;
	UINT uiTOA;

	UINT uiIndex;

} ;

struct STR_RES_INTRA_DATA {
	float fIntraFreq;

} ;

struct STR_RES_IQ_DATA {
	short sI;
	short sQ;
} ;

#define MAX_COL_PDW_DATA			(500)
#define MAX_COL_INTRA_DATA			(500)
#define MAX_COL_IQ_DATA				( (64*1024) + 1024 )


typedef union {
	unsigned char buffer[MAX_COL_IQ_DATA];
	UINT uiBuffer[1000];
	
	// 
	// 요구 데이터 구조체 정의
	STR_REQ_SETMODE stSetMode;
	STR_REQ_SETMODE_RSA stSetModeRSA;
	UINT uiMode;

	// 
	// 결과 데이터 구조체 정의
	UINT uiResult;
	STR_RES_INIT stResInit;
	STR_RES_COL_START stColStart;
	STR_RES_PDW_DATA stPDWData[MAX_COL_PDW_DATA];
	STR_RES_PDW_DATA_RSA stRSAPDWData[MAX_COL_PDW_DATA];
	STR_RES_INTRA_DATA stIntraData[MAX_COL_INTRA_DATA];
	STR_RES_IQ_DATA stIQData[MAX_COL_IQ_DATA];

} STR_DATA_CONTENTS;

#endif


#endif // !defined(AFX_SHUICD_H__166D4120_2F94_4231_AE60_7C719E3EC05C__INCLUDED_)
