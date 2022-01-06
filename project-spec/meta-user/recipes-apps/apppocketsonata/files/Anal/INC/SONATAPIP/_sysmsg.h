/****************************************************************************************
 파 일 명 : _sysmsg.h
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 목    적 : 제어조종 및 재밍신호관리기와의 인터페이스 메시지 및 구조 정의
 가    정 :
 저 자 명 : Jo Churl-hee
 변 경 자 :
 변경내용 : (목적)
 변경일시 : 99-05-03 10:05오후
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 입력정의 :
 출력정의 :
 관련모듈 :
 자료구조 : (전역변수)
 에러처리/복귀순서:
 컴파일 일시 :
*****************************************************************************************/

#ifndef _SYSMSG_H_
#define _SYSMSG_H_

/*----------------------------------------------------------------------------------------
    인터페이스 메시지 OPCODE 구조
  자리 수 : 4 자리 - X X X X
             1 2 3 4
    1 자리 : 장치간 인터페이스 종류
       1 X X X : CCU    -> RSA, JSM
           2 X X X : CCU,JSM  -> RSA
           3 X X X : CCU    -> RSA
           4 X X X : RSA    -> CCU, JSM
           5 X X X : RSA    -> JSM
           6 X X X : JSM    -> CCU
    2 자리 : 메시지의 종류
       X 0 X X : 에러 메시지
       X 1 X X : 시스템 운용 관련 메시지
       X 2 X X : 비트 관련 메시지
       X 3 X X : 시스템 각종 운용 변수 설정 관련된 메시지
       X 4 X X : 라이브러리 관련 메시지(IPL, JPL)
       X 5 X X : 위협관련 메시지(AET, JAM)
----------------------------------------------------------------------------------------*/

/////////////////////////////////////////////////////////////////////////////////////////
//  레이더 징표분석기 외부 메시지 정의 : CCU->RSA
//
//  OP코드 + SIZE : Default 8 Bytes
//

/* 운용 메시지  */
#define   Msys_Error        1001  /* (  0) */
#define   Msys_SetMode      1101  /* (  4)시스템모드(1:ES,2:EW,3:비상) */
#define   Msys_Start        1102  /* (  0) */

/* BIT 메시지  */
#define   Mbit_ReqIbit      1201  /* (  4)장치코드 */
/* 1:ES전체, 2:RSA,
             3:대역1 전방향 수신장치, 4:대역1 수신방탐 처리기,
             5:대역1 좌현방향탐지장치, 6:대역1 우현방향탐지장치,
             7:대역1 신호분배기,
             8:대역2 전방향 수신장치, 9:대역2 수신방탐 처리기,
             10:대역2 좌현방향탐지장치, 11:대역2 우현방향탐지장치,
             12:대역2 신호분배기,
             13:대역3 전방향 수신장치, 14:대역3 수신방탐 처리기,
             15:대역3 좌현방향탐지장치, 16:대역3 우현방향탐지장치,
             17:대역3 신호분배기 */
#define   Mbit_StartSbit    1202  /* (  8)밴드 (1:Low,2:Mid,3:Hgh) + 방위
                                  ( 0xF1:1사분면(45도),  0xF2:2사분면(135도),
                                  0xF3:3사분면(225도), 0xF4:4사분면(315도) ) */
#define   Mbit_StopSbit     1203  /* (  8)밴드 (1:Low,2:Mid,3:Hgh) + 방위   `98.9.2
                                  ( 0xF1:1사분면(45도),  0xF2:2사분면(135도),
                                  0xF3:3사분면(225도), 0xF4:4사분면(315도) ) */
#define   Mbit_ReqCbit      1204  /* (  0)  */  //  `98.9.2
#define   Mbit_ReqUbit      1205  /* (  0)  */  //  `99.05.04
#define   Mbit_StartSbit_V3 1206  // for SONATA Ver 3, debug 01-06-01 13:08:09

/*! \bug  랜 상태 요구 메시지
    \date 2007-03-29 10:16:23, 조철희
*/
#define		Mbit_ReqLanStatus	1207

#define   Mbit_ReqUbitTEST  1210  /* (  0)  */  //  `98.9.2

