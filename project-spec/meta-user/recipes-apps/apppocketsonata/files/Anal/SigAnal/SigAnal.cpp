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
        m_pDatabase = new Kompex::CSQLiteDatabase(pFileName, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, 0);

    }
    catch (Kompex::SQLiteException &sException) {
        std::cerr << "\nException Occured" << std::endl;
		sException.Show();
        std::cerr << "SQLite result code: " << sException.GetSqliteResultCode() << std::endl;
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

    //srand( (unsigned int) time(NULL) );

    SetSaveFile(true);

    _SAFE_NEW(m_pMidasBlue, CMIDASBlueFileFormat)

    szSize = CCommonUtils::CheckMultiplyOverflow( (int) sizeof(_PDW), (int) uiCoMaxPdw);
    m_stSavePDWData.pstPDW = NULL;
    _SAFE_MALLOC(m_stSavePDWData.pstPDW, _PDW, szSize)

    // DB 관련 변수 초기화
    InitDataFromDB();

}

/**
 * @brief     소멸자 처리를 한다.
 * @return    
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-18, 13:11
 * @warning
 */
CSigAnal::~CSigAnal()
{
    _SAFE_DELETE(m_pMidasBlue)

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
 * @brief     PDW 데이터의 단위를 장치에 맞ㄱ게 설정한다.
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


#elif defined(_701_)
	float _toaRes[_701::enUnknown_BW + 1] = { (float) 14.0625, (float) 6.48824, (float) 0.0 };

	_spOneSec = FDIV(1000000000, _toaRes[GetBandWidth()]);
	_spOneMilli = FDIV(1000000, _toaRes[GetBandWidth()]);
	_spOneMicrosec = FDIV(1000, _toaRes[GetBandWidth()]);
	_spOneNanosec = FDIV(1, _toaRes[GetBandWidth()]);

	_spAOAres = (float) 0.1;
	_spAMPres = (float)(0.25);
	_spPWres = _spOneMicrosec;

#endif
}

/**
 * @brief     분석하여 LOB 이외의 PDW 데이터를 저장한다.
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2008-01-22 12:40:25
 * @warning
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
 * @brief     중간 수집 데이터 파일을 저장한다.
 * @param     STR_PDWINDEX * pPDWIndex
 * @param     STR_PDWDATA * pstPDW
 * @param     bool bSaveFile
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-29, 11:14
 * @warning
 */
void CSigAnal::SaveGroupPDWFile( STR_PDWINDEX *pPDWIndex, STR_PDWDATA *pPDWData, bool bSaveFile )
{
    unsigned int i;

    PDWINDEX *pPdwIndex;
    _PDW *pPDW;

    if( m_bSaveFile == true && bSaveFile == true ) {
        m_stSavePDWData.SetTotalPDW( pPDWIndex->uiCount );

        pPdwIndex = pPDWIndex->pIndex;
        for( i = 0; i < pPDWIndex->uiCount ; ++i ) {
            pPDW = & pPDWData->pstPDW[*pPdwIndex++];
            memcpy( &m_stSavePDWData.pstPDW[i], pPDW, sizeof( _PDW ) );

        }

        // 수집한 PDW 파일 저장하기...
        InsertRAWData( &m_stSavePDWData, -1, false );
    }
}

/**
 * @brief     LOB 데이터에 해당되는 PDW 데이터만 저장한다.
 * @param     STR_EMITTER * pEmitter
 * @param     _PDW * pstPDW
 * @param     int iPLOBID
 * @param     bool bSaveFile
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
        InsertRAWData(&m_stSavePDWData, iPLOBID );
    }

}



#ifdef _MSSQL_
/**
 * @brief     데이터베이스 포인터를 리턴한다.
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
 * @brief     OPINITID 값을 DB 에서 로딩하여 다음 값으로 설장한다.
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
//     char buffer[400];
// 
//     sprintf_s(buffer, sizeof(buffer), "select max(OP_INIT_ID) from LOBDATA");
//     m_uiOpInitID = GetINTData(buffer) + 1;
// 
//     sprintf_s(buffer, sizeof(buffer), "select max(OP_INIT_ID) from RAWDATA");
//     m_uiOpInitID = max(m_uiOpInitID, (unsigned int) GetINTData(buffer) + 1);

#endif

#else
    // m_lOpInitID = _spOne;


#endif

}

/**
 * @brief     InsertRAWData
 * @param     STR_PDWDATA * pPDWData
 * @param     int iGroupID
 * @param     int iPLOBID
 * @param     bool bInsertDB
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-01-23, 17:53
 * @warning
 */
