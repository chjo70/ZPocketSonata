#include "cencdec.h"



SONATA::FREQ_RESOL _spFreqRes[ 3 ] = {  { 0,    2560,   0,      0.625 },
                                        { 1280, 6400,   1260,   1.25  },
                                        { 5866, 18740,  5866,   1.5   } } ;

/**
 * @brief SONATA::CEncode::DOA
 */
int SONATA::ENCODE::DOA( float fDOA )
{
    return (int) ( fDOA / _spAoaRes + 0.5 );
}

/**
 * @brief SONATA::ENCODE::FREQ
 * @param fFREQ
 * @return
 */
int SONATA::ENCODE::FREQ( int iBAND, float fFREQ )
{
    return (int) ( ( ( fFREQ - _spFreqRes[iBAND].iOffset ) / _spFreqRes[iBAND].fRes ) + 0.5 );
}

/**
 * @brief SONATA::ENCODE::TOA
 * @param fTOA [us]
 * @return
 */
unsigned int SONATA::ENCODE::TOA( float fTOA )
{
    return (unsigned int) ( fTOA * _spToaRes + 0.5 );
}

/**
 * @brief SONATA::ENCODE::PW
 * @param fPW
 * @return
 */
int SONATA::ENCODE::PW( float fPW )
{
    return (int) ( fPW / _spPWRes + 0.5 );
}


/**
 * @brief SONATA::ENCODE::PA
 * @param fPA
 * @return
 */
int SONATA::ENCODE::PA( float fPA )
{
    return (int) ( ( fPA - _spPAOffset ) / _spPARes + 0.5 );
}


////////////////////////////////////////////////////////////////////////////////////////////////


/**
 * @brief SONATA::DECODE::DOA
 * @param iDOA
 * @return
 */
float SONATA::DECODE::DOA( int iDOA )
{
    return (float) iDOA * _spAoaRes;

}

/**
 * @brief SONATA::DECODE::FREQ
 * @param iBAND
 * @param iFREQ
 * @return
 */
float SONATA::DECODE::FREQ( int iBAND, int iFREQ )
{
    return ( (float) iFREQ  * _spFreqRes[iBAND].fRes ) + _spFreqRes[iBAND].iOffset;
}

/**
 * @brief SONATA::DECODE::FREQ_C
 * @param iBAND
 * @param iFREQ
 * @return
 */
float SONATA::DECODE::FREQ_C( int iBAND, int iFREQ )
{
    return ( ( (float) iFREQ  * _spFreqRes[iBAND].fRes ) + 0.5 ) + _spFreqRes[iBAND].iOffset;
}

/**
 * @brief SONATA::DECODE::FREQ_F
 * @param iBAND
 * @param iFREQ
 * @return
 */
float SONATA::DECODE::FREQ_F( int iBAND, int iFREQ )
{
    return ( (float) iFREQ  * _spFreqRes[iBAND].fRes ) + _spFreqRes[iBAND].iOffset;
}

/**
 * @brief SONATA::DECODE::TOA
 * @param uiTOA
 * @return
 */
float SONATA::DECODE::TOA( unsigned int uiTOA )
{
    return ( (float) uiTOA / (float) _spToaRes );
}

/**
 * @brief SONATA::DECODE::PW
 * @param uiTOA
 * @return
 */
float SONATA::DECODE::PW( int iPW )
{
    return ( (float) iPW * (float) _spPWRes );
}

/**
 * @brief SONATA::DECODE::PA
 * @param iPA
 * @return
 */
float SONATA::DECODE::PA( int iPA )
{

    return ( (float) iPA * (float) _spPARes + _spPAOffset);
}
