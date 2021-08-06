#ifndef _H_EL_EMITTER_DATATYPE
#define _H_EL_EMITTER_DATATYPE

#ifndef __VXWORKS__
#include <memory.h>
#endif


#include <string>
#include <list>
using namespace std;

#include "ELMsgDefn.h"

//#include "../Identify/ELCEDLibDataType2.h"


/**
* [�떇蹂꾩옄 : D-GR-SDD-XXX]
* [異붿쟻�꽦 : R-GR-SRS-XXX]
*
* @file ELEmitterDataType.h
* @brief 諛⑹궗泥� 紐⑸줉李쎌뿉�꽌 View/Logic 媛� 諛쒖깮�븯�뒗 �씤�꽣�럹�씠�뒪 data �젙�쓽
* @author �씠�젙�궓
* @date 2013.5.25
*   
* [媛쒖젙�씠�젰]
*  2013.5.25. �떊洹쒖옉�꽦
*  2013.6.18. std::string strIsFisintTask �뜲�씠�꽣 異붽�
*/

// �쐞移� �궛異쒗븯湲� �쐞�븳 理쒕� LOB 媛��닔 �젙�쓽
#define MAX_OF_LOBS_PE								(30)					// LOB 理쒕� 媛��닔
// 鍮붿뿉�꽌 蹂닿��븯湲� �쐞�븳 LOB 媛��닔 �젙�쓽
#define MAX_OF_LOBS										(100)					// LOB �썑蹂� 媛쒖닔


/************************************************************************************
*   ELINT Logic -> View�뿉 �궗�슜�릺�뒗 �옄猷뚰삎 援ъ“泥�
*************************************************************************************/

/* 1.  E_EL_LV_SHOW_EMITTER_DATA �넚�떊�떆 data_in�뿉 �궗�슜�릺�뒗 援ъ“泥�. 由ы꽩�뾾�쓬*/
//#ifndef ST_EMIITERINFO_DISP
//#define ST_EMIITERINFO_DISP
// stEmitterInfoDisp �쓽 以묐났 �젙�쓽瑜� 留됯린�쐞�빐 #ifndef.. �궗�슜

#define SIZE_OF_CHAR_EMITTER_INFO	15
#define SIZE_OF_CHAR_MID_INFO		32

//#define MAX_IDCANDIDATE					10

// �궗�슜�븞�븿.
typedef struct stEmitterInfoDisp
{
	string strEmitterNum;
	string strDirection;
	string strTaskId;
	string strIsFisintTask; // 2013.6.18. 異붽�
	string strFrqTypeRange;
	string strPRITypeRange;
	string strSJ;
	string strPwRange;
	string strPaRange;
	string strScanTypePeriod;
	string strElintNoteAir;
	string strPrimFuncAir;
	string strPlatformAir;
	string strIdNumberAir;
	string strConsistRateAir;
	string strElintNoteGnd;
	string strPrimFuncGnd;
	string strPlatformGnd;
	string strIdNumberGnd;
	string strConsisitRateGnd;
	string strEstimated;
	string strRptStat;
	string strSOI;
	string strPosEstimated;
	string strActivatedOrNot;
}_EMITTER_INFO;

// MAX_COLUMN 媛믪� �쁽�옱 70媛� �씠硫� �씠�긽�씠 �맆�븣 �씠 媛믩룄 媛숈씠 利앷��떆耳쒖빞 �븳�떎. , 議곗쿋�씗
// 68媛쒕줈 �븯硫� S/W媛� 遺덉븞�븿.
// UpdateHeaderCol()瑜� 媛숈씠 怨좎쿂�뿬 �븿. �솢 �씠�젃寃� 留뚮뱾�뿀�뒗吏� 紐⑤Ⅴ寃좊꽕...
#define NUM_OF_EMITTER_FIELD_NAME 90

