// CGenPDW.cpp: �ó����� ������ �о ���Ϸ� �����ϰų� ���յ� PDW ������ �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"

#define _USE_MATH_DEFINES

#include "CGenPDW.h"

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "../../files/Utils/ccommonutils.h"


/**
 * @brief     CGenPDW
 * @return    
 * @exception
 * @author    ��ö�� (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-04, 10:13
 * @warning
 */
CGenPDW::CGenPDW( int iCoMergedPDW )
{
    size_t szSize;

    // �ʱ�ȭ
    m_stSavePDWData.pstPDW = NULL;
    m_File = NULL;

    m_iCoMergedPDW = iCoMergedPDW;

    memset( &m_stMergedPDWData.x, 0, sizeof( UNION_HEADER ) );
    szSize = CCommonUtils::CheckMultiplyOverflow( sizeof( _PDW ), iCoMergedPDW );
    m_stMergedPDWData.pstPDW = ( _PDW* ) malloc( szSize );
    m_stMergedPDWData.SetTotalPDW( 0 );

}

/**
 * @brief     CGenPDW
 * @param     char * pszFileName
 * @return    
 * @exception
 * @author    ��ö�� (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-27, 20:39
 * @warning
 */
// CGenPDW::CGenPDW( char *pszFileName )
// {
//     
// 
//     //  mak_file�� read mode�� open �� �� ������ ��� ���� ó�� 
//     strcpy( m_szMakfilename, pszFileName );
// 
//     if( (m_File = fopen( m_szMakfilename, "rt" )) == NULL ) {
//         printf( "\n %s File Open ERROR : %s", m_szMakfilename, strerror( errno ) );
//     }
// 
// 
// }

/**
 * @brief     OpenFile
 * @param     char * pszFileName
 * @return    void
 * @exception
 * @author    ��ö�� (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-04, 11:16
 * @warning
 */
void CGenPDW::OpenFile( char *pszFileName )
{
    if( m_File != NULL ) {
        fclose( m_File );
    }

    //  mak_file�� read mode�� open �� �� ������ ��� ���� ó�� 
    strcpy( m_szMakfilename, pszFileName );

    m_File = fopen( m_szMakfilename, "rt" );
    if( m_File == NULL ) {
        printf( "\n %s File Open ERROR : %s", m_szMakfilename, strerror( errno ) );
    }
}

/**
 * @brief     ~CGenPDW
 * @param     void
 * @return    
 * @exception
 * @author    ��ö�� (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-27, 20:40
 * @warning
 */
CGenPDW::~CGenPDW()
{
    if( m_File != NULL ) {
        fclose( m_File );
    }

    free( m_stMergedPDWData.pstPDW );

}

/**
 * @brief     ParsingThePDWMakefile
 * @return    void
 * @exception
 * @author    ��ö�� (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-27, 20:46
 * @warning
 */
void CGenPDW::ParseAndMakefile()
{

    SkipTheHeader();

    //////////////////////////////////////////////////////////
    while( ! feof( m_File ) ) {
		GetLineCommand();

        // ��ġ�� ���
        g_enUnitType = CCommonUtils::WhatUnitType( m_stGenPDWInfo.szFileName );

        // �޸� �Ҵ�
        //m_stSavePDWData.pstPDW = (_PDW *) malloc( m_stGenPDWInfo.uiCoAllPDW * sizeof(_PDW) );
        m_stSavePDWData.pstPDW = new _PDW[m_stGenPDWInfo.uiCoAllPDW];
        m_pstPDW = m_stSavePDWData.pstPDW;

        CRawFile::OpenFile( m_stGenPDWInfo.szFileName, O_CREAT | O_BINARY | O_WRONLY ); //  | O_TRUNC );

        MakeFileHeader();
        Write( &m_stSavePDWData.x, sizeof( UNION_HEADER ) );

        SetGenerateInfo();

        // PDW �߻��ؼ� ���Ϸ� ����
        GeneratePDW();
        Write( m_stSavePDWData.pstPDW, sizeof( _PDW ) * m_stSavePDWData.GetTotalPDW() );

        CloseFile();       

        delete( m_stSavePDWData.pstPDW );
        m_stSavePDWData.pstPDW = NULL;

    }



}

