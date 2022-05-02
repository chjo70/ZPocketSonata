#include "stdafx.h"


#define _MAIN_GLOBALS_

#include "CGenPDW.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "../../files/Utils/ccommonutils.h"


/**
 * @brief     CGenPDW
 * @param     char * pszFileName
 * @return    
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-27, 20:39
 * @warning
 */
CGenPDW::CGenPDW( char *pszFileName )
{
    //  mak_file을 read mode로 open 한 후 에러인 경우 에러 처리 
    strcpy( m_szMakfilename, pszFileName );

    m_File = NULL;
    if( (m_File = fopen( m_szMakfilename, "rt" )) == NULL ) {
        printf( "\n %s File Open ERROR : %s", m_szMakfilename, strerror( errno ) );
    }


}


/**
 * @brief     ~CGenPDW
 * @param     void
 * @return    
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-27, 20:40
 * @warning
 */
CGenPDW::~CGenPDW( void )
{
    if( m_File != NULL ) {
        fclose( m_File );
    }

}


/**
 * @brief     ParsingThePDWMakefile
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-27, 20:46
 * @warning
 */
void CGenPDW::ParsingThePDWMakefile()
{

    SkipTheHeader();

    //////////////////////////////////////////////////////////
    while( ! feof( m_File ) ) {
		GetLineCommand();

        // 장치명 얻기
        g_enUnitType = CCommonUtils::WhatUnitType( m_stGenPDWInfo.szFileName );

        // 메모리 할당
        m_stSavePDWData.pstPDW = (_PDW *) malloc( m_stGenPDWInfo.uiCoAllPDW * sizeof(_PDW) );
        m_pstPDW = m_stSavePDWData.pstPDW;

        FileOpen( m_stGenPDWInfo.szFileName, O_CREAT | O_BINARY | O_WRONLY ); //  | O_TRUNC );

        MakeFileHeader();
        Write( &m_stSavePDWData.x, sizeof( UNION_HEADER ) );

        SetGenerateInfo();

        // PDW 발생해서 파일로 저장
        GeneratePDW();
        Write( m_stSavePDWData.pstPDW, sizeof( _PDW ) * m_stSavePDWData.GetTotalPDW() );

        FileClose();       

        free( m_stSavePDWData.pstPDW );

    }

}

/**
 * @brief     SetGenerateInfo
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-28, 15:11
 * @warning
 */
void CGenPDW::SetGenerateInfo()
{
    int iBandWidth = m_stSavePDWData.GetBandWidth();

    // 
    m_tTOA = CEncode::EncodeTOAus( m_stGenPDWInfo.uiFirstTOA, iBandWidth );
    
    m_uiPRIStaggerLvl = 0;
    m_iPriWidth = (int) ( ( (float ) m_stGenPDWInfo.iPRIMean * m_stGenPDWInfo.fJitterp ) / 100. + 0.5 );

    m_ui1DOA = CEncode::EncodeDOA( 1.0 );

    m_iPWError = CEncode::EncodePWns( (float) m_stGenPDWInfo.uiPWError, iBandWidth );

    if( g_enUnitType == en_XBAND ) {
        m_i360DOA = 36000;

    }
    else if( g_enUnitType == en_ZPOCKETSONATA ) {
        m_i360DOA = 4 * 1024;

    }
    else {
        m_i360DOA = 0;
    }

    m_uiPRIDwellCount = 0;

}

/**
 * @brief     MakeFileHeader
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-28, 13:58
 * @warning
 */
