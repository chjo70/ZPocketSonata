
#pragma once

#ifndef __VXWORKS__
#include <memory.h>
#endif

#include <vector>
#include <list>
#include <map>
#include <float.h>

using namespace std;

#ifdef _MSC_VER
#include <string>
#include <string.h>
#include <atlstr.h>

#else
#include "../SigAnal/_Type.h"
#endif



enum EnumNullValueType
{
	//INVALID_INT_VALUE = 0xFFFFFFFF
	INVALID_INT_VALUE = -1
};


#ifdef __VXWORKS__

#else
template <typename T> void DeletePointers(std::list<T*> &i_listContainer)	//#FA_Q_2502_T5
{
	for ( auto iter = i_listContainer.begin() ; iter != i_listContainer.end(); iter++) //#FA_C_PotentialUnboundedLoop_T3
	{
		delete (*iter);
		// *iter = nullptr;
	}
	i_listContainer.clear();
}
//end_static_0918

//////////////////////////////////////////////////////////////////////////
// 벡터 메모리 삭제
//start_static_0918
template <typename T> void DeletePointers(std::vector<T*> &i_vecContainer)	//#FA_Q_2502_T5
{
	for (auto iter = i_vecContainer.begin(); iter != i_vecContainer.end(); iter++ ) //#FA_C_PotentialUnboundedLoop_T3
	{
		delete (*iter);
		// *iter = nullptr;
	}
	i_vecContainer.clear();
}
//end_static_0918

// template <typename T> void DeletePointers2(std::vector<T*> &i_vecContainer)
// {
//     for( auto it=i_vecContainer.begin() ; it != i_vecContainer.end() ; ) { //#FA_C_PotentialUnboundedLoop_T3
// 		it = i_vecContainer.erase( it );
// 	}
// 	i_vecContainer.clear();
// }

//////////////////////////////////////////////////////////////////////////
//start_static_0918
template <typename T1, typename T2> void DeletePointers(std::map<T1, T2*> &i_mapContainer)	//#FA_Q_2502_T5
{
	for (auto iter = i_mapContainer.begin(); iter != i_mapContainer.end(); ) //#FA_C_PotentialUnboundedLoop_T3
	{
		i_mapContainer.erase( iter++ );
	}
	i_mapContainer.clear();
}
//end_static_0918

template <typename T> void DeleteRangePointers( std::list<T> *pListContainer, typename list<T>::iterator itStart, typename list<T>::iterator itEnd )
{
	for (auto iter = itStart; iter != itEnd; iter++) //#FA_C_PotentialUnboundedLoop_T3
	{
		delete (*iter);
	}
	pListContainer->erase( itStart, itEnd );
}
#endif

enum EnumLibraryWndType
{
	E_BASIC_RADAR_LIST_WND = 1,							//레이더 목록(기본형)
	E_BASIC_RADAR_MODE_LIST_WND,						//레이더 모드목록(기본형)
	E_BASIC_RADAR_INFO_SEARCH_WND,						//레이더 정보조회(기본형)
	E_BASIC_RADAR_COMMENTS_WND,							//주석창(레이더정보조회)(기본형)
	E_BASIC_RADAR_MODE_RELATION_WND,					//레이더 모드 연관관계(기본형)
	E_BASIC_RELATED_EMITTER_WND,						//연관방사체(기본형)
	E_BASIC_RADAR_MODE_INFO_SEARCH_WND,					//레이더 모드 정보 조회(기본형)
	E_BASIC_RF_DETAIL_INFO_WND,							//주파수 세부정보(기본형)
	E_BASIC_PRI_DETAIL_INFO_WND,						//펄스반복주기 세부정보(기본형)
	E_BASIC_PD_DETAIL_INFO_WND,							//펄스폭 세부정보(기본형)
	E_BASIC_PA_DIFF_DETAIL_INFO_IN_GROUP_WND,			//그룹내 PA차 세부정보(기본형)
	E_BASIC_INTRAPULSE_CW_MOD_DETAIL_INFO_SEARCH_WND,	//펄스내/CW변조 세부정보(기본형)
	E_BASIC_PLATFORM_LIST_WND,							//플랫폼 목록(기본형)
	E_BASIC_PLATFORM_INFO_SEARCH_WND,					//플랫폼 정보조회(기본형)
	E_BASIC_WEAPON_SYSTEM_LIST_WND,						//무기체계목록(기본형)
	E_BASIC_WEAPON_SYSTEM_INFO_SEARCH_WND,				//무기체계 정보조회(기본형)
	E_BASIC_THREAT_LIST_WND,							//위협목록(기본형)
	E_BASIC_DEVICE_WND,									//장비목록(기본형)
	E_BASIC_THREAT_INFO_SEARCH_WND,						//위협 정보조회(기본형)

	E_PRTC_RADAR_LIST_WND,								//레이더 목록(실무형)
	E_PRTC_RADAR_MODE_LIST_WND,							//레이더 모드목록(실무형)
	E_PRTC_RADAR_INFO_SEARCH_WND,						//레이더 정보조회(실무형)
	E_PRTC_RADAR_COMMENTS_WND,							//주석창(레이더정보조회)(실무형)
	E_PRTC_RADAR_MODE_RELATION_WND,						//레이더 모드 연관관계(실무형)
	E_PRTC_RELATED_EMITTER_WND,							//연관방사체(실무형)
	E_PRTC_RADAR_MODE_INFO_SEARCH_WND,					//레이더 모드 정보 조회(실무형)
	E_PRTC_RF_DETAIL_INFO_WND,							//주파수 세부정보(실무형)
	E_PRTC_PRI_DETAIL_INFO_WND,							//펄스반복주기 세부정보(실무형)
	E_PRTC_PD_DETAIL_INFO_WND,							//펄스폭 세부정보(실무형)
	E_PRTC_PA_DIFF_DETAIL_INFO_IN_GROUP_WND,			//그룹내 PA차 세부정보(실무형)
	E_PRTC_INTRAPULSE_CW_MOD_DETAIL_INFO_SEARCH_WND,	//펄스내/CW변조 세부정보(실무형)
	E_PRTC_PLATFORM_LIST_WND,							//플랫폼 목록(실무형)
	E_PRTC_PLATFORM_INFO_SEARCH_WND,					//플랫폼 정보조회(실무형)
	E_PRTC_WEAPON_SYSTEM_LIST_WND,						//무기체계목록(실무형)
	E_PRTC_WEAPON_SYSTEM_INFO_SEARCH_WND,				//무기체계 정보조회(실무형)
	E_PRTC_THREAT_LIST_WND,								//위협목록(실무형)
	E_PRTC_DEVICE_WND,									//장비목록(실무형)
	E_PRTC_THREAT_INFO_SEARCH_WND,						//위협 정보조회(실무형)

	EnumNumOfLibWnd,
};

enum EnumValueCheck
{
	NOT_ERROR = 0,	// 오류 없음.
	MIN_MAX_ERROR,	// Min/Max 오류 - Min값이 Max값보다 큼.
	VALID_ERROR		// 유효값이 아님.
};

enum ENUM_SequenceSpot {
    enRFSequenceValue=0,
    enPRISequenceValue,
    enPWSequenceValue,
    enScanSequenceValue,

    enRFSpotValue,
    enPRISpotValue,
};

enum EnumParamSetAssocTypeCode
{
	enumSimultaneous = 1,
	enumSequential,
	enumIndependentSimultaneous,
};

namespace PlatformCode
{
	enum EnumPlatformCode
	{
		enumUndefinedPlatformCode = -1,

		enumUnKnown = 0,
		enumLand,
		enumSea,
		enumLand_Sea_And_Air,
		enumCoastal,
		enumAir,

		enumMaxOfPlatformCode

	};
}

static const char _PlatformCodes[PlatformCode::enumAir + 1][25 + 1] =
{
	"UNKNOWN",
	"LAND",
	"SEA",
	"LAND_SEA_AND_AIR",
	"COASTAL",
   "AIR"
};

enum EnumFunctionCodes
{
	enumUndefinedFunctionCode = -1,			//아무것도 표시되지 않음.

	enumAA_Anti_Aircraft_Fire_Control = 0,
	enumAB_Airborne_Search_and_Bomb,
	enumAI_Airborne_Intercept,
	enumAL_Altimeter,
	enumAM_Airborne_Recon_Mapping,
	enumAT_Air_Traffic_Control,
	enumAV_Avian_Control,
	enumBN_Beacon_Transponder,
	enumBS_Battlefield_Surveillance,
	enumCA_Controlled_Approach_G_S,
	enumCI_Controlled_Intercept_A_G_S,
	enumCS_Coastal_Surveillance,
	enumDC_Decoy_Mimic,
	enumDT_Data_Transmission,
	enumES_Earth_Surveillance,
	enumEW_Early_Warning,
	enumFC_Fire_Control,
	enumGB_Gun_Laying_Beacon,
	enumGM_Ground_Mapping,
	enumGT_Ground_Traffic_Control,
	enumHF_Height_Finder,
	enumHS_Harbor_Surveillance,
	enumIF_IFF_Interrogator,
	enumIL_Instrument_Landing_System,
	enumIS_Ionospheric_Sounding,
	enumIT_IFF_Transponder,
	enumJB_Barrage_Jamming,
	enumJC_Click_Jamming,
	enumJD_Deceptive_Jamming,
	enumJF_Frequency_Swept_Jamming,
	enumJG_Jamming__General,
	enumJN_Noise_Jamming,
	enumJP_Pulsed_Jamming,
	enumJR_Repeater_Jamming,
	enumJS_Spot_Noise_Jamming,
	enumJT_Transponder_Jamming,
	enumMA_Missile_Acquisition,
	enumMC_Missile_Control,
	enumMD_Missile_Downlink,
	enumME_Meteorological,
	enumMF_Multi_Function,
	enumMG_Missile_Guidance,
	enumMH_Missile_Homing,
	enumMT_Missile_Tracking,
	enumNA_Navigation_General,
	enumND_Navigation_DME,
	enumNT_Navigation_Terrain_Following,
	enumNW_Navigation_Weather_Avoidance,
	enumPF_Proximity_Fuse,
	enumRI_Instrumentation,
	enumRO_Range_Only,
	enumRS_Radiosonde,
	enumSB_Sonobuoy,
	enumSP_Space,
	enumSS_Surface_Search,
	enumST_Shell_Tracking,
	enumTA_Target_Acquisition,
	enumTI_Target_Illumination,
	enumTT_Target_Tracking,
	enumTV_Television,
	enumUN_Unknown,
	enumVR_Video_Remoting,
	enumXP_Experimental_or_Trainer,

	enumMaxOfFunctionCodes,
};

/*
// static char _FunctionCodes[enumXP_Experimental_or_Trainer+1][4] =
// {
// 	"AA", "AB", "AI", "AL", "AM", "AT", "AV", \
// 	"BN", "BS", \
// 	"CA", "CI", "CS", \
// 	"DC", "DT", \
// 	"ES", "EW", \
// 	"FC", \
// 	"GB", "GM", "GT", \
// 	"HF", "HS", \
// 	"IF", "IL", "IS", "IT", \
// 	"JB", "JC", "JD", "JF", "JG", "JN", "JP", "JR", "JS", "JT", \
// 	"MA", "MC", "MD", "ME", "MF", "MG", "MH", "MT",
// 	"NA", "ND", "NT", "NW", \
// 	"PF", \
// 	"RI", "RO", "RS", \
// 	"SB", "SP", "SS", "ST", \
// 	"TA", "TI", "TT", "TV", \
// 	"UN", \
// 	"VR", \
// 	"XP"
// };
*/

namespace PolizationCode
{
	/**
	 * @enum      EnumPolizationCode, 일치율 점수에 가산점을 준다.
	 * @brief     레이더 모드 별로 극성 정보를 정의한다.
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 */
	enum EnumPolizationCode
	{
		enumUndefinedPolization = -1,														//아무것도 표시되지 않음