void CSigAnal::InsertRAWData(STR_PDWDATA *pPDWData, int iPLOBID, bool bInsertDB )
{
    bool bRet = true;
    char buffer[100] = { 0 };
    char szDirectory[500], szRawDataPathname[600];

    struct timespec tiNow;

    CCommonUtils::GetCollectTime(&tiNow, GetColTime(), GetColTimeMs() );
    CCommonUtils::getFileNamingDesignatedTime(buffer, sizeof(buffer), tiNow.tv_sec);

#ifdef _ELINT_
    sprintf_s(szDirectory, "%s\\수집소_%d\\%s", SHARED_DATA_DIRECTORY, pPDWData->x.el.iCollectorID, pPDWData->x.el.aucTaskID);

#elif defined(_701_)
	sprintf_s(szDirectory, "%s/수집소_%d/%s", SHARED_DATA_DIRECTORY, pPDWData->x._701.GetCollectorID(), pPDWData->x._701.aucTaskID);


#elif defined(_XBAND_)
    //sprintf_s( szDirectory, "%s\\수집소_%d\\%s\\%s", SHARED_DATA_DIRECTORY, pPDWData->x.el.iCollectorID, buffer, pPDWData->x.el.aucTaskID );
    sprintf_s(szDirectory, "%s/수집소_%d/%s", SHARED_DATA_DIRECTORY, pPDWData->x.xb.GetCollectorID(), pPDWData->x.xb.aucTaskID);

#elif defined(_POCKETSONATA_)
    //strftime(buffer, 100, "%Y-%m-%d", pstTime);
    sprintf(szDirectory, _T("%s/%s/BRD_%d/%s"), SHARED_DATA_DIRECTORY, buffer, pPDWData->x.ps.uiBoardID, g_szCollectBank[pPDWData->x.ps.uiBank]);

#else
    sprintf(szDirectory, "%s/BRD", pLocalDirectory);

#endif

    m_szRawDataFilename[0] = NULL;


#ifdef _POCKETSONATA_

#else
    if ( /*pstTime != NULL &&*/ m_bSaveFile == true) {
        bRet = CreateDir(szDirectory);

        if ( bRet == true ) {
            // 순수 신호 수집한 데이터
            if( iPLOBID == 0 ) {
                sprintf( m_szRawDataFilename, _T( "#%d[%s]_D%06d_%s" ), pPDWData->GetCollectorID(), buffer, GetPDWID(), PDW_EXT );
            }
            // 그룹화 신호 수집 데이터
            else if( iPLOBID < 0 ) {
                sprintf( m_szRawDataFilename, _T( "#%d[%s]_D%06d_[G%02d]%s" ), pPDWData->GetCollectorID(), buffer, GetPDWID(), GetCoGroup(), PDW_EXT );
            }
            // 분석 신호 수집 데이터
            else {
                sprintf( m_szRawDataFilename, _T( "#%d[%s]_D%06d_[G%02d][L%02d]%s" ), pPDWData->GetCollectorID(), buffer, GetPDWID(), GetCoGroup(), iPLOBID, PDW_EXT );
            }

            sprintf(szRawDataPathname, _T("%s/%s"), szDirectory, m_szRawDataFilename);
            m_pMidasBlue->SaveRawDataFile( szRawDataPathname, E_EL_SCDT_PDW, pPDWData->pstPDW, & pPDWData->x, pPDWData->GetTotalPDW() );

            if (m_bDBThread == false) {
                if( bInsertDB == true ) {
                    // RAWDATA 테이블에 저장
                    InsertToDB_RAW( pPDWData, iPLOBID );
                }
            }
            else {
                TRACE("Push the data for InsertToDB_RAW()");
            }
        }
    }


#endif


}