/* 시스템 변수 메시지 */
#define   Mcnf_Audio        3301  /* (  4)동작코드(0:Disable, 1:Enable) */
#define   Mcnf_AudioParam   3302  /* ( 24)LAN_AUD_PAR   `98.9.2
                                        Band Low + High,
                                        Frq. Low + High,
                                        AOA  Low + High */

#define   Mcnf_ScanLevel    3303  /* (  4)위협레벨(0:낮음 ~ 9:높음) */
#define   Mcnf_InhibitAoa   3304  /* (108)LAN_IHB_AOA[9]
                                       (Flag(0:Clear,1:Set)+fromAOA+toAOA) * 9 */
#define   Mcnf_InhibitFreq  3305  /* (144)LAN_IHB_FRQ[9]
                                       (Flag(0:Clear,1:Set)+Band+lowFrq+highFrq) * 9 */

#define   Mcnf_BandEnable     3306  /* (  8)밴드+동작코드(0:Disable,1:Enable) */
#define   Mcnf_NotchFilter    3307  /* (  8)밴드+주파수 */
#define   Mcnf_FmopThreshold  3308  /* (  8)밴드+Threshold */
#define   Mcnf_Dca            3309  /* (  8)밴드(1:Low, 2:Mid, 3:High)+감쇄기 레벨 */
#define   Mcnf_RxThreshold    3310  /* (  8)밴드+Threshold */
#define   Mcnf_PMOPThreshold  3311  //
#define   Mcnf_RxAntOffset    3312  //
#define   Mcnf_EABlankingAttn 3313  //
#define   Mcnf_DelTime        3314  // debug, 01-01-16
#define   Mcnf_ReqSys         3315  // debug, 01-01-16
#define   Mcnf_SetSys         3316  // debug, 01-01-16
#define   Mcnf_EWMode         3317  // 03-07-25
#define   Mcnf_AutoLevel      3318  // 03-07-25
#define   Mcnf_DV             3350  // debug, 01-01-16

// 오디오 시험을 하기 위한 OP코드 추가
#define		Mcnf_AudioWideFrq		3390
#define		Mcnf_AudioWideAoa		3391

// 열잡음 간섭 억제기술 수정사항을 위한 추가
#define   Mcnf_RxThreshold_AutoMode		3320
#define   Mcnf_RxThreshold_AutoLvlThr	4320

/* IPL 메시지 */
#define   Mipl_ReqVersion     3401  /* (  0) */
#define   Mipl_Start          3402  /* (  8)개수+버젼번호(년+월+번호) */
#define   Mipl_Download       3403  /* (516)(STR_IPL) (TBD ? CheckSum) */
#define   Mipl_End            3404  /* (  0) */

/* 에미터 메시지 */
#define   Maet_ReqScan        3501  /* (  4)AET 번호 */
#define   Maet_Clear          3502  /* (  4)AET 번호 */
#define   Maet_SigHide        3504  /* (  4)AET 번호 */
#define   Maet_SigShow        3505  /* (  4)AET 번호 */

#define   Maet_AddJamming     3511  // 03-07-25
#define   Maet_DelJamming     3512  // 03-07-25

///////////////////////////////////////////////////////////////////////////////////////
#define		Mreq_SetConfig			(9301)
#define		Mreq_Stop						(9302)
#define		Mreq_ColStart				(9401)
#define		Mreq_RawData				(9405)

/////////////////////////////////////////////////////////////////////////////////////////
//  레이더 징표분석기 외부 메시지 정의 : RSA->CCU
//
/* 운용 메시지  */
#define   Esys_SetMode        2101  /* (  0) */

/* BIT 메시지  */
#define   Mbit_ResultEsIbit   4201  /* ( 68)LAN_BIT(17 * 4Byte)
                                         ES종합,RSA,
                                         수신기대역1(5W), 대역2(5W), 대역3(5W) */
#define   Mbit_ResultEsSbit   4202  /* (312)STR_AET */  // 재사용 `98.9.3
#define   Mbit_Aet            4203  /* (312)STR_AET */  // 재사용 `98.9.3
#define   Mbit_ResultEsCbit   4204  /* (  8)RSA(0:정상, 1:비정상) +
                                          RXDF(0:정상, 1:비정상)
                                          Band1:D5(통신), D4(기능)
                                          Band1:D3(통신), D2(기능)
                                          Band1:D1(통신), D0(기능) */
