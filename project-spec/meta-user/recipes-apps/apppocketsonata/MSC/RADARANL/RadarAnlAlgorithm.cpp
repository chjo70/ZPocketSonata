
#include "stdafx.h"

#define MATHFUNCSDLL_EXPORTS

#define _MAIN_
#define _MAIN_GLOBALS_

#include "../../files/Anal/OFP_Main.h"

#include "../../files/Anal/SigAnal/SysPara.h"
#include "../../files/Anal/NewSigAnal/NewSigAnal.h"

#include "../../files/Anal/EmitterMerge/ELEmitterMergeMngr.h"

#include "../../files/Include/globals.h"

#include "RadarAnlAlgorithm.h"


CELEmitterMergeMngr *gpEmitterMergeMngr;

#ifdef _MSSQL_
CODBCDatabase gz_theMyODBC;
#endif


namespace RadarAnlAlgotirhm
{

	void RadarAnlAlgotirhm::Init( HWND hWnd, bool bDBThread, bool bLocal )
	{
		SetWindowHandler( hWnd );

		if( bLocal == false /* && CheckPing() == TRUE */ ) {
			SetLocal( bLocal );
		}
		else {
			SetLocal( true );
		}

        if( g_pTheLog == NULL ) {
            g_pTheLog = new CLog();
        }

		::Log( enNormal, "+---------------------------------------------------+" );
		::Log( enNormal, "���̴� �м� ���̺귯���� �����մϴ�....Ver" );

		if( gpEmitterMergeMngr == NULL ) {
#ifdef _MSSQL_
			gpEmitterMergeMngr = new CELEmitterMergeMngr( bDBThread, & gz_theMyODBC );
#else
			gpEmitterMergeMngr = new CELEmitterMergeMngr( bDBThread, NULL );
#endif
			
		}

		return;
	}

	void RadarAnlAlgotirhm::SWInit()
	{
		if( gpEmitterMergeMngr == NULL ) {
			printf( "\n Init() �Լ��� ȣ������ �ʰ� Start() �Լ��� �����߽��ϴ�.!!" );
		}
		else {
			gpEmitterMergeMngr->Init();

			//gpEmitterMergeMngr->InitOfThreat();
			//gpEmitterMergeMngr->ClearLOBs( pTheThreat->m_nIndex );
			gpEmitterMergeMngr->InitOfLOBClustering();

			gpEmitterMergeMngr->GetGlobalSequenceNum();

			//m_sLOBOtherInfo.bUpdate = false;

			//DeleteAllQData();
		}

	}

	void RadarAnlAlgotirhm::Start( STR_LOBDATA *pLOBData )
	{
		SRxLOBHeader *pstLOBHeader;
		SRxLOBData *pstLOBData;

		if( gpEmitterMergeMngr == NULL ) {
			printf( "\n Init() �Լ��� ȣ������ �ʰ� Start() �Լ��� �����߽��ϴ�.!!" );
		}
		else {
			gpEmitterMergeMngr->Start();

			if( pLOBData->stLOBHeader.uiNumOfLOB > MAX_LOB_DATA || pLOBData->stLOBHeader.uiNumOfLOB == 0 ) {
				Printf( "\n LOB ������ ����[%d]�� �ʰ��ؼ� ������ �ߴ��մϴ�." , pLOBData->stLOBHeader.uiNumOfLOB );
				Log( enError, "LOB ������ ����[%d]�� �ʰ��ؼ� ������ �ߴ��մϴ�." , pLOBData->stLOBHeader.uiNumOfLOB );
				return;
			}

			Log( enNormal, "OP_INIT_ID[%ld] ���̴� ��Ž[%d]���� LOB ������ [%d]���� �����Ͽ� ó���մϴ�." , gpEmitterMergeMngr->GetOpInitID(), pLOBData->stLOBData->iCollectorID, pLOBData->stLOBHeader.uiNumOfLOB );
			pstLOBHeader = & pLOBData->stLOBHeader;
			pstLOBData = & pLOBData->stLOBData[0];
			for( unsigned int i=0 ; i < pstLOBHeader->uiNumOfLOB ; ++i ) {
				if( pstLOBData->aucTaskID[0] != NULL ) {
					gpEmitterMergeMngr->ManageThreat( pstLOBHeader, pstLOBData, NULL, false );

					++ pstLOBData;
				}
				else {
					Printf( "\n %d ��° LOB �������� ���� ������ �����ϴ� !!!" , i+1 );
					Log( enError, "%d ��° LOB �������� ���� ������ �����ϴ� !!!" , i+1 );
					break;
				}
			}

			gpEmitterMergeMngr->PrintAllABTData();

			Log( enLineFeed, "" );

		}

		return;
	}

