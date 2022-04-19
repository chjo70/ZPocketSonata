#include "stdafx.h"

#include "../OFP_Main.h"

#include "SigAnal.h"

#include "../../Include/globals.h"

#include "../../Utils/ccommonutils.h"

#ifdef _MSSQL_
CSigAnal::CSigAnal(unsigned int uiCoMaxPdw, bool bDBThread, const char *pFileName) : CMSSQL(&m_theMyODBC)
#else
CSigAnal::CSigAnal(unsigned int uiCoMaxPdw, bool bDBThread, const char *pFileName)
#endif
{
    size_t szSize;

    SetStep(_spZero);

    CCommonUtils::SetUnitType();

    m_bDBThread = bDBThread;

#ifdef _SQLITE_
    try {
        m_pDatabase = new Kompex::SQLiteDatabase(pFileName, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, 0);

    }
    catch (Kompex::SQLiteException &exception) {
        std::cerr << "\nException Occured" << std::endl;
        exception.Show();
        std::cerr << "SQLite result code: " << exception.GetSqliteResultCode() << std::endl;
    }

    // SQLITE ÆÄÀÏ¸í »ý¼ºÇÏ±â
    char szSQLiteFileName[100];

    strcpy(szSQLiteFileName, CEDEOB_SQLITE_FOLDER);
    strcat(szSQLiteFileName, "/");
    strcat(szSQLiteFileName, CEDEOB_SQLITE_FILENAME);

    m_pszSQLString = (char *)malloc(MAX_SQL_SIZE);
#elif _MSSQL_
    CMSSQL::Init();

    m_pszSQLString = (char *)malloc(MAX_SQL_SIZE);

#else

#endif

    srand(time(NULL) & (unsigned int)0xFFFF);

    SetSaveFile(true);

    _SAFE_NEW(m_pMidasBlue, CMIDASBlueFileFormat);

    szSize = CCommonUtils::CheckMultiplyOverflow(sizeof(_PDW), uiCoMaxPdw);
    m_stSavePDWData.pstPDW = NULL;
    _SAFE_MALLOC(m_stSavePDWData.pstPDW, _PDW, szSize);

    // DB °ü·Ã º¯¼ö ÃÊ±âÈ­
    InitDataFromDB();

}


/**
 * @brief     ~CSigAnal
 * @return    
 * @exception
 * @author    Á¶Ã¶Èñ (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-18, 13:11
 * @warning
 */
CSigAnal::~CSigAnal()
{
    _SAFE_DELETE(m_pMidasBlue);

    _SAFE_FREE(m_stSavePDWData.pstPDW)

#if defined(_SQLITE_) || defined(_MSSQL_)
        _SAFE_FREE(m_pszSQLString)

#endif

#ifdef _MSSQL_
    m_theMyODBC.Close();
#endif

}


/**
 * @brief     ºÐ¼® ¸ðµâÀ» ÃÊ±âÈ­ ÇÑ´Ù.
 * @param     void
 * @return    void
 * @exception
 * @author    Á¶Ã¶Èñ (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-18, 13:18
 * @warning
 */
void CSigAnal::Initialize()
{

}


/**
 * @brief     SaveEmitterPdwFile
 * @param     STR_EMITTER * pEmitter
 * @param     int iPLOBID
 * @return    void
 * @exception
 * @author    Á¶Ã¶Èñ (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-18, 15:34
 * @warning
 */
void CSigAnal::SaveEmitterPdwFile(STR_EMITTER *pEmitter, _PDW *pstPDW, int iPLOBID, bool bSaveFile)
{
    unsigned int i;

    PDWINDEX *pPdwIndex;
    _PDW *pPDW;

    if (m_bSaveFile == true && bSaveFile == true) {
        m_stSavePDWData.SetTotalPDW(pEmitter->pdw.uiCount);

        pPdwIndex = pEmitter->pdw.pIndex;
        for (i = 0; i < pEmitter->pdw.uiCount; ++i) {
            pPDW = &pstPDW[*pPdwIndex++];
            memcpy(&m_stSavePDWData.pstPDW[i], pPDW, sizeof(_PDW));

        }

        // ¼öÁýÇÑ PDW ÆÄÀÏ ÀúÀåÇÏ±â...
        InsertRAWData(&m_stSavePDWData, iPLOBID);
    }

}

#ifdef _MSSQL_
/**
 * @brief     GetCODBCDatabase
 * @return    CODBCDatabase *
 * @exception
 * @author    Á¶Ã¶Èñ (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-18, 14:07
 * @warning
 */
CODBCDatabase *CSigAnal::GetCODBCDatabase()
{
    return &m_theMyODBC;

}
#endif

/**
 * @brief     InitDataFromDB
 * @return    void
 * @exception
 * @author    Á¶Ã¶Èñ (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-18, 13:22
 * @warning
 */