		enumC_Diverse_Agile_or_adaptive_Capable_of_pulse_to_pulse_agility = 0,
		enumD_Diverse_Option_of_operating_with_any_of_several_polarizations,
		enumG_Linear_with_no_reference_to_plane_unknown_whether_H_or_V,						// H, V 보다 점수를 덜 준다.
		enumH_Linear_horizontal_as_compared_with_earth_horizon_or_platform,					// H
		enumJ_Circular_with_right_hand_sense,												// RC
		enumK_Circular_with_left_hand_sense,												// LC
		enumL_Circular_with_undetermined_sense,												// 식별은 되고 RC, LC보다 점수 덜 준다.
		enumM_Elliptical,
		enumR_Rotating,
		enumS_Linear_slant_undetermined_angle,												// RS, LS에 점수 덜 준다.
		enumT_Linear_slant_right_of_vertical_as_compared_with_earth_horizon_or_platform,	// RS
		enumU_Linear_slant_left_of_vertical_as_compared_with_earth_horizon_or_platform,		// LS
		enumV_Linear_vertical_as_compared_with_earth_horizon_or_platform,					// V
		enumW_Unpolarized_modulated_or_spinning_linear_polarization,
		enumY_Polarization_fixed_but_type_unknown,
		enumZ_Undetermined
	};
}
/*
static char _PolizationCode[PolizationCode::enumZ_Undetermined + 1][100 + 1] =
{
	"C - Diverse (Agile or adaptive). Capable of pulse-to-pulse agility.",
	"D - Diverse.Option of operating with any of several polarizations.",
	"G - Linear with no reference to plane (unknown whether H or V).",
	"H - Linear - horizontal as compared with earth horizon or platform.",
	"J - Circular, with right hand sense.",
	"K - Circular, with left hand sense.",
	"L - Circular, undetermined sense.",
	"M - Elliptical.",
	"R - Rotating.",
	"S - Linear - slant, undetermined angle.",
	"T - Linear - slant, right of vertical as compared with earth horizon or platform",
	"U - Linear - slant, leeft of vertical as compared with earth horizon or platform",
	"V - Linear - vertical as compared with earth horizon or platform",
	"W - Unpolarized - modulated or spinning linear polarization",
	"Y - Polarization fixed but type unknown",
	"Z - Undetermined"
};	*/

enum EnumRotationDirCode
{
	enumUndefinedRotationDir = -1,	//아무것도 표시되지 않음

	enumCounterClockwise = 0,
	enumClockwise
};
/*
static char _RotationDirCode[enumClockwise + 1][25 + 1] =
{
	"Counter Clockwise",
	"Clockwise"
};	*/

namespace ContinuityCode
{
	enum EnumContinuityCode
	{
		enumUndefinedContinuityCode = -1, //아무것도 표시되지 않음

		enumUnknown = 0,
		enumDiscrete,
		enumCountinuous
	};
}
/*
static char _ContinuityCodes[ContinuityCode::enumCountinuous + 1][25 + 1] =
{
	"UNKNOWN",
	"DISCRETE",
	"COUNTINUOUS"
};	*/

namespace PatternCode
{
	enum EnumPatternCode
	{
		enumUndefinedPatternCode = -1, //아무것도 표시되지 않음

		enumUnknown = 0,
		enumPatterned,
		enumNonPatterned,
		enumAdaptive,
		enumUnmodulated = 5
	};
}
/*
static char _PatternCodes[PatternCode::enumUnmodulated + 1][25 + 1] =
{
	"UNKNOWN",
	"PATTERNED",
	"NON_PATTERNED",
	"ADAPTIVE",
	"",
	"UNMODULATED"
};	*/

namespace CohencyCode
{
	enum EnumCoherencyCode
	{
		enumUndefinedCoherencyCode = -1,

		enumCoherent = 0,
		enumNonCoherent,
		enumUnknown = 3
	};
}
/*
static char _CoherencyCodes[CohencyCode::enumUnknown + 1][25 + 1] =
{
	"COHERENT",
	"NON_COHERENT",
	"",
	"UNKNOWN"
};	*/

enum EnumValidationCode
{
	enumUndefinedValidationCode = -1,

	enumUnvalidated = 0,
	enumValidated,			//기본값
	enumPostulated
};
/*
static char _ValidationCodes[enumPostulated + 1][25 + 1] =
{
	"UNVALIDATED",
	"VALIDATED",
	"POSTULATED"
};	*/

enum EnumRF_LagacyTypeCode
{
	enumUndefinedRF_LagacyType = -1,				//아무것도 표시되지 않음

	enumRF_Agile = 0,							// 어자일
	enumRF_AgilePulseToPulse,					// 어자일 : 펄스대 ?
	enumRF_AgileGroupToGroup,					// 어자일 : 호핑
	enumRF_AgileSubPulse,						// 어자일 : 이건 뭐지 ?
	enumMultipleRF,
	enumMultipleRF_Simultaneous,
	enumMultipleRF_Sequential,
	enumLimitedRFChangeCapable,
	enumRF_Sweeping,							// 패턴 형태 : ?
	enumRF_SweepingLinear,						// 패턴 형태 : ?
	enumRF_SweepingSinusoidal,					// 패턴 형태 : 사인파
	enumRF_SweepingTriangular,					// 패턴 형태 : 삼각파
	enumRF_Sliding,								// 패턴 패턴 : ?
	enumOnOffKeyed,
	enumConstantSingleRF,						// 고정
	enumLinearRF_Stepping,						// 호핑인가 ?
};
/*
static char _RF_LagacyTypeCodes[enumLinearRF_Stepping + 1][100 + 1] =
{
	"RF_AGILE",
	"RF_AGILE_PULSE_TO_PULSE",
	"RF_AGILE_GROUP_TO_GROUP",
	"RF_AGILE_SUB_PULSE",
	"MULTIPLE_RF",
	"MULTIPLE_RF_SIMULTANEOUS",
	"MULTIPLE_RF_SEQUENTIAL",
	"LIMITED_RF_CHANGE_CAPABLE",
	"RF_SWEEPING",
	"RF_SWEEPING_LINEAR",
	"RF_SWEEPING_SINUSOIDAL",
	"RF_SWEEPING_TRIANGULAR",
	"RF_SLIDING",
	"ON_OFF_KEYED",
	"CONSTANT_SINGLE_RF",
	"LINEAR_RF_STEPPING"
};	*/

/**
 * @enum      EnumPRI_LegacyTypeCode
 * @brief     PRI 형태 정의
 * @author    조철희 (churlhee.jo@lignex1.com)
 */
enum EnumPRI_LegacyTypeCode
{
	enumUndefinedPRI_LegacyType = -1,

	enumPulseConstant = 20,				// Stable
	enumStagger,						// Stagger
	enumJitter,							// Jitter
	enumDwellAndSwitch,					// D&S 형태
	enumPulsePositionModulation,
	enumPulseFrequencyModulation,
	enumPRI_Sliding,					// 패턴
	enumPRI_PhaseModulationOrShifting
};

// static char _PRI_LagacyTypeCodes[(enumPRI_PhaseModulationOrShifting - enumPulseConstant) + 1][100 + 1] =
// {
// 	"PULSE_CONSTANT",
// 	"STAGGER",
// 	"JITTER",
// 	"DWELL_AND_SWITCH",
// 	"PULSE_POSITION_MODULATION",
// 	"PULSE_FREQUENCY_MODULATION",
// 	"PRI_SLIDING",
// 	"PRI_PHASE_MODULATION_OR_SHIFTING"
// };

namespace CEDSignalType
{
	enum EnumSignalType	//#FA_Q_2502_T2
	{

#ifdef _XBAND_
		enumSignalUndefined = -1,
		enumCW =0,
		enumPulsed,	//기본값
		enumEA

#elif defined(_POCKETSONATA_)
		enumSignalUndefined = 0,
        enumPulsed,
        enumCW,
        enumEA

#else
		enumSignalUndefined = -1,
		enumPulsed = 0,	//기본값
		enumCW,
		enumEA
#endif
	};
}

#ifdef _XBAND_
static char _SignalType[CEDSignalType::enumEA + 1][11] =
{
	"CW",
	"Pulsed",
	"EA"
};
#else
// static char _SignalType[CEDSignalType::enumEA + 1][11] =
// {
// 	"Pulsed",
// 	"CW",
// 	"EA"
// };
#endif

namespace RadarModeFreqType
{
	enum EnumRadarModeFreqType
	{
        enumFIXED = 1,
        enumAGILE,
        enumPATTERN,
        enumHOPPING,

        enumFreqUnknown
	};
}

// static const char* _strFrqType[]=
// {
// 	"고정",
// 	"호핑",
// 	"어자일",
// 	"패턴",
//
// 	"모름"
// };

namespace RadarModePRIType
{
#if defined(_XBAND_) || defined(_POCKETSONATA_)
	enum EnumRadarModePRIType
	{
		enumStable = 0,
		enumJITTER,
		enumDwellSWITCH,
		enumSTAGGER,
		enumPATTERN,

		enumPRIUnknown
	};
#else
	enum EnumRadarModePRIType
	{
		enumStable = 1,
		enumJITTER,
		enumDwellSWITCH,
		enumSTAGGER,
		enumPATTERN,

		enumPRIUnknown
	};
#endif
}

// static const char* _strPRIType[]=
// {
// 	"고정",
// 	"지터",
// 	"드웰",
// 	"스태거",
// 	"패턴",
//
// 	"모름"
// };


enum EnumRadarStatus
{
	enumUndefinedRadarStatus = -1,

	enumActive = 0,	//기본값
	enumRenotated,
	enumCanceled,
	enumIncorporated,
	enumRetired,
	enumUndetected,

	enumMaxOfRadarStatus
};

// static char _RadarStatus[enumUndetected + 1][21] =
// {
// 	"ACTIVE",
// 	"RENOTATED",
// 	"CANCELED",
// 	"INCORPORATED",
// 	"RETIRED",
// 	"UNDETECTED"
// };

// 섹터형, 탐지형, 추적형 추가할 때 CheckScanType()와 CalcMatchRatio()에 해당 항목을 추가 코딩해야 함.
namespace ScanType
{
	//start_static_0919
	enum EnumScanType	//#FA_Q_2502_T2
	{
		enumUndefinedScanType = INT_MAX,                        //아무것도 표시되지 않음

		enumA_Circular = 0,										// 탐지형
		enumB_Horizontal_Sector_Bi_directional,					// 섹터형(탐지형)
		enumC_Vertical_Sector_Bi_directional,					// 섹터형(탐지형)
		enumD_Non_Scanning,										// 추적형
		enumE_Irregular,										// Unknown
		enumF_Conical,											// 추적형
		enumG_Lobe_Switching,									// 추적형
		enumH_Orthogonal_or_Interleaved_Sectors,				// 탐색형
		enumJ_Raster,											// 섹터형(탐지형)
		enumK_Spiral,											// 섹터형(탐지형)
		enumL_Helical,											// 섹터형(탐지형)
		enumO_Sector_Uni_or_Bi_Directional,						// 섹터형(탐지형)
		enumP_Agile_Beam,										// 추적형
		enumR_Other_Combination_Patterns,						// Unknown
		enumS_Vertical_Sector_Uni_Directional,					// 섹터형(탐지형)
		enumT_Horizontal_Sector,								// 섹터형(탐지형)
		enumU_Uni_Directional_Sector_Plane_Undertermined,		// 섹터형(탐지형)
		enumV_Bi_Directional_Sector_Plane_Undetermined,			// 섹터형(탐지형)
		enumZ_Undetermined										// Unknown
	};
	//end_static_0919
}
/*
static char _ScanTypes[ScanType::enumZ_Undetermined + 1][100 + 1] =
{
	"A - Circular",
	"B - Horizontal Sector (Bi-directional)",
	"C - Vertical Sector (Bi-directional)",
	"D - Non-Scanning",
	"E - Irregular",
	"F - Conical",
	"G - Lobe Switching",
	"H - Orthogonal or Interleaved Sectors",
	"J - Raster",
	"K - Spiral",
	"L - Helical",
	"O - Sector Uni or Bi-Directional",
	"P - Agile Beam",
	"R - Other Combination/Patterns",
	"S - Vertical Sector (Uni-Directional)",
	"T - Horizontal Sector (Uni-Directional)",
	"U - Uni-Directional Sector (Plane Undertermined)",
	"V - Bi-Directional Sector (Plane Undetermined)",
	"Z - Undetermined"
};	*/

namespace MOP_CW_ModulationType
{
	enum EnumMOP_CW_ModulationType
	{
		enumUndefinedMOP_CW_ModulationType = -1,

		enumUnknown = 0,		// UNKNOWN
		enumFrequency,			// FSK
		enumPhase,				// PSK
		enumAmplitude,			// PSK
		enumUnModulated			// NM
	};
}
/*
static char _MOP_CW_ModulationType[MOP_CW_ModulationType::enumUnModulated + 1][25 + 1] =
{
	"UNKNOWN",
	"FREQUENCY",
	"PHASE",
	"AMPLITUDE",
	"UNMODULATED"
};	*/

enum EnumMOP_CW_LegacyType
{
	enumUndefinedMOP_CW_LegacyType = -1,	//아무것도 표시되지 않음

