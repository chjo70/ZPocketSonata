#pragma once

#include <stdio.h>
#include <fcntl.h>


#include "../../../Anal/SigAnal/_Macro.h"
#include "../../../Anal/SigAnal/_Struct.h"

#include "../../../Anal/MIDAS/RawFile.h"

#include "../../../Anal/MIDAS/PDWIQ.h"

#ifdef _FFTW_
#include "../../../../MSC/DeltaGraph/FFTW/fftw3.h"

#endif

#include "../../../Anal/MIDAS/Midas.h"
#include "../../../Include/struct.h"
#include "../../EmitterMerge/IsNumber.h"

#include "../../../Utils/clog.h"


// RAW 데이터 개수 정의 : 왜 필요하지 ?
#define			PDW_ITEMS						(1024*128)			// 9437164
#define			IQ_ITEMS						(1024*128)

#define			MAX_RAWDATA_SIZE				max( (sizeof(struct SRxPDWHeader) + sizeof(struct SRxPDWDataRGroup)*PDW_ITEMS), sizeof(TNEW_IQ)*IQ_ITEMS )	// 2,432,052

#if HEADER_CONTROL_BLOCK_SIZE < 100
#define			MAX_HEADER_SIZE					100
#else
#define			MAX_HEADER_SIZE					HEADER_CONTROL_BLOCK_SIZE
#endif

#define	RAD2DEG			(57.2957795130)


enum ENUM_SUB_GRAPH {
	enUnselectedSubGraph = -1,

	enSubMenu_1 = 1,
	enSubMenu_2,
	enSubMenu_3,
	enSubMenu_4,
	enSubMenu_5,
	enSubMenu_6,

}  ;

// #ifndef _ENUM_DataType
// #define _ENUM_DataType
// typedef enum {
// 	en_UnknownData = 0,
//
// 	en_PDW_DATA,
// 	en_IQ_DATA,
// 	en_IF_DATA,
//
// } ENUM_DataType;
// #endif


enum ENUM_CONVERT_OPTION {
    enUnitToPDW,        // 장비 포멧을 PDW 구조체로 변경 (PDW 저장장치에 따라 PDW 불러오기용)

    enPDWToPDW,         // PDW 구조체를 PDW 구조체로 변경 (저장된 PDW 파일을 불러오기용)
	enCSVToPDW,         // CSV로 저장된 를 PDW 구조체(실제 값)로 변경

    enPDWToReal,        // PDW 구조체를 실제값으로 변경 (그래프 전시용)

    enUnitToReal        // 장비 포멧을 실제값으로 변경 (그래프 전시용)

} ;


#define MAX_SONATA_DATA		(10000)
// typedef union {
// 	TNEW_PDW stPDWData[MAX_SONATA_DATA];
// 	TNEW_IQ stIQData[MAX_SONATA_DATA];
//
// 	DMAPDW stZPDWData[MAX_SONATA_DATA];
//
// } UNI_SONATA_DATA;
//
// struct STR_SONATA_DATA {
// 	UINT uiItem;
//
// 	ENUM_UnitID m_enUnitID;
// 	ENUM_BoardID m_enBoardID;
// 	ENUM_DataType enDataType;
//
// 	UNI_SONATA_DATA unRawData;
//
// 	UINT uiNo;
//
// } ;


struct STR_RAWDATA {
	UINT uiByte;
	void *pDataBuffer;

	ENUM_DataType enDataType;
	ENUM_UnitType enUnitType;

    char szFileName[_MAX_PATH];

} ;

//typedef unsigned long long int _TOA;

struct STR_PDWREALDATA {
	unsigned int uiDataItems;

    _TOA *pullTOA;

	float *pfAOA;			// [degree]
	float *pfFreq;			// [KHz]
    float *pfPA;
	float *pfPW;			// [ns]

    double *pdTOA;
    float *pfDTOA;

	char *pcType;			// [신호형태]
	char *pcDV;				// [DV]

    unsigned int *puiIndex;

	STR_PDWREALDATA() : uiDataItems(0), pullTOA(NULL), pfAOA(NULL), pfFreq(NULL), pfPA(NULL), pfPW(NULL), pdTOA(NULL), pfDTOA(NULL), pcType(NULL), pcDV(NULL), puiIndex(NULL) {

	}


    void SetTotalPDW( unsigned int i_uiDataItems ) {
        uiDataItems = i_uiDataItems;

    } ;

} ;

struct STR_IQ_DATA {
	int iDataItems;

	float *pfI;
	float *pfQ;
	float *pfPA;
	float *pfIP;
	float *pfFFT;

} ;

struct STR_FILTER_SETUP {
	unsigned long long int ullToaMin;
	unsigned long long int ullToaMax;
	unsigned long long int ullDtoaMin;
	unsigned long long int ullDtoaMax;
	unsigned int uiAoaMin;
	unsigned int uiAoaMax;
	unsigned int uiFrqMin;
	unsigned int uiFrqMax;
	unsigned int uiPAMin;
	unsigned int uiPAMax;
	unsigned int uiPWMin;
	unsigned int uiPWMax;

	ENUM_SUB_GRAPH enSubGraph;

} ;

struct STR_ZOOM_INFO {
	double dZoomMinX;
	double dZoomMaxX;
	double dZoomMinY;
	double dZoomMaxY;

	ENUM_SUB_GRAPH enSubGraph;

} ;


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
#define _COMMON_FUNCTIONS_		\
    void Init( char *pRawData, STR_FILTER_SETUP *pstFilterSetup=NULL ); \
	void Alloc( unsigned int uiItems=0 );	\
	void Free();	\
    void ConvertArrayData( STR_PDWDATA *pPDWData, bool bSwap=true, STR_FILTER_SETUP *pFilterSetup=NULL );	\
	void ConvertArrayForELINT() { }	\
	void *GetData();	\
    void *GetRealData();	\
	void *GetHeader() { return NULL; }	\
	int GetHeaderSize();	\
    unsigned int GetOneDataSize();	\
	unsigned int GetDataItems( unsigned long long ullFileSize=0 );    \
    void SetHeaderData( void *pData ) { \
        if( m_iHeaderSize != -1 ) { \
            memcpy( & m_stHeader, pData, (size_t) m_iHeaderSize ); \
            m_stHeader.CheckColTime(); \
        } \
    }


class CData
{
public:
    char *m_pRawHeaderBuffer;           // 헤더 데이터 저장소
    char *m_pRawDataBuffer;             // 실제 데이터 저장소

    size_t m_szFileSize;

    int m_iHeaderSize;                  // 헤더 크기
    unsigned int m_uiOneDataSize;        // 한개 PDW 데이터 크기
    unsigned long long  m_ullFileSize;  // 파일 크기
    UINT m_uiTotalDataItems;            // 전체 PDW 개수

    STR_PDWDATA m_PDWData;
	STR_PDWREALDATA m_PDWRealData;             // PDW 데이터 개수 와 실제 PDW 항목별 데이터 값

    ENUM_DataType m_enDataType;
    ENUM_UnitType m_enUnitType;

#ifdef _GRAPH_
    UINT m_uiWindowNumber;
#endif

    STR_FILTER_SETUP m_strFilterSetup;

public:
    CData();
    virtual ~CData();

    void Alloc( unsigned int uiItems=0 );
    void Free();

    void AllocData( int iItems );
    void FreeData();

    void AllocRealData( int iItems );
    void FreeRealData();

    void ClearFilterSetup();
    void swapByteOrder(unsigned int& ui);
    void swapByteOrder(unsigned long long& ull);
    void AllSwapData32( void *pData, int iLength );
    void ExecuteFFT( int iDataItems, STR_IQ_DATA *pIQData );

    void UpdateMacroSysVar();

    void ConvertPDWData( STR_FILTER_SETUP *pFilterSetup=NULL, bool bSwap=true, ENUM_CONVERT_OPTION enOption=enUnitToPDW );

    inline ENUM_UnitType GetUnitType() { return m_enUnitType; }

#ifdef _GRAPH_
    inline void IncWindowNumber() { ++m_uiWindowNumber; }
    inline void DecWindowNumber() { --m_uiWindowNumber; }
    inline unsigned int GetWindowNumber() { return m_uiWindowNumber; }
#endif

    virtual void ConvertArrayData( STR_PDWDATA *pPDWData, bool bSwap, STR_FILTER_SETUP *pFilterSetup=NULL ) = 0;
    virtual void MakeHeaderData( STR_PDWDATA *pPDWData ) = 0;
    virtual void MakePDWDataByUnitToPDW( STR_PDWDATA *pPDWData ) = 0;
    virtual void MakePDWDataToReal( STR_PDWREALDATA *pPDWRealData ) = 0;
	virtual void MakeCSVDataToPDW() = 0;
    virtual void *GetData() = 0;
    virtual void *GetRealData() = 0;
    virtual void *GetHeader() = 0;
    virtual void Init( char *pRawData, STR_FILTER_SETUP *pstFilterSetup=NULL );

    virtual int GetHeaderSize() = 0;
    virtual int GetBandWidth() = 0;
    virtual unsigned int GetOneDataSize() = 0;
    virtual unsigned int GetDataItems( unsigned long long ullFileSize=0 ) = 0;
    virtual void SetHeaderData( void *pData ) = 0;
};


////////////////////////////////////////////////////////////////////////////////////////////////////
// 소나타 PDW 데이터

// namespace SONATA {
// 	const unsigned int uiPDW_CW=4;
// 	const unsigned int uiPDW_NORMAL=0;
// 	const unsigned int uiPDW_CHIRPUP=2;
// 	const unsigned int uiPDW_CHIRPDN=3;
// 	const unsigned int uiPDW_PMOP=1;
// 	const unsigned int uiPDW_DV=1;
//
//     const float fAoaRes=(360.0/1024.);
//     const float fToaRes=(20);
//     const float fPWRes=(50);
//     const float fPARes=(80./256.);
//     const float fPAOffset=(-70.);
// }

