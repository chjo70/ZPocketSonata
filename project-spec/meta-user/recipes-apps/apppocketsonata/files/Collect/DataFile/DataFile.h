#pragma once

#include <stdio.h>

#include "../../Include/system.h"

#include "_iq.h"
#include "../../Anal/INC/PDW.h"

#include "../../Anal/OFP_Main.h"




#include "../../Utils/cfile.h"

//#include "../FFTW/fftw3.h"

#define			MAX_RAWDATA_SIZE				(4000000)	// 2,432,052

typedef enum {
	en_UnknownData = 0,

	en_PDW_DATA,
	en_IQ_DATA

} ENUM_DataType;

typedef enum {
	en_UnknownUnit = 0,

	en_SONATA,
	en_ELINT,
	en_701,
    en_KFX,
    enPOCKETSONATA

} ENUM_UnitType;

#define MAX_SONATA_DATA		(10000)
typedef union {
	TNEW_PDW stPDWData[MAX_SONATA_DATA];
	TNEW_IQ stIQData[MAX_SONATA_DATA];

} UNI_SONATA_DATA;

struct STR_SONATA_DATA {
	UINT uiItem;
	ENUM_DataType enDataType;

	UNI_SONATA_DATA unRawData;

} ;


struct STR_RAWDATA {
	UINT uiByte;
	void *pDataBuffer;

	UINT uiDataItems;
	ENUM_DataType enDataType;
	ENUM_UnitType enUnitType;
	char szFileName[MAX_PATH];

} ;

typedef unsigned long long int _TOA;

struct STR_PDW_DATA {
	float *pfFreq;			// [KHz]
	float *pfPW;			// [ns]
	float *pfAOA;			// [degree]
	float *pfTOA;
	float *pfPA;
	float *pfDTOA;

	_TOA *pfllTOA;

	char *pcType;			// [신호형태]
	char *pcDV;				// [DV]

	float *pfPh1;
	float *pfPh2;
	float *pfPh3;
	float *pfPh4;

}  ;

struct STR_IQ_DATA {
	float *pfI;
	float *pfQ;
	float *pfPA;
	float *pfIP;
	float *pfFFT;

} ;

struct STR_FILTER_SETUP {
	double dToaMin;
	double dToaMax;
	double dAoaMin;
	double dAoaMax;
	double dFrqMin;
	double dFrqMax;
	double dPaMin;
	double dPaMax;

} ;



class CData
{
public:
	STR_RAWDATA *m_pRawData;

	UINT m_uiWindowNumber;

	bool m_bPhaseData;

    STR_FILTER_SETUP m_strFilterSetup;

    float _spOneSec;
    float _spOneMilli;
    float _spOneMicrosec;
    float _spOneNanosec;

    float _spAMPres;
    float _spPWres;
    float _spAOAres;

public:
	void swapByteOrder(unsigned int& ui);
	void swapByteOrder(unsigned long long& ull);
	void AllSwapData32( void *pData, int iLength );

public:
	CData(STR_RAWDATA *pRawData);
	virtual ~CData();

	virtual void Alloc()=0;
	virtual void Free()=0;
    virtual void ConvertArray( STR_PDWDATA *pPDWData=NULL ) = 0;
	virtual void *GetData() = 0;
};

class CPDW : public CData
{
private:
	STR_PDW_DATA m_PDWData;

public:
	CPDW(STR_RAWDATA *pRawData);
	virtual ~CPDW();

	void Alloc();
	void Free();
    void ConvertArray( STR_PDWDATA *pPDWData=NULL );
	void *GetData();

};

// 수퍼헷 PDW 데이터
class CSPDW : public CData
{
private:
	STR_PDW_DATA m_PDWData;

public:
	CSPDW(STR_RAWDATA *pRawData);
	virtual ~CSPDW();

	void Alloc();
	void Free();
    void ConvertArray( STR_PDWDATA *pPDWData=NULL );
	void *GetData();

};

// 인천공항 PDW
class CEPDW : public CData
{
private:
	STR_PDW_DATA m_PDWData;

public:
	CEPDW(STR_RAWDATA *pRawData, STR_FILTER_SETUP *pstFilterSetup );
	virtual ~CEPDW();

	void Alloc();
	void Free();
    void ConvertArray( STR_PDWDATA *pPDWData=NULL );
	void *GetData();

};

// 701 PDW
class C7PDW : public CData
{
private:
	STR_PDW_DATA m_PDWData;

public:
	C7PDW(STR_RAWDATA *pRawData, STR_FILTER_SETUP *pstFilterSetup );
	virtual ~C7PDW();

	void Alloc();
	void Free();
    void ConvertArray( STR_PDWDATA *pPDWData=NULL );
	void *GetData();

};