	enumFMOP = 40,
	enumFMOP_Linear,
	enumFMOP_NonLinear,
	enumFMOP_Stepped,
	enumPMOP,
	enumPMOP_BPSK,
	enumPMOP_QPSK,
	enumPMOP_MSK,
	enumPMOP_PolyTime = 49,
	enumAMOP = 50,
	enumPCM,
	enumFM_Triangular = 53,
	enumFM_Sinusoidal = 55,
	enumAM_Tones = 62,
	enumON_OFF_Keying,
	enumOOK_SRW
};
/*
static EnumMOP_CW_LegacyType _MOP_CW_LegacyTypeArray[16] =
{
	enumFMOP,
	enumFMOP_Linear,
	enumFMOP_NonLinear,
	enumFMOP_Stepped,
	enumPMOP,
	enumPMOP_BPSK,
	enumPMOP_QPSK,
	enumPMOP_MSK,
	enumPMOP_PolyTime,
	enumAMOP,
	enumPCM,
	enumFM_Triangular,
	enumFM_Sinusoidal,
	enumAM_Tones,
	enumON_OFF_Keying,
	enumOOK_SRW
};	*/
/*
static char _MOP_CW_LegacyType[16][100 + 1] =
{
	"FMOP",
	"FMOP_LINEAR",
	"FMOP_NONLINEAR",
	"FMOP_STEPPED",
	"PMOP",
	"PMOP_BPSK",
	"PMOP_QPSK",
	"PMOP_MSK",
	"PMOP_POLY_TIME",
	"AMOP",
	"PCM",
	"FM_TRIANGULAR",
	"FM_SINUSOIDAL",
	"AM_TONES",
	"ON_OFF_KEYING",
	"OOK_SRW"
};	*/

enum EnumThreatStatusCode
{
	enumUndefinedThreatStatusCode = -1,

	enumC = 0,	//기본값
	enumP,
	enumN,
	enumX,
	enumD,
	enumU,
	enumI,
	enumA
};
/*
static char _ThreatStatucCode[enumA + 1][2] =
{
	"C",
	"P",
	"N",
	"X",
	"D",
	"U",
	"I",
	"A"
};	*/

namespace CountryCode
{
	enum EnumCountryCode
	{
		enumUndefinedCountry = -1,	//아무것도 표시되지 않음

		enumAA_Aruba = 0,
		enumAC_Antigua_and_Barbuda,
		enumAE_United_Arab_Emirates,
		enumAF_Afghanistan,
		enumAG_Algeria,
		enumAJ_Azerbaijan,
		enumAL_Albania,
		enumAM_Armenia,
		enumAN_Andorra,
		enumAO_Angola,
		enumAQ_American_Samoa,
		enumAR_Argentina,
		enumAS_Australia,
		enumAT_Ashmore_and_Cartier_Islands,
		enumAU_Austria,
		enumAV_Anguilla,
		enumAX_Akrotiri,
		enumAY_Antarctica,
		enumBA_Bahrain,
		enumBB_Barbados,
		enumBC_Botswana,
		enumBD_Bermuda,
		enumBE_Belgium,
		enumBF_Bahamas,
		enumBG_Bangladesh,
		enumBH_Belize,
		enumBK_Bosnia_and_Herzegovina,
		enumBL_Bolivia,
		enumBM_Burma_Myanmar,
		enumBN_Benin,
		enumBO_Belarus,
		enumBP_Solomon_Islands,
		enumBQ_Navassa_Island,
		enumBR_Brazil,
		enumBS_Bassas_da_India,
		enumBT_Bhutan,
		enumBU_Bulgaria,
		enumBV_Bouvet_Island,
		enumBX_Brunei,
		enumBY_Burundi,
		enumCA_Canada,
		enumCB_Cambodia,
		enumCD_Chad,
		enumCE_Sri_Lanka,
		enumCF_Republic_of_the_Congo,
		enumCG_Democratic_Republic_of_the_Congo,
		enumCH_People_s_Republic_of_China,
		enumCI_Chile,
		enumCJ_Cayman_Islands,
		enumCK_Cocos_Keeling_Islands,
		enumCM_Cameroon,
		enumCN_Comoros,
		enumCO_Colombia,
		enumCQ_Northern_Mariana_Islands,
		enumCR_Coral_Sea_Islands,
		enumCS_Costa_Rica_CRI,
		enumCT_Central_African_Republic,
		enumCU_Cuba_CUB,
		enumCV_Cape_Verde,
		enumCW_Cook_Islands,
		enumCY_Cyprus,
		enumDA_Denmark,
		enumDJ_Djibouti,
		enumDO_Dominica,
		enumDR_Dominican_Republic,
		enumDX_Dhekelia,
		enumEC_Ecuador,
		enumEG_Egypt,
		enumEI_Republic_of_Ireland,
		enumEK_Equatorial_Guinea,
		enumEN_Estonia,
		enumER_Eritrea,
		enumES_El_Salvador,
		enumET_Ethiopia,
		enumEU_Europa_Island,
		enumEZ_Czech_Republic,
		enumFG_French_Guiana,
		enumFI_Finland,
		enumFJ_Fiji,
		enumFK_Falkland_Islands_Islas_Malvinas,
		enumFM_Federated_States_of_Micronesia,
		enumFO_Faroe_Islands,
		enumFP_French_Polynesia,
		enumFQ_Baker_Island,
		enumFR_France,
		enumFS_French_Southern_Territories,
		enumGA_The_Gambia,
		enumGB_Gabon,
		enumGG_Georgia,
		enumGH_Ghana,
		enumGI_Gibraltar,
		enumGJ_Grenada,
		enumGK_Guernsey,
		enumGL_Greenland,
		enumGM_Germany,
		enumGO_Glorioso_Islands,
		enumGP_Guadeloupe,
		enumGQ_Guam,
		enumGR_Greece,
		enumGT_Guatemala,
		enumGV_Guinea,
		enumGY_Guyana,
		enumGZ_Gaza_Strip,
		enumHA_Haiti,
		enumHK_Hong_Kong,
		enumHM_Heard_Island_and_McDonald_Islands,
		enumHO_Honduras,
		enumHR_Croatia,
		enumHU_Hungary,
		enumIC_Iceland,
		enumID_Indonesia,
		enumIM_Isle_of_Man,
		enumIN_India,
		enumIO_British_Indian_Ocean_Territory,
		enumIP_Clipperton_Island,
		enumIR_Iran,
		enumIS_Israel,
		enumIT_Italy,
		enumIV_Cote_d_lvoire,
		enumIZ_Iraq,
		enumJA_Japan,
		enumJE_Jersey,
		enumJM_Jamaica,
		enumJN_Jan_Mayen,
		enumJO_Jordan,
		enumJQ_Johnston_Atoll,
		enumJU_Juan_de_Nova_Island,
		enumKE_Kenya,
		enumKG_Kyrgyzstan,
		enumKN_North_Korea,
		enumKQ_Kingman_Reef,
		enumKR_Kiribati,
		enumKS_South_Korea,
		enumKT_Christmas_Island,
		enumKU_Kuwait,
		enumKZ_Kazakhstan,
		enumLA_Laos,
		enumLE_Lebanon,
		enumLG_Latvia,
		enumLH_Lithuania,
		enumLI_Liberia,
		enumLO_Slovakia,
		enumLS_Liechtenstein,
		enumLT_Lesotho,
		enumLU_Luxembourg,
		enumLY_Libya,
		enumMA_Madagascar,
		enumMB_Martinique,
		enumMC_Macau,
		enumMD_Moldova,
		enumMF_Mayotte,
		enumMG_Mongolia,
		enumMH_Montserrat,
		enumMI_Malawi,
		enumMJ_Montenegro,
		enumMK_Republic_of_Macedonia,
		enumML_Mali,
		enumMN_Monaco,
		enumMO_Morocco,
		enumMP_Mauritius,
		enumMQ_Midway_Islands,
		enumMR_Mauritania,
		enumMT_Malta,
		enumMU_Oman,
		enumMV_Maldives,
		enumMX_Mexico,
		enumMY_Malaysia,
		enumMZ_Mozambique,
		enumNC_New_Caledonia,
		enumNE_Niue,
		enumNF_Norfolk_Island,
		enumNG_Niger,
		enumNH_Vanuatu,
		enumNI_Nigeria,
		enumNL_Netherlands,
		enumNO_Norway,
		enumNP_Nepal,
		enumNR_Nauru,
		enumNS_Suriname,
		enumNT_Netherlands_Antilles,
		enumNU_Nicaragua,
		enumNZ_New_Zealand,
		enumOD_South_Sudan,
		enumPA_Paraguay,
		enumPC_Pitcairn_Islands,
		enumPE_Peru,
		enumPF_Paracel_Islands,
		enumPG_Spratly_Islands,
		enumPK_Pakistan,
		enumPL_Poland,
		enumPM_Panama,
		enumPO_Portugal,
		enumPP_Papua_New_Guinea,
		enumPS_Palau,
		enumPU_Guinea_Bissau,
		enumQA_Qatar,
		enumRB_Serbia,
		enumRE_Reunion,
		enumRM_Marshall_Islands,
		enumRO_Romania,
		enumRP_Philippines,
		enumRQ_Puerto_Rico,
		enumRS_Russia,
		enumRW_Rwanda,
		enumSA_Saudi_Arabia,
		enumSB_Saint_Pierre_and_Miquelon,
		enumSC_Saint_Kitts_and_Nevis,
		enumSE_Seychelles,
		enumSF_South_Africa,
		enumSG_Senegal,
		enumSH_Saint_Helena,
		enumSI_Slovenia,
		enumSL_Sierra_Leone,
		enumSM_San_Marino,
		enumSN_Singapore,
		enumSO_Somalia,
		enumSP_Spain,
		enumST_Saint_Lucia,
		enumSU_Sudan,
		enumSV_Svalbard,
		enumSW_Sweden,
		enumSX_South_Georgia_and_the_South_Sandwich_Islands,
		enumSY_Syria,
		enumSZ_Switzerland,
		enumTD_Trinidad_and_Tobago,
		enumTE_Tromelin_Island,
		enumTH_Thailand,
		enumTI_Tajikistan,
		enumTK_Turks_and_Caicos_Islands,
		enumTL_Tokelau,
		enumTN_Tonga,
		enumTO_Togo,
		enumTP_Sao_Tome_and_Principe,
		enumTS_Tunisia,
		enumTT_Timor_Leste_EastTimor,
		enumTU_Turkey,
		enumTV_Tuvalu,
		enumTW_Republic_of_China_Taiwan,
		enumTX_Turkmenistan,
		enumTZ_Tanzania,
		enumUG_Republic_of_Uganda,
		enumUK_United_Kingdom,
		enumUP_Ukraine,
		enumUS_United_States,
		enumUV_Burkina_Faso,
		enumUY_Uruguay,
		enumUZ_Uzbekistan,
		enumVC_Saint_Vincent_and_the_Grenadines,
		enumVE_Venezuela,
		enumVI_British_Virgin_Islands,
		enumVM_Vietnam,
		enumVQ_US_Virgin_Islands,
		enumVT_Vatican_City,
		enumWA_Namibia,
		enumWE_West_Bank,
		enumWF_Wallis_and_Futuna,
		enumWI_Western_Sahara,
		enumWQ_Wake_Island,
		enumWS_Samoa,
		enumWZ_Swaziland,
		enumYM_Yemen,
		enumZA_Zambia,
		enumZI_Zimbabwe,

		enumMaxOfCountryCode,
	};
}

