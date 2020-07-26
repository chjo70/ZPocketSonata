/****************************************************************************************
 �� �� �� : _sysmsg.h
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 ��    �� : �������� �� ��ֽ�ȣ��������� �������̽� �޽��� �� ���� ����
 ��    �� :
 �� �� �� : Jo Churl-hee
 �� �� �� :
 ���泻�� : (����)
 �����Ͻ� : 99-05-03 10:05����
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 �Է����� :
 ������� :
 ���ø�� :
 �ڷᱸ�� : (��������)
 ����ó��/���ͼ���:
 ������ �Ͻ� :
*****************************************************************************************/

#ifndef _SYSMSG_H_
#define _SYSMSG_H_

/*----------------------------------------------------------------------------------------
    �������̽� �޽��� OPCODE ����
  �ڸ� �� : 4 �ڸ� - X X X X
             1 2 3 4
    1 �ڸ� : ��ġ�� �������̽� ����
       1 X X X : CCU    -> RSA, JSM
           2 X X X : CCU,JSM  -> RSA
           3 X X X : CCU    -> RSA
           4 X X X : RSA    -> CCU, JSM
           5 X X X : RSA    -> JSM
           6 X X X : JSM    -> CCU
    2 �ڸ� : �޽����� ����
       X 0 X X : ���� �޽���
       X 1 X X : �ý��� ��� ���� �޽���
       X 2 X X : ��Ʈ ���� �޽���
       X 3 X X : �ý��� ���� ��� ���� ���� ���õ� �޽���
       X 4 X X : ���̺귯�� ���� �޽���(IPL, JPL)
       X 5 X X : �������� �޽���(AET, JAM)
----------------------------------------------------------------------------------------*/

/////////////////////////////////////////////////////////////////////////////////////////
//  ���̴� ¡ǥ�м��� �ܺ� �޽��� ���� : CCU->RSA
//
//  OP�ڵ� + SIZE : Default 8 Bytes
//

/* ��� �޽���  */
#define   Msys_Error        1001  /* (  0) */
#define   Msys_SetMode      1101  /* (  4)�ý��۸��(1:ES,2:EW,3:���) */
#define   Msys_Start        1102  /* (  0) */

/* BIT �޽���  */
#define   Mbit_ReqIbit      1201  /* (  4)��ġ�ڵ� */
/* 1:ES��ü, 2:RSA,
             3:�뿪1 ������ ������ġ, 4:�뿪1 ���Ź�Ž ó����,
             5:�뿪1 ��������Ž����ġ, 6:�뿪1 ��������Ž����ġ,
             7:�뿪1 ��ȣ�й��,
             8:�뿪2 ������ ������ġ, 9:�뿪2 ���Ź�Ž ó����,
             10:�뿪2 ��������Ž����ġ, 11:�뿪2 ��������Ž����ġ,
             12:�뿪2 ��ȣ�й��,
             13:�뿪3 ������ ������ġ, 14:�뿪3 ���Ź�Ž ó����,
             15:�뿪3 ��������Ž����ġ, 16:�뿪3 ��������Ž����ġ,
             17:�뿪3 ��ȣ�й�� */
#define   Mbit_StartSbit    1202  /* (  8)��� (1:Low,2:Mid,3:Hgh) + ����
                                  ( 0xF1:1��и�(45��),  0xF2:2��и�(135��),
                                  0xF3:3��и�(225��), 0xF4:4��и�(315��) ) */
#define   Mbit_StopSbit     1203  /* (  8)��� (1:Low,2:Mid,3:Hgh) + ����   `98.9.2
                                  ( 0xF1:1��и�(45��),  0xF2:2��и�(135��),
                                  0xF3:3��и�(225��), 0xF4:4��и�(315��) ) */
#define   Mbit_ReqCbit      1204  /* (  0)  */  //  `98.9.2
#define   Mbit_ReqUbit      1205  /* (  0)  */  //  `99.05.04
#define   Mbit_StartSbit_V3 1206  // for SONATA Ver 3, debug 01-06-01 13:08:09

/*! \bug  �� ���� �䱸 �޽���
    \date 2007-03-29 10:16:23, ��ö��
*/
#define		Mbit_ReqLanStatus	1207

#define   Mbit_ReqUbitTEST  1210  /* (  0)  */  //  `98.9.2