typedef struct stEmitterInfo
{
	CString strLinkNum;	 //#FA_Q_2502_T1						// "SDF ID";
	CString strEmitterNum;					// "諛⑹궗泥대쾲�샇",
	CString strSignalNum;						// "�떊�샇�씪�젴踰덊샇",
	CString strMissionId;						// "�엫臾대챸",
	CString strTaskId;							// "怨쇱젣ID",
	CString strTaskName;						// "怨쇱젣紐�",
	CString strSrchBandId;					// "�깘�깋���뿭 id"
	CString strDirection;						// "諛⑹쐞[�룄]",
	CString strMinDirection;				// "理쒖냼 諛⑹쐞[�룄]",
	CString strMaxDirection;				// "理쒕� 諛⑹쐞[�룄]",
	CString strDirectionDev;				// "諛⑹쐞�렪李�[�룄]",
	CString strFisintTask;					// "FISINT怨쇱젣",
	CString strFrqType;							// "二쇳뙆�닔�삎�깭",
	CString strFrq;									// "二쇳뙆�닔[Hz]",
	CString strMinFrq;							// "理쒖냼 二쇳뙆�닔[Hz]",
	CString strMaxFrq;							// "理쒕� 二쇳뙆�닔[Hz]",
	CString strFrqPatternRange;			// "二쇳뙆�닔�뙣�꽩�삎�깭/踰붿쐞[ms]",
	CString strFrqRangeDev;					// "二쇳뙆�닔�렪李�[Hz]",
	CString strPriority;						// "�슦�꽑�닚�쐞",
	CString strTime;								// "�씪�옄/�떆媛�",
	CString strModType;							// "蹂�議고삎�깭",
	CString strSigType;		//#FA_Q_2502_T1					// "�떊�샇�삎�깭",
	CString strPw;									// "PW[ns]",
	CString strMinPw;								// "理쒖냼 PW[ns]",
	CString strMaxPw;								// "理쒕� PW[ns]",
	CString strPa;									// "PA[dB]",
	CString strMinPa;								// "理쒖냼 PA[dBm]",
	CString strMaxPa;								// "理쒕� PA[dBm]",
	CString strPriType;							// "PRI�삎�깭",
	CString strPri;									// "PRI[ns]",
	CString strMinPri;							// "理쒖냼 PRI",
	CString strMaxPri;							// "理쒕� PRI",
	CString strPRIPatternRange;			// "PRI�뙣�꽩�삎�깭/踰붿쐞[ns]",
	CString strPrf;									// "PRF踰붿쐞[PPS]",
	CString strMinPrf;							// "PRF踰붿쐞[PPS]",
	CString strMaxPrf;							// "PRF踰붿쐞[PPS]",
	CString strPulsePerGrp;					// "�럡�뒪�닔/洹몃９",
	CString strSJ;									// "S/J",
	CString strScanTypePeroid;			// "�뒪罹뷀삎�깭/二쇨린",
	CString strAirElintNotation;		// "[A]E-NOT",
	CString strAirFunc;							// "[A]湲곕뒫遺��샇",
	CString strAirSiteFunc;					// "[A]�궗�씠�듃湲곕뒫",
	CString strAirThreat;						// "[A]�쐞�삊",
	CString strAirEqupNo;						// "[A]�옣鍮꾨쾲�샇",
	CString strAirConsistancyRatio;	// "[A]�씪移섏쑉[%]",
	CString strAirConsistancy;			// "[A]�씪移섎룄",
	CString strAirGeoCoord;					// "[A]吏�由ъ쥖�몴",
	CString strAirAlt;							// "[A]怨좊룄[m]",
	CString strAirConfIterval;			// "[A]�떊猶곌뎄媛�[m]",
	CString strAirCep;							// "[A]CEP[m]",
	CString strAirMajorAxis;				// "[A]�옣異�[m]",
	CString strAirMinorAxis;				// "[A]�떒異�(m)",
	CString strAirMajorAxisAzimuth; // "[A]�옣異뺣갑�쐞[�룄]",
	CString strGndElintNotation;		// "[G]E-NOT",
	CString strGndPinNr;						// "[G]PIN NR",
	CString strGndFunc;							// "[G]湲곕뒫遺��샇",
	CString strGndSiteFunc;					// "[G]�궗�씠�듃湲곕뒫",
	CString strGndThreat;						// "[G]�쐞�삊",
	CString strGndEqupNo;						// "[G]�옣鍮꾨쾲�샇",
	CString strGndConsistancyRatio;	// "[G]�씪移섏쑉[%]",
	CString strGndConsistancy;			// "[G]�씪移섎룄",
	CString strGndGeoLongitude;			// "[G]吏�由ъ쥖�몴(寃쎈룄)",
	CString strGndGeoLatitude;			// "[G]吏�由ъ쥖�몴(�쐞�룄)",
	CString strGndAlt;							// "[G]怨좊룄[m]",
	CString strGndConfIterval;			// "[G]�떊猶곌뎄媛�[m]",
	CString strGndCep;							// "[G]CEP[m]",
	CString strGndMajorAxis;				// "[G]�옣異�[m]",
	CString strGndMinorAxis;				// "[G]�떒異�(m)",
	CString strGndMajorAxisAzimuth; // "[G]�옣異뺣갑�쐞[�룄]",												
	CString strGndBaseName;					// "[G]湲곗�紐�",
	CString strGndIdInfo;						// "[G]�떇蹂꾩젙蹂�",
	CString strGndCandidate;				// "[G]�떇蹂� �썑蹂� 紐⑸줉",
	CString strGndDistError;				// "[G]嫄곕━ �삤李�[km]",
	CString strGndDistErrorToNM;		// "[G]嫄곕━ �삤李�[nm]",
	CString strGndEOBId;						// "[G] EOB ID",
	CString strFinalReport;					// "理쒖쥌蹂닿퀬",							
	CString strFinalAlarm;					// "理쒖쥌寃쎈낫",							",
	CString strPosEstimation;				// "�궛異쒖뿬遺�",							
	CString strSOI;									// "愿��떖�떊�샇"							
	CString strIsStorePDW;					// "PDW ���옣�뿬遺�"
	CString strNumOfCol;						// "�닔吏묎컻�닔[PDW/IQ]"
	CString strNumOfAmbigiousBeam;	// "紐⑦샇�꽦",
	CString strNumOfPDWSet;					// "PDW �꽭�듃"
	CString strActivatedOrNot;			// "�솢�룞�뿬遺�"
	CString strLobId;								// "LOB #" . 2014.10.8. 異붽�. �씠�젙�궓
	CString strDtctId;							// "Dtct ID" . 2015.3.3. 異붽�. �씠�젙�궓
	CString strIdCode;							// "�떇蹂� 肄붾뱶" . 2015.3.31. 異붽�. 議곗쿋�씗
	CString strPolization;					// "洹뱀꽦" . 2015.4.1. 異붽�. 議곗쿋�씗
	CString strTaskOperator;				// "怨쇱젣 �슫�슜�궗", 2015.4.7. 異붽�. 議곗쿋�씗
	CString strGndModeSymbol;					// 紐⑤뱶 遺��샇

	stEmitterInfo()
	{
		strLinkNum="";						
		strEmitterNum="";					
		strSignalNum="";					
		strMissionId="";						
		strTaskId="";							
		strTaskName="";					
		strSrchBandId="";					
		strDirection="";						
		strMinDirection="";				// 
		strMaxDirection="";				
		strDirectionDev="";				
		strFisintTask="";					// 
		strFrqType="";						
		strFrq="";								
		strMinFrq="";							
		strMaxFrq="";						
		strFrqPatternRange="";			
		strFrqRangeDev="";				
		strPriority="";						// 
		strTime="";							
		strModType="";						
		strSigType="";						
		strPw="";								
		strMinPw="";							
		strMaxPw="";							
		strPa="";								
		strMinPa="";							
		strMaxPa="";							
		strPriType="";						
		strPri="";								
		strMinPri="";							
		strMaxPri="";							
		strPRIPatternRange="";			
		strPrf="";								
		strMinPrf="";							
		strMaxPrf="";							
		strPulsePerGrp="";					
		strSJ="";								
		strScanTypePeroid="";			
		strAirElintNotation="";		// "[A
		strAirFunc="";						
		strAirSiteFunc="";					
		strAirThreat="";						
		strAirEqupNo="";					
		strAirConsistancyRatio="";	// 
		strAirConsistancy="";			// 
		strAirGeoCoord="";				
		strAirAlt="";							
		strAirConfIterval="";			// 
		strAirCep="";							
		strAirMajorAxis="";				// 
		strAirMinorAxis="";				// 
		strAirMajorAxisAzimuth=""; //
		strGndElintNotation="";		// 
		strGndPinNr="";						
		strGndFunc="";						
		strGndSiteFunc="";					
		strGndThreat="";					
		strGndEqupNo="";					
		strGndConsistancyRatio="";	
		strGndConsistancy="";			
		strGndGeoLongitude="";			
		strGndGeoLatitude="";			
		strGndAlt="";							
		strGndConfIterval="";			// 
		strGndCep="";						
		strGndMajorAxis="";				
		strGndMinorAxis="";				
		strGndMajorAxisAzimuth=""; 
			strGndBaseName="";				
		strGndIdInfo="";						
		strGndCandidate="";				
		strGndDistError="";				
		strGndDistErrorToNM="";		
		strGndEOBId="";					
		strFinalReport="";					
		strFinalAlarm="";					
		strPosEstimation="";				
		strSOI="";								
		strIsStorePDW="";					
		strNumOfCol="";					
		strNumOfAmbigiousBeam="";	
		strNumOfPDWSet="";				
		strActivatedOrNot="";			
		strLobId="";							
		strDtctId="";							
		strIdCode="";							
		strPolization="";					// 
		strTaskOperator="";				
		strGndModeSymbol="";			
	};

//	void stEmitterInfo::SetInterCommInfo(BYTE *i_pbyInData)
//	{
//		int nCount=0;
//		USHORT nSize=0;
//		
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strLinkNum.SetString((const char*)&i_pbyInData[nCount], nSize) ;								// "SDF ID";
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strEmitterNum.SetString((const char*)&i_pbyInData[nCount], nSize);					// "諛⑹궗泥대쾲�샇",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strSignalNum.SetString((const char*)&i_pbyInData[nCount], nSize);						// "�떊�샇�씪�젴踰덊샇",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strMissionId.SetString((const char*)&i_pbyInData[nCount], nSize);						// "�엫臾대챸",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strTaskId.SetString((const char*)&i_pbyInData[nCount], nSize);							// "怨쇱젣ID",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strSrchBandId.SetString((const char*)&i_pbyInData[nCount], nSize);					// "�깘�깋���뿭 id"
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strDirection.SetString((const char*)&i_pbyInData[nCount], nSize);						// "諛⑹쐞[�룄]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strDirectionDev.SetString((const char*)&i_pbyInData[nCount], nSize);				// "諛⑹쐞�렪李�[�룄]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strFisintTask.SetString((const char*)&i_pbyInData[nCount], nSize);					// "FISINT怨쇱젣",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strFrqType.SetString((const char*)&i_pbyInData[nCount], nSize);				// "二쇳뙆�닔�삎�깭",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strFrq.SetString((const char*)&i_pbyInData[nCount], nSize);				// "二쇳뙆�닔[Hz]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strMinFrq.SetString((const char*)&i_pbyInData[nCount], nSize);				// "理쒖냼 二쇳뙆�닔[Hz]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strMaxFrq.SetString((const char*)&i_pbyInData[nCount], nSize);				// "理쒕� 二쇳뙆�닔[Hz]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strFrqPatternRange.SetString((const char*)&i_pbyInData[nCount], nSize);			// "二쇳뙆�닔�뙣�꽩�삎�깭/踰붿쐞[ms]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strFrqRangeDev.SetString((const char*)&i_pbyInData[nCount], nSize);					// "二쇳뙆�닔�렪李�[Hz]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strPriority.SetString((const char*)&i_pbyInData[nCount], nSize);						// "�슦�꽑�닚�쐞",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strTime.SetString((const char*)&i_pbyInData[nCount], nSize);								// "�씪�옄/�떆媛�",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strModType.SetString((const char*)&i_pbyInData[nCount], nSize);							// "蹂�議고삎�깭",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strSigType.SetString((const char*)&i_pbyInData[nCount], nSize);							// "�떊�샇�삎�깭",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strPw.SetString((const char*)&i_pbyInData[nCount], nSize);							// "PW踰붿쐞[ns]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strMinPw.SetString((const char*)&i_pbyInData[nCount], nSize);							// "PW踰붿쐞[ns]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strMaxPw.SetString((const char*)&i_pbyInData[nCount], nSize);							// "PW踰붿쐞[ns]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strPa.SetString((const char*)&i_pbyInData[nCount], nSize);							// "PA踰붿쐞[dB]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strMinPa.SetString((const char*)&i_pbyInData[nCount], nSize);							// "PA踰붿쐞[dB]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strMaxPa.SetString((const char*)&i_pbyInData[nCount], nSize);							// "PA踰붿쐞[dB]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strPriType.SetString((const char*)&i_pbyInData[nCount], nSize);							// "PRI�삎�깭",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strPri.SetString((const char*)&i_pbyInData[nCount], nSize);									// "PRI[ns]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strMinPri.SetString((const char*)&i_pbyInData[nCount], nSize);							// "理쒖냼 PRI[ns]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strMaxPri.SetString((const char*)&i_pbyInData[nCount], nSize);							// "理쒕� PRI[ns]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strPRIPatternRange.SetString((const char*)&i_pbyInData[nCount], nSize);			// "PRI�뙣�꽩�삎�깭/踰붿쐞[ns]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strPrf.SetString((const char*)&i_pbyInData[nCount], nSize);						// "PRF踰붿쐞[PPS]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strMinPrf.SetString((const char*)&i_pbyInData[nCount], nSize);						// "PRF踰붿쐞[PPS]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strMaxPrf.SetString((const char*)&i_pbyInData[nCount], nSize);						// "PRF踰붿쐞[PPS]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strPulsePerGrp.SetString((const char*)&i_pbyInData[nCount], nSize);					// "�럡�뒪�닔/洹몃９",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strSJ.SetString((const char*)&i_pbyInData[nCount], nSize);									// "S/J",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strScanTypePeroid.SetString((const char*)&i_pbyInData[nCount], nSize);			// "�뒪罹뷀삎�깭/二쇨린",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strAirElintNotation.SetString((const char*)&i_pbyInData[nCount], nSize);		// "[A]E-NOT",
//		nCount+=nSize;
//
//		//memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		//nCount+=sizeof(USHORT);
//		//strAirPinNr.SetString((const char*)&i_pbyInData[nCount], nSize);						// "[A]PIN NR",
//		//nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strAirFunc.SetString((const char*)&i_pbyInData[nCount], nSize);							// "[A]湲곕뒫遺��샇",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strAirSiteFunc.SetString((const char*)&i_pbyInData[nCount], nSize);					// "[A]�궗�씠�듃湲곕뒫",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strAirThreat.SetString((const char*)&i_pbyInData[nCount], nSize);						// "[A]�쐞�삊",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strAirEqupNo.SetString((const char*)&i_pbyInData[nCount], nSize);						// "[A]�옣鍮꾨쾲�샇",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strAirConsistancy.SetString((const char*)&i_pbyInData[nCount], nSize);			// "[A]�씪移섏쑉[%]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strAirGeoCoord.SetString((const char*)&i_pbyInData[nCount], nSize);					// "[A]吏�由ъ쥖�몴",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strAirAlt.SetString((const char*)&i_pbyInData[nCount], nSize);							// "[A]怨좊룄[m]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strAirConfIterval.SetString((const char*)&i_pbyInData[nCount], nSize);			// "[A]�떊猶곌뎄媛�[m]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strAirCep.SetString((const char*)&i_pbyInData[nCount], nSize);							// "[A]CEP[m]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strAirMajorAxis.SetString((const char*)&i_pbyInData[nCount], nSize);				// "[A]�옣異�[m]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strAirMinorAxis.SetString((const char*)&i_pbyInData[nCount], nSize);				//"[A]�떒異�(m)",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strAirMajorAxisAzimuth.SetString((const char*)&i_pbyInData[nCount], nSize); //"[A]�옣異뺣갑�쐞[�룄]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strGndElintNotation.SetString((const char*)&i_pbyInData[nCount], nSize);		// "[G]E-NOT",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strGndPinNr.SetString((const char*)&i_pbyInData[nCount], nSize);						// "[G]PIN NR",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strGndFunc.SetString((const char*)&i_pbyInData[nCount], nSize);							// "[G]湲곕뒫遺��샇",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strGndSiteFunc.SetString((const char*)&i_pbyInData[nCount], nSize);					// "[G]�궗�씠�듃湲곕뒫",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strGndThreat.SetString((const char*)&i_pbyInData[nCount], nSize);						// "[G]�쐞�삊",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strGndEqupNo.SetString((const char*)&i_pbyInData[nCount], nSize);						// "[G]�옣鍮꾨쾲�샇",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strGndConsistancy.SetString((const char*)&i_pbyInData[nCount], nSize);			// "[G]�씪移섏쑉[%]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strGndGeoLongitude.SetString((const char*)&i_pbyInData[nCount], nSize);			//"[G]吏�由ъ쥖�몴(寃쎈룄)",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strGndGeoLatitude.SetString((const char*)&i_pbyInData[nCount], nSize);			//"[G]吏�由ъ쥖�몴(�쐞�룄)",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strGndAlt.SetString((const char*)&i_pbyInData[nCount], nSize);							// "[G]怨좊룄[m]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strGndConfIterval.SetString((const char*)&i_pbyInData[nCount], nSize);			// "[G]�떊猶곌뎄媛�[m]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strGndCep.SetString((const char*)&i_pbyInData[nCount], nSize);							// "[G]CEP[m]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strGndMajorAxis.SetString((const char*)&i_pbyInData[nCount], nSize);				// "[G]�옣異�[m]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strGndMinorAxis.SetString((const char*)&i_pbyInData[nCount], nSize);				//"[G]�떒異�(m)",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strGndMajorAxisAzimuth.SetString((const char*)&i_pbyInData[nCount], nSize); //"[G]�옣異뺣갑�쐞[�룄]",			
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strFinalReport.SetString((const char*)&i_pbyInData[nCount], nSize);					// "理쒖쥌蹂닿퀬",			
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strFinalAlarm.SetString((const char*)&i_pbyInData[nCount], nSize);					// "理쒖쥌寃쎈낫",							",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strPosEstimation.SetString((const char*)&i_pbyInData[nCount], nSize);				// "�궛異쒖뿬遺�",							
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strSOI.SetString((const char*)&i_pbyInData[nCount], nSize);									// "愿��떖�떊�샇"	
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strIsStorePDW.SetString((const char*)&i_pbyInData[nCount], nSize);					// "PDW ���옣�뿬遺�"
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strNumOfCol.SetString((const char*)&i_pbyInData[nCount], nSize);						// "�닔吏묎컻�닔[PDW/IQ]"
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strNumOfAmbigiousBeam.SetString((const char*)&i_pbyInData[nCount], nSize);	// "紐⑦샇�꽦",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strNumOfPDWSet.SetString((const char*)&i_pbyInData[nCount], nSize);					// "PDW �꽭�듃"
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strIdCode.SetString((const char*)&i_pbyInData[nCount], nSize);							// "�떇蹂� 肄붾뱶"
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strPolization.SetString((const char*)&i_pbyInData[nCount], nSize);					// "洹뱀꽦"
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strTaskOperator.SetString((const char*)&i_pbyInData[nCount], nSize);		// "怨쇱젣 �슫�슜�궗"
//		nCount+=nSize;
//
//	}
//	int stEmitterInfo::GetInterCommInfo(BYTE * i_pbyOutData)
//	{
//		int nCount=0;
//		USHORT nSize=0;
//		
//		nSize=strLinkNum.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strLinkNum.GetBuffer(), nSize);								// "SDF ID";
//		nCount+=nSize;
//		
//		nSize=strEmitterNum.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strEmitterNum.GetBuffer(), nSize);					// "諛⑹궗泥대쾲�샇",
//		nCount+=nSize;
//
//		nSize=strSignalNum.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strSignalNum.GetBuffer(), nSize);						// "�떊�샇�씪�젴踰덊샇",
//		nCount+=nSize;
//
//		nSize=strMissionId.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strMissionId.GetBuffer(), nSize);						// "�엫臾대챸",
//		nCount+=nSize;
//
//		nSize=strTaskId.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strTaskId.GetBuffer(), nSize);							// "怨쇱젣ID",
//		nCount+=nSize;
//
//		nSize=strSrchBandId.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strSrchBandId.GetBuffer(), nSize);					// "�깘�깋���뿭 id"
//		nCount+=nSize;
//
//		nSize=strDirection.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strDirection.GetBuffer(), nSize);						// "諛⑹쐞[�룄]",
//		nCount+=nSize;
//
//		nSize=strDirectionDev.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strDirectionDev.GetBuffer(), nSize);				// "諛⑹쐞�렪李�[�룄]",
//		nCount+=nSize;
//
//		nSize=strFisintTask.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strFisintTask.GetBuffer(), nSize);					// "FISINT怨쇱젣",
//		nCount+=nSize;
//
//		nSize=strFrqType.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strFrqType.GetBuffer(), nSize);				// "二쇳뙆�닔�삎�깭",
//		nCount+=nSize;
//
//		nSize=strFrq.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strFrq.GetBuffer(), nSize);				// "二쇳뙆�닔[Hz]",
//		nCount+=nSize;
//
//		nSize=strMinFrq.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strMinFrq.GetBuffer(), nSize);				// "理쒖냼 二쇳뙆�닔",
//		nCount+=nSize;
//
//		nSize=strMaxFrq.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strMaxFrq.GetBuffer(), nSize);				// "理쒕� 二쇳뙆�닔",
//		nCount+=nSize;
//
//		nSize=strFrqPatternRange.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strFrqPatternRange.GetBuffer(), nSize);			// "二쇳뙆�닔�뙣�꽩�삎�깭/踰붿쐞[ms]",
//		nCount+=nSize;
//
//		nSize=strFrqRangeDev.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strFrqRangeDev.GetBuffer(), nSize);					// "二쇳뙆�닔�렪李�[Hz]",
//		nCount+=nSize;
//
//		nSize=strPriority.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strPriority.GetBuffer(), nSize);						// "�슦�꽑�닚�쐞",
//		nCount+=nSize;
//
//		nSize=strTime.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strTime.GetBuffer(), nSize);								// "�씪�옄/�떆媛�",
//		nCount+=nSize;
//
//		nSize=strModType.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strModType.GetBuffer(), nSize);							// "蹂�議고삎�깭",
//		nCount+=nSize;
//
//		nSize=strSigType.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strSigType.GetBuffer(), nSize);							// "�떊�샇�삎�깭",
//		nCount+=nSize;
//
//		nSize=strPw.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strPw.GetBuffer(), nSize);							// "PW踰붿쐞[ns]",
//		nCount+=nSize;
//
//		nSize=strMinPw.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strMinPw.GetBuffer(), nSize);							// "PW踰붿쐞[ns]",
//		nCount+=nSize;
//
//		nSize=strMaxPw.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strMaxPw.GetBuffer(), nSize);							// "PW踰붿쐞[ns]",
//		nCount+=nSize;
//
//		nSize=strPa.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strPa.GetBuffer(), nSize);							// "PA踰붿쐞[dB]",
//		nCount+=nSize;
//
//		nSize=strMinPa.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strMinPa.GetBuffer(), nSize);							// "PA踰붿쐞[dB]",
//		nCount+=nSize;
//
//		nSize=strMaxPa.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strMaxPa.GetBuffer(), nSize);							// "PA踰붿쐞[dB]",
//		nCount+=nSize;
//
//		nSize=strLinkNum.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strPriType.GetBuffer(), nSize);							// "PRI�삎�깭",
//		nCount+=nSize;
//
//		nSize=strLinkNum.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strPri.GetBuffer(), nSize);									// "PRI[ns]",
//		nCount+=nSize;
//
//		nSize=strLinkNum.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strMinPri.GetBuffer(), nSize);							// "理쒖냼 PRI[ns]",
//		nCount+=nSize;
//
//		nSize=strLinkNum.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strMaxPri.GetBuffer(), nSize);							// "理쒕� PRI[ns]",
//		nCount+=nSize;
//
//		nSize=strPRIPatternRange.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strPRIPatternRange.GetBuffer(), nSize);			// "PRI�뙣�꽩�삎�깭/踰붿쐞[ns]",
//		nCount+=nSize;
//
//		nSize=strPrf.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strPrf.GetBuffer(), nSize);						// "PRF踰붿쐞[PPS]",
//		nCount+=nSize;
//
//		nSize=strMinPrf.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strMinPrf.GetBuffer(), nSize);						// "PRF踰붿쐞[PPS]",
//		nCount+=nSize;
//
//		nSize=strMaxPrf.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strMaxPrf.GetBuffer(), nSize);						// "PRF踰붿쐞[PPS]",
//		nCount+=nSize;
//
//		nSize=strPulsePerGrp.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strPulsePerGrp.GetBuffer(), nSize);					// "�럡�뒪�닔/洹몃９",
//		nCount+=nSize;
//
//		nSize=strSJ.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strSJ.GetBuffer(), nSize);									// "S/J",
//		nCount+=nSize;
//
//		nSize=strScanTypePeroid.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strScanTypePeroid.GetBuffer(), nSize);			// "�뒪罹뷀삎�깭/二쇨린",
//		nCount+=nSize;
//
//		nSize=strAirElintNotation.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strAirElintNotation.GetBuffer(), nSize);		// "[A]E-NOT",
//		nCount+=nSize;
//
//// 		nSize=strAirPinNr.GetLength();
//// 		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//// 		nCount+=sizeof(USHORT);
//// 		memcpy(&i_pbyOutData[nCount], strAirPinNr.GetBuffer(), nSize);						// "[A]PIN NR",
//// 		nCount+=nSize;
//
//		nSize=strAirFunc.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strAirFunc.GetBuffer(), nSize);							// "[A]湲곕뒫遺��샇",
//		nCount+=nSize;
//
//		nSize=strAirSiteFunc.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strAirSiteFunc.GetBuffer(), nSize);					// "[A]�궗�씠�듃湲곕뒫",
//		nCount+=nSize;
//
//		nSize=strAirThreat.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strAirThreat.GetBuffer(), nSize);						// "[A]�쐞�삊",
//		nCount+=nSize;
//
//		nSize=strAirEqupNo.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strAirEqupNo.GetBuffer(), nSize);						// "[A]�옣鍮꾨쾲�샇",
//		nCount+=nSize;
//
//		nSize=strAirConsistancy.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strAirConsistancy.GetBuffer(), nSize);			// "[A]�씪移섏쑉[%]",
//		nCount+=nSize;
//
//		nSize=strAirGeoCoord.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strAirGeoCoord.GetBuffer(), nSize);					// "[A]吏�由ъ쥖�몴",
//		nCount+=nSize;
//
//		nSize=strAirAlt.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strAirAlt.GetBuffer(), nSize);							// "[A]怨좊룄[m]",
//		nCount+=nSize;
//
//		nSize=strAirConfIterval.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strAirConfIterval.GetBuffer(), nSize);			// "[A]�떊猶곌뎄媛�[m]",
//		nCount+=nSize;
//
//		nSize=strAirCep.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strAirCep.GetBuffer(), nSize);							// "[A]CEP[m]",
//		nCount+=nSize;
//
//		nSize=strAirMajorAxis.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strAirMajorAxis.GetBuffer(), nSize);				// "[A]�옣異�[m]",
//		nCount+=nSize;
//
//		nSize=strAirMinorAxis.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strAirMinorAxis.GetBuffer(), nSize);				//"[A]�떒異�(m)",
//		nCount+=nSize;
//
//		nSize=strAirMajorAxisAzimuth.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strAirMajorAxisAzimuth.GetBuffer(), nSize); //"[A]�옣異뺣갑�쐞[�룄]",
//		nCount+=nSize;
//
//		nSize=strGndElintNotation.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strGndElintNotation.GetBuffer(), nSize);		// "[G]E-NOT",
//		nCount+=nSize;
//
//		nSize=strGndPinNr.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strGndPinNr.GetBuffer(), nSize);						// "[G]PIN NR",
//		nCount+=nSize;
//
//		nSize=strGndFunc.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strGndFunc.GetBuffer(), nSize);							// "[G]湲곕뒫遺��샇",
//		nCount+=nSize;
//
//		nSize=strGndSiteFunc.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strGndSiteFunc.GetBuffer(), nSize);					// "[G]�궗�씠�듃湲곕뒫",
//		nCount+=nSize;
//
//		nSize=strGndThreat.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strGndThreat.GetBuffer(), nSize);						// "[G]�쐞�삊",
//		nCount+=nSize;
//
//		nSize=strLinkNum.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strGndEqupNo.GetBuffer(), nSize);						// "[G]�옣鍮꾨쾲�샇",
//		nCount+=nSize;
//
//		nSize=strGndConsistancy.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strGndConsistancy.GetBuffer(), nSize);			// "[G]�씪移섏쑉[%]",
//		nCount+=nSize;
//
//		nSize=strGndGeoLatitude.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strGndGeoLatitude.GetBuffer(), nSize);					//"[G]吏�由ъ쥖�몴",
//		nCount+=nSize;
//
//		nSize=strGndGeoLongitude.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strGndGeoLongitude.GetBuffer(), nSize);					//"[G]吏�由ъ쥖�몴",
//		nCount+=nSize;
//
//		nSize=strGndAlt.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strGndAlt.GetBuffer(), nSize);							// "[G]怨좊룄[m]",
//		nCount+=nSize;
//
//		nSize=strGndConfIterval.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strGndConfIterval.GetBuffer(), nSize);			// "[G]�떊猶곌뎄媛�[m]",
//		nCount+=nSize;
//
//		nSize=strGndCep.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strGndCep.GetBuffer(), nSize);							// "[G]CEP[m]",
//		nCount+=nSize;
//
//		nSize=strGndMajorAxis.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strGndMajorAxis.GetBuffer(), nSize);				// "[G]�옣異�[m]",
//		nCount+=nSize;
//
//		nSize=strGndMinorAxis.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strGndMinorAxis.GetBuffer(), nSize);				//"[G]�떒異�(m)",
//		nCount+=nSize;
//
//		nSize=strGndMajorAxisAzimuth.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strGndMajorAxisAzimuth.GetBuffer(), nSize); //"[G]�옣異뺣갑�쐞[�룄]",			
//		nCount+=nSize;
//
//		nSize=strFinalReport.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strFinalReport.GetBuffer(), nSize);					// "理쒖쥌蹂닿퀬",			
//		nCount+=nSize;
//		
//		nSize=strFinalAlarm.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strFinalAlarm.GetBuffer(), nSize);					// "理쒖쥌寃쎈낫",							",
//		nCount+=nSize;
//
//		nSize=strPosEstimation.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strPosEstimation.GetBuffer(), nSize);				// "�궛異쒖뿬遺�",							
//		nCount+=nSize;
//
//		nSize=strSOI.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strSOI.GetBuffer(), nSize);									// "愿��떖�떊�샇"	
//		nCount+=nSize;
//						
//		nSize=strIsStorePDW.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strIsStorePDW.GetBuffer(), nSize);					// "PDW ���옣�뿬遺�"
//		nCount+=nSize;
//
//		nSize=strNumOfCol.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strNumOfCol.GetBuffer(), nSize);						// "�닔吏묎컻�닔[PDW/IQ]"
//		nCount+=nSize;
//
//		nSize=strNumOfAmbigiousBeam.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strNumOfAmbigiousBeam.GetBuffer(), nSize);	// "紐⑦샇�꽦",
//		nCount+=nSize;
//
//		nSize=strNumOfPDWSet.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strNumOfPDWSet.GetBuffer(), nSize);					// "PDW �꽭�듃"
//		nCount+=nSize;
//
//		nSize=strActivatedOrNot.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strActivatedOrNot.GetBuffer(), nSize);					// "�솢�룞�뿬遺�"
//		nCount+=nSize;
//
//		nSize=strLobId.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strLobId.GetBuffer(), nSize);					// "LOB ID"
//		nCount+=nSize;
//
//		nSize=strDtctId.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strDtctId.GetBuffer(), nSize);					// "DTCT ID"
//		nCount+=nSize;
//
//		nSize=strIdCode.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strIdCode.GetBuffer(), nSize);					// "�떇蹂꾩퐫�뱶"
//		nCount+=nSize;
//
//		nSize=strPolization.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strPolization.GetBuffer(), nSize);			// "洹뱀꽦"
//		nCount+=nSize;
//
//		nSize=strTaskOperator.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strPolization.GetBuffer(), nSize);			// "怨쇱젣 �슫�슜�궗"
//		nCount+=nSize;
//
//		return nCount;
//	}
} I_EMITTER_STR;		

