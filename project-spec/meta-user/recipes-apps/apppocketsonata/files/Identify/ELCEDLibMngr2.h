/**
 * @file      ELCEDLibMngr2.h
 * @brief     
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-03-08, 오후 7:20 
 * @warning   
 */


#ifndef H_EL_CED_LIB_MNGR_2
#define H_EL_CED_LIB_MNGR_2
#pragma once

#include <vector>
#include <list>
#include <map>

#include "../TASK/ELMsgQThread.h" 
#include "..\..\CEFCOMMON\CommonControllerIF.h"
#include "..\..\CEFCOMMON\CommonMngr.h"
#include "..\..\COMMON\DBIF\Elintdb.h"
#include "..\..\COMMON\DBIF\ElintLIBDataTypedb.h"

#include "..\ACTIONTYPE\ELCEDLibActionType2.h"
#include "..\ACTIONTYPE\ELCommonListActionType.h"
#include "..\DATATYPE\ELCEDLibDataType2.h"
#include "..\DATATYPE\ELGMIMsgDefn.h"

#include "..\DEFINE\ELMsgDefn.h"
#include "..\..\ASAE\PopDialogEI\ELCEDCommon.h"

#include "../ACTIONTYPE/ELManualTaskActionType.h"
#include "ELManualTaskMngr.h"


#define RF_MODULATIONCODE_RULE_FILE			"./../COMMON/rfModulationCodeConversionRule.xml"
#define PRI_MODULATIONCODE_RULE_FILE		"./../COMMON/priModulationCodeConversionRule.xml"

#define MAX_OF_FIELDLIST								(9999999)

#define	MAX_COLUMS_OF_RADAR_MODE_TABLE		(314)
#define	MAX_COLUMS_OF_RADAR_MOP_CW_TABLE	(41)

// 쓰레드 커맨드
enum EN_THREAD_COMMAND {
	LOAD_XML = 1,
	LOAD_XML2
};

// CED/EOB 변경 값
enum EN_CEDEOB_UPDATE {
	// EOB 기본형을 실무형으로 이동
	enCopyEobToPrtc = 1,

	// EOB 실무형에 위협/장비 추가/변경/삭제
	enUpdatePrtcThreat,

	// EOB 기본형 불러오기
	enImportThreatAndDevice,

	// EOB 실무형 전체 삭제
	enDeleteAllPrtcEOBData,

	// CED 기본형 레이더를 실무형으로 이동
	enCopyRadarToPrtc,

	// CED 실무형 레이더를 추가/변경/삭제
	enDeletePrtcRadars,

	// CED 실무형 레이더모드를 추가/변경/삭제
	enUpdatePrtcRadarMode,
	enDeletePrtcRadarModes,

	// CED 기본형 레이더 모드를 실무형으로 이동
	enCopyRadarModeToPrtc,

	// CED 기본형 불러오기
	enLoadXMLFiles,

	// CED 실무형 전체 삭제
	enDeleteAllPrtcCEDData
};

/**
* [식별자 : CLS-GMU-EL-L-SIM]
*
* [추적성 : SRS-G-SAFR-013]
*
* @class	CELCEDLibMngr2
* @brief	CED/EOB 위협 목록창, 레이더모드 창 관련 뷰와 로직간의 게이트웨이 역할을 해주는 클래스
*
* (1) 클래스 설명
* - 본 클래스는 자료관리 CED/EOB 관련 정보 보기, 생성, 전시, 불러오기, 내보내기 기능 등을 수행하는 클래스이다.
*
* (2) 설계결정사항
* - 해당사항 없음
*
* (3) 제한 및 예외처리
* - 해당사항 없음
*/
class CELCEDLibMngr2 : public CCommonMngr
{
	friend class CELCEDLibController2;
private:
	CELCEDLibMngr2(void);
public:
	~CELCEDLibMngr2(void);

private:
	void Receive(unsigned int i_uiOpcode, unsigned short i_usSize, unsigned short i_usOperatorID, void* i_pvData,  bool i_bServer = false, bool i_bReplay = false){}
	void XMLRowToDB(CString &i_strXMLPath, CString &i_strXMLFile);
	
	bool GetDataFromDB(EnumLibType i_eLibType, EnumLoadType enLoadType );
	void InitModCodeGererator();
	CString GenerateModCode(SRadarMode &i_stRadarMode);
	void DeleteAllBasicCEDData( CString *pStrTableName );
	void DeleteAllBasicCEDData();
	void DeleteAllBasicEOBData();

	void ClearCEDData(EnumLibType i_eLibType);
	void ClearEOBData(EnumLibType i_eLibType);

	//void CalculateThreatLonLat(EnumLibType i_eLibType);
	void UpdateThreatLonLat(SThreat &i_stThreat, EnumLibType i_eLibType);

	//////////////////////////////////////////////////////////////////////////
	//
	bool GetCEDDataFromDB(EnumLibType i_eLibType, EnumLoadType enLoadType=E_EL_NO_LOAD);
	bool GetEOBDataFromDB(EnumLibType i_eLibType);
	bool GetParamSetAssocTypeCode();

