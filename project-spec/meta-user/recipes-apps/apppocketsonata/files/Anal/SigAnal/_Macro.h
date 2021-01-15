/*!
  \file     _macro.h
  \brief    매크로 정의문을 설명한다.
    \version  0.0.1
*/

#ifndef  __MACRO_H
#define  __MACRO_H

#include "../INC/PDW.h"
#include "../SigAnal/_Define.h"

#define DFD_FREQ_OFFSET		(1900)

#define _spSONATAPAoffset			(-70)					// amplitude initial value
#define _spSONATAAMPres       (0.3125)			// dB */
#define	_spSONATAAOAmax				(0x1FF)	
#define	_spSONATAAmpmax				(0xFF)	

#define	FREQ_MIN			(500)			// 최소 주파수
#define	FREQ_MAX			(18000)


enum ENUM_UnitID {
	enUnknown = -1,

	enSHU = 0,
	enRSA,
	enZPocketSonata

} ;

enum ENUM_BoardID {
    enPRC_Unknown,
    enPRC1=1,
    enPRC2,
    enPRC3,
    enPRC4,
    enPRC5,
    enPRC6,

    enMaster=enPRC3

};

#define _SAFE_FREE(A)           if( A != 0 ) { free( A ); A = 0; }

#define DivideBy2( A, B )       ( ( (A) + (B) + 1 ) / 2 )		//!< 나누기 2
#define _DIV( A, B )            (UINT) ( (float) (A) / (float) (B) )	//!< 정수 나누기
#define UDIV( A, B )            (unsigned int) ( (float) (A) / (float) (B) + 0.5 )
#define NDIV( A, B )            (int) ( (float) (A) / (float) (B) - 0.5 )

#define F_NDIV( A, B )          (UINT) ( (float) (A) / (float) (B) - 0.5 )
#define C_NDIV( A, B )          (UINT) ( (float) (A) / (float) (B) + 0.5 )
#define FDIV( A, B )            (float) ( (float) (A) / (float) (B) )
#define F_UDIV( A, B )          (int) ( (float) (A) / (float) (B) - 0.5 )
#define C_UDIV( A, B )          (int) ( (float) (A) / (float) (B) + 0.5 )
#define IDIV( A, B )            ( ( (A) > 0 ) ? UDIV(A,B) : NDIV(A,B) )
#define F_IDIV( A, B )          ( ( (A) > 0 ) ? F_UDIV(A,B) : F_NDIV(A,B) )
#define C_IDIV( A, B )          ( ( (A) > 0 ) ? C_UDIV(A,B) : C_NDIV(A,B) )
#define IMUL( A, B )            ( ( (A) > 0 ) ? UMUL(A,B) : NMUL(A,B) )
#define F_MUL( A, B )           (int) ( ( (float) (A) * (float) (B) ) - 0.5 )
#define C_MUL( A, B )           (int) ( ( (float) (A) * (float) (B) ) + 0.5 )
#define UADD( A, B )            (UINT) ( (float) (A) + (float) (B) + 0.5 )
#define FADD( A, B )            (float) ( (float) (A) + (float) (B) )
#define FMUL( A, B )            ( (float) (A) * (float) (B) )
#define FDMUL( A, B )           (float) ( (double) (A) * (double) (B) )
#define TMUL( A, B )            (_TOA) ( (_TOA) (A) * (_TOA) (B) + 0.5 )
#define TDIV( A, B )            (_TOA) ( (_TOA) (A) / (_TOA) (B) + 0.5 )
#define UMUL( A, B )            (UINT) ( ( (float) (A) * (float) (B) ) + 0.5 )
#define NMUL( A, B )            (UINT) ( (float) (A) * (float) (B) - 0.5 )