#define NUM_OF_LOB_LIST_FIELD_NAME 45
// static const char* strLobListFieldName [] =
// {
// 	"�닚踰�",
// 	"LINK踰덊샇", // 2015.1.5. �씠�젙�궓 異붽�
// 	"E-NOT",
// 	"�떇蹂꾩퐫�뱶",
// 	"怨쇱젣 �슫�슜�궗",
// 	"�씪�옄/�떆媛�",
// 	"LOB#",
// 	"AET踰덊샇",
// 	"�씤�듃�씪�럡�뒪 蹂�議고삎�깭",
// 	"二쇳뙆�닔�삎�깭",
// 	"二쇳뙆�닔[MHz]",
// 	"理쒖냼 二쇳뙆�닔[MHz]",
// 	"理쒕� 二쇳뙆�닔[MHz]",
// 	"PW[us]",
// 	"PRI[us]",
// 	"PRF[KHz]",
// 	"洹몃９�떦�럡�뒪�닔",
// 	"PIT",
// 	"�룷吏��뀡�닔",
// 	"AMP",
// 	"RF Dev[MHz]",
// 	"DOA",
// 	"AOA",
// 	"AzStdDev",
// 	"AMB",
// 	"Sid",
// 	"BL",
// 	"FOV",
// 	"AC#",
// 	"AC�쐞移�",
// 	"AC Alt",
// 	"AC FOM",
// 	"Hdg",
// 	"Pitch",
// 	"Roll",
// 	"�뭹吏�",
// 	"PDW 媛쒖닔",
// 	"�뒪罹뷀삎�깭/二쇨린[ms]",
// 	"PRI蹂�議고삎�깭",
// 	"PRI吏��꽣�쑉",
// 	"理쒖쥌蹂닿퀬",
// 	"怨쇱젣ID",
// 	"�떊�샇ID",
// 	"遺꾧레",
// 	"�럡�뒪�닔 洹몃９"
// };

typedef struct stLOBInfoDisp
{
	bool bIsSelected;
	CString strElintNotation;	// "ELINT Notation"
	CString strLinkNum;	   //#FA_Q_2502_T1		// Link 踰덊샇, 2015.1.5. �씠�젙�궓 異붽�
	CString strSrchTime;			// 	"�씪�옄/�떆媛�"
	CString strLobNum;			// "LOB#"
	CString strEmitterNum;		// "Emitter#"
	CString strModType;			// "蹂�議고삎�깭"
	CString strFrqType;			// "二쇳뙆�닔�삎�깭",
	CString strFrq;					// "二쇳뙆�닔[Hz]",
	CString strMinFrq;				// "理쒖냼 二쇳뙆�닔[Hz]",
	CString strMaxFrq;			// "理쒕� 二쇳뙆�닔[Hz]",
	CString strPW;					// "PW",
	CString strPRI;					// "PRI",
	CString strPRF;					// "PRF",
	CString strMinPRF;			// "理쒖냼 PRF[PPS]",
	CString strMaxPRF;			// "理쒕� PRF[PPS]",
	CString strPulsePerGrp;		// "洹몃９�떦�럡�뒪�닔",
	CString strPIT;					// "PIT",
	CString strNumOfPos;		// "�룷吏��뀡�닔",
	CString strAmp;				// "AMP",
	CString strRfDev;				// "RF Dev.",
	CString strDoa;				// "DOA",
	CString strAoa;				// "AOA",
	CString strAzStdDev;		// "AzStdDev",
	CString strAmb	;				// "AMB",
	CString strSid;					// "Sid",
	CString strBL;					// "BL",
	CString strFov;				// "FOV",
	CString strACNum;			// "AC#",
	CString strACPos;				// "AC�쐞移�",
	CString strACAlt;				//"AC Alt",
	CString strAcFom;			// "AC FOM",
	CString strHdg;				// "Hdg",
	CString strPitch;				// "Pitch",
	CString strRoll;					// "Roll",
	CString strQuality;			// "�뭹吏�",
	CString strNumOfPdw;		// "PDW 媛쒖닔",
	CString strScanTypePeriod;// "�뒪罹뷀삎�깭/二쇨린",
	CString strPriModType;		// "PRI蹂�議고삎�깭",
	CString strPriJitterRate;		//"PRI吏��꽣�쑉"
	CString strFinalReport;		// "理쒖쥌蹂닿퀬"
	CString strTaskId;				// "怨쇱젣ID" 2014.10.08 異붽�. �씠�젙�궓.
	CString strTaskName;			// "怨쇱젣紐�" 2015.06.03 異붽�. 議곗쿋�씗
	CString strDtctId;				// DTCT ID . 2015.3.3. �씠�젙�궓 異붽�
	CString strIdCode;				// �떇蹂� 肄붾뱶, 2015.4.2. 議곗쿋�씗 異붽�
	CString strTaskOperator;	// 怨쇱젣 �슫�슜�옄, 2015.4.7. 議곗쿋�씗 異붽�
	CString strPolization;	// 洹뱀꽦. 2015.7.15. �씠�젙�궓 異붽�
	CString strPPG;	// �럡�뒪�닔 洹몃９. 2015.7.15. �씠�젙�궓 異붽�

        stLOBInfoDisp()
		:bIsSelected(false)
	{
		strElintNotation="";
		strLinkNum="";			
		strSrchTime="";			
		strLobNum="";			
		strEmitterNum="";		
		strModType="";			
		strFrqType="";					
		strFrq="";							
		strMinFrq="";						
		strMaxFrq="";					
		strPW="";					
		strPRI="";					
		strPRF="";				
		strMinPRF="";			
		strMaxPRF="";			
		strPulsePerGrp="";		
		strPIT="";					
		strNumOfPos="";		
		strAmp="";				
		strRfDev="";				
		strDoa="";				
		strAoa="";				
		strAzStdDev="";		
		strAmb="";				
		strSid="";					
		strBL="";					
		strFov="";				
		strACNum="";			
		strACPos="";				
		strACAlt="";				
		strAcFom="";			
		strHdg="";				
		strPitch="";				
		strRoll="";					
		strQuality="";			
		strNumOfPdw="";		
		strScanTypePeriod="";
		strPriModType="";		
		strPriJitterRate="";		
		strFinalReport="";		
		strTaskId="";				
		strTaskName="";		
		strDtctId="";				
		strIdCode="";			
		strTaskOperator="";	
		strPolization="";
		strPPG="";
	};
}I_LOB_STR;	

// RAW DATA : PDW �뜲�씠�꽣 ���엯
#define NUM_OF_PDW_HEAD_FIELD_NAME 9
// static const char *strPdwHeadFieldName[] = {
// 	"�닚踰�",
// 	"踰덊샇",
// 	/*"PDW Set ID",*/
// 	"LINK踰덊샇",
// 	"怨쇱젣 ID",
// 	"�깘�깋���뿭踰덊샇",
// 	/*"諛⑹궗泥� 踰덊샇",*/
// 	/*"鍮� 踰덊샇",*/
// 	"LOB 踰덊샇",
// 	"�깦�뵆媛쒖닔",
// 	"�뿰愿� �럡�뒪 踰덊샇",
// 	"�삎�깭"
// };
// 
#define NUM_OF_PDW_BODY_FIELD_NAME 19
// static const char *strPdwBodyFieldName[] = {
// 	"�닔吏묒떆�옉�떆媛�",
// 	"�룊洹� DTOA[us]",
// 	"�떊�샇�삎�깭",
// 	"洹뱀꽦 �쑀�슚�꽦[%]",
// 	/*"FMOP[%]",
// 	"PMOP[%]",*/
// 	"Blanking[%]",
// 	//"梨꾨꼸蹂�寃쎌뿬遺�",
// 	/*"BLK[%]",*/
// 	"DV[%]",
// 	"FOV(IN)[%]",
// 	"Ch#",
// 	"�룊洹� �꽭湲�[dBm]",
// 	"�룊洹� 二쇳뙆�닔[MHz]",
// 	"�룊洹� 諛⑺뼢[�룄]",
// 	"洹뱀꽦[%]",
// 	"PPF",
// 	"�룊洹� �럡�뒪�룺[ns]",
// 	//"I �뜲�씠�꽣",
// 	//"Q �뜲�씠�꽣",
// 	"PRF ID",
// 	"Spectrum ID",
// 	//"DtctId",
// 	//"怨쇱젣 �슫�슜�궗",
// 	"�뙆�씪紐�",
// 	"怨쇱젣紐�",
// 	"遺� �뙆�씪紐�"
// };

struct I_PDWIQIF_STR
{
	CString strPdwSetId; // "PDW Set ID",
	CString strLinkNum; //#FA_Q_2502_T1     // "Link 踰덊샇",
	CString strTaskId; // "怨쇱젣 ID",
	CString strSrchBandId; // "�깘�깋���뿭踰덊샇",
	CString strAetNum; // "AET 踰덊샇"
	CString strAbtNum; //"ABT 踰덊샇". 2016.6.8. �씠�젙�궓 異붽�
	CString strLobNum; // "LOB踰덊샇",
	CString strPdwCount; // "PDW媛쒖닔/IQ媛쒖닔",
	CString strPdwId; // PDW ID, PDW �뿰愿� 踰덊샇
	CString strDataType; // "�삎�떇", : PDW, IQ, IF
	CString strTime; // "�닔吏묒떆�옉�떆媛�",
	CString strToa; // "TOA",
	CString strSignalType; // "�떊�샇�삎�깭",
	//CString strBitFlag; //"BIT Flag",
	CString strPolFlag; //"洹뱀꽦 �쑀�슚�꽦",
	CString strFmopFlag; // "FMOP Flag",
	CString strPmopFlag; // "PMOP Flag",
	CString strBlankingTag; // "Blanking Tag",
	CString strChannelChangePOP; // "梨꾨꼸蹂�寃쎌뿬遺�",
	CString strBLK; // "梨꾨꼸蹂�寃쎈갑�뼢",
	CString strDI; //"DI",
	CString strFovFlag; // "FOV Flag",
	CString strChannelNum; // "Ch#",
	CString strPa; // "�떊�샇�꽭湲�",
	CString strFrq; // "痢≪젙二쇳뙆�닔",
	CString strSigDirection; // "�떊�샇諛⑺뼢",
	CString strPolarization; // "�떊�샇洹뱀꽦",
	CString strPPFTag; // "PPF Tag",
	CString strPw; // "�럡�뒪�룺",
	CString strIData; // "I�뜲�씠�꽣"
	CString strQData; // "Q�뜲�씠�꽣",	
	CString strFilename;		// �뙆�씪紐꿂String strDtctId; // DTCT ID
	CString strTaskName;
	CString strFatherFilename;
	CString strDtctId; // "DTCT ID", 2015.3.3. �씠�젙�궓 異붽�
		
	UINT nPRFDBSetID;	//�솕硫댄몴�떆�븞�맖, PRF 紐⑸줉-DB�쓽 �떇蹂� ID濡쒕쭔 �궗�슜
	UINT nSpectrumDBSetID;	//�솕硫댄몴�떆�븞�맖, Spectrum 紐⑸줉-DB�쓽 �떇蹂� ID濡쒕쭔 �궗�슜
	
	//@start_WJH
	I_PDWIQIF_STR()
	{	
	//	strPdwSetId= _T("");
	//	strLinkNum=_T("");// "Link 踰덊샇",
	//	strTaskId=_T("");		 // "怨쇱젣 ID",
	//	strSrchBandId=_T(""); // "�깘�깋���뿭踰덊샇",
	//	strAetNum=_T(""); // "AET 踰덊샇"
	//	strAbtNum=_T(""); // "ABT 踰덊샇". 2016.6.8. �씠�젙�궓 異붽�
	//	strLobNum=_T(""); // "LOB踰덊샇",
	//	strPdwCount=_T(""); // "PDW媛쒖닔/IQ媛쒖닔",
	//	strPdwId=_T(""); // PDW ID, PDW �뿰愿� 踰덊샇
	//	strDataType=_T(""); // "�삎�떇", : PDW, IQ, IF
	//	strTime=_T(""); // "�닔吏묒떆�옉�떆媛�",
	//	strToa=_T(""); // "TOA",
	//	strSignalType=_T(""); // "�떊�샇�삎�깭",
	//	strBitFlag=_T(""); //"BIT Flag",
	//	strFmopFlag=_T(""); // "FMOP Flag",
	//	strPmopFlag=_T(""); // "PMOP Flag",
	//	strBlankingTag=_T(""); // "Blanking Tag",
	//	strChannelChangePOP=_T(""); // "梨꾨꼸蹂�寃쎌뿬遺�",
	//	strBLK=_T(""); // "梨꾨꼸蹂�寃쎈갑�뼢",
	//	strDI=_T(""); //"DI",
	//	strFovFlag=_T(""); // "FOV Flag",
	//	strChannelNum=_T(""); // "Ch#",
	//	strPa=_T(""); // "�떊�샇�꽭湲�",
	//	strFrq=_T(""); // "痢≪젙二쇳뙆�닔",
	//	strSigDirection=_T(""); // "�떊�샇諛⑺뼢",
	//	strPolarization=_T(""); // "�떊�샇洹뱀꽦",
	//	strPPFTag=_T(""); // "PPF Tag",
	//	strPw=_T(""); // "�럡�뒪�룺",
	//	strIData=_T(""); // "I�뜲�씠�꽣"
	//	strQData=_T(""); // "Q�뜲�씠�꽣",	
	//	strFilename=_T("");		// �뙆�씪紐�		
	//	strTaskName=_T(""); // DTCT ID				
	//	strFatherFilename=_T("");
		strDtctId=_T(""); // DTCT ID		

		nPRFDBSetID = 0;
		nSpectrumDBSetID = 0;	
	}	  
	//@end_WJH
} ;



//////////////////////////////////////////////////////////////////////////
// �떇蹂� 寃곌낵 �뜲�씠�꽣 援ъ“泥� �젙�쓽
//
#define NUM_OF_IDRESULT_BODY_FIELD_NAME			28
// static const char *strIdResultBodyFieldName[] = {
// 	"�닚踰�",
// 	"�떇蹂� ���긽",
// 	"�떇蹂� �썑蹂�(CED)",
// 	"ELNOT",
// 	"Primary Function"
// 	"�쐞�삊紐�",
// 	"T �슦�꽑�닚�쐞",
// 	"�쐞�삊踰덊샇",
// 	"�쟻�븘援щ텇",
// 	"�뿉誘명꽣紐�",
// 	"理쒕��쐞�삊諛섍꼍[km]",
// 	"E �슦�꽑�닚�쐞",
// 	"�뿉誘명꽣踰덊샇",
// 	"�뵆�옯�뤌",
// 	"鍮붾챸",
// 	"B �슦�꽑�닚�쐞",
// 	"�떊�샇�삎�깭",
// 	"MOP�삎�떇",
// 	"二쇳뙆�닔 �삎�깭 諛� 踰붿쐞",
// 	"PRI �삎�깭 諛� 踰붿쐞",
// 	"�럡�뒪�룺 踰붿쐞",
// 	"�뒪罹� �삎�깭/踰붿쐞",
// 	"洹뱀꽦",
// 	"鍮뷀룺",
// 	"鍮붾쾲�샇",
// 	"ELIMENT �뜲�씠�꽣/�닔",
// 	"�떇蹂� �썑蹂�(EOB)",
// 	"EOB"
// };

