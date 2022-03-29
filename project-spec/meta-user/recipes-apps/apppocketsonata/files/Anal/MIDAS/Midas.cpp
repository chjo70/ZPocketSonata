/**
 * @file      Midas.cpp
 * @brief     MIDAS Blue 포멧으로 변환하는 클래스
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2014-11-27, 오후 3:17
 * @warning
 */

#include "stdafx.h"

#define _DECODE_

#ifdef __GNUC__

#include <sys/types.h>
#include <unistd.h>

#include <float.h>

#include "../SigAnal/_Type.h"

#else
#include <io.h>

#endif


#include <fcntl.h>
#include <time.h>
#include <stdlib.h>


#include "../Collect/DataFile/DataFile.h"

#include "Midas.h"

#include "../../Utils/ccommonutils.h"
#include "../../Include/global.h"


#define _EXT_HEADER_

#ifdef _DECODE_
#include "ELDecoder.h"
#include "../Collect/DataFile/DataFile.h"

#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

ENUM_ENDIAN_MODE g_enEndian;

/**
 * @brief     MIDAS 포멧을 처리하기 위한 메모리를 할당한다.
 * @param     void
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-02-07, 오후 2:59
 * @warning
 */
CMIDASBlueFileFormat::CMIDASBlueFileFormat(void)
{
    m_pExtendOfHeader = NULL;

    // m_pHCB = ( SELMIDAS_HCB * ) new byte[sizeof( SELMIDAS_HCB ) ];
    m_pHCB = ( SELMIDAS_HCB * ) malloc( HEADER_CONTROL_BLOCK_SIZE );

    // m_pPDWRecords = ( S_EL_PDW_RECORDS * ) new S_EL_PDW_RECORDS[MAX_OF_PDW_DATA];
    m_pPDWRecords = ( S_EL_PDW_RECORDS * ) malloc( sizeof( S_EL_PDW_RECORDS ) * MAX_OF_PDW_DATA );

    //m_pSubrecords = ( SELMIDAS_SUBRECORDS * ) new SELMIDAS_SUBRECORDS[MAX_SUBRECORDS_OF_PDWDATA+1];
    m_pSubrecords = ( SELMIDAS_SUBRECORDS * ) malloc( sizeof( SELMIDAS_SUBRECORDS ) * ( MAX_SUBRECORDS_OF_PDWDATA+1 ) );

    // 초기 설정 정의
    memset( & m_strKeywordValue, 0, sizeof(SEL_KEYWORD_VALUE) );
    strcpy( m_strKeywordValue.writer_version, "0.1" );
#if defined(_ELINT_) || defined(_XBAND_)
    strcpy( m_strKeywordValue.writer, "ELINT" );
#elif _POCKETSONATA_
    strcpy( m_strKeywordValue.writer, "ZSONATA" );
#else
    strcpy( m_strKeywordValue.writer, "MIDAS" );
#endif

}


/**
 * @brief     메모리 해지 처리한다.
 * @param     void
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-02-07, 오후 2:59
 * @warning
 */
CMIDASBlueFileFormat::~CMIDASBlueFileFormat(void)
{
    free( m_pHCB );
    free( m_pPDWRecords );
    free( m_pSubrecords );

    MIDASClose();

}

/**
 * @brief SaveMIDASFormat
 * @param pMidasFileName
 * @param enFileType
 * @param pData
 * @return
 */
bool CMIDASBlueFileFormat::SaveMIDASFormat( const char *pMidasFileName, EnumSCDataType enFileType, void *pData, SEL_KEYWORD_VALUE *pstKeywordValue )
{
    bool bRet = true;

    if( pstKeywordValue->numberofdata == 0 ) {
        bRet = false;
    }
    else {
        m_enFileType = enFileType;

        //memcpy( & m_strKeywordValue, pstKeywordValue, sizeof(SEL_KEYWORD_VALUE) );

        // 1. 사용자 지정 파일 생성
        if( FileOpen( pMidasFileName, O_CREAT | O_BINARY | O_WRONLY ) == false ) { //DTEC_Else
            bRet = false;
        }
        else {
            if( enFileType == E_EL_SCDT_PDW ) {
               m_pPDWData = ( STR_PDWDATA * ) pData;

               // 2. MIDAS 포멧으로 헤더 및 부가 구조체 저장
               MakeHeader();

               // 3. Adjunct 헤더 파일 변환
               MakeAdjunct();

               // 4. HCD 저장
               WriteHeader();
               // 5. 데이터 저장
               if( ! WriteData( 0, 0 ) ) { //DTEC_Else
                   bRet = false;

               }
               else {
                   // 6. Extended Header 변환
                   MakeExtendedHeader();

                   WriteExtendedHeader();
               }
            }
            else {

            }

            // 7. 변환 파일 닫기
            FileClose();

            // 8.
            MIDASClose();
        }

        //printf( "신호 수집 EPDW : %s" , pMidasFileName );
    }

    return bRet;

}

/**
 * @brief     IQ, PDW 등의 입력 파일을 MIDAS 포멧으로 변환하여 저장한다.
 * @param     char * pMidasFileName
 * @param     EnumSCDataType enFileType
 * @param     int i_pstReadFile
 * @param     int i_nFileRawDataStartOffset
 * @param     SEL_KEYWORD_VALUE & stKeywordValue
 * @return    bool
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-07-15, 오후 3:38
 * @warning
 */
bool CMIDASBlueFileFormat::SaveMIDASFormat( char *pMidasFileName, EnumSCDataType enFileType, int i_pstReadFile, int i_nFileRawDataStartOffset, SEL_KEYWORD_VALUE & stKeywordValue, char *pInputFilename, char *pTaskId )
{
    bool bRet=true;

    m_enFileType = enFileType;

    if( m_enFileType != E_EL_SCDT_IF || pInputFilename == NULL ) {
        // 1. 사용자 지정 파일 생성
        if( FileOpen( pMidasFileName, O_CREAT | O_BINARY ) == false ) { //DTEC_Else
            bRet = false;
        }
        else {

            //
            memcpy( & m_strKeywordValue, & stKeywordValue, sizeof(SEL_KEYWORD_VALUE) );

            // 2. MIDAS 포멧으로 헤더 및 부가 구조체 저장
            MakeHeader();

            // 3. Adjunct 헤더 파일 변환
            MakeAdjunct();

            // 4. HCD 저장
            WriteHeader();

            // 5. 데이터 저장
            if( ! WriteData( i_pstReadFile, i_nFileRawDataStartOffset ) ) { //DTEC_Else
                bRet = false;

            }
            else {
                // 6. Extended Header 변환
                MakeExtendedHeader();

                WriteExtendedHeader();
            }

            // 7. 변환 파일 닫기
            FileClose();

            // 8.
            MIDASClose();
        }
    }
    else {
        SELIFMIDAS stIFMIDAS;

        if( m_vecConvertIFList.size() == 0 ) {
            strcpy( m_szIFTaskId, pTaskId );
        }

        if( strcmp( m_szIFTaskId, pTaskId ) == 0 ) {
            strcpy( stIFMIDAS.szInputFilename, pInputFilename );
            strcpy( stIFMIDAS.szOutputFilename, pMidasFileName );
            stIFMIDAS.keywordValue = stKeywordValue;
            m_vecConvertIFList.push_back( stIFMIDAS );
        }

        bRet = false;
    }

    return bRet;
}

/**
 * @brief     MIDAS 포멧에 데이터 영역을 기록한다.
 * @param     E_EL_FILE_TYPE enFileType
 * @param     void * pData
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2014-12-03, 오후 2:19
 * @warning
 */
