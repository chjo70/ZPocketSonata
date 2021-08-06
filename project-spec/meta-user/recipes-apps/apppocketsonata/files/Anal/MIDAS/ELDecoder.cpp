// ELDecoder.cpp: implementation of the ELDecoder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include <math.h>
#include <time.h>

#ifdef __linux__
#elif __VXWORKS__
#include <vxworks.h>
#else
#include <mmsystem.h>
#endif

#include "../SigAnal/_type.h"
#include "ELDecoder.h"

#define ENDIAN16(x)		((x&0x00ff)<<8) | ((x&0xff00)>>8)
#define ENDIAN32(x)     (x & 0x000000FF) << 24 | (x & 0x0000FF00) << 8 | \
	(x & 0xFF000000) >> 24 | (x & 0x00FF0000) >> 8
#define ENDIAN64(x) (DWORD64) ( \
	(((DWORD64 (x) <<56) & 0xff00000000000000)) | \
	(((DWORD64 (x) <<40) & 0x00ff000000000000)) | \
	(((DWORD64 (x) <<24) & 0x0000ff0000000000)) | \
	(((DWORD64 (x) <<8)  & 0x000000ff00000000)) | \
	(((DWORD64 (x) >>8)  & 0x00000000ff000000)) | \
	(((DWORD64 (x) >>24) & 0x0000000000ff0000)) | \
	(((DWORD64 (x) >>40) & 0x000000000000ff00)) | \
	(((DWORD64 (x) >>56) & 0x00000000000000ff)))

void AllEndian32(void* i_pData, unsigned int i_nSize)
{
	DWORD dwValue=0;
	UINT nStepSize=sizeof(DWORD);
	for(int i=0; i<(int)i_nSize; i+=nStepSize) 
	{
		memcpy(&dwValue, &((BYTE*)i_pData)[i], nStepSize);
		dwValue=ENDIAN32(dwValue);
		memcpy(&((BYTE*)i_pData)[i], &dwValue, nStepSize);
	}
}

#ifndef __VXWORKS__
void AllEndian64(void *i_pData, unsigned int i_nSize)
{
	unsigned __int64 un64Value=0;
	UINT nStepSize=sizeof(unsigned __int64);
	for(int i=0; i<(int)i_nSize; i+=nStepSize) 
	{
		memcpy(&un64Value, &((BYTE*)i_pData)[i], nStepSize);
		un64Value=_byteswap_uint64(un64Value);
		memcpy(&((BYTE*)i_pData)[i], &un64Value, nStepSize);
	}
}


void AllEndian16(void* i_pData, UINT i_nSize)
{
	WORD dwValue=0;
	UINT nStepSize=sizeof(WORD);
	for(int i=0; i<(int)i_nSize; i+=nStepSize) 
	{
		memcpy(&dwValue, &((BYTE*)i_pData)[i], nStepSize);
		dwValue=ENDIAN16(dwValue);
		memcpy(&((BYTE*)i_pData)[i], &dwValue, nStepSize);
	}
}
#endif

static time_t _stNOW;
static tm _stTM;

// REAL
float ELDecoder::DecodeAOA(const int i_iBinAoa)
{
	float fAoa = 0.0;
	fAoa = (float)i_iBinAoa * (float)DEF_OF_RES_AOA;
	return fAoa;
}

float ELDecoder::DecodePW2(const int i_iBinPw)
{
	float fPw = 0.0;
	fPw = ( (float)i_iBinPw * (float)DEF_OF_RES_PW ) / (float) 1000.;
	return fPw;
}

float ELDecoder::DecodePWDev(const int i_iBinPw)
{
	float fPw = 0.0;
	fPw = ( (float)i_iBinPw ) / (float) 1000.;
	return fPw;
}

float ELDecoder::DecodePW(const int i_iBinPw)
{
	float fPw = 0.0;
	fPw = ( (float)i_iBinPw * (float)DEF_OF_RES_PW );
	return fPw;
}

float ELDecoder::DecodePRI(const int i_iBinPRI)
{
	float fPRI = 0.0;
	fPRI = (float)i_iBinPRI / (float)DEF_OF_RES_PRI;
	return fPRI;
}

float ELDecoder::DecodePRF(const int i_iBinPRI)
{
	float fPRF = 0.0;
	if( i_iBinPRI != 0 )
		fPRF = (float) DEF_OF_RES_PRF / i_iBinPRI;
	return fPRF;
}

float ELDecoder::DecodePPS(const int i_iBinPRI)
{
	float fPPS = 0.0;
	if( i_iBinPRI != 0 )
		fPPS = (float) DEF_OF_RES_PPS / i_iBinPRI;
	return fPPS;
}

