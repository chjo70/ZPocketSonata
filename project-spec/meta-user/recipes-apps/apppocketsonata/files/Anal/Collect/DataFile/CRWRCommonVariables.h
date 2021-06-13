/**
* @file CRWRCommonVariables.h
* RWR Operation CSC에서 사용하는 공용변수 및 함수 헤더 파일
* RWR Operation CSC의 공용변수 및 함수를 지원한다.
*/
#ifndef RWRCOMMONVARIABLES_H_
#define RWRCOMMONVARIABLES_H_

#ifndef _WIN32
#include <stdint.h>
#endif



#ifdef _POCKETSONATA_
#ifdef __linux__
#include "../../../Utils/chwio.h"
#endif
//#include "../../Test/hw_interface.h"

#else

#endif

#pragma pack( push, 1 )


//#include <Data/CPDWContainer.h>
//#include <SignalProcessing/CSignalProcessingVariables.h>
//#include <Util/Time/CStopWatch.h>
// #include <ns_api.h>
// #include <algorithm>
// #include <stdio.h>
// #include <vector>
// #include <list>
// #include <map>

/**
* @brief 다음상태메시지 
* COLLECT_STOP: 수집중지, 허용값: 1
* MDF_MODE_CHANGE_REQ: MDF모드변경, 허용값: 2
* THREAT_INIT: 위협초기화, 허용값: 3
* SEARCH_BAND_SEND_END: 탐색대역설정완료, 허용값: 4
* UNKNOWN_MSG: 무효 메시지, 허용값: 5
* SIZE_OF_NEXT_ACTION: 사이즈
*/
typedef enum _NextActionMsg
{
	COLLECT_STOP 							= 1,
	MDF_MODE_CHANGE_REQ						= 2,
	THREAT_INIT								= 3,
	SEARCH_BAND_SEND_END					= 4, 
	UNKNOWN_MSG								= 5,
	SIZE_OF_NEXT_ACTION
}NextActionMsg;

/**
* @brief 동적탐색대역 구분 
* UNKNOWN_NO: 미식별, 허용값: 0
* JLT_NO: Jamming LT, 허용값: 1
* ILT_NO: Interference LT, 허용값: 2
* XCC_NO: X대역 동적탐색대역 요청, 허용값: 3
* SCAN_NO: 스캔분석 동적탐색대역 생성, 허용값: 4
*/
typedef enum _DynamicBandType
{
	UNKNOWN_NO								= 0,
	JLT_NO 									= 1,
	ILT_NO	 								= 2,
	XCC_NO									= 3,
	SCAN_NO									= 4
}DynamicBandType;

/**
* @brief PDW컨테이너상태
* INIT: 초기상태, 허용값: 0x0000
* COLLET_START: 수집시작, 허용값: 0x1000
* COLLECT_END: 수집완료상태 수신완료, 허용값: 0x0001
* PDW_STORE_REQ: PDW 저장 요청, 허용값: 0x0010
* FULL: PDW 저장 완료, 허용값: 0x0100
* PDW_STORE_END: 수집완료 상태 수신 후 PDW 저장 완료, 허용값: 0x0101
* PDW_STORING: 수집완료 상태 수신 후 PDW 저장 요청, 허용값: 0x0011
* SIGPROC_DOING: 신호처리중, 허용값: 0x0111
* UNKNOWN: 미지정, 허용값: 0xFFFF
*/
typedef enum _EContainerState
{
	INIT							= 0x0000,		///< 초기상태	
	COLLET_START					= 0x1000,		///< 수집시작
	COLLECT_END						= 0x0001,		///< 수집완료 상태 수신 완료
	PDW_STORE_REQ					= 0x0010,		///< PDW 저장 요청
	FULL							= 0x0100,		///< PDW 저장 완료
	PDW_STORE_END					= 0x0101,		///< 수집완료 상태 수신 후 PDW 저장 완료
	PDW_STORING						= 0x0011, 		///< 수집완료 상태 수신 후 PDW 저장 요청
	SIGPROC_DOING					= 0x0111,		///< 신호처리중
	UNKNOWN							= 0xFFFF,
}EContainerState;

/**
 * @brief 수집가능상태
 * CAN_COLLECT: 수집가능, 허용값: 0x0
 * CAN_NOT_COLLECT: 수집불가능, 허용값: 0x1
 */
typedef enum _ECollectFlag
{
	CAN_COLLECT						= 0x0,		///< 초기상태	
	CAN_NOT_COLLECT					= 0x1		///< 수집완료 상태 수신 완료
}ECollectFlag;

