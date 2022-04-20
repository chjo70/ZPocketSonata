#pragma once


#ifdef _MSSQL_
#include "../../ODBC/mssql.h"
#include "../../ODBC/odbccore.h"

#elif _SQLITE_
#include "../../SQLite/KompexSQLitePrerequisites.h"
#include "../../SQLite/KompexSQLiteDatabase.h"
#include "../../SQLite/KompexSQLiteStatement.h"
#include "../../SQLite/KompexSQLiteException.h"
#include "../../SQLite/KompexSQLiteStreamRedirection.h"
#include "../../SQLite/KompexSQLiteBlob.h"

#endif


#include "../MIDAS/Midas.h"
#include "../MIDAS/RawFile.h"


#ifdef _MSSQL_
class CSigAnal : public CMSSQL, public CRawFile
#else
class CSigAnal : public CRawFile
#endif
{
private:
    bool m_bDBThread;

    char *m_pszSQLString;

#ifdef _MSSQL_
    LONG m_lOpInitID;
    CODBCDatabase m_theMyODBC;

#elif _SQLITE_
    Kompex::SQLiteDatabase *m_pDatabase;

#endif

    bool m_bSaveFile;

    char m_szRawDataFilename[200];

    UINT m_uiStep;

#if defined(_ELINT_)
    char m_szTaskID[LENGTH_OF_TASK_ID];
    EN_RADARCOLLECTORID m_enCollectorID;
    ELINT::ENUM_BANDWIDTH m_enBandWidth;

#elif defined(_XBAND_)
    char m_szTaskID[LENGTH_OF_TASK_ID];
    EN_RADARCOLLECTORID m_enCollectorID;
    XBAND::ENUM_BANDWIDTH m_enBandWidth;

#elif _POCKETSONATA_
    ENUM_BANDWIDTH m_enBandWidth;

#endif    

protected:
    CMIDASBlueFileFormat *m_pMidasBlue;

    STR_PDWDATA m_stSavePDWData;        // 분석한 LOB를 근거로 파일로 저장하기 위한 데이터 포인터

private:

protected:
#ifdef _MSSQL_
    CODBCDatabase *GetCODBCDatabase();
#endif
    void SaveGroupPdwFile(int index);
    void SaveRemainedPdwFile();
    void SaveEmitterPdwFile(STR_EMITTER *pEmitter, _PDW *pstPDW, int iPLOBID, bool bSaveFile);

public:
    CSigAnal(unsigned int uiCoMaxPdw, bool bDBThread, const char *pFileName );
    virtual ~CSigAnal();

    void NextStep() { ++m_uiStep; }
    void SetStep( unsigned int uiStep ) { m_uiStep=uiStep; }
    unsigned int GetStep() { return m_uiStep; }

    bool IsSaveFile() const { return m_bSaveFile; }
    void SetSaveFile(bool val) { m_bSaveFile = val; }
    void Initialize();

    void InitResolution();

    void InitDataFromDB();

    bool InsertToDB_RAW(STR_PDWDATA *pPDWData, int iPLOBID);
    void InsertRAWData(STR_PDWDATA *pPDWData, int iPLOBID );

    virtual __time32_t GetColTime() = 0;
    virtual unsigned int GetColTimeMs() = 0;
    virtual unsigned int GetPDWID() = 0;

#if defined(_ELINT_)
    ELINT::ENUM_BANDWIDTH GetBandWidth() const { return m_enBandWidth; }
    void SetBandWidth(ELINT::ENUM_BANDWIDTH val) { m_enBandWidth = val; }
#elif defined(_XBAND_)
    XBAND::ENUM_BANDWIDTH GetBandWidth() const { return m_enBandWidth; }
    void SetBandWidth(XBAND::ENUM_BANDWIDTH val) { m_enBandWidth = val; }
#endif

    inline char *GetTaskID() {
#if defined(_ELINT_) || defined(_XBAND_)
        return (char *)& m_szTaskID[0];
#else
        return NULL;
#endif
    }
    inline void SetTaskID( char *pVal) { strcpy(m_szTaskID, pVal ); }

#if defined(_ELINT_) || defined(_XBAND_)
    EN_RADARCOLLECTORID GetCollectorID() const { return m_enCollectorID; }
    void SetCollectorID(EN_RADARCOLLECTORID val) { m_enCollectorID = val; }
#endif
};