//////////////////////////////////////////////////////////////////////////
// SONATA 체계 RSA PDW 포멧
// namespace PDW {
//     #define PDW_PA_INIT		    (-89.0)
//
// 	#define ONE_SEC				(20000000)
// 	#define ONE_MICROSEC		(20)
//
// 	#define PW_RES				(50)
//
// 	#define	DOA_RES				(0.351562)
//
// 	#define	AMP_RES				(0.351562)
//
// 	struct FREQ_RESOL {
// 		UINT uiMin;
// 		UINT uiMax;
// 		int iOffset;
// 		float fRes;			// 각 구간에 따른 resolution
// 	} ;
//
// 	static FREQ_RESOL stFreqRes[ 3 ] = { {    0,  2560, 0, 0.625 },   /* LOW  FREQUENCY */
// 										 { 1280,  6400, 1260, 1.25  },   /* MID  FREQUENCY */
// 										 { 5866, 18740, 5866, 1.5   } } ;
//
// }
//
// class CPDW : public CData
// {
// private:
// 	//STR_PDW_DATA m_PDWData;
//
// public:
// 	CPDW(STR_RAWDATA *pRawData);
// 	virtual ~CPDW();
//
// 	void Alloc( unsigned int uiItems=0 );
// 	void Free();
// 	void ReadDataHeader() {  }
//     void ConvertPDWData( STR_PDWDATA *pPDWData, STR_FILTER_SETUP *pFilterSetup=NULL, bool bSwap=true, ENUM_CONVERT_OPTION enOption=enUnitToPDW );
//
// 	void *GetData();
//     void *GetRealData();
//
//     unsigned int GetDataItems( unsigned long long ullFileSize );
//
// 	void *GetHeader() { return NULL; }
//
// 	inline unsigned int GetOffsetSize() { return 0; }
// 	inline int GetHeaderSize() { return 0; }
//     inline unsigned int GetOneDataSize() { return sizeof(struct TNEW_PDW); }
//     inline void SetHeaderData( void *pData ) { return; }
//
// public:
//
//     /**
//      * @brief     DecodeTOAus
//      * @param     unsigned int uiTOA
//      * @return    float
//      * @exception
//      * @author    조철희 (churlhee.jo@lignex1.com)
//      * @version   0.0.1
//      * @date      2022-02-09, 17:02
//      * @warning
//      */
//     static double DecodeTOAus( unsigned int uiTOA  )
//     {
//         return (double) uiTOA / (double) ONE_MICROSEC;
//     } ;
//
// 	/**
// 	 * @brief     DecodeRealFREQMHz
// 	 * @param     int iBand
// 	 * @param     unsigned int uiFreq
// 	 * @return    float
// 	 * @exception
// 	 * @author    조철희 (churlhee.jo@lignex1.com)
// 	 * @version   0.0.1
// 	 * @date      2022-02-09, 17:02
// 	 * @warning
// 	 */
// 	static float DecodeRealFREQMHz( int iBand, unsigned int uiFreq )
// 	{
// 		float fVal=0.0;
//
// 		if( iBand >= 0 && iBand <= 2 ) {
// 			fVal = FMUL( PDW::stFreqRes[iBand].fRes, uiFreq ) + PDW::stFreqRes[iBand].iOffset;
// 		}
//
// 		return fVal;
// 	}
//
// 	/**
// 	 * @brief     DecodePW
// 	 * @param     unsigned int uiPW
// 	 * @return    float
// 	 * @exception
// 	 * @author    조철희 (churlhee.jo@lignex1.com)
// 	 * @version   0.0.1
// 	 * @date      2022-02-09, 17:02
// 	 * @warning
// 	 */
// 	static float DecodePW( unsigned int uiPW )
// 	{
// 		return (float) ( uiPW ) * (float) PW_RES;		/* [ns] */
// 	} ;
//
// 	/**
// 	 * @brief     DecodeFREQMHz
// 	 * @param     int iFreq
// 	 * @return    float
// 	 * @exception
// 	 * @author    조철희 (churlhee.jo@lignex1.com)
// 	 * @version   0.0.1
// 	 * @date      2022-02-09, 17:03
// 	 * @warning
// 	 */
// 	static float DecodeFREQMHz( int iFreq )
// 	{
// 		return 0.0;
// 	} ;
//
// 	/**
// 	 * @brief     DecodeDOA
// 	 * @param     unsigned int uiDOA
// 	 * @return    float
// 	 * @exception
// 	 * @author    조철희 (churlhee.jo@lignex1.com)
// 	 * @version   0.0.1
// 	 * @date      2022-02-09, 17:03
// 	 * @warning
// 	 */
// 	static float DecodeDOA( unsigned int uiDOA )
// 	{
// 		return (float) DOA_RES * (float) uiDOA;
// 	} ;
//
// 	/**
// 	 * @brief     DecodePA
// 	 * @param     unsigned int uiPA
// 	 * @return    float
// 	 * @exception
// 	 * @author    조철희 (churlhee.jo@lignex1.com)
// 	 * @version   0.0.1
// 	 * @date      2022-02-09, 17:03
// 	 * @warning
// 	 */
// 	static float DecodePA( unsigned int uiPA )
// 	{
// 		return (float) ( ( (float) uiPA * (float) AMP_RES ) - (float) 110. );
// 	} ;
//
//     /**
//      * @brief DecodeDOA
//      * @param iDOA
//      * @return
//      */
//     static unsigned int EncodeDOA(float fDOA )
//     {
//         fDOA = ( float ) fmod( ( double ) fDOA + ( double ) (360 * 10), (double) 360.0 );
//         return (unsigned int) ( (float) fDOA / SONATA::fAoaRes + 0.5 );
//     } ;
//
// };



////////////////////////////////////////////////////////////////////////////////////////////////////
// SONATA + 수퍼헷 PDW 데이터


namespace SONATA {
	const unsigned int uiPDW_CW = 4;
	const unsigned int uiPDW_NORMAL = 0;
	const unsigned int uiPDW_CHIRPUP = 2;
	const unsigned int uiPDW_CHIRPDN = 3;
	const unsigned int uiPDW_PMOP = 1;
	const unsigned int uiPDW_DV = 1;

	const float _fDOARes = (360.0 / 1024.);
	const double _dTOARes = ( 50. / 1000000000. );
	const double _dPWRes = (50. / 1000000000.);
	const float _fPARes = (float) (80. / 256.);
	const int _iPAOffset = -70;
	const double dPAOffset = (-70.);

// #ifndef _FREQ_RESOL_
// #define _FREQ_RESOL_
// 	struct FREQ_RESOL {
// 		// frequency band code를 위한 구조체
// 		unsigned int uiMin;       // min frequency
// 		unsigned int uiMax;       // max frequency
// 		int iOffset;       // max frequency
// 		float fRes;			// 각 구간에 따른 resolution
// 	};
// #endif

	const FREQ_RESOL _gFreqRes[3] =
	{
		{    0,  2560, 0, 0.625 },   /* LOW  FREQUENCY */
		{ 1280,  6400, 1260, 1.25  },   /* MID  FREQUENCY */
		{ 5866, 18740, 5866, 1.5   }
	};
}

#if defined(_GRAPH_) || defined(_SONATA_)
class CSPDW : public CData
{
private:
	STR_SONATA_HEADER m_stHeader;

	//static int m_iBoardID;

public:
	CSPDW(char *pRawData, STR_FILTER_SETUP *pstFilterSetup, size_t szFileSize );
	virtual ~CSPDW();

	_COMMON_FUNCTIONS_;

	void MakeHeaderData(STR_PDWDATA *pPDWData);
	void MakePDWData(STR_PDWDATA *pPDWData, ENUM_CONVERT_OPTION enOption) { }
	void MakePDWDataByUnitToPDW(STR_PDWDATA *pPDWData) { }
	void MakePDWDataToReal(STR_PDWREALDATA *pPDWData);
	void MakeCSVDataToPDW() { }

	inline int GetBandWidth() { return (int)0; }
	inline unsigned int GetOffsetSize() { return 0; }
	inline void UpdateHeaderSize() { GetHeaderSize(); }


	/**
	 * @brief     DecodeTOA
	 * @param     UINT uiTOA
	 * @return    double
	 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   1.0.0
	 * @date      2023-01-08 11:39:54
	 * @warning
	 */
	static double DecodeTOA( UINT uiTOA )
	{
		return (double)( (double) uiTOA * (double) SONATA::_dTOARes);
	};

	/**
	 * @brief     DecodePW
	 * @param     UINT uiPW
	 * @return    double
	 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   1.0.0
	 * @date      2023-01-08 11:39:57
	 * @warning
	 */
	static double DecodePW(UINT uiPW)
	{
		return (double)((double)uiPW * (double)SONATA::_dTOARes);
	};

	/**
	 * @brief     DecodeDOA
	 * @param     unsigned int uiDOA
	 * @return    float
	 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   1.0.0
	 * @date      2023-01-08 11:40:01
	 * @warning
	 */
	static float DecodeDOA( unsigned int uiDOA )
	{
		float fDOA;
		fDOA = (float) SONATA::_fDOARes * (float)( uiDOA % 0x100 );
		return fDOA;
	};

	/**
	 * @brief     DecodePA
	 * @param     unsigned int uiPA
	 * @return    float
	 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   1.0.0
	 * @date      2023-01-08 11:40:03
	 * @warning
	 */
	static float DecodePA(unsigned int uiPA)
	{
		float fPA;
		fPA = (float)SONATA::_fPARes * (float)(uiPA) + SONATA::_iPAOffset;
		return fPA;
	};

	/**
	 * @brief     DecodeFREQ
	 * @param     unsigned int uiFreq
	 * @param     int iBand
	 * @return    float
	 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   1.0.0
	 * @date      2023-01-08 11:40:05
	 * @warning
	 */
	static float DecodeFREQ(unsigned int uiFreq, int iBand )
	{
		float fFreq;
		fFreq = (float) SONATA::_gFreqRes[iBand].fRes * (float)(uiFreq) +SONATA::_gFreqRes[iBand].iOffset;
		fFreq *= 1000000.;
		return fFreq;
	};

};
#endif

#if defined(_GRAPH_) || defined(_ELINT_)
namespace ELINT {
	const unsigned int uiPDW_CW=0;
	const unsigned int uiPDW_NORMAL=1;
	const unsigned int uiPDW_DV=1;

    const float _toaRes[ELINT::en50MHZ_BW+1] = { (float) 65.104167, (float) 8.138021 } ;

    const float _fFreqRes=(float) 0.001;
    const float _fDOARes=(float) 0.01;
    const float _fPARes=(float) 0.25;
}

// 인천공항 PDW
class CEPDW : public CData
{
private:
    STR_ELINT_HEADER m_stHeader;

	ELINT::ENUM_BANDWIDTH m_enBandWidth;

public:
	CEPDW(STR_RAWDATA *pRawData, STR_FILTER_SETUP *pstFilterSetup );
	virtual ~CEPDW();

	void Alloc( unsigned int uiItems=0 );
	void Free();
	void ReadDataHeader() {  }
    void ConvertPDWData( STR_PDWDATA *pPDWData, STR_FILTER_SETUP *pFilterSetup=NULL, bool bSwap=true, ENUM_CONVERT_OPTION enOption=enUnitToPDW );
	void *GetData();
    void *GetRealData();
	void *GetHeader() { return (void *) & m_stHeader; }
    unsigned int GetDataItems( unsigned long long ullFileSize );
    int GetHeaderSize();

	inline unsigned int GetOffsetSize() { return sizeof(int)*4; }
    inline unsigned int GetOneDataSize() { return sizeof( _PDW); }

    inline void SetHeaderData( void *pData );



    /**
     * @brief     EncodePulseType
     * @param     int iPulseType
     * @return    unsigned int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-10, 10:53
     * @warning
     */
    static unsigned int EncodePulseType( int iPulseType )
    {
        unsigned int ipluseType= STAT_CW;

        if( iPulseType == 0 ) {
            ipluseType = STAT_NORMAL;
        }
        else {
            // ipluseType = STAT_CW;
        }

        return ipluseType;
    } ;