/**
 * @brief 간섭대역결과 전송 목적지
 * DRC_DES: DRC, 허용값: 0x0
 * JMMC_DES: JMMC, 허용값: 0x1
 */
typedef enum _DesType
{
	DRC_DES = 0,
	JMMC_DES = 1
}DesType;

/**
 * @brief 신호처리 경과시간
 * PDW_STORE_ELAPSED_TIME: PDW저장 경과시간, 허용값: 0
 * SIG_ANALYSIS_TIME: 신호분석 경과시간, 허용값: 1
 * EMITTER_IDENTIFY_TIME: 에미터식별 경과시간, 허용값: 2
 * INSERT_PRE_AET_TIME: PreAET 삽입 시간, 허용값: 3
 * MANAGE_THREAT_TIME: 위협관리 시간, 허용값: 4
 * ARRANGE_THREAT_TIME: 위협정렬 시간, 허용값: 5
 * POST_CLEANING_TIME: 위협초기화 시간, 허용값: 6
 */
typedef enum _ElapsedTimeType
{
	PDW_STORE_ELAPSED_TIME 	= 0,
	SIG_ANALYSIS_TIME		= 1,
	EMITTER_IDENTIFY_TIME	= 2,
	INSERT_PRE_AET_TIME		= 3,
	MANAGE_THREAT_TIME		= 4,
	ARRANGE_THREAT_TIME		= 5, 
	POST_CLEANING_TIME		= 6,
}ElapsedTimeType;

/**
* @struct SAESAOPerationFreqData
* - 구조체 설명
* AESA운용모드
* - 설계결정사항
* 없음
*/
struct SAESAOPerationFreqData
{
	SAESAOPerationFreqData() : m_operationMode(0), m_freqMin(0), m_freqMax(0) {}
	
	unsigned short m_operationMode;
	unsigned int m_freqMin;
	unsigned int m_freqMax;
};


/**
* @struct SXCCDynamicBand
* - 구조체 설명
* X대역 동적탐색대역요청 정보
* - 설계결정사항
* 없음
*/
struct SXCCDynamicBand
{
	SXCCDynamicBand() : m_beamID(0), m_freqMin(0), m_freqMax(0) {}
	
	unsigned int m_beamID;
	unsigned int m_freqMin;
	unsigned int m_freqMax;
};

/**
* @struct SInterferenceInfo
* - 구조체 설명
* 간섭대역요청정보
* - 설계결정사항
* 없음
*/
struct SInterferenceInfo
{
	SInterferenceInfo() : m_jammingAllocNo(0), m_AETNumber(0), m_freqMin(0), m_freqMax(0) {}
	
	unsigned char m_jammingAllocNo;
	unsigned int m_AETNumber;
	unsigned int m_freqMin;
	unsigned int m_freqMax;
};


/**
* @struct SJammingFreq
* - 구조체 설명
* 간섭대역주파수정보
* - 설계결정사항
* 없음
*/
struct SJammingFreq
{
	SJammingFreq() : m_freqMin(0.0), m_freqMax(0.0){}
	
	float m_freqMin;
	float m_freqMax;
};


/**
* @struct SDRCCollectEndState
* - 구조체 설명
* 수집상태정보 구조체
* - 설계결정사항
* 없음
*/
struct SDRCCollectEndState
{
	SDRCCollectEndState() : m_searchBandNumber(0), m_isOVP(0), m_endState(0), m_PDWCount(0){}
				
	unsigned int m_searchBandNumber;	
	unsigned int m_isOVP;		
	unsigned int m_endState;				
	unsigned int m_PDWCount;					
};


/**
* @struct SCollectEndState
* - 구조체 설명
* 신호수집완료 구조체
* - 설계결정사항
* 없음
*/
// struct SCollectEndState
// {
// 	SCollectEndState() : m_PDWCount(0), m_searchBandNumber(0), m_containerIndex(0), m_fullCheck(CAN_COLLECT), m_endState(0), m_collectFail(0), m_bandGroup(INIT_BAND){}
// 	
// 	void Init()
// 	{
// 		m_PDWCount = 0;
// 		m_searchBandNumber = 0;
// 		m_containerIndex = 0;
// 		m_fullCheck = CAN_COLLECT;
// 		m_endState = 0;
// 		m_collectFail = 0;
// 		m_bandGroup = INIT_BAND;
// 	}
// 	
// 	unsigned int m_PDWCount;					///< 수집개수
// 	unsigned int m_searchBandNumber;			///< 탐색대역번호
// 	int m_containerIndex;						///< PDW컨테이너 인덱스
// 	ECollectFlag m_fullCheck;					///< Container Full 여부
// 	unsigned int m_endState;					///< 완료상태 구분
// 	unsigned char m_collectFail;				///< 수집실패상태
// 	EBandGroup m_bandGroup;						///< 밴드그룹
// };


