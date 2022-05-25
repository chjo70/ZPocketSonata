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

    SetUnitType();

    SetStep(_spZero);

#if defined(_ELINT_) || defined(_XBAND_)
    m_szTaskID[0] = NULL;
#endif

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

    // SQLITE 파일명 생성하기
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

    // DB 관련 변수 초기화
    InitDataFromDB();

}


/**
 * @brief     ~CSigAnal
 * @return    
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
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
 * @brief     분석 모듈을 초기화 한다.
 * @param     void
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-18, 13:18
 * @warning
 */
void CSigAnal::Initialize()
{

}




/**
 * @brief     InitResolution
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-06, 15:37
 * @warning
 */
void CSigAnal::InitResolution()
{

#if defined(_ELINT_)
    float _toaRes[ELINT::enUnknown_BW + 1] = { (float) 65.104167, (float) 8.138021, (float) 0.0 };

    //STR_PDWDATA *pPDWData;
    //m_enBandWidth = pPDWData->x.el.enBandWidth;

    _spOneSec = FDIV(1000000000, _toaRes[GetBandWidth()]);
    _spOneMilli = FDIV(1000000, _toaRes[GetBandWidth()]);
    _spOneMicrosec = FDIV(1000, _toaRes[GetBandWidth()]);
    _spOneNanosec = FDIV(1, _toaRes[GetBandWidth()]);

    _spAOAres = (float) 0.01;
    _spAMPres = (float)(0.25);
    _spPWres = _spOneMicrosec;

#elif defined(_XBAND_)
    float _toaRes[XBAND::enUnknown_BW + 1] = { (float) 65.104167, (float) 8.138021, (float) 0.0 };

    _spOneSec = FDIV(1000000000, _toaRes[GetBandWidth()]);
    _spOneMilli = FDIV(1000000, _toaRes[GetBandWidth()]);
    _spOneMicrosec = FDIV(1000, _toaRes[GetBandWidth()]);
    _spOneNanosec = FDIV(1, _toaRes[GetBandWidth()]);

    _spAOAres = (float) 0.01;
    _spAMPres = (float)(0.25);
    _spPWres = _spOneMicrosec;


#elif defined(_POCKETSONATA_)
    _spOneSec = FDIV(1000000000, 6.48824007);
    _spOneMilli = FDIV(1000000, 6.48824007);
    _spOneMicrosec = FDIV(1000, 6.48824007);
    _spOneNanosec = FDIV(1, 6.48824007);

    _spAOAres = (float)(0.351562);
    _spAMPres = (float)(0.351562);
    _spPWres = _spOneMicrosec;

#elif defined(_SONATA_)
    _spOneSec = 20000000.;
    _spOneMilli = FDIV(_spOneSec, 1000.);
    _spOneMicrosec = FDIV(_spOneMilli, 1000.);
    _spOneNanosec = FDIV(_spOneMicrosec, 1000.);

    _spAOAres = (float)(0.351562);
    _spAMPres = (float)(0.351562);
    _spPWres = (float)(50);

#endif
}



//////////////////////////////////////////////////////////////////////////
/*! \brief    CNewSigAnal::SaveRemainedPdwFile
        \author   조철희
        \return   void
        \version  0.0.1
        \date     2008-01-22 12:40:25
        \warning
*/
void CSigAnal::SaveRemainedPdwFile()
{
#ifdef _DEBUG_MAKEPDW_NO
    CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
    CA50SigAnalView *pView = (CA50SigAnalView *)pFrame->GetActiveView();

    UINT i;
    FILE *pdwfile;
    TNEW_PDW *pPDW;
    char filename[100];

    CString strFilename = pView->GetFileTitle();

    LPTSTR p = strFilename.GetBuffer(100);

    m_theMakeAET->MarkAllAetToPdwIndex();

    sprintf(filename, "c:\\temp\\%03d_rem_%s.pdw", m_nStep, p);
    pdwfile = fopen(filename, "wb");
    for (i = 0; i < m_pPDWData->count; ++i) {
        if (MARK[i] == EXTRACT_MARK)
            continue;

        pPDW = &m_pPDWData->pPdw[i];
#ifdef _A50_RWR
        TNEW_PDW pdw;

        pdw.word[0] = ntohl(pPDW->word[0]);
        pdw.word[1] = ntohl(pPDW->word[1]);
        pdw.word[2] = ntohl(pPDW->word[2]);
        pdw.word[3] = ntohl(pPDW->word[3]);

        fwrite(&pdw, sizeof(TNEW_PDW), 1, pdwfile);
#else
        fwrite(pPDW, sizeof(TNEW_PDW), 1, pdwfile);
#endif

    }

    fclose(pdwfile);

    strFilename.ReleaseBuffer();

#endif
}