float ELDecoder::DecodeFreq2(const int i_iBinFreq)
{
	float fFREQ = 0.0;
	fFREQ = (float)i_iBinFreq / (float)DEF_OF_RES_FREQ2;
	return fFREQ;
}

/**
 * @brief     방사체/빔 목록창에 전시하기 위해서 주파수를 변환한다.
 * @param     i_iBinFreq 입력 주파수
 * @return    float 형으로 변환 결과를 리턴함.
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-07-19, 오후 7:36 
 * @warning   
 */
float ELDecoder::DecodeFreq3(const int i_iBinFreq)
{
	float fFREQ = 0.0;
	fFREQ = (float)i_iBinFreq / (float)DEF_OF_RES_FREQ3;
	return fFREQ;
}

/**
 * @brief     방사체/빔 목록창에 전시하기 위해서 인트라 주파수를 변환한다.
 * @param     i_iBinFreq 입력 주파수
 * @return    float 형으로 변환 결과를 리턴함.
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-07-19, 오후 7:37 
 * @warning   
 */
float ELDecoder::DecodeFreq6(const int i_iBinFreq)
{
	float fFREQ = 0.0;
	fFREQ = (float)i_iBinFreq / (float)DEF_OF_RES_FREQ6;
	return fFREQ;
}

float ELDecoder::DecodeScanPrd(const int i_iBinScanPrd)
{
	float fScanPrd = 0.0;
	fScanPrd = (float)i_iBinScanPrd / (float) 1000.;
	return fScanPrd;
}

float ELDecoder::DecodeHz(const int i_iBinHz)
{
	float fHZ = 0.0;
	if( i_iBinHz != 0 )
		fHZ = (float)1000. / (float) i_iBinHz;
	else
		fHZ = (float) 0.;
	return fHZ;
}

float ELDecoder::DecodeDIRatio(const int i_iBinDI)
{
	float fDIRatio = 0.0;
	fDIRatio = (float) i_iBinDI / (float)10.;
	return fDIRatio;
}

float ELDecoder::DecodeWindeBandPW(const int i_iBinPw)
{
	float fPw = 0.0;
	fPw = (float)i_iBinPw * (float)DEF_OF_RES_WB_PW;
	return fPw;
}

float ELDecoder::DecodePA(const int i_iBinPa)
{
	float fPa = 0.0;	
	fPa = ( (float)i_iBinPa * (float)DEF_OF_RES_PA) + (float)DEF_OF_BASE_PA;
	return fPa;
}

float ELDecoder::DecodeGainPA(const int i_iBinPa)
{
	float fPa = 0.0;
	fPa = (float)i_iBinPa * (float)DEF_OF_RES_PA;
	return fPa;
}


float ELDecoder::DecodePA(const float i_fBinPa)
{
	float fPa = 0.0;
	fPa = i_fBinPa * (float)DEF_OF_RES_PA;
	return fPa;
}

/**
 * @brief     로컬 타임과 비교하여 시간 표시를 스마트하게 표시하는 함수
 * @param     char * pSmartTime
 * @param     char * szTime
 * @return    void
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-05-10, 오전 10:06 
 * @warning   
 */
// void ELDecoder::DecodeStringTime( char *szTime, char *pSmartTime )
// {
// 	char szToday[30]={0,};
// 
// 	UpdateDateTime();
// 
// 	sscanf( pSmartTime, "%s" , szToday );
// 
// 	strcpy( szTime, pSmartTime );
// 
// }

/**
 * @brief     DecodeSmartTime
 * @param     char * pSmartTime
 * @param     char * pszTime
 * @return    void
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-06-17, 오후 4:47 
 * @warning   
 */
// void ELDecoder::DecodeSmartTime( char *pSmartTime, char *pszTime )
// {
// 	// codesonar, uninitialized variable. 이정남
// 	//struct tm szTimeConvert;
// 	struct tm szTimeConvert = tm();
// 	unsigned int uiMillisec=0;
// 
// 	if( pszTime[0] == NULL )
// 	{//DTEC_NullPointCheck
// 		pSmartTime[0] = NULL;
// 	}
// 	else {
// 		UpdateDateTime();
// 
// 		sscanf_s( pszTime, "%d/%d/%d %d:%d:%d.%d" , & szTimeConvert.tm_year, & szTimeConvert.tm_mon, & szTimeConvert.tm_mday, & szTimeConvert.tm_hour, & szTimeConvert.tm_min, & szTimeConvert.tm_sec, & uiMillisec );
// 		//sprintf( pSmartTime, "%02d/%02d/%02d %02d:%02d:%02d.%03d" , szTimeConvert.tm_year, szTimeConvert.tm_mon, szTimeConvert.tm_mday, szTimeConvert.tm_hour, szTimeConvert.tm_min, szTimeConvert.tm_sec, uiMillisec/1000000 );
// 		sprintf( pSmartTime, "%02d/%02d/%02d %02d:%02d:%02d.%03d" , szTimeConvert.tm_year, szTimeConvert.tm_mon, szTimeConvert.tm_mday, szTimeConvert.tm_hour, szTimeConvert.tm_min, szTimeConvert.tm_sec, uiMillisec );
// 
// 	}
// 
// }