/*
//static char _CountryCodes[CountryCode::enumZI_Zimbabwe + 1][2 + 1] =
//{
//	"AA", "AC", "AE", "AF", "AG", "AJ", "AL", "AM", "AN", "AO", "AQ", "AR", "AS", "AT", "AU", "AV", "AX", "AY", \
//	"BA", "BB", "BC", "BD", "BE", "BF", "BG", "BH", "BK", "BL", "BM", "BN", "BO", "BP", "BQ", "BR", "BS", "BT", "BU", "BV", "BX", "BY", \
//	"CA", "CB", "CD", "CE", "CF", "CG", "CH", "CI", "CJ", "CK", "CM", "CN", "CO", "CQ", "CR", "CS", "CT", "CU", "CV", "CW", "CY", \
//	"DA", "DJ", "DO", "DR", "DX", \
//	"EC", "EG", "EI", "EK", "EN", "ER", "ES", "ET", "EU", "EZ", \
//	"FG", "FI", "FJ", "FK", "FM", "FO", "FP", "FQ", "FR", "FS", \
//	"GA", "GB", "GG", "GH", "GI", "GJ", "GK", "GL", "GM", "GO", "GP", "GQ", "GR", "GT", "GV", "GY", "GZ", \
//	"HA", "HK", "HM", "HO", "HR", "HU", \
//	"IC", "ID", "IM", "IN", "IO", "IP", "IR", "IS", "IT", "IV", "IZ", \
//	"JA", "JE", "JM", "JN", "JO", "JQ", "JU", \
//	"KE", "KG", "KN", "KQ", "KR", "KS", "KT", "KU", "KZ", "LA", \
//	"LE", "LG", "LH", "LI", "LO", "LS", "LT", "LU", "LY", \
//	"MA", "MB", "MC", "MD", "MF", "MG", "MH", "MI", "MJ", "MK", "ML", "MN", "MO", "MP", "MQ", "MR", "MT", "MU", "MV", "MX", "MY", "MZ", \
//	"NC", "NE", "NF", "NG", "NH", "NI", "NL", "NO", "NP", "NR", "NS", "NT", "NU", "NZ", \
//	"OD", \
//	"PA", "PC", "PE", "PF", "PG", "PK", "PL", "PM", "PO", "PP", "PS", "PU", \
//	"QA", \
//	"RB", "RE", "RM", "RO", "RP", "RQ", "RS", "RW", \
//	"SA", "SB", "SC", "SE", "SF", "SG", "SH", "SI", "SL", "SM", "SN", "SO", "SP", "ST", "SU", "SV", "SW", "SX", "SY", "SZ", \
//	"TD", "TE", "TH", "TI", "TK", "TL", "TN", "TO", "TP", "TS", "TT", "TU", "TV", "TW", "TX", "TZ", \
//	"UG", "UK", "UP", "US", "UV", "UY", "UZ", \
//	"VC", "VE", "VI", "VM", "VQ", "VT", \
//	"WA", "WE", "WF", "WI", "WQ", "WS", "WZ", \
//	"YM", \
//	"ZA", "ZI"
//};
  */

namespace FriendOrFOE
{
	enum EnumFriendOrFOE
	{
		enumUndefinedFriendOrFOE = -1,

		enumUnknown = 0,
		enumFriend,
		enumFOE,

		enumMaxOfFriendOrFOE,
	};
}
/*
static char _FriendOrFOE[FriendOrFOE::enumFOE + 1][10 + 1] =
{
	"UNKNOWN",
	"FRIEND",
	"FOE"
};	*/

struct SRadarComments
{
	int nRadarCommentIndex;	//레이더에 대한 주석의 인덱스
    CString strTitle;		//주석제목 (30)
    CString strComments;	//실제 주석
	bool bUpdate;

	SRadarComments()
	{
		nRadarCommentIndex = 0;
		strTitle = "";
		strComments = "";
		bUpdate = false;
	}
};


struct SParamSetAssociations
{
	int nAssocIndex;						//하나의 모드 연관관계마다 붙는 유니크 인덱스
    CString strSetCode;						//레이더 안의 모드 연관관계 하나에 붙이는 코드값 (알파벳 대문자 1문자 혹은 2문자)
	EnumParamSetAssocTypeCode eAssocType;	//연관타입코드 (Simultaneous, Sequential, Independent-simultaneous) (PARAM_SET_ASSOC_TYPE_CODE 참조)
    CString strAssocType;					//연관타입명(Simultaneous, Sequential, Independent-simultaneous)

	SParamSetAssociations()
	{
		nAssocIndex = 0;
		strSetCode = "";
		eAssocType = enumSimultaneous;
		strAssocType = "";
	}
};

// 레이더 와 레이더 모드의 연관관계 코드값을 갖는 구조체
struct SParamSetAssocTypeCode
{
	int nCodeVal;								// CODE - NUMBER
    CString strAbbreviation;		// ABBREVIATION - VARCHAR2(30)
    CString strName;						// NAME - VARCHAR2(100)

	SParamSetAssocTypeCode()
	{
		nCodeVal=0;
		strAbbreviation="";
		strName="";
	}
};

struct SAssocELNOT
{
	int nRadarIndex;		//레이더 인덱스
	int nAssocRadarIndex;	//연관레이더 인덱스
	SAssocELNOT()
	{
		nRadarIndex=0;
		nAssocRadarIndex=0;
	}
};

struct SRadarUserCountry
{
    CString strUserCountry;						//레이더를 사용하는 나라(2)	//*추후 삭제 예정
	CountryCode::EnumCountryCode eUserCountry;	//국가=>enum으로 표현
	int nSeclab;

	SRadarUserCountry()
	{
		strUserCountry="";
		eUserCountry=CountryCode::enumUndefinedCountry;
		nSeclab=0;
	}
};

struct SWeaponSystem	//무기체계
{
    CString strWeaponSys;						//무기체계 이름(40)
	int nWeaponIndex;							//인덱스

    vector<CString> vecSelectedELNOT_ForGUI;	//관련된 전정부호명
	SWeaponSystem() : nWeaponIndex(0)
	{
        strWeaponSys = "";
        vecSelectedELNOT_ForGUI = vector<CString>();
	}
};

struct SPlatform	//플랫폼
{
	int nPlatformIndex;							//인덱스
    CString strPlatform;						//플랫폼명(40)

    vector<CString> vecSelectedELNOT_ForGUI;	//관련된 전정부호명 목록
	SPlatform() : nPlatformIndex(0)
	{
        strPlatform = "";
        vecSelectedELNOT_ForGUI = vector<CString>();
	}
};


struct SThreatAndDeviceBase
{
	unsigned int uiDeviceIndex;						//유일한 인덱스
	string strThreatStatus;
	EnumThreatStatusCode eStatus_ForGUI;	//THREAT_STATUS_CODE 참조 (C, P, N, X, D, U, I 중 하나)

	string strDeviceStatus;
	EnumThreatStatusCode eDevStatus_ForGUI;	//DEVICE_STATUS_CODE 참조 (C, P, N, X, D, U, I 중 하나)

	SThreatAndDeviceBase()
	{
		uiDeviceIndex = 0;
		strThreatStatus = "";
		eStatus_ForGUI = enumC;
		strDeviceStatus = "";
		eDevStatus_ForGUI = enumC;
	}
};

struct SDeviceInfoFromRadar
{
	float fMinFreq_ForGUI;						//최소주파수
	float fMaxFreq_ForGUI;						//최대주파수
	float fMinPRI_ForGUI;						//최소PRI
	float fMaxPRI_ForGUI;						//최대PRI
	bool bIsBasicCEDExist;						//CED존재여부
	EnumFunctionCodes eFunctionCode_For_GUI;
	CEDSignalType::EnumSignalType eSignalType;		//신호형태 (Pulsed, CW, EA) enum형태

	SDeviceInfoFromRadar()
	{
		fMinFreq_ForGUI=0.0f;						//최소주파수
		fMaxFreq_ForGUI=0.0f;						//최대주파수
		fMinPRI_ForGUI=0.0f;						//최소PRI
		fMaxPRI_ForGUI=0.0f;						//최대PRI
		bIsBasicCEDExist=false;						//CED존재여부
		eFunctionCode_For_GUI=enumUndefinedFunctionCode;
		eSignalType=CEDSignalType::enumSignalUndefined;		//신호형태 (Pulsed, CW, EA) enum형태
	}

};

#define DLONGITUDE2LONG(A)				(double) ( A / 1000000.0 )
#define DLATITUDE2LAT(A)					(double) ( A / 1000000.0 )
#define ILONGITUDE2LONG(A)				(int) ( ( (float) (A) * 1000000.0 ) + 0.5 )
#define IILATITUDE2LAT(A)					(int) ( ( (float) (A) * 1000000.0 ) + 0.5 )
struct SDeviceBase
{
	unsigned int uiDeviceIndex;					//	Threat안에서 장비의 인덱스
	//int nRadarIndex;					//	레이더 인덱스
	float fIdentificationRange;		//	식별반경(NM: 노티컬마일; 기본값 5

	float fLatitude;					//	위도
	float fLongitude;					//	경도
	float fElevation;						//	고도 (0~99999 ?)

    char szELNOT[_MAX_ELNOT_STRING_SIZE_];		//	NOTATION (5)
    char szDeviceName[_MAX_STRING_SIZE_];		//	장비명 (주로 NICKNAME) (50)


	SDeviceBase()
	{
		uiDeviceIndex=0;
		//nRadarIndex=0;

		fIdentificationRange = ( float ) 0.;
        fLatitude = (float) 0.;
        fLongitude = (float) 0.;
		fElevation = (float) 0.;

        szELNOT[0] = 0;
        szDeviceName[0] = 0;

	}

// 	double GetLongitude()
// 	{
// 		int iLongitude;
// 		iLongitude = GetILongitude();
//
// 		double dbLongitude = DLONGITUDE2LONG( iLongitude );
// 		return dbLongitude;
// 	}

// 	int GetILongitude()
// 	{
// 		char ch=0;
//
// 		int iVal=0;
//
// 		//memcpy( szBuffer, (LPCSTR) strLongitude, strLongitude.GetLength()+1 );
//         //sscanf_s( szLongitude, "%d%1c" , & iVal, & ch );
// #ifdef _MSC_VER
//         sscanf_s( szLongitude, "%d%1c" , & iVal, & ch, sizeof(char) );
// #else
//         sscanf( szLongitude, "%d%1c" , & iVal, & ch );
// #endif
//
// 		if( ch != 'E' && ch != 'e' && ch != 'W' && ch == 'w' ) {
// 			iVal = 0;
// 		}
// 		return iVal;
// 	}

// 	double GetLatitude()
// 	{
// 		int iLatitude;
//
// 		iLatitude = GetILatitude();
//
// 		double dbLatitude = DLATITUDE2LAT( iLatitude );
// 		return dbLatitude;
// 	}
//
// 	int GetILatitude()
// 	{
// 		char ch=0;
//
// 		int iVal=0;
//
// 		// memcpy( szBuffer, (LPCSTR) strLatitude, strLatitude.GetLength()+1 );
//
// #ifdef _MSC_VER
//         sscanf_s( szLatitude, "%d%1c" , & iVal, & ch, sizeof(char) );
// #else
//         sscanf( szLatitude, "%d%1c" , & iVal, & ch );
// #endif
//
// 		if( ch != 'N' && ch != 'n' && ch != 'S' && ch == 's' ) {
// 			iVal = 0;
// 		}
//
// 		return iVal;
// 	}

};

struct SThreatBase	//위협 (EOB 기반임)
{
                                                                                                                //PIN
// 	char szBE_Number[_MAX_BE_NUMBER_STRING_SIZE_];								//위협의 BE Number (10)
// 	char szFacilityName[_MAX_SIZE_OF_FACILITYNAME_];							//기지명칭 (위협명) (50)
 	char szPlaceNameKor[_MAX_STRING_SIZE_];												//한글지명 (50)
 	char szPlaceNameEng[_MAX_STRING_SIZE_];												//영문지명 (50)
// 	char szUserCountry[_MAX_USER_COUNTRY_STRING_SIZE_];						//사용국가 (2)	//*추후 삭제예정
// 	char szPrimaryFunction[_MAX_PRIMARY_FUNCTION_STRING_SIZE_];		//주기능코드(문자열)
// 	char szADA[_MAX_ADA_STRING_SIZE_];														//대공방공구역 (ADA) (AA123 형식) (5)
//
// 	CountryCode::EnumCountryCode eUserCountry;	//사용국가를 enum으로 표현
// 	EnumFunctionCodes ePrimaryFunction_ForGUI;	//주기능코드
// 	FriendOrFOE::EnumFriendOrFOE eFriendOrFOE;	//적아구분 enum값
// 	int nPriority;															//우선순위 (0~255, 기본값 255)
// 	int nCategory;															//자체 구분 카테고리 (99999 형식)(5)
//
// 	char szDTC[_MAX_DATETIME_STRING_SIZE_];							//DATE TIME CREATED (생성시간)
// 	char szDTLI[_MAX_DATETIME_STRING_SIZE_];						//DATE TIME LAST INFO (마지막 반영시간)
// 	char szDTFI[_MAX_DATETIME_STRING_SIZE_];						//DATE TIME FIRST INFO (최초 반영시간)
// 	char szDistinction[_MAX_DISTINCTION_STRING_SIZE_];	//구분(자체적으로 만들어 사용하는 코드)
//
    PlatformCode::EnumPlatformCode ePlatform;						//탑재 플랫폼의 종류 (PLATFORM_CODE 참조)

// 	char szSymbolCode[_MAX_SYMBOLCODE_STRING_SIZE_];		//2525B 심볼코드
// 	char szThreatLatitude[_MAX_LATITUDE_STRING_SIZE_];				//위도
// 	char szThreatLongitude[_MAX_LONGITUDE_STRING_SIZE_];			//경도
//
    SThreatBase() {
        //iPinNum = 0;																		//PIN

// 		eUserCountry=CountryCode::enumUndefinedCountry;	//사용국가를 enum으로 표현
// 		ePrimaryFunction_ForGUI=enumUndefinedFunctionCode;	//주기능코드
// 		szBE_Number[0] = NULL;
// 		szFacilityName[0] = NULL;
// 		szPlaceNameKor[0] = NULL;
// 		szPlaceNameEng[0] = NULL;
// 		szUserCountry[0] = NULL;
// 		szPrimaryFunction[0] = NULL;								//주기능코드(문자열)
// 		eFriendOrFOE=FriendOrFOE::enumUnknown;			//적아구분 enum값
// 		nPriority=255;															//우선순위 (0~255, 기본값 255)
// 		szADA[0] = NULL;														//대공방공구역 (ADA) (AA123 형식) (5)
// 		nCategory=0;																//자체 구분 카테고리 (99999 형식)(5)
// 		szDTC[0] = NULL;														//DATE TIME CREATED (생성시간)
// 		szDTLI[0] = NULL;														//DATE TIME LAST INFO (마지막 반영시간)
// 		szDTFI[0] = NULL;														//DATE TIME FIRST INFO (최초 반영시간)
// 		ePlatform=PlatformCode::enumUnKnown;				//탑재 플랫폼의 종류 (PLATFORM_CODE 참조)
// 		szDistinction[0] = NULL;										//구분(자체적으로 만들어 사용하는 코드)
// 		szSymbolCode[0] = NULL;										//2525B 심볼코드
// 		szThreatLatitude[0] = NULL;									//위도
// 		szThreatLongitude[0] = NULL;								//경도
        }
};

