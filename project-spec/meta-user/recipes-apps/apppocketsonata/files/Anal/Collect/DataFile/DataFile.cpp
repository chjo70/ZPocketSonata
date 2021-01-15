#ifdef _MSC_VER
#include "stdafx.h"
#else
#include "../../SigAnal/stdafx.h"
#endif

#include <math.h>
#include <stdio.h>
#include <float.h>
#include <string.h>

#include <fcntl.h>


#if defined(_GUI_)
#define _MAIN_GLOBALS_
#elif __linux__
//#define _MAIN_GLOBALS_

#elif defined(_MSC_VER)
#define _MAIN_
#define _MAIN_GLOBALS_
#endif


#include "DataFile.h"

#include "CRWRCommonVariables.h"

static int stDataFile;

const char stDV[2] = { ' ', '*' } ;

//static char *m_pRawDataBuffer;

#define	RAD2DEG			(180./M_PI)		// 57.295779513082320876798154814114


////////////////////////////////////////////////////////////////////////

CPDW::CPDW(STR_RAWDATA *pRawData) : CData(pRawData )
{
    m_RawData.enDataType = en_PDW_DATA;
    m_RawData.enUnitType = en_SONATA;
}

CPDW::~CPDW(void)
{

}

void CPDW::Alloc( int iItems )
{
	if( iItems == 0 ) {
		iItems = m_RawData.uiDataItems;
	}

	m_PDWData.pfFreq = (float *)malloc(sizeof(float) * iItems );
	m_PDWData.pfPW = (float *)malloc(sizeof(float) * iItems );
	m_PDWData.pfAOA = (float *)malloc(sizeof(float) * iItems );
	m_PDWData.pfTOA = (float *)malloc(sizeof(float) * iItems );
	m_PDWData.pfDTOA = (float *)malloc(sizeof(float) * iItems );
	m_PDWData.pfPA = (float *)malloc(sizeof(float) * iItems );
	m_PDWData.pullTOA = (_TOA *)malloc(sizeof(_TOA) * iItems );

	m_PDWData.pcType = (char *)malloc(sizeof(char) * iItems );
	m_PDWData.pcDV = (char *)malloc(sizeof(char) * iItems );
}

