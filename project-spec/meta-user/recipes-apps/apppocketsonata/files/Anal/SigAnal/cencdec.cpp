// cencdec.cpp: implementation of the SONATA class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"


#include "cencdec.h"

#include "../Collect/DataFile/DataFile.h"

// SONATA::FREQ_RESOL _spFreqRes[ 3 ] = {  { 0,    2560,   0,      0.625 },
//                                         { 1280, 6400,   1260,   1.25  },
//                                         { 5866, 18740,  5866,   1.5   } } ;

/**
 * @brief SONATA::CEncode::DOA
 */
int SONATA::ENCODE::DOA( float fDOA )
{
    return (int) ( fDOA / SONATA::_fDOARes + 0.5 );

}

/**
 * @brief     BAND
 * @param     float fFREQ
 * @return    int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-11-24 15:31:01
 * @warning
 */
int SONATA::ENCODE::BAND( float fFREQ )
{
    int iBand=0;

    if( fFREQ > 6000.0 ) {
        iBand = 2;
    }
    else if( fFREQ > 2000.0 ) {
        iBand = 1;
    }
    else {

    }

    return iBand;
}

/**
 * @brief SONATA::ENCODE::FREQ
 * @param fFREQ
 * @return
 */
int SONATA::ENCODE::FREQ( int iBAND, float fFREQ )
{
    return (int) ( ( ( fFREQ - _gFreqRes[iBAND].iOffset ) / _gFreqRes[iBAND].fRes ) + 0.5 );
}

/**
 * @brief SONATA::ENCODE::TOA
 * @param fTOA [us]
 * @return
 */
unsigned int SONATA::ENCODE::TOA( float fTOA )
{
    return (unsigned int) ( fTOA * SONATA::_dTOARes + 0.5 );
}

/**
 * @brief SONATA::ENCODE::PW
 * @param fPW
 * @return
 */
int SONATA::ENCODE::PW( float fPW )
{
    return (int) ( fPW / SONATA::_dPWRes + 0.5 );
}


/**
 * @brief SONATA::ENCODE::PA
 * @param fPA
 * @return
 */
int SONATA::ENCODE::PA( float fPA )
{
    return (int) ( ( fPA - SONATA::_iPAOffset) / SONATA::_fPARes + 0.5 );
}


int SONATA::ENCODE::SCNPRD( float fScanPrd )
{
    return (int) ( fScanPrd + 0.5 );
}

////////////////////////////////////////////////////////////////////////////////////////////////


/**
 * @brief SONATA::DECODE::DOA
 * @param iDOA
 * @return
 */
float SONATA::DECODE::DOA( int iDOA )
{
    return (float) iDOA *SONATA::_fDOARes;

}

/**
 * @brief SONATA::DECODE::FREQ
 * @param iBAND
 * @param iFREQ
 * @return
 */
float SONATA::DECODE::FREQ( int iBAND, int iFREQ )
{
    return ( (float) iFREQ  * _gFreqRes[iBAND].fRes ) + _gFreqRes[iBAND].iOffset;
}

/**
 * @brief SONATA::DECODE::FREQ_C
 * @param iBAND
 * @param iFREQ
 * @return
 */
float SONATA::DECODE::FREQ_C( int iBAND, int iFREQ )
{
    return ( ( (float) iFREQ  * _gFreqRes[iBAND].fRes ) + (float) 0.5 ) + _gFreqRes[iBAND].iOffset;
}

/**
 * @brief SONATA::DECODE::FREQ_F
 * @param iBAND
 * @param iFREQ
 * @return
 */
float SONATA::DECODE::FREQ_F( int iBAND, int iFREQ )
{
    return ( (float) iFREQ  * _gFreqRes[iBAND].fRes ) + _gFreqRes[iBAND].iOffset;
}

/**
 * @brief SONATA::DECODE::TOA
 * @param uiTOA
 * @return
 */
float SONATA::DECODE::TOA( unsigned int uiTOA )
{
    return ( (float) uiTOA / (float) SONATA::_dTOARes);
}

/**
 * @brief SONATA::DECODE::PW
 * @param uiTOA
 * @return
 */
float SONATA::DECODE::PW( int iPW )
{
    return ( (float) iPW * (float) SONATA::_dPWRes);
}

/**
 * @brief SONATA::DECODE::PA
 * @param iPA
 * @return
 */
float SONATA::DECODE::PA( int iPA )
{
    return ( (float) iPA * (float) SONATA::_fPARes + SONATA::_iPAOffset);
}