/**
 * @brief     SaveGroupPDWFile
 * @param     int index
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-09, 11:45
 * @warning
 */
void CSigAnal::SaveGroupPDWFile(int index)
{
    UINT uiSize;
    char filename[100];
    char szDirectory[100];

    int i;
    CFile cFile;
    BOOL bRet;
    PDWINDEX *pPdwIndex;
    _PDW *pPDW;

    STR_PDWDATA stPDWData;
	
	bRet = MakeDirectory(szDirectory, pPDWData);


    // 
    //         cFile.Open( filename, CFile::modeCreate | CFile::modeReadWrite );
    // 
    //         uiSize = sizeof( STR_PDWDATA ) - ( MAX_PDW * sizeof(_PDW) );
    //         memcpy( & stPDWData, m_pPDWData, uiSize );
    //         stPDWData.iIsStorePDW = 0;
    //         stPDWData.count = m_pGrPdwIndex->count;
    // 
	m_stSavePDWData.SetTotalPDW(pEmitter->stPDW.uiCount);
	pPdwIndex = m_pGrPdwIndex->pIndex;
	for( i=0 ; i < m_pGrPdwIndex->count ; ++i ) {
		pPDW = & m_pPDWData->stPDW[ *pPdwIndex++ ];
		memcpy( & stPDWData.stPDW[i], pPDW, sizeof(_PDW) );

	}

}

/**
 * @brief     SaveEmitterPdwFile
 * @param     STR_EMITTER * pEmitter
 * @param     int iPLOBID
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-18, 15:34
 * @warning
 */
void CSigAnal::SaveEmitterPDWFile(STR_EMITTER *pEmitter, _PDW *pstPDW, int iPLOBID, bool bSaveFile)
{
    unsigned int i;

    PDWINDEX *pPdwIndex;
    _PDW *pPDW;

    if (m_bSaveFile == true && bSaveFile == true) {
        m_stSavePDWData.SetTotalPDW(pEmitter->stPDW.uiCount);

        pPdwIndex = pEmitter->stPDW.pIndex;
        for (i = 0; i < pEmitter->stPDW.uiCount; ++i) {
            pPDW = &pstPDW[*pPdwIndex++];
            memcpy(&m_stSavePDWData.pstPDW[i], pPDW, sizeof(_PDW));

        }

        // 수집한 PDW 파일 저장하기...
        InsertRAWData(&m_stSavePDWData, iPLOBID);
    }

}



#ifdef _MSSQL_
/**
 * @brief     GetCODBCDatabase
 * @return    CODBCDatabase *
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
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
 * @author    조철희 (churlhee.jo@lignex1.com)
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
 * @brief     PLOBID 값으로 PDW 데이터를 DB 및 파일에 저장한다.
 * @param     STR_PDWDATA * pPDWData
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-01-23, 17:53
 * @warning
 */