void CPDW::Free()
{
	free(m_PDWData.pfFreq);
	free(m_PDWData.pfPW);
	free(m_PDWData.pfAOA);
	free(m_PDWData.pfTOA);
	free(m_PDWData.pfDTOA);
	free(m_PDWData.pfPA);

	free( m_PDWData.pullTOA );

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
void CPDW::ConvertArray( STR_PDWDATA *pPDWData, bool bSwap, STR_FILTER_SETUP *pFilterSetup )
{
    unsigned int i;

	float *pfFreq = m_PDWData.pfFreq;
	float *pfPW = m_PDWData.pfPW;
	float *pfAOA = m_PDWData.pfAOA;
	float *pfTOA = m_PDWData.pfTOA;
	float *pfDTOA = m_PDWData.pfDTOA;
	float *pfPA = m_PDWData.pfPA;
	_TOA *pfllTOA = m_PDWData.pullTOA;

	char *pcType = m_PDWData.pcType;
	char *pcDV = m_PDWData.pcDV;

	UINT uiToa, preToa, uiDToa;
	UINT uiTemp;

	TNEW_PDW temp;

	TNEW_PDW *pPDW = (TNEW_PDW *) m_pRawDataBuffer;

	m_bPhaseData = false;

	_spOneSec = 20000000.;
	_spOneMilli = FDIV( _spOneSec, 1000. );
	_spOneMicrosec = FDIV( _spOneMilli, 1000. );
	_spOneNanosec = FDIV( _spOneMicrosec, 1000. );

	_spAOAres = (float) ( 0.351562 );
	_spAMPres = (float) (0.351562);
	//_spPWres = ( _spOneMicrosec * 25 ) / 10.;
	_spPWres = (float) ( 50 );

	m_PDWData.iDataItems = 0;

    Log( enNormal, _T("ConvertArray()를 [%d]개를 변환합니다.") , m_RawData.uiDataItems );

    for (i = 0; i < m_RawData.uiDataItems ; ++i) {
		temp.bpdw[0][0] = pPDW->item.toa_1;
		temp.bpdw[0][1] = pPDW->item.toa_2;
		temp.bpdw[0][2] = pPDW->item.toa_3;
		temp.bpdw[0][3] = pPDW->item.toa_4;

		uiToa = temp.wpdw[0];
		*pfTOA = FDIV(uiToa, _spOneMicrosec );
		//*pfTOA = FDIV( uiToa * 20, 1000. );

		if (i == 0) {
			*pfDTOA = 0;
			preToa = uiToa;
		}
		else {
			uiDToa = uiToa - preToa;
			*pfDTOA = FDIV( uiDToa, _spOneMicrosec );
			//*pfDTOA = FDIV( uiDToa*20, 1000. );
			preToa = uiToa;
		}

		*pfllTOA = uiToa;


		uiTemp = BIT_MERGE(pPDW->item.frequency_h, pPDW->item.frequency_l);
		*pfFreq = FFRQCNV(pPDW->item.band + 1, uiTemp);

		uiTemp = BIT_MERGE(pPDW->item.pulse_width_h, pPDW->item.pulse_width_l);
		*pfPW = FMUL( uiTemp, _spPWres );

		uiTemp = BIT_MERGE(pPDW->item.direction_h, pPDW->item.direction_l);
		*pfAOA = FAOACNV(uiTemp);

		uiTemp = pPDW->item.amplitude;
		*pfPA = FPACNV(uiTemp);

		*pcType = pPDW->item.stat;
		*pcDV = pPDW->item.dv;

		// printf( "\n [%3d] 0x%02X %5.1f%1c[deg] %8.2f[MHz] %10.3f[us] %8.3f[ns]" , i+1, *pcType, *pfAOA, stDV[*pcDV], *pfFreq, *pfTOA, *pfPW );
		// 필터링 조건
		if( ( m_strFilterSetup.dToaMin <= *pfTOA && m_strFilterSetup.dToaMax >= *pfTOA ) &&
			( m_strFilterSetup.dAoaMin <= *pfAOA && m_strFilterSetup.dAoaMax >= *pfAOA ) &&
			( m_strFilterSetup.dPAMin <= *pfPA && m_strFilterSetup.dPAMax >= *pfPA ) &&
			( m_strFilterSetup.dPWMin <= *pfPW && m_strFilterSetup.dPWMax >= *pfPW ) &&
			( m_strFilterSetup.dFrqMin <= *pfFreq && m_strFilterSetup.dFrqMax >= *pfFreq ) ) {
			++pfFreq;
			++pfAOA;
			++pfPW;
			++pfPA;
			++pfTOA;
			++pfDTOA;
			++pcType;
			++pcDV;

			++ pfllTOA;

			++ m_PDWData.iDataItems;
		}

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
        memcpy( & m_strFilterSetup, pstFilterSetup, sizeof(STR_FILTER_SETUP) );
	}

}

/**
 * @brief		~CEPDW
 * @param		void
 * @return		
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2020/12/29 10:26:27
 * @warning		
 */
CEPDW::~CEPDW(void)
{

}

/**
 * @brief		Alloc
 * @param		int iItems
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2020/12/29 10:26:34
 * @warning		
 */
void CEPDW::Alloc( int iItems )
{
	if( iItems == 0 ) {
		iItems = m_RawData.uiDataItems;
	}

	m_PDWData.pfFreq = (float *)malloc(sizeof(float) * iItems );
	m_PDWData.pfPW = (float *)malloc(sizeof(float) * iItems );
	m_PDWData.pfAOA = (float *)malloc(sizeof(float) * iItems );
	m_PDWData.pfTOA = (float *)malloc(sizeof(float) * iItems );
	m_PDWData.pfDTOA = (float *)malloc(sizeof(float) * iItems );
	m_PDWData.pfPA = (float *)malloc(sizeof(float) * iItems );
	m_PDWData.pullTOA = (_TOA *)malloc(sizeof(_TOA) * iItems );

	m_PDWData.pcType = (char *)malloc(sizeof(char) * iItems );
	m_PDWData.pcDV = (char *)malloc(sizeof(char) * iItems );

	m_PDWData.pfPh1 = (float *)malloc(sizeof(float) * iItems );
	m_PDWData.pfPh2 = (float *)malloc(sizeof(float) * iItems );
	m_PDWData.pfPh3 = (float *)malloc(sizeof(float) * iItems );
	m_PDWData.pfPh4 = (float *)malloc(sizeof(float) * iItems );

}

void CEPDW::Free()
{
	free(m_PDWData.pfFreq);
	free(m_PDWData.pfPW);
	free(m_PDWData.pfAOA);
	free(m_PDWData.pfTOA);
	free(m_PDWData.pfDTOA);
	free(m_PDWData.pfPA);

	free( m_PDWData.pullTOA );

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
void CEPDW::ConvertArray( STR_PDWDATA *pPDWData, bool bSwap, STR_FILTER_SETUP *pFilterSetup )
{
    unsigned int i;

	float *pfFreq = m_PDWData.pfFreq;
	float *pfPW = m_PDWData.pfPW;
	float *pfAOA = m_PDWData.pfAOA;
	float *pfTOA = m_PDWData.pfTOA;
	float *pfDTOA = m_PDWData.pfDTOA;
	float *pfPA = m_PDWData.pfPA;
	_TOA *pullTOA = m_PDWData.pullTOA;

	float *pfPh1 = m_PDWData.pfPh1;
	float *pfPh2 = m_PDWData.pfPh2;
	float *pfPh3 = m_PDWData.pfPh3;
	float *pfPh4 = m_PDWData.pfPh4;

	char *pcType = m_PDWData.pcType;
	char *pcDV = m_PDWData.pcDV;

	//_TOA uiToa /*firstToa*/ ;
	float fPreToa;

    //STR_PDWDATA *pPDWData = (STR_PDWDATA *) m_pRawDataBuffer;
	_PDW *pPDW = (_PDW *) & m_pRawDataBuffer[m_uiLengthOfHeader];

// 	if( iOffset != 0 ) {
// 		m_enBandWidth = pPDWData->x.el.enBandWidth;
// 
// 	}

	_spOneSec = FDIV( 1000000000, _toaRes[m_enBandWidth] );
	_spOneMilli = FDIV( 1000000, _toaRes[m_enBandWidth] );
	_spOneMicrosec = FDIV( 1000, _toaRes[m_enBandWidth] );
	_spOneNanosec = FDIV( 1, _toaRes[m_enBandWidth] );

	_spAMPres = (float) (0.25);
	_spPWres = _spOneMicrosec;

	m_PDWData.iDataItems = 0;

    Log( enNormal, _T("ConvertArray()를 [%d]개를 변환합니다.") , m_RawData.uiDataItems );

    for ( i=0; i < m_RawData.uiDataItems ; ++i ) {
		if (i == 0) {
			if( pPDWData->x.el.iIsStorePDW == 1 && m_uiLengthOfHeader != 0 ) {
				m_ll1stToa = pPDW->ullTOA;
			}
			else {
				// m_ll1stToa = 0;
			}

			*pfDTOA = 0;
			*pfTOA = FDIV(pPDW->ullTOA-m_ll1stToa, _spOneMicrosec );
			fPreToa = *pfTOA;
		}
		else {
			//uiToa = pPDW->llTOA - m_ll1stToa;
			*pfTOA = FDIV(pPDW->ullTOA-m_ll1stToa, _spOneMicrosec );

			//*pfDTOA = (float) ( uiToa - preToa );
			*pfDTOA = FDIV( *pfTOA-fPreToa, _spOneMicrosec );
			fPreToa = *pfTOA;
		}

		*pullTOA = pPDW->ullTOA;

		*pfFreq = F_FRQMhzCNV( 0, pPDW->iFreq );	//FFRQCNV(pPDW->item.band + 1, uiTemp);

		*pfPW = PWCNV(pPDW->iPW * 1000. );

		if( pPDW->iAOA == 0 ) {
			*pfAOA = (float) 0.00000001;
		}
		else {
			*pfAOA = AOACNV( pPDW->iAOA );
		}

		*pfPA = PACNV(pPDW->iPA);

		*pcType = pPDW->iPulseType;

		*pcDV = _spOne;

		if( m_bPhaseData == true ) {
			//*pfPh1 = pPDW->fPh1;
			//*pfPh2 = pPDW->fPh2;
			//*pfPh3 = pPDW->fPh3;
			//*pfPh4 = pPDW->fPh4;
		}

		printf( "\n [%3d] 0x%02X %5.1f%1c[deg] %8.2f[kHz] %10.3f[us] %8.3f[ns]" , i+1, *pcType, *pfAOA, stDV[*pcDV], *pfFreq, *pfTOA, *pfPW );

		// 필터링 조건
		if( ( m_strFilterSetup.dToaMin <= *pfTOA && m_strFilterSetup.dToaMax >= *pfTOA ) &&
			( m_strFilterSetup.dAoaMin <= *pfAOA && m_strFilterSetup.dAoaMax >= *pfAOA ) &&
			( m_strFilterSetup.dPAMin <= *pfPA && m_strFilterSetup.dPAMax >= *pfPA ) &&
			( m_strFilterSetup.dPWMin <= *pfPW && m_strFilterSetup.dPWMax >= *pfPW ) &&
			( m_strFilterSetup.dFrqMin <= *pfFreq && m_strFilterSetup.dFrqMax >= *pfFreq ) ) {
// 		if( ( (double) *pfAOA >= m_strFilterSetup.dAoaMin && (double) *pfAOA <= m_strFilterSetup.dAoaMax ) &&
// 			( (double) *pfFreq >= m_strFilterSetup.dFrqMin && (double) *pfFreq <= m_strFilterSetup.dFrqMax ) ) {
			++pfFreq;
			++pfAOA;
			++pfPW;
			++pfPA;
			++pfTOA;
			++pfDTOA;
			++pcType;
			++pcDV;

			++ pullTOA;

			if( m_bPhaseData == true ) {
				++ pfPh1;
				++ pfPh2;
				++ pfPh3;
				++ pfPh4;
			}

			++ m_PDWData.iDataItems;
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

	//m_pRawData->uiDataItems = uiDataItems;
	Log( enNormal, _T("필터링 PDW 개수는 %d 입니다.") , m_PDWData.iDataItems );
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

void CSPDW::Alloc( int iItems )
{
	if( iItems == 0 ) {
		iItems = m_RawData.uiDataItems;
	}

	m_PDWData.pfFreq = (float *)malloc(sizeof(float) * iItems );
	m_PDWData.pfPW = (float *)malloc(sizeof(float) * iItems );
	m_PDWData.pfAOA = (float *)malloc(sizeof(float) * iItems );
	m_PDWData.pfTOA = (float *)malloc(sizeof(float) * iItems );
	m_PDWData.pfDTOA = (float *)malloc(sizeof(float) * iItems );
	m_PDWData.pfPA = (float *)malloc(sizeof(float) * iItems );
	m_PDWData.pullTOA = (_TOA *)malloc(sizeof(_TOA) * iItems );

	m_PDWData.pcType = (char *)malloc(sizeof(char) * iItems );
	m_PDWData.pcDV = (char *)malloc(sizeof(char) * iItems );
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
void CSPDW::ConvertArray( STR_PDWDATA *pPDWData, bool bSwap, STR_FILTER_SETUP *pFilterSetup )
{
	unsigned int i;

	float *pfFreq = m_PDWData.pfFreq;
	float *pfPW = m_PDWData.pfPW;
	float *pfAOA = m_PDWData.pfAOA;
	float *pfTOA = m_PDWData.pfTOA;
	float *pfDTOA = m_PDWData.pfDTOA;
	float *pfPA = m_PDWData.pfPA;
	_TOA *pullTOA = m_PDWData.pullTOA;

	char *pcType = m_PDWData.pcType;
	char *pcDV = m_PDWData.pcDV;

	UINT uiToa, preToa, uiDToa;
	UINT uiTemp;

	TNEW_PDW temp;

	TNEW_PDW *pPDW = (TNEW_PDW *) m_pRawDataBuffer;

	m_bPhaseData = false;

	_spOneSec = 50000000.;
	_spOneMilli = FDIV( _spOneSec, 1000. );
	_spOneMicrosec = FDIV( _spOneMilli, 1000. );
	_spOneNanosec = FDIV( _spOneMicrosec, 1000. );

	_spAOAres = (float) ( 0.351562 );
	_spAMPres = (float) (0.351562);
	_spPWres = _spOneMicrosec;

	m_PDWData.iDataItems = 0;

    for (i = 0; i < m_RawData.uiDataItems ; ++i) {
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
			//*pfDTOA = FDIV( uiDToa*20, 1000. );
			preToa = uiToa;
		}

		*pullTOA = uiToa;


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
		// 필터링 조건
		if( ( m_strFilterSetup.dToaMin <= *pfTOA && m_strFilterSetup.dToaMax >= *pfTOA ) &&
			( m_strFilterSetup.dAoaMin <= *pfAOA && m_strFilterSetup.dAoaMax >= *pfAOA ) &&
			( m_strFilterSetup.dPAMin <= *pfPA && m_strFilterSetup.dPAMax >= *pfPA ) &&
			( m_strFilterSetup.dPWMin <= *pfPW && m_strFilterSetup.dPWMax >= *pfPW ) &&
			( m_strFilterSetup.dFrqMin <= *pfFreq && m_strFilterSetup.dFrqMax >= *pfFreq ) ) {
				++pfFreq;
				++pfAOA;
				++pfPW;
				++pfPA;
				++pfTOA;
				++pfDTOA;
				++pcType;
				++pcDV;

				++ pullTOA;

				++ m_PDWData.iDataItems;
		}

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
void CKFXPDW::Alloc( int iItems )
{

	if( iItems == 0 ) {
		iItems = m_RawData.uiDataItems;
	}

	m_PDWData.pfFreq = (float *)malloc(sizeof(float) * iItems);
	m_PDWData.pfPW = (float *)malloc(sizeof(float) * iItems );
	m_PDWData.pfAOA = (float *)malloc(sizeof(float) * iItems);
	m_PDWData.pfTOA = (float *)malloc(sizeof(float) * iItems);
	m_PDWData.pfDTOA = (float *)malloc(sizeof(float) * iItems);
	m_PDWData.pfPA = (float *)malloc(sizeof(float) * iItems);
	m_PDWData.pullTOA = (_TOA *)malloc(sizeof(_TOA) * iItems);

	m_PDWData.pcType = (char *)malloc(sizeof(char) * iItems);
	m_PDWData.pcDV = (char *)malloc(sizeof(char) * iItems);
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
	free(m_PDWData.pullTOA);

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
void CKFXPDW::ConvertArray( STR_PDWDATA *pPDWData, bool bSwap, STR_FILTER_SETUP *pFilterSetup )
{
    unsigned int i;

	float *pfFreq = m_PDWData.pfFreq;
	float *pfPW = m_PDWData.pfPW;
	float *pfAOA = m_PDWData.pfAOA;
	float *pfTOA = m_PDWData.pfTOA;
	float *pfDTOA = m_PDWData.pfDTOA;
	float *pfPA = m_PDWData.pfPA;

	char *pcType = m_PDWData.pcType;
	char *pcDV = m_PDWData.pcDV;

	_TOA *pullTOA = m_PDWData.pullTOA;

	float /*fToa,*/ /* firstToa, */ preToa;

	_TOA llToa;
	UDRCPDW *pPDW = (UDRCPDW *) & m_pRawDataBuffer[m_uiLengthOfHeader];

	_spOneSec = 20000000.;
	_spOneMilli = FDIV( _spOneSec, 1000. );
	_spOneMicrosec = FDIV( _spOneMilli, 1000. );
	_spOneNanosec = FDIV( _spOneMicrosec, 1000. );

	_spAOAres = (float) ( 0.351562 );
	_spAMPres = (float) (0.351562);
	_spPWres = _spOneMicrosec;

	m_PDWData.iDataItems = 0;

    Log( enNormal, _T("ConvertArray()를 [%d]개를 변환합니다.") , m_RawData.uiDataItems );

    for (i = 0; i < m_RawData.uiDataItems ; ++i) {
		llToa = (_TOA) ( pPDW->sPDWFormat.m_LSBTOA ) | ( (_TOA) pPDW->sPDWFormat.m_MSBTOA << 32 );
		*pullTOA = llToa;
		if (i == 0) {
// 			if( iOffset != 0 ) {
// 				m_ll1stToa = llToa;
// 			}
			*pfTOA = DecodeTOA( llToa-m_ll1stToa );
			*pfDTOA = 0;
			preToa = *pfTOA;
		}
		else {
			*pfTOA = DecodeTOA( llToa-m_ll1stToa );

			*pfDTOA = ( *pfTOA - preToa );

			preToa = *pfTOA;
		}

		*pfFreq = DecodeFREQ( pPDW->sPDWFormat.m_freq );		// MHz

		*pfPW = DecodePW( pPDW->sPDWFormat.m_PW );

		*pfAOA = DecodeDOA( pPDW->sPDWFormat.m_DOA );

		*pfPA = DecodePA( pPDW->sPDWFormat.m_PA );

		*pcType = 0; // pPDW->sPDWFormat.m_sigType;

		*pcDV = pPDW->sPDWFormat.m_DI;

		printf( "\n [%3d] 0x%02X %5.1f%1c[deg] %8.2f[MHz] %10.3f[us] %8.3f[ns]" , i+1, *pcType, *pfAOA, stDV[*pcDV], *pfFreq, *pfTOA, *pfPW );

		// 필터링 조건
		if( ( m_strFilterSetup.dToaMin <= *pfTOA && m_strFilterSetup.dToaMax >= *pfTOA ) &&
			( m_strFilterSetup.dAoaMin <= *pfAOA && m_strFilterSetup.dAoaMax >= *pfAOA ) &&
			( m_strFilterSetup.dPAMin <= *pfPA && m_strFilterSetup.dPAMax >= *pfPA ) &&
			( m_strFilterSetup.dPWMin <= *pfPW && m_strFilterSetup.dPWMax >= *pfPW ) &&
			( m_strFilterSetup.dFrqMin <= *pfFreq && m_strFilterSetup.dFrqMax >= *pfFreq ) ) {
				++pfFreq;
				++pfAOA;
				++pfPW;
				++pfPA;
				++pfTOA;
				++pfDTOA;
				++pcType;
				++pcDV;
				++pullTOA;

				++ m_PDWData.iDataItems;

				//++ m_stFilterSetup.uiDataItems;

		}

		++pPDW;
	}

	Log( enNormal, _T("필터링 PDW 개수는 %d 입니다.") , m_PDWData.iDataItems );
}




//////////////////////////////////////////////////////////////////////////

/**
 * @brief CPOCKETSONATAPDW::CPOCKETSONATAPDW
 * @param pRawData
 * @param pstFilterSetup
 */
CPOCKETSONATAPDW::CPOCKETSONATAPDW(STR_RAWDATA *pRawData, STR_FILTER_SETUP *pstFilterSetup, int iBoardID ) : CData(pRawData )
{
    m_bPhaseData = false;

    m_iBoardID = iBoardID;

    memset( & m_PDWData, 0, sizeof(STR_PDW_DATA) );

    m_RawData.enDataType = en_PDW_DATA;
    m_RawData.enUnitType = en_ZPOCKETSONATA;

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
CPOCKETSONATAPDW::~CPOCKETSONATAPDW(void)
{
    Free();
}

/**
 * @brief
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/02/27 21:44:02
 * @warning
 */
void CPOCKETSONATAPDW::Alloc( int iItems )
{

	if( iItems == 0 ) {
		iItems = m_RawData.uiDataItems;
	}

    Log( enNormal, _T("Alloc()을 [%d]개를 할당합니다.") , iItems );

    if( m_PDWData.pfFreq == 0 ) {
        m_PDWData.pfFreq = (float *)malloc(sizeof(float) * iItems);
    }

    if( m_PDWData.pfPW == 0 ) {
        m_PDWData.pfPW = (float *)malloc(sizeof(float) * iItems );
    }

    if( m_PDWData.pfAOA == 0 ) {
        m_PDWData.pfAOA = (float *)malloc(sizeof(float) * iItems);
    }

    if( m_PDWData.pfTOA == 0 ) {
        m_PDWData.pfTOA = (float *)malloc(sizeof(float) * iItems);
    }

    if( m_PDWData.pfDTOA == 0 ) {
        m_PDWData.pfDTOA = (float *)malloc(sizeof(float) * iItems);
    }

    if( m_PDWData.pfPA == 0 ) {
        m_PDWData.pfPA = (float *)malloc(sizeof(float) * iItems);
    }

    if( m_PDWData.pullTOA == 0 ) {
        m_PDWData.pullTOA = (_TOA *)malloc(sizeof(_TOA) * iItems);
    }

    if( m_PDWData.pcType == 0 ) {
        m_PDWData.pcType = (char *)malloc(sizeof(char) * iItems);
    }

    if( m_PDWData.pcDV == 0 ) {
        m_PDWData.pcDV = (char *)malloc(sizeof(char) * iItems);
    }

}

/**
 * @brief
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/02/27 21:41:58
 * @warning
 */
void CPOCKETSONATAPDW::Free()
{
    _SAFE_FREE( m_PDWData.pfFreq );
	_SAFE_FREE( m_PDWData.pfPW );
	_SAFE_FREE( m_PDWData.pfAOA );
	_SAFE_FREE( m_PDWData.pfTOA );
	_SAFE_FREE( m_PDWData.pfDTOA );
	_SAFE_FREE( m_PDWData.pfPA );
	_SAFE_FREE( m_PDWData.pullTOA );

	_SAFE_FREE( m_PDWData.pcType );
	_SAFE_FREE( m_PDWData.pcDV );

}

/**
 * @brief
 * @return    void *
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/02/27 21:41:55
 * @warning
 */
void *CPOCKETSONATAPDW::GetData()
{
    return & m_PDWData;
}

/**
  * @brief      포켓 소나타용 으로 PDW 데이터를 변환한다.
  * @return 	void
  * @date       2019/06/07 10:10
*/
void CPOCKETSONATAPDW::ConvertArray( STR_PDWDATA *pPDWData, bool bSwap, STR_FILTER_SETUP *pFilterSetup )
{
    unsigned int i;
    int iCh;

    _TOA ullToa;

    DMAPDW *pPDW = (DMAPDW *) & m_pRawDataBuffer[0];

    Log( enNormal, _T("ConvertArray()를 [%d]개를 변환합니다.") , m_RawData.uiDataItems );

    if( pPDWData == NULL ) {
        float *pfFreq, *pfPW, *pfAOA, *pfTOA, *pfDTOA, *pfPA;
        char *pcType, *pcDV;
        _TOA *pullTOA;

        float preToa;

        UINT uiFreq;

        Alloc( m_RawData.uiDataItems );

        pfFreq = m_PDWData.pfFreq;
        pfPW = m_PDWData.pfPW;
        pfAOA = m_PDWData.pfAOA;
        pfTOA = m_PDWData.pfTOA;
        pfDTOA = m_PDWData.pfDTOA;
        pfPA = m_PDWData.pfPA;

        pcType = m_PDWData.pcType;
        pcDV = m_PDWData.pcDV;

        pullTOA = m_PDWData.pullTOA;

        m_PDWData.iDataItems = 0;

        for (i = 0; i < m_RawData.uiDataItems ; ++i) {
            ullToa = (_TOA) ( pPDW->uPDW.uniPdw_freq_toa.stPdw_freq_toa.toa_L ) | ( (_TOA) pPDW->uPDW.uniPdw_toa_edge.stPdw_toa_edge.toa_H << 16 );

            *pullTOA = ullToa;
            if (i == 0) {
                *pfTOA = DecodeTOAus( ullToa );
                *pfDTOA = 0;
            }
            else {
                *pfTOA = DecodeTOAus( ullToa );

                *pfDTOA = ( *pfTOA - preToa );
            }
            preToa = *pfTOA;

            uiFreq = ( pPDW->uPDW.uniPdw_pw_freq.stPdw_pw_freq.frequency_L ) | ( pPDW->uPDW.uniPdw_freq_toa.stPdw_freq_toa.frequency_H << 8 );
            iCh = pPDW->uPDW.uniPdw_freq_toa.stPdw_freq_toa.pdw_phch;
            *pfFreq = DecodeFREQ( uiFreq, iCh, m_stHeader.uiBoardID );

            *pfPW = DecodePW( pPDW->uPDW.uniPdw_pw_freq.stPdw_pw_freq.pulse_width );

            *pfAOA = DecodeDOA( pPDW->uPDW.uniPdw_dir_pa.stPdw_dir_pa.doa );

            *pfPA = DecodePA( pPDW->uPDW.uniPdw_dir_pa.stPdw_dir_pa.pa );

            *pcType = 0; // pPDW->sPDWFormat.m_sigType;

            *pcDV = pPDW->uPDW.uniPdw_dir_pa.stPdw_dir_pa.di;

            printf( "\n [%3d] 0x%02X %5.1f%1c[deg] %8.2f[MHz] %10.3f[us] %8.3f[ns]" , i+1, *pcType, *pfAOA, stDV[(*pcDV & 0x1)], *pfFreq, *pfTOA, *pfPW );

            // 필터링 조건
            if( pFilterSetup == NULL || ( pFilterSetup->enSubGraph == enUnselectedSubGraph || \
                                        ( ( ( pFilterSetup->dToaMin == 0 ) || ( pFilterSetup->dToaMin <= *pfTOA && *pfTOA <= pFilterSetup->dToaMax ) ) && \
                                        ( ( pFilterSetup->dAoaMin == 0 ) || ( pFilterSetup->dAoaMin <= *pfAOA && *pfAOA <= pFilterSetup->dAoaMax ) ) && \
                                        ( ( pFilterSetup->dFrqMin == 0 ) || ( pFilterSetup->dFrqMin <= *pfFreq && *pfFreq <= pFilterSetup->dFrqMax ) ) && \
                                        ( ( pFilterSetup->dPAMin == 0 ) || ( pFilterSetup->dPAMin <= *pfPA && *pfPA <= pFilterSetup->dPAMax ) ) ) ) ) {
                ++pfFreq;
                ++pfAOA;
                ++pfPW;
                ++pfPA;
                ++pfTOA;
                ++pfDTOA;
                ++pcType;
                ++pcDV;
                ++pullTOA;

                ++ m_PDWData.iDataItems;
            }
            ++pPDW;
        }
    }
    else {
        _PDW *pPDW1;

        float fOffsetFreq;

        pPDW1 = & pPDWData->stPDW[0];

        fOffsetFreq = POCKETSONATA::m_fCenterFreq[m_stHeader.uiBoardID/*m_iBoardID*/] / (float) PDW_FREQ_RES;

        for (i = 0; i < m_RawData.uiDataItems; ++i ) {
            int iFreq;
            float fFREQ;

            ullToa = (_TOA) ( pPDW->uPDW.uniPdw_freq_toa.stPdw_freq_toa.toa_L ) | ( (_TOA) pPDW->uPDW.uniPdw_toa_edge.stPdw_toa_edge.toa_H << 16 );

            pPDW1->ullTOA = ullToa;

            iFreq = ( pPDW->uPDW.uniPdw_pw_freq.stPdw_pw_freq.frequency_L ) | ( pPDW->uPDW.uniPdw_freq_toa.stPdw_freq_toa.frequency_H << 8 );

            iCh = pPDW->uPDW.uniPdw_freq_toa.stPdw_freq_toa.pdw_phch;
            if( iCh < 7 ) {
                if( iFreq & 0x8000) {
                    iFreq = 0x10000 - iFreq;
                    fFREQ = ( fOffsetFreq + ( ( ( (float) PH_WIDTH_FREQ * (float) iCh) ) / (float) PDW_FREQ_RES ) - (float) iFreq );
                }
                else {
                    fFREQ = ( fOffsetFreq + ( ( ( (float) PH_WIDTH_FREQ * (float) iCh) ) / (float) PDW_FREQ_RES ) + (float) iFreq );
                }

            }
            else {
                iCh = 15 - iCh;
                if( iFreq & 0x8000 ) {
                    iFreq = 0x10000 - iFreq;
                    fFREQ = ( fOffsetFreq - ( ( ( (float) PH_WIDTH_FREQ * (float) iCh) ) / (float) PDW_FREQ_RES ) - (float) iFreq );
                }
                else {
                    fFREQ = ( fOffsetFreq - ( ( ( (float) PH_WIDTH_FREQ * (float) iCh) ) / (float) PDW_FREQ_RES ) + (float) iFreq );
                }
            }

            // [kHz] 단위로 변경
            pPDW1->iFreq = (int) ( fFREQ + 0.5 );

            pPDW1->iPW = pPDW->uPDW.uniPdw_pw_freq.stPdw_pw_freq.pulse_width;

            pPDW1->iAOA = pPDW->uPDW.uniPdw_dir_pa.stPdw_dir_pa.doa;

            pPDW1->iPA = pPDW->uPDW.uniPdw_dir_pa.stPdw_dir_pa.pa;

            pPDW1->iPulseType = 0; // pPDW->uniPdw_status.stPdw_status.cw_pulse;

            //*pcDV = pPDW->sPDWFormat.m_DI;

            //printf( "\n [%3d] 0x%02X %5.1f%1c[deg] %8.2f[MHz] %10.3f[us] %8.3f[ns]" , i+1, *pcType, *pfAOA, stDV[*pcDV], *pfFreq, *pfTOA, *pfPW );

            ++pPDW1;

            ++pPDW;
        }

        pPDWData->uiTotalPDW = m_RawData.uiDataItems;
    }



}


/**
 * @brief		GetHeaderSize
 * @return		unsigned int
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2020/12/24 14:48:53
 * @warning		
 */
unsigned int CPOCKETSONATAPDW::GetHeaderSize()
{
    if( m_iHeaderSize == -1 ) {
        memcpy( & m_stHeader, m_pRawHeaderBuffer, sizeof(m_stHeader) );

        m_iHeaderSize = sizeof(STR_PDWFILE_HEADER);
    }

	return m_iHeaderSize;
}

/**
 * @brief		GetOneDataSize
 * @return		unsigned int
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2020/12/24 14:48:53
 * @warning		
 */
unsigned int CPOCKETSONATAPDW::GetOneDataSize()
{
	return sizeof(DMAPDW);
}

/**
 * @brief		GetDataSize
 * @return		unsigned int
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2020/12/24 15:02:30
 * @warning		
 */
unsigned int CPOCKETSONATAPDW::GetDataItems()
{
    unsigned int uiDataItems;

    if( m_iHeaderSize != -1 ) {
	    uiDataItems = m_stHeader.uiSignalCount;
    }
    else {
        uiDataItems = (unsigned int) -1;
    }

	return uiDataItems;
}

/**
 * @brief		ReadDataHeader
 * @param		void
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2021/01/08 15:09:39
 * @warning		
 */
void CPOCKETSONATAPDW::ReadDataHeader(void)
{
    memcpy( & m_stHeader, m_pRawHeaderBuffer, sizeof(m_stHeader) );

}


//////////////////////////////////////////////////////////////////////////
C7PDW::C7PDW(STR_RAWDATA *pRawData, STR_FILTER_SETUP *pstFilterSetup ) : CData(pRawData )
{
	m_bPhaseData = false;

    memset( & m_PDWData, 0, sizeof(STR_PDW_DATA) );

    m_RawData.enDataType = en_PDW_DATA;
    m_RawData.enUnitType = en_701;

	//Alloc( PDW_ITEMS );

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
	Free();
}

/**
 * @brief     
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/02/27 21:44:02
 * @warning   
 */
void C7PDW::Alloc( int iItems )
{

	if( iItems == 0 ) {
		iItems = m_RawData.uiDataItems;
	}

	Log( enNormal, _T("Alloc()을 [%d]개를 할당합니다.") , iItems );

    if( m_PDWData.pfFreq == 0 ) {
	    m_PDWData.pfFreq = (float *) malloc(sizeof(float) * iItems );
    }

    if( m_PDWData.pfPW == 0 ) {
	    m_PDWData.pfPW = (float *) malloc(sizeof(float) * iItems );
    }

    if( m_PDWData.pfAOA == 0 ) {
	    m_PDWData.pfAOA = (float *) malloc(sizeof(float) * iItems );
    }

    if( m_PDWData.pfTOA == 0 ) {
	    m_PDWData.pfTOA = (float *) malloc(sizeof(float) * iItems );
    }

    if( m_PDWData.pfDTOA == 0 ) {
	    m_PDWData.pfDTOA = (float *) malloc(sizeof(float) * iItems );
    }

    if( m_PDWData.pfPA == 0 ) {
	    m_PDWData.pfPA = (float *) malloc(sizeof(float) * iItems );
    }

    if( m_PDWData.pullTOA == 0 ) {
	    m_PDWData.pullTOA = (_TOA *) malloc(sizeof(_TOA) * iItems );
    }

    if( m_PDWData.pcType == 0 ) {
	    m_PDWData.pcType = (char *) malloc(sizeof(char) * iItems );
    }

    if( m_PDWData.pcDV == 0 ) {
	    m_PDWData.pcDV = (char *) malloc(sizeof(char) * iItems );
    }

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
	Log( enNormal, _T("Free()를 해지합니다.") );

	_SAFE_FREE( m_PDWData.pfFreq);
	_SAFE_FREE(m_PDWData.pfPW);
	_SAFE_FREE(m_PDWData.pfAOA);
	_SAFE_FREE(m_PDWData.pfTOA);
	_SAFE_FREE(m_PDWData.pfDTOA);
	_SAFE_FREE(m_PDWData.pfPA);
	_SAFE_FREE(m_PDWData.pullTOA);

	_SAFE_FREE(m_PDWData.pcType);
	_SAFE_FREE(m_PDWData.pcDV);

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
void C7PDW::ConvertArray( STR_PDWDATA *pPDWData, bool bSwap, STR_FILTER_SETUP *pFilterSetup )
{
    unsigned int i;

    Alloc( m_RawData.uiDataItems );

	float *pfFreq = m_PDWData.pfFreq;
	float *pfPW = m_PDWData.pfPW;
	float *pfAOA = m_PDWData.pfAOA;
	float *pfTOA = m_PDWData.pfTOA;
	float *pfDTOA = m_PDWData.pfDTOA;
	float *pfPA = m_PDWData.pfPA;

	_TOA *pullTOA = m_PDWData.pullTOA;

	char *pcType = m_PDWData.pcType;
	char *pcDV = m_PDWData.pcDV;

	float fPreToa;

	SRxPDWDataRGroup *pPDW = (SRxPDWDataRGroup *) & m_pRawDataBuffer[0];

	_spOneSec = 20000000.;
	_spOneMilli = FDIV( _spOneSec, 1000. );
	_spOneMicrosec = FDIV( _spOneMilli, 1000. );
	_spOneNanosec = FDIV( _spOneMicrosec, 1000. );

	_spAOAres = (float) ( 0.351562 );
	_spAMPres = (float) (0.351562);
	_spPWres = _spOneMicrosec;

	m_PDWData.iDataItems = 0;

    Log( enNormal, _T("ConvertArray()를 [%d]개를 변환합니다.") , m_RawData.uiDataItems );    

    for (i = 0; i < m_RawData.uiDataItems ; ++i) {
        if( bSwap == true ) {
		    swapByteOrder( pPDW->ullTOA );
		    AllSwapData32( & pPDW->iSignalType, sizeof(SRxPDWDataRGroup)- sizeof(long long int) );
        }

		*pullTOA  = pPDW->ullTOA;

	
		*pfTOA = FDMUL( pPDW->ullTOA, 6.48824/1000.0 );
        *pfTOA /= 1000000.;

        if (i == 0) {
            *pfDTOA = 0;
        }
        else {
            *pfDTOA = (float) ( *pfTOA - fPreToa );

            *pfDTOA /= 1000000.;
        }        
        fPreToa = *pfTOA;

		*pfFreq = FMUL( pPDW->iFreq, 0.010 );		// MHz
 
 		*pfPW = FMUL( pPDW->iPW, 6.48824 );

 		*pfAOA = FMUL( pPDW->iDirection, 0.1 );

 		*pfPA = FMUL( pPDW->iPA, 0.25 ) - (float) 110.;
 
 		*pcType = pPDW->iSignalType;

 		*pcDV = pPDW->iDirectionVaild ^ 1;



		// 필터링 조건
		if( ( m_strFilterSetup.dToaMin <= *pfTOA && m_strFilterSetup.dToaMax >= *pfTOA ) &&
			( m_strFilterSetup.dAoaMin <= *pfAOA && m_strFilterSetup.dAoaMax >= *pfAOA ) &&
			( m_strFilterSetup.dPAMin <= *pfPA && m_strFilterSetup.dPAMax >= *pfPA ) &&
			( m_strFilterSetup.dPWMin <= *pfPW && m_strFilterSetup.dPWMax >= *pfPW ) &&
			( m_strFilterSetup.dFrqMin <= *pfFreq && m_strFilterSetup.dFrqMax >= *pfFreq ) ) {
			++pfFreq;
			++pfAOA;
			++pfPW;
			++pfPA;
			++pfTOA;
			++pfDTOA;
			++pcType;
			++pcDV;
			++pullTOA;

			++ m_PDWData.iDataItems;

			//++ m_stFilterSetup.uiDataItems;
		}

		// printf( "\n [%3d] 0x%02X %5.1f%1c[deg] %8.2f[MHz] %10.3f[us] %8.3f[ns]" , i+1, *pcType, *pfAOA, stDV[*pcDV], *pfFreq, *pfTOA, *pfPW );

		++pPDW;
	}

	Log( enNormal, _T("PDW 개수는 %d 입니다.") , m_PDWData.iDataItems );

}


/**
 * @brief		GetHeaderSize
 * @return		unsigned int
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2020/12/24 14:48:53
 * @warning		
 */
unsigned int C7PDW::GetHeaderSize()
{
    if( m_iHeaderSize == -1 ) {
	    memcpy( & m_stHeader, m_pRawHeaderBuffer, sizeof(m_stHeader) );

	    AllSwapData32( & m_stHeader.uiAcqTime, sizeof(int)*4 );
	    AllSwapData32( & m_stHeader.iSearchBandID, sizeof(int)*4 );

        m_iHeaderSize = sizeof(SRxPDWHeader);
    }

	return m_iHeaderSize;
}

/**
 * @brief		GetOneDataSize
 * @return		unsigned int
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2020/12/24 14:48:53
 * @warning		
 */
unsigned int C7PDW::GetOneDataSize()
{
	return sizeof(SRxPDWDataRGroup);
}

/**
 * @brief		GetDataSize
 * @return		unsigned int
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2020/12/24 15:02:30
 * @warning		
 */
unsigned int C7PDW::GetDataItems()
{
    unsigned int uiDataItems;

    if( m_iHeaderSize != -1 ) {
	    uiDataItems = m_stHeader.iNumOfPDW;
    }
    else {
        uiDataItems = (unsigned int) -1;
    }

	return uiDataItems;
}


/**
 * @brief		ReadDataHeader
 * @param		void
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2020/12/28 10:22:37
 * @warning		
 */
void C7PDW::ReadDataHeader(void)
{
	memcpy( & m_stHeader, m_pRawDataBuffer, sizeof(m_stHeader) );

}


//////////////////////////////////////////////////////////////////////////
//

CIQ::CIQ(STR_RAWDATA *pRawData) : CData(pRawData )
{
	Alloc( IQ_ITEMS );
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
void CIQ::Alloc( int iItems )
{

	if( iItems == 0 ) {
		iItems = m_RawData.uiDataItems;
	}

	m_IQData.pfI = (float *)malloc( sizeof(float) * iItems );
	m_IQData.pfQ = (float *)malloc( sizeof(float) * iItems );
	m_IQData.pfPA = (float *)malloc( sizeof(float) * iItems );
	m_IQData.pfIP = (float *)malloc( sizeof(float) * iItems );
	m_IQData.pfFFT = (float *)malloc( sizeof(float) * iItems );

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

void *CIQ::GetHeader()
{
	return & m_IQHeader;
}

void CIQ::ReadDataHeader()
{
	memcpy( & m_IQHeader, m_pRawDataBuffer, sizeof(STR_IQ_HEADER) );
}

/**
  * @brief		IQ 데이터 구조에 저장한다.
  * @return 	void
  * @date       2019/06/07 10:11
*/
void CIQ::ConvertArray( STR_PDWDATA *pPDWData, bool bSwap, STR_FILTER_SETUP *pFilterSetup )
{
	UINT i;

	float *psI = m_IQData.pfI;
	float *psQ = m_IQData.pfQ;
	float *psPA = m_IQData.pfPA;
	float *psIP = m_IQData.pfIP;
	float *psFFT = m_IQData.pfFFT;

	float fVal1, fVal2;

	TNEW_IQ *pIQ = (TNEW_IQ *) & m_pRawDataBuffer[m_uiLengthOfHeader];

	for (i = 0; i < m_RawData.uiDataItems; ++i) {
		*psI = (float) pIQ->sI;
		*psQ = (float) pIQ->sQ;

		// 순시 진폭
		*psPA = sqrt( *psI * *psI + *psQ * *psQ );
		*psPA = (float) (20.*log10( *psPA ) ) - (float) 80.;

		// 순시 위상차
		// 		if( i == 0 ) {
		// 			*psIP = 0.0;
		// 			fVal2 = (float) ( atan2( *psQ, *psI ) * RAD2DEG );
		// 		}
		// 		else {
		// 			fVal1 = (float) ( atan2( *psQ, *psI ) * RAD2DEG );
		// 			*psIP = fVal1 - fVal2;
		// 			fVal2 = fVal1;
		// 		}
		// 		if( *psIP > 180. ) {
		// 			*psIP -= ( 2 * 180. );
		// 		}
		// 		else if( *psIP < -180 ) {
		// 			*psIP += ( 2 * 180. );
		// 		}
		// 		else {
		// 
		// 		}

		if( i == 0 ) {
			*psIP = 0.0;
			fVal2 = (float) ( atan2( *psQ, *psI ) * RAD2DEG );
		}
		else {
			fVal1 = (float) ( atan2( *psQ, *psI ) * RAD2DEG );
			*psIP = fVal1;
		}

		// printf( "\n [%3d] %10d %10d" , i+1, *psI, *psQ );

		++psI;
		++psQ;
		++psPA;
		++psIP;

		++pIQ;
	}

    ExecuteFFT( m_RawData.uiDataItems, & m_IQData );

}

//////////////////////////////////////////////////////////////////////////

CEIQ::CEIQ(STR_RAWDATA *pRawData) : CData(pRawData )
{
	Alloc( IQ_ITEMS );
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
CEIQ::~CEIQ(void)
{
	Free();
}


/**
 * @brief     
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/02/27 21:44:08
 * @warning   
 */
void CEIQ::Alloc( int iItems )
{

	if( iItems == 0 ) {
		iItems = m_RawData.uiDataItems;
	}

	m_IQData.pfI = (float *)malloc( sizeof(float) * iItems );
	m_IQData.pfQ = (float *)malloc( sizeof(float) * iItems );
	m_IQData.pfPA = (float *)malloc( sizeof(float) * iItems );
	m_IQData.pfIP = (float *)malloc( sizeof(float) * iItems );
	m_IQData.pfFFT = (float *)malloc( sizeof(float) * iItems );
	
}

/**
 * @brief     
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/02/27 21:44:09
 * @warning   
 */
void CEIQ::Free()
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
void *CEIQ::GetData()
{
	return & m_IQData;
}

/**
  * @brief		IQ 데이터 구조에 저장한다.
  * @return 	void
  * @date       2019/06/07 10:11
*/
void CEIQ::ConvertArray( STR_PDWDATA *pPDWData, bool bSwap, STR_FILTER_SETUP *pFilterSetup )
{
    unsigned int i;

	float *psI = m_IQData.pfI;
	float *psQ = m_IQData.pfQ;
	float *psPA = m_IQData.pfPA;
	float *psIP = m_IQData.pfIP;
	float *psFFT = m_IQData.pfFFT;

	float fVal1, fVal2;

	TNEW_IQ *pIQ;

	pIQ = (TNEW_IQ *) & m_pRawDataBuffer[m_uiLengthOfHeader];
// 	if( iOffset <= 0 ) {
//        	pIQ = (TNEW_IQ *) & m_pRawDataBuffer[0];
// 	}	
// 	else {
// 		pIQ = (TNEW_IQ *) & m_pRawDataBuffer[iOffset];
// 	}

    Log( enNormal, _T("ConvertArray()를 [%d]개를 변환합니다.") , m_RawData.uiDataItems );

	m_IQData.iDataItems = 0;

    for (i = 0; i < m_RawData.uiDataItems ; ++i ) {
		*psI = (float) pIQ->sI;
		*psQ = (float) pIQ->sQ;

		// 순시 진폭
		*psPA = sqrt( *psI * *psI + *psQ * *psQ );
		*psPA = (float) (20.*log10( *psPA ) ) - (float) 80.;

		// 순시 위상차
// 		if( i == 0 ) {
// 			*psIP = 0.0;
// 			fVal2 = (float) ( atan2( *psQ, *psI ) * RAD2DEG );
// 		}
// 		else {
// 			fVal1 = (float) ( atan2( *psQ, *psI ) * RAD2DEG );
// 			*psIP = fVal1 - fVal2;
// 			fVal2 = fVal1;
// 		}
// 		if( *psIP > 180. ) {
// 			*psIP -= ( 2 * 180. );
// 		}
// 		else if( *psIP < -180 ) {
// 			*psIP += ( 2 * 180. );
// 		}
// 		else {
// 
// 		}
		if( i == 0 ) {
			*psIP = 0.0;
			fVal2 = (float) ( atan2( *psQ, *psI ) * RAD2DEG );
		}
		else {
			fVal1 = (float) ( atan2( *psQ, *psI ) * RAD2DEG );
			*psIP = fVal1;
		}

		// printf( "\n [%3d] %10d %10d" , i+1, *psI, *psQ );

		++psI;
		++psQ;
		++psPA;
		++psIP;

		++ m_IQData.iDataItems;
		
		++pIQ;
	}

    ExecuteFFT( m_RawData.uiDataItems, & m_IQData );

}


/**
 * @brief		GetHeaderSize
 * @return		unsigned int
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2020/12/24 14:48:53
 * @warning		
 */
unsigned int CEIQ::GetHeaderSize()
{
	return 0; 
}

/**
 * @brief		GetOneDataSize
 * @return		unsigned int
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2020/12/24 14:48:53
 * @warning		
 */
unsigned int CEIQ::GetOneDataSize()
{
	return sizeof(SRxPDWDataRGroup);
}


/**
 * @brief		GetDataItems
 * @return		unsigned int
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2020/12/28 10:19:33
 * @warning		
 */
unsigned int CEIQ::GetDataItems()
{
	return sizeof(TNEW_IQ);
}


/**
 * @brief		ReadDataHeader
 * @param		void
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2020/12/28 10:19:37
 * @warning		
 */
void CEIQ::ReadDataHeader(void)
{


}

//////////////////////////////////////////////////////////////////////////
//


/**
 * @brief		C7IQ
 * @param		STR_RAWDATA * pRawData
 * @return		
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2020/12/24 14:47:22
 * @warning		
 */
C7IQ::C7IQ(STR_RAWDATA *pRawData, STR_FILTER_SETUP *pFilterSetup ) : CData( pRawData )
{
	Alloc( IQ_ITEMS );
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
C7IQ::~C7IQ(void)
{
	Free();
}


/**
 * @brief     
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/02/27 21:44:08
 * @warning   
 */
void C7IQ::Alloc( int iItems )
{

	if( iItems == 0 ) {
		iItems = m_RawData.uiDataItems;
	}

	m_IQData.pfI = (float *)malloc( sizeof(float) * iItems );
	m_IQData.pfQ = (float *)malloc( sizeof(float) * iItems );
	m_IQData.pfPA = (float *)malloc( sizeof(float) * iItems );
	m_IQData.pfIP = (float *)malloc( sizeof(float) * iItems );
	m_IQData.pfFFT = (float *)malloc( sizeof(float) * iItems );
	
}

/**
 * @brief     
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/02/27 21:44:09
 * @warning   
 */
void C7IQ::Free()
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
void *C7IQ::GetData()
{
	return & m_IQData;
}

/**
  * @brief		IQ 데이터 구조에 저장한다.
  * @return 	void
  * @date       2019/06/07 10:11
*/
void C7IQ::ConvertArray( STR_PDWDATA *pPDWData, bool bSwap, STR_FILTER_SETUP *pFilterSetup )
{
	unsigned int ui;

	float *psI = m_IQData.pfI;
	float *psQ = m_IQData.pfQ;
	float *psPA = m_IQData.pfPA;
	float *psIP = m_IQData.pfIP;
	float *psFFT = m_IQData.pfFFT;

	float fVal1, fVal2;

	SRxIQDataRGroup1 *pIQ;

    pIQ = (SRxIQDataRGroup1 *) & m_pRawDataBuffer[m_uiLengthOfHeader];
// 	if( iOffset <= 0 ) {
// 		pIQ = (SRxIQDataRGroup1 *) & m_pRawDataBuffer[0];
// 	}
// 	else {
// 		pIQ = (SRxIQDataRGroup1 *) & m_pRawDataBuffer[iOffset];
// 	}

	m_IQData.iDataItems = 0;

    for (ui = 0; ui < m_RawData.uiDataItems ; ++ui ) {
		*psI = (float) ( (short) ( pIQ->sIData ^ (0x8A5A) ) );
		*psQ = (float) ( (short) ( pIQ->sQData ^ (0x8A5A) ) );

		// 순시 진폭
		*psPA = sqrt( *psI * *psI + *psQ * *psQ );
		*psPA = (float) (20.*log10( *psPA ) ) - (float) 80.;

		// 순시 위상차
/*
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

		}		*/
		if( ui == 0 ) {
			*psIP = 0.0;
			fVal2 = (float) ( atan2( *psQ, *psI ) * RAD2DEG );
		}
		else {
			fVal1 = (float) ( atan2( *psQ, *psI ) * RAD2DEG );
			*psIP = fVal1;
		}

		// printf( "\n [%3d] %10d %10d" , i+1, *psI, *psQ );

		++psI;
		++psQ;
		++psPA;
		++psIP;

		++ m_IQData.iDataItems;
		
		++pIQ;
	}

    ExecuteFFT( m_RawData.uiDataItems, & m_IQData );

}

/**
 * @brief		CMIDAS
 * @param		STR_RAWDATA * pRawData
 * @return		
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2020/12/28 10:53:28
 * @warning		
 */
CMIDAS::CMIDAS(STR_RAWDATA *pRawData) : CData( pRawData )
{
	//Alloc( IQ_ITEMS );
	m_pSubRecords = 0;

	memset( & m_PDWData, 0, sizeof(STR_PDW_DATA) );
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
CMIDAS::~CMIDAS(void)
{
	Free();
}


/**
 * @brief     
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/02/27 21:44:08
 * @warning   
 */
void CMIDAS::Alloc( int iItems )
{
	Log( enNormal, _T("Alloc()을 [%d]개를 할당합니다.") , iItems );

	m_PDWData.iDataItems = iItems;

	if( m_PDWData.pfFreq == NULL ) {
		m_PDWData.pfFreq = (float *) malloc(sizeof(float) * iItems );
	}

	if( m_PDWData.pfPW == NULL ) {
		m_PDWData.pfPW = (float *) malloc(sizeof(float) * iItems );
	}

	if( m_PDWData.pfAOA == NULL ) {
		m_PDWData.pfAOA = (float *) malloc(sizeof(float) * iItems );
	}

	if( m_PDWData.pfTOA == NULL ) {
		m_PDWData.pfTOA = (float *) malloc(sizeof(float) * iItems );
	}

	if( m_PDWData.pfDTOA == NULL ) {
		m_PDWData.pfDTOA = (float *) malloc(sizeof(float) * iItems );
	}

	if( m_PDWData.pfPA == NULL ) {
		m_PDWData.pfPA = (float *) malloc(sizeof(float) * iItems );
	}

	if( m_PDWData.pullTOA == NULL ) {
		m_PDWData.pullTOA = (_TOA *) malloc(sizeof(_TOA) * iItems );
	}

	if( m_PDWData.pcType == NULL ) {
		m_PDWData.pcType = (char *) malloc(sizeof(char) * iItems );
	}

	if( m_PDWData.pcDV == NULL ) {
		m_PDWData.pcDV = (char *) malloc(sizeof(char) * iItems );
	}

}

/**
 * @brief     
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/02/27 21:44:09
 * @warning   
 */
void CMIDAS::Free()
{
	Log( enNormal, _T("Free()를 해지합니다.") );

	free(m_PDWData.pfFreq);
	free(m_PDWData.pfPW);
	free(m_PDWData.pfAOA);
	free(m_PDWData.pfTOA);
	free(m_PDWData.pfDTOA);
	free(m_PDWData.pfPA);
	free(m_PDWData.pullTOA);

	free(m_PDWData.pcType);
	free(m_PDWData.pcDV);

	if( m_pSubRecords != 0 ) {
		free( m_pSubRecords );
	}

}

/**
 * @brief     
 * @return    void *
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/02/27 21:44:12
 * @warning   
 */
void *CMIDAS::GetData()
{
	return & m_PDWData;
}

/**
  * @brief		IQ 데이터 구조에 저장한다.
  * @return 	void
  * @date       2019/06/07 10:11
*/
void CMIDAS::ConvertArray( STR_PDWDATA *pPDWData, bool bSwap, STR_FILTER_SETUP *pFilterSetup )
{
	unsigned int ui;

	S_EL_PDW_RECORDS strPDWRecords;

	float fPreToa;

    Alloc( m_RawData.uiDataItems );

	float *pfFreq = m_PDWData.pfFreq;
	float *pfPW = m_PDWData.pfPW;
	float *pfAOA = m_PDWData.pfAOA;
	float *pfTOA = m_PDWData.pfTOA;
	float *pfDTOA = m_PDWData.pfDTOA;
	float *pfPA = m_PDWData.pfPA;

	_TOA *pullTOA = m_PDWData.pullTOA;

	char *pcType = m_PDWData.pcType;
	char *pcDV = m_PDWData.pcDV;	

	m_pDataChar = (char *) & m_pRawDataBuffer[0];
	
	m_PDWData.iDataItems = 0;

    Log( enNormal, _T("ConvertArray()를 [%d]개를 변환합니다.") , m_RawData.uiDataItems );

    for( ui=0 ; ui < m_RawData.uiDataItems ; ++ui ) {
		GetSubRecords( & strPDWRecords );

		//*pfTOA = (float) strPDWRecords.ltoa / 1000.;
        *pfTOA = (float) ( strPDWRecords.ltoa / 1000000000. );

        if( ui == 0 ) {
            *pfDTOA = 0.0;
        }
        else {
            *pfDTOA = *pfTOA - fPreToa;
        }
        fPreToa = *pfTOA;

		*pfAOA = (float) strPDWRecords.ldoa;
		*pfPA = (float) strPDWRecords.lpa;
		//*pfPW = (float) strPDWRecords.lpw * 1000000000.;
        *pfPW = (float) strPDWRecords.lpw;
		*pfFreq = (float) ( strPDWRecords.lfreq / 1000000. );
        //*pfFreq = (float) strPDWRecords.lfreq;
        
        *pcDV = PDW_DV;

        *pcType = 0;

        *pullTOA = 0;

		//*pfFreq = GetFreq();

		// 필터링 조건
        if( pFilterSetup == NULL || ( pFilterSetup->enSubGraph == enUnselectedSubGraph || \
            ( ( ( pFilterSetup->dToaMin == 0 ) || ( pFilterSetup->dToaMin <= *pfTOA && *pfTOA <= pFilterSetup->dToaMax ) ) && \
            ( ( pFilterSetup->dAoaMin == 0 ) || ( pFilterSetup->dAoaMin <= *pfAOA && *pfAOA <= pFilterSetup->dAoaMax ) ) && \
            ( ( pFilterSetup->dFrqMin == 0 ) || ( pFilterSetup->dFrqMin <= *pfFreq && *pfFreq <= pFilterSetup->dFrqMax ) ) && \
            ( ( pFilterSetup->dPAMin == 0 ) || ( pFilterSetup->dPAMin <= *pfPA && *pfPA <= pFilterSetup->dPAMax ) ) ) ) ) {
				++pfFreq;
				++pfAOA;
				++pfPW;
				++pfPA;
				++pfTOA;
				++pfDTOA;
				++pcType;
				++pcDV;
				++pullTOA;

				++ m_PDWData.iDataItems;

				//++ m_stFilterSetup.uiDataItems;
		}
	}

}

/**
 * @brief		GetSubRecords
 * @param		S_EL_PDW_RECORDS * pPDWRecords
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2020/12/28 11:26:37
 * @warning		
 */
void CMIDAS::GetSubRecords( S_EL_PDW_RECORDS *pPDWRecords )
{
	unsigned int i;
	SELSUBRECORDS *pSubRecords;

	pSubRecords = m_pSubRecords;
	for( i=0 ; i < m_ADJ._6000.subrecords ; ++i ) {
        if( strncmp( pSubRecords->name, stSubrecordName[enTOAOfSub], strlen(stSubrecordName[enTOAOfSub]) ) == 0 ) {
			pPDWRecords->ltoa = GetSubValue( pSubRecords->format );
		}
        else if( strncmp( pSubRecords->name, stSubrecordName[enDTOAOfSub], strlen(stSubrecordName[enDTOAOfSub]) ) == 0 ) {
			pPDWRecords->ldtoa = GetSubValue( pSubRecords->format );
		}
        else if( strncmp( pSubRecords->name, stSubrecordName[enFreqOfSub], strlen(stSubrecordName[enFreqOfSub]) ) == 0 ) {
			pPDWRecords->lfreq = GetSubValue( pSubRecords->format );
		}
        else if( strncmp( pSubRecords->name, stSubrecordName[enPWOfSub], strlen(stSubrecordName[enPWOfSub]) ) == 0 ) {
			pPDWRecords->lpw = GetSubValue( pSubRecords->format );
		}
        else if( strncmp( pSubRecords->name, stSubrecordName[enPAOfSub], strlen(stSubrecordName[enPAOfSub]) ) == 0 ) {
			pPDWRecords->lpa = GetSubValue( pSubRecords->format );
		}
        else if( strncmp( pSubRecords->name, stSubrecordName[enDOAOfSub], strlen(stSubrecordName[enDOAOfSub]) ) == 0 ) {
			pPDWRecords->ldoa = GetSubValue( pSubRecords->format );
		}
		else {
            printf( "서브 레코드(%s)에 맞는 것이 없습니다 !!" , pSubRecords->name );
			++ pSubRecords;
		}

		++ pSubRecords;
	}
		
}

/**
 * @brief		GetSubValue
 * @param		char * psubformat
 * @return		long double
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2020/12/28 11:57:28
 * @warning		
 */
double CMIDAS::GetSubValue( char *psubformat )
{
	double dvalue=0;

	char ch;
	short sh;
	int in;
	float fl;
	double du;
    long int li;

	switch( psubformat[1] ) {
		case DATA_FORMAT_TYPE_DESIGNATOR_ASCII :
		case DATA_FORMAT_TYPE_DESIGNATOR__8BIT_INTEGER :
			memcpy( & ch, m_pDataChar, sizeof(char) );
			m_pDataChar += 1;
			break;
		case DATA_FORMAT_TYPE_DESIGNATOR_16BIT_INTEGER :
			memcpy( & sh, m_pDataChar, sizeof(short) );
			m_pDataChar += 2;
			break;
		case DATA_FORMAT_TYPE_DESIGNATOR_32BIT_INTEGER :
			memcpy( & in, m_pDataChar, sizeof(int) );
			m_pDataChar += 4;
			break;

		case DATA_FORMAT_TYPE_DESIGNATOR_32BIT_FLOAT :
			memcpy( & fl, m_pDataChar, sizeof(float) );
			m_pDataChar += 4;
			break;

		case DATA_FORMAT_TYPE_DESIGNATOR_64BIT_INTEGER :
			memcpy( & li, m_pDataChar, sizeof(long int) );
            dvalue = (long int) li;
			m_pDataChar += sizeof(long int);
			break;

		case DATA_FORMAT_TYPE_DESIGNATOR_64BIT_FLOAT :
			memcpy( & du, m_pDataChar, sizeof(double) );
			dvalue = (double) du;
			m_pDataChar += sizeof( double );
			break;

		case DATA_FORMAT_TYPE_DESIGNATOR_4BIT_INTEGER :
			// iSize = 4;
			break;

		default :
			// iSize = 8;
			break;
	}

	return dvalue;
}

/**
 * @brief		GetHeaderSize
 * @return		unsigned int
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2020/12/24 14:48:53
 * @warning		
 */
unsigned int CMIDAS::GetHeaderSize()
{

    if( m_iHeaderSize == -1 ) {
	    memcpy( & m_HCB, m_pRawHeaderBuffer, sizeof(SELMIDAS_HCB) );

	    if( m_HCB.type == MIDAS_FILE_TYPE_1001 ) {
		    memcpy( & m_ADJ._1000, & m_pRawHeaderBuffer[0x100], sizeof(SELMIDAS_ADJUNCT_TYPE_1000) );
	    }
	    else if( m_HCB.type == MIDAS_FILE_TYPE_6003 ) {
		    memcpy( & m_ADJ._6000, & m_pRawHeaderBuffer[0x100], sizeof(SELMIDAS_ADJUNCT_TYPE_6000) );

		    m_pSubRecords = ( SELSUBRECORDS * ) malloc( m_ADJ._6000.subrecords * sizeof(SELSUBRECORDS) );
		    memcpy( m_pSubRecords, & m_pRawHeaderBuffer[0x100+sizeof(SELMIDAS_ADJUNCT_TYPE_6000)], m_ADJ._6000.subrecords * sizeof(SELSUBRECORDS) );
	    }
	    else {

	    }	

        m_iHeaderSize = HEADER_CONTROL_BLOCK_SIZE;
    }

	return m_iHeaderSize;
}

/**
 * @brief		GetOneDataSize
 * @return		unsigned int
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2021/01/08 13:38:43
 * @warning		
 */
unsigned int CMIDAS::GetOneDataSize()
{
    if( m_iOneDataSize == -1 ) {
        if( m_HCB.type == MIDAS_FILE_TYPE_1001 ) {

        }
        else if( m_HCB.type == MIDAS_FILE_TYPE_6003 ) {
            m_iOneDataSize = m_ADJ._6000.record_length;
        }
        else {

        }
    }

    return m_iOneDataSize;
}

/**
 * @brief		GetDataSize
 * @return		unsigned int
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2020/12/24 15:02:30
 * @warning		
 */
unsigned int CMIDAS::GetDataItems()
{
	unsigned int i, iBit=0;
	SELSUBRECORDS *pSubRecords;

	//memcpy( & m_HCB, m_pRawDataBuffer, sizeof(SELMIDAS_HCB) );

	if( m_HCB.type == MIDAS_FILE_TYPE_1001 ) {
		m_enFileType = E_EL_SCDT_IQ;

		iBit = 16;
	}
	else if( m_HCB.type == MIDAS_FILE_TYPE_6003 ) {
		m_enFileType = E_EL_SCDT_PDW;

		pSubRecords = m_pSubRecords;
		for( i=0, iBit=0 ; i < m_ADJ._6000.subrecords ; ++i ) {
			iBit += GetDataFormatSize( pSubRecords->format[1] );
			++ pSubRecords;
		}
		
	}
	else {
		m_enFileType = E_EL_SCDT_UNKNOWN;
	}
	
	return (unsigned int) ( m_HCB.data_size / ( iBit / 8. ) );
}


/**
 * @brief		GetDataFormatSize
 * @param		char ch
 * @return		int
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2020/12/24 16:06:31
 * @warning		
 */
int CMIDAS::GetDataFormatSize( char ch )
{
	int iSize;

	switch( ch ) {
		case DATA_FORMAT_TYPE_DESIGNATOR_ASCII :
		case DATA_FORMAT_TYPE_DESIGNATOR__8BIT_INTEGER :
			iSize = 8;
			break;
		case DATA_FORMAT_TYPE_DESIGNATOR_16BIT_INTEGER :
			iSize = 16;
			break;
		case DATA_FORMAT_TYPE_DESIGNATOR_32BIT_INTEGER :
		case DATA_FORMAT_TYPE_DESIGNATOR_32BIT_FLOAT :
			iSize = 32;
			break;
		case DATA_FORMAT_TYPE_DESIGNATOR_64BIT_INTEGER :
		case DATA_FORMAT_TYPE_DESIGNATOR_64BIT_FLOAT :
			iSize = 64;
			break;

		case DATA_FORMAT_TYPE_DESIGNATOR_4BIT_INTEGER :
			iSize = 4;
			break;

		default :
			iSize = 8;
			break;
	}

	return iSize;
}

void CMIDAS::ReadDataHeader(void)
{


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

    m_iHeaderSize = -1;
    m_iOneDataSize = -1;

    m_pRawDataBuffer = 0;
    m_pRawHeaderBuffer = (char *) malloc(sizeof(char)* MAX_HEADER_SIZE );

	m_uiWindowNumber = 0;

	m_bPhaseData = true;

	ClearFilterSetup();

}


/**
 * @brief		ClearFilterSetup
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2021/01/08 12:41:24
 * @warning		
 */
void CData::ClearFilterSetup()
{

	m_strFilterSetup.dToaMin = 0.;
	m_strFilterSetup.dToaMax = DBL_MAX;
	m_strFilterSetup.dDtoaMin = 0;
	m_strFilterSetup.dDtoaMax = DBL_MAX;
	m_strFilterSetup.dAoaMin = 0;
	m_strFilterSetup.dAoaMax = DBL_MAX;
	m_strFilterSetup.dFrqMin = 0;
	m_strFilterSetup.dFrqMax = DBL_MAX;
	m_strFilterSetup.dPAMin = -DBL_MAX;
	m_strFilterSetup.dPAMax = DBL_MAX;
	m_strFilterSetup.dPWMin = 0;
	m_strFilterSetup.dPWMax = DBL_MAX;

	//m_strFilterSetup.uiDataItems = 0;

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
    _SAFE_FREE( m_pRawHeaderBuffer );
}


/**
 * @brief CData::AllSwapData32
 * @param pData
 * @param iLength
 */
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

/**
 * @brief CData::swapByteOrder
 * @param ull
 */
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

/**
 * @brief CData::swapByteOrder
 * @param ui
 */
void CData::swapByteOrder(unsigned int& ui) 
{
	ui = (ui >> 24) |
		((ui<<8) & 0x00FF0000) |
		((ui>>8) & 0x0000FF00) |
		(ui << 24);
}


/**
 * @brief     
 * @param     int iDataItems
 * @param     STR_IQ_DATA * pIQData
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/03/16 22:31:50
 * @warning   
 */
void CData::ExecuteFFT( int iDataItems, STR_IQ_DATA *pIQData )
{
	int i;

	float *psI, *psQ;

	float *psFFT = pIQData->pfFFT;

#ifdef _FFTW_

	fftw_complex *pIn, *pOut;
	fftw_complex *pP;
	fftw_plan plan;

	int N = iDataItems, nShift;

	if( iDataItems != 0 ) {
		pIn = ( fftw_complex * ) fftw_malloc( sizeof(fftw_complex) * N );
		pOut = ( fftw_complex * ) fftw_malloc( sizeof(fftw_complex) * N );
		plan = fftw_plan_dft_1d( N, pIn, pOut, FFTW_FORWARD, FFTW_ESTIMATE );

		psI = pIQData->pfI;
		psQ = pIQData->pfQ;

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
		for( i=0 ; i < (N/2) ; ++i ) {
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
	}
#endif

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
	m_iFileIndex = 0;

	m_pData = NULL;

	m_szPathname[0] = 0;

	Alloc();

//     if( stDataFile == 0 ) {
//         m_pData->m_pRawDataBuffer = 0;
//     }

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

}

/**
 * @brief CDataFile::Free
 */
void CDataFile::Free()
{

	if( m_pData != NULL ) {
        // DeltaGraph 인 경우에 아래 루틴을 처리할 필요가 없음. 
#ifndef _WINDOWS
		delete m_pData;
		m_pData = NULL;
#endif

	}

}

/**
  * @brief		RAW 데이터 파일 읽기
  * @param		CString & strPathname
  * @return 	void
  * @return		성공시 true, 실패시 false
  * @date       2019/05/31 10:34
*/
CData *CDataFile::ReadDataFile( char *pPathname, int iFileIndex, CData *pData, STR_FILTER_SETUP *pstFilterSetup )
{
	int iDataItems;
	ENUM_DataType enDataType;
	ENUM_UnitType enUnitType;

	if( m_szPathname[0] == 0 ) {
		strcpy( m_szPathname, pPathname );

		enUnitType = WhatUnitType( m_szPathname );
		enDataType = WhatDataType( m_szPathname );

	}
	else {
		enUnitType = m_pData->m_RawData.enUnitType;
		enDataType = m_pData->m_RawData.enDataType;
	}

	if( enDataType == en_PDW_DATA && enUnitType == en_SONATA ) {
		//uiLengthOfHeader = 0;
		//uiLengthOf1PDWIQ = sizeof(TNEW_PDW);

		if( m_pData == NULL ) {
			m_pData = pData;
			if( m_pData == NULL ) {
				m_pData = new CPDW( NULL );

				iDataItems = LoadRawData( m_pData, iFileIndex );
			}
			else {
				iDataItems = m_pData->m_RawData.uiDataItems;
			}
		}
		else {
			iDataItems = m_pData->m_RawData.uiDataItems;
		}

	}
	else if( enDataType == en_PDW_DATA && enUnitType == en_SONATA_SHU ) {
		if( m_pData == NULL ) {
			m_pData = pData;
			if( m_pData == NULL ) {
				//uiLengthOfHeader = 0;
				//uiLengthOf1PDWIQ = sizeof(TNEW_PDW);

				m_pData = new CSPDW( NULL );

				iDataItems = LoadRawData( m_pData, iFileIndex );
			}
			else {
				iDataItems = m_pData->m_RawData.uiDataItems;
			}
		}
		else {
			iDataItems = m_pData->m_RawData.uiDataItems;
		}

	}

	else if( enDataType == en_PDW_DATA && enUnitType == en_ELINT ) {
		//uiLengthOfHeader = (sizeof(STR_PDWDATA)-sizeof(_PDW)*MAX_PDW);
		//uiLengthOf1PDWIQ = sizeof(_PDW);

		if( m_pData == NULL ) {
			m_pData = pData;
			if( m_pData == NULL ) {
				m_pData = new CEPDW( NULL, pstFilterSetup );
			}
		}

		iDataItems = LoadRawData( m_pData, iFileIndex );

	}

	else if( enDataType == en_PDW_DATA && enUnitType == en_701 ) {
		if( m_pData == NULL ) {
			m_pData = pData;
			if( m_pData == NULL ) {
				m_pData = new C7PDW( NULL, pstFilterSetup );
				iDataItems = LoadRawData( m_pData, iFileIndex );
			}
		}
        else {
            memcpy( & m_pData->m_strFilterSetup, pstFilterSetup, sizeof(STR_FILTER_SETUP) );
            //iDataItems = LoadRawData( m_pData, iFileIndex );
            //unsigned int uiLengthOfHeader = m_pData->GetHeaderSize();
            m_pData->ConvertArray( NULL, false );
        }
	}

	else if( enDataType == en_IQ_DATA && enUnitType == en_701 ) {
		//uiLengthOfHeader = sizeof(SRxIQHeader);
		//uiLengthOf1PDWIQ = sizeof(SRXIQDataRGroup);

		if( m_pData == NULL ) {
			m_pData = pData;
			if( m_pData == NULL ) {
                m_pData = new C7IQ( NULL, pstFilterSetup );
				iDataItems = LoadRawData( m_pData, iFileIndex );
			}
		}		

	}

	else if( enDataType == en_PDW_DATA && enUnitType == en_ZPOCKETSONATA ) {
		//uiLengthOfHeader = sizeof(STR_PDWFILE_HEADER);
		//uiLengthOf1PDWIQ = sizeof(DMAPDW);

		if( m_pData == NULL ) {
			m_pData = pData;
			if( m_pData == NULL ) {
                m_pData = new CPOCKETSONATAPDW( NULL, pstFilterSetup, 0 );
				iDataItems = LoadRawData( m_pData, iFileIndex );
			}
			else {

			}
		}
		else {
            pData->ConvertArray( NULL, /* uiLengthOfHeader*/ 0, pstFilterSetup );
		}

		STR_PDW_DATA *pPDWData = (STR_PDW_DATA *) GetData();
		iDataItems = pPDWData->iDataItems;

	}

	else if( enDataType == en_PDW_DATA && enUnitType == en_KFX ) {
		//uiLengthOfHeader = sizeof(STR_PDWFILE_HEADER);
		//uiLengthOf1PDWIQ = sizeof(UDRCPDW);

		if( m_pData == NULL ) {
			m_pData = pData;
			if( m_pData == NULL ) {
				m_pData = new CKFXPDW( NULL, pstFilterSetup );
				iDataItems = LoadRawData( m_pData, iFileIndex );
			}
			else {

			}
		}
		iDataItems = m_pData->m_RawData.uiDataItems;


		// 		if( m_RawDataFile.m_hFile == (HANDLE) -1 && m_RawDataFile.Open( m_strPathname.GetBuffer(), CFile::shareDenyNone | CFile::typeBinary) == TRUE ) {
		// 			if( m_pData == NULL ) {
		// 				m_pData = new CKFXPDW( & m_RawData, pstFilterSetup );
		// 			}
		// 
		// 		}
		// 		STR_PDWFILE_HEADER *pPDWFile;
		// 
		// 		if( iFileIndex <= 0 ) {
		// 			m_iFileIndex = 0;
		// 
		// 			m_dwFileEnd = m_RawDataFile.SeekToEnd();
		// 			m_RawDataFile.Seek( 0, CFile::begin );
		// 
		// 			m_RawData.uiByte = m_RawDataFile.Read( m_pRawDataBuffer, sizeof(STR_PDWFILE_HEADER) + sizeof(UDRCPDW)*PDW_ITEMS );
		// 
		// 			pPDWFile = ( STR_PDWFILE_HEADER * ) m_pRawDataBuffer;
		// 
		// 			m_RawData.uiDataItems = pPDWFile->uiSignalCount;
		// 
		// 			iDataItems = ( m_RawData.uiByte - sizeof(STR_PDWFILE_HEADER) ) / sizeof(UDRCPDW);
		// 
		// 			m_pData->ConvertArray( iDataItems, sizeof(STR_PDWFILE_HEADER) );
		// 		}
		// 		else {
		// 			m_iFileIndex = iFileIndex;
		// 
		// 			m_RawDataFile.Seek( sizeof(STR_PDWFILE_HEADER) + sizeof(UDRCPDW)*(m_iFileIndex*PDW_ITEMS), CFile::begin );
		// 
		// 			m_RawData.uiByte = m_RawDataFile.Read( m_pRawDataBuffer, sizeof(UDRCPDW)*PDW_ITEMS );
		// 
		// 			iDataItems = m_RawData.uiByte / sizeof(UDRCPDW);
		// 
		// 			m_pData->ConvertArray( iDataItems, 0 );
		// 
		// 		}

	}

	//////////////////////////////////////////////////////////////////////////
	else if( enDataType == en_IQ_DATA && enUnitType == en_SONATA ) {
		//uiLengthOfHeader = sizeof(STR_IQ_HEADER);
		//uiLengthOf1PDWIQ = sizeof(TNEW_IQ);

		if( m_pData == NULL ) {
			m_pData = pData;
			if( m_pData == NULL ) {
				m_pData = new CIQ( NULL );
				iDataItems = LoadRawData( m_pData, iFileIndex );
			}
			else {
				iDataItems = m_pData->m_RawData.uiDataItems;
			}
		}
		else {
			iDataItems = m_pData->m_RawData.uiDataItems;
		}

		// 		if (m_RawDataFile.Open( strPathname.GetBuffer(), CFile::modeRead | CFile::typeBinary) == TRUE) {
		// 			m_RawData.uiByte = m_RawDataFile.Read( m_pRawDataBuffer, MAX_RAWDATA_SIZE );
		// 			m_RawData.uiDataItems = m_RawData.uiByte / sizeof(TNEW_IQ);
		// 
		// 			m_pData = new CIQ( & m_RawData );
		// 
		// 			m_pData->ConvertArray( 0 );
		// 
		// 			m_RawDataFile.Close();
		// 
		// 		}
		// 		else {
		// 			m_RawData.uiByte = -1;
		// 			m_RawData.uiDataItems = -1;
		// 		}

	}

	//////////////////////////////////////////////////////////////////////////
	else if( enDataType == en_IQ_DATA && enUnitType == en_ELINT ) {
		if( m_pData == NULL ) {
			m_pData = pData;
			if( m_pData == NULL ) {
				m_pData = new CEIQ( NULL );
				iDataItems = LoadRawData( m_pData, iFileIndex );
			}
			else {

			}
		}
		iDataItems = m_pData->m_RawData.uiDataItems;

		//iDataItems = LoadRawData( m_pData, iFileIndex, uiLengthOfHeader, uiLengthOf1PDWIQ );

		// 		if( m_RawDataFile.m_hFile == (HANDLE) -1 && m_RawDataFile.Open( m_strPathname.GetBuffer(), CFile::shareDenyNone | CFile::typeBinary) == TRUE ) {
		// 			if( m_pData == NULL ) {
		// 				m_pData = new CEIQ( & m_RawData );
		// 			}
		// 		}
		// 
		// 		if( iFileIndex <= 0 ) {
		// 			m_iFileIndex = 0;
		// 
		// 			m_dwFileEnd = m_RawDataFile.SeekToEnd();
		// 			m_RawDataFile.Seek( 0, CFile::begin );
		// 
		// 			m_RawData.uiByte = m_RawDataFile.Read( m_pRawDataBuffer, sizeof(TNEW_IQ)*IQ_ITEMS );
		// 
		// 			m_RawData.uiDataItems = m_RawData.uiByte /*m_dwFileEnd*/ / sizeof(TNEW_IQ);
		// 
		// 			iDataItems = m_RawData.uiByte / sizeof(TNEW_IQ);
		// 
		// 			m_pData->ConvertArray( iDataItems, -1 );
		// 
		// 		}
		// 		else {
		// 			m_iFileIndex = iFileIndex;
		// 
		// 			//m_RawDataFile.Seek( sizeof(STR_PDWFILE_HEADER) + sizeof(UDRCPDW)*(m_iFileIndex*IQ_ITEMS), CFile::begin );
		// 
		// 			m_RawData.uiByte = m_RawDataFile.Read( m_pRawDataBuffer, sizeof(TNEW_IQ)*IQ_ITEMS );
		// 
		// 			iDataItems = m_RawData.uiByte / sizeof(TNEW_IQ);
		// 
		// 			m_pData->ConvertArray( iDataItems, 0 );
		// 		}

	}
	else if( enUnitType == en_MIDAS ) {
		if( m_pData == NULL ) {
			m_pData = pData;
			if( m_pData == NULL ) {
				m_pData = new CMIDAS( NULL );
				iDataItems = LoadRawData( m_pData, iFileIndex );
			}
			else {

			}
		}
        else {
            pData->ConvertArray( NULL, /* uiLengthOfHeader*/ 0, pstFilterSetup );
        }

        STR_PDW_DATA *pPDWData = (STR_PDW_DATA *) GetData();
        iDataItems = pPDWData->iDataItems;

	}
	else {

	}

	m_pData->m_RawData.enUnitType = enUnitType;
	m_pData->m_RawData.enDataType = enDataType;

	STR_PDW_DATA *pPDWData = (STR_PDW_DATA *) GetData();
	iDataItems = pPDWData->iDataItems;

	// 파일 닫기 처리
	if( m_RawDataFile.GetFileHandler() != NULL ) {
		m_RawDataFile.FileClose();
		Log( enNormal, _T("파일을 닫습니다.") );
	}

	Log( enNormal, _T("현재 위치[%d], 총 개수[%d]") , m_iFileIndex, iDataItems );

	return m_pData;

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
#endif

    if( enUnitType == en_SONATA || enUnitType == en_KFX ) {
        if( enDataType == en_PDW_DATA) {

            if( ! m_RawDataFile.FileOpen( pstPathname, O_CREAT | O_BINARY ) ) {
                //LOGMSG1( enWarning, _T("PDW 데이터 파일[%s]을 생성하지 못합니다 !") , strPathname );
            }
            else {
                m_RawDataFile.Write( pData, iNumData );
                m_RawDataFile.FileClose();
            }
        }
        else if( enDataType == en_IQ_DATA ) {
            if( ! m_RawDataFile.FileOpen( pstPathname, O_CREAT | O_BINARY ) ) {
                //Log( enError, _T("IQ 데이터 파일[%s]을 생성하지 못합니다 !") , strPathname );
            }
            else {
                // IQ 헤더 정보 저장
                if( pDataEtc != NULL ) {
                    m_RawDataFile.Write( pDataEtc, iSizeOfEtc );
                }

                m_RawDataFile.Write( pData, iNumData );
                m_RawDataFile.FileClose();
            }
        }
    }

}


/**
 * @brief     
 * @return    ENUM_DataType
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/03/12 19:36:17
 * @warning   
 */
ENUM_DataType CDataFile::WhatDataType( char *pStrPathname )
{
	ENUM_DataType enDataType=en_UnknownData;

	if( NULL != strstr( pStrPathname, ".pdw" ) || NULL != strstr( pStrPathname, ".npw" ) || NULL != strstr( pStrPathname, ".spdw" ) ) {
		enDataType = en_PDW_DATA;
	}
	else if( NULL != strstr( pStrPathname, "e4.dat" ) ) {
		enDataType = en_PDW_DATA;
	}
	else if( NULL != strstr( pStrPathname, ".kpdw" ) ) {
		enDataType = en_PDW_DATA;
	}
	else if( NULL != strstr( pStrPathname, ".iq" ) || NULL != strstr( pStrPathname, ".siq" ) || 
			 NULL != strstr( pStrPathname, "e2.dat" ) || NULL != strstr( pStrPathname, ".eiq" ) ) {
		enDataType = en_IQ_DATA;
	}
	else if( NULL != strstr( pStrPathname, ".epdw" ) || NULL != strstr( pStrPathname, ".enpw" ) || NULL != strstr( pStrPathname, ".zpdw" ) ) {
		enDataType = en_PDW_DATA;
	}

	return enDataType;

}

/**
 * @brief     
 * @return    ENUM_UnitType
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/03/12 19:38:24
 * @warning   
 */
 ENUM_UnitType CDataFile::WhatUnitType( char *pStrPathname )
{
	ENUM_UnitType enUnitType;

    if( NULL != strstr( pStrPathname, ".midas" ) ) {
        enUnitType = en_MIDAS;
    }
	else if( NULL != strstr( pStrPathname, ".pdw" ) || NULL != strstr( pStrPathname, ".npw" ) ||
		NULL != strstr( pStrPathname, ".iq" ) || NULL != strstr( pStrPathname, ".siq" ) ) {
		enUnitType = en_SONATA;
	}
	else if( NULL != strstr( pStrPathname, ".spdw" ) ) {
		enUnitType = en_SONATA_SHU;
	}
	else if( NULL != strstr( pStrPathname, ".dat" ) ) {
		enUnitType = en_701;
	}
	else if( NULL != strstr( pStrPathname, ".kpdw" ) ) {
		enUnitType = en_KFX;
	}
	else if( NULL != strstr( pStrPathname, ".epdw" ) || NULL != strstr( pStrPathname, ".enpw" ) ) {
		enUnitType = en_ELINT;
	}
	else if( NULL != strstr( pStrPathname, ".zpdw" ) || NULL != strstr( pStrPathname, ".znpw" ) ) {
		enUnitType = en_ZPOCKETSONATA;
	}
	else {
		enUnitType = en_UnknownUnit;
	}

	return enUnitType;

}


 /**
 * @brief     
 * @param     CData * pData
 * @param     int iFileIndex
 * @param     UINT uiHeaderLength
 * @param     UINT uiLengthOf1PDW
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/03/30 19:09:13
 * @warning   
 */
UINT CDataFile::LoadRawData( CData *pData, int iFileIndex )
{
	//UINT uiLengthOfHeader;

	if( m_RawDataFile.FileOpen( m_szPathname, O_RDONLY | O_BINARY ) == TRUE ) {
		Log( enNormal, _T("파일[%s]을 오픈합니다."), m_szPathname );

		// 1. 헤더 파일만 읽기
		ReadDataHeader( pData );

		// 1.1 헤더 크기 계산
		pData->m_uiLengthOfHeader = pData->GetHeaderSize();

		// 1.2 데이터 엘리먼트 계산
		pData->m_RawData.uiDataItems = GetDataItems( pData );

		// 2. 전체 파일 읽기
		ReadDataAll( pData );		
		
		// 2.1 데이터 변환
        pData->ConvertArray( NULL, true );

	}
	else {
		Log( enError, _T("파일[%s]이 존재하지 않습니다."), m_szPathname );
	}

	return pData->m_RawData.uiDataItems;
}

/**
 * @brief		GetHeaderSize
 * @param		CData * pData
 * @return		unsigned int
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2020/12/24 15:25:49
 * @warning		
 */
unsigned int CDataFile::GetHeaderSize( CData *pData )
{
	return pData->GetHeaderSize();
}

unsigned int CDataFile::GetOneDataSize( CData *pData )
{
    return pData->GetOneDataSize();
}

/**
 * @brief		GetDataSize
 * @param		CData * pData
 * @return		unsigned int
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2020/12/24 15:25:45
 * @warning		
 */
// unsigned int CDataFile::GetDataSize( CData *pData )
// {
// 
// 	return -1; // pData->GetDataSize();
// 
// }


/**
 * @brief		ReadDataHeader
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2020/12/28 9:35:52
 * @warning		
 */
void CDataFile::ReadDataHeader( CData *pData )
{
	int iRead;

	m_RawDataFile.SeekToStart();

	// 데이터 파일 중에서 제일 큰 것을 읽는다.
	iRead = m_RawDataFile.Read( pData->m_pRawHeaderBuffer, MAX_HEADER_SIZE );	

	m_RawDataFile.SeekToStart();

}

/**
 * @brief		ReadDataAll
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2020/12/28 10:35:26
 * @warning		
 */
void CDataFile::ReadDataAll( CData *pData )
{
	m_RawDataFile.SeekToStart();

    if( pData->m_pRawDataBuffer == 0 && pData->m_RawData.uiDataItems != 0 ) {
        pData->m_pRawDataBuffer = (char *) malloc( sizeof( char ) * pData->GetOneDataSize() * pData->m_RawData.uiDataItems );
    }

	// 데이터 파일 중에서 제일 큰 것을 읽는다.
	pData->m_RawData.uiByte = m_RawDataFile.Read( pData->m_pRawDataBuffer, pData->GetOneDataSize() * pData->m_RawData.uiDataItems, pData->GetHeaderSize() );		

	m_RawDataFile.SeekToStart();

}

/**
 * @brief		GetDataItems
 * @param		CData * pData
 * @return		unsigned int
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2020/12/24 16:19:44
 * @warning		
 */
unsigned int CDataFile::GetDataItems( CData *pData )
{
	
	return pData->GetDataItems();

}

/**
  * @brief		RAW 데이터 파일 읽기
  * @param		CString & strPathname
  * @return 	void
  * @return		성공시 true, 실패시 false
  * @date       2019/05/31 10:34
*/
void CDataFile::ReadDataMemory( STR_PDWDATA *pPDWData, const char *pstData, char *pstPathname, STR_FILTER_SETUP *pstFilterSetup )
{
    STR_PDWFILE_HEADER *pPDWFile;

	ENUM_DataType enDataType = WhatDataType( pstPathname );
    ENUM_UnitType enUnitType = WhatUnitType( pstPathname );

    pPDWFile = ( STR_PDWFILE_HEADER * ) pstData;

    if( enDataType == en_PDW_DATA && enUnitType == en_SONATA ) {
        m_pData->m_RawData.enDataType = en_PDW_DATA;
        m_pData->m_RawData.enUnitType = en_SONATA;

        if (m_RawDataFile.FileOpen( pstPathname, O_RDONLY | O_BINARY ) == TRUE ) {
            m_pData->m_RawData.uiByte = m_RawDataFile.Read( m_pData->m_pRawDataBuffer, MAX_RAWDATA_SIZE );
            m_pData->m_RawData.uiDataItems = m_pData->m_RawData.uiByte / sizeof(TNEW_PDW);

            m_pData = new CPDW( & m_pData->m_RawData );

            m_pData->Alloc();

            m_pData->ConvertArray( pPDWData, 0 );

            m_RawDataFile.FileClose();

        }
        else {
            m_pData->m_RawData.uiByte = -1;
            m_pData->m_RawData.uiDataItems = -1;
        }

    }

    else if( enDataType == en_PDW_DATA && enUnitType == en_SONATA_SHU ) {
        m_pData->m_RawData.enDataType = en_PDW_DATA;
        m_pData->m_RawData.enUnitType = en_SONATA;

        if (m_RawDataFile.FileOpen( pstPathname, O_RDONLY | O_BINARY ) == TRUE) {
            m_pData->m_RawData.uiByte = m_RawDataFile.Read( m_pData->m_pRawDataBuffer, MAX_RAWDATA_SIZE );
            m_pData->m_RawData.uiDataItems = m_pData->m_RawData.uiByte / sizeof(TNEW_SPDW);

            m_pData = new CSPDW( & m_pData->m_RawData );

            m_pData->Alloc();

            m_pData->ConvertArray( NULL, 0 );

            m_RawDataFile.FileClose();

        }
        else {
            m_pData->m_RawData.uiByte = -1;
            m_pData->m_RawData.uiDataItems = -1;
        }

    }

    else if( enDataType == en_PDW_DATA && enUnitType == en_ELINT ) {
        m_pData->m_RawData.enDataType = en_PDW_DATA;
        m_pData->m_RawData.enUnitType = en_ELINT;

        if (m_RawDataFile.FileOpen( pstPathname, O_RDONLY | O_BINARY ) == TRUE) {
            STR_PDWDATA *pPDWData;

            m_pData->m_RawData.uiByte = m_RawDataFile.Read( m_pData->m_pRawDataBuffer, MAX_RAWDATA_SIZE );
            pPDWData = ( STR_PDWDATA * ) m_pData->m_pRawDataBuffer;
            m_pData->m_RawData.uiDataItems = pPDWData->uiTotalPDW;

            m_pData = new CEPDW( & m_pData->m_RawData, pstFilterSetup );

            m_pData->Alloc();

            m_pData->ConvertArray( NULL, 0 );

            m_RawDataFile.FileClose();

        }
        else {
            m_pData->m_RawData.uiByte = -1;
            m_pData->m_RawData.uiDataItems = 0;
        }

    }

    else if( enDataType == en_PDW_DATA && enUnitType == en_701 ) {
        m_pData->m_RawData.enDataType = en_PDW_DATA;
        m_pData->m_RawData.enUnitType = en_701;

        if (m_RawDataFile.FileOpen( pstPathname, O_RDONLY | O_BINARY ) == TRUE) {
            SRxPDWHeader *pPDWHeader;

            m_pData->m_RawData.uiByte = m_RawDataFile.Read( m_pData->m_pRawDataBuffer, MAX_RAWDATA_SIZE );

            pPDWHeader = ( SRxPDWHeader * ) m_pData->m_pRawDataBuffer;

            m_pData = new C7PDW( & m_pData->m_RawData, pstFilterSetup );

            m_pData->AllSwapData32( & pPDWHeader->uiAcqTime, sizeof(int)*4 );
            m_pData->AllSwapData32( & pPDWHeader->iSearchBandID, sizeof(int)*4 );

            m_pData->m_RawData.uiDataItems = pPDWHeader->iNumOfPDW;

            m_pData->Alloc();

            m_pData->ConvertArray( pPDWData, 0 );

            m_RawDataFile.FileClose();

        }
        else {
            m_pData->m_RawData.uiByte = -1;
            m_pData->m_RawData.uiDataItems = 0;
        }

    }

    else if( enDataType == en_PDW_DATA && enUnitType == en_KFX ) {
        m_pData->m_RawData.enDataType = en_PDW_DATA;
        m_pData->m_RawData.enUnitType = en_KFX;

        STR_PDWFILE_HEADER *pPDWFile;

        m_pData->m_pRawDataBuffer = (char *) pstData;
        pPDWFile = ( STR_PDWFILE_HEADER * ) m_pData->m_pRawDataBuffer;

        m_pData = new CKFXPDW( & m_pData->m_RawData, pstFilterSetup );

        m_pData->m_RawData.uiDataItems = pPDWFile->uiSignalCount;

        if( pPDWData == NULL ) {
            m_pData->Alloc();
        }

        m_pData->ConvertArray( pPDWData, 0 );

    }

    else if( enDataType == en_PDW_DATA && enUnitType == en_ZPOCKETSONATA ) {
        pPDWFile = ( STR_PDWFILE_HEADER * ) & pstData[0];

        m_pData = new CPOCKETSONATAPDW( NULL, pstFilterSetup, pPDWFile->uiBoardID );

        m_pData->m_pRawDataBuffer = (char *) & pstData[sizeof(STR_PDWFILE_HEADER)];

        m_pData->m_RawData.uiDataItems = pPDWFile->uiSignalCount;

        m_pData->ConvertArray( pPDWData, true );
    }

    //////////////////////////////////////////////////////////////////////////
    else if( enDataType == en_IQ_DATA && enUnitType == en_SONATA ) {
        m_pData->m_RawData.enDataType = en_IQ_DATA;
        m_pData->m_RawData.enUnitType = en_SONATA;

        if (m_RawDataFile.FileOpen( pstPathname, O_RDONLY | O_BINARY ) == TRUE) {
            m_pData->m_RawData.uiByte = m_RawDataFile.Read( m_pData->m_pRawDataBuffer, MAX_RAWDATA_SIZE );
            m_pData->m_RawData.uiDataItems = m_pData->m_RawData.uiByte / sizeof(TNEW_IQ);

            m_pData = new CIQ( & m_pData->m_RawData );

            m_pData->Alloc();

            m_pData->ConvertArray( NULL, 0 );

            m_RawDataFile.FileClose();

        }
        else {
            m_pData->m_RawData.uiByte = -1;
            m_pData->m_RawData.uiDataItems = -1;
        }

    }
    else {
        printf("\n Error !!");

    }

    if( m_pData != NULL ) {
        delete m_pData;
        m_pData = NULL;

        //m_pData->m_pRawDataBuffer = 0;
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

/**
 * @brief		GetHeader
 * @return		void *
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2020/12/28 16:19:28
 * @warning		
 */
void *CDataFile::GetHeader() 
{ 
	if( m_pData != NULL ) 
		return m_pData->GetHeader(); 
	else 
		return NULL; 
}

void CDataFile::SetData( CData *pData )
{
	m_pData = pData;

	++ m_pData->m_uiWindowNumber;

}
