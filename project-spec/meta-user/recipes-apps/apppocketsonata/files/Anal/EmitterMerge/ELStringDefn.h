#ifndef _H_EL_STRING_DEFN
#define _H_EL_STRING_DEFN

#define LENGTH_OF_LOB_STRING	(14)

// 탐색필터 관련//
enum ENUM_SRCH_FILTER_EEP_LIMIT
{
  E_EEP_LESS_THAN_1_KM = 0,
  E_EEP_LESS_THAN_5_KM,
  E_EEP_LESS_THAN_10_KM,
  E_EEP_LESS_THAN_20_KM,
  E_EEP_LESS_THAN_50_KM,
};

static const char* strSrchFilterEEPLimit[LENGTH_OF_LOB_STRING] = 
{
  "1 km",
  "5 km",
  "10 km",
  "20 km",
  "50 km"
};

// PDW 관련 //
enum ENUM_PDW_AXIS_INFO
{
	E_NO_SELECT = 0,
	E_PDW_FRQ,
	E_PDW_TOA,
	E_PDW_PW,
	E_PDW_PA,
	E_PDW_FRQ_DIFF,
	E_PDW_DIR,
	E_PDW_PMOP,
	E_PDW_DIR_VALID,
	E_PDW_BAND,
	E_PDW_STAT
};
#define NUM_OF_PDW_AXIS_INFO 11
static const char* strPDWAxisInfo[LENGTH_OF_LOB_STRING] = 
{
	"미선택",
	"주파수",
	"TOA",
	"펄스폭",
	"신호세기",
	"주파수 차",
	"방탐",
	"PMOP",
	"방탐유효",
	"대역",
	"상태"
};



// AET - Frq Type
enum ENUM_AET_FRQ_TYPE
{
	E_AET_FRQ_UNKNOWN = 0,

	E_AET_FRQ_FIXED,
	E_AET_FRQ_HOPPING,
	E_AET_FRQ_AGILE,
	E_AET_FRQ_PATTERN,
};

#define NUM_OF_AET_FRQ_TYPE 4
/*! \bug		위협 에미터 주파수 형태 재정의
    \author 조철희 (churlhee.jo@lignex1.com)
    \date 	2013-09-23 17:22:28
*/
static const char* strAetFrqType[LENGTH_OF_LOB_STRING+1]=
{
	"-",
	"고정",
	"호핑",
	"어자일",
	"패턴"
};

// AET - Mop Type
enum ENUM_AET_MOP_TYPE
{
	E_AET_MOP_UNK = 0x00,
	E_AET_MOP_NM = 0x01,
	E_AET_MOP_PSK = 0x02,
	E_AET_MOP_FSK = 0x04,
	E_AET_MOP_LFM = 0x08,
	E_AET_MOP_NLFM = 0x10,
	E_AET_NO_PULSE = 0x20,
};
#define NUM_OF_AET_MOP_TYPE 6
/*! \bug		변조 특성 수정
    \author 조철희 (churlhee.jo@lignex1.com)
    \date 	2013-09-23 17:28:13
*/
static const char* strAetMopType[LENGTH_OF_LOB_STRING]=
{
	"모름",
	"NM",			// Non-modulation
	"PSK",		// PSK
	"FSK",		// FSK
	"LFM",		// LFM
	"NLFM",		// NLFM
	"개수부족"
};

// AET - PRI Type
enum ENUM_AET_PRI_TYPE
{
	E_AET_PRI_FIXED=0,
	E_AET_PRI_JITTER,
	E_AET_PRI_DWELL_SWITCH,
	E_AET_PRI_STAGGER,
	E_AET_PRI_PATTERN,
	
	//E_AET_PRI_BEACON, // 2015.4.12. 추가. 현재 ICD에 반영되어 있지 않음.
};
#define NUM_OF_AET_PRI_TYPE		5
/*! \bug		PRI 형태 변경
    \author 조철희 (churlhee.jo@lignex1.com)
    \date 	2013-09-23 17:31:24
*/
static const char* strAetPriType[LENGTH_OF_LOB_STRING+1]=
{
	"고정",
	"지터",
	"D&S",
	"스태거",
	"패턴",
	
};


