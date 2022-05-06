/****************************************************************************************
 �� �� �� : npwmake.c  by ������
 ��    �� : npw ȭ���� ����
 �� �� �� : makȭ���� ����� makȭ�Ͽ� ���ϵ� ������� npwȭ���� �����Ѵ�. 
			mak_filename[.mak]�� ������ mak ȭ���� ī��/�����Ͽ� ����Ѵ�.
			Header�� ���� ������ �Է��Ѵ�. ���ٿ� �� ȭ�Ͼ� ����.
			makȭ���� �� �� ��ŭ �������� npwȭ���� ������ �� �ִ�. 
 �߿��ڷᱸ�� :
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

////////////   ���� ��� 
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

////////////   ���뺯�� 
// extern	int errno;
// FILE		*wfp = NULL;
// FILE		*rfp = NULL;
// 
// char		szMakfilename[MAX_PATH];
// TNEW_PDW	new_pdw;                

/*
1.  Idx	        // 1 ���� ���� 
2.  Filename
3.  Count
4.  FstTOA[us]	// ���� TOA
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
// 	UINT		Idx;			// �߻� ��ȣ index
// 	char		filename[50];	// �߻� ��ȣ ȭ�ϸ� [���� 15�� �̳�]
// 	UINT		Count;			// �߻� �޽��� 
// 	UINT		FstTOA;			// �ʱ� TOA offset [us]
// 	UINT		Stat;			// normal=0, Pmop=1, chirp_up=2, chirp_dn=3, cw=4, ��������=12, ��������=13, bit=15
// 	UINT		DV;				// Direction Valid=1, Not Valid=0
//     UINT		AOA;			// ����� ���� AOA ���� ������ ����    
// 	char		FType[3];		// ���ļ� ����  : FIX(fixed)   AGI(agile)    PAT(pattern)  HOP(hopping)
// 
//     UINT		Freq;			// �߽� ���ļ� [MHz]
// 	UINT		uiCenterFreq;			// �߽� ���ļ� [MHz]
// 	UINT		uiPatternFreq;
// 
//     UINT		Bc;
// 	UINT		BW;				// ���ļ� �� [MHz]
// 	char		FPatType[3];	// ���ļ� ���� ���� : SIN(sine)  TRI(triangle)   SW+(saw+)     SW-(saw-)
// 	//UINT		FPatPrd;		// ���ļ� ���� �ֱ�[msec]
// 	UINT		FHopLvl;		// ���ļ� Hopping level �� 
// 	float		HL[16];			// ���ļ� Hopping level ��[MHz]
// 	char		PType[3];		// PRI ����   : STB(stable)  STG(stagger)  JIT(jitter)   DNS(dwell & switch) 
// 	int			PRI;			// PRI [us]
// 	float		Jitp;			// PRI Jitter%
// 	UINT		PSLvl;			// PRI switch Level �� 
// 	UINT		PL[16];			// PRI switch level �� [usec]
// 	char		PPatType[3];	// PRI ���� ����  : SIN(sine)  TRI(triangle)  SW+(saw+)     SW-(saw-)
// 	//UINT		PPatPrd;		// PRI ���� �ֱ� [msec]
// 	UINT		PdnsCnt;		// D&S �� level�� �޽��� 
// 	float		PA;				// �޽� ���� [dBm]
// 	UINT		PW;				// �޽��� [nsec]
// 	UINT		Fmop;			// Freq Diff [MHz]
// 	UINT		Pmop;			// Phase Modulation
// 	char		ScanType[3];	// ��ĵ Type : STD(steady)  CON(conical)  CIR(circular) BID(bi-directional)  UNI(uni-directional)
// 	UINT		ScanPrd;		// scan period
// 	UINT		SPul_Cnt;		// �� lobe���� �޽��� 
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
// 	UINT		FPatPrd;	// ���ļ� ���� �ֱ�
// 	float		Fpmax;		// ���ļ� MAX
// 	float		Fpmin;		// ���ļ� MIN
// 	float		Fslop;		// ���ļ� �����/�ﰢ�� ���� 
// 	UINT		Hop_idx;	// Hopping level index		
// 	UINT		Hop_cnt;	// Hopping level �޽��� 
// 
// 	// PRI
// 	UINT		PPatPrd;	// PRI ���� �ֱ�
// 	float		fPRI;		// float�� PRI
// 	float		Ppmax;		// PRI MAX
// 	float		Ppmin;		// PRI MIN
// 	float		Pslop;		// PRI �����/�ﰢ�� ���� 
// 	float		Pdiff;		// PRI ����� �޽��� ��� ���� 
// 	UINT		Dns_idx;	// D&S level index 
// 	UINT		Dns_cnt;	// D&S level �޽��� decount�� 
// 
// 	UINT		Bi1_prd;	// Bi-sector scan �ֱ� 1
// 	UINT		Bi2_prd;	// Bi-sector scan �ֱ� 2
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
        printf("\n  mak_filename[.mak]�� ������ mak ȭ���� ī��/�����Ͽ� ����Ѵ�.");
		printf("\n  Header�� ���� ������ �Է��Ѵ�. ���ٿ� �� ȭ�Ͼ� ����");
		printf("\n  �Էµ� �ٸ�ŭ ���ȭ���� �����ȴ�. ");
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
// 		// makȭ�Ͽ��� PRAMETER���� ���� 
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
// 				new_pdw.item.toa_4   = ( toa >> 24 ) & 0xFF;	// TOA �� �Է� 
// 				new_pdw.item.toa_3   = ( toa >> 16 ) & 0xFF;
// 				new_pdw.item.toa_2   = ( toa >> 8  ) & 0xFF;
// 				new_pdw.item.toa_1   = toa & 0xFF;
// 
// 				// ���ļ� �� �Է� 
// 				makeFreqPdw();
// 
// 				// PRI �� �Է� 
// 				makePRIPdw( total );
// 
// 				// PW �� �Է� 
// 				makePWPdw();
// 
// 				// PA �� �Է� 
// 				if( strcmp( ScanType, "STD" ) != 0 )	// NOT Scan Steady
// 				{
// 					makePAPdw( isl );	// next TOA ������ ���� 
// 				}
// 	
// 				// ��� ȭ�Ͽ� ����
// 				if( Pulse_Skip == 0 )
// 					fwrite( (char *)&new_pdw,sizeof(TNEW_PDW),1,wfp );
// 				else {
// 					if( kCount % Pulse_Skip != 0 )
// 						fwrite( (char *)&new_pdw,sizeof(TNEW_PDW),1,wfp );
// 				}
// 
// 				// ���� TOA ��� 
// 				toa += pPRI;
// 				total++;
// 
// 			} // for( isl=0; isl < SPul_Cnt , ��ĵ Lobe�� Loop
// 
// 			// ���� TOA ��� 
// 			if( strcmp( ScanType, "BID" ) == 0 )	// for Bi-Sector
// 			{
// 				if( sl % 2 )
// 					toa += Bi2_prd;	// scan �����Է� 
// 				else
// 					toa += Bi1_prd;	// scan �����Է� 
// 			}
// 			else if( strcmp( ScanType, "CIR" ) == 0 ||  // for Circular
// 					 strcmp( ScanType, "UNI" ) == 0 )	// for Uni-Sector
// 				toa += ScanPrd;	// scan �����Է� 
// 
// 		} // for( sl=0; total < Count; sl++),  ��ĵ Loop
// 
// 		printf( "\n           Make Done [ %s ]", filename );
// 		fclose( wfp );
// 
// 		// ���� �� Idx Read 
// 		fscanf( rfp, "%u", &Idx ); 	// Read Index 
// 		ofl++;
// 
// 	}	//	while( 1 ), ��� ȭ�� Loop(ofl)
// 
// 	fclose( rfp );

    delete pTheGenPDW;

    return 0;

}

/**************************************************************************************
 �� �� �� : wanna_create by ����  
 Input    : filename
 Output   : band code
 �� �� �� : 1998. 01. 12
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
 �� �� �� : pdwcnvt by �����
 Input    : Freq
 Process  : Freq�� ����� �ش� band code�� ���Ѵ�
 Output   : band code
 �� �� �� : 1998. 04. 01
**************************************************************************************/
// UINT GetBandOfFreq( UINT Freq )
// {
//     UINT  i;
// 
//     /* Freq�� band code�� ���Ѵ�. */
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
 �� �� �� : ConvertFreq by �����
 Input    : Freq, band code
 Process  : band code�� index�� �ش� resolution�� min������ ���ο� Freq�� ����
 Output   : ��ȯ�� Freq
 �� �� �� : 1998. 04. 01
