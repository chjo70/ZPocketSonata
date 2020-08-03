//#include "StdAfx.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

#define _MAIN_

#include "../../Include/system.h"

#include "DataFile.h"



//#include "../Log/LogDebug.h"

#include "CRWRCommonVariables.h"

static int stDataFile;

const char stDV[2] = { ' ', '*' } ;

#define	RAD2DEG			(180./M_PI)		// 57.295779513082320876798154814114

//////////////////////////////////////////////////////////////////////////

CPDW::CPDW(STR_RAWDATA *pRawData) : CData(pRawData )
{

}

CPDW::~CPDW(void)
{

}

void CPDW::Alloc()
{
	m_PDWData.pfFreq = (float *)malloc(sizeof(float) * m_pRawData->uiDataItems);
	m_PDWData.pfPW = (float *)malloc(sizeof(float) * m_pRawData->uiDataItems);
	m_PDWData.pfAOA = (float *)malloc(sizeof(float) * m_pRawData->uiDataItems);
	m_PDWData.pfTOA = (float *)malloc(sizeof(float) * m_pRawData->uiDataItems);
	m_PDWData.pfDTOA = (float *)malloc(sizeof(float) * m_pRawData->uiDataItems);
	m_PDWData.pfPA = (float *)malloc(sizeof(float) * m_pRawData->uiDataItems);
	m_PDWData.pfllTOA = (_TOA *)malloc(sizeof(_TOA) * m_pRawData->uiDataItems);

	m_PDWData.pcType = (char *)malloc(sizeof(char) * m_pRawData->uiDataItems);
	m_PDWData.pcDV = (char *)malloc(sizeof(char) * m_pRawData->uiDataItems);
}

void CPDW::Free()
{
	free(m_PDWData.pfFreq);
	free(m_PDWData.pfPW);
	free(m_PDWData.pfAOA);
	free(m_PDWData.pfTOA);
	free(m_PDWData.pfDTOA);
	free(m_PDWData.pfPA);

	free( m_PDWData.pfllTOA );

	free(m_PDWData.pcType);
	free(m_PDWData.pcDV);

}

void *CPDW::GetData()
{
	return & m_PDWData;
}

/**
  * @brief		
  * @return 	void
  * @date       2019/06/07 10:10
*/
void CPDW::ConvertArray()
{
	UINT i;

	float *pfFreq = m_PDWData.pfFreq;
	float *pfPW = m_PDWData.pfPW;
	float *pfAOA = m_PDWData.pfAOA;
	float *pfTOA = m_PDWData.pfTOA;
	float *pfDTOA = m_PDWData.pfDTOA;
	float *pfPA = m_PDWData.pfPA;
	_TOA *pfllTOA = m_PDWData.pfllTOA;

	char *pcType = m_PDWData.pcType;
	char *pcDV = m_PDWData.pcDV;

	UINT uiToa, preToa, uiDToa;
	UINT uiTemp;

	TNEW_PDW temp;

	TNEW_PDW *pPDW = (TNEW_PDW *)gstpRawDataBuffer;

	m_bPhaseData = false;

	_spOneSec = 20000000.;
	_spOneMilli = FDIV( _spOneSec, 1000. );
	_spOneMicrosec = FDIV( _spOneMilli, 1000. );
	_spOneNanosec = FDIV( _spOneMicrosec, 1000. );

	_spAOAres = (float) ( 0.351562 );
	_spAMPres = (float) (0.351562);
	_spPWres = _spOneMicrosec;

	for (i = 0; i < m_pRawData->uiDataItems; ++i) {
		temp.bpdw[0][0] = pPDW->item.toa_1;
		temp.bpdw[0][1] = pPDW->item.toa_2;
		temp.bpdw[0][2] = pPDW->item.toa_3;
		temp.bpdw[0][3] = pPDW->item.toa_4;

		uiToa = temp.wpdw[0];
		*pfTOA = FDIV(uiToa, _spOneMicrosec );

		if (i == 0) {
			*pfDTOA = 0;
			preToa = uiToa;
		}
		else {
			uiDToa = uiToa - preToa;
			*pfDTOA = FDIV( uiDToa, _spOneMicrosec );
			preToa = uiToa;
		}

		*pfllTOA = uiToa;


		uiTemp = BIT_MERGE(pPDW->item.frequency_h, pPDW->item.frequency_l);
		*pfFreq = FFRQCNV(pPDW->item.band + 1, uiTemp);

		uiTemp = BIT_MERGE(pPDW->item.pulse_width_h, pPDW->item.pulse_width_l);
		*pfPW = FPWCNV(uiTemp);

		uiTemp = BIT_MERGE(pPDW->item.direction_h, pPDW->item.direction_l);
		*pfAOA = FAOACNV(uiTemp);

		uiTemp = pPDW->item.amplitude;
		*pfPA = FPACNV(uiTemp);

		*pcType = pPDW->item.stat;
		*pcDV = pPDW->item.dv;

		// printf( "\n [%3d] 0x%02X %5.1f%1c[deg] %8.2f[MHz] %10.3f[us] %8.3f[ns]" , i+1, *pcType, *pfAOA, stDV[*pcDV], *pfFreq, *pfTOA, *pfPW );

		++pfFreq;
		++pfAOA;
		++pfPW;
		++pfPA;
		++pfTOA;
		++pfDTOA;
		++pcType;
		++pcDV;

		++ pfllTOA;

		++pPDW;
	}
}