bool CMIDASBlueFileFormat::WriteData( int destFileId, int iSkipByte, bool bMultiIFData )
{
    bool bRet=true;
    long sz_file;
    unsigned int uiWrite;
    unsigned int i, numberofdata;

    long long int llNullCh=0;

    int iRecords, iSize;

    S_UNI_DATA_SET x;
    /*! \bug  신뢰성: 변수 초기화
            \author 조철희 (churlhee.jo@lignex1.com)
            \date 	2015-10-5 17:36:12
    */
    unsigned int uiWriteByte=0;

    numberofdata = m_strKeywordValue.numberofdata;

    if( m_enFileType != E_EL_SCDT_PDW2SP370 ) {
        // 데이터 블럭에서 쓰고 난 이후에 512 블럭을 맞추기 위해서 NULL 문자 개수를 계산함.
        llNullCh = (long long int) ( ( m_pHCB->ext_start * BYTE_IN_A_BLOCK ) - ( m_pHCB->data_size + (long long int) ( HEADER_CONTROL_BLOCK_SIZE ) ) );
        if( llNullCh < 0 ) { //DTEC_Else
            bRet = false;
        }
    }

    if( bRet == true ) {
        switch( m_enFileType ) {
            case E_EL_SCDT_IQ :
                // 읽을 파일의 헤더를 생략한다.
                sz_file = _lseek( destFileId, sizeof(SRxIQData), SEEK_SET );
                if( sz_file != sizeof(SRxIQData) ) { //DTEC_Else
                    bRet = false;
                }
                else {
                    uiWriteByte = MAX_OF_IQ_DATA * sizeof(SRxIQDataRGroup1);
                    for( i=0 ; i < numberofdata ; ++i ) {
                        iSize = _read( destFileId, (char *) & x.iqData[0], uiWriteByte );
                        if( iSize <= 0 ) {
                            break;
                        }
                        else {
                            TransferIQ( & x.iqData[0], iSize );
                            uiWrite = Write( & x.iqData[0], iSize );
                        }
                    }
                }
                break;

            case E_EL_SCDT_IF :
                _lseek( destFileId, 0L, SEEK_END );
#if defined(__linux__) || defined(__VXWORKS__)
                sz_file = 0;
                //sz_file = tell( destFileId );
#else
                sz_file = _tell( destFileId );
#endif

                _lseek( destFileId, 0L, SEEK_SET );

                // 읽을 파일의 헤더를 생략한다.
                if( sz_file > 36 * 1024 * 1024 ) {
                    sz_file = _lseek( destFileId, sizeof(SRxIFData), SEEK_SET );
                    if( sz_file != sizeof(SRxIFData) ) { //DTEC_Else
                        bRet = false;
                    }
                    else {
                        uiWriteByte = MAX_OF_IF_DATA * sizeof(SRxIFDataRGroupEEEI);
                        for( i=0 ; i < numberofdata ; ++i ) {
                            iSize = _read( destFileId, (char *) & x.ifData[0], uiWriteByte );
                            if( iSize <= 0 ) { //DTEC_Else
                                break;
                            }
                            else {
                                //TransferIF( & x.ifData[0], iSize );
                                uiWrite = Write( & x.ifData[0], iSize );
                            }
                        }
                    }
                }
                break;

            case E_EL_SCDT_PDW :
                // 읽을 파일의 헤더를 생략한다.
                if( destFileId != 0 ) {
                    sz_file = _lseek( destFileId, sizeof(SRxPDWData), SEEK_SET );
                    if( sz_file != sizeof(SRxPDWData) ) { //DTEC_Else
                        bRet = false;
                    }
                    else {
                        uiWriteByte = MAX_OF_PDW_DATA * sizeof(SRxPDWDataRGroup);
                        for( i=0 ; i < numberofdata ; ++i ) {
                            iSize = _read( destFileId, (char * )& x.pdwData[0], uiWriteByte );
                            if( iSize <= 0 ) { //DTEC_Else
                                break;
                            }
                            else {
                                iRecords = (int) ( iSize / sizeof(SRxPDWDataRGroup) );
                                TransferPDW2Record( & x.pdwData[0], iRecords );
                                iSize = iRecords * sizeof( S_EL_PDW_RECORDS );

                                if( g_enEndian == enBIG_ENDIAN ) {
                                    int i;
                                    for( i=0 ; i < iRecords ; ++i ) {
                                        CCommonUtils::swapByteOrder( m_pPDWRecords[i].dtoa );
                                        CCommonUtils::swapByteOrder( m_pPDWRecords[i].ddtoa );
                                        CCommonUtils::swapByteOrder( m_pPDWRecords[i].dfreq );
                                        CCommonUtils::swapByteOrder( m_pPDWRecords[i].dpw );
                                        CCommonUtils::swapByteOrder( m_pPDWRecords[i].dpa );
                                        CCommonUtils::swapByteOrder( m_pPDWRecords[i].ddoa );
                                    }
                                }
                                uiWrite = Write( m_pPDWRecords, iSize );
                            }
                        }
                    }
                }
                else {
                    // 각 항목별 최소/최대값 초기화
                    MakeInitMinMaxValue( m_MinMaxOfSubrecords );
                    
                    m_ullfirstTOA = m_pPDWData->pstPDW[0].ullTOA;
                    for( i=0 ; i < numberofdata ; i += MAX_OF_PDW_DATA ) {
                        if( numberofdata - i >= MAX_OF_PDW_DATA ) {
                            iRecords = MAX_OF_PDW_DATA;
                        }
                        else {
                            iRecords = numberofdata - i;
                        }
                        TransferPDW2Record( & m_pPDWData->pstPDW[i], iRecords );
                        iSize = iRecords * sizeof( S_EL_PDW_RECORDS );

                        if( g_enEndian == enBIG_ENDIAN ) {
                            int i;
                            for( i=0 ; i < iRecords ; ++i ) {
                                CCommonUtils::swapByteOrder( m_pPDWRecords[i].dtoa );
                                CCommonUtils::swapByteOrder( m_pPDWRecords[i].ddtoa );
                                CCommonUtils::swapByteOrder( m_pPDWRecords[i].dfreq );
                                CCommonUtils::swapByteOrder( m_pPDWRecords[i].dpw );
                                CCommonUtils::swapByteOrder( m_pPDWRecords[i].dpa );
                                CCommonUtils::swapByteOrder( m_pPDWRecords[i].ddoa );
                            }
                        }
                        uiWrite = Write( m_pPDWRecords, iSize );
                    }                    
                }

                uiWriteByte = MAX_OF_PDW_DATA * sizeof(S_EL_PDW_RECORDS);
                break;

// 		case E_EL_SCDT_PRF :
// 			iWriteByte = MAX_OF_PRF_TONE_DATA * sizeof(short);
// 			for( i=0 ; i < numberofdata ; ++i ) {
// 				iSize = _read( destFileId, & x.cbyte, iWriteByte );
// 				if( iSize == 0 ) { //DTEC_Else
// 					break;
// 				}
// 				else
// 					iWrite = Write( & x.cbyte, iSize, 1 );
// 			}
// 			break;
//
// 		case E_EL_SCDT_SAMPLING :
// 			iWriteByte = MAX_OF_SAMPLING_DATA * sizeof(short);
// 			for( i=0 ; i < numberofdata ; ++i ) {
// 				iSize = _read( destFileId, & x.cbyte, iWriteByte );
// 				if( iSize == 0 ) { //DTEC_Else
// 					break;
// 				}
// 				else
// 					iWrite = Write( & x.cbyte, iSize, 1 );
// 			}
// 			break;

#ifdef _SP370_
            case E_EL_SCDT_PDW2SP370 :
                // 읽을 파일의 헤더를 생략한다.
                sz_file = _lseek( destFileId, sizeof(SRxPDWData), SEEK_SET );
                if( sz_file != sizeof(SRxPDWData) ) { //DTEC_Else
                    bRet = false;
                }
                else {
                    iWriteByte = MAX_OF_PDW_DATA * sizeof(SRxPDWDataRGroup);
                    for( i=0 ; i < numberofdata ; ++i ) {
                        uiSize = _read( destFileId, & x.pdwData[0], iWriteByte );
                        if( uiSize == 0 ) { //DTEC_Else
                            break;
                        }
                        else {
                            iRecords = iSize / sizeof(SRxPDWDataRGroup);
                            TransferPDW2SP370( & x.pdwData[0], iRecords );
                            uiSize = iRecords * sizeof( SELSP350_PDWWORDS );
                            uiWrite = Write( m_stPDWWord, uiSize, 1 );
                        }
                    }
                }
                break;
#endif

            case E_EL_SCDT_UNKNOWN :
            case E_EL_SCDT_SPECTRUM	:
            case E_EL_SCDT_LOB	:
            case E_EL_SCDT_PRF :
            case E_EL_SCDT_LOG :
            case E_EL_SCDT_ALL :					// 검색할 때 인자를 주기 위한 것
                {
                    //DTEC_Else
                }
                break;

            default :
                { //DTEC_Else

                }
                break;
        }


        if( bRet == true && m_enFileType != E_EL_SCDT_PDW2SP370 ) {
            if( bMultiIFData == false ) {
                char *pNullData;

                // 데이터와 NULL 문자 저장
                pNullData = ( char * ) malloc( sizeof(char) * uiWriteByte );
                if( pNullData != NULL ) {
                    memset( pNullData, 0, uiWriteByte );
                    //printf( "\nuiWriteByte=%d", uiWriteByte );
                    do {
                    	//printf( "\n llNullCh[%lld, %lld]" , llNullCh, llNullCh-(long long int) uiWriteByte );
                        if( llNullCh-(long long int) uiWriteByte > (long long int ) 0 ) { //DTEC_Else
                            llNullCh -= (long long int) Write( pNullData, uiWriteByte );
                        }
                        else {
                            llNullCh -= (long long int) Write( pNullData, (int) llNullCh );
                        }
                    } while( llNullCh > (long long int) 0 );

                    free( pNullData );
                }
                else {

                }
            }
        }
    }

    return bRet;

}

/**
 * @brief     PDW 구조체를 PDW 레코드로 변환한다.
 * @param     *pS_EL_PDW_DATA 변환할 PDW 데이터
 * @param     iRecords 레코드 갯수, 즉 PDW 갯수
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-07-16, 오전 10:54
 * @warning
 */
void CMIDASBlueFileFormat::TransferPDW2Record( SRxPDWDataRGroup *pS_EL_PDW_DATA, int iRecords )
{
    long long int pre_TOA=0, dtoa=0;
    S_EL_PDW_RECORDS *pPDWRecords;

    // 각 항목별 최소/최대값 초기화
    MakeInitMinMaxValue( m_MinMaxOfSubrecords );

    pPDWRecords = m_pPDWRecords;
    for( int i=0 ; i < iRecords ; ++i ) {
#ifdef __linux__
#else
        //AllEndian64( & pS_EL_PDW_DATA->llTOA, sizeof(long long int) );
        //AllEndian32( & pS_EL_PDW_DATA->iSignalType, sizeof(SRxPDWDataRGroup)- sizeof(long long int) );

// 		if( i != 0 ) {
// 			dtoa = pS_EL_PDW_DATA->llTOA - pre_TOA;
// 		}
//
// 		pPDWRecords->doa = ELDecoder::DecodeAOA( pS_EL_PDW_DATA->iDirection );					// [도]
// 		MakeMinMaxValue( & m_MinMaxOfSubrecords[enDOAOfSub], pPDWRecords->doa );
//
//         pPDWRecords->lfreq = (long double) ( ELDecoder::DecodeFrq( pS_EL_PDW_DATA->iFreq ) * 1000 );		// [Hz]
// 		MakeMinMaxValue( & m_MinMaxOfSubrecords[enFreqOfSub], pPDWRecords->lfreq );
//
// 		pPDWRecords->pa = ELDecoder::DecodePA( pS_EL_PDW_DATA->iPA );										// [dBm]
// 		MakeMinMaxValue( & m_MinMaxOfSubrecords[enPAOfSub], pPDWRecords->pa );
//
// 		pPDWRecords->pw = (float) ( ELDecoder::DecodePW( pS_EL_PDW_DATA->iPW ) / 1000000000. );			// [s]
// 		MakeMinMaxValue( & m_MinMaxOfSubrecords[enPWOfSub], pPDWRecords->pw );
//
// 		pPDWRecords->toa = (float) ( ELDecoder::DecodeToa( pS_EL_PDW_DATA->llTOA ) / 1000000000. );	// [s]
// 		MakeMinMaxValue( & m_MinMaxOfSubrecords[enTOAOfSub], pPDWRecords->toa );
//
//         pPDWRecords->ldtoa = (long double) ( ELDecoder::DecodeToa( dtoa ) / 1000000000. );									// [s]
// 		MakeMinMaxValue( & m_MinMaxOfSubrecords[enDTOAOfSub], pPDWRecords->ldtoa );
#endif

        pre_TOA = pS_EL_PDW_DATA->ullTOA;

        ++ pPDWRecords;
        ++ pS_EL_PDW_DATA;
    }
}

/**
 * @brief CMIDASBlueFileFormat::TransferPDW2Record
 * @param pS_EL_PDW_DATA
 * @param iRecords
 */
