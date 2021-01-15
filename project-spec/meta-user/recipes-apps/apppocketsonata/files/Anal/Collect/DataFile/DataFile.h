#pragma once

#include <stdio.h>

#include "../../INC/system.h"

#include "../../../Anal/OFP_Main.h"

#include "../../../Anal/MIDAS/RawFile.h"

#include "../../../Anal/MIDAS/PDWIQ.h"

#ifdef _FFTW_
#include "../../../FFTW/fftw3.h"
#endif

#include "../../../Anal/MIDAS/Midas.h"

//#include "../../Log/LogDebug.h"

#define			PDW_ITEMS						(1024*128)			// 9437164
#define			IQ_ITEMS						(1024*128)

//#define			MAX_RAWDATA_SIZE				(4000000)	// 2,432,052
#define			MAX_RAWDATA_SIZE				_max( (sizeof(SRxPDWHeader) + sizeof(SRxPDWDataRGroup)*PDW_ITEMS), sizeof(TNEW_IQ)*IQ_ITEMS )	// 2,432,052

#define			MAX_HEADER_SIZE					_max( HEADER_CONTROL_BLOCK_SIZE, 100 )


//#define			INIT_VAL			(-1.0)


typedef enum {
	enUnselectedSubGraph = -1,

	enSubMenu_1 = 1,
	enSubMenu_2,
	enSubMenu_3,
	enSubMenu_4,
	enSubMenu_5,
	enSubMenu_6,


} ENUM_SUB_GRAPH ;

typedef enum {
	en_UnknownData = 0,

	en_PDW_DATA,
	en_IQ_DATA,
	en_IF_DATA,

} ENUM_DataType;

typedef enum {
	en_UnknownUnit = 0,

	en_SONATA,
	en_SONATA_SHU,
	en_ELINT,
	en_701,
    en_KFX,
    en_ZPOCKETSONATA,

	en_MIDAS,

} ENUM_UnitType;

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

	UINT uiDataItems;
	ENUM_DataType enDataType;
	ENUM_UnitType enUnitType;
    char szFileName[_MAX_PATH];

} ;

typedef unsigned long long int _TOA;

struct STR_PDW_DATA {
	int iDataItems;

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
	double dToaMin;
	double dToaMax;
	double dDtoaMin;
	double dDtoaMax;
	double dAoaMin;
	double dAoaMax;
	double dFrqMin;
	double dFrqMax;
	double dPAMin;
	double dPAMax;
	double dPWMin;
	double dPWMax;

	ENUM_SUB_GRAPH enSubGraph;

} ;

typedef struct {
	double dZoomMinX;
	double dZoomMaxX;
	double dZoomMinY;
	double dZoomMaxY;

	ENUM_SUB_GRAPH enSubGraph;

} STR_ZOOM_INFO;


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
#define _COMMON_FUNCTIONS_		\
	void Alloc( int iItems=0 );	\
	void Free();	\
	void ReadDataHeader();  \
    void ConvertArray( STR_PDWDATA *pPDWData, bool bSwap=true, STR_FILTER_SETUP *pFilterSetup=NULL );	\
	void ConvertArrayForELINT() { }	\
	void *GetData();	\
	void *GetHeader() { return NULL; }	\
	unsigned int GetHeaderSize();	\
    unsigned int GetOneDataSize();	\
	unsigned int GetDataItems();


class CData
{
public:
    char *m_pRawHeaderBuffer;
    char *m_pRawDataBuffer;

    int m_iHeaderSize;
    int m_iOneDataSize;

public:
    STR_RAWDATA m_RawData;

    UINT m_uiWindowNumber;

    UINT m_uiLengthOfHeader;

    bool m_bPhaseData;

    STR_FILTER_SETUP m_strFilterSetup;

    _TOA m_ll1stToa;

    float _spOneSec;
    float _spOneMilli;
    float _spOneMicrosec;
    float _spOneNanosec;

    float _spAMPres;
    float _spPWres;
    float _spAOAres;

public:
    void ClearFilterSetup();
    void swapByteOrder(unsigned int& ui);
    void swapByteOrder(unsigned long long& ull);
    void AllSwapData32( void *pData, int iLength );
    void ExecuteFFT( int iDataItems, STR_IQ_DATA *pIQData );

public:
    CData(STR_RAWDATA *pRawData);
    virtual ~CData();