//////////////////////////////////////////////////////////////////////////
CEPDW::CEPDW(STR_RAWDATA *pRawData, STR_FILTER_SETUP *pstFilterSetup ) : CData(pRawData )
{
	STR_PDWDATA *pPDWData;
 
 	if( pRawData->uiByte == (sizeof(STR_PDWDATA)-sizeof(pPDWData->stPDW) ) + sizeof(_PDW)*pRawData->uiDataItems ) {
 		m_bPhaseData = true;
 	}
	else {
		m_bPhaseData = false;
	}

	if( pstFilterSetup != NULL ) {
		memcpy( & m_stFilterSetup, pstFilterSetup, sizeof(STR_FILTER_SETUP) );
	}

}

CEPDW::~CEPDW(void)
{

}

void CEPDW::Alloc()
{
	m_PDWData.pfFreq = (float *)malloc(sizeof(float) * m_pRawData->uiDataItems);
	m_PDWData.pfPW = (float *)malloc(sizeof(float) * m_pRawData->uiDataItems);
	m_PDWData.pfAOA = (float *)malloc(sizeof(float) * m_pRawData->uiDataItems);
	m_PDWData.pfTOA = (float *)malloc(sizeof(float) * m_pRawData->uiDataItems);
	m_PDWData.pfDTOA = (float *)malloc(sizeof(float) * m_pRawData->uiDataItems);
	m_PDWData.pfPA = (float *)malloc(sizeof(float) * m_pRawData->uiDataItems);
	m_PDWData.pfllTOA = (_TOA *)malloc(sizeof(_TOA) * m_pRawData->uiDataItems);

	m_PDWData.pcType = (char *)malloc(sizeof(char) * m_pRawData->uiDataItems);
	m_PDWData.pcDV = (char *)malloc(sizeof(char) * m_pRawData->uiDataItems);

	m_PDWData.pfPh1 = (float *)malloc(sizeof(float) * m_pRawData->uiDataItems);
	m_PDWData.pfPh2 = (float *)malloc(sizeof(float) * m_pRawData->uiDataItems);
	m_PDWData.pfPh3 = (float *)malloc(sizeof(float) * m_pRawData->uiDataItems);
	m_PDWData.pfPh4 = (float *)malloc(sizeof(float) * m_pRawData->uiDataItems);

}

void CEPDW::Free()
{
	free(m_PDWData.pfFreq);
	free(m_PDWData.pfPW);
	free(m_PDWData.pfAOA);
	free(m_PDWData.pfTOA);
	free(m_PDWData.pfDTOA);
	free(m_PDWData.pfPA);

	free( m_PDWData.pfllTOA );

	free(m_PDWData.pcType);
	free(m_PDWData.pcDV);

	free( m_PDWData.pfPh1 );
	free( m_PDWData.pfPh2 );
	free( m_PDWData.pfPh3 );
	free( m_PDWData.pfPh4 );

}

void *CEPDW::GetData()
{
	return & m_PDWData;
}

/**
  * @brief		
  * @return 	void
  * @date       2019/06/07 10:10
*/
void CEPDW::ConvertArray()
{
	UINT i, uiDataItems;

	float *pfFreq = m_PDWData.pfFreq;
	float *pfPW = m_PDWData.pfPW;
	float *pfAOA = m_PDWData.pfAOA;
	float *pfTOA = m_PDWData.pfTOA;
	float *pfDTOA = m_PDWData.pfDTOA;
	float *pfPA = m_PDWData.pfPA;
	_TOA *pfllTOA = m_PDWData.pfllTOA;

	float *pfPh1 = m_PDWData.pfPh1;
	float *pfPh2 = m_PDWData.pfPh2;
	float *pfPh3 = m_PDWData.pfPh3;
	float *pfPh4 = m_PDWData.pfPh4;

	char *pcType = m_PDWData.pcType;
	char *pcDV = m_PDWData.pcDV;

	_TOA uiToa, firstToa, preToa;

	STR_PDWDATA *pPDWData = (STR_PDWDATA *) gstpRawDataBuffer;
	_PDW *pPDW = (_PDW *) pPDWData->stPDW;

	_spOneSec = FDIV( 1000000000, _toaRes[pPDWData->enBandWidth] );
	_spOneMilli = FDIV( 1000000, _toaRes[pPDWData->enBandWidth] );
	_spOneMicrosec = FDIV( 1000, _toaRes[pPDWData->enBandWidth] );
	_spOneNanosec = FDIV( 1, _toaRes[pPDWData->enBandWidth] );

	_spAMPres = (float) (0.25);
	_spPWres = _spOneMicrosec;

	for (i = uiDataItems = 0; i < m_pRawData->uiDataItems ; ++i ) {
		if (i == 0) {
			if( pPDWData->iIsStorePDW == 1 ) {
				firstToa = pPDW->llTOA;
			}
			else {
				firstToa = 0;
			}

			*pfDTOA = 0;
			*pfTOA = 0;
			preToa = 0; // pPDW->llTOA;
		}
		else {
			uiToa = pPDW->llTOA - firstToa;
			*pfTOA = FDIV(uiToa, _spOneMicrosec );

			*pfDTOA = (float) ( uiToa - preToa );
			*pfDTOA = FDIV(*pfDTOA, _spOneMicrosec );
			preToa = pPDW->llTOA - firstToa;
		}

		*pfllTOA = pPDW->llTOA;

		*pfFreq = F_FRQMhzCNV( 0, pPDW->iFreq );	//FFRQCNV(pPDW->item.band + 1, uiTemp);

		*pfPW = PWCNV(pPDW->iPW * 1000. );

		if( pPDW->iAOA == 0 ) {
			*pfAOA = (float) 0.00000001;
		}
		else {
			*pfAOA = AOACNV( pPDW->iAOA );
		}

		*pfPA = PACNV(pPDW->iPA);

		if( pPDW->iPulseType == 0 ) {
			*pcType = PDW_CW;
		}
		else {
			*pcType = PDW_NORMAL;
		}

		*pcDV = PDW_DV;

		if( m_bPhaseData == true ) {
			*pfPh1 = pPDW->fPh1;
			*pfPh2 = pPDW->fPh2;
			*pfPh3 = pPDW->fPh3;
			*pfPh4 = pPDW->fPh4;
		}

		printf( "\n [%3d] 0x%02X %5.1f%1c[deg] %8.2f[kHz] %10.3f[us] %8.3f[ns]" , i+1, *pcType, *pfAOA, stDV[*pcDV], *pfFreq, *pfTOA, *pfPW );

		if( ( (double) *pfAOA >= m_stFilterSetup.dAoaMin && (double) *pfAOA <= m_stFilterSetup.dAoaMax ) &&
			( (double) *pfFreq >= m_stFilterSetup.dFrqMin && (double) *pfFreq <= m_stFilterSetup.dFrqMax ) ) {
			++pfFreq;
			++pfAOA;
			++pfPW;
			++pfPA;
			++pfTOA;
			++pfDTOA;
			++pcType;
			++pcDV;

			++ pfllTOA;

			if( m_bPhaseData == true ) {
				++ pfPh1;
				++ pfPh2;
				++ pfPh3;
				++ pfPh4;
			}

			++ uiDataItems;
		}

		if( m_bPhaseData == true ) {
			++ pPDW;
		}
		else {
			char *pByte;

			++ pPDW;
			pByte = (char *) pPDW;
			pByte = pByte - (sizeof(float)*4);
			pPDW = ( _PDW * ) pByte;
		}
	}

	m_pRawData->uiDataItems = uiDataItems;
}

