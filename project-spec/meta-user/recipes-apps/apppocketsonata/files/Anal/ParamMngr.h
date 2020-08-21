#pragma once

#define		MIN_LISTITEMSOF_LOB					(100)
#define		DELTA_DISTANCE_BT_POINT_AND_POINT			(20)
#define		FTP_FOLDER						"c:/"

#define		GET_LOB_NUMS						(1)
#define		THRESHOLD_OF_FOV					(10)
#define		EFFECTIVE_DOA_DIFF1					(30.0)
#define		EFFECTIVE_DOA_DIFF2					(30.0)
#define		EFFECTIVE_DOA_DIFF3					(5.0)

#define		EFFECTIVE_DIST_BT_EOB					(15)					// 단위 [km]

#define		EFFECTIVE_DIST						(40)

#define		DELETE_THREAT_WNEN_CO_LOB				(30)

// INI 파일 정의
#define INI_FILE    "packetSonata.ini"

#ifdef _WIN32

#else
#include "../MinIni/minIni.h"

#endif
 
/**
 * [식별자 : CLS-GMU-GR-L-TPM]
 *
 * [추적성 : SRS-G-SOFR-009]
 *
 * @class    CParamMngr
 * @brief   운용자 변수 적용을 위한 환경파일 관리 클래스
 *
 * (1) 클래스 설명
 * - 운용자 변수 적용을 위한 환경파일 관리 클래스
 *
 * (2) 설계결정사항
 * - 환경파일 관리 및 저장 기능 필요.
 *
 * (3) 제한 및 예외처리
 * - 해당사항없음
 */
class CParamMngr 
{
private:
    CParamMngr(void);
    virtual ~CParamMngr(void);

    static CParamMngr* m_pInstance;

    bool m_b701DLL;
    bool m_bPosServerMode;
    bool m_bPdwIsV2;
    bool m_bIqIsV2;
    bool m_bEmitterIsV2;
    bool m_bIsMaster;
    bool m_bIsLinkShare;
    bool m_bIsEmitterMerge;
    bool m_bIsIdentifyFreqBasedTask;
    bool m_bIsLOBClustering;
    int m_nLink;
    int m_nPOSN2GMI_LINK;
    int m_iDistanceForBeamMerge;
    int m_nLOBNum;
    int m_nMinIDMatchRatio;
    int m_nMaxListItemsOfLOB;
    CString m_strMidasFolder;

    //elint trace
    bool m_bElintTrace;
    bool m_bLineNum;
    bool m_bTimeInfo;
    bool m_bIsPOSN;

    // elint 고이득 안테나 가속도
    int m_nAcceleration;

    // elint 수동과제 h/w blanking
    int m_nHwBlanking;

    // elint 수동과제 h/w blank Channel 항목
    int m_nHWBlankChannel;

    // RAW PDW DATA SEND
    int m_nRawPdwSend; // 0: off, 1 : on

    // 데이터 획득을 위한 DB 접근 주기
    int m_nDBAccessPeriod; // msec

    int m_nThresholdOfFOV;
    float m_fEffectiveDOADiff1;
    float m_fEffectiveDOADiff2;
    float m_fEffectiveDOADiff3;
    float m_fEffectiveDistOfEOB;

    int m_iEffectiveDist;

    int m_iDeleteThreatWhenCoLOB;

    int m_nNumOfPdwProcessing;

    bool m_bSimulatorMode;

private :
    bool m_bRealserver1;
    bool m_bRealserver2;
    bool m_bPSS;
    bool m_bIsELINT;
    bool m_bIsValidLOB;

	// cep, eep 지도전시 최소 길이 관련 변수
private:
    unsigned int m_uiEmitterCEPRadius;
    unsigned int m_uiEmitterEEPMajorAxis;
    unsigned int m_uiEmitterEEPMinorAxis;
    unsigned int m_uiBeamEEPMajorAxis;
    unsigned int m_uiBeamEEPMinorAxis;

	// 방사체, 빔 유/무효 전시 관련 변수
private:
    bool m_bDisplayValidEmitterOnly;
    bool m_bDisplayValidBeamOnly;