	void MakeRadarInfo( SRadar *pRadar, SELCEDCREATE *pSELCEDCREATE, UINT uiMode );
	void MakeRadarModeInfo( SRadarMode *pRadarMode, std::list<SELDBGmiAbt*> *pListData );
	void MakeRadarModeInfo( SRadarMode *pRadarMode, std::list<SELDBGmiAet*> *pListData );
	void MakePolizatioan( SRadarMode *pRadar, SELDBGmiAbt *pSELDBGmiAbt );
	void MakePolizatioan( SRadarMode *pRadar, SELDBGmiAet *pSELDBGmiAet );
	void MakeScanType( SRadarMode *pRadar, SELDBGmiAbt *pSELDBGmiAbt );
	void MakeScanType( SRadarMode *pRadar, SELDBGmiAet *pSELDBGmiAet );
	void MakeScanRange( SRadarMode *pRadar, SELDBGmiAbt *pSELDBGmiAbt );
	void MakeScanRange( SRadarMode *pRadar, SELDBGmiAet *pSELDBGmiAet );

	// 기본적으로 문자열 테이블을 로드하는 함수
	void LoadCEDEOBStringTable();

	int UpdateColumnOfTable( CString *pstrTable, int nColumnLength );

	void InsertOneRowToDB( string tableName, EL_FIELD_INFO *field, int nFieldInfo, EL_FIELD_INFO *pAddFieldInfo );
	bool FindSetValue( EL_FIELD_INFO *pField, int nFieldInfo, char *pSetFieldName, char *pSetValue );

	RadarModeFreqType::EnumRadarModeFreqType GetNewFreqType( EL_FIELD_INFO *field, int nFieldInfo );
	RadarModePRIType::EnumRadarModePRIType GetNewPRIType( EL_FIELD_INFO *field, int nFieldInfo );

public:
	static CELCEDLibMngr2* GetUniqueInstance();				///< 객체 포인터
	CELCEDComon m_CELCEDComon;												///< CED 기능 객체
	BOOL m_bIsReCalLatLon[E_EL_LIB_TYPE_PRACTICAL+1];	///< 위/경도 계산 플레그
	char m_modCodeResult[3];													///< 변조코드 라이브러리 호출시 결과 문자열

private:
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// View-Logic간 함수
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void InitializeRadarListData(EnumLibType i_eLibType, bool bIsDB = false);
	void InitializeRadarModeListData(EnumLibType i_eLibType, bool bIsDB = false);
	void InitializePlatformList(EnumLibType i_eLibType);
	void InitializeWeaponSystemList(EnumLibType i_eLibType);
	void InitializeDeviceList(EnumLibType i_eLibType, bool bIsDB = false);
	void InitializeThreatList(EnumLibType i_eLibType, bool bIsDB = false);
	void LoadXMLFiles(vector<pair<CString, CString> > &i_vecXMLFiles);
	//void RunThreadLoadXMLFiles(vector<pair<CString, CString> > &i_vecXMLFiles);
	void ImportThreatAndDevice( vector<SEobExcelData> &i_vecEobExcel );
	void ArrangeThreatAndDevice( vector<SEobExcelData> *pVecEobExcel );
	void UpdateDBThreatLatLong( int nThreatIndex, EnumLibType i_eLibType );
	void SetWindowState(EnumLibraryWndType &i_eWndType, bool i_bIsOpen);
	void SetDeleteAllPrtcEOBDataStatus(bool bIsDelete);
	void SetDeleteAllPrtcCEDDataStatus(bool bIsDelete);

	void DeleteAllPrtcCEDData();
	void DeleteAllPrtcEOBData();
	void DeletePrtcRadars(vector<int> &i_vecRadarIndex);
	// RADAR_INDEX에 의한 RADAR 및 관련목록 삭제 
	void DeletePrtcRadar(int i_nRadarIndex);
	void DeletePrtcRadarModes(vector<int> &i_vecRadexModeIndex);
	void DeletePrtcRadarMode(int i_nRadarModeIndex);
	void DeletePrtcPlatforms(vector<long> &i_vecPlatformIndex);
	void DeletePrtcWeaponSystems(vector<long> &i_vecWeaponSystemIndex);
	void DeletePrtcThreats(vector<int> &i_vecThreatIndex);
	void DeletePrtcDevices(vector<SDevicePK> &i_vecDevicePk);
	void AddPrtcRadar(SRadar &i_stRadar);
	void AddPrtcRadarMode(SRadarModeCopyInfo &i_stRadarMode);
	void AddPrtcPlatform(SPlatform &i_stPlatform);
	void AddPrtcWeaponSystem(SWeaponSystem &i_stWeaponSystem);
	void AddPrtcThreat(SThreat &i_stThreat);
	void UpdatePrtcRadar(SRadar &i_stRadar);
	void UpdatePrtcRadarAssociations(SRadar &i_stRadar);
	void UpdatePrtcRadarMode(SRadarMode &i_stRadarMode);
	void UpdatePrtcPlatform(SPlatform &i_stPlatform);
	void UpdatePrtcWeaponSystem(SWeaponSystem &i_stWeaponSystem);
	void UpdatePrtcThreat(SThreat &i_stThreat);
	void UpdatePrtcThreatPriorities(SThreatPriorities &i_stThreatPriorities);
	void UpdatePrtcThreatFOE(SThreatFOE &i_stThreatFOE);	
	bool CopyRadarToPrtc(vector<long> &i_vecRadarIndex, bool bOver = false);
	bool CopyRadarModeToPrtc(vector<long> &i_vecRadarModeIndex, bool bOver = false);
	bool CopyPlatformToPrtc(vector<long> &i_vecPlatformIndex, bool bOver = false);
	void CopyWeaponSystemToPrtc(vector<long> &i_vecWeaponSystemIndex, bool bOver = false);
	
	void CopyPrtcRadarModeBelongTables(CString strCondition, int nNewRadarModeIndex);