void CSigAnal::InsertRAWData(STR_PDWDATA *pPDWData, int iPLOBID )
{
    bool bRet = true;
    char buffer[100] = { 0 };
    TCHAR szDirectory[500], szRawDataPathname[600];

	bRet = MakeDirectory(szDirectory, pPDWData );

    if ( /*pstTime != NULL &&*/ bRet == true) {
        if (m_bSaveFile == true) {
			struct tm *pstTime;
			struct timespec tiNow;

			CCommonUtils::GetCollectTime(&tiNow, GetColTime(), GetColTimeMs());
			pstTime = localtime(&tiNow.tv_sec);

            // 2. 파일명 생성하기
            strftime(buffer, 100, "%Y-%m-%d_%H_%M_%S", pstTime);

            sprintf(m_szRawDataFilename, _T("%d_%s_%010d_%d%s"), pPDWData->GetCollectorID(), buffer, GetPDWID(), iPLOBID, PDW_EXT);
            //sprintf(m_szRawDataFilename, _T("%d_%s_%010d_%d.%s.%s"), pPDWData->x.ps.uiBoardID, buffer, GetPDWID(), iPLOBID, PDW_TYPE, MIDAS_EXT);

            sprintf(szRawDataPathname, _T("%s/%s"), szDirectory, m_szRawDataFilename);
            m_pMidasBlue->SaveRawDataFile(szRawDataPathname, E_EL_SCDT_PDW, pPDWData->pstPDW, & pPDWData->x, pPDWData->GetTotalPDW() );
        }
        else {
            m_szRawDataFilename[0] = NULL;
        }

        if (m_bDBThread == false) {
            // RAWDATA 데이터 저장
            InsertToDB_RAW(pPDWData, iPLOBID);
        }
        else {
            TRACE("Push the data for InsertToDB_RAW()");
        }

    }

}

/**
 * @brief     디렉토리를 생성한다.
 * @param     char * pszDirectory
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-25, 23:59
 * @warning
 */
bool CSigAnal::MakeDirectory( char *pszDirectory, STR_PDWDATA *pPDWData)
{
	bool bRet = false;
	struct tm *pstTime;
	struct timespec tiNow;

	CCommonUtils::GetCollectTime(&tiNow, GetColTime(), GetColTimeMs());
	pstTime = localtime(&tiNow.tv_sec);

#ifdef _ELINT_
	sprintf_s(pszDirectory, "%s\\수집소_%d\\%s", SHARED_DATA_DIRECTORY, pPDWData->x.el.iCollectorID, pPDWData->x.el.aucTaskID);

#elif _XBAND_
	//sprintf_s( szDirectory, "%s\\수집소_%d\\%s\\%s", SHARED_DATA_DIRECTORY, pPDWData->x.el.iCollectorID, buffer, pPDWData->x.el.aucTaskID );
	sprintf(pszDirectory, "%s\\수집소_%d\\%s", SHARED_DATA_DIRECTORY, pPDWData->x.el.GetCollectorID(), pPDWData->x.el.aucTaskID);

#elif _POCKETSONATA_
	strftime(buffer, 100, "%Y-%m-%d", pstTime);
	sprintf(pszDirectory, _T("%s/%s/BRD_%d/%s"), SHARED_DATA_DIRECTORY, buffer, pPDWData->x.ps.uiBoardID, g_szCollectBank[pPDWData->x.ps.uiBank]);

#else
	sprintf(pszDirectory, "%s/BRD", pLocalDirectory);

#endif

	if ( /*pstTime != NULL &&*/ m_bSaveFile == true) {
		bRet = CreateDir(pszDirectory);
	}

	return bRet;

}