// AET - 주파수/PRI 패턴 Type
enum ENUM_AET_FREQ_PRI_PATTERN_TYPE
{
	E_AET_FREQ_PRI_UNKNOWN = 0,
	E_AET_FREQ_PRI_SINE,
	E_AET_FREQ_PRI_SLIDE_INC,
	E_AET_FREQ_PRI_SLIDE_DEC,
	E_AET_FREQ_PRI_SAW_TRI
};

#define NUM_OF_AET_PRI_PATTERN_TYPE 5
/*! \bug  	스캔 형태 값 수정
    \author 조철희 (churlhee.jo@lignex1.com)
    \date 	2013-09-23 19:09:12
*/
static const char* strAetFreqPRIPatternType[LENGTH_OF_LOB_STRING]=
{
	"모름",
	"사인",
	"SL+",
	"SL-",
	"삼각"
};


// AET - Scan Type
#define NUM_OF_AET_SCAN_TYPE 3
enum ENUM_AET_SCAN_TYPE
{
	E_AET_SCAN_UNKNOWN = 0,
	E_AET_SCAN_TRACKING,
	E_AET_SCAN_SEARCH,
	/*! \todo   스캔 분석이 더 좋아지면 추후에 고려... (IdentifyScan() 함수에 비교 추가)
	    \author 조철희 (churlhee.jo@lignex1.com)
	    \date 	2014-12-30 13:56:52
	*/
	E_AET_SCAN_SECTOR
};
#define NUM_OF_AET_SCAN_TYPE 3
/*! \bug  	스캔 형태 값 수정
    \author 조철희 (churlhee.jo@lignex1.com)
    \date 	2013-09-23 19:09:12
*/
static const char* strAetScanType[LENGTH_OF_LOB_STRING]=
{
	"모름",
	"추적",
	"탐색",
	"섹터"
};

// AET - FISINT 과제
enum ENUM_AET_FISINT_TASK
{
	E_AET_FISINT_TASK_UNSET = 0,
	E_AET_FISINT_TASK_SET
};
#define NUM_OF_AET_FISINT_TASK 2
static const char* strAetFisintTask[LENGTH_OF_LOB_STRING]=
{
	"미설정",
	"설정"
};

//// AET 관련  - Signal Type// 2014.03.18. aet 신호형태 정의가 이상해서 수정.
enum ENUM_AET_SIGNAL_TYPE
{
	E_AET_SIGNAL_PULSE = 0,
	E_AET_SIGNAL_CW,
};
#define NUM_OF_AET_SIGNAL_TYPE 2
static const char* strAetSignalType[LENGTH_OF_LOB_STRING] = 
{
	"Pulse",
	"CW",
};

//// PDW 관련  - Signal Type// 2014.03.18. aet 신호형태 정의를 사용해 오고 있었으나, 실제 ICD 내용과 다르기 때문에 재정의함.
enum ENUM_PDW_SIGNAL_TYPE
{
	E_PDW_SIGNAL_CW = 0,
	E_PDW_SIGNAL_PULSE,
};
#define NUM_OF_PDW_SIGNAL_TYPE 2
static const char* strPdwSignalType[LENGTH_OF_LOB_STRING] = 
{
	"CW",
	"Pulse",
};


//// AET 관련  - 저장여부//
enum ENUM_AET_STORED_PDW
{
	E_AET_STORED_PDW = 0,
	E_AET_NOT_STORED_PDW = 1
};
#define NUM_OF_AET_STORED_PDW 2
static const char* strAetStoredPDW[LENGTH_OF_LOB_STRING] = 
{
	"저장",
	"저장안함"
};

// 과제 관리
enum ENUM_DATA_MGNT
{
	E_DATA_MGNT_RECORD_ONLY = 0,
	E_DATA_MGNT_RECORD_AND_TRANSMIT,
	E_DATA_MGNT_TRANSMIT_ONLY,
	E_DATA_MGNT_NO_ACTION
};
#define NUM_OF_ENUM_DATA_MGNT 4
static const char* strDataMgnt [LENGTH_OF_LOB_STRING] =
{
	"저장",
	"저장+전송",
	"전송",
	"없음"
};

