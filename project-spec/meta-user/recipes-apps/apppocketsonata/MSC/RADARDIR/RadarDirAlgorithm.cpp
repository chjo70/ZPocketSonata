
#include "pch.h"

#define MATHFUNCSDLL_EXPORTS

//#include "Anal/SigAnal/SysPara.h"
//#include "Anal/NewSigAnal/NewSigAnal.h"

#include "Include/globals.h"

#include "RadarDirAlgorithm.h"


enum ANALYSIS_MODE { NORMAL_MDOE = 0, SIMUL_MODE };


// CLogName 에 있는 클래스의 전역 변수 선언 합니다.
//char CLogName::m_szName[enETC_ANAL+1][10];

namespace RadarDirAlgotirhm
{

	/**
	 * @brief     Init
	 * @param     HWND hWnd
	 * @param     bool bLocal
	 * @return    void
	 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   1.0.0
	 * @date      2023-10-23 18:55:44
	 * @warning
	 */
	void RadarDirAlgotirhm::Init( int iCoreOfSigAnal, HWND hWnd, bool bLocal )
	{
        int i;

        char *pThreadName;
        char szDBFileName[100];

        g_iCoreOfSigAnal = iCoreOfSigAnal;

		if( bLocal == false /*&& CheckPing() == true*/ ) {
#ifdef _MSC_VER
			SetLocal( bLocal );
#endif
		}
		else {
#ifdef _MSC_VER
			SetLocal( true );
#endif
		}

        if( g_pTheLog == NULL ) {
            g_pTheLog = new CLog();

		    ::Log( enNormal, "+---------------------------------------------------+" );
		    ::Log( enNormal,  "레이더 방탐 라이브러리를 구동합니다...." );
        }

#ifdef _MSC_VER
		SetWindowHandler( hWnd );
#endif

        if( g_pTheSysConfig == NULL ) {
            g_pTheSysConfig = new CSysConfig();
        }

        if( gstPDWData.pstPDW == NULL ) {
            gstPDWData.pstPDW = ( _PDW * ) malloc( sizeof( _PDW ) * MAX_PDW );

        }

        if( gpSysPara == NULL ) {
            gpSysPara = new CSysPara;

        }

        // 탐지 분석 생성
        gpTheNewSigAnal = new CNewSigAnal * [iCoreOfSigAnal];

        for( i=0 ; i < g_iCoreOfSigAnal ; ++i ) {


#ifdef __VXWORKS__
            TASK_ID taskId = taskIdSelf();
            pThreadName = taskName( taskId );

#else
            pThreadName = NULL;
#endif



#ifdef _SQLITE_

#ifdef __VXWORKS__
            strcpy( szDBFileName, ATADRV );
            strcat( szDBFileName, "/" );
            strcat( szDBFileName, SQLITE_DIRECTORY );
            strcat( szDBFileName, "/" );
            strcat( szDBFileName, EMITTER_SQLITE_FILEEXTNAME );
#else
            // SQLITE 파일명 생성하기
            strcpy( szDBFileName, EMITTER_SQLITE_FOLDER );
            strcat( szDBFileName, "/" );
            strcat( szDBFileName, EMITTER_SQLITE_FILEEXTNAME );

#endif

#elif _MSC_VER
            //sprintf( szSrcSQLiteFileName, "%s_%d.sqlite3", EMITTER_SQLITE_FILENAME, g_enBoardId );
            //strcat( szSQLiteFileName, szSrcSQLiteFileName );
#else
            szDBFileName[0] = NULL;

#endif

            gpTheNewSigAnal[i] = new CNewSigAnal( MAX_PDW, false, szDBFileName, pThreadName );

            SetMute( i, false );
        }

        gpTheScanSigAnal = new CScanSigAnal( MAX_PDW, false, szDBFileName, pThreadName );

		return;
	}

	/**
	 * @brief     SetMute
	 * @param     bool bEnable
	 * @return    void
	 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   1.0.0
	 * @date      2023-10-23 16:52:13
	 * @warning
	 */
	void RadarDirAlgotirhm::SetMute( bool bEnable, int iCoreOfSigAnal )
	{

#ifdef _MSC_VER
		::SetMute( bEnable );
#endif

		if( gpTheNewSigAnal != NULL && gpTheNewSigAnal[iCoreOfSigAnal] != NULL ) {
            gpTheNewSigAnal[iCoreOfSigAnal]->SetSaveFile( ! bEnable );
		}

		return;
	}

	/**
	 * @brief     SWInit
	 * @return    void
	 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   1.0.0
	 * @date      2023-10-26 17:23:11
	 * @warning
	 */
	void RadarDirAlgotirhm::SWInit()
	{
        int i;

        for( i = 0; i < g_iCoreOfSigAnal ; ++i ) {
            if( gpTheNewSigAnal[i] != NULL ) {
                // gpTheNewSigAnal[i]->SWInit();
            }
        }

		return;
	}

