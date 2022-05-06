/****************************************************************************************
 파 일 명 : npwmake.c  by 서성태
 목    적 : npw 화일을 만듦
 사 용 법 : mak화일을 만들어 mak화일에 수록된 정보대로 npw화일을 생성한다. 
			mak_filename[.mak]은 기존의 mak 화일을 카피/수정하여 사용한다.
			Header에 적힌 내용대로 입력한다. 한줄에 한 화일씩 생성.
			mak화일의 줄 수 만큼 여러개의 npw화일을 생성할 수 있다. 
 중요자료구조 :
*****************************************************************************************/

#include "stdafx.h"

#define _MAIN_GLOBALS_

#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../../files/Anal/Collect/GenPDW/CGenPDW.h"

#include "../../files/Utils/ccommonutils.h"

////////////   Sub Function 
int	wanna_create( char *filename );
UINT GetBandOfFreq( UINT Freq );
float ConvertFreq( float Freq, UINT band );
//void getParam( void );
// void setParam( void );
// void makeFreqPdw( void );
// void makePRIPdw( UINT pul_idx );
// void makePAPdw( UINT lob_idx );

////////////   공용 상수 
#define PIE					3.141592
//#define ONE_SEC             20000000			// 1 sec  / 50 ns */
#define ONE_MILLISEC        (ONE_SEC/1000)		// 1 msec / 50 ns */
//#define ONE_MICROSEC        (ONE_MILLISEC/1000)	// 1 usec / 50 ns */
#define MAX_TOA				((UINT)-1)	// TOA One Turn

//enum	mark { Unmark=0,  Mark=1 };

// FREQ_RESOL  l_freq_resol[4] = {
//                {    0,  2560, 0.625 },     /* low  Freq */
//                { 1280,  6000, 1.25  },     /* mid  Freq */
//                { 5866, 18000, 1.5   },     /* high Freq */
// 			   {    0,     0, 0.    }
//             };
// 
// FREQ_RESOL  l_freq_rimit[4] = {
//                {    0,  2000, 0.625 },     /* low  Freq */
//                { 2001,  6000, 1.25  },     /* mid  Freq */
//                { 6001, 18152.5, 1.5   },     /* high Freq */
//                {    0,     0, 0     }
//             };

////////////   공용변수 
// extern	int errno;
// FILE		*wfp = NULL;
// FILE		*rfp = NULL;
// 
// char		szMakfilename[MAX_PATH];
// TNEW_PDW	new_pdw;                