//////////////////////////////////////////////////////////////////////////
CSPDW::CSPDW(STR_RAWDATA *pRawData) : CData(pRawData )
{

}

/**
 * @brief     
 * @param     void
 * @return    
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/02/27 21:41:39
 * @warning   
 */
CSPDW::~CSPDW(void)
{

}

void CSPDW::Alloc()
{
	m_PDWData.pfFreq = (float *)malloc(sizeof(float) * m_pRawData->uiDataItems);
	m_PDWData.pfPW = (float *)malloc(sizeof(float) * m_pRawData->uiDataItems);
	m_PDWData.pfAOA = (float *)malloc(sizeof(float) * m_pRawData->uiDataItems);
	m_PDWData.pfTOA = (float *)malloc(sizeof(float) * m_pRawData->uiDataItems);
	m_PDWData.pfDTOA = (float *)malloc(sizeof(float) * m_pRawData->uiDataItems);
	m_PDWData.pfPA = (float *)malloc(sizeof(float) * m_pRawData->uiDataItems);

	m_PDWData.pcType = (char *)malloc(sizeof(char) * m_pRawData->uiDataItems);
	m_PDWData.pcDV = (char *)malloc(sizeof(char) * m_pRawData->uiDataItems);
}

/**
 * @brief     
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/02/27 21:41:58
 * @warning   
 */
void CSPDW::Free()
{
	free(m_PDWData.pfFreq);
	free(m_PDWData.pfPW);
	free(m_PDWData.pfAOA);
	free(m_PDWData.pfTOA);
	free(m_PDWData.pfDTOA);
	free(m_PDWData.pfPA);

	free(m_PDWData.pcType);
	free(m_PDWData.pcDV);

}

/**
 * @brief     
 * @return    void *
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/02/27 21:41:55
 * @warning   
 */
void *CSPDW::GetData()
{
	return & m_PDWData;
}

/**
  * @brief		
  * @return 	void
  * @date       2019/06/07 10:10
*/
void CSPDW::ConvertArray()
{
	UINT i;

	float *pfFreq = m_PDWData.pfFreq;
	float *pfPW = m_PDWData.pfPW;
	float *pfAOA = m_PDWData.pfAOA;
	float *pfTOA = m_PDWData.pfTOA;
	float *pfDTOA = m_PDWData.pfDTOA;
	float *pfPA = m_PDWData.pfPA;

	char *pcType = m_PDWData.pcType;
	char *pcDV = m_PDWData.pcDV;

	float fToa, /* firstToa, */ preToa;

	TNEW_SPDW *pPDW = (TNEW_SPDW *) gstpRawDataBuffer;

	_spOneSec = 20000000.;
	_spOneMilli = FDIV( _spOneSec, 1000. );
	_spOneMicrosec = FDIV( _spOneMilli, 1000. );
	_spOneNanosec = FDIV( _spOneMicrosec, 1000. );

	_spAOAres = (float) ( 0.351562 );
	_spAMPres = (float) (0.351562);
	_spPWres = _spOneMicrosec;

	for (i = 0; i < m_pRawData->uiDataItems; ++i) {

		if (i == 0) {
			//firstToa = pPDW->TOA;
			*pfTOA = FDIV( ( pPDW->TOA * 20 ), 1000. );
			*pfDTOA = 0;
			preToa = FDIV( ( pPDW->TOA * 20 ), 1000. );
		}
		else {
			fToa = (float) pPDW->TOA; // - firstToa;
			//*pfTOA = ( fToa * 20. ) / 1000.;
			//*pfTOA = ( fToa * 4 * 100 );
			*pfTOA = FDIV( ( fToa * 20 ), 1000. );

			*pfDTOA = ( *pfTOA - preToa );

			preToa = *pfTOA;
		}

		*pfFreq = pPDW->Freq;

		*pfPW = FDIV( pPDW->PW, 1000. );

		*pfAOA = 90.0;

		*pfPA = pPDW->PA;

		*pcType = 0;
		*pcDV = 1;

		// printf( "\n [%3d] 0x%02X %5.1f%1c[deg] %8.2f[MHz] %10.3f[us] %8.3f[ns]" , i+1, *pcType, *pfAOA, stDV[*pcDV], *pfFreq, *pfTOA, *pfPW );

		++pfFreq;
		++pfAOA;
		++pfPW;
		++pfPA;
		++pfTOA;
		++pfDTOA;
		++pcType;
		++pcDV;

		++pPDW;
	}
}

