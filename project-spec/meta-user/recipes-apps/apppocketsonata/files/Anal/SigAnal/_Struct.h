// Struct.h: interface for the Ž���м��� ����Ʈ������ ����ü
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRUCT_H__554E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_)
#define AFX_STRUCT_H__554E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../INC/_pdw.h"
#include "../INC/_aetipl.h"

//#define BIT_MERGE(high,low)     ( ( ((UINT)high) << 8 ) | low )

// PDW  �޽��� �÷���
//##ModelId=452B0C5402BC
enum PULSE_EXTRACT_MARK { UnMark=0, STABLE_MARK, REFSTB_MARK, JITTER_MARK, DWELL_MARK, UNKNOWN_MARK, EXTRACT_MARK, Discard } ;

//##ModelId=452B0C5402D0
typedef USHORT PDWINDEX;

// #ifndef _STR_PDWData
// #define _STR_PDWData
// typedef struct {
// 	UINT count;
// 	_PDW *pPdw;
// 
// } STR_PDWDATA ;
// #endif

// Ž�� PDW Index
//##ModelId=452B0C5402E5
typedef struct {
  PDWINDEX *pIndex;
  int count;

} STR_PDWINDEX ;

// ������׷� 
//##ModelId=452B0C5402F8
typedef struct {
	PDWINDEX hist[ TOTAL_FRQAOAPWBIN ];
	int bin_count;

} STR_FRQAOAPWHISTOGRAM ;


// DTOA ������׷� ����ü
//##ModelId=452B0C540302
typedef struct {
	int bin_count;
	PDWINDEX hist[ DTOA_BIN ];

	STR_LOWHIGH bin_range;

	int bin_peak_count;
	UINT bin_peak[ MAX_PEAK_DTOAHISTOGRAM+1 ];

	int dtoa_peak_count;
	_TOA dtoa_peak[ MAX_PEAK_DTOAHISTOGRAM+1 ];	// Dwell ������ �м��ϱ� ���� ����

} STR_DTOA_HISTOGRAM ;

// ����(AOA) �׷� 
//##ModelId=452B0C540317
typedef struct {
	UINT band;
  UINT stat;
  PDWINDEX *pIndex;
  int count;
  UINT bOverAoa;
  UINT from_aoa;
  UINT to_aoa;
  UINT from_bin;
  UINT to_bin;

} STR_AOA_GROUP ;

// ���� �׷�ȭ ����ü
//##ModelId=452B0C54032A
typedef struct {
  STR_AOA_GROUP aoa[ MAX_AGRT ];
  int count;
	int coAnal;

} STR_AOA_GROUPS ;

// ���ļ� �׷���� ���̺�  
//##ModelId=452B0C540335
typedef struct {
	int	aoa_idx;			// ���� �׷�ȭ �ε���

	UINT from_frq;
	UINT to_frq;
  UINT from_bin;
  UINT to_bin;
	char narrow_wide;
	char end_of_aoagroup;

} STR_FRQ_GROUP ;

// ���ļ� �׷���� ���̺�  
//##ModelId=452B0C540348
typedef struct {
	STR_FRQ_GROUP frq[ MAX_FGRT ];
	int count;
	int coAnal;

} STR_FRQ_GROUPS ;

//##ModelId=452B0C54035C
typedef struct {
	int	frq_idx;			// ���ļ� �׷�ȭ �ε���

	UINT from_pw;
	UINT to_pw;
  UINT from_bin;
  UINT to_bin;

} STR_PW_GROUP ;

// ���ļ� �׷���� ���̺�  
//##ModelId=452B0C540366
typedef struct {
	STR_PW_GROUP pw[ MAX_PGRT ];
	int count;
	int coAnal;

} STR_PW_GROUPS ;

// ISODATA Ŭ�����͸� ���̺�
//##ModelId=452B0C540371
typedef struct {
	int count;
	PDWINDEX index[SAP_MAX_PDW];
	int center;
	float deviation;
	float distance;
	STR_LOWHIGH aoa;

} STR_CLUSTER ;

// Ž���� �޽����� �����Կ��� �м��� ���� �ʴ� ����
//##ModelId=452B0C54038E
typedef struct {
	STR_LOWHIGH	aoa; 
	STR_LOWHIGH	frq;
	UINT band;
	UINT tot_cnt;
	UINT count;
	UINT enable;

} STR_FIRST_FRQAOA_PEAK ;