typedef struct stIdResultInfoStr
{
	int iBeamId;										// "�닚踰�",
	int nLinkNo;										// 留곹겕 踰덊샇
	CString strCreateTime;					// �닔吏� �떆媛�
	CString strIdRatio;							//"�씪移섏쑉"
	CString strIdObject;						// "�떇蹂� ���긽",
	CString strIdCandidate;					// "�떇蹂� �썑蹂� 踰덊샇",
	CString strElNot;								// "ELNOT",
	CString strPriFunc;							// "Primary Function",
	CString strThreatName;					// "�쐞�삊紐�",
	CString strPriority;						// "T �슦�꽑�닚�쐞",
	CString strThreatNum;						// "�쐞�삊踰덊샇",
	CString strFriendOrFoe;					// "�쟻�븘援щ텇",
	CString strEmitterName;					//"�뿉誘명꽣紐�",
	CString strMaxRadius;						//"理쒕��쐞�삊諛섍꼍",
	CString strEPriority;						//"E �슦�꽑�닚�쐞",
	CString strEmitterNum;					//"�뿉誘명꽣踰덊샇",
	CString strPlatform;						//"�뵆�젢�뤌",
	CString strBeamName;						//"鍮붾챸",
	CString strBPriority;						//"B �슦�꽑�닚�쐞",
	CString strSigType;		//#FA_Q_2502_T1					//"�떊�샇�삎�깭",
	CString strMopType;							//"MOP�삎�떇",
	CString strFreqGroup;						//"RF �삎�깭/理쒕�",
	CString strPRIGroup;						//"PRI �삎�깭/踰붿쐞",
	CString strPWGroup;							//"�럡�뒪�룺 踰붿쐞",		
	CString strASPGroup;						//"�뒪罹� �삎�깭/踰붿쐞",
	CString strPolarity;						//"洹뱀꽦",
	CString strBeamWidth;						//"鍮뷀룺",
	CString strEtc;									//"湲고�",
	short sEOBId;										//"�떇蹂� (EOB)"
	float fEOBErrorDistance;				//"嫄곕━ �삤李�",
	unsigned int uiEOBPinNumber;		//"PIN #"
	CString strEOBBaseName;					//"吏�紐�",
	CString strFunctionCode;				//"援щ텇",
	CString strFacilityName;				//"�떆�꽕�씠由�",
	CString strSiteStatus;					//"Site�긽�깭",
	CString strLongitude;						//"寃쎈룄[�룄]",
	CString strLatitude;						//"�쐞�룄[�룄]",
	float fElivation;								//"怨좊룄[km]",
	CString strADA;									//"諛⑷났援ъ뿭",
	CString strBENumber;						//"BE #",
	CString strCategory;						//"移댄뀒怨좊━",
	CString strPrimaryFunction;			//"PF(EOB)",
	CString strNomenclature;				//"紐낅챸踰�",
	CString strElintNotation;				//"ELNOT(EOB)",
	CString strEquipStatus;							//"�옣鍮꾩긽�깭",

	stIdResultInfoStr() :	iBeamId(0), sEOBId(0), uiEOBPinNumber(0)
	{}
} I_IDRESULT_STR;


//=======> �씠�븯 �궗�슜�븞�븷 �삁�젙
						  
											
struct I_THREAT_DATA {
	unsigned short usSdfId;
	unsigned char szTaskId[LENGTH_OF_TASK_ID];
	unsigned short usSearchBandId;
	unsigned short usSerialNum;
	unsigned char ucAnalysisStatus;
    I_THREAT_DATA(){
		usSdfId=0;
		memset(&szTaskId, 0, LENGTH_OF_TASK_ID);
		usSearchBandId=0;
		usSerialNum=0;
		ucAnalysisStatus=0;
	}
};

//static const I_THREAT_DATA stInitThreatData;

struct I_AET_DATA {
	unsigned short usAetId;
 	unsigned short usThreatId;
 	unsigned short usEmitterId;
 	unsigned short usBeamId;

#ifdef _ELINT_
	LONG lOpInitID;
	unsigned char	aucTaskID[LENGTH_OF_TASK_ID];
#endif

};

//static const I_AET_DATA g_stInitAETData;

/*
static const char* strIdResult[] = 
{
	"-",
	"湲곗꽦",
	"�떊異�",
	"遺덈챸"
}; */
enum EnumIdResult
{
	E_EL_PE_UNK_ID=0,
	E_EL_OLD_ID=1,						// 湲곗꽦
	E_EL_NEW_ID,							// �떊異�
	E_EL_UNK_ID								// 遺덈챸
};

struct STR_CEDEOBID_INFO {
	EnumIdResult eIdResult;					// 0=湲곗꽦, 1=�떊異�, 2=遺덈챸

	// CED�쓽 �젅�씠�뜑 紐⑤뱶 �씤�뜳�뒪
	int nCoRadarModeIndex;
	int nRadarModeIndex[MAX_IDCANDIDATE];

    int n3LevelRadarModeIndex[THREE_LEVEL_IDCANDIDATE];

	// CED�쓽 �젅�씠�뜑 �씤�뜳�뒪
	//int nCoRadarIndex;
	//int nRadarIndex[MAX_IDCANDIDATE];

	// EOB�쓽 �쐞�삊/�옣移� �씤�뜳�뒪
	int nThreatIndex;
	int nDeviceIndex;

// 	STR_CEDEOBID_INFO::STR_CEDEOBID_INFO() : eIdResult(E_EL_OLD_ID), nCoRadarModeIndex(0), nCoRadarIndex(0), nThreatIndex(0), nDeviceIndex(0)
// 	{
// 		memset( nRadarModeIndex, 0, sizeof(nRadarModeIndex) );
// 		memset( nRadarIndex, 0, sizeof(nRadarIndex) );
// 	}

} ;

// �쐞移� �궛異� �븯湲� �쐞�븳 援ъ“泥� �젙�쓽
struct STR_LOBS {
	float fDoa;
	float fLatitude;
	float fLongitude;
	float fAltitude;

	int iCollectorID;

	unsigned int uiLOBID;				// �겢�윭�뒪�꽣留� �븯硫댁꽌 援щ텇�쓣 �븯湲� �쐞�븳 蹂��닔 異붽�

} ;

/**
 * @enum      E_BEAM_CODE
 * @brief     鍮� �깮�꽦 肄붾뱶 �젙�쓽
 * @author    議곗쿋�씗 (churlhee.jo@lignex1.com)
 */
enum E_BEAM_CODE
{
	E_UNKNOWN_CODE=0,
	E_CREATE_FREQ_TYPE_CODE=1,
	E_CREATE_PRI_TYPE_CODE,
	E_CREATE_INTRA_TYPE_CODE,
	E_CREATE_SIGNAL_TYPE_CODE,

	E_CREATE_DIST_CODE,

};

// LOB瑜� �뾽�뜲�씠�듃�븯湲� �쐞�븳 援ъ“泥� �젙�쓽
struct STR_UPDATE_LOB_ABT_AET {
	unsigned int uiAETID;
	unsigned int uiABTID;
	unsigned int uiLOBID;
	string strAcqTime;

	unsigned int uiSeqNum;

}  ;

enum ENUM_PE_STAT {
	E_EL_PESTAT_FAIL=0,					// �쐞移� �궛異� �썑 �뿉�윭媛� �궃 �긽�깭
	E_EL_PESTAT_SUCCESS,				// �쐞移� �궛異� 寃곌낵媛� �꽦怨듭씤 �긽�깭
	E_EL_PESTAT_NOT_YET,				// LOB媛� �쟻�뼱�꽌 �쐞移� �궛異� �닔�뻾 �씠�쟾 �긽�깭
	E_EL_PESTAT_IMPOSSIBILITY		// �빆怨듦린媛� 怨좎젙 �쐞移섎줈 �궛異쒗븯湲� �뼱�젮�슫 �긽�깭
};

struct STR_POSITION_ESTIMATION {
	ENUM_PE_STAT enValid;
	float fLongitude;							// [deg]
	float fLatitude;							// [deg]
    float fAltidude;							// [m]
	float fCEP;										// [m]
	float fMajorAxis;							// [m]
	float fMinorAxis;							// [m]
	float fTheta;									// [0.1�룄]
	float fDistanceErrorOfThreat;	// [m]

	//int iManualLongitude;				// [deg], MANUAL_POS_EST_LONG
	//int iManualLatitude;				// [deg], MANUAL_POS_EST_LAT

	bool bApplayOfLOBClustering;// TRUE: �쟻�슜, FALSE: 誘몄쟻�슜

// 	STR_POSITION_ESTIMATION::STR_POSITION_ESTIMATION() : enValid(E_EL_PESTAT_FAIL), fLongitude(0.0), fLatitude(0.0), fCEP(0), fMajorAxis(0), fMinorAxis(0), fTheta(0), fDistanceErrorOfThreat(0), bApplayOfLOBClustering(false)
// 	{
// 
// 	}

} ;


typedef struct STempAmbiBeam
{
	unsigned short usAmbiguousBeamId;
	STempAmbiBeam(){
		usAmbiguousBeamId=0;
	}
}I_AmbiBeam;


/*--------------------------------------------------------------------------------
*						GMI LOB 泥섎━�슜 �뜲�씠�꽣 ���엯 �떊洹� �젙�쓽 2016.2.13. �씠�젙�궓
*--------------------------------------------------------------------------------*/
/*! Beam �삉�뒗 Emitter �긽�깭瑜� �젙�쓽�븳 enum
 * @enum      E_BEAM_EMITTER_STAT
 * @brief 
 * @author    �씠�젙�궓 (jeongnam.lee@lignex1.com)
 * @date      2016-02-13 �삤�쟾 8:27
 */
enum E_BEAM_EMITTER_STAT
{
	E_ES_NOT_AVAILABLE = 0,			// 媛앹껜媛� �깮�꽦�릺吏� �븡�� 寃쎌슦 (�븘�슂�꽦�뿉 ���빐�꽌�뒗 �끉�쓽 �븘�슂)

	// �궡遺��쟻�쑝濡� �쐞�삊 �긽�깭 �젙蹂� 媛� : �쟾�떆�븷 �븘�슂媛� �뾾�쓬.
    E_ES_NEW,									// �떊洹� 泥섎━ (�긽�깭�젙蹂대줈 �솢�슜�븿, �쟾�떆), �솢�룞
	E_ES_UPDATE,								// �솢�룞
	E_ES_DELETE,								// 誘명솢�룞 泥섎━
    E_ES_DEACTIVATED,                           // �솢�룞 以묒�
    E_ES_REACTIVATED,                           // �솢�룞 �옱媛�

};

// static const char* strBeamEmitterStat[] = 
// {
// 	"-",
// 
// 	"�솢�룞(�떊洹�)",
// 	"�솢�룞",
// 	"誘명솢�룞",
// 	"以묒�",
// 	"�솢�룞(�옱媛�)",
// 
// };

// �뿰�룞湲곗� 吏��긽 POSN媛꾩쓽 OPCODE �젙蹂�
enum E_EMITTER_OPCODE
{
	E_EO_NOT_AVAILABLE = 0,					// 媛앹껜媛� �깮�꽦�릺吏� �븡�� 寃쎌슦 (�븘�슂�꽦�뿉 ���빐�꽌�뒗 �끉�쓽 �븘�슂)

	// �븘�옒 肄붾뱶�뱾�� �빐�떦 諛⑹궗泥�/鍮� 紐⑸줉李쎌뿉 �쟾�떆�빐�빞 �븿.
	E_MR_UPDATE_INFO,								// 蹂�寃� 泥섎━ (ELNOT, �쐞移� �궛異� �벑 蹂�寃�), 諛⑹궗泥�/鍮� �뀒�씠釉붿뿉 �뜲�씠�꽣(ELNOT, �쐞移� �궛異� �젙蹂�) 異붽�
	E_MR_REMOVE_AETABT,							// 諛⑹궗泥�/鍮� 紐⑸줉李쎌뿉�꽌 �젣嫄�
	E_MR_REMOVE_LOB,								// LOB 紐⑸줉李쎌뿉�꽌 �젣嫄�

	// �븘�옒 肄붾뱶�뱾�� �빐�떦 LOB 紐⑸줉李쎌뿉 �쟾�떆�빐�빞 �븿.
	E_MR_CHANGE,										// (諛⑹궗泥�/)鍮�/LOB 踰덊샇 蹂�寃�

	//////////////////////////////////////////////////////////////////////////
	E_MR_UPDATE_STAT,								// �쐞�삊 �긽�깭 �젙蹂�, (�솢�룞, 誘명솢�룞 �벑)

	E_MR_ALERT_UPDATE,							// 寃쎈낫 泥섎━
	E_MR_REPORT_UPDATE,							// 蹂닿퀬�꽌 泥섎━

	E_MR_REMOVE_AET									// 諛⑹궗泥댁뿉�꽌 �빐�떦 �빆紐� �젣嫄�

};

// static const char* strBeamEmitterOpcode[] = 
// {
//  	"媛앹젣�깮�꽦�븞�맖",
// 
// 	"媛깆떊 ",
// 	"�궘�젣(E/B)",
// 	"�궘�젣(L) ",
// 
// 	"蹂�寃� ",
// 	//////////////////////////////////////////////////////////////////////////
// 	"�긽�깭 ",
// 
// 	"寃쎈낫 ",
// 	"蹂닿퀬�꽌",
// 
// 	"�궘�젣(E)",
// 
// 	"�긽�깭 蹂��룞�뾾�쓬(NoChange)"
// };


struct I_AET_ANAL {
	int uiSeqNum;

	//////////////////////////////////////////////////////////////////////////
	// LOB 愿�由ъ뿉 �븘�슂�븳 蹂��닔
        //int iLinkNum;																								// �닔�떊�븳 �쐞�삊 �뿉誘명꽣�쓽 留곹겕 踰덊샇

	bool isFiltered;																						// �닔吏� �븘�꽣 �뿬遺�
	bool isManualEdited;																				// �닔�룞 �렪吏� �뿬遺�

	unsigned int uiAETID;
	unsigned int uiABTID;
	unsigned int uiLOBID;

	time_t tiAcqTime;																						// �빆怨듭뿉�꽌 遺꾩꽍 �떆媛�, LOB 硫붿떆吏��뿉 time_t 濡� �릺�뼱 �엳�쑝硫� �궘�젣�븿.
	int tiContactTimems;																				// �빆怨듭뿉�꽌 遺꾩꽍 �떆媛�

	E_BEAM_EMITTER_STAT enEmitterStat;													// LOB �긽�깭

        //int iTaskType;																							// 怨쇱젣 �삎�깭 醫낅쪟

	unsigned int uiCoLOB;																				// LOB 媛쒖닔

	int iBeamValidity;

	//////////////////////////////////////////////////////////////////////////
	// �떇蹂� 異붽� �젙蹂�
	//
	// �떇蹂� �썑蹂� �젙蹂�
	bool bOverCount;
	//int usCoCandidate;
	int usThreatId[MAX_IDCANDIDATE];

	// �쐞�삊 �젅踰�
	//unsigned short usPriorityLevel;

	// �씪移섏쑉
	int iIdRatio[MAX_IDCANDIDATE];

	// �떊洹� CED 諛� EOB濡� �떇蹂꾪븳 �젙蹂�
	STR_CEDEOBID_INFO idInfo;

	// �쐞移� �궛異� �젙蹂�
	STR_POSITION_ESTIMATION peInfo;

	//char chELNOT[_MAX_ELNOT_STRING_SIZE_];					// MAX_SIZE_OF_ELNOT

	// EOB 嫄곕━ �삤李� [km]
	double dEOBErrorDistance;

	// �떇蹂� ���긽
	//EnumLibType sIdObject;

	// 蹂�議� 肄붾뱶
	//char modCode[MAX_SIZE_OF_MODULATIONCODE];

	E_BEAM_CODE eBeamCode;

	bool bCompFreq;
	bool bCompPRI;

} ;

//static I_AET_ANAL g_stInitAETAnal;





typedef struct STempAET
{
	I_THREAT_DATA stThreat;
	I_AET_DATA stAet;
	I_AET_ANAL stAnal;
	STempAET(){
		//memset(&stThreat, 0, sizeof(I_THREAT_DATA));
		//memset(&stAet, 0, sizeof(I_AET_DATA));
		//memset(&stAnal, 0, sizeof(I_AET_ANAL));

	/*	g_stInitThreatData;
		g_stInitAETData;
		g_stInitAETAnal;*/
	}
}I_AET;
static const I_AET g_stInitAET;

/**
 * @typedef   SELLOBDATA_EXT
 * @brief     �닔�떊 �쐞�삊 �뜲�씠�꽣 援ъ“泥� �씠�쇅�뿉 異붽�濡� �뱾�뼱媛��뒗 援ъ“泥� �젙�쓽
 * @author    議곗쿋�씗 (churlhee.jo@lignex1.com)
 */
struct SELLOBDATA_EXT {
	I_AET_ANAL aetAnal;
	I_AET_DATA aetData;

} ;


struct STR_LOBDATAEXT {
	SRxLOBData stLOBData;
	SELLOBDATA_EXT stLOBDataExt;

}  ;

struct STR_ID_TYPE {
	int iSignalType;
	int iFrqType;
	int iPRIType;
	//int iScanType;
	//int iMOPType;

} ;