	/**
	 * @brief     Start
	 * @param     STR_PDWDATA * pPDWData
	 * @return    void
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2021-07-10, 14:28
	 * @warning
	 */
	void RadarDirAlgotirhm::Start( STR_UZPOCKETPDW *pstUZPOCKETPDW, int iSigAnal, bool bDBInsert )
	{

		if( gpTheNewSigAnal != NULL ) {
			ENUM_BoardID enBoardID;

            UZPOCKETPDW2PDWData( & gstPDWData, pstUZPOCKETPDW );

            enBoardID = ( ENUM_BoardID ) gstPDWData.GetBand();
            gpTheNewSigAnal[iSigAnal]->SetGlobalBoardID( enBoardID );

            Start( & gstPDWData, iSigAnal, bDBInsert );

		}
		else {
			printf( "\n Init() 함수를 호출하지 않고 Start() 함수를 실행했습니다.!!" );
		}

		return;
	}

	/**
	 * @brief     Start
	 * @param     STR_PDWDATA * pPDWData
	 * @return    void
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2021-07-10, 14:28
	 * @warning
	 */
	void RadarDirAlgotirhm::Start( STR_PDWDATA *pPDWData, int iSigAnal, bool bDBInsert )
	{

		if( gpTheNewSigAnal != NULL ) {
            ENUM_BoardID enBoardID;

            enBoardID = ( ENUM_BoardID ) pPDWData->GetBand();
            gpTheNewSigAnal[iSigAnal]->SetGlobalBoardID( enBoardID );
            gpTheNewSigAnal[iSigAnal]->Start( pPDWData, bDBInsert );
		}
		else {
			printf( "\n Init() 함수를 호출하지 않고 Start() 함수를 실행했습니다.!!" );
		}

		return;
	}

    /**
     * @brief     Start
     * @param     STR_PDWDATA * pPDWData
     * @param     SRxLOBData * pLOBData
     * @param     int iSigAnal
     * @param     bool bDBInsert
     * @return    void
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-12-21 13:22:17
     * @warning
     */
    void RadarDirAlgotirhm::Start( STR_PDWDATA *pPDWData, SRxLOBData *pLOBData, unsigned int uiScanStep, unsigned int uiReqScanPeriod, STR_SCANRESULT *pstScanResult )
    {

        if( gpTheNewSigAnal != NULL ) {
            gpTheScanSigAnal->Start( pPDWData, pLOBData, uiScanStep, uiReqScanPeriod, pstScanResult );
        }
        else {
            printf( "\n Init() 함수를 호출하지 않고 Start() 함수를 실행했습니다.!!" );
        }

        return;
    }

    /**
     * @brief     LoadCEDLibrary
     * @return    void
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2021-07-10, 14:28
     * @warning
     */
    bool RadarDirAlgotirhm::LoadCEDLibrary()
    {
        bool bRet = false;

        if( g_iCoreOfSigAnal == 0 || gpTheNewSigAnal == NULL || gpTheNewSigAnal[0] == NULL ) {
            printf( "\n Init() 함수를 호출하지 않고 SWInit() 함수를 실행했습니다.!!" );

        }
        else {
            bRet = gpTheNewSigAnal[0]->LoadCEDLibrary();

        }

        return true;
    }

    /**
     * @brief     LoadEOBLibrary
     * @return    bool
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-11-06 20:21:20
     * @warning
     */
    bool RadarDirAlgotirhm::LoadEOBLibrary()
    {
        bool bRet = false;

        if( g_iCoreOfSigAnal == 0 || gpTheNewSigAnal == NULL || gpTheNewSigAnal[0] == NULL ) {
            printf( "\n Init() 함수를 호출하지 않고 SWInit() 함수를 실행했습니다.!!" );

        }
        else {
            bRet = gpTheNewSigAnal[0]->LoadEOBLibrary();

        }

        return true;
    }

	/**
	 * @brief     GetCoLOB
	 * @return    int
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022-01-08, 13:23
	 * @warning
	 */
	int RadarDirAlgotirhm::GetCoLOB( int iSigANal )
	{
        if( g_iCoreOfSigAnal != 0 && gpTheNewSigAnal != NULL && gpTheNewSigAnal[iSigANal] != NULL ) {
			return gpTheNewSigAnal[iSigANal]->GetCoLOB();
		}
		else {
			printf( "\n Init() 함수를 호출하지 않고 GetCoEmitter() 함수를 실행했습니다.!!" );
			return -1;
		}

	}

	/**
	 * @brief     LOB 데이터를 리턴한다.
	 * @return    SRxLOBData *
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022-01-08, 13:23
	 * @warning
	 */
	SRxLOBData *RadarDirAlgotirhm::GetLOBData( int iSigANal )
	{
        if( g_iCoreOfSigAnal != 0 && gpTheNewSigAnal != NULL && gpTheNewSigAnal[iSigANal] != NULL ) {
			return gpTheNewSigAnal[iSigANal]->GetLOBData();
		}
		else {
			return NULL;
		}
	}