/* �ý��� ���� �޽��� */
#define   Mcnf_Audio        3301  /* (  4)�����ڵ�(0:Disable, 1:Enable) */
#define   Mcnf_AudioParam   3302  /* ( 24)LAN_AUD_PAR   `98.9.2
                                        Band Low + High,
                                        Frq. Low + High,
                                        AOA  Low + High */

#define   Mcnf_ScanLevel    3303  /* (  4)��������(0:���� ~ 9:����) */
#define   Mcnf_InhibitAoa   3304  /* (108)LAN_IHB_AOA[9]
                                       (Flag(0:Clear,1:Set)+fromAOA+toAOA) * 9 */
#define   Mcnf_InhibitFreq  3305  /* (144)LAN_IHB_FRQ[9]
                                       (Flag(0:Clear,1:Set)+Band+lowFrq+highFrq) * 9 */

#define   Mcnf_BandEnable     3306  /* (  8)���+�����ڵ�(0:Disable,1:Enable) */
#define   Mcnf_NotchFilter    3307  /* (  8)���+���ļ� */
#define   Mcnf_FmopThreshold  3308  /* (  8)���+Threshold */
#define   Mcnf_Dca            3309  /* (  8)���(1:Low, 2:Mid, 3:High)+����� ���� */
#define   Mcnf_RxThreshold    3310  /* (  8)���+Threshold */
#define   Mcnf_PMOPThreshold  3311  //
#define   Mcnf_RxAntOffset    3312  //
#define   Mcnf_EABlankingAttn 3313  //
#define   Mcnf_DelTime        3314  // debug, 01-01-16
#define   Mcnf_ReqSys         3315  // debug, 01-01-16
#define   Mcnf_SetSys         3316  // debug, 01-01-16
#define   Mcnf_EWMode         3317  // 03-07-25
#define   Mcnf_AutoLevel      3318  // 03-07-25
#define   Mcnf_DV             3350  // debug, 01-01-16

// ����� ������ �ϱ� ���� OP�ڵ� �߰�
#define		Mcnf_AudioWideFrq		3390
#define		Mcnf_AudioWideAoa		3391

// ������ ���� ������� ���������� ���� �߰�
#define   Mcnf_RxThreshold_AutoMode		3320
#define   Mcnf_RxThreshold_AutoLvlThr	4320

/* IPL �޽��� */
#define   Mipl_ReqVersion     3401  /* (  0) */
#define   Mipl_Start          3402  /* (  8)����+������ȣ(��+��+��ȣ) */
#define   Mipl_Download       3403  /* (516)(STR_IPL) (TBD ? CheckSum) */
#define   Mipl_End            3404  /* (  0) */

/* ������ �޽��� */
#define   Maet_ReqScan        3501  /* (  4)AET ��ȣ */
#define   Maet_Clear          3502  /* (  4)AET ��ȣ */
#define   Maet_SigHide        3504  /* (  4)AET ��ȣ */
#define   Maet_SigShow        3505  /* (  4)AET ��ȣ */

#define   Maet_AddJamming     3511  // 03-07-25
#define   Maet_DelJamming     3512  // 03-07-25

///////////////////////////////////////////////////////////////////////////////////////
#define		Mreq_SetConfig			(9301)
#define		Mreq_Stop						(9302)
#define		Mreq_ColStart				(9401)
#define		Mreq_RawData				(9405)

/////////////////////////////////////////////////////////////////////////////////////////
//  ���̴� ¡ǥ�м��� �ܺ� �޽��� ���� : RSA->CCU
//
/* ��� �޽���  */
#define   Esys_SetMode        2101  /* (  0) */

/* BIT �޽���  */
#define   Mbit_ResultEsIbit   4201  /* ( 68)LAN_BIT(17 * 4Byte)
                                         ES����,RSA,
                                         ���ű�뿪1(5W), �뿪2(5W), �뿪3(5W) */
#define   Mbit_ResultEsSbit   4202  /* (312)STR_AET */  // ���� `98.9.3
#define   Mbit_Aet            4203  /* (312)STR_AET */  // ���� `98.9.3
#define   Mbit_ResultEsCbit   4204  /* (  8)RSA(0:����, 1:������) +
                                          RXDF(0:����, 1:������)
                                          Band1:D5(���), D4(���)
                                          Band1:D3(���), D2(���)
                                          Band1:D1(���), D0(���) */