struct SELMANUALVAL {
    unsigned int doaInfo : 1;
    unsigned int freqInfo : 1;
    unsigned int priInfo : 1;
    unsigned int pwInfo : 1;
    unsigned int paInfo : 1;
    unsigned int idInfo : 1;
    unsigned int peInfo : 1;

    unsigned int _dummy : 25;

} ;


/**
 * @typedef   UELMANUALVAL
 * @brief     �닔�룞 �렪吏� �뿬遺�瑜� 寃곗젙�븯湲� �쐞�븳 �뵆�젅洹� 援ъ“泥�
 * @author    議곗쿋�씗 (churlhee.jo@lignex1.com)
 */
union UELMANUALVAL {
    SELMANUALVAL x;
    unsigned int val32;

}  ;

/**
 * @typedef   SELABTDATA_EXT
 * @brief     ABT 援ъ“泥� �젙�쓽
 * @author    議곗쿋�씗 (churlhee.jo@lignex1.com)
 */
struct SELABTDATA_EXT {
    // �늻�쟻�맂 �쟾泥� PDW 媛쒖닔
    //int nCoTotalPdw;
    //int nCoTotalIQ;

    // �씤�듃�씪 蹂�議� �쑀臾�
    //bool bIntraMop;

    // �쐞移� �궛異� �젙蹂�-Covariace 媛�
    double dPECoVar[4];

    float fLastAOA;
    float fRadarLatitude;
    float fRadarLongitude;

    // �닔�룞 �렪吏� �뿬遺�
    bool bIsManualEdited;

    // 諛⑹궗泥댁쓽 �솢�룞 �긽�깭瑜� ���옣
    enum E_BEAM_EMITTER_STAT enBeamEmitterStat;

    // 鍮� �쑀�슚�꽦 媛��닔
    int nCoBeamValidity;

    // �닔�룞 �렪吏� �뿬遺� �뵆�젅洹�
    //UELMANUALVAL xManualEdited;

	// �닔�룞/�옄�룞 �쐞移� 寃곌낵 �젙蹂� �뿬遺�
    bool bManualPosEstPreferred;
    float fManualLatitude;
    float fManualLongitude;

    //SLOBOtherInfo stLOBOtherInfo;

    int iLOBPoolIndex;

    STR_ID_TYPE stIDType;

    enTHREAT_PLATFORM enPlatform;

    int nCoIdEOB;
    //STR_EOB_RESULT stEOBResult[MAX_CANDIDATE_EOB];

    // 鍮� 蹂묓빀 �젙蹂�
    bool bCompFreq;
    bool bCompPRI;

    // �떊洹� CED 諛� EOB濡� �떇蹂꾪븳 �젙蹂�
    STR_CEDEOBID_INFO idInfo;

    ENUM_PE_STAT enValid;
    bool bApplayOfLOBClustering;// TRUE: �쟻�슜, FALSE: 誘몄쟻�슜

    UINT uiPE;
    bool bFullOfPE;
    double dLatitude[MAX_OF_LOBS_PE];
    double dLongitude[MAX_OF_LOBS_PE];
    double dEasting[MAX_OF_LOBS_PE];
    double dNorthing[MAX_OF_LOBS_PE];

    // �뒪罹� 遺꾩꽍 異붽� �젙蹂�
    unsigned int uiTry;
    unsigned int uiScanStep;

#ifdef _ELINT_
    // FISINT�슜 怨쇱젣
    //bool bIsFISINTTask;
    UINT uiOpInitID;

    unsigned int uiSeqNum;
#elif _POCKETSONATA_
    unsigned uiOpcode;
    time_t tiSendLan;

#endif

} ;

struct SELAETDATA_EXT {
	// �늻�쟻�맂 �쟾泥� PDW 媛쒖닔
	int nCoTotalPdw;
	//int nCoTotalIQ;

	// �씤�듃�씪 蹂�議� �쑀臾�
	// bool bIntraMop;
	
	// 諛⑹궗泥� 媛꾩쓽 �떇蹂꾩쓣 �쐞�븳 �젙蹂�
	//char szEOBELNOT[_MAX_ELNOT_STRING_SIZE_];					// EOB �긽�쓽 ELNOT

	// 諛⑹궗泥댁쓽 �솢�룞 �긽�깭瑜� ���옣
	enum E_BEAM_EMITTER_STAT enBeamEmitterStat;

	// �닔�룞 �렪吏� �뿬遺� �뵆�젅洹�
	bool bIsManualEdited;

	bool bIsFISINTTask;

	// �닔�룞 �렪吏� �젙蹂�
    UELMANUALVAL xMannualEdited;

	int iPinNumber;
	//char szELNOT[_MAX_ELNOT_STRING_SIZE_];

	//int iTaskType;		// 怨쇱젣 �삎�깭

	// �뿬�윭媛쒖쓽 誘몄떇蹂� 鍮� 以묒뿉�꽌 ���몴 ABT 踰덊샇
	unsigned int nUnIDABTID;

	// �닔�룞/�옄�룞 �쐞移� 寃곌낵 �젙蹂� �뿬遺�
	bool bManualPosEstPreferred;

    float fManualLatitude;
    float fManualLongitude;

    STR_CEDEOBID_INFO idInfo;


	unsigned int uiSeqNum;


} ;

struct STR_ABTDATAEXT {
	SRxLOBData stLOBData;
	SRxABTData stABTData;
	SELABTDATA_EXT stABTDataExt;

} ;


/*!
 * @typedef   SELIDENTIFICATION_INFO
 * @brief     �떊�샇 �떇蹂� �샃�뀡 李쎌뿉 ���븳 援ъ“泥� �젙�쓽 (GMI 蹂묓빀 泥섎━�슜 援ъ“泥�)
 * @author    �씠�젙�궓(jeongnam.lee@lignex1.com)
 * @date      2016-02-13 
 */
// typedef struct {
// 	SRxThreatData				stMsgData;		// �빆怨듭뿉�꽌 �닔�떊�맂 硫붿떆吏��쓽 Data (Header) �젙蹂�
// 	SRxThreatDataGroup		stMsgDataGrp;	// �빆怨듭뿉�꽌 �닔�떊�맂 硫붿떆吏��쓽 DataGrp �젙蹂�
// 	SPosEstData stPosEst;							// 吏��긽�뿉�꽌 �쐞移� �궛異쒗븳 �젙蹂�
// 	I_AET stCDFAet;									// �떊�샇 �떇蹂� �엯�젰 諛� 寃곌낵 �젙蹂�
// 
// } SELIDENTIFICATION_INFO_MR;

/*! Beam (ABT) �젙蹂대�� �떞怨� �엳�뒗 援ъ“泥�
 * @struct     SBeamInfoFamily
 * @brief 
 * @author    �씠�젙�궓 (jeongnam.lee@lignex1.com)
 * @date      2016-02-13 �삤�쟾 8:28 
 */
#define LENGTH_OF_GMI_CHAR 64
struct SThreatFamilyInfo
{
	E_EMITTER_OPCODE enOpcode;						// �뿰�룞湲곗� POSN媛꾩쓽 紐낅졊 媛�

	unsigned int nSeqNum;									// DB �뀒�씠釉붿쓽 SEQ_NUM

	unsigned int iAETID;									// 諛⑹궗泥� #
	unsigned int iABTID;									// ABT #
	unsigned int iLOBID;									// LOB #

	bool bApplySearchFilter;							// ApplySearchFilterToAlarmAndMapDisplay() �븿�닔 �닔�뻾 �뿬遺�

	bool bIsFISINTTask;										// FISINT�슜 怨쇱젣

	// 寃쎈낫 諛� 蹂닿퀬�꽌 理쒖큹/理쒖쥌 蹂닿퀬 �떆媛�
	time_t ti_FirstTime;									// 理쒖큹 �떆媛�
	time_t ti_FinalTime;								// 理쒖쥌 �떆媛�(寃쎈낫)

	E_BEAM_CODE eBeamCode;								// 鍮� �긽�깭 �쟾�넚, �뵒踰꾧퉭�쓣 �쐞�븳 肄붾뱶

	E_BEAM_EMITTER_STAT enEmitterStat;					// �쐞�삊 �긽�깭 �젙蹂�

	unsigned int iChangedAETID;							// AET #
	unsigned int iChangedABTID;							// ABT #

        SThreatFamilyInfo() : enOpcode(E_EO_NOT_AVAILABLE), nSeqNum(0), iAETID(0), iABTID(0), iLOBID(0),
            bApplySearchFilter(false), bIsFISINTTask(false), ti_FirstTime(0), ti_FinalTime(0), eBeamCode(E_UNKNOWN_CODE), enEmitterStat(E_ES_NOT_AVAILABLE), iChangedAETID(0), iChangedABTID(0)
	{

	}

} ;



typedef struct SEmitterFilter
{
	bool bFrqUse;
	float fFrqMin;
	float fFrqMax;
	bool bPriUse;
	float fPriMin;
	float fPriMax;
	bool bPwUse;
	float fPwMin;
	float fPwMax;
        SEmitterFilter()
		:bFrqUse(false)
                ,fFrqMin(0.0)
                ,fFrqMax(0.0)
		,bPriUse(false)
                ,fPriMin(0.0)
                ,fPriMax(0.0)
		,bPwUse(false)
		,fPwMin(0.0)
		,fPwMax(0.0)
	{
	}
}I_EMITTER_FILTER;

// typedef struct STempPDW
// {
// 	SRxPDWData stData;
// 	SAvgPDWDataRGroup stAvgData;
// 	//std::list<SRXPDWDataRGroup> listGroup; // 2014.07.15.�씠�젙�궓. �궗�슜�븯吏� �븡�븘�꽌 二쇱꽍泥섎━
// 	STempPDW()
// 	{
// 		memset(&stData, 0, sizeof(SRxPDWData));
// 		memset(&stAvgData, 0, sizeof(SRXPDWDataRGroup));
// 		//stData.Init();
// 		//stAvgData.Init();
// 		//listGroup.clear(); // 2014.07.15.�씠�젙�궓. �궗�슜�븯吏� �븡�븘�꽌 二쇱꽍泥섎━
// 	}
// }I_PDW;

// 諛⑹궗泥�/LOB 紐⑸줉李쎌뿉�꽌 蹂닿퀬�꽌 �옉�꽦 硫붾돱 �겢由� �떆 諛쒖깮
// struct SEmitterInfoForReport
// {
// 	std::string strDtctId;
// 	std::string strTaskId;
// 	int nAetId;
// 	int nLobId;
// 	bool bFromEmitterWnd;
// 	SEmitterInfoForReport()
// 	: strTaskId("")
// 	, strDtctId("")
// 	, nAetId(-1)
// 	, nLobId(-1)
// 	, bFromEmitterWnd(true){};
// };

struct SEmitterActivationInfo
{
	int nDetectYear; //珥덉텧 �뀈�룄
	int nDetectMon; // 珥덉텧 �썡
	int nDetectDay; // 異붿킄 �씪
	int nDetectTimeHour;	// 珥덉텧 �떆媛� (�떆)
	int nDetectTimeMin;		// 珥덉텧 �떆媛� (遺�)
	int nDetectTimeSec;		// 珥덉텧 �떆媛� (珥�)
	int nRecentUpdateTimeHour;  // 媛깆떊 �떆媛� (�떆)
	int nRecentUpdateTimeMin;	 // 媛깆떊 �떆媛� (遺�)
	int nRecentUpdateTimeSec;	 // 媛깆떊 �떆媛� (珥�)
	int nTotalActTimeHour;			// 珥� �솢�룞 �떆媛� (�떆)
	int nTotalActTimeMin;			 // 珥� �솢�룞 �떆媛� (遺�)
	int nTotalActTimeSec;			// 珥� �솢�룞 �떆媛� (珥�)
	bool bDeactivatedNow;			// �솢�룞醫낅즺 �뿬遺�
	int nDeactivatedTimeHour;			// �솢�룞醫낅즺 �떆媛� (�떆)
	int nDeactivatedTimeMin;			 // �솢�룞醫낅즺 �떆媛� (遺�)
	int nDeactivatedTimeSec;			// �솢�룞醫낅즺 �떆媛� (珥�)
	bool bTimeOfConvergenceIsValid; // 
	int nTimeOfConvergenceHour;
	int nTimeOfConvergenceMin;
	int nTimeOfConvergenceSec;
	int nTimeOfConvergenceLobNum;
	int nNumOfDetectionToday;
	int nNumOfTotalLob;
	int nNumOfLobUsedToPosEst;
	int nNumOfTotalPdw;
	bool bIsSoi; // 愿��떖�떊�샇�씤吏�. 2015.3.30. �씠�젙�궓. 愿��떖�떊�샇�뒗 寃쎈낫/�뿰愿�怨쇱젣 �꽕�젙 �떊�샇�씤吏��쓽 �쓽誘몄엫.
	int nFinalAircraftLatitude;
	int nFinalAircraftLongitude;
	int nFinalAircraftDoa;
	SEmitterActivationInfo()
		:nDetectYear(0),
		 nDetectMon(0),
	     nDetectDay(0),
		 nDetectTimeHour(0),
		 nDetectTimeMin(0),
		 nDetectTimeSec(0),
		 nRecentUpdateTimeHour(0),
		 nRecentUpdateTimeMin(0),
		 nRecentUpdateTimeSec(0),
		 nTotalActTimeHour(0),
		 nTotalActTimeMin(0),
		 nTotalActTimeSec(0),
		 bDeactivatedNow(false),
		 nDeactivatedTimeHour(0),
		 nDeactivatedTimeMin(0),
		 nDeactivatedTimeSec(0),
		 bTimeOfConvergenceIsValid(false),
		 nTimeOfConvergenceHour(0),
		 nTimeOfConvergenceMin(0),
		 nTimeOfConvergenceSec(0),
		 nTimeOfConvergenceLobNum(0),
		 nNumOfDetectionToday(0),
		 nNumOfTotalLob(0),
		 nNumOfLobUsedToPosEst(0),
		 nNumOfTotalPdw(0),
		 bIsSoi(false),
		 nFinalAircraftLatitude(0),
		 nFinalAircraftLongitude(0),
         nFinalAircraftDoa(0)
	{};
};

typedef struct stIdntfyReslt
{
    string strIdnfyRsltID;				// "0" �� �옄�룞�쑝濡� DB�뿉�꽌 Unique �닔濡� �븷�떦
    string strDtctSigID;						// �떒�쐞 : �뾾�쓬.
    string strIdnfyTime;					// �떒�쐞 : �떆:遺�:珥�
	int	nRadarModeIndex;							// nRadarModeIndex
	int	nThreatIndex;	
	int	nDeviceIndex;
	unsigned int uiBeamID;
	int uiLobID;
	int uiAetID;
    unsigned int uiCandidateNum;
    string strMsgAetID;
    string strElnotAir;
    string strElnotGnd;

    stIdntfyReslt()
        :strIdnfyRsltID("")
        ,strDtctSigID("")
        ,strIdnfyTime("")
        ,nRadarModeIndex(0)
        ,nThreatIndex(0)
        ,nDeviceIndex(0)
        ,uiBeamID(0)
		,uiLobID(0)
		,uiAetID(0)
        ,uiCandidateNum(0)
		,strMsgAetID("")	
		,strElnotAir("")
		,strElnotGnd("")
	{		
	};
}SELIdentify;

/**
 * @typedef   I_PDW_IQ_DATA
 * @brief     PDW 諛� IQ �뜲�씠�꽣 議댁옱 �뿬遺�瑜� 蹂닿��븯�뒗 援ъ“泥�
 * @author    議곗쿋�씗 (churlhee.jo@lignex1.com)
 */
typedef struct SPDWIQData
{
	bool bPDW;
	bool bIQ;
	SPDWIQData(){
		bIQ = false;
		bPDW = false;
	}
} I_PDW_IQ_DATA;

// 諛⑹궗泥�/鍮�/LOB 한글이 다.. 
#define _ACTIVE_STAT_						"ACT"
#define _DEACTIVE_STAT_				"DEA"
#define _REACTIVE_STAT_					"REA"
#define _DELETE_STAT_					"DEL"

/*! Emitter �젙蹂대�� �떞怨� �엳�뒗 援ъ“泥�
 * @struct     SEmitterInfoFamily
 * @brief 
 * @author    �씠�젙�궓 (jeongnam.lee@lignex1.com)
 * @date      2016-02-13 �삤�쟾 8:28 
 */
// struct SEmitterInfoFamily
// {
// 	E_BEAM_EMITTER_STAT eStat;					// Emitter Status 
// 	char szEmitterIdGnd[LENGTH_OF_GMI_CHAR];							// 吏��긽�뿉�꽌 �젙�쓽�븳 Emitter Unique ID
// 	char szPastEmitterIdGnd[LENGTH_OF_GMI_CHAR];					// Emitter Status媛� E_MR_NEW_BY_DEMERGE �씤 寃쎌슦, �씠�쟾 Emitter ID瑜� 湲곗엯.
// 	SELIDENTIFICATION_INFO_MR stEmitter;	// �떇蹂�, �쐞移섏궛異�, �젣�썝 �벑 Emitter �젙蹂�	
// 	
// 	SEmitterInfoFamily(){
// 		memset(szEmitterIdGnd, 0, LENGTH_OF_GMI_CHAR);
// 		memset(szPastEmitterIdGnd, 0, LENGTH_OF_GMI_CHAR);
// 	}
// };