	/**
	 * @brief     GetLOBData
	 * @param     STR_LOBDATA * pLOBData
	 * @return    bool
	 * @exception
	 * @author    ��ö�� (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2021-10-28, 13:38
	 * @warning
	 */
	bool RadarAnlAlgotirhm::GetLOBData( STR_LOBDATA *pLOBData )
	{
		unsigned int i;
		bool bRet = false;

		vector<SRxLOBData>::pointer pSRxLOBData;

		pLOBData->stLOBHeader.uiNumOfLOB = gpEmitterMergeMngr->m_VecLOBData.size();
		if( pLOBData->stLOBHeader.uiNumOfLOB > MAX_LOB_DATA ) {
			Printf( "\n LOB ������ ����[%d]�� �ʰ��ؼ� ����� �������� �ʽ��ϴ�. �������� Ȯ���غ�����." , pLOBData->stLOBHeader.uiNumOfLOB );
			Log( enError, "LOB ������ ����[%d]�� �ʰ��ؼ� ����� �������� �ʽ��ϴ�. �������� Ȯ���غ�����." , pLOBData->stLOBHeader.uiNumOfLOB );
		}
		else {
			pSRxLOBData = gpEmitterMergeMngr->m_VecLOBData.data();
			for( i=0 ; i < pLOBData->stLOBHeader.uiNumOfLOB ; ++i ) {
				memcpy( & pLOBData->stLOBData[i], pSRxLOBData, sizeof(SRxLOBData) );
				++ pSRxLOBData;

				bRet = true;
			}
		}

		return bRet;
	}

	/**
	 * @brief     GetABTData
	 * @param     STR_ABTDATA * pABTData
	 * @return    bool
	 * @exception
	 * @author    ��ö�� (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2021-10-28, 13:38
	 * @warning
	 */
	bool RadarAnlAlgotirhm::GetABTData( STR_ABTDATA *pABTData )
	{
		int i;
		bool bRet = false;

		vector<SRxABTData>::pointer pSRxABTData;

		pABTData->stABTHeader.iNumOfABT = gpEmitterMergeMngr->m_VecABTData.size();

		if( pABTData->stABTHeader.iNumOfABT > MAX_LOB_DATA ) {
			Printf( "\n ABT ������ ����[%d]�� �ʰ��ؼ� ����� �������� �ʽ��ϴ�. �������� Ȯ���غ�����." , pABTData->stABTHeader.iNumOfABT );
			Log( enError, "ABT ������ ����[%d]�� �ʰ��ؼ� ����� �������� �ʽ��ϴ�. �������� Ȯ���غ�����." , pABTData->stABTHeader.iNumOfABT );
		}
		else {
			pSRxABTData = gpEmitterMergeMngr->m_VecABTData.data();
			for( i=0 ; i < pABTData->stABTHeader.iNumOfABT ; ++i ) {
				memcpy( & pABTData->stABTData[i], pSRxABTData, sizeof(SRxABTData) );
				++ pSRxABTData;

				bRet = true;
			}
		}

		return bRet;
	}

	/**
	 * @brief     UpdateCEDEOBLibrary
	 * @return    void
	 * @exception
	 * @author    ��ö�� (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2021-10-28, 13:39
	 * @warning
	 */
	void RadarAnlAlgotirhm::UpdateCEDEOBLibrary()
	{
		if( gpEmitterMergeMngr != NULL ) {
			gpEmitterMergeMngr->UpdateCEDEOBLibrary();
		}
		else {
			printf( "\n Init() �Լ��� ȣ������ �ʰ� UpdateCEDEOBLibrary() �Լ��� �����߽��ϴ�.!!" );
			Log( enError, "Init() �Լ��� ȣ������ �ʰ� UpdateCEDEOBLibrary() �Լ��� �����߽��ϴ�.!!" );
		}
		return;
	}

	/**
	 * @brief     Close
	 * @return    void
	 * @exception
	 * @author    ��ö�� (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2021-10-28, 13:39
	 * @warning
	 */
	void RadarAnlAlgotirhm::Close()
	{

        if( g_pTheLog != NULL ) {
		Log( enNormal, "���̴� �м� ���̺귯���� �����մϴ�...." );
        }
        else {
            printf( "\n ���̴� �м� ���̺귯���� �����մϴ�...." );
        }

		if( gpEmitterMergeMngr != NULL ) {
			delete gpEmitterMergeMngr;
            gpEmitterMergeMngr = NULL;
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
     * @author    ��ö�� (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-21, 17:06
     * @warning
     */
    unsigned int RadarAnlAlgotirhm::GetOpInitID()
    {
        return gpEmitterMergeMngr->GetOpInitID();

    }

}