#define WeightedVal( A,B,C,D)   UDIV( (A*C) + (B*D), C+D)
#define WeightedAdvVal(A,B,C)   UDIV( FADD(FMUL( A, B ), C), FADD( 1, A ) )
#define ThreeOverTen( A )       ( UINT ) ( ( ( ( A ) * 3 ) + 5 ) / 10 )
#define HalfThreeOverTen( A )   ( UINT ) ( ( ( ( A ) * 3 ) + 10 ) / 20 )




#define BIT_MERGE(high,low)     ( ( ((UINT)high) << 8 ) | low )




template <typename T>
T _diffabs( T x, T y)
{

    if (x > y) {
        return x - y;
    }
    else {
        return y - x;
    }

}



#define _abs(a)                 ( (a) >= 0 ? (a) : -(a) )
#define High( A )               ( (int) A >> 8 ) & 0x00ff
#define Low( A )                ( A & 0x00ff )

#ifdef _ELINT_
#define FRQMhzCNV( A, B )		IMUL( (B), ( 0.001) )
#define IFRQMhzCNV( A, B )		IDIV( (B), ( 0.001) )
#define TOAusCNV( A )           IDIV( (A), _spOneMicrosec )
#define ITOAusCNV( A )			IMUL( (A), _spOneMicrosec )					// X us 로 값으로 변환함
#define IFTOAusCNV( A )			FMUL( (A), _spOneMicrosec )					// X us 로 값으로 변환함
#define ITTOAusCNV( A )			TMUL( (A), _spOneMicrosec )					// X us 로 값으로 변환함

#define PWCNV( A )				IDIV( (A*1000.), _spOneMicrosec )
#define IPWCNV( A )				IMUL( (A), _spOneMicrosec )
#define AOACNV( A )             IMUL( (A), _spAOAres )
#define IAOACNV( A )            IDIV( (A), _spAOAres )

#define AddAOA(A, B)            ( ( A + B + MAX_AOA) % MAX_AOA )
#define SubAOA(A, B)            ( ( A - B + MAX_AOA) % MAX_AOA )
//#define FRQRESCNV( A, B )		(UINT) ( abs( (int) IMUL( gFreqRes[(A)].res, (B) ) ) )
#define FTOAsCNV( A )			FDIV( (A), _spOneMicrosec )

#define PACNV( A )				(float)( FMUL( (A), _spAMPres ) - (float) 110. )
#define IPACNV( A )				FDIV( (A), _spAMPres )

#elif defined(_POCKETSONATA_)
#define FFRQCNV( A, B )         CPOCKETSONATAPDW::DecodeFREQMHz( B )
#define FRQMhzCNV( A, B )		CPOCKETSONATAPDW::DecodeFREQMHz( B )
#define IFRQMhzCNV( A, B )      CPOCKETSONATAPDW::EncodeFREQMHzCeiling( B )
#define IFRQCNV( A, B )         IDIV( (B), ( gFreqRes[A].res ) )

#define IFRQMhzLOW( A )         CPOCKETSONATAPDW::EncodeFREQMHzFloor( A )
#define IFRQMhzHGH( A )         CPOCKETSONATAPDW::EncodeFREQMHzCeiling( A )

#define TOAusCNV( A )           CPOCKETSONATAPDW::DecodeTOAus( A )
#define TOAmsCNV( A )           CPOCKETSONATAPDW::DecodeTOAms( A )
#define FTOAsCNV( A )			CPOCKETSONATAPDW::DecodeTOAs( A )
#define ITOAusCNV( A )			CPOCKETSONATAPDW::EncodeTOAus( A )
#define ITTOAusCNV( A )			CPOCKETSONATAPDW::EncodeTOAus( A )

#define PWCNV( A )				CPOCKETSONATAPDW::DecodePWus( A )
#define IPWCNV( A )				IMUL( (A), _spOneNanosec )
#define FPWCNV( A )             FMUL( (A), _spOneNanosec )

#define IPWCNVLOW( A )			CPOCKETSONATAPDW::EncodePWFloor( A )
#define IPWCNVHGH( A )			CPOCKETSONATAPDW::EncodePWCeiling( A )