	// DB FETCH 개수 관련
private:
    unsigned int m_uiNumOfLOBPerFetch;
    unsigned int m_uiNumOfPDWPerFetch;
    unsigned int m_uiNumOfLOBPerFetch_Supervisor;
    unsigned int m_uiNumOfPDWPerFetch_Supervisor;

private:
    CString m_strFilename;
	
public:
	
	/**
	* @brief       싱글턴 객체 획득 함수
	* @return      CParamMngr*   
	*/
	static CParamMngr* getInstance();	
	
	/**
	* @brief       객체소멸 함수
	* @return      void   
	*/
	static void ReleaseInstance();

	
	/**
	* @brief       파라메타 로드 함수
	* @return      void   
	*/
	void LoadParameter();

	
	/**
	* @brief       DLL 확인 함수
	* @return      bool   확인 true, 미확인 false
	*/
	bool Is701DLL(){return m_b701DLL;};
	
	/**
	* @brief       포지션 서버 모드 확인 함수
	* @return      bool   포지션서버모드 true, 그 외 false
	*/
	bool IsPosServerMode(){return m_bPosServerMode;};

	
	/**
	* @brief       ELINT PDW 처리방법 버전 확인 함수
	* @return      bool   버전2 true, 그외 false
	*/
	bool IsElintPdwPrcsMethodVersion2(){ return m_bPdwIsV2;}
	
	/**
	* @brief       ELINT IQ 처리방법 버전 확인 함수
	* @return      bool   버전2 true, 그외 false
	*/
	bool IsElintIqPrcsMethodVersion2(){ return m_bIqIsV2;}
	
	/**
	* @brief       ELINT 방사체 처리방법 버전 확인 함수
	* @return      bool   버전2 true, 그외 false
	*/
	bool IsElintEmitterPrcsMethodVersion2(){ return m_bEmitterIsV2;}
	
	/**
	* @brief       마스터 SERVER 여부 확인 함수
	* @return      bool   마스터 true, 그 외 false
	*/
	inline bool IsElintMaster(){ return m_bIsMaster;}
	
	/**
	* @brief       링크쉐어 모드 확인 함수
	* @return      bool   링크쉐어 true, 그 외 false
	*/
	inline bool IsLinkShare(){ return m_bIsLinkShare;}
	
	/**
	* @brief       포지션여부 확인 함수
	* @return      bool   포지션 true, 서버 false
	*/
	inline bool IsPOSN(){ return m_bIsPOSN;}
	
	/**
	* @brief       ELINT 사용자 확인 여부 함수
	* @return      bool   ELINT 사용자 true, 그 외 false
	*/
	inline bool IsELINTUser(){ return m_bIsELINT;}
	
	/**
	* @brief       방사체 병합 모드 확인 함수
	* @return      bool   방사체병합 true, 그 외 false
	*/
	inline bool IsEmitterMerge(){ return m_bIsEmitterMerge;}
	
	/**
	* @brief       주파수 기반 식별 여부 확인 함수
	* @return      bool   주파수 기반 식별 true, 그 외 false
	*/
	inline bool IsIdentifyFreqBasedTask(){ return m_bIsIdentifyFreqBasedTask;}
	
	/**
	* @brief       LOB 클러스터링 수행 여부 체크 함수
	* @return      bool   클러스터링 true, 그 외 false
	*/
	inline bool IsLOBClustering(){ return m_bIsLOBClustering;}
	
	/**
	* @brief       PSS 인지 여부를 확인하는 함수
	* @return      bool   PSS true, 그 외 false
	*/
	inline bool IsPSS(){ return m_bPSS;}
	
	/**
	* @brief       유효 LOB 체크 여부 확인 함수
	* @return      bool   체크 true, 미체크 false
	*/
	inline bool IsValidLOB(){ return m_bIsValidLOB;}

	
	/**
	* @brief       링크번호 획득 함수
	* @return      int   링크번호
	*/
	inline int GetLinkNum(){ return m_nLink;}
	
	/**
	* @brief       POSN2GMI_LINK 사용여부 확인 함수
	* @return      int   사용번호
	*/
	inline int GetPOSN2GMI_LINK(){ return m_nPOSN2GMI_LINK;}
	
	/**
	* @brief       LOB 개수 체크 함수
	* @return      int   LOB 개수
	*/
	inline int GetLOBNum(){ return m_nLOBNum;}
	