void CGenPDW::MakeFileHeader()
{
    switch( g_enUnitType ) {
    case en_ZPOCKETSONATA:
        m_stSavePDWData.x.ps.uiBoardID = 0;
        m_stSavePDWData.x.ps.uiBank = 0;
        m_stSavePDWData.x.ps.uiBand = 0;
        m_stSavePDWData.x.ps.iIsStorePDW = 1;
        break;

    case en_ELINT:
        m_stSavePDWData.x.ps.uiBoardID = 0;
        m_stSavePDWData.x.ps.uiBank = 0;
        m_stSavePDWData.x.ps.uiBand = 0;
        m_stSavePDWData.x.ps.iIsStorePDW = 1;

    case en_XBAND:
        strcpy( m_stSavePDWData.x.xb.aucTaskID, "SIMPDW" );
        
        m_stSavePDWData.x.xb.iIsStorePDW = 1;
        m_stSavePDWData.x.xb.enCollectorID = RADARCOL_Unknown;
        m_stSavePDWData.x.xb.enBandWidth = XBAND::en120MHZ_BW;
        break;

    case en_SONATA:
        break;

    default:
        memset( & m_stSavePDWData.x, 0, sizeof( UNION_HEADER ) );
        break;

    }

    struct timespec tiNow;

    tiNow.tv_sec = time( NULL );
    //CCommonUtils::GetCollectTime( &tiNow );
    //CCommonUtils::GetCollectTime( pTimeSpec );
    //CCommonUtils::CheckMultiplyOverflow( 10, 10 );


    m_stSavePDWData.SetColTime( tiNow.tv_sec, 0 );
    m_stSavePDWData.SetTotalPDW( m_stGenPDWInfo.uiCoAllPDW );
    m_stSavePDWData.SetPDWID( 0 );
}

/**
 * @brief     GeneratePDW
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-28, 13:14
 * @warning
 */
void CGenPDW::GeneratePDW()
{
    UINT i, j;

    for( i = 0 ; i < m_stGenPDWInfo.uiCoAllPDW ; ) {

        m_stGenPDWInfo.uiCoScanPrd = max( 1, m_stGenPDWInfo.uiCoScanPrd );

        for( j = 0 ; j < m_stGenPDWInfo.uiCoScanPrd ; ++j, ++i ) {
            MakeSignalType();
            MakeDOAOfPDW();
            MakeFreqOfPDW();
            MakePRIOfPDW( i == 0 );
            MakePWOfPDW();
            MakePAOfPDW();

            ++m_pstPDW;
        }
        
    }
    // m_theMidasBlue.SaveRawDataFile( m_stGenPDWInfo.szFileName, E_EL_SCDT_PDW, m_stSavePDWData.pstPDW, & m_stSavePDWData.x, 10 );
}

/**
 * @brief     MakeSignalType
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-28, 16:30
 * @warning
 */
void CGenPDW::MakeSignalType()
{
    m_pstPDW->iPulseType = 0;
}

/**
 * @brief     MakePRIOfDOA
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-28, 16:48
 * @warning
 */
void CGenPDW::MakeDOAOfPDW()
{
    int iDOA;
    float fDOA;
    unsigned uiDOAError;

    fDOA = (float) m_stGenPDWInfo.uiAOA;

    iDOA = CEncode::EncodeDOA( fDOA );

    uiDOAError = m_ui1DOA * m_stGenPDWInfo.uiDOAError;
    iDOA += Rand( (int) uiDOAError );
    iDOA = ( iDOA + m_i360DOA ) % m_i360DOA;

    m_pstPDW->uiAOA = (unsigned int) iDOA;
}

/**
 * @brief     MakePRIOfPW
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-28, 17:16
 * @warning
 */
void CGenPDW::MakePWOfPDW()
{
    unsigned int uiPW, uiPW2;
    float fPW;

    fPW = (float) m_stGenPDWInfo.uiPW;
    
    int iBandWidth = m_stSavePDWData.GetBandWidth();
    uiPW = CEncode::EncodePWns( fPW, iBandWidth );

    uiPW2 = uiPW;

    uiPW += Rand( ( int ) m_stGenPDWInfo.uiPWError );
    if( ( int ) uiPW < 0 ) {
        uiPW = uiPW2;
    }

    m_pstPDW->uiPW = ( unsigned int ) uiPW;
}

/**
 * @brief     MakePRIOfPA
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-02, 18:20
 * @warning
 */
