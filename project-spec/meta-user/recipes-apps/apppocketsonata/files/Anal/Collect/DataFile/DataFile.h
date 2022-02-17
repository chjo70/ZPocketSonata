#pragma once

#include <stdio.h>

//#include "../../INC/system.h"
//#include "../../../Anal/SigAnal/_Type.h"
#include "../../../Anal/SigAnal/_Macro.h"
#include "../../../Anal/SigAnal/_Struct.h"

#include "../../../Anal/MIDAS/RawFile.h"

#include "../../../Anal/MIDAS/PDWIQ.h"

#ifdef _FFTW_
#include "../../../../MSC/DeltaGraph/FFTW/fftw3.h"

#endif

#include "../../../Anal/MIDAS/Midas.h"


#define			PDW_ITEMS						(1024*128)			// 9437164
#define			IQ_ITEMS						(1024*128)

//#define			MAX_RAWDATA_SIZE				(4000000)	// 2,432,052
#define			MAX_RAWDATA_SIZE				_max( (sizeof(SRxPDWHeader) + sizeof(SRxPDWDataRGroup)*PDW_ITEMS), sizeof(TNEW_IQ)*IQ_ITEMS )	// 2,432,052

#define			MAX_HEADER_SIZE					_max( HEADER_CONTROL_BLOCK_SIZE, 100 )

#define	RAD2DEG			(57.2957795130)


typedef enum {
	enUnselectedSubGraph = -1,

	enSubMenu_1 = 1,
	enSubMenu_2,
	enSubMenu_3,
	enSubMenu_4,
	enSubMenu_5,
	enSubMenu_6,


} ENUM_SUB_GRAPH ;

#ifndef _ENUM_DataType
#define _ENUM_DataType
typedef enum {
	en_UnknownData = 0,

	en_PDW_DATA,
	en_IQ_DATA,
	en_IF_DATA,

} ENUM_DataType;
#endif


typedef enum {
    enUnitToPDW,        // 장비 포멧을 PDW 구조체로 변경 (PDW 저장장치에 따라 PDW 불러오기용)
    enPDWToPDW,         // PDW 구조체를 PDW 구조체로 변경 (저장된 PDW 파일을 불러오기용)
    enPDWToReal,        // PDW 구조체를 실제값으로 변경 (그래프 전시용)
    enUnitToReal        // 장비 포멧을 실제값으로 변경 (그래프 전시용)

} ENUM_CONVERT_OPTION;


#define MAX_SONATA_DATA		(10000)
typedef union {
	TNEW_PDW stPDWData[MAX_SONATA_DATA];
	TNEW_IQ stIQData[MAX_SONATA_DATA];

	DMAPDW stZPDWData[MAX_SONATA_DATA];

} UNI_SONATA_DATA;

struct STR_SONATA_DATA {
	UINT uiItem;

	ENUM_UnitID m_enUnitID;
	ENUM_BoardID m_enBoardID;
	ENUM_DataType enDataType;

	UNI_SONATA_DATA unRawData;

	UINT uiNo;

} ;


struct STR_RAWDATA {
	UINT uiByte;
	void *pDataBuffer;

	//UINT uiDataItems;
	ENUM_DataType enDataType;
	ENUM_UnitType enUnitType;
    char szFileName[_MAX_PATH];

} ;

typedef unsigned long long int _TOA;

struct STR_PDW_DATA {
	unsigned int uiDataItems;

	float *pfFreq;			// [KHz]
	float *pfPW;			// [ns]
	float *pfAOA;			// [degree]
	float *pfTOA;
	float *pfPA;
	float *pfDTOA;

	_TOA *pullTOA;

	char *pcType;			// [신호형태]
	char *pcDV;				// [DV]

	float *pfPh1;
	float *pfPh2;
	float *pfPh3;
	float *pfPh4;

}  ;

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
	void Alloc( unsigned int iItems=0 );	\
	void Free();	\
    void ConvertArrayData( STR_PDWDATA *pPDWData, bool bSwap=true, STR_FILTER_SETUP *pFilterSetup=NULL );	\
    void BypassArrayData( STR_PDWDATA *pPDWData ); \
	void ConvertArrayForELINT() { }	\
	void *GetData();	\
	void *GetHeader() { return NULL; }	\
	unsigned int GetHeaderSize();	\
    unsigned int GetOneDataSize();	\
	unsigned int GetDataItems( unsigned long long ullFileSize=0 );    \
    void SetHeaderData( void *pData ) { \
        if( m_iHeaderSize != -1 ) { \
            memcpy( & m_stHeader, pData, m_iHeaderSize ); \
            m_stHeader.CheckColTime(); \
        } \
    }


class CData
{
public:
    char *m_pRawHeaderBuffer;           // 헤더 데이터 저장소
    char *m_pRawDataBuffer;             // 실제 데이터 저장소

    int m_iHeaderSize;                  // 헤더 크기
    unsigned int m_iOneDataSize;        // 한개 PDW 데이터 크기
    unsigned long long  m_ullFileSize;  // 파일 크기
    UINT m_uiTotalDataItems;            // 전체 PDW 개수

