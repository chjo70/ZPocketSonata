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
class CSigAnal : public CRawFile, public CLogName
#endif
{
private:
    bool m_bDBThread;

	unsigned int m_uiCoMaxPdw;

    std::string m_strAnalDirectory;
    std::string m_strDebugDirectory;

#if defined(_MSSQL_) || defined(_SQLITE_)
    char *m_pszSQLString;
#endif

#ifdef _MSSQL_
    CODBCDatabase m_theMyODBC;

#elif _SQLITE_
    Kompex::CSQLiteDatabase *m_pDatabase;

#endif

    ENUM_ANAL_TYPE m_enAnalType;

    bool m_bSaveFile;

    char m_szRawDataFilename[200];

    unsigned int m_uiStep;

    unsigned int m_uiIsStorePDW;

    unsigned int m_uiPDWID;

    time_t m_tColTime;
    unsigned int m_tColTimeMs;

#if defined(_ELINT_)
    char m_szTaskID[LENGTH_OF_TASK_ID];
    ELINT::ENUM_BANDWIDTH m_enBandWidth;

#elif defined(_701_)
	char m_szTaskID[LENGTH_OF_TASK_ID];
	_701::ENUM_BANDWIDTH m_enBandWidth;

#elif defined(_XBAND_)
    char m_szTaskID[LENGTH_OF_TASK_ID];
    EN_RADARCOLLECTORID m_enCollectorID;
    XBAND::ENUM_BANDWIDTH m_enBandWidth;

#elif defined(_POCKETSONATA_) || defined(_712_)
    POCKETSONATA::ENUM_BANDWIDTH m_enBandWidth;

#else

#endif

protected:
    CMIDASBlueFileFormat *m_pMidasBlue;

    STR_PDWDATA m_stSavePDWData;        // 분석한 LOB를 근거로 파일로 저장하기 위한 데이터 포인터

private:
    /*
    template<typename T>
    void SortingTOAOfPDW( const T &pPDWData )
    {
        unsigned int uiCoPDW;

        // 1. 기준 TOA 를 찾습니다.
        //     _PDW *pPDW;
        // pPDW = pPDWData->pstPDW;
        // unsigned int uiCoPDW, uiCoDestPDW;//
        // uiCoPDW = pPDWData->GetTotalPDW();
        //  _TOA tFirstTOA, tDiffTOA;
    //     if( pPDWData->GetTotalPDW() >= _spTwo ) {
    //         tDiffTOA = pPDW[1].GetTOA();
    //         tDiffTOA = tDiffTOA - pPDW[0].GetTOA();
    //
    //         if( tDiffTOA >= CPOCKETSONATAPDW::EncodeTOAs( 100 ) ) {
    //             // TRACE( "\n 역전 입니다." );
    //         }
    //
    //     }

#if 0
        unsigned int ui;
        _PDW *pDestPDW, *pSrcPDW;

        // 2. False PDW 를 버린다.
        pSrcPDW = pPDWData->pstPDW;
        pDestPDW = pPDWData->pstPDW;
        for( ui = 0; ui < uiCoPDW; ++ui ) {
            if( pSrcPDW->GetFalsePDW() == 0 ) {
                memcpy( pDestPDW, pSrcPDW, sizeof( _PDW ) );
                ++ pDestPDW;
                ++ uiCoDestPDW;
            }

            ++ pSrcPDW;

        }
        pPDWData->SetTotalPDW( uiCoDestPDW );
#endif

        // 3. TOA 순으로 정렬 합니다.
        _PDW *pPDW = pPDWData->pstPDW;
        uiCoPDW = pPDWData->GetTotalPDW();
        qsort( pPDW, ( size_t ) uiCoPDW, sizeof( _PDW ), incTOACompare );
    }

    */

protected:
    void DeleteAllFiles();

#ifdef _MSSQL_
    CODBCDatabase *GetCODBCDatabase();
#endif
    void SaveGroupPDWFile( STR_PDWINDEX *pPDWIndex, STR_PDWDATA *pstPDW, int iPLOBID, bool bSaveFile );
    void SaveGroupPDWFile( STR_PDWINDEX *pPDWIndex, STR_STATIC_PDWDATA *pPDWData, int iPLOBID, bool bSaveFile );
    void SATATIC_PDWDATA_TO_PDWDATA(STR_STATIC_PDWDATA *pPDWData );
    void SaveRemainedPdwFile();
    void SaveEmitterPDWFile(STR_EMITTER *pEmitter, _PDW *pstPDW, int iPLOBID, bool bSaveFile);
    void SaveEmitterPDWFile( STR_EMITTER *pEmitter, STR_STATIC_PDWDATA *pPDWData, int iPLOBID, bool bSaveFile );
    bool InsertToDB_LOB( SRxLOBData *pLOBData );

public:
    CSigAnal(unsigned int uiCoMaxPdw, bool bDBThread, const char *pFileName, const char *pThreadName=NULL );
    virtual ~CSigAnal();

	void AllocMemory();

    void NextStep() { ++m_uiStep; }
    void SetStep( unsigned int uiStep ) { m_uiStep=uiStep; }
    unsigned int GetStep() { return m_uiStep; }

    bool IsSaveFile() const { return m_bSaveFile; }
    void SetSaveFile(bool val) {
		m_bSaveFile = val;
	}
    void Initialize();

    void InitResolution();

    void InitDataFromDB();

    bool DeleteDB_RAW( const char *pTable, unsigned int uiCoRecord=0 );
    bool InsertToDB_RAW(STR_PDWDATA *pPDWData, int iPLOBID);
    void InsertRAWData(STR_PDWDATA *pPDWData, int iPLOBID, int iScanStep, bool bInsertDB=true );
    bool InsertToDB_LOB( SRxLOBData *pLOBData, int iCoLOBData, bool bDBInsert );
#ifdef _SQLITE_
    void SQLiteException( Kompex::SQLiteException *psException );
#endif

    bool InsertToDB_Position( SRxLOBData *pLOBData, bool bFreqSeq );

    //! 출력 관련 함수
    void DISP_FineLOB(SRxLOBData *pLOB);

	unsigned int GetOpInitID();
    void MakeAnalDirectory( UNION_HEADER* pUniHeader, bool bLog=true );
    void MakeDebugDirectory( UNION_HEADER *pUniHeader, bool bLog = true );

    void SortingTOAOfPDW( STR_PDWDATA *pPDWData );
    void SortingTOAOfPDW( STR_STATIC_PDWDATA *pPDWData );

    /**
     * @brief     GetAnalDirectory
     * @return    const char*
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-08-16 13:23:08
     * @warning
     */
    inline const char* GetAnalDirectory() {
        return m_strAnalDirectory.c_str();
    }

    /**
     * @brief     GetDebugDirectory
     * @return    const char *
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-08-16 13:23:05
     * @warning
     */
    inline const char *GetDebugDirectory()
    {
        return m_strDebugDirectory.c_str();
    }


    /**
     * @brief     GetColTime
     * @return    time_t
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-21, 10:13
     * @warning
     */
    inline time_t GetColTime() {
        return m_tColTime;
    }

    /**
     * @brief     SetColTime
     * @param     time_t val
     * @return    void
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-21, 10:13
     * @warning
     */
    inline void SetColTime(time_t val) {
        m_tColTime = val;
    }

    /**
     * @brief     GetColTimeMs
     * @return    unsigned int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-21, 10:13
     * @warning
     */
    inline unsigned int GetColTimeMs() {
        return m_tColTimeMs;
    }
    /**
     * @brief     SetColTimeMs
     * @param     unsigned int val
     * @return    void
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-21, 10:13
     * @warning
     */
    inline void SetColTimeMs(unsigned int val) {
        m_tColTimeMs = val;
    }

    /**
     * @brief     GetPDWID
     * @return    unsigned int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-21, 10:13
     * @warning
     */
    inline unsigned int GetPDWID() {
        return m_uiPDWID;
    }

    /**
     * @brief     SetPDWID
     * @param     unsigned int val
     * @return    void
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-21, 10:14
     * @warning
     */
    inline void SetPDWID(unsigned int val) {
        m_uiPDWID = val;
    }

    /**
     * @brief     IsStorePDW
     * @return    int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-21, 10:14
     * @warning
     */
    inline unsigned int IsStorePDW() {
        return m_uiIsStorePDW;
    }
    /**
     * @brief     SetStorePDW
     * @param     int val
     * @return    void
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-21, 10:14
     * @warning
     */
    inline void SetStorePDW(unsigned int uiVal) {
        m_uiIsStorePDW = uiVal;
    }

    void SetBandWidth( int iVal ) {
#if defined(_ELINT_)
        m_enBandWidth = (ELINT::ENUM_BANDWIDTH) iVal;

#elif defined(_XBAND_)
        m_enBandWidth = (XBAND::ENUM_BANDWIDTH) iVal;

#elif defined(_701_)
		m_enBandWidth = (_701::ENUM_BANDWIDTH) iVal;

#elif defined(_POCKETSONATA_) || defined(_712_)
		m_enBandWidth = (POCKETSONATA::ENUM_BANDWIDTH) iVal;

#else
// #error "대역을 설정해줘야 합니다..."
#endif

    }


#if defined(_ELINT_)
    ELINT::ENUM_BANDWIDTH GetBandWidth() const {
        return m_enBandWidth;
    }

#elif defined(_XBAND_)
    /**
     * @brief     GetBandWidth
     * @return    XBAND::ENUM_BANDWIDTH
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-21, 10:14
     * @warning
     */
    XBAND::ENUM_BANDWIDTH GetBandWidth() const {
        return m_enBandWidth;
    }

#elif defined(_701_)
	_701::ENUM_BANDWIDTH GetBandWidth() const {
		return m_enBandWidth;
	}

#elif defined(_POCKETSONATA_) || defined(_712_)

#endif

    /**
     * @brief     GetTaskID
     * @return    char *
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-10, 14:37
     * @warning
     */
    inline char *GetTaskID() {
#if defined(_ELINT_) || defined(_XBAND_)
        return (char *)& m_szTaskID[0];
#else
        return NULL;
#endif
    }

    /**
     * @brief     SetTaskID
     * @param     char * pVal
     * @return    void
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-21, 10:14
     * @warning
     */
    inline void SetTaskID( char *pVal ) {
#if defined(_ELINT_) || defined(_XBAND_)
        strcpy( m_szTaskID, pVal );
#else

#endif

    }

    /**
     * @brief     GetCollectorID
     * @return    EN_RADARCOLLECTORID
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-10, 14:38
     * @warning
     */
    EN_RADARCOLLECTORID GetCollectorID() const {
#if defined(_ELINT_) || defined(_XBAND_)
        return m_enCollectorID;
#else
        return RADARCOL_Unknown;
#endif
    }

    /**
     * @brief     SetCollectorID
     * @param     EN_RADARCOLLECTORID val
     * @return    void
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-10, 14:38
     * @warning
     */
    void SetCollectorID(EN_RADARCOLLECTORID val) {
#if defined(_ELINT_) || defined(_XBAND_)
        m_enCollectorID = val;
#else

#endif
    }

#ifdef _LOG_ANALTYPE_

    inline void SetAnalType( ENUM_ANAL_TYPE enAnalType )
    {
        m_enAnalType = enAnalType;
    }

    bool IsLogAnalType( LogType enLogType )
    {
        bool bRet = true;

        if( g_enLogAnalType == enALL ) {
        }
        else {
            if( enLogType != enError ) {
                if( m_enAnalType & g_enLogAnalType ) {

                }
                else {
                    bRet = false;
                }
            }
        }

        return bRet;
    }
#endif

    /**
     * @brief     GetRawDataFilename
     * @return    char
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-25, 14:36
     * @warning
     */
    const char *GetRawDataFilename() const { return & m_szRawDataFilename[0]; }


    virtual int GetCoGroup() = 0;

    // _DEFINE_LOG_VIRTUAL_FUNCTION

};

