
#include "stdafx.h"

#define MATHFUNCSDLL_EXPORTS

#define _MAIN_
#define _MAIN_GLOBALS_


#include "../../files/Anal/OFP_Main.h"

#include "../../files/Anal/SigAnal/SysPara.h"
#include "../../files/Anal/NewSigAnal/NewSigAnal.h"

#include "../../files/Anal/EmitterMerge/ELEmitterMergeMngr.h"

#include "../../files/Include/globals.h"

#include "../../files/Anal/INC/PDW.h"

#include "RadarAnlAlgorithm.h"


CELEmitterMergeMngr *gpEmitterMergeMngr;

#ifdef _MSSQL_
CODBCDatabase gz_theMyODBC;
#endif


namespace RadarAnlAlgotirhm
{
    char gszHeader[100] = { "+-----------------------------------------------------------------------+" };

#if defined(_POCKETSONATA_) || defined(_712_)
    char gszProject[20] = { "위협 관리/식별" };

#elif defined(_ELINT_) || defined(_XBAND_)
    char gszProject[20] = { "레이더 분석" };

#else
    char gszProject[20] = { "ELINT" };

#endif

    /**
     * @brief     위협 병합 및 식별 라이브러리를 초기화한다. 최소 한번은 호출해야 합니다.
     * @param     HWND hWnd, 이 값은 WM_USER_LOGMSG 메시지를 처리할 Window Handler를 설정한다. 보통 pMainFrame->GetOutputWnd()->GetSafeHwnd() 으로 세팅한다.
     * @param     bool bDBThread, DB 쓰레드를 적용 여부를 결정한다.
     * @param     bool bLocal
     * @return    void
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2022-10-19 13:45:37
     * @warning
     */
	void RadarAnlAlgotirhm::Init( HWND hWnd, bool bDBThread, bool bLocal )
	{
		SetWindowHandler( hWnd );

		if( bLocal == false /* && CheckPing() == TRUE */ ) {
            //SetLocal( bLocal );
		}
		else {
            SetLocal( true );
		}

        SetLocal( true );

        if( g_pTheLog == NULL ) {
            g_pTheLog = new CLog();
        }

        ::Log(enNormal, "%s", gszHeader);
        ::Log(enNormal, "%s 라이브러리를 구동합니다....Ver", gszProject);

		if( gpEmitterMergeMngr == NULL ) {
			g_pTheSysConfig = new CSysConfig();

#ifdef _MSSQL_
			gpEmitterMergeMngr = new CELEmitterMergeMngr( bDBThread, & gz_theMyODBC );
#else
			gpEmitterMergeMngr = new CELEmitterMergeMngr( bDBThread, NULL );
#endif

		}

		return;
	}

    /**
     * @brief     위협 병합 및 식별 관리를 초기화할 때 호출한다.
     * @return    void
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2022-10-19 13:45:05
     * @warning
     */
	void RadarAnlAlgotirhm::SWInit()
	{
        ::Log(enNormal, "%s", gszHeader);
        ::Log(enNormal, "%s 라이브러리를 초기화 합니다.", gszProject);

		if( gpEmitterMergeMngr == NULL ) {
            ::Log(enError, "Init() 함수를 호출하지 않고 Start() 함수를 실행했습니다.!!");
		}
		else {
			gpEmitterMergeMngr->Init();

		}

	}