// struct SDevice : public SThreatAndDeviceBase, SThreatBase, SDeviceBase, SDeviceInfoFromRadar	//장비 (EOB 기반)
// {
// 	time_t tiDBUpdateTime;												// DB에서 갖고온 업데이트 시간
// 	int nDBThreatIndex;
// 	int nDBDeviceIndex;
//
// 	SDevice()
// 	{
// 		tiDBUpdateTime = 0;
// 		nDBThreatIndex = 0;
// 		nDBDeviceIndex = 0;
//
// 	}
// };

enum ENUM_THREAT_PLATFORM {
	enPlatform_UNKNOWN=0,

	enPlatform_GROUND,

	enPlatform_AIR,
	enPlatform_MOVING_GROUND,
} ;

/**
    @struct SThreat
    @brief  위협 +_ 장비 관련 구조체
**/
struct SThreat : public SDeviceBase	//위협 (EOB 기반임)
{
	//vector <SDevice> vecDevice;	//장비
    unsigned int uiPinNum;
	unsigned int uiThreatIndex;
	unsigned int uiPriority;

	//float fLatitude;
	//float fLongitude;


	int iCategory;

	FriendOrFOE::EnumFriendOrFOE eFriendOrFOE;	//적아구분 enum값
	ENUM_THREAT_PLATFORM enPlatform;

	// float fIdRange;

    char szPlaceNameKor[_MAX_SITE_NAME_SIZE];
    //char szPlaceNameEng[_MAX_SITE_NAME_SIZE];
    //char szRadarModeName[_MAX_RADARMODE_NAME_SIZE];
    char szThreatName[_MAX_THREAT_NAME_SIZE];
    char szSiteName[_MAX_SITE_NAME_SIZE];
    char szSymbolCode[_MAX_SYMBOLCODE_STRING_SIZE_];

    // char szPrimaryFunction[_MAX_PRIMARY_FUNCTION_STRING_SIZE_];		//주기능코드(문자열)

	SThreat() //: tiDBUpdateTime(0), nDBThreatIndex(0)
	{
		//vecDevice = vector <SDevice>();
	}

// 	int GetILatitude()
// 	{
// 		int nLength, nRet;
// 		nLength = (int) strlen( szThreatLatitude );
// 		if ( nLength != 7 ) {
// 			nRet = -1;
// 		}
// 		else
// 		{
// 			//double dbLatitude = _ttof(strLatitude.Left(2))+_ttof(strLatitude.Mid(2,2))*1.0/60.0+_ttof(strLatitude.Mid(4,2))*1.0/60.0/60.0;
// 			nRet = (int) _ttof(szThreatLatitude);
// 		}
//
// 		return nRet;
// 	}
//
// 	int GetILongitude()
// 	{
// 		int nLength, nRet;
// 		nLength = (int) strlen( szThreatLongitude );
// 		if ( nLength != 8 ) {
// 			nRet = -1;
// 		}
// 		else
// 		{
// 			// double dbLongitude = _ttof(strLongitude.Left(3))+_ttof(strLongitude.Mid(3,2))*1.0/60.0+_ttof(strLongitude.Mid(5,2))*1.0/60.0/60.0;
// 			nRet = (int) _ttof(szThreatLongitude);
// 		}
// 		return nRet;
// 	}

};

// struct SRelatedThreat	: SThreatBase, SDeviceBase, SThreatAndDeviceBase //연관 위협(+장비)
// {
// 	SRelatedThreat()	{}
// 	void SetData(SThreat &i_stThreat, SDevice &i_stDevice)
// 	{
// 		nThreatIndex					= i_stThreat.nThreatIndex;						//유일한 인덱스
// 		eStatus_ForGUI				= i_stThreat.eStatus_ForGUI;					//THREAT_STATUS_CODE 참조 (C, P, N, X, D, U, I 중 하나)
// 		nPin									= i_stThreat.nPin;									//PIN
// 		strcpy_s( szBE_Number, i_stThreat.szBE_Number );					//위협의 BE Number (10)
// 		strcpy_s( szFacilityName, i_stThreat.szFacilityName );					//기지명칭 (위협명) (50)
// 		strcpy_s( szPlaceNameKor, i_stThreat.szPlaceNameKor );				//한글지명 (50)
// 		strcpy_s( szPlaceNameEng, i_stThreat.szPlaceNameEng );				//영문지명 (50)
// 		strcpy_s( szUserCountry, i_stThreat.szUserCountry );					//사용국가 (2)	//*추후 삭제예정
// 		eUserCountry					= i_stThreat.eUserCountry;					//사용국가를 enum으로 표현
// 		ePrimaryFunction_ForGUI	= i_stThreat.ePrimaryFunction_ForGUI;	//주기능코드
// 		eFriendOrFOE					= i_stThreat.eFriendOrFOE;					//적아구분 enum값
// 		nPriority							= i_stThreat.nPriority;								//우선순위 (0~255, 기본값 255)
// 		strcpy_s( szADA, i_stThreat.szADA );								//대공방공구역 (ADA) (AA123 형식) (5)
// 		nCategory						= i_stThreat.nCategory;						//자체 구분 카테고리 (99999) (5)
// 		strcpy_s( szDTC, i_stThreat.szDTC );											//DATE TIME CREATED (생성시간)
// 		strcpy_s( szDTLI, i_stThreat.szDTLI );									//DATE TIME LAST INFO (마지막 반영시간)
// 		strcpy_s( szDTFI, i_stThreat.szDTFI );										//DATE TIME FIRST INFO (최초 반영시간)
// 		ePlatform							= i_stThreat.ePlatform;							//탑재 플랫폼의 종류 (PLATFORM_CODE 참조)
// 		strcpy_s( szDistinction, i_stThreat.szDistinction );						//구분(자체적으로 만들어 사용하는 코드)
// 		strcpy_s( szSymbolCode, i_stThreat.szSymbolCode );					//2525B 심볼코드
// 		strcpy_s( szThreatLatitude, i_stThreat.szThreatLatitude );				//위도
// 		strcpy_s( szThreatLongitude, i_stThreat.szThreatLongitude );			//경도
// 		nDeviceIndex					= i_stDevice.nDeviceIndex;					//Threat안에서 장비의 인덱스
// 		nRadarIndex					= i_stDevice.nRadarIndex;						//레이더 인덱스
// 		strcpy_s( szELNOT, i_stDevice.szELNOT );							//NOTATION (5)
//
// 		//strDeviceName					= i_stDevice.strDeviceName;					//장비명 (주로 NICKNAME) (50)
// 		strcpy_s( szDeviceName, i_stDevice.szDeviceName );
//
// 		eDevStatus_ForGUI			= i_stDevice.eDevStatus_ForGUI;			//STATUS_CODE 참조 (C, P, N, X, D, U, I 중 하나)
// 		nIdentificationRange		= i_stDevice.nIdentificationRange;			//식별반경(NM: 노티컬마일; 기본값 5
// 		strcpy_s( szLatitude, i_stDevice.szLatitude );							//위도
// 		strcpy_s( szLongitude, i_stDevice.szLongitude );						//경도
// 		nElevation						= i_stDevice.nElevation;							//고도 (0~99999 ?)
// 	}
// 	SRelatedThreat(SThreat &i_stThreat, SDevice &i_stDevice)
// 	{
// 		SetData(i_stThreat, i_stDevice);
// 	}
// };

// EOB 엑셀 데이터를 읽어들이기 위한 구조체 - 전신대 추가
struct SEobExcelData
{
	int		nPin;							//PIN
    CString	strPlaceNameKor;		//한글지명
	//CString	strPlaceNameEng;		//영문지명
	//CString	strUserCountry;			//국가
	//CString	strFriendOrFOE;			//적아구분
	//int		nPriority;						//우선순위
    CString	strDistinction;				//구분
    CString	strFacilityName;			//Facility Name
    CString	strStatus;						//Status
	//CString	strIdentificationRange;//식별반경
	//CString	strPlatform;					//플랫폼형태
    CString	strLatitude;					//위도
    CString	strLongitude;				//경도
	int		nElevation;					//고도
    CString	strADA;							//대공방공구역 (ADA) (AA123 형식) (5)
    CString	strBENumber;				//위협의 BE Number (10)
    CString	strCategory;				//Category
    CString	strPrimaryFunction;		//PRI FUNCTION
    CString	strDTC;							//DATE TIME CREATED (생성시간)
    CString	strDTLI;						//DATE TIME LAST INFO (마지막 반영시간)
	int		nDeviceIndex;				//Threat안에서 장비의 인덱스
    CString	strDeviceName;			//장비명 (주로 NICKNAME) (50)
    CString	strELNOT;						//NOTATION (5)
    CString	strDevStatus;				//장비Status
    CString	strDTFI;						//DATE TIME FIRST INFO (최초 반영시간)
	SEobExcelData()
	{
		nPin=0;
		strPlaceNameKor="";
		//CString	strPlaceNameEng;
		//CString	strUserCountry;
		//CString	strFriendOrFOE;
		//int		nPriority;
		strDistinction="";
		strFacilityName="";
		strStatus="";
		//CString	strIdentificatio
		//CString	strPlatform;
		strLatitude="";
		strLongitude="";
		nElevation=0;
		strADA="";
		strBENumber="";
		strCategory="";
		strPrimaryFunction="";
		strDTC="";
		strDTLI="";
		nDeviceIndex=0;
		strDeviceName="";
		strELNOT="";
		strDevStatus="";
		strDTFI="";
	}
};

struct SThreatPriorities
{
	vector<long> vlThreatIndex;	//위협 인덱스들
	int nPriority;						//위협 우선순위

	SThreatPriorities()
	{
		nPriority=0;
	}
};

struct SThreatFOE
{
	vector<long> vlThreatIndex;								//위협 인덱스들
	FriendOrFOE::EnumFriendOrFOE eFriendOrFOE;		//적아구분 enum값

	SThreatFOE()
	{
		eFriendOrFOE = FriendOrFOE::enumUnknown;
	}
};

struct SCountry
{
    CString strCountryCode;	//두자리 국가코드 (2)
    CString strCountryName;	//Full Name (80)
    CString strTrigraph;			//세글자 국가코드 (3)
	SCountry()
	{
		strCountryCode="";
		strCountryName="";
		strTrigraph="";
	}
};

struct SFunctionCodes
{
    CString strAbbreviation;	//두글자 알파벳 (2 ?)
    CString strName;			//풀어쓴 내용 (45)
	EnumFunctionCodes eFunctionCodes_ForGUI;
	SFunctionCodes()
	{
		strAbbreviation="";
		strName="";
		eFunctionCodes_ForGUI=enumUndefinedFunctionCode;
	}
};