	//////////////////////////////////////////////////////////////////////////
	bool CopyEobToPrtc(vector<long> &i_vecThreatIndex, bool bOver = false);
	void CopyEobDeviceToPrtc(vector<SDevicePK> &i_vecDevicePk, bool bOver = false);

	//
	void GetNewThreatIndex(int &i_nNewThreatIndex, EnumLibType i_eLibType = E_EL_LIB_TYPE_PRACTICAL);
	void GetNewThreatPin(int &i_nNewThreatPin, EnumLibType i_eLibType = E_EL_LIB_TYPE_PRACTICAL);
	int GetNewDeviceIndex(int i_nThreatIndex, EnumLibType i_eLibType = E_EL_LIB_TYPE_PRACTICAL);
	void GetNewPlatformIndex(int &i_nNewPlatformIndex);
	void GetNewWeaponIndex(int &i_nNewWeaponIndex);	
	void GetNewParamSetAssociations(int &i_nNewAssocIndex);
	void GetNewRadarIndex( int *pnNewRadarIndex );
	void GetNewRadarModeIndex( int *pnNewRadarModeIndex );
	void GetNewRadarCommentIndex(int nRadarIndex, int &i_nNewRadarCommentIndex);	
	void GetNewRadarModCommentIndex(int nRadarModIndex, int &i_nNewRadarModCommentIndex);	

	void GetELNOTFromBasicRadar( int &i_nRadarIndex, CString &strELNOT );
	void GetELNOTFromPrtcRadar( int &i_nRadarIndex, CString &strELNOT );
	void GetPrtcRadarIndexFromELNOT( char *pszELNOT, int &i_nRadarIndex );
	
	int GetThreatIndexFromDB(int nPin, EnumLibType i_eLibType = E_EL_LIB_TYPE_PRACTICAL);
	int GetThreatPinFromDB(int nThreatIndex, EnumLibType i_eLibType = E_EL_LIB_TYPE_PRACTICAL);
	int GetRadarIndex(CString strELNOT, EnumLibType i_eLibType = E_EL_LIB_TYPE_PRACTICAL);
	int GetRadarIndexFromDB(CString strELNOT, EnumLibType i_eLibType = E_EL_LIB_TYPE_PRACTICAL);
	
	CString GetELNOTFromDeviceDB( CString strCondition, EnumLibType i_eLibType = E_EL_LIB_TYPE_PRACTICAL );
	void DuplicatedCheckAndCopyPlatform(int nBeforeRadarIndex, int nAfterRadarIndex);
	void DuplicatedCheckAndCopyWeaponSystem(int nBeforeRadarIndex, int nAfterRadarIndex);
	void DuplicatedCheckAndCopyAssocELNOT(int nBeforeRadarIndex, int nAfterRadarIndex);
	void DuplicatedCheckAndCopyRadarComment(int nBeforeRadarIndex, int nAfterRadarIndex);
	void DuplicatedCheckAndCopyParamSetAssociations(int nBeforeRadarIndex, int nAfterRadarIndex);

	//void GetThreatDataFromThreatIndex(int nThreatIndex, SThreat& stThreat, EnumLibType i_eLibType);
	//void IsRadarDataFromELNOT(CString strELNOT, BOOL& bRetun, EnumLibType i_eLibType);
	void IsRadarModeDataFromELNOT(CString strELNOT, BOOL& bRetun, EnumLibType i_eLibType);

	// 레이더 모드 세부 작성
	void MakeFreqType( SRadarMode *pRadar, SELDBGmiAbt *pSELDBGmiAbt );
	void MakeMOPType( SRadarMode *pRadar, SELDBGmiAbt *pSELDBGmiAbt );
	void MakeSigType( SRadarMode *pRadar, SELDBGmiAbt *pSELDBGmiAbt );
	void MakeSigType( SRadarMode *pRadar, SELDBGmiAet *pSELDBGmiAet );
	void MakeFreqRange( SRadarMode *pRadar, SELDBGmiAbt *pSELDBGmiAbt );
	void MakePRIType( SRadarMode *pRadar, SELDBGmiAbt *pSELDBGmiAbt );
	void MakePRIRange( SRadarMode *pRadar, SELDBGmiAbt *pSELDBGmiAbt );
	void MakePWRange( SRadarMode *pRadar, SELDBGmiAbt *pSELDBGmiAbt );
	
	// 레이더 모드 라이프 사이클
	void MakeRadarModeLifeCycle( SRadarMode *pRadarMode, std::list<SELDBGmiAbt*> *pListData, SRadar *pRadar );

	void InsertThreat( int nThreatIndex, SEobExcelData *pSEobExcelData );
	void InsertDevice( int nThreatIndex, SEobExcelData *pSEobExcelData );
	bool IsThreat( int nLimit, int nPin, vector<SEobExcelData> *pvecEobExcel );

	void InitVectorCapacity();
	
	int String2Latitude( char *pszLatitude );
	int String2Longitude( char *pszLongitude );

	bool ProcessCEDEOBUpdate( EN_CEDEOB_UPDATE enCEDEOBUpdate );

	int IsCheckModeCode( SRadarMode *pstRadarMode );

	void MakeThreatFromDBThreatAndDBDevice( SThreat *pThreat, int nDevice, EnumLibType enLibType );
	
public:
	inline bool IsCompleteCEDEOBLoading() { return m_bCompletingTheCEDEOBLoading; }