void CSigAnal::InitDataFromDB()
{

#ifdef _MSSQL_

#if defined(_ELINT_) || defined(_XBAND_) || defined(_POCKETSONATA_)
    char buffer[400];

    sprintf_s(buffer, sizeof(buffer), "select max(OP_INIT_ID) from LOBDATA");
    m_lOpInitID = GetINTData(buffer) + 1;

    sprintf_s(buffer, sizeof(buffer), "select max(OP_INIT_ID) from RAWDATA");
    m_lOpInitID = _max(m_lOpInitID, GetINTData(buffer) + 1);

#endif

#else
    // m_lOpInitID = _spOne;


#endif

}

/**
 * @brief     InsertRAWData
 * @param     STR_PDWDATA * pPDWData
 * @return    void
 * @exception
 * @author    Á¶Ã¶Èñ (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-01-23, 17:53
 * @warning
 */
void CSigAnal::InsertRAWData(STR_PDWDATA *pPDWData, int iPLOBID )
{
    bool bRet = true;
    char buffer[100] = { 0 };
    TCHAR szDirectory[500], szRawDataPathname[600];

    struct tm *pstTime;
    struct timespec tiNow;

    CCommonUtils::GetCollectTime(&tiNow, GetColTime(), GetColTimeMs() );
    pstTime = localtime(&tiNow.tv_sec);

#ifdef _ELINT_
    sprintf_s(szDirectory, "%s\\¼öÁý¼Ò_%d\\%s", SHARED_DATA_DIRECTORY, pPDWData->x.el.iCollectorID, pPDWData->x.el.aucTaskID);

#elif _XBAND_
    //sprintf_s( szDirectory, "%s\\¼öÁý¼Ò_%d\\%s\\%s", SHARED_DATA_DIRECTORY, pPDWData->x.el.iCollectorID, buffer, pPDWData->x.el.aucTaskID );
    sprintf_s(szDirectory, "%s\\¼öÁý¼Ò_%d\\%s", SHARED_DATA_DIRECTORY, pPDWData->x.el.GetCollectorID(), pPDWData->x.el.aucTaskID);

#elif _POCKETSONATA_
    strftime(buffer, 100, "%Y-%m-%d", pstTime);
    sprintf(szDirectory, _T("%s/%s/BRD_%d/%s"), SHARED_DATA_DIRECTORY, buffer, pPDWData->x.ps.uiBoardID, g_szCollectBank[pPDWData->x.ps.iBank]);

#else
    sprintf(szDirectory, "%s/BRD", pLocalDirectory);

#endif

    if ( /*pstTime != NULL &&*/ m_bSaveFile == true) {
        bRet = CreateDir(szDirectory);
    }

    if ( /*pstTime != NULL &&*/ bRet == true) {
        if (m_bSaveFile == true) {
            // 2. ÆÄÀÏ¸í »ý¼ºÇÏ±â
            strftime(buffer, 100, "%Y-%m-%d_%H_%M_%S", pstTime);

#if defined(_ELINT_) || defined(_XBAND_)
            sprintf(m_szRawDataFilename, _T("%d_%s_%010d_%d%s"), pPDWData->x.el.GetCollectorID(), buffer, GetPDWID(), iPLOBID, PDW_EXT);

#elif _POCKETSONATA_
            sprintf(m_szRawDataFilename, _T("%d_%s_%010d_%d.%s.%s"), pPDWData->x.ps.uiBoardID, buffer, GetPDWID(), iPLOBID, PDW_TYPE, MIDAS_EXT);

#else

#endif
            sprintf(szRawDataPathname, _T("%s/%s"), szDirectory, m_szRawDataFilename);
            //m_pMidasBlue->SaveRawDataFile(szRawDataPathname, E_EL_SCDT_PDW, pPDWData);
        }
        else {
            m_szRawDataFilename[0] = NULL;
        }

        if (m_bDBThread == false) {
            // RAWDATA µ¥ÀÌÅÍ ÀúÀå
            InsertToDB_RAW(pPDWData, iPLOBID);
        }
        else {
            TRACE("Push the data for InsertToDB_RAW()");
        }

    }

}

/**
 * @brief
 * @param     STR_PDWDATA * pPDWData
 * @return    bool
 * @author    Á¶Ã¶Èñ (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022/01/23 23:33:21
 * @warning
 */