#define   Mbit_ResultEsUbit   4205  /* (  8)RSA(0:����, 1:������) +   */
#define		Mbit_ResultLanStatus	4206	/* (  8)RSA(0:����, 1:������) + 	*/

/* IPL �޽��� */
#define   Mipl_Version        4401  /* (  4)������ȣ(��+��+��ȣ) */
#define   Mipl_WriteStatus    4402  /* (  4)Writing�ϰ� �ִ� �ۼ�Ʈ(IPL������ ����) */
#define   Mipl_SetAnalysisMode	3410  /* CCU���� RSA�� �⺻/���� �ĺ� ��� ���� */
#define   Mipl_AnalysisMode		4410  /* RSA���� CCU�� ������ �ĺ���� �� ���� */
#define   Mipl_SetFSDetectMode	3411  /* CCU���� RSA�� �ҽ�ȣŽ����� ���� */
#define   Mipl_FSDetectMode		4411  /* RSA���� CCU�� ������ �ҽ�ȣŽ����� �� ���� */

/* ������ �޽��� */
#define   Maet_New_Ccu        4501    /* (312)STR_AET */
#define   Maet_Update_Ccu     4502    /* (312)STR_AET */
#define   Maet_Lost_Ccu       4503    /* (  4)AET ��ȣ */
#define   Maet_Delete_Ccu     4504    /* (  4)AET ��ȣ */
#define   Maet_AllSend_Ccu    4505

// added 01-01-16
#define   Ecnf_SetSys         4601

// debug, 00-05-12 14:52:34
#define   Msys_Modify         4609

// DEBUG�� LAN �޽���
#define   Msys_Reboot         4700
#define   Mdebug_Get_Pdw      0x1ff0
#define   Mdebug_Snd_Pdw      0x1ff1
#define   Mdebug_Rcv_Pdw      (Mdebug_Snd_Pdw)


///////////////////////////////////////////////////////////////////////////////////////
#define		Mres_SetConfig			(9302)
#define		Mres_ColStart				(9404)
#define		Mres_RawData_PDW		(9506)

/////////////////////////////////////////////////////////////////////////////////////////
//   A sort of Msys_Error's Error
//   Common error's value
#define   Invalid_Command     0x01  // error message of Mrdf_*
#define   Invalid_OpData      0x02
#define   TimeOut             0x03
#define   OnScan              0x04

//   Mipl_End's error value
#define   FailErase           0x01
#define   FailWrite           0x02
#define   InvCount            0x03
#define   MisMatchCount       0x04

//   Msys_Start's error value
#define   RSAError            0x01
#define   RXDFError           0x02

/////////////////////////////////////////////////////////////////////////////////////////
//  ���̴� ¡ǥ�м��� ���ű������� ���� ����
//
#define   _spMaxUsrIhbSize    9

/////////////////////////////////////////////////////////////////////////////////////////
//  LAN ��� Send Size Offset ����   `98.9.8a
//  appended def. for the variable LAN structure, 99.05.06
//
#define   _spSndSizeOffset    (2*sizeof(UINT))  // OpCode + Size
#define   _spRecSizeOffset    (2*sizeof(UINT))  // OpCode + Size
#define   _spCoMsys_Error     (2*sizeof(UINT))  // request opcdeo + error code

/* LAN �⺻ ������ */
//##ModelId=452B0C4E03E1
typedef struct
{
  UINT d1;            // opcode or operand
  UINT d2;            // operand
} LAN_DATA;

/* RSA CNF ���� INHIBIT ������ */
//##ModelId=452B0C4F000D
//typedef hwLAN_IHB_AOA LAN_IHB_AOA;      // in hw_str.h
//##ModelId=452B0C4F0034
//typedef hwLAN_IHB_FRQ LAN_IHB_FRQ;

/* RSA CNF ����� ���� ������ */
//##ModelId=452B0C4F003F
//typedef AUD_RANGE LAN_AUDIO;        // in hw_str.h

//##ModelId=452B0C4F0053
typedef struct
{
  UINT nsp;
  UINT cip;
  UINT sap;
  UINT ksp[ 4 ];
  UINT coEcho;
} STR_PRCSBIT ;