//////////////////////////////////////////////////////////////////////////
CKFXPDW::CKFXPDW(STR_RAWDATA *pRawData, STR_FILTER_SETUP *pstFilterSetup ) : CData(pRawData )
{
	m_bPhaseData = false;
}

/**
 * @brief     
 * @param     void
 * @return    
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/02/27 21:41:39
 * @warning   
 */
CKFXPDW::~CKFXPDW(void)
{

}

/**
 * @brief     
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/02/27 21:44:02
 * @warning   
 */
void CKFXPDW::Alloc()
{
	m_PDWData.pfFreq = (float *)malloc(sizeof(float) * m_pRawData->uiDataItems);
	m_PDWData.pfPW = (float *)malloc(sizeof(float) * m_pRawData->uiDataItems);
	m_PDWData.pfAOA = (float *)malloc(sizeof(float) * m_pRawData->uiDataItems);
	m_PDWData.pfTOA = (float *)malloc(sizeof(float) * m_pRawData->uiDataItems);
	m_PDWData.pfDTOA = (float *)malloc(sizeof(float) * m_pRawData->uiDataItems);
	m_PDWData.pfPA = (float *)malloc(sizeof(float) * m_pRawData->uiDataItems);
	m_PDWData.pfllTOA = (_TOA *)malloc(sizeof(_TOA) * m_pRawData->uiDataItems);

	m_PDWData.pcType = (char *)malloc(sizeof(char) * m_pRawData->uiDataItems);
	m_PDWData.pcDV = (char *)malloc(sizeof(char) * m_pRawData->uiDataItems);
}

/**
 * @brief     
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/02/27 21:41:58
 * @warning   
 */
void CKFXPDW::Free()
{
	free(m_PDWData.pfFreq);
	free(m_PDWData.pfPW);
	free(m_PDWData.pfAOA);
	free(m_PDWData.pfTOA);
	free(m_PDWData.pfDTOA);
	free(m_PDWData.pfPA);
	free(m_PDWData.pfllTOA);

	free(m_PDWData.pcType);
	free(m_PDWData.pcDV);

}

/**
 * @brief     
 * @return    void *
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/02/27 21:41:55
 * @warning   
 */
void *CKFXPDW::GetData()
{
	return & m_PDWData;
}

/**
  * @brief		
  * @return 	void
  * @date       2019/06/07 10:10
*/
void CKFXPDW::ConvertArray()
{
	UINT i;

	float *pfFreq = m_PDWData.pfFreq;
	float *pfPW = m_PDWData.pfPW;
	float *pfAOA = m_PDWData.pfAOA;
	float *pfTOA = m_PDWData.pfTOA;
	float *pfDTOA = m_PDWData.pfDTOA;
	float *pfPA = m_PDWData.pfPA;

	char *pcType = m_PDWData.pcType;
	char *pcDV = m_PDWData.pcDV;

	_TOA *pfllTOA = m_PDWData.pfllTOA;

	float /*fToa*/ /* firstToa, */ preToa;

	_TOA llToa, ll1stToa;
	UDRCPDW *pPDW = (UDRCPDW *) & gstpRawDataBuffer[sizeof(STR_PDWFILE_HEADER)];

	_spOneSec = 20000000.;
	_spOneMilli = FDIV( _spOneSec, 1000. );
	_spOneMicrosec = FDIV( _spOneMilli, 1000. );
	_spOneNanosec = FDIV( _spOneMicrosec, 1000. );

	_spAOAres = (float) ( 0.351562 );
	_spAMPres = (float) (0.351562);
	_spPWres = _spOneMicrosec;

	for (i = 0; i < m_pRawData->uiDataItems; ++i) {
		llToa = (_TOA) ( pPDW->sPDWFormat.m_LSBTOA ) | ( (_TOA) pPDW->sPDWFormat.m_MSBTOA << 32 );
		*pfllTOA = llToa;
 		if (i == 0) {
			ll1stToa = llToa;
 			*pfTOA = DecodeTOA( llToa-ll1stToa );
 			*pfDTOA = 0;
 			preToa = *pfTOA;
 		}
 		else {
			*pfTOA = DecodeTOA( llToa-ll1stToa );

 			*pfDTOA = ( *pfTOA - preToa );
 
 			preToa = *pfTOA;
 		}

		*pfFreq = DecodeFREQ( pPDW->sPDWFormat.m_freq );		// MHz
 
 		*pfPW = DecodePW( pPDW->sPDWFormat.m_PW );

 		*pfAOA = DecodeDOA( pPDW->sPDWFormat.m_DOA );

 		*pfPA = DecodePA( pPDW->sPDWFormat.m_PA );
 
 		*pcType = 0; // pPDW->sPDWFormat.m_sigType;

 		*pcDV = pPDW->sPDWFormat.m_DI;

        //printf( "\n [%3d] 0x%02X %5.1f%1c[deg] %8.2f[MHz] %10.3f[us] %8.3f[ns]" , i+1, *pcType, *pfAOA, stDV[*pcDV], *pfFreq, *pfTOA, *pfPW );

		++pfFreq;
		++pfAOA;
		++pfPW;
		++pfPA;
		++pfTOA;
		++pfDTOA;
		++pcType;
		++pcDV;
		++pfllTOA;

		++pPDW;
	}
}