struct SRadarModeComments
{
	int nRadarModeCommentIndex;	//주석의 인덱스
    CString strTitle;						//주석 이름(30)
    CString strType;						//주석의 형태(ERP, GEN, MODE, MOP, PD, POL, PRI, RF, SCAN)
    CString strComments;				//실제 주석
	bool bUpdate;
	SRadarModeComments()
	{
		nRadarModeCommentIndex=0;
		strTitle="";
		strType="";
		strComments="";
		bUpdate=false;

	}
};

// struct SRadarPRI_SpotValues
// {
// 	float fPRI_Min;		//주로 나오는 PRI 값(USEC)
// 	float fPRI_Max;	//주로 나오는 PRI 값(USEC)
// 	int nSeclab;
//
// 	SRadarPRI_SpotValues()
// 	{
// 		fPRI_Min=0.0f;
// 		fPRI_Max=0.0f;
// 		nSeclab=0;
// 	}
// };

struct SRadarPRI_GroupSpacing
{
	int nSequenceNum;		//값의 시퀀스를 나타낸 것이 아닌 단순 일련번호
	float fGroupSpacing;		//그룹 펄스 안의 펄스간 간격에 올 수 있는 값 (USEC)
	SRadarPRI_GroupSpacing()
	{
		nSequenceNum=0;
		fGroupSpacing=0.0f;
	}
};

struct SRadarPRI_Values		//PRI Eliment
{
	int nPRI_Index;				//레이더 모드 안에서의 PRI 인덱스
	float fPRI_Min;					//PRI 최소(USEC)
	float fPRI_Max;				//PRI 최대(USEC)
	float fDwellDurationMin;		//한 Dwell이 유지되는 시간(USEC) 최소
	float fDwellDurationMax;	//한 Dwell이 유지되는 시간(USEC) 최대
	int nPulsesPerDwell;			//Dwell당 펄스 수
	float fTransitionMin;			//다음 Dwell로 전환되는데 걸리는 시간(USEC) 최소
	float fTransitionMax;			//다음 Dwell로 전환되는데 걸리는 시간(USEC) 최대

	SRadarPRI_Values()
	{
		nPRI_Index=0;
		fPRI_Min=0;
		fPRI_Max=0;
		fDwellDurationMin=0.0f;
		fDwellDurationMax=0.0f;
		nPulsesPerDwell=0;
		fTransitionMin=0.0f;
		fTransitionMax=0.0f;
	}
};

struct SRadarPRI_SequenceName
{
	int nPRI_SeqID;				//레이더모드 안에서 시퀀스의 일련번호
    CString strPRI_SeqName;	//시퀀스의 이름(32)

	SRadarPRI_SequenceName()
	{
		nPRI_SeqID=0;
		strPRI_SeqName="";
	}
};

struct SRadarPRI_SequenceNumIndex
{
	int nPRI_SequenceNum;	//시퀀스 안에서 값이 나오는 순서
	int nPRI_Index;			//PRI값(Value)을 가리키는 인덱스
	SRadarPRI_SequenceNumIndex()
	{
		nPRI_SequenceNum=0;
		nPRI_Index=0;
	}
};
struct SRadarPRI_Sequence : SRadarPRI_SequenceName
{
	vector<SRadarPRI_SequenceNumIndex> vecPRI_NumIndex;
	SRadarPRI_Sequence()
	{
		vecPRI_NumIndex = vector<SRadarPRI_SequenceNumIndex>();
	}
};

struct SRadarPD_Values
{
	int nPD_Index;		//실제 PD값을 가리키는 인덱스
	float fPD_Min;		//PD 최소 (USEC)
	float fPD_Max;		//PD최대 (USEC)

	SRadarPD_Values()
	{
		nPD_Index=0;
		fPD_Min=0.0;
		fPD_Max=0.0;
	}
};

struct SRadarPD_SequenceName
{
	int nPD_SeqID;			//PD 시퀀스의 번호
	CString strPD_SeqName;	//시퀀스 이름(32)

	SRadarPD_SequenceName()
	{
		nPD_SeqID=0;
		strPD_SeqName="";
	}
};

struct SRadarPD_SequenceNumIndex
{
	int nPD_SequenceNum;	//시퀀스 안에서 값이 나오는 순서
	int nPD_Index;			//PD값(Value)을 가리키는 인덱스

	SRadarPD_SequenceNumIndex()
	{
		nPD_SequenceNum=0;
		nPD_Index=0;
	}
};
struct SRadarPD_Sequence : SRadarPD_SequenceName
{
	vector<SRadarPD_SequenceNumIndex> vecPD_NumIndex;
	SRadarPD_Sequence()
	{
		vecPD_NumIndex = vector<SRadarPD_SequenceNumIndex>();
	}
};


struct SRadarPD_SpotValues
{
	float fPD_Min;	//PD 최소값
	float fPD_Max;	//PD 최대값

	SRadarPD_SpotValues()
	{
		fPD_Min=0.0;
		fPD_Max=0.0;
	}
};

struct SRadarMOP_CW_Values
{
	int nMOP_CW_Index;
	int nMOP_CW_ValueIndex;	//변조값 Index
	float fMOP_CW_Min;		//변조값 Min (FMOP이면 주파수값 MHZ, PMOP이면 위상 DEGREEE)
	float fMOP_CW_Max;		//변조값 Min (FMOP이면 주파수값 MHZ, PMOP이면 위상 DEGREEE)

	SRadarMOP_CW_Values()
	{
		nMOP_CW_Index=0;
		nMOP_CW_ValueIndex=0;
		fMOP_CW_Min=0.0f;
		fMOP_CW_Max=0.0f;
	}
};

struct SRadarMOP_CW_SeqName
{
	int nMOP_CW_Index;		//레이더 모드 안의 MOP_CW 데이터 Index
	int nMOP_CW_SeqID;		//MOP_CW 안에서 시퀀스 한개의 Index
	CString strMOP_CW_Name;	//시퀀스의 이름(32)

	SRadarMOP_CW_SeqName()
	{
		nMOP_CW_Index=0;
		nMOP_CW_SeqID=0;
		strMOP_CW_Name="";
	}
};

struct SRadarMOP_CW_SequenceNumIndex
{
	int nMOP_CW_SequenceNum;	//한 시퀀스 안에서 값의 순서
	int nMOP_CW_ValueIndex;		//실제 값을 가리키는 인덱스
	float fMOP_CW_Duration;		//변조값(주파수/위상)의 지속시간(USEC)

	SRadarMOP_CW_SequenceNumIndex()
	{
		nMOP_CW_SequenceNum=0;
		nMOP_CW_ValueIndex=0;
		fMOP_CW_Duration=0.0f;
	}
};
struct SRadarMOP_CW_Sequence : SRadarMOP_CW_SeqName
{
	vector<SRadarMOP_CW_SequenceNumIndex> vecMOP_CW_NumIndex;
	SRadarMOP_CW_Sequence()
	{
		vecMOP_CW_NumIndex = vector<SRadarMOP_CW_SequenceNumIndex>();
	}
};

struct SRadarMOP_CW
{
	int nRadarModeIndex;															//레이더 모드 인덱스
	int nMOP_CW_Index;																//레이더 모드 안에서의 MOP_CW 데이터 인덱스
	int nSeclab;
	MOP_CW_ModulationType::EnumMOP_CW_ModulationType eMOP_CW_ModulationType;	//펄스 내 또는 CW 변조형태 (MOP_CW_MOD_TYPE_CODE 참조)
	float fMOP_CW_BIT_DurationMin;											//비트 유지시간 (usec)
	float fMOP_CW_BIT_DurationMax;											//비트 유지시간 (usec)
	ContinuityCode::EnumContinuityCode eMOP_CW_Continuity;						//변조의 연속성 (CONTINUITY_CODE참조)
	int nMOP_CW_NumElements;													//변조 주기의 ELEMENT 수
	int nMOP_CW_NumPositions;													//변조 주기의 POSITION 수
	PatternCode::EnumPatternCode eMOP_CW_Pattern;					//변조의 패턴여부 (PATTERN_CODE참조)
	float fMOP_CW_PatternPeriodMin;											//패턴주기 MIN (us)
	float fMOP_CW_PatternPeriodMax;											//패턴주기 MAX (us)
	float fMOP_CW_RangeMin;														//값변경폭 MIN (KHz, Degree, dB)
	float fMOP_CW_RangeMax;														//값변경폭 MAX (KHz, Degree, dB)
	float fMOP_CW_RateMin;														//값변경율 (kHz, Degree, dB/usec) MIN
	float fMOP_CW_RateMax;														//값변경율 (kHz, Degree, dB/usec) MAX
	float fMOP_CW_StepMin;														//변조값의 STEP (FMOP이면 KHZ, PMOP이면 DEGREE)
	float fMOP_CW_StepMax;														//변조값의 STEP (FMOP이면 KHZ, PMOP이면 DEGREE)
	float fMOP_CW_MeanMin;														//평균값 MIN (MHZ, Degree, dB)
	float fMOP_CW_MeanMax;														//평균값 MAX (MHZ, Degree, dB)
	EnumMOP_CW_LegacyType eMOP_CW_LegacyType;					//변조형태의 LEGACY TERM (MOP_CW_LEGACY_TYPE_CODE)
	CString strMOP_CW_PatternName;											//변조패턴의 이름
	float fMOP_CW_OnTimeMin;													//CW ON TIME (us)
	float fMOP_CW_OnTimeMax;													//CW ON TIME (us)
	float fMOP_CW_OffTimeMin;													//CW OFF TIME (us)
	float fMOP_CW_OffTimeMax;													//CW OFF TIME (us)
	float fMOP_CW_DutyCycleMin;												//CW의 DUTY CYCLE %
	float fMOP_CW_DutyCycleMax;												//CW의 DUTY CYCLE %

	map <int /*nMOP_CW_SeqID*/, SRadarMOP_CW_Sequence> mapRadarMOP_CW_Sequence;	//레이더 모드 안에서 변조값 시퀀스의 일련번호들
	vector <SRadarMOP_CW_Values> vecRadarMOP_CW_Values;							//레이더 모드 안에서의 변조값 엘리먼트 목록

	SRadarMOP_CW()
	{
		nRadarModeIndex=0;
		nMOP_CW_Index=0;
		nSeclab=0;
		fMOP_CW_BIT_DurationMin=0.0f;
		fMOP_CW_BIT_DurationMax=0.0f;
		eMOP_CW_ModulationType=MOP_CW_ModulationType::enumUnknown;
		eMOP_CW_Continuity=ContinuityCode::enumUnknown;
		nMOP_CW_NumElements=0;
		nMOP_CW_NumPositions=0;
		eMOP_CW_Pattern=PatternCode::enumUnknown;
		fMOP_CW_PatternPeriodMin=0.0f;
		fMOP_CW_PatternPeriodMax=0.0f;
		fMOP_CW_RangeMin=0.0f;
		fMOP_CW_RangeMax=0.0f;
		fMOP_CW_RateMin=0.0f;
		fMOP_CW_RateMax=0.0f;
		fMOP_CW_StepMin=0.0f;
		fMOP_CW_StepMax=0.0f;
		fMOP_CW_MeanMin=0.0f;
		fMOP_CW_MeanMax=0.0f;
		eMOP_CW_LegacyType = enumUndefinedMOP_CW_LegacyType;
		fMOP_CW_OnTimeMin=0.0f;
		fMOP_CW_OnTimeMax=0.0f;
		fMOP_CW_OffTimeMin=0.0f;
		fMOP_CW_OffTimeMax=0.0f;
		fMOP_CW_DutyCycleMin=0.0f;
		fMOP_CW_DutyCycleMax=0.0f;

                strMOP_CW_PatternName = "";

		vecRadarMOP_CW_Values = vector <SRadarMOP_CW_Values>();

		mapRadarMOP_CW_Sequence = map <int /*nMOP_CW_SeqID*/, SRadarMOP_CW_Sequence>();
	}
};

struct SRadarRF_Values
{
	int nRF_Index;			//RF값에 매기는 단순 일련번호
	float fRF_Min;		//RF 최소값(MHz)
	float fRF_Max;		//RF 최대값(MHz)

	SRadarRF_Values()
	{
		nRF_Index=0;
		fRF_Min=0.0f;
		fRF_Max=0.0f;
	}
};

struct SRadarRF_SequenceName
{
	int nRF_SeqID;						//RF시퀀스의 ID
	CString strRF_SeqName;		//시퀀스 이름(32)

	SRadarRF_SequenceName()
	{
		nRF_SeqID=0;
		strRF_SeqName="";
	}
};