#define   Mbit_ResultEsUbit   4205  /* (  8)RSA(0:정상, 1:비정상) +   */
#define		Mbit_ResultLanStatus	4206	/* (  8)RSA(0:정상, 1:비정상) + 	*/

/* IPL 메시지 */
#define   Mipl_Version        4401  /* (  4)버젼번호(년+월+번호) */
#define   Mipl_WriteStatus    4402  /* (  4)Writing하고 있는 퍼센트(IPL개수에 대한) */
#define   Mipl_SetAnalysisMode	3410  /* CCU에서 RSA로 기본/개략 식별 모드 설정 */
#define   Mipl_AnalysisMode		4410  /* RSA에서 CCU로 설정된 식별모드 값 전송 */
#define   Mipl_SetFSDetectMode	3411  /* CCU에서 RSA로 소신호탐지모드 설정 */
#define   Mipl_FSDetectMode		4411  /* RSA에서 CCU로 설정된 소신호탐지모드 값 전송 */

/* 에미터 메시지 */
#define   Maet_New_Ccu        4501    /* (312)STR_AET */
#define   Maet_Update_Ccu     4502    /* (312)STR_AET */
#define   Maet_Lost_Ccu       4503    /* (  4)AET 번호 */
#define   Maet_Delete_Ccu     4504    /* (  4)AET 번호 */
#define   Maet_AllSend_Ccu    4505

// added 01-01-16
#define   Ecnf_SetSys         4601

// debug, 00-05-12 14:52:34
#define   Msys_Modify         4609

// DEBUG용 LAN 메시지
#define   Msys_Reboot         4700
#define   Mdebug_Get_Pdw      0x1ff0
#define   Mdebug_Snd_Pdw      0x1ff1
#define   Mdebug_Rcv_Pdw      (Mdebug_Snd_Pdw)


///////////////////////////////////////////////////////////////////////////////////////
#define		Mres_SetConfig			(9302)
#define		Mres_ColStart				(9404)
#define		Mres_RawData_PDW		(9506)
#define		Mres_RawData_ZPDW		(9508)

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
//  레이더 징표분석기 수신금지영역 개수 정의
//
#define   _spMaxUsrIhbSize    9

/////////////////////////////////////////////////////////////////////////////////////////
//  LAN 통신 Send Size Offset 정의   `98.9.8a
//  appended def. for the variable LAN structure, 99.05.06
//
#define   _spSndSizeOffset    (2*sizeof(UINT))  // OpCode + Size
#define   _spRecSizeOffset    (2*sizeof(UINT))  // OpCode + Size
#define   _spCoMsys_Error     (2*sizeof(UINT))  // request opcdeo + error code

/* LAN 기본 데이터 */
//##ModelId=452B0C4E03E1
struct LAN_DATA
{
  unsigned int d1;            // opcode or operand
  unsigned int d2;            // operand
} ;

/* RSA CNF 방위 INHIBIT 데이터 */
//##ModelId=452B0C4F000D
//typedef hwLAN_IHB_AOA LAN_IHB_AOA;      // in hw_str.h
//##ModelId=452B0C4F0034
//typedef hwLAN_IHB_FRQ LAN_IHB_FRQ;

/* RSA CNF 오디오 설정 데이터 */
//##ModelId=452B0C4F003F

//##ModelId=452B0C4F0053
struct STR_PRCSBIT {
  unsigned int nsp;
  unsigned int cip;
  unsigned int sap;
  unsigned int ksp[ 4 ];
  unsigned int coEcho;
}  ;

