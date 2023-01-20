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
    CODBCDatabase m_theMyODBC;

#elif _SQLITE_
    Kompex::CSQLiteDatabase *m_pDatabase;

#endif

    bool m_bSaveFile;

    char m_szRawDataFilename[200];

    unsigned int m_uiStep;

    unsigned int m_uiIsStorePDW;

    unsigned int m_uiPDWID;

    time_t m_tColTime;
    unsigned int m_tColTimeMs;

#if defined(_ELINT_) || defined(_701_)
    char m_szTaskID[LENGTH_OF_TASK_ID];
    //EN_RADARCOLLECTORID m_enCollectorID;
    _701::ENUM_BANDWIDTH m_enBandWidth;

#elif defined(_XBAND_)
    char m_szTaskID[LENGTH_OF_TASK_ID];
    EN_RADARCOLLECTORID m_enCollectorID;
    XBAND::ENUM_BANDWIDTH m_enBandWidth;

#elif defined(_POCKETSONATA_)
    POCKETSONATA::ENUM_BANDWIDTH m_enBandWidth;



#else

#endif    

protected:
    CMIDASBlueFileFormat *m_pMidasBlue;

    STR_PDWDATA m_stSavePDWData;        // �м��� LOB�� �ٰŷ� ���Ϸ� �����ϱ� ���� ������ ������

private:

protected:
#ifdef _MSSQL_
    CODBCDatabase *GetCODBCDatabase();
#endif
    void SaveGroupPDWFile( STR_PDWINDEX *pPDWIndex, STR_PDWDATA *pstPDW, bool bSaveFile );
    void SaveRemainedPdwFile();
    void SaveEmitterPDWFile(STR_EMITTER *pEmitter, _PDW *pstPDW, int iPLOBID, bool bSaveFile);
    void InsertToDB_LOB( SRxLOBData *pLOBData );

public:
    CSigAnal(unsigned int uiCoMaxPdw, bool bDBThread, const char *pFileName );
    virtual ~CSigAnal();

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

    bool InsertToDB_RAW(STR_PDWDATA *pPDWData, int iPLOBID);
    void InsertRAWData(STR_PDWDATA *pPDWData, int iPLOBID, bool bInsertDB=true );
    void InsertToDB_LOB( SRxLOBData *pLOBData, int iCoLOBData, bool bDBInsert );

    bool InsertToDB_Position( SRxLOBData *pLOBData, bool bFreqSeq );

    //! ��� ���� �Լ�
    void DISP_FineLOB(SRxLOBData *pLOB);

	unsigned int GetOpInitID();


    /**
     * @brief     GetColTime
     * @return    __time32_t
     * @exception
     * @author    ��ö�� (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-21, 10:13
     * @warning
     */
    inline time_t GetColTime() {
        return m_tColTime;
    }

    /**
     * @brief     SetColTime
     * @param     __time32_t val
     * @return    void
     * @exception
     * @author    ��ö�� (churlhee.jo@lignex1.com)
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
     * @author    ��ö�� (churlhee.jo@lignex1.com)
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
     * @author    ��ö�� (churlhee.jo@lignex1.com)
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
     * @author    ��ö�� (churlhee.jo@lignex1.com)
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
     * @author    ��ö�� (churlhee.jo@lignex1.com)
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
     * @author    ��ö�� (churlhee.jo@lignex1.com)
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
     * @author    ��ö�� (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-21, 10:14
     * @warning
     */
    inline void SetStorePDW(unsigned int uiVal) { 
        m_uiIsStorePDW = uiVal;
    }

    void SetBandWidth( int iVal ) {
// #if defined(_ELINT_)
//         m_enBandWidth = (ELINT::ENUM_BANDWIDTH) iVal;
// 
// #elif defined(_XBAND_)
//         m_enBandWidth = (XBAND::ENUM_BANDWIDTH) iVal;
// 
// #elif defined(_701_)
// 		m_enBandWidth = (_701::ENUM_BANDWIDTH) iVal;
// 
// #else
// #error "�뿪�� ��������� �մϴ�..."
// #endif

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
     * @author    ��ö�� (churlhee.jo@lignex1.com)
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

#elif defined(_POCKETSONATA_)

#endif

    /**
     * @brief     GetTaskID
     * @return    char *
     * @exception
     * @author    ��ö�� (churlhee.jo@lignex1.com)
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
     * @author    ��ö�� (churlhee.jo@lignex1.com)
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
     * @author    ��ö�� (churlhee.jo@lignex1.com)
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
     * @author    ��ö�� (churlhee.jo@lignex1.com)
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

    /**
     * @brief     GetRawDataFilename
     * @return    char
     * @exception
     * @author    ��ö�� (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-25, 14:36
     * @warning
     */
    const char *GetRawDataFilename() const { return & m_szRawDataFilename[0]; }


    virtual int GetCoGroup() = 0;

};