    virtual void Alloc( int nItems=0 )=0;
    virtual void Free()=0;
    virtual void ReadDataHeader() = 0;
    virtual void ConvertArray( STR_PDWDATA *pPDWData, bool bSwap=true, STR_FILTER_SETUP *pFilterSetup=NULL ) = 0;
    virtual void *GetData() = 0;
    virtual void *GetHeader() = 0;

    virtual unsigned int GetHeaderSize() = 0;
    virtual unsigned int GetOneDataSize() = 0;
    virtual unsigned int GetDataItems() = 0;
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

class CPDW : public CData
{
private:
	STR_PDW_DATA m_PDWData;

public:
	CPDW(STR_RAWDATA *pRawData);
	virtual ~CPDW();

	void Alloc( int nItems=0 );
	void Free();
	void ReadDataHeader() {  }
    void ConvertArray( STR_PDWDATA *pPDWData, bool bSwap=true, STR_FILTER_SETUP *pFilterSetup=NULL );
	void *GetData();
	void *GetHeader() { return NULL; }

	inline unsigned int GetHeaderSize() { return 0; }
    inline unsigned int GetOneDataSize() { return 0; }
	inline unsigned int GetDataItems() { return 0; }

public:
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
	STR_PDW_DATA m_PDWData;

public:
	CSPDW(STR_RAWDATA *pRawData);
	virtual ~CSPDW();

	void Alloc( int nItems=0 );
	void Free();
	void ReadDataHeader() {  }
    void ConvertArray( STR_PDWDATA *pPDWData, bool bSwap=true, STR_FILTER_SETUP *pFilterSetup=NULL );
	void *GetData();
	void *GetHeader() { return NULL; }

	inline unsigned int GetHeaderSize() { return 0; }
    inline unsigned int GetOneDataSize() { return 0; }
	inline unsigned int GetDataItems() { return 0; }

};

namespace ELINT {
	const unsigned int uiPDW_CW=0;
	const unsigned int uiPDW_NORMAL=1;
	const unsigned int uiPDW_DV=1;
}

// 인천공항 PDW
class CEPDW : public CData
{
private:
	STR_PDW_DATA m_PDWData;

	ENUM_BANDWIDTH m_enBandWidth;

public:
	CEPDW(STR_RAWDATA *pRawData, STR_FILTER_SETUP *pstFilterSetup );
	virtual ~CEPDW();

	void Alloc( int nItems=0 );
	void Free();
	void ReadDataHeader() {  }
    void ConvertArray( STR_PDWDATA *pPDWData, bool bSwap=true, STR_FILTER_SETUP *pFilterSetup=NULL );
	void *GetData();
	void *GetHeader() { return NULL; }

	inline unsigned int GetHeaderSize() { return 0; }
    inline unsigned int GetOneDataSize() { return 0; }
	inline unsigned int GetDataItems() { return 0; }

};

// 701 PDW
class C7PDW : public CData
{
private:
	SRxPDWHeader m_stHeader;
	STR_PDW_DATA m_PDWData;

public:
	C7PDW(STR_RAWDATA *pRawData, STR_FILTER_SETUP *pstFilterSetup );
	virtual ~C7PDW();

	_COMMON_FUNCTIONS_

};

// KFX PDW
class CKFXPDW : public CData
{
private:
	STR_PDW_DATA m_PDWData;

public:
	CKFXPDW(STR_RAWDATA *pRawData, STR_FILTER_SETUP *pstFilterSetup );
	virtual ~CKFXPDW();

	void Alloc( int nItems=0 );
	void Free();
	void ReadDataHeader() {  }
    void ConvertArray( STR_PDWDATA *pPDWData, bool bSwap=true, STR_FILTER_SETUP *pFilterSetup=NULL );
	void *GetData();
	void *GetHeader() { return NULL; }

	inline unsigned int GetHeaderSize() { return 0; }
    inline unsigned int GetOneDataSize() { return 0; }
	inline unsigned int GetDataItems() { return 0; }

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
    #define PDW_FREQ_RES		(1.953125)
    //#define PDW_AOA_RES			0.087890625