	SRadarMode* GetRadarModeData( int i_nRadarModeIndex, EnumLibType i_eLibType);
	SRadarMode* GetRadarModeData( vector<SRadarMode> *pVecRTRadarMode, int i_nRadarModeIndex, EnumLibType i_eLibType );
	//SRadarMode* GetRadarModeData( vector<SRadarMode> *pVecRTRadarMode, int nThreatIndex, int nDeviceIndex );
	//SRadarMode* GetRadarModeData( SRadarMode *pRTRadarMode, int nThreatIndex, int nDeviceIndex );
	SRadarMode* GetRadarModeData( SRadarMode *pRTRadarMode, int i_nRadarModeIndex, EnumLibType i_eLibType );

	SRadarMode* GetRadarData( vector<SRadarMode> *pVecRTRadarMode, int i_nRadarModeIndex, EnumLibType i_eLibType );
	SRadarMode* GetRadarData( SRadarMode *pRTRadarMode, int nRadarIndex, EnumLibType enLibType );

	void GetDeviceSameELNOT( CString &strELNOT, SDevice &stDevice );

	//SRadarMode* GetRadarData( vector<SRadarMode> *pVecRTRadarMode, int nThreatIndex, int nDevciceIndex, EnumLibType enLibType );
	SRadar* GetRadarData(int i_nRadarIndex, EnumLibType i_eLibType);
	SRadar* GetRadarData( vector<SRadar> *pVecRadar, int nRadarIndex, EnumLibType i_eLibType );
	SThreat* GetThreatData(int i_nThreatIndex, EnumLibType i_eLibType);

	vector<SRadarMode>* GetAllRadarModeData(EnumLibType i_eLibType);
	vector<SThreat>* GetAllThreatData(EnumLibType i_eLibType);

	//int GetRadarIndexFromRadarModeIndex( vector<SRadar> *pMapRadar, int i_nRadarModeIndex );
	//SRadar* GetRadarDataFromRadarModeIndex(int i_nRadarModeIndex, EnumLibType i_eLibType);
		
	SDevice* GetDeviceData(int i_nThreatIndex, int i_nDeviceIndex, EnumLibType i_eLibType);
	SDevice* GetDeviceSameELNOT( CString *pStrELNOT, EnumLibType eEOBLibType );

	char *GetEnglishSiteNameFromDB( int nThreatIndex, EnumLibType i_eLibType /* = E_EL_LIB_TYPE_PRACTICAL*/);

	//////////////////////////////////////////////////////////////////////////
	// 기존 함수 활용하기 위한 함수
	//vector<SRadarMode> *RqstCEDLibData( EnumLibType i_eLibType );
	void RqstEOBLibData(EnumLibType i_eLibType);

	bool ReceiveInterComm(UINT i_uiMsg, WPARAM i_wParam, LPARAM i_lParam);

	//int GetNumOfEOB(EnumLibType i_eLibType);

	//로그오프용 함수
	BOOL Finalize();

	//void PorcessViewToLogicThreatInfo();
	//void PorcessViewToLogicRadarModeInfo();

	void MakeThreatInfoFromAETID( SThreat *pThreat, int nAETIDMakeRadarInfoFromAETID );
	void MakeRadarInfoFromAETID( SRadar *pRadar, SELCEDCREATE *pSELCEDCREATE, UINT uiMode );

	void MakeTableByThreatStatusCode( vector<SELDBThreatStatusCode*> *pListThreatStatusCode );

	SRadar *Find( vector<SRadar> *pVecRadarMode, int i_nRadarIndex );
	SRadarMode *Find( vector<SRadarMode> *pVecRadarRadar, int i_nRadarModeIndex );
	SRadarMode *Find( SRadarMode *pRadarMode, int i_nRadarModeIndex );

	//SRadarMode *FindRadar( vector<SRadarMode> *pVecRadarMode, int nRadarIndex );
	SRadarMode *FindRadar( SRadarMode *pRadarMode, int nRadarIndex );
	//SRadarMode *FindRadar( vector<SRadarMode> *pVecRadarMode, int nThreatIndex, int nDeviceIndex );
	
	SThreat *Find( vector<SThreat> *pVecThreat, int nThreatIndex );
	//SPlatform *Find( vector<SPlatform> *pVecPlatform, int nPlatformIndex );
	SWeaponSystem *Find( vector<SWeaponSystem> *pVecWeaponSystem, int nWeaponIndex );
	SRadarMode *Find( vector<SRadarMode> *pVecRadarMode, int iThreatIndex, int nDeviceIndex );
	SRadarMode *Find( SRadarMode *pRadarMode, int iThreatIndex, int nDeviceIndex );
	SRadarMode *Find( SRadarMode *pVecRadarMode, char *pszELNOT, int iThreatIndex );

	SDeviceData *Find( int nThreatIndex, int nDeviceIndex=0 );

	void GetDefaullt2525BSymbol( CString *pString );
	void SetCEDEOBLibTypeOfEnvVarIdnf( SELDBEnvVarIdnf *pSELDBEnvVarIdnf  );

	CString GenerateModCodeFromLIB(SRadarMode &i_stRadarMode);

	//inline int GetRadarIndexFromRadarModeIndex( int i_nRadarModeIndex, EnumLibType eEOBLibType ) { return GetRadarIndexFromRadarModeIndex( & m_vecRadar[eEOBLibType], i_nRadarModeIndex ); }