void CGenPDW::MakePAOfPDW()
{
    unsigned int uiPA;
    float fPA;

    fPA = ( float ) m_stGenPDWInfo.fPA;

    uiPA = CEncode::EncodePA( fPA );

    uiPA += Rand( ( int ) m_stGenPDWInfo.uiPAError );

    m_pstPDW->uiPA = ( unsigned int ) uiPA;
}

/**
 * @brief     MakePRIOfPDW
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-28, 14:57
 * @warning
 */
void CGenPDW::MakePRIOfPDW( bool bSkippedPDW )
{
    _TOA tDTOA=0;
    float fTOA;

    int iBandWidth;

    if( bSkippedPDW == false ) {
        if( strcmp( m_stGenPDWInfo.szPRIType, "STB" ) == 0 ) {
            fTOA = ( float ) m_stGenPDWInfo.iPRIMean;

        }
        else if( strcmp( m_stGenPDWInfo.szPRIType, "STG" ) == 0 ) {
            fTOA = ( float ) m_stGenPDWInfo.fPRISwtVal[m_uiPRIStaggerLvl];
            m_uiPRIStaggerLvl = (++m_uiPRIStaggerLvl) % m_stGenPDWInfo.uiPRIHopLvl;
        }
        else if( strcmp( m_stGenPDWInfo.szPRIType, "JIT" ) == 0 ) {
            fTOA = ( float ) Rand( m_iPriWidth );
            fTOA += ( float ) m_stGenPDWInfo.iPRIMean;
        }
        else if( strcmp( m_stGenPDWInfo.szPRIType, "DNS" ) == 0 ) {
            fTOA = ( float ) m_stGenPDWInfo.fPRISwtVal[m_uiPRIStaggerLvl];

            ++m_uiPRIDwellCount;

            if( m_uiPRIDwellCount % m_stGenPDWInfo.uiCoPRIPatPDW == 0 ) {
                m_uiPRIStaggerLvl = (++m_uiPRIStaggerLvl) % m_stGenPDWInfo.uiPRIHopLvl;
            }
        }
        else if( strcmp( m_stGenPDWInfo.szPRIType, "PAT" ) == 0 ) {
            if( strcmp( m_stGenPDWInfo.szPRIPatType, "SIN" ) == 0 ) {
                fTOA = ( float ) m_stGenPDWInfo.iPRIMean;
                fTOA = ( UINT ) (PRI_width / 2 * sin( ( 2. * M_PI * fTOA ) / (float) m_stGenPDWInfo.uiPRIPatPrd ) + PRI);
            }

        }
        else {
            fTOA = 0.0;
        }

        fTOA += ( float ) Rand( m_stGenPDWInfo.uiTOAError * 1000 ) / 1000.;        

        iBandWidth = m_stSavePDWData.GetBandWidth();
        tDTOA = CEncode::EncodeTOAus( fTOA, iBandWidth );

        // TRACE( "\n fTOA[%f], DTOA[%llu]", fTOA, tDTOA );
    }

    m_pstPDW->ullTOA = tDTOA + m_tTOA;
    m_tTOA = m_pstPDW->ullTOA;

    // 	if( strcmp( PType, "PAT" ) == 0 )	// PRI Pattern 
    // 	{
    // 		if( strcmp( PPatType, "DNS" ) == 0 )	// Dwell & Switch
    // 		{
    // 
    // 		}
    // 		else if( strcmp( PPatType, "SIN" ) == 0 )	// PRI Pattern sinusoidal ( PRI 패턴 사인파)
    // 		{
    // 			pPRI = (UINT)( PRI_width / 2 * sin( 2 * PIE / PPatPrd * toa ) + PRI );
    // 		}
    // 		else
    // 		{
    // 			fPRI = fPRI + Pslop * Pdiff;
    // 			if( strcmp( PPatType, "TRI" ) == 0 )	// PRI Pattern Triangle (PRI 패턴 삼각파)
    // 			{
    // 				if( fPRI > Ppmax )
    // 				{
    // 					fPRI   = 2 * Ppmax - fPRI;
    // 					Pslop *= -1;
    // 				}
    // 				if( fPRI < Ppmin )
    // 				{
    // 					fPRI   = 2 * Ppmin - fPRI;
    // 					Pslop *= -1;
    // 				}
    // 			}
    // 			else
    // 			{
    // 				if( strcmp( PPatType, "SW+" ) == 0 )	// PRI Pattern SAW+ (PRI 패턴 톱니파 증가)
    // 				{
    // 					if( fPRI > Ppmax )
    // 					{
    // 						fPRI = fPRI - PRI_width;
    // 					}
    // 				}
    // 				if( strcmp( PPatType, "SW-" ) == 0 )	// PRI Pattern SAW- (PRI 패턴 톱니파 감소)
    // 				{
    // 					if( fPRI < Ppmin )
    // 					{
    // 						fPRI = fPRI + PRI_width;
    // 					}
    // 				}
    // 			}
    // 			pPRI = (UINT)(fPRI + 0.5);
    // 
    // 		}
    // 	}

}