#define AOACNV( A )             CPOCKETSONATAPDW::DecodeDOA( A )
#define IAOACNV( A )            CPOCKETSONATAPDW::EncodeDOA( A )
#define FAOACNV( A )            CPOCKETSONATAPDW::DecodeDOA( A )

#define AddAOA(A, B)            ( ( A + B + MAX_AOA) % MAX_AOA )
#define SubAOA(A, B)            ( ( A - B + MAX_AOA) % MAX_AOA )


#define PACNV( A )				CPOCKETSONATAPDW::DecodePA( A )
#define IPACNV( A )				FDIV( (A), _spAMPres )
#define FPACNV( A )				(float)( FMUL( (A), _spAMPres ) - (float) 110. )

#define F_FRQMhzCNV( A, B )		FMUL( (B), 0 )

#elif defined(_SONATA_)
#define FFRQCNV( A, B )             FMUL( (B), ( gFreqRes[(A)].res ) )
#define F_FRQCNV( A, B )            (UINT) ( F_MUL( gFreqRes[(A)].res, (B) ) + gFreqRes[(A)].offset )
#define C_FRQCNV( A, B )            (UINT) ( C_MUL( gFreqRes[(A)].res, (B) ) + gFreqRes[(A)].offset )
#define FRQMhzCNV( A, B )           IMUL( (B), ( gFreqRes[(A)].res ) )
#define IFRQMhzCNV( A )             IDIV( (A), ( gFreqRes[0].res ) )
#define IFRQCNV( A, B )             IDIV( (A), ( gFreqRes[0].res ) )

#define IFRQMhzLOW( A )             F_IDIV( (A), ( gFreqRes[0].res ) )
#define IFRQMhzHGH( A )             C_IDIV( (A), ( gFreqRes[0].res ) )

#define TOAusCNV( A )           IDIV( (A), _spOneMicrosec )
#define TOAmsCNV( A )           IDIV( (A), _spOneMilli )
#define ITOAusCNV( A )			IMUL( (A), _spOneMicrosec )					// X us 로 값으로 변환함
#define ITOAmsCNV( A )			IMUL( (A), _spOneMilli )					// X us 로 값으로 변환함
#define IFTOAusCNV( A )			FMUL( (A), _spOneMicrosec )					// X us 로 값으로 변환함
#define ITTOAusCNV( A )			TMUL( (A), _spOneMicrosec )					// X us 로 값으로 변환함

#define PWCNV( A )				IDIV( A, _spOneNanosec )
#define IPWCNV( A )				IMUL( (A), _spOneNanosec )
#define FPWCNV( A )             FMUL( (A), _spOneNanosec )

#define IPWCNVLOW( A )			F_MUL( (A), _spOneNanosec )
#define IPWCNVHGH( A )			C_MUL( (A), _spOneNanosec )

#define AOACNV( A )             FMUL( (A), _spAOAres )
#define IAOACNV( A )            IDIV( (A), _spAOAres )
#define FAOACNV( A )            (float) ( (float) A * _spAOAres )

#define AddAOA(A, B)            ( ( A + B + MAX_AOA) % MAX_AOA )
#define SubAOA(A, B)            ( ( A - B + MAX_AOA) % MAX_AOA )
#define FTOAsCNV( A )			FDIV( (A), _spOneMicrosec )

#define PACNV( A )				(float)( FMUL( (A), _spAMPres ) - (float) 110. )
#define IPACNV( A )				FDIV( (A), _spAMPres )
#define FPACNV( A )				(float)( FMUL( (A), _spAMPres ) - (float) 110. )

#define F_FRQMhzCNV( A, B )		FMUL( (B), 0 )


#else
#define F_FRQMhzCNV( A, B )		FMUL( (B), 0 )
#define FFRQCNV( A, B )             FMUL( (B), ( gFreqRes[(A)].res ) )
#define FFRQCNV( A, B )             FMUL( (B), ( gFreqRes[(A)].res ) )
#define AddAOA(A, B)            ( ( A + B + MAX_AOA) % MAX_AOA )
#define SubAOA(A, B)            ( ( A - B + MAX_AOA) % MAX_AOA )