struct SRadarRF_SequenceNumIndex
{
	int nRF_SequenceNum;		//시퀀스 안에서 값이 나오는 순서
	int nRF_Index;					//RF값(Value)을 가리키는 인덱스

	SRadarRF_SequenceNumIndex()
	{
		nRF_SequenceNum=0;
		nRF_Index=0;
	}
};

struct SRadarRF_Sequence : SRadarRF_SequenceName
{
	vector<SRadarRF_SequenceNumIndex> vecRF_NumIndex;	//시퀀스 안에서 값이 나오는 순서, RF값(Value)를 가리키는 인덱스
	SRadarRF_Sequence()
	{
		vecRF_NumIndex = vector<SRadarRF_SequenceNumIndex>();
	}
};

struct SRadarRF_SpotValues
{
	float fRF_Min;		//RF 최소값(MHz)
	float fRF_Max;		//RF 최대값(MHz)

	SRadarRF_SpotValues()
	{
		fRF_Min=0.0f;
		fRF_Max=0.0f;
	}
};

struct SRadarPA_Diff_InGroup
{
	int nSequenceNum;				//순서
	float fPA_Diff;						//PA차(dBm)

	SRadarPA_Diff_InGroup()
	{
		nSequenceNum=0;
		fPA_Diff=0.0f;
	}
};

struct SRadarModeLifeCycle
{
	int nRadarIndex;					//레이더 모드가 어떤 레이더에 속하였는지를 나타냄
	int nRadarModeIndex;			//레이더 모드 인덱스
	CString strRadarModeName;	//모드명: 레이더 모드의 이름(30)
	// CString strModeCode;			//모드부호: 모드 코드 (예: DA000) DB로 임포트할 때는 앞의 2자리만 사용

	char szModeCode[_MAX_MODECODE_STRING_SIZE_];

	SRadarModeLifeCycle()
	{
		nRadarIndex=0;
		nRadarModeIndex=0;
                strRadarModeName="";
		szModeCode[0] = 0;
	}
};



struct SRadarMode_Sequence_Values
{
	int iRadarModeIndex;	//레이더 모드 인덱스
    int i_Index;	//레이더 모드 안에서의 PRI 인덱스

    float f_Min;	//PRI 최소(USEC)
    float f_Max;	//PRI 최대(USEC)

    SRadarMode_Sequence_Values():
    iRadarModeIndex(0),
            i_Index(0),
            f_Min(0.0),
            f_Max(0.0)
	{
	}
};

#define MAX_FREQ_PRI_SPOT               (16)

struct SRadarMode_Spot_Values
{
    int iRadarModeIndex;	//레이더 모드 인덱스

    float f_Min;	//PRI 최소(USEC)
    float f_Max;	//PRI 최대(USEC)

    SRadarMode_Spot_Values() :
        iRadarModeIndex(0),
        f_Min(0.0),
        f_Max(0.0)
    {
    }
};

struct SRadarInfo
{
    unsigned int uiRadarIndex;								// 레이더 인덱스

    char szRadarName[_MAX_RADARNAME_SIZE];

    char szELNOT[_MAX_ELNOT_STRING_SIZE_];			//* 전정부호(5): SRadar에서 읽어와서 채워줘야 함.
    unsigned int uiRadarPriority;								//*우선순위: SRadar에서 읽어와서 채워줘야 함.
    EnumRadarStatus eStatus;						//*상태 enum값
    char szNickName[_MAX_NICKNAME_STRING_SIZE_];
    //char szPlaceNameKor[_MAX_SIZE_OF_KOREASITENAME_];
    //char szWeaponSys[_MAX_WEAPON_STRING_SIZE_];
    //char szPlatform[_MAX_PLATFORM_STRING_SIZE_];

    int nUnknownEmitterTime_ForGUI;					//방사체 미활동판단시간(sec) (INVALID_INT_VALUE 이면 미표시)

    // int iTimeInactivatedOfRadar;					// 비활성화 시간

    unsigned int uiThreatIndex;								// ELNOT과 동일한 위협 번호
    unsigned int uiDeviceIndex;								// ELNOT과 동일한 장비 번호
    char szDeviceELNOT[_MAX_ELNOT_STRING_SIZE_];

    SRadarInfo()
    {
        uiRadarIndex =0;
        szDeviceELNOT[0] = 0;
        szELNOT[0] = 0;
        szNickName[0] = 0;
        //szPlaceNameKor[0] = 0;
        //szWeaponSys[0] = 0;
        //szPlatform[0] = 0;
        //szModeCode[0] = NULL;

        uiRadarPriority=0;
        eStatus=enumActive;
        nUnknownEmitterTime_ForGUI=0;
        uiRadarIndex = 0;
        uiThreatIndex = 0;
        uiDeviceIndex = 0;
    }
};

struct SRadarMode : SRadarInfo //, SParamSetAssociations		//레이더 모드 (옛날 Beam의 개념)
{
    unsigned int uiRadarModeIndex;												//레이더 모드에 대한 유니크한 인덱스

    time_t tiCreated;
	time_t tiLastUpdated;

	time_t tiFirstSeen;
	time_t tiLastSeen;

    EnumFunctionCodes eFunctionCode;                                        // 기능코드 Enum
    EnumValidationCode eValidation;                                         // 상태: 레이더 모드가 검증되었는지 여부 (VALIDATION_CODE참조)
    unsigned int uiRadarModePriority;                                                 // 우선순위
    bool bIgnoreFreqType;                                                   // 주파수 세부 관계없이 동일 빔으로 관리
    bool bIgnorePRIType;                                                    // PRI 세부 관계없이 동일 빔으로 관리

    char szModulationCode[_MAX_SIZE_OF_MODULATIONCODE];

    char szModeCode[_MAX_MODECODE_STRING_SIZE_];
    char szRadarModeName[_MAX_RADARMODE_NAME_SIZE];


	int iTimeInactivated;										// 비활성화 시간

    PlatformCode::EnumPlatformCode ePlatform;					//플랫폼 형태: 탑재 플랫폼의 종류 (PLATFORM_CODE 참조)
    CEDSignalType::EnumSignalType eSignalType;					//신호형태 (Pulsed, CW, EA) enum형태

    // 극성
    PolizationCode::EnumPolizationCode ePolarization;			//극성 (POLARIZATION_CODE 참조)

    // 주파수
    RadarModeFreqType::EnumRadarModeFreqType eRF_Type;			// 주파수형태 (Pulsed, CW, EA) enum형태
    //ContinuityCode::EnumContinuityCode eRF_Continuity;
    float fRF_TypicalMin;										//주관측범위: 주파수 Typical 최소(MHz)
    float fRF_TypicalMax;																		//주관측범위: 주파수 Typical 최대(MHz)
    PatternCode::EnumPatternCode eRF_Pattern;                   // RF 변화의 패턴 여부 (PATTERN_CODE 참조)
    int nRF_NumPositions;                                       // RF POSITION 수
    int nRF_NumElements;                                        // RF 엘트리먼트 수
    float fRF_PatternPeriodMin;                                 // RF 패턴 주기 (USEC) 최소
    float fRF_PatternPeriodMax;                                 // RF 패턴 주기 (USEC) 최대
    float fRF_MeanMin;                                          // RF 평균 최소
    float fRF_MeanMax;                                          // RF 평균 최대
    float fRF_RangeMin;                                         // 주파수 필터링 정보
    float fRF_RangeMax;

    // PRI
    RadarModePRIType::EnumRadarModePRIType ePRI_Type;			// PRI 형태 (Pulsed, CW, EA) enum형태
    float fPRI_TypicalMin;                                      // PRI TYPICAL (USEC) 최소
    float fPRI_TypicalMax;                                      // PRI TYPICAL (USEC) 최대
    PatternCode::EnumPatternCode ePRI_Pattern;                  // PRI 변화의 패턴 여부 (PATTERN_CODE 참조)
    int nPRI_NumPositions;                                      // PRI POSITION 수
    int nPRI_NumElements;                                       // PRI 엘트리먼트 수
    float fPRI_PatternPeriodMin;                                // PRI 패턴주기 MIN (USEC)
    float fPRI_PatternPeriodMax;                                // PRI 패턴주기 MAX (USEC)
    float fPRI_MeanMin;                                         // PRI 평균 최소
    float fPRI_MeanMax;                                         // PRI 평균 최대

    // 펄스폭
    float fPD_TypicalMin;                                       // PD TYPICAL 값 (USEC) 최소
    float fPD_TypicalMax;                                       // PD TYPICAL 값 (USEC) 최대
    float fPD_RangeMin;                                         // 펄스폭 필터링 정보
    float fPD_RangeMax;

    //* 스캔
    ScanType::EnumScanType eScanPrimaryType;				// 주 스캔타입 코드(SCAN_TYPE_CODE참조)
    float fScanPrimaryTypicalMin;						// 주 스캔 주기값의 TYPICAL (SEC) 최소
    float fScanPrimaryTypicalMax;						// 주 스캔 주기값의 TYPICAL (SEC) 최대
    ScanType::EnumScanType eScanSecondaryType;				// 부 스캔타입 코드(SCAN_TYPE_CODE참조)
    float fScanSecondaryTypicalMin;						// 부 스캔 주기값의 TYPICAL (SEC)
    float fScanSecondaryTypicalMax;						// 부 스캔 주기값의 TYPICAL (SEC)

	//* 주파수 세부정보
	//map <int /*nRF_Seq_ID*/, SRadarRF_Sequence> mapRadarRF_Sequence;		//레이더 모드 안에서 RF 시퀀스의 일련번호들 (구조체 내의 nRF_Index값으로 아래의 엘리먼트 목록에서 최소/최대 주파수를 가져온다)
	//vector <SRadarRF_Values> vecRadarRF_Values;							//레이더 모드 안에서 RF 값들(엘리먼트 목록)
	vector <SRadarMode_Sequence_Values> vecRadarMode_RFSequenceValues;						//레이더 모드 안에서 PRI값들(엘리먼트 목록)
	vector <SRadarMode_Spot_Values> vecRadarRF_SpotValues;			//주로 나오는 RF 값들(주관측값 목록)

    //* 펄스반복주기 세부정보
    vector <SRadarMode_Spot_Values> vecRadarPRI_SpotValues;		//주로 나오는 PRI 값들 (주관측값 목록)
    //map <int /*nPRI_Seq_ID*/, SRadarPRI_Sequence> mapRadarPRI_Sequence;		//레이더 모드 안에서 PRI 시퀀스의 일련번호들 (구조체 내의 nPRI_SeqID값으로 아래의 엘리먼트 목록에서 최소/최대 PRI값을 가져온다.)
    vector <SRadarMode_Sequence_Values> vecRadarMode_PRISequenceValues;		//레이더 모드 안에서 PRI값들(엘리먼트 목록)
    //vector <SRadarPRI_GroupSpacing> vecRadarPRI_GroupSpacing;				//그룹 펄스 안의 펄스간 간격에 올 수 있는 값들