// �޽��� �� ����
//##ModelId=452B0C540398
typedef struct {
	STR_PDWINDEX pdw;				// �޽��� �ε���, �� ����ü�� ���� �տ� �־�� ��.

	UINT miss;							// missing ����, <- �� �տ� ������ �������� ���ƾ���. CPulExt::MemcpySeg() ������.
	UINT pri_band;					// �޽��� ������ ���� PRI ���
	UINT extract_step;			// ���� �޽���, STABLE, Jitter PRI
	PDWINDEX gr_ref_idx;				// �����޽�, �����޽��� ���� �޽�
	PDWINDEX first_idx;			// �޽��� ���� �޽� �ε���, pdw.pIndex�� �ε����� ����Ų��.
	PDWINDEX last_idx;			// �޽��� ���� �޽�, pdw.pIndex�� �ε����� ����Ų��.
	_TOA first_toa;					// �޽��� ù��° TOA
	_TOA last_toa;					// �޽��� ������ TOA
	UINT stat;							// PDW ����
	UINT freq_type;					// ���ļ� Ÿ��
	STR_MINMAX aoa;					// ���� ���� 
	STR_MINMAX_MEDIAN freq;				// ���ļ� ���� 
	STR_MINMAX pa;					// ��ȣ���� ���� 
	STR_MINMAX pw;					// �޽��� ���� 
	UINT pri_type;					// PRI Ÿ��
	STR_MINMAX_TOA pri;					// PRI ����
	UINT min_dtoa;					// DTOA ���� �߿��� �ּҰ� �Ǵ� ��
	float jitter_p;					// ������
	UINT continuity;				// �޽��� ���Ӽ�(%)
	UINT band;							// ���ļ� Band Code
	UINT peak_idx;					// peak PA�� �޽� index
	//UINT cd;								// Correct Detection
	//UINT steady;						// steady ��ĵƯ��
	SEG_MARK mark;							// �޽����� ���� ǥ�� 
													// ����=0, �������=1, �����ͷ� üũ�� ����=2
	UINT pri_pat_period;		// PRI  ���� �ֱ�
	UINT freq_pat_period;		// FREQ ���� �ֱ�
	
} STR_PULSE_TRAIN_SEG ;

// Freq resolution struct
//##ModelId=452B0C5403A3
/*
typedef struct {    // frequency band code�� ���� ����ü
  UINT min;					// min frequency
  UINT max;					// max frequency
  float res;				// �� ������ ���� resolution

} STR_FREQ_RESOL ;
*/

// PRI Table 
//##ModelId=452B0C5403B6
typedef struct {
	_TOA min_pri;		// ���� ���� 
	_TOA max_pri;		// ���� ���� 

} STR_PRI_RANGE_TABLE ;

// ������ ����
//##ModelId=452B0C5403CA
typedef struct {
	STR_PDWINDEX pdw;						// PDW ����
	UINT seg_idx[ MAX_PT ];			// �޽��� index, �Ķ���� ���� 
	int seg_count;							// seg[] ��, �޽��� ��

	PRI_TYPE pri_type;							// PRI ����
	_TOA framePri;								// ���°��� ���� frmae PRI ��
	STR_MINMAX_TOA pri;							// ������ �޽����� PRI ����
	UINT pri_patterntype;
	float priPeriod;

	int stag_dwell_element_cnt;					// stagger level �� 
	_TOA stag_dwell_element[ MAX_STAGGER_LEVEL_ELEMENT ];		// Stagger level

	int stag_dwell_level_cnt;					// stagger level �� 
	_TOA stag_dwell_level[ MAX_STAGGER_LEVEL_ELEMENT ];		// Stagger level

	int hop_level[ MAX_HOP_LEVEL_ELEMENT ];					// Hopping level
	int hop_level_cnt;					// Hop level �� 

	SIGNAL_TYPE signal_type;	

	FREQ_TYPE freq_type;
	UINT freq_patterntype;
	STR_TYPEMINMAX freq;				// ������ ���� ���սÿ� �Ǵ��� ���ļ� ��跮
	float freqPeriod;

	STR_MINMAX pw;							// ������ �޽����� PRI ����

	UINT main_seg;							// �м��� ������ seg index
	EMITTER_MARK mark;									// ���� ���� 

	int iDIRatio;

} STR_EMITTER ;

// �޽����� ������ �Ի��ϱ� ���� ����
//##ModelId=452B0C5403D5
typedef struct {
	_TOA *pTOAParam;
	UINT *puiParam;
	int *piParam;

	int count;

} STR_PDWPARAM ;