// 과제종류
enum ENUM_EL_TASK
{
	E_EL_TASK_SRCH_WB = 0,	// 탐지광대역
	E_EL_TASK_SRCH_NB,		// 탐지협대역
	E_EL_TASK_HG_WB,			// 고감도광대역
	E_EL_TASK_HG_NB,			// 고감도협대역
	E_EL_INVALID_TASK
};
#define NUM_OF_ENUM_EL_TASK 4
static const char* strElintTask [LENGTH_OF_LOB_STRING] =
{
	"탐지광대역",
	"탐지협대역",
	"고감도광대역",
	"고감도협대역"
};

#define NUM_OF_ENUM_EL_SUMMARYTASK 2
enum ENUM_EL_SMIPLE_TASK
{
	E_EL_TASK_SRCH = 0,		// 탐지 과제
	E_EL_TASK_HG,					// 고감도 과제
};
static const char* strSummaryTask [LENGTH_OF_LOB_STRING] =
{
	"탐지",
	"고감도"
};



enum ENUM_EL_DT_ANT_DIR
{
	E_EL_DT_ANT_LEFT = 0,	// 좌측
	E_EL_DT_ANT_RIGHT,		// 우측
	E_EL_DT_ANT_BOTH,			// BOTH
};
#define NUM_OF_ENUM_EL_DT_ANT_DIR 3
static const char* strDetAntDirection [LENGTH_OF_LOB_STRING] =
{
	"좌",
	"우",
	"BOTH",
	"-"
};

#define NUM_OF_ENUM_EL_LINK 2
static const char* strLinkNum2 [LENGTH_OF_LOB_STRING] =
{
	"링크 #1",
	"링크 #2"
};

#ifndef ENUM_NB_PATH
#define ENUM_NB_PATH
enum EnumNBPath
{
	E_EL_NBP_NONE_AMPLITY=0,	//비증폭
	E_EL_NBP_AMPLITY,			//증폭	
	E_EL_NBP_HIGH_AMPLITY,	//고증폭 (추가됨*)
	E_EL_NBP_AUTO,				//자동
};
#endif

#define NUM_OF_ENUM_EL_RX_PATH 4
static const char* strRxPath [LENGTH_OF_LOB_STRING] =
{
	"비증폭",
	"증폭",
	"고증폭",
	"자동"
};

#define NUM_OF_ENUM_EL_PDW_BLK 2
static const char* strPdwBLK [LENGTH_OF_LOB_STRING] =
{
	"미검출",
	"검출"
};

#define NUM_OF_ENUM_EL_PDW_FLAG 2
static const char* strPdwFlag [LENGTH_OF_LOB_STRING] =
{
	"X",
	"O"
};

#define NUM_OF_ENUM_EL_PDW_VALID 2
static const char* strPdwDirectionValid [LENGTH_OF_LOB_STRING] =
{
	"유효",
	"무효"
};


#define NUM_OF_ENUM_EL_PDW_FOV 2
static const char* strPdwFOV [LENGTH_OF_LOB_STRING] =
{
	"정상",
	"비정상"
};

/*!
 * @enum			ENUM_AET_PRI_TYPE
 * @brief			극성
 * @author    조철희
 * @date      2014-12-31 
 */
enum ENUM_AET_POLIZATION_TYPE
{
	E_AET_POLIZATION_UNK = -1,
	E_AET_POLIZATION_V = 0,
	E_AET_POLIZATION_H,
	E_AET_POLIZATION_RC,
	E_AET_POLIZATION_LC,
	E_AET_POLIZATION_RS,
	E_AET_POLIZATION_LS,
	E_AET_POLIZATION_ERROR
};

#define NUM_OF_ENUM_EL_PDW_POL 6
static const char* strPdwPOL [LENGTH_OF_LOB_STRING] =
{
	"V",
	"H",
	"RC",
	"LC",
	"RS",				// RS, S+
	"LS",				// LS, S-
	"-"
};