/* RSA IBIT 종합 데이터 */
//##ModelId=452B0C4F0067
typedef union
{
  UINT w32;
  struct
  {
    UINT dummy : 8;  /* bit22-31 Reserved */
    UINT cip : 1; /* bit0  제어식별프로세서판 */
    UINT gen : 1; /* general bit */

    UINT kdm4 : 1;  /* bit21 추적데이터저장판4 */
    UINT kdm3 : 1;  /* bit18 추적데이터저장판3 */
    UINT kdm2 : 1;  /* bit15 추적데이터저장판2 */
    UINT kdm1 : 1;  /* bit12 추적데이터저장판1 */
    UINT ndm : 1; /* bit9  탐지데이터저장판 */
    UINT sdm : 1; /* bit4  스캔데이터저장판 */

    UINT sap : 1; /* bit3  스캔프로세서판 */
    UINT nsp : 1; /* bit8  탐지프로세서판 */
    UINT ksp1 : 1;  /* bit11 추적프로세서판1 */
    UINT ksp2 : 1;  /* bit14 추적프로세서판2 */
    UINT ksp3 : 1;  /* bit17 추적프로세서판3 */
    UINT ksp4 : 1;  /* bit20 추적프로세서판4 */
    UINT saf : 1; /* bit5  스캔분석필터판 */
    UINT nsf : 1; /* bit10 탐지필터판 */
    UINT ksf1 : 1;  /* bit13 추적필터판1 */
    UINT ksf2 : 1;  /* bit16 추적필터판2 */
    UINT ksf3 : 1;  /* bit19 추적필터판3 */
    UINT ksf4 : 1;  /* bit22 추적필터판4 */
    UINT aud : 1; /* bit6  오디오발생판 */
    UINT rcv : 1; /* bit7  PDW 수신판 */
    UINT pdw : 1; /* bit2  공용메모리판 */
    UINT cmm : 1; /* bit2  공용메모리판 */
  } bits;
} LAN_RSA_IBIT;

/* RXDF I/R BIT 종합 데이터 */
//##ModelId=452B0C4F007A
typedef union
{
  UINT w32;
  struct
  {
  UINT        : 29;
    UINT Power : 1; /* 전원공급기 */
    UINT PreAmp : 1;  /* 고주파전단증폭기 */
    UINT Total : 1; /* 전방향수신기 종합 */
  } bits;
} RBIT_OMNI;

//##ModelId=452B0C4F008F
typedef union
{
  UINT w32;
  struct
  {
  UINT    : 13;
    UINT d18 : 1; /* SIO 통신 */    // `98.9.2
    UINT d17 : 1; /* DFD */
    UINT d16 : 1; /* 수신제어판 */
    UINT d15 : 1; /* 주파수정보처리판 */
    UINT d14 : 1; /* 신호측정제어판 */
    UINT d13 : 1; /* 신호제원합성판 */
    UINT d12 : 1; /* 수신제어접속판 */
    UINT d11 : 1; /* 전방향고주파조립체 */
    UINT d10 : 1; /* 방탐제어접속판 */
    UINT d9 : 1;  /* 방위출력제어판 */
    UINT d8 : 1;  /* 위상방위연산판 */
    UINT d7 : 1;  /* 위상측정보정판 */
    UINT d6 : 1;  /* 진폭방위연산판 */
    UINT d5 : 1;  /* 진폭구간방위연산판 */
    UINT d4 : 1;  /* 진폭방위보정판 */
    UINT d3 : 1;  /* 진폭측정판2 */
    UINT d2 : 1;  /* 진폭측정판1 */
    UINT d1 : 1;  /* 진폭정보처리판 */
    UINT d0 : 1;  /* 수신방탐처리장치 종합 */
  } bits;
} RBIT_CTRL;

//##ModelId=452B0C4F00A2
typedef union
{
  UINT w32;
  struct
  {
  UINT        : 27;
    UINT Power : 1; /* 전원공급기, 대역 3 */
    UINT Video : 1; /* 비데오처리판 */
    UINT Phase : 1; /* 위상검출조립체 */
    UINT AmpDet : 1;  /* 진폭검출조립체 */
    UINT Total : 1; /* 방탐수신기(좌) 종합 */
  } bits;
} RBIT_LEFT;

//##ModelId=452B0C4F00B6
typedef union
{
  UINT w32;
  struct
  {
  UINT        : 27;
    UINT Power : 1; /* 전원공급기, 대역 3 */
    UINT Video : 1; /* 비데오처리판 */
    UINT Phase : 1; /* 위상검출조립체 */
    UINT AmpDet : 1;  /* 진폭검출조립체 */
    UINT Total : 1; /* 방탐수신기(우) 종합 */
  } bits;
} RBIT_RIGHT;