    static const float m_fCenterFreq[enPRC6] = { 3072000., 3072000., 3072000., 3072000., 3072000., 3072000. } ;
}


class CPOCKETSONATAPDW : public CData
{
private:
	STR_PDWFILE_HEADER m_stHeader;

    STR_PDW_DATA m_PDWData;

	int m_iBoardID;

public:
    CPOCKETSONATAPDW(STR_RAWDATA *pRawData, STR_FILTER_SETUP *pstFilterSetup, int iBoardID );
    virtual ~CPOCKETSONATAPDW();

    _COMMON_FUNCTIONS_;

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

        fPA = (float) iPA;
        return fPA;		/* [dBm] */
    } ;

    /**
     * @brief DecodeFREQ
     * @param iFreq
     * @param iCh
     * @param iBoardID
     * @return
     */
    static float DecodeFREQ( int iFreq, int iCh, int iBoardID )
    {
        float fFREQ;

        if( iCh < 7 ) {
            fFREQ = (( POCKETSONATA::m_fCenterFreq[iBoardID] - (float) L_PH_MIN_FREQ) + ( PH_WIDTH_FREQ * iCh ) + ( (float) iFreq * (float) PDW_FREQ_RES) );
        }
        else {
            iCh = 15 - iCh;
            fFREQ = ( ( POCKETSONATA::m_fCenterFreq[iBoardID] - H_PH_MIN_FREQ) - ( PH_WIDTH_FREQ * iCh) + ( (float) iFreq * (float) PDW_FREQ_RES ) );
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
        float fFreq;

        fFreq = ( (float) iFreq * (float) PDW_FREQ_RES / (float) 1000. );
        return fFreq;	/* [MHz] */
    } ;

    static int EncodeFREQMHzFloor( float fFreq )
    {
        float fRetFreq;

        fRetFreq = ( ( (float) fFreq * (float) 1000. ) / (float) PDW_FREQ_RES );
        return (int) fRetFreq;	/* [MHz] */
    } ;

    static int EncodeFREQMHzCeiling( float fFreq )
    {
        float fRetFreq;

        fRetFreq = ( ( (float) fFreq * (float) 1000. ) / (float) PDW_FREQ_RES );
        return (int) ( fRetFreq + 0.5 );	/* [MHz] */
    } ;


    static int DecodeFREQ( int iFreq )
    {
        float fFreq;

        fFreq = (float) iFreq * (float) PDW_FREQ_RES;
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

        fretPW = (float) ( (float) iPW * (float) PDW_TIME_RES / (float) 1000. + 0.5 );
        return fretPW;
    } ;

    static float DecodePWns( int iPW )
    {
        float fretPW;

        fretPW = (float) ( (float) iPW * (float) PDW_TIME_RES / (float) 1000000. + 0.5 );
        return fretPW;
    } ;

    static int EncodePWFloor( float fPW )
    {
        float fretPW;

        fretPW = (float) ( (float) fPW * (float) 1. / (float) PDW_TIME_RES );
        return (int) fretPW;
    } ;

    static int EncodePWCeiling( float fPW )
    {
        float fretPW;

        fretPW = (float) ( (float) fPW * (float) 1. / (float) PDW_TIME_RES );
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
    static int EncodeTOAus( _TOA iTOA  )
    {
        int iretTOA;

        iretTOA = (int) ( ( ( (float) iTOA * (float) 1000.0 ) / (float) PDW_TIME_RES ) + 0.5 );
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

};

class CIQ : public CData
{
private:
	STR_IQ_HEADER m_IQHeader;
	STR_IQ_DATA m_IQData;

public:
	CIQ(STR_RAWDATA *pRawData);
	virtual ~CIQ();

	void Alloc( int nItems=0 );
	void Free();
	void ReadDataHeader();
    void ConvertArray( STR_PDWDATA *pPDWData, bool bSwap=false, STR_FILTER_SETUP *pFilterSetup=NULL );
	void *GetData();
	void *GetHeader();

	inline unsigned int GetHeaderSize() { return 0; }
    inline unsigned int GetOneDataSize() { return 0; }
	inline unsigned int GetDataItems() { return 0; }

};

// 701 IQ
class C7IQ : public CData
{
private:
	STR_IQ_DATA m_IQData;

public:
    C7IQ(STR_RAWDATA *pRawData, STR_FILTER_SETUP *pFilterSetup );
	virtual ~C7IQ();

	void Alloc( int iItems=0 );
	void Free();
	void ReadDataHeader() {  }
    void ConvertArray( STR_PDWDATA *pPDWData, bool bSwap=true, STR_FILTER_SETUP *pFilterSetup=NULL );
	void *GetData();
	void *GetHeader() { return NULL; }

	inline unsigned int GetHeaderSize() { return 0; }
    inline unsigned int GetOneDataSize() { return 0; }
	inline unsigned int GetDataItems() { return 0; }
};

class CEIQ : public CData
{
private:
	STR_IQ_DATA m_IQData;

public:
	CEIQ(STR_RAWDATA *pRawData);
	virtual ~CEIQ();

	_COMMON_FUNCTIONS_;

};

union UNI_ADJUNCT_TYPE {
	SELMIDAS_ADJUNCT_TYPE_1000 _1000;
	SELMIDAS_ADJUNCT_TYPE_2000 _2000;
	SELMIDAS_ADJUNCT_TYPE_6000 _6000;
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

	STR_PDW_DATA m_PDWData;

	char *m_pDataChar;

public:
	CMIDAS(STR_RAWDATA *pRawData);
	virtual ~CMIDAS();

	_COMMON_FUNCTIONS_;

	int GetDataFormatSize( char ch );
	void GetSubRecords( S_EL_PDW_RECORDS *pPDWRecords );
	double GetSubValue( char *psubformat );

};

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
        Log( enNormal, _T("\n MapData()에 경로명[%s]을 추가했습니다.") , *pStrPathName );
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

class CDataFile
{
private:
	int m_iFileIndex;
	//ULONGLONG m_dwFileEnd;

	CRawFile m_RawDataFile;

	CData *m_pData;

	char m_szPathname[500];

public:
	

public:
	CDataFile(void);
	virtual ~CDataFile(void);

    void ReadDataMemory( STR_PDWDATA *pPDWData, const char *pstData, char *pstPathname, STR_FILTER_SETUP *pstFilterSetup=NULL );
	CData *ReadDataFile( char *pPathname, int iFileIndex, CData *pData, STR_FILTER_SETUP *pstFilterSetup );
	UINT LoadRawData( CData *pData, int iFileIndex );
    void SaveDataFile( char *pstPathname, void *pData, int iNumData, ENUM_UnitType enUnitType, ENUM_DataType enDataType, void *pDataEtc=NULL, int iSizeOfEtc=0 );
	void Alloc();
	void Free();
	void *GetData();
	void *GetHeader();
	void SetData( CData *pData );

	// 파일 읽기 관련 함수
	void ReadDataHeader( CData *pData );
	void ReadDataAll( CData *pData );

	ENUM_DataType WhatDataType( char *pStrPathname );
	ENUM_UnitType WhatUnitType( char *pStrPathname );

	unsigned int GetHeaderSize( CData *pData );
	unsigned int GetOneDataSize( CData *pData );
	unsigned int GetDataItems( CData *pData );


	inline int GetFileIndex() { return m_iFileIndex; }

	inline UINT GetDataItems() { if( m_pData != NULL ) return m_pData->m_RawData.uiDataItems; else return 0; }
	inline ENUM_UnitType GetUnitType() { return m_pData->m_RawData.enUnitType; }
	inline ENUM_DataType GetDataType() { return m_pData->m_RawData.enDataType; }
	inline UINT GetWindowNumber() { if( m_pData != NULL ) return m_pData->m_uiWindowNumber; else return 0; }
	inline CData *GetRawData() { if( m_pData != NULL ) return m_pData; else return NULL; }
	inline STR_FILTER_SETUP *GetFilterSetup() { return & m_pData->m_strFilterSetup; }
	inline void ClearFilterSetup() { m_pData->ClearFilterSetup(); }
	inline UINT GetFilteredDataItems() { STR_PDW_DATA *pPDWData=(STR_PDW_DATA *) m_pData->GetData(); return pPDWData->iDataItems; }
	
	inline bool IsPhaseData() { return m_pData->m_bPhaseData; }
	
private:
	
	
};