/////////////////////////////////////////////////////////////////////////////////////////
//  RF AOA margin
//

/////////////////////////////////////////////////////////////////////////////////////////
//  system parameter data structure
//
//##ModelId=452B0C4E030E
typedef struct
{
  UINT mode;
} STR_CT ;

//##ModelId=452B0C4E032C
typedef struct
{
  UINT aoadiff[ ALL_BAND+1 ];
  UINT frqdiff[ ALL_BAND+1 ];
} STR_SP;

//##ModelId=452B0C4E0354
typedef struct
{
	// ���ļ� ���� �Ӱ谪
  UINT fixfrq[ ALL_BAND+1 ];

	// ���ļ� ���� �Ӱ谪
  UINT agifrq[ ALL_BAND+1 ];
  UINT pri;     // pri tol.
  UINT prd;     // scan tol.

  UINT frqPrd;      // When Pattern Agile, comparative period val.
  UINT priPrd;      // When PRI Pattern, comparative period val.

} STR_ID ;

//##ModelId=452B0C4E035F
typedef struct
{
  //  UINT  mode;
  UINT aoa[ ALL_BAND+1 ];

  UINT fixfrq[ ALL_BAND+1 ];
  UINT fixfrq_boundary[ ALL_BAND+1 ];

  UINT agifrqmean;    // agile/agile, agile/pattern
  UINT agifrqin;    // agile/agile, agile/pattern
  UINT agifrqout;   // agile/agile, agile/pattern
  UINT agifrqpat[ ALL_BAND+1 ];  // pattern/pattern
  UINT md_agifrq[ ALL_BAND+1 ];  // debug, 00-01-31 16:35:43

  UINT fixpri;      // stable PRI.
  UINT agiprimean;    // agile/agile, agile/pattern
  UINT agipriin;    // agile/agile, agile/pattern
  UINT agipriout;   // agile/agile, agile/pattern
  UINT agipripat; // pattern/pattern

  UINT frqPrd;      // When Pattern Agile, comparative period val.
  UINT priPrd;      // When PRI Pattern, comparative period val.

  UINT scnPrd;      // When scan is sucessful, comparative period val.

  UINT jtrper;      // PRI jitter %

  UINT pw;        // PRI jitter %

  UINT mdyMethod;   // Method of modify parameter, debug, 00-08-31 10:19:35
} STR_MG ;

//##ModelId=452B0C4E0373
typedef struct
{
  UINT aoa[ ALL_BAND+1 ];

  UINT fixfrq[ ALL_BAND+1 ];
  UINT agifrq[ ALL_BAND+1 ];
  UINT agiratio;    //  debug, 00-04-19 17:46:13

  //  UINT  pw;       // PW
  //  UINT  pa;

  UINT CWTo;
  UINT CWPc;

  UINT normPc;
  UINT abnormPc;

  UINT chirpTo;
  UINT chirpPc;

  float maxTim;     // as times as scan period for collecting time out
  UINT timPrd;      // as times as scan period for collecting pulse count

  //STR_LOWHIGH tkto;   // Track Timeout
  //STR_LOWHIGH tkpc;   // Track Pulse count

  UINT scto[ _spMaxTryScan + 1 ];

} STR_FT ;

//#ModelId=452B0C4E037D
typedef struct
{
  STR_LOWHIGH frq[ ALL_BAND+1 ];

} STR_FG ;

//##ModelId=452B0C4E039A
typedef struct
{
  UINT Pdw_Max;            // ���� PDW �ִ��
  UINT Aoa_Shift_Cnt;      // ���� ������ BIN ũ�� = 2^N
  UINT Aoa_Peak_Thr;       // ���� ������׷� PEAK �Ӱ谪  // 00.02.09
  UINT Aoa_Hist_Thr;       // ���� ������׷� ���� �Ӱ谪  // 00.02.09
  UINT Aoa_Range_Margin;   // ���� �׷� ���� margin

  UINT Freq_Shift_Cnt;     // ���ļ� ������ BIN ũ�� = 2^N
  UINT Freq_Peak_Thr;      // ���ļ� ������׷� PEAK �Ӱ谪    // 00.02.09
  UINT Freq_Hist_Thr;      // ���ļ� ������׷� ���� �Ӱ谪    // 00.02.09
  UINT Freq_Range_Margin;  // ���ļ� �׷� ���� margin

  UINT Rpt_Aet_Cnt;    // Ž��; �ϳ��� �׷쿡�� REPORT�� AET�� ������ ����
} STR_NP ;