/**
 * @brief     데이터베이스에 PDW 테이블에 레코드를 추가한다.
 * @param     STR_PDWDATA * pPDWData
 * @return    bool
 * @author    조철희 (churlhee.jo@lignex1.com)
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
            m_lOpInitID, GetPDWID(), iPLOBID, buffer, pPDWData->GetTotalPDW(), m_szRawDataFilename, E_EL_SCDT_PDW, pPDWData->x.ps.uiBank);

#elif defined(_ELINT_)
        sprintf_s(m_pszSQLString, MAX_SQL_SIZE, "INSERT INTO RAWDATA ( OP_INIT_ID, PDWID, PLOBID, TASK_ID, CREATE_TIME, CREATE_TIME_MS, COUNTOFDATA, FILENAME, DATA_TYPE ) values( \
                                                 '%ld', '%d', '%d', '%s', '%s', '%d', '%d', '%s', '0' )", \
            m_lOpInitID, GetPDWID(), iPLOBID, pPDWData->x.el.aucTaskID, buffer, iPLOBID, pPDWData->GetTotalPDW(), m_szRawDataFilename);

#elif defined(_XBAND_)
        sprintf_s(m_pszSQLString, MAX_SQL_SIZE, "INSERT INTO RAWDATA ( OP_INIT_ID, PDWID, PLOBID, TASK_ID, CREATE_TIME, CREATE_TIME_MS, COUNTOFDATA, FILENAME, DATA_TYPE ) values( \
                                                 '%ld', '%d', '%d', '%s', '%s', '%d', '%d', '%s', '0' )", \
            m_lOpInitID, GetPDWID(), iPLOBID, pPDWData->x.xb.aucTaskID, buffer, iPLOBID, pPDWData->GetTotalPDW(), m_szRawDataFilename);

#else
        sprintf_s(m_pszSQLString, MAX_SQL_SIZE, "INSERT INTO RAWDATA ( OP_INIT_ID, PDWID, PLOBID, TASK_ID, CREATE_TIME, CREATE_TIME_MS, COUNTOFDATA, FILENAME, DATA_TYPE ) values( \
                                                 '%ld', '%d', '%d', '%s', '%s', '%d', '%d', '%s', '0' )", \
            m_lOpInitID, GetPDWID(), pPDWData->x.el.aucTaskID, buffer, iPLOBID, pPDWData->GetTotalPDW(), m_szRawDataFilename);


#endif

#elif _SQLITE_
#ifdef _POCKETSONATA_
        sprintf(m_pszSQLString, "INSERT INTO RAWDATA ( PDWID, PLOBID, CREATE_TIME, CREATE_TIME_MS, COUNTOFDATA, FILENAME, DATA_TYPE, COL_BANK ) values( \
                                                 '%d', '%d', '%s', '0', '%d', '%s', '%d', '%d' )", \
            GetPDWID(), iPLOBID, buffer, pPDWData->GetTotalPDW(), m_szRawDataFilename, E_EL_SCDT_PDW, pPDWData->x.ps.uiBank);

#elif defined(_ELINT_)
        sprintf_s(m_pszSQLString, MAX_SQL_SIZE, "INSERT INTO RAWDATA ( PDWID, PLOBID, TASK_ID, CREATE_TIME, CREATE_TIME_MS, COUNTOFDATA, FILENAME, DATA_TYPE ) values( \
                                                 '%d', '%d', '%s', '%s', '%d', '%d', '%s', '0' )", \
            GetPDWID(), iPLOBID, pPDWData->x.el.aucTaskID, buffer, iPLOBID, pPDWData->GetTotalPDW(), m_szRawDataFilename);

#elif defined(_XBAND_)
        sprintf_s(m_pszSQLString, MAX_SQL_SIZE, "INSERT INTO RAWDATA ( PDWID, PLOBID, TASK_ID, CREATE_TIME, CREATE_TIME_MS, COUNTOFDATA, FILENAME, DATA_TYPE ) values( \
                                                 '%d', '%d', '%s', '%s', '%d', '%d', '%s', '0' )", \
            GetPDWID(), iPLOBID, pPDWData->x.xb.aucTaskID, buffer, iPLOBID, pPDWData->GetTotalPDW(), m_szRawDataFilename);
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
        Log(enNormal, ".InsertRAW[O%d, P%d, P%d]", m_lOpInitID, GetPDWID(), iPLOBID);

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


/**
 * @brief     DISP_FineAet
 * @param     SRxLOBData * pLOB
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-20, 19:36
 * @warning
 */