/**
 * @brief     데이터베이스에 PDW 테이블에 레코드를 추가한다.
 * @param     STR_PDWDATA * pPDWData
 * @param     int iPLOBID
 * @return    bool
 * @exception
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
                                                 '%d', '%d', '%d', '%s', '0', '%d', '%s', '%d', '%d' )", \
            m_uiOpInitID, GetPDWID(), iPLOBID, buffer, pPDWData->GetTotalPDW(), m_szRawDataFilename, E_EL_SCDT_PDW, pPDWData->x.ps.uiBank);

#elif defined(_ELINT_)
        sprintf_s(m_pszSQLString, MAX_SQL_SIZE, "INSERT INTO RAWDATA ( OP_INIT_ID, PDWID, PLOBID, TASK_ID, CREATE_TIME, CREATE_TIME_MS, COUNTOFDATA, FILENAME, DATA_TYPE ) values( \
                                                 '%d', '%d', '%d', '%s', '%s', '%d', '%d', '%s', '0' )", \
			GetOpInitID(), GetPDWID(), iPLOBID, pPDWData->x.el.aucTaskID, buffer, iPLOBID, pPDWData->GetTotalPDW(), m_szRawDataFilename);
#elif defined(_701_)
		sprintf_s(m_pszSQLString, MAX_SQL_SIZE, "INSERT INTO RAWDATA ( OP_INIT_ID, PDWID, PLOBID, TASK_ID, CREATE_TIME, CREATE_TIME_MS, COUNTOFDATA, FILENAME, DATA_TYPE ) values( \
                                                 '%d', '%d', '%d', '%s', '%s', '%d', '%d', '%s', '0' )", \
			GetOpInitID(), GetPDWID(), iPLOBID, pPDWData->x._701.aucTaskID, buffer, iPLOBID, pPDWData->GetTotalPDW(), m_szRawDataFilename);


#elif defined(_XBAND_)
        sprintf_s(m_pszSQLString, MAX_SQL_SIZE, "INSERT INTO RAWDATA ( OP_INIT_ID, PDWID, PLOBID, TASK_ID, CREATE_TIME, CREATE_TIME_MS, COUNTOFDATA, FILENAME, DATA_TYPE ) values( \
                                                 '%d', '%d', '%d', '%s', '%s', '%d', '%d', '%s', '0' )", \
            GetOpInitID(), GetPDWID(), iPLOBID, pPDWData->x.xb.aucTaskID, buffer, iPLOBID, pPDWData->GetTotalPDW(), m_szRawDataFilename);

#else
        sprintf_s(m_pszSQLString, MAX_SQL_SIZE, "INSERT INTO RAWDATA ( OP_INIT_ID, PDWID, PLOBID, TASK_ID, CREATE_TIME, CREATE_TIME_MS, COUNTOFDATA, FILENAME, DATA_TYPE ) values( \
                                                 '%d', '%d', '%d', '%s', '%s', '%d', '%d', '%s', '0' )", \
            m_uiOpInitID, GetPDWID(), pPDWData->x.el.aucTaskID, buffer, iPLOBID, pPDWData->GetTotalPDW(), m_szRawDataFilename);


#endif

#elif _SQLITE_
#ifdef _POCKETSONATA_
        sprintf(m_pszSQLString, "INSERT INTO RAWDATA ( OP_INIT_ID, PDWID, PLOBID, CREATE_TIME, CREATE_TIME_MS, COUNTOFDATA, FILENAME, DATA_TYPE, COL_BANK ) values( \
                                                 '%d', '%d', '%d', '%s', '0', '%d', '%s', '%d', '%d' )", \
			g_pTheSysConfig->GetOpInitID(), GetPDWID(), iPLOBID, buffer, pPDWData->GetTotalPDW(), m_szRawDataFilename, E_EL_SCDT_PDW, pPDWData->x.ps.uiBank);

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
                                                 '%d', '%d', '%d', '%s', '%s', '%d', '%d', '%s', '0' )", \
            m_uiOpInitID, GetPDWID(), pPDWData->x.el.aucTaskID, buffer, iPLOBID, pPDWData->GetTotalPDW(), m_szRawDataFilename);

#endif

#endif


#ifdef _MSSQL_
        DECLARE_BEGIN_CHECKODBC

        CODBCRecordset theRS = CODBCRecordset(m_pMyODBC);

        theRS.Open(m_pszSQLString);
        Log(enNormal, ".InsertRAW[O%d, P%d, P%d]", GetOpInitID(), GetPDWID(), iPLOBID);

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
            catch (Kompex::SQLiteException &sException) {
                LOGMSG1(enError, " m_pszSQLString[%s]", m_pszSQLString);
                bRet = false;
                std::cerr << "\nException Occured" << std::endl;
				sException.Show();
                std::cerr << "SQLite result code: " << sException.GetSqliteResultCode() << std::endl;
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
 * @brief     LOB 데이터를 출력한다.
 * @param     SRxLOBData * pLOB
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-20, 19:36
 * @warning
 */
void CSigAnal::DISP_FineLOB(SRxLOBData *pLOB)
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

    sprintf(&buffer[iCnt], " [%3d/%3d]", pLOB->iNumOfPDW, pLOB->iTotalOfPDW );

    //printf( "\n%s", buffer );
    Log(enNormal, "\t%s", buffer);

}

/**
 * @brief     LOB 데이터를 DB에 삽입한다.
 * @param     SRxLOBData * pLOBData
 * @param     int iCoLOBData
 * @param     bool bDBInsert
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-06-02, 11:11
 * @warning
 */
void CSigAnal::InsertToDB_LOB( SRxLOBData *pLOBData, int iCoLOBData, bool bDBInsert )
{

    if( bDBInsert == true ) {
        int i;

        for( i = 0 ; i < iCoLOBData ; ++i ) {
            InsertToDB_LOB( pLOBData );

            // FREQ 레벨값 저장
            if( pLOBData->iFreqPositionCount >= _spTwo ) {
                InsertToDB_Position( pLOBData, true );
            }
            // PRI 레벨값 저장
            if( pLOBData->iPRIPositionCount >= _spTwo ) {
                InsertToDB_Position( pLOBData, false );
            }

            ++pLOBData;
        }
    }

}

/**
 * @brief     주파수 및 PRI POSITION 값을 DB에 삽입한다.
 * @param     SRxLOBData * pLOBData
 * @param     bool bFreqSeq
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-06-05, 17:02
 * @warning
 */