	void RTGetELNOTFromRadarIndexDB( int &i_nRadarIndex, CString &strELNOT, EnumLibType i_eLibType = E_EL_LIB_TYPE_PRACTICAL );
	void ReqWeaponSystemDetailList( SWeaponSystem *pSWeaponSystem, EnumLibType i_eLibType );

private:
	EnumLibType m_enGeoLibType;						///< 지도창에서 기본형 또는 실무형에서 요청한 값

	int m_iMaxEobIndfRangeNM;							///< EOB 중에서 최대 식별 반경 거리 값
	bool m_bIsCEDLibLoaded[E_EL_LIB_TYPE_PRACTICAL+1];	///< CED/EOB 로딩 여부
	bool m_bIsEOBLibLoaded[E_EL_LIB_TYPE_PRACTICAL+1];	///< CED/EOB 로딩 여부
	bool m_bCompletingTheCEDEOBLoading;									///< CED/EOB 불로오기 완료 여부
	map<EnumLibraryWndType, bool> m_mapIsWindowOpen;		///< 창 활성 여부 플레그 

	CMSXmlParser m_xmlParser;														///< CED XML Parser를 처리하기 위한 객체

	// CED 관련 데이터 정의
	vector<SRadar> m_vecRadar[E_EL_LIB_TYPE_PRACTICAL+1];										///< 레이더 데이터
	vector<SRadarMode> m_vecRadarMode[E_EL_LIB_TYPE_PRACTICAL+1];						///< 레이더 모드 데이터
	vector<SPlatform> m_vecAllPlatform[E_EL_LIB_TYPE_PRACTICAL+1];					///< 레이더 모드 데이터
	vector<SWeaponSystem> m_vecAllWeaponSystem[E_EL_LIB_TYPE_PRACTICAL+1];	///< 무기 체계 포인터

	// CED 식별하기 위한 데이터 정의
	UINT uiRTRadarMode;																	///< 레이더 모드 개수
	SRadarMode *m_pRTRadarMode;													///< 레이더 모드 데이터

	// EOB 식별하기 위한 데이터 정의
	vector<SDeviceData> m_vecRTDeviceData;							///< 장비 데이터

	SELDBRadar *m_pSELDBRadar;													///< 레이더 테이블 값을 로드하기 위한 데이터
	SELDBRadarList *m_pSELDBRadarList;									///< 레이더 목록창에 전싷
	SELDBRadarMode *m_pSELDBRadarMode;
	SELDBRadarModeList *m_pSELDBRadarModeList;

	int m_nSELDBRadarMode;
	int m_nSELDBRadar;

	// EOB 관련 데이터 정의	
	vector<SThreat> m_vecThreat[E_EL_LIB_TYPE_PRACTICAL+1];										///< 위협 데이터
	vector<SDevice> m_vecDevice[E_EL_LIB_TYPE_PRACTICAL+1];										///< 장비 데이터

	////////////////////////////////////////////////////////////////////////////////////////////
	vector<SParamSetAssocTypeCode> m_vecParamSetAssocTypeCode;		///< 연관 무기 체계 데이터

	void *m_pclsGenerator;																			///< 모드 코드 객체
	CElintdb** m_pElintDb;																			///< ELINT DB 포인터
	CCommondb **m_pCommonDB;																		///< 공통 DB 포인터
	static CELCEDLibMngr2 *uniqueInstance;											///< 객체 포인터

	SELLIBUPDATE m_SELCEDUpdate;																///< CED 업데이트 상태
	SELLIBUPDATE m_SELEOBUpdate;																///< EOB 업데이트 상태

	vector<SELDBThreat *> m_VecDBThreat;													///< THREAT 테이블의 데이터
	vector<SELDBDevice *> m_VecDBDevice;													///< DEVICE 테이블의 데이터

	char *m_pTableStatusCode;

	SELDBEnvVarIdnf *m_pSELDBEnvVarIdnf;												///< 시스템 설정값 환경 포인터

	vector<pair<CString, CString> > m_CEDXMLFiles;

public:
	//////////////////////////////////////////////////////////////////////////
	// 아래는 실시간 EOB 를 처리하기 위한 함수 정의
	//int RTGetRadarIndexFromThreat( int nThreatIndex, int nDeviceIndex, EnumLibType enLibType );
	char *RTGetELNOTFromDeviceMemory( int nThreatIndex, int nDeviceIndex );
	char *RTGetKoreaSiteName( int nThreatIndex, EnumLibType eEOBDefaultLibType );
	char *RTGetEOBBENumber( int nThreatIndex, EnumLibType eEOBDefaultLibType );
	char *RTGetEOBFunctionCode( int nThreatIndex, EnumLibType eEOBDefaultLibType );
	int RTGetEOBPriority( int nThreatIndex, EnumLibType eEOBDefaultLibType );

	vector<SDeviceData>* RTGetAllDeviceData( vector<SDeviceData> *pVecDeviceData, char *pszCondition, EnumLibType eEOBLibType );
	void RTGetAllDeviceData( vector<SDeviceData> *pVecDeviceData, STR_POSESTDATA *pPosEstData, EnumLibType eEOBLibType );

	SDevice *RTGetDeviceData( int nThreatIndex, int nDeviceIndex, EnumLibType enLibType );
	SDevice *RTGetDeviceData( int nThreatIndex, char *szELNOT, EnumLibType enLibType );
	SThreat *RTGetThreatData( int nThreatIndex, EnumLibType enLibType );
	bool RTGetThreatDeviceData( SThreat *pThreat, int nThreatIndex, EnumLibType enLibType );

