#ifndef _H_EL_POS_EST_DATATYPE
#define _H_EL_POS_EST_DATATYPE

#define SIZE_OF_CHAR_SMALL_INFO 15
#define SIZE_OF_DTCT_ID 25
struct SPosEstData
{
    bool bIsManualPosEstApply;
    double dEstPosX;
    double dEstPosY;
    double dEstLatitude;
    double dEstLongitude;
    double dEstAltitude;
    double dLengthMajorAxis;
    double dLengthMinorAxis;
    double dCEP;									// CEP
    double dEstError;
    double dTiltAngleDeg;					// EEP의 Theta 각도
    bool bIsValid;
    unsigned char szTaskId[LENGTH_OF_TASK_ID+1];
    int nEmitterId;								// AETID
    int nLobId;
    int nSearchBandId;
    int nNumOfLobUsed;
    int nActPeriod;
    int nActNum;
    int nThreatIndex;
    int nDeviceIndex;
    int nRadarIndex;

    /*! \todo   아래 뱐수는 삭제해야 함.
        \author 조철희 (churlhee.jo@lignex1.com)
        \date 	2015-10-28 16:33:19
    */
    int nPinNumber;
    int iEOBId;										// EOB ID

    int nHourConvergence; // 최초 위치산출 시각 (시)
    int nMinConvergene; // 최초 위치산출 시각 (분)
    int nSecConvergence; // 최초 위치산출 시각 (초)
    int nNumOfLobConvergence; // 최초 위치 산출시 사용된 lob 개수
    unsigned char szElintNotation[SIZE_OF_CHAR_SMALL_INFO];
    unsigned char szDtctId[SIZE_OF_DTCT_ID];

    SPosEstData()
    {
        bIsManualPosEstApply = false;
        bIsValid = false;
        memset(szTaskId, 0, LENGTH_OF_TASK_ID+1);
        nEmitterId = 0;
        nLobId = 0;
        nSearchBandId = 0;
        nNumOfLobUsed = 0;
        nActPeriod = 0;
        nActNum = 0;
        dEstPosX = (double)0.0;
        dEstPosY = 0.0;
        dEstLatitude = 0.0;
        dEstLongitude = 0.0;
        dEstAltitude = 0.0;
        dLengthMajorAxis = 0.0;
        dLengthMinorAxis = 0.0;
        dCEP = -1.;
        dTiltAngleDeg = 0.0;

        dEstError = -1.;

        nThreatIndex = 0;
        nDeviceIndex = 0;
        nRadarIndex = 0;
        nPinNumber = 0;
        iEOBId = 0;

        nHourConvergence = 0;
        nMinConvergene = 0;
        nSecConvergence = 0;
        nNumOfLobConvergence = 0;
        memset(szElintNotation, 0, SIZE_OF_CHAR_SMALL_INFO);
        memset(szDtctId, 0, SIZE_OF_DTCT_ID);
    };
};

struct SPosIdSet
{
	int nEmitterId;
	int nLobId;
	int nDrawObjId;
	char szTaskId[LENGTH_OF_TASK_ID];
	int nSearchBandId;

    SPosIdSet()
	{
		memset(&szTaskId, 0, LENGTH_OF_TASK_ID);
		nSearchBandId = -1;			
		nEmitterId = -1;
		nLobId = -1;
		nDrawObjId = -1;
	};
};

struct STR_POSESTDATA {
	int nEmitterId;
	int nBeamId;

	// 입력 값, 위치 산출 값을 아래에 저장한다.
	double dEstLatitude;		
	double dEstLongitude;
	double dEstAltitude;

} ;

#endif