/**
 * @brief     ParseAndMakeMemory
 * @return    void
 * @exception
 * @author    ��ö�� (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-04, 11:26
 * @warning
 */
void CGenPDW::ParseAndMakeMemory( SIGAPDW *pSigPDW )
{

    m_stMergedPDWData.SetTotalPDW( 0 );

    SkipTheHeader();

    //////////////////////////////////////////////////////////
    while( !feof( m_File ) ) {
        size_t szSize;

        GetLineCommand();

        // �޸� �Ҵ�
        szSize = CCommonUtils::CheckMultiplyOverflow( sizeof( _PDW ), m_stGenPDWInfo.uiCoAllPDW );
        m_stSavePDWData.pstPDW = ( _PDW * ) malloc(  szSize );
        m_pstPDW = m_stSavePDWData.pstPDW;

        MakeFileHeader();

        // PDW �߻��ؼ� ���Ϸ� ����
        SetGenerateInfo();
        GeneratePDW( pSigPDW );

        free( m_stSavePDWData.pstPDW );
        m_stSavePDWData.pstPDW = NULL;

    }

}

/**
 * @brief     SetGenerateInfo
 * @return    void
 * @exception
 * @author    ��ö�� (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-28, 15:11
 * @warning
 */
void CGenPDW::SetGenerateInfo()
{
    int iBandWidth = m_stSavePDWData.GetBandWidth();

    // 
    m_tTOA = CEncode::EncodeTOAus( (float) m_stGenPDWInfo.uiFirstTOA, iBandWidth );


    m_fPRICountPerPeriod = ( float ) (( float ) m_stGenPDWInfo.uiPRIPatPrd / ( float ) m_stGenPDWInfo.iPRIMean);    
    m_uiPRILvl = 0;
    m_fPriWidth = (float) ( ( (float ) m_stGenPDWInfo.iPRIMean * m_stGenPDWInfo.fJitterp ) / 100. / 2.0 );

    m_ui1DOA = CEncode::EncodeDOA( 1.0 );

//     m_tFreqPeriod = CEncode::EncodeTOAus( m_stGenPDWInfo.uiFreqPatPrd, iBandWidth );
//     m_tPRIPeriod = m_stGenPDWInfo.uiPRIPatPrd;

    //m_iPWError = CEncode::EncodePWns( (float) m_stGenPDWInfo.uiPWError, iBandWidth );

    if( g_enUnitType == en_XBAND ) {
        m_i360DOA = 36000;

    }
    else if( g_enUnitType == en_ZPOCKETSONATA ) {
        m_i360DOA = 4 * 1024;

    }
    else {
        m_i360DOA = 360;    // �⺻��
    }

    m_uiPRIDwellCount = 0;

}

/**
 * @brief     MakeFileHeader
 * @return    void
 * @exception
 * @author    ��ö�� (churlhee.jo@lignex1.com)
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
        break;

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
 * @author    ��ö�� (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-28, 13:14
 * @warning
 */
void CGenPDW::GeneratePDW( SIGAPDW *pSigPDW )
{
    UINT i, j;

    for( i = 0 ; i < m_stGenPDWInfo.uiCoAllPDW ; ) {

        m_stGenPDWInfo.uiCoScanPrd = max( 1, m_stGenPDWInfo.uiCoScanPrd );

        for( j = 0 ; j < m_stGenPDWInfo.uiCoScanPrd && i < m_stGenPDWInfo.uiCoAllPDW ; ++j, ++i ) {
            MakeSignalType();
            MakeDOAOfPDW( );
            MakeFreqOfPDW( );
            MakePRIOfPDW( i == 0 );
            MakePWOfPDW( );
            MakePAOfPDW( );

            ++m_pstPDW;
        }
        
    }

    MergePDW( pSigPDW );
    
}

/**
 * @brief     �߻��� PDW ���� �ð������� �����Ͽ� �����Ѵ�.
 * @return    void
 * @exception
 * @author    ��ö�� (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-04, 13:40
 * @warning
 */