/*
1.  Idx	        // 1 부터 시작 
2.  Filename
3.  Count
4.  FstTOA[us]	// 최초 TOA
5.  Stat 
6.  DV 
7.  AOA[deg] 
8.  FType	
9.  Freq[MHz] 
10. BW[MHz] 
11. FPatType 
12. FPatPrd 
13. FHopLvl 
14. HL[0] HL[1] HL[2] HL[3] HL[4] HL[5] HL[6] HL[7] HL[8] HL[9] HL[10] HL[11] HL[12] HL[13] HL[14] HL[15] 
15. PType 
16. PRI[us] 
17. Jitp 
18. PSLvl 
19. PL[0] PL[1] PL[2] PL[3] PL[4] PL[5] PL[6] PL[7] PL[8] PL[9] PL[10] PL[11] PL[12] PL[13] PL[14] PL[15] 
20. PPatType 
21. PPatPrd 
22. PdnsCnt 
23. PA[dBm] 
24. PW[ns] 
25. Fmop[MHz] 
26. Pmop  
27. ScanType 
28. ScanPrd[ms] 
29. SPul_Cnt
*/
////////////////    Read Parameter
// 	UINT		Idx;			// 발생 신호 index
// 	char		filename[50];	// 발생 신호 화일명 [영문 15자 이내]
// 	UINT		Count;			// 발생 펄스수 
// 	UINT		FstTOA;			// 초기 TOA offset [us]
// 	UINT		Stat;			// normal=0, Pmop=1, chirp_up=2, chirp_dn=3, cw=4, 우현보정=12, 좌현보정=13, bit=15
// 	UINT		DV;				// Direction Valid=1, Not Valid=0
//     UINT		AOA;			// 계산을 위해 AOA 값을 저장한 변수    
// 	char		FType[3];		// 주파수 형태  : FIX(fixed)   AGI(agile)    PAT(pattern)  HOP(hopping)
// 
//     UINT		Freq;			// 중심 주파수 [MHz]
// 	UINT		uiCenterFreq;			// 중심 주파수 [MHz]
// 	UINT		uiPatternFreq;
// 
//     UINT		Bc;
// 	UINT		BW;				// 주파수 폭 [MHz]
// 	char		FPatType[3];	// 주파수 패턴 형태 : SIN(sine)  TRI(triangle)   SW+(saw+)     SW-(saw-)
// 	//UINT		FPatPrd;		// 주파수 패턴 주기[msec]
// 	UINT		FHopLvl;		// 주파수 Hopping level 수 
// 	float		HL[16];			// 주파수 Hopping level 값[MHz]
// 	char		PType[3];		// PRI 형태   : STB(stable)  STG(stagger)  JIT(jitter)   DNS(dwell & switch) 
// 	int			PRI;			// PRI [us]
// 	float		Jitp;			// PRI Jitter%
// 	UINT		PSLvl;			// PRI switch Level 수 
// 	UINT		PL[16];			// PRI switch level 값 [usec]
// 	char		PPatType[3];	// PRI 패턴 형태  : SIN(sine)  TRI(triangle)  SW+(saw+)     SW-(saw-)
// 	//UINT		PPatPrd;		// PRI 패턴 주기 [msec]
// 	UINT		PdnsCnt;		// D&S 한 level의 펄스수 
// 	float		PA;				// 펄스 세기 [dBm]
// 	UINT		PW;				// 펄스폭 [nsec]
// 	UINT		Fmop;			// Freq Diff [MHz]
// 	UINT		Pmop;			// Phase Modulation
// 	char		ScanType[3];	// 스캔 Type : STD(steady)  CON(conical)  CIR(circular) BID(bi-directional)  UNI(uni-directional)
// 	UINT		ScanPrd;		// scan period
// 	UINT		SPul_Cnt;		// 한 lobe내의 펄스수 
// 
// 	UINT Freq_Error;
// 	UINT Toa_Error;
// 	UINT Pw_Error;
// 	UINT Pulse_Skip;
// 
// ///////////////   Calc Parameter
// //INT		bc;			// BAND CODE
//     UINT		pFreq;
// 
// 	float		PRI_width;
// 	UINT		pPRI;
// 	UINT		toa;
// 
// 	UCHAR		pa;
// 	float		Pa_width;
// 	UCHAR		pa_array[200];
// 
// 	// Freq 
// 	UINT		FPatPrd;	// 주파수 패턴 주기
// 	float		Fpmax;		// 주파수 MAX
// 	float		Fpmin;		// 주파수 MIN
// 	float		Fslop;		// 주파수 톱니파/삼각파 기울기 
// 	UINT		Hop_idx;	// Hopping level index		
// 	UINT		Hop_cnt;	// Hopping level 펄스수 
// 
// 	// PRI
// 	UINT		PPatPrd;	// PRI 패턴 주기
// 	float		fPRI;		// float형 PRI
// 	float		Ppmax;		// PRI MAX
// 	float		Ppmin;		// PRI MIN
// 	float		Pslop;		// PRI 톱니파/삼각파 기울기 
// 	float		Pdiff;		// PRI 톱니파 펄스간 평균 간격 
// 	UINT		Dns_idx;	// D&S level index 
// 	UINT		Dns_cnt;	// D&S level 펄스수 decount용 
// 
// 	UINT		Bi1_prd;	// Bi-sector scan 주기 1
// 	UINT		Bi2_prd;	// Bi-sector scan 주기 2
// 
// 	UINT Hop_prd;


///////////////////     MAIN   ////////////////////////////

int Rand( int range );
void makePWPdw();