void CMIDASBlueFileFormat::TransferPDW2Record( _PDW *pS_EL_PDW_DATA, int iRecords )
{
    _TOA pre_TOA=0, dtoa=0;

    S_EL_PDW_RECORDS *pPDWRecords;

    pPDWRecords = m_pPDWRecords;
    for( int i=0 ; i < iRecords ; ++i ) {
        if( i != 0 ) {
            dtoa = pS_EL_PDW_DATA->ullTOA - pre_TOA;
        }

#ifdef _DECODE_
#ifdef _POCKETSONATA_
        pPDWRecords->ddoa = (double) CPOCKETSONATAPDW::DecodeDOA( pS_EL_PDW_DATA->uiAOA );

        pPDWRecords->dfreq = (double) ( CPOCKETSONATAPDW::DecodeFREQMHz( pS_EL_PDW_DATA->uiFreq ) * 1000000. );		// [Hz]

        pPDWRecords->dpa = (double) CPOCKETSONATAPDW::DecodePA( pS_EL_PDW_DATA->uiPA );										// [dBm]

        pPDWRecords->dpw = (double) ( CPOCKETSONATAPDW::DecodePW( pS_EL_PDW_DATA->uiPW ) / 1000000000. );			// [s]

        pPDWRecords->dtoa = CPOCKETSONATAPDW::DblDecodeTOA( pS_EL_PDW_DATA->ullTOA-m_ullfirstTOA );	// [s]

        pPDWRecords->ddtoa = 0;

#elif defined(_ELINT_) || defined(_XBAND_)
        pPDWRecords->ddoa = FAOACNV( pS_EL_PDW_DATA->uiAOA );

        pPDWRecords->dfreq = DFRQMhzCNV( 0, pS_EL_PDW_DATA->uiFreq ) * 1000000.;

        pPDWRecords->dpa = PACNV( pS_EL_PDW_DATA->uiPA );										// [dBm]

        pPDWRecords->dpw = DPWCNV( pS_EL_PDW_DATA->uiPW );			// [s]

        pPDWRecords->dtoa = (float) ( pS_EL_PDW_DATA->ullTOA - m_ullfirstTOA );	// [s]

        pPDWRecords->ddtoa = 0;
#else
        pPDWRecords->ddoa = 0;
        pPDWRecords->dfreq = 0;
        pPDWRecords->dpa = 0;
        pPDWRecords->dpw = 0;
        pPDWRecords->dtoa = 0;
        pPDWRecords->ddtoa = 0;

#endif

#endif

        MakeMinMaxValue( & m_MinMaxOfSubrecords[enTOAOfSub], pPDWRecords->dtoa );
        MakeMinMaxValue( & m_MinMaxOfSubrecords[enDTOAOfSub], pPDWRecords->ddtoa );
        MakeMinMaxValue( & m_MinMaxOfSubrecords[enDOAOfSub], pPDWRecords->ddoa );
        MakeMinMaxValue( & m_MinMaxOfSubrecords[enFreqOfSub], pPDWRecords->dfreq );
        MakeMinMaxValue( & m_MinMaxOfSubrecords[enPAOfSub], pPDWRecords->dpa );
        MakeMinMaxValue( & m_MinMaxOfSubrecords[enPWOfSub], pPDWRecords->dpw );

        pre_TOA = pS_EL_PDW_DATA->ullTOA;

        ++ pPDWRecords;
        ++ pS_EL_PDW_DATA;
    }
}

/**
 * @brief 최소/최대 범위를 입력한다.
 * @param pSEL_MIN_MAX
 * @param dValue
 */
void CMIDASBlueFileFormat::MakeMinMaxValue( SEL_MIN_MAX *pSEL_MIN_MAX, double dValue )
{
    pSEL_MIN_MAX->fMinVal = _min( pSEL_MIN_MAX->fMinVal, (float) dValue );
    pSEL_MIN_MAX->fMaxVal = _max( pSEL_MIN_MAX->fMaxVal, (float) dValue );

}

/**
 * @brief 구조체의 초기값으로 설정한다.
 * @param pSEL_MIN_MAX
 */
void CMIDASBlueFileFormat::MakeInitMinMaxValue( SEL_MIN_MAX *pSEL_MIN_MAX )
{
    int i;

    for( i=0 ; i < MAX_SUBRECORDS_OF_PDWDATA ; ++i ) {
        //pSEL_MIN_MAX->fMinVal = (float) +999999999999999.9;
        //pSEL_MIN_MAX->fMaxVal = (float) -999999999999999.9;

        pSEL_MIN_MAX->fMinVal = FLT_MAX;
        pSEL_MIN_MAX->fMaxVal = FLT_MIN;

        ++ pSEL_MIN_MAX;
    }
}

/**
 * @brief     파일 서버의 저장된 IQ 데이터를 MIDAS IQ 데이터 포멧으로 변환한다.
 * @param     *pSRxIQDataRGroup IQ 데이터
 * @param     int iByte 읽은 바이트 갯수
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-07-25, 오후 4:47
 * @warning
 */
void CMIDASBlueFileFormat::TransferIQ( SRxIQDataRGroup1 *pSRxIQDataRGroup, int iByte )
{
    unsigned short temp;

    for( int i=0 ; i < (int) ( iByte / sizeof( SRxIQDataRGroup1 ) ) ; ++i ) {
#ifdef __linux__
#else
        //AllEndian16( pSRxIQDataRGroup, sizeof(SRxIQDataRGroup) );
#endif

        temp = pSRxIQDataRGroup->sIData;
        pSRxIQDataRGroup->sIData = pSRxIQDataRGroup->sQData;
        pSRxIQDataRGroup->sQData = temp;

        ++ pSRxIQDataRGroup;
    }

}

/**
 * @brief     파일 서버의 저장된 IF 데이터를 MIDAS IF 데이터 포멧으로 변환한다.
 * @param     *SRxIFDataRGroupEEEI IF 데이터
 * @param     int iByte 읽은 바이트 갯수
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-07-25, 오후 5:00
 * @warning
 */
void CMIDASBlueFileFormat::TransferIF( SRxIFDataRGroupEEEI *pSRxIFDataRGroup, int iByte )
{

    for( unsigned int i=0 ; i < iByte / sizeof( SRxIFDataRGroupEEEI ) ; ++i ) {
        pSRxIFDataRGroup->sIData = pSRxIFDataRGroup->sIData ^ XOR_I_DATA;
        pSRxIFDataRGroup->sQData = pSRxIFDataRGroup->sQData ^ XOR_Q_DATA;

        ++ pSRxIFDataRGroup;
    }

}

/**
 * @brief     데이터 포멧에 따라 데이터 사이지를 리턴한다.
 * @param     void
 * @return    int
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2015-03-24, 오전 10:11
 * @warning
 */
int CMIDASBlueFileFormat::GetSampleSize()
{
    int iRet;

    if( m_enFileType == E_EL_SCDT_IQ || m_enFileType == E_EL_SCDT_IF ) {
        iRet = 16;
    }
    else if( m_enFileType == E_EL_SCDT_PDW ) {
        iRet = 0;
    }
    else {
        iRet = 0;
    }

// 	switch( m_enFileType ) {
// 		case E_EL_SCDT_IQ :
// 		case E_EL_SCDT_IF :
// 			iRet = 16;
//
// 		case E_EL_SCDT_PDW :
// 			iRet = 0;
//
// 		default :
// 			{ //DTEC_Else
// 				iRet = 0;
// 			}
// 			break;
// 	}

    return iRet;

}

/*!
 * @brief     MIDAS 포멧의 헤더 정보를 기록한다.
 * @return    리턴값 없음
 * @param     void
 * @version   1.0
 * @author    조철희
 * @date      2014-11-22 오후 8:52
 * @warning
 */
void CMIDASBlueFileFormat::MakeHeader()
{
    m_uiSizeOfExtend = EXTENDED_HEADER_SIZE;

    if( m_enFileType == E_EL_SCDT_PDW2SP370 ) {
#ifdef __linux__
#else
        //CPDW2SP370::Init();
        //CPDW2SP370::MakeHeader();
#endif
    }
    else {
        SELMIDAS_HCB *pHCB;

        pHCB = ( SELMIDAS_HCB * ) m_pHCB;

        if( m_enFileType == E_EL_SCDT_PDW ) {
            m_uiSizeOfExtend = 2 * EXTENDED_HEADER_SIZE;
        }
        else if( m_enFileType == E_EL_SCDT_IF ) {
#ifdef _EXT_HEADER_
            m_uiSizeOfExtend = 2 * EXTENDED_HEADER_SIZE;
#endif
            m_uiSizeOfExtend = 0x0600;
        }
        else {

        }

        memset( pHCB, 0, sizeof(char)*HEADER_CONTROL_BLOCK_SIZE );

        // 버젼 정보
        memcpy( pHCB->version, "BLUE", 4);

        // 헤더 정보
        memcpy( pHCB->head_rep, "EEEI", 4);

        // 데이터 정보
        memcpy( pHCB->data_rep, "EEEI", 4);

        // 첨부 플레그
        //pHCB->detached = 0;						// 파일 자체에 데이터 파일이 있음.

        // protected
        pHCB->_protected = 1;					// 읽기 모드(수정 불가)

        // pipe
        pHCB->pipe = 0;								// pipe 파일 안 함.

        // Extended header의 시작 번지 (512byte*N)
        pHCB->ext_start = CalcExtStart();					// 데이터를 쓰고나서 / 512를 나눈 값으로 설정함.

        // Extended header의 크기
        pHCB->ext_size = m_uiSizeOfExtend;	// extended header 길이를 바이트 단위로 기록한다.

        // 데이터 시작
        pHCB->data_start = (double) HEADER_CONTROL_BLOCK_SIZE;		// 데이터 시작 번지, bytes

        // 데이터 크기
        pHCB->data_size = CalcDataSize();					// 데이터 길이, bytes

        if( m_enFileType == E_EL_SCDT_IQ || m_enFileType == E_EL_SCDT_IF ) {
            // 타입
            pHCB->type = MIDAS_FILE_TYPE_1001;

            // 데이터 포멧
            pHCB->format[0] = DATA_FORMAT_SIZE_DESIGNATOR_COMPLEX;
            pHCB->format[1] = DATA_FORMAT_TYPE_DESIGNATOR_16BIT_INTEGER;

        }
        else if( m_enFileType == E_EL_SCDT_PDW ) {
            // 타입
            pHCB->type = MIDAS_FILE_TYPE_6003;

            // 데이터 포멧
            pHCB->format[0] = DATA_FORMAT_SIZE_DESIGNATOR_SCALR;
            pHCB->format[1] = DATA_FORMAT_TYPE_DESIGNATOR_32BIT_FLOAT;
        }
        else { //DTEC_Else
            pHCB->type = MIDAS_FILE_TYPE_1001;

            // 데이터 포멧
            pHCB->format[0] = DATA_FORMAT_SIZE_DESIGNATOR_SCALR;
            pHCB->format[1] = DATA_FORMAT_TYPE_DESIGNATOR_16BIT_INTEGER;
        }

        // flagmask
        pHCB->flagmask = 0;

        // timecode
        pHCB->timecode = 0.0;

        // in_byte
        pHCB->in_byte = 0.0;

        // out_byte
        pHCB->out_byte = 0.0;

        // out_bytes
        memset( pHCB->outbytes, 0, sizeof( pHCB->outbytes ) );

        //////////////////////////////////////////////////////////////////////////
        // 키워드
        // 버젼, IO 등 기록하기
        memset( pHCB->keywords, 0, sizeof( pHCB->keywords ) );

        unsigned int c = 0;
        if( m_strKeywordValue.writer_version[0] == 0 ) {
            c += sprintf( & pHCB->keywords[c], "VER=%s" , DEFAULT_HEADER_VER );
        }
        else {
            c += sprintf( & pHCB->keywords[c], "VER=%s" , m_strKeywordValue.writer_version );
        }
        c += 1;

        if( m_strKeywordValue.writer[0] == 0 ) {
            c += sprintf( & pHCB->keywords[c], "IO=%s" , DEFAULT_WRITER_VALUE );
        }
        else {
            c += sprintf( & pHCB->keywords[c], "IO=%s" , m_strKeywordValue.writer );
        }
        c += 1;

        // IQ 데이터에 대해서만 최소, 최대 값을 적어 넣음
        // IQ 키워드
        if( m_enFileType == E_EL_SCDT_IQ || m_enFileType == E_EL_SCDT_IF ) {
            short minval=-32767, maxval=0x7FFF;
            c += sprintf( & pHCB->keywords[c], "MINVAL=%+d" , minval );
            c += 1;
            c += sprintf( & pHCB->keywords[c], "MAXVAL=%+d" , maxval );
            c += 1;
        }

        unsigned int uiSize= sizeof( pHCB->keywords ) - c;
        if( uiSize <= sizeof(pHCB->keywords) ) {
            memset( & pHCB->keywords[c], 0, uiSize );
        }

        // 키워드 길이; keylength
        pHCB->uiKeylength = c;
    }

}