	//inline int RTGetRadarIndexFromRadarModeIndex( int i_nRadarModeIndex, EnumLibType eEOBLibType ) { return GetRadarIndexFromRadarModeIndex( & m_mapRTRadar[eEOBLibType], i_nRadarModeIndex ); }
	//int RTGetRadarIndexFromRadarModeIndex( int i_nRadarModeIndex, EnumLibType eCEDLibType );
	void RTGetRadarModeCodeFromRadarIndex( vector<SELDBRadarLifecycle*> *pVecRadarLifeCycle, int nRadarIndex, EnumLibType eLibType );
	bool RTGetRadarDataFromRadarModeIndex( SRadar *pRadar, int nRadarModeIndex, EnumLibType eLibType );

	bool RTGetModulationCode( SRadarMode *pstRadarMode, int nRadarModeIndex, EnumLibType eLibType );

	void RTGetPlatformDataFromIndex( SELREQUEST_PLATFORM *pReqPlatform, SPlatform *pPlatform );

	void MakeThreatsFromDBThreat( int nThreat );

	//////////////////////////////////////////////////////////////////////////
	// 아래는 실시간 CED 를 처리하기 위한 함수 정의
	SRadarMode *RTGetAllRadarModeData( EnumLibType i_eCEDLibType, EnumLibType i_eEOBLibType, char *pszCondition );

	inline SRadarMode *RTGetAllRadarModeData( int iIndex=0 ) { return & m_pRTRadarMode[iIndex]; }

 	inline SRadarMode *RTGetRadarModeDataFromMemory( int nRadarModeIndex, EnumLibType enLibType ) { return GetRadarModeData( & m_pRTRadarMode[0], nRadarModeIndex, enLibType ); } 
 	inline SRadarMode *RTGetRadarDataFromMemory( int nRadarIndex, EnumLibType enLibType ) { return GetRadarData( & m_pRTRadarMode[0], nRadarIndex, enLibType ); } 
// 	inline SRadarMode *RTGetRadarDataFromMemory( int nThreatSequenceIndex, int nDeviceIndex, EnumLibType enLibType ) { return GetRadarData( & m_vecRTRadarMode[m_nIDBank], nThreatIndex, nDeviceIndex, enLibType ); } 
 //	inline SRadarMode *RTGetRadarModeFromThreatMemory( int nThreatIndex, int nDeviceIndex ) { return GetRadarModeData( & m_pRTRadarMode[0], nThreatIndex, nDeviceIndex ); } 
 	//inline int RTGetRadarIndexFromThreatMemory( int nThreatIndex, int nDeviceIndex ) { return GetRadarIndexFromThreat( & m_pRTRadarMode[0], nThreatIndex, nDeviceIndex ); }
	inline int RTGetRadarIndexFromThreatMemory( char *pszELNOT, int nThreatIndex ) { return GetRadarIndexFromThreat( & m_pRTRadarMode[0], pszELNOT, nThreatIndex ); }

	inline void ClearCountOfRTRadarMode() { uiRTRadarMode = 0; }
	inline void IncCountOfRTRadarMode() { ++ uiRTRadarMode; }
	inline UINT GetCountOfRTRadarMode() { return uiRTRadarMode; }

	inline vector<SThreat> *GetThreatData( EnumLibType i_eCEDLibType ) { return & m_vecThreat[i_eCEDLibType]; }
	inline vector<SDevice> *GetDeviceData( EnumLibType i_eEOBLibType ) { return & m_vecDevice[i_eEOBLibType]; }

	bool RTGetRadarData( SRadar *pstRadar, int nRadarIndex, EnumLibType eLibType );
	bool RTGetRadarIndexFromELNOT( int *pnRadarIndex, const char *szELNOT, EnumLibType i_eLibType );
	bool RTGetRadarModeIndexFromRadarIndexAndMode( int *pnRadarIndex, int nRadarIndex, char *szModeCode, EnumLibType i_eLibType );
	//int GetRadarIndexFromThreat( vector<SRadarMode> *pRTRadarMode, int nThreatIndex, int nDeviceIndex );
	//int GetRadarIndexFromThreat( SRadarMode *pRTRadarMode, int nThreatIndex, int nDeviceIndex );
	int GetRadarIndexFromThreat( SRadarMode *pRTRadarMode, char *pszELNOT, int nThreatIndex );
	SRadar *RTGetRadarDataFromInfo( SELREQUEST_RADAR *pReqRadar, EnumLibType i_eCEDLibType, EnumLibType i_eEOBLibType );
	SThreat *RTGetThreatDataFromPINNum( CString *pStrPinNum, EnumLibType i_eLibType );
	SRadarMode *RTGeRadarModeDataFromInfo( SELREQUEST_RADAR *pReqRadar, EnumLibType i_eCEDLibType, EnumLibType i_eEOBLibType );
	int FindRadarModeIndexInRadarModeLifeCycle( vector<SELDBRadarModeLifeCycle*> *pVecRadarModeLifeCycle, CString *pStrModeCode );

	void GetRadarModeRF( string condition, EnumLibType eLibType );
	void InsertRadarModeRF( SRadarMode *pstRadarMode );
	void InsertRadarModeRF_Values( SRadarMode *pstRadarMode, vector<SELDBRadarRF_Values*> *pVecRadarRF_Values );
	void InsertRadarModeRF_Sequence( SRadarMode *pstRadarMode, vector<SELDBRadarRF_Sequence*> *pVecRadarRF_Sequence, vector<SELDBRadarRF_SequenceName*> *pVecRadarRF_SequenceName );
	void InsertRadarModeRF_SpotValues( SRadarMode *pstRadarMode, vector<SELDBRadarRF_SpotValues*> *pVecRadarRF_SpotValues );

