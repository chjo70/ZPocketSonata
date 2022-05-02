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

    CDataFile m_theDataFile;

    _PDW *m_pstPDW;


    // 방생하기 위햔 변수 모음
    int m_iPriWidth;
    _TOA m_tTOA;
    UINT m_uiPRIDwellCount;
    UINT m_uiPRIStaggerLvl;
    UINT m_ui1DOA;
    int m_i360DOA;
    int m_iPWError;
    

private:
    void GetLineCommand();
    void GeneratePDW();
    void MakeFileHeader();

    void SetGenerateInfo();

    // PDW 데이터 생성하기
    void MakeSignalType();
    void MakeFreqOfPDW();
    void MakePRIOfPDW( bool bSkippedPDW );
    void MakePWOfPDW();
    void MakePRIOfDOA();
    void MakePRIOfPW();
    void MakePRIOfPA();

    int Rand( int range );

public:
    CGenPDW( char *pszFileName  );
    virtual ~CGenPDW();

    void ParsingThePDWMakefile();
    void SkipTheHeader();

    //void MakeFileHeader();

};

