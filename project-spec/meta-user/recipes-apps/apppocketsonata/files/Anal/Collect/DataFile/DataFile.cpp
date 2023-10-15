﻿/**

    @file      DataFile.cpp
    @brief
    @details   ~
    @author    조철희
    @date      12.06.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/


#include "stdafx.h"


#include <math.h>
#include <stdio.h>
#include <float.h>
#include <string.h>

#include <stdint.h>

#if defined(_MSC_VER)


#elif defined(__linux__)


#elif defined(__VXWORKS__)
#include <ctype.h>

#else

#endif


#include "DataFile.h"

#include "CRWRCommonVariables.h"

#include "../../../Utils/clog.h"
#include "../../../Utils/ccommonutils.h"

#include "../../Identify/ELUtil.h"



#if PDW_ITEMS < IQ_ITEMS
#define			MAX_ITEMS					IQ_ITEMS
#else
#define			MAX_ITEMS					PDW_ITEMS
#endif

#define         MAX_ITEMS_BYTE                  ( MAX_ITEMS * 50 )

static int stDataFile;

int CPOCKETSONATAPDW::m_iBoardID;


//#ifdef _CGI_LIST_
//void Log( int nType, const char *fmt, ... )
//{
//    return;
//}
//#endif


////////////////////////////////////////////////////////////////////////

/**
 * @brief     CData
 * @param     STR_RAWDATA * pRawData
 * @return
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-06-30, 12:17
 * @warning
 */
// CPDW::CPDW(STR_RAWDATA *pRawData) : CData()
// {
//     m_enDataType = en_PDW_DATA;
//     m_enUnitType = en_SONATA;
//
// }
//
// /**
//  * @brief     ~CPDW
//  * @param     void
//  * @return
//  * @exception
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2021-06-30, 12:17
//  * @warning
//  */
// CPDW::~CPDW(void)
// {
//
// }
//
// /**
//  * @brief     Alloc
//  * @param     unsigned int uiItems
//  * @return    void
//  * @exception
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2021-06-30, 12:17
//  * @warning
//  */
// void CPDW::Alloc( unsigned int uiItems )
// {
//
// }
//
// /**
//  * @brief     Free
//  * @return    void
//  * @exception
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2021-06-30, 12:17
//  * @warning
//  */
// void CPDW::Free()
// {
//
// }
//
// /**
//  * @brief     GetData
//  * @return    void *
//  * @exception
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2021-06-30, 12:17
//  * @warning
//  */
// void *CPDW::GetData()
// {
// 	return & m_PDWData;
// }
//
// void *CPDW::GetRealData()
// {
//     return & m_PDWRealData;
// }
//
// /**
//  * @brief     ConvertArray
//  * @param     STR_PDWDATA * pPDWData
//  * @param     bool bSwap
//  * @param     STR_FILTER_SETUP * pFilterSetup
//  * @return    void
//  * @exception
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2021-06-30, 12:19
//  * @warning
//  */
// void CPDW::ConvertPDWData( STR_PDWDATA *pPDWData, STR_FILTER_SETUP *pFilterSetup, bool bSwap, ENUM_CONVERT_OPTION enOption )
// {
// //const char stDV[2] = { ' ', '*' } ;
// //     unsigned int i;
// //
// // 	Alloc( m_PDWData.uiDataItems );
// //
// // 	float *pfFreq = m_PDWData.pfFreq;
// // 	float *pfPW = m_PDWData.pfPW;
// // 	float *pfAOA = m_PDWData.pfAOA;
// // 	float *pfTOA = m_PDWData.pfTOA;
// // 	float *pfDTOA = m_PDWData.pfDTOA;
// // 	float *pfPA = m_PDWData.pfPA;
// // 	_TOA *pfllTOA = m_PDWData.pullTOA;
// //
// // 	char *pcType = m_PDWData.pcType;
// // 	char *pcDV = m_PDWData.pcDV;
// //
// // 	UINT uiToa, preToa, uiDToa;
// // 	UINT uiTemp;
// //
// // 	TNEW_PDW temp;
// //
// //     if( m_pRawDataBuffer != NULL ) {
// // 	    TNEW_PDW *pPDW = (TNEW_PDW *) m_pRawDataBuffer;
// //
// // 	    m_PDWData.uiDataItems = 0;
// //
// //         //Log( enNormal, "ConvertArray()를 [%d]개를 변환합니다." , m_RawData.uiDataItems );
// //
// //         for (i = 0; i < m_PDWData.uiDataItems ; ++i) {
// // 		    temp.bpdw[0][0] = pPDW->item.toa_1;
// // 		    temp.bpdw[0][1] = pPDW->item.toa_2;
// // 		    temp.bpdw[0][2] = pPDW->item.toa_3;
// // 		    temp.bpdw[0][3] = pPDW->item.toa_4;
// //
// // 		    uiToa = temp.wpdw[0];
// // 			*pfTOA = DecodeTOAus( uiToa );
// //
// // 		    if (i == 0) {
// // 			    *pfDTOA = 0;
// // 			    preToa = uiToa;
// // 		    }
// // 		    else {
// // 			    uiDToa = uiToa - preToa;
// // 				*pfDTOA = DecodeTOAus( uiDToa );
// // 			    preToa = uiToa;
// // 		    }
// //
// // 		    *pfllTOA = uiToa;
// //
// //
// // 		    uiTemp = BIT_MERGE(pPDW->item.frequency_h, pPDW->item.frequency_l);
// // 		    //*pfFreq = FFRQCNV(pPDW->item.band, uiTemp);
// // 			*pfFreq = DecodeRealFREQMHz( pPDW->item.band, uiTemp );
// //
// // 		    uiTemp = BIT_MERGE(pPDW->item.pulse_width_h, pPDW->item.pulse_width_l);
// // 		    //*pfPW = FMUL( uiTemp, m_spPWres );
// // 			*pfPW = DecodePW( uiTemp );
// //
// // 		    uiTemp = BIT_MERGE(pPDW->item.direction_h, pPDW->item.direction_l);
// // 		    //*pfAOA = FAOACNV(uiTemp);
// // 			*pfAOA = DecodeDOA( uiTemp );
// //
// // 		    uiTemp = pPDW->item.amplitude;
// // 		    //*pfPA = PACNV(uiTemp);
// // 			*pfPA = DecodePA(uiTemp);
// //
// // 		    *pcType = pPDW->item.stat;
// // 		    *pcDV = pPDW->item.dv;
// //
// // 		    // printf( "\n [%3d] 0x%02X %5.1f%1c[deg] %8.2f[MHz] %10.3f[us] %8.3f[ns]" , i+1, *pcType, *pfAOA, stDV[*pcDV], *pfFreq, *pfTOA, *pfPW );
// // 		    // 필터링 조건
// // /*		    if( ( m_strFilterSetup.dToaMin <= *pfTOA && m_strFilterSetup.dToaMax >= *pfTOA ) &&
// // 			    ( m_strFilterSetup.dAoaMin <= *pfAOA && m_strFilterSetup.dAoaMax >= *pfAOA ) &&
// // 			    ( m_strFilterSetup.dPAMin <= *pfPA && m_strFilterSetup.dPAMax >= *pfPA ) &&
// // 			    ( m_strFilterSetup.dPWMin <= *pfPW && m_strFilterSetup.dPWMax >= *pfPW ) &&
// // 			    ( m_strFilterSetup.dFrqMin <= *pfFreq && m_strFilterSetup.dFrqMax >= *pfFreq ) ) {
// // 			    ++pfFreq;
// // 			    ++pfAOA;
// // 			    ++pfPW;
// // 			    ++pfPA;
// // 			    ++pfTOA;
// // 			    ++pfDTOA;
// // 			    ++pcType;
// // 			    ++pcDV;
// //
// // 			    ++ pfllTOA;
// //
// // 			    ++ m_PDWData.uiDataItems;
// // 		    }
// // */
// // 		    ++pPDW;
// // 	    }
// //     }
// }
//
//
// /**
//  * @brief
//  * @param     unsigned long long ullFileSize
//  * @return    unsigned int
//  * @author    議곗쿋??(churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2022/01/25 23:56:38
//  * @warning
//  */
// unsigned int CPDW::GetDataItems( unsigned long long ullFileSize )
// {
// 	unsigned int uiDataItems;
//
// 	if( ullFileSize <= UINT32_MAX ) {
// 		uiDataItems = (unsigned int) ( ullFileSize ) / sizeof( struct TNEW_PDW );
// 	    }
// 	else {
// 		uiDataItems = 0;
//     }
//     return uiDataItems;
// }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if defined(_GRAPH_) || defined(_ELINT_)
/**
 * @brief     CData
 * @param     STR_RAWDATA * pRawData
 * @param     STR_FILTER_SETUP * pstFilterSetup
 * @return
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-06-30, 12:17
 * @warning
 */