void CGenPDW::MergePDW( SIGAPDW *pSigPDW )
{
    int iIndex, iMove;

    UINT i, uiCoTotalPDW, uiCoMergedPDW;

    m_pstPDW = m_stSavePDWData.pstPDW;
    uiCoTotalPDW = m_stSavePDWData.GetTotalPDW();

    if( pSigPDW != NULL ) {
        for( i = 0 ; i < uiCoTotalPDW ; ++i ) {
            iIndex = m_stMergedPDWData.GetIndexByTOA( m_pstPDW->GetTOA() );
        }
    }
    else {
        //pstMergedPDW = m_stMergedPDWData.pstPDW;

        for( i = 0 ; i < uiCoTotalPDW ; ++i ) {
            // ��ġ ã��
            iIndex = m_stMergedPDWData.GetIndexByTOA( m_pstPDW->GetTOA() );

            // �����Ѵ�.
            if( iIndex >= 0 ) {
                uiCoMergedPDW = m_stMergedPDWData.GetTotalPDW();

                if( iIndex < m_iCoMergedPDW ) {
                    iMove = ( int ) uiCoMergedPDW - iIndex;
                    if( iMove > 0 ) {
                        memmove( &m_stMergedPDWData.pstPDW[iIndex + 1], &m_stMergedPDWData.pstPDW[iIndex], sizeof( _PDW )*( size_t ) iMove );
                    }

                    memcpy( &m_stMergedPDWData.pstPDW[iIndex], m_pstPDW, sizeof( _PDW ) );
                }

                // ���յ� PDW ���� ���� : �ִ� �ʱ� ������ �Լ����� ������ ������ �����ϰ� ��.
                ++uiCoMergedPDW;
                if( uiCoMergedPDW < ( UINT ) m_iCoMergedPDW ) {
                    m_stMergedPDWData.SetTotalPDW( uiCoMergedPDW );
                }
            }
            // ��ü �Ǵ� �����Ѵ�.
            else {
                if( m_pstPDW->GetPulseamplitude() > m_stMergedPDWData.pstPDW[-iIndex - 1].GetPulseamplitude() ) {
                    memcpy( &m_stMergedPDWData.pstPDW[-iIndex - 1], m_pstPDW, sizeof( _PDW ) );
                }
            }

            ++m_pstPDW;
        }
    }

}

/**
 * @brief     PDW �� ��ȣ���¸� ���� �߻��Ѵ�.
 * @return    void
 * @exception
 * @author    ��ö�� (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-28, 16:30
 * @warning
 */
void CGenPDW::MakeSignalType( SIGAPDW *pSigPDW )
{
    m_pstPDW->iPulseType = CEncode::EncodePulseType ( m_stGenPDWInfo.uiSignalType );

}

/**
 * @brief     PDW �� ���� ���� ���� �߻��Ѵ�.
 * @return    void
 * @exception
 * @author    ��ö�� (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-28, 16:48
 * @warning
 */
void CGenPDW::MakeDOAOfPDW( SIGAPDW *pSigPDW )
{
    unsigned int uiDOA;
    float fDOA;
    unsigned uiDOAError;

    fDOA = (float) m_stGenPDWInfo.uiAOA;

    uiDOA = CEncode::EncodeDOA( fDOA );

    uiDOAError = m_ui1DOA * m_stGenPDWInfo.uiDOAError;
    uiDOA += CCommonUtils::Rand( (int) uiDOAError );
    uiDOA = (uiDOA + m_i360DOA ) % m_i360DOA;

    m_pstPDW->uiAOA = uiDOA;
}

/**
 * @brief     PDW �� �޽����� ���� �߻��Ѵ�.
 * @return    void
 * @exception
 * @author    ��ö�� (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-28, 17:16
 * @warning
 */
void CGenPDW::MakePWOfPDW( SIGAPDW *pSigPDW )
{
    float fPW;

    fPW = (float) m_stGenPDWInfo.uiPW + CCommonUtils::Rand( ( int ) m_stGenPDWInfo.uiPWError );
    if( fPW < 0 ) {
        fPW = (float) m_stGenPDWInfo.uiPW;
    }
    
    int iBandWidth = m_stSavePDWData.GetBandWidth();
    m_pstPDW->uiPW = CEncode::EncodePWns( fPW, iBandWidth );

}