// void ELDecoder::DecodeSmartMillisec( char *pSmartTime, char *pszTime )
// {
// 	// codesonar, uninitialized variable. 이정남
// 	//struct tm szTimeConvert;
// 	struct tm szTimeConvert = tm();
// 	unsigned int uiMillisec=0;
// 
// 	if( pszTime[0] == NULL )
// 	{//DTEC_NullPointCheck
// 		pSmartTime[0] = NULL;
// 	}
// 	else {
// 		UpdateDateTime();
// 
// 		sscanf_s( pszTime, "%d/%d/%d %d:%d:%d.%d" , & szTimeConvert.tm_year, & szTimeConvert.tm_mon, & szTimeConvert.tm_mday, & szTimeConvert.tm_hour, & szTimeConvert.tm_min, & szTimeConvert.tm_sec, & uiMillisec );
// 		sprintf( pSmartTime, "%02d/%02d/%02d %02d:%02d:%02d.%03d" , szTimeConvert.tm_year, szTimeConvert.tm_mon, szTimeConvert.tm_mday, szTimeConvert.tm_hour, szTimeConvert.tm_min, szTimeConvert.tm_sec, uiMillisec/1000000 );
// 
// 	}
// 
// }

/**
 * @brief     년월일을 초로 변환, 기본검색의 날짜 또는 수집 데이터 목록창에서 날짜/시간 문자열을 초로 변환
 * @param     unsigned int * pTime_t
 * @param     unsigned int * pMillisec
 * @param     char * pszTime
 * @return    void
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-01-09, 오후 4:09 
 * @warning   
 */
// void ELDecoder::DecodeStringTime( unsigned int *pTime_t, unsigned int *pMillisec, char *pszTime )
// {
// 	//struct tm tmToday;
// 
// 	//codesonar. Uninitialzed Variable. 이정남.
// 	struct tm tmToday = tm();
// 
// 	// pszTime 포멧: 01/11/01 01:54:04.112
// 	sscanf_s( pszTime, "%d/%02d/%02d %02d:%02d:%02d.%d" , & tmToday.tm_year, & tmToday.tm_mon, & tmToday.tm_mday, & tmToday.tm_hour, & tmToday.tm_min, & tmToday.tm_sec, pMillisec );
// 
// 	// 연도 변환
// 	if( tmToday.tm_year > 2000 )
// 		tmToday.tm_year -= 1900;
// 	else { //DTEC_Else
// 		tmToday.tm_year = ( tmToday.tm_year + 2000 - 1900 );
// 	}
// 
// 	// 월 변환
// 	-- tmToday.tm_mon;
// 
// 	*pTime_t = _mktime32( & tmToday );
// }

/**
 * @brief     UpdateDateTime
 * @param     void
 * @return    void
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-05-10, 오전 10:25 
 * @warning   
 */
void ELDecoder::UpdateDateTime()
{
	if( _stNOW == 0 ) {
#ifdef _MSC_VER			
		_stNOW = time( NULL );
		_localtime32_s( & _stTM, & _stNOW );

		_stTM.tm_year -= 100;
		_stTM.tm_mon += 1;
#else
		
#endif		
	}
}

// float ELDecoder::DecodeFrq(const int i_iBinFrq)
// {
// 	float fFrq = 0.0;
// 	fFrq = (float)i_iBinFrq * (float)DEF_OF_RES_FRQ;
// 	return fFrq;
// }

// float ELDecoder::DecodeFrq(const unsigned long long int i_iBinFrq)
// {
// 	float fFrq = 0.0;
// 	fFrq = (float)i_iBinFrq * (float)DEF_OF_RES_FRQ;
// 	return fFrq;
// }


// float ELDecoder::DecodeFrqChangeWidth(const int i_iBinFrqChangeWidth)
// {
// 	float fFrqChangeWidth = 0.0;
// 	fFrqChangeWidth = (float)i_iBinFrqChangeWidth * DEF_OF_RES_FRQ_CHANGE_WIDTH;
// 	return fFrqChangeWidth;
// }