//////////////////////////////////////////////////////////////////////////
C7PDW::C7PDW(STR_RAWDATA *pRawData, STR_FILTER_SETUP *pstFilterSetup ) : CData(pRawData )
{
	m_bPhaseData = false;
}

/**
 * @brief     
 * @param     void
 * @return    
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/02/27 21:41:39
 * @warning   
 */
C7PDW::~C7PDW(void)
{

}

/**
 * @brief     
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/02/27 21:44:02
 * @warning   
 */
void C7PDW::Alloc()
{
	m_PDWData.pfFreq = (float *)malloc(sizeof(float) * m_pRawData->uiDataItems);
	m_PDWData.pfPW = (float *)malloc(sizeof(float) * m_pRawData->uiDataItems);
	m_PDWData.pfAOA = (float *)malloc(sizeof(float) * m_pRawData->uiDataItems);
	m_PDWData.pfTOA = (float *)malloc(sizeof(float) * m_pRawData->uiDataItems);
	m_PDWData.pfDTOA = (float *)malloc(sizeof(float) * m_pRawData->uiDataItems);
	m_PDWData.pfPA = (float *)malloc(sizeof(float) * m_pRawData->uiDataItems);
	m_PDWData.pfllTOA = (_TOA *)malloc(sizeof(_TOA) * m_pRawData->uiDataItems);

	m_PDWData.pcType = (char *)malloc(sizeof(char) * m_pRawData->uiDataItems);
	m_PDWData.pcDV = (char *)malloc(sizeof(char) * m_pRawData->uiDataItems);
}

/**
 * @brief     
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/02/27 21:41:58
 * @warning   
 */
void C7PDW::Free()
{
	free(m_PDWData.pfFreq);
	free(m_PDWData.pfPW);
	free(m_PDWData.pfAOA);
	free(m_PDWData.pfTOA);
	free(m_PDWData.pfDTOA);
	free(m_PDWData.pfPA);
	free(m_PDWData.pfllTOA);

	free(m_PDWData.pcType);
	free(m_PDWData.pcDV);

}

/**
 * @brief     
 * @return    void *
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/02/27 21:41:55
 * @warning   
 */
void *C7PDW::GetData()
{
	return & m_PDWData;
}

/**
  * @brief		
  * @return 	void
  * @date       2019/06/07 10:10
*/
void C7PDW::ConvertArray()
{
	UINT i;

	float *pfFreq = m_PDWData.pfFreq;
	float *pfPW = m_PDWData.pfPW;
	float *pfAOA = m_PDWData.pfAOA;
	float *pfTOA = m_PDWData.pfTOA;
	float *pfDTOA = m_PDWData.pfDTOA;
	float *pfPA = m_PDWData.pfPA;

	char *pcType = m_PDWData.pcType;
	char *pcDV = m_PDWData.pcDV;

	float /*fToa*/ /* firstToa, */ preToa;

	SRXPDWDataRGroup *pPDW = (SRXPDWDataRGroup *) & gstpRawDataBuffer[sizeof(SRxPDWHeader)];

	_spOneSec = 20000000.;
	_spOneMilli = FDIV( _spOneSec, 1000. );
	_spOneMicrosec = FDIV( _spOneMilli, 1000. );
	_spOneNanosec = FDIV( _spOneMicrosec, 1000. );

	_spAOAres = (float) ( 0.351562 );
	_spAMPres = (float) (0.351562);
	_spPWres = _spOneMicrosec;

	for (i = 0; i < m_pRawData->uiDataItems; ++i) {
		swapByteOrder( pPDW->llTOA );
		AllSwapData32( & pPDW->iSignalType, sizeof(SRXPDWDataRGroup)- sizeof(long long int) );

 		if (i == 0) {
// 			//firstToa = pPDW->TOA;
 			*pfTOA = FDIV( pPDW->llTOA, 1000.0 );
 			*pfDTOA = 0;
 			preToa = *pfTOA;
 		}
 		else {
// 			fToa = (float) pPDW->TOA; // - firstToa;
			*pfTOA = FDIV( pPDW->llTOA, 1000.0 );

 			*pfDTOA = ( *pfTOA - preToa );
 
 			preToa = *pfTOA;
 		}

		*pfFreq = FMUL( pPDW->iFreq, 0.010 );		// MHz
 
 		*pfPW = FMUL( pPDW->iPW, 6.48824 );

 		*pfAOA = FMUL( pPDW->iDirection, 0.1 );

 		*pfPA = FMUL( pPDW->iPA, 0.25 ) - (float) 110.;
 
 		*pcType = pPDW->iSignalType;

 		*pcDV = pPDW->iDirectionVaild ^ 1;

		// printf( "\n [%3d] 0x%02X %5.1f%1c[deg] %8.2f[MHz] %10.3f[us] %8.3f[ns]" , i+1, *pcType, *pfAOA, stDV[*pcDV], *pfFreq, *pfTOA, *pfPW );

		++pfFreq;
		++pfAOA;
		++pfPW;
		++pfPA;
		++pfTOA;
		++pfDTOA;
		++pcType;
		++pcDV;

		++pPDW;
	}
}


//////////////////////////////////////////////////////////////////////////
//

CIQ::CIQ(STR_RAWDATA *pRawData) : CData(pRawData )
{

}

/**
 * @brief     
 * @param     void
 * @return    
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/02/27 21:44:06
 * @warning   
 */
CIQ::~CIQ(void)
{

}


/**
 * @brief     
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/02/27 21:44:08
 * @warning   
 */