/**
 * @brief     데이터 사이즈를 리턴한다.
 * @param     void
 * @return    double
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2015-03-04, 오후 2:19
 * @warning
 */
double CMIDASBlueFileFormat::CalcDataSize()
{
    double data_size = HEADER_CONTROL_BLOCK_SIZE;

    if( m_enFileType == E_EL_SCDT_IQ ) {
        data_size = m_strKeywordValue.numberofdata * sizeof( SRxIFDataRGroupEEEI );
    }
    else if( m_enFileType == E_EL_SCDT_IF ) {
        data_size = m_strKeywordValue.numberofdata * sizeof( SRxIFDataRGroupEEEI );
        // data_size = m_vecConvertIFList.size() * data_size;
    }
    else if( m_enFileType == E_EL_SCDT_PDW ) {
        data_size = m_strKeywordValue.numberofdata * sizeof( S_EL_PDW_RECORDS );
    }
    else { //DTEC_Else
        data_size = 0;
    }

    return data_size;
}

/**
 * @brief     exr_start의 값을 포멧에 따라 정의한다.
 * @param     void
 * @return    unsigned int
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2015-03-04, 오후 2:19
 * @warning
 */
unsigned int CMIDASBlueFileFormat::CalcExtStart()
{
    unsigned int ret_ext_start=0;
    unsigned int ext_start = HEADER_CONTROL_BLOCK_SIZE;

    if( m_enFileType == E_EL_SCDT_IQ ) {
        ext_start += ( m_strKeywordValue.numberofdata * 2 * sizeof(short) );
    }
    else if( m_enFileType == E_EL_SCDT_IF ) {
        ext_start += ( m_strKeywordValue.numberofdata * m_vecConvertIFList.size() * sizeof(SRxIFDataRGroupEEEI) );
    }
    else if( m_enFileType == E_EL_SCDT_PDW ) {
        ext_start += ( m_strKeywordValue.numberofdata * sizeof( S_EL_PDW_RECORDS ) );
    }
    else { //DTEC_Else
        ext_start += 0;
    }

    ret_ext_start = ext_start / BYTE_IN_A_BLOCK;
    if( ext_start % BYTE_IN_A_BLOCK != 0 ) {
        ++ ret_ext_start;
    }

    return ret_ext_start;
}

/**
 * @brief     Adjunct 포멧에 데이터를 기록한다.
 * @param     void
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2014-11-26, 오후 2:19
 * @warning
 */
void CMIDASBlueFileFormat::MakeAdjunct()
{
    char *pByte;
    int nOffset, iOffset;

    SELMIDAS_ADJUNCT_TYPE_1000 *pAdjunct1000;
    SELMIDAS_ADJUNCT_TYPE_6000 *pAdjunct6000;
    SELSUBRECORDS *pSubRecords;

    pByte = ( char * ) m_pHCB;

    switch( m_enFileType ) {
        case E_EL_SCDT_UNKNOWN :
        case E_EL_SCDT_PDW2SP370 :
        case E_EL_SCDT_SPECTRUM	:
        case E_EL_SCDT_LOB	:
        case E_EL_SCDT_PRF :
        case E_EL_SCDT_LOG :
        case E_EL_SCDT_ALL :					// 검색할 때 인자를 주기 위한 것
            {
                //DTEC_Else
            }
            break;

        case E_EL_SCDT_IQ :
        case E_EL_SCDT_IF :
            pAdjunct1000 = ( SELMIDAS_ADJUNCT_TYPE_1000 * ) & pByte[0x100];

            // xstart
            pAdjunct1000->xstart = 0.0;

            // xdelta, 샘플링 타임
            if( m_strKeywordValue.dSamplingPeriod > 0.0 || m_strKeywordValue.dSamplingPeriod < 0.0 ) {
                // pAdjunct1000->xdelta = 1000000. / m_strKeywordValue.dSamplingPeriod;
                pAdjunct1000->xdelta = m_strKeywordValue.dSamplingPeriod;
            }
            else { //DTEC_Else
                pAdjunct1000->xdelta = 1000000. / DEFAULT_SAMPLINGRATE_VALUE;
            }

            // xunits
            pAdjunct1000->xunits = GetValueUnits();
            break;

        case E_EL_SCDT_PDW :
            pAdjunct6000 = ( SELMIDAS_ADJUNCT_TYPE_6000 * ) & pByte[0x100];

            pAdjunct6000->rstart = 0.0;
            pAdjunct6000->rdelta = 1 * 10.0e-10;
            pAdjunct6000->runits = VALUE_UNITS_TIME;
            pAdjunct6000->subrecords = MAX_SUBRECORDS_OF_PDWDATA;
            pAdjunct6000->r2start = 0.0;
            pAdjunct6000->r2delta = pAdjunct6000->rdelta; // 1.0e-010;
            pAdjunct6000->r2units = VALUE_UNITS_TIME;
            pAdjunct6000->record_length = sizeof(S_EL_PDW_RECORDS);

            // SUBRECORDS 초기화
            pSubRecords = ( SELSUBRECORDS * ) & pAdjunct6000[1];
            pSubRecords->offset = 0;
            nOffset = 0;

            // 주파수 SUBRECORDS 입력
            iOffset = MakeSubRecords( pSubRecords, stSubrecordName[0], DATA_FORMAT_SIZE_DESIGNATOR_SCALR, DATA_FORMAT_TYPE_DESIGNATOR_64BIT_FLOAT, nOffset );
            nOffset += iOffset;
            ++ pSubRecords;

            // TOA SUBRECORDS 입력
            iOffset += MakeSubRecords( pSubRecords, stSubrecordName[1], DATA_FORMAT_SIZE_DESIGNATOR_SCALR, DATA_FORMAT_TYPE_DESIGNATOR_64BIT_FLOAT, nOffset );
            nOffset += iOffset;
            ++ pSubRecords;

            // DOA SUBRECORDS 입력
            iOffset += MakeSubRecords( pSubRecords, stSubrecordName[2], DATA_FORMAT_SIZE_DESIGNATOR_SCALR, DATA_FORMAT_TYPE_DESIGNATOR_64BIT_FLOAT, nOffset );
            nOffset += iOffset;
            ++ pSubRecords;

            // PW SUBRECORDS 입력
            iOffset += MakeSubRecords( pSubRecords, stSubrecordName[3], DATA_FORMAT_SIZE_DESIGNATOR_SCALR, DATA_FORMAT_TYPE_DESIGNATOR_64BIT_FLOAT, nOffset );
            nOffset += iOffset;
            ++ pSubRecords;

            // PA SUBRECORDS 입력
            iOffset += MakeSubRecords( pSubRecords, (char *) stSubrecordName[4], DATA_FORMAT_SIZE_DESIGNATOR_SCALR, DATA_FORMAT_TYPE_DESIGNATOR_64BIT_FLOAT, nOffset );
            nOffset += iOffset;
            ++ pSubRecords;

            // DTOA SUBRECORDS 입력
            MakeSubRecords( pSubRecords, (char *) stSubrecordName[5], DATA_FORMAT_SIZE_DESIGNATOR_SCALR, DATA_FORMAT_TYPE_DESIGNATOR_64BIT_FLOAT, nOffset );
            //++ ioffset;
            //++ pSubRecords;
            break;

        default :
            { //DTEC_Else

            }
            break;
    }

}

/**
 * @brief     PDW 데이터의 SUBRECORDS 값을 입력한다.
 * @param     SELSUBRECORDS * pSubRecords
 * @param     char * pName
 * @param     unsigned char data_type1
 * @param     unsigned char data_type2
 * @param     int iOffset
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-07-16, 오전 9:48
 * @warning
 */
int CMIDASBlueFileFormat::MakeSubRecords( SELSUBRECORDS *pSubRecords, const char *pName, unsigned char data_type1, unsigned char data_type2, int nOffset )
{
    int offset;

    memset( pSubRecords->name, 0, 4 );
    memcpy( pSubRecords->name, pName, strnlen_s( pName, 100 ) );
    pSubRecords->format[0] = data_type1;
    pSubRecords->format[1] = data_type2;

    pSubRecords->offset = nOffset;

    switch( data_type2 ) {
    case DATA_FORMAT_TYPE_DESIGNATOR__8BIT_INTEGER :
        offset = 1;
        break;

    case DATA_FORMAT_TYPE_DESIGNATOR_16BIT_INTEGER :
        offset = 2;
        break;

    case DATA_FORMAT_TYPE_DESIGNATOR_32BIT_FLOAT :
        offset = 4;
        break;

    case DATA_FORMAT_TYPE_DESIGNATOR_64BIT_INTEGER :
    case DATA_FORMAT_TYPE_DESIGNATOR_64BIT_FLOAT :
        offset = 8;
        break;

    default :
        offset = 4;
        break;

    }

    return offset;

}

/**
 * @brief     데이터 포멧에 따라 값을 리턴한다.
 * @param     void
 * @return    unsigned int
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2014-11-26, 오후 5:37
 * @warning
 */
unsigned int CMIDASBlueFileFormat::GetValueUnits()
{
    unsigned int bRet;

    if( m_enFileType == E_EL_SCDT_IQ ) {
        bRet = VALUE_UNITS_TIME;
    }
    else if( m_enFileType == E_EL_SCDT_IF ) {
        bRet = VALUE_UNITS_TIME;
    }
    else if( m_enFileType == E_EL_SCDT_PDW ) {
        bRet = VALUE_UNITS_NONE;
    }
    else { //DTEC_Else
        bRet = VALUE_UNITS_NOT_APPLICABLE;
    }

    return bRet;
}

