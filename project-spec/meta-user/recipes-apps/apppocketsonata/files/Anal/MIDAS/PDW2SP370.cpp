/**
 * @file      PDW2SP370.cpp
 * @brief     PDW 데이터를 SP-350 구조로 변환해주는 클래스
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-02-07, 오후 2:48 
 * @warning   
 */

#include "stdafx.h"

#include <stdio.h>
#include <string.h>

#ifdef __linux__
#include <sys/types.h>
#include <unistd.h>

#include "../Anal/SigAnal/_Type.h"

#elif defined(__VXWORKS__)
#include <ioLib.h>

#elif _MSC_VER

#else
#include <io.h>

#endif



#define UDIV( A, B )            (unsigned int) ( (float) (A) / (float) (B) + 0.5 )

#include "PDW2SP370.h"


#include "ELDecoder.h"


/**
 * @brief     초기화 처리
 * @param     void
 * @return    void
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-02-07, 오후 2:49 
 * @warning   
 */
CPDW2SP370::CPDW2SP370(void)
{

	Init();

}


/**
 * @brief     메모리 해지 처리한다.
 * @param     void
 * @return    void
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-02-07, 오후 3:00 
 * @warning   
 */
CPDW2SP370::~CPDW2SP370(void)
{
}

/**
 * @brief     Init
 * @param     void
 * @return    void
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-02-07, 오후 3:00 
 * @warning   
 */
void CPDW2SP370::Init(void)
{
	m_nPDWWord = 0;
	memset( & m_stPDWHeader, 0 , sizeof(SELSP350_PDWHEADER ) );

	memset( & m_stPDWWord, 0 , sizeof(SELSP350_PDWWORDS ) );
	
}

/**
 * @brief     SP-350 변환시 PDW 헤더를 저장한다.
 * @param     void
 * @return    bool
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-02-07, 오후 3:10 
 * @warning   
 */
bool CPDW2SP370::MakeHeader(void)
{
	int length, index;
	char strUnicode[256]={0,};

#if defined(__linux__) || defined(__VXWORKS__)
    strcpy_s( & m_stPDWHeader.szMasterLibraryName[0], LIBRARY_NAME );
#else
    strcpy_s( & m_stPDWHeader.szMasterLibraryName[0], sizeof(m_stPDWHeader.szMasterLibraryName), LIBRARY_NAME );
#endif

#ifndef __VXWORKS__
	//pMultibyte = ConvertUnicodeToMultibyte( strUnicode );
	//int len=MultiByteToWideChar( CP_ACP, 0, m_stPDWHeader.szMasterLibraryName, strlen(m_stPDWHeader.szMasterLibraryName), NULL, NULL );
	//MultiByteToWideChar( CP_ACP, 0, m_stPDWHeader.szMasterLibraryName, strlen(m_stPDWHeader.szMasterLibraryName), strUnicode, len );

	//strcpy_s( & m_stPDWHeader.szMasterLibraryName[0], sizeof(m_stPDWHeader.szMasterLibraryName), LIBRARY_NAME );
	memcpy( & m_stPDWHeader.szMasterLibraryName[0], strUnicode, strlen(strUnicode)*2 );
	index = (int) strlen(strUnicode)*2;
	length = sizeof(m_stPDWHeader.szMasterLibraryName) - index;
	memset( & m_stPDWHeader.szMasterLibraryName[index], 0, (size_t) length );
#endif
	
	m_stPDWHeader.ucIndexOffsetInBytes = 8;

	return true;
}

/**
 * @brief     PDW 데이터를 변환한다.
 * @param     int nPDW
 * @return    bool
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-02-07, 오후 3:10 
 * @warning   
 */
bool CPDW2SP370::TransferPDW2SP370( SRxPDWDataRGroup *pS_EL_PDW_DATA, int iRecords )
{
	int i, iFreq;
	unsigned int uiAoa;
	double dToa, dPa, dAoa, dPw;
	SELSP350_PDWWORDS *pstPDWWord;

	pstPDWWord = & m_stPDWWord[0];
	for( i=0 ; i < iRecords ; ++i ) {
		AllEndian64( & pS_EL_PDW_DATA->ullTOA, sizeof(long long int) );
		AllEndian32( & pS_EL_PDW_DATA->uiPulseType, sizeof(SRxPDWDataRGroup)- sizeof(long long int) );

		memset( pstPDWWord, 0, sizeof(SELSP350_PDWWORDS) );

		// 1번째 Phase
		dToa = ELDecoder::DecodeToa( pS_EL_PDW_DATA->ullTOA );			// ns 단위로 변경
		pstPDWWord->x.usTOA = UDIV( dToa, 12.5 );

		// 2번째 Phase
		dPa = ELDecoder::DecodeGainPA( (int) pS_EL_PDW_DATA->uiPA );			// ns 단위로 변경
		//iPa = UDIV( ( 0xFF * pS_EL_PDW_DATA->iPA ), 440 );
		pstPDWWord->x.ucAmp = UDIV( dPa, 0.34 );

		dAoa = ELDecoder::DecodeAOA( pS_EL_PDW_DATA->uiDirection );	// 도 단위로 변경
		//iAoa = UDIV( ( 0x7FF * pS_EL_PDW_DATA->iDirection ), 3600 );
		uiAoa = UDIV( dAoa, 0.08789 );
		pstPDWWord->x.uiHighAOA = uiAoa >> 5;
		pstPDWWord->x.uiLowAOA = uiAoa & (unsigned int) 0x0FF;
		pstPDWWord->x.uiAOAInvalid = pS_EL_PDW_DATA->uiDirectionVaild;

		pstPDWWord->x.usPOPPedFlag = _INVALID;
		pstPDWWord->x.usPOPFlag = _INVALID;
		pstPDWWord->x.usPMOPFlag = pS_EL_PDW_DATA->uiPMOPFlag;
		pstPDWWord->x._notused1 = 0;
		pstPDWWord->x._notused2 = 0;
		pstPDWWord->x._notused3 = 0;

		// 3번째 Phase
		pstPDWWord->x.usFreq = (unsigned short) ( pS_EL_PDW_DATA->uiFreq / (unsigned int) 100 );
		iFreq = (int) pS_EL_PDW_DATA->uiFreq - (int) ( ( pS_EL_PDW_DATA->uiFreq / 100 ) * 100 );
		pstPDWWord->x.usFreqFraction = UDIV( iFreq, 3.90625 );

		pstPDWWord->x.usSignalCenterStatus = _VALID;
		pstPDWWord->x.usIFMValid = _VALID;
		pstPDWWord->x._notused4 = _INVALID;
		pstPDWWord->x.usPulseSource = 0x14;

		// 4번째 Phase
		pstPDWWord->x.usCW = ( pS_EL_PDW_DATA->uiPulseType == (unsigned int) E_PDW_SIGNAL_CW ? (unsigned int) 1 : (unsigned int) 0 );
		dPw = ELDecoder::DecodePW2( (int) pS_EL_PDW_DATA->uiPW );	// 도 단위로 변경
		pstPDWWord->x.usPW = UDIV( dPw*1000., 40 );
		//pstPDWWord->x.usPW = pS_EL_PDW_DATA->iPW;

		pstPDWWord->x.usHighFMOP = 0;			
		pstPDWWord->x.usLowFMOP = 0;

		AllEndian32( pstPDWWord, sizeof(SELSP350_PDWWORDS) );

		++ pstPDWWord;

		++ pS_EL_PDW_DATA;
	}
	return true;
}

