#ifndef CENCDEC_H
#define CENCDEC_H


namespace SONATA
{

struct FREQ_RESOL {
    // frequency band code를 위한 구조체
    unsigned int uiMin;       // min frequency
    unsigned int uiMax;       // max frequency
    int iOffset;       // max frequency
    float fRes;			// 각 구간에 따른 resolution
} ;

#define     _spAoaRes           (360.0/1024.)
#define     _spToaRes           (20)
#define     _spPWRes            (50)
#define     _spPARes            (80./256.)
#define     _spPAOffset         (-70.)


    namespace ENCODE
    {

        int DOA( float fDOA );
        int FREQ( int iBAND, float fFREQ );
        unsigned int TOA( float fTOA );
        int PW( float fPW );
        int PA( float fPA );

    } ;

    /**
     *
     */
    namespace DECODE
    {
        float DOA( int iDOA );
        float FREQ( int iBAND, int iFREQ );
        float FREQ_F( int iBAND, int iFREQ );
        float FREQ_C( int iBAND, int iFREQ );
        float TOA( unsigned int fTOA );
        float PW( int iPW );
        float PA( int iPA );
    } ;

}

#endif // CENCDEC_H