bool CSigAnal::InsertToDB_Position( SRxLOBData *pLOBData, bool bFreqSeq )
{
    bool bRet = true;

#if defined(_MSSQL_)
    int i;
    size_t szIndex;

    m_pszSQLString[0] = NULL;

    strcpy( m_pszSQLString, "INSERT INTO LOB_POSITION ( OP_INIT_ID, PDWID, PLOBID, LOBID, ABTID, AETID, SEQ_TYPE, POSITION_COUNT, " );
    szIndex = strlen( m_pszSQLString );
    for( i = 1 ; i < pLOBData->iFreqPositionCount || i < pLOBData->iPRIPositionCount ; ++i ) {
        szIndex += (size_t) sprintf( &m_pszSQLString[szIndex], "SEQ_%02d, ", i );
    }
    szIndex += (size_t) sprintf( &m_pszSQLString[szIndex], "SEQ_%02d ) values ( ", i );

    szIndex += (size_t) sprintf( &m_pszSQLString[szIndex], "'%ld', '%ld', '%ld', '%ld', '%ld', '%ld', '%d', ", GetOpInitID(), pLOBData->uiPDWID, pLOBData->uiPLOBID, pLOBData->uiLOBID, pLOBData->uiABTID, pLOBData->uiAETID, bFreqSeq );
    if( bFreqSeq == true ) {
        szIndex += sprintf( &m_pszSQLString[szIndex], "'%d', ", pLOBData->iFreqPositionCount );
        for( i = 0 ; i < pLOBData->iFreqPositionCount - 1 ; ++i ) {
            szIndex += (size_t) sprintf( &m_pszSQLString[szIndex], "'%f', ", pLOBData->fFreqSeq[i] );
        }
        sprintf( &m_pszSQLString[szIndex], "'%f' )", pLOBData->fFreqSeq[i] );
    }
    else {
        szIndex += (size_t) sprintf( &m_pszSQLString[szIndex], "'%d', ", pLOBData->iPRIPositionCount );
        for( i = 0 ; i < pLOBData->iPRIPositionCount - 1 ; ++i ) {
            szIndex += (size_t) sprintf( &m_pszSQLString[szIndex], "'%f', ", pLOBData->fPRISeq[i] );
        }
        sprintf( &m_pszSQLString[szIndex], "'%f' )", pLOBData->fPRISeq[i] );

    }

#elif defined(_SQLITE_)
    int i;
    size_t szIndex;

    m_pszSQLString[0] = NULL;

    strcpy( m_pszSQLString, "INSERT INTO LOB_POSITION ( SEQ_TYPE, PDWID, PLOBID, LOBID, ABTID, AETID, POSITION_COUNT, " );
    szIndex = strlen( m_pszSQLString );
    for( i = 1 ; i < pLOBData->iFreqPositionCount || i < pLOBData->iPRIPositionCount ; ++i ) {
        szIndex += (size_t) sprintf( &m_pszSQLString[szIndex], "SEQ_%02d, ", i );
    }
    szIndex += (size_t) sprintf( &m_pszSQLString[szIndex], "SEQ_%02d ) values ( ", i );

    if( bFreqSeq == true ) {
        szIndex += (size_t) sprintf( &m_pszSQLString[szIndex], "'%d', '%d', '%d', '%d', '%d', '%d', '%d', ", bFreqSeq, pLOBData->uiPDWID, pLOBData->uiPLOBID, pLOBData->uiLOBID, pLOBData->uiABTID, pLOBData->uiAETID, pLOBData->iFreqPositionCount );
        for( i = 0 ; i < pLOBData->iFreqPositionCount - 1 ; ++i ) {
            szIndex += (size_t) sprintf( &m_pszSQLString[szIndex], "'%f', ", pLOBData->fFreqSeq[i] );
        }
        sprintf( &m_pszSQLString[szIndex], "'%f' )", pLOBData->fFreqSeq[i] );
    }
    else {
        szIndex += (size_t) sprintf( &m_pszSQLString[szIndex], "'%d', '%d', '%d', '%d', '%d', '%d', '%d', ", bFreqSeq, pLOBData->uiPDWID, pLOBData->uiPLOBID, pLOBData->uiLOBID, pLOBData->uiABTID, pLOBData->uiAETID, pLOBData->iPRIPositionCount );
        for( i = 0 ; i < pLOBData->iPRIPositionCount - 1 ; ++i ) {
            szIndex += (size_t) sprintf( &m_pszSQLString[szIndex], "'%f', ", pLOBData->fPRISeq[i] );
        }
        sprintf( &m_pszSQLString[szIndex], "'%f' )", pLOBData->fPRISeq[i] );

    }

#endif

#ifdef _MSSQL_
    if( m_pszSQLString[0] != NULL ) {

        DECLARE_BEGIN_CHECKODBC

        CODBCRecordset theRS = CODBCRecordset( m_pMyODBC );

        theRS.Open( m_pszSQLString );
        theRS.Close();

        DECLARE_END_CHECKODBC
    }

#elif _SQLITE_ 
    if( m_pszSQLString[0] != NULL ) {

        try {
            Kompex::SQLiteStatement stmt( m_pDatabase );
            stmt.SqlStatement( m_pszSQLString );
            Log( enDebug, ".InsertLOB_Position[L%d][C%d/%d]", pLOBData->uiLOBID, pLOBData->iFreqPositionCount, pLOBData->iPRIPositionCount );

            // do not forget to clean-up
            stmt.FreeQuery();
        }
        catch( Kompex::SQLiteException &sException) {
            bRet = false;
            std::cerr << "\nException Occured" << std::endl;
			sException.Show();
            std::cerr << "SQLite result code: " << sException.GetSqliteResultCode() << std::endl;
        }
    }

#else

#endif

    return bRet;

}

/**
 * @brief     LOB 데이터를 DB에 삽입한다.
 * @param     SRxLOBData * pLOBData
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-06-02, 11:36
 * @warning
 */
