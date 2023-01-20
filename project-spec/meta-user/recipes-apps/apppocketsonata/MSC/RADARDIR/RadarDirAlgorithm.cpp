
#include "stdafx.h"

#define MATHFUNCSDLL_EXPORTS

#include "../../files/Anal/SigAnal/SysPara.h"
#include "../../files/Anal/NewSigAnal/NewSigAnal.h"

#include "RadarDirAlgorithm.h"

#include "../../files/Include/globals.h"


enum ANALYSIS_MODE { NORMAL_MDOE = 0, SIMUL_MODE };


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
		    ::Log( enNormal,  "���̴� ��Ž ���̺귯���� �����մϴ�...." );
        }

		SetWindowHandler( hWnd );
		
		if( gpNewSigAnal == NULL ) {
			g_pTheSysConfig = new CSysConfig();

			gpNewSigAnal = new CNewSigAnal( MAX_PDW, false );
			//gpNewSigAnal->InitAllVar( NORMAL_MDOE );
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
			printf( "\n Init() �Լ��� ȣ������ �ʰ� SWInit() �Լ��� �����߽��ϴ�.!!" );

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
	 * @author    ��ö�� (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2021-07-10, 14:28
	 * @warning
	 */
	void RadarDirAlgotirhm::Start( STR_PDWDATA *pPDWData, bool bDBInsert )
	{
		
		if( gpNewSigAnal != NULL ) {
			gpNewSigAnal->Start( pPDWData, bDBInsert );
		}
		else {
			printf( "\n Init() �Լ��� ȣ������ �ʰ� Start() �Լ��� �����߽��ϴ�.!!" );
		}

		return;
	}

    /**
     * @brief     LoadCEDLibrary
     * @return    void
     * @exception
     * @author    ��ö�� (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2021-07-10, 14:28
     * @warning
     */
    void RadarDirAlgotirhm::LoadCEDLibrary()
    {

        if( gpNewSigAnal == NULL ) {
            printf( "\n Init() �Լ��� ȣ������ �ʰ� SWInit() �Լ��� �����߽��ϴ�.!!" );

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
	 * @author    ��ö�� (churlhee.jo@lignex1.com)
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
			printf( "\n Init() �Լ��� ȣ������ �ʰ� GetCoEmitter() �Լ��� �����߽��ϴ�.!!" );
			return -1;
		}

	}

	/**
	 * @brief     LOB �����͸� �����Ѵ�.
	 * @return    SRxLOBData *
	 * @exception
	 * @author    ��ö�� (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022-01-08, 13:23
	 * @warning
	 */
	SRxLOBData *RadarDirAlgotirhm::GetLOBData()
	{
		if( gpNewSigAnal != NULL ) {
			return gpNewSigAnal->GetLOBData();
		}
		else {
			return NULL;
		}
	}

	/**
	 * @brief     Ž�� �м� DLL �� ���� ó���Ѵ�. �ݵ�� �������� ȣ���ؾ� �Ѵ�.
	 * @return    void
	 * @exception
	 * @author    ��ö�� (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022-01-08, 13:23
	 * @warning
	 */
	void RadarDirAlgotirhm::Close()
	{
        if( g_pTheLog != NULL ) {
		    Log( enNormal, "���̴� ��Ž ���̺귯���� �����մϴ�...." );
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
		if (g_pTheSysConfig != NULL) {
			delete g_pTheSysConfig;
			g_pTheSysConfig = NULL;
		}

		return;
	}


    /**
     * @brief     OPINITID ���� �����Ѵ�.
     * @return    LONG
     * @exception
     * @author    ��ö�� (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-21, 16:58
     * @warning
     */
    unsigned int RadarDirAlgotirhm::GetOpInitID()
    {
        return gpNewSigAnal->GetOpInitID();

    }


}


