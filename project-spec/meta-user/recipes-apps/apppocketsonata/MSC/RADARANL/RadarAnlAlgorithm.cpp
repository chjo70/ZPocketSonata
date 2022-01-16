
#include "stdafx.h"

#define MATHFUNCSDLL_EXPORTS

#define _MAIN_
#define _MAIN_GLOBALS_

#include "../../files/Anal/OFP_Main.h"

#include "../../files/Anal/SigAnal/SysPara.h"
#include "../../files/Anal/NewSigAnal/NewSigAnal.h"

#include "RadarAnlAlgorithm.h"

#include "../../files/Anal/EmitterMerge/ELEmitterMergeMngr.h"

#include "../../files/Include/globals.h"


CELEmitterMergeMngr *gpEmitterMergeMngr;
CODBCDatabase gz_theMyODBC;


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
		::Log( enNormal, "레이더 분석 라이브러리를 구동합니다....Ver" );

		if( gpEmitterMergeMngr == NULL ) {
			gpEmitterMergeMngr = new CELEmitterMergeMngr( bDBThread, & gz_theMyODBC );
			
		}

		return;
	}

	void RadarAnlAlgotirhm::SWInit()
	{
		if( gpEmitterMergeMngr == NULL ) {
			printf( "\n Init() 함수를 호출하지 않고 Start() 함수를 실행했습니다.!!" );
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
		bool bIsResult = false;
		SRxLOBHeader *pstLOBHeader;
		SRxLOBData *pstLOBData;

		if( gpEmitterMergeMngr == NULL ) {
			printf( "\n Init() 함수를 호출하지 않고 Start() 함수를 실행했습니다.!!" );
		}
		else {
			gpEmitterMergeMngr->Start();

			if( pLOBData->stLOBHeader.iNumOfLOB > MAX_LOB_DATA || pLOBData->stLOBHeader.iNumOfLOB == 0 ) {
				Printf( "\n LOB 데이터 개수[%d]가 초과해서 실행을 중단합니다." , pLOBData->stLOBHeader.iNumOfLOB );
				Log( enError, "LOB 데이터 개수[%d]가 초과해서 실행을 중단합니다." , pLOBData->stLOBHeader.iNumOfLOB );
				return;
			}

			Log( enNormal, "OP_INIT_ID[%d] 레이더 방탐[%d]에서 LOB 데이터 [%d]개를 수신하여 처리합니다." , gpEmitterMergeMngr->GetOpInitID(), pLOBData->stLOBData->iCollectorID, pLOBData->stLOBHeader.iNumOfLOB );
			pstLOBHeader = & pLOBData->stLOBHeader;
			pstLOBData = & pLOBData->stLOBData[0];
			for( int i=0 ; i < pstLOBHeader->iNumOfLOB ; ++i ) {
				if( pstLOBData->aucTaskID[0] != NULL ) {
					bIsResult = gpEmitterMergeMngr->ManageThreat( pstLOBHeader, pstLOBData, NULL, true );

					++ pstLOBData;
				}
				else {
					Printf( "\n %d 번째 LOB 데이터의 과제 정보가 없습니다 !!!" , i+1 );
					Log( enError, "%d 번째 LOB 데어터의 과제 정보가 없습니다 !!!" , i+1 );
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
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2021-10-28, 13:38
	 * @warning
	 */
	bool RadarAnlAlgotirhm::GetLOBData( STR_LOBDATA *pLOBData )
	{
		int i;
		bool bRet = false;

		vector<SRxLOBData>::pointer pSRxLOBData;

		pLOBData->stLOBHeader.iNumOfLOB = gpEmitterMergeMngr->m_VecLOBData.size();
		if( pLOBData->stLOBHeader.iNumOfLOB > MAX_LOB_DATA ) {
			Printf( "\n LOB 데이터 개수[%d]가 초과해서 결과를 리턴하지 않습니다. 리컨값을 확인해보세요." , pLOBData->stLOBHeader.iNumOfLOB );
			Log( enError, "LOB 데이터 개수[%d]가 초과해서 결과를 리턴하지 않습니다. 리컨값을 확인해보세요." , pLOBData->stLOBHeader.iNumOfLOB );
		}
		else {
			pSRxLOBData = gpEmitterMergeMngr->m_VecLOBData.data();
			for( i=0 ; i < pLOBData->stLOBHeader.iNumOfLOB ; ++i ) {
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
	 * @author    조철희 (churlhee.jo@lignex1.com)
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
			Printf( "\n ABT 데이터 개수[%d]가 초과해서 결과를 리턴하지 않습니다. 리컨값을 확인해보세요." , pABTData->stABTHeader.iNumOfABT );
			Log( enError, "ABT 데이터 개수[%d]가 초과해서 결과를 리턴하지 않습니다. 리컨값을 확인해보세요." , pABTData->stABTHeader.iNumOfABT );
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
	 * @author    조철희 (churlhee.jo@lignex1.com)
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
			printf( "\n Init() 함수를 호출하지 않고 UpdateCEDEOBLibrary() 함수를 실행했습니다.!!" );
			Log( enError, "Init() 함수를 호출하지 않고 UpdateCEDEOBLibrary() 함수를 실행했습니다.!!" );
		}
		return;
	}

	/**
	 * @brief     Close
	 * @return    void
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2021-10-28, 13:39
	 * @warning
	 */
	void RadarAnlAlgotirhm::Close()
	{
		printf( "\n 레이더 분석 라이브러리를 종료합니다...." );
		Log( enNormal, "레이더 분석 라이브러리를 종료합니다...." );

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

}