//##ModelId=452B0C4E03AE
typedef struct
{
  UINT Pdw_Max;            // ���� PDW �ִ��
  /*  UINT    Aoa_Shift_Cnt;      // ���� ������ BIN ũ�� = 2^N
      UINT    Aoa_Peak_Thr;       // ���� ������׷� PEAK �Ӱ谪  // 00.02.09
      UINT    Aoa_Hist_Thr;       // ���� ������׷� ���� �Ӱ谪  // 00.02.09
      UINT    Aoa_Range_Margin;   // ���� �׷� ���� margin
   
      UINT    Freq_Shift_Cnt;     // ���ļ� ������ BIN ũ�� = 2^N
      UINT    Freq_Peak_Thr;      // ���ļ� ������׷� PEAK �Ӱ谪    // 00.02.09
      UINT    Freq_Hist_Thr;      // ���ļ� ������׷� ���� �Ӱ谪    // 00.02.09
      UINT    Freq_Range_Margin;  // ���ļ� �׷� ���� margin
  */

  UINT Rpt_Aet_Cnt;    // ����; �ϳ��� �׷쿡�� REPORT�� AET�� ������ ����
} STR_KP ;

//##ModelId=452B0C4E03B9
typedef struct
{
  UINT Cw_Min_Cnt;         // CW��ȣ�� �м��ϱ� ���� �ּ� CW����

  UINT Mpc;                //000223 // Stable �޽����� �ּ� �޽��� (Min. Pulse Count)
  UINT Mjpc;               //000223 // Jitter �޽����� �ּ� �޽��� (Min. Jitter Pulse Count)
  UINT Rpc;                // ���� �޽����� �޽��� (Reference Pule Count)
  UINT Rjgpc;              // 000404  Jitter Stagger �����޽����� �ּ� �޽��� (Min. Jitter Stagger Pulse Count)

  UINT Stb_Max_Miss;       // �ִ� ��� STABLE MISS ����
  UINT Jit_Max_Miss;       // �ִ� ��� JITTER MISS ����

  UINT Reflex_Zone;        // �ݻ��� ó�� ����
  UINT Hprf_First_Pri;     // �ݻ���ó�� ������ High PRF���� ó��

  UINT Jitter_P;           // �ִ� Ž�� jitter %  990226

  UINT Dtoa_Sd;            // 500ns / (50 ns) MEAN ERROR
  UINT Freq_Sd;            // low : 1.5 / (0.5MHz), mid : 3.75 / (1.25MHz), High : 4.5 / (1.5MHz)


  UINT Jstg_Pt_P;          // Jitter Stagger�м����� Stagger�� ����� �޽����� ���� ���, �̻���~�� Stagger�� ����
  UINT Jit_Merge_Miss_Cnt; // �ִ� ��� ���� JITTER MISS ����

  // ���� �м�
  UINT Pat_Min_Cnt;        // ���� �м��� �ʿ��� �ּ� �޽���
  UINT Lhp;                // Least Half Period �ּ� ���ֱ� �޽���
  UINT Cross_Over;         // ���Ͽ��� LHP���� ����� ���������� �ִ� ȸ��
  UINT Lhp_Thresh;         // ���� Ȯ�ο� ���Ǵ� �ּҹ��ֱ��� ȸ��
  UINT Bad_Max;            // ���� Ȯ�ο��� �ִ� bad ȸ��
  UINT Filt_Fac;           // Filtering Factor ���� �Ķ���� ��չ迭(filt[])�� ���鶧 ����� ��~�ϴ� ��ȣ��
  UINT Maxparam_Min;       // ��չ迭(filt[])�� �ִ밪�� �ּ����� ��
  UINT Pp_Max_Margin_P;    // �����ֱ� �������� ���Ǵ� �ִ밪�� margin %
  UINT Pp_Match_P;         // �����ֱ� ���ϱ⿡�� ���Ϻ񱳿��� ��������

  // MAKE AET
  UINT Conti_Thr;          // ���Ӽ� �ִ� ����
  UINT Rpt_Pul_Cnt;        // �� �� �̻��� �޽����� AET�� ������ REPORT ���
} STR_CM ;

//##ModelId=452B0C4E03CC
typedef struct
{
  UINT Pdw_Max;            // ���� PDW �ִ��
  UINT st[ _spMaxTryScan ];
  UINT offst[ _spMaxTryScan ];

  UINT thtrkprd;
} STR_SC;