    SRadarMode()
    {
        szRadarModeName[0] = 0;

		szRadarName[0] = 0;
		tiCreated = 0;
		tiLastUpdated = 0;

		tiFirstSeen = 0;
		tiLastSeen = 0;

        //nRadarModenPriority = INVALID_INT_VALUE;
        eSignalType=CEDSignalType::enumPulsed;
        eRF_Type=RadarModeFreqType::enumFIXED;
        ePRI_Type=RadarModePRIType::enumStable;
        uiRadarModeIndex=0;
        eFunctionCode=enumUndefinedFunctionCode;
        //fERP_TypicalMin=FLT_MIN;
        //fERP_TypicalMax=FLT_MIN;
        ePlatform=PlatformCode::enumUnKnown;
        //ePolarization=PolizationCode::enumUndefinedPolization;
        //ePOL_RotationDirection=enumUndefinedRotationDir;
        fRF_TypicalMin=FLT_MIN;
        fRF_TypicalMax=FLT_MIN;
        //fRF_ChannelSpacingMin=FLT_MIN;
        //fRF_ChannelSpacingMax=FLT_MIN;
        //eRF_Continuity=ContinuityCode::enumUnknown;
        //eRF_Pattern=PatternCode::enumUnknown;
        //nRF_NumElements=INVALID_INT_VALUE;
        nRF_NumPositions=INVALID_INT_VALUE;
        fRF_PatternPeriodMin=FLT_MIN;
        fRF_PatternPeriodMax=FLT_MIN;
        //fRF_RangeMin=FLT_MIN;
        //fRF_RangeMax=FLT_MIN;
        //fRF_RateMin=FLT_MIN;
        //fRF_RateMax=FLT_MIN;
        //eRF_Coherency=CohencyCode::enumUnknown;
        //ePRI_Continuity=ContinuityCode::enumUnknown;
        //fPRI_FramePeriodMin=FLT_MIN;
        //fPRI_FramePeriodMax=FLT_MIN;
        //nPRI_NumElements=INVALID_INT_VALUE;
        //nPRI_NumPositions=INVALID_INT_VALUE;
        //ePRI_Pattern=PatternCode::enumUnknown;
        fPRI_PatternPeriodMin=FLT_MIN;
        fPRI_PatternPeriodMax=FLT_MIN;
        //fPRI_PPG_Min=FLT_MIN;
        //fPRI_PPG_Max=FLT_MIN;
        //fPRI_RangeMin=FLT_MIN;
        //fPRI_RangeMax=FLT_MIN;
        //fPRI_RateMin=FLT_MIN;
        //fPRI_RateMax=FLT_MIN;
        //fPRI_SubframePeriodMin=FLT_MIN;
        //fPRI_SubframePeriodMax=FLT_MIN;
        fPRI_TypicalMin=FLT_MIN;
        fPRI_TypicalMax=FLT_MIN;
        //ePD_Continuity=ContinuityCode::enumUnknown;
        fPD_TypicalMin=FLT_MIN;
        fPD_TypicalMax=FLT_MIN;
        //nPD_NumElements=INVALID_INT_VALUE;
        //nPD_NumPositions=INVALID_INT_VALUE;
        //ePD_Pattern=PatternCode::enumUnknown;
        //fPD_PatternPeriodMin=FLT_MIN;
        //fPD_PatternPeriodMax=FLT_MIN;
        //fScanPrimaryTypicalMin=FLT_MIN;
        //fScanPrimaryTypicalMax=FLT_MIN;
        //eScanSecondaryType=ScanType::enumUndefinedScanType;
        //fScanSecondaryTypicalMin=FLT_MIN;
        //fScanSecondaryTypicalMax=FLT_MIN;
        eValidation=enumUnvalidated;
        //eRF_LagacyType=enumUndefinedRF_LagacyType;
        //ePRI_LagacyType=enumUndefinedPRI_LegacyType;
        //eScanPrimaryType=ScanType::enumUndefinedScanType;

        //strModulationCode = _T("");

        //stRadarModeLifeCycle = SRadarModeLifeCycle();

        //vecRadarRF_Values = vector <SRadarRF_Values>();
        vecRadarRF_SpotValues = vector <SRadarMode_Spot_Values>();
		vecRadarMode_RFSequenceValues = vector <SRadarMode_Sequence_Values>();

		vecRadarPRI_SpotValues = vector <SRadarMode_Spot_Values>();
        vecRadarMode_PRISequenceValues = vector <SRadarMode_Sequence_Values>();
        //vecRadarPRI_GroupSpacing = vector <SRadarPRI_GroupSpacing>();
        //vecRadarPD_Values = vector <SRadarPD_Values>();
        //vecRadarPD_SpotValues = vector <SRadarPD_SpotValues>();
        //vecRadarPA_Diff_InGroup = vector<SRadarPA_Diff_InGroup>();
        //vecRadarModeComments = vector <SRadarModeComments>();


        //mapRadarPRI_Sequence = map <int /*nPRI_Seq_ID*/, SRadarPRI_Sequence>();
        //mapRadarPD_Sequence = map <int /*nPD_Seq_ID*/, SRadarPD_Sequence>();
        //mapRadarMOP_CW = map<int /*nMOP_CW_Index*/, SRadarMOP_CW>();
        //mapRadarRF_Sequence = map <int /*nRF_Seq_ID*/, SRadarRF_Sequence>();
    }

    void Init() {
		vecRadarMode_RFSequenceValues.clear();
		vecRadarRF_SpotValues.clear();


		vecRadarPRI_SpotValues.clear();
		vecRadarMode_PRISequenceValues.clear();


        //vecRadarModeComments.clear();
        //mapRadarPRI_Sequence.clear();
        //vecRadarPRI_GroupSpacing.clear();
        //mapRadarPD_Sequence.clear();
        //vecRadarPD_Values.clear();
        //vecRadarPD_SpotValues.clear();
        //mapRadarMOP_CW.clear();
        //mapRadarRF_Sequence.clear();
        //vecRadarRF_Values.clear();
        //vecRadarRF_SpotValues.clear();
        //vecRadarPA_Diff_InGroup.clear();
    }
};


struct SRadarModeCopyInfo
{
	int nRadarIndex;		//레이더 인덱스
	SRadarMode stRadarMode;	//레이더 모드

	SRadarModeCopyInfo()
	{
		nRadarIndex=0;
		stRadarMode=SRadarMode();
		}
};


// struct SRadar
// {
// 	int nRadarIndex;															//레이더에 대한 유일한 인덱스
// 	int nSeclab;
// 	char szELNOT[_MAX_ELNOT_STRING_SIZE_];										//Elint Notation (5) 전정부호
// 	char szNickName[_MAX_NICKNAME_STRING_SIZE_];								//닉네임
//
// 	EnumFunctionCodes eFunctionCodes_ForGUI;									//레이더의 주기능 코드, 알파벳 (2)
// 	//char szFunctionCode[MAX_SIZE_OF_FUNCTIONCODE];
//
// 	int nPriority;																//(방사체)우선순위 (0~255)
// 	int nUnknownEmitterTime_ForGUI;												//방사체 미활동판단시간(sec) (0이면 미표시)
// 	SignalType::EnumSignalType eSignalType;										//신호형태 (Pulsed, CW, EA) enum형태
// 	float fMinFreq_ForGUI;														//최소주파수(MHz)
// 	float fMaxFreq_ForGUI;														//최대주파수(MHz)
// 	float fMinPRI_ForGUI;														//최소PRI(us)
// 	float fMaxPRI_ForGUI;														//최대PRI(us)
// 	EnumRadarStatus eStatus;													//상태 enum값 :Active, Renotated, Canceled, InCorporated, Retired, Undetected
// 	int nPrimaryWeaponSys;														//주연관 무기체계의 인덱스 (GUI목록에서는 아래의 map에서 구조체를 찾아 구조체 내부 이름 표시)
// 	int nPrimaryPlatform;														//주연관 플랫폼의 인덱스 (GUI목록에서는 아래의 map에서 구조체를 찾아 구조체 내부 이름 표시)
// 	vector <SRelatedThreat> vecRealtedThreat_ForGUI;							//연관위협
// 	vector <SRadarComments> vecRadarComments;									//주석
// 	map <int /*nAssocIndex*/, SParamSetAssociations> mapParamSetAssociations;	//해당 레이더-레이더모드간 연관관계 정보
// 	vector <SAssocELNOT> vecAssocELNOT;
// 	vector <SRadarUserCountry> vecRadarUserCountry;
// 	map <int /*nWeaponIndex*/, SWeaponSystem> mapAssocWeapSys;					//연관무기체계(GUI 목록에서는 구조체 내부의 이름 표시)
// 	map <int /*nPlatformIndex*/, SPlatform> mapAssocPlatform;					//연관플랫폼(GUI 목록에서는 구조체 내부의 이름 표시)
// 	vector<SRadarMode> vecRadarMode_ForGUI;										//구성 레이더모드
//
// 	SRadar()
// 	{
// 		nRadarIndex=0;
// 		nSeclab=0;
// 		eFunctionCodes_ForGUI=enumUndefinedFunctionCode;
// 		eSignalType=SignalType::enumCW;
// 		nPriority=0;
// 		nPrimaryWeaponSys=INVALID_INT_VALUE;
// 		nPrimaryPlatform=INVALID_INT_VALUE;
// 		nUnknownEmitterTime_ForGUI=INVALID_INT_VALUE;
// 		fMinFreq_ForGUI=0.0f;
// 		fMaxFreq_ForGUI=0.0f;
// 		fMinPRI_ForGUI=0.0f;
// 		fMaxPRI_ForGUI=0.0f;
// 		eStatus=enumActive;
//
// 		szELNOT[0] = NULL;
// 		szNickName[0] = NULL;
//
// 		vecRealtedThreat_ForGUI = vector <SRelatedThreat>();
// 		vecRadarComments = vector <SRadarComments>();
// 		vecAssocELNOT = vector <SAssocELNOT>();
// 		vecRadarUserCountry = vector <SRadarUserCountry>();
// 		vecRadarMode_ForGUI = vector<SRadarMode>();
//
// 		mapParamSetAssociations = map <int /*nAssocIndex*/, SParamSetAssociations>();
// 		mapAssocWeapSys = map <int /*nWeaponIndex*/, SWeaponSystem>();
// 		mapAssocPlatform = map <int /*nPlatformIndex*/, SPlatform>();
// 	}
//
// 	void Init() {
// 		vecRealtedThreat_ForGUI.clear();
// 		vecRadarComments.clear();
// 		vecAssocELNOT.clear();
// 		vecRadarUserCountry.clear();
// 		vecRadarMode_ForGUI.clear();
//
// 		mapParamSetAssociations.clear();
// 		mapAssocWeapSys.clear();
// 		mapAssocPlatform.clear();
//
// 	}
// };

//////////////////////////////////////////////////////////////////////////
// 전신대 추가 - 장비목록 실무형으로 이동에 필요..
struct SDevicePK
{
	int nThreatIndex; // 위협인덱스
	int nDeviceIndex; // 장비인덱스

	SDevicePK()
	{
		nThreatIndex=0;
		nDeviceIndex=0;
	}
};

// 전신대 추가 - 방사체 목록 실무형으로 이동에 필요..
struct SELNOTCopy
{
	int nBeforeRadarIndex;	// 원본 레이더 인덱스
	int nAfterRadarIndex;	// New 레이더 인덱스

	SELNOTCopy()
	{
		nBeforeRadarIndex = 0;
		nAfterRadarIndex = 0;
	}
};

typedef struct stSELThreatMapData{
	bool bShow;
	unsigned long long nThreatIndex;

	double dLatitude;				//	위도
	double dLongitude;			//	경도

	CString strSymbolCode;	//2525B 심볼코드
	CString strPlaceNameKor; // 한글지명
	CString strBeNumber; // BE번호
	CString strDevices; // 구성장비
	CString strADA; // ADA
	CString strCategory; // 구분
	CString strStatus; // 상태

	int nPinNumber;
	int nDeviceIdx;

	//EnumLibType enLibType;
	stSELThreatMapData()
	{
		bShow=false;
		nDeviceIdx = 0;
		nThreatIndex=0;
		dLatitude=0.0;
		dLongitude=0.0;
		strSymbolCode="";
		strPlaceNameKor="";
		strBeNumber = "";
		strDevices = "";
		strADA = "";
		strCategory = "";
		strStatus = "";
		nPinNumber=0;
		//enLibType=E_EL_LIB_TYPE_NORMAL;
	}
} SELThreatMapData;



// 타 창으로 위협 정보 를 전송하기 위한 구조체 정의
typedef struct stSELThreatInfo{
	double dLongitude;
	double dLatitude;
	CString strPinNum;
	stSELThreatInfo()
	{
		dLongitude = 0;
		dLatitude = 0;
		strPinNum = "";
	}

} SELThreatInfo;

/**
 * @typedef   SDeviceData
 * @brief     EOB 식별하기 위한 구조체 정의
 * @author    조철희 (churlhee.jo@lignex1.com)
 */
typedef struct stSELDeviceData
{
	double eob_latitude;
	double eob_longitude;

	int nIdentificationRange;
	int nThreatIndex;
	int nDeviceIndex;
	int nPriority;
	char szELNOT[_MAX_ELNOT_STRING_SIZE_];
	char szPlaceNameKor[_MAX_STRING_SIZE_];
	char szBE_Number[_MAX_BE_NUMBER_STRING_SIZE_];								//위협의 BE Number (10)
	char szPrimaryFunction[_MAX_PRIMARY_FUNCTION_STRING_SIZE_];		//주기능코드(문자열)

	stSELDeviceData()
	{
		eob_latitude=0;
		eob_longitude=0;

		nIdentificationRange=0;
		nThreatIndex=0;
		nDeviceIndex=0;
		memset(&szELNOT, 0, sizeof(szELNOT) );
		memset(&szPlaceNameKor, 0, sizeof(szPlaceNameKor) );
		memset(&szBE_Number, 0, sizeof(szBE_Number) );
		memset(&szPrimaryFunction, 0, sizeof(szPrimaryFunction) );
	}

} SDeviceData;