void CSigAnal::InsertToDB_LOB( SRxLOBData *pLOBData )
{
    bool bRet = true;

#ifdef _MSSQL_
    char buffer[100] = { 0 };

    m_pszSQLString[0] = NULL;

    CCommonUtils::getStringDesignatedTime( buffer, sizeof( buffer ), pLOBData->tiContactTime );

#ifdef _POCKETSONATA_
    sprintf_s( m_pszSQLString, MAX_SQL_SIZE, "INSERT INTO LOBDATA ( \
                                                OP_INIT_ID, PDWID, PLOBID, LOBID, ABTID, AETID, TASK_ID, CONTACT_TIME, CONTACT_TIME_MS, \
                                                SIGNAL_TYPE, DOA_MEAN, DOA_MIN, DOA_MAX, DI_RATIO, \
                                                FREQ_TYPE, FREQ_PATTERN_TYPE, FREQ_PATTERN_PERIOD, FREQ_MEAN, FREQ_MIN, FREQ_MAX, FREQ_POSITION_COUNT, \
                                                PRI_TYPE, PRI_PATTERN_TYPE, PRI_PATTERN_PERIOD, PRI_MEAN, PRI_MIN, PRI_MAX, PRI_JITTER_RATIO, PRI_POSITION_COUNT, \
                                                PW_MEAN, PW_MIN, PW_MAX, PA_MEAN, PA_MIN, PA_MAX, NUM_PDW, \
                                                LATITUDE, LONGITUDE, RADARMODE_NAME, RADARMODE_INDEX ) \
                                                values( '%ld', '%ld', '%ld', '%ld', '%ld', '%ld', '%s', '%s', '%d', \
                                                '%d', '%f', '%f', '%f', '%d', \
                                                '%d', '%d', '%f', '%f', '%f', '%f', '%d', \
                                                '%d', '%d', '%f', '%f', '%f', '%f', '%f', '%d', \
                                                '%f', '%f', '%f', '%f', '%f', '%f', '%d', \
                                                '%f', '%f', '%s', '%d' )", \
		GetOpInitID(), pLOBData->uiPDWID, pLOBData->uiPLOBID, pLOBData->uiLOBID, pLOBData->uiABTID, pLOBData->uiAETID, pLOBData->aucTaskID, buffer, pLOBData->tiContactTimems, \
        pLOBData->iSignalType, pLOBData->fDOAMean, pLOBData->fDOAMin, pLOBData->fDOAMax, pLOBData->iDIRatio, \
        pLOBData->iFreqType, pLOBData->iFreqPatternType, pLOBData->fFreqPatternPeriod, pLOBData->fFreqMean, pLOBData->fFreqMin, pLOBData->fFreqMax, pLOBData->iFreqPositionCount, \
        pLOBData->iPRIType, pLOBData->iPRIPatternType, pLOBData->fPRIPatternPeriod, pLOBData->fPRIMean, pLOBData->fPRIMin, pLOBData->fPRIMax, pLOBData->fPRIJitterRatio, pLOBData->iPRIPositionCount, \
        pLOBData->fPWMean, pLOBData->fPWMin, pLOBData->fPWMax, pLOBData->fPAMean, pLOBData->fPAMin, pLOBData->fPAMax, pLOBData->iNumOfPDW, \
        pLOBData->fCollectLatitude, pLOBData->fCollectLongitude, pLOBData->szRadarModeName, pLOBData->iRadarModeIndex );

#elif _701_
	sprintf_s(m_pszSQLString, MAX_SQL_SIZE, "INSERT INTO LOBDATA ( \
                                                OP_INIT_ID, PDWID, PLOBID, LOBID, ABTID, AETID, TASK_ID, CONTACT_TIME, CONTACT_TIME_MS, \
                                                SIGNAL_TYPE, DOA_MEAN, DOA_MIN, DOA_MAX, DI_RATIO, \
                                                FREQ_TYPE, FREQ_PATTERN_TYPE, FREQ_PATTERN_PERIOD, FREQ_MEAN, FREQ_MIN, FREQ_MAX, FREQ_POSITION_COUNT, \
                                                PRI_TYPE, PRI_PATTERN_TYPE, PRI_PATTERN_PERIOD, PRI_MEAN, PRI_MIN, PRI_MAX, PRI_JITTER_RATIO, PRI_POSITION_COUNT, \
                                                PW_MEAN, PW_MIN, PW_MAX, PA_MEAN, PA_MIN, PA_MAX, NUM_PDW, \
                                                LATITUDE, LONGITUDE, RADARMODE_NAME, RADARMODE_INDEX ) \
                                                values( '%ld', '%ld', '%ld', '%ld', '%ld', '%ld', '%s', '%s', '%d', \
                                                '%d', '%f', '%f', '%f', '%d', \
                                                '%d', '%d', '%f', '%f', '%f', '%f', '%d', \
                                                '%d', '%d', '%f', '%f', '%f', '%f', '%f', '%d', \
                                                '%f', '%f', '%f', '%f', '%f', '%f', '%d', \
                                                '%f', '%f', '%s', '%d' )", \
		GetOpInitID(), pLOBData->uiPDWID, pLOBData->uiPLOBID, pLOBData->uiLOBID, pLOBData->uiABTID, pLOBData->uiAETID, pLOBData->aucTaskID, buffer, pLOBData->tiContactTimems, \
		pLOBData->iSignalType, pLOBData->fDOAMean, pLOBData->fDOAMin, pLOBData->fDOAMax, pLOBData->iDIRatio, \
		pLOBData->iFreqType, pLOBData->iFreqPatternType, pLOBData->fFreqPatternPeriod, pLOBData->fFreqMean, pLOBData->fFreqMin, pLOBData->fFreqMax, pLOBData->iFreqPositionCount, \
		pLOBData->iPRIType, pLOBData->iPRIPatternType, pLOBData->fPRIPatternPeriod, pLOBData->fPRIMean, pLOBData->fPRIMin, pLOBData->fPRIMax, pLOBData->fPRIJitterRatio, pLOBData->iPRIPositionCount, \
		pLOBData->fPWMean, pLOBData->fPWMin, pLOBData->fPWMax, pLOBData->fPAMean, pLOBData->fPAMin, pLOBData->fPAMax, pLOBData->iNumOfPDW, \
		pLOBData->fCollectLatitude, pLOBData->fCollectLongitude, pLOBData->szRadarModeName, pLOBData->iRadarModeIndex);

#else
    sprintf_s( m_pszSQLString, MAX_SQL_SIZE, "INSERT INTO LOBDATA ( \
												OP_INIT_ID, PDWID, PLOBID, LOBID, ABTID, AETID, TASK_ID, CONTACT_TIME, CONTACT_TIME_MS, \
												SIGNAL_TYPE, DOA_MEAN, DOA_MIN, DOA_MAX, DOA_MODE, DI_RATIO, \
												FREQ_TYPE, FREQ_PATTERN_TYPE, FREQ_PATTERN_PERIOD, FREQ_MEAN, FREQ_MIN, FREQ_MAX, FREQ_MODE, FREQ_POSITION_COUNT, \
												PRI_TYPE, PRI_PATTERN_TYPE, PRI_PATTERN_PERIOD, PRI_MEAN, PRI_MIN, PRI_MAX, PRI_MODE, PRI_JITTER_RATIO, PRI_POSITION_COUNT, \
												PW_MEAN, PW_MIN, PW_MAX, PW_MODE, PA_MEAN, PA_MIN, PA_MAX, PA_MODE, IS_STORED_PDW, NUM_PDW, \
												COLLECTOR_ID, LATITUDE, LONGITUDE, RADARMODE_NAME, RADARMODE_INDEX ) \
												values( '%ld', '%d', '%d', '%d', '%d', '%d', '%s', '%s', '%d', \
												'%d', '%f', '%f', '%f', '%f', '%d', \
												'%d', '%d', '%f', '%f', '%f', '%f', '%f', '%d', \
												'%d', '%d', '%f', '%f', '%f', '%f', '%f', '%f', '%d', \
												'%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%d', '%d', \
												'%d', '%f', '%f', '%s', '%d' )", \
        GetOpInitID(), pLOBData->uiPDWID, pLOBData->uiPLOBID, pLOBData->uiLOBID, pLOBData->uiABTID, pLOBData->uiAETID, pLOBData->aucTaskID, buffer, pLOBData->tiContactTimems, \
        pLOBData->iSignalType, pLOBData->fDOAMean, pLOBData->fDOAMin, pLOBData->fDOAMax, pLOBData->fDOAMode, pLOBData->iDIRatio, \
        pLOBData->iFreqType, pLOBData->iFreqPatternType, pLOBData->fFreqPatternPeriod, pLOBData->fFreqMean, pLOBData->fFreqMin, pLOBData->fFreqMax, pLOBData->fFreqMode, pLOBData->iFreqPositionCount, \
        pLOBData->iPRIType, pLOBData->iPRIPatternType, pLOBData->fPRIPatternPeriod, pLOBData->fPRIMean, pLOBData->fPRIMin, pLOBData->fPRIMax, pLOBData->fPRIMode, pLOBData->fPRIJitterRatio, pLOBData->iPRIPositionCount, \
        pLOBData->fPWMean, pLOBData->fPWMin, pLOBData->fPWMax, pLOBData->fPWMode, pLOBData->fPAMean, pLOBData->fPAMin, pLOBData->fPAMax, pLOBData->fPAMode, m_bSaveFile, pLOBData->iNumOfPDW, \
        pLOBData->iCollectorID, pLOBData->fCollectLatitude, pLOBData->fCollectLongitude, pLOBData->szRadarModeName, pLOBData->iRadarModeIndex );

#endif

#elif _SQLITE_
    char buffer[100] = { 0 };

    m_pszSQLString[0] = NULL;

    CCommonUtils::getStringDesignatedTime( buffer, sizeof( buffer ), pLOBData->tiContactTime );

#if defined(_POCKETSONATA_)
    sprintf( m_pszSQLString, "INSERT INTO LOBDATA ( \
							PDWID, PLOBID, LOBID, ABTID, AETID, CONTACT_TIME, CONTACT_TIME_MS, PRIMARY_ELNOT, PRIMARY_MODECODE, SECONDARY_ELNOT, SECONDARY_MODECODE, \
							TERTIARY_ELNOT, TERTIARY_MODECODE, MODULATION_CODE, RADARMODE_NAME, NICK_NAME, RADARMODE_INDEX, \
							SIGNAL_TYPE, DOA_MEAN, DOA_MIN, DOA_MAX, DOA_DEV, DOA_STD, DI_RATIO, \
							FREQ_TYPE, FREQ_PATTERN_TYPE, FREQ_PATTERN_PERIOD, FREQ_MEAN, FREQ_MIN, FREQ_MAX, FREQ_DEV, FREQ_POSITION_COUNT, FREQ_ELEMENT_COUNT, \
							PRI_TYPE, PRI_PATTERN_TYPE, PRI_PATTERN_PERIOD, PRI_MEAN, PRI_MIN, PRI_MAX, PRI_DEV, PRI_JITTER_RATIO, PRI_POSITION_COUNT, PRI_ELEMENT_COUNT, \
							PW_MEAN, PW_MIN, PW_MAX, PW_DEV, \
							PA_MEAN, PA_MIN, PA_MAX, PA_DEV, \
							SCAN_TYPE, SCAN_PRD, \
							INTRA_TYPE, INTRA_TYPE_DETAIL, INTRA_FRQ_MEAN, INTRA_FRQ_MIN, INTRA_FRQ_MAX, INTRA_FRQ_DEVIATION, \
							LATITUDE, LONGITUDE, \
							IS_FILTERED, NUM_PDW ) VALUES \
							( %d, %d, %d, %d, %d, '%s', %d, '%s', '%s', '%s', '%s', \
							'%s', '%s', '%s', '%s', '%s', %d, \
							%d, %f, %f, %f, %f, %d, \
							%d, %d, %f, %f, %f, %f, %f, %d, %d, \
							%d, %d, %f, %f, %f, %f, %f, %f, %d, %d, \
							%f, %f, %f, %f, \
							%f, %f, %f, %f, \
							%d, %f, \
							%d, %d, %f, %f, %f, %f, \
							%f, %f, \
							%d, %d )", \
        pLOBData->uiPDWID, pLOBData->uiPLOBID, pLOBData->uiLOBID, pLOBData->uiABTID, pLOBData->uiAETID, buffer, pLOBData->tiContactTimems, \
        pLOBData->szPrimaryELNOT, pLOBData->szPrimaryModeCode, \
        pLOBData->szSecondaryELNOT, pLOBData->szSecondaryModeCode, \
        pLOBData->szTertiaryELNOT, pLOBData->szTertiaryModeCode, \
        pLOBData->szModulationCode, pLOBData->szRadarModeName, pLOBData->szNickName, \
        pLOBData->iRadarModeIndex, \
        pLOBData->iSignalType, pLOBData->fDOAMean, pLOBData->fDOAMin, pLOBData->fDOAMax, pLOBData->fDOADeviation, pLOBData->iDIRatio, \
        pLOBData->iFreqType, pLOBData->iFreqPatternType, pLOBData->fFreqPatternPeriod, \
        pLOBData->fFreqMean, pLOBData->fFreqMin, pLOBData->fFreqMax, pLOBData->fFreqDeviation, pLOBData->iFreqPositionCount, pLOBData->iFreqElementCount, \
        pLOBData->iPRIType, pLOBData->iPRIPatternType, pLOBData->fPRIPatternPeriod, \
        pLOBData->fPRIMean, pLOBData->fPRIMin, pLOBData->fPRIMax, pLOBData->fPRIDeviation, pLOBData->fPRIJitterRatio, pLOBData->iPRIPositionCount, pLOBData->iPRIElementCount, \
        pLOBData->fPWMean, pLOBData->fPWMin, pLOBData->fPWMax, pLOBData->fPWDeviation, \
        pLOBData->fPAMean, pLOBData->fPAMin, pLOBData->fPAMax, pLOBData->fPWDeviation, \
        pLOBData->iScanType, pLOBData->fScanPeriod, \
        pLOBData->iMOPType, pLOBData->iDetailMOPType, pLOBData->fMOPMaxFreq, pLOBData->fMOPMinFreq, pLOBData->fMOPMeanFreq, pLOBData->fMOPFreqDeviation, \
        pLOBData->fCollectLatitude, pLOBData->fCollectLongitude, \
        0, pLOBData->iNumOfPDW );

#else
    sprintf( m_pszSQLString, "INSERT INTO LOBDATA ( \
                             SEQ_NUM, PDWID, PLOBID, LOBID, ABTID, AETID, CONTACT_TIME, CONTACT_TIME_MS, \
                             PRIMARY_ELNOT, PRIMARY_MODECODE, SECONDARY_ELNOT, SECONDARY_MODECODE, \
                             TERTIARY_ELNOT, TERTIARY_MODECODE, \
                             MODULATION_CODE, RADARMODE_NAME, NICK_NAME, FUNC_CODE, RADARMODE_INDEX, \
                             SIGNAL_TYPE, DOA_MEAN, DOA_MIN, DOA_MAX, DOA_DEV, DOA_STD, DI_RATIO, \
                             FREQ_TYPE, FREQ_PATTERN_TYPE, FREQ_PATTERN_PERIOD, FREQ_MEAN, FREQ_MIN, FREQ_MAX, FREQ_DEV, FREQ_POSITION_COUNT, FREQ_ELEMENT_COUNT, \
                             PRI_TYPE, PRI_PATTERN_TYPE, PRI_PATTERN_PERIOD, PRI_MEAN, PRI_MIN, PRI_MAX, PRI_DEV, PRI_JITTER_RATIO, PRI_POSITION_COUNT, PRI_ELEMENT_COUNT, \
                             PW_MEAN, PW_MIN, PW_MAX, PW_DEV, \
                             PA_MEAN, PA_MIN, PA_MAX, PA_DEV, \
                             LAT, LONG, \
                             IS_DATA_STORE, IS_FILTERED, NUM_PDW, NUM_IQ ) VALUES \
                             ( %d, %d, %d, %d, %d, %d, \"%s\", %d, \
                             \"%s\", \"%s\", \"%s\", \"%s\", \
                             \"%s\", \"%s\", \
                             \"%s\", \"%s\", \"%s\", \"%s\", %d, \
                             %d, %f, %f, %f, %f, %f, %d, \
                             %d, %d, %f, %f, %f, %f, %f, %d, %d, \
                             %d, %d, %f, %f, %f, %f, %f, %f, %d, %d, \
                             %f, %f, %f, %f, \
                             %f, %f, %f, %f, \
                             %f, %f, \
                             %d, %d, %d, %d )", \
        m_nSeqNum, pLOBData->uiPDWID, pLOBData->uiPLOBID, pLOBData->uiLOBID, pLOBData->uiABTID, pLOBData->uiAETID, buffer, pLOBData->tiContactTimems, \
        pLOBData->szPrimaryELNOT, pLOBData->szPrimaryModeCode, pLOBData->szSecondaryELNOT, pLOBData->szSecondaryModeCode, \
        pLOBData->szTertiaryELNOT, pLOBData->szTertiaryModeCode, \
        pLOBData->szModulationCode, pLOBData->szRadarModeName, pLOBData->szNickName, pLOBData->szFuncCode, pLOBData->iRadarModeIndex, \
        pLOBData->iSignalType, pLOBData->fDOAMean, pLOBData->fDOAMin, pLOBData->fDOAMax, pLOBData->fDOADeviation, pLOBData->fDOASDeviation, pLOBData->iDIRatio, \
        pLOBData->iFreqType, pLOBData->iFreqPatternType, pLOBData->fFreqPatternPeriod, \
        pLOBData->fFreqMean, pLOBData->fFreqMin, pLOBData->fFreqMax, pLOBData->fFreqDeviation, pLOBData->iFreqPositionCount, pLOBData->iFreqElementCount, \
        pLOBData->iPRIType, pLOBData->iPRIPatternType, pLOBData->fPRIPatternPeriod, \
        pLOBData->fPRIMean, pLOBData->fPRIMin, pLOBData->fPRIMax, pLOBData->fPRIDeviation, pLOBData->fPRIJitterRatio, pLOBData->iPRIPositionCount, pLOBData->iPRIElementCount, \
        pLOBData->fPWMean, pLOBData->fPWMin, pLOBData->fPWMax, pLOBData->fPWDeviation, \
        pLOBData->fPAMean, pLOBData->fPAMin, pLOBData->fPAMax, pLOBData->fPADeviation, \
        pLOBData->fCollectLatitude, pLOBData->fCollectLongitude, \
        pLOBData->iIsStoreData, pExt->aetAnal.isFiltered, pLOBData->iNumOfPDW, pLOBData->iNumOfIQ );

#endif

#else

#endif

    // 여기서 부터 SQL 문을 실행 합니다.
#ifdef _MSSQL_
    //if( m_pszSQLString[0] != NULL ) {
        DECLARE_BEGIN_CHECKODBC

        char buffer[100];

        CODBCRecordset theRS = CODBCRecordset( m_pMyODBC );

        CCommonUtils::getStringDesignatedTime( buffer, sizeof( buffer ), pLOBData->tiContactTime );

        theRS.Open( m_pszSQLString );
        Log( enDebug, ".InsertLOB[O%d][A%d][B%d][L%d]", GetOpInitID(), pLOBData->uiAETID, pLOBData->uiABTID, pLOBData->uiLOBID );

        theRS.Close();

        DECLARE_END_CHECKODBC
//     }
//     else {
//         bRet = false;
//     }
#elif _SQLITE_  
    if( m_pszSQLString[0] != NULL ) {
        try {
            Kompex::SQLiteStatement stmt( m_pDatabase );
            stmt.SqlStatement( m_pszSQLString );
            Log( enDebug, ".InsertLOB[A%d][B%d][L%d]", pLOBData->uiAETID, pLOBData->uiABTID, pLOBData->uiLOBID );

            if( pLOBData->iRadarModeIndex > 0 ) {
                stmt.SqlStatement( m_pszSQLString );
                //m_pIdentifyAlg->UpdateRadarMode( pLOBData );
            }

            // do not forget to clean-up
            stmt.FreeQuery();

        }
        catch( Kompex::SQLiteException &sException) {
            LOGMSG1( enError, " m_pszSQLString[%s]", m_pszSQLString );
            bRet = false;
            std::cerr << "\nException Occured" << std::endl;
			sException.Show();
            std::cerr << "SQLite result code: " << sException.GetSqliteResultCode() << std::endl;
        }
    }
    else {
        bRet = false;
    }

#else

#endif

    return;

}

/**
 * @brief     GetOpInitID
 * @return    LONG
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-21, 16:56
 * @warning
 */
unsigned int CSigAnal::GetOpInitID() 
{
	return g_pTheSysConfig->GetOpInitID();
}