//##ModelId=452B0C4E03D6
typedef struct
{
  UINT mode;

  UINT ver[ 2 ];
  UINT date;

  // Control system parameters
  UINT scnLev;    // 6

  STR_SP sp;

  STR_FG pw;      // Antenna Freq. range

  //  STR_ID    id;
  STR_MG mg;
  STR_FT ft;

  // Ž�� system parameters
  STR_NP np;

  // ���� system parameters
  STR_KP kp;

  // ����(Common) system parameters
  STR_CM cm;

  // ��ĵ(SAP) system parameters
  STR_SC sc;
} STR_SYS ;

/**	\brief	����ü�� FREQ_RESOL 
*/
typedef struct {
  // frequency band code�� ���� ����ü 
  UINT min;       // min frequency
  UINT max;       // max frequency
	int offset;       // max frequency
  float res;			// �� ������ ���� resolution
} FREQ_RESOL ;

typedef struct {
  // frequency band code�� ���� ����ü 
  UINT min;       // min frequency
  UINT max;       // max frequency
	float offset;      // max frequency
  float res;			// �� ������ ���� resolution
} PA_RESOL ;

typedef struct {
	int iPulseCount1;
	_TOA dtoa1;
	int iPulseCount2;
	_TOA dtoa2;

	bool bUsed;

} STR_DWELL_LEVEL;

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef _MAIN_
  STR_SYS _sp;

  // ���ļ� ��庰 �ɼ°��� resolution
  // Update AOA threshold
  UINT _sprfaoa[ 6 ] =
  {
    0, 2 * _spRxdfAoa, 2 * _spRxdfAoa, 2 * _spRxdfAoa, 2 * _spRxdfAoa, 2 * _spRxdfAoa
  } ;

  // �����ͷ� �����ϴ� �� 
  UINT _spdiffaoa[ 6 ] =
  {
    0, 5 * _spRxdfAoa, 5 * _spRxdfAoa, 5 * _spRxdfAoa, 5 * _spRxdfAoa, 5 * _spRxdfAoa
  } ;


#define DFD_FREQ_OFFSET		(1900)

FREQ_RESOL gFreqRes[ 6 ] =
{	// min, max, offset, res
  {     0,     0,				 DFD_FREQ_OFFSET,  1.25 }, 
	{  2000,  6000,        DFD_FREQ_OFFSET,  1.25 },		/* ���뿪		*/
	{  5500, 10000,  12000-DFD_FREQ_OFFSET, -1.25 },		/* ��뿪1	*/
	{ 10000, 14000,  16000-DFD_FREQ_OFFSET, -1.25 },		/* ��뿪2	*/
	{ 14000, 18000,  12000+DFD_FREQ_OFFSET,  1.25 },		/* ��뿪3	*/
	{     0,  5000,   6300-DFD_FREQ_OFFSET, -1.25 }		/* C/D			*/
} ;

PA_RESOL gPaRes[ 6 ] =
{	// min, max, offset, res
  {     0,     0,  (float) _spPAoffset, _spAMPres }, 
	{  2000,  6000,  (float) _spPAoffset, _spAMPres },		/* ���뿪		*/
	{  5500, 10000,  (float) _spPAoffset, _spAMPres },		/* ��뿪1	*/
	{ 10000, 14000,  (float) _spPAoffset, _spAMPres },		/* ��뿪2	*/
	{ 14000, 18000,  (float) _spPAoffset, _spAMPres },		/* ��뿪3	*/
	{     0,  5000,  (float) -54.14071, (float) 0.24681 }		/* C/D			*/
} ;

#else
	extern float _toaRes[en50MHZ_BW+1];

  extern STR_SYS _sp;

#ifdef _ELINT_
  extern UINT _sprfaoa[ 6 ];
  extern UINT _spdiffaoa[ 6 ];
	extern FREQ_RESOL gFreqRes[ 6 ];
	extern PA_RESOL gPaRes[ 6 ];
#else
  extern UINT _sprfaoa[ 4 ];
  extern UINT _spdiffaoa[ 4 ];
	extern FREQ_RESOL gFreqRes[ 4 ];
#endif

#endif


#ifdef __cplusplus
}
#endif


// qsort �Լ� ����
int pdwindexCompare( const void *arg1, const void *arg2 );

#endif // !defined(AFX_NSTRUCT_H__554E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_)
