#pragma once

#include <stdio.h>

#include "../../Files/Anal/SigAnal/_Struct.h"

#include "../../Files/Anal/EmitterMerge/ELMsgDefn.h"

#include "../../Files/Anal/Collect/DataFile/DataFile.h"

typedef struct {
    unsigned int uiIdex;    // 인덱스

    char szFileName[200];   // 파일명

    UINT uiCoAllPDW;
    UINT uiFirstTOA;
    UINT uiSignalType;
    UINT uiDV;
    UINT uiAOA;

    char szFreqType[100];
    int iFreqMean;
    UINT uiBW;
    char szFreqPatType[100];
    UINT uiFreqPatPrd;
    UINT uiFreqHopLvl;
    float fFreqSwtVal[MAX_FREQ_PRI_STEP];

    char szPRIType[100];
    int iPRIMean;
    float fJitterp;
    char szPRIPatType[100];
    UINT uiPRIHopLvl;
    float fPRISwtVal[MAX_FREQ_PRI_STEP];
    UINT uiPRIPatPrd;
    UINT uiCoPRIPatPDW;

    float fPA;
    UINT uiPW;
    UINT uiFmop;
    UINT uiPmop;

    char szScanType[100];
    UINT uiScanPrd;
    UINT uiCoScanPrd;

    UINT uiDOAError;
    UINT uiFreqError;
    UINT uiTOAError;
    UINT uiPWError;
    UINT uiPAError;
    UINT uiCoPulseSkip;

} STR_GENPDW_INFO ;

class CGenPDW : public CRawFile
{
private:
    FILE *m_File;

    char m_szMakfilename[200];

    STR_GENPDW_INFO m_stGenPDWInfo;

    STR_PDWDATA m_stSavePDWData;
    CMIDASBlueFileFormat m_theMidasBlue;

    // 병합된 멤버 변수
    int m_iCoMergedPDW;
    STR_PDWDATA m_stMergedPDWData;


    CDataFile m_theDataFile;

    _PDW *m_pstPDW;


    // 방생하기 위? 변수 모음
    float m_fPriWidth;
    _TOA m_tTOA;

    //_TOA m_tFreqPeriod;
    //_TOA m_tPRIPeriod;

    float m_fFreqCountPerPeriod;

    // PRI 발생에 따른 변수 모음
    float m_fPRICountPerPeriod;
    UINT m_uiPRIDwellCount;
    UINT m_uiPRILvl;

    UINT m_ui1DOA;
    int m_i360DOA;

private:
    void GetLineCommand();
    bool IsValidCheck();
    void MergePDW( SIGAPDW *pSigPDW=NULL );
    void GeneratePDW( SIGAPDW *pSigPDW=NULL );
    void MakeFileHeader();

    void SetGenerateInfo();

    // PDW 데이터 생성하기
    void MakeSignalType( SIGAPDW *pSigPDW=NULL );
    void MakeFreqOfPDW( SIGAPDW *pSigPDW = NULL );
    void MakePRIOfPDW( bool bSkippedPDW, SIGAPDW *pSigPDW = NULL );
    void MakeDOAOfPDW( SIGAPDW *pSigPDW = NULL );
    void MakePWOfPDW( SIGAPDW *pSigPDW = NULL );
    void MakePAOfPDW( SIGAPDW *pSigPDW = NULL );

public:
    CGenPDW( int iCoPDW=NEW_COLLECT_PDW );
    //CGenPDW( char *pszFileName );

    virtual ~CGenPDW();

    void ParseAndMakefile( );
    void ParseAndMakeMemory( SIGAPDW *pSigPDW=NULL );
    void SkipTheHeader();

    void OpenMakefile( char *pszFileName );

    inline _PDW *GetMergedPDWData() { return m_stMergedPDWData.pstPDW; }
};

