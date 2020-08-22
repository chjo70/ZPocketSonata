#pragma once

#include <stdio.h>

#include "../../Include/system.h"

#include "_iq.h"
#include "../../Anal/INC/PDW.h"

#include "../../Anal/OFP_Main.h"
//#include "../../Anal/SigAnal/_Macro.h"



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

static char *gstpRawDataBuffer;

class CData
{
public:
    STR_RAWDATA *m_pRawData;

    UINT m_uiWindowNumber;

    bool m_bPhaseData;

    STR_FILTER_SETUP m_stFilterSetup;

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
class CPOCKETSONATAPDW : public CData
{
private:
    STR_PDW_DATA m_PDWData;

public:
    CPOCKETSONATAPDW(STR_RAWDATA *pRawData, STR_FILTER_SETUP *pstFilterSetup );
    virtual ~CPOCKETSONATAPDW();

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

