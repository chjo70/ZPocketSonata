#pragma once

//#include "../../DEFINE/ELStringDefn.h"


//#include "../../../COMMON/DBIF/ElintDtctDataTypedb.h"

// #define DEF_OF_RES_FRQ_BAND1		0.625 //MHz
// #define DEF_OF_RES_FRQ_BAND2		1.250 //MHz
// #define DEF_OF_OFFSET_FRQ_BAND2	1280.0 //MHz
// #define DEF_OF_RES_FRQ_BAND3		1.500 //MHz
// #define DEF_OF_OFFSET_FRQ_BAND3	5866.0 //MHz
// #define DEF_OF_RES_TEST_PW					50 // nano sec
// #define DEF_OF_RES_TEST_TOA					0.000000050 // sec
// #define DEF_OF_RES_TEST_PA					0.3125
// #define DEF_OF_OFFSET_PA				-75.0
// #define DEF_OF_RES_DIRECTION		0.3515625 // degree
// #define DEF_OF_RES_FRQ_DIFF_BAND1	0.625 // MHz
// #define DEF_OF_RES_FRQ_DIFF_BAND2	1.250 // MHz
// #define DEF_OF_RES_FRQ_DIFF_BAND3	1.500 // MHz
// 
// #define DEF_OF_BAND_1	0
// #define DEF_OF_BAND_2	1
// #define DEF_OF_BAND_3	2
// #define DEF_OF_BAND_4	3
// 
// #define DEF_OF_RES_FREQ								(10.) // usec
// #define DEF_OF_RES_FREQ2							(100.) // usec
// #define DEF_OF_RES_FREQ3							(1000.) // usec
// #define DEF_OF_RES_FREQ6							(100.) // usec
// #define DEF_OF_RES_AOA								0.1 // Deg
// #define DEF_OF_RES_PW									6.48824 // nano sec
// #define DEF_OF_RES_WB_PW							6.48824 // nano sec
// #define DEF_OF_RES_NB_PW							14.0625 // nano sec
// #define DEF_OF_RES_PA									0.25 // dBm
// #define DEF_OF_RES_FRQ								10 // KHz
// #define DEF_OF_RES_FRQ_CHANGE_PERIOD	(10.0) // 0.1 // usec
// #define DEF_OF_RES_FRQ_CHANGE_WIDTH		1 // MHz
// #define DEF_OF_RES_PRI								(1000.) // usec
// #define DEF_OF_RES_PRF								(1000000.) // usec
// #define DEF_OF_RES_PPS								(1000000000.) // usec
// #define DEF_OF_RES_PRI_CHANGE_PERIOD	0.1 //usec
// #define DEF_OF_RES_PRI_CHANGE_PERCENT	0.1 // %
// #define DEF_OF_RES_TOA								6.48824 //nano sec
// #define DEF_OF_RES_WB_TOA							6.48824 //nano sec
// #define DEF_OF_RES_NB_TOA							14.0625 //nano sec
// #define DEF_OF_RES_NAVIPOS						0.1			// degree
// #define DEF_OF_BASE_PA								-110 //dB
#define DEF_OF_RES_GEOPOS							(1000000.0)
//#define DEF_OF_RES_ALTITUDE						4