int main( int argc, char **argv ) 
{
    int kCount=0;

	///////////////////////////////////////////////////////
	printf( "\n < NPW MAKE PROGRAM > " );

    if( argc != 2 ) {
        printf("Usage : %s mak_filename[.mak] ", argv[0]);
        printf("\n  mak_filename[.mak]은 기존의 mak 화일을 카피/수정하여 사용한다.");
		printf("\n  Header에 적힌 내용대로 입력한다. 한줄에 한 화일씩 생성");
		printf("\n  입력된 줄만큼 출력화일이 생성된다. ");
        exit(1);
    }

    CGenPDW *pTheGenPDW;

    pTheGenPDW = new CGenPDW( 0 );
    pTheGenPDW->OpenFile( argv[1] );

    pTheGenPDW->ParseAndMakefile();



    //struct timespec tiNow;
    //CCommonUtils::GetCollectTime( &tiNow );




// 	while( ofl == Idx )
// 	{
// 		Hop_cnt = 0;
// 
// 		// mak화일에서 PRAMETER값을 읽음 
// 		getParam();
// 
// 		if( ( wfp = fopen( filename, "wb" ) ) == NULL )  
// 		{
// 			printf("\n %s File Open ERROR : %s", filename, strerror(errno));
// 			exit(1);
// 		}
// 
// 		/////////////////// SET PDW PARAMETER //////////////////////
// 		setParam();
// 
// 		/////////////////////// MAKE NPW ///////////////////////////
// 		total   = 0;
// 		Dns_idx = Rand(100) + 200;
// 		Hop_idx	= 0;
// 
// 		kCount = Rand(200) + 200;
// 
// 		for( sl=0; total < Count; sl++)
// 		{
// 			for( isl=0; isl < SPul_Cnt && total < Count ; isl++, ++kCount )		
// 			{
// 				new_pdw.item.toa_4   = ( toa >> 24 ) & 0xFF;	// TOA 값 입력 
// 				new_pdw.item.toa_3   = ( toa >> 16 ) & 0xFF;
// 				new_pdw.item.toa_2   = ( toa >> 8  ) & 0xFF;
// 				new_pdw.item.toa_1   = toa & 0xFF;
// 
// 				// 주파수 값 입력 
// 				makeFreqPdw();
// 
// 				// PRI 값 입력 
// 				makePRIPdw( total );
// 
// 				// PW 값 입력 
// 				makePWPdw();
// 
// 				// PA 값 입력 
// 				if( strcmp( ScanType, "STD" ) != 0 )	// NOT Scan Steady
// 				{
// 					makePAPdw( isl );	// next TOA 값까지 수정 
// 				}
// 	
// 				// 출력 화일에 저장
// 				if( Pulse_Skip == 0 )
// 					fwrite( (char *)&new_pdw,sizeof(TNEW_PDW),1,wfp );
// 				else {
// 					if( kCount % Pulse_Skip != 0 )
// 						fwrite( (char *)&new_pdw,sizeof(TNEW_PDW),1,wfp );
// 				}
// 
// 				// 다음 TOA 계산 
// 				toa += pPRI;
// 				total++;
// 
// 			} // for( isl=0; isl < SPul_Cnt , 스캔 Lobe내 Loop
// 
// 			// 다음 TOA 계산 
// 			if( strcmp( ScanType, "BID" ) == 0 )	// for Bi-Sector
// 			{
// 				if( sl % 2 )
// 					toa += Bi2_prd;	// scan 간격입력 
// 				else
// 					toa += Bi1_prd;	// scan 간격입력 
// 			}
// 			else if( strcmp( ScanType, "CIR" ) == 0 ||  // for Circular
// 					 strcmp( ScanType, "UNI" ) == 0 )	// for Uni-Sector
// 				toa += ScanPrd;	// scan 간격입력 
// 
// 		} // for( sl=0; total < Count; sl++),  스캔 Loop
// 
// 		printf( "\n           Make Done [ %s ]", filename );
// 		fclose( wfp );
// 
// 		// 다음 줄 Idx Read 
// 		fscanf( rfp, "%u", &Idx ); 	// Read Index 
// 		ofl++;
// 
// 	}	//	while( 1 ), 출력 화일 Loop(ofl)
// 
// 	fclose( rfp );

    delete pTheGenPDW;

    return 0;

}

/**************************************************************************************
 함 수 명 : wanna_create by 김용우  
 Input    : filename
 Output   : band code
 작 성 일 : 1998. 01. 12
 **************************************************************************************/
