/*!
  \file     _macro.h
  \brief    매크로 정의문을 설명한다.
    \version  0.0.1
*/



#ifndef  __MACRO_H
#define  __MACRO_H

#include "../INC/PDW.h"
#include "_Define.h"


//#define DFD_FREQ_OFFSET		(1900)

#define _spSONATAPAoffset			(-70)					// amplitude initial value
#define _spSONATAAMPres       (0.3125)			// dB */
#define	_spSONATAAOAmax				(0x1FF)	
#define	_spSONATAAmpmax				(0xFF)	


enum ENUM_UnitID {
	enUnknown = -1,

	enSHU = 0,
	enRSA,
	enZPocketSonata

} ;

enum ENUM_BoardID {
    enPRC_Unknown=0,

    enPRC1=1,
    enPRC2,
    enPRC3,
    enPRC4,
    enPRC5,
    enPRC6,
    enMAXPRC,

    enMaster=enPRC3

};

#define _SAFE_FREE(A)           if( A != NULL ) { free( A ); A = NULL; }
#define _SAFE_DELETE(A)         if( A != NULL ) { delete A; A = NULL; }


#define _SAFE_NEW(A, B)         try { \
                                    A = new B;    \
                                } \
                                catch( bad_alloc ex ) { \
                                    TRACE( "new memory[##A]:%s" , ex.what() ); \
                                }


