#pragma once

#include "../INC/PDW.h"

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

struct SRxIQData {
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
};

/*!
 * @struct	SRxIFData
 * @brief	IF 데이터 전송
 */
struct SRxIFData {
	int iSDFID;
	unsigned char aucTaskID[LENGTH_OF_TASK_ID];
	int iSearchBandID;
	int iSerialNumber;
	unsigned int uiNumOfSample;

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

};