int	wanna_create( char *filename )
{
	char sbuf[50];

	if( access( filename, 00 ) )
		return 1;	/* file not exist */

	printf("\n File [%s] is already exist. \n", filename);
	printf(" Do you want overwrite ? (y/N)");
	fgets( sbuf, 49, stdin );
	if( toupper( sbuf[0] ) == 'Y' )
		return 1;
	return 0;
}

/**************************************************************************************
 함 수 명 : pdwcnvt by 백옥동
 Input    : Freq
 Process  : Freq를 참고로 해당 band code를 구한다
 Output   : band code
 작 성 일 : 1998. 04. 01
**************************************************************************************/
// UINT GetBandOfFreq( UINT Freq )
// {
//     UINT  i;
// 
//     /* Freq의 band code를 구한다. */
//     for( i=0; l_freq_rimit[i].resolution; i++ ) 
//     {
//         if( Freq >= l_freq_rimit[i].min  &&  Freq <= l_freq_rimit[i].max ) 
//             return( i );
//         else ;
//     } /* end of for */
// 
//     return( -1 );
// }

/**************************************************************************************
 함 수 명 : ConvertFreq by 백옥동
 Input    : Freq, band code
 Process  : band code를 index로 해당 resolution과 min값으로 새로운 Freq를 구함
 Output   : 변환된 Freq
 작 성 일 : 1998. 04. 01
**************************************************************************************/
// float ConvertFreq( float freq, UINT band )
// {
//     freq -= l_freq_resol[band].min;
//     freq /= l_freq_resol[band].resolution;
// 
//     return( freq );
// }

/************************************************************************************
 함 수 명 : getParam
 Input    : 
 Process  : mak 화일에서 parameter값을 읽어들임 
 Output   : 
*************************************************************************************/


