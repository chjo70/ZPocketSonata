#ifndef CENCDEC_H
#define CENCDEC_H

/**
 *  SONATA 용으로 실제값을 SONATA 체계와 연동하기 위해서 값을 역/변환해주는 함수를 정의한다.
 */
namespace SONATA {
//     struct FREQ_RESOL {
//         // frequency band code를 위한 구조체
//         unsigned int uiMin;       // min frequency
//         unsigned int uiMax;       // max frequency
//         int iOffset;       // max frequency
//         float fRes;			// 각 구간에 따른 resolution
//     } ;

    namespace ENCODE {
        int DOA( float fDOA );
        int BAND( float fFREQ );
        int FREQ( int iBAND, float fFREQ );
        unsigned int TOA( float fTOA );
        int PW( float fPW );
        int PA( float fPA );
        int SCNPRD( float fScanPrd );
    } ;

    /**
     *
     */
    namespace DECODE {
        float DOA( int iDOA );
        float FREQ( int iBAND, int iFREQ );
        float FREQ_F( int iBAND, int iFREQ );
        float FREQ_C( int iBAND, int iFREQ );
        float TOA( unsigned int fTOA );
        float PW( int iPW );
        float PA( int iPA );
    } ;

}

/**
 *  다른 체계용을 위한 정의한 예시 입니다. 위에서 처럼 정의해서 사용하면 됩니다.
 */
namespace OTHER_SYSTEM {

}

#endif // CENCDEC_H