	STR_PDW_DATA m_PDWData;             // PDW 데이터 개수 와 실제 PDW 항목별 데이터 값

    //STR_RAWDATA m_RawData;

    ENUM_DataType m_enDataType;
    ENUM_UnitType m_enUnitType;

    UINT m_uiWindowNumber;

    STR_FILTER_SETUP m_strFilterSetup;

public:
    CData();
    virtual ~CData();

    void Alloc( unsigned int uiItems=0 );
    void Free();

    void ClearFilterSetup();
    void swapByteOrder(unsigned int& ui);
    void swapByteOrder(unsigned long long& ull);
    void AllSwapData32( void *pData, int iLength );
    void ExecuteFFT( int iDataItems, STR_IQ_DATA *pIQData );

    void UpdateMacroSysVar();

    void ConvertPDWData( STR_PDWDATA *pPDWData, STR_FILTER_SETUP *pFilterSetup=NULL, bool bSwap=true, ENUM_CONVERT_OPTION enOption=enUnitToPDW );

    virtual void BypassArrayData( STR_PDWDATA *pPDWData )=0;
    virtual void ConvertArrayData( STR_PDWDATA *pPDWData, bool bSwap, STR_FILTER_SETUP *pFilterSetup=NULL ) = 0;
    virtual void MakeHeaderData( STR_PDWDATA *pPDWData ) = 0;
    virtual void MakePDWDataByUnitToPDW( STR_PDWDATA *pPDWData ) = 0;
    virtual void *GetData() = 0;
    virtual void *GetHeader() = 0;

    virtual unsigned int GetHeaderSize() = 0;
    virtual unsigned int GetOneDataSize() = 0;
    virtual unsigned int GetDataItems( unsigned long long ullFileSize=0 ) = 0;
    virtual void SetHeaderData( void *pData ) = 0;
};


////////////////////////////////////////////////////////////////////////////////////////////////////
// 소나타 PDW 데이터

namespace SONATA {
	const unsigned int uiPDW_CW=4;
	const unsigned int uiPDW_NORMAL=0;
	const unsigned int uiPDW_CHIRPUP=2;
	const unsigned int uiPDW_CHIRPDN=3;
	const unsigned int uiPDW_PMOP=1;
	const unsigned int uiPDW_DV=1;

    const float fAoaRes=(360.0/1024.);
    const float fToaRes=(20);
    const float fPWRes=(50);
    const float fPARes=(80./256.);
    const float fPAOffset=(-70.);
}

//////////////////////////////////////////////////////////////////////////
// SONATA 체계 RSA PDW 포멧
namespace PDW {
    #define PDW_PA_INIT		    (-89.0)

	#define ONE_SEC				(20000000)
	#define ONE_MICROSEC		(20)

	#define PW_RES				(50)

	#define	DOA_RES				(0.351562)

	#define	AMP_RES				(0.351562)

	struct FREQ_RESOL {
		UINT uiMin;
		UINT uiMax;
		int iOffset;
		float fRes;			// 각 구간에 따른 resolution
	} ;

	static FREQ_RESOL stFreqRes[ 3 ] = { {    0,  2560, 0, 0.625 },   /* LOW  FREQUENCY */
										 { 1280,  6400, 1260, 1.25  },   /* MID  FREQUENCY */
										 { 5866, 18740, 5866, 1.5   } } ;

}

class CPDW : public CData
{
private:
	//STR_PDW_DATA m_PDWData;

public:
	CPDW(STR_RAWDATA *pRawData);
	virtual ~CPDW();

	void Alloc( unsigned int nItems=0 );
	void Free();
	void ReadDataHeader() {  }
    void ConvertPDWData( STR_PDWDATA *pPDWData, STR_FILTER_SETUP *pFilterSetup=NULL, bool bSwap=true, ENUM_CONVERT_OPTION enOption=enUnitToPDW );
    
	void *GetData();

    unsigned int GetDataItems( unsigned long long ullFileSize );

	void *GetHeader() { return NULL; }

	inline unsigned int GetOffsetSize() { return 0; }
	inline unsigned int GetHeaderSize() { return 0; }
    inline unsigned int GetOneDataSize() { return sizeof(TNEW_PDW); }
    inline void SetHeaderData( void *pData ) { return; }

public:

    /**
     * @brief     DecodeTOAus
     * @param     unsigned int uiTOA
     * @return    float
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-02-09, 17:02
     * @warning
     */
    static float DecodeTOAus( unsigned int uiTOA  )
    {
        return (float) uiTOA / (float) ONE_MICROSEC;
    } ;

	/**
	 * @brief     DecodeRealFREQMHz
	 * @param     int iBand
	 * @param     unsigned int uiFreq
	 * @return    float
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022-02-09, 17:02
	 * @warning
	 */
	static float DecodeRealFREQMHz( int iBand, unsigned int uiFreq )
	{
		float fVal=0.0;

		if( iBand >= 0 && iBand <= 2 ) {
			fVal = FMUL( PDW::stFreqRes[iBand].fRes, uiFreq ) + PDW::stFreqRes[iBand].iOffset;
		}
		
		return fVal;
	}