/************************************************************************************
 함 수 명 : setParam
 Input    : 
 Process  : 화일에서 읽어들인 parameter값을 PDW format에 맞도록 변환
 Output   : 
*************************************************************************************/
// void setParam( void )
// {
// 	UINT	i;
// 
// 	/////////////////// SET PDW PARAMETER //////////////////////
// 
// 	// Decimal to Binary( 보기 값에서 PDW포멧 값으로 전환 )
// 	AOA  = (UINT)  ( AOA / DIRECTION_RESOL );	// 방위 
// 	toa	 = (UINT)  ( FstTOA * ONE_MICROSEC );	// TOA
// 
// 
// 	if( (Bc = GetBandOfFreq( (UINT)Freq )) == -1 )// Band Code
// 	{
// 		printf(" \n [E] Not Vaild Freq " );
// 		exit(1);
// 	}
// 
// 	// Freq = ConvertFreq( Freq, Bc );				// 주파수 
// 
// 	// PRI	 = (UINT)  ( PRI * ONE_MICROSEC );		// PRI
// //	PRI	 = (UINT)  ( PRI * 1 );		// PRI
// //PW	 = (UINT)  ( PW  / PULSE_WIDTH_RESOL );
// 	PW	 = (UINT)  ( PW  / 1 );
// 	PA	 = (float)(( PA  - AMPLITUDE_INIT ) / AMPLITUDE_RESOL);
// 
// 	// 고정 PDW 값 저장 
// 	new_pdw.item.phase1	= 0;	// Phase Code 입력 
// 	new_pdw.item.phase2 = 1;
// 	new_pdw.item.phase3 = 2;
// 	new_pdw.item.phase4 = 3;
// 	new_pdw.pdw[3][0]   = 0xff;	// 빈곳을 1로 채움
// 	new_pdw.pdw[3][1]   = 0xff;	// PARITY ERROR방지용 
// 	new_pdw.item.stat	= Stat;
// 	new_pdw.item.dv		= DV;	
// 	new_pdw.item.band		 = Bc;
// 	new_pdw.item.pmop        = Pmop;
// 	new_pdw.item.freq_diff   = Fmop;
// 	new_pdw.item.pulse_width_l	= PW & 0xFF ;		// 펄스폭 값 입력 
// 	new_pdw.item.pulse_width_h	= ( PW >> 8 ) & 0x07;
// 	new_pdw.item.direction_l	= AOA & 0xFF;			// 방위 값 입력 
// 	new_pdw.item.direction_h	= ( AOA >> 8 ) & 0x03;
// 
// 	///////////////   주파수 TYPE 별 계산 
// 	if( strcmp( FType, "AGI" ) == 0 )			// Agile
// 	{
// 		BW = (UINT)(BW / l_freq_resol[Bc].resolution);
// 	}
// 	else if( strcmp( FType, "PAT" ) == 0 )	// FREQ Pattern 
// 	{
// 		// FPatPrd = (UINT)( FPatPrd * ONE_MILLISEC );
// 		// FPatPrd = 0.001 * FPatPrd;
// 			// BW = (float)(BW / l_freq_resol[Bc].resolution);
// //			FPatPul = (float)FPatPrd / PRI;	// 한주기당 펄스수 
// 
// 		FPatPrd = (UINT)( FPatPrd * ONE_MICROSEC );
// 		Fpmax	= (float)(Freq + BW / 2.);
// 		Fpmin	= (float)(Freq - BW / 2.);
// 		if( strcmp( FPatType, "SIN" ) == 0 )			// Freq Pattern Sine
// 		{
// 			// 2 * pi = FPatPrd ( 1주기 )
// 			// 현재 주파수(pFreq) = BW / 2 * sin( FPatPrd / 2 * pi * toa ) + Freq )
// 		}
// 		else if( strcmp( FPatType, "TRI" ) == 0 )	// Freq Pattern Triangle (주파수 패턴 삼각파)
// 		{
// 			Fslop	= (float)(BW * 1000. / (FPatPrd / 2.));   // 삼각파의 기울기 계산 
// 		}
// 		else if( strcmp( FPatType, "SW+" ) == 0 )		// Freq Pattern SAW+ (주파수 패턴 톱니파 증가)
// 		{
// 			Fslop	= (float) ( (float) ( BW / 2. ) / (float) FPatPrd );		 // 톱니파의 기울기 계산 
// 			uiPatternFreq = uiCenterFreq - ( BW / 2 );
// 		}
// 		else if( strcmp( FPatType, "SW-" ) == 0 )		// Freq Pattern SAW- (주파수 패턴 톱니파 감소)
// 		{
// 			Fslop	= (float) ( (float) ( -BW / 2. ) / (float) FPatPrd );		 // 톱니파의 기울기 계산 
// 			uiPatternFreq = uiCenterFreq - ( BW / 2 );
// 			//Fslop	= (float) ( (float) -BW / (float) FPatPrd );		 // 톱니파의 기울기 계산 
// 		}
// 		else
// 			printf(" \n \n [E] Freq Pattern Type (주파수 패턴 형태)가 잘못 되었습니다. ");
// 	}
// 	else if( strcmp( FType, "FIX" ) == 0 )	// FREQ Fixed
// 	{
// 		pFreq = (int) ( (Freq + 0.5) );
// 		pFreq = (UINT) ConvertFreq( pFreq, Bc );
// 		new_pdw.item.frequency_l  = pFreq & 0xFF;
// 		new_pdw.item.frequency_h  = ( pFreq >> 8 ) & 0x1F;
// 	}
// 	else if( strcmp( FType, "HOP" ) == 0 )
// 	{
// 		for( i=0; i < FHopLvl; i++)
// 		{
// 			// HL[i] = ConvertFreq( HL[i] , Bc );		// Freq Hopping level 값
// 		}
// 
// 	}
// 	else
// 		printf(" \n \n [E] Freq Type (주파수 형태)가 잘못 되었습니다. ");
// 
// 
// 	///////////////   PRI TYPE 별 계산 
// 	PRI_width = (float)(PRI * Jitp / 100 * 2);	// Jitter 폭 
// 	pPRI = PRI;
// 	if( strcmp( PType, "STB" ) == 0 )		// PRI Stable
// 	{
// 	}
// 	else if( strcmp( PType, "JIT" ) == 0 )			// Jitter
// 	{
// 	}
// 	else if( strcmp( PType, "PAT" ) == 0 )		// PRI Pattern 
// 	{
// 		PPatPrd = (UINT)( PPatPrd * ONE_MILLISEC );
// 		if( strcmp( PPatType, "DNS" ) == 0 )		// PRI Dwell & Switch 
// 		{
// 			for( i=0; i < PSLvl; i++)
// 			{
// 				PL[i] = PL[i] * ONE_MICROSEC;		// PRI D&S level 값
// 			}
// 		}
// 		else
// 		{
// 			pPRI = fPRI = PRI ;
// 			Ppmax	= (float)(PRI + PRI_width / 2.);
// 			Ppmin	= (float)(PRI - PRI_width / 2.);
// 			if( strcmp( PPatType, "SIN" ) == 0 )		// PRI Pattern Sine
// 			{
// 				// 2 * pi = PPatPrd ( 1주기 )
// 				// 현재 PRI(pPRI) = PRI_width / 2 * sin( PPatPrd / 2 * pi * toa ) + pPRI )
// 			}
// 			else if( strcmp( PPatType, "TRI" ) == 0 )	// PRI Pattern Triangle (주파수 패턴 삼각파)
// 			{
// 				Pdiff	= PRI_width / ( (PPatPrd / 2) / PRI);	//  펄스간 평균 간격 
// 				Pslop	= 1;
// //				Pslop	= (float)(PRI_width / (PPatPrd / 2.));   // 삼각파의 기울기 계산 
// 			}
// 			else
// 			{
// 				Pdiff	= PRI_width / (PPatPrd / PRI);	//  펄스간 평균 간격 
// 				if( strcmp( PPatType, "SW+" ) == 0 )	// PRI Pattern SAW+ (PRI 패턴 톱니파 증가)
// 				{
// 	//				Pslop	= PRI_width / (float)PPatPrd;		 // 톱니파의 기울기 계산 
// 					Pslop	= 1;
// 				}
// 				else if( strcmp( PPatType, "SW-" ) == 0 )	// PRI Pattern SAW- (PRI 패턴 톱니파 감소)
// 				{
// 	//				Pslop	= (-1) * PRI_width / (float)PPatPrd;// 톱니파의 기울기 계산 
// 					Pslop	= -1;
// 				}
// 				else
// 					printf(" \n \n [E] PRI Pattern Type (PRI 패턴 형태)가 잘못 되었습니다. ");
// 			}
// 		}
// 	}
// 	else if( strcmp( PType, "STG" ) == 0 )		// PRI STAGGER 
// 	{
// 		for( i=0; i < PSLvl; i++)
// 		{
// 			PL[i] = PL[i];		// PRI Stagger level 값
// 		}
// 	}
// 	else if( strcmp( PType, "DNS" ) == 0 )		// PRI STAGGER 
// 	{
// 
// 	}
// 	else
// 		printf(" \n \n [E] PRI Type (PRI 형태)가 잘못 되었습니다. ");
// 	
// 	
// 	/////////////   스캔 TYPE 별 계산 
// 	// Scan 
// 	if( strcmp( ScanType, "STD" ) == 0 )	// for Steady 
// 	{
// 		ScanPrd = 0;	// Input scan period [ms] 
// 		new_pdw.item.amplitude = (UCHAR)PA;
// 	}
// 	else if( strcmp( ScanType, "CON" ) == 0 )	// for Conical 
// 	{
// 		ScanPrd = (UINT)( ScanPrd * ONE_MILLISEC );
// 		// Pa_width = 7 dBm
// 		Pa_width = (float)( 7 / AMPLITUDE_RESOL );
// 	}
// 	else if( strcmp( ScanType, "CIR" ) == 0	||	// for Circular 
// 			 strcmp( ScanType, "UNI" ) == 0)	// for Uni-direction
// 	{
// 		ScanPrd = (UINT)( ScanPrd * ONE_MILLISEC - ( PRI * SPul_Cnt ) );	
// 		for( i=0; i < SPul_Cnt; i++ )	 
// 		{
// 			pa_array[i] = (UCHAR)( sin( i * PIE / SPul_Cnt ) * PA + 0.5 );
// 		}
// 	}
// 	else if( strcmp( ScanType, "BID" ) == 0 )	// for Bi-Sector
// 	{
// 		// Bi_sector period 는 3:1의 비율로 지정 
// 		ScanPrd = (UINT)( ScanPrd * ONE_MILLISEC - ( 2 * PRI * SPul_Cnt ) );	
// 		Bi1_prd = ScanPrd / 4 * 3 ;		// Bi-sector scan 주기 1
// 		Bi2_prd = ScanPrd / 4 * 1 ;		// Bi-sector scan 주기 2
// 		for( i=0; i < SPul_Cnt; i++ )	
// 		{
// 			pa_array[i] = (UCHAR)( sin( i * PIE / SPul_Cnt ) * PA + 0.5 );
// 		}
// 	}
// 	else 
// 		printf(" \n\n [E] 스캔 type이 잘못 되었습니다 !!! ");
// 
// }