/* RSA IBIT ���� ������ */
//##ModelId=452B0C4F0067
typedef union
{
  UINT w32;
  struct
  {
    UINT dummy : 8;  /* bit22-31 Reserved */
    UINT cip : 1; /* bit0  ����ĺ����μ����� */
    UINT gen : 1; /* general bit */

    UINT kdm4 : 1;  /* bit21 ����������������4 */
    UINT kdm3 : 1;  /* bit18 ����������������3 */
    UINT kdm2 : 1;  /* bit15 ����������������2 */
    UINT kdm1 : 1;  /* bit12 ����������������1 */
    UINT ndm : 1; /* bit9  Ž�������������� */
    UINT sdm : 1; /* bit4  ��ĵ������������ */

    UINT sap : 1; /* bit3  ��ĵ���μ����� */
    UINT nsp : 1; /* bit8  Ž�����μ����� */
    UINT ksp1 : 1;  /* bit11 �������μ�����1 */
    UINT ksp2 : 1;  /* bit14 �������μ�����2 */
    UINT ksp3 : 1;  /* bit17 �������μ�����3 */
    UINT ksp4 : 1;  /* bit20 �������μ�����4 */
    UINT saf : 1; /* bit5  ��ĵ�м������� */
    UINT nsf : 1; /* bit10 Ž�������� */
    UINT ksf1 : 1;  /* bit13 ����������1 */
    UINT ksf2 : 1;  /* bit16 ����������2 */
    UINT ksf3 : 1;  /* bit19 ����������3 */
    UINT ksf4 : 1;  /* bit22 ����������4 */
    UINT aud : 1; /* bit6  ������߻��� */
    UINT rcv : 1; /* bit7  PDW ������ */
    UINT pdw : 1; /* bit2  ����޸��� */
    UINT cmm : 1; /* bit2  ����޸��� */
  } bits;
} LAN_RSA_IBIT;

/* RXDF I/R BIT ���� ������ */
//##ModelId=452B0C4F007A
typedef union
{
  UINT w32;
  struct
  {
  UINT        : 29;
    UINT Power : 1; /* �������ޱ� */
    UINT PreAmp : 1;  /* ���������������� */
    UINT Total : 1; /* ��������ű� ���� */
  } bits;
} RBIT_OMNI;

//##ModelId=452B0C4F008F
typedef union
{
  UINT w32;
  struct
  {
  UINT    : 13;
    UINT d18 : 1; /* SIO ��� */    // `98.9.2
    UINT d17 : 1; /* DFD */
    UINT d16 : 1; /* ���������� */
    UINT d15 : 1; /* ���ļ�����ó���� */
    UINT d14 : 1; /* ��ȣ���������� */
    UINT d13 : 1; /* ��ȣ�����ռ��� */
    UINT d12 : 1; /* �������������� */
    UINT d11 : 1; /* ���������������ü */
    UINT d10 : 1; /* ��Ž���������� */
    UINT d9 : 1;  /* ������������� */
    UINT d8 : 1;  /* ������������� */
    UINT d7 : 1;  /* �������������� */
    UINT d6 : 1;  /* �������������� */
    UINT d5 : 1;  /* ������������������ */
    UINT d4 : 1;  /* �������������� */
    UINT d3 : 1;  /* ����������2 */
    UINT d2 : 1;  /* ����������1 */
    UINT d1 : 1;  /* ��������ó���� */
    UINT d0 : 1;  /* ���Ź�Žó����ġ ���� */
  } bits;
} RBIT_CTRL;

//##ModelId=452B0C4F00A2
typedef union
{
  UINT w32;
  struct
  {
  UINT        : 27;
    UINT Power : 1; /* �������ޱ�, �뿪 3 */
    UINT Video : 1; /* �񵥿�ó���� */
    UINT Phase : 1; /* �����������ü */
    UINT AmpDet : 1;  /* ������������ü */
    UINT Total : 1; /* ��Ž���ű�(��) ���� */
  } bits;
} RBIT_LEFT;

//##ModelId=452B0C4F00B6
typedef union
{
  UINT w32;
  struct
  {
  UINT        : 27;
    UINT Power : 1; /* �������ޱ�, �뿪 3 */
    UINT Video : 1; /* �񵥿�ó���� */
    UINT Phase : 1; /* �����������ü */
    UINT AmpDet : 1;  /* ������������ü */
    UINT Total : 1; /* ��Ž���ű�(��) ���� */
  } bits;
} RBIT_RIGHT;