    /**
     * @brief     위협 관리에 LOB 데이터를 실어 위협 관리를 수행하게 한다.
     * @param     STR_LOBDATA * pLOBData
     * @return    void
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2022-10-19 13:55:31
     * @warning
     */
    bool RadarAnlAlgotirhm::Start(STR_LOBDATA *pLOBData)
	{
        bool bRet = false;

		SRxLOBHeader *pstLOBHeader;
		SRxLOBData *pstLOBData;

		if( gpEmitterMergeMngr == NULL ) {
            ::Log(enError, "Init() 함수를 호출하지 않고 Start() 함수를 실행했습니다 !!");
		}
		else {
			gpEmitterMergeMngr->Start();

			if( pLOBData->stLOBHeader.uiNumOfLOB > MAX_LOB_DATA || pLOBData->stLOBHeader.uiNumOfLOB == 0 ) {
                ::Log(enError, "LOB 데이터 개수[%d]가 초과해서 실행을 중단합니다.", pLOBData->stLOBHeader.uiNumOfLOB);
			}
            else {

#if defined(_ELINT_) || defined(_XBAND_)
                ::Log(enNormal, "OP_INIT_ID[%ld] 레이더 방탐[%d]에서 LOB 데이터 [%d]개를 수신하여 처리합니다.", pLOBData->stLOBData[0].uiOpInitID, pLOBData->stLOBData[0].iCollectorID, pLOBData->stLOBHeader.uiNumOfLOB);
#else
                ::Log(enNormal, "OP_INIT_ID[%d] LOB 데이터 [%d]개를 수신하여 처리합니다.", GetOpInitID(), pLOBData->stLOBHeader.uiNumOfLOB);
#endif

			pstLOBHeader = & pLOBData->stLOBHeader;
			pstLOBData = & pLOBData->stLOBData[0];
			for( unsigned int i=0 ; i < pstLOBHeader->uiNumOfLOB ; ++i ) {
#if defined(_ELINT_) || defined(_XBAND_)
				if( pstLOBData->aucTaskID[0] != NULL ) {
					gpEmitterMergeMngr->ManageThreat( pstLOBHeader, pstLOBData, NULL, false );
                    gpEmitterMergeMngr->DISP_FineLOB(pstLOBData);

                    bRet = true;

					++ pstLOBData;
				}
				else {
					Log( enError, "%d 번째 LOB 데어터의 과제 정보가 없습니다 !!!" , i+1 );
				}
#else
				gpEmitterMergeMngr->ManageThreat(pstLOBHeader, pstLOBData, NULL, false);
				gpEmitterMergeMngr->DISP_FineLOB(pstLOBData);

				bRet = true;

				++pstLOBData;
#endif

			}

			gpEmitterMergeMngr->PrintAllABTData();

                ::Log(enLineFeed, "");
            }

		}

        return bRet;
    }


    /**
     * @brief     식별 라이브러리가 변경이 됐을때 이를 호출하여 CED/EOB를 불러오도록 한다.
     * @return    void
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2021-10-28, 13:39
     * @warning
     */
    void RadarAnlAlgotirhm::UpdateCEDEOBLibrary()
    {
        if (gpEmitterMergeMngr != NULL) {
            gpEmitterMergeMngr->UpdateCEDEOBLibrary();
        }
        else {
            printf("\n Init() 함수를 호출하지 않고 UpdateCEDEOBLibrary() 함수를 실행했습니다.!!");
            Log(enError, "Init() 함수를 호출하지 않고 UpdateCEDEOBLibrary() 함수를 실행했습니다.!!");
        }
        return;
    }

    /**
     * @brief     레이더 분석 라이브러리를 종료 합니다. 프로그램 종료시 호출하면 됩니다.
     * @return    void
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2021-10-28, 13:39
     * @warning
     */
    void RadarAnlAlgotirhm::Close()
    {

        if (g_pTheLog != NULL) {
            Log(enNormal, "레이더 분석 라이브러리를 종료합니다....");
        }
        else {
            printf("\n 레이더 분석 라이브러리를 종료합니다....");
        }

        if (gpEmitterMergeMngr != NULL) {
            delete gpEmitterMergeMngr;
            gpEmitterMergeMngr = NULL;
        }
        if (g_pTheLog != NULL) {
            delete g_pTheLog;
            g_pTheLog = NULL;
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
		unsigned int i;
		bool bRet = false;

		vector<SRxLOBData>::pointer pSRxLOBData;

		pLOBData->stLOBHeader.uiNumOfLOB = gpEmitterMergeMngr->m_VecLOBData.size();
		if( pLOBData->stLOBHeader.uiNumOfLOB > MAX_LOB_DATA ) {
			Printf( "\n LOB 데이터 개수[%d]가 초과해서 결과를 리턴하지 않습니다. 리컨값을 확인해보세요." , pLOBData->stLOBHeader.uiNumOfLOB );
			Log( enError, "LOB 데이터 개수[%d]가 초과해서 결과를 리턴하지 않습니다. 리컨값을 확인해보세요." , pLOBData->stLOBHeader.uiNumOfLOB );
		}
		else {
			pSRxLOBData = gpEmitterMergeMngr->m_VecLOBData.data();
			for( i=0 ; i < pLOBData->stLOBHeader.uiNumOfLOB ; ++i ) {
				memcpy( & pLOBData->stLOBData[i], pSRxLOBData, sizeof(struct SRxLOBData) );
				++ pSRxLOBData;

				bRet = true;
			}
		}

		return bRet;
	}

    /**
     * @brief     GetLOBData
     * @return    std::vector<SRxLOBData> *
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-06-13 09:39:15
     * @warning
     */
    std::vector<SRxLOBData> *RadarAnlAlgotirhm::GetLOBData()
    {
        return & gpEmitterMergeMngr->m_VecLOBData;
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
				memcpy( & pABTData->stABTData[i], pSRxABTData, sizeof( struct SRxABTData) );
				++ pSRxABTData;

				bRet = true;
			}
		}