	void GetRadarModePRI( string condition, EnumLibType eLibType );
	void InsertRadarModePRI( SRadarMode *pstRadarMode );
	void InsertRadarModePRI_SpotValues( SRadarMode *pstRadarMode, vector<SELDBRadarPRI_SpotValues*> *pVecRadarPRI_SpotValues );
	void InsertRadarModePRI_Sequence( SRadarMode *pstRadarMode, vector<SELDBRadarPRI_Sequence*> *pVecRadarPRI_Sequence, vector<SELDBRadarPRI_SequenceName*> *pVecRadarPRI_SequenceName );
	void InsertRadarModePRI_Values( SRadarMode *pstRadarMode, vector<SELDBRadarPRI_Values*> *pVecRadarPRI_Values );
	void InsertRadarModePRI_Group_Spacing( SRadarMode *pstRadarMode, vector<SELDBRadarPRI_GroupSpacing*> *pVecRadarPRI_GroupSpacing );

	void GetRadarModePD( string condition, EnumLibType eLibType );
	void InsertRadarModePD( SRadarMode *pstRadarMode );
	void InsertRadarModePD_SpotValues( SRadarMode *pstRadarMode, vector<SELDBRadarPD_SpotValues*> *pVecRadarPD_SpotValues );
	void InsertRadarModePD_Sequence( SRadarMode *pstRadarMode, vector<SELDBRadarPD_Sequence*> *pVecRadarPD_Sequence, vector<SELDBRadarPD_SequenceName*> *pVecRadarPD_SequenceName );
	void InsertRadarModePD_Values( SRadarMode *pstRadarMode, vector<SELDBRadarPD_Values*> *pVecRadarPD_Values );

	void GetRadarModeMOP( string condition, EnumLibType eLibType );
	void InsertRadarModeMOP( SRadarMode *pstRadarMode );
	void InsertRadarMOP_CW_Sequence( SRadarMOP_CW *pstRadarMOP_CW,  int nRadarModeIndex, vector<SELDBRadarMOP_CW_Sequence*> *pVecRadarMOP_CW_Sequence, vector<SELDBRadarMOP_CW_SEQ_Name*> *pVecRadarMOP_CW_SEQ_Name );
	void InsertRadarMOP_CW_Values( SRadarMOP_CW *pstRadarMOP_CW, vector<SELDBRadarMOP_CW_Values*> *pVecRadarMOP_CW_Values );

	void InsertRadarModePA_Diff_InGroup( SRadarMode *pstRadarMode, vector<SELDBRadarPA_Diff_InGroup*> *pVecRadarPA_Diff_InGroup );
	void InsertRadarModeComments( SRadarMode *pstRadarMode, vector<SELDBRadarModeComments*> *pVecRadarModeComments );
	void InsertParamSetAssociations( SRadarMode *pstRadarMode, vector<SELDBParamSetAssociations*> *pVecParamSetAssociations );

	// RADAR 관련 정보 업데이트 함수
	void InsertRadarRelatedThreat( SRadar *pstRadar, vector<SThreat> *pVecThreat, vector<SDevice> *pVecDevice );
	void InsertRadarModeLifeCycle( SRadar *pstRadar, SRadarMode *pstRadarMode, vector<SELDBRadarModeLifeCycle*> *pVecRadarModeLifeCycle );
	void InsertRadarModeLifeCycle( SRadar *pstRadar, vector<SRadarMode> *pVecRadarMode, vector<SELDBRadarModeLifeCycle*> *pVecRadarModeLifeCycle );

	void InsertRadarComments( SRadar *pstRadar, vector<SELDBRadarComments*> *pVecRadarComments );
	void InsertRadarRF( SRadar *pstRadar );
	void InsertParamSetAssociations( SRadar *pstRadar, vector<SELDBParamSetAssociations*> *pVecParamSetAssociations );

	// 플레폼 관련 저장
	void InsertPlatform( vector<SPlatform> *pVecAllPlatform, vector<SELDBPlatform*> *pVecPlatform );
	void InsertAssocPlatform( EnumLibType i_eLibType );
	void InsertWeaponSystem( vector<SWeaponSystem> *pVecAllWeaponSystem, vector<SELDBWeaponSystem*> *pVecWeaponSystem );
	//void InsertAssocPlatform( vector<SRadar> *pVecRadar, vector<SRadarMode> *pVecRadarMode, vector<SPlatform> *pVecAllPlatform, vector<SELDBAssocPlatform*> *pVecAssocPlatform, EnumLibType i_eLibType );
	void InsertAssocPlatform( SRadar *pstRadar, vector<SELDBPlatform*> *pVecPlatform );
	void InsertAssocWeaponSys( SRadar *pstRadar, vector<SELDBWeaponSystem*> *pVecWeaponSys );
	//void InsertAssocWeapSys( vector<SRadar> *pVecRadar, vector<SRadarMode> *pVecRadarMode, vector<SWeaponSystem> *pVecAllWeaponSystem, vector<SELDBAssocWeapSys*> *pVecAssocWeapSys, EnumLibType i_eLibType );
	void InsertAssocWeapSys( EnumLibType i_eLibType );
	void InsertAssocWeapSysPlatform( EnumLibType i_eLibType );
	//void InsertAssocELNOT( vector<SRadar> *pVecRadar, vector<SELDBAssocELNOT*> *pVecAssocELNOT );
	void InsertAssocELNOT( SRadar *pstRadar, vector<SELDBAssocELNOT*> *pVecAssocELNOT );