//##ModelId=452B0C4F00C1
typedef union
{
  UINT w32;
  struct
  {
  UINT         : 31;
    UINT total : 1; /* ��ȣ�й���ġ ���� */
  } bits;
} RBIT_SHARE;

//##ModelId=452B0C4F00D4
/*
typedef union
{
  UINT w32[ 2 ];
  struct
  {
  UINT      : 16;  reserved
  UINT      : 8;   reserved

    UINT sh : 1;

    UINT rvm : 1;
    UINT rpf : 1;
    UINT raf : 1;

    UINT lvm : 1;
    UINT lpf : 1;
    UINT laf : 1;

    UINT omni : 1;    bit18 ���̴�¡ǥ�м��� ���� 

  UINT    : 16;

  UINT    : 4;
    UINT gn : 1;
    UINT io : 1;
    UINT hf : 1;
    UINT rc : 1;
    UINT sr : 1;
    UINT sm : 1;
    UINT fi : 1;
    UINT dO : 1;
    UINT pd : 1;
    UINT ad : 1;
    UINT ai : 1;
    UINT am : 1;
  } dO ;

  struct
  {
  UINT      : 8;  // reserved

    UINT sh : 1;

    UINT rvm : 1;
    UINT rpf : 1;
    UINT raf : 1;

    UINT lvm : 1;
    UINT lpf : 1;
    UINT laf : 1;

    UINT omni : 1;     bit18 ���̴�¡ǥ�м��� ���� 

  UINT      : 16;  reserved

  UINT    : 4;
    UINT gn : 1;
    UINT io : 1;
    UINT hf : 1;
    UINT rc : 1;
    UINT sr : 1;
    UINT sm : 1;
    UINT fi : 1;
    UINT dO : 1;
    UINT pd : 1;
    UINT ad : 1;
    UINT ai : 1;

  UINT      : 16;  reserved
  } ok ;
} RDF_UBIT5;    5 Words
*/

/* ES (RSA + RXDF) BIT ��� ���� ������ */
//##ModelId=452B0C4F00DF
typedef union
{
  UINT w32;

  struct
  {
  UINT      : 15;     // truth table
    UINT bCip : 1;

    UINT bSap : 1;    /* bit3  ��ĵ���μ����� */
    UINT bNsp : 1;    /* bit8  Ž�����μ����� */
    UINT bKsp1 : 1;    /* bit11 �������μ�����1 */
    UINT bKsp2 : 1;    /* bit14 �������μ�����2 */

    UINT bKsp3 : 1;    /* bit17 �������μ�����3 */
    UINT bKsp4 : 1;    /* bit20 �������μ�����4 */
    UINT bSaf : 1;    /* bit5  ��ĵ�м������� */
    UINT bNsf : 1;    /* bit10 Ž�������� */

    UINT bKsf1 : 1;    /* bit13 ����������1 */
    UINT bKsf2 : 1;    /* bit16 ����������2 */
    UINT bKsf3 : 1;    /* bit19 ����������3 */
    UINT bKsf4 : 1;    /* bit22 ����������4 */

    UINT bAud : 1;    /* bit6  ������߻��� */
    int bRcv : 1;    /* bit7  PDW ������ */
    int bPdw : 1;    /* bit2  ����޸��� */
    UINT bCmm : 1;    /* bit2  ����޸��� */
  } rsa ;
} RSA_UBIT ;

//##ModelId=452B0C4F00FC
typedef union
{
  UINT w32;
  char c[ 4 ];
  struct
  {
  UINT       : 8;
    UINT bTsd : 1;
  UINT       : 23;
  } tsd ;
  struct
  {
  UINT       : 8;
  UINT       : 1;
    UINT bVid : 1;
    UINT bPhs : 1;
    UINT bAmp : 1;
  UINT       : 20;
  } sdfu ;      // Right
  struct
  {
  UINT       : 8;
  UINT       : 4;
    UINT bVid : 1;
    UINT bPhs : 1;
    UINT bAmp : 1;
  UINT       : 17;
  } pdfu ;      // Left
  struct
  {
  UINT       : 8;
  UINT       : 7;
    UINT bOru : 1;
  UINT       : 16;
  } oru ;
  struct
  {
  UINT       : 16;
  UINT       : 1;
    UINT bDfd : 1;
  UINT       : 1;
  UINT       : 1;
    UINT bIo : 1;
    UINT bHf : 1;
  UINT       : 1;
    UINT bRc : 1;
    UINT bSr : 1;
    UINT bSm : 1;
    UINT bFi : 1;
    UINT bDo : 1;
    UINT bPd : 1;
    UINT bAd : 1;
    UINT bAi : 1;
    UINT bAm : 1;
  } sp ;
} RXDF_UBIT ;