void CIQ::Alloc()
{
	m_IQData.pfI = (float *)malloc( sizeof(float) * m_pRawData->uiDataItems);
	m_IQData.pfQ = (float *)malloc( sizeof(float) * m_pRawData->uiDataItems);
	m_IQData.pfPA = (float *)malloc( sizeof(float) * m_pRawData->uiDataItems);
	m_IQData.pfIP = (float *)malloc( sizeof(float) * m_pRawData->uiDataItems);
	m_IQData.pfFFT = (float *)malloc( sizeof(float) * m_pRawData->uiDataItems);
	
}

/**
 * @brief     
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/02/27 21:44:09
 * @warning   
 */
void CIQ::Free()
{
	free(m_IQData.pfI);
	free(m_IQData.pfQ);
	free(m_IQData.pfPA);
	free(m_IQData.pfIP);
	free(m_IQData.pfFFT);
}

/**
 * @brief     
 * @return    void *
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/02/27 21:44:12
 * @warning   
 */
void *CIQ::GetData()
{
	return & m_IQData;
}

/**
  * @brief		IQ 데이터 구조에 저장한다.
  * @return 	void
  * @date       2019/06/07 10:11
*/
void CIQ::ConvertArray()
{
	UINT i;

	float *psI = m_IQData.pfI;
	float *psQ = m_IQData.pfQ;
	float *psPA = m_IQData.pfPA;
	float *psIP = m_IQData.pfIP;
	float *psFFT = m_IQData.pfFFT;

	float fVal1, fVal2;

	TNEW_IQ *pIQ = (TNEW_IQ *) gstpRawDataBuffer;

	for (i = 0; i < m_pRawData->uiDataItems; ++i) {
		*psI = (float) pIQ->sI;
		*psQ = (float) pIQ->sQ;

		// 순시 진폭
		*psPA = sqrt( *psI * *psI + *psQ * *psQ );
		*psPA = (float) (20.*log10( *psPA ) ) - (float) 80.;

		// 순시 위상차
		if( i == 0 ) {
			*psIP = 0.0;
			fVal2 = (float) ( atan2( *psQ, *psI ) * RAD2DEG );
		}
		else {
			fVal1 = (float) ( atan2( *psQ, *psI ) * RAD2DEG );
			*psIP = fVal1 - fVal2;
			fVal2 = fVal1;
		}
		if( *psIP > 180. ) {
			*psIP -= ( 2 * 180. );
		}
		else if( *psIP < -180 ) {
			*psIP += ( 2 * 180. );
		}
		else {

		}

		// printf( "\n [%3d] %10d %10d" , i+1, *psI, *psQ );

		++psI;
		++psQ;
		++psPA;
		++psIP;
		
		++pIQ;
	}

#ifdef _FFTW_
	fftw_complex *pIn, *pOut;
	fftw_complex *pP;
	fftw_plan plan;

	UINT N = m_pRawData->uiDataItems, nShift;

	pIn = ( fftw_complex * ) fftw_malloc( sizeof(fftw_complex) * N );
	pOut = ( fftw_complex * ) fftw_malloc( sizeof(fftw_complex) * N );
	plan = fftw_plan_dft_1d( N, pIn, pOut, FFTW_FORWARD, FFTW_ESTIMATE );

	psI = m_IQData.pfI;
	psQ = m_IQData.pfQ;

	pP = pIn;
	for( i=0 ; i < N ; ++i ) {
		pP[i][0] = *psI;
		pP[i][1] = *psQ;

		++ psI;
		++ psQ;
	}

	fftw_execute( plan );

	nShift = ( N / 2 );
	fftw_complex swap;
	for( i=0 ; i < (unsigned int) (N/2) ; ++i ) {
 		swap[0] = pOut[i][0];
 		swap[1] = pOut[i][1];
 
 		pOut[i][0] = pOut[nShift][0];
		pOut[i][1] = pOut[nShift][1];

		pOut[nShift][0] = swap[0];
		pOut[nShift][1] = swap[1];
 
 		++ nShift;
	}	

	for( i=0 ; i < N ; ++i ) {
		*psFFT = (float) sqrt( pOut[i][0] * pOut[i][0] + pOut[i][1] * pOut[i][1] );
		++ psFFT;

	}

	fftw_destroy_plan( plan );
	fftw_free( pIn );
	fftw_free( pOut );
#endif

}

//////////////////////////////////////////////////////////////////////////
/**
 * @brief     
 * @param     STR_RAWDATA * pRawData
 * @return    
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/02/27 21:44:19
 * @warning   
 */
CData::CData( STR_RAWDATA *pRawData )
{
	m_pRawData = pRawData;

	m_uiWindowNumber = 1;

	m_bPhaseData = true;

	m_stFilterSetup.dToaMin = -1.;
	m_stFilterSetup.dToaMax = -1.;
	m_stFilterSetup.dAoaMin = -360.;
	m_stFilterSetup.dAoaMax = 360.;
	m_stFilterSetup.dFrqMin = 500.;
	m_stFilterSetup.dFrqMax = 18000.;
	m_stFilterSetup.dPaMin = -100.;
	m_stFilterSetup.dPaMax = 10.;
}

/**
 * @brief     
 * @param     void
 * @return    
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/02/27 21:44:22
 * @warning   
 */
CData::~CData(void)
{
	//Free();
}



void CData::AllSwapData32( void *pData, int iLength )
{
	int i;
	UINT *pWord;

	pWord = (UINT *) pData;
	for( i=0 ; i < iLength ; i+=sizeof(int) ) {
		swapByteOrder( *pWord );
		++ pWord;
	}

}

void CData::swapByteOrder(unsigned long long& ull)
{
	ull = (ull >> 56) |
		((ull<<40) & 0x00FF000000000000) |
		((ull<<24) & 0x0000FF0000000000) |
		((ull<<8) & 0x000000FF00000000) |
		((ull>>8) & 0x00000000FF000000) |
		((ull>>24) & 0x0000000000FF0000) |
		((ull>>40) & 0x000000000000FF00) |
		(ull << 56);
}