//##ModelId=452B0C4F00C1
typedef union
{
  UINT w32;
  struct
  {
  UINT         : 31;
    UINT total : 1; /* 신호분배장치 종합 */
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

    UINT omni : 1;    bit18 레이더징표분석기 종합 

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

    UINT omni : 1;     bit18 레이더징표분석기 종합 

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

/* ES (RSA + RXDF) BIT 결과 종합 데이터 */
//##ModelId=452B0C4F00DF
typedef union
{
  UINT w32;

  struct
  {
  UINT      : 15;     // truth table
    UINT bCip : 1;

    UINT bSap : 1;    /* bit3  스캔프로세서판 */
    UINT bNsp : 1;    /* bit8  탐지프로세서판 */
    UINT bKsp1 : 1;    /* bit11 추적프로세서판1 */
    UINT bKsp2 : 1;    /* bit14 추적프로세서판2 */

    UINT bKsp3 : 1;    /* bit17 추적프로세서판3 */
    UINT bKsp4 : 1;    /* bit20 추적프로세서판4 */
    UINT bSaf : 1;    /* bit5  스캔분석필터판 */
    UINT bNsf : 1;    /* bit10 탐지필터판 */

    UINT bKsf1 : 1;    /* bit13 추적필터판1 */
    UINT bKsf2 : 1;    /* bit16 추적필터판2 */
    UINT bKsf3 : 1;    /* bit19 추적필터판3 */
    UINT bKsf4 : 1;    /* bit22 추적필터판4 */

    UINT bAud : 1;    /* bit6  오디오발생판 */
    int bRcv : 1;    /* bit7  PDW 수신판 */
    int bPdw : 1;    /* bit2  공용메모리판 */
    UINT bCmm : 1;    /* bit2  공용메모리판 */
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
    UINT b1cm : 1;  /* bit5 Band1 SIO 통신 */
    UINT b1fn : 1;  /* bit4 Band1 기능 */
    UINT b2cm : 1;  /* bit3 Band2 SIO 통신 */
    UINT b2fn : 1;  /* bit2 Band2 기능 */
    UINT b3cm : 1;  /* bit1 Band3 SIO 통신 */
    UINT b3fn : 1;  /* bit0 Band3 기능 */
  } bits;
} LAN_RDF_CBIT;

//##ModelId=452B0C4F0125
typedef LAN_RSA_IBIT LAN_RSA_CBIT;

/* ES (RSA + RXDF) BIT 종합 데이터 */
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
/* ES (RSA + RXDF) BIT 종합 데이터 */
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
    UINT baet : 1;    // AET 유무
    UINT bB3pdw : 1;    // PDW 수 Check
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
/* ES (RSA + RXDF) CBIT 종합 데이터 */
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

    UINT bCip : 1;    /* bit0  제어식별프로세서판 */

    UINT bSap : 1;    /* bit3  스캔프로세서판 */
    UINT bNsp : 1;    /* bit8  탐지프로세서판 */
    UINT bKsp1 : 1;    /* bit11 추적프로세서판1 */
    UINT bKsp2 : 1;    /* bit14 추적프로세서판2 */

    UINT bKsp3 : 1;    /* bit17 추적프로세서판3 */
    UINT bKsp4 : 1;    /* bit20 추적프로세서판4 */
    UINT bSaf : 1;    /* bit5  스캔분석필터판 */
    UINT bNsf : 1;    /* bit10 탐지필터판 */

    UINT bKsf1 : 1;    /* bit13 추적필터판1 */
    UINT bKsf2 : 1;    /* bit16 추적필터판2 */
    UINT bKsf3 : 1;    /* bit19 추적필터판3 */
    UINT bKsf4 : 1;    /* bit22 추적필터판4 */

    UINT bAud : 1;    /* bit6  오디오발생판 */
    int bRcv : 1;    /* bit7  PDW 수신판 */
    int bPdw : 1;    /* bit2  공용메모리판 */
    UINT bCmm : 1;    /* bit2  공용메모리판 */
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
  // 수신기 밴드별 방탐 오차(δA)
  UINT spaoadiff[ 3 ];

  // 수신기밴드별 주파수 오차(δF)
  UINT spfrqdiff[ 3 ];

  // 추적 윈도우셀
  UINT sptrkaoa;
  UINT sptrkfixfrq;
  UINT sptrkagifrq;

  // 에미터 병합
  UINT spmrgaoa;
  UINT spmrgfrq;

  // 최소펄스열수
  UINT spminstb;
  UINT spminjit;
  UINT spminrefpri;
  UINT spminagipri;

  // 그룹화
  UINT spshiftaoa;
  UINT spshiftfrq;
} STR_CNFSYS ;

/*
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
*/

// PDW 수신판 관련 정의
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