#define TOAsCNV( A )						UDIV( (A), _spOneSec )
#define TOAmsCNV( A )           UDIV( (A), _spOneMilli )
#define TOAusCNV( A )           UDIV( (A), _spOneMicrosec )
#define TOAnsCNV( A )           UMUL( (A), _spTimeNsRes )
#define FTOAsCNV( A )						FDIV( (A), _spOneMicrosec )

#define F_TOAusCNV( A )         UDIV( (A), _spOneMicrosec )
#define C_TOAusCNV( A )         UDIV( (A), _spOneMicrosec )

#define F_TOAnsCNV( A )         F_MUL( (A), _spTimeNsRes )
#define C_TOAnsCNV( A )         C_MUL( (A), _spTimeNsRes )

#define FTOAmsCNV( A )          FDIV( (A), _spOneMilli )
#define FTOAusCNV( A )          FDIV( (A), _spOneMicrosec )

//#define AMPCNV( A )             (int) ( UMUL( A, _spAMPres) + _spPAoffset )
#define FRQRESCNV( A, B )				(UINT) ( abs( (int) IMUL( gFreqRes[(A)].res, (B) ) ) )
#define FRQCNV( A, B )          (UINT) ( UMUL( gFreqRes[(A)].res, (B) ) + gFreqRes[(A)].offset )
#define F_FRQCNV( A, B )        (UINT) ( F_MUL( gFreqRes[(A)].res, (B) ) + gFreqRes[(A)].offset )
#define C_FRQCNV( A, B )        (UINT) ( C_MUL( gFreqRes[(A)].res, (B) ) + gFreqRes[(A)].offset )
#define AOACNV( A )             UMUL( (A), _spAOAres )
#define F_AOACNV( A )           (UINT) ( (A) * _spAOAres )
#define C_AOACNV( A )           (UINT) ( C_MUL( (A), _spAOAres ) )
#define PWCNV( A )              UMUL( (A), _spPWres )
#define F_PWCNV( A )            F_MUL( (A), _spPWres )
#define C_PWCNV( A )            C_MUL( (A), _spPWres )
#define PACNV( A )				(float)( FMUL( (A), _spAMPres ) - (float) 110. )
#define F_PACNV( A, B )         F_IDIV( FPACNV(A,B), 1 )
#define C_PACNV( A, B )         C_IDIV( FPACNV(A,B), 1 )

//#define F_PACNV( A )            ( F_MUL( (A), _spAMPres ) - _spPAoffset )
//#define C_PACNV( A )            ( C_MUL( (A), _spAMPres ) - 74.6875 )
#define FAOACNV( A )            (float) ( (float) A * _spAOAres )
#define FPWCNV( A )             (float) ( (float) A * _spPWres )
//#define FPACNV( A, B )					(float) ( ( (float) (A) * gPaRes[B].res ) + gPaRes[B].offset )
#define FPACNV( A )							(float) ( ( (float) (A) * gPaRes[0].res ) + gPaRes[0].offset )
#define FDBCNV( A, B )					(float) ( ( (float) (A) / gPaRes[B].res ) )
#define UDBCNV( A, B )					UDIV( (A), gPaRes[B].res )

//#define FFRQCNV( A, B )         (float) ( ( (float) B * gFreqRes[A].res) + gFreqRes[A].offset )
#endif

#ifdef _WIN32
#define PrintFunction { printf( "\n%s" , __FUNCTION__ ); Log( enNormal, "%s", __FUNCTION__ ); }
#else
#define PrintFunction { }
#endif

#if defined(_WIN32)
//#define printf                  Printf

#ifdef __cplusplus
extern "C"
{
#endif

  // void Printf( char *format, ... );

#ifdef __cplusplus
}
#endif

#define _printf                 printf

#else

#endif