void CData::swapByteOrder(unsigned int& ui) 
{
	ui = (ui >> 24) |
		((ui<<8) & 0x00FF0000) |
		((ui>>8) & 0x0000FF00) |
		(ui << 24);
}


//////////////////////////////////////////////////////////////////////////

/**
 * @brief     
 * @param     void
 * @return    
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/02/27 21:44:24
 * @warning   
 */
CDataFile::CDataFile(void)
{
	Alloc();

	++stDataFile;
}


/**
  * @brief		
  * @param		void
  * @return 	
  * @date       2019/05/31 10:43
*/
CDataFile::~CDataFile(void)
{
	--stDataFile;

	Free();

}

/**
  * @brief		
  * @return 	void
  * @date       2019/05/31 10:43
*/
void CDataFile::Alloc()
{
	if( gstpRawDataBuffer == NULL ) {
		gstpRawDataBuffer = (char *) malloc(sizeof(char)* MAX_RAWDATA_SIZE );
	}
}

void CDataFile::Free()
{
	if( gstpRawDataBuffer != NULL ) {
		//free( gstpRawDataBuffer );
		//gstpRawDataBuffer = NULL;
	}

	if (stDataFile == 0) {
		free(gstpRawDataBuffer);
		gstpRawDataBuffer = NULL;
	}

	//m_pData->Free();
	//delete m_pData;

}


/**
 * @brief     
 * @param     CString & strPathname
 * @param     void * pData
 * @param     int iNumData
 * @param     ENUM_UnitType enUnitType
 * @param     ENUM_DataType enDataType
 * @param     void * pDataEtc
 * @param     int iSizeOfEtc
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/03/04 14:09:35
 * @warning   
 */
void CDataFile::SaveDataFile( char *pstPathname, void *pData, int iNumData, ENUM_UnitType enUnitType, ENUM_DataType enDataType, void *pDataEtc, int iSizeOfEtc )
{
#ifdef _Winodws
	CFileException ex;

	if( enUnitType == en_SONATA || enUnitType == en_KFX ) {
		if( enDataType == en_PDW_DATA) {
			
			if( ! m_RawDataFile.Open( strPathname, CFile::modeWrite | CFile::shareExclusive | CFile::modeCreate, &ex ) ) {
				Log( enError, _T("PDW 데이터 파일[%s]을 생성하지 못합니다 !") , strPathname );
			}
			else {
				m_RawDataFile.Write( pData, iNumData );
				m_RawDataFile.Close();
			}
		}
		else if( enDataType == en_IQ_DATA ) {
			if( ! m_RawDataFile.Open( strPathname, CFile::modeWrite | CFile::shareExclusive | CFile::modeCreate, &ex ) ) {
				Log( enError, _T("IQ 데이터 파일[%s]을 생성하지 못합니다 !") , strPathname );
			}
			else {
				// IQ 헤더 정보 저장
				if( pDataEtc != NULL ) {
					m_RawDataFile.Write( pDataEtc, iSizeOfEtc );
				}

				m_RawDataFile.Write( pData, iNumData );
				m_RawDataFile.Close();
			}
		}
	}
#endif
}