#define _SAFE_MALLOC(A, B, C )  if( A == NULL ) { \
                                    A = ( B * ) malloc( C ); \
                                    if( A == NULL ) { \
                                        TRACE( "malloc error new memory[%s]" , #A ); \
                                    } \
                                } \
                                else { TRACE( "Already malloc memory[%s]" , #A ); }



#define DivideBy2( A, B )       ( ( (A) + (B) + 1 ) / 2 )		//!< 나누기 2
#define _DIV( A, B )            (UINT) ( (float) (A) / (float) (B) )	//!< 정수 나누기
#define UDIV( A, B )            (unsigned int) ( (float) (A) / (float) (B) + 0.5 )
#define NDIV( A, B )            (int) ( (float) (A) / (float) (B) - 0.5 )

#define F_NDIV( A, B )          (UINT) ( (float) (A) / (float) (B) - 0.5 )
#define C_NDIV( A, B )          (UINT) ( (float) (A) / (float) (B) + 0.5 )
#define FDIV( A, B )            (float) ( (float) (A) / (float) (B) )
#define F_UDIV( A, B )          (int) ( (float) (A) / (float) (B) - 0.5 )
#define C_UDIV( A, B )          (int) ( (float) (A) / (float) (B) + 0.5 )
#define IDIV( A, B )            ( ( (A) > 0 ) ? (int) UDIV(A,B) : NDIV(A,B) )
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

#if defined(_ELINT_) || defined(_XBAND_)
#define FRQMhzCNV( A, B )		IMUL( (B), ( 0.001) )
#define I_FRQMhzCNV( A, B )		IMUL( (B), ( 0.001) )
#define FFRQMhzCNV( A, B )		(float) ( (float)(B) * (float) (0.001) )
#define DFRQMhzCNV( A, B )		(double) ( (double)(B) * (double) (0.001) )
#define IFRQMhzCNV( A, B )		IDIV( (B), ( 0.001) )
#define TOAusCNV( A )           FDIV( (A), _spOneMicrosec )
#define I_TOAusCNV( A )         IDIV( (A), _spOneMicrosec )
#define ITOAusCNV( A )			IMUL( (A), _spOneMicrosec )					
#define UTOAusCNV( A )			UMUL( (A), _spOneMicrosec )					
#define IFTOAusCNV( A )			FMUL( (A), _spOneMicrosec )					
#define ITTOAusCNV( A )			TMUL( (A), _spOneMicrosec )					
#define TOAmsCNV( A )           IMUL( (A), _spOneMilli )					

#define PWCNV( A )				FDIV( (A*1000.), _spOneMicrosec )
#define I_PWCNV( A )			IDIV( (A*1000.), _spOneMicrosec )
#define DPWCNV( A )				FDIV( (A*1000.), _spOneMicrosec )
#define IPWCNV( A )				IDIV( (A*_spOneMicrosec), 1000. )
#define AOACNV( A )             FMUL( (A), _spAOAres )
#define I_AOACNV( A )           IMUL( (A), _spAOAres )
#define FAOACNV( A )            FMUL( (A), _spAOAres )
#define IAOACNV( A )            IDIV( (A), _spAOAres )

#define I_IPACNV( A )			IDIV( (A), _spAMPres )

#define I_IFRQMhzCNV( A, B )	IDIV( FMUL( B, 1000. ), (0.001) )

#define IPWCNVLOW( A )			_DIV( (A*_spOneMicrosec), 1000. )
#define IPWCNVHGH( A )			UDIV( (A*_spOneMicrosec), 1000. )

#define AddAOA(A, B)            ( ( A + B + MAX_AOA) % MAX_AOA )
#define SubAOA(A, B)            ( ( A - B + MAX_AOA) % MAX_AOA )
//#define FRQRESCNV( A, B )		(UINT) ( abs( (int) IMUL( gFreqRes[(A)].fRes, (B) ) ) )
#define FTOAsCNV( A )			FDIV( (A), _spOneMicrosec )

#define PACNV( A )				(float)( FMUL( (A), _spAMPres ) - (float) 110. )
#define IPACNV( A )				IDIV( (A + 110.), _spAMPres )

#define FFRQCNV( A, B )			( FMUL( gFreqRes[0].fRes, (A) ) + gFreqRes[0].iOffset )


#define F_FRQMhzCNV( A, B )		FMUL( (B), (_frqRes[0]) )
#define F_IFRQMhzCNV( A, B )	FDIV( (B), (_frqRes[0]) )

#define FPWCNV( A )             FMUL( (A), _spOneNanosec )

#define FPACNV( A )				(float)( FMUL( (A), _spAMPres ) - (float) 110. )



////////////////////////////////////////////////////////////////////////////////////////
#elif defined(_POCKETSONATA_)
#define FFRQCNV( A, B )         CPOCKETSONATAPDW::DecodeFREQMHz( B )
#define FRQMhzCNV( A, B )		FDIV( ( FMUL( gFreqRes[(A)].fRes, (B) ) + gFreqRes[(A)].iOffset ), 1000 )  //CPOCKETSONATAPDW::DecodeFREQMHz( B )
#define I_FRQMhzCNV( A, B )		IDIV( ( FMUL( gFreqRes[(A)].fRes, (B) ) + gFreqRes[(A)].iOffset ), 1000 )  //CPOCKETSONATAPDW::DecodeFREQMHz( B )
#define FFRQMhzCNV( A, B )		CPOCKETSONATAPDW::DecodeFREQMHz( B )
#define IFRQMhzCNV( A, B )		FDIV( ( FMUL( B, 1000. ) - gFreqRes[(A)].iOffset ), gFreqRes[(A)].fRes )
#define I_IFRQMhzCNV( A, B )	IDIV( ( FMUL( B, 1000. ) - gFreqRes[(A)].iOffset ), gFreqRes[(A)].fRes )
#define IFRQMhz( A, B )         CPOCKETSONATAPDW::EncodeFREQMHzCeiling( B )
#define IFRQCNV( A, B )         IDIV( (B), ( gFreqRes[A].fRes ) )
#define I_IFRQCNV( A, B )       IDIV( (B), ( gFreqRes[A].fRes ) )

//#define IFRQMhzCNV( A, B, C )   CPOCKETSONATAPDW::EncodeRealFREQMHz( A )

#define IFRQMhzLOW( A )         CPOCKETSONATAPDW::EncodeFREQMHzFloor( A )
#define IFRQMhzHGH( A )         CPOCKETSONATAPDW::EncodeFREQMHzCeiling( A )

#define TOAusCNV( A )           CPOCKETSONATAPDW::DecodeTOAus( A )
#define IFTOAusCNV( A )			CPOCKETSONATAPDW::DecodeTOAus( A )
#define I_TOAusCNV( A )         (int) ( CPOCKETSONATAPDW::DecodeTOAus( A ) + 0.5 )
#define TOAmsCNV( A )           CPOCKETSONATAPDW::DecodeTOAms( A )
#define FTOAsCNV( A )			CPOCKETSONATAPDW::DecodeTOAs( A )
#define ITOAusCNV( A )			CPOCKETSONATAPDW::EncodeTOAus( A )
#define UTOAusCNV( A )			(unsigned int) CPOCKETSONATAPDW::EncodeTOAus( A )
#define ITTOAusCNV( A )			CPOCKETSONATAPDW::EncodeTOAus( A )

#define PWCNV( A )				CPOCKETSONATAPDW::DecodePWus( A )
#define I_PWCNV( A )			(int) ( CPOCKETSONATAPDW::DecodePWus( A ) + 0.5 )
#define IPWCNV( A )				IMUL( (A), _spOneNanosec )
#define FPWCNV( A )             FMUL( (A), _spOneNanosec )

#define IPWCNVLOW( A )			CPOCKETSONATAPDW::EncodePWFloor( A )
#define IPWCNVHGH( A )			CPOCKETSONATAPDW::EncodePWCeiling( A )

#define AOACNV( A )             CPOCKETSONATAPDW::DecodeDOA( A )
#define I_AOACNV( A )           IMUL( CPOCKETSONATAPDW::DecodeDOA( A ), 1.0 )
#define IAOACNV( A )            CPOCKETSONATAPDW::EncodeDOA( A )
#define FAOACNV( A )            CPOCKETSONATAPDW::DecodeDOA( A )

#define AddAOA(A, B)            ( ( A + B + MAX_AOA) % MAX_AOA )
#define SubAOA(A, B)            ( ( A - B + MAX_AOA) % MAX_AOA )


#define PACNV( A )				CPOCKETSONATAPDW::DecodePA( A )
#define IPACNV( A )				FDIV( (A), _spAMPres )
#define I_IPACNV( A )			IDIV( (A), _spAMPres )
#define FPACNV( A )				(float)( FMUL( (A), _spAMPres ) - (float) 110. )

#define F_FRQMhzCNV( A, B )		FMUL( (B), 0 )

////////////////////////////////////////////////////////////////////////////////////////
#elif defined(_SONATA_)
#define FFRQCNV( A, B )             FMUL( (B), ( gFreqRes[(A)].fRes ) )
#define F_FRQCNV( A, B )            (UINT) ( F_MUL( gFreqRes[(A)].fRes, (B) ) + gFreqRes[(A)].iOffset )
#define C_FRQCNV( A, B )            (UINT) ( C_MUL( gFreqRes[(A)].fRes, (B) ) + gFreqRes[(A)].iOffset )
#define FRQMhzCNV( A, B )           IMUL( (B), ( gFreqRes[(A)].fRes ) )
#define I_FRQMhzCNV( A, B )         IMUL( (B), ( gFreqRes[(A)].fRes ) )
#define IFRQMhzCNV( A )             IDIV( (A), ( gFreqRes[0].fRes ) )
#define IFRQCNV( A, B )             IDIV( (A), ( gFreqRes[0].fRes ) )

#define IFRQMhzLOW( A )             F_IDIV( (A), ( gFreqRes[0].fRes ) )
#define IFRQMhzHGH( A )             C_IDIV( (A), ( gFreqRes[0].fRes ) )

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

#define AOACNV( A )             IMUL( (A), _spAOAres )
#define I_AOACNV( A )           IMUL( (A), _spAOAres )
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
#define FFRQCNV( A, B )         FMUL( (B), ( gFreqRes[(A)].fRes ) )
#define FFRQCNV( A, B )         FMUL( (B), ( gFreqRes[(A)].fRes ) )
#define AddAOA(A, B)            ( ( A + B + MAX_AOA) % MAX_AOA )
#define SubAOA(A, B)            ( ( A - B + MAX_AOA) % MAX_AOA )

#define TOAsCNV( A )			UDIV( (A), _spOneSec )
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
#define FRQRESCNV( A, B )		(UINT) ( abs( (int) IMUL( gFreqRes[(A)].fRes, (B) ) ) )
#define FRQCNV( A, B )          (UINT) ( UMUL( gFreqRes[(A)].fRes, (B) ) + gFreqRes[(A)].iOffset )
#define F_FRQCNV( A, B )        (UINT) ( F_MUL( gFreqRes[(A)].fRes, (B) ) + gFreqRes[(A)].iOffset )
#define C_FRQCNV( A, B )        (UINT) ( C_MUL( gFreqRes[(A)].fRes, (B) ) + gFreqRes[(A)].iOffset )
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
//#define FPACNV( A, B )					(float) ( ( (float) (A) * gPaRes[B].fRes ) + gPaRes[B].iOffset )
#define FPACNV( A )				(float) ( ( (float) (A) * gPaRes[0].fRes ) + gPaRes[0].iOffset )
#define FDBCNV( A, B )			(float) ( ( (float) (A) / gPaRes[B].fRes ) )
#define UDBCNV( A, B )			UDIV( (A), gPaRes[B].fRes )


//#define FFRQCNV( A, B )         (float) ( ( (float) B * gFreqRes[A].fRes) + gFreqRes[A].iOffset )
#endif

#ifdef _WIN32
#define PrintFunction { printf( "\n%s" , __FUNCTION__ ); g_pTheLog->LogMsg( enNormal, "%s", __FUNCTION__ ); }
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

#ifdef _WIN32
#define WhereIs									TRACE( "...in %s file, %d line(s)" , __FILE__, __LINE__ )
#else
#define WhereIs									printf( "...in %s file, %d line(s)" , __FILE__, __LINE__ )
#endif

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

#if defined(_ELINT_)
float _frqRes[en50MHZ_BW+1] = { (float) 0.001, (float) 0.001 } ;
#elif defined(_XBAND_)
float _frqRes[en50MHZ_BW+1] = { (float) 0.001, (float) 0.001 } ;
//float _frqRes[en50MHZ_BW+1] = { (float) 0.117, (float) 1.875 } ;
#else
float _frqRes[en50MHZ_BW+1] = { (float) 0.117, (float) 65.104167 } ;
#endif


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

#endif   /* end of ifdef _COMMON_H */