/**
* @struct SInformationOfPDWs
* - 구조체 설명
* 신호수집완료 구조체
* - 설계결정사항
* 없음
*/
struct SInformationOfPDWs
{
	SInformationOfPDWs() : m_searchBandNumber(0), m_eraseState(0), m_PDWCount(0){}
	
	unsigned int m_searchBandNumber;			///< 수집완료한 탐색대역번호
	unsigned int m_eraseState;					///< 완료상태 구분
	unsigned int m_PDWCount;					///< PDW 개수
};


/**
* @struct SReqPDW
* - 구조체 설명
* PDW전송요청 데이터 구조체
* - 설계결정사항
* 없음
*/
struct SReqPDW
{	
	SReqPDW() : m_bandNumber(0), m_PDWCount(0){}
	
	unsigned int m_bandNumber;					///< 수집개수
	unsigned int m_PDWCount;					///< 탐색대역번호
};

/**
* @struct SJLTData 
* - 구조체 설명
* Jamming LT 데이터 구조체
* - 설계결정사항
* 없음
*/
struct SJLTData
{
	SJLTData() : m_AETNo(0), m_freqMin(0), m_freqMax(0){}
		
	void Init()
	{
		m_AETNo = 0;
		m_freqMin = 0;
		m_freqMax = 0;
	}
	
	unsigned int m_AETNo;						///< AET번호
	unsigned int m_freqMin;						///< 최소 주파수
	unsigned int m_freqMax;						///< 최대 주파수
};

/**
* @struct SBandForLT 
* - 구조체 설명
* LT를 위한 탐색대역
* - 설계결정사항
* 없음
*/
struct SBandForLT
{	
	SBandForLT() : m_searchBandNumber(0), m_JLTAETNo(0), m_freqMin(0.0), m_freqMax(0.0){}
	
	int m_searchBandNumber;
	unsigned int m_JLTAETNo;
	float m_freqMin;
	float m_freqMax;
};
 
/**
* @struct SNewCollectData 
* - 구조체 설명
* 수집제어정보
* - 설계결정사항
* 없음
*/
struct SNewCollectData
{
	SNewCollectData() : m_bandGroup(0), m_currentNumber(0), m_nextNumber(0) {}
	
	unsigned int m_bandGroup;
	unsigned int m_currentNumber;
	unsigned int m_nextNumber;
};


/**
* @struct SScanCollectInfo
* - 구조체 설명
* 스캔상세분석을 위한 기본정보
* - 설계결정사항
* 없음
*/
struct SScanCollectInfo
{	
	SScanCollectInfo() : m_searchNo(0), m_AETNo(0),  m_collectTime(0), m_collectCount(0){}
	
	int m_searchNo;
	int m_AETNo;
	float m_collectTime;
	unsigned int m_collectCount;
};

/**
* @struct SElapsedTimeData
* - 구조체 설명
* 경과시간 측정 구조체
* - 설계결정사항
* 없음
*/
// struct SElapsedTimeData
// {
// 	SElapsedTimeData() : pWatchTimer(NULL), m_PDWStoreTime(0.0), m_analysisTime(0.0), m_identifyTime(0.0), 
// 			m_preAETMakeTime(0.0), m_manageThreatTime(0.0), m_arrangeThreatTime(0.0), m_postCleaningTime(0.0), m_totalTime(0.0)
// 	{
// 		pWatchTimer = new CStopWatch(); 
// 	}
// 	
// 	~SElapsedTimeData()
// 	{
// 		if(pWatchTimer != NULL)
// 		{
// 			delete pWatchTimer;
// 		}
// 	}
// 	
// 	void Init()
// 	{
// 		m_PDWStoreTime = 0.0;
// 		m_analysisTime = 0.0;
// 		m_identifyTime = 0.0;
// 		m_preAETMakeTime = 0.0;
// 		m_manageThreatTime = 0.0;
// 		m_arrangeThreatTime = 0.0;
// 		m_postCleaningTime = 0.0;
// 		m_totalTime = 0.0;
// 	}
// 	
// //	CStopWatch* pWatchTimer;
// 	double m_PDWStoreTime;
// 	double m_analysisTime;
// 	double m_identifyTime;
// 	double m_preAETMakeTime;
// 	double m_manageThreatTime;
// 	double m_arrangeThreatTime;
// 	double m_postCleaningTime;
// 	
// 	double m_totalTime;
// };