/**
  * @brief		RAW 데이터 파일 읽기
  * @param		CString & strPathname
  * @return 	void
  * @return		성공시 true, 실패시 false
  * @date       2019/05/31 10:34
*/
void CDataFile::ReadDataFile( const char *pstPathname, STR_FILTER_SETUP *pstFilterSetup )
{
	bool bPDW=false, bSPDW=false, b7PDW=false, bIQ=false, bEPDW=false, bKFXPDW=false;

	m_pData = NULL;

    // strPathname.MakeLower();

#ifdef _MBCS
    const char *pch;

    if( NULL != strstr( pstPathname, _T(".pdw") ) || NULL != strstr( pstPathname, _T(".npw") ) ) {
		bPDW = true;
	}
    if( NULL != strstr( pstPathname, _T(".spdw") ) ) {
		bSPDW = true;
	}
    if( NULL != strstr( pstPathname, _T(".dat") ) ) {
		b7PDW = true;
	}
    if( NULL != strstr( pstPathname, _T(".kpdw" ) ) ) {
        bKFXPDW = true;
    }
    if( NULL != strstr( pstPathname, _T(".iq") ) || NULL != strstr( pstPathname, _T(".siq") ) ) {
		bIQ = true;
	}
    if( NULL != strstr( pstPathname, _T(".epdw") ) || NULL != strstr( pstPathname, _T(".enpw") ) ) {
		bEPDW = true;
	}
#else
    if( NULL != wcsstr( pstPathname, L".pdw" ) || NULL != wcsstr( pstPathname, L".npw" ) ) {
		bPDW = true;
	}
    if( NULL != wcsstr( pstPathname, L".spdw" ) ) {
		bSPDW = true;
	}
    if( NULL != wcsstr( pstPathname, L".dat" ) ) {
		b7PDW = true;
	}
    if( NULL != wcsstr( pstPathname, L".kpdw" ) ) {
		bKFXPDW = true;
	}
    if( NULL != wcsstr( pstPathname, L".iq" ) || NULL != wcsstr( pstPathname, L".siq" ) ) {
		bIQ = true;
	}
    if( NULL != wcsstr( pstPathname, L".epdw" ) || NULL != wcsstr( pstPathname, L".enpw" ) ) {
		bEPDW = true;
	}

#endif

	if( bPDW == true ) {
		m_RawData.enDataType = en_PDW_DATA;
		m_RawData.enUnitType = en_SONATA;

        if (m_RawDataFile.Open( pstPathname, CFile::shareDenyNone | CFile::typeBinary) == TRUE ) {
			m_RawData.uiByte = m_RawDataFile.Read( gstpRawDataBuffer, MAX_RAWDATA_SIZE );
			m_RawData.uiDataItems = m_RawData.uiByte / sizeof(TNEW_PDW);

			m_pData = new CPDW( & m_RawData );

			m_pData->Alloc();

			m_pData->ConvertArray();

			m_RawDataFile.Close();

		}
		else {
			m_RawData.uiByte = -1;
			m_RawData.uiDataItems = -1;
		}

	}

	else if( bSPDW == true ) {
		m_RawData.enDataType = en_PDW_DATA;
		m_RawData.enUnitType = en_SONATA;

        if (m_RawDataFile.Open( pstPathname, CFile::shareDenyNone | CFile::typeBinary) == TRUE) {
			m_RawData.uiByte = m_RawDataFile.Read( gstpRawDataBuffer, MAX_RAWDATA_SIZE );
			m_RawData.uiDataItems = m_RawData.uiByte / sizeof(TNEW_SPDW);

			m_pData = new CSPDW( & m_RawData );

			m_pData->Alloc();

			m_pData->ConvertArray();

			m_RawDataFile.Close();

		}
		else {
			m_RawData.uiByte = -1;
			m_RawData.uiDataItems = -1;
		}

	}

	else if( bEPDW == true ) {
		m_RawData.enDataType = en_PDW_DATA;
		m_RawData.enUnitType = en_ELINT;

        if (m_RawDataFile.Open( pstPathname, CFile::shareDenyNone | CFile::typeBinary) == TRUE) {
			STR_PDWDATA *pPDWData;

			m_RawData.uiByte = m_RawDataFile.Read( gstpRawDataBuffer, MAX_RAWDATA_SIZE );
			pPDWData = ( STR_PDWDATA * ) gstpRawDataBuffer;
			m_RawData.uiDataItems = pPDWData->count;

			m_pData = new CEPDW( & m_RawData, pstFilterSetup );

			m_pData->Alloc();

			m_pData->ConvertArray();

			m_RawDataFile.Close();

		}
		else {
			m_RawData.uiByte = -1;
			m_RawData.uiDataItems = 0;
		}

	}

	else if( b7PDW == true ) {
		m_RawData.enDataType = en_PDW_DATA;
		m_RawData.enUnitType = en_701;

        if (m_RawDataFile.Open( pstPathname, CFile::shareDenyNone | CFile::typeBinary) == TRUE) {
			SRxPDWHeader *pPDWHeader;

			m_RawData.uiByte = m_RawDataFile.Read( gstpRawDataBuffer, MAX_RAWDATA_SIZE );
			
			pPDWHeader = ( SRxPDWHeader * ) gstpRawDataBuffer;
			
			m_pData = new C7PDW( & m_RawData, pstFilterSetup );

			m_pData->AllSwapData32( & pPDWHeader->uiAcqTime, sizeof(int)*4 );
			m_pData->AllSwapData32( & pPDWHeader->iSearchBandID, sizeof(int)*4 );

			m_RawData.uiDataItems = pPDWHeader->iNumOfPDW;

			m_pData->Alloc();

			m_pData->ConvertArray();

			m_RawDataFile.Close();

		}
		else {
			m_RawData.uiByte = -1;
			m_RawData.uiDataItems = 0;
		}

	}

	else if( bKFXPDW == true ) {
		m_RawData.enDataType = en_PDW_DATA;
		m_RawData.enUnitType = en_KFX;

        if (m_RawDataFile.Open( pstPathname, CFile::shareDenyNone | CFile::typeBinary) == TRUE) {
			STR_PDWFILE_HEADER *pPDWFile;

			m_RawData.uiByte = m_RawDataFile.Read( gstpRawDataBuffer, MAX_RAWDATA_SIZE );

			pPDWFile = ( STR_PDWFILE_HEADER * ) gstpRawDataBuffer;

			m_pData = new CKFXPDW( & m_RawData, pstFilterSetup );

			m_RawData.uiDataItems = pPDWFile->uiSignalCount;

			m_pData->Alloc();

			m_pData->ConvertArray();

			m_RawDataFile.Close();

		}
		else {
			m_RawData.uiByte = -1;
			m_RawData.uiDataItems = 0;
		}

	}

	//////////////////////////////////////////////////////////////////////////
	else if( bIQ == true ) {
		m_RawData.enDataType = en_IQ_DATA;
		m_RawData.enUnitType = en_SONATA;

        if (m_RawDataFile.Open( pstPathname, CFile::modeRead | CFile::typeBinary) == TRUE) {
			m_RawData.uiByte = m_RawDataFile.Read( gstpRawDataBuffer, MAX_RAWDATA_SIZE );
			m_RawData.uiDataItems = m_RawData.uiByte / sizeof(TNEW_IQ);

			m_pData = new CIQ( & m_RawData );

			m_pData->Alloc();

			m_pData->ConvertArray();

			m_RawDataFile.Close();

		}
		else {
			m_RawData.uiByte = -1;
			m_RawData.uiDataItems = -1;
        }
		
	}
	else {
		printf("\n Error !!");

	}

}

/**
 * @brief     
 * @return    void *
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/02/27 21:49:58
 * @warning   
 */
void *CDataFile::GetData() 
{ 
	if( m_pData != NULL ) 
		return m_pData->GetData(); 
	else 
		return NULL; 
}

void CDataFile::SetData( CData *pData )
{
	m_pData = pData;

	++ m_pData->m_uiWindowNumber;

}