	// DB 테이블 로딩
	//int LoadRadarDBTable( EnumLibType eLibType, char *pszRadarModeCondition );
	//int LoadRadarModeDBTable( EnumLibType eLibType, char *pszRadarModeCondition );
	void UnLoadRadarDBTable();
	void UnLoadRadarModeDBTable();

	// 레이더모드에 대한 View 테이블 로딩
	int LoadRadarModeVDBTable( EnumLibType eCEDLibType, EnumLibType eEOBLibType, char *pszRadarModeCondition );

	// DB 정보로 부터 레이더 정보 만들기
	void MakeRadarFromDBRadar( SRadar *pstRadar, SELDBRadar *pSELDBRadar );
	void MakeRadarFromDBRadarList( UINT nRadar, SELDBRadarList *pSELDBRadarList, EnumLibType eLibType );
	void MakeRadarModeFromDBRadar( SRadarMode *pstRadarMode, SELDBRadarMode *pSELDBRadarMode );
	void MakeFreqPRIType( SRadarMode *pstRadarMode );
	void MakeVecRadarModeFromDBRadar( vector<SRadarMode> *pVecRadarMode, int nRadarMode, SELDBRadarMode *pSELDBRadarMode, EnumLibType i_eLibType, EnumLoadType enLoadType );

	// DB 정보로 부터 레이더모드 정보 만들기
	void MakeRadarFromDBRadarModeList( UINT nRadarMode, SELDBRadarModeList *pSELDBRadarModeList, EnumLibType eLibType, EnumLoadType enLoadType );

	// DB 정보로 부터 위협 정보 만들기
	void MakeThreatFromDBThreat( SThreat *pstThreat, SELDBThreat *pSELDBThreat );

	// DB 정보로 부터 장비 정보 만들기
	void MakeDeviceFromDBDevice( SDevice *pstDevice, SELDBDevice *pSELDBDevice );

	void CalculateLonLatAndUpdateThreat( SThreat *pThreat, int nDeviceCount, double dTotLatitude, double dTotLongitude, EnumLibType enLibType );

	void SetGeodeticInfo(double& i_dLat, double& i_dLong);
	void SendReqDigitalMapPos(void * i_Data);

private:
	//void OpenProgressBar( char *pProgressBar );
	//void UpdateProgressBar( char *pProgressBar, double nProgress );
	//void CloseProgressBar( char *pProgressBar );

private :
	SDevice m_stDevice;
	SThreat m_stThreat;

	SRadar m_stRadar;
	SRadarMode m_stRadarMode;

	// 레이더
	vector<SELDBRadarComments*> m_vecRadarComments;
	vector<SELDBWeaponSystem*> m_vecWeaponSystem;
	vector<SELDBAssocWeapSys*> m_vecAssocWeapSys;
	vector<SELDBAssocPlatform*> m_vecAssocPlatform;
	vector<SELDBPlatform*> m_vecPlatform;
	vector<SELDBAssocELNOT*> m_vecAssocELNOT;
	vector<SELDBParamSetAssociations*> m_vecParamSetAssociations;

	// 레이더 모드
	vector<SELDBRadarModeLifeCycle*> m_vecRadarModeLifeCycle;
	vector<SELDBRadarModeComments*> m_vecRadarModeComments;

	vector<SELDBRadarPD_Values*> m_vecRadarPD_Values;
	vector<SELDBRadarPD_Sequence*> m_vecRadarPD_Sequence;
	vector<SELDBRadarPD_SequenceName*> m_vecRadarPD_SequenceName;
	vector<SELDBRadarPD_SpotValues*> m_vecRadarPD_SpotValues;

	vector<SELDBRadarRF_Sequence*> m_vecRadarRF_Sequence;
	vector<SELDBRadarRF_Values*> m_vecRadarRF_Values;
	vector<SELDBRadarRF_SequenceName*> m_vecRadarRF_SequenceName;
	vector<SELDBRadarRF_SpotValues*> m_vecRadarRF_SpotValues;

	vector<SELDBRadarPRI_Values*> m_vecRadarPRI_Values;
	vector<SELDBRadarPRI_Sequence*> m_vecRadarPRI_Sequence;
	vector<SELDBRadarPRI_SequenceName*> m_vecRadarPRI_SequenceName;
	vector<SELDBRadarPRI_SpotValues*> m_vecRadarPRI_SpotValues;
	vector<SELDBRadarPRI_GroupSpacing*> m_vecRadarPRI_GroupSpacing;

	vector<SELDBRadarMOP_CW*> m_vecRadarMOP_CW;
	vector<SELDBRadarMOP_CW_Values*> m_vecRadarMOP_CW_Values;
	vector<SELDBRadarMOP_CW_Sequence*> m_vecRadarMOP_CW_Sequence;
	vector<SELDBRadarMOP_CW_SEQ_Name*> m_vecRadarMOP_CW_SEQ_Name;

	vector<SELDBRadarPA_Diff_InGroup*> m_vecRadarPA_Diff_InGroup;

	vector<SELDBFunctionCodes*> m_vecFunctionCodes;
	vector<SELDBThreatStatusCode*> m_vecThreatStatusCode;
	vector<SELDBCountry*> m_vecCountry;

};


#define GP_MNGR_CED_LIB2	CELCEDLibMngr2::GetUniqueInstance()

#endif