#define LITTLE_ENDIAN_MODE


struct POCPDW {
    union {
        unsigned int pdw_index;

        struct {
            unsigned int index	  : 16;
            unsigned int reserved : 16;
        } stPdw_index;
    } uniPdw_index;

    union
    {
        unsigned int		pdw_toa_edge;
        struct
        {
            unsigned int 		toa_H			: 28;
            unsigned int 		edge			: 1;
            unsigned int 		reserved		: 3;
        }stPdw_toa_edge;
    }uniPdw_toa_edge;

    union
    {
        unsigned int		pdw_freq_toa;
        struct
        {
            unsigned int 		frequency_H	: 8;
            unsigned int 		pdw_phch		: 8;
            unsigned int		toa_L			: 16;
        }stPdw_freq_toa;
    }uniPdw_freq_toa;

    union
    {
        unsigned int		pdw_pw_freq;
        struct
        {
            unsigned int 		pulse_width	: 24;
            unsigned int 		frequency_L	: 8;
        }stPdw_pw_freq;
    }uniPdw_pw_freq;

    union
    {
        unsigned int	pdw_dir_pa;
        struct
        {
            unsigned int 		doa				: 12; // res = 0.087890625 deg
            unsigned int 		di				: 1; // '0' - Valid, '1' - invalid
            unsigned int 		reserved		: 3;
            unsigned int 		pa				: 16; // res = 0 ~ 65536 (linear scale)
        }stPdw_dir_pa;
    }uniPdw_dir_pa;

    union {
            unsigned int	pdw_status;
            struct
            {
                unsigned int 		cw_pulse		: 1; // '0' - pulse, '1' - CW
                unsigned int 		pmop			: 1; // '0' - No-mop, '1'-mop
                unsigned int 		fmop			: 1; // '0' - No-mop, '1'-mop
                unsigned int 		false_pdw		: 1; // '0' - ture, '1'-false
                unsigned int 		fmop_dir		: 2; // '0' - tri, '1' - up, '2' - down, '3' - unknown
                unsigned int 		reserved		: 10;
                unsigned int 		fmop_bw		: 16; // res = 3.11MHz
            }stPdw_status;
    } uniPdw_status;
} ;

/**
* union UDRCPDW
* - union 설명
* PDW
* - 설계결정사항
* 없음
*/
union UDRCPDW
{
    char chData[32];

#ifndef LITTLE_ENDIAN_MODE

	struct
	{
		//1
		unsigned int m_LSBTOA :			32;
		
		//2
		unsigned int m_MSBTOA :			10;
		unsigned int m_Ovp :			1;
		unsigned int m_PA :				9; 
		unsigned int m_Rsvd :			3;
		unsigned int m_DOA :			9;
		
		//3
		unsigned int m_ChNo :			4;
		unsigned int m_sigType :		1; // 0:CW, 1:Pulse
		unsigned int m_BLK :			1;
		unsigned int m_FMOP :			1;
		unsigned int m_PMOP :			1;
		unsigned int m_ChChg :			2;
		unsigned int m_DI :				1;
		unsigned int m_freq :			21; 
		
		//4
		unsigned char m_ft1 : 			1;
		unsigned char m_ft2 : 			1;
		unsigned char m_ft3 : 			1;
		unsigned char m_ft4 : 			1;
		unsigned char m_ft5 : 			1;
		unsigned char m_ft6 : 			1;
		unsigned char m_ft7 : 			1;
		unsigned char m_ft8 : 			1;
		unsigned char PWI : 			1;
		unsigned char TOAI:				1;
		unsigned int m_PW :				22;

		//5
		unsigned int m_PDWNum :			32;
		
		//6
		unsigned int m_Rsvd2 :			3;
		unsigned int m_FMOPMinFreq :	13;
		unsigned int m_Rsvd3 :			3;
		unsigned int m_FMOPMaxFreq :	13;
		
		//7
		unsigned int m_PMOPRsvdTime	:	20;
		unsigned int m_PMOPCount :		8;
		unsigned int m_Rsvd4 :			2;
		unsigned int m_PMOPMode :		2;
		