    /**
     * @brief     GetEmitterData
     * @param     int iSigANal
     * @return    STR_EMITTER *
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-12-11 15:28:22
     * @warning
     */
    STR_PDWDATA *RadarDirAlgotirhm::GetLOB2PDWData( unsigned int uiLOBIndex, int iSigANal )
    {
        if( g_iCoreOfSigAnal != 0 && gpTheNewSigAnal != NULL && gpTheNewSigAnal[iSigANal] != NULL ) {
            return gpTheNewSigAnal[iSigANal]->GetLOB2PDWData( uiLOBIndex );;
        }
        else {
            return NULL;
        }
    }

	/**
	 * @brief     탐지 분석 DLL 을 종료 처리한다. 반드시 마지막에 호출해야 한다.
	 * @return    void
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022-01-08, 13:23
	 * @warning
	 */
	void RadarDirAlgotirhm::Close( int iSigAnal )
	{

        if( g_iCoreOfSigAnal != 0 && gpTheNewSigAnal != NULL && gpTheNewSigAnal[iSigAnal] != NULL ) {
			delete gpTheNewSigAnal[iSigAnal];
            gpTheNewSigAnal[iSigAnal] = NULL;
		}

        delete gpTheNewSigAnal;

        delete gpTheScanSigAnal;

		return;
	}

    /**
     * @brief     CloseAll
     * @return    void
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-10-30 13:41:43
     * @warning
     */
    void RadarDirAlgotirhm::CloseAll()
    {
        int i;

        for( i = 0; i < g_iCoreOfSigAnal; ++i ) {
            Close( i );
        }

        if( gpSysPara != NULL ) {
            delete gpSysPara;
            gpSysPara = NULL;
        }
        if( g_pTheLog != NULL ) {
            delete g_pTheLog;
            g_pTheLog = NULL;
        }
        if( g_pTheSysConfig != NULL ) {
            delete g_pTheSysConfig;
            g_pTheSysConfig = NULL;
        }

        if( gstPDWData.pstPDW != NULL ) {
            free( gstPDWData.pstPDW );
        }

        if( g_pTheLog != NULL ) {
            Log( enNormal, "레이더 방탐 라이브러리를 종료합니다...." );
        }

        return;
    }

    /**
     * @brief     OPINITID 값을 리턴한다.
     * @return    LONG
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-21, 16:58
     * @warning
     */
    unsigned int RadarDirAlgotirhm::GetOpInitID( int iSigAnal )
    {
        return gpTheNewSigAnal[iSigAnal]->GetOpInitID();

    }

    /**
     * @brief     UZPOCKETPDW2PDWData
     * @param     STR_PDWDATA * pPDWData
     * @param     STR_UZPOCKETPDW * pstUZPOCKETPDW
     * @return    unsigned int
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-10-26 16:47:57
     * @warning
     */
    unsigned int RadarDirAlgotirhm::UZPOCKETPDW2PDWData( STR_PDWDATA *pPDWData, STR_UZPOCKETPDW *pstUZPOCKETPDW)
    {
    	int i;

    	_PDW *pPDW;
    	UZPOCKETPDW *pstPDW;

    	DMAPDW *pDMAPDW;

    	memcpy( & pPDWData->x, & pstUZPOCKETPDW->x, sizeof(UNION_HEADER) );

    	unsigned int uiCoTotalPDW = pstUZPOCKETPDW->GetTotalPDW();

    	pPDW = pPDWData->pstPDW;
    	pstPDW = pstUZPOCKETPDW->pstPDW;

    	//printf( "\n uiCoTotalPDW[%d]" , uiCoTotalPDW );

    	for( i=0 ; i < (int) uiCoTotalPDW ; ++i ) {
    		pDMAPDW = ( DMAPDW * ) pstPDW;

    	    pPDW->iStat = pDMAPDW->GetPulsetype();

            pPDW->tTOA = pDMAPDW->GetTOA();
            pPDW->uiAOA = pDMAPDW->GetAOA();
            pPDW->uiFreq = pDMAPDW->GetFrequency();
            pPDW->uiPW = pDMAPDW->GetPulsewidth();
            pPDW->uiPA = pDMAPDW->GetPulseamplitude();

    	    pPDW->uiIndex = pDMAPDW->GetIndex();

            pPDW->x.ps.x.stStrBitMap.CwPulse = pDMAPDW->uPDW.stHwPdwDataRf.CwPulse;
            pPDW->x.ps.x.stStrBitMap.Pmop = pDMAPDW->uPDW.stHwPdwDataRf.Pmop;
            pPDW->x.ps.x.stStrBitMap.Fmop = pDMAPDW->uPDW.stHwPdwDataRf.Fmop;
            pPDW->x.ps.x.stStrBitMap.FmopDir = pDMAPDW->uPDW.stHwPdwDataRf.FmopDir;

            pPDW->SetChannel( pDMAPDW->GetChannel() );

    	    ++ pPDW;
    	    ++ pstPDW;

    	    if( i > MAX_PDW ) {
                TRACE( ( const char * ) "...in %s 파일 %d 라인", strrchr( __FILE__, '\\' ) ? strrchr( __FILE__, '\\' ) : __FILE__, __LINE__ );
    	    	break;
    	    }


    	}

    	return (unsigned int) i;

    }



}


