
#include "stdafx.h"

#define MATHFUNCSDLL_EXPORTS

//#include "../../files/Anal/OFP_Main.h"

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
		
		if( bLocal == false && CheckPing() == TRUE ) {
			SetLocal( bLocal );
		}
		else {
			SetLocal( true );
		}

        if( g_pTheLog == NULL ) {
            g_pTheLog = new CLog();
        }
		
		::Log( enNormal, "+---------------------------------------------------+" );
		::Log( enNormal,  "레이더 방탐 라이브러리를 구동합니다...." );

		SetWindowHandler( hWnd );
		
		if( gpNewSigAnal == NULL ) {
			gpNewSigAnal = new CNewSigAnal( MAX_PDW );
			gpNewSigAnal->InitVar( NORMAL_MDOE );
		}

		if( gpSysPara == NULL ) {
			gpSysPara = new CSysPara;
		}

		SetMute( true );

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

	int RadarDirAlgotirhm::GetCoLOB()
	{
		if( gpNewSigAnal != NULL ) {
			return gpNewSigAnal->GetCoAet();
		}
		else {
			printf( "\n Init() 함수를 호출하지 않고 GetCoEmitter() 함수를 실행했습니다.!!" );
			return -1;
		}

	}

	SRxLOBData *RadarDirAlgotirhm::GetLOBData()
	{
		if( gpNewSigAnal != NULL ) {
			return gpNewSigAnal->GetLOB();
		}
		else {
			return NULL;
		}
	}

	void RadarDirAlgotirhm::Close()
	{
		Log( enNormal, "레이더 방탐 라이브러리를 종료합니다...." );

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

// 	void RadarDirAlgotirhm::Log( int nType, const char *fmt, ... )
// 	{
// 		_TCHAR szLog[5096];
// 		va_list args;
// 
// 		if( fmt != NULL ) {
// 			ZeroMemory( szLog, sizeof(szLog) );
// 
// 			va_start( args, fmt );
// 			vsprintf_s( szLog, fmt, args );
// 			va_end( args );
// 
// 			::Log( nType, szLog );
// 
// 		}
// 
// 		return;
// 	}

}