//##ModelId=452B0C4F0110
typedef union
{
  UINT w32[ 4 ];

  RSA_UBIT rsa;       // 32bit.
  RXDF_UBIT sp[ 3 ];        // 32bit * 3
} ES_UBIT;      //Modified 1+1+5*3=17 Words `98.8.24

/* LAN RXDF CBIT Result */  // `98.9.3
//##ModelId=452B0C4F011A
typedef union
{
  UINT w32;
  struct
  {
  UINT    : 26;
    UINT b1cm : 1;  /* bit5 Band1 SIO ��� */
    UINT b1fn : 1;  /* bit4 Band1 ��� */
    UINT b2cm : 1;  /* bit3 Band2 SIO ��� */
    UINT b2fn : 1;  /* bit2 Band2 ��� */
    UINT b3cm : 1;  /* bit1 Band3 SIO ��� */
    UINT b3fn : 1;  /* bit0 Band3 ��� */
  } bits;
} LAN_RDF_CBIT;

//##ModelId=452B0C4F0125
typedef LAN_RSA_IBIT LAN_RSA_CBIT;

/* ES (RSA + RXDF) BIT ���� ������ */
//##ModelId=452B0C4F0138
typedef union
{
  UINT w32;
  struct
  {
		UINT      : 21;

    UINT b3Comu : 1;  // Band 3 communication bit
    UINT b2Comu : 1;  // Band 2 communication bit
    UINT b1Comu : 1;  // Band 1 communication bit

    UINT bRsa : 1;		// RSA General Set IBIT
    UINT b3Sp : 1;		// Each Unit IBIT
    UINT b2Sp : 1;
    UINT b1Sp : 1;

    UINT bTsd : 1;
    UINT bSdfu : 1;
    UINT bPdfu : 1;
    UINT bOru : 1;
  } es ;

} ES_IBIT;    // edited `98.9.2, modified `99.05.17

////////////////////////////////////////////////////////////////////
/* ES (RSA + RXDF) BIT ���� ������ */
//##ModelId=452B0C4F0142
typedef union
{
  UINT w32;
  struct
  {
  UINT      : 20;   // dummy

    UINT bCltr : 1;
    UINT bCltl : 1;
    UINT bDiu : 1;
    UINT bSp : 1;
    UINT bTsd : 2;
    UINT bSdfu : 2;
    UINT bPdfu : 2;
    UINT bOru : 2;
  } rxdf ;
} RXDF_SBIT ;

//##ModelId=452B0C4F0160
typedef union
{
  UINT w32;
  struct
  {
  UINT      : 28;
    UINT baet : 1;    // AET ����
    UINT bB3pdw : 1;    // PDW �� Check
    UINT bB2pdw : 1;
    UINT bB1pdw : 1;
  } rsa ;
} RSA_SBIT ;

//##ModelId=452B0C4F016A
typedef struct
{
  RXDF_SBIT sp[ 3 ];  // SP SBIT

  RSA_SBIT rsa; // RSA SBIT
} ES_SBIT ;

////////////////////////////////////////////////////////////////////
/* ES (RSA + RXDF) CBIT ���� ������ */
//##ModelId=452B0C4F017E
typedef union
{
  UINT w32;
  struct
  {
  UINT      : 26;

    UINT bSpin : 1;
    UINT bSpout : 1;

    UINT bSdfuTp : 1; // SDFU Temperature
    UINT bPdfuTp : 1;
    UINT bOruSw : 1;  // Oru Switch
    UINT bOruTp : 1;  // Oru Temperature
  } rxdf ;
} RXDF_CBIT ;