	/**
	 * @brief     DecodePW
	 * @param     unsigned int uiPW
	 * @return    float
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022-02-09, 17:02
	 * @warning
	 */
	static float DecodePW( unsigned int uiPW )
	{
		return (float) ( uiPW ) * (float) PW_RES;		/* [ns] */
	} ;

	/**
	 * @brief     DecodeFREQMHz
	 * @param     int iFreq
	 * @return    float
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022-02-09, 17:03
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
	 * @date      2022-02-09, 17:03
	 * @warning
	 */
	static float DecodeDOA( unsigned int uiDOA )
	{
		return (float) DOA_RES * (float) uiDOA;
	} ;

	/**
	 * @brief     DecodePA
	 * @param     unsigned int uiPA
	 * @return    float
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022-02-09, 17:03
	 * @warning
	 */
	static float DecodePA( unsigned int uiPA )
	{		
		return (float) ( ( (float) uiPA * (float) AMP_RES ) - (float) 110. );
	} ;

    /**
     * @brief DecodeDOA
     * @param iDOA
     * @return
     */
    static float EncodeDOA(float fDOA )
    {
        return (float) ( (float) fDOA / SONATA::fAoaRes + 0.5 );
    } ;

};



////////////////////////////////////////////////////////////////////////////////////////////////////
// 수퍼헷 PDW 데이터

class CSPDW : public CData
{
private:
	//STR_PDW_DATA m_PDWData;

public:
	CSPDW(STR_RAWDATA *pRawData);
	virtual ~CSPDW();

	void Alloc( unsigned int nItems=0 );
	void Free();
	void ReadDataHeader() {  }
    void ConvertPDWData( STR_PDWDATA *pPDWData, STR_FILTER_SETUP *pFilterSetup=NULL, bool bSwap=true, ENUM_CONVERT_OPTION enOption=enUnitToPDW );
	void *GetData();
	void *GetHeader() { return NULL; }

    virtual void ConvertArrayData( STR_PDWDATA *pPDWData, bool bSwap, STR_FILTER_SETUP *pFilterSetup=NULL ) = 0;

	inline unsigned int GetOffsetSize() { return 0; }
	inline unsigned int GetHeaderSize() { return 0; }
    inline unsigned int GetOneDataSize() { return 0; }
	inline unsigned int GetDataItems( unsigned long long ullFileSize ) { return 0; }
    inline void SetHeaderData( void *pData ) { return; }

};

namespace ELINT {
	const unsigned int uiPDW_CW=0;
	const unsigned int uiPDW_NORMAL=1;
	const unsigned int uiPDW_DV=1;

    const float _toaRes[en50MHZ_BW+1] = { (float) 65.104167, (float) 8.138021 } ;
    const float fFreqRes=(float) 0.001;
    const float fDOARes=(float) 0.01;
    const float fPARes=(float) 0.25;
}

// 인천공항 PDW
class CEPDW : public CData
{
private:
    STR_ELINT_HEADER m_stHeader;

	ENUM_BANDWIDTH m_enBandWidth;

public:
	CEPDW(STR_RAWDATA *pRawData, STR_FILTER_SETUP *pstFilterSetup );
	virtual ~CEPDW();

	void Alloc( unsigned int nItems=0 );
	void Free();
	void ReadDataHeader() {  }
    void ConvertPDWData( STR_PDWDATA *pPDWData, STR_FILTER_SETUP *pFilterSetup=NULL, bool bSwap=true, ENUM_CONVERT_OPTION enOption=enUnitToPDW );
	void *GetData();
	void *GetHeader() { return (void *) & m_stHeader; }
    unsigned int GetDataItems( unsigned long long ullFileSize );
    unsigned int GetHeaderSize();

	inline unsigned int GetOffsetSize() { return sizeof(int)*4; }

	//inline unsigned int GetHeaderSize() { return sizeof(STR_ELINT_HEADER); }
    inline unsigned int GetOneDataSize() { return sizeof(_PDW); }
    inline void SetHeaderData( void *pData );

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
    static float DecodeTOAus( _TOA uiTOA, ENUM_BANDWIDTH enBandWidth )
    {
        return (float) ( ( (float) uiTOA * ELINT::_toaRes[enBandWidth] ) / (float) 1000000000. );
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

		fVal = FMUL( uiFreq, ELINT::fFreqRes );
		
		return fVal;
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
	static float DecodePW( unsigned int uiPW, ENUM_BANDWIDTH enBandWidth )
	{
		return (float) ( ( (float) uiPW * ELINT::_toaRes[enBandWidth] ) / (float) 1000000000. );
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
		fDOA = (float) ELINT::fDOARes * (float) ( uiDOA % 36000 );
		return fDOA;
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
		return (float) ( ( (float) uiPA * (float) ELINT::fPARes ) - (float) 110. );
	} ;

};


namespace XPDW {
	const float _toaRes[en50MHZ_BW+1] = { (float) 65.104167, (float) 8.138021 } ;
	const float fFreqRes=(float) 0.001;
	const float fDOARes=(float) 0.01;
	const float fPARes=(float) 0.25;
}

class CXPDW : public CData
{
private:
	STR_ELINT_HEADER m_stHeader;