/*! Emitter �삉�뒗 Beam�씠 Merge濡� �씤�븯�뿬 Delete ���긽�씠 �깮湲� 寃쎌슦, ID瑜� 湲곕줉�븯湲� �쐞�븳 援ъ“泥�
 * @struct     SDeleteID
 * @brief 
 * @author    �씠�젙�궓 (jeongnam.lee@lignex1.com)
 * @date      2016-02-13 �삤�쟾 8:40 
 */
struct SDeleteID
{
	char szIdGnd[LENGTH_OF_GMI_CHAR];					// �궘�젣 ���긽�씤 ID. (Emitter  Unique ID �삉�뒗 Beam Unique ID)
	
	SDeleteID(){
		memset(szIdGnd, 0, LENGTH_OF_GMI_CHAR);	
	}
} ;

// VER.3 紐⑸줉李쎌슜 援ъ“泥� && ENUM ���엯
enum E_GMI_PROC_MSG_INFO_TYPE 
{	
	E_GMI_LOB = 0,
	E_GMI_ABT,
	E_GMI_AET,
};

// #define LENGTH_OF_SHORT_CHAR 64
// #define LENGTH_OF_FRQ_OR_PRI_SEQ_CHAR 1024
// struct SLobInfoToWnd
// {
// 	unsigned long long ullSeqNum;
// 	char szMissionId[LENGTH_OF_MISSION_ID+1];
// 	char szMissionName[SIZE_OF_TASK_NAME];
// 	char szTaskId[LENGTH_OF_TASK_ID];
// 	char szTaskName[SIZE_OF_TASK_NAME];
// 	int nSearchBandId;
// 	char szTaskType[LENGTH_OF_SHORT_CHAR];
// 	char szDetAntDirection[LENGTH_OF_SHORT_CHAR];
// 	char szLinkNum[LENGTH_OF_SHORT_CHAR];
// 	char szAircraftNum[LENGTH_OF_SHORT_CHAR];
// 	char szRxPath[LENGTH_OF_SHORT_CHAR];
// 	unsigned int uiLobId;
// 	unsigned int uiAbtId;
// 	unsigned int uiAetId;
// 	char szElnotPri[LENGTH_OF_SHORT_CHAR];
// 	char szModeCodePri[LENGTH_OF_SHORT_CHAR];
// 	char szModulationCode[LENGTH_OF_SHORT_CHAR];
// 	char szNickName[LENGTH_OF_SHORT_CHAR];
// 	char szPriFuncCode[LENGTH_OF_SHORT_CHAR];
// 	char szElnotSec[LENGTH_OF_SHORT_CHAR];
// 	char szModeCodeSec[LENGTH_OF_SHORT_CHAR];
// 	char szElnotTert[LENGTH_OF_SHORT_CHAR];
// 	char szModeCodeTert[LENGTH_OF_SHORT_CHAR];
// 	char szSigType[LENGTH_OF_SHORT_CHAR];
// 	int iPolarization;
// 	char szPolarization[LENGTH_OF_SHORT_CHAR];
// 	int iRatioOfPOL;
// 	//int iIsFISINTTask;
// 	char szIsFISINTTask[LENGTH_OF_SHORT_CHAR];
// 	
// 	int nNumOfPPG;
// 	int nNumOfPulse;
// 	char szTimeInfo[LENGTH_OF_SHORT_CHAR];
// 	char szValidity[LENGTH_OF_SHORT_CHAR];
// 	char szBL[LENGTH_OF_SHORT_CHAR];
// 	int iFov;
// 	int iDoaMean; // �빐�긽�룄 0.1 deg
// 	int iDoaMax;
// 	int iDoaMin;
// 	int iDoaDev;
// 	int iDoaStd;
// 	int iDIRatio;
// 	char szFrqType[LENGTH_OF_SHORT_CHAR];
// 	char szFrqPatternType[LENGTH_OF_SHORT_CHAR];
// 	char szHasFrqPeriod[LENGTH_OF_SHORT_CHAR];
// 	int nFrqPeriod; // �빐�긽�룄 10khz
// 	int nFrqPositionCount;
// 	int nFrqElementCount;
// 	int nFrqMean; // �빐�긽�룄 10khz
// 	int nFrqMax;
// 	int nFrqMin;
// 	int nFrqDev;
// 	int arrFrqSeq[MAX_FREQ_PRI_STEP];
// 	char szFrqSeq[LENGTH_OF_FRQ_OR_PRI_SEQ_CHAR];	
// 	char szPriType[LENGTH_OF_SHORT_CHAR];
// 	char szPriPatternType[LENGTH_OF_SHORT_CHAR];
// 	char szHasPriPeriod[LENGTH_OF_SHORT_CHAR];
// 	int nPriPeriod; // us
// 	int nPriPositionCount;
// 	int nPriElementCount;
// 	int nPriMean;
// 	int nPriMax;
// 	int nPriMin;
// 	int nPriDev;
// 	int iPriJitterRatio;
// 	int arrPRISeq[MAX_FREQ_PRI_STEP];
// 	char szPRISeq[LENGTH_OF_FRQ_OR_PRI_SEQ_CHAR];
// 	int nPrfMean;
// 	int nPrfMax;
// 	int nPrfMin;
// 	int nPrfDev;
// 	int iPaMean;
// 	int iPaMax;
// 	int iPaMin;
// 	int iPaDev;
// 	int iPwMean;
// 	int iPwMax;
// 	int iPwMin;
// 	int iPwDev;
// 	char szScanType[LENGTH_OF_SHORT_CHAR];
// 	char szScanTypeDetail[LENGTH_OF_SHORT_CHAR];
// 	int nScanPeriodMicroSec;
// 	float fScanPeriodHz;
// 	char szIntraType[LENGTH_OF_SHORT_CHAR];
// 	char szIntraDetailType[LENGTH_OF_SHORT_CHAR];
// 	int nIntraFrqMean; // 10khz�빐�긽�룄
// 	int nIntraFrqMax;
// 	int nIntraFrqMin;
// 	int nIntraFrqChangeWidth;
// 	int arrPriPerGroup[MAX_PRI_PER_GROUP];
// 	int arrPaDiffPerGroup[MAX_PADIFF_PER_GROUP];
// 	int nAircraftLatitude;
// 	int nAircraftLongitude;
// 	int nAircraftPitch; // 0.1�룄 �빐�긽�룄
// 	int nAircraftRoll;
// 	int nAircraftHeading;
// 	int nAircraftAltitude;
// 	int nAircraftFOM;
// 	char szIsPDWRestored[LENGTH_OF_SHORT_CHAR];
// 	char szIsIQRestored[LENGTH_OF_SHORT_CHAR];
// 	char szFirstReportTime[LENGTH_OF_SHORT_CHAR];
// 	char szFinalReportTime[LENGTH_OF_SHORT_CHAR];
// 	char szStat[LENGTH_OF_SHORT_CHAR];
// 	int nHour;
// 	int nMin;
// 	int nSec;
// 	int nIsSelect;
// 	unsigned int nAirLobId;
// 	int nIsFiltered;
// 	unsigned int uiNewAbtId;
// 	unsigned int uiNewAetId;
// 	E_EMITTER_OPCODE eOpCodeForUpdate; // �뾽�뜲�씠�듃 �릺�뒗 �궡�슜�씠 �떎�뼇�빐 �졇�꽌, Update Key瑜� �뫊�꽌 �떇蹂꾪븯湲곕줈 �븿. �씠�젙�궓. 2018.4.10.
// 
// 	// 議곗쿋�씗, �떆媛� �닚�쑝濡� �젙�젹�븯湲� �쐞�빐 異붽��맂 �븿�닔
// 	bool operator<(const SLobInfoToWnd & other ) 
// 	{
// 		return strcmp( this->szTimeInfo, other.szTimeInfo ) < 0;
// 	}
// 
// 	SLobInfoToWnd()
// 		:ullSeqNum(0),
// 		nSearchBandId(0),
// 	uiLobId(0),
// 	uiAbtId(0),
// 	uiAetId(0),
// 	iPolarization(0),
// 	iRatioOfPOL(0),
// 	nNumOfPPG(0),
// 	nNumOfPulse(0),
// 	iDoaMean(0), // �빐�긽�룄 0.1 deg
// 	iDoaMax(0),
// 	iDoaMin(0),
// 	iDoaDev(0),
// 	iDoaStd(0),
// 	iDIRatio(0),
// 	iFov(0),
// 	nFrqPeriod(0), // �빐�긽�룄 10khz
// 	nFrqPositionCount(0),
// 	nFrqElementCount(0),
// 	nFrqMean(0), // �빐�긽�룄 10khz
// 	nFrqMax(0),
// 	nFrqMin(0),
// 	nFrqDev(0),
// 	nPriPeriod(0), // us
// 	nPriPositionCount(0),
// 	nPriElementCount(0),
// 	nPriMean(0),
// 	nPriMax(0),
// 	nPriMin(0),
// 	nPriDev(0),
// 	iPriJitterRatio(0),
// 	iPwMean(0),
// 	iPwMax(0),
// 	iPwMin(0),
// 	iPwDev(0),
// 	nPrfMean(0),
// 	nPrfMax(0),
// 	nPrfMin(0),
// 	nPrfDev(0),
// 	iPaMean(0),
// 	iPaMax(0),
// 	iPaMin(0),
// 	iPaDev(0),
// 	nScanPeriodMicroSec(0),
// 	fScanPeriodHz(0.0),
// 	nIntraFrqMean(0), // 10khz�빐�긽�룄
// 	nIntraFrqMax(0),
// 	nIntraFrqMin(0),
// 	nIntraFrqChangeWidth(0),
// 	nAircraftLatitude(0),
// 	nAircraftLongitude(0),
// 	nAircraftPitch(0), // 0.1�룄 �빐�긽�룄
// 	nAircraftRoll(0),
// 	nAircraftHeading(0),
// 	nAircraftAltitude(0),
// 	nAircraftFOM(0),
// 	nHour(0),
// 	nMin(0),
// 	nSec(0),
// 	nIsSelect(0),
// 	nAirLobId(0),
// 	nIsFiltered(0),
// 	uiNewAbtId(0),
// 	uiNewAetId(0),
// 	eOpCodeForUpdate(E_EO_NOT_AVAILABLE)
// 	{
// 		memset(szMissionId, 0, LENGTH_OF_MISSION_ID+1);
// 		memset(szMissionName, 0,SIZE_OF_TASK_NAME);
// 		memset(szTaskId, 0,LENGTH_OF_TASK_ID);
// 		memset(szTaskName, 0,SIZE_OF_TASK_NAME);
// 		memset(szTaskType, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szDetAntDirection, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szLinkNum, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szAircraftNum, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szElnotPri, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szModeCodePri, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szModulationCode, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szNickName, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szPriFuncCode, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szElnotSec, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szModeCodeSec, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szElnotTert, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szModeCodeTert, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szSigType, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szTimeInfo, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szValidity, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szBL, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szFrqType, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szFrqPatternType, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szHasFrqPeriod, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szPriType, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szPriPatternType, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szHasPriPeriod, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szScanType, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szScanTypeDetail, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szIntraType, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szIntraDetailType, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szIsPDWRestored, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szIsIQRestored, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szFirstReportTime, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szFinalReportTime, 0,LENGTH_OF_SHORT_CHAR);	
// 		memset(szStat, 0, LENGTH_OF_SHORT_CHAR);
// 		memset(arrFrqSeq, 0, MAX_FREQ_PRI_STEP*sizeof(int));
// 		memset(arrPRISeq, 0, MAX_FREQ_PRI_STEP*sizeof(int));
// 		memset(arrPriPerGroup, 0, MAX_PRI_PER_GROUP*sizeof(int));
// 		memset(arrPaDiffPerGroup, 0, MAX_PADIFF_PER_GROUP*sizeof(int));
// 		memset(szIsFISINTTask, 0, LENGTH_OF_SHORT_CHAR);
// 		memset(szPRISeq, 0, LENGTH_OF_FRQ_OR_PRI_SEQ_CHAR);
// 		memset(szFrqSeq, 0, LENGTH_OF_FRQ_OR_PRI_SEQ_CHAR);
// 		memset(szPolarization, 0, LENGTH_OF_SHORT_CHAR);
// 		memset(szRxPath, 0, LENGTH_OF_SHORT_CHAR);//LDRA異붽�
// 
// 	}
// };
// 
// struct SAbtInfoToWnd
// {
// 	unsigned long long ullSeqNum;
// 	char szMissionId[LENGTH_OF_MISSION_ID+1];
// 	char szMissionName[SIZE_OF_TASK_NAME];
// 	unsigned int uiAbtId;
// 	unsigned int uiAetId;
// 	int iRadarModeIndex;
// 	int iThreatIndex;
// 	char szTaskType[LENGTH_OF_SHORT_CHAR];
// 	char szElnotPri[LENGTH_OF_SHORT_CHAR];
// 	char szModeCodePri[LENGTH_OF_SHORT_CHAR];
// 	char szModulationCode[LENGTH_OF_SHORT_CHAR];
// 	char szNickName[LENGTH_OF_SHORT_CHAR];
// 	char szPriFuncCode[LENGTH_OF_SHORT_CHAR];
// 	char szPlatform[LENGTH_OF_SHORT_CHAR];
// 	char szPlaceNameKor[LENGTH_OF_SHORT_CHAR]; // 2018-02-22 �븳湲�吏�紐� 異붽�
// 	int nRadarModePriority;
// 	float fDistanceErrFromThreat;
// 	int nRadarPriority;
// 	char szSigType[LENGTH_OF_SHORT_CHAR];
// 	int nNumOfPPG;
// 	int nNumOfLOB;
// 	int iDoaMean; // �빐�긽�룄 0.1 deg
// 	int iDoaMax;
// 	int iDoaMin;
// 	int iDoaDev;
// 	int iDoaStd;
// 	char szFirstDetectTimeInfo[LENGTH_OF_SHORT_CHAR];
// 	char szFinalDetectTimeInfo[LENGTH_OF_SHORT_CHAR];
// 	char szValidity[LENGTH_OF_SHORT_CHAR];
// 	char szFrqType[LENGTH_OF_SHORT_CHAR];
// 	char szFrqPatternType[LENGTH_OF_SHORT_CHAR];
// 	char szHasFrqPeriod[LENGTH_OF_SHORT_CHAR];
// 	int nFrqPeriodMean; // �빐�긽�룄 10khz
// 	int nFrqPeriodMax; // �빐�긽�룄 10khz
// 	int nFrqPeriodMin; // �빐�긽�룄 10khz
// 	int nFrqPositionCount;
// 	int nFrqElementCount;
// 	int nFrqMean; // �빐�긽�룄 10khz
// 	int nFrqMax;
// 	int nFrqMin;
// 	int nFrqDev;
// 	int arrFrqElement[64];
// 	char szFrqElement[LENGTH_OF_FRQ_OR_PRI_SEQ_CHAR];		
// 	char szPriType[LENGTH_OF_SHORT_CHAR];
// 	char szPriPatternType[LENGTH_OF_SHORT_CHAR];
// 	char szHasPriPeriod[LENGTH_OF_SHORT_CHAR];
// 	int nPriPeriodMean; // us
// 	int nPriPeriodMax; // us
// 	int nPriPeriodMin; // us
// 	int nPriPositionCount;
// 	int nPriElementCount;
// 	int nPriMean;
// 	int nPriMax;
// 	int nPriMin;
// 	int nPriDev;
// 	int iPriJitterRatio;
// 	int arrPriElement[64];
// 	char szPriElement[LENGTH_OF_FRQ_OR_PRI_SEQ_CHAR];
// 	int nPwMean;
// 	int nPwMax;
// 	int nPwMin;
// 	int nPwDev;
// 	int nPaMean;
// 	int nPaMax;
// 	int nPaMin;
// 	int nPaDev;
// 	char szScanType[LENGTH_OF_SHORT_CHAR];
// 	int nScanPeriodMinMicroSec;
// 	int nScanPeriodMaxMicroSec;
// 	float fScanPeriodMinHz;
// 	float fScanPeriodMaxHz;
// 	char szHasIntraModulation[LENGTH_OF_SHORT_CHAR];
// 	int nIntraFrqChangeWidthMin;
// 	int nIntraFrqChangeWidthMax;
// 	int arrPriPerGroup[MAX_PRI_PER_GROUP];
// 	int arrPaDiffPerGroup[MAX_PADIFF_PER_GROUP];
// 	// �쐞移섏궛異� 愿��젴
// 	int nPosEstLat;
// 	int nPosEstLong;
// 	int nManualPosEstLat;
// 	int nManualPosEstLong;
// 	int nRepresentPosEstLat;
// 	int nRepresentPosEstLong;
// 	int nAltitude; // meter
// 	int nCEP;// meter
// 	int nLengthOfMajorAxis; // meter
// 	int nLengthOfMinorAxis;
// 	int nEEPTiltAngle; // 0.1�룄 �빐�긽�룄
// 	int nManualPosEstPreferred; // �닔�룞�쐞移섏궛異쒖쓣 �슦�꽑�븳�떎�뒗 indicator.
// 	unsigned int uiNewAetId;
// 	E_EMITTER_OPCODE eOpCodeForUpdate; // �뾽�뜲�씠�듃 �릺�뒗 �궡�슜�씠 �떎�뼇�빐 �졇�꽌, Update Key瑜� �뫊�꽌 �떇蹂꾪븯湲곕줈 �븿. �씠�젙�궓. 2018.4.10.
// 
// 	char szFirstReportTime[LENGTH_OF_SHORT_CHAR];
// 	char szFinalReportTime[LENGTH_OF_SHORT_CHAR];
// 	char szFinalAlarmTime[LENGTH_OF_SHORT_CHAR];
// 	char szPolarization[LENGTH_OF_SHORT_CHAR];
// 	char szStat[LENGTH_OF_SHORT_CHAR];
// 
// 	SAbtInfoToWnd()
// 		:ullSeqNum(0),
// 	uiAbtId(0),
// 	uiAetId(0),
// 	iRadarModeIndex(0), //LDRA異붽�
// 	iThreatIndex(0),//LDRA異붽�
// 	nRadarModePriority(0),
// 	fDistanceErrFromThreat(0.0),
// 	nRadarPriority(0),	
// 	nNumOfPPG(0),
// 	nNumOfLOB(0),
// 	iDoaMean(0), // �빐�긽�룄 0.1 deg
// 	iDoaMax(0),
// 	iDoaMin(0),
// 	iDoaDev(0),
// 	iDoaStd(0),
// 	nFrqPeriodMean(0), // �빐�긽�룄 10khz
// 	nFrqPeriodMax(0), // �빐�긽�룄 10khz
// 	nFrqPeriodMin(0), // �빐�긽�룄 10khz
// 	nFrqPositionCount(0),
// 	nFrqElementCount(0),
// 	nFrqMean(0), // �빐�긽�룄 10khz
// 	nFrqMax(0),
// 	nFrqMin(0),
// 	nFrqDev(0),	
// 	nPriPeriodMean(0), // us
// 	nPriPeriodMax(0), // us
// 	nPriPeriodMin(0), // us
// 	nPriPositionCount(0),
// 	nPriElementCount(0),
// 	nPriMean(0),
// 	nPriMax(0),
// 	nPriMin(0),
// 	nPriDev(0),
// 	iPriJitterRatio(0),	
// 	nPwMean(0),
// 	nPwMax(0),
// 	nPwMin(0),
// 	nPwDev(0),
// 	nPaMean(0),
// 	nPaMax(0),
// 	nPaMin(0),
// 	nPaDev(0),
// 	nScanPeriodMinMicroSec(0),
// 	nScanPeriodMaxMicroSec(0),
// 	fScanPeriodMinHz(0),
// 	fScanPeriodMaxHz(0),
// 	nIntraFrqChangeWidthMin(0),
// 	nIntraFrqChangeWidthMax(0),
// 	nPosEstLat(0),
// 	nPosEstLong(0),
// 	nManualPosEstLat(0),
// 	nManualPosEstLong(0),
// 	nRepresentPosEstLat(0),
// 	nRepresentPosEstLong(0),
// 	nAltitude(0), // meter
// 	nCEP(0),// meter
// 	nLengthOfMajorAxis(0), // meter
// 	nLengthOfMinorAxis(0),
// 	nEEPTiltAngle(0),  // 0.1�룄 �빐�긽�룄
// 	nManualPosEstPreferred(0),
// 	uiNewAetId(0),
// 	eOpCodeForUpdate(E_EO_NOT_AVAILABLE)
// 	{
// 		//@start_�씠�떆�삩
// 		memset(szMissionId, 0,LENGTH_OF_MISSION_ID+1);
// 		memset(szMissionName, 0,SIZE_OF_TASK_NAME);
// 		memset(szTaskType, 0, LENGTH_OF_SHORT_CHAR);
// 		memset(szElnotPri, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szModeCodePri, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szModulationCode, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szNickName, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szPriFuncCode, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szPlatform, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szSigType, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szFirstDetectTimeInfo, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szFinalDetectTimeInfo, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szValidity, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szFrqType, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szFrqPatternType, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szHasFrqPeriod, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(arrFrqElement, 0, 64);
// 		memset(szFrqElement,0,LENGTH_OF_FRQ_OR_PRI_SEQ_CHAR);
// 		memset(szPriType, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szPriPatternType, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szHasPriPeriod, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(arrPriElement,0, 64);
// 		memset(szPriElement, 0, LENGTH_OF_FRQ_OR_PRI_SEQ_CHAR);
// 		memset(szScanType, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szHasIntraModulation, 0,LENGTH_OF_SHORT_CHAR);		
// 		memset(arrPriPerGroup, 0, sizeof(int)*MAX_PRI_PER_GROUP);
// 		memset(arrPaDiffPerGroup, 0, sizeof(int)*MAX_PADIFF_PER_GROUP);
// 		memset(szFirstReportTime,0, LENGTH_OF_SHORT_CHAR);
// 		memset(szFinalReportTime,0, LENGTH_OF_SHORT_CHAR);
// 		memset(szFinalAlarmTime,0, LENGTH_OF_SHORT_CHAR);
// 		memset(szPolarization, 0, LENGTH_OF_SHORT_CHAR);		
// 		memset(szStat, 0, LENGTH_OF_SHORT_CHAR);
// 		memset(szPlaceNameKor, 0, LENGTH_OF_SHORT_CHAR);
// 		//@end_�씠�떆�삩
// 	}
// };
// 
// struct SAetInfoToWnd
// {
// 	unsigned long long ullSeqNum;
// 	char szMissionId[LENGTH_OF_MISSION_ID+1];
// 	char szMissionName[SIZE_OF_TASK_NAME];
// 	char szTaskType[LENGTH_OF_SHORT_CHAR];
// 	unsigned int uiAetId;
// 
// 	//CED 愿��젴 �젙蹂�
// 	int iRadarIndex;
// 	int iThreatIndex;
// 	char szElnotPri[LENGTH_OF_SHORT_CHAR];
// 	char szIdResult[LENGTH_OF_SHORT_CHAR];
// 	char szNickName[LENGTH_OF_SHORT_CHAR];
// 	char szPriFuncCode[LENGTH_OF_SHORT_CHAR];
// 	int nRadarPriority;
// 	
// 	//EOB 愿��젴
// 	unsigned int uiPinNum;
// 	char szThreatName[LENGTH_OF_SHORT_CHAR];
// 	char szBENumber[LENGTH_OF_SHORT_CHAR];
// 	char szThreatFuncCode[LENGTH_OF_SHORT_CHAR];
// 	int nThreatPriority;
// 	float fDistanceErrFromThreat; // Nautical Mile
// 	int iEquipNumber;
// 	//char szEquipNumber[LENGTH_OF_SHORT_CHAR];
// 
// 	int nNumOfLOB;
// 	int nNumOfBeam;
// 	char szFirstDetectTimeInfo[LENGTH_OF_SHORT_CHAR];
// 	char szFinalDetectTimeInfo[LENGTH_OF_SHORT_CHAR];
// 	char szValidity[LENGTH_OF_SHORT_CHAR];
// 	int nFrqMean; // �빐�긽�룄 10khz
// 	int nFrqMax;
// 	int nFrqMin;
// 	int nFrqDev;
// 	int nPriMean;
// 	int nPriMax;
// 	int nPriMin;
// 	int nPriDev;
// 	int nPrfMean;
// 	int nPrfMax;
// 	int nPrfMin;
// 	int nPrfDev;
// 	int nPrfMinPPS;
// 	int nPrfMaxPPS;
// 	int nPwMean;
// 	int nPwMax;
// 	int nPwMin;
// 	int nPwDev;
// 	int nPaMean;
// 	int nPaMax;
// 	int nPaMin;
// 	int nPaDev;
// 	// �쐞移섏궛異� 愿��젴
// 	char szPosEstValidity[LENGTH_OF_SHORT_CHAR];
// 	int nPosEstLat; // �옄�룞�쑝濡� 媛깆떊�릺�뒗 �쐞移� �궛異쒓컪
// 	int nPosEstLong; // �옄�룞�쑝濡� 媛깆떊�릺�뒗 �쐞移� �궛異쒓컪
// 	int nManualPosEstLat; // 怨좎젙�맂 �닔�룞�쐞移� �궛異쒓컪
// 	int nManualPosEstLong; // 怨좎젙�맂 �닔�룞�쐞移� �궛異쒓컪	
// 	int nRepresentPosEstLat; // ���몴 �쐞移� �쐞�룄
// 	int nRepresentPosEstLong; // ���몴 �쐞移� 寃쎈룄
// 	int nAltitude; // meter
// 	int nCEP;// meter
// 	int nLengthOfMajorAxis; // meter
// 	int nLengthOfMinorAxis;
// 	int nEEPTiltAngle; // 0.1�룄 �빐�긽�룄
// 	int nManualPosEstPreferred; // �닔�룞�쐞移섏궛異쒖쓣 �슦�꽑�븳�떎�뒗 indicator.
// 
// 	E_EMITTER_OPCODE eOpCodeForUpdate; // �뾽�뜲�씠�듃 �릺�뒗 �궡�슜�씠 �떎�뼇�빐 �졇�꽌, Update Key瑜� �뫊�꽌 �떇蹂꾪븯湲곕줈 �븿. �씠�젙�궓. 2018.4.10.
// 	char szManualPosEstPreferred[LENGTH_OF_SHORT_CHAR];
// 	char szFirstReportTime[LENGTH_OF_SHORT_CHAR];
// 	char szFinalReportTime[LENGTH_OF_SHORT_CHAR];
// 	char szFinalAlarmTime[LENGTH_OF_SHORT_CHAR];
// 
// 	char szStat[LENGTH_OF_SHORT_CHAR];
// 
// 	SAetInfoToWnd()
// 	:ullSeqNum(0)
// 	 ,uiAetId(0)
// 	 ,iRadarIndex(0)
// 	 ,iThreatIndex(0)
// 	 ,nRadarPriority(0)
// 	 ,uiPinNum(0)
// 	 ,nThreatPriority(0)
// 	 ,fDistanceErrFromThreat(0.0) // Nautical Mile
// 	 ,iEquipNumber(0)
// 	 ,nNumOfLOB(0)
// 	 ,nNumOfBeam(0)
// 	 ,nFrqMean(0) // �빐�긽�룄 10khz
// 	 ,nFrqMax(0)
// 	 ,nFrqMin(0)
// 	 ,nFrqDev(0)
// 	 ,nPriMean(0)
// 	 ,nPriMax(0)
// 	 ,nPriMin(0)
// 	 ,nPriDev(0)
// 	 ,nPrfMean(0)
// 	 ,nPrfMax(0)
// 	 ,nPrfMin(0)
// 	 ,nPrfDev(0)
// 	 ,nPrfMinPPS(0)
// 	 ,nPrfMaxPPS(0)
// 	 ,nPwMean(0)
// 	 ,nPwMax(0)
// 	 ,nPwMin(0)
// 	 ,nPwDev(0)
// 	 ,nPaMean(0)
// 	 ,nPaMax(0)
// 	 ,nPaMin(0)
// 	 ,nPaDev(0)
// 	 ,nPosEstLat(0)
// 	 ,nPosEstLong(0)
// 	 ,nManualPosEstLat(0)
// 	 ,nManualPosEstLong(0)
// 	 ,nRepresentPosEstLat(0)
// 	 ,nRepresentPosEstLong(0)
// 	 ,nAltitude(0) // meter
// 	 ,nCEP(0)// meter
// 	 ,nLengthOfMajorAxis(0) // meter
// 	 ,nLengthOfMinorAxis(0)
// 	 ,nEEPTiltAngle(0) // 0.1�룄 �빐�긽�룄
// 	 ,nManualPosEstPreferred(0)
// 	 ,eOpCodeForUpdate(E_EO_NOT_AVAILABLE)
// 	 //,szManualPosEstPreferred(0)
// 	{
// 		//@start_�씠�떆�삩
// 		memset(szMissionId, 0, LENGTH_OF_MISSION_ID+1);
// 		memset(szMissionName, 0, SIZE_OF_TASK_NAME);
// 		memset(szTaskType, 0, SIZE_OF_TASK_NAME);
// 		memset(szElnotPri, 0, LENGTH_OF_SHORT_CHAR);
// 		memset(szIdResult, 0, LENGTH_OF_SHORT_CHAR);
// 		memset(szNickName, 0, LENGTH_OF_SHORT_CHAR);
// 		memset(szPriFuncCode, 0, LENGTH_OF_SHORT_CHAR);		
// 		memset(szThreatName, 0, LENGTH_OF_SHORT_CHAR);
// 		memset(szBENumber, 0, LENGTH_OF_SHORT_CHAR);
// 		memset(szThreatFuncCode, 0, LENGTH_OF_SHORT_CHAR);	
// 		//memset(szEquipNumber, 0, LENGTH_OF_SHORT_CHAR);	
// 		memset(szFirstDetectTimeInfo, 0, LENGTH_OF_SHORT_CHAR);
// 		memset(szFinalDetectTimeInfo, 0, LENGTH_OF_SHORT_CHAR);
// 		memset(szValidity, 0, LENGTH_OF_SHORT_CHAR);	
// 		memset(szPosEstValidity, 0, LENGTH_OF_SHORT_CHAR);
// 		memset(szManualPosEstPreferred, 0, LENGTH_OF_SHORT_CHAR);
// 		memset(szFirstReportTime, 0, LENGTH_OF_SHORT_CHAR);
// 		memset(szFinalReportTime, 0, LENGTH_OF_SHORT_CHAR);
// 		memset(szFinalAlarmTime, 0, LENGTH_OF_SHORT_CHAR);
// 		memset(szStat, 0, LENGTH_OF_SHORT_CHAR);
// 
// 		//@end_�씠�떆�삩
// 		
// 	}
// };