/**
 * @brief     헤더 구조체 정보를 기록한다.
 * @param     void
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2014-11-26, 오후 4:44
 * @warning
 */
int CMIDASBlueFileFormat::WriteHeader()
{
    int nWrite=0;

    if( m_enFileType == E_EL_SCDT_PDW2SP370 ) {
#ifdef __linux__
#else
        //nWrite = Write( & m_stPDWHeader, sizeof(SELSP350_PDWHEADER ), 1 );
#endif
    }
    else {
        if( g_enEndian == enLITTLE_ENDIAN ) {
            nWrite = Write( m_pHCB, sizeof(char)*HEADER_CONTROL_BLOCK_SIZE );
        }
        else {
            SELMIDAS_HCB m_HCB;

            memcpy( & m_HCB, m_pHCB, sizeof(SELMIDAS_HCB) );
            CCommonUtils::swapByteOrder( m_HCB.detached );
            CCommonUtils::swapByteOrder( m_HCB._protected );
            CCommonUtils::swapByteOrder( m_HCB.pipe );
            CCommonUtils::swapByteOrder( m_HCB.ext_start );
            CCommonUtils::swapByteOrder( m_HCB.ext_size );
            CCommonUtils::swapByteOrder( m_HCB.data_start );
            CCommonUtils::swapByteOrder( m_HCB.data_size );
            CCommonUtils::swapByteOrder( m_HCB.type );
            CCommonUtils::swapByteOrder( m_HCB.flagmask );
            CCommonUtils::swapByteOrder( m_HCB.timecode );
            CCommonUtils::swapByteOrder( m_HCB.inlet );
            CCommonUtils::swapByteOrder( m_HCB.outlets );
            CCommonUtils::swapByteOrder( m_HCB.outmaks );
            CCommonUtils::swapByteOrder( m_HCB.pipeloc );
            CCommonUtils::swapByteOrder( m_HCB.pipesize );
            CCommonUtils::swapByteOrder( m_HCB.in_byte );
            CCommonUtils::swapByteOrder( m_HCB.out_byte );
            CCommonUtils::swapByteOrder( m_HCB.outbytes, 8 );
            CCommonUtils::swapByteOrder( m_HCB.uiKeylength );

            size_t szSize = CCommonUtils::CheckMultiplyOverflow( sizeof(char), HEADER_CONTROL_BLOCK_SIZE );
            nWrite = Write( & m_HCB, szSize );
        }
    }
    return nWrite;
}

/**
 * @brief     Extended Header 포멧에 데이터를 기록한다.
 * @param     void
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2015-03-06, 17:01:25
 * @warning
 */