// 함수 안에서 min/max validity 체크도 해주자. (실체계 코딩 때)
// namespace ELTestDecoder
// {
// 	double DecodeFrq(const int nBand, const unsigned short usBinFrq);
// 	double DecodePW(const unsigned short usBinPW);
// 	double DecodeTOA(const unsigned int nBinTOA);
// 	double DecodePA(const unsigned char ucBinPA);
// } ;
// 
// namespace ELDecoder
// {
// 	float DecodePW2(const int i_iBinPw);
// 	float DecodePWDev(const int i_iBinPw);
// 	float DecodeScanPrd(const int i_iBinScanPrd);
// 	float DecodeDIRatio(const int i_iBinDI);
// 	float DecodePOLRatio(const int i_iBinPOL);
// 	float DecodeHz(const int i_iBinHz);
// 	float DecodeFreq2(const int i_iBinFreq);
// 	float DecodeFreq3(const int i_iBinFreq);
// 	float DecodeFreq6(const int i_iBinFreq);
// 	float DecodePPS(const int i_iBinPRI);
// 	int DecodePPSTOPRI(const int i_iBinPPS);
// 	int DecodePPSTOPRI(const float i_fBinPPS);
// 	float DecodePRF(const int i_iBinPRF);
// 	float DecodePRI(const int i_iBinPRI);
// 	float DecodeAOA(const float i_fBinAoa);
// 	float DecodeAOA(const int i_iBinAoa);
// 	float DecodePW(const int i_iBinPw);
// 	float DecodePW(const int i_iBinPw, ENUM_EL_TASK enTaskType );
// 	float DecodeWindeBandPW(const int i_iBinPw);
// 	float DecodePA(const int i_iBinPa);
// 	float DecodePA(const float i_fBinPa);
// 	float DecodeGainPA(const int i_iBinPa);
// 	float DecodeFrq(const int i_iBinFrq);
// 	float DecodeFrq(const unsigned long long int i_iBinFrq);
// 	float DecodeFrqChangePeriod(const int i_iBinFrqChangePeriod);
// 	float DecodeMeanFrqStep(const int i_iBinMeanFrqStep);
// 	float DecodePriRatioPercent(const int i_iBinPriChangePercent);
// 	double DecodeToa(const unsigned long long int i_llilToa);
// 	double DecodeToa(const long long int i_llilToa, ENUM_EL_TASK enTaskType );
// 	double DecodeWideBandToa(const long long int i_llilToa);
// 	int DecodeAltitude(const int i_nAltitude);
// 
// 	void MakeTimeString( char *pString, time_t ti, unsigned int millisec );
// 	void MakeTextTimeString( char *pString, time_t ti, unsigned int millisec );
// 	void MakeTimeString( CString *pString, time_t ti, unsigned int millisec );
// 	void MakeTimeString2( CString *pString, time_t ti, unsigned int millisec );
// 	void DecodeStringTime( unsigned int *pTime_t, unsigned int *pMillisec, char *pszTime );
// 	void MakeSystemTimeFromTimeString( SYSTEMTIME *pSystemTime, CString *pStrText );
// 	bool CompareOfSystemTime( SYSTEMTIME *pSystemTime1, SYSTEMTIME *pSystemTime2 );
// 	void AddSystemTime( SYSTEMTIME *pSystemTime, float fDuration );
// 	void MakeStringSystemTime( CString *pString, SYSTEMTIME *pSystemTime );
// 	void MakeDateStringSystemTime( CString *pString, SYSTEMTIME *pSystemTime );
// 	double InvDecodeToa(const long long int i_llilToa, ENUM_EL_TASK enTaskType );
// 	void DecodeLongTOA( SCMLongTime *pcmlongtime, unsigned long long int llDTOA, unsigned long long int llTOADiv, ENUM_EL_TASK enTaskType );
// 
// 	double DecodeGeoPosition(const int& i_nPosLatLong);
// 	double DecodeDecimalGeoPosition(const double& i_fPosLatLong);
// 	double DecodeGeoStringPosition(CString& i_strLatLong);
// 
// 	void UpdateDateTime();
// 	void DecodeSmartTime( char *pSmartTime, char *szTime );
// 	void DecodeSmartMillisec( char *pSmartTime, char *szTime );
// 	void DecodeStringTime( char *szTime, char *pSmartTime );
// 
// 	void MakeSequence( char *szSeq, int *pArrSeq, int nElement, E_EN_DATA_ELEMENT_TYPE enElementType );
// 
// 	void ConvertLobInfoToWnd2LOBDataGroup( SRxLOBDataGroup *pLOBDataGroup, SLobInfoToWnd *pSLobInfoToWnd );
// 	void ConvertLobInfoToWnd2LOBData( SRxLOBData *pLOBData, SLobInfoToWnd *pSLobInfoToWnd );
// 
// 	int GetComboValue( char *pSearch, const char **pRefTable, int nRef );
// 	void ConvertLobInfoToWnd2LOBData( SRxLOBData *pLOBData, SLobInfoToWnd *pSLobInfoToWnd );
// 
// 	void DecodeDate( char *pszDate, char *pszDateTime );
// 	void DecodeDate( char *pszDate, string *pString );
// 	void DecodeTime( char *pszTime, string *pString );
// 
// 	float M2Map( int iEEPTiltAngle );
// 
// 	void ELGetTickCount();
// 	DWORD ELGetTickDuration();
// 
// };
