/****************************************************************************************
 파 일 명 : _pdw.h
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 목    적 : PDW 정의
 가    정 :
 저 자 명 : 조철희
 변 경 자 :
 변경내용 : (목적)
 변경일시 : 2007-12-28 10:05:31
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 입력정의 :
 출력정의 :
 관련모듈 :
 자료구조 : (전역변수)
 에러처리/복귀순서:
 컴파일 일시 :
*****************************************************************************************/

#ifndef _PDW_H_
#define _PDW_H_

#include "../SigAnal/_type.h"

#ifdef _SONATA_
#define PDW_WORD_LEN        4
#define PDW_WORD_CNT        4
typedef union
{
    UCHAR bpdw[ PDW_WORD_CNT ][ PDW_WORD_LEN ];
    UINT wpdw[ PDW_WORD_CNT ];
    struct
    {
        UCHAR direction_h : 2;  /* Phase 1 */
        UCHAR stat : 4;
        UCHAR phase1 : 2;
        UCHAR direction_l : 8;
        UCHAR frequency_h : 5;
        UCHAR band : 2;
        UCHAR dv : 1;

        UCHAR frequency_l : 8;  /* Phase 2 */
        UCHAR pulse_width_h : 3;
        UCHAR pq : 1;
        UCHAR fil1 : 2;
        UCHAR phase2 : 2;
        UCHAR pulse_width_l : 8;
        UCHAR toa_4 : 8;

        UCHAR amplitude : 8;  /* Phase 3 */
        UCHAR fil2 : 6;
        UCHAR phase3 : 2;
        UCHAR toa_3 : 8;
        UCHAR toa_2 : 8;
        UCHAR toa_1 : 8;

        UCHAR chlp : 1; /* Phase 4 */
        UCHAR fil3 : 5;
        UCHAR phase4 : 2;
        UCHAR channel : 8;
        UCHAR pmop : 8;
        UCHAR freq_diff : 8;
    } item ;
} TNEW_PDW;

#endif


#ifdef _ELINT_

#define LENGTH_OF_TASK_ID			(19+1)		//과제ID 문자열 길이 (TBD)

#define _MAX_PDW					(4096)

#ifndef _PDW_STRUCT
#define _PDW_STRUCT
typedef struct {
    long long int llTOA;

    int iFreq;
    int iPulseType;
    int iPA;
    int iPW;
    int iPFTag;
    int iAOA;

    float fPh1;
    float fPh2;
    float fPh3;
    float fPh4;

} _PDW;
#endif

#ifndef ENUM_BANDWIDTH_ENUM
#define ENUM_BANDWIDTH_ENUM
typedef enum {
    en5MHZ_BW=0,
    en50MHZ_BW,

} ENUM_BANDWIDTH ;
#endif

#ifndef _STR_PDWDATA
#define _STR_PDWDATA
typedef struct {
    char	aucTaskID[LENGTH_OF_TASK_ID];
    unsigned int iIsStorePDW;
    int iCollectorID;
    ENUM_BANDWIDTH enBandWidth;

    UINT count;
    _PDW stPDW[_MAX_PDW];

} STR_PDWDATA ;


#endif

#define PDW_NORMAL          (1)
#define PDW_CW              (0)

#define PDW_DV							(1)
#else

//PDW 상태 별 정의 값
#define PDW_NORMAL          (1)
#define PDW_CW              (2)
#define PDW_FMOP						(5)
#define PDW_CW_FMOP					(6)
#define PDW_SHORTP          (7)
#define PDW_ALL							(8)

#ifndef _WIN32
typedef union {
    unsigned int wpdw[4];
    unsigned char bpdw[ 4 ][ 4 ];

    struct pdw_phase {
        // Phase 1
        unsigned toa				 : 32; 	// [0 ~ 4,294,967,295] Res. 20ns (0 ~ 85,899,345.900 us)

        // Phase 2
        unsigned freq				 : 14; 	// [0 ~ 8,191] Res. 1.25 MHz
        unsigned fdiff			 : 3;		// 주파수 최대 변이값 (<- Reserved)
        unsigned blank_tag	 : 1;		// Blanking Tag
        unsigned pw					 : 14; 	// [0 ~ 16,383] Res. 20ns (0 ~ 327.660 us)

        // Phase 3
        unsigned amplitude	 : 8;  	// [0 ~ 255] Res. 0.3125 dBm (-74.6875 ~ + 5 dBm)
        unsigned filter_tag	 : 8;  	// 전처리필터 번호 (<- Reserved)
        unsigned aoa				 : 9;  	// [0 ~ 511] Res. 0.703125 도 (0 ~ 359.297 도)
        unsigned dv					 : 1;  	// [Valid | Invalid ]
        unsigned max_channel : 2;		// Ch1(0x0), Ch2(0x1), Ch3(0x2), Ch4(0x3)
        unsigned stat			   : 4;  	// PMOP(0x8), FMOP(0x4), CW(0x2), Pulse(0x1), Short Pulse(0xF)

        // Phase 4 for dummy
        unsigned flag        : 28;	// 수집 완료 플레그
        unsigned band        : 4;

    } item ;

} _PDW;

#else
typedef union {
    unsigned int word[4];
    unsigned char byte[ 4 ][ 4 ];

    struct pdw_phase {
        // Phase 1
        unsigned toa				 : 32; 	// [0 ~ 4,294,967,295] Res. 20ns (0 ~ 85,899,345.900 us)

        // Phase 2
        unsigned freq				 : 14; 	// [0 ~ 8,191] Res. 1.25 MHz
        unsigned fdiff			 : 3;		// 주파수 최대 변이값 (<- Reserved)
        unsigned blank_tag	 : 1;		// Blanking Tag
        unsigned pw					 : 14; 	// [0 ~ 16,383] Res. 20ns (0 ~ 327.660 us)

        // Phase 3
        unsigned amplitude	 : 8;  	// [0 ~ 255] Res. 0.3125 dBm (-74.6875 ~ + 5 dBm)
        unsigned filter_tag	 : 8;  	// 전처리필터 번호 (<- Reserved)
        unsigned aoa				 : 9;  	// [0 ~ 511] Res. 0.703125 도 (0 ~ 359.297 도)
        unsigned dv					 : 1;  	// [Valid | Invalid ]
        unsigned max_channel : 2;		// Ch1(0x0), Ch2(0x1), Ch3(0x2), Ch4(0x3)
        unsigned stat			   : 4;  	// PMOP(0x8), FMOP(0x4), CW(0x2), Pulse(0x1), Short Pulse(0xF)


        // Phase 4 for dummy
        unsigned flag        : 28;	// 수집 완료 플레그
        unsigned band        : 4;

    } item ;

} _PDW;
#endif


// PDW의 Phase 개수
#define PDW_WORD_LEN        4
#define PDW_WORD_CNT        4
#define SizeOfPDW           16
#define ByteOfPhase         4
#define SizeOfPSEUDO_PDW    ByteOfPhase

#endif



#endif  // #ifndef _PDW_H_