	/**
	* @brief       최소 ID 매칭 비율 획득 함수
	* @return      int   최소 ID 매칭 비율
	*/
	inline int GetMinIDMatchRatio(){ return m_nMinIDMatchRatio;}
	
	/**
	* @brief       LOB 리스트 아이템 획득 함수
	* @return      int   리스트 아이템
	*/
	inline int GetListItemsOfLOB(){ return m_nMaxListItemsOfLOB;}
	
	/**
	* @brief       ELINT Trace on/off 여부 확인 함수
	* @return      bool   on true, 그외 false
	*/
	inline bool IsElintTraceOn(){return m_bElintTrace;};
	
	/**
	* @brief       FOV 스레스홀드값 획득 함수
	* @return      int   FOV 스레스홀드 값
	*/
	inline int GetThresholdOfFOV(){ return m_nThresholdOfFOV;}
	
	/**
	* @brief       유효 DOADiff1 획득함수
	* @return      int   DOADiff1
	*/
	inline float GetEffectiveDOADiff1(){ return m_fEffectiveDOADiff1;}
	
	/**
	* @brief       유효 DOADiff2 획득함수
	* @return      int   DOADiff2
	*/
	inline float GetEffectiveDOADiff2(){ return m_fEffectiveDOADiff2;}
	
	/**
	* @brief       유효 DOADiff3 획득함수
	* @return      float   DOADiff3
	*/
	inline float GetEffectiveDOADiff3(){ return m_fEffectiveDOADiff3;}
	
	/**
	* @brief       유효 DistOfEOB 획득함수
	* @return      float   DistOfEOB
	*/
	inline float GetEffectiveDistOfEOB(){ return m_fEffectiveDistOfEOB;}
	
	/**
	* @brief       유효거리 획득 함수
	* @return      int   유효거리
	*/
	inline int GetEffectiveDist() { return m_iEffectiveDist; }
	
	/**
	* @brief       위협삭제 관련정보 획득 함수
	* @return      int   위협삭제 정보
	*/
	inline int GetDeleteThreatWhenCoLOB(){ return m_iDeleteThreatWhenCoLOB;}
	
	/**
	* @brief       모의기 모드 체크 함수
	* @return      bool   모의기모드 true, 그 외 false
	*/
	inline bool IsSimulatroMode(){ return m_bSimulatorMode;}

	
	/**
	* @brief       고이득안테나 가속도 값 획득 함수
	* @return      int   가속도 값
	*/
	int GetElintHGAAcceleration(){return m_nAcceleration;};
	
	/**
	* @brief       HW블랭킹 모드 획득 함수
	* @return      int   HW블랭킹 모드 값
	*/
	int GetElintHWBlankingMode(){return m_nHwBlanking;};
	
	/**
	* @brief       HW블랭킹 채널 획득 함수
	* @return      int   HW블랭킹 채널 값
	*/
	int GetElintHWBlankChannel(){return m_nHWBlankChannel;};
	
	/**
	* @brief       빔병합을 위한 거리 획득 함수
	* @return      int   빔병합 거리
	*/
	int GetDistanceForBeamMerge(){return m_iDistanceForBeamMerge;};
	
	/**
	* @brief       분석안된 PDW 전송 여부 확인 함수
	* @return      int   PDW 전송 여부
	*/
	int GetPdwRawDataSendParam();
	
	/**
	* @brief       DB Polling 시간 획득 함수
	* @return      int   DB Polling 시간 (초)
	*/
        //DWORD GetDBAccessPeriodTime(){return m_nDBAccessPeriod;};
	
	/**
	* @brief       MIDAS 폴더 획득 함수
	* @return      CString   MIDAS 폴더
	*/
	CString GetMidasFolder(){return m_strMidasFolder;};
	
	/**
	* @brief       PDW 프로세싱 개수 획득 함수
	* @return      int    PDW 프로세싱 개수
	*/
	int GetNumOfPdwProcessing();

