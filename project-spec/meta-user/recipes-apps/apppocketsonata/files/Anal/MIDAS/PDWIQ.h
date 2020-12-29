#pragma once

//#include "../INC/PDW.h"

enum ENUM_PDW_SIGNAL_TYPE
{
	E_PDW_SIGNAL_CW = 0,
	E_PDW_SIGNAL_PULSE,
};


/*!
 * @struct	SRxIQData
 * @brief	IQ 데이터 그룹
 */
struct SRxIQDataRGroup1
{
	short sQData;	//int->float
	short sIData;	//int->float
	
};

struct SRxIFDataRGroupEEEI
{
	short sIData;	//int->float
	short sQData;	//int->float

	// !!!! 아래 초기화 구문 주석 풀어야 함 !!!!!!!!!!!!!! codesonar, uninitialized variable 에러 원인이 됨.
	SRxIFDataRGroupEEEI()
		:sIData(0),
		sQData(0)
	{
	}
};

struct SRxIQData
{
	unsigned int uiAcqTime;
	unsigned int uiAcqTimeMilSec;
	int iGain;
	int iTaskType;
	int iSDFID;
	int iPDWSetID;
	unsigned char aucTaskID[LENGTH_OF_TASK_ID];
	long long int llTOA;
	int iSearchBandID;
	unsigned int uiRelatedPDWSN;
	int iChannelNumber;
	int	iAETID;	
	int iLOBID;
	unsigned int uiNumOfSample;
	unsigned int _reserved;

	SRxIQData() :
	uiAcqTime(0),
		uiAcqTimeMilSec(0),
		iGain(0),
		iTaskType(0),
		iSDFID(0),
		iPDWSetID(0),
		llTOA(0),
		iSearchBandID(0),
		uiRelatedPDWSN(0),
		iChannelNumber(0),
		iAETID(0),
		iLOBID(0),
		uiNumOfSample(0),
		//@start_이시온
		_reserved(0)
		//@end_이시온
	{
		memset(&aucTaskID[0], ' ', LENGTH_OF_TASK_ID);
	}
}; 

/*!
 * @struct	SRxIFData
 * @brief	IF 데이터 전송
 */
struct SRxIFData
{
	int iSDFID;
	unsigned char aucTaskID[LENGTH_OF_TASK_ID];
	int iSearchBandID;
	int iSerialNumber;
	unsigned int uiNumOfSample;

SRxIFData() :
	iSDFID(0),
	iSearchBandID(0),
	iSerialNumber(0),
	uiNumOfSample(0)
	{
		// 20160316 유상범 space로 정보를 채우는 것 때문에 filename에 space가 추가되어 저장된다.(PATH_BIT), 0으로 초기화 변경
		// memset(&aucTaskID[0], ' ', LENGTH_OF_TASK_ID);
		memset( &aucTaskID, 0, sizeof( aucTaskID ) );
	}
};

struct SRxPDWData
{
	unsigned int uiAcqTime;
	unsigned int uiAcqTimeMilSec;
	int iPDWSetID;
	int iSDFID;
	unsigned char aucTaskID[LENGTH_OF_TASK_ID];
	int iSearchBandID;
	int	iAETID;	
	int	iLOBID;
	int	iNumOfPDW;

	SRxPDWData() :
	uiAcqTime(0),
		uiAcqTimeMilSec(0),
		iPDWSetID(0),
		iSDFID(0),
		iSearchBandID(0),
		iAETID(0),
		iLOBID(0),
		iNumOfPDW(0)
	{
		memset(&aucTaskID[0], 0, LENGTH_OF_TASK_ID);
	}
};