**************************************************************************************/
// float ConvertFreq( float freq, UINT band )
// {
//     freq -= l_freq_resol[band].min;
//     freq /= l_freq_resol[band].resolution;
// 
//     return( freq );
// }

/************************************************************************************
 �� �� �� : getParam
 Input    : 
 Process  : mak ȭ�Ͽ��� parameter���� �о���� 
 Output   : 
*************************************************************************************/


/************************************************************************************
 �� �� �� : setParam
 Input    : 
 Process  : ȭ�Ͽ��� �о���� parameter���� PDW format�� �µ��� ��ȯ
 Output   : 
*************************************************************************************/
// void setParam( void )
// {
// 	UINT	i;
// 
// 	/////////////////// SET PDW PARAMETER //////////////////////
// 
// 	// Decimal to Binary( ���� ������ PDW���� ������ ��ȯ )
// 	AOA  = (UINT)  ( AOA / DIRECTION_RESOL );	// ���� 
// 	toa	 = (UINT)  ( FstTOA * ONE_MICROSEC );	// TOA
// 
// 
// 	if( (Bc = GetBandOfFreq( (UINT)Freq )) == -1 )// Band Code
// 	{
// 		printf(" \n [E] Not Vaild Freq " );
// 		exit(1);
// 	}
// 
// 	// Freq = ConvertFreq( Freq, Bc );				// ���ļ� 
// 
// 	// PRI	 = (UINT)  ( PRI * ONE_MICROSEC );		// PRI
// //	PRI	 = (UINT)  ( PRI * 1 );		// PRI
// //PW	 = (UINT)  ( PW  / PULSE_WIDTH_RESOL );
// 	PW	 = (UINT)  ( PW  / 1 );
// 	PA	 = (float)(( PA  - AMPLITUDE_INIT ) / AMPLITUDE_RESOL);
// 
// 	// ���� PDW �� ���� 
// 	new_pdw.item.phase1	= 0;	// Phase Code �Է� 
// 	new_pdw.item.phase2 = 1;
// 	new_pdw.item.phase3 = 2;
// 	new_pdw.item.phase4 = 3;
// 	new_pdw.pdw[3][0]   = 0xff;	// ����� 1�� ä��
// 	new_pdw.pdw[3][1]   = 0xff;	// PARITY ERROR������ 
// 	new_pdw.item.stat	= Stat;
// 	new_pdw.item.dv		= DV;	
// 	new_pdw.item.band		 = Bc;
// 	new_pdw.item.pmop        = Pmop;
// 	new_pdw.item.freq_diff   = Fmop;
// 	new_pdw.item.pulse_width_l	= PW & 0xFF ;		// �޽��� �� �Է� 
// 	new_pdw.item.pulse_width_h	= ( PW >> 8 ) & 0x07;
// 	new_pdw.item.direction_l	= AOA & 0xFF;			// ���� �� �Է� 
// 	new_pdw.item.direction_h	= ( AOA >> 8 ) & 0x03;
// 
// 	///////////////   ���ļ� TYPE �� ��� 
// 	if( strcmp( FType, "AGI" ) == 0 )			// Agile
// 	{
// 		BW = (UINT)(BW / l_freq_resol[Bc].resolution);
// 	}
// 	else if( strcmp( FType, "PAT" ) == 0 )	// FREQ Pattern 
// 	{
// 		// FPatPrd = (UINT)( FPatPrd * ONE_MILLISEC );
// 		// FPatPrd = 0.001 * FPatPrd;
// 			// BW = (float)(BW / l_freq_resol[Bc].resolution);
// //			FPatPul = (float)FPatPrd / PRI;	// ���ֱ�� �޽��� 
// 
// 		FPatPrd = (UINT)( FPatPrd * ONE_MICROSEC );
// 		Fpmax	= (float)(Freq + BW / 2.);
// 		Fpmin	= (float)(Freq - BW / 2.);
// 		if( strcmp( FPatType, "SIN" ) == 0 )			// Freq Pattern Sine
// 		{
// 			// 2 * pi = FPatPrd ( 1�ֱ� )
// 			// ���� ���ļ�(pFreq) = BW / 2 * sin( FPatPrd / 2 * pi * toa ) + Freq )
// 		}
// 		else if( strcmp( FPatType, "TRI" ) == 0 )	// Freq Pattern Triangle (���ļ� ���� �ﰢ��)
// 		{
// 			Fslop	= (float)(BW * 1000. / (FPatPrd / 2.));   // �ﰢ���� ���� ��� 
// 		}
// 		else if( strcmp( FPatType, "SW+" ) == 0 )		// Freq Pattern SAW+ (���ļ� ���� ����� ����)
// 		{
// 			Fslop	= (float) ( (float) ( BW / 2. ) / (float) FPatPrd );		 // ������� ���� ��� 
// 			uiPatternFreq = uiCenterFreq - ( BW / 2 );
// 		}
// 		else if( strcmp( FPatType, "SW-" ) == 0 )		// Freq Pattern SAW- (���ļ� ���� ����� ����)
// 		{
// 			Fslop	= (float) ( (float) ( -BW / 2. ) / (float) FPatPrd );		 // ������� ���� ��� 
// 			uiPatternFreq = uiCenterFreq - ( BW / 2 );
// 			//Fslop	= (float) ( (float) -BW / (float) FPatPrd );		 // ������� ���� ��� 
// 		}
// 		else
// 			printf(" \n \n [E] Freq Pattern Type (���ļ� ���� ����)�� �߸� �Ǿ����ϴ�. ");
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
// 			// HL[i] = ConvertFreq( HL[i] , Bc );		// Freq Hopping level ��
// 		}
// 
// 	}
// 	else
// 		printf(" \n \n [E] Freq Type (���ļ� ����)�� �߸� �Ǿ����ϴ�. ");
// 
// 
// 	///////////////   PRI TYPE �� ��� 
// 	PRI_width = (float)(PRI * Jitp / 100 * 2);	// Jitter �� 
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
// 				PL[i] = PL[i] * ONE_MICROSEC;		// PRI D&S level ��
// 			}
// 		}
// 		else
// 		{
// 			pPRI = fPRI = PRI ;
// 			Ppmax	= (float)(PRI + PRI_width / 2.);
// 			Ppmin	= (float)(PRI - PRI_width / 2.);
// 			if( strcmp( PPatType, "SIN" ) == 0 )		// PRI Pattern Sine
// 			{
// 				// 2 * pi = PPatPrd ( 1�ֱ� )
// 				// ���� PRI(pPRI) = PRI_width / 2 * sin( PPatPrd / 2 * pi * toa ) + pPRI )
// 			}
// 			else if( strcmp( PPatType, "TRI" ) == 0 )	// PRI Pattern Triangle (���ļ� ���� �ﰢ��)
// 			{
// 				Pdiff	= PRI_width / ( (PPatPrd / 2) / PRI);	//  �޽��� ��� ���� 
// 				Pslop	= 1;
// //				Pslop	= (float)(PRI_width / (PPatPrd / 2.));   // �ﰢ���� ���� ��� 
// 			}
// 			else
// 			{
// 				Pdiff	= PRI_width / (PPatPrd / PRI);	//  �޽��� ��� ���� 
// 				if( strcmp( PPatType, "SW+" ) == 0 )	// PRI Pattern SAW+ (PRI ���� ����� ����)
// 				{
// 	//				Pslop	= PRI_width / (float)PPatPrd;		 // ������� ���� ��� 
// 					Pslop	= 1;
// 				}
// 				else if( strcmp( PPatType, "SW-" ) == 0 )	// PRI Pattern SAW- (PRI ���� ����� ����)
// 				{
// 	//				Pslop	= (-1) * PRI_width / (float)PPatPrd;// ������� ���� ��� 
// 					Pslop	= -1;
// 				}
// 				else
// 					printf(" \n \n [E] PRI Pattern Type (PRI ���� ����)�� �߸� �Ǿ����ϴ�. ");
// 			}
// 		}
// 	}
// 	else if( strcmp( PType, "STG" ) == 0 )		// PRI STAGGER 
// 	{
// 		for( i=0; i < PSLvl; i++)
// 		{
// 			PL[i] = PL[i];		// PRI Stagger level ��
// 		}
// 	}
// 	else if( strcmp( PType, "DNS" ) == 0 )		// PRI STAGGER 
// 	{
// 
// 	}
// 	else
// 		printf(" \n \n [E] PRI Type (PRI ����)�� �߸� �Ǿ����ϴ�. ");
// 	
// 	
// 	/////////////   ��ĵ TYPE �� ��� 
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
// 		// Bi_sector period �� 3:1�� ������ ���� 
// 		ScanPrd = (UINT)( ScanPrd * ONE_MILLISEC - ( 2 * PRI * SPul_Cnt ) );	
// 		Bi1_prd = ScanPrd / 4 * 3 ;		// Bi-sector scan �ֱ� 1
// 		Bi2_prd = ScanPrd / 4 * 1 ;		// Bi-sector scan �ֱ� 2
// 		for( i=0; i < SPul_Cnt; i++ )	
// 		{
// 			pa_array[i] = (UCHAR)( sin( i * PIE / SPul_Cnt ) * PA + 0.5 );
// 		}
// 	}
// 	else 
// 		printf(" \n\n [E] ��ĵ type�� �߸� �Ǿ����ϴ� !!! ");
// 
// }