void CMIDASBlueFileFormat::MakeExtendedHeader()
{
    int c;
    char buffer[2129];
    char *pByte;

    tm tm_time={0};

#ifdef __linux__
    tm *p_tm_time;
#endif

    time_t time_tick=0, start_time;

    SELMIDAS_BINARY_KEYWORD *pBinKeyword;

    long double dTimeTag=0.;

    double dValue;

    if( m_strKeywordValue.tiTime == 0 ) { //DTEC_Else
#ifdef __linux__
        p_tm_time = localtime( & time_tick );
        memcpy( & tm_time, p_tm_time, sizeof(tm) );
#else
        localtime_s( & tm_time, & time_tick );
#endif

        start_time = mktime( & tm_time );
        dTimeTag = (long double) ( difftime( time_tick, start_time ) * 10000000000. );
    }
    else {
#ifdef __linux__
        p_tm_time = localtime( & m_strKeywordValue.tiTime );
        memcpy( & tm_time, p_tm_time, sizeof(tm) );
#else
        localtime_s( & tm_time, & m_strKeywordValue.tiTime );
#endif
        tm_time.tm_hour = 0;
        tm_time.tm_min = 0;
        tm_time.tm_sec = 0;
        start_time = mktime( & tm_time );
        dTimeTag = (long double) ( difftime( m_strKeywordValue.tiTime, start_time ) * 10000000000. );
    }

    if( m_enFileType != E_EL_SCDT_PDW2SP370 ) {
        time_tick = time( NULL );

        //m_pExtendOfHeader = new byte[m_SizeOfExtend];
        m_pExtendOfHeader = ( unsigned char * ) malloc( m_uiSizeOfExtend );

        if( m_pExtendOfHeader != NULL ) {
            memset( m_pExtendOfHeader, 0, sizeof( char ) * m_uiSizeOfExtend );

            // Extended Header 구조체 초기화
            pBinKeyword = ( SELMIDAS_BINARY_KEYWORD * ) & m_pExtendOfHeader[0];

            // CLASSIFICATION
            // keyword, value 저장
            if( m_enFileType == E_EL_SCDT_PDW ) {
                pBinKeyword = MakeSetBinaryKeyword( pBinKeyword, (char *) "SECRETCLASSIFICATION", (char *) "CLASSIFICATION" );

                pBinKeyword = MakeSetBinaryKeyword( pBinKeyword, (char *) "UNTAGGEDFUNCTIONS_VALUES", (char *) "FUNCTIONS_VALUES" );

                pBinKeyword = MakeSetBinaryKeyword( pBinKeyword, (char *) "PLATINUMIO", (char *) "IO" );

                pBinKeyword = MakeSetBinaryKeyword( pBinKeyword, (char *) "jpluto/ASPENIOVERSION", (char *) "IOVERSION" );

                //pBinKeyword = MakeSetBinaryKeyword( pBinKeyword, "UNTAGGEDSIGNAL_VALUES", "SIGNAL_VALUES" );

            }
            else {
                pBinKeyword = MakeSetBinaryKeyword( pBinKeyword, (char *) "UNCLASSIFIEDCLASSIFICATION", (char *)"CLASSIFICATION" );

                // WRITER
                sprintf( buffer, "%sWRITER" , DEFAULT_WRITER_VALUE );
                pBinKeyword = MakeSetBinaryKeyword( pBinKeyword, buffer, (char *) "WRITER" );

                // WRITER_VERSION
                if( m_strKeywordValue.writer_version[0] == 0 ) {
                    sprintf( buffer, "%sWRITER_VERSION" , DEFAULT_WRITER_VERSION_VALUE );
                }
                else {  //DTEC_Else
                    sprintf( buffer, "%sWRITER1_VERSION" , m_strKeywordValue.writer_version );
                }
                pBinKeyword = MakeSetBinaryKeyword( pBinKeyword, buffer, (char *) "WRITER_VERSION" );

                // COLLECTOR
                if( m_strKeywordValue.collector[0] == 0 ) {
                    sprintf( buffer, "%sCOLLECTOR" , DEFAULT_COLLECTOR_VALUE );
                }
                else { //DTEC_Else
                    sprintf( buffer, "%sCOLLECTOR" , m_strKeywordValue.collector );
                }
                pBinKeyword = MakeSetBinaryKeyword( pBinKeyword, buffer, (char *) "COLLECTOR" );

                // FEED
                if( m_strKeywordValue.feed[0] == 0 ) {
                    c = sprintf( buffer, "%sFEED" , DEFAULT_FEED_VALUE );
                }
                else { //DTEC_Else
                    c = sprintf( buffer, "%sFEED" , m_strKeywordValue.feed );
                }
                pBinKeyword = MakeSetBinaryKeyword( pBinKeyword, buffer, (char *) "FEED" );

                // SIGNAL_ID
                if( m_strKeywordValue.signal_id[0] == 0 ) {
                    c = sprintf( buffer, "%sSIGNAL_ID" , DEFAULT_SIGNAL_ID_VALUE );
                }
                else { //DTEC_Else
                    c = sprintf( buffer, "%sSIGNAL_ID" , m_strKeywordValue.signal_id );
                }
                pBinKeyword = MakeSetBinaryKeyword( pBinKeyword, buffer, (char *) "SIGNAL_ID" );

                // NOTES
                if( m_strKeywordValue.notes[0] == 0 ) {
                    sprintf( buffer, "%sNOTES" , DEFAULT_NOTES_VALUE );
                }
                else { //DTEC_Else
                    sprintf( buffer, "%sNOTES" , m_strKeywordValue.notes );
                }
                pBinKeyword = MakeSetBinaryKeyword( pBinKeyword, buffer, (char *) "NOTES" );

                // TIME_EPOCH
                if( m_strKeywordValue.tiTime == 0 ) { //DTEC_Else
#ifdef __linux__
                    p_tm_time = localtime( & time_tick );
                    memcpy( & tm_time, p_tm_time, sizeof(tm) );
#else
                    localtime_s( & tm_time, & time_tick );
#endif
                }
                else {
#ifdef __linux__
                    p_tm_time = localtime( & time_tick );
                    memcpy( & tm_time, p_tm_time, sizeof(tm) );
#else
                    localtime_s( & tm_time, & m_strKeywordValue.tiTime );
#endif
                }
                sprintf( buffer, (char *) "%4d-%02d-%02dT00:00:00TIME_EPOCH" , tm_time.tm_year+1900, tm_time.tm_mon+1, tm_time.tm_mday );
                pBinKeyword = MakeSetBinaryKeyword( pBinKeyword, buffer, (char *) "TIME_EPOCH" );

                // TIME_DELTA
                pBinKeyword = MakeValueBinaryKeyword( pBinKeyword, (long double) 1.0e-010, (char *) "TIME_DELTA", DATA_FORMAT_TYPE_DESIGNATOR_64BIT_FLOAT );

                // TIMETAG.OFFSET
                pBinKeyword = MakeValueBinaryKeyword( pBinKeyword, (long double) 0, (char *) "TIMETAG.OFFSET", DATA_FORMAT_TYPE_DESIGNATOR_64BIT_INTEGER );

                // TIMETAG.TIME
                pBinKeyword = MakeValueBinaryKeyword( pBinKeyword, dTimeTag, (char *) "TIMETAG.TIME", DATA_FORMAT_TYPE_DESIGNATOR_64BIT_INTEGER );
            }

            // ACQDATE
            if( m_strKeywordValue.tiTime == 0 ) { //DTEC_Else
#ifdef __linux__
                    p_tm_time = localtime( & time_tick );
                    memcpy( & tm_time, p_tm_time, sizeof(tm) );
#else
                    localtime_s( & tm_time, & time_tick );
#endif
            }
            else {
#ifdef __linux__
                    p_tm_time = localtime( & m_strKeywordValue.tiTime );
                    memcpy( & tm_time, p_tm_time, sizeof(tm) );
#else
                    localtime_s( & tm_time, & m_strKeywordValue.tiTime );
#endif
            }
            c = sprintf( buffer, (char *)"%4d%02d%02dACQDATE" , tm_time.tm_year+1900, tm_time.tm_mon+1, tm_time.tm_mday );
            pBinKeyword = MakeSetBinaryKeyword( pBinKeyword, buffer, (char *) "ACQDATE" );

            // ACQTIME
            if( m_strKeywordValue.tiTime == 0 ) { //DTEC_Else
#ifdef __linux__
                    p_tm_time = localtime( & time_tick );
                    memcpy( & tm_time, p_tm_time, sizeof(tm) );
#else
                    localtime_s( & tm_time, & time_tick );
#endif
            }
            else {
#ifdef __linux__
                    p_tm_time = localtime( & m_strKeywordValue.tiTime );
                    memcpy( & tm_time, p_tm_time, sizeof(tm) );
#else
                    localtime_s( & tm_time, & m_strKeywordValue.tiTime );
#endif

            }
            c = sprintf( buffer, (char *)"%02d:%02d:%02dACQTIME" , tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec );
            pBinKeyword = MakeSetBinaryKeyword( pBinKeyword, buffer, (char *) "ACQTIME" );

            // 메타 파일 종류에 따른 extended_header 영역에 기록하기
            if( m_enFileType == E_EL_SCDT_PDW ) {
                unsigned int lkey;

                // SUBREC_DEF 키워드 추가
                c = MakeSubRecords();
                lkey = MakeBinaryKeyword( pBinKeyword, ( char *) m_pSubrecords, (char *) SUBREC_DEF, c, DATA_FORMAT_TYPE_DESIGNATOR_ASCII );
                //pBinKeyword = ( SELMIDAS_BINARY_KEYWORD * ) ( (char *) pBinKeyword + pBinKeyword->lkey );
                pByte = ( char * ) pBinKeyword;
                pBinKeyword = ( SELMIDAS_BINARY_KEYWORD * ) & pByte[lkey];

                // SUBREC_DESCRIP
                pBinKeyword = MakeSetBinaryKeyword( pBinKeyword, (char *) "TYPE0SUBREC_DESCRIP", (char *) "SUBREC_DESCRIP" );

                // TIMETAG.OFFSET
                pBinKeyword = MakeValueBinaryKeyword( pBinKeyword, (long double) 0, (char *) "TIMETAG.OFFSET", DATA_FORMAT_TYPE_DESIGNATOR_64BIT_INTEGER );

                // TIMETAG.TIME
                pBinKeyword = MakeValueBinaryKeyword( pBinKeyword, (long double) 0, (char *) "TIMETAG.TIME", DATA_FORMAT_TYPE_DESIGNATOR_64BIT_FLOAT );

                // TIMETAG.TIME.UNITS
                pBinKeyword = MakeValueBinaryKeyword( pBinKeyword, (long double) VALUE_UNITS_TIME, (char *) "TIMETAG.UNITS", DATA_FORMAT_TYPE_DESIGNATOR_16BIT_INTEGER );

                // TIME_DELTA
                pBinKeyword = MakeValueBinaryKeyword( pBinKeyword, (long double) 1.0, (char *) "TIME_DELTA", DATA_FORMAT_TYPE_DESIGNATOR_64BIT_FLOAT );

                // TIME_EPOCH
                if( m_strKeywordValue.tiTime == 0 ) { //DTEC_Else
#ifdef __linux__
                    p_tm_time = localtime( & time_tick );
                    memcpy( & tm_time, p_tm_time, sizeof(tm) );
#else
                    localtime_s( & tm_time, & time_tick );
#endif
                }
                else {
#ifdef __linux__
                    p_tm_time = localtime( & m_strKeywordValue.tiTime  );
                    memcpy( & tm_time, p_tm_time, sizeof(tm) );
#else
                    localtime_s( & tm_time, & m_strKeywordValue.tiTime  );
#endif
                }
                c = sprintf( buffer, (char *) "%4d-%02d-%02dT00:00:00ZTIME_EPOCH" , tm_time.tm_year+1900, tm_time.tm_mon+1, tm_time.tm_mday );
                pBinKeyword = MakeSetBinaryKeyword( pBinKeyword, buffer, (char *) "TIME_EPOCH" );

                // TIME_TICKS
                pBinKeyword = MakeValueBinaryKeyword( pBinKeyword, (long double) 1, (char *) "TIME_TICKS", DATA_FORMAT_TYPE_DESIGNATOR_64BIT_INTEGER );

                // EVENT.DURATION
                long double dDuration = m_MinMaxOfSubrecords[enTOAOfSub].fMaxVal - m_MinMaxOfSubrecords[enTOAOfSub].fMinVal;
                pBinKeyword = MakeValueBinaryKeyword( pBinKeyword, (long double) dDuration, (char *) "EVENT.DURATION", DATA_FORMAT_TYPE_DESIGNATOR_64BIT_FLOAT );

                // EVENT.DURATION.UNITS
                pBinKeyword = MakeValueBinaryKeyword( pBinKeyword, (long double) VALUE_UNITS_TIME, (char *) "EVENT.DURATION.UNITS", DATA_FORMAT_TYPE_DESIGNATOR_16BIT_INTEGER );

                // EVENT.OFFSET
                pBinKeyword = MakeValueBinaryKeyword( pBinKeyword, (long double) 0, (char *) "EVENT.OFFSET", DATA_FORMAT_TYPE_DESIGNATOR_64BIT_INTEGER );

                // EVENT.TIME
                pBinKeyword = MakeValueBinaryKeyword( pBinKeyword, (long double) 0, (char *) "EVENT.TIME", DATA_FORMAT_TYPE_DESIGNATOR_64BIT_FLOAT );

                // EVENT.TIME.UNITS
                pBinKeyword = MakeValueBinaryKeyword( pBinKeyword, (long double) VALUE_UNITS_COUNTS, (char *) "EVENT.TIME.UNITS", DATA_FORMAT_TYPE_DESIGNATOR_16BIT_INTEGER );

            }
            else {
                // COL_RF
                pBinKeyword = MakeValueBinaryKeyword( pBinKeyword, (long double) m_strKeywordValue.dRF, (char *) "COL_RF", DATA_FORMAT_TYPE_DESIGNATOR_64BIT_FLOAT );

                // COL_RF_UNITS
                pBinKeyword = MakeValueBinaryKeyword( pBinKeyword, (long double) VALUE_UNITS_HZ, (char *) "COL_RF.UNITS", DATA_FORMAT_TYPE_DESIGNATOR__8BIT_INTEGER );

                // ACQETF (?)
                dValue = m_strKeywordValue.dRF;
                c = sizeof( dValue );
                memcpy( buffer, & dValue, sizeof(dValue) );
                c += sprintf( & buffer[sizeof(dValue)], (char *) "ACQETF" );
                MakeBinaryKeyword( pBinKeyword, buffer, (char *) "ACQETF", c, DATA_FORMAT_TYPE_DESIGNATOR_64BIT_FLOAT );
                //pBinKeyword = ( SELMIDAS_BINARY_KEYWORD * ) ( (char *) pBinKeyword + pBinKeyword->lkey );
                pByte = ( char * ) pBinKeyword;
                pBinKeyword = ( SELMIDAS_BINARY_KEYWORD * ) & pByte[pBinKeyword->lkey];

                // ACQETF.UNITS
                pBinKeyword = MakeValueBinaryKeyword( pBinKeyword, (long double) VALUE_UNITS_HZ, (char *) "ACQETF.UNITS", DATA_FORMAT_TYPE_DESIGNATOR__8BIT_INTEGER );

                // COL_BW
                pBinKeyword = MakeValueBinaryKeyword( pBinKeyword, (long double) m_strKeywordValue.dBW, (char *) "COL_BW", DATA_FORMAT_TYPE_DESIGNATOR_64BIT_FLOAT );

                // COL_BW.UNITS
                pBinKeyword = MakeValueBinaryKeyword( pBinKeyword, (long double) VALUE_UNITS_HZ, (char *) "COL_BW.UNITS", DATA_FORMAT_TYPE_DESIGNATOR__8BIT_INTEGER );

                // OUTPUT_IF
                pBinKeyword = MakeValueBinaryKeyword( pBinKeyword, (long double) 0, (char *) "OUTPUT_IF", DATA_FORMAT_TYPE_DESIGNATOR_64BIT_FLOAT );

                // OUTPUT_IF_UNITS
                pBinKeyword = MakeValueBinaryKeyword( pBinKeyword, (long double) VALUE_UNITS_HZ, (char *) "OUTPUT_IF.UNITS", DATA_FORMAT_TYPE_DESIGNATOR__8BIT_INTEGER );

                // SPECTRUM
                pBinKeyword = MakeValueBinaryKeyword( pBinKeyword, (long double) 0, (char *) "SPECTRUM", DATA_FORMAT_TYPE_DESIGNATOR__8BIT_INTEGER );

                // REC_BW
                pBinKeyword = MakeValueBinaryKeyword( pBinKeyword, (long double) ( 1. / m_strKeywordValue.dSamplingPeriod ), "REC_BW", DATA_FORMAT_TYPE_DESIGNATOR_64BIT_FLOAT );

                // REC_BW_UNITS
                pBinKeyword = MakeValueBinaryKeyword( pBinKeyword, (long double) VALUE_UNITS_HZ, (char *) "REC_BW.UNITS", DATA_FORMAT_TYPE_DESIGNATOR__8BIT_INTEGER );

                // COL_SAMPLE_RATE
                pBinKeyword = MakeValueBinaryKeyword( pBinKeyword, (long double) ( 1. / m_strKeywordValue.dSamplingPeriod ), "COL_SAMPLE_RATE", DATA_FORMAT_TYPE_DESIGNATOR_64BIT_FLOAT );

                // COL_SAMPLE_RATE_UNITS
                pBinKeyword = MakeValueBinaryKeyword( pBinKeyword, (long double) VALUE_UNITS_HZ, (char *) "COL_SAMPLE_RATE.UNITS", DATA_FORMAT_TYPE_DESIGNATOR__8BIT_INTEGER );

                // COL_SAMPLE_SIZE
                pBinKeyword = MakeValueBinaryKeyword( pBinKeyword, (long double) GetSampleSize(), (char *) "COL_SAMPLE_SIZE", DATA_FORMAT_TYPE_DESIGNATOR__8BIT_INTEGER );

                // GAIN_MODE
                pBinKeyword = MakeValueBinaryKeyword( pBinKeyword, (long double) ( m_strKeywordValue.gain_mode & 0x1 ), "GAIN_MODE", DATA_FORMAT_TYPE_DESIGNATOR__8BIT_INTEGER );

                // COL_GAIN : 기본값: 70
                pBinKeyword = MakeValueBinaryKeyword( pBinKeyword, (long double) m_strKeywordValue.dGain_value, (char *) "COL_GAIN", DATA_FORMAT_TYPE_DESIGNATOR_64BIT_FLOAT );

                // COL_GAIN.UNITS
                pBinKeyword = MakeValueBinaryKeyword( pBinKeyword, (long double) VALUE_UNITS_RELATIVE_POWER, (char *) "COL_GAIN.UNITS", DATA_FORMAT_TYPE_DESIGNATOR__8BIT_INTEGER );

                // COL_LOCKED_LO
                pBinKeyword = MakeValueBinaryKeyword( pBinKeyword, (long double) m_strKeywordValue.dLockedLO, (char *) "COL_LOCKED_LO", DATA_FORMAT_TYPE_DESIGNATOR_64BIT_FLOAT );

                // COL_LOCKED_LO.UNITS
                pBinKeyword = MakeValueBinaryKeyword( pBinKeyword, (long double) VALUE_UNITS_HZ, (char *) "COL_LOCKED_LO.UNITS", DATA_FORMAT_TYPE_DESIGNATOR__8BIT_INTEGER );

                // DATA_BANDWIDTH
                pBinKeyword = MakeValueBinaryKeyword( pBinKeyword, (long double) ( 1. / m_strKeywordValue.dSamplingPeriod ), (char *) "DATA_BANDWIDTH", DATA_FORMAT_TYPE_DESIGNATOR_64BIT_FLOAT );

                // DATA_BANDWIDTH.UNITS
                pBinKeyword = MakeValueBinaryKeyword( pBinKeyword, (long double) VALUE_UNITS_HZ, (char *) "DATA_BANDWIDTH.UNITS", DATA_FORMAT_TYPE_DESIGNATOR__8BIT_INTEGER );

                // EVENT.DURATION
                long double dDuration = m_vecConvertIFList.size() * ( 36. * 1024. * 1024. / 4. ) / 71110000.;
                pBinKeyword = MakeValueBinaryKeyword( pBinKeyword, (long double) dDuration, (char *) "EVENT.DURATION", DATA_FORMAT_TYPE_DESIGNATOR_64BIT_FLOAT );

                // EVENT.OFFSET
                pBinKeyword = MakeValueBinaryKeyword( pBinKeyword, (long double) 0, (char *) "EVENT.OFFSET", DATA_FORMAT_TYPE_DESIGNATOR_64BIT_INTEGER );

                // EVENT.TIME
                pBinKeyword = MakeValueBinaryKeyword( pBinKeyword, (long double) dTimeTag, (char *) "EVENT.TIME", DATA_FORMAT_TYPE_DESIGNATOR_64BIT_INTEGER );

                // EVENT.TIME.UNITS
                //pBinKeyword = MakeValueBinaryKeyword( pBinKeyword, (ULONGLONG) VALUE_UNITS_COUNTS, "EVENT.TIME.UNITS", DATA_FORMAT_TYPE_DESIGNATOR_16BIT_INTEGER );

                // MISSION
                pBinKeyword = MakeValueBinaryKeyword( pBinKeyword, (long double) m_strKeywordValue.mission, (char *) "MISSION", DATA_FORMAT_TYPE_DESIGNATOR_16BIT_INTEGER );

                // RECEIVER
                pBinKeyword = MakeValueBinaryKeyword( pBinKeyword, (unsigned long long) m_strKeywordValue.receiver, (char *) "RECEIVER", DATA_FORMAT_TYPE_DESIGNATOR__8BIT_INTEGER, 0x1d0 );
            }
        }
    }

}