void CGenPDW::MakePWOfPDW()
{


}

/**
 * @brief     MakeFreqOfPDW
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-28, 14:36
 * @warning
 */
void CGenPDW::MakeFreqOfPDW()
{
    float fFrequency;
    UINT uiFrequency;

    if( strcmp( m_stGenPDWInfo.szFreqType, "FIX" ) == 0 ) {
        fFrequency = ( float ) m_stGenPDWInfo.iFreqMean;
        
    }
    else if( strcmp( m_stGenPDWInfo.szFreqType, "AGI" ) == 0 ) {
        fFrequency = (float) ( rand() % (int) m_stGenPDWInfo.uiBW );
        fFrequency += ( fFrequency - (m_stGenPDWInfo.uiBW / 2 ) );
        fFrequency += ( float ) m_stGenPDWInfo.iFreqMean;
		
	}
    else {
        fFrequency = 0.;
    }

    fFrequency = fFrequency + ( float ) Rand( m_stGenPDWInfo.uiFreqError );

    uiFrequency = CEncode::EncodeRealFREQMHz( fFrequency );

    m_pstPDW->uiFreq = uiFrequency;


    // 	//float fRatio;
    // 	UINT	temp, uiTOA1, uiTOA2, uiTOA;
    // 
    // 	if( strcmp( FType, "PAT" ) == 0 )	// FREQ Pattern 
    // 	{
    // 		if( strcmp( FPatType, "SIN" ) == 0 )	// Freq Pattern sinusoidal (주파수 패턴 사인파)
    // 		{
    // 			// 2 * pi = FPatPrd ( 1주기 )
    // 			pFreq = (UINT)( BW / 2. * sin( ( 2. * PIE * toa ) / ( FPatPrd * 1000. ) ) + Freq );
    // 			// pFreq = ConvertFreq( pFreq, Bc );
    // 		}
    // 		else
    // 		{
    // 			//uiTOA1 = ( toa * ( ONE_MILLISEC / 1000 ) );
    // 			//uiTOA2 = uiTOA1 % FPatPrd;
    // 			//Freq = Freq + ( Fslop * uiTOA2 );
    // 			//fRatio = (float) uiTOA2 / (float) FPatPrd;
    // 
    // 			//Freq = Freq + (UINT) ( BW * fRatio + 0.5 );
    // 			uiTOA = toa % FPatPrd;
    // 			Freq = uiPatternFreq + ( Fslop * uiTOA );
    // 			printf( "\nTOA[%12u], Freq[%12u]" , toa, Freq );
    // 			if( strcmp( FPatType, "TRI" ) == 0 )	// Freq Pattern Triangle (주파수 패턴 삼각파)
    // 			{
    // 				if( Freq > Fpmax )
    // 				{
    // 					Fslop *= -1;
    // 					Freq = 2 * Fpmax - Freq;
    // 				}
    // 				if( Freq < Fpmin )
    // 				{
    // 					Fslop *= -1;
    // 					Freq = 2 * Fpmin - Freq;
    // 				}
    // 			}
    // 			if( strcmp( FPatType, "SW+" ) == 0 )	// Freq Pattern SAW+ (주파수 패턴 톱니파 증가)
    // 			{
    // 				if( Freq > Fpmax ) {
    // 					Freq = ( uiCenterFreq + ( BW / 2 ) );
    // 					uiPatternFreq = ( uiCenterFreq - ( BW / 2 )  );
    // 				}
    // 			}
    // 			if( strcmp( FPatType, "SW-" ) == 0 )	// Freq Pattern SAW- (주파수 패턴 톱니파 감소)
    // 			{
    // 				if( Freq < Fpmin )
    // 					Freq = Freq + BW;
    // 			}
    // 			pFreq = (UINT)(Freq + 0.5);
    // 
    // 			
    // 		}
    // 		pFreq = (UINT) ( pFreq + Rand( Freq_Error ) );
    // 	}

    // 	else if( strcmp( FType, "HOP" ) == 0 )	// Hopping
    // 	{
    // 		Hop_prd = ( FPatPrd *1000. ) / FHopLvl / PRI;	// Hopping level당 펄스수의 계산 
    // 
    // 		if( Hop_cnt % Hop_prd == 0 )
    // 			++ Hop_idx;
    // 
    // 		pFreq  = (UINT)HL[ Hop_idx % FHopLvl ];
    // 
    // 		++ Hop_cnt;
    // 
    // 		pFreq = (UINT) ( pFreq + Rand( Freq_Error ) );
    // 
    // 	}
    // 	else if( strcmp( FType, "FIX" ) == 0 )	// Fixed
    // 	{
    // 		int iFreq;
    // 
    // 		iFreq = (int) ( (Freq + 0.5) );
    // 		pFreq = (UINT) ( iFreq + Rand( Freq_Error ) );
    // 
    // 	}
    // 
    // 	pFreq = (UINT) ConvertFreq( pFreq, Bc );
    // 	
    // 	new_pdw.item.frequency_l  = pFreq & 0xFF;
    // 	new_pdw.item.frequency_h  = ( pFreq >> 8 ) & 0x1F;
}

