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

protected:
    CMIDASBlueFileFormat *m_pMidasBlue;

    STR_PDWDATA m_stSavePDWData;        // 분석한 LOB를 근거로 파일로 저장하기 위한 데이터 포인터

private:

protected:
#ifdef _MSSQL_
    CODBCDatabase *GetCODBCDatabase();
#endif

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

    void InitDataFromDB();

    bool InsertToDB_RAW(STR_PDWDATA *pPDWData, int iPLOBID);
    void InsertRAWData(STR_PDWDATA *pPDWData, int iPLOBID );

    virtual __time32_t GetColTime() = 0;
    virtual unsigned int GetColTimeMs() = 0;
    virtual unsigned int GetPDWID() = 0;

};