/**
 * @brief     서브 레코드 구조체에 데이터를 구성한다. PDW 구조체에 적용한다.
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-07-21, 오후 5:00
 * @warning
 */
int CMIDASBlueFileFormat::MakeSubRecords()
{
    int i, c, iOffset=0;
    char buffer[100];
    SELMIDAS_SUBRECORDS *pSubrecords;

    pSubrecords = m_pSubrecords;
    memset( pSubrecords, 0, sizeof(SELMIDAS_SUBRECORDS) * MAX_SUBRECORDS_OF_PDWDATA );

    for( i=0 ; i < MAX_SUBRECORDS_OF_PDWDATA ; ++i ) {
        // 컬럼명
        memset( pSubrecords->name, 0x20, sizeof( pSubrecords->name ) );
        c = sprintf( buffer, (char *) "%s" , stSubrecordName[i] );
        memcpy( pSubrecords->name, buffer , strlen(buffer) );
        _PUT_ARRAY_VALUE( pSubrecords->name, c, 0x20 );

#ifdef __VXWORKS__
        // 최소 값
        memset( pSubrecords->minval, 0x20, sizeof( pSubrecords->minval ) );
        //c = sprintf( & pSubrecords->minval[0], stSubrecordFormat[i], m_MinMaxOfSubrecords[i].fMinVal );
        //_PUT_ARRAY_VALUE( pSubrecords->minval, c, 0x20 );

        // 최대 값
        memset( pSubrecords->maxval, 0x20, sizeof( pSubrecords->maxval ) );
        //c = sprintf( & pSubrecords->maxval[0], stSubrecordFormat[i], m_MinMaxOfSubrecords[i].fMaxVal );
        //_PUT_ARRAY_VALUE( pSubrecords->maxval, c, 0x20 );
#else
        // 최소 값
        memset( pSubrecords->minval, 0x20, sizeof( pSubrecords->minval ) );
        c = sprintf( & pSubrecords->minval[0], stSubrecordFormat[i], m_MinMaxOfSubrecords[i].fMinVal );
        _PUT_ARRAY_VALUE( pSubrecords->minval, c, 0x20 );

        // 최대 값
        memset( pSubrecords->maxval, 0x20, sizeof( pSubrecords->maxval ) );
        c = sprintf( & pSubrecords->maxval[0], stSubrecordFormat[i], m_MinMaxOfSubrecords[i].fMaxVal );
        _PUT_ARRAY_VALUE( pSubrecords->maxval, c, 0x20 );
#endif

        // 옵셋
        memset( pSubrecords->offset, 0x20, sizeof( pSubrecords->offset ) );
        c = sprintf( buffer, (char *) "%d" , iOffset );
        memcpy( pSubrecords->offset, buffer , strlen(buffer) );
        //pSubrecords->offset[c] = 0x20;
        _PUT_ARRAY_VALUE( pSubrecords->offset, c, 0x20 );

        // 엘리먼트 갯수
        c = sprintf( buffer, (char *) "%d" , 1 );
        memset( pSubrecords->num_elts, 0x20, sizeof( pSubrecords->num_elts ) );
        memcpy( pSubrecords->num_elts, buffer , strlen(buffer) );

        // 단위
        sprintf( buffer, (char *) "%d" , stSubrecordUnit[i] );
        memset( pSubrecords->units, 0x20, sizeof( pSubrecords->units ) );
        memcpy( pSubrecords->units, buffer , strlen(buffer) );

        // 데이터 포멧
        pSubrecords->format[0] = DATA_FORMAT_SIZE_DESIGNATOR_SCALR;
        if( strcmp( stSubrecordName[i], stSubrecordName[enFreqOfSub] ) == 0 ) {
            pSubrecords->format[1] = DATA_FORMAT_TYPE_DESIGNATOR_64BIT_FLOAT;
            iOffset += 8;
        }
        else if( strcmp( stSubrecordName[i], stSubrecordName[enTOAOfSub] ) == 0 || strcmp( stSubrecordName[i], stSubrecordName[enDTOAOfSub] ) == 0 ) {
            pSubrecords->format[1] = DATA_FORMAT_TYPE_DESIGNATOR_64BIT_FLOAT;
            iOffset += 8;
        }
        else {
            pSubrecords->format[1] = DATA_FORMAT_TYPE_DESIGNATOR_64BIT_FLOAT;
            iOffset += 8;
        }

        // Greek 접두어 코드
        //sprintf( buffer, sizeof(buffer), "%03d" , 0 );
        sprintf( buffer, "   " );
        memcpy( pSubrecords->uprefix, buffer , strlen(buffer) );

        // 예비
        memset( pSubrecords->reserved, 0x20, sizeof( pSubrecords->reserved ) );

        ++ pSubrecords;
    }

    //memcpy( pSubrecords, "SUBREC_DEF", strlen("SUBREC_DEF") );
    strcpy( (char *) pSubrecords, SUBREC_DEF );

    return sizeof( SELMIDAS_SUBRECORDS ) * MAX_SUBRECORDS_OF_PDWDATA + strlen(SUBREC_DEF);

}

/**
 * @brief     키워드, 값, 타입 등을 입력받아서 MIDAS 포멧으로 기록한다.
 * @param     void
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2015-03-06, 17:01:25
 * @warning
 */
unsigned int CMIDASBlueFileFormat::MakeBinaryKeyword( SELMIDAS_BINARY_KEYWORD *pBinKeyword, char *value_keyword, char *keyword, int c, char type, int lkey )
{
    unsigned int uiret=0;

    /*! \bug  신뢰성: 상/하한값 설정하게 함.
            \author 조철희 (churlhee.jo@lignex1.com)
            \date 	2015-10-5 17:20:10
    */
    if( c > 0 && c < MAX_OF_KEYWORD ) {
        // SELMIDAS_BINARY_KEYWORD 구조체 다음이 문자열
        //memcpy( (char *) pBinKeyword + sizeof(SELMIDAS_BINARY_KEYWORD), value_keyword, c );
        memcpy( (char *) & pBinKeyword[1], value_keyword, c );

        if( lkey == 0 ) {
            if( c % 8 == 0 )
                pBinKeyword->lkey = sizeof(SELMIDAS_BINARY_KEYWORD) + ( c / 8 ) * 8;
            else
                pBinKeyword->lkey = sizeof(SELMIDAS_BINARY_KEYWORD) + ( c / 8 + 1 ) * 8;
        }
        else {
            pBinKeyword->lkey = lkey;
        }
        uiret = pBinKeyword->lkey;

        // binary keyword 구조체에 값을 저장
        pBinKeyword->ltag = (unsigned char) strlen( keyword );
        pBinKeyword->lext = (unsigned short) ( pBinKeyword->lkey - ( c - pBinKeyword->ltag ) );

        pBinKeyword->type = type;

        if( g_enEndian == enBIG_ENDIAN ) {
            CCommonUtils::swapByteOrder( pBinKeyword->lkey );
            CCommonUtils::swapByteOrder( pBinKeyword->lext );
        }
    }
    else {
        printf( "\n 키워드 값이 초과 되었습니다." );
    }

    return uiret;
}

/**
 * @brief     키워드에 값을 설정한다.
 * @param     SELMIDAS_BINARY_KEYWORD * pBinKeyword
 * @param     unsigned long long ivalue
 * @param     char * keyword
 * @param     char type
 * @param     int lkey
 * @return    SELMIDAS_BINARY_KEYWORD *
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-05, 12:20
 * @warning
 */