	void WriteProfile( char *pAppName, char *pAppKey, char *pValue );

	
	/**
	* @brief       POS2GMI 링크 설정 함수
	* @param       int nLink   링크번호
	* @return      void   
	*/
	inline void SetPOSN2GMI_LINK( int nLink ) { m_nPOSN2GMI_LINK=nLink; }

	
	/**
	* @brief       ELINT Trace 관련 확인 함수
	* @return      bool   On true, 그 외 false
	*/
	inline bool IsElintTraceLineNumOn()
	{
		bool bRtn = false;
		if(m_bElintTrace && m_bLineNum)
			bRtn = true;
		else
			;
		return bRtn;
	};
	
	/**
	* @brief       ELINT Trace 시간 관련 확인 함수
	* @return      bool    On true, 그 외 false
	*/
	inline bool IsElintTraceTimeInfoOn()
	{
		bool bRtn = false;
		if(m_bElintTrace && m_bTimeInfo)
			bRtn = true;
		else
			;
		return bRtn;
	};

	// 로그인 정보로 플레그를 업데이트한다.
	
	/**
	* @brief       로그인 정보로 플레그를 업데이트한다.
	* @return      void   
	*/
	//void CheckMaster();

	// cep, eep 지도전시 최소 길이 관련 변수
	
	
	/**   
	* @brief	방사체 전시를 위한 CEP 최소반경 획득 함수
	* @return	unsigned int  CEP 최소반경
	*/
	unsigned int GetEmitterCEPRadius()
	{
		return m_uiEmitterCEPRadius;
	};
	
	/**
	* @brief	방사체 전시를 위한 EEP 장축 최소길이 획득 함수
	* @return	unsigned int	EEP 장축 최소길이
	*/
	unsigned int GetEmitterEEPMajorAxis()
	{
		return m_uiEmitterEEPMajorAxis;
	};
	
	
	/**
	* @brief	방사체 전시를 위한 EEP 단축 최소길이 획득 함수
	* @return	unsigned int		EEP 단축 최소길이
	*/
	unsigned int GetEmitterEEPMinorAxis()
	{
		return m_uiEmitterEEPMinorAxis;
	};
	
	/**
	* @brief	빔 전시를 위한 EEP 장축 최소길이 획득 함수
	* @return	unsigned int   EEP 장축 최소길이
	*/
	unsigned int GetBeamEEPMajorAxis()
	{
		return m_uiBeamEEPMajorAxis;
	};
	
	/**
	* @brief	빔 전시를 위한 EEP 단축 최소길이 획득 함수
	* @return	unsigned int    EEP 단축 최소길이
	*/
	unsigned int GetBeamEEPMinorAxis()
	{
		return m_uiBeamEEPMinorAxis;
	};	

	/**
	* @brief	유효 방사체 전시 여부 확인 함수
	* @return	bool 유효방사체 only 는 true, 그 외 false
	*/
	bool DisplayValidEmitterOnly()
	{
		return m_bDisplayValidEmitterOnly;
	};	

	/**
	* @brief	유효 빔 전시 여부 확인 함수
	* @return	bool 유효빔 only 는 true, 그 외 false
	*/
	bool DisplayValidBeamOnly()
	{
		return m_bDisplayValidBeamOnly;
	};	

	/**
	* @brief	LOB Fetch 개수 획득함수
	* @return	LOB Fetch 개수
	*/
	unsigned int GetLOBNumPerFetch()
	{
		return m_uiNumOfLOBPerFetch;
	};	

	/**
	* @brief	슈퍼바이저 LOB Fetch 개수 획득함수
	* @return	LOB Fetch 개수
	*/
	unsigned int GetLOBNumPerFetchSupervisor()
	{
		return m_uiNumOfLOBPerFetch_Supervisor;
	};	

	/**
	* @brief	PDWIQ Fetch 개수 획득함수
	* @return	PDWIQ Fetch 개수
	*/
	unsigned int GetPDWIQNumPerFetch()
	{
		return m_uiNumOfPDWPerFetch;
	};	

	/**
	* @brief	슈퍼바이저 PDWIQ Fetch 개수 획득함수
	* @return	PDWIQ Fetch 개수
	*/
	unsigned int GetPDWIQNumPerFetchSupervisor()
	{
		return m_uiNumOfPDWPerFetch_Supervisor;
	};	
};

#define GP_MGR_PARAM CParamMngr::getInstance()