#define NUM_OF_ENUM_EL_CHANNEL_CHANGE 4
static const char* strChnChg [LENGTH_OF_LOB_STRING] =
{
	"없음",
	"POP",
	"하향",
	"상향",
	"모름"
};

// RAW 데이터 종류
#define NUM_OF_RAW_DATA_TYPE 3
enum ENUM_RAW_DATA_TYPE
{
	E_RAW_DATA_PDW = 0,	// PDW
	E_RAW_DATA_IQ,		// IQ
	E_RAW_DATA_IF			// IF	
};
static const char* strRawDataType [LENGTH_OF_LOB_STRING] = 
{
	"PDW",
	"IQ",
	"IF"
};

// 식별 일치율 종류
#define NUM_OF_CONSISTENCY 3
enum ENUM_CONSISTENCY_TYPE
{
	E_CERTAIN = 0,	// 확실
	E_UNCERTAIN,		// 비확실
	E_CANT_DECISION	// 판단불가
};
static const char* strConsistencyType [LENGTH_OF_LOB_STRING] = 
{
	"확실",
	"비확실",
	"판단불가"
};

// 위치산출 유무효
#define NUM_OF_VALIDITY	3
enum ENUM_VALIDITY_TYPE
{
	E_INVALID = 0,	// 무효
	E_VALID,				// 유효
	E_NOT_IGNORE		// 무시
};
static const char* strValidityType [LENGTH_OF_LOB_STRING] = 
{
	"무효",
	"유효",
	"-"
};
static const char* strValidityType2[LENGTH_OF_LOB_STRING] = 
{
	"유효",
	"무효",
	"-"
};

#define NUM_OF_ENUM_EL_COMMON_FLAG 2
static const char* strCommonFlag [LENGTH_OF_LOB_STRING] =
{
	"X",
	"O"
};

enum ENUM_POS_SYNC_TYPE
{
	E_POS_SYNC_AET = 0,	// AET
	E_POS_SYNC_PDW,	// PDW
	E_POS_SYNC_IQ,			// IQ	
	E_POS_SYNC_IF,
};

#define NUM_OF_ENUM_EL_BIT_FLAG 2
static const char* strBitFlag [LENGTH_OF_LOB_STRING] =
{
	"외부신호",
	"BIT신호"
};

enum ENUM_BIT_FLAG
{
	E_BIT_FLAG_EXT_SIG = 0,	// 외부신호
	E_BIT_FLAG_BIT_SIG,			// BIT신호
};

static const char* strStorageType [LENGTH_OF_LOB_STRING] = 
{
	"IF(ODD)",
	"IF(EVEN)",
	"디지털"
};

// 2018.04.17 활동여부 전시를 위한 정의
static const char* strActivityType [LENGTH_OF_LOB_STRING] = 
{
	"미활동",
	"활동",
	"활동",
	"미활동",
	"활동",
	"활동"
};

//#define STR_AIR_INDEPENDENT_DC_TASK		"DC_TASK"	//
//#define STR_AIR_INDEPENDENT_HG_TASK		"HG_TASK"	//

#ifdef _ELINT_
const char aet_signal_type[7][3] = { "NP" , "CW" , "DP" , "FM" , "CF", "SH", "AL" };
const char aet_freq_type[6][3] = { "--", "F_" , "HP" , "RA" , "PA", "UK" };
const char aet_pri_type[6][3] = { "ST" , "JT", "DW" , "SG" , "PT" } ;
const char aet_asp_type_ch[7][3] = { "UK" , "CR" , "UD" , "BD" , "CO" , "ST" , "UF" } ;
const char aet_stat[5] = { 'N', 'U', 'M', 'L', 'D' } ;

#elif defined(_POCKETSONATA_)
static const char aet_signal_type[5][3] = { "UK" , "NP" , "CW" , "DP" , "HP" };
static const char aet_freq_type[8][3] = { "F_" , "RA" , "PA", "HP", "C+", "C-", "pM" };
static const char aet_pri_type[6][3] = { "ST" , "SG" , "JT" , "PT", "DW" } ;
static const char aet_asp_type_ch[7][3] = { "UK" , "CR" , "SC" , "TW" , "CO" , "ST" , "MA" } ;

#else

#endif

#endif