SELMIDAS_BINARY_KEYWORD *CMIDASBlueFileFormat::MakeValueBinaryKeyword( SELMIDAS_BINARY_KEYWORD *pBinKeyword, unsigned long long ivalue, char *keyword, char type, int lkey )
{
    int c=0;
    char buffer[200];
    unsigned short sValue;
    long double ldValue;
    unsigned long long llValue;
    unsigned char cValue;
    int ikey;

    switch( type ) {
    case DATA_FORMAT_TYPE_DESIGNATOR_64BIT_FLOAT :
        ldValue = (long double) ivalue;
        c = sizeof( ldValue );
        memcpy( buffer, & ldValue, sizeof(ldValue) );
        c += sprintf( & buffer[sizeof(ldValue)], "%s", keyword );
        break;

    case DATA_FORMAT_TYPE_DESIGNATOR_16BIT_INTEGER :
        sValue = (unsigned short) ivalue;
        c = sizeof( sValue );
        memcpy( buffer, & sValue, sizeof(sValue) );
        c += sprintf( & buffer[sizeof(sValue)], "%s", keyword );
        break;

    case DATA_FORMAT_TYPE_DESIGNATOR_64BIT_INTEGER :
        llValue = (unsigned long long) ivalue;
        c = sizeof( llValue );
        memcpy( buffer, & llValue, sizeof(llValue) );
        c += sprintf( & buffer[sizeof(llValue)], "%s", keyword );
        break;

    case DATA_FORMAT_TYPE_DESIGNATOR__8BIT_INTEGER :
        cValue = (unsigned char) ivalue;
        c = sizeof( cValue );
        memcpy( buffer, & cValue, sizeof(cValue) );
        c += sprintf( & buffer[sizeof(cValue)], "%s", keyword );
        break;

    default :
        printf( "\n 에러 발생..." );
        memset( buffer, 0, sizeof(buffer) );
        break;
    }

    ikey = MakeBinaryKeyword( pBinKeyword, buffer, keyword, c, type, lkey );
    char *pByte = ( char * ) pBinKeyword;
    return ( SELMIDAS_BINARY_KEYWORD * ) ( & pByte[ikey] );

}

/**
 * @brief CMIDASBlueFileFormat::MakeValueBinaryKeyword
 * @param pBinKeyword
 * @param ivalue
 * @param keyword
 * @param type
 * @return
 */
SELMIDAS_BINARY_KEYWORD *CMIDASBlueFileFormat::MakeValueBinaryKeyword( SELMIDAS_BINARY_KEYWORD *pBinKeyword, long double ivalue, char *keyword, char type )
{
    int c=0;
    char buffer[200];
    unsigned short sValue;
    long double ldValue;
    unsigned long long llValue;
    unsigned char cValue;
    int ikey;

    switch( type ) {
    case DATA_FORMAT_TYPE_DESIGNATOR_64BIT_FLOAT :
        ldValue = (long double) ivalue;
        c = sizeof( ldValue );
        memcpy( buffer, & ldValue, sizeof(ldValue) );
        c += sprintf( & buffer[sizeof(ldValue)], "%s", keyword );
        break;

    case DATA_FORMAT_TYPE_DESIGNATOR_16BIT_INTEGER :
        sValue = (unsigned short) ivalue;
        c = sizeof( sValue );
        memcpy( buffer, & sValue, sizeof(sValue) );
        c += sprintf( & buffer[sizeof(sValue)], "%s", keyword );
        break;

    case DATA_FORMAT_TYPE_DESIGNATOR_64BIT_INTEGER :
        llValue = (unsigned long long ) ivalue;
        c = sizeof( llValue );
        memcpy( buffer, & llValue, sizeof(llValue) );
        c += sprintf( & buffer[sizeof(llValue)], "%s", keyword );
        break;

    case DATA_FORMAT_TYPE_DESIGNATOR__8BIT_INTEGER :
        cValue = (unsigned char) ivalue;
        c = sizeof( cValue );
        memcpy( buffer, & cValue, sizeof(cValue) );
        c += sprintf( & buffer[sizeof(cValue)], "%s", keyword );
        break;

    default :
        printf( "\n 에러 발생..." );
        break;
    }

    ikey = MakeBinaryKeyword( pBinKeyword, buffer, keyword, c, type );
    char *pByte = ( char * ) pBinKeyword;
    return ( SELMIDAS_BINARY_KEYWORD * ) ( & pByte[ikey] );
    //return ( SELMIDAS_BINARY_KEYWORD * ) ( (char *) pBinKeyword + pBinKeyword->lkey );

}

/**
 * @brief     문자열로 키워드 값을 설정한다.
 * @param     SELMIDAS_BINARY_KEYWORD * pBinKeyword
 * @param     char * pValue
 * @param     char * keyword
 * @return    SELMIDAS_BINARY_KEYWORD *
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-08-10, 17:04
 * @warning
 */
SELMIDAS_BINARY_KEYWORD *CMIDASBlueFileFormat::MakeSetBinaryKeyword( SELMIDAS_BINARY_KEYWORD *pBinKeyword, char *pValue, char *keyword )
{
    int c;
    char *pByte;
    unsigned int lKey;

    c = strlen( pValue );
    lKey = MakeBinaryKeyword( pBinKeyword, pValue, keyword, c, DATA_FORMAT_TYPE_DESIGNATOR_ASCII );
    pByte = (char *) pBinKeyword;
    
    return ( SELMIDAS_BINARY_KEYWORD * ) ( & pByte[lKey] );

}

/**
 * @brief     Extended header 구조체를 파일에 저장한다.
 * @param     void
 * @return    int
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2015-03-06, 17:01:25
 * @warning
 */
int CMIDASBlueFileFormat::WriteExtendedHeader()
{
    int iWrite=0;

    if( m_enFileType != E_EL_SCDT_PDW2SP370 && m_pExtendOfHeader != NULL ) {
        iWrite = Write( m_pExtendOfHeader, sizeof(char)*m_uiSizeOfExtend );
    }

    return iWrite;
}

/**
 * @brief     MakeMIDASFileName
 * @param     CString * pstrOutFilePathName
 * @param     CString * pstrFileName
 * @param     EnumSCDataType eDataType
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-01-05, 오후 8:23
 * @warning
 */
void CMIDASBlueFileFormat::MakeMIDASFileName( char *pstOutFilePathName, char *pstFileName, EnumSCDataType eDataType )
{
    strcpy( pstOutFilePathName, pstFileName );

    if( eDataType == E_EL_SCDT_PDW ) {
        strcat( pstOutFilePathName, ".xpdw" );
    }
    else if( eDataType == E_EL_SCDT_PDW2SP370 ) {
        strcat( pstOutFilePathName, ".pd2" );
    }
    else {
        strcat( pstOutFilePathName, ".complex" );
    }

}

/**
 * @brief     InitIFMidas
 * @param     I_RAWDataSel * pRAWDataSel
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-01-09, 오후 7:32
 * @warning
 */
void CMIDASBlueFileFormat::InitIFMidas()
{
    m_vecConvertIFList.clear();

}

/**
 * @brief     SaveIFMIDASFormat
 * @param     void
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-01-09, 오후 7:38
 * @warning
 */
bool CMIDASBlueFileFormat::SaveAllIFMIDASFormat()
{
    int iFile;
    bool bRet=true;
    unsigned int i, nSize;
    
#ifndef __VXWORKS__    

    vector<SELIFMIDAS>::pointer pConvertIFList;

    if( m_vecConvertIFList.size() != 0 ) {
        m_enFileType = E_EL_SCDT_IF;

        pConvertIFList = m_vecConvertIFList.data();

        // 1. 사용자 지정 파일 생성
        if( FileOpen( (*pConvertIFList).szOutputFilename, O_CREAT | O_BINARY ) == false ) { //DTEC_Else
            return false;
        }

        //
        memcpy( & m_strKeywordValue, & (*pConvertIFList).keywordValue, sizeof(SEL_KEYWORD_VALUE) );
        //m_pKeywordValue =

        // 2. MIDAS 포멧으로 헤더 및 부가 구조체 저장
        MakeHeader();

        // 3. Adjunct 헤더 파일 변환
        MakeAdjunct();

        // 4. HCD 저장
        WriteHeader();

        // 5. 데이터 저장
        nSize = m_vecConvertIFList.size();
        for( i=0 ; i < nSize ; ++i ) {
#ifdef __linux__
            iFile = open( (*pConvertIFList).szInputFilename, O_RDONLY );
#else
            iFile = _open( (*pConvertIFList).szInputFilename, _O_RDONLY | _O_BINARY );
#endif

            //_sopen_s( & iFile, (char*)(LPCSTR) (*pConvertIFList).strInputFilename, _O_RDONLY | _O_BINARY, _SH_DENYNO, _S_IWRITE );
            bRet = WriteData( iFile, 0, nSize >= 2 );
            if( bRet == false ) { //DTEC_Else
                break;
            }

            close( iFile );

            ++ pConvertIFList;
        }

        if( bRet == true ) {
            // 6. Extended Header 변환
            MakeExtendedHeader();

            WriteExtendedHeader();
        }

        // 7. 변환 파일 닫기
        FileClose();

        // 8.
        MIDASClose();

        bRet = true;
    }
#endif    

    return bRet;

}

/**
 * @brief CMIDASBlueFileFormat::MIDASClose
 */
void CMIDASBlueFileFormat::MIDASClose()
{
    if( m_pExtendOfHeader != NULL ) {
        free(  m_pExtendOfHeader );
    }
    m_pExtendOfHeader = NULL;

}

/**
 * @brief CMIDASBlueFileFormat::SaveRawDataFile
 * @param bSaveFile
 * @param enDataType
 * @param pData
 * @param uiStep
 * @param iBoardID
 */
void CMIDASBlueFileFormat::SaveRawDataFile( const char *pRawdataFileName, EnumSCDataType enDataType, void *pData )
{
    STR_PDWDATA *pPDWData;

    pPDWData = ( STR_PDWDATA * ) pData;

    m_strKeywordValue.numberofdata = pPDWData->GetTotalPDW();    

    //printf( "\n m_szRawDataFilename[%s]" , m_szRawDataFilename );
    strcpy( m_szRawDataFilename, pRawdataFileName );

#ifdef _MSC_VER

#ifdef _XBAND_
	if( true == FileOpen( pRawdataFileName, O_WRONLY | O_CREAT | O_BINARY ) ) {
		Write( & pPDWData->x, sizeof(STR_ELINT_HEADER) );

		Write( & pPDWData->pstPDW[0], pPDWData->GetTotalPDW()*sizeof(_PDW) );

		FileClose();
	}

#else
	SaveMIDASFormat( pRawdataFileName, E_EL_SCDT_PDW, pPDWData, & m_strKeywordValue );

#endif

#endif

}