// GUI->LOGIC
// struct SCommonListWndSelect
// {
// 	int nAetId;
//     int nAbtId;
// 	int nLobId;
// 	std::string strRecentTime;
// 	SCommonListWndSelect()
// 	:nAetId(0)
// 	,nAbtId(0)
// 	,nLobId(0)
// 	,strRecentTime("")
//     {}
// };


#define NUM_OF_MANUAL_INPUT_COUNT	_	36

#define DF_MANUAL_SIG_SIGTYPE				(0x0000000000000001)		/*�떊�샇�삎�깭-----*/
#define DF_MANUAL_SIG_MODTYPE				(0x0000000000000002)		/*蹂�議고삎�깭-----*/
#define DF_MANUAL_SIG_POLARIZATION		(0x0000000000000004)		/*洹뱀꽦*/
#define DF_MANUAL_DOA_MEAN					(0x0000000000000008)		/*諛⑹쐞媛� �룊洹�-----*/
#define DF_MANUAL_DOA_MAX					(0x0000000000000010)		/*諛⑹쐞媛� 理쒕�-----*/
#define DF_MANUAL_DOA_MIN						(0x0000000000000020)		/*諛⑹쐞媛� 理쒖냼-----*/
#define DF_MANUAL_POSEST_NS					(0x0000000000000040)		/*NS*/
#define DF_MANUAL_POSEST_LAT				(0x0000000000000080)		/*�쐞�룄*/
#define DF_MANUAL_POSEST_EW					(0x0000000000000100)		/*EW*/
#define DF_MANUAL_POSEST_LONG				(0x0000000000000200)		/*寃쎈룄*/
#define DF_MANUAL_FRQ_FRQTYPE				(0x0000000000000400)		/*二쇳뙆�닔 �삎�깭-----*/
#define DF_MANUAL_FRQ_MEAN					(0x0000000000000800)		/*二쇳뙆�닔 �룊洹�-----*/
#define DF_MANUAL_FRQ_MAX						(0x0000000000001000)		/*二쇳뙆�닔 理쒕�-----*/
#define DF_MANUAL_FRQ_MIN						(0x0000000000002000)		/*二쇳뙆�닔 理쒖냼-----*/
#define DF_MANUAL_FRQ_CHNG_WIDTH		(0x0000000000004000)		/*二쇳뙆�닔 蹂�寃쏀룺*/
#define DF_MANUAL_FRQ_PERIOD				(0x0000000000008000)		/*二쇨린-----*/
#define DF_MANUAL_FRQ_STEP					(0x0000000000010000)		/*�떒�닔*/
#define DF_MANUAL_FRQ_LEVEL					(0x0000000000020000)		/*�젅踰�*/
#define DF_MANUAL_PRI_PRITYPE					(0x0000000000040000)		/*PRI �삎�깭-----*/
#define DF_MANUAL_PRI_MEAN					(0x0000000000080000)		/*PRI �룊洹�-----*/
#define DF_MANUAL_PRI_MAX						(0x0000000000100000)		/*PRI 理쒕�-----*/
#define DF_MANUAL_PRI_MIN						(0x0000000000200000)		/*PRI 理쒖냼-----*/
#define DF_MANUAL_PRI_CHNG_WIDTH		(0x0000000000400000)		/*PRI 蹂�寃쏀룺*/
#define DF_MANUAL_PRI_PERIOD					(0x0000000000800000)		/*二쇨린-----*/
#define DF_MANUAL_PRI_STEP						(0x0000000001000000)		/*�떒�닔*/
#define DF_MANUAL_PRI_CHNG_RATIO			(0x0000000002000000)		/*PRI 蹂�寃쎈쪧*/
#define DF_MANUAL_PRI_LEVEL					(0x0000000004000000)		/*�젅踰�*/
#define DF_MANUAL_ELNOT							(0x0000000008000000)		/*ELNOT-----*/
#define DF_MANUAL_PA_MEAN						(0x0000000010000000)		/*PA �룊洹�-----*/
#define DF_MANUAL_PA_MAX						(0x0000000020000000)		/*PA 理쒕�-----*/
#define DF_MANUAL_PA_MIN						(0x0000000040000000)		/*PA 理쒖냼-----*/
#define DF_MANUAL_PA_SCAN_TYPE				(0x0000000080000000)		/*�뒪罹뷀��엯-----*/
#define DF_MANUAL_PA_SCAN_PERIOD			(0x0000000100000000)		/*�뒪罹붿＜湲�*/
#define DF_MANUAL_PW_MEAN					(0x0000000200000000)		/*PW �룊洹�*/
#define DF_MANUAL_PW_MAX					(0x0000000400000000)		/*PW 理쒕�*/
#define DF_MANUAL_PW_MIN						(0x0000000800000000)		/*PW 理쒖냼*/
#define DF_MANUAL_PIN_NUM					(0x000000100000000)			/*PIN NUMBER _ 2015.10.31. 異붽�*/