		//8
		unsigned int m_Rsvd5 :			16;
		unsigned int m_AntPAGap : 		8;
		unsigned char m_Rsvd6 : 		2;
		unsigned char m_secondAnt :		2;
		unsigned char m_Rsvd7 : 		2;
		unsigned char m_firstAnt : 		2;
		
	} sPDWFormat;

#else
	struct
	{
		//1
		unsigned int m_LSBTOA :32;

		//2
		unsigned int m_DOA :9;
		unsigned int x1 :3;
		unsigned int m_PA :9;
		unsigned int m_Ovp :1;
		unsigned int m_MSBTOA :10;

		//3
		unsigned int m_freq :21;
		unsigned int m_DI :1;
		unsigned int m_ChChg :2;
		unsigned int m_PMOP :1;
		unsigned int m_FMOP :1;
		unsigned int m_BLK :1;
		unsigned int m_sigType :1;
		unsigned int m_ChNo :4;

		//4
		unsigned int m_PW :22;
		unsigned int m_TOAinvalid :1;
		unsigned int m_PWinvalid :1;
		unsigned int m_ft8 :1;
		unsigned int m_ft7 :1;
		unsigned int m_ft6 :1;
		unsigned int m_ft5 :1;
		unsigned int m_ft4 :1;
		unsigned int m_ft3 :1;
		unsigned int m_ft2 :1;
		unsigned int m_ft1 :1;

		//5
		unsigned int m_PDWNum :32;

		//6
		unsigned int m_FMOPMaxFreq :13;
		unsigned int m_Rsvd3 :3;
		unsigned int m_FMOPMinFreq :13;
		unsigned int m_Rsvd2 :3;

		//7
		unsigned int m_PMOPMode :2;
		unsigned int m_Rsvd4 :2;
		unsigned int m_PMOPCount :8;
		unsigned int m_PMOPRsvdTime :20;

		//8
		unsigned int m_Ant_1st :2;
		unsigned int m_Rsvd5 :2;
		unsigned int m_Ant_2nd :2;
		unsigned int m_Rsvd6 :2;
		unsigned int m_PA_Diff :8;
		unsigned int m_Rsvd7 :16;

	}sPDWFormat;
#endif

};

#if CPU == _VX_PPCE6500
	#define SEND_MASKING(Value)		(ERWRTaskMsg)(((Value & 0xFFFF) << 8) | 0x11120000)
	#define RECV_MASKING(Value)		(ERWRTaskMsg)((Value & 0x0000FF00) >> 8)
#else
	#define SEND_MASKING(Value)		(ERWRTaskMsg)(((Value & 0xFFFF) << 8) | 0x11120000)
	#define RECV_MASKING(Value)		(ERWRTaskMsg)((Value & 0x0000FF00) >> 8)
#endif


extern bool sigProcLog;
extern bool sigProcTimeFlag;
extern bool totalTimeFlag;

void SigProcLogOff();
void SigProcLogOn();

void SigProcTimeOff();
void SigProcTimeOn();

void SigProcLogOff();
void SigProcLogOn();