// float ELDecoder::DecodeMeanFrqStep(const int i_iBinMeanFrqStep)
// {
// 	float fMeanFrqStep = 0.0;
// 	fMeanFrqStep = (float)i_iBinMeanFrqStep * (float)DEF_OF_RES_FRQ;
// 	return fMeanFrqStep;
// }
// 
// float ELDecoder::DecodeFrqChangePeriod(const int i_iBinFrqChangePeriod)
// {
// 	float fFrqChangePeriod = 0.0;
// 	fFrqChangePeriod = (float)i_iBinFrqChangePeriod * (float)DEF_OF_RES_FRQ_CHANGE_PERIOD;
// 	return fFrqChangePeriod;
// }
// 
// float ELDecoder::DecodePriChangePeriod(const int i_iBinPriChangePeriod)
// {
// 	float fPri = 0.0;
// 	fPri = (float)i_iBinPriChangePeriod * (float)DEF_OF_RES_PRI_CHANGE_PERIOD;
// 	return fPri;
// }

//////////////////////////////////////////////////////////////////////////
/*!
 * @brief     
 * @param     const int i_iBinPriChangePercent
 * @return    float
 * @version   0.0.1
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-11-24 오후 2:53 
 * @warning   
 */
// float ELDecoder::DecodePriRatioPercent(const int i_iBinPriChangePercent)
// {
// 	float fPri = 0.0;
// 	fPri = (float)i_iBinPriChangePercent * (float)DEF_OF_RES_PRI_CHANGE_PERCENT;
// 	return fPri;
// }

double ELDecoder::DecodeToa(const long long int i_llilToa)
{
	double dToa = 0.0;
	dToa = (double)i_llilToa * (double)DEF_OF_RES_TOA;
	return dToa;
}

// double ELDecoder::DecodeWideBandToa(const long long int i_llilToa)
// {
// 	double dToa = 0.0;
// 	dToa = (double)i_llilToa * (double)DEF_OF_RES_WB_TOA;
// 	return dToa;
// }
// 
// int ELDecoder::DecodeAltitude(const int i_nAltitude)
// {
// 	int nRtn = 0;
// 	nRtn = i_nAltitude * DEF_OF_RES_ALTITUDE;
// 	if( (nRtn/DEF_OF_RES_ALTITUDE) != i_nAltitude)
// 		nRtn = -1;
// 	return nRtn;
// }

// 시간 정보(초와 ms)를 저장할 수 있는 문자열로 변환
void ELDecoder::MakeTextTimeString( char *pString, time_t ti, unsigned int millisec )
{
	struct tm *pToday=nullptr;

	pToday = localtime( & ti );

	if( pToday !=nullptr ) {
		sprintf( pString, "%04d_%02d_%02d %02d_%02d_%02d_%03d", pToday->tm_year+1900, pToday->tm_mon+1, pToday->tm_mday, pToday->tm_hour, pToday->tm_min, pToday->tm_sec, millisec );
	}
}

/**
 * @brief     MakeTimeString
 * @param     char * pString
 * @param     time_t ti
 * @param     unsigned int millisec
 * @return    void
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-12-31, 오전 12:45 
 * @warning   
 */
void ELDecoder::MakeTimeString( char *pString, time_t ti, unsigned int millisec )
{
	struct tm *pToday=nullptr;

	pToday = localtime( & ti );

	if( pToday !=nullptr ) {
		sprintf( pString, "%04d/%02d/%02d %02d:%02d:%02d.%03d", pToday->tm_year+1900, pToday->tm_mon+1, pToday->tm_mday, pToday->tm_hour, pToday->tm_min, pToday->tm_sec, millisec );
	}
}

// double ELDecoder::DecodeGeoPosition(const int& i_nPosLatLong)
// {
// 	double dVal = 0.0;
// 	dVal = (double)i_nPosLatLong / (double)DEF_OF_RES_GEOPOS;
// 	return dVal;
// }

/**
 * @brief     기준 값의 문자열 테이블과 찾고자할 문자열과 비교하여 인덱스를 리턴한다.
 * @param     *pSearch 찾고자할 데이터 포인터
 * @param     *pRefTable 기준 테이블의 문자열 데이터 포인터
 * @param     nRef 기준 문자열 갯수
 * @return    int
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-08-10, 오후 2:58 
 * @warning   
 */
// int ELDecoder::GetComboValue( char *pSearch, const char **pRefTable, int nRef )
// {
// 	int iRet=0;
// 
// 	for( int i=0 ; i < nRef ; ++i ) {
// 		if( strcmp( pSearch, pRefTable[i] ) == 0 ) {
// 			iRet = i;
// 			break;
// 		}
// 	}
// 
// 	return iRet;
// }