// /************************************************************************************
//  함 수 명 : makeFreqPdw
//  Input    : 
//  Process  :  Freq Type 별로 주파수 값을 계산하여  PDW 포멧에 입력한다 
//  Output   : 
// *************************************************************************************/
// void makeFreqPdw( void )
// {
// 	//float fRatio;
// 	UINT	temp, uiTOA1, uiTOA2, uiTOA;
// 
// 	if( strcmp( FType, "PAT" ) == 0 )	// FREQ Pattern 
// 	{
// 		if( strcmp( FPatType, "SIN" ) == 0 )	// Freq Pattern sinusoidal (주파수 패턴 사인파)
// 		{
// 			// 2 * pi = FPatPrd ( 1주기 )
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
// 			if( strcmp( FPatType, "TRI" ) == 0 )	// Freq Pattern Triangle (주파수 패턴 삼각파)
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
// 			if( strcmp( FPatType, "SW+" ) == 0 )	// Freq Pattern SAW+ (주파수 패턴 톱니파 증가)
// 			{
// 				if( Freq > Fpmax ) {
// 					Freq = ( uiCenterFreq + ( BW / 2 ) );
// 					uiPatternFreq = ( uiCenterFreq - ( BW / 2 )  );
// 				}
// 			}
// 			if( strcmp( FPatType, "SW-" ) == 0 )	// Freq Pattern SAW- (주파수 패턴 톱니파 감소)
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
// 	else if( strcmp( FType, "AGI" ) == 0 )	// Agile
// 	{
// //		temp  = ( rand() % (int)(BW + 0.5) );
// 
// 		temp  = ( rand() % (int)BW );
// 		pFreq = (UINT)( temp + ( Freq - BW / 2 ) + 0.5 );
// 
// 		pFreq = (UINT) ( pFreq + Rand( Freq_Error ) );
// 		// ++ pFreq;
// 		
// 	}
// 	else if( strcmp( FType, "HOP" ) == 0 )	// Hopping
// 	{
// 		Hop_prd = ( FPatPrd *1000. ) / FHopLvl / PRI;	// Hopping level당 펄스수의 계산 
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
// 
// }
// 
// /************************************************************************************
//  함 수 명 : makePRIPdw
//  Input    : 
//  Process  :  PRI Type 별로 PRI 값을 계산하여 PDW 포멧에 입력한다 
//  Output   : 
// *************************************************************************************/
// void makePRIPdw( UINT pul_idx )
// {