/**
 * @brief     GetLineCommand
 * @param     void
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-28, 10:31
 * @warning
 */
void CGenPDW::GetLineCommand( void )
{
    int i;

    fscanf( m_File, "%u", &m_stGenPDWInfo.uiIdex ); 	// Read Index 

    fscanf( m_File, "%s", m_stGenPDWInfo.szFileName ); 	// Read NPW Filename 
    
    fscanf( m_File, "%u", &m_stGenPDWInfo.uiCoAllPDW );		// 펄스 개수
    fscanf( m_File, "%d", &m_stGenPDWInfo.uiFirstTOA );		// 초기 TOA값 
    fscanf( m_File, "%u", &m_stGenPDWInfo.uiSignalType );			// normal =0, Pmop =1, chirp+ =2 chirp- =3, cw =4, bit =15
    fscanf( m_File, "%u", &m_stGenPDWInfo.uiDV );			// Direction Valid
    fscanf( m_File, "%u", &m_stGenPDWInfo.uiAOA );			// 방위 [deg]

    fscanf( m_File, "%s", m_stGenPDWInfo.szFreqType );			// 주파수 형태  : FIX(fixed)   AGI(agile)    PAT(pattern)  HOP(hopping)
    // fscanf( rfp, "%d", & Bc );			// 주파수 [MHz]
    fscanf( m_File, "%d", &m_stGenPDWInfo.iFreqMean );			// 주파수 [MHz]

    fscanf( m_File, "%d", &m_stGenPDWInfo.uiBW );			// 주파수 폭 [MHz]
    fscanf( m_File, "%s", m_stGenPDWInfo.szFreqPatType );		// 주파수 패턴 형태 : SIN(sine)    SW+(saw+)     SW-(saw-)
    fscanf( m_File, "%d", &m_stGenPDWInfo.uiFreqPatPrd );		// 주파수 패턴 주기[msec]
    fscanf( m_File, "%u", &m_stGenPDWInfo.uiFreqHopLvl );		// 주파수 Hopping level 수 
    for( i = 0; i < MAX_FREQ_PRI_STEP ; i++ ) {
         fscanf( m_File, "%f", &m_stGenPDWInfo.fFreqSwtVal[i] );	// 주파수 Hopping level 값[MHz]
    }
 
    fscanf( m_File, "%s", m_stGenPDWInfo.szPRIType );			// PRI 형태  : STB(stable)  STG(stagger)  JIT(jitter)   DNS(dwell & switch) 
    fscanf( m_File, "%d", &m_stGenPDWInfo.iPRIMean );			// PRI [us]
    fscanf( m_File, "%f", &m_stGenPDWInfo.fJitterp );			// Jitter %
    fscanf( m_File, "%u", &m_stGenPDWInfo.uiPRIHopLvl );		// PRI switch Level 수 
    for( i = 0; i < MAX_FREQ_PRI_STEP ; i++ ) {
        fscanf( m_File, "%f", &m_stGenPDWInfo.fPRISwtVal[i] );	// PRI switch level 값 [usec]
    }
    fscanf( m_File, "%s", m_stGenPDWInfo.szPRIPatType );		// PRI 패턴 형태  : SIN(sine)    SW+(saw+)     SW-(saw-)
    fscanf( m_File, "%u", &m_stGenPDWInfo.uiPRIPatPrd );		// PRI 패턴 주기[msec]
    fscanf( m_File, "%u", &m_stGenPDWInfo.uiCoPRIPatPDW );		// PRI 패턴 주기[msec]

    fscanf( m_File, "%f", &m_stGenPDWInfo.fPA );			// PA [dBm]
    fscanf( m_File, "%d", &m_stGenPDWInfo.uiPW );			// Pulse Width [nsec]
    fscanf( m_File, "%x", &m_stGenPDWInfo.uiFmop );			// Freq. Diff. [MHz]
    fscanf( m_File, "%x", &m_stGenPDWInfo.uiPmop );			// Pulse Modulation

    fscanf( m_File, "%s", m_stGenPDWInfo.szScanType );		// 스캔 Type : STD(steady)  CON(conical)  CIR(circular) BID(bi-directional)  UNI(uni-directional)
    fscanf( m_File, "%u", &m_stGenPDWInfo.uiScanPrd );		// 스캔 주기 [ms]
    fscanf( m_File, "%u", &m_stGenPDWInfo.uiCoScanPrd );		// 스캔 lobe 당 펄스수  

    fscanf( m_File, "%u", &m_stGenPDWInfo.uiDOAError );	
    fscanf( m_File, "%u", &m_stGenPDWInfo.uiFreqError );	// 주파수 오차
    fscanf( m_File, "%u", &m_stGenPDWInfo.uiTOAError );	// TOA 오차
    fscanf( m_File, "%u", &m_stGenPDWInfo.uiPWError );		// 펄스폭 오차
    fscanf( m_File, "%u", &m_stGenPDWInfo.uiPAError );		// 펄스폭 오차
    fscanf( m_File, "%u", &m_stGenPDWInfo.uiCoPulseSkip );	// 누락율: N 개중에 1개 누락

    printf( "\n %u   PDW 생성하기...  [ %s ]", m_stGenPDWInfo.uiIdex, m_stGenPDWInfo.szFileName );

}

/**
 * @brief     SkipTheHeader
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-27, 20:46
 * @warning
 */
void CGenPDW::SkipTheHeader()
{
    int i;
    char  buf[1024];

    for( i = 0; i < 10; i++ ) {	// 10 줄 
        fgets( buf, 1024, m_File );
    }
}

/**
 * @brief     Rand
 * @param     int range
 * @return    int
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-28, 14:41
 * @warning
 */
int CGenPDW::Rand( int range )
{
	int random_val = 0;

    if( range == 0 ) {
    }
    else {
        random_val = rand() % ( 2 * range + 1 );
        random_val -= range;
    }

	return random_val;

}