void CSigAnal::DISP_FineAet(SRxLOBData *pLOB)
{
    char buffer[500];

    // 신호 정보
    int iCnt = 0;
    iCnt += sprintf(&buffer[iCnt], "%s", g_szAetSignalType[pLOB->iSignalType]);

#ifdef __VXWORKS__
    // 방위
    iCnt += sprintf(&buffer[iCnt], " %4d(%4d,%4d)", UMUL(pLOB->fDOAMean, 1), UMUL(pLOB->fDOAMin, 1), UMUL(pLOB->fDOAMax, 1));

    // 주파수
    iCnt += sprintf(&buffer[iCnt], " %s", g_szAetFreqType[pLOB->iFreqType]);
    iCnt += sprintf(&buffer[iCnt], " %d[%d, %d]", UMUL(pLOB->fFreqMean, 1), UMUL(pLOB->fFreqMin, 1), UMUL(pLOB->fFreqMax, 1));

    // PRI
    iCnt += sprintf(&buffer[iCnt], " %s    ", g_szAetPriType[pLOB->iPRIType]);
    iCnt += sprintf(&buffer[iCnt], "%d(%d,%d), %2d", UMUL(pLOB->fPRIMean, 1), UMUL(pLOB->fPRIMin, 1), UMUL(pLOB->fPRIMax, 1), pLOB->iPRIPositionCount);

    // PW
    iCnt += sprintf(&buffer[iCnt], " %d(%d,%d)", UMUL(pLOB->fPWMean, 1), UMUL(pLOB->fPWMin, 1), UMUL(pLOB->fPWMax, 1));

    // PA
    iCnt += sprintf(&buffer[iCnt], " %d(%d,%d)", UMUL(pLOB->fPAMean, 1), UMUL(pLOB->fPAMin, 1), UMUL(pLOB->fPAMax, 1));

#else
    // 방위
    iCnt += sprintf(&buffer[iCnt], " %4.1f(%4.1f,%4.1f)", pLOB->fDOAMean, pLOB->fDOAMin, pLOB->fDOAMax);

    // 주파수
    iCnt += sprintf(&buffer[iCnt], " %s", g_szAetFreqType[pLOB->iFreqType]);
    iCnt += sprintf(&buffer[iCnt], " %.3f[%.3f, %.3f]", pLOB->fFreqMean, pLOB->fFreqMin, pLOB->fFreqMax);

    if (pLOB->iFreqType == _PATTERN_AGILE) {
        //printf( "%s(%s,%s)%s" , Comma( buff1 ), Comma( buff2 ), Comma( buff3 ), Comma( buff4 ) );
    }
    else {
        // printf( "%s(%s∼%s)%3d" , Comma( buff1 ), Comma( buff2 ), Comma( buff3 ), FRQCNV( pNewAet->aet.frq.band, temp )-FRQCNV( pNewAet->aet.frq.band, 0 ) );
        //printf( "%s(%s,%s)%3d" , buff1, buff2, buff3, FRQCNV( pManAet->aet.frq.band, temp )-FRQCNV( pManAet->aet.frq.band, 0 ) );
    }

    // PRI
    iCnt += sprintf(&buffer[iCnt], " %s    ", g_szAetPriType[pLOB->iPRIType]);
    iCnt += sprintf(&buffer[iCnt], "%0.1f(%.1f,%.1f), %2d", pLOB->fPRIMean, pLOB->fPRIMin, pLOB->fPRIMax, pLOB->iPRIPositionCount);

    // PW
    iCnt += sprintf(&buffer[iCnt], " %.2f(%.2f,%.2f)", pLOB->fPWMean, pLOB->fPWMin, pLOB->fPWMax);

    // PA
    iCnt += sprintf(&buffer[iCnt], " %.2f(%.2f,%.2f)", pLOB->fPAMean, pLOB->fPAMin, pLOB->fPAMax);

    // ID
    //printf( " [%d][%d,%d,%d,%d,%d]" , pManAet->aet.id.coAmbi, pManAet->aet.id.noIPL[0], pManAet->aet.id.noIPL[1], pManAet->aet.id.noIPL[2], pManAet->aet.id.noIPL[3], pManAet->aet.id.noIPL[4] );

#endif

    sprintf(&buffer[iCnt], " [%3d]", pLOB->iNumOfPDW);

    //printf( "\n%s", buffer );
    Log(enNormal, "\t%s", buffer);

}