// 
// }
// 
// /************************************************************************************
//  함 수 명 : makePAPdw
//  Input    : 
//  Process  :  스캔 Type 별로 PA 값을 계산하여 PDW 포멧에 입력한다 
//  Output   : 
// *************************************************************************************/
// void makePAPdw( UINT lob_idx ) 
// {
// 	UINT	T;
// 	if( strcmp( ScanType, "STD" ) == 0 )	// for Conical 
// 	{
// 	}
// 	else if( strcmp( ScanType, "CON" ) == 0 )	// for Conical 
// 	{
// 		// sine 형 , 진폭 = Pa_width , 주기 = ScanPrd
// 		T = (Pa_width / 2.) * sin( (2 * PIE) / ScanPrd * toa );
// 		 T = (UINT)( T + PA ); 
// 		 new_pdw.item.amplitude = T;
// 	}
// 	else 	// for Cir, Bi, Uni 
// 		new_pdw.item.amplitude     = pa_array[lob_idx];
// 
// }
// 
// void makePWPdw()
// {
// 	UINT pw;
// 
// 	int x=ONE_MICROSEC;
// 
// 	pw = ( PW * ONE_MICROSEC ) + Rand( Pw_Error * ONE_MICROSEC );
// 	pw /= 1000;
// 	new_pdw.item.pulse_width_l	= pw & 0xFF ;		// 펄스폭 값 입력 
// 	new_pdw.item.pulse_width_h	= ( pw >> 8 ) & 0x07;
// }
// 