    /**
     * @brief     DecodeTOAus
     * @param     _TOA uiTOA
     * @param     ENUM_BANDWIDTH enBandWidth
     * @return    double
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-02-09, 17:03
     * @warning
     */
    static double DecodeTOAus( _TOA uiTOA, ELINT::ENUM_BANDWIDTH enBandWidth )
    {
        return (double) ( ( (double) uiTOA * ELINT::_toaRes[enBandWidth] ) / (float) 1000000000. );
    } ;

    /**
     * @brief     EncodeTOAus
     * @param     float fTOA
     * @param     ELINT::ENUM_BANDWIDTH enBandWidth
     * @return    _TOA
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-10, 11:38
     * @warning
     */
    static _TOA EncodeTOAus( float fTOA, ELINT::ENUM_BANDWIDTH enBandWidth )
    {
        return ( unsigned int ) (((fTOA * (float) 1000.) / ELINT::_toaRes[enBandWidth]) + 0.5);
    } ;

	/**
	 * @brief     DecodeRealFREQMHz
	 * @param     unsigned int uiFreq
	 * @return    float
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022-02-09, 17:04
	 * @warning
	 */
	static float DecodeRealFREQMHz( unsigned int uiFreq )
	{
		float fVal;

		fVal = FMUL( uiFreq, ELINT::_fFreqRes );

		return fVal;
	} ;

    /**
     * @brief     EncodeRealFREQMHz
     * @param     float fFreq
     * @return    unsigned int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-10, 11:38
     * @warning
     */
    static unsigned int EncodeRealFREQMHz( float fFreq )
    {
        unsigned int uiFreq;

        uiFreq = UDIV( fFreq, ELINT::_fFreqRes );

        return uiFreq;
    } ;

	/**
	 * @brief     펄스폭을 [초] 단위로 리턴한다.
	 * @param     unsigned int uiPW
	 * @param     ENUM_BANDWIDTH enBandWidth
	 * @return    float
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022-01-29, 15:20
	 * @warning
	 */
	static float DecodePW( unsigned int uiPW, ELINT::ENUM_BANDWIDTH enBandWidth )
	{
		return (float) ( ( (float) uiPW * ELINT::_toaRes[enBandWidth] ) / (float) 1000000000. );
	} ;

    /**
     * @brief     EncodePWns
     * @param     float fPW
     * @param     XBAND::ENUM_BANDWIDTH enBandWidth
     * @return    unsigned int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-10, 11:07
     * @warning
     */
    static unsigned int EncodePWns( float fPW, ELINT::ENUM_BANDWIDTH enBandWidth )
    {
        return ( unsigned int ) (( float ) (fPW / ELINT::_toaRes[enBandWidth]) + 0.5);
    } ;

	/**
	 * @brief     DecodeFREQMHz
	 * @param     int iFreq
	 * @return    float
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022-01-29, 15:20
	 * @warning
	 */
	static float DecodeFREQMHz( int iFreq )
	{
		return 0.0;
	} ;

	/**
	 * @brief     DecodeDOA
	 * @param     unsigned int uiDOA
	 * @return    float
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022-01-29, 15:20
	 * @warning
	 */
	static float DecodeDOA( unsigned int uiDOA )
	{
		float fDOA;
		fDOA = (float) ELINT::_fDOARes * (float) ( uiDOA % 36000 );
		return fDOA;
	} ;

    /**
     * @brief     EncodeDOA
     * @param     float fDOA
     * @return    unsigned int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-10, 11:07
     * @warning
     */
    static unsigned int EncodeDOA( float fDOA ) {
        fDOA = ( float ) fmod( ( double ) fDOA + ( double ) (360 * 10), (double) 360.0 );
        return ( unsigned int ) (( float ) fDOA / ELINT::_fDOARes + 0.5);
    } ;

	/**
	 * @brief     DecodePA
	 * @param     unsigned int uiPA
	 * @return    float
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022-01-29, 15:20
	 * @warning
	 */
	static float DecodePA( unsigned int uiPA )
	{
		return (float) ( ( (float) uiPA * (float) ELINT::_fPARes ) - (float) 110. );
	} ;

    /**
     * @brief     EncodePA
     * @param     float fPA
     * @return    unsigned int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-10, 11:39
     * @warning
     */
    static unsigned int EncodePA( float fPA )
    {
        return ( unsigned int ) ((( float ) (fPA + (float) 110.0) / ( float ) ELINT::_fPARes) + 0.5);
    } ;





};
#endif

#if defined(_GRAPH_) || defined(_XBAND_)
namespace XBAND {
	const float _toaRes[XBAND::en120MHZ_BW +1] = { (float) 65.104167, (float) 8.138021 } ;
	const float _fFreqRes=(float) 0.001;
	const float _fDOARes=(float) 0.01;
	const float _fPARes=(float) 0.25;
}

class CXPDW : public CData
{
private:
	STR_XBAND_HEADER m_stHeader;

    XBAND::ENUM_BANDWIDTH m_enBandWidth;

public:
	CXPDW( char *pRawData, STR_FILTER_SETUP *pstFilterSetup );
	virtual ~CXPDW();

    _COMMON_FUNCTIONS_;

    void MakeHeaderData( STR_PDWDATA *pPDWData );
    void MakePDWData( STR_PDWDATA *pPDWDat, ENUM_CONVERT_OPTION enOption );
    void MakePDWDataByUnitToPDW( STR_PDWDATA *pPDWData );
    void MakePDWDataToReal( STR_PDWREALDATA *pPDWRealData );
	void MakeCSVDataToPDW() { }

    inline int GetBandWidth() { return (int) m_enBandWidth; }

    inline void UpdateHeaderSize() { GetHeaderSize(); }

    /**
     * @brief
     * @param     int iPulseType
     * @return    unsigned int
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022/02/21 23:08:21
     * @warning
     */
    static unsigned int EncodePulseType( int iPulseType )
    {
        unsigned int ipluseType=STAT_CW;

        if( iPulseType == 0 ) {
            ipluseType = STAT_NORMAL;
        }
        else {
            // ipluseType = STAT_CW;
        }

        return ipluseType;
    } ;

    /**
     * @brief     DecodeTOAus
     * @param     _TOA uiTOA
     * @param     ENUM_BANDWIDTH enBandWidth
     * @return    float
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-02-09, 17:03
     * @warning
     */
    static double DecodeTOAus( _TOA tTOA, XBAND::ENUM_BANDWIDTH enBandWidth )
    {
        return (float) ( ( (float) tTOA * XBAND::_toaRes[enBandWidth] ) / (float) 1. );
    } ;

    /**
     * @brief     [s] 단위로 리턴한다.
     * @param     _TOA uiTOA
     * @param     ENUM_BANDWIDTH enBandWidth
     * @return    float
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022/02/22 22:37:47
     * @warning
     */
    static double DecodeTOA( _TOA tTOA, XBAND::ENUM_BANDWIDTH enBandWidth )
    {
        return (double) ( ( (double) tTOA * XBAND::_toaRes[enBandWidth] ) / (double) 1000000000. );
    } ;

	/**
     * @brief
     * @param     _TOA uiTOA
     * @param     ENUM_BANDWIDTH enBandWidth
     * @return    unsigned int
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022/02/17 15:16:39
     * @warning
     */
    static _TOA EncodeTOAus( float fTOA, XBAND::ENUM_BANDWIDTH enBandWidth )
    {
        return (unsigned int) ( ( ( fTOA * (float) 1000. ) / XBAND::_toaRes[enBandWidth] ) + 0.5 );
    } ;

    static _TOA EncodeTOAs( float fTOA, XBAND::ENUM_BANDWIDTH enBandWidth )
    {
        return ( unsigned int ) ( ( ( fTOA * ( float ) 1000000000. ) / XBAND::_toaRes[enBandWidth] ) + 0.5 );
    };

	/**
	 * @brief     DecodeRealFREQMHz
	 * @param     unsigned int uiFreq
	 * @return    float
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022-02-09, 17:04
	 * @warning
	 */
	static float DecodeRealFREQMHz( unsigned int uiFreq )
	{
		float fVal;

		fVal = FMUL( uiFreq, XBAND::_fFreqRes );

		return fVal;
	} ;

	/**
     * @brief
     * @param     float fFreq
     * @return    unsigned int
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022/02/17 15:33:22
     * @warning
     */
    static unsigned int EncodeRealFREQMHz( float fFreq )
    {
        unsigned int uiFreq;

        uiFreq = UDIV( fFreq, XBAND::_fFreqRes );

        return uiFreq;
    } ;

    /**
     * @brief     DecodeFREQ
     * @param     unsigned int uiFreq
     * @return    float
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-02-22, 15:52
     * @warning
     */
    static float DecodeFREQ( unsigned int uiFreq )
    {
        float fFreq;

        fFreq = FMUL( uiFreq, XBAND::_fFreqRes );
        fFreq *= 1000000.;

        return fFreq;
    } ;

    /**
     * @brief
     * @param     unsigned int uiFreq
     * @return    float
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022/02/22 22:36:54
     * @warning
     */
    static float DecodeFREQMHz( unsigned int uiFreq )
    {
        float fFreq;

        fFreq = FMUL( uiFreq, XBAND::_fFreqRes );

        return fFreq;
    } ;

	/**
	 * @brief     DecodePW
	 * @param     unsigned int uiPW
	 * @param     ENUM_BANDWIDTH enBandWidth
	 * @return    float
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022-01-29, 15:20
	 * @warning
	 */
	static float DecodePW( unsigned int uiPW, XBAND::ENUM_BANDWIDTH enBandWidth )
	{
		return (float) ( ( (float) uiPW * XBAND::_toaRes[enBandWidth] ) / (float) 1000000000. );
	} ;

	/**
     * @brief
     * @param     float fPW
     * @param     ENUM_BANDWIDTH enBandWidth
     * @return    unsigned int
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022/02/21 23:20:19
     * @warning
     */
    static unsigned int EncodePWns( float fPW, XBAND::ENUM_BANDWIDTH enBandWidth )
    {
        return (unsigned int) ( (float) ( fPW / XBAND::_toaRes[enBandWidth] ) + 0.5 );
    } ;

	/**
	 * @brief     DecodeFREQMHz
	 * @param     int iFreq
	 * @return    float
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022-01-29, 15:20
	 * @warning
	 */
	static float DecodeFREQMHz( int iFreq )
	{
		return 0.0;
	} ;

	/**
	 * @brief     DecodeDOA
	 * @param     unsigned int uiDOA
	 * @return    float
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022-01-29, 15:20
	 * @warning
	 */
	static float DecodeDOA( unsigned int uiDOA )
	{
		float fDOA;
		fDOA = (float)XBAND::_fDOARes * (float) ( uiDOA % 36000 );
		return fDOA;
	} ;