// KFX PDW
class CKFXPDW : public CData
{
private:
	STR_PDW_DATA m_PDWData;

public:
	CKFXPDW(STR_RAWDATA *pRawData, STR_FILTER_SETUP *pstFilterSetup );
	virtual ~CKFXPDW();

	void Alloc();
	void Free();
    void ConvertArray( STR_PDWDATA *pPDWData=NULL );
	void *GetData();

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
namespace _ZPOCKETSONATA_ {
    #define PH_WIDTH_FREQ		128000
    #define L_PH_MIN_FREQ		64000
    #define H_PH_MIN_FREQ		192000 //kHz

    #define PDW_TIME_RES		7.8125
    #define PDW_FREQ_RES		(1.953125)
    #define PDW_AOA_RES			0.087890625

    static const float m_fCenterFreq[enPRC6] = { 3072000., 3072000., 3072000., 3072000., 3072000., 3072000. } ;
}

class CPOCKETSONATAPDW : public CData
{
private:
    STR_PDW_DATA m_PDWData;

    //static ENUM_BoardID m_enBoardID;

public:
    CPOCKETSONATAPDW(STR_RAWDATA *pRawData, STR_FILTER_SETUP *pstFilterSetup );
    virtual ~CPOCKETSONATAPDW();

    void Alloc();
    void Free();
    void ConvertArray( STR_PDWDATA *pPDWData=NULL );
    void *GetData();

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
            fFREQ = (( _ZPOCKETSONATA_::m_fCenterFreq[iBoardID] - (float) L_PH_MIN_FREQ) + ( PH_WIDTH_FREQ * iCh ) + ( (float) iFreq * (float) PDW_FREQ_RES) );
        }
        else {
            iCh = 15 - iCh;
            fFREQ = ( ( _ZPOCKETSONATA_::m_fCenterFreq[iBoardID] - H_PH_MIN_FREQ) - ( PH_WIDTH_FREQ * iCh) + ( (float) iFreq * (float) PDW_FREQ_RES ) );
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
    static int DecodePWus( int iPW )
    {
        int iretPW;

        iretPW = (int) ( (float) iPW * (float) PDW_TIME_RES / (float) 1000. + 0.5 );
        return iretPW;
    } ;

    static int EncodePWFloor( float fPW )
    {
        float iretPW;

        iretPW = (int) ( (float) fPW * (float) 1. / (float) PDW_TIME_RES );
        return (int) iretPW;
    } ;

    static int EncodePWCeiling( float fPW )
    {
        float iretPW;

        iretPW = (int) ( (float) fPW * (float) 1. / (float) PDW_TIME_RES );
        return (int) ( iretPW + 0.5 );
    } ;

    /**
     * @brief DecodeTOA
     * @param iTOA
     * @return
     */
    static float DecodeTOA( _TOA iTOA  )
    {
        float fTOA;

        fTOA = (float) ( (float) iTOA * (float) PDW_TIME_RES / (float) 1.0 );
        return fTOA;	/* [ns] */
    } ;

    /**
     * @brief DecodeTOAus
     * @param iTOA
     * @return
     */
    static float DecodeTOAus( _TOA iTOA  )
    {
        float fretTOA;

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
	STR_IQ_DATA m_IQData;

public:
	CIQ(STR_RAWDATA *pRawData);
	virtual ~CIQ();

	void Alloc();
	void Free();
    void ConvertArray( STR_PDWDATA *pPDWData=NULL );
	void *GetData();

};

class CDataFile
{
private:
	CFile m_RawDataFile;

	STR_RAWDATA m_RawData;
	CData *m_pData;

public:
	CDataFile(void);
	virtual ~CDataFile(void);

    void ReadDataMemory( STR_PDWDATA *pPDWData, const char *pstData, const char *pstPathname, STR_FILTER_SETUP *pstFilterSetup=NULL );
    void ReadDataFile( const char *pstPathname, STR_FILTER_SETUP *pstFilterSetup=NULL );
    void SaveDataFile( char *pstPathname, void *pData, int iNumData, ENUM_UnitType enUnitType, ENUM_DataType enDataType, void *pDataEtc=NULL, int iSizeOfEtc=0 );
	void Alloc();
	void Free();
	void *GetData();
	void SetData( CData *pData );

	inline UINT GetDataItems() { if( m_pData != NULL ) return m_pData->m_pRawData->uiDataItems; else return 0; }
	inline ENUM_UnitType GetUnitType() { return m_pData->m_pRawData->enUnitType; }
	inline ENUM_DataType GetDataType() { return m_pData->m_pRawData->enDataType; }
	inline UINT GetWindowNumber() { if( m_pData != NULL ) return m_pData->m_uiWindowNumber; else return 0; }
	inline CData *GetRawData() { if( m_pData != NULL ) return m_pData; else return NULL; }
	
	inline bool IsPhaseData() { return m_pData->m_bPhaseData; }
	
private:
	
	
};

