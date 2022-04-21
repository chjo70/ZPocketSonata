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

    int m_iIsStorePDW;

    unsigned int m_uiPDWID;

    __time32_t m_tColTime;
    unsigned int m_tColTimeMs;

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

    STR_PDWDATA m_stSavePDWData;        // ∫–ºÆ«— LOB∏¶ ±Ÿ∞≈∑Œ ∆ƒ¿œ∑Œ ¿˙¿Â«œ±‚ ¿ß«— µ•¿Ã≈Õ ∆˜¿Œ≈Õ

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

    //! √‚∑¬ ∞¸∑√ «‘ºˆ
    void DISP_FineAet(SRxLOBData *pLOB);

#ifdef _MSSQL_
    /**
     * @brief     GetOpInitID
     * @return    LONG
     * @exception
     * @author    ¡∂√∂»Ò (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-21, 16:56
     * @warning
     */
    inline LONG GetOPInitID() {
        return m_lOpInitID;
    }

#endif


    /**
     * @brief     GetColTime
     * @return    __time32_t
     * @exception
     * @author    ¡∂√∂»Ò (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-21, 10:13
     * @warning
     */
    inline __time32_t GetColTime() {
        return m_tColTime;
    }

    /**
     * @brief     SetColTime
     * @param     __time32_t val
     * @return    void
     * @exception
     * @author    ¡∂√∂»Ò (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-21, 10:13
     * @warning
     */
    inline void SetColTime(__time32_t val) { 
        m_tColTime = val; 
    }

    /**
     * @brief     GetColTimeMs
     * @return    unsigned int
     * @exception
     * @author    ¡∂√∂»Ò (churlhee.jo@lignex1.com)
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
     * @author    ¡∂√∂»Ò (churlhee.jo@lignex1.com)
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
     * @author    ¡∂√∂»Ò (churlhee.jo@lignex1.com)
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
     * @author    ¡∂√∂»Ò (churlhee.jo@lignex1.com)
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
     * @author    ¡∂√∂»Ò (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-21, 10:14
     * @warning
     */
    inline int IsStorePDW() { 
        return m_iIsStorePDW; 
    }
    /**
     * @brief     SetStorePDW
     * @param     int val
     * @return    void
     * @exception
     * @author    ¡∂√∂»Ò (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-21, 10:14
     * @warning
     */
    inline void SetStorePDW(int val) { 
        m_iIsStorePDW = val; 
    }


#if defined(_ELINT_)
    ELINT::ENUM_BANDWIDTH GetBandWidth() const { return m_enBandWidth; }
    void SetBandWidth(ELINT::ENUM_BANDWIDTH val) { m_enBandWidth = val; }

#elif defined(_XBAND_)
    /**
     * @brief     GetBandWidth
     * @return    XBAND::ENUM_BANDWIDTH
     * @exception
     * @author    ¡∂√∂»Ò (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-21, 10:14
     * @warning
     */
    XBAND::ENUM_BANDWIDTH GetBandWidth() const { 
        return m_enBandWidth; 
    }

    /**
     * @brief     SetBandWidth
     * @param     XBAND::ENUM_BANDWIDTH val
     * @return    void
     * @exception
     * @author    ¡∂√∂»Ò (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-21, 10:14
     * @warning
     */
    inline void SetBandWidth(XBAND::ENUM_BANDWIDTH val) { 
        m_enBandWidth = val; 
    }

#elif defined(_POCKETSONATA_)

#endif

    inline char *GetTaskID() {
#if defined(_ELINT_) || defined(_XBAND_)
        return (char *)& m_szTaskID[0];
#else
        return NULL;
#endif
    }
    
#if defined(_ELINT_) || defined(_XBAND_)
    /**
     * @brief     SetTaskID
     * @param     char * pVal
     * @return    void
     * @exception
     * @author    ¡∂√∂»Ò (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-21, 10:14
     * @warning
     */
    inline void SetTaskID(char *pVal) { 
        strcpy(m_szTaskID, pVal); 
    }

    EN_RADARCOLLECTORID GetCollectorID() const { return m_enCollectorID; }
    void SetCollectorID(EN_RADARCOLLECTORID val) { m_enCollectorID = val; }
#endif
};