CEPDW::CEPDW(STR_RAWDATA *pRawData, STR_FILTER_SETUP *pstFilterSetup ) : CData()
{

	if( pstFilterSetup != NULL ) {
        memcpy( & m_strFilterSetup, pstFilterSetup, sizeof( struct STR_FILTER_SETUP) );
	}
    else {

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
    Free();
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
void CEPDW::Alloc( unsigned int uiItems )
{


}

/**
 * @brief     Free
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-05, 10:23
 * @warning
 */
void CEPDW::Free()
{


}

/**
 * @brief     GetData
 * @return    void *
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-05, 10:23
 * @warning
 */
void *CEPDW::GetData()
{
	return & m_PDWData;
}

void *CEPDW::GetRealData()
{
    return & m_PDWRealData;
}

/**
 * @brief     ConvertArray
 * @param     STR_PDWDATA * pPDWData
 * @param     bool bSwap
 * @param     STR_FILTER_SETUP * pFilterSetup
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-05, 10:23
 * @warning
 */
void CEPDW::ConvertPDWData( STR_PDWDATA *pPDWData, STR_FILTER_SETUP *pFilterSetup, bool bSwap, ENUM_CONVERT_OPTION enOption )
{
//     unsigned int i;
//
// 	unsigned long long int ll1stToa;
//
//     //LOGMSG1( enNormal, _T("Converting %d Items In ConvertArray()") , m_RawData.uiDataItems );
//
//     Alloc( m_uiTotalDataItems );
//
// 	float *pfFreq = m_PDWData.pfFreq;
// 	float *pfPW = m_PDWData.pfPW;
// 	float *pfAOA = m_PDWData.pfAOA;
//     float *pfPA = m_PDWData.pfPA;
//     _TOA *pullTOA = m_PDWData.pullTOA;
//
// 	float *pfTOA = m_PDWData.pfTOA;
// 	float *pfDTOA = m_PDWData.pfDTOA;
//
// 	float *pfPh1 = m_PDWData.pfPh1;
// 	float *pfPh2 = m_PDWData.pfPh2;
// 	float *pfPh3 = m_PDWData.pfPh3;
// 	float *pfPh4 = m_PDWData.pfPh4;
//
// 	char *pcType = m_PDWData.pcType;
// 	char *pcDV = m_PDWData.pcDV;
//
// 	float fPreToa;
//
// 	_PDW *pPDW = (_PDW *) & m_pRawDataBuffer[0];
//
//     bool bFirst=true;
//
// 	m_PDWData.uiDataItems = 0;
//
//     for ( i=0; i < m_uiTotalDataItems ; ++i ) {
//
//         // 필터링 조건
//         if( ( m_strFilterSetup.ullToaMin <= pPDW->ullTOA && m_strFilterSetup.ullToaMax >= pPDW->ullTOA ) &&
//             ( m_strFilterSetup.uiAoaMin <= pPDW->uiAOA && m_strFilterSetup.uiAoaMax >= pPDW->uiAOA ) &&
//             ( m_strFilterSetup.uiPAMin <= pPDW->uiPA && m_strFilterSetup.uiPAMax >= pPDW->uiPA ) &&
//             ( m_strFilterSetup.uiPWMin <= pPDW->uiPW && m_strFilterSetup.uiPWMax >= pPDW->uiPW ) &&
//             ( m_strFilterSetup.uiFrqMin <= pPDW->uiFreq && m_strFilterSetup.uiFrqMax >= pPDW->uiFreq ) ) {
//
// 			if( bFirst == true) {
// 				ll1stToa = pPDW->ullTOA;
//
// 				*pfDTOA++ = 0;
// 				//*pfTOA = DecodeTOAus( pPDW->ullTOA - ll1stToa, m_enBandWidth );
//                 *pfTOA = DecodeTOAus( pPDW->ullTOA, m_enBandWidth );
//
// 				bFirst = false;
// 			}
// 			else {
// 				//*pfTOA = DecodeTOAus( pPDW->ullTOA - ll1stToa, m_enBandWidth );
//                 *pfTOA = DecodeTOAus( pPDW->ullTOA, m_enBandWidth );
// 				*pfDTOA++ = *pfTOA - fPreToa;
// 			}
// 			fPreToa = *pfTOA++;
//
// 			*pullTOA++ = pPDW->ullTOA;
//
//             // 그래프 와 목록창으로 길제 값을 보기 위한 처리
//             *pfFreq++ = DecodeRealFREQMHz( pPDW->uiFreq );
//             *pfPW++ = DecodePW( pPDW->uiPW, m_enBandWidth );
//             *pfAOA++ = DecodeDOA( pPDW->uiAOA );
//             *pfPA++ = DecodePA( pPDW->uiPA );
//
// 			*pcType++ = pPDW->iPulseType;
//
// 			*pcDV++ = 1;
//
// 			++ m_PDWData.uiDataItems;
// 		}
//
// 		++ pPDW;
//     }

	//m_pRawData->uiDataItems = uiDataItems;
    //LOGMSG1( enNormal, _T("The count of filtererd PDW(s) is %d.") , m_PDWData.uiDataItems );
}

/**
 * @brief     GetHeaderSize
 * @return    unsigned int
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-20, 15:02
 * @warning
 */
int CEPDW::GetHeaderSize()
{
    memcpy( & m_stHeader, m_pRawHeaderBuffer, sizeof( m_stHeader) );

    // 테스트
    m_iHeaderSize = sizeof( struct STR_ELINT_HEADER2 );
    m_iHeaderSize = sizeof( struct STR_ELINT_HEADER);

    m_enBandWidth = m_stHeader.enBandWidth;

    return m_iHeaderSize;
}

/**
 * @brief     GetDataItems
 * @return    unsigned int
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-20, 15:02
 * @warning
 */
unsigned int CEPDW::GetDataItems( unsigned long long ullFileSize )
{
    unsigned int uiDataItems;

    memcpy( & m_stHeader, & m_pRawHeaderBuffer[0], sizeof( struct STR_ELINT_HEADER) );

    memcpy( & uiDataItems, & m_pRawHeaderBuffer[sizeof( struct STR_ELINT_HEADER)], sizeof(int) );

    // 아래는 시간 정보
    //memcpy( & m_stHeader, m_pRawDataBuffer[sizeof(struct STR_ELINT_HEADER)+sizeof(int)], sizeof(int) );
    //memcpy( & m_stHeader, m_pRawDataBuffersizeof(struct STR_ELINT_HEADER)+sizeof(int)*2], sizeof(int) );

    m_enBandWidth = m_stHeader.enBandWidth;

    return uiDataItems;
}

/**
 * @brief
 * @param     void * pData
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022/02/15 18:10:56
 * @warning
 */
void CEPDW::SetHeaderData( void *pData )
{
    memcpy( & m_stHeader, pData, sizeof( struct STR_ELINT_HEADER) );

    m_stHeader.stCommon.CheckColTime();

    return;
}

#endif

#if defined(_GRAPH_) || defined(_XBAND_)
///////////////////////////////////////////////////////////////////////////////////////
// X밴드 방탐기

/**
 * @brief     CData
 * @param     STR_RAWDATA * pRawData
 * @param     STR_FILTER_SETUP * pstFilterSetup
 * @return
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-06-30, 12:17
 * @warning
 */
CXPDW::CXPDW( char *pRawData, STR_FILTER_SETUP *pstFilterSetup ) : CData( )
{

    m_enDataType = en_PDW_DATA;
    m_enUnitType = en_XBAND;

    m_enBandWidth = XBAND::en5MHZ_BW;

	CXPDW::Init( pRawData );

    if( pstFilterSetup != NULL ) {
        // memcpy( &m_strFilterSetup, pstFilterSetup, sizeof( struct STR_FILTER_SETUP ) );
		memcpy_s(&m_strFilterSetup, sizeof( struct STR_FILTER_SETUP), pstFilterSetup, sizeof( struct STR_FILTER_SETUP));
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
CXPDW::~CXPDW(void)
{
    Free();
}

/**
 * @brief
 * @param     const char * pRawData
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022/02/18 23:06:22
 * @warning
 */
void CXPDW::Init( char *pRawData, STR_FILTER_SETUP *pstFilterSetup )
{
    UNION_HEADER *puniPDWFileHeader;

    m_pRawHeaderBuffer = (char *) & pRawData[0];
    m_pRawDataBuffer = (char *) & pRawData[sizeof( struct STR_XBAND_HEADER )];

    puniPDWFileHeader = ( UNION_HEADER * ) m_pRawHeaderBuffer;

    CXPDW::UpdateHeaderSize();

    m_PDWRealData.uiDataItems = 0;

    m_uiTotalDataItems = puniPDWFileHeader->GetTotalPDW( m_enUnitType );
    m_enBandWidth = (XBAND::ENUM_BANDWIDTH ) puniPDWFileHeader->GetBandWidth();

    if( pstFilterSetup != NULL ) {
        memcpy( &m_strFilterSetup, pstFilterSetup, sizeof( struct STR_FILTER_SETUP ) );
    }

}

/**
 * @brief
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022/02/18 23:06:32
 * @warning
 */
void CXPDW::Free()
{

}

/**
 * @brief     GetData
 * @return    void *
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-05, 10:23
 * @warning
 */
void *CXPDW::GetData()
{
	return & m_PDWData;
}

/**
 * @brief     GetRealData
 * @return    void *
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-11-24 14:37:31
 * @warning
 */
void *CXPDW::GetRealData()
{
    return & m_PDWRealData;
}

/**
 * @brief     ConvertArray
 * @param     STR_PDWDATA * pPDWData
 * @param     bool bSwap
 * @param     STR_FILTER_SETUP * pFilterSetup
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-05, 10:23
 * @warning
 */
void CXPDW::ConvertArrayData( STR_PDWDATA *pPDWData, bool bSwap, STR_FILTER_SETUP *pFilterSetup )
{
//     unsigned int i;
//
// 	unsigned long long int ll1stToa;
//
//     if( pPDWData == NULL ) {
//         //Alloc( m_uiTotalDataItems );
//
// 	    float *pfFreq = m_PDWData.pfFreq;
// 	    float *pfPW = m_PDWData.pfPW;
// 	    float *pfAOA = m_PDWData.pfAOA;
// 	    float *pfTOA = m_PDWData.pfTOA;
// 	    float *pfDTOA = m_PDWData.pfDTOA;
// 	    float *pfPA = m_PDWData.pfPA;
// 	    unsigned long long int *pullTOA = m_PDWData.pullTOA;
//
// 	    char *pcType = m_PDWData.pcType;
// 	    char *pcDV = m_PDWData.pcDV;
//
//         float fPreToa;
//
//         bool bFirst=true;
//
//         _PDW *pPDW = (_PDW *) & m_pRawDataBuffer[0];
//
//         m_PDWData.uiDataItems = 0;
//
//         for ( i=0; i < m_uiTotalDataItems ; ++i ) {
//             // 필터링 조건
//             if( ( m_strFilterSetup.ullToaMin <= pPDW->ullTOA && m_strFilterSetup.ullToaMax >= pPDW->ullTOA ) &&
//                 ( m_strFilterSetup.uiAoaMin <= pPDW->uiAOA && m_strFilterSetup.uiAoaMax >= pPDW->uiAOA ) &&
//                 ( m_strFilterSetup.uiPAMin <= pPDW->uiPA && m_strFilterSetup.uiPAMax >= pPDW->uiPA ) &&
//                 ( m_strFilterSetup.uiPWMin <= pPDW->uiPW && m_strFilterSetup.uiPWMax >= pPDW->uiPW ) &&
//                 ( m_strFilterSetup.uiFrqMin <= pPDW->uiFreq && m_strFilterSetup.uiFrqMax >= pPDW->uiFreq ) ) {
//
//                     if( bFirst == true) {
//                         ll1stToa = pPDW->ullTOA;
//
//                         *pfDTOA++ = 0;
//                         *pfTOA = DecodeTOAus( pPDW->ullTOA, m_enBandWidth );
//
//                         bFirst = false;
//                     }
//                     else {
//                         *pfTOA = DecodeTOAus( pPDW->ullTOA, m_enBandWidth );
//                         *pfDTOA++ = *pfTOA - fPreToa;
//                     }
//                     fPreToa = *pfTOA++;
//
//                     *pullTOA++ = pPDW->ullTOA;
//
//                     *pfFreq++ = DecodeRealFREQMHz( pPDW->uiFreq );
//                     *pfPW++ = DecodePW( pPDW->uiPW, m_enBandWidth );
//                     *pfAOA++ = DecodeDOA( pPDW->uiAOA );
//                     *pfPA++ = DecodePA( pPDW->uiPA );
//
//                     *pcType++ = pPDW->iPulseType;
//
//                     *pcDV++ = 1;
//
//                     ++ m_PDWData.uiDataItems;
//             }
//
//             ++ pPDW;
//
//         }
//     }
//     else {
// //         float fPreToa;
// //
// //         bool bFirst=true;
// //
// //         _PDW *pPDW = (_PDW *) & m_pRawDataBuffer[0];
// //         _PDW *pCvtPDW = (_PDW *) & pPDWData->stPDW[0]
// //
// //         m_PDWData.uiDataItems = 0;
// //
// //         for ( i=0; i < m_uiTotalDataItems ; ++i ) {
// //             // 필터링 조건
// //             if( ( m_strFilterSetup.ullToaMin <= pPDW->ullTOA && m_strFilterSetup.ullToaMax >= pPDW->ullTOA ) &&
// //                 ( m_strFilterSetup.uiAoaMin <= pPDW->uiAOA && m_strFilterSetup.uiAoaMax >= pPDW->uiAOA ) &&
// //                 ( m_strFilterSetup.uiPAMin <= pPDW->uiPA && m_strFilterSetup.uiPAMax >= pPDW->uiPA ) &&
// //                 ( m_strFilterSetup.uiPWMin <= pPDW->uiPW && m_strFilterSetup.uiPWMax >= pPDW->uiPW ) &&
// //                 ( m_strFilterSetup.uiFrqMin <= pPDW->uiFreq && m_strFilterSetup.uiFrqMax >= pPDW->uiFreq ) ) {
// //
// //                     if( bFirst == true) {
// //                         ll1stToa = pPDW->ullTOA;
// //
// //                         *pfDTOA++ = 0;
// //                         *pfTOA = DecodeTOAus( pPDW->ullTOA, m_enBandWidth );
// //
// //                         bFirst = false;
// //                     }
// //                     else {
// //                         *pfTOA = DecodeTOAus( pPDW->ullTOA, m_enBandWidth );
// //                         *pfDTOA++ = *pfTOA - fPreToa;
// //                     }
// //                     fPreToa = *pfTOA++;
// //
// //                     *pullTOA++ = pPDW->ullTOA;
// //
// //                     pCvtPDW-> = DecodeRealFREQMHz( pPDW->uiFreq );
// //                     *pfPW++ = DecodePW( pPDW->uiPW, m_enBandWidth );
// //                     *pfAOA++ = DecodeDOA( pPDW->uiAOA );
// //                     *pfPA++ = DecodePA( pPDW->uiPA );
// //
// //                     *pcType++ = pPDW->iPulseType;
// //
// //                     *pcDV++ = 1;
// //
// //                     ++ pCvtPDW;
// //                     ++ m_PDWData.uiDataItems;
// //             }
// //
// //             ++ pPDW;
// //
// //         }
//     }

}

/**
 * @brief     GetHeaderSize
 * @return    unsigned int
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-20, 15:02
 * @warning
 */
int CXPDW::GetHeaderSize()
{

    memcpy( & m_stHeader, m_pRawHeaderBuffer, sizeof(m_stHeader) );

    m_iHeaderSize = sizeof( struct STR_XBAND_HEADER);

    return m_iHeaderSize;
}

/**
 * @brief
 * @return    unsigned int
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022/02/17 0:23:55
 * @warning
 */
unsigned int CXPDW::GetOneDataSize()
{
    return sizeof(struct _PDW);
}

/**
 * @brief     GetDataItems
 * @return    unsigned int
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-20, 15:02
 * @warning
 */
unsigned int CXPDW::GetDataItems( unsigned long long ullFileSize )
{
    unsigned int uiDataItems;

	memcpy( & m_stHeader, & m_pRawHeaderBuffer[0], sizeof( struct STR_ELINT_HEADER) );

	memcpy( & uiDataItems, & m_pRawHeaderBuffer[sizeof( struct STR_ELINT_HEADER)], sizeof(int) );

	// 아래는 시간 정보
	//memcpy( & m_stHeader, m_pRawDataBuffer[sizeof(struct STR_ELINT_HEADER)+sizeof(int)], sizeof(int) );
	//memcpy( & m_stHeader, m_pRawDataBuffersizeof(struct STR_ELINT_HEADER)+sizeof(int)*2], sizeof(int) );

	m_enBandWidth = m_stHeader.enBandWidth;

    return uiDataItems;
}

/**
 * @brief
 * @param     STR_PDWDATA * pPDWData
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022/02/15 20:05:35
 * @warning
 */
void CXPDW::MakeHeaderData( STR_PDWDATA *pPDWData )
{
    memcpy( & pPDWData->x.xb, & m_stHeader, sizeof(m_stHeader) );

}


/**
 * @brief
 * @param     STR_PDWDATA * pPDWData
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022/02/17 0:19:36
 * @warning
 */
void CXPDW::MakePDWDataByUnitToPDW( STR_PDWDATA *pPDWData )
{


}

/**
 * @brief     MakePDWDataToReal
 * @param     STR_PDWREALDATA * pPDWRealData
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-02-22, 15:28
 * @warning
 */
void CXPDW::MakePDWDataToReal( STR_PDWREALDATA *pPDWRealData )
{
    bool bFirstTOA = true;
    unsigned int i, uiDataItems;
    int iCh;

    XBAND::ENUM_BANDWIDTH enBandWidth;

    _TOA ullTOA, ullFirstTOA, ullPreTOA = 0;
    int iPulseType;
    UINT uiFreq, uiPW, uiPA, uiAOA;

    _TOA *pullTOA = pPDWRealData->pullTOA;

    float *pfAOA = pPDWRealData->pfAOA;
    float *pfFreq = pPDWRealData->pfFreq;
    float *pfPA = pPDWRealData->pfPA;
    float *pfPW = pPDWRealData->pfPW;

    double *pdTOA = pPDWRealData->pdTOA;
    float *pfDTOA = pPDWRealData->pfDTOA;

    char *pcType = pPDWRealData->pcType;
    char *pcDV = pPDWRealData->pcDV;

    _PDW *pPDW = ( _PDW * ) & m_pRawDataBuffer[0];

    uiDataItems = 0;
    enBandWidth = m_stHeader.enBandWidth;

    for( i = 0 ; i < m_uiTotalDataItems ; ++i ) {
        // 시간 정보
        ullTOA = pPDW->GetTOA();

        // 방위 저장
        uiAOA = pPDW->GetAOA();

        // 주파수 변환
        iCh = pPDW->GetChannel();
        uiFreq = pPDW->GetFrequency( iCh );

        // 펄스폭 저장
        uiPW = pPDW->GetPulsewidth();

        // 신호 세기 저장
        uiPA = pPDW->GetPulseamplitude();

		iPulseType = pPDW->GetPulsetype();

        // 필터링 조건
        if( (m_strFilterSetup.ullToaMin <= ullTOA && m_strFilterSetup.ullToaMax >= ullTOA) &&
			TCompDOAMarginDiff<unsigned int>( uiAOA , m_strFilterSetup.uiAoaMin, m_strFilterSetup.uiAoaMax) == TRUE &&
            (m_strFilterSetup.uiPAMin <= uiPA && m_strFilterSetup.uiPAMax >= uiPA) &&
            (m_strFilterSetup.uiPWMin <= uiPW && m_strFilterSetup.uiPWMax >= uiPW) &&
            (m_strFilterSetup.uiFrqMin <= uiFreq && m_strFilterSetup.uiFrqMax >= uiFreq) ) {
            if( bFirstTOA == true ) {
                _EQUALS3( ullPreTOA, ullFirstTOA, ullTOA )

                bFirstTOA = false;
            }
            *pfDTOA++ = (float) CXPDW::DecodeTOA( ullTOA - ullPreTOA, enBandWidth );
            ullPreTOA = ullTOA;


            // 시간 저장
            *pullTOA++ = ullTOA;

            *pdTOA++ = CXPDW::DecodeTOA( ullTOA, enBandWidth );
            *pfAOA++ = CXPDW::DecodeDOA( uiAOA );
            *pfFreq++ = CXPDW::DecodeFREQ( uiFreq );
            *pfPA++ = CXPDW::DecodePA( uiPA );
            *pfPW++ = CXPDW::DecodePW( uiPW, enBandWidth );

            *pcType++ = iPulseType;
            *pcDV++ = 1;

            ++uiDataItems;

        }

        ++pPDW;

    }

    pPDWRealData->SetTotalPDW( uiDataItems );

}
#endif

#if defined(_GRAPH_) || defined(_SONATA_)
//////////////////////////////////////////////////////////////////////////

/**
 * @brief     CData
 * @param     STR_RAWDATA * pRawData
 * @return
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-02-14, 14:26
 * @warning
 */
CSPDW::CSPDW(char *pRawData, STR_FILTER_SETUP *pstFilterSetup, size_t szFileSize ) : CData( )
{
	m_ullFileSize = szFileSize;

	m_enDataType = en_PDW_DATA;
	m_enUnitType = en_SONATA;

	CSPDW::Init(pRawData );

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
    Free();
}

/**
 * @brief     Init
 * @param     char * pRawData
 * @param     STR_FILTER_SETUP * pstFilterSetup
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-11-24 11:53:22
 * @warning
 */
void CSPDW::Init(char *pRawData, STR_FILTER_SETUP *pstFilterSetup)
{
	UNION_HEADER *puniPDWFileHeader;

	m_pRawHeaderBuffer = (char *)& pRawData[0];
	m_pRawDataBuffer = (char *)& pRawData[0];

	puniPDWFileHeader = (UNION_HEADER *)m_pRawHeaderBuffer;

    CSPDW::UpdateHeaderSize();

	//m_uiTotalDataItems = puniPDWFileHeader->GetTotalPDW(m_enUnitType);
	m_uiTotalDataItems = GetDataItems();

	//m_iBoardID = -1;

}

/**
 * @brief     GetHeaderSize
 * @return    int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-11-24 11:51:04
 * @warning
 */
int CSPDW::GetHeaderSize()
{

	return 0;
}

/**
 * @brief     GetOneDataSize
 * @return    unsigned int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-11-24 11:51:41
 * @warning
 */
unsigned int CSPDW::GetOneDataSize()
{
	return sizeof( union TNEW_PDW);
}

/**
 * @brief     GetDataItems
 * @param     unsigned long long ullFileSize
 * @return    unsigned int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-11-24 11:52:06
 * @warning
 */
unsigned int CSPDW::GetDataItems(unsigned long long ullFileSize)
{
	unsigned int uiDataItems=0;

	unsigned int uiDataSize = GetOneDataSize();

	if (uiDataSize != 0) {
		uiDataItems = (UINT) (m_ullFileSize) / uiDataSize;
	}
	//TDIV<unsigned long long>(m_ullFileSize, GetOneDataSize());

	return uiDataItems;
}


/**
 * @brief     MakeHeaderData
 * @param     STR_PDWDATA * pPDWData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-11-24 12:16:38
 * @warning
 */
void CSPDW::MakeHeaderData(STR_PDWDATA *pPDWData)
{
	pPDWData->x.so.stCommon.uiTotalPDW = m_uiTotalDataItems;


}

/**
 * @brief     MakePDWDataToReal
 * @param     STR_PDWREALDATA * pPDWRealData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-11-24 12:17:00
 * @warning
 */
void CSPDW::MakePDWDataToReal(STR_PDWREALDATA *pPDWRealData)
{
	bool bFirstTOA = true;
	unsigned int i, uiDataItems;
	int iCh;

	// SONATA::ENUM_BANDWIDTH enBandWidth;

	UINT ullTOA, ullFirstTOA, ullPreTOA = 0;
	int iPulseType, iDV, iBand;

	UINT uiFreq, uiPW, uiPA, uiAOA;

	_TOA *pullTOA = pPDWRealData->pullTOA;

	float *pfAOA = pPDWRealData->pfAOA;
	float *pfFreq = pPDWRealData->pfFreq;
	float *pfPA = pPDWRealData->pfPA;
	float *pfPW = pPDWRealData->pfPW;

	double *pdTOA = pPDWRealData->pdTOA;
	float *pfDTOA = pPDWRealData->pfDTOA;

	char *pcType = pPDWRealData->pcType;
	char *pcDV = pPDWRealData->pcDV;

	TNEW_PDW *pPDW = (TNEW_PDW *)& m_pRawDataBuffer[0];

	uiDataItems = 0;
	//enBandWidth = m_stHeader.enBandWidth;

	for (i = 0; i < m_uiTotalDataItems; ++i) {
		// 시간 정보
		ullTOA = pPDW->GetTOA();

		// 방위 저장
		uiAOA = pPDW->GetAOA();

		// 주파수 변환
		iCh = -1;
		uiFreq = pPDW->GetFrequency();

		// 펄스폭 저장
		uiPW = pPDW->GetPulsewidth();

		// 신호 세기 저장
		uiPA = pPDW->GetPulseamplitude();

		iPulseType = pPDW->GetPulsetype();

		iDV = pPDW->GetDirectionValid();

		iBand = pPDW->GetBand();

		// 필터링 조건
		if ((m_strFilterSetup.ullToaMin <= ullTOA && m_strFilterSetup.ullToaMax >= ullTOA) &&
			(m_strFilterSetup.uiAoaMin <= uiAOA && m_strFilterSetup.uiAoaMax >= uiAOA) &&
			(m_strFilterSetup.uiPAMin <= uiPA && m_strFilterSetup.uiPAMax >= uiPA) &&
			(m_strFilterSetup.uiPWMin <= uiPW && m_strFilterSetup.uiPWMax >= uiPW) &&
			(m_strFilterSetup.uiFrqMin <= uiFreq && m_strFilterSetup.uiFrqMax >= uiFreq)) {
			if (bFirstTOA == true) {
				_EQUALS3(ullPreTOA, ullFirstTOA, ullTOA)

				bFirstTOA = false;
			}
			*pfDTOA++ = (float)CSPDW::DecodeTOA(ullTOA - ullPreTOA );
			ullPreTOA = ullTOA;


			// 시간 저장
			*pullTOA++ = ullTOA;

 			*pdTOA++ = CSPDW::DecodeTOA( ullTOA );
 			*pfAOA++ = CSPDW::DecodeDOA(uiAOA);
 			*pfFreq++ = CSPDW::DecodeFREQ(uiFreq, iBand);
 			*pfPA++ = CSPDW::DecodePA(uiPA);
 			*pfPW++ = (float) CSPDW::DecodePW(uiPW );

 			*pcType++ = iPulseType;
 			*pcDV++ = iDV;

 			++uiDataItems;

 		}

		++pPDW;

	}

	pPDWRealData->SetTotalPDW(uiDataItems);

}


/**
 * @brief     ConvertArrayData
 * @param     STR_PDWDATA * pPDWData
 * @param     bool bSwap
 * @param     STR_FILTER_SETUP * pFilterSetup
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-11-24 12:13:42
 * @warning
 */
void CSPDW::ConvertArrayData(STR_PDWDATA *pPDWData, bool bSwap, STR_FILTER_SETUP *pFilterSetup)
{
	//     unsigned int i;
	//     int iCh;
	//
	//     float *pfFreq, *pfPW, *pfAOA, *pfTOA, *pfDTOA, *pfPA;
	//     char *pcType, *pcDV;
	//     _TOA *pullTOA;
	//
	//     _TOA ullToa;
	//
	//     //float preToa;
	//
	//     UINT uiFreq, uiPW, uiPA, uiAOA;
	//
	//     pfFreq = m_PDWData.pfFreq;
	//     pfPW = m_PDWData.pfPW;
	//     pfAOA = m_PDWData.pfAOA;
	//     pfTOA = m_PDWData.pfTOA;
	//     pfDTOA = m_PDWData.pfDTOA;
	//     pfPA = m_PDWData.pfPA;
	//
	//     pcType = m_PDWData.pcType;
	//     pcDV = m_PDWData.pcDV;
	//
	//     pullTOA = m_PDWData.pullTOA;
	//
	//     DMAPDW *pPDW = (DMAPDW *) & m_pRawDataBuffer[0];
	//
	//     m_PDWData.uiDataItems = 0;
	//
	//     for( i=0 ; i < m_uiTotalDataItems ; ++i ) {
	//         int iFreq;
	//
	//         ullToa = (_TOA) ( pPDW->uPDW.x.uniPdw_freq_toa.stPdw_freq_toa.toa_L ) | ( (_TOA) pPDW->uPDW.x.uniPdw_toa_edge.stPdw_toa_edge.toa_H << 16 );
	//
	//         // 주파수 변환
	//         iCh = pPDW->uPDW.x.uniPdw_freq_toa.stPdw_freq_toa.pdw_phch;
	//         iCh = ( 16 + ( iCh - 8 ) ) % 16;
	//
	//         iFreq = ( pPDW->uPDW.x.uniPdw_pw_freq.stPdw_pw_freq.frequency_L ) | ( pPDW->uPDW.x.uniPdw_freq_toa.stPdw_freq_toa.frequency_H << 8 );
	//         iFreq = ( 0x10000 + ( iFreq - 0x8000 ) ) % 0x10000;
	//
	//         uiFreq = iFreq + ( iCh * 0x10000 );
	//
	//         // 펄스폭 저장
	//         uiPW = pPDW->uPDW.x.uniPdw_pw_freq.stPdw_pw_freq.pulse_width;
	//
	//         // 방위 저장
	//         uiAOA = pPDW->uPDW.x.uniPdw_dir_pa.stPdw_dir_pa.doa;
	//
	//         // 신호 세기 저장
	//         uiPA = pPDW->uPDW.x.uniPdw_dir_pa.stPdw_dir_pa.pa;
	//
	//         // 필터링 조건
	//         if( ( m_strFilterSetup.ullToaMin <= ullToa && m_strFilterSetup.ullToaMax >= ullToa ) &&
	//             ( m_strFilterSetup.uiAoaMin <= uiAOA && m_strFilterSetup.uiAoaMax >= uiAOA ) &&
	//             ( m_strFilterSetup.uiPAMin <= uiPA && m_strFilterSetup.uiPAMax >= uiPA ) &&
	//             ( m_strFilterSetup.uiPWMin <= uiPW && m_strFilterSetup.uiPWMax >= uiPW ) &&
	//             ( m_strFilterSetup.uiFrqMin <= uiFreq && m_strFilterSetup.uiFrqMax >= uiFreq ) ) {
	//
	//             // 시간 저장
	//             *pullTOA++ = ullToa;
	//
	//             *pfFreq++ = DecodeFREQMHz( uiFreq );
	//             *pfPW++ = DecodePW( uiPW );
	//             *pfAOA++ = DecodeDOA( uiAOA );
	//             *pfPA++ = DecodePA( uiPA );
	//
	//             // 신호 형태 저장
	// #ifdef _POCKETSONATA_
	//             *pcType = STAT_NORMAL;
	//             if( pPDW->uPDW.x.uniPdw_status.stPdw_status.cw_pulse == 1 )
	//                 *pcType = STAT_CW;
	//             else {
	//                 if( pPDW->uPDW.x.uniPdw_status.stPdw_status.pmop_flag == 1 )
	//                     *pcType = STAT_PMOP;
	//                 else if( pPDW->uPDW.x.uniPdw_status.stPdw_status.fmop_flag == 1 ) {
	//                     if( pPDW->uPDW.x.uniPdw_status.stPdw_status.fmop_dir == 1 )
	//                         *pcType = STAT_CHIRPUP;
	//                     else
	//                         *pcType = STAT_CHIRPDN;
	//                 }
	//
	//             }
	//             ++ pcType;
	// #elif defined(_ELINT_) || defined(_XBAND_)
	//
	// #endif
	//
	//             ++ m_PDWData.uiDataItems;
	//         }
	//
	//
	//         ++ pPDW;
	//
	//     }


}

/**
 * @brief     Alloc
 * @param     unsigned int uiItems
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-06-30, 12:05
 * @warning
 */
void CSPDW::Alloc( unsigned int uiItems )
{
// 	if( uiItems == 0 ) {
// 		// uiItems = m_PDWData.uiDataItems;
// 	}
//     else if ( uiItems <= MAX_ITEMS ) {
// 	    m_PDWData.pfFreq = (float *)malloc(sizeof(float) * uiItems );
// 	    m_PDWData.pfPW = (float *)malloc(sizeof(float) * uiItems );
// 	    m_PDWData.pfAOA = (float *)malloc(sizeof(float) * uiItems );
// 	    m_PDWData.pfTOA = (float *)malloc(sizeof(float) * uiItems );
// 	    m_PDWData.pfDTOA = (float *)malloc(sizeof(float) * uiItems );
// 	    m_PDWData.pfPA = (float *)malloc(sizeof(float) * uiItems );
// 	    m_PDWData.pullTOA = (_TOA *)malloc(sizeof(_TOA) * uiItems );
//
// 	    m_PDWData.pcType = (char *)malloc(sizeof(char) * uiItems );
// 	    m_PDWData.pcDV = (char *)malloc(sizeof(char) * uiItems );
//     }
//     else {
//
//     }

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
// 	_SAFE_FREE(m_PDWData.pfFreq);
// 	_SAFE_FREE(m_PDWData.pfPW);
// 	_SAFE_FREE(m_PDWData.pfAOA);
// 	_SAFE_FREE(m_PDWData.pfTOA);
// 	_SAFE_FREE(m_PDWData.pfDTOA);
// 	_SAFE_FREE(m_PDWData.pfPA);
//     _SAFE_FREE( m_PDWData.pullTOA );
// 	_SAFE_FREE(m_PDWData.pcType);
// 	_SAFE_FREE(m_PDWData.pcDV);

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
 * @brief     GetRealData
 * @return    void *
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-11-24 14:38:34
 * @warning
 */
void *CSPDW::GetRealData()
{
    return & m_PDWRealData;
}

/**
  * @brief
  * @return 	void
  * @date       2019/06/07 10:10
*/
// void CSPDW::ConvertPDWData( STR_PDWDATA *pPDWData, STR_FILTER_SETUP *pFilterSetup, bool bSwap, ENUM_CONVERT_OPTION enOption )
// {
//
// }

#endif



#if defined(_GRAPH_) || defined(_KFX_)
//////////////////////////////////////////////////////////////////////////
CKFXPDW::CKFXPDW(STR_RAWDATA *pRawData, STR_FILTER_SETUP *pstFilterSetup ) : CData( )
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
CKFXPDW::~CKFXPDW(void)
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
void CKFXPDW::Alloc( unsigned int uiItems )
{

// 	if( uiItems == 0 ) {
// 		//uiItems = m_PDWData.uiDataItems;
// 	}
//     else if ( uiItems <= MAX_ITEMS ) {
//         m_PDWData.pfFreq = (float *)malloc(sizeof(float) * uiItems);
//         m_PDWData.pfPW = (float *)malloc(sizeof(float) * uiItems );
//         m_PDWData.pfAOA = (float *)malloc(sizeof(float) * uiItems);
//         m_PDWData.pfTOA = (float *)malloc(sizeof(float) * uiItems);
//         m_PDWData.pfDTOA = (float *)malloc(sizeof(float) * uiItems);
//         m_PDWData.pfPA = (float *)malloc(sizeof(float) * uiItems);
//         m_PDWData.pullTOA = (_TOA *)malloc(sizeof(_TOA) * uiItems);
//
//         m_PDWData.pcType = (char *)malloc(sizeof(char) * uiItems);
//         m_PDWData.pcDV = (char *)malloc(sizeof(char) * uiItems);
//     }
//     else {
//
//     }
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
// 	_SAFE_FREE(m_PDWData.pfFreq);
// 	_SAFE_FREE(m_PDWData.pfPW);
// 	_SAFE_FREE(m_PDWData.pfAOA);
// 	_SAFE_FREE(m_PDWData.pfTOA);
// 	_SAFE_FREE(m_PDWData.pfDTOA);
// 	_SAFE_FREE(m_PDWData.pfPA);
// 	_SAFE_FREE(m_PDWData.pullTOA);
// 	_SAFE_FREE(m_PDWData.pcType);
// 	_SAFE_FREE(m_PDWData.pcDV);

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

void *CKFXPDW::GetRealData()
{
    return & m_PDWRealData;
}

/**
  * @brief
  * @return 	void
  * @date       2019/06/07 10:10
*/
void CKFXPDW::ConvertPDWData( STR_PDWDATA *pPDWData, STR_FILTER_SETUP *pFilterSetup, bool bSwap, ENUM_CONVERT_OPTION enOption )
{
//     unsigned int i;
//
// 	float *pfFreq = m_PDWData.pfFreq;
// 	float *pfPW = m_PDWData.pfPW;
// 	float *pfAOA = m_PDWData.pfAOA;
// 	float *pfTOA = m_PDWData.pfTOA;
// 	float *pfDTOA = m_PDWData.pfDTOA;
// 	float *pfPA = m_PDWData.pfPA;
//
// 	char *pcType = m_PDWData.pcType;
// 	char *pcDV = m_PDWData.pcDV;
//
// 	_TOA *pullTOA = m_PDWData.pullTOA;
//
// 	float /*fToa,*/ /* firstToa, */ preToa;
//
// 	unsigned long long int llToa;
// 	UDRCPDW *pPDW = (UDRCPDW *) & m_pRawDataBuffer[m_iHeaderSize];
//
// // 	m_spOneSec = 20000000.;
// // 	m_spOneMilli = FDIV( m_spOneSec, 1000. );
// // 	m_spOneMicrosec = FDIV( m_spOneMilli, 1000. );
// // 	m_spOneNanosec = FDIV( m_spOneMicrosec, 1000. );
// //
// // 	m_spAOAres = (float) ( 0.351562 );
// // 	m_spAMPres = (float) (0.351562);
// // 	m_spPWres = m_spOneMicrosec;
//
// 	m_PDWData.uiDataItems = 0;
//
//     //Log( enNormal, "ConvertArray()를 [%d]개를 변환합니다." , m_RawData.uiDataItems );
//
//     for (i = 0; i < m_PDWData.uiDataItems ; ++i) {
// 		llToa = (_TOA) ( pPDW->sPDWFormat.m_LSBTOA ) | ( (_TOA) pPDW->sPDWFormat.m_MSBTOA << 32 );
// 		*pullTOA = llToa;
// 		if (i == 0) {
// // 			if( iOffset != 0 ) {
// // 				m_ll1stToa = llToa;
// // 			}
// 			*pfTOA = DecodeTOA( llToa );
// 			*pfDTOA = 0;
// 			preToa = *pfTOA;
// 		}
// 		else {
// 			*pfTOA = DecodeTOA( llToa-llToa );
//
// 			*pfDTOA = ( *pfTOA - preToa );
//
// 			preToa = *pfTOA;
// 			}
//
// 		*pfFreq = DecodeFREQ( pPDW->sPDWFormat.m_freq );		// MHz
//
// 		*pfPW = DecodePW( pPDW->sPDWFormat.m_PW );
//
// 		*pfAOA = DecodeDOA( pPDW->sPDWFormat.m_DOA );
//
// 		*pfPA = DecodePA( pPDW->sPDWFormat.m_PA );
//
// 		*pcType = 0; // pPDW->sPDWFormat.m_sigType;
//
// 		*pcDV = pPDW->sPDWFormat.m_DI;
//
// 		printf( "\n [%3d] 0x%02X %5.1f%1c[deg] %8.2f[MHz] %10.3f[us] %8.3f[ns]" , i+1, *pcType, *pfAOA, stDV[*pcDV], *pfFreq, *pfTOA, *pfPW );
//
// 		// 필터링 조건
// // 		if( ( m_strFilterSetup.dToaMin <= *pfTOA && m_strFilterSetup.dToaMax >= *pfTOA ) &&
// // 			( m_strFilterSetup.dAoaMin <= *pfAOA && m_strFilterSetup.dAoaMax >= *pfAOA ) &&
// // 			( m_strFilterSetup.dPAMin <= *pfPA && m_strFilterSetup.dPAMax >= *pfPA ) &&
// // 			( m_strFilterSetup.dPWMin <= *pfPW && m_strFilterSetup.dPWMax >= *pfPW ) &&
// // 			( m_strFilterSetup.dFrqMin <= *pfFreq && m_strFilterSetup.dFrqMax >= *pfFreq ) ) {
// // 				++pfFreq;
// // 				++pfAOA;
// // 				++pfPW;
// // 				++pfPA;
// // 				++pfTOA;
// // 				++pfDTOA;
// // 				++pcType;
// // 				++pcDV;
// // 				++pullTOA;
// //
// // 				++ m_PDWData.uiDataItems;
// //
// // 				//++ m_stFilterSetup.uiDataItems;
// //
// // 		}
//
// 		++pPDW;
// 		}
//
//     //Log( enNormal, "필터링 PDW 개수는 %d 입니다.", m_PDWData.uiDataItems );
}

#endif


//////////////////////////////////////////////////////////////////////////

/**
 * @brief CPOCKETSONATAPDW::CPOCKETSONATAPDW
 * @param pRawData
 * @param pstFilterSetup
 */
CPOCKETSONATAPDW::CPOCKETSONATAPDW( char *pRawData, STR_FILTER_SETUP *pstFilterSetup, int iBoardID ) : CData( )
{
    m_enDataType = en_PDW_DATA;
    m_enUnitType = en_ZPOCKETSONATA;

    m_szFileSize = sizeof( union UNION_HEADER ) + 1;

	CPOCKETSONATAPDW::Init( pRawData );

#if 0
    int iSize1 = sizeof( union UNION_HEADER );
    int iSize2 = sizeof( struct STR_POCKETSONATA_HEADER );

#endif

}

/**
 * @brief
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022/02/18 22:28:42
 * @warning
 */
void CPOCKETSONATAPDW::Init( char *pRawData, STR_FILTER_SETUP *pstFilterSetup )
{
    UNION_HEADER *puniPDWFileHeader;

    m_pRawHeaderBuffer = (char *) & pRawData[0];
    //if( m_szFileSize <= sizeof( union UNION_HEADER ) ) {
    if( m_szFileSize <= sizeof( union UNION_HEADER ) ) { //|| m_szFileSize <= sizeof( struct STR_POCKETSONATA_HEADER ) ) {
        m_pRawDataBuffer = NULL;
	}
    else {
        m_pRawDataBuffer = (char *) & pRawData[sizeof( struct STR_POCKETSONATA_HEADER )];
	}

    puniPDWFileHeader = ( UNION_HEADER * ) m_pRawHeaderBuffer;

    CPOCKETSONATAPDW::UpdateHeaderSize();

    // 헤더 크기 초기화
    if( puniPDWFileHeader != NULL && m_pRawDataBuffer != NULL ) {
        m_uiTotalDataItems = puniPDWFileHeader->GetTotalPDW( m_enUnitType );
        m_iBoardID = puniPDWFileHeader->GetBoardID( m_enUnitType );
    }
    else {
        m_uiTotalDataItems = 0;
        m_iBoardID = 0;
    }

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
void CPOCKETSONATAPDW::Alloc( unsigned int uiItems )
{

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

void *CPOCKETSONATAPDW::GetRealData()
{
    return & m_PDWRealData;
}


/**
  * @brief      포켓 소나타용 으로 PDW 데이터를 변환한다.
  * @return 	void
  * @date       2019/06/07 10:10
*/
void CPOCKETSONATAPDW::ConvertArrayData( STR_PDWDATA *pPDWData, bool bSwap, STR_FILTER_SETUP *pFilterSetup )
{
//     unsigned int i;
//     int iCh;
//
//     float *pfFreq, *pfPW, *pfAOA, *pfTOA, *pfDTOA, *pfPA;
//     char *pcType, *pcDV;
//     _TOA *pullTOA;
//
//     _TOA ullToa;
//
//     //float preToa;
//
//     UINT uiFreq, uiPW, uiPA, uiAOA;
//
//     pfFreq = m_PDWData.pfFreq;
//     pfPW = m_PDWData.pfPW;
//     pfAOA = m_PDWData.pfAOA;
//     pfTOA = m_PDWData.pfTOA;
//     pfDTOA = m_PDWData.pfDTOA;
//     pfPA = m_PDWData.pfPA;
//
//     pcType = m_PDWData.pcType;
//     pcDV = m_PDWData.pcDV;
//
//     pullTOA = m_PDWData.pullTOA;
//
//     DMAPDW *pPDW = (DMAPDW *) & m_pRawDataBuffer[0];
//
//     m_PDWData.uiDataItems = 0;
//
//     for( i=0 ; i < m_uiTotalDataItems ; ++i ) {
//         int iFreq;
//
//         ullToa = (_TOA) ( pPDW->uPDW.x.uniPdw_freq_toa.stPdw_freq_toa.toa_L ) | ( (_TOA) pPDW->uPDW.x.uniPdw_toa_edge.stPdw_toa_edge.toa_H << 16 );
//
//         // 주파수 변환
//         iCh = pPDW->uPDW.x.uniPdw_freq_toa.stPdw_freq_toa.pdw_phch;
//         iCh = ( 16 + ( iCh - 8 ) ) % 16;
//
//         iFreq = ( pPDW->uPDW.x.uniPdw_pw_freq.stPdw_pw_freq.frequency_L ) | ( pPDW->uPDW.x.uniPdw_freq_toa.stPdw_freq_toa.frequency_H << 8 );
//         iFreq = ( 0x10000 + ( iFreq - 0x8000 ) ) % 0x10000;
//
//         uiFreq = iFreq + ( iCh * 0x10000 );
//
//         // 펄스폭 저장
//         uiPW = pPDW->uPDW.x.uniPdw_pw_freq.stPdw_pw_freq.pulse_width;
//
//         // 방위 저장
//         uiAOA = pPDW->uPDW.x.uniPdw_dir_pa.stPdw_dir_pa.doa;
//
//         // 신호 세기 저장
//         uiPA = pPDW->uPDW.x.uniPdw_dir_pa.stPdw_dir_pa.pa;
//
//         // 필터링 조건
//         if( ( m_strFilterSetup.ullToaMin <= ullToa && m_strFilterSetup.ullToaMax >= ullToa ) &&
//             ( m_strFilterSetup.uiAoaMin <= uiAOA && m_strFilterSetup.uiAoaMax >= uiAOA ) &&
//             ( m_strFilterSetup.uiPAMin <= uiPA && m_strFilterSetup.uiPAMax >= uiPA ) &&
//             ( m_strFilterSetup.uiPWMin <= uiPW && m_strFilterSetup.uiPWMax >= uiPW ) &&
//             ( m_strFilterSetup.uiFrqMin <= uiFreq && m_strFilterSetup.uiFrqMax >= uiFreq ) ) {
//
//             // 시간 저장
//             *pullTOA++ = ullToa;
//
//             *pfFreq++ = DecodeFREQMHz( uiFreq );
//             *pfPW++ = DecodePW( uiPW );
//             *pfAOA++ = DecodeDOA( uiAOA );
//             *pfPA++ = DecodePA( uiPA );
//
//             // 신호 형태 저장
// #ifdef _POCKETSONATA_
//             *pcType = STAT_NORMAL;
//             if( pPDW->uPDW.x.uniPdw_status.stPdw_status.cw_pulse == 1 )
//                 *pcType = STAT_CW;
//             else {
//                 if( pPDW->uPDW.x.uniPdw_status.stPdw_status.pmop_flag == 1 )
//                     *pcType = STAT_PMOP;
//                 else if( pPDW->uPDW.x.uniPdw_status.stPdw_status.fmop_flag == 1 ) {
//                     if( pPDW->uPDW.x.uniPdw_status.stPdw_status.fmop_dir == 1 )
//                         *pcType = STAT_CHIRPUP;
//                     else
//                         *pcType = STAT_CHIRPDN;
//                 }
//
//             }
//             ++ pcType;
// #elif defined(_ELINT_) || defined(_XBAND_)
//
// #endif
//
//             ++ m_PDWData.uiDataItems;
//         }
//
//
//         ++ pPDW;
//
//     }


}


/**
 * @brief		GetHeaderSize
 * @return		unsigned int
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2020/12/24 14:48:53
 * @warning
 */
int CPOCKETSONATAPDW::GetHeaderSize()
{
    memcpy( & m_stHeader, m_pRawHeaderBuffer, sizeof(m_stHeader) );

    m_iHeaderSize = sizeof( struct STR_POCKETSONATA_HEADER);

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
	return sizeof(struct _PDW);
}

/**
 * @brief		GetDataSize
 * @return		unsigned int
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2020/12/24 15:02:30
 * @warning
 */
unsigned int CPOCKETSONATAPDW::GetDataItems( unsigned long long ullFileSize )
{
    unsigned int uiDataItems;

    memcpy( & m_stHeader, & m_pRawHeaderBuffer[0], sizeof( struct STR_POCKETSONATA_HEADER) );

    uiDataItems = m_stHeader.GetTotalPDW();

	return uiDataItems;
}

/**
 * @brief
 * @param     STR_PDWDATA * pPDWData
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date      2022/02/15 22:05:46
 * @warning
 */
void CPOCKETSONATAPDW::MakeHeaderData( STR_PDWDATA *pPDWData )
{
    memcpy( & pPDWData->x.ps, & m_stHeader, sizeof(m_stHeader) );

}

/**
 * @brief       장치에 따라 PDW 구조체로 변환한다
 * @param		STR_PDWDATA * pPDWData
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date      2022/02/16 23:07:14
 * @warning
 */
void CPOCKETSONATAPDW::MakePDWDataByUnitToPDW( STR_PDWDATA *pPDWData )
{
    unsigned int i, uiDataItems;
    int iCh;

    _TOA ullToa;
    UINT uiFreq, uiPW, uiPA, uiAOA;

    _PDW *pPDW = & pPDWData->pstPDW[0];

    DMAPDW *pDMAPDW = (DMAPDW *) & m_pRawDataBuffer[0];

    uiDataItems = 0;

    for( i=0 ; i < m_uiTotalDataItems ; ++i ) {
        ullToa = (_TOA) ( pDMAPDW->GetTOA() );

        // 방위 저장
        uiAOA = pDMAPDW->GetAOA();

        // 주파수 변환
        iCh = pDMAPDW->GetChannel();
        uiFreq = pDMAPDW->GetFrequency();

        // 펄스폭 저장
        uiPW = pDMAPDW->GetPulsewidth();

        // 신호 세기 저장
        uiPA = pDMAPDW->GetPulseamplitude();

        // 필터링 조건
        if( ( m_strFilterSetup.ullToaMin <= ullToa && m_strFilterSetup.ullToaMax >= ullToa ) &&
            ( m_strFilterSetup.uiAoaMin <= uiAOA && m_strFilterSetup.uiAoaMax >= uiAOA ) &&
            ( m_strFilterSetup.uiPAMin <= uiPA && m_strFilterSetup.uiPAMax >= uiPA ) &&
            ( m_strFilterSetup.uiPWMin <= uiPW && m_strFilterSetup.uiPWMax >= uiPW ) &&
            ( m_strFilterSetup.uiFrqMin <= uiFreq && m_strFilterSetup.uiFrqMax >= uiFreq ) ) {
                if( pPDW != NULL ) {
                    memset( pPDW, 0, sizeof(struct _PDW) );

                    // 시간 저장
                    pPDW->tTOA = ullToa;
                    pPDW->uiAOA = uiAOA;
                    pPDW->uiFreq = uiFreq;
                    pPDW->uiPW = uiPW;
                    pPDW->uiPA = uiPA;

                    pPDW->iStat = pDMAPDW->GetPulsetype();

                    pPDW->uiIndex = pDMAPDW->GetIndex();

                    // 상태 값 저장
#if defined(_POCKETSONATA_) || defined(_712_)
                    pPDW->x.ps.x.stStrBitMap.CwPulse = pDMAPDW->uPDW.stHwPdwDataRf.CwPulse;
                    pPDW->x.ps.x.stStrBitMap.Pmop = pDMAPDW->uPDW.stHwPdwDataRf.Pmop;
                    pPDW->x.ps.x.stStrBitMap.Fmop = pDMAPDW->uPDW.stHwPdwDataRf.Fmop;
                    pPDW->x.ps.x.stStrBitMap.FmopDir = pDMAPDW->uPDW.stHwPdwDataRf.FmopDir;
#endif

                    pPDW->SetChannel( iCh );

                    ++ uiDataItems;

                    ++ pPDW;
                }
        }

        ++ pDMAPDW;

    }

    m_PDWData.SetTotalPDW( uiDataItems );

}


/**
 * @brief     MakePDWDataToReal
 * @param     STR_PDWREALDATA * pPDWData
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-02-22, 15:27
 * @warning
 */
void CPOCKETSONATAPDW::MakePDWDataToReal( STR_PDWREALDATA *pPDWRealData )
{
    bool bFirstTOA = true;
    unsigned int i, uiDataItems;
    //int iCh;

    _TOA ullTOA, ullFirstTOA, ullPreTOA = 0;
    int iPulseType;
    unsigned int uiIndex;
    UINT uiFreq, uiPW, uiPA, uiAOA;

    _TOA *pullTOA = pPDWRealData->pullTOA;

    float *pfAOA = pPDWRealData->pfAOA;
    float *pfFreq = pPDWRealData->pfFreq;
    float *pfPA = pPDWRealData->pfPA;
    float *pfPW = pPDWRealData->pfPW;

    double *pdTOA = pPDWRealData->pdTOA;
    float *pfDTOA = pPDWRealData->pfDTOA;

    char *pcType = pPDWRealData->pcType;
    char *pcDV = pPDWRealData->pcDV;

    unsigned int *puiIndex = pPDWRealData->puiIndex;

    _PDW *pPDW = ( _PDW * ) & m_pRawDataBuffer[0];

    uiDataItems = 0;

    if( pPDW != NULL ) {
        for( i=0 ; i < m_uiTotalDataItems ; ++i ) {
            // 시간 정보
            ullTOA = pPDW->GetTOA();

            // 방위 저장
            uiAOA = pPDW->GetAOA();

            // 주파수 변환
            uiFreq = pPDW->GetFrequency();

            // 펄스폭 저장
            uiPW = pPDW->GetPulsewidth();

            // 신호 세기 저장
            uiPA = pPDW->GetPulseamplitude();

		    iPulseType = pPDW->GetPulsetype();

            uiIndex = pPDW->GetIndex();

            // 필터링 조건
            if( (m_strFilterSetup.ullToaMin <= ullTOA && m_strFilterSetup.ullToaMax >= ullTOA) &&
                (m_strFilterSetup.uiAoaMin <= uiAOA && m_strFilterSetup.uiAoaMax >= uiAOA) &&
                (m_strFilterSetup.uiPAMin <= uiPA && m_strFilterSetup.uiPAMax >= uiPA) &&
                (m_strFilterSetup.uiPWMin <= uiPW && m_strFilterSetup.uiPWMax >= uiPW) &&
                (m_strFilterSetup.uiFrqMin <= uiFreq && m_strFilterSetup.uiFrqMax >= uiFreq) ) {
                //iCh = pPDW->GetChannel();

                if( bFirstTOA == true ) {
                    _EQUALS3( ullPreTOA, ullFirstTOA, ullTOA )

                    bFirstTOA = false;
                }
                *pfDTOA++ = (float) CPOCKETSONATAPDW::DecodeTOAs( ullTOA - ullPreTOA);
                ullPreTOA = ullTOA;

                // 시간 저장
                *pullTOA++ = ullTOA;

                *pdTOA++ = CPOCKETSONATAPDW::DecodeTOAs( ullTOA );
                *pfAOA++ = CPOCKETSONATAPDW::DecodeDOA( (int) uiAOA );
                *pfFreq++ = CPOCKETSONATAPDW::DecodeFREQ( (int) uiFreq );
                *pfPA++ = CPOCKETSONATAPDW::DecodePA( (int) uiPA );
                *pfPW++ = CPOCKETSONATAPDW::DecodePW((int) uiPW );

                *pcType++ = iPulseType;
                *pcDV++ = 1;

                *puiIndex++ = uiIndex;

                ++uiDataItems;
            }

            ++pPDW;

        }
    }

    m_PDWRealData.SetTotalPDW( uiDataItems );

}


#if defined(_GRAPH_) || defined(_701_)

//////////////////////////////////////////////////////////////////////////

/**
 * @brief     CData
 * @param     char * pRawData
 * @param     STR_FILTER_SETUP * pstFilterSetup
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-11-24 15:23:29
 * @warning
 */
C7PDW::C7PDW(char *pRawData, STR_FILTER_SETUP *pstFilterSetup, ENUM_DataType enDataType) : CData()
{
	m_bSwap = false;

    m_enDataType = enDataType;
    m_enUnitType = en_701;

	m_enBandWidth = _701::enNARROW_BW;

	C7PDW::Init(pRawData);

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
 * @param     char * pRawData
 * @param     STR_FILTER_SETUP * pstFilterSetup
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-11-24 15:24:03
 * @warning
 */
void C7PDW::Init( char *pRawData, STR_FILTER_SETUP *pstFilterSetup )
{
	UNION_HEADER *puniPDWFileHeader;

	if (m_enDataType == en_PDW_DATA_CSV) {
		unsigned int uiTotalDataItems = (unsigned int) -1;
		int iDataIndex = 0;
		char *pIndex;

		m_pRawHeaderBuffer = (char *)& pRawData[0];

		// 헤더 찾기
		pIndex = strstr( & pRawData[0], "\r\n");
		if (pIndex != NULL) {
			iDataIndex = pIndex - &pRawData[0] + 2;

			// PDW 항목 개수 카운팅
			do {
				pIndex += 2;
				++uiTotalDataItems;
			} while ((pIndex = strstr(pIndex, "\r\n")) != NULL);
		}

		m_pRawDataBuffer = (char *)& pRawData[ iDataIndex ];

		memset(&m_uniHeader, 0, sizeof(union UNION_HEADER));
		puniPDWFileHeader = (UNION_HEADER *) & m_uniHeader;

		m_uniHeader.SetTotalPDW(uiTotalDataItems);
		m_uniHeader.SetTaskID("CSV");

	}
	else {
		m_pRawHeaderBuffer = (char *)& pRawData[0];
		m_pRawDataBuffer = (char *)& pRawData[sizeof(union UNION_HEADER)];

		puniPDWFileHeader = (UNION_HEADER *)m_pRawHeaderBuffer;

	}

    C7PDW::UpdateHeaderSize();

	m_uiTotalDataItems = puniPDWFileHeader->GetTotalPDW(m_enUnitType);

	//m_iBoardID = puniPDWFileHeader->GetBoardID(m_enUnitType);
}


/**
 * @brief
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/02/27 21:44:02
 * @warning
 */
void C7PDW::Alloc( unsigned int uiItems )
{

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
 * @brief     GetRealData
 * @return    STR_PDWREALDATA *
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-01-19 13:07:18
 * @warning
 */
void *C7PDW::GetRealData()
{
    return & m_PDWRealData;
}

/**
 * @brief     701 헤더를 복사한다.
 * @param     STR_PDWDATA * pPDWData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-01-08 11:34:18
 * @warning
 */
void C7PDW::MakeHeaderData(STR_PDWDATA *pPDWData)
{
	memcpy(&pPDWData->x.e7, &m_stHeader, sizeof(m_stHeader));

}

/**
  * @brief
  * @return 	void
  * @date       2019/06/07 10:10
*/
void C7PDW::ConvertArrayData( STR_PDWDATA *pPDWData, bool bSwap, STR_FILTER_SETUP *pFilterSetup )
{


}

/**
 * @brief     MakePDWDataToReal
 * @param     STR_PDWREALDATA * pPDWRealData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-11-24 15:26:40
 * @warning
 */
void C7PDW::MakePDWDataToReal(STR_PDWREALDATA *pPDWRealData)
{
	bool bFirstTOA = true;
	unsigned int i, uiDataItems;
	int iCh;

	_TOA ullTOA, ullFirstTOA, ullPreTOA = 0;
	int iPulseType;
	UINT uiFreq, uiPW, uiPA, uiAOA, uiDirectionValid;

	SRxPDWDataRGroup stRxPDWDataRGroup;

	_PDW *pPDW;

	_TOA *pullTOA = pPDWRealData->pullTOA;

	float *pfAOA = pPDWRealData->pfAOA;
	float *pfFreq = pPDWRealData->pfFreq;
	float *pfPA = pPDWRealData->pfPA;
	float *pfPW = pPDWRealData->pfPW;

	double *pdTOA = pPDWRealData->pdTOA;
	float *pfDTOA = pPDWRealData->pfDTOA;

	char *pcType = pPDWRealData->pcType;
	char *pcDV = pPDWRealData->pcDV;

	int iIndex = 0;

	uiDataItems = 0;

	if (m_enDataType == en_PDW_DATA_CSV) {
		pPDW = NULL;
	}
	else {
		pPDW = (_PDW *)& m_pRawDataBuffer[0];
	}

	for (i = 0; i < m_uiTotalDataItems; ++i) {
		if (m_enDataType == en_PDW_DATA_CSV) {
			iIndex += UpdateRow(&stRxPDWDataRGroup, (char *)& m_pRawDataBuffer[iIndex]);

			// 시간 정보
			ullTOA = stRxPDWDataRGroup.GetTOA(m_enDataType);

			// 방위 저장
			uiAOA = stRxPDWDataRGroup.GetAOA(m_enDataType);

			// 주파수 변환
			iCh = stRxPDWDataRGroup.GetChannel(m_enDataType);
			uiFreq = stRxPDWDataRGroup.GetFrequency( m_enDataType);

			// 펄스폭 저장
			uiPW = stRxPDWDataRGroup.GetPulsewidth(m_enDataType);

			// 신호 세기 저장
			uiPA = stRxPDWDataRGroup.GetPulseamplitude(m_enDataType);

			// 신호 형태
			iPulseType = stRxPDWDataRGroup.GetPulsetype(m_enDataType);

			// 방탐 유효
			uiDirectionValid = stRxPDWDataRGroup.GetDirectionValid(m_enDataType);
		}
		else {
			// 시간 정보
			ullTOA = pPDW->GetTOA();

			// 방위 저장
			uiAOA = pPDW->GetAOA();

			// 주파수 변환
			iCh = pPDW->GetChannel();
			uiFreq = pPDW->GetFrequency(iCh );

			// 펄스폭 저장
			uiPW = pPDW->GetPulsewidth();

			// 신호 세기 저장
			uiPA = pPDW->GetPulseamplitude();

			// 신호 형태
			iPulseType = pPDW->GetPulsetype();

			// 방탐 유효
			uiDirectionValid = pPDW->GetDirectionValid();
		}

		// 필터링 조건
		if ((m_strFilterSetup.ullToaMin <= ullTOA && m_strFilterSetup.ullToaMax >= ullTOA) &&
			(m_strFilterSetup.uiAoaMin <= uiAOA && m_strFilterSetup.uiAoaMax >= uiAOA) &&
			(m_strFilterSetup.uiPAMin <= uiPA && m_strFilterSetup.uiPAMax >= uiPA) &&
			(m_strFilterSetup.uiPWMin <= uiPW && m_strFilterSetup.uiPWMax >= uiPW) &&
			(m_strFilterSetup.uiFrqMin <= uiFreq && m_strFilterSetup.uiFrqMax >= uiFreq)) {
			if (bFirstTOA == true) {
				_EQUALS3(ullPreTOA, ullFirstTOA, ullTOA)

				bFirstTOA = false;
			}
 			*pfDTOA++ = (float)C7PDW::DecodeTOA(ullTOA - ullPreTOA, m_enBandWidth);
 			ullPreTOA = ullTOA;


 			// 시간 저장
 			*pullTOA++ = ullTOA;

 			*pdTOA++ = C7PDW::DecodeTOA(ullTOA, m_enBandWidth );
 			*pfAOA++ = C7PDW::DecodeDOA(uiAOA);
 			*pfFreq++ = C7PDW::DecodeFREQ(uiFreq);
 			*pfPA++ = C7PDW::DecodePA(uiPA);
 			*pfPW++ = C7PDW::DecodePW(uiPW, m_enBandWidth);

			*pcType++ = iPulseType;
			*pcDV++ = uiDirectionValid;

			++uiDataItems;

		}

		if (m_enDataType != en_PDW_DATA_CSV) {
			++pPDW;
		}

	}

	pPDWRealData->SetTotalPDW(uiDataItems);

}

/**
 * @brief     MakeCSVDataToPDW
 * @param     void
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-01-19 13:20:23
 * @warning
 */
void C7PDW::MakeCSVDataToPDW(void)
{
	unsigned int i;

	SRxPDWDataRGroup stRxPDWDataRGroup;

	_PDW *pPDW;

	pPDW = m_PDWData.pstPDW;

	int iIndex = 0;

	if (m_enDataType == en_PDW_DATA_CSV) {
		for (i = 0; i < m_uiTotalDataItems; ++i) {
			iIndex += UpdateRow(&stRxPDWDataRGroup, (char *)& m_pRawDataBuffer[iIndex]);

			// 시간 정보
			pPDW->tTOA = stRxPDWDataRGroup.GetTOA(m_enDataType);

			// 방위 저장
			pPDW->uiAOA = stRxPDWDataRGroup.GetAOA(m_enDataType);

			// 주파수 변환
			pPDW->x._701.iChannel = stRxPDWDataRGroup.GetChannel(m_enDataType);
			pPDW->uiFreq = stRxPDWDataRGroup.GetFrequency( m_enDataType);

			// 펄스폭 저장
			pPDW->uiPW = stRxPDWDataRGroup.GetPulsewidth(m_enDataType);

			// 신호 세기 저장
			pPDW->uiPA = stRxPDWDataRGroup.GetPulseamplitude(m_enDataType);

			// 신호 형태
			pPDW->iStat = stRxPDWDataRGroup.GetPulsetype(m_enDataType);

			// 방탐 유효
			pPDW->x._701.iDirectionValid = stRxPDWDataRGroup.GetDirectionValid(m_enDataType);

			++pPDW;

		}
	}

	m_PDWData.SetTotalPDW(m_uiTotalDataItems);

}


/**
 * @brief     UpdateRow
 * @param     SRxPDWDataRGroup * pstRxPDWDataRGroup
 * @param     char * pData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-01-17 18:11:35
 * @warning
 */
int C7PDW::UpdateRow(SRxPDWDataRGroup *pstRxPDWDataRGroup, char *pData )
{
	int iIndex;

	vector<string> vecValues;

	iIndex = CCommonUtils::Parsing( & vecValues, pData);

	pstRxPDWDataRGroup->uiPDWID = (UINT) atoi( vecValues[0].c_str() );

	if (vecValues[1].compare( "Pulse" ) == 0) {
 		pstRxPDWDataRGroup->uiPulseType = STAT_NORMAL;
 	}
 	else {
 		pstRxPDWDataRGroup->uiPulseType = STAT_CW;
 	}

	pstRxPDWDataRGroup->uiDirection = (unsigned int) ( atof(vecValues[2].c_str()) * 10. + 0.5 );
	pstRxPDWDataRGroup->uiFreq = (unsigned int)( atof(vecValues[3].c_str()) * 100. + 0.5 );
	pstRxPDWDataRGroup->ullTOA = (_TOA) ( atof(vecValues[4].c_str()) * 1000. / _701::_toaRes[1] + 0.5 );
	pstRxPDWDataRGroup->uiPW = (unsigned int)(atof(vecValues[6].c_str()) / _701::_toaRes[1] + 0.5 );
	pstRxPDWDataRGroup->uiPA = (unsigned int)( atof(vecValues[7].c_str()) / -0.25 );
	pstRxPDWDataRGroup->uiChannelNumber = (unsigned int) atoi(vecValues[8].c_str());

	if (vecValues[12].compare("유효") == 0) {
		pstRxPDWDataRGroup->uiDirectionVaild = 0;
	}
	else {
		pstRxPDWDataRGroup->uiDirectionVaild = 1;
	}


// 	unsigned int uiDirectionVaild;
// 	unsigned int uiAcqDirectionLimit;
// 	unsigned int uiPolization;
// 	unsigned int uiPFTag;

	return iIndex;

}


/**
 * @brief		GetHeaderSize
 * @return		unsigned int
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2020/12/24 14:48:53
 * @warning
 */
int C7PDW::GetHeaderSize()
{
	if (m_enDataType == en_PDW_DATA_CSV) {
		memset(&m_stHeader, 0, sizeof(m_stHeader));

		memcpy(&m_stHeader, &m_uniHeader.e7, sizeof( struct STR_701_HEADER));
		//m_stHeader.SetTotalPDW( m_uniHeader.GetTotalPDW(m_enUnitType) );
	}
	else {
		if (m_bSwap == true) {
			AllSwapData32(&m_pRawHeaderBuffer[36], sizeof(int) * 4);
			AllSwapData32(m_pRawHeaderBuffer, sizeof(int) * 4);
		}

		memcpy(&m_stHeader, m_pRawHeaderBuffer, sizeof(m_stHeader));

		//AllSwapData32( & m_stHeader.uiAcqTime, sizeof(int)*4 );
		//AllSwapData32( & m_stHeader.iSearchBandID, sizeof(int)*4 );

		m_iHeaderSize = sizeof( struct SRxPDWHeader);
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
	return sizeof( struct SRxPDWDataRGroup);
}

/**
 * @brief		GetDataSize
 * @return		unsigned int
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2020/12/24 15:02:30
 * @warning
 */
unsigned int C7PDW::GetDataItems( unsigned long long ullFileSize )
{
	return (unsigned int) m_stHeader.GetTotalPDW();
}

#endif

//////////////////////////////////////////////////////////////////////////
//

CIQ::CIQ(STR_RAWDATA *pRawData) : CData( )
{
	//Alloc( IQ_ITEMS );
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
void CIQ::Alloc( unsigned int uiItems )
{

// 	if( uiItems == 0 ) {
// 		// uiItems = m_RawData.uiDataItems;
// 	}
//
//     else if ( uiItems <= MAX_ITEMS ) {
// 	    m_IQData.pfI = (float *) malloc( sizeof(float) * uiItems );
// 	    m_IQData.pfQ = (float *) malloc( sizeof(float) * uiItems );
// 	    m_IQData.pfPA = (float *) malloc( sizeof(float) * uiItems );
// 	    m_IQData.pfIP = (float *) malloc( sizeof(float) * uiItems );
// 	    m_IQData.pfFFT = (float *) malloc( sizeof(float) * uiItems );
//     }
//     else {
//
//     }

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
// 	_SAFE_FREE(m_IQData.pfI)
// 	_SAFE_FREE(m_IQData.pfQ)
// 	_SAFE_FREE(m_IQData.pfPA)
// 	_SAFE_FREE(m_IQData.pfIP)
// 	_SAFE_FREE(m_IQData.pfFFT)
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

/**
  * @brief		IQ 데이터 구조에 저장한다.
  * @return 	void
  * @date       2019/06/07 10:11
*/
void CIQ::ConvertPDWData( STR_PDWDATA *pPDWData, STR_FILTER_SETUP *pFilterSetup, bool bSwap, ENUM_CONVERT_OPTION enOption )
{
// 	UINT i;
//
// 	float *psI = m_IQData.pfI;
// 	float *psQ = m_IQData.pfQ;
// 	float *psPA = m_IQData.pfPA;
// 	float *psIP = m_IQData.pfIP;
// 	float *psFFT = m_IQData.pfFFT;
//
// 	float fVal1, fVal2;
//
// 	TNEW_IQ *pIQ = (TNEW_IQ *) & m_pRawDataBuffer[m_iHeaderSize];
//
// 	for (i = 0; i < m_PDWData.uiDataItems; ++i) {
// 		*psI = (float) pIQ->sI;
// 		*psQ = (float) pIQ->sQ;
//
// 		// 순시 진폭
// 		*psPA = sqrt( *psI * *psI + *psQ * *psQ );
// 		*psPA = (float) (20.*log10( *psPA ) ) - (float) 80.;
//
// 		// 순시 위상차
// 		// 		if( i == 0 ) {
// 		// 			*psIP = 0.0;
// 		// 			fVal2 = (float) ( atan2( *psQ, *psI ) * RAD2DEG );
// 		// 		}
// 		// 		else {
// 		// 			fVal1 = (float) ( atan2( *psQ, *psI ) * RAD2DEG );
// 		// 			*psIP = fVal1 - fVal2;
// 		// 			fVal2 = fVal1;
// 		// 		}
// 		// 		if( *psIP > 180. ) {
// 		// 			*psIP -= ( 2 * 180. );
// 		// 		}
// 		// 		else if( *psIP < -180 ) {
// 		// 			*psIP += ( 2 * 180. );
// 		// 		}
// 		// 		else {
// 		//
// 		// 		}
//
// 		if( i == 0 ) {
// 			*psIP = 0.0;
// 			fVal2 = (float) ( atan2( *psQ, *psI ) * RAD2DEG );
// 		}
// 		else {
// 			fVal1 = (float) ( atan2( *psQ, *psI ) * RAD2DEG );
// 			*psIP = fVal1;
// 		}
//
// 		// printf( "\n [%3d] %10d %10d" , i+1, *psI, *psQ );
//
// 		++psI;
// 		++psQ;
// 		++psPA;
// 		++psIP;
//
// 		++pIQ;
// 	}
//
//     ExecuteFFT( m_PDWData.uiDataItems, & m_IQData );

}

//////////////////////////////////////////////////////////////////////////

CEIQ::CEIQ(STR_RAWDATA *pRawData) : CData()
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

void CEIQ::Init( char *pRawData, STR_FILTER_SETUP *pstFilterSetup )
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
void CEIQ::Alloc( unsigned int uiItems )
{

// 	if( uiItems == 0 ) {
// 		// uiItems = m_RawData.uiDataItems;
// 	}
//     else if ( uiItems <= MAX_ITEMS ) {
//         m_IQData.pfI = (float *)malloc( sizeof(float) * uiItems );
// 	    m_IQData.pfQ = (float *)malloc( sizeof(float) * uiItems );
// 	    m_IQData.pfPA = (float *)malloc( sizeof(float) * uiItems );
// 	    m_IQData.pfIP = (float *)malloc( sizeof(float) * uiItems );
// 	    m_IQData.pfFFT = (float *)malloc( sizeof(float) * uiItems );
//     }
//     else {
//     }

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
// 	_SAFE_FREE(m_IQData.pfI);
// 	_SAFE_FREE(m_IQData.pfQ);
// 	_SAFE_FREE(m_IQData.pfPA);
// 	_SAFE_FREE(m_IQData.pfIP);
// 	_SAFE_FREE(m_IQData.pfFFT);
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

void *CEIQ::GetRealData()
{
    return NULL;
}

/**
  * @brief		IQ 데이터 구조에 저장한다.
  * @return 	void
  * @date       2019/06/07 10:11
*/
void CEIQ::ConvertArrayData( STR_PDWDATA *pPDWData, bool bSwap, STR_FILTER_SETUP *pFilterSetup )
{
//     unsigned int i;
//
// 	float *psI = m_IQData.pfI;
// 	float *psQ = m_IQData.pfQ;
// 	float *psPA = m_IQData.pfPA;
// 	float *psIP = m_IQData.pfIP;
// 	float *psFFT = m_IQData.pfFFT;
//
// 	float fVal1, fVal2;
//
// 	TNEW_IQ *pIQ;
//
// 	pIQ = (TNEW_IQ *) & m_pRawDataBuffer[m_iHeaderSize];
// // 	if( iOffset <= 0 ) {
// //        	pIQ = (TNEW_IQ *) & m_pRawDataBuffer[0];
// // 	}
// // 	else {
// // 		pIQ = (TNEW_IQ *) & m_pRawDataBuffer[iOffset];
// // 	}
//
//     //Log( enNormal, "ConvertArray()를 [%d]개를 변환합니다." , m_RawData.uiDataItems );
//
// 	m_IQData.iDataItems = 0;
//
//     for (i = 0; i < m_PDWData.uiDataItems ; ++i ) {
// 		*psI = (float) pIQ->sI;
// 		*psQ = (float) pIQ->sQ;
//
// 		// 순시 진폭
// 		*psPA = sqrt( *psI * *psI + *psQ * *psQ );
// 		*psPA = (float) (20.*log10( *psPA ) ) - (float) 80.;
//
// 		// 순시 위상차
// // 		if( i == 0 ) {
// // 			*psIP = 0.0;
// // 			fVal2 = (float) ( atan2( *psQ, *psI ) * RAD2DEG );
// // 		}
// // 		else {
// // 			fVal1 = (float) ( atan2( *psQ, *psI ) * RAD2DEG );
// // 			*psIP = fVal1 - fVal2;
// // 			fVal2 = fVal1;
// // 		}
// // 		if( *psIP > 180. ) {
// // 			*psIP -= ( 2 * 180. );
// // 		}
// // 		else if( *psIP < -180 ) {
// // 			*psIP += ( 2 * 180. );
// // 		}
// // 		else {
// //
// // 		}
// 		if( i == 0 ) {
// 			*psIP = 0.0;
// 			fVal2 = (float) ( atan2( *psQ, *psI ) * RAD2DEG );
// 		}
// 		else {
// 			fVal1 = (float) ( atan2( *psQ, *psI ) * RAD2DEG );
// 			*psIP = fVal1;
// 		}
//
// 		// printf( "\n [%3d] %10d %10d" , i+1, *psI, *psQ );
//
// 		++psI;
// 		++psQ;
// 		++psPA;
// 		++psIP;
//
// 		++ m_IQData.iDataItems;
//
// 		++pIQ;
// 		}
//
//     ExecuteFFT( m_PDWData.uiDataItems, & m_IQData );

}


/**
 * @brief		GetHeaderSize
 * @return		unsigned int
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2020/12/24 14:48:53
 * @warning
 */
int CEIQ::GetHeaderSize()
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
	return sizeof( struct SRxPDWDataRGroup);
}


/**
 * @brief		GetDataItems
 * @return		unsigned int
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2020/12/28 10:19:33
 * @warning
 */
unsigned int CEIQ::GetDataItems( unsigned long long ullFileSize )
{
	return sizeof( struct TNEW_IQ);
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
C7IQ::C7IQ(STR_RAWDATA *pRawData, STR_FILTER_SETUP *pFilterSetup ) : CData( )
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
void C7IQ::Alloc( unsigned int uiItems )
{

// 	if( uiItems == 0 ) {
// 		// uiItems = m_RawData.uiDataItems;
// 	}
//     else if ( uiItems <= MAX_ITEMS ) {
// 	    m_IQData.pfI = (float *) malloc( sizeof(float) * uiItems );
// 	    m_IQData.pfQ = (float *) malloc( sizeof(float) * uiItems );
// 	    m_IQData.pfPA = (float *) malloc( sizeof(float) * uiItems );
// 	    m_IQData.pfIP = (float *) malloc( sizeof(float) * uiItems );
// 	    m_IQData.pfFFT = (float *) malloc( sizeof(float) * uiItems );
//     }
//     else {
//     }

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
	_SAFE_FREE(m_IQData.pfI)
	_SAFE_FREE(m_IQData.pfQ)
	_SAFE_FREE(m_IQData.pfPA)
	_SAFE_FREE(m_IQData.pfIP)
	_SAFE_FREE(m_IQData.pfFFT)
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
void C7IQ::ConvertPDWData( STR_PDWDATA *pPDWData, STR_FILTER_SETUP *pFilterSetup, bool bSwap, ENUM_CONVERT_OPTION enOption )
{
// 	unsigned int ui;
//
// 	float *psI = m_IQData.pfI;
// 	float *psQ = m_IQData.pfQ;
// 	float *psPA = m_IQData.pfPA;
// 	float *psIP = m_IQData.pfIP;
// 	float *psFFT = m_IQData.pfFFT;
//
// 	float fVal1, fVal2;
//
// 	SRxIQDataRGroup1 *pIQ;
//
//     pIQ = (SRxIQDataRGroup1 *) & m_pRawDataBuffer[m_iHeaderSize];
// // 	if( iOffset <= 0 ) {
// // 		pIQ = (SRxIQDataRGroup1 *) & m_pRawDataBuffer[0];
// // 	}
// // 	else {
// // 		pIQ = (SRxIQDataRGroup1 *) & m_pRawDataBuffer[iOffset];
// // 	}
//
// 	m_IQData.iDataItems = 0;
//
//     for (ui = 0; ui < m_PDWData.uiDataItems ; ++ui ) {
// 		*psI = (float) ( (short) ( pIQ->sIData ^ (0x8A5A) ) );
// 		*psQ = (float) ( (short) ( pIQ->sQData ^ (0x8A5A) ) );
//
// 		// 순시 진폭
// 		*psPA = sqrt( *psI * *psI + *psQ * *psQ );
// 		*psPA = (float) (20.*log10( *psPA ) ) - (float) 80.;
//
// 		// 순시 위상차
// /*
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
// 		}		*/
// 		if( ui == 0 ) {
// 			*psIP = 0.0;
// 			fVal2 = (float) ( atan2( *psQ, *psI ) * RAD2DEG );
// 	}
// 	else {
// 			fVal1 = (float) ( atan2( *psQ, *psI ) * RAD2DEG );
// 			*psIP = fVal1;
// 	}
//
// 		// printf( "\n [%3d] %10d %10d" , i+1, *psI, *psQ );
//
// 		++psI;
// 		++psQ;
// 		++psPA;
// 		++psIP;
//
// 		++ m_IQData.iDataItems;
//
// 		++pIQ;
// 	}
//
//     ExecuteFFT( m_PDWData.uiDataItems, & m_IQData );

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
CMIDAS::CMIDAS(STR_RAWDATA *pRawData) : CData(  )
{
	//Alloc( IQ_ITEMS );
	m_pSubRecords = NULL;

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

void CMIDAS::Init( char *pRawData, STR_FILTER_SETUP *pstFilterSetup )
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
void CMIDAS::Alloc( unsigned int uiItems )
{
    //Log( enNormal, "Alloc()을 [%d]개를 할당합니다." , uiItems );

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
    //Log( enNormal, "Free()를 해지합니다." );

// 	_SAFE_FREE(m_PDWData.pfFreq);
// 	_SAFE_FREE(m_PDWData.pfPW);
// 	_SAFE_FREE(m_PDWData.pfAOA);
// 	_SAFE_FREE(m_PDWData.pfTOA);
// 	_SAFE_FREE(m_PDWData.pfDTOA);
// 	_SAFE_FREE(m_PDWData.pfPA);
// 	_SAFE_FREE(m_PDWData.pullTOA);
//
// 	_SAFE_FREE(m_PDWData.pcType);
// 	_SAFE_FREE(m_PDWData.pcDV);
//
// 	if( m_pSubRecords != NULL ) {
// 		_SAFE_FREE( m_pSubRecords );
// 	}

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

void *CMIDAS::GetRealData()
{
    return NULL;
}

/**
  * @brief		IQ 데이터 구조에 저장한다.
  * @return 	void
  * @date       2019/06/07 10:11
*/
void CMIDAS::ConvertArrayData( STR_PDWDATA *pPDWData, bool bSwap, STR_FILTER_SETUP *pFilterSetup )
{
	/*
// 	unsigned int ui;
//
// 	S_EL_PDW_RECORDS strPDWRecords;
//
// 	float fPreToa;
//
//     Alloc( m_PDWData.uiDataItems );
//
// 	float *pfFreq = m_PDWData.pfFreq;
// 	float *pfPW = m_PDWData.pfPW;
// 	float *pfAOA = m_PDWData.pfAOA;
// 	float *pfTOA = m_PDWData.pfTOA;
// 	float *pfDTOA = m_PDWData.pfDTOA;
// 	float *pfPA = m_PDWData.pfPA;
//
// 	_TOA *pullTOA = m_PDWData.pullTOA;
//
// 	char *pcType = m_PDWData.pcType;
// 	char *pcDV = m_PDWData.pcDV;
//
// 	m_pDataChar = (char *) & m_pRawDataBuffer[0];
//
// 	m_PDWData.uiDataItems = 0;
//
//     //Log( enNormal, "ConvertArray()를 [%d]개를 변환합니다." , m_RawData.uiDataItems );
//
//     for( ui=0 ; ui < m_PDWData.uiDataItems ; ++ui ) {
// 		GetSubRecords( & strPDWRecords );
//
// 		*pfTOA = (float) strPDWRecords.ltoa / 1000.;
//         *pfTOA = (float) ( strPDWRecords.dtoa / 1000000000. );
//
//         if( ui == 0 ) {
//             *pfDTOA = 0.0;
//         }
//         else {
//             *pfDTOA = *pfTOA - fPreToa;
//         }
//         fPreToa = *pfTOA;
//
// 		*pfAOA = (float) strPDWRecords.ddoa;
// 		*pfPA = (float) strPDWRecords.dpa;
// 		*pfPW = (float) strPDWRecords.lpw * 1000000000.;
//         *pfPW = (float) strPDWRecords.dpw;
// 		*pfFreq = (float) ( strPDWRecords.dfreq / 1000000. );
//         *pfFreq = (float) strPDWRecords.lfreq;
//
//         *pcDV = 0;
//
//         *pcType = 0;
//
//         *pullTOA = 0;
//
// 		*pfFreq = GetFreq();
//
// 		// 필터링 조건
// //         if( pFilterSetup == NULL || ( pFilterSetup->enSubGraph == enUnselectedSubGraph || \
// //             ( ( ( pFilterSetup->dToaMin == 0 ) || ( pFilterSetup->dToaMin <= *pfTOA && *pfTOA <= pFilterSetup->dToaMax ) ) && \
// //             ( ( pFilterSetup->dAoaMin == 0 ) || ( pFilterSetup->dAoaMin <= *pfAOA && *pfAOA <= pFilterSetup->dAoaMax ) ) && \
// //             ( ( pFilterSetup->dFrqMin == 0 ) || ( pFilterSetup->dFrqMin <= *pfFreq && *pfFreq <= pFilterSetup->dFrqMax ) ) && \
// //             ( ( pFilterSetup->dPAMin == 0 ) || ( pFilterSetup->dPAMin <= *pfPA && *pfPA <= pFilterSetup->dPAMax ) ) ) ) ) {
// // 				++pfFreq;
// // 				++pfAOA;
// // 				++pfPW;
// // 				++pfPA;
// // 				++pfTOA;
// // 				++pfDTOA;
// // 				++pcType;
// // 				++pcDV;
// // 				++pullTOA;
// //
// // 				++ m_PDWData.uiDataItems;
// //
// // 				//++ m_stFilterSetup.uiDataItems;
// // 		}
// 		}


*/

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
// void CMIDAS::GetSubRecords( S_EL_PDW_RECORDS *pPDWRecords )
// {
// 	unsigned int i;
// 	SELSUBRECORDS *pSubRecords;
//
//     memset( pPDWRecords, 0, sizeof( struct S_EL_PDW_RECORDS) );
//
// 	pSubRecords = m_pSubRecords;
// 	for( i=0 ; i < m_ADJ._6000.subrecords ; ++i ) {
//         if( strncmp( pSubRecords->name, stSubrecordName[enTOAOfSub], strnlen_s(stSubrecordName[enTOAOfSub], 4 ) ) == 0 ) {
// 			pPDWRecords->dtoa = GetSubValue( pSubRecords->format );
// 		}
//         else if( strncmp( pSubRecords->name, stSubrecordName[enDTOAOfSub], strnlen_s(stSubrecordName[enDTOAOfSub], 4 ) ) == 0 ) {
// 			pPDWRecords->ddtoa = GetSubValue( pSubRecords->format );
// 		}
//         else if( strncmp( pSubRecords->name, stSubrecordName[enFreqOfSub], strnlen_s(stSubrecordName[enFreqOfSub], 4 ) ) == 0 ) {
// 			pPDWRecords->dfreq = GetSubValue( pSubRecords->format );
// 		}
//         else if( strncmp( pSubRecords->name, stSubrecordName[enPWOfSub], strnlen_s(stSubrecordName[enPWOfSub], 4 ) ) == 0 ) {
// 			pPDWRecords->dpw = GetSubValue( pSubRecords->format );
// 		}
//         else if( strncmp( pSubRecords->name, stSubrecordName[enPAOfSub], strnlen_s(stSubrecordName[enPAOfSub], 4 ) ) == 0 ) {
// 			pPDWRecords->dpa = GetSubValue( pSubRecords->format );
// 		}
//         else if( strncmp( pSubRecords->name, stSubrecordName[enDOAOfSub], strnlen_s(stSubrecordName[enDOAOfSub], 4 ) ) == 0 ) {
// 			pPDWRecords->ddoa = GetSubValue( pSubRecords->format );
// 		}
// 		else {
//             printf( "서브 레코드(%s)에 맞는 것이 없습니다 !!" , pSubRecords->name );
// 			++ pSubRecords;
// 		}
//
// 		++ pSubRecords;
// 	}
//
// }

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
			++ m_pDataChar;
			break;
		case DATA_FORMAT_TYPE_DESIGNATOR_16BIT_INTEGER :
			memcpy( & sh, m_pDataChar, sizeof(short) );
			++ m_pDataChar;
            ++ m_pDataChar;
			break;
		case DATA_FORMAT_TYPE_DESIGNATOR_32BIT_INTEGER :
			memcpy( & in, m_pDataChar, sizeof(int) );
			++ m_pDataChar;
            ++ m_pDataChar;
            ++ m_pDataChar;
            ++ m_pDataChar;
			break;

		case DATA_FORMAT_TYPE_DESIGNATOR_32BIT_FLOAT :
			memcpy( & fl, m_pDataChar, sizeof(float) );
			++ m_pDataChar;
            ++ m_pDataChar;
            ++ m_pDataChar;
            ++ m_pDataChar;
			break;

		case DATA_FORMAT_TYPE_DESIGNATOR_64BIT_INTEGER :
			memcpy( & li, m_pDataChar, sizeof(long int) );
            dvalue = (long int) li;
            ++ m_pDataChar;
            ++ m_pDataChar;
            ++ m_pDataChar;
            ++ m_pDataChar;
            ++ m_pDataChar;
            ++ m_pDataChar;
            ++ m_pDataChar;
            ++ m_pDataChar;
			//m_pDataChar += sizeof(long int);
			break;

		case DATA_FORMAT_TYPE_DESIGNATOR_64BIT_FLOAT :
			memcpy( & du, m_pDataChar, sizeof(double) );
			dvalue = (double) du;
            ++ m_pDataChar;
            ++ m_pDataChar;
            ++ m_pDataChar;
            ++ m_pDataChar;
            ++ m_pDataChar;
            ++ m_pDataChar;
            ++ m_pDataChar;
            ++ m_pDataChar;
			//m_pDataChar += sizeof( double );
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
int CMIDAS::GetHeaderSize()
{

    if( m_iHeaderSize == -1 ) {
	    memcpy( & m_HCB, m_pRawHeaderBuffer, sizeof( struct SELMIDAS_HCB) );

	    if( m_HCB.iType == MIDAS_FILE_TYPE_1001 ) {
		    memcpy( & m_ADJ._1000, & m_pRawHeaderBuffer[0x100], sizeof( struct SELMIDAS_ADJUNCT_TYPE_1000) );
	    }
	    else if( m_HCB.iType == MIDAS_FILE_TYPE_6003 ) {
		    memcpy( & m_ADJ._6000, & m_pRawHeaderBuffer[0x100], sizeof( struct SELMIDAS_ADJUNCT_TYPE_6000) );

            UINT uiSize = min( m_ADJ._6000.subrecords * sizeof( struct SELSUBRECORDS), MAX_ITEMS );
		    m_pSubRecords = ( SELSUBRECORDS * ) malloc( uiSize );
            if( m_pSubRecords != NULL ) {
		        memcpy( m_pSubRecords, & m_pRawHeaderBuffer[0x100+sizeof( struct SELMIDAS_ADJUNCT_TYPE_6000)], uiSize );
            }
            else {
            }
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
    if( m_uiOneDataSize == UINT_MAX ) {
        if( m_HCB.iType == MIDAS_FILE_TYPE_1001 ) {

        }
        else if( m_HCB.iType == MIDAS_FILE_TYPE_6003 ) {
            m_uiOneDataSize = m_ADJ._6000.record_length;
        }
        else {

        }
    }

    return m_uiOneDataSize;
}

/**
 * @brief		GetDataSize
 * @return		unsigned int
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2020/12/24 15:02:30
 * @warning
 */
unsigned int CMIDAS::GetDataItems( unsigned long long ullFileSize )
{
    unsigned int i;

    int iBit = 0;

	SELSUBRECORDS *pSubRecords;

	if( m_HCB.iType == MIDAS_FILE_TYPE_1001 ) {
		m_enFileType = E_EL_SCDT_IQ;

		iBit = 16;
	}
	else if( m_HCB.iType == MIDAS_FILE_TYPE_6003 ) {
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
CData::CData()
{

    m_iHeaderSize = -1;
    m_uiOneDataSize = UINT_MAX;

    m_pRawDataBuffer = NULL;
    m_pRawHeaderBuffer = NULL;

#ifdef _GRAPH_
	m_uiWindowNumber = 0;
#endif

    m_uiTotalDataItems = 0;

    //
    memset( & m_PDWData.x, 0, sizeof(union UNION_HEADER) );
    m_PDWData.pstPDW = NULL;

    //
    //memset( &m_PDWRealData, 0, sizeof(struct STR_PDWREALDATA) );
	// 멍청한 정적 툴 -> STR_PDWREALDATA 구조체에 초기값 설정
	// memset(&m_PDWRealData, 0, sizeof(m_PDWRealData));

	ClearFilterSetup();

}

/**
 * @brief     Init
 * @param     char * pRawData
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-04, 14:37
 * @warning
 */
void CData::Init( char *pRawData, STR_FILTER_SETUP *pstFilterSetup )
{

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

	m_strFilterSetup.ullToaMin = 0;
	m_strFilterSetup.ullToaMax = UINT64_MAX;
	m_strFilterSetup.ullDtoaMin = 0;
	m_strFilterSetup.ullDtoaMax = UINT64_MAX;
	m_strFilterSetup.uiAoaMin = 0;
	m_strFilterSetup.uiAoaMax = UINT32_MAX;
	m_strFilterSetup.uiFrqMin = 0;
	m_strFilterSetup.uiFrqMax = UINT32_MAX;
	m_strFilterSetup.uiPAMin = 0;
	m_strFilterSetup.uiPAMax = UINT32_MAX;
	m_strFilterSetup.uiPWMin = 0;
	m_strFilterSetup.uiPWMax = UINT32_MAX;

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
    FreeData();
    FreeRealData();

}

/**
 * @brief		Alloc
 * @param		unsigned int uiItems
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2022/02/14 18:17:33
 * @warning
 */
void CData::Alloc( unsigned int uiItems )
{

}


/**
 * @brief
 * @param     unsigned int uiItems
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022/02/22 0:08:50
 * @warning
 */
void CData::AllocData( int iItems )
{
    size_t szPDW;

    FreeData();

    szPDW = CCommonUtils::CheckMultiplyOverflow( (int) sizeof( struct _PDW ), iItems );

    //_SAFE_MALLOC( m_PDWData.pstPDW, _PDW, szPDW )
	// 위에서 FreeData()를 호출하기 때문에 아래에서 그냥 malloc()을 수행함.
	_FORCED_MALLOC( m_PDWData.pstPDW, _PDW, szPDW )

}

/**
 * @brief
 * @param     unsigned int uiItems
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022/02/22 0:57:14
 * @warning
 */
void CData::AllocRealData( int iItems )
{
    size_t szSize, szdSize;

    FreeRealData();

    szSize = CCommonUtils::CheckMultiplyOverflow( (int) sizeof(float), iItems );
    szdSize = CCommonUtils::CheckMultiplyOverflow( (int) sizeof(double), iItems );

    _FORCED_MALLOC( m_PDWRealData.pfAOA, float, szSize )
	_FORCED_MALLOC( m_PDWRealData.pfFreq, float, szSize )
	_FORCED_MALLOC( m_PDWRealData.pfPW, float, szSize )
	_FORCED_MALLOC( m_PDWRealData.pfPA, float, szSize )
	_FORCED_MALLOC( m_PDWRealData.pfDTOA, float, szSize )

	_FORCED_MALLOC(m_PDWRealData.pdTOA, double, szdSize)

    _FORCED_MALLOC( m_PDWRealData.puiIndex, unsigned int, szSize )

    szSize = CCommonUtils::CheckMultiplyOverflow( (int) sizeof(_TOA), iItems );
	_FORCED_MALLOC( m_PDWRealData.pullTOA, _TOA, szSize )

    szSize = CCommonUtils::CheckMultiplyOverflow( (int) sizeof(char), iItems );
	_FORCED_MALLOC( m_PDWRealData.pcType, char, szSize )
	_FORCED_MALLOC( m_PDWRealData.pcDV, char, szSize )



}

/**
 * @brief
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022/02/22 1:00:51
 * @warning
 */
void CData::FreeRealData()
{
    _SAFE_FREE( m_PDWRealData.pfAOA )
    _SAFE_FREE( m_PDWRealData.pfFreq )
    _SAFE_FREE( m_PDWRealData.pfPW )
    _SAFE_FREE( m_PDWRealData.pfPA )
    _SAFE_FREE( m_PDWRealData.pdTOA )
    _SAFE_FREE( m_PDWRealData.pfDTOA )

    _SAFE_FREE( m_PDWRealData.puiIndex )

    _SAFE_FREE( m_PDWRealData.pullTOA )

    _SAFE_FREE( m_PDWRealData.pcType )
    _SAFE_FREE( m_PDWRealData.pcDV )

}

/**
 * @brief
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022/02/22 0:14:37
 * @warning
 */
void CData::FreeData()
{
    _SAFE_FREE( m_PDWData.pstPDW )

}

/**
 * @brief
 * @return    void
 * @author    鈺곌퀣荑??(churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022/01/28 23:42:19
 * @warning
 */
void CData::Free()
{
// 	_SAFE_FREE( m_PDWData.pfFreq );
// 	_SAFE_FREE( m_PDWData.pfPW );
// 	_SAFE_FREE( m_PDWData.pfAOA );
// 	_SAFE_FREE( m_PDWData.pfTOA );
// 	_SAFE_FREE( m_PDWData.pfDTOA );
// 	_SAFE_FREE( m_PDWData.pfPA );
// 	_SAFE_FREE( m_PDWData.pullTOA );
// 	_SAFE_FREE( m_PDWData.pcType );
// 	_SAFE_FREE( m_PDWData.pcDV );
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
 * @brief     swapByteOrder
 * @param     unsigned long long & ull
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-01-08 13:14:37
 * @warning
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
 * @brief     swapByteOrder
 * @param     unsigned int & ui
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-01-08 13:14:47
 * @warning
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
#ifdef _FFTW_
	int i;

	float *psI, *psQ;
	float *psFFT = pIQData->pfFFT;

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

		//fftw_destroy_plan( plan );
		//fftw__SAFE_FREE( pIn );
		//fftw__SAFE_FREE( pOut );
	}
#endif

}

/**
 * @brief     UpdateMacroSysVar
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-21, 12:07
 * @warning
 */
void CData::UpdateMacroSysVar()
{

#if defined(_ELINT_) || defined(_XBAND_)
//     _spAMPres = m_spAMPres;
//     _spAOAres = (float) 0.01;
//     _spOneMicrosec = m_spOneMicrosec;

#else
    //_spAMPres = m_spAMPres;
    //_spAOAres = (float) 0.01;
    //_spOneMicrosec = m_spOneMicrosec;
#endif



}

/**
 * @brief     ConvertArray
 * @param     STR_PDWDATA * pPDWData
 * @param     bool bSwap
 * @param     STR_FILTER_SETUP * pFilterSetup
 * @param     bool bConvert
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-02-14, 11:54
 * @warning
 */
void CData::ConvertPDWData( STR_FILTER_SETUP *pFilterSetup, bool bSwap, ENUM_CONVERT_OPTION enOption )
{

	// 필터 적용한 정보 저장
	if (pFilterSetup != NULL) {
		memcpy(&m_strFilterSetup, pFilterSetup, sizeof( struct STR_FILTER_SETUP));
	}

    unsigned int uiTotalPDW;

	//
    switch( enOption ) {
    case enUnitToPDW :
        MakeHeaderData( & m_PDWData );

        AllocData( (int) m_PDWData.GetTotalPDW() );
        MakePDWDataByUnitToPDW( & m_PDWData );
        break;

    case enPDWToPDW :
        MakeHeaderData( & m_PDWData  );

        uiTotalPDW = m_PDWData.GetTotalPDW();
        AllocData( (int) uiTotalPDW );
        if( m_PDWData.pstPDW != NULL ) {
            memcpy( & m_PDWData.pstPDW[0], & m_pRawDataBuffer[0], sizeof( struct _PDW) * uiTotalPDW);
        }
        break;

    case enPDWToReal :
        MakeHeaderData( & m_PDWData  );

        AllocRealData((int) m_PDWData.GetTotalPDW() );
        MakePDWDataToReal( & m_PDWRealData );
        break;

	case enCSVToPDW :
		MakeHeaderData(&m_PDWData);

		AllocData( (int) m_PDWData.GetTotalPDW());

		MakeCSVDataToPDW();

		break;

    case enUnitToReal :
        break;

    default :
        break;
    }

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

	Alloc();

	++stDataFile;

#if 1
    CheckOverflow<long long int>( 0 );
    CheckOverflow<size_t>( 0 );
    WhereIs;

#endif

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

    _SAFE_DELETE( m_pData )

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

       		if( ! m_RawDataFile.RawOpenFile( pstPathname, O_CREAT | O_RDWR ) ) {
                //LOGMSG1( enWarning, _T("PDW 데이터 파일[%s]을 생성하지 못합니다 !") , strPathname );
            }
            else {
                m_RawDataFile.Write( pData, (unsigned int) iNumData );
                m_RawDataFile.CloseFile();
            }
        }
        else if( enDataType == en_IQ_DATA ) {
            if( ! m_RawDataFile.RawOpenFile( pstPathname, O_CREAT | O_RDWR ) ) {
                //Log( enError, _T("IQ 데이터 파일[%s]을 생성하지 못합니다 !") , pstPathname );
            }
            else {
                // IQ 헤더 정보 저장
                if( pDataEtc != NULL ) {
                    m_RawDataFile.Write( pDataEtc, (unsigned int) iSizeOfEtc );
                }

                m_RawDataFile.Write( pData, (unsigned int) iNumData );
                m_RawDataFile.CloseFile();
            }
        }
		else {
		}
    }

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
int CDataFile::GetHeaderSize( CData *pData )
{
	return pData->GetHeaderSize();
}

/**
 * @brief
 * @param     CData * pData
 * @return    unsigned int
 * @author    議곗쿋??(churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022/01/26 22:34:12
 * @warning
 */
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
void CDataFile::ReadDataHeader()
{
    // 파일 처음으로 이동
	m_RawDataFile.SeekToStart();

    // 1.1 헤더 크기 계산
	m_pData->m_iHeaderSize = GetHeaderSize( m_pData );

	if( m_pData->m_iHeaderSize != 0 ) {
	    // 데이터 파일 중에서 제일 큰 것을 읽는다.
	    m_RawDataFile.Read( m_pData->m_pRawHeaderBuffer, MAX_HEADER_SIZE );

            // 다시 처음으로 이동
	    m_RawDataFile.SeekToStart();

		unsigned long long int ullFileSize = m_RawDataFile.GetRawFileSize();
        m_pData->m_ullFileSize = ullFileSize;

    }
    else {
#ifdef _MSC_VER
        m_pData->m_pRawHeaderBuffer[0] = NULL;
#else
        m_pData->m_pRawHeaderBuffer[0] = (char) '\0';
#endif
    }

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
	unsigned int uiTotalDataItems;
    size_t szData;

	m_RawDataFile.SeekToStart();

	uiTotalDataItems = pData->m_uiTotalDataItems;
    if( pData->m_pRawDataBuffer == NULL && uiTotalDataItems != 0 ) {
        szData = CCommonUtils::CheckMultiplyOverflow( (int) pData->GetOneDataSize(), (int) uiTotalDataItems);

        pData->m_pRawDataBuffer = (char *) malloc( szData );

    }

	// 데이터 파일 중에서 제일 큰 것을 읽는다.
	//pData->m_RawData.uiByte = m_RawDataFile.Read( pData->m_pRawDataBuffer, pData->GetOneDataSize() * pData->m_uiTotalDataItems, pData->GetHeaderSize()+pData->GetOffsetSize() );
	int iHeaderSize;
	unsigned int uiDataSize;

	iHeaderSize = pData->GetHeaderSize();
	uiDataSize = pData->GetOneDataSize() * uiTotalDataItems;
    m_RawDataFile.Read( pData->m_pRawDataBuffer, uiDataSize, iHeaderSize );

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
	unsigned int uiTotalDataItems;
	unsigned long long ullFileSize=m_RawDataFile.GetRawFileSize();

	uiTotalDataItems = pData->GetDataItems( ullFileSize );
	pData->m_uiTotalDataItems = uiTotalDataItems;

	return uiTotalDataItems;

}

#ifdef _READDATAFILE_
/**
 * @brief
 * @param     STR_PDWDATA * pPDWData
 * @param     char * pPathname
 * @param     STR_FILTER_SETUP * pstFilterSetup
 * @param     ENUM_CONVERT_OPTION enOption
 * @return    CData *
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022/02/20 15:55:40
 * @warning
 */
CData *CDataFile::ReadDataFile( char *pPathname, STR_FILTER_SETUP *pstFilterSetup, ENUM_CONVERT_OPTION enOption )
{
    char *pTempData = NULL;
    size_t szFileSize;
    unsigned long long int ullFileSize;

    if( pPathname != NULL ) {
        ullFileSize = FileSize( pPathname );
        szFileSize = CheckOverflow<size_t>( ullFileSize );

        if( ullFileSize != 0 ) {
            pTempData = new char[szFileSize];
            memset( pTempData, 0, szFileSize );

            if( m_RawDataFile.RawOpenFile( pPathname, O_RDONLY | O_BINARY ) == true ) {
                m_RawDataFile.Read( pTempData, szFileSize );
                ReadDataMemory( pTempData, pPathname, pstFilterSetup, enOption, szFileSize );

            }

            m_RawDataFile.CloseFile();
            delete[] pTempData;
        }
    }
    else {
        ReadDataMemory( NULL, pPathname, pstFilterSetup, enOption );

    }

    return m_pData;

}

#endif

/**
  * @brief		RAW 데이터 파일 읽기
  * @param		CString & strPathname
  * @return 	void
  * @return		성공시 true, 실패시 false
  * @date       2019/05/31 10:34
*/
void CDataFile::ReadDataMemory( char *pstData, char *pstPathname, STR_FILTER_SETUP *pstFilterSetup, ENUM_CONVERT_OPTION enOption, size_t szFileSize )
{
    if( pstData != NULL && pstPathname != NULL ) {
        ENUM_DataType enDataType = CCommonUtils::WhatDataType( pstPathname );
        ENUM_UnitType enUnitType = CCommonUtils::WhatUnitType( pstPathname );

        // 장치 정보 업데이트
        g_enUnitType = enUnitType;

		// 소형 전자전의 PDW 인 경우
        if( enDataType == en_PDW_DATA && enUnitType == en_SONATA ) {
#if defined(_GRAPH_) || defined(_SONATA_)
			if (m_pData == NULL) {
				m_pData = new CSPDW(pstData, pstFilterSetup, szFileSize );
			}
			else {
				m_pData->Init(pstData);
			}
#endif
        }

//         else if( enDataType == en_PDW_DATA && enUnitType == en_SONATA_SHU ) {
//
//         }

		// 701 장치 이며 CSV 또는 RAW 데이터 파일인 경우,
#if defined(_GRAPH_) || defined(_701_)
        else if( enDataType == en_PDW_DATA && enUnitType == en_701 ) {

			if (m_pData != NULL) {
				delete m_pData;
			}
			m_pData = new C7PDW(pstData, pstFilterSetup, enDataType);

			m_pData->Init(pstData, pstFilterSetup );
        }
		else if ( enDataType == en_PDW_DATA_CSV && enUnitType == en_701) {
			if (m_pData != NULL) {
				delete m_pData;
			}
			m_pData = new C7PDW(pstData, pstFilterSetup, enDataType);

			m_pData->Init(pstData, pstFilterSetup);
        }
#endif

//
//         else if( enDataType == en_PDW_DATA && enUnitType == en_KFX ) {
//
//         }
//
//         else if( enDataType == en_PDW_DATA && enUnitType == en_ELINT ) {
//
//         }

        // 소형 전자전의 PDW 인 경우
#if defined(_GRAPH_) || defined(_POCKETSONATA_) || defined(_712_)
        else if( enDataType == en_PDW_DATA && enUnitType == en_ZPOCKETSONATA ) {

            if( m_pData == NULL ) {
                m_pData = new CPOCKETSONATAPDW( pstData, pstFilterSetup, -1 );
            }
            else {
                m_pData->Init( pstData );
            }
        }
#endif

        // X대역 방탐기의 PDW 인 경우
#if defined(_GRAPH_) || defined(_XBAND_)
        else if( enDataType == en_PDW_DATA && enUnitType == en_XBAND ) {
            if( m_pData == NULL ) {
                m_pData = new CXPDW( pstData, pstFilterSetup );
            }
            else {
                m_pData->Init( pstData, pstFilterSetup );
            }
        }
#endif

        //////////////////////////////////////////////////////////////////////////
//         else if( enDataType == en_IQ_DATA && enUnitType == en_SONATA ) {
//
//         }
        else {
            // printf( "\n Error !!" );

        }

        if( enUnitType != en_UnknownUnit && m_pData != NULL ) {
            m_pData->ConvertPDWData( pstFilterSetup, false, enOption );
        }
    }
    else {
		if (m_pData != NULL) {
			m_pData->ConvertPDWData(NULL, false, enOption);
		}
    }

}

/**
 * @brief     ConvertArray
 * @param     CData * pData
 * @param     bool bSwap
 * @param     STR_FILTER_SETUP * pFilterSetup
 * @param     bool bConvert
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-02-14, 12:30
 * @warning
 */
void CDataFile::ConvertArray( STR_PDWDATA *pPDWData, bool bSwap, STR_FILTER_SETUP *pFilterSetup, bool bConvert )
{
    //m_pData->ConvertPDWData( pPDWData, bSwap, pFilterSetup, bConvert );

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
	void *pData;

	pData = NULL;
	if( m_pData != NULL ) {
		pData = m_pData->GetData();
	}

	return pData;
}

/**
 * @brief     GetRealData
 * @return    void *
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-02-22, 16:26
 * @warning
 */
void *CDataFile::GetRealData()
{
	void *pData;

	pData = NULL;
	if (m_pData != NULL) {
		pData = m_pData->GetRealData();
	}

	return pData;
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
	void *pData;

	pData = NULL;
	if (m_pData != NULL) {
		pData = m_pData->GetHeader();
	}

	return pData;
}

/**
 * @brief     GetBandWidth
 * @return    int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-02-02 20:10:07
 * @warning
 */
int CDataFile::GetBandWidth()
{
	int iRet = 0;

	if (m_pData != NULL) {
		iRet = m_pData->GetBandWidth();
	}

    return iRet;
}

/**
 * @brief     SetData
 * @param     CData * pData
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-02-09, 17:51
 * @warning
 */
void CDataFile::SetData( CData *pData )
{
	m_pData = pData;

#ifdef _GRAPH_
    IncWindowNumber();
#endif

}