		return bRet;
	}

    /**
     * @brief     GetABTData
     * @return    std::vector<SRxABTData> *
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-06-13 09:39:56
     * @warning
     */
    std::vector<SRxABTData> *RadarAnlAlgotirhm::GetABTData()
    {
        return & gpEmitterMergeMngr->m_VecABTData;
    }

    /**
     * @brief     GetAETData
     * @param     STR_AETDATA * pAETData
     * @return    bool
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-06-09 20:09:34
     * @warning
     */
    bool RadarAnlAlgotirhm::GetAETData( STR_AETDATA *pAETData )
    {
        int i;
        bool bRet = false;

        vector<SRxAETData>::pointer pSRxAETData;

        pAETData->stAETHeader.iNumOfAET = gpEmitterMergeMngr->m_VecAETData.size();

        if( pAETData->stAETHeader.iNumOfAET > MAX_LOB_DATA ) {
            Printf( "\n AET 데이터 개수[%d]가 초과해서 결과를 리턴하지 않습니다. 리컨값을 확인해보세요.", pAETData->stAETHeader.iNumOfAET );
            Log( enError, "AET 데이터 개수[%d]가 초과해서 결과를 리턴하지 않습니다. 리컨값을 확인해보세요.", pAETData->stAETHeader.iNumOfAET );
        }
        else {
            pSRxAETData = gpEmitterMergeMngr->m_VecAETData.data();
            for( i = 0; i < pAETData->stAETHeader.iNumOfAET; ++i ) {
                memcpy( & pAETData->stAETData[i], pSRxAETData, sizeof( struct SRxAETData ) );
                ++ pSRxAETData;

                bRet = true;
            }
        }

        return bRet;
    }

    /**
     * @brief     GetAETData
     * @return    std::vector<SRxAETData> *
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-06-13 09:40:48
     * @warning
     */
    std::vector<SRxAETData> *RadarAnlAlgotirhm::GetAETData()
    {
        return & gpEmitterMergeMngr->m_VecAETData;
    }

#if defined(_POCKETSONATA_) || defined(_712_)

	/**
     * @brief     위협 관리/식별 함수에 대한 위협 결과를 얻을때 사용한다. Start() 후에
     * @param     std::vector<SRxLOBData> * pVecLOBData
     * @param     std::vector<SRxABTData> * pVecABTData
     * @param     std::vector<SRxAETData> * pVecAETData
     * @return    bool
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
	 * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2022-10-19 16:23:39
	 * @warning
	 */
    bool RadarAnlAlgotirhm::GetResult(std::vector<SRxLOBData> *pVecLOBData, std::vector<SRxABTData> *pVecABTData, std::vector<SRxAETData> *pVecAETData)
	{
        return false;
	}

	unsigned int RadarAnlAlgotirhm::GetOpInitID()
	{
		return gpEmitterMergeMngr->GetOpInitID();

	}

#else



    /**
     * @brief     GetOPInitID
     * @return    LONG
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-21, 17:06
     * @warning
     */
    unsigned int RadarAnlAlgotirhm::GetOpInitID()
    {
        return gpEmitterMergeMngr->GetOpInitID();

    }

#endif


}