/**
* @class CRWRCommonVariables 
* @brief
* RWR Operation manager CSC의 공용변수 및 함수를 지원한다
* - 설계결정사항
* 없음
*/
// class CRWRCommonVariables
// {
// 	private : 
// 		/**
// 		* @brief 최대 태스크 개수
// 		*/
// 		int m_taskCount;
// 		
// 		/**
// 		* @brief 탐색대역번호별 타임아웃 카운트 맵 
// 		*/
// 		std::map<int, bool> m_pTimeOutPDWContainersMap;
// 		
// 		/**
// 		* @brief 신호분석 PA 해상도
// 		*/
// 		double m_SigProcPAResolution;
// 		
// 		/**
// 		* @brief 신호분석 AOA 해상도
// 		*/
// 		double m_SigProcAOAResolution;
// 		
// 		/**
// 		* @brief 수집완료 Timeout 이후 오류처리 확인용 PDW패키지 인덱스
// 		*/
// 		int m_PDWPackageIndex;
// 		
// 		/**
// 		* @brief 수집완료 타이머 활성화 여부 판단 변수
// 		*/
// 		std::vector<bool> m_collectEndTimeoutList;
// 		
// 		/**
// 		* @brief 신호처리 경과시간 측정 데이터 맵
// 		*/
// 		std::map<int, SElapsedTimeData*> m_SigProcElapsedTimerList;
// 		
// 		/**
// 		* @brief 신호처리 경과시간 측정 데이터 맵 type definition
// 		*/
// 		typedef std::map<int, SElapsedTimeData*> TimerMap;
// 		
// 	public:
// 		
// 		/**
// 		* @brief 미확인 신호처리태스크 ID
// 		*/
// 		const static int m_unknownSigProcID;
// 		
// 		/**
// 		* @brief 유효하지않은 탐색대역번호
// 		*/
// 		const static int m_notValidBandNo;
// 		
// 		/**
// 		* @brief 유효하지않은  AET번호
// 		*/
// 		const static int m_notValidAETNo;
// 		
// 		/**
// 		* @brief 태스트용 탐색대역번호 최대 개수
// 		*/
// 		const static int m_searchBandMaxCount;
// 		
// 		/**
// 		* @brief PDW 최대 개수
// 		*/
// 		const static unsigned int m_MaxPDWCount;
// 
// 		/**
// 		* @brief PDW저장 재시도 횟수
// 		*/
// 		const static int m_PDWStoreTryCount;
// 		
// 		/**
// 		* @brief 수집요청 재시도 횟수
// 		*/
// 		const static int m_collectTryCount;
// 		
// 		/**
// 		* @brief 정상수집완료
// 		*/
// 		const static int m_normalCollectEnd;
// 		
// 		/**
// 		* @brief PDW 컨테인너 Full완료
// 		*/
// 		const static int m_PDWContainerFullEnd;
// 		
// 		/**
// 		* @brief Timeout 완료
// 		*/
// 		const static int m_timeoutCollectEnd;
// 
// 		/**
// 		* @brief 수집실패
// 		*/
// 		const static int m_collectFail;
// 		
// 		/**
// 		* @brief 시간 해상도
// 		*/
// 		const static double	m_timeRes;
// 		
// 		/**
// 		* @brief PA 해상도
// 		*/
// 		const static double m_PARes;
// 		
// 		/**
// 		* @brief PA 오프셋
// 		*/
// 		const static double m_PAOffset;
// 		
// 		/**
// 		* @brief 방위 해상도
// 		*/
// 		const static double	m_DOARes;
// 		
// 		/**
// 		* @brief 주파수 해상도
// 		*/
// 		const static double m_freqRes;
// 		
// 		/**
// 		* @brief 펄스폭 해상도
// 		*/
// 		const static double m_PWRes;
// 		
// 		/**
// 		* @brief PMOP 최소간격 해상도
// 		*/
// 		const static double m_PMOPRes;
// 		
// 		/**
// 		* @brief PMOP 최소간격 해상도
// 		*/
// 		const static int m_FMOPOffSet;
// 		
// 		/**
// 		* @brief 수집실패판단 시간 마진
// 		*/
// 		const static int m_collectWaitMarginTime;
// 
// 		/**
// 		* @brief PDW저장 대기 시간
// 		*/
// 		const static int m_storeWaitTime;
// 		
// 		/**
// 		* @brief 동적탐색대역번호 개수 임계치
// 		*/
// 		const static int m_dynamicBandNoCountThreshold;
// 		
// 		/**
// 		* @brief ILT동적탐색대역참조데이터 최대값
// 		*/
// 		const static int m_ILTRefDataMax;
// 		
// 		/**
// 		* @brief 무효 RLog 시퀀스 번호
// 		*/
// 		const static int m_notAvailableSequence;
// 		
// 		CRWRCommonVariables(int PDWContainerCount);
// 		
// 		~CRWRCommonVariables();
// 		
// 		void SetResolutions(CPDWContainer* pPDWContainer);
// 		
// 		double GetSigProcPAResolution();
// 		
// 		double GetSigProcAOAResolution();
// 		
// 		bool CheckTimeOutPDWContainer(int PDWContainerIndex);
// 		
// 		void InsertTimeOutFlag(int PDWContainerIndex, bool flag);
// 		
// 		void SetTimeOutCollectEndFlag(int containerIndex, bool flag);
// 		
// 		bool GetTimeOutCollectEndFlag(int containerIndex2);
// 		
// 		CStopWatch* GetSigProcElapsedTimer(int sigProcIndex);
// 		
// 		void SaveCurrentElapsedTime(ElapsedTimeType timeType, int currSigProcIndex, double toSaveTime);
// 		
// 		SElapsedTimeData* GetCurrentElapsedTimeData(int currSigProcIndex);
// 		
// 		const char* GetConvertedSearchBandGroupString(EBandGroup searchBandGroup) const;
// 		
// 		double GetTotalSigProcElapsedTime(int completeSigProcIndex);		
// 		
// };

#pragma pack( pop )

#endif