    /**
     * @brief     EncodeDOA
     * @param     float fDOA
     * @return    unsigned int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-02-22, 15:51
     * @warning
     */
    static unsigned int EncodeDOA(float fDOA )
    {
        fDOA = (float) fmod( (double) fDOA + (double) (360*10), (double) 360.0 );
        return (unsigned int) ( (float) fDOA / XBAND::_fDOARes + 0.5 );
    } ;

	/**
	 * @brief     DecodePA
	 * @param     unsigned int uiPA
	 * @return    float
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022-01-29, 15:20
	 * @warning
	 */
	static float DecodePA( unsigned int uiPA )
	{
		return (float) ( ( (float) uiPA * (float)XBAND::_fPARes ) - (float) 110. );
	} ;

    /**
     * @brief
     * @param     float fPA
     * @return    unsigned int
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022/02/21 23:23:01
     * @warning
     */
    static unsigned int EncodePA( float fPA )
    {
        return (unsigned int) ( ( (float) ( fPA + (float) 110.0 ) / (float)XBAND::_fPARes ) + 0.5 );
    } ;

};
#endif


#if defined(_GRAPH_) || defined(_701_)
namespace _701 {
	const float _toaRes[_701::enWIDE_BW + 1] = { (float) 14.0625, (float) 6.48824 };
	const float _fFreqRes = (float) 0.01;
	const float _fDOARes = (float) 0.1;
	const float _fPARes = (float) 0.25;
}

// 701 PDW
class C7PDW : public CData
{
private:
	bool m_bSwap;

	STR_701_HEADER m_stHeader;

	_701::ENUM_BANDWIDTH m_enBandWidth;

	UNION_HEADER m_uniHeader;				///< PDW 헤더용 구조체 저장소, CSV 때문에 따로 할당

public:
	C7PDW( char *pRawData, STR_FILTER_SETUP *pstFilterSetup, ENUM_DataType enDataType );
	virtual ~C7PDW();

	_COMMON_FUNCTIONS_

	void MakeHeaderData(STR_PDWDATA *pPDWData);
	void MakePDWData(STR_PDWDATA *pPDWData, ENUM_CONVERT_OPTION enOption) { }
	void MakePDWDataByUnitToPDW(STR_PDWDATA *pPDWData) { }
	void MakePDWDataToReal(STR_PDWREALDATA *pPDWData);
	void MakeCSVDataToPDW(void);

	// CSV 를 읽기 위한 함수 추가
	int UpdateRow(SRxPDWDataRGroup *pstRxPDWDataRGroup, char *pData);

	inline int GetBandWidth() { return (int) m_enBandWidth; }
	inline unsigned int GetOffsetSize() { return 0; }
	inline void UpdateHeaderSize() { GetHeaderSize(); }

	/**
	 * @brief
	 * @param     int iPulseType
	 * @return    unsigned int
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022/02/21 23:08:21
	 * @warning
	 */
	static unsigned int EncodePulseType(int iPulseType)
	{
		unsigned int ipluseType;

		if (iPulseType == 0) {
			ipluseType = STAT_NORMAL;
		}
		else {
			ipluseType = STAT_CW;
		}

		return ipluseType;
	};

	/**
	 * @brief     DecodeTOAus
	 * @param     _TOA uiTOA
	 * @param     ENUM_BANDWIDTH enBandWidth
	 * @return    float
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022-02-09, 17:03
	 * @warning
	 */
	static double DecodeTOAus(_TOA tTOA, _701::ENUM_BANDWIDTH enBandWidth)
	{
		return (float)(((float)tTOA * _701::_toaRes[enBandWidth]) / (float) 1.);
	};

	/**
	 * @brief     [s] 단위로 리턴한다.
	 * @param     _TOA uiTOA
	 * @param     ENUM_BANDWIDTH enBandWidth
	 * @return    float
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022/02/22 22:37:47
	 * @warning
	 */
	static double DecodeTOA(_TOA tTOA, _701::ENUM_BANDWIDTH enBandWidth)
	{
		return (double)(((double)tTOA * _701::_toaRes[enBandWidth]) / (double) 1000000000.);
	};

	/**
	 * @brief
	 * @param     _TOA uiTOA
	 * @param     ENUM_BANDWIDTH enBandWidth
	 * @return    unsigned int
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022/02/17 15:16:39
	 * @warning
	 */
	static _TOA EncodeTOAus(float fTOA, _701::ENUM_BANDWIDTH enBandWidth)
	{
		return (unsigned int)(((fTOA * (float) 1000.) / _701::_toaRes[enBandWidth]) + 0.5);
	};

	/**
	 * @brief     EncodeTOAs
	 * @param     float fTOA
	 * @param     _701::ENUM_BANDWIDTH enBandWidth
	 * @return    _TOA
	 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   1.0.0
	 * @date      2023-01-18 18:29:36
	 * @warning
	 */
	static _TOA EncodeTOAs(float fTOA, _701::ENUM_BANDWIDTH enBandWidth)
	{
		return (unsigned int)(((fTOA * (float) 1000000000.) / _701::_toaRes[enBandWidth]) + 0.5);
	};

	/**
	 * @brief     DecodeRealFREQMHz
	 * @param     unsigned int uiFreq
	 * @return    float
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022-02-09, 17:04
	 * @warning
	 */
	static float DecodeRealFREQMHz(unsigned int uiFreq)
	{
		float fVal;

		fVal = FMUL(uiFreq, _701::_fFreqRes);

		return fVal;
	};

	/**
	 * @brief
	 * @param     float fFreq
	 * @return    unsigned int
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022/02/17 15:33:22
	 * @warning
	 */
	static unsigned int EncodeRealFREQMHz(float fFreq)
	{
		unsigned int uiFreq;

		uiFreq = UDIV(fFreq, _701::_fFreqRes);

		return uiFreq;
	};

	/**
	 * @brief     DecodeFREQ
	 * @param     unsigned int uiFreq
	 * @return    float
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022-02-22, 15:52
	 * @warning
	 */
	static float DecodeFREQ(unsigned int uiFreq)
	{
		float fFreq;

		fFreq = FMUL(uiFreq, _701::_fFreqRes);
		fFreq *= 1000000.;

		return fFreq;
	};

	/**
	 * @brief
	 * @param     unsigned int uiFreq
	 * @return    float
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022/02/22 22:36:54
	 * @warning
	 */
	static float DecodeFREQMHz(unsigned int uiFreq)
	{
		float fFreq;

		fFreq = FMUL(uiFreq, _701::_fFreqRes);

		return fFreq;
	};

	/**
	 * @brief     DecodePW
	 * @param     unsigned int uiPW
	 * @param     ENUM_BANDWIDTH enBandWidth
	 * @return    float
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022-01-29, 15:20
	 * @warning
	 */
	static float DecodePW(unsigned int uiPW, _701::ENUM_BANDWIDTH enBandWidth )
	{
		return (float)(((float)uiPW * _701::_toaRes[enBandWidth]) / (float) 1000000000.);
	};

	/**
	 * @brief
	 * @param     float fPW
	 * @param     ENUM_BANDWIDTH enBandWidth
	 * @return    unsigned int
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022/02/21 23:20:19
	 * @warning
	 */
	static unsigned int EncodePWns(float fPW, _701::ENUM_BANDWIDTH enBandWidth)
	{
		return (unsigned int)((float)(fPW / _701::_toaRes[enBandWidth]) + 0.5);
	};

	/**
	 * @brief     EncodePWs
	 * @param     float fPW
	 * @param     _701::ENUM_BANDWIDTH enBandWidth
	 * @return    unsigned int
	 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   1.0.0
	 * @date      2023-01-24 16:02:03
	 * @warning
	 */
	static unsigned int EncodePWs(float fPW, _701::ENUM_BANDWIDTH enBandWidth)
	{
		return (unsigned int)((float)(fPW * 1000000000. / _701::_toaRes[enBandWidth]) + 0.5);
	};

	/**
	 * @brief     DecodeFREQMHz
	 * @param     int iFreq
	 * @return    float
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022-01-29, 15:20
	 * @warning
	 */
	static float DecodeFREQMHz(int iFreq)
	{
		return 0.0;
	};

	/**
	 * @brief     DecodeDOA
	 * @param     unsigned int uiDOA
	 * @return    float
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022-01-29, 15:20
	 * @warning
	 */
	static float DecodeDOA(unsigned int uiDOA)
	{
		float fDOA;
		fDOA = (float)_701::_fDOARes * (float)(uiDOA % 36000);
		return fDOA;
	};

	/**
	 * @brief     EncodeDOA
	 * @param     float fDOA
	 * @return    unsigned int
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022-02-22, 15:51
	 * @warning
	 */
	static unsigned int EncodeDOA(float fDOA)
	{
		fDOA = (float)fmod((double)fDOA + (double)(360 * 10), (double) 360.0);
		return (unsigned int)((float)fDOA / _701::_fDOARes + 0.5);
	};

	/**
	 * @brief     DecodePA
	 * @param     unsigned int uiPA
	 * @return    float
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022-01-29, 15:20
	 * @warning
	 */
	static float DecodePA(unsigned int uiPA)
	{
		//return (float)(((float)uiPA * (float)_701::_fPARes) - (float) 110.);
		return -(float)(((float)uiPA * (float)_701::_fPARes) );
	};

	/**
	 * @brief
	 * @param     float fPA
	 * @return    unsigned int
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022/02/21 23:23:01
	 * @warning
	 */
	static unsigned int EncodePA(float fPA)
	{
		return (unsigned int)(( (float)-fPA  / (float)_701::_fPARes) + 0.5);
	};


};
#endif

///////////////////////////////////////////////////////////////////////////////////
// KFX PDW
#if defined(_GRAPH_) || defined(_KFX_)
class CKFXPDW : public CData
{
private:
	//STR_PDW_DATA m_PDWData;

public:
	CKFXPDW(STR_RAWDATA *pRawData, STR_FILTER_SETUP *pstFilterSetup );
	virtual ~CKFXPDW();

	void Alloc( unsigned int uiItems=0 );
	void Free();
	void ReadDataHeader() {  }
    void ConvertPDWData( STR_PDWDATA *pPDWData, STR_FILTER_SETUP *pFilterSetup=NULL, bool bSwap=true, ENUM_CONVERT_OPTION enOption=enUnitToPDW );
	void *GetData();
    void *GetRealData();
	void *GetHeader() { return NULL; }

	inline unsigned int GetOffsetSize() { return 0; }
	inline int GetHeaderSize() { return 0; }
    inline unsigned int GetOneDataSize() { return 0; }
	inline unsigned int GetDataItems( unsigned long long ullFileSize ) { return 0; }

    inline void SetHeaderData( void *pData ) { return; }

public:
	float DecodeDOA(int iDOA  )
	{
		float fDOA;

		fDOA = (float) ( (float) iDOA * (float) 360. ) / (float) 512;
		return fDOA;	/* [degree] */
	} ;

	float DecodePA(int iPA )
	{
		float fPA;

		fPA = (float) ( (float) iPA * (float) 0.25 ) - (float) 110.0;
		return fPA;		/* [dBm] */
	} ;