/*
/////////////////////////////////////////////////////////////////////////////////////////
//  Convert AET res. to IPL res.
//
*/
#define AET2IPL_PW( A )       ( A * 50 )
#define AET2IPL_PRI( A )      ( A * 50 )
#define AET2IPL_FREQ( A )     ( A * 1000 )
#define AET2IPL_PRD( A )      (UINT) ( ( ( 50. / 1000. ) * (float) A ) + 0.5 )
#define IPL2AET_PRD( A )      (UINT) ( ( 20. * (float) A ) + 0.5 )
#define IPL2AET_FREQ( A )     UDIV( A, 1000 )

#define _HEADER_PRINT( A )    printf( "A" );

#if defined(M68K) && !defined(_MBIT)
#define WhereIs       printf( "...in %s file, %d line(s)" , __FILE__, __LINE__ )
#define Hold          printf( "\n Press Any Key...." ), WhereIs, sc_getc()
#endif

#if defined(M68K) && defined(_MBIT)
#define WhereIs       RC_Print( "...in %s file, %d line(s)" , __FILE__, __LINE__ )
#define Hold          RC_Print( "\n Press Any Key...." ), WhereIs, sc_getc()
#endif

#if !defined(M68K) && !defined(_MBIT)
#ifndef WhereIs
#define WhereIs       printf( "...in %s file, %d line(s)" , __FILE__, __LINE__ )
#endif

#define Hold          printf( "\n Press Any Key...." ), WhereIs, sc_getc()

#endif


void _InitResolution();

#ifdef _MAIN_GLOBALS_
float _spOneSec;
float _spOneMilli;
float _spOneMicrosec;
float _spOneNanosec;

float _spAMPres;
float _spAOAres;
float _spTOAres;
float _spPWres;

float _toaRes[en50MHZ_BW+1] = { (float) 65.104167, (float) 8.138021 } ;
float _frqRes[2] = { (float) 0.117, (float) 65.104167 } ;

int _spAnalMinPulseCount;

void _InitResolution()
{
#ifdef _ELINT_
    m_enBandWidth = pPDWData->enBandWidth;

    _spOneSec = FDIV( 1000000000, _toaRes[m_enBandWidth] );
    _spOneMilli = FDIV( 1000000, _toaRes[m_enBandWidth] );
    _spOneMicrosec = FDIV( 1000, _toaRes[m_enBandWidth] );
    _spOneNanosec = FDIV( 1, _toaRes[m_enBandWidth] );

    _spAOAres = (float) 0.01;
    _spAMPres = (float) (0.25);
    _spPWres = _spOneMicrosec;

#elif defined(_POCKETSONATA_)
    _spOneSec = FDIV( 1000000000, 6.48824007 );
    _spOneMilli = FDIV( 1000000, 6.48824007 );
    _spOneMicrosec = FDIV( 1000, 6.48824007 );
    _spOneNanosec = FDIV( 1, 6.48824007 );

    _spAOAres = (float) ( 0.351562 );
    _spAMPres = (float) (0.351562);
    _spPWres = _spOneMicrosec;

#elif defined(_SONATA_)
    _spOneSec = 20000000.;
    _spOneMilli = FDIV( _spOneSec, 1000. );
    _spOneMicrosec = FDIV( _spOneMilli, 1000. );
    _spOneNanosec = FDIV( _spOneMicrosec, 1000. );

    _spAOAres = (float) ( 0.351562 );
    _spAMPres = (float) (0.351562);
    _spPWres = (float) ( 50 );

#endif
}

#else
extern float _spOneSec;
extern float _spOneMilli;
extern float _spOneMicrosec;
extern float _spOneNanosec;

extern float _spAMPres;
extern float _spAOAres;
extern float _spTOAres;
extern float _spPWres;

extern float _toaRes[en50MHZ_BW+1];
extern float _frqRes[2];

extern int _spAnalMinPulseCount;

#endif

#endif   /* end of ifdef _COMMON_H */
