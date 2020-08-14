/*!
  \file     _macro.h
  \brief    매크로 정의문을 설명한다.
	\version  0.0.1
*/

#ifndef  _MACRO_H
#define  _MACRO_H

#include "../INC/PDW.h"

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

#endif

#define DivideBy2( A, B )       ( ( (A) + (B) + 1 ) / 2 )		//!< 나누기 2
#define _DIV( A, B )            (UINT) ( (float) (A) / (float) (B) )	//!< 정수 나누기
#define UDIV( A, B )            (UINT) ( (float) (A) / (float) (B) + 0.5 )
#define NDIV( A, B )            (UINT) ( (float) (A) / (float) (B) - 0.5 )

#define F_NDIV( A, B )          (UINT) ( (float) (A) / (float) (B) - 0.5 )
#define C_NDIV( A, B )          (UINT) ( (float) (A) / (float) (B) + 0.5 )
#define FDIV( A, B )            (float) ( (float) (A) / (float) (B) )
#define F_UDIV( A, B )          (UINT) ( (float) (A) / (float) (B) - 0.5 )
#define C_UDIV( A, B )          (UINT) ( (float) (A) / (float) (B) + 0.5 )
#define IDIV( A, B )            ( ( (A) > 0 ) ? UDIV(A,B) : NDIV(A,B) )
#define F_IDIV( A, B )          ( ( (A) > 0 ) ? F_UDIV(A,B) : F_NDIV(A,B) )
#define C_IDIV( A, B )          ( ( (A) > 0 ) ? C_UDIV(A,B) : C_NDIV(A,B) )
#define IMUL( A, B )            ( ( (A) > 0 ) ? UMUL(A,B) : NMUL(A,B) )
#define UADD( A, B )            (UINT) ( (float) (A) + (float) (B) + 0.5 )
#define FADD( A, B )            (float) ( (float) (A) + (float) (B) )
#define FMUL( A, B )            ( (float) (A) * (float) (B) )
#define TMUL( A, B )            (_TOA) ( (_TOA) (A) * (_TOA) (B) + 0.5 )
#define TDIV( A, B )            (_TOA) ( (_TOA) (A) / (_TOA) (B) + 0.5 )
#define UMUL( A, B )            (UINT) ( ( (float) (A) * (float) (B) ) + 0.5 )
#define NMUL( A, B )            (UINT) ( (float) (A) * (float) (B) - 0.5 )
#define F_MUL( A, B )           (UINT) ( ( (float) (A) * (float) (B) ) - 0.5 )
#define C_MUL( A, B )           (UINT) ( ( (float) (A) * (float) (B) ) + 0.999 )
#define WeightedVal( A,B,C,D)   UDIV( (A*C) + (B*D), C+D)
#define WeightedAdvVal(A,B,C)   UDIV( FADD(FMUL( A, B ), C), FADD( 1, A ) )
#define ThreeOverTen( A )       ( UINT ) ( ( ( ( A ) * 3 ) + 5 ) / 10 )
#define HalfThreeOverTen( A )   ( UINT ) ( ( ( ( A ) * 3 ) + 10 ) / 20 )



#define _max(a,b)               ( ( (int)(a) > (int)(b) ) ? (a) : (b) )
#define _min(a,b)               ( ( (int)(a) < (int)(b) ) ? (a) : (b) )





#define BIT_MERGE(high,low)     ( ( ((UINT)high) << 8 ) | low )


//#define _diffabs(a, b)          ( (a) > (b) ? (a)-(b) : (b)-(a) )
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
#define FRQMhzCNV( A, B )		IMUL( (B), ( gFreqRes[(A)].res ) )
#define IFRQMhzCNV( A, B )		IDIV( (B), ( gFreqRes[(A)].res ) )
#define TOAusCNV( A )           IDIV( (A), _spOneMicrosec )
#define ITOAusCNV( A )			IMUL( (A), _spOneMicrosec )					// X us 로 값으로 변환함
#define IFTOAusCNV( A )			FMUL( (A), _spOneMicrosec )					// X us 로 값으로 변환함
#define ITTOAusCNV( A )			TMUL( (A), _spOneMicrosec )					// X us 로 값으로 변환함

#define PWCNV( A )				IDIV( A, _spOneNanosec )
#define IPWCNV( A )				IMUL( (A), _spOneMicrosec )
#define AOACNV( A )             IMUL( (A), _spAOAres )
#define IAOACNV( A )            IDIV( (A), _spAOAres )

#define AddAOA(A, B)            ( ( A + B + MAX_AOA) % MAX_AOA )
#define SubAOA(A, B)            ( ( A - B + MAX_AOA) % MAX_AOA )
//#define FRQRESCNV( A, B )				(UINT) ( abs( (int) IMUL( gFreqRes[(A)].res, (B) ) ) )
#define FTOAsCNV( A )			FDIV( (A), _spOneMicrosec )

#define PACNV( A )				(float)( FMUL( (A), _spAMPres ) - (float) 110. )
#define IPACNV( A )				FDIV( (A), _spAMPres )

#else
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
#define PACNV( A, B )           IDIV( FPACNV(A,B), 1 )
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
#define FFRQCNV( A )						( FMUL( gFreqRes[0].res, (A) ) + gFreqRes[0].offset )
//#define FFRQCNV( A, B )         (float) ( ( (float) B * gFreqRes[A].res) + gFreqRes[A].offset )
#endif

#ifdef _WIN32
#define PrintFunction { printf( "\n%s" , __FUNCTION__ ); Log( enNormal, "%s", __FUNCTION__ ); }
#else
#define PrintFunction { }
#endif

#if defined(_WIN32)
#define printf                  Printf

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

#endif   /* end of ifdef _COMMON_H */
