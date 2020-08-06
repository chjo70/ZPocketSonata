/*!
  \file     _macro.h
  \brief    매크로 정의문을 설명한다.
	\version  0.0.1
*/

#ifndef  _MACRO_H
#define  _MACRO_H

#define DFD_FREQ_OFFSET		(1900)

#define _spSONATAPAoffset			(-70)					// amplitude initial value
#define _spSONATAAMPres       (0.3125)			// dB */
#define	_spSONATAAOAmax				(0x1FF)	
#define	_spSONATAAmpmax				(0xFF)	

#define	FREQ_MIN			(500)			// 최소 주파수
#define	FREQ_MAX			(18000)


struct FREQ_RESOL {
	// frequency band code를 위한 구조체 
	UINT min;       // min frequency
	UINT max;       // max frequency
	float res;			// 각 구간에 따른 resolution
}  ;

struct PA_RESOL {
	// frequency band code를 위한 구조체 
	UINT min;       // min frequency
	UINT max;       // max frequency
	float offset;      // max frequency
	float res;			// 각 구간에 따른 resolution
}  ;


#ifdef _MAIN_

// SONATA 변환식
FREQ_RESOL gFreqRes[ 4 ] =
{
	{    0,     0, 0     }, 
	{    0,  2560, 0.625 },   /* LOW  FREQUENCY */
	{ 1280,  6400, 1.25  },   /* MID  FREQUENCY */
	{ 5866, 18740, 1.5   } } ;

PA_RESOL gPaRes[ 6 ] = { {     0,     0,  (float) _spSONATAPAoffset, _spSONATAAMPres }, 
												{  2000,  6000,  (float) _spSONATAPAoffset, _spSONATAAMPres },		/* 저대역		*/
												{  5500, 10000,  (float) _spSONATAPAoffset, _spSONATAAMPres },		/* 고대역1	*/
												{ 10000, 14000,  (float) _spSONATAPAoffset, _spSONATAAMPres },		/* 고대역2	*/
												{ 14000, 18000,  (float) _spSONATAPAoffset, _spSONATAAMPres },		/* 고대역3	*/
												{     0,  5000,  (float) -54.14071, (float) 0.24681 } };		/* C/D			*/

// 인천공항 ELINT
float _toaRes[en50MHZ_BW+1] = { (float) 65.104167, (float) 8.138021 } ;
//float _frqRes[en50MHZ_BW+1] = { (float) 0.117, (float) 65.104167 } ;
float _frqRes[en50MHZ_BW+1] = { (float) 0.001, (float) 0.001 } ;

float _spAMPres;
float _spAOAres=(float) 0.01;
float _spTOAres;
float _spPWres;

float _spOneSec;
float _spOneMilli;
float _spOneMicrosec;
float _spOneNanosec;

float _spFreqMin;
float _spFreqMax;

// #define   _spAOAres       (0.351562)		// Degree */
// #define   _spTOAres       (0.000000025)		// SEC(25 ns) */
// #define   _spPWres        (25.)				// pw res.

#else
extern FREQ_RESOL gFreqRes[ 4 ];
extern PA_RESOL gPaRes[ 6 ];

extern float _toaRes[en50MHZ_BW+1];
extern float _frqRes[en50MHZ_BW+1];

extern float _spFreqMin;
extern float _spFreqMax;

#endif



#define BIT_MERGE(high,low)     ( ( ((UINT)high) << 8 ) | low )


#define DivideBy2( A, B )       ( ( (A) + (B) + 1 ) / 2 )		//!< 나누기 2
#define _DIV( A, B )            (UINT) ( (float) (A) / (float) (B) )	//!< 정수 나누기
#define UDIV( A, B )            (UINT) ( (float) (A) / (float) (B) + 0.5 )
#define NDIV( A, B )            (UINT) ( (float) (A) / (float) (B) - 0.5 )

#define F_FRQMhzCNV( A, B )		FMUL( (B), (_frqRes[0]) )
#define FRQMhzCNV( A, B )		IMUL( (B), (_frqRes[0]) )
#define IFRQMhzCNV( A, B )		IDIV( (B), (_frqRes[0]) )

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
#define _diffabs(a, b)          ( (a) > (b) ? (a)-(b) : (b)-(a) )
#define _abs(a)                 ( (a) >= 0 ? (a) : -(a) )
#define High( A )               ( (int) A >> 8 ) & 0x00ff
#define Low( A )                ( A & 0x00ff )

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
#define FRQRESCNV( A, B )		(UINT) ( abs( (int) IMUL( gFreqRes[(A)].res, (B) ) ) )
#define FRQCNV( A, B )          (UINT) ( UMUL( gFreqRes[(A)].res, (B) ) + gFreqRes[(A)].offset )
#define F_FRQCNV( A, B )        (UINT) ( F_MUL( gFreqRes[(A)].res, (B) ) + gFreqRes[(A)].offset )
#define C_FRQCNV( A, B )        (UINT) ( C_MUL( gFreqRes[(A)].res, (B) ) + gFreqRes[(A)].offset )
#define AOACNV( A )             FMUL( (A), _spAOAres )
#define F_AOACNV( A )           (UINT) ( (A) * _spAOAres )
#define C_AOACNV( A )           (UINT) ( C_MUL( (A), _spAOAres ) )

//#define PWCNV( A )              UMUL( (A), _spPWres )
#define PWCNV( A )              FDIV( (A), _spPWres )

#define F_PWCNV( A )            F_MUL( (A), _spPWres )
#define C_PWCNV( A )            C_MUL( (A), _spPWres )
//#define PACNV( A, B )           IDIV( FPACNV(A,B), 1 )
#define F_PACNV( A, B )         F_IDIV( FPACNV(A,B), 1 )
#define C_PACNV( A, B )         C_IDIV( FPACNV(A,B), 1 )

#define PACNV( A )							(float) ( FMUL( (A), _spAMPres ) - (float) 110. )
#define IPACNV( A )							(float) ( IDIV( (A), _spAMPres ) - (float) 110. )


//#define F_PACNV( A )            ( F_MUL( (A), _spAMPres ) - _spPAoffset )
//#define C_PACNV( A )            ( C_MUL( (A), _spAMPres ) - 74.6875 )
#define FAOACNV( A )            (float) ( (float) A * _spAOAres )
#define FPWCNV( A )             (float) ( (float) A * _spPWres )
//#define FPACNV( A, B )					(float) ( ( (float) (A) * gPaRes[B].res ) + gPaRes[B].offset )


#define FPACNV( A )							(float) ( ( (float) (A) * gPaRes[0].res ) + gPaRes[0].offset )


#define FDBCNV( A, B )					(float) ( ( (float) (A) / gPaRes[B].res ) )
#define UDBCNV( A, B )					UDIV( (A), gPaRes[B].res )
//#define FFRQCNV( A )						( FMUL( gFreqRes[0].res, (A) ) + gFreqRes[0].offset )
#define FFRQCNV( A, B )         (float) ( ( (float) B * gFreqRes[A].res) + gFreqRes[A].min )

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

#endif   /* end of ifdef _COMMON_H */