/**
 * @brief     PDW �� ��ȣ���⸦ ���� �߻��Ѵ�.
 * @return    void
 * @exception
 * @author    ��ö�� (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-02, 18:20
 * @warning
 */
void CGenPDW::MakePAOfPDW( SIGAPDW *pSigPDW )
{
    unsigned int uiPA;
    float fPA;

    fPA = ( float ) m_stGenPDWInfo.fPA;

    uiPA = CEncode::EncodePA( fPA );

    uiPA += (unsigned int) CCommonUtils::Rand( ( int ) m_stGenPDWInfo.uiPAError );

    m_pstPDW->uiPA = ( unsigned int ) uiPA;
}

/**
 * @brief     PDW �� PRI�� ���� �߻��Ѵ�.
 * @return    void
 * @exception
 * @author    ��ö�� (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-28, 14:57
 * @warning
 */
void CGenPDW::MakePRIOfPDW( bool bSkippedPDW, SIGAPDW *pSigPDW )
{
    _TOA tDTOA=0;
    float fTOA=0.0;

    int iBandWidth;

    if( bSkippedPDW == false ) {
        if( strcmp( m_stGenPDWInfo.szPRIType, "STB" ) == 0 ) {
            fTOA = ( float ) m_stGenPDWInfo.iPRIMean;

        }
        else if( strcmp( m_stGenPDWInfo.szPRIType, "STG" ) == 0 ) {
            fTOA = ( float ) m_stGenPDWInfo.fPRISwtVal[m_uiPRILvl];
            ++m_uiPRILvl;
            m_uiPRILvl = m_uiPRILvl % m_stGenPDWInfo.uiPRIHopLvl;
        }
        else if( strcmp( m_stGenPDWInfo.szPRIType, "JIT" ) == 0 ) {
            fTOA = ( float ) CCommonUtils::Rand( (int) ( m_fPriWidth + 0.5 ) );
            fTOA += ( float ) m_stGenPDWInfo.iPRIMean;
        }
        else if( strcmp( m_stGenPDWInfo.szPRIType, "DNS" ) == 0 ) {
            fTOA = ( float ) m_stGenPDWInfo.fPRISwtVal[m_uiPRILvl];

            ++m_uiPRIDwellCount;

            if( m_uiPRIDwellCount % m_stGenPDWInfo.uiCoPRIPatPDW == 0 ) {
                ++ m_uiPRILvl;
                m_uiPRILvl = m_uiPRILvl % m_stGenPDWInfo.uiPRIHopLvl;
            }
        }
        else if( strcmp( m_stGenPDWInfo.szPRIType, "PAT" ) == 0 ) {
            if( strcmp( m_stGenPDWInfo.szPRIPatType, "SIN" ) == 0 ) {
                double dTheta;

                fTOA = ( float ) m_stGenPDWInfo.iPRIMean;

                dTheta = (2. * M_PI * (( float ) m_uiPRILvl )) / m_fPRICountPerPeriod;
                fTOA += ( m_fPriWidth ) * (float) sin( dTheta );

            }
            else if( strcmp( m_stGenPDWInfo.szPRIPatType, "TRI" ) == 0 ) {
                int iHalfPRICountPerPeriod = (int) ( ( m_fPRICountPerPeriod / (float) 2.0 ) + 0.5 );

                if( m_uiPRILvl % iHalfPRICountPerPeriod == 0 ) {
                    fTOA = ( float ) m_stGenPDWInfo.iPRIMean - m_fPriWidth;
                    fTOA += (( float ) (m_uiPRILvl % ( int ) (m_fPRICountPerPeriod + 0.5)) * ( float ) m_stGenPDWInfo.iPRIMean * (((float) 2. * m_fPriWidth) / ( float ) m_stGenPDWInfo.uiPRIPatPrd));
                }
                else {
                    fTOA = ( float ) m_stGenPDWInfo.iPRIMean + m_fPriWidth;
                    fTOA -= (( float ) (m_uiPRILvl % ( int ) (m_fPRICountPerPeriod + 0.5)) * ( float ) m_stGenPDWInfo.iPRIMean * (((float) 2. * m_fPriWidth) / ( float ) m_stGenPDWInfo.uiPRIPatPrd));
                }
            }

            else if( strcmp( m_stGenPDWInfo.szPRIPatType, "SW+" ) == 0 ) {
                fTOA = ( float ) m_stGenPDWInfo.iPRIMean - m_fPriWidth;
                fTOA += (( float ) (m_uiPRILvl % (int) ( m_fPRICountPerPeriod+0.5) ) * ( float ) m_stGenPDWInfo.iPRIMean * (( (float) 2. * m_fPriWidth) / ( float ) m_stGenPDWInfo.uiPRIPatPrd));
            }

            else if( strcmp( m_stGenPDWInfo.szPRIPatType, "SW-" ) == 0 ) {
                fTOA = ( float ) m_stGenPDWInfo.iPRIMean + m_fPriWidth;
                fTOA -= (( float ) (m_uiPRILvl % ( int ) (m_fPRICountPerPeriod + 0.5)) * ( float ) m_stGenPDWInfo.iPRIMean * (( (float) 2. * m_fPriWidth) / ( float ) m_stGenPDWInfo.uiPRIPatPrd));
            }

            else {
                printf( "\n PRI ���� Ÿ���� �߸� �Է��߽��ϴ� !!" );
            }

            ++m_uiPRILvl;
        }
        else {
            printf( "\n PRI Ÿ���� �߸� �Է��߽��ϴ� !!" );
        }

        fTOA += ( float ) (CCommonUtils::Rand( m_stGenPDWInfo.uiTOAError * 1000 ) / 1000. );

        iBandWidth = m_stSavePDWData.GetBandWidth();
        tDTOA = CEncode::EncodeTOAus( fTOA, iBandWidth );

        // TRACE( "\n fTOA[%f], DTOA[%llu]", fTOA, tDTOA );
    }

    m_pstPDW->ullTOA = tDTOA + m_tTOA;
    m_tTOA = m_pstPDW->ullTOA;

    // 	if( strcmp( PType, "PAT" ) == 0 )	// PRI Pattern 
    // 	{
    // 		else if( strcmp( PPatType, "SIN" ) == 0 )	// PRI Pattern sinusoidal ( PRI ���� ������)
    // 		{
    // 			pPRI = (UINT)( PRI_width / 2 * sin( 2 * PIE / PPatPrd * toa ) + PRI );
    // 		}
    // 		else
    // 		{
    // 			fPRI = fPRI + Pslop * Pdiff;
    // 			if( strcmp( PPatType, "TRI" ) == 0 )	// PRI Pattern Triangle (PRI ���� �ﰢ��)
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
    // 				if( strcmp( PPatType, "SW+" ) == 0 )	// PRI Pattern SAW+ (PRI ���� ����� ����)
    // 				{
    // 					if( fPRI > Ppmax )
    // 					{
    // 						fPRI = fPRI - PRI_width;
    // 					}
    // 				}
    // 				if( strcmp( PPatType, "SW-" ) == 0 )	// PRI Pattern SAW- (PRI ���� ����� ����)
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

/**
 * @brief     MakeFreqOfPDW
 * @return    void
 * @exception
 * @author    ��ö�� (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-28, 14:36
 * @warning
 */
void CGenPDW::MakeFreqOfPDW( SIGAPDW *pSigPDW )
{
    int iCh;

    float fFrequency;
    UINT uiFrequency;

    if( strcmp( m_stGenPDWInfo.szFreqType, "FIX" ) == 0 ) {
        fFrequency = ( float ) m_stGenPDWInfo.iFreqMean;
        
    }
    else if( strcmp( m_stGenPDWInfo.szFreqType, "AGI" ) == 0 ) {
        fFrequency = ( float ) m_stGenPDWInfo.iFreqMean + (float) CCommonUtils::Rand( m_stGenPDWInfo.uiBW );
		
	}
    else {
        fFrequency = 0.;
    }

    fFrequency = fFrequency + ( float ) CCommonUtils::Rand( m_stGenPDWInfo.uiFreqError * 1000 ) / (float) 1000;

    uiFrequency = CEncode::EncodeRealFREQMHz( & iCh, fFrequency );
    m_pstPDW->SetChannel( iCh );

    m_pstPDW->uiFreq = uiFrequency;


    // 	//float fRatio;
    // 	UINT	temp, uiTOA1, uiTOA2, uiTOA;
    // 
    // 	if( strcmp( FType, "PAT" ) == 0 )	// FREQ Pattern 
    // 	{
    // 		if( strcmp( FPatType, "SIN" ) == 0 )	// Freq Pattern sinusoidal (���ļ� ���� ������)
    // 		{
    // 			// 2 * pi = FPatPrd ( 1�ֱ� )
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
    // 			if( strcmp( FPatType, "TRI" ) == 0 )	// Freq Pattern Triangle (���ļ� ���� �ﰢ��)
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
    // 			if( strcmp( FPatType, "SW+" ) == 0 )	// Freq Pattern SAW+ (���ļ� ���� ����� ����)
    // 			{
    // 				if( Freq > Fpmax ) {
    // 					Freq = ( uiCenterFreq + ( BW / 2 ) );
    // 					uiPatternFreq = ( uiCenterFreq - ( BW / 2 )  );
    // 				}
    // 			}
    // 			if( strcmp( FPatType, "SW-" ) == 0 )	// Freq Pattern SAW- (���ļ� ���� ����� ����)
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
    // 		Hop_prd = ( FPatPrd *1000. ) / FHopLvl / PRI;	// Hopping level�� �޽����� ��� 
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
 * @author    ��ö�� (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-28, 10:31
 * @warning
 */
void CGenPDW::GetLineCommand( void )
{
    int i;

    fscanf( m_File, "%u", &m_stGenPDWInfo.uiIdex ); 	// Read Index 

    fscanf_s( m_File, "%s", m_stGenPDWInfo.szFileName, sizeof( m_stGenPDWInfo.szFileName) ); 	// Read NPW Filename 
    
    fscanf( m_File, "%u", &m_stGenPDWInfo.uiCoAllPDW );		// �޽� ����
    fscanf( m_File, "%d", &m_stGenPDWInfo.uiFirstTOA );		// �ʱ� TOA�� 
    fscanf( m_File, "%u", &m_stGenPDWInfo.uiSignalType );			// normal =0, Pmop =1, chirp+ =2 chirp- =3, cw =4, bit =15
    fscanf( m_File, "%u", &m_stGenPDWInfo.uiDV );			// Direction Valid
    fscanf( m_File, "%u", &m_stGenPDWInfo.uiAOA );			// ���� [deg]

    fscanf_s( m_File, "%s", m_stGenPDWInfo.szFreqType, sizeof( m_stGenPDWInfo.szFreqType ) );			// ���ļ� ����  : FIX(fixed)   AGI(agile)    PAT(pattern)  HOP(hopping)
    // fscanf( rfp, "%d", & Bc );			// ���ļ� [MHz]
    fscanf( m_File, "%d", &m_stGenPDWInfo.iFreqMean );			// ���ļ� [MHz]

    fscanf( m_File, "%d", &m_stGenPDWInfo.uiBW );			// ���ļ� �� [MHz]
    fscanf_s( m_File, "%s", m_stGenPDWInfo.szFreqPatType, sizeof( m_stGenPDWInfo.szFreqPatType ) );		// ���ļ� ���� ���� : SIN(sine)    SW+(saw+)     SW-(saw-)
    fscanf( m_File, "%d", &m_stGenPDWInfo.uiFreqPatPrd );		// ���ļ� ���� �ֱ�[msec]
    fscanf( m_File, "%u", &m_stGenPDWInfo.uiFreqHopLvl );		// ���ļ� Hopping level �� 
    for( i = 0; i < MAX_FREQ_PRI_STEP ; i++ ) {
         fscanf( m_File, "%f", &m_stGenPDWInfo.fFreqSwtVal[i] );	// ���ļ� Hopping level ��[MHz]
    }
 
    fscanf_s( m_File, "%s", m_stGenPDWInfo.szPRIType, sizeof( m_stGenPDWInfo.szPRIType ) );			// PRI ����  : STB(stable)  STG(stagger)  JIT(jitter)   DNS(dwell & switch) 
    fscanf( m_File, "%d", &m_stGenPDWInfo.iPRIMean );			// PRI [us]
    fscanf( m_File, "%f", &m_stGenPDWInfo.fJitterp );			// Jitter %
    fscanf( m_File, "%u", &m_stGenPDWInfo.uiPRIHopLvl );		// PRI switch Level �� 
    for( i = 0; i < MAX_FREQ_PRI_STEP ; i++ ) {
        fscanf( m_File, "%f", &m_stGenPDWInfo.fPRISwtVal[i] );	// PRI switch level �� [usec]
    }
    fscanf_s( m_File, "%s", m_stGenPDWInfo.szPRIPatType, sizeof( m_stGenPDWInfo.szPRIPatType ) );		// PRI ���� ����  : SIN(sine)    SW+(saw+)     SW-(saw-)
    fscanf( m_File, "%u", &m_stGenPDWInfo.uiPRIPatPrd );		// PRI ���� �ֱ�[msec]
    fscanf( m_File, "%u", &m_stGenPDWInfo.uiCoPRIPatPDW );		// PRI ���� �ֱ�[msec]

    fscanf( m_File, "%f", &m_stGenPDWInfo.fPA );			// PA [dBm]
    fscanf( m_File, "%d", &m_stGenPDWInfo.uiPW );			// Pulse Width [nsec]
    fscanf( m_File, "%x", &m_stGenPDWInfo.uiFmop );			// Freq. Diff. [MHz]
    fscanf( m_File, "%x", &m_stGenPDWInfo.uiPmop );			// Pulse Modulation

    fscanf_s( m_File, "%s", m_stGenPDWInfo.szScanType, sizeof( m_stGenPDWInfo.szScanType ) );		// ��ĵ Type : STD(steady)  CON(conical)  CIR(circular) BID(bi-directional)  UNI(uni-directional)
    fscanf( m_File, "%u", &m_stGenPDWInfo.uiScanPrd );		// ��ĵ �ֱ� [ms]
    fscanf( m_File, "%u", &m_stGenPDWInfo.uiCoScanPrd );		// ��ĵ lobe �� �޽���  

    fscanf( m_File, "%u", &m_stGenPDWInfo.uiDOAError );	
    fscanf( m_File, "%u", &m_stGenPDWInfo.uiFreqError );	// ���ļ� ����
    fscanf( m_File, "%u", &m_stGenPDWInfo.uiTOAError );	// TOA ����
    fscanf( m_File, "%u", &m_stGenPDWInfo.uiPWError );		// �޽��� ����
    fscanf( m_File, "%u", &m_stGenPDWInfo.uiPAError );		// �޽��� ����
    fscanf( m_File, "%u", &m_stGenPDWInfo.uiCoPulseSkip );	// ������: N ���߿� 1�� ����

    // �� üũ�ؼ� ���� �߻��� ������ �����Ѵ�.
    if( IsValidCheck() == false ) {
        printf( "\n ���� �� ���� �Դϴ�." );
        m_stGenPDWInfo.uiCoPRIPatPDW = 1;
    }

    printf( "\n %u   PDW �����ϱ�...  [ %s ]", m_stGenPDWInfo.uiIdex, m_stGenPDWInfo.szFileName );

}

/**
 * @brief     IsValidCheck
 * @return    bool
 * @exception
 * @author    ��ö�� (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-10, 16:21
 * @warning
 */
bool CGenPDW::IsValidCheck()
{
    bool bRet = true;

    if( m_stGenPDWInfo.uiCoPRIPatPDW == 0 || m_stGenPDWInfo.uiPRIHopLvl == 0 ) {
        //bRet = false;
    }

    return bRet;

}

/**
 * @brief     �ó����� ������ ���(�ó����� ����)�� �����Ѵ�.
 * @return    void
 * @exception
 * @author    ��ö�� (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-27, 20:46
 * @warning
 */
void CGenPDW::SkipTheHeader()
{
    int i;
    char  buf[1024];

    if( m_File != NULL ) {
        for( i = 0; i < 10; i++ ) {	// 10 �� 
            fgets( buf, 1024, m_File );
        }

    }

}