// /************************************************************************************
//  �� �� �� : makeFreqPdw
//  Input    : 
//  Process  :  Freq Type ���� ���ļ� ���� ����Ͽ�  PDW ���信 �Է��Ѵ� 
//  Output   : 
// *************************************************************************************/
// void makeFreqPdw( void )
// {
// 	//float fRatio;
// 	UINT	temp, uiTOA1, uiTOA2, uiTOA;
// 
// 	if( strcmp( FType, "PAT" ) == 0 )	// FREQ Pattern 
// 	{
// 		if( strcmp( FPatType, "SIN" ) == 0 )	// Freq Pattern sinusoidal (���ļ� ���� ������)
// 		{
// 			// 2 * pi = FPatPrd ( 1�ֱ� )
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
// 			if( strcmp( FPatType, "TRI" ) == 0 )	// Freq Pattern Triangle (���ļ� ���� �ﰢ��)
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
// 			if( strcmp( FPatType, "SW+" ) == 0 )	// Freq Pattern SAW+ (���ļ� ���� ����� ����)
// 			{
// 				if( Freq > Fpmax ) {
// 					Freq = ( uiCenterFreq + ( BW / 2 ) );
// 					uiPatternFreq = ( uiCenterFreq - ( BW / 2 )  );
// 				}
// 			}
// 			if( strcmp( FPatType, "SW-" ) == 0 )	// Freq Pattern SAW- (���ļ� ���� ����� ����)
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
// 		Hop_prd = ( FPatPrd *1000. ) / FHopLvl / PRI;	// Hopping level�� �޽����� ��� 
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
//  �� �� �� : makePRIPdw
//  Input    : 
//  Process  :  PRI Type ���� PRI ���� ����Ͽ� PDW ���信 �Է��Ѵ� 
//  Output   : 
// *************************************************************************************/
// void makePRIPdw( UINT pul_idx )
// {

// 
// }
// 
// /************************************************************************************
//  �� �� �� : makePAPdw
//  Input    : 
//  Process  :  ��ĵ Type ���� PA ���� ����Ͽ� PDW ���信 �Է��Ѵ� 
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
// 		// sine �� , ���� = Pa_width , �ֱ� = ScanPrd
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
// 	new_pdw.item.pulse_width_l	= pw & 0xFF ;		// �޽��� �� �Է� 
// 	new_pdw.item.pulse_width_h	= ( pw >> 8 ) & 0x07;
// }
// 