	float DecodeFREQ( int iFreq )
	{
		float fFREQ;

		fFREQ = (float) ( (float) iFreq * (float) 13.1072 ) / (float) 1000.0;
		return fFREQ;	/* [MHz] */
	} ;

	float DecodePW( int iPW )
	{
		float fPW;

		fPW = (float) ( (float) iPW * (float) 6.48824007 / (float) 1.0 );
		return fPW;		/* [ns] */
	} ;

	float DecodeTOA( _TOA iTOA  )
	{
		float fTOA;

		fTOA = (float) ( (float) iTOA * (float) 6.48824007 / (float) 1000.0 );
		return fTOA;	/* [ns] */
	} ;

};
#endif

///////////////////////////////////////////////////////////////////////////////////
// 함정용 전자전장비
// CPOCKETSONATAPDW PDW
namespace POCKETSONATA {
    #define PDW_DOA_MAX         ( 3599 )

    #define PH_WIDTH_FREQ		128000
    #define L_PH_MIN_FREQ		64000
    #define H_PH_MIN_FREQ		192000  // [kHz]

    #define PDW_PA_DB_MIN		(float) (-89)
    #define PDW_PA_DB_MAX		(float) (7.329466)          // 20 * log10(0xffff) - 89.0
    #define PDW_PA_RANGE        (float) ( PDW_PA_DB_MAX - PDW_PA_DB_MIN )

    #define PDW_PA_MAX          ( 1 << 16 )

    #define PDW_PW_MAX          (0xFFFFFF)
    #define PDW_PW_MIN          (0)
    #define PDW_PW_NS_MIN       (float) ( 0. )
    #define PDW_PW_NS_MAX       (float) ( 108854.6 ) // [us]


    #define FMOP_BW             (float) (3.79)      // MHz

    const unsigned int uiPDW_CW=1;
    const unsigned int uiPDW_NORMAL=0;

	const float m_fCenterFreq[enMAXPRC][2] = { { 0., 0. }, \
											   { 0., 1072000. }, \
											   { 3072000., 5072000. }, \
											   { 7072000., 9072000. }, \
											   { 11072000., 13072000. }, \
											   { 15072000., 17072000. } };


    const float _toaRes = (float) 6.48824007;
    const float _fFreqRes = ( float ) 1000.;
    const float _fDOARes = (float) ( 0.1 );		// = 0.087890625
    //const float _fPARes = (float) ( ( float ) PDW_PA_RANGE / (float) ( 64 * 1024 - 1 ) );		// = ?

}

class CPOCKETSONATAPDW : public CData
{
private:
	STR_POCKETSONATA_HEADER m_stHeader;

public:
    CPOCKETSONATAPDW( char *pRawData, STR_FILTER_SETUP *pstFilterSetup, int iBoardID );
    virtual ~CPOCKETSONATAPDW();

    _COMMON_FUNCTIONS_;

    void MakeHeaderData( STR_PDWDATA *pPDWData );
    void MakePDWData( STR_PDWDATA *pPDWData, ENUM_CONVERT_OPTION enOption );
    void MakePDWDataByUnitToPDW( STR_PDWDATA *pPDWData );
    void MakePDWDataToReal( STR_PDWREALDATA *pPDWData );
	void MakeCSVDataToPDW() { }

    inline int GetBandWidth() { return ( int ) 0; }
	inline unsigned int GetOffsetSize() { return 0; }
    inline void UpdateHeaderSize() { CPOCKETSONATAPDW::GetHeaderSize(); }

public:
    /**
     * @brief     EncodePulseType
     * @param     int iPulseType
     * @return    unsigned int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-10, 10:52
     * @warning
     */
    static unsigned int EncodePulseType( int iPulseType )
    {
        unsigned int ipluseType=STAT_CW;

        if( iPulseType == 0 ) {
            ipluseType = STAT_NORMAL;
        }
        else {
            //ipluseType = STAT_CW;
        }

        return ipluseType;
    } ;

    /**
     * @brief     방향정보로 단위로 [도] 변환한다.
     * @param     int iDOA
     * @return    float
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2022-07-04 13:25:57
     * @warning
     */
    static float DecodeDOA(int iDOA )
    {
        float fDOA;

        fDOA = (float) ( (float) iDOA * POCKETSONATA::_fDOARes );
        return fDOA;	/* [degree] */
    } ;

    /**
     * @brief EncodeDOA
     * @param fDOA
     * @return
     */
    static unsigned int EncodeDOA( float fDOA )
    {
        unsigned int uiDOA;

        fDOA = ( float ) fmod( ( double ) fDOA + ( double ) (3600.), (double) 360.0 );
        uiDOA = (unsigned int) ( ( fDOA / POCKETSONATA::_fDOARes ) + 0.5 );
        return uiDOA;
    } ;

    /**
     * @brief     EncodeDOAFloor
     * @param     float fDOA
     * @return    unsigned int
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-12-02 11:50:12
     * @warning
     */
    static unsigned int EncodeDOAFloor( float fDOA )
    {
        unsigned int uiDOA;

        fDOA = ( float ) fmod( ( double ) fDOA + ( double ) ( 360 * 10 ), ( double ) 360.0 );
        uiDOA = ( unsigned int ) ( ( fDOA / POCKETSONATA::_fDOARes ) );
        return uiDOA;
    };

    /**
     * @brief     EncodeDOACeiling
     * @param     float fDOA
     * @return    unsigned int
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-12-02 14:11:48
     * @warning
     */
    static unsigned int DecodeDOACeiling( float fDOA )
    {
        unsigned int uiDOA;

        fDOA = ( float ) fmod( ( double ) fDOA + ( double ) ( 360 * 10 ), ( double ) 360.0 );
        uiDOA = ( unsigned int ) ( ( fDOA / POCKETSONATA::_fDOARes ) + 0.5 );
        return uiDOA;
    };

    /**
     * @brief     DecodeRealFREQMHz
     * @param     int iFreq
     * @param     int iCh
     * @param     int iBoardID
     * @return    float
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2021-07-24, 10:47
     * @warning
     */
    static float DecodeRealFREQMHz( int iFreq, int iCh, int iBoardID, int iNo )
    {
        float fFREQ=(float) 0.;

        if( iBoardID == 1 && iNo == 0 ) {
        }
        else {
            if( iCh < 8 ) {
                if((unsigned int) iFreq & ( unsigned int ) 0x8000 ) {
                    fFREQ = POCKETSONATA::m_fCenterFreq[iBoardID][iNo] + ( float ) (PH_WIDTH_FREQ * iCh) - ( float ) (( float ) (0x10000 - iFreq) * POCKETSONATA::_fFreqRes);
                }
                else {
                    fFREQ = POCKETSONATA::m_fCenterFreq[iBoardID][iNo] + ( float ) (PH_WIDTH_FREQ * iCh) + ( float ) (( float ) iFreq * POCKETSONATA::_fFreqRes);      // 1.953125*32767 = 64MHz
                }
            }
            else {
                iCh = 16 - iCh;
                if((unsigned int) iFreq & (unsigned int) 0x8000 ) {
                    fFREQ = ((POCKETSONATA::m_fCenterFreq[iBoardID][iNo]) - (PH_WIDTH_FREQ * iCh) - (( float ) (0x10000 - iFreq) * POCKETSONATA::_fFreqRes));
                }
                else {
                    fFREQ = ((POCKETSONATA::m_fCenterFreq[iBoardID][iNo]) - (PH_WIDTH_FREQ * iCh) + (( float ) iFreq * POCKETSONATA::_fFreqRes));
                }
            }
        }

        return fFREQ / (float) 1000.;	/* [MHz] */
    } ;

    /**
     * @brief     DecodeFREQ
     * @param     int iFreq
     * @return    float
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-10, 16:05
     * @warning
     */
    static float DecodeFREQ( int iFreq )
    {
        float fFreq;

#if 0
        fFreq = (float) 1984000. + POCKETSONATA::_fFreqRes * (float) iFreq;
#else
        fFreq = POCKETSONATA::_fFreqRes * ( float ) iFreq;
#endif
        return fFreq;
    } ;

    /**
     * @brief DecodeFREQMHz
     * @param iFreqHz
     * @return
     */
    static float DecodeFREQMHz( unsigned int uiFreq )
    {
        float fRetFreq;

        fRetFreq = ( (float) uiFreq * POCKETSONATA::_fFreqRes / (float) 1000000. );
        return fRetFreq;	/* [MHz] */
    } ;

    /**
     * @brief     EncodeRealFREQMHz
     * @param     int * piFreq
     * @param     int * piCh
     * @param     int iBoardID
     * @param     float fFreq
     * @return    bool
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2021-07-24, 10:47
     * @warning
     */
    static bool EncodeRealFREQMHz( int *piFreq, float fFreq )
    {
        bool bRet=true;

#if 0
        float fFREQ;
		*piCh = 0;

        if( is_not_zero<float>(fFreq) == true ) {
            int iNo = 0;

            fFREQ = (fFreq * (float) 1000.) - (POCKETSONATA::m_fCenterFreq[iBoardID][iNo] - 64000);

            if( fFREQ < 0. ) {
                fFREQ += 1024000.0;
                *piCh = ( int ) (( float ) fFREQ / (float) 128000.);

                if( fFREQ - (*piCh * 128000) >= 64000 ) {
                    *piFreq = IDIV( (fFREQ - ( float ) (*piCh * 128000) - (float) 64000.), POCKETSONATA::_fFreqRes );
                }
                else {
                    *piFreq = IDIV( (fFREQ - ( float ) (*piCh * 128000)), POCKETSONATA::_fFreqRes ) + 32768;
                }

                *piCh += 8;
            }
            else {
                *piCh = ( int ) (( float ) fFREQ / (float) 128000.);

                if( fFREQ - (*piCh * 128000) >= 64000 ) {
                    *piFreq = IDIV( (fFREQ - ( float ) (*piCh * 128000) - (float) 64000.), POCKETSONATA::_fFreqRes );
                }
                else {
                    *piFreq = IDIV( (fFREQ - ( float ) (*piCh * 128000)), POCKETSONATA::_fFreqRes ) + 32768;
                }

            }
        }
        else {
			*piFreq = 0;
            bRet = false;
        }
#else
        *piFreq = (int) ( ( fFreq * POCKETSONATA::_fFreqRes ) + 0.5 );

#endif

        return bRet;
    } ;