bool CSigAnal::InsertToDB_RAW(STR_PDWDATA *pPDWData, int iPLOBID)
{
    if (pPDWData != NULL) {
        struct timespec tiNow;

        char buffer[100];

        CCommonUtils::GetCollectTime(&tiNow, GetColTime(), GetColTimeMs() );
        CCommonUtils::getStringDesignatedTime(buffer, sizeof(buffer), tiNow.tv_sec);

#ifdef _MSSQL_
#ifdef _POCKETSONATA_
        sprintf_s(m_pszSQLString, MAX_SQL_SIZE, "INSERT INTO RAWDATA ( OP_INIT_ID, PDWID, PLOBID, CREATE_TIME, CREATE_TIME_MS, COUNTOFDATA, FILENAME, DATA_TYPE, COL_BANK ) values( \
                                                 '%ld', '%d', '%d', '%s', '0', '%d', '%s', '%d', '%d' )", \
            m_lOpInitID, GetPDWID(), iPLOBID, buffer, pPDWData->GetTotalPDW(), m_szRawDataFilename, E_EL_SCDT_PDW, pPDWData->x.ps.iBank);

#elif defined(_ELINT_) || defined(_XBAND_)
        sprintf_s(m_pszSQLString, MAX_SQL_SIZE, "INSERT INTO RAWDATA ( OP_INIT_ID, PDWID, PLOBID, TASK_ID, CREATE_TIME, CREATE_TIME_MS, COUNTOFDATA, FILENAME, DATA_TYPE ) values( \
                                                 '%ld', '%d', '%d', '%s', '%s', '%d', '%d', '%s', '0' )", \
            m_lOpInitID, GetPDWID(), iPLOBID, pPDWData->x.el.aucTaskID, buffer, iPLOBID, pPDWData->GetTotalPDW(), m_szRawDataFilename);

#else
        sprintf_s(m_pszSQLString, MAX_SQL_SIZE, "INSERT INTO RAWDATA ( OP_INIT_ID, PDWID, PLOBID, TASK_ID, CREATE_TIME, CREATE_TIME_MS, COUNTOFDATA, FILENAME, DATA_TYPE ) values( \
                                                 '%ld', '%d', '%d', '%s', '%s', '%d', '%d', '%s', '0' )", \
            m_lOpInitID, GetPDWID(), pPDWData->x.el.aucTaskID, buffer, iPLOBID, pPDWData->GetTotalPDW(), m_szRawDataFilename);


#endif

#elif _SQLITE_
#ifdef _POCKETSONATA_
        sprintf(m_pszSQLString, "INSERT INTO RAWDATA ( PDWID, PLOBID, CREATE_TIME, CREATE_TIME_MS, COUNTOFDATA, FILENAME, DATA_TYPE, COL_BANK ) values( \
                                                 '%d', '%d', '%s', '0', '%d', '%s', '%d', '%d' )", \
            GetPDWID(), iPLOBID, buffer, pPDWData->GetTotalPDW(), m_szRawDataFilename, E_EL_SCDT_PDW, pPDWData->x.ps.iBank);

#elif defined(_ELINT_) || defined(_XBAND_)
        sprintf_s(m_pszSQLString, MAX_SQL_SIZE, "INSERT INTO RAWDATA ( OP_INIT_ID, PDWID, PLOBID, TASK_ID, CREATE_TIME, CREATE_TIME_MS, COUNTOFDATA, FILENAME, DATA_TYPE ) values( \
                                                 '%ld', '%d', '%d', '%s', '%s', '%d', '%d', '%s', '0' )", \
            m_lOpInitID, GetPDWID(), iPLOBID, pPDWData->x.el.aucTaskID, buffer, iPLOBID, pPDWData->GetTotalPDW(), m_szRawDataFilename);

#else
        sprintf_s(m_pszSQLString, MAX_SQL_SIZE, "INSERT INTO RAWDATA ( OP_INIT_ID, PDWID, PLOBID, TASK_ID, CREATE_TIME, CREATE_TIME_MS, COUNTOFDATA, FILENAME, DATA_TYPE ) values( \
                                                 '%ld', '%d', '%d', '%s', '%s', '%d', '%d', '%s', '0' )", \
            m_lOpInitID, GetPDWID(), pPDWData->x.el.aucTaskID, buffer, iPLOBID, pPDWData->GetTotalPDW(), m_szRawDataFilename);

#endif

#endif


#ifdef _MSSQL_
        DECLARE_BEGIN_CHECKODBC

        CODBCRecordset theRS = CODBCRecordset(m_pMyODBC);

        theRS.Open(m_pszSQLString);
        Log(enDebug, ".InsertRAW[O%d, P%d, P%d]", m_lOpInitID, GetPDWID(), iPLOBID);

        theRS.Close();

        DECLARE_END_CHECKODBC

    }

    DECLARE_RETURN

#elif _SQLITE_
        bool bRet = true;

        if (m_pszSQLString[0] != NULL) {
            try {
                Kompex::SQLiteStatement stmt(m_pDatabase);
                stmt.SqlStatement(m_pszSQLString);
                Log(enDebug, ".InsertRAW[P%d, P%d]", GetPDWID(), iPLOBID);

                // do not forget to clean-up
                stmt.FreeQuery();

            }
            catch (Kompex::SQLiteException &exception) {
                LOGMSG1(enError, " m_pszSQLString[%s]", m_pszSQLString);
                bRet = false;
                std::cerr << "\nException Occured" << std::endl;
                exception.Show();
                std::cerr << "SQLite result code: " << exception.GetSqliteResultCode() << std::endl;
            }
        }
        else {
            bRet = false;
        }

}

    return true;

#else

    }

    return true;

#endif

}