	ENUM_BANDWIDTH m_enBandWidth;

public:
	CXPDW( const char *pRawData, STR_FILTER_SETUP *pstFilterSetup );
	virtual ~CXPDW();

    _COMMON_FUNCTIONS_;

    void MakeHeaderData( STR_PDWDATA *pPDWData );
    void MakePDWData( STR_PDWDATA *pPDWDat, ENUM_CONVERT_OPTION enOption );
    void MakePDWDataByUnitToPDW( STR_PDWDATA *pPDWData );
    inline void UpdateHeaderSize() { GetHeaderSize(); }



    static unsigned int EncodePulseType( int iPulseType )
    {
        unsigned int ipluseType;

        if( iPulseType == 0 ) {
            ipluseType = STAT_NORMAL;
        }
        else {
            ipluseType = STAT_CW;
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
    static float DecodeTOAus( _TOA uiTOA, ENUM_BANDWIDTH enBandWidth )
    {
        return (float) ( ( (float) uiTOA * XPDW::_toaRes[enBandWidth] ) / (float) 1000000000. );
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
    static unsigned int EncodeTOAus( float fTOA, ENUM_BANDWIDTH enBandWidth )
    {
        return (unsigned int) ( ( ( fTOA * (float) 1000. ) / XPDW::_toaRes[enBandWidth] ) + 0.5 );
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

		fVal = FMUL( uiFreq, XPDW::fFreqRes );
		
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

        uiFreq = IDIV( fFreq, XPDW::fFreqRes );

        return uiFreq;
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
	static float DecodePW( unsigned int uiPW, ENUM_BANDWIDTH enBandWidth )
	{
		return (float) ( ( (float) uiPW * XPDW::_toaRes[enBandWidth] ) / (float) 1000000000. );
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
		fDOA = (float) XPDW::fDOARes * (float) ( uiDOA % 36000 );
		return fDOA;
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
		return (float) ( ( (float) uiPA * (float) XPDW::fPARes ) - (float) 110. );
	} ;

    /**
     * @brief DecodeDOA
     * @param iDOA
     * @return
     */
    static unsigned int EncodeDOA(float fDOA )
    {
        return (unsigned int) ( (float) fDOA / XPDW::fDOARes + 0.5 );
    } ;

};

// 701 PDW
class C7PDW : public CData
{
private:
	SRxPDWHeader m_stHeader;
	//STR_PDW_DATA m_PDWData;

public:
	C7PDW(STR_RAWDATA *pRawData, STR_FILTER_SETUP *pstFilterSetup );
	virtual ~C7PDW();

	_COMMON_FUNCTIONS_

	inline unsigned int GetOffsetSize() { return 0; }

};

// KFX PDW
class CKFXPDW : public CData
{
private:
	//STR_PDW_DATA m_PDWData;

public:
	CKFXPDW(STR_RAWDATA *pRawData, STR_FILTER_SETUP *pstFilterSetup );
	virtual ~CKFXPDW();

	void Alloc( unsigned int nItems=0 );
	void Free();
	void ReadDataHeader() {  }
    void ConvertPDWData( STR_PDWDATA *pPDWData, STR_FILTER_SETUP *pFilterSetup=NULL, bool bSwap=true, ENUM_CONVERT_OPTION enOption=enUnitToPDW );
	void *GetData();
	void *GetHeader() { return NULL; }

	inline unsigned int GetOffsetSize() { return 0; }
	inline unsigned int GetHeaderSize() { return 0; }
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

// CPOCKETSONATAPDW PDW
namespace POCKETSONATA {
    #define PH_WIDTH_FREQ		128000
    #define L_PH_MIN_FREQ		64000
    #define H_PH_MIN_FREQ		192000  // [kHz]

    #define PDW_TIME_RES		7.8125  // [ns]

    const float fPDW_FREQ_RES=1.953125;
    //#define PDW_FREQ_RES		(1.953125)
    //#define PDW_AOA_RES			0.087890625

    #define PDW_PA_INIT		    (-89.0)

    const unsigned int uiPDW_CW=1;
    const unsigned int uiPDW_NORMAL=0;

    static const float m_fCenterFreq[enMAXPRC] = { 0, 3072000., 3072000., 3072000., 3072000., 3072000., 3072000. } ;

	#define ONE_MICROSEC		(20)
}


class CPOCKETSONATAPDW : public CData
{
private:
	POCKETSONATA_HEADER m_stHeader;

    //STR_PDW_DATA m_PDWData;

	static int m_iBoardID;

public:
    CPOCKETSONATAPDW( const char *pRawData, STR_FILTER_SETUP *pstFilterSetup, int iBoardID );
    virtual ~CPOCKETSONATAPDW();

    _COMMON_FUNCTIONS_;

    void MakeHeaderData( STR_PDWDATA *pPDWData );
    void MakePDWData( STR_PDWDATA *pPDWData, ENUM_CONVERT_OPTION enOption );
    void MakePDWDataByUnitToPDW( STR_PDWDATA *pPDWData );

	inline unsigned int GetOffsetSize() { return 0; }
    inline void UpdateHeaderSize() { GetHeaderSize(); }

public:
    /**
     * @brief DecodeDOA
     * @param iDOA
     * @return
     */
    static float DecodeDOA(int iDOA )
    {
        float fDOA;

        fDOA = (float) ( (float) iDOA * (float) 360. ) / (float) ( 4.*1024. );
        return fDOA;	/* [degree] */
    } ;

    /**
     * @brief EncodeDOA
     * @param fDOA
     * @return
     */
    static int EncodeDOA( float fDOA )
    {
        int iDOA;

        iDOA = (int) ( ( fDOA * (float) ( 4.*1024. ) / (float) 360. ) + 0.5 );
        return iDOA;
    } ;

    /**
     * @brief DecodePA
     * @param iPA
     * @return
     */
    static float DecodePA(int iPA )
    {
        float fPA;

        fPA = (float) PDW_PA_INIT + FMUL( 20.,  (float) log10( (double) iPA ) );
        return fPA;		/* [dBm] */
    } ;

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
    static float DecodeRealFREQMHz( int iFreq, int iCh, int iBoardID )
    {
        float fFREQ;

        if( iCh < 8 ) {
            if( iFreq & 0x8000 ) {
                fFREQ = POCKETSONATA::m_fCenterFreq[iBoardID] + (float) ( PH_WIDTH_FREQ * iCh ) - (float) ( (float) ( 0x10000 - iFreq ) * POCKETSONATA::fPDW_FREQ_RES);
            }
            else {
                fFREQ = POCKETSONATA::m_fCenterFreq[iBoardID] + (float) ( PH_WIDTH_FREQ * iCh ) + (float) ( (float) iFreq * POCKETSONATA::fPDW_FREQ_RES);      // 1.953125*32767 = 64MHz
            }
        }
        else {
            iCh = 16 - iCh;
            if( iFreq & 0x8000 ) {
                fFREQ = ( ( POCKETSONATA::m_fCenterFreq[iBoardID] ) - ( PH_WIDTH_FREQ * iCh) - ( (float) ( 0x10000 - iFreq ) * POCKETSONATA::fPDW_FREQ_RES ) );
            }
            else {
                fFREQ = ( ( POCKETSONATA::m_fCenterFreq[iBoardID] ) - ( PH_WIDTH_FREQ * iCh) + ( (float) iFreq * POCKETSONATA::fPDW_FREQ_RES ) );
            }
        }

        return fFREQ / (float) 1000.;	/* [MHz] */
    } ;

    /**
     * @brief DecodeFREQMHz
     * @param iFreqHz
     * @return
     */
    static float DecodeFREQMHz( int iFreq )
    {
        float fRetFreq;

        fRetFreq = ( (float) iFreq * POCKETSONATA::fPDW_FREQ_RES / (float) 1000. );
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
    static bool EncodeRealFREQMHz( int *piFreq, int *piCh, int iBoardID, float fFreq )
    {
        bool bRet=true;
        float fFREQ;
        
        fFREQ = ( fFreq * (float) 1000. ) - ( POCKETSONATA::m_fCenterFreq[iBoardID] - 64000 );

        if( fFREQ < 0. ) {
            fFREQ += 1024000.0;
            *piCh = (int) ( (float) fFREQ / (float) 128000. );    

            if( fFREQ - ( *piCh * 128000 ) >= 64000 ) {
                *piFreq = IDIV( ( fFREQ - (float) ( *piCh * 128000 ) - (float) 64000. ), POCKETSONATA::fPDW_FREQ_RES );
            }
            else {
                *piFreq = IDIV( ( fFREQ - (float) ( *piCh * 128000 ) ), POCKETSONATA::fPDW_FREQ_RES ) + 32768;
            }

            *piCh += 8;
        }
        else {
            *piCh = (int) ( (float) fFREQ / (float) 128000. );    

            if( fFREQ - ( *piCh * 128000 ) >= 64000 ) {
                *piFreq = IDIV( ( fFREQ - (float) ( *piCh * 128000 ) - (float) 64000. ), POCKETSONATA::fPDW_FREQ_RES );
            }
            else {
                *piFreq = IDIV( ( fFREQ - (float) ( *piCh * 128000 ) ), POCKETSONATA::fPDW_FREQ_RES ) + 32768;
            }

        }

        return bRet;
    } ;

    static bool EncodeRealFREQMHz( int *piFreq, int *piCh, float fFreq )
    {
        bool bRet=true;
        float fFREQ;

        fFREQ = ( fFreq * (float) 1000. ) - ( POCKETSONATA::m_fCenterFreq[CPOCKETSONATAPDW::m_iBoardID] - 64000 );

        if( fFREQ < 0. ) {
            fFREQ += 1024000.0;
            *piCh = (int) ( (float) fFREQ / (float) 128000. );    

            if( fFREQ - ( *piCh * 128000 ) >= 64000 ) {
                *piFreq = IDIV( ( fFREQ - (float) ( *piCh * 128000 ) - (float) 64000. ), POCKETSONATA::fPDW_FREQ_RES );
            }
            else {
                *piFreq = IDIV( ( fFREQ - (float) ( *piCh * 128000 ) ), POCKETSONATA::fPDW_FREQ_RES ) + 32768;
            }

            *piCh += 8;
        }
        else {
            *piCh = (int) ( (float) fFREQ / (float) 128000. );    

            if( fFREQ - ( *piCh * 128000 ) >= 64000 ) {
                *piFreq = IDIV( ( fFREQ - (float) ( *piCh * 128000 ) - (float) 64000. ), POCKETSONATA::fPDW_FREQ_RES );
            }
            else {
                *piFreq = IDIV( ( fFREQ - (float) ( *piCh * 128000 ) ), POCKETSONATA::fPDW_FREQ_RES ) + 32768;
            }

        }

        return bRet;
    } ;

    /**
     * @brief DecodeFREQMHz
     * @param iFreqHz
     * @return
     */
    static float EncodeFREQMHz( float fFreq )
    {
        float fRetFreq;

        fRetFreq = ( ( fFreq * (float) 1000. ) / POCKETSONATA::fPDW_FREQ_RES );
        return fRetFreq;	/* [MHz] */
    } ;

    /**
     * @brief EncodeFREQMHzFloor
     * @param fFreq
     * @return
     */
    static int EncodeFREQMHzFloor( float fFreq )
    {
        float fRetFreq;

        fRetFreq = ( ( (float) fFreq * (float) 1000. ) / POCKETSONATA::fPDW_FREQ_RES );
        return (int) fRetFreq;	/* [MHz] */
    } ;

    static int EncodeFREQMHzCeiling( float fFreq )
    {
        float fRetFreq;

        fRetFreq = ( ( (float) fFreq * (float) 1000. ) / POCKETSONATA::fPDW_FREQ_RES );
        return (int) ( fRetFreq + 0.5 );	/* [MHz] */
    } ;


    static int DecodeFREQ( int iFreq )
    {
        float fFreq;

        fFreq = (float) iFreq * POCKETSONATA::fPDW_FREQ_RES;
        return (int) ( fFreq + 0.5 );	/* [kHz] */
    } ;

    /**
     * @brief DecodePW
     * @param iPW
     * @return
     */
    static float DecodePW( int iPW )
    {
        float fPW;

        fPW = (float) ( (float) iPW * (float) PDW_TIME_RES / (float) 1.0 );
        return fPW;		/* [ns] */
    } ;

    /**
     * @brief DecodePWus
     * @param iPW
     * @return
     */
    static float DecodePWus( int iPW )
    {
        float fretPW;

        fretPW = (float) iPW * (float) PDW_TIME_RES;
        fretPW = ( fretPW / (float) 1000. );
        return fretPW;
    } ;

    static float DecodePWns( int iPW )
    {
        float fretPW;

        fretPW = (float) iPW * (float) PDW_TIME_RES;
        fretPW = ( fretPW / (float) 1000000. );
        return fretPW;
    } ;

    static int EncodePWFloor( float fPW )
    {
        float fretPW;

        fretPW = fPW * (float) 1000.;
        fretPW = fretPW / (float) PDW_TIME_RES;
        return (int) fretPW;
    } ;

    static int EncodePWCeiling( float fPW )
    {
        float fretPW;

        fretPW = fPW * (float) 1000.;
        fretPW = fretPW / (float) PDW_TIME_RES;
        return (int) ( fretPW + 0.5 );
    } ;

    /**
     * @brief DecodeTOA
     * @param iTOA
     * @return
     */
    static float DecodeTOA( _TOA iTOA  )
    {
        long double dTOA;

        iTOA = iTOA & 0xFFFFFFFFFFF;

        dTOA = (long double) ( (long double) iTOA * (long double) PDW_TIME_RES / (long double) 1.0 );
        return (float) dTOA;	/* [ns] */
    } ;

    static double DblDecodeTOA( _TOA iTOA  )
    {
        double dTOA;

        iTOA = iTOA & 0xFFFFFFFFFFF;

        dTOA = (double) ( (double) iTOA * (double) PDW_TIME_RES / (double) 1.0 );
        return dTOA;	/* [ns] */
    } ;

    /**
     * @brief DecodeTOAus
     * @param iTOA
     * @return
     */
    static float DecodeTOAus( _TOA iTOA  )
    {
        float fretTOA;

        iTOA = iTOA & 0xFFFFFFFFFFF;

        fretTOA = ( (float) iTOA * (float) PDW_TIME_RES / (float) 1000. );
        return fretTOA;	/* [us] */
    } ;

    /**
     * @brief DecodeTOAms
     * @param iTOA
     * @return
     */
    static float DecodeTOAms( _TOA iTOA  )
    {
        float fretTOA;

        iTOA = iTOA & 0xFFFFFFFFFFF;

        fretTOA = ( (float) iTOA * (float) PDW_TIME_RES / (float) 1000000. );
        return fretTOA;	/* [ms] */
    } ;

    /**
     * @brief EncodeTOAus
     * @param iTOA
     * @return
     */
    static _TOA EncodeTOAus( _TOA iTOA  )
    {
        _TOA iretTOA;

        iretTOA = (_TOA) ( ( ( (float) iTOA * (float) 1000.0 ) / (float) PDW_TIME_RES ) + 0.5 );
        return iretTOA;	/* [ns] */
    } ;

    /**
     * @brief     
     * @param     float fTOA
     * @return    _TOA
     * @author    議곗쿋??(churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022/01/09 12:59:01
     * @warning   
     */
    static _TOA EncodeTOAus( float fTOA  )
    {
        _TOA iretTOA;

        iretTOA = (_TOA) ( ( ( fTOA * (float) 1000.0 ) / (float) PDW_TIME_RES ) + 0.5 );
        return iretTOA;	/* [ns] */
    } ;

    /**
     * @brief DecodeTOAs
     * @param iTOA
     * @return
     */
    static int DecodeTOAs( _TOA iTOA  )
    {
        int iretTOA;

        iretTOA = (int) ( ( (float) iTOA * (float) 1000000. * (float) PDW_TIME_RES ) + 0.5 );
        return iretTOA;	/* [ns] */
    } ;

    /**
     * @brief DecodeTOA
     * @param ffTOA
     * @return
     */
    static float DecodeTOA( float ffTOA )
    {
        float fTOA;

        fTOA = (float) ( (float) ffTOA * (float) PDW_TIME_RES / (float) 1000.0 );
        return fTOA;	/* [ns] */
    } ;

    static bool Test()
    {
        bool bRet=true;

        int i, j;
        int iFreq, iCh;
        int iDFreq, iDCh;
        float fFreq;

        for( i=0 ; i < 15 ; ++i ) {
            for( j=0 ; j < 0xFFFF ; ++j ) {
                iDFreq = j;
                iDCh = i;
                fFreq = CPOCKETSONATAPDW::DecodeRealFREQMHz( iDFreq, iDCh, 3 );
                CPOCKETSONATAPDW::EncodeRealFREQMHz( & iFreq, & iCh, 3, fFreq );
                if( iDFreq == iFreq && iDCh == iCh ) {
                }
                else {
                    fFreq = CPOCKETSONATAPDW::DecodeRealFREQMHz( iDFreq, iDCh, 3 );
                    CPOCKETSONATAPDW::EncodeRealFREQMHz( & iFreq, & iCh, 3, fFreq );
                    bRet = false;
                }

                iDFreq = j;
                iDCh = i;
                fFreq = CPOCKETSONATAPDW::DecodeRealFREQMHz( iDFreq, iDCh, 3 );
                CPOCKETSONATAPDW::EncodeRealFREQMHz( & iFreq, & iCh, 3, fFreq );
                if( iDFreq == iFreq && iDCh == iCh ) {
                }
                else {
                    fFreq = CPOCKETSONATAPDW::DecodeRealFREQMHz( iDFreq, iDCh, 3 );
                    CPOCKETSONATAPDW::EncodeRealFREQMHz( & iFreq, & iCh, 3, fFreq );
                    bRet = false;
                }
            }
        }

        return bRet;
    }


};

class CIQ : public CData
{
private:
	STR_IQ_HEADER m_IQHeader;
	STR_IQ_DATA m_IQData;

public:
	CIQ(STR_RAWDATA *pRawData);
	virtual ~CIQ();

	void Alloc( unsigned int nItems=0 );
	void Free();
	void ReadDataHeader();
    void ConvertPDWData( STR_PDWDATA *pPDWData, STR_FILTER_SETUP *pFilterSetup=NULL, bool bSwap=true, ENUM_CONVERT_OPTION enOption=enUnitToPDW );
	void *GetData();
	void *GetHeader();

	inline unsigned int GetOffsetSize() { return 0; }
	inline unsigned int GetHeaderSize() { return 0; }
    inline unsigned int GetOneDataSize() { return 0; }
	inline unsigned int GetDataItems( unsigned long long ullFileSize ) { return 0; }
    inline void SetHeaderData( void *pData ) { return; }

};

// 701 IQ
class C7IQ : public CData
{
private:
	STR_IQ_DATA m_IQData;

public:
    C7IQ(STR_RAWDATA *pRawData, STR_FILTER_SETUP *pFilterSetup );
	virtual ~C7IQ();

	void Alloc( unsigned int iItems=0 );
	void Free();
	void ReadDataHeader() {  }
    void ConvertPDWData( STR_PDWDATA *pPDWData, STR_FILTER_SETUP *pFilterSetup=NULL, bool bSwap=true, ENUM_CONVERT_OPTION enOption=enUnitToPDW );
	void *GetData();
	void *GetHeader() { return NULL; }

	inline unsigned int GetOffsetSize() { return 0; }
	inline unsigned int GetHeaderSize() { return 0; }
    inline unsigned int GetOneDataSize() { return 0; }
	inline unsigned int GetDataItems( unsigned long long ullFileSize ) { return 0; }
    
    inline void SetHeaderData( void *pData ) { return; }
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

// union UNI_ADJUNCT_TYPE {
// 	SELMIDAS_ADJUNCT_TYPE_1000 _1000;
// 	SELMIDAS_ADJUNCT_TYPE_2000 _2000;
// 	SELMIDAS_ADJUNCT_TYPE_6000 _6000;
// };

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
	void GetSubRecords( S_EL_PDW_RECORDS *pPDWRecords );
	double GetSubValue( char *psubformat );

	inline unsigned int GetOffsetSize() { return 0; }

};

#ifndef __VXWORKS__
//////////////////////////////////////////////////////////////////////////
class CMapData {
private:
	bool m_bMapData;

	static map<CString, CData *> m_gMapData;

public:
	CMapData(void)
	{

	}

	virtual ~CMapData(void)
	{

	}

	void IncWindowNumber( CData *pData )
	{
		++ pData->m_uiWindowNumber;
	}

	void AddMapData( CString *pStrPathName, CData *pData )
	{
#ifdef __linux__
#elif defined(_MSC_VER)
        //Log( enNormal, _T("\n MapData()에 경로명[%s]을 추가했습니다.") , *pStrPathName );
#else

#endif
        
		m_gMapData.insert( make_pair( *pStrPathName, pData ) );
	}

	CData *FindMapData( CString *pStrPathName )
	{
		CData *pData;
		map<CString, CData *>::iterator it;

		it = m_gMapData.find( *pStrPathName );
		if( it == m_gMapData.end() ) {
			pData = NULL;
		}
		else {
			pData = it->second;

			// 데이터 ID 증가
			//++ pData->m_uiLoadFile;
		}

		return pData;
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
			CData *pData;

			while( it != m_gMapData.end() ) {
                if( pStrWindowTitle->Compare( it->first ) == 0 ) {
					pData = it->second;

					if( pData->m_uiWindowNumber == 0 ) {
						delete it->second;
						m_gMapData.erase( it++ );
					}
					else {
						++ it;

						// 데이터 ID 감소
						-- pData->m_uiWindowNumber;
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

class CDataFile
{
private:
	int m_iFileIndex;

    char m_szPathname[500];

	CRawFile m_RawDataFile;
	CData *m_pData;

public:
	

public:
	CDataFile(void);
	virtual ~CDataFile(void);

    void ConvertArray( STR_PDWDATA *pPDWData, bool bSwap, STR_FILTER_SETUP *pFilterSetup, bool bConvert );
    void ReadDataMemory( STR_PDWDATA *pPDWData, const char *pstData, char *pstPathname, STR_FILTER_SETUP *pstFilterSetup=NULL, ENUM_CONVERT_OPTION enOption=enUnitToPDW );
	CData *ReadDataFile( STR_PDWDATA *pPDWData, char *pPathname, int iFileIndex=-1, CData *pData=NULL, STR_FILTER_SETUP *pstFilterSetup=NULL, bool bConvert=true );
	UINT LoadRawData( STR_PDWDATA *pPDWData, int iFileIndex, bool bConvert=true );
    void SaveDataFile( char *pstPathname, void *pData, int iNumData, ENUM_UnitType enUnitType, ENUM_DataType enDataType, void *pDataEtc=NULL, int iSizeOfEtc=0 );
	void Alloc();
	void Free();
	void *GetData();
	void *GetHeader();
	void SetData( CData *pData );

	// 파일 읽기 관련 함수
	void ReadDataHeader();
	void ReadDataAll( CData *pData );

	ENUM_DataType WhatDataType( char *pStrPathname );
	ENUM_UnitType WhatUnitType( char *pStrPathname );

	unsigned int GetHeaderSize( CData *pData );
	unsigned int GetOneDataSize( CData *pData );
	unsigned int GetDataItems( CData *pData );

    void BypassArrayData( STR_PDWDATA *pPDWData );

	inline int GetFileIndex() { return m_iFileIndex; }

	inline UINT GetDataItems() { if( m_pData != NULL ) return m_pData->m_PDWData.uiDataItems; else return 0; }
	inline ENUM_UnitType GetUnitType() { return m_pData->m_enUnitType; }
	inline ENUM_DataType GetDataType() { return m_pData->m_enDataType; }
	inline UINT GetWindowNumber() { if( m_pData != NULL ) return m_pData->m_uiWindowNumber; else return 0; }
	inline CData *GetRawData() { if( m_pData != NULL ) return m_pData; else return NULL; }
	inline STR_FILTER_SETUP *GetFilterSetup() { return & m_pData->m_strFilterSetup; }
	inline void ClearFilterSetup() { m_pData->ClearFilterSetup(); }
	inline UINT GetFilteredDataItems() { STR_PDW_DATA *pPDWData=(STR_PDW_DATA *) m_pData->GetData(); return pPDWData->uiDataItems; }

    //inline STR_PDWDATA { if( m_pData != NULL ) return m_pData->m_PDWData; else return NULL; }
	
private:
	
	
};