    /**
     * @brief
     * @param     int * piFreq
     * @param     int * piCh
     * @param     float fFreq
     * @return    bool
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022/02/21 23:09:10
     * @warning
     */
#if 0
    static bool EncodeRealFREQMHz( int *piFreq, int *piCh, float fFreq, int iBoardID=m_iBoardID, int iNo=0 )
    {
        bool bRet=true;
        float fFREQ;

        fFREQ = ( fFreq * (float) 1000. ) - ( POCKETSONATA::m_fCenterFreq[iBoardID][iNo] - 64000 );

        if( fFREQ < 0. ) {
            fFREQ += 1024000.0;
            *piCh = (int) ( (float) fFREQ / (float) 128000. );

            if( fFREQ - ( *piCh * 128000 ) >= 64000 ) {
                *piFreq = IDIV( ( fFREQ - (float) ( *piCh * 128000 ) - (float) 64000. ), POCKETSONATA::_fFreqRes );
            }
            else {
                *piFreq = IDIV( ( fFREQ - (float) ( *piCh * 128000 ) ), POCKETSONATA::_fFreqRes ) + 32768;
            }

            *piCh += 8;
        }
        else {
            *piCh = (int) ( (float) fFREQ / (float) 128000. );

            if( fFREQ - ( *piCh * 128000 ) >= 64000 ) {
                *piFreq = IDIV( ( fFREQ - (float) ( *piCh * 128000 ) - (float) 64000. ), POCKETSONATA::_fFreqRes );
            }
            else {
                *piFreq = IDIV( ( fFREQ - (float) ( *piCh * 128000 ) ), POCKETSONATA::_fFreqRes ) + 32768;
            }

        }

        return bRet;
    } ;
#endif

    /**
     * @brief EncodeFREQMHz
     * @param iFreqHz
     * @return
     */
    static unsigned int EncodeFREQMHz( float fFreq )
    {
        unsigned int uiRet;
        float fRetFreq;

        if( fFreq > 0 && fFreq < MAX_FREQ_MHZ ) {
            fRetFreq = ( ( fFreq * (float) 1000000. ) / POCKETSONATA::_fFreqRes);
            uiRet = ( unsigned int ) ( fRetFreq + 0.5 );	/* [MHz] */
        }
        else {
            uiRet = 0;
        }
        return uiRet;
    } ;

    /**
     * @brief     EncodeRealFREQMHz
     * @param     float fFreq
     * @return    unsigned int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-02, 18:53
     * @warning
     */
    static unsigned int EncodeRealFREQMHz( float fFreq )
    {
        float fRetFreq= ( float ) 0.0;

        if( fFreq > ( float ) 0. ) {
            fRetFreq = ((fFreq * (float) 1000000.) / POCKETSONATA::_fFreqRes);
        }
        return (unsigned int) ( fRetFreq + 0.5 );	/* [MHz] */
    } ;

    /**
     * @brief EncodeFREQMHzFloor
     * @param fFreq
     * @return
     */
    static int EncodeFREQMHzFloor( float fFreq )
    {
        float fRetFreq= ( float ) 0.0;

        if( fFreq > (float) 0. ) {
            fRetFreq = ( ( ( (float) fFreq - ( float ) 0.001 ) * (float) 1000000. ) / POCKETSONATA::_fFreqRes );
        }
        else {
        }
        return (int) ( fRetFreq );	/* [MHz] */
    } ;

    /**
     * @brief
     * @param     float fFreq
     * @return    int
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022/02/21 23:09:18
     * @warning
     */
    static int EncodeFREQMHzCeiling( float fFreq )
    {
        float fRetFreq=(float) 0.0;

        if( fFreq > (float) 0. ) {
            fRetFreq = ( ( ( (float) fFreq + (float) 0.001 ) * (float) 1000000. ) / POCKETSONATA::_fFreqRes);
        }
        else {
        }
        return (int) ( fRetFreq + 0.5 );	/* [MHz] */
    } ;

    /**
     * @brief     펄스폭으로 단위가 [ns]로 변환한다.
     * @param     int iPW
     * @return    float
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2022-07-04 13:27:20
     * @warning
     */
    static float DecodePW( int iPW )
    {
        float fPW=(float) 0.0;

        if( iPW >= 0 ) {
            fPW = (float) ( (float) iPW * POCKETSONATA::_toaRes / (float) 1000000000.);
        }
        else {
        }
        return fPW;		/* [ns] */
    } ;

    /**
     * @brief     펄스폭으로 단위가 [us]로 변환한다.
     * @param     int iPW
     * @return    float
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2022-07-04 13:27:46
     * @warning
     */
    static float DecodePWus( int iPW )
    {
        float fretPW=(float) 0.0;

        if( iPW >= 0 ) {
            fretPW = (float) iPW * POCKETSONATA::_toaRes;
            fretPW = ( fretPW / (float) 1000. );
        }
        else {
        }
        return fretPW;
    } ;

    /**
     * @brief
     * @param     int iPW
     * @return    float
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022/02/21 23:09:36
     * @warning
     */
    static float DecodePWns( int iPW )
    {
        float fretPW=(float) 0.0;

        if( iPW >= 0 ) {
            fretPW = (float) iPW * POCKETSONATA::_toaRes;
        }
        else {

        }
        return fretPW;
    } ;

    /**
     * @brief     EncodePWns
     * @param     float fPW
     * @return    unsigned int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-02, 18:53
     * @warning
     */
    static unsigned int EncodePWns( float fPW )
    {
        unsigned int uiRet = PDW_PW_MAX;
        float fretPW;

        if( fPW < 0 || fPW > PDW_PW_NS_MAX ) {

        }
        else {
            fretPW = fPW / POCKETSONATA::_toaRes;

            uiRet = ( unsigned int ) ( fretPW + 0.5 );
        }

        return uiRet;
    } ;

    /**
     * @brief
     * @param     float fPW
     * @return    int
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022/02/21 23:09:41
     * @warning
     */
    static int EncodePWFloor( float fPW )
    {
        int iRet = PDW_PW_MAX;
        float fretPW;

        if( fPW < 0 || fPW > PDW_PW_NS_MAX ) {
        }
        else {
            fretPW = fPW * ( float ) 1000.;
            fretPW = fretPW / POCKETSONATA::_toaRes;

            iRet = ( int ) ( fretPW + 0.5 );
        }
        return iRet;
    } ;

    /**
     * @brief     펄스폭 값을 PDW 값으로 변환 합니다.
     * @param     float fPW [ns]
     * @return    int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-02, 19:16
     * @warning
     */
    static int EncodePW( float fPW )
    {
        int iRet= PDW_PW_MAX;
        float fretPW;

        if( fPW < 0 || fPW > PDW_PW_NS_MAX ) {

        }
        else {
            fretPW = fPW * ( float ) 1000.;
            fretPW = fretPW / POCKETSONATA::_toaRes;

            iRet = ( int ) ( fretPW + 0.5 );
            if( iRet > PDW_PW_MAX ) {
                iRet = PDW_PW_MAX;
            }
        }

        return iRet;
    } ;

    /**
     * @brief DecodeTOA
     * @param ffTOA
     * @return
     */
    static float DecodeTOA( _TOA tTOA )
    {
        float fTOA;

        fTOA = ( float ) ( ( float ) tTOA * ( float ) POCKETSONATA::_toaRes / ( float ) 1000.0 );
        return fTOA;	/* [ns] */
    } ;

    /**
     * @brief
     * @param     _TOA iTOA
     * @return    double
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022/02/21 23:09:47
     * @warning
     */
    static double DblDecodeTOA( _TOA iTOA  )
    {
        double dTOA;

        iTOA = iTOA & 0xFFFFFFFFFFF;

        dTOA = (double) ( (double) iTOA * (double) POCKETSONATA::_toaRes / (double) 1.0 );
        return dTOA;	/* [ns] */
    } ;

    /**
     * @brief DecodeTOAus
     * @param iTOA
     * @return
     */
    static double DecodeTOAus( _TOA iTOA  )
    {
        double fretTOA;

        iTOA = iTOA & 0xFFFFFFFFFFF;

        fretTOA = ( (double) iTOA * POCKETSONATA::_toaRes / (double) 1000. );
        return fretTOA;	/* [us] */
    } ;

    /**
     * @brief DecodeTOAms
     * @param iTOA
     * @return
     */
    static double DecodeTOAms( _TOA tTOA  )
    {
        double fretTOA;

        fretTOA = ( (double) tTOA * POCKETSONATA::_toaRes / (double) 1000000. );
        return fretTOA;	/* [ms] */
    } ;

    /**
     * @brief DecodeTOAs
     * @param iTOA
     * @return
     */
    static double DecodeTOAs( _TOA tTOA )
    {
        double fretTOA;

        fretTOA = ( ( double ) tTOA * POCKETSONATA::_toaRes / ( double ) 1000000000. );
        return fretTOA;	/* [ms] */
    };

    /**
     * @brief EncodeTOAus
     * @param iTOA
     * @return
     */
    static _TOA EncodeTOAus( float fTOA  )
    {
        _TOA iretTOA;

        iretTOA = (_TOA) ( ( ( fTOA * (float) 1000.0 ) / POCKETSONATA::_toaRes) + 0.5 );
        return iretTOA;
    } ;

    /**
     * @brief     EncodeTOAms
     * @param     float fTOA
     * @return    _TOA
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-09-11 16:57:00
     * @warning
     */
    static _TOA EncodeTOAms( float fTOA )
    {
        _TOA iretTOA;

        iretTOA = ( _TOA ) ( ( ( fTOA * ( float ) 1000000.0 ) / POCKETSONATA::_toaRes ) + 0.5 );
        return iretTOA;
    };

    /**
     * @brief     EncodeTOAs
     * @param     float fTOA
     * @return    _TOA
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-04-07 20:41:50
     * @warning
     */
    static _TOA EncodeTOAs( float fTOA )
    {
        _TOA iretTOA;

        iretTOA = ( _TOA ) ( ( ( fTOA * ( float ) 1000000000.0 ) / POCKETSONATA::_toaRes ) + 0.5 );
        return iretTOA;	/* [ns] */
    };

    /**
     * @brief     EncodePA
     * @param     float fPA
     * @return    unsigned int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-02, 18:58
     * @warning
     */
    static unsigned int EncodePA( float fPA )
    {
        float fValue;
        unsigned int uiRet;

        if( fPA > PDW_PA_DB_MAX ) {
            uiRet = 0xFFFF;
        }
        else {
            fValue = ( fPA - PDW_PA_DB_MIN ) / ( float ) 20.;
            if( fValue > ( float ) 0.0 ) {
                fValue = ( float ) pow( 10., ( double ) fValue );
            }
            else {
                fValue = ( float ) 0.0;
            }
            uiRet = ( unsigned int ) ( fValue + 0.5 );
        }

        return uiRet;
    } ;

    /**
     * @brief     EncodePAFloor
     * @param     float fPA
     * @return    unsigned int
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-12-02 10:53:55
     * @warning
     */
    static unsigned int EncodePAFloor( float fPA )
    {
        float fValue;
        unsigned int uiRet;

        if( fPA > PDW_PA_DB_MAX ) {
            uiRet = 0xFFFF;
        }
        else {
            fValue = ( fPA - PDW_PA_DB_MIN ) / ( float ) 20.;
            if( fValue > ( float ) 0.0 ) {
                fValue = ( float ) pow( 10., ( double ) fValue );
            }
            else {
                fValue = ( float ) 0.0;
            }
            uiRet = ( unsigned int ) ( fValue );
        }

        return uiRet;
    };

