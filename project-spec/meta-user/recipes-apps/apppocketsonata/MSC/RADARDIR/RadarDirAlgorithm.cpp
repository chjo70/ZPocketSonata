
#include "stdafx.h"

#define MATHFUNCSDLL_EXPORTS

#include "../../files/Anal/SigAnal/SysPara.h"
#include "../../files/Anal/NewSigAnal/NewSigAnal.h"

#include "RadarDirAlgorithm.h"

#include "../../files/Include/globals.h"



CNewSigAnal *gpNewSigAnal;
CSysPara *gpSysPara;

namespace RadarDirAlgotirhm
{

	void RadarDirAlgotirhm::Init( HWND hWnd, bool bLocal )
	{
		
		if( bLocal == false /*&& CheckPing() == TRUE*/ ) {
			SetLocal( bLocal );
		}
		else {
			SetLocal( true );
		}

        if( g_pTheLog == NULL ) {
            g_pTheLog = new CLog();

		
		    ::Log( enNormal, "+---------------------------------------------------+" );
		    ::Log( enNormal,  "레이더 방탐 라이브러리를 구동합니다...." );
        }

		SetWindowHandler( hWnd );
		
		if( gpNewSigAnal == NULL ) {
			gpNewSigAnal = new CNewSigAnal( MAX_PDW, false );
			gpNewSigAnal->InitVar( NORMAL_MDOE );
		}

		if( gpSysPara == NULL ) {
			gpSysPara = new CSysPara;
		}

		SetMute( false );

		return;
	}

	void RadarDirAlgotirhm::SetMute( bool bEnable )
	{
		::SetMute( bEnable );

		if( gpNewSigAnal != NULL ) {
			gpNewSigAnal->SetSaveFile( ! bEnable );
		}

		return;
	}

	void RadarDirAlgotirhm::SWInit()
	{

		if( gpNewSigAnal == NULL ) {
			printf( "\n Init() 함수를 호출하지 않고 SWInit() 함수를 실행했습니다.!!" );

		}
		else {
			//gpNewSigAnal->SWInit();

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
	void RadarDirAlgotirhm::Start( STR_PDWDATA *pPDWData )
	{
		
		if( gpNewSigAnal != NULL ) {
			gpNewSigAnal->Start( pPDWData );
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
    void RadarDirAlgotirhm::LoadCEDLibrary()
    {

        if( gpNewSigAnal == NULL ) {
            printf( "\n Init() 함수를 호출하지 않고 SWInit() 함수를 실행했습니다.!!" );

        }
        else {
            gpNewSigAnal->LoadCEDLibrary();

        }

        return;
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
	int RadarDirAlgotirhm::GetCoLOB()
	{
		if( gpNewSigAnal != NULL ) {
			return gpNewSigAnal->GetCoLOB();
		}
		else {
			printf( "\n Init() 함수를 호출하지 않고 GetCoEmitter() 함수를 실행했습니다.!!" );
			return -1;
		}

	}

	/**
	 * @brief     GetLOBData
	 * @return    SRxLOBData *
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022-01-08, 13:23
	 * @warning
	 */
	SRxLOBData *RadarDirAlgotirhm::GetLOBData()
	{
		if( gpNewSigAnal != NULL ) {
			return gpNewSigAnal->GetLOB();
		}
		else {
			return NULL;
		}
	}

	/**
	 * @brief     Close
	 * @return    void
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022-01-08, 13:23
	 * @warning
	 */
	void RadarDirAlgotirhm::Close()
	{
        if( g_pTheLog != NULL ) {
		    Log( enNormal, "레이더 방탐 라이브러리를 종료합니다...." );
        }

		if( gpNewSigAnal != NULL ) {
			delete gpNewSigAnal;
            gpNewSigAnal = NULL;
		}
		if( gpSysPara != NULL ) {
			delete gpSysPara;
            gpSysPara = NULL;
		}
        if( g_pTheLog != NULL ) {
            delete g_pTheLog;
            g_pTheLog = NULL;
        }

		return;
	}


    /**
     * @brief     GetOPInitID
     * @return    LONG
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-21, 16:58
     * @warning
     */
    LONG RadarDirAlgotirhm::GetOpInitID()
    {
        return gpNewSigAnal->GetOpInitID();

    }


}