struct SFLTMData
{
	int nFrqType;
	int nPriType;
	int nMeanFrq;
	int nMeanPri;
	int nMeanPw;
	int nMeanPa;
	int nMeanDoa;
	int nAntDir;
        SFLTMData()
		:nFrqType(0)
		,nPriType(0)
		,nMeanFrq(0)
		,nMeanPri(0)
		,nMeanPw(0)
		,nMeanPa(0)
		,nMeanDoa(0)
		,nAntDir(0)
	{};
};


//////////////////////////////////////////////////////////////////////////
// 諛⑹궗泥�/鍮�/LOB 李쎌뿉�꽌 CED/EOB 李쎌쑝濡� �뜲�씠�꽣瑜� �쟾�떖�븯湲� �쐞�븳 援ъ“泥� �젙�쓽
// typedef struct {
// 	SRadar stSRadar;
// 	EnumLibType enLibType;
// 
// } SELCALLCEDLIB;

// CED �깮�꽦�떆 李몄“�릺�뒗 �씤�옄
// typedef struct {
// 	int nAETId;
// 	int nABTId;
// 
// 	char szMissionId[LENGTH_OF_MISSION_ID+2];
// 
// } SELCEDCREATE ;


struct SELCHECKRANGE {
	bool bCheckBox;
	float low;
	float high;
} ;

enum EnumRangeSearchRef {
	enumIncludeAllInput=0,						// �엯�젰踰붿쐞瑜� 紐⑤몢�룷�븿
	enumOverlapWithInnerInput,				// �엯�젰 踰붿쐞 �궡遺��뿉 以묒꺽
	enumOverlapWithInput							// �엯�젰 踰붿쐞�� 以묒꺽

} ;


// typedef struct {
// 	//EnumLibType enLibType;	// 湲곕낯�삎 �삉�뒗 �떎臾댄삎
// 
// 	CString strELNOT;
// 	CString strNickName;
// 	int iPin;
// 	EnumFunctionCodes eFunctionCodes_ForGUI;	// 二쇨린�뒫 肄붾뱶
// 	EnumRadarStatus eStatus;									// �긽�깭
// 	CString strAssocWeapSys;									// �뿰愿� 臾닿린 泥닿퀎
// 	CString strAssocPlatform;									// �뿰愿� �뵆�젅�뤌
// 
// 	EnumRangeSearchRef eRangeSearchRef;			// 踰붿쐞 寃��깋 湲곗�
// 
// 	SELCHECKRANGE stFreq;											// 二쇳뙆�닔 踰붿쐞
// 	SELCHECKRANGE stPRI;											// PRI 踰붿쐞
// } SELRADARLIST_SEARCH_FILTER;


struct SELRANGE {
	int low;
	int high;
} ;

// typedef struct stSELRADARMODELIST_SEARCH_FILTER{
// 	EnumLibType enLibType;	// 湲곕낯�삎 �삉�뒗 �떎臾댄삎
// 
// 	// 諛⑹궗泥�
// 	CString strELNOT;
// 	CString strNickName;
// 	int iPin;
// 	EnumRadarStatus eStatus;									// �긽�깭
// 	CString strAssocWeapSys;									// �뿰愿� 臾닿린 泥닿퀎
// 	CString strAssocPlatform;									// �뿰愿� �뵆�젅�뤌
// 
// 	// 紐⑤뱶�젣�썝
// 	PlatformCode::EnumPlatformCode ePlatform;
// 	EnumValidationCode eValidation;
// 	EnumFunctionCodes	eFunctionCode;	// 二쇨린�뒫 肄붾뱶
// 	SignalType::EnumSignalType eSignalType;									//�떊�샇�삎�깭 (Pulsed, CW, EA) enum�삎�깭
// 	ScanType::EnumScanType	eScanPrimaryType;								//二� �뒪罹뷀��엯 肄붾뱶(SCAN_TYPE_CODE 李몄“)
// 	CString strModulationCode;												//* 蹂�議곗퐫�뱶(2) [怨꾩궛�븘�슂]
// 	PolizationCode::EnumPolizationCode ePolarization;
// 	EnumRangeSearchRef eRangeSearchRef;
// 	float fRF_TypicalMin;													//二쇨�痢〓쾾�쐞: 二쇳뙆�닔 Typical 理쒖냼(MHz)
// 	float fRF_TypicalMax;													//二쇨�痢〓쾾�쐞: 二쇳뙆�닔 Typical 理쒕�(MHz)
// 	float fPRI_TypicalMin;													//PRI TYPICAL (USEC) 理쒖냼
// 	float fPRI_TypicalMax;													//PRI TYPICAL (USEC) 理쒕�
// 	float fScanPrimaryTypicalMin;											//二� �뒪罹� 二쇨린媛믪쓽 TYPICAL (SEC) 理쒖냼
// 	float fScanPrimaryTypicalMax;											//二� �뒪罹� 二쇨린媛믪쓽 TYPICAL (SEC) 理쒕�
// 	float fPD_TypicalMin;													//PD TYPICAL 媛� (USEC) 理쒖냼
// 	float fPD_TypicalMax;													//PD TYPICAL 媛� (USEC) 理쒕�
// 
// 	// 二쇳뙆�닔
// 	ContinuityCode::EnumContinuityCode eRF_Continuity;						//二쇳뙆�닔 媛믩텇�룷�뿰�냽�꽦: RF 蹂��솕�쓽 �뿰�냽�꽦 (CONTINUITY_CODE 李몄“)
// 	PatternCode::EnumPatternCode eRF_Pattern;								//RF 蹂��솕�쓽 �뙣�꽩 �뿬遺� (PATTERN_CODE 李몄“)
// 	EnumRF_LagacyTypeCode eRF_LagacyType;									//RF_LEGACY_TYPE_CODE 李몄“
// 	SELRANGE stRF_NumElements;													//NUMBER	PRI ELEMENT �닔
// 	SELRANGE stRF_NumPositions;													//NUMBER	PRI POSITION �닔
// 
// 	// PD
// 	ContinuityCode::EnumContinuityCode ePD_Continuity;						//PD媛믪쓽 �뿰�냽�꽦 (CONTINUITY_CODE 李몄“)
// 	PatternCode::EnumPatternCode ePD_Pattern;								//PD媛믪쓽 �뙣�꽩�뿬遺� (PATTERN_CODE 李몄“)
// 	SELRANGE stPD_NumElements;													//PD ELEMENT �닔
// 	SELRANGE stPD_NumPositions;													//PD Positon �닔
// 	float fPD_PatternPeriodMin;												//PD �뙣�꽩二쇨린 (USEC) 理쒖냼
// 	float fPD_PatternPeriodMax;												//PD �뙣�꽩二쇨린 (USEC) 理쒕�
// 
// 	// PRI
// 	ContinuityCode::EnumContinuityCode ePRI_Continuity;						//PRI 蹂��솕�쓽 �뿰�냽�꽦 (CONTINUITY_CODE 李몄“)
// 	PatternCode::EnumPatternCode ePRI_Pattern;								//NUMBER PRI蹂��솕�쓽 �뙣�꽩�뿬遺�	(PATTERN_CODE 李몄“)
// 	EnumPRI_LegacyTypeCode ePRI_LagacyType;									//PRI_LAGACY_TYPE_CODE 李몄“
// 	SELRANGE stPRI_NumElements;													//NUMBER	PRI ELEMENT �닔
// 	SELRANGE stPRI_NumPositions;													//NUMBER	PRI POSITION �닔
// 	float fPRI_FramePeriodMin;												//PRI FRAME 二쇨린 (USEC) 理쒖냼
// 	float fPRI_FramePeriodMax;												//PRI FRAME 二쇨린 (USEC) 理쒕�
// 	float fPRI_SubframePeriodMin;											//PRI SUBFRAME 二쇨린 (USEC) 理쒖냼
// 	float fPRI_SubframePeriodMax;											//PRI SUBFRAME 二쇨린 (USEC) 理쒕�
// 	float fPRI_PPG_Min;														//Pulse Per Group 理쒖냼
// 	float fPRI_PPG_Max;														//Pulse Per Group 理쒕�
// 
// 	// �럡�뒪�궡 蹂�議�
// 	MOP_CW_ModulationType::EnumMOP_CW_ModulationType eMOP_CW_ModulationType;	//�럡�뒪 �궡 �삉�뒗 CW 蹂�議고삎�깭 (MOP_CW_MOD_TYPE_CODE 李몄“)
// 	EnumMOP_CW_LegacyType eMOP_CW_LegacyType;					//蹂�議고삎�깭�쓽 LEGACY TERM (MOP_CW_LEGACY_TYPE_CODE)
// 
// 	stSELRADARMODELIST_SEARCH_FILTER()
// 	{
// 		enLibType = E_EL_LIB_TYPE_NORMAL;	// 湲곕낯�삎 �삉�뒗 �떎臾댄삎
// 
// 		// 諛⑹궗泥�
// 		strELNOT="";
// 		strNickName="";
// 		iPin = 0;
// 		eStatus = enumUndefinedRadarStatus;									// �긽�깭
// 		strAssocWeapSys="";									// �뿰愿� 臾닿린 泥닿퀎
// 		strAssocPlatform="";									// �뿰愿� �뵆�젅�뤌
// 
// 		// 紐⑤뱶�젣�썝
// 		ePlatform = PlatformCode::enumUndefinedPlatformCode;
// 		eValidation=enumUndefinedValidationCode;
// 		eFunctionCode=enumUndefinedFunctionCode;	// 二쇨린�뒫 肄붾뱶
// 		eSignalType=SignalType::enumSignalUndefined;									//�떊�샇�삎�깭 (Pulsed, CW, EA) enum�삎�깭
// 		eScanPrimaryType=ScanType::enumUndefinedScanType;								//二� �뒪罹뷀��엯 肄붾뱶(SCAN_TYPE_CODE 李몄“)
// 		strModulationCode="";												//* 蹂�議곗퐫�뱶(2) [怨꾩궛�븘�슂]
// 		ePolarization=PolizationCode::enumUndefinedPolization;
// 		eRangeSearchRef=enumIncludeAllInput;
// 		fRF_TypicalMin=0.0f;													//二쇨�痢〓쾾�쐞: 二쇳뙆�닔 Typical 理쒖냼(MHz)
// 		fRF_TypicalMax=0.0f;													//二쇨�痢〓쾾�쐞: 二쇳뙆�닔 Typical 理쒕�(MHz)
// 		fPRI_TypicalMin=0.0f;													//PRI TYPICAL (USEC) 理쒖냼
// 		fPRI_TypicalMax=0.0f;													//PRI TYPICAL (USEC) 理쒕�
// 		fScanPrimaryTypicalMin=0.0f;											//二� �뒪罹� 二쇨린媛믪쓽 TYPICAL (SEC) 理쒖냼
// 		fScanPrimaryTypicalMax=0.0f;											//二� �뒪罹� 二쇨린媛믪쓽 TYPICAL (SEC) 理쒕�
// 		fPD_TypicalMin=0.0f;													//PD TYPICAL 媛� (USEC) 理쒖냼
// 		fPD_TypicalMax=0.0f;													//PD TYPICAL 媛� (USEC) 理쒕�
// 
// 		// 二쇳뙆�닔
// 		eRF_Continuity=ContinuityCode::enumUndefinedContinuityCode;						//二쇳뙆�닔 媛믩텇�룷�뿰�냽�꽦: RF 蹂��솕�쓽 �뿰�냽�꽦 (CONTINUITY_CODE 李몄“)
// 		eRF_Pattern=PatternCode::enumUndefinedPatternCode;								//RF 蹂��솕�쓽 �뙣�꽩 �뿬遺� (PATTERN_CODE 李몄“)
// 		eRF_LagacyType=enumUndefinedRF_LagacyType;									//RF_LEGACY_TYPE_CODE 李몄“
// 		stRF_NumElements = SELRANGE();													//NUMBER	PRI ELEMENT �닔
// 		stRF_NumPositions = SELRANGE();													//NUMBER	PRI POSITION �닔
// 
// 		// PD
// 		ePD_Continuity=ContinuityCode::enumUndefinedContinuityCode;						//PD媛믪쓽 �뿰�냽�꽦 (CONTINUITY_CODE 李몄“)
// 		ePD_Pattern=PatternCode::enumUndefinedPatternCode;								//PD媛믪쓽 �뙣�꽩�뿬遺� (PATTERN_CODE 李몄“)
// 		stPD_NumElements = SELRANGE();													//PD ELEMENT �닔
// 		stPD_NumPositions = SELRANGE();													//PD Positon �닔
// 		fPD_PatternPeriodMin=0.0f;												//PD �뙣�꽩二쇨린 (USEC) 理쒖냼
// 		fPD_PatternPeriodMax=0.0f;												//PD �뙣�꽩二쇨린 (USEC) 理쒕�
// 
// 		// PRI
// 		ePRI_Continuity=ContinuityCode::enumUndefinedContinuityCode;						//PRI 蹂��솕�쓽 �뿰�냽�꽦 (CONTINUITY_CODE 李몄“)
// 		ePRI_Pattern=PatternCode::enumUndefinedPatternCode;								//NUMBER PRI蹂��솕�쓽 �뙣�꽩�뿬遺�	(PATTERN_CODE 李몄“)
// 		ePRI_LagacyType=enumUndefinedPRI_LegacyType;									//PRI_LAGACY_TYPE_CODE 李몄“
// 		stPRI_NumElements = SELRANGE();													//NUMBER	PRI ELEMENT �닔
// 		stPRI_NumPositions = SELRANGE();													//NUMBER	PRI POSITION �닔
// 		fPRI_FramePeriodMin=0.0f;												//PRI FRAME 二쇨린 (USEC) 理쒖냼
// 		fPRI_FramePeriodMax=0.0f;												//PRI FRAME 二쇨린 (USEC) 理쒕�
// 		fPRI_SubframePeriodMin=0.0f;											//PRI SUBFRAME 二쇨린 (USEC) 理쒖냼
// 		fPRI_SubframePeriodMax=0.0f;											//PRI SUBFRAME 二쇨린 (USEC) 理쒕�
// 		fPRI_PPG_Min=0.0f;														//Pulse Per Group 理쒖냼
// 		fPRI_PPG_Max=0.0f;														//Pulse Per Group 理쒕�
// 
// 		// �럡�뒪�궡 蹂�議�
// 		eMOP_CW_ModulationType=MOP_CW_ModulationType::enumUndefinedMOP_CW_ModulationType;	//�럡�뒪 �궡 �삉�뒗 CW 蹂�議고삎�깭 (MOP_CW_MOD_TYPE_CODE 李몄“)
// 		eMOP_CW_LegacyType=enumUndefinedMOP_CW_LegacyType;					//蹂�議고삎�깭�쓽 LEGACY TERM (MOP_CW_LEGACY_TYPE_CODE)
// 	}
// 
// } SELRADARMODELIST_SEARCH_FILTER;

// typedef struct {
// 	EnumLibType enLibType;	// 湲곕낯�삎 �삉�뒗 �떎臾댄삎
// 
// 	int iPin;
// 	CString strBE_Number;
// 	CString strFacilityName;											//湲곗�紐낆묶 (�쐞�삊紐�)
// 
// 	EnumFunctionCodes ePrimaryFunction_ForGUI;		//二쇨린�뒫肄붾뱶
// 	FriendOrFOE::EnumFriendOrFOE eFriendOrFOE;		//�쟻�븘援щ텇 enum媛�
// 
// 	CString strPlaceNameKor;										//�븳湲�吏�紐� (50)
// 	CString strPlaceNameEng;										//�쁺臾몄�紐� (50)
// 
// 	CString strCategory;												//�옄泥� 援щ텇 移댄뀒怨좊━ (99999 �삎�떇)(5)
// 	CString strADA;														//��怨듬갑怨듦뎄�뿭 (ADA) (AA123 �삎�떇) (5)
// 
// 	CountryCode::EnumCountryCode eUserCountry;	//�궗�슜援�媛�瑜� enum�쑝濡� �몴�쁽
// 	PlatformCode::EnumPlatformCode ePlatform;			//�깙�옱 �뵆�옯�뤌�쓽 醫낅쪟 (PLATFORM_CODE 李몄“)
// 
// } SELTHREATLIST_SEARCH_FILTER;

//#endif




/************************************************************************************
*   ELINT View -> Logic�뿉 �궗�슜�릺�뒗 �옄猷뚰삎 援ъ“泥�
*************************************************************************************/

#endif