    /**
	 * @brief     신호세기인 [dBm] 단위로 변환한다.
	 * @param     int iPA
	 * @return    float
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   1.0.0
	 * @date      2022-07-04 13:26:35
	 * @warning
	 */
    static float DecodePA( int iPA )
    {
        float fPA;

        if( iPA == 0 ) {
            fPA = (float) PDW_PA_DB_MIN;
        }
        else if( iPA >= 0x10000 ) {
            fPA = ( float ) 7.329466;
            TRACE( "\n PA 값이 초과 됐습니다 !!" );
            WhereIs;
        }
        else {
            fPA = ( float ) 20. * (float) log10( iPA ) + PDW_PA_DB_MIN;
        }
        return fPA;		/* [dBm] */
    } ;

    /**
     * @brief     DecodeFMOPBW
     * @param     int iFMOPBW
     * @return    float
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-10-08 16:19:04
     * @warning
     */
    static float DecodeFMOPBW( int iFMOPBW )
    {
        float fFMOPBW;

        fFMOPBW = ( float ) iFMOPBW * ( float ) FMOP_BW;

        return fFMOPBW;
    };

    /**
     * @brief     EncodeFMOPBW
     * @param     float fFMOPBW
     * @return    int
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-10-08 16:23:06
     * @warning
     */
    static int EncodeFMOPBW( float fFMOPBW )
    {
        int iFMOPBW;

        iFMOPBW = (int) ( ( ( float ) fFMOPBW / ( float ) FMOP_BW ) + (float) 0.5 );

        return iFMOPBW;
    };

};

class CIQ : public CData
{
private:
	STR_IQ_HEADER m_IQHeader;
	STR_IQ_DATA m_IQData;

public:
	CIQ(STR_RAWDATA *pRawData);
	virtual ~CIQ();

	void Alloc( unsigned int uiItems=0 );
	void Free();
	void ReadDataHeader();
    void ConvertPDWData( STR_PDWDATA *pPDWData, STR_FILTER_SETUP *pFilterSetup=NULL, bool bSwap=true, ENUM_CONVERT_OPTION enOption=enUnitToPDW );
	void *GetData();
	void *GetHeader();

	inline unsigned int GetOffsetSize() { return 0; }
	inline int GetHeaderSize() { return 0; }
    inline unsigned int GetOneDataSize() { return 0; }
	//inline unsigned int GetDataItems( unsigned long long ullFileSize ) { return 0; }
    //inline void SetHeaderData( void *pData ) { return; }

};

// 701 IQ
class C7IQ : public CData
{
private:
	STR_IQ_DATA m_IQData;

public:
    C7IQ(STR_RAWDATA *pRawData, STR_FILTER_SETUP *pFilterSetup );
	virtual ~C7IQ();

	void Alloc( unsigned int uiItems=0 );
	void Free();
	void ReadDataHeader() {  }
    void ConvertPDWData( STR_PDWDATA *pPDWData, STR_FILTER_SETUP *pFilterSetup=NULL, bool bSwap=true, ENUM_CONVERT_OPTION enOption=enUnitToPDW );
	void *GetData();
	void *GetHeader() { return NULL; }

	inline unsigned int GetOffsetSize() { return 0; }
	inline int GetHeaderSize() { return 0; }
    inline unsigned int GetOneDataSize() { return 0; }
	//inline unsigned int GetDataItems( unsigned long long ullFileSize ) { return 0; }
    //inline void SetHeaderData( void *pData ) { return; }
};

class CEIQ : public CData
{
private:
	STR_IQ_DATA m_IQData;

    SRxPDWHeader m_stHeader;

public:
	CEIQ(STR_RAWDATA *pRawData);
	virtual ~CEIQ();

	_COMMON_FUNCTIONS_;

	inline unsigned int GetOffsetSize() { return 0; }

};

class CMIDAS : public CData
{
private:
	// STR_IQ_DATA m_IQData;
	SELMIDAS_HCB m_HCB;
	UNI_ADJUNCT_TYPE m_ADJ;

	// PDW SUBRecord 경우
	SELSUBRECORDS *m_pSubRecords;

	EnumSCDataType m_enFileType;

	//STR_PDW_DATA m_PDWData;

	char *m_pDataChar;

    STR_ELINT_HEADER m_stHeader;    // 수정해야 함.

public:
	CMIDAS(STR_RAWDATA *pRawData);
	virtual ~CMIDAS();

	_COMMON_FUNCTIONS_;

	int GetDataFormatSize( char ch );
	//void GetSubRecords( S_EL_PDW_RECORDS *pPDWRecords );
	double GetSubValue( char *psubformat );

	inline unsigned int GetOffsetSize() { return 0; }

};


// PDW 데이터 파일을 읽거나 쓰기 위한 클래스 정의
class CDataFile
{
private:
	int m_iFileIndex;

	CRawFile m_RawDataFile;
	CData *m_pData;

public:


public:
	CDataFile(void);
	virtual ~CDataFile(void);

    void ConvertArray( STR_PDWDATA *pPDWData, bool bSwap, STR_FILTER_SETUP *pFilterSetup, bool bConvert );
    CData *ReadDataFile( char *pPathname, STR_FILTER_SETUP *pstFilterSetup, ENUM_CONVERT_OPTION enOption );
    void ReadDataMemory( char *pstData, char *pstPathname, STR_FILTER_SETUP *pstFilterSetup, ENUM_CONVERT_OPTION enOption, size_t szFileSize=0 );
    void SaveDataFile( char *pstPathname, void *pData, int iNumData, ENUM_UnitType enUnitType, ENUM_DataType enDataType, void *pDataEtc=NULL, int iSizeOfEtc=0 );
	void Alloc();
	void Free();
	void *GetData();
    void *GetRealData();
	void *GetHeader();
    int GetBandWidth();
	void SetData( CData *pData );

	// 파일 읽기 관련 함수
	void ReadDataHeader();
	void ReadDataAll( CData *pData );

	//ENUM_DataType WhatDataType( char *pStrPathname );
	//ENUM_UnitType WhatUnitType( char *pStrPathname );

	int GetHeaderSize( CData *pData );
	unsigned int GetOneDataSize( CData *pData );
	unsigned int GetDataItems( CData *pData );

	inline int GetFileIndex() { return m_iFileIndex; }

    inline unsigned long long int FileSize( char *pPathFileName ) { return m_RawDataFile.GetRawFileSize( pPathFileName ); }

    /**
     * @brief     GetDataItems
     * @return    UINT
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-09, 11:13
     * @warning
     */
    inline UINT GetDataItems() {
        UINT uiRet = 0;
        if( m_pData != NULL ) {
            uiRet = m_pData->m_PDWData.GetTotalPDW();
        }

        return uiRet;
    }
	inline ENUM_UnitType GetUnitType() { return m_pData->m_enUnitType; }
	inline ENUM_DataType GetDataType() { return m_pData->m_enDataType; }

	/**
	 * @brief     GetRawData
	 * @return    CData *
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022-05-09, 11:13
	 * @warning
	 */
	inline CData *GetRawData() {
        CData *pRet=NULL;
        if( m_pData != NULL ) {
            pRet = m_pData;
        }

        return pRet;
    }

	inline STR_FILTER_SETUP *GetFilterSetup() { return & m_pData->m_strFilterSetup; }

	/**
	 * @brief     ClearFilterSetup
	 * @return    void
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022-05-09, 11:15
	 * @warning
	 */
	inline void ClearFilterSetup() {
        m_pData->ClearFilterSetup();
    }

	/**
	 * @brief     GetFilteredDataItems
	 * @return    UINT
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022-05-09, 11:15
	 * @warning
	 */
	inline UINT GetFilteredDataItems() {
        STR_PDWREALDATA *pPDWData=(STR_PDWREALDATA *) m_pData->GetData();
        return pPDWData->uiDataItems;
    }

    inline UINT GetFilteredRealDataItems() {
		STR_PDWREALDATA *pPDWRealData=(STR_PDWREALDATA *) m_pData->GetRealData();
		return pPDWRealData->uiDataItems;
	}

#ifdef _GRAPH_
    inline UINT GetWindowNumber() { if( m_pData != NULL ) return m_pData->m_uiWindowNumber; else return 0; }
    inline void IncWindowNumber() { m_pData->IncWindowNumber(); }
    inline void DecWindowNumber() { m_pData->DecWindowNumber(); }
#endif

    inline STR_PDWDATA *GetPDWData() { return & m_pData->m_PDWData; }

	//inline STR_PDWREALDATA *GetRealData() { return (STR_PDWREALDATA * ) m_pData->GetRealData(); }

    //inline STR_PDWDATA { if( m_pData != NULL ) return m_pData->m_PDWData; else return NULL; }

private:


};


#ifdef _GRAPH_

//////////////////////////////////////////////////////////////////////////
class CMapData {
private:
    bool m_bMapData;

    static map<CString, CDataFile *> m_gMapData;

public:
    CMapData(void)
    {

    }

    virtual ~CMapData(void)
    {

    }

    void IncWindowNumber( CDataFile *pDataFile )
    {
        pDataFile->IncWindowNumber(); // m_pData->m_uiWindowNumber;
    }


    void AddMapData( CString *pStrPathName, CDataFile *pData )
    {
#ifdef __linux__
#elif defined(_MSC_VER)
        Log( enNormal, _T("\n MapData()에 경로명[%s]을 추가했습니다.") , *pStrPathName );
#else

#endif

        m_gMapData.insert( make_pair( *pStrPathName, pData ) );
    }

    CDataFile *FindMapData( CString *pStrPathName )
    {
        CDataFile *pDataFile;
        map<CString, CDataFile *>::iterator it;

        it = m_gMapData.find( *pStrPathName );
        if( it == m_gMapData.end() ) {
            pDataFile = NULL;
        }
        else {
            pDataFile = it->second;

            // 데이터 ID 증가
            //++ pData->m_uiLoadFile;
        }

        return pDataFile;
    }

    void CloseMapData( CString *pStrWindowTitle )
    {
        auto it=m_gMapData.begin();

        if( pStrWindowTitle == NULL ) {
            while( it != m_gMapData.end() ) {
                //it->second->Free();
                delete it->second;

                ++ it;
            }
            m_gMapData.clear();
        }
        else {
#ifdef _MSC_VER
            CDataFile *pDataFile;

            while( it != m_gMapData.end() ) {
                if( pStrWindowTitle->Compare( it->first ) == 0 ) {
                    pDataFile = it->second;

                    if( pDataFile->GetWindowNumber() == 0 ) {
                        delete it->second;
                        m_gMapData.erase( it++ );
                    }
                    else {
                        ++ it;

                        // 데이터 ID 감소
                        pDataFile->DecWindowNumber();
                    }

                }
                else {
                    ++ it;
                }
            }
#endif
        }
    }

};
#endif


class CEncode {
    // Encode
public:


    static unsigned int EncodePulseType( int iPulseType ) {
        unsigned int uiPulseType=0;

        if( g_enUnitType == en_XBAND ) {
#if defined(_GRAPH_) || defined(_XBAND_)
            uiPulseType = CXPDW::EncodePulseType( iPulseType );
#endif

        }
        else if( g_enUnitType == en_ZPOCKETSONATA ) {
            uiPulseType = CPOCKETSONATAPDW::EncodePulseType( iPulseType );

        }
        else if( g_enUnitType == en_ELINT ) {
#if defined(_GRAPH_) || defined(_ELINT_)
            uiPulseType = CEPDW::EncodePulseType( iPulseType );
#endif

        }
        else {
            //uiPulseType = 0;

        }
        return uiPulseType;

    } ;


    /**
     * @brief     EncodeDOA
     * @param     float fDOA
     * @return    unsigned int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-02, 19:24
     * @warning
     */
    static unsigned int EncodeDOA( float fDOA ) {
        unsigned uiDOA=0;

        if( g_enUnitType == en_XBAND ) {
#if defined(_GRAPH_) || defined(_XBAND_)
            uiDOA = CXPDW::EncodeDOA( fDOA );
#endif

        }
        else if( g_enUnitType == en_ZPOCKETSONATA ) {
            uiDOA = CPOCKETSONATAPDW::EncodeDOA( fDOA );

        }
        else if( g_enUnitType == en_ELINT ) {
#if defined(_GRAPH_) || defined(_ELINT_)
            uiDOA = CEPDW::EncodeDOA( fDOA );
#endif

        }
		else if (g_enUnitType == en_701 ) {
#if defined(_GRAPH_) || defined(_701)
			uiDOA = C7PDW::EncodeDOA(fDOA);
#endif

		}
        else {
            // uiDOA = 0;
        }

        return uiDOA;
    } ;

    /**
     * @brief     EncodePA
     * @param     float fPA
     * @return    unsigned int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-02, 19:27
     * @warning
     */
    static unsigned int EncodePA( float fPA ) {
        unsigned int uiPA=0;

        if( g_enUnitType == en_XBAND ) {
#if defined(_GRAPH_) || defined(_XBAND_)
            uiPA = CXPDW::EncodePA( fPA );
#endif

        }
        else if( g_enUnitType == en_ZPOCKETSONATA ) {
            uiPA = CPOCKETSONATAPDW::EncodePA( fPA );

        }
        else if( g_enUnitType == en_ELINT ) {
#if defined(_GRAPH_) || defined(_ELINT_)
            uiPA = CEPDW::EncodePA( fPA );
#endif

        }
		else if (g_enUnitType == en_701) {
#if defined(_GRAPH_) || defined(_701)
			uiPA = C7PDW::EncodePA(fPA);
#endif

		}

        else {
            // uiPA = 0;

        }
        return uiPA;

    } ;

    /**
     * @brief     EncodeTOAus
     * @param     float fTOA
     * @param     int iBandWidth
     * @return    unsigned int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-02, 19:30
     * @warning
     */
#if defined(_GRAPH_) || defined(_XBAND_) || defined(_ELINT_)
    static _TOA EncodeTOAus( float fTOA, int iBandWidth ) {
        _TOA tTOA=0;

        if( g_enUnitType == en_XBAND ) {
#if defined(_GRAPH_) || defined(_XBAND_)
            tTOA = CXPDW::EncodeTOAus( fTOA, (XBAND::ENUM_BANDWIDTH) iBandWidth );
#endif

        }
        else if( g_enUnitType == en_ZPOCKETSONATA ) {
            tTOA = CPOCKETSONATAPDW::EncodeTOAus( fTOA );

        }
        else if( g_enUnitType == en_ELINT ) {
#if defined(_GRAPH_) || defined(_ELINT_)
            tTOA = CEPDW::EncodeTOAus( fTOA, (ELINT::ENUM_BANDWIDTH) iBandWidth );
#endif

        }
		else if (g_enUnitType == en_701) {
			//tTOA = C7PDW::EncodeTOAus(fTOA, (ELINT::ENUM_BANDWIDTH) iBandWidth);
			tTOA = 0;

		}
        else {
            // tTOA = 0;
        }
        return tTOA;
    }
#endif

	static _TOA EncodeTOAs(float fTOA, int iBandWidth) {
		_TOA tTOA=0;

		if (g_enUnitType == en_XBAND) {
#if defined(_GRAPH_) || defined(_XBAND_)
			tTOA = CXPDW::EncodeTOAs(fTOA, (XBAND::ENUM_BANDWIDTH) iBandWidth);
#endif
		}
		else if (g_enUnitType == en_ZPOCKETSONATA) {
            tTOA = CPOCKETSONATAPDW::EncodeTOAs( fTOA );

		}
		else if (g_enUnitType == en_ELINT) {
			//tTOA = CEPDW::EncodeTOAs(fTOA, (ELINT::ENUM_BANDWIDTH) iBandWidth);

		}
		else if (g_enUnitType == en_701) {
#if defined(_GRAPH_) || defined(_701)
			tTOA = C7PDW::EncodeTOAs(fTOA, (_701::ENUM_BANDWIDTH) iBandWidth);
#endif

		}
		else {
			//tTOA = 0;
		}
		return tTOA;
	}

    /**
     * @brief     EncodePWns
     * @param     float fPWns
     * @param     int iBandWidth
     * @return    unsigned int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-02, 19:24
     * @warning
     */
#if defined(_GRAPH_) || defined(_XBAND_) || defined(_ELINT_)
    static unsigned int EncodePWns( float fPWns, int iBandWidth ) {
        unsigned uiPW=0;

        if( g_enUnitType == en_XBAND ) {
#if defined(_GRAPH_) || defined(_XBAND_)
            uiPW = CXPDW::EncodePWns( fPWns, (XBAND::ENUM_BANDWIDTH) iBandWidth );
#endif

        }
        else if( g_enUnitType == en_ZPOCKETSONATA ) {
            uiPW = CPOCKETSONATAPDW::EncodePWns( fPWns );

        }
        else if( g_enUnitType == en_ELINT ) {
#if defined(_GRAPH_) || defined(_ELINT_)
            uiPW = CEPDW::EncodePWns( fPWns, (ELINT::ENUM_BANDWIDTH) iBandWidth );
#endif

        }
        else {
            //uiPW = 0;
        }

        return uiPW;
    } ;
#endif

	/**
	 * @brief     EncodePWs
	 * @param     float fPWns
	 * @param     int iBandWidth
	 * @return    unsigned int
	 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   1.0.0
	 * @date      2023-01-24 15:41:32
	 * @warning
	 */
	static unsigned int EncodePWs(float fPWns, int iBandWidth) {
		unsigned uiPW=0;

		if (g_enUnitType == en_XBAND) {
#if defined(_GRAPH_) || defined(_XBAND_)
			uiPW = CXPDW::EncodePWns(fPWns, (XBAND::ENUM_BANDWIDTH) iBandWidth);
#endif

		}
		else if (g_enUnitType == en_ZPOCKETSONATA) {
			uiPW = CPOCKETSONATAPDW::EncodePWns(fPWns);

		}
		else if (g_enUnitType == en_ELINT) {
#if defined(_GRAPH_) || defined(_ELINT_)
			uiPW = CEPDW::EncodePWns(fPWns, (ELINT::ENUM_BANDWIDTH) iBandWidth);
#endif

		}
		else if (g_enUnitType == en_701) {
#if defined(_GRAPH_) || defined(_701)
			uiPW = C7PDW::EncodePWs(fPWns, (_701::ENUM_BANDWIDTH) iBandWidth);
#endif

		}
		else {
			//uiPW = 0;
		}

		return uiPW;
	};

    /**
     * @brief     EncodeRealFREQMHz
     * @param     float fFrequency
     * @return    unsigned int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-02, 19:32
     * @warning
     */
    static unsigned int EncodeRealFREQMHz( int *piCh, float fFrequency ) {
        unsigned int uiFrequency=0;

        if( g_enUnitType == en_XBAND ) {
#if defined(_GRAPH_) || defined(_XBAND_)
            *piCh = -1;
            uiFrequency = CXPDW::EncodeRealFREQMHz( fFrequency );
#endif

        }
        else if( g_enUnitType == en_ZPOCKETSONATA ) {
            //int iBoardID = 3; // GetBandOfFreq( fFrequency );

            CPOCKETSONATAPDW::EncodeRealFREQMHz( ( int * ) & uiFrequency, fFrequency );
        }
        else if( g_enUnitType == en_ELINT ) {
#if defined(_GRAPH_) || defined(_ELINT_)
            *piCh = 0;
            uiFrequency = CEPDW::EncodeRealFREQMHz( fFrequency );
#endif

        }
		else if (g_enUnitType == en_701) {
#if defined(_GRAPH_) || defined(_701)
			*piCh = 0;
			uiFrequency = C7PDW::EncodeRealFREQMHz(fFrequency);
#endif

		}
        else {
            *piCh = 0;
            //uiFrequency = 0;
        }

        return uiFrequency;
    } ;

};

class CDecode {
public:

    /**
     * @brief     DecodeRealFREQMHz
     * @param     unsigned int uiFrequency
     * @return    float
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-16, 15:47
     * @warning
     */
    static float DecodeRealFREQMHz( unsigned int uiFrequency ) {
        float fFrequency=(float) 0.0;

        if( g_enUnitType == en_XBAND ) {
#if defined(_GRAPH_) || defined(_XBAND_)
            fFrequency = CXPDW::DecodeRealFREQMHz( uiFrequency );
#endif

        }
        else if( g_enUnitType == en_ZPOCKETSONATA ) {
            //int iBoardID = 3; // GetBandOfFreq( fFrequency );
            // uiFrequency = CPOCKETSONATAPDW::DecodeRealFREQMHz( uiFrequency, *piCh, ( int ) iBoardID, fFrequency );
            fFrequency = 0;
        }
        else if( g_enUnitType == en_ELINT ) {
#if defined(_GRAPH_) || defined(_ELINT_)
            fFrequency = CEPDW::DecodeRealFREQMHz( uiFrequency );
#endif

        }
        else {
            //fFrequency = 0;
        }

        return fFrequency;
    } ;


//     static unsigned int DecodePWns( float fPWns, int iBandWidth ) {
//         unsigned uiPW;
//
//         if( g_enUnitType == en_XBAND ) {
//             uiPW = CXPDW::DecodePWns( fPWns, (XBAND::ENUM_BANDWIDTH) iBandWidth );
//
//         }
//         else if( g_enUnitType == en_ZPOCKETSONATA ) {
//             uiPW = CPOCKETSONATAPDW::DecodePWns( fPWns );
//
//         }
//         else if( g_enUnitType == en_ELINT ) {
//             uiPW = CEPDW::DecodePWns( fPWns, (ELINT::ENUM_BANDWIDTH) iBandWidth );
//
//         }
//         else {
//             uiPW = 0;
//         }
//
//         return uiPW;
//     } ;

};