//##ModelId=452B0C4F0188
typedef union
{
  UINT w32;
  struct
  {
  UINT         : 15;    /* bit22-31 Reserved */

    UINT bCip : 1;    /* bit0  ����ĺ����μ����� */

    UINT bSap : 1;    /* bit3  ��ĵ���μ����� */
    UINT bNsp : 1;    /* bit8  Ž�����μ����� */
    UINT bKsp1 : 1;    /* bit11 �������μ�����1 */
    UINT bKsp2 : 1;    /* bit14 �������μ�����2 */

    UINT bKsp3 : 1;    /* bit17 �������μ�����3 */
    UINT bKsp4 : 1;    /* bit20 �������μ�����4 */
    UINT bSaf : 1;    /* bit5  ��ĵ�м������� */
    UINT bNsf : 1;    /* bit10 Ž�������� */

    UINT bKsf1 : 1;    /* bit13 ����������1 */
    UINT bKsf2 : 1;    /* bit16 ����������2 */
    UINT bKsf3 : 1;    /* bit19 ����������3 */
    UINT bKsf4 : 1;    /* bit22 ����������4 */

    UINT bAud : 1;    /* bit6  ������߻��� */
    int bRcv : 1;    /* bit7  PDW ������ */
    int bPdw : 1;    /* bit2  ����޸��� */
    UINT bCmm : 1;    /* bit2  ����޸��� */
  } rsa ;
} RSA_CBIT ;

//##ModelId=452B0C4F0193
typedef struct
{
  RXDF_CBIT sp[ 3 ];
  RSA_CBIT rsa;
} ES_CBIT;

//##ModelId=452B0C4F01A6
typedef struct
{
  // ���ű� ��庰 ��Ž ����(��A)
  UINT spaoadiff[ 3 ];

  // ���ű��庰 ���ļ� ����(��F)
  UINT spfrqdiff[ 3 ];

  // ���� �����켿
  UINT sptrkaoa;
  UINT sptrkfixfrq;
  UINT sptrkagifrq;

  // ������ ����
  UINT spmrgaoa;
  UINT spmrgfrq;

  // �ּ��޽�����
  UINT spminstb;
  UINT spminjit;
  UINT spminrefpri;
  UINT spminagipri;

  // �׷�ȭ
  UINT spshiftaoa;
  UINT spshiftfrq;
} STR_CNFSYS ;

typedef struct {
	float fAOALow, fAOAHgh;
	float fFreqLow, fFreqHgh;
	float fPALow, fPAHgh;
	UINT uiCoPulseNum;
	float fColTime;

} STR_REQ_SETMODE_RSA;

typedef struct {
	UINT uiStatus;
	UINT uiCoPulsenum;
	UINT uiPhase3Num;

} STR_RES_COL_START;

typedef struct {
	float fAOA;
	float fFreq;
	float fPA;
	float fPW;
	UINT uiTOA;

	UINT uiIndex;

} STR_RES_PDW_DATA;

// PDW ������ ���� ����
#define	PDW_RCV_PDW			(1000)
#define	PDW_BLOCK				(30)

//##ModelId=452B0C4F01D9
typedef struct
{
  UINT code;
  UINT size;
  union STR_LAN_PARA
  {
    UINT noEMT;                      // Snd AET#
    //time_t timeTick;          // Time of Msys_Start
    //STR_AET aet;                        // Snd AET Data
    //STR_IPL ipl;                        // Rcv IPL Record
    //LAN_DATA data;                       // Snd & Rcv 4 or 8 Byte Data
    //LAN_IHB_AOA cnfaoa[ _spMaxUsrIhbSize ];   // Rcv RSA cnf ihbaoa 9-range
    //LAN_IHB_FRQ cnffrq[ _spMaxUsrIhbSize ];   // Rcv RSA cnf ihbfrq 9-range
    //LAN_AUDIO cnfaud;                     // Rcv Audio-Para Data, Added `98.8.24

    //ES_IBIT ibit;                       // Snd ES, RSA & RXDF BIT Data
    //ES_SBIT sbit;                       // Snd ES, RSA & RXDF BIT Data
    //ES_CBIT cbit;                       // Snd ES, RSA & RXDF BIT Data
    //ES_UBIT ubit;                       // Snd ES, RSA & RXDF BIT Data

    //STR_SYS sp;
    //STR_CNFSYS cnf;           // System Variable

    //TNEW_PDW pdw[ 100 ];

		//
                //STR_REQ_SETMODE_RSA strReqMode;
                //STR_RES_COL_START strResColStart;

                //STR_RES_PDW_DATA stPDW[PDW_RCV_PDW];

		// 
		UINT uiResult;
  } para;
} STR_LAN_MSG;

#endif

