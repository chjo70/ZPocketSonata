
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
    char gszHeader[100] = { "+-----------------------------------------------------------------------+" };

#ifdef _POCKETSONATA_
    char gszProject[20] = { "���� ����/�ĺ�" };

#elif defined(_ELINT_) || defined(_XBAND_)
    char gszProject[20] = { "���̴� �м�" };

#else
    char gszProject[20] = { "ELINT" };

#endif

    /**
     * @brief     ���� ���� �� �ĺ� ���̺귯���� �ʱ�ȭ�Ѵ�. �ּ� �ѹ��� ȣ���ؾ� �մϴ�.
     * @param     HWND hWnd, �� ���� WM_USER_LOGMSG �޽����� ó���� Window Handler�� �����Ѵ�. ���� pMainFrame->GetOutputWnd()->GetSafeHwnd() ���� �����Ѵ�.
     * @param     bool bDBThread, DB �����带 ���� ���θ� �����Ѵ�.
     * @param     bool bLocal
     * @return    void
     * @exception ���ܻ����� �Է����ְų� '�ش���� ����' ���� ���ּ���.
     * @author    ��ö�� (churlhee.jo@lignex1.com)
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
            //SetLocal( true );
		}

        if( g_pTheLog == NULL ) {
            g_pTheLog = new CLog();
        }

        ::Log(enNormal, "%s", gszHeader);
        ::Log(enNormal, "%s ���̺귯���� �����մϴ�....Ver", gszProject);

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
     * @brief     ���� ���� �� �ĺ� ������ �ʱ�ȭ�� �� ȣ���Ѵ�.
     * @return    void
     * @exception ���ܻ����� �Է����ְų� '�ش���� ����' ���� ���ּ���.
     * @author    ��ö�� (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2022-10-19 13:45:05
     * @warning
     */
	void RadarAnlAlgotirhm::SWInit()
	{
        ::Log(enNormal, "%s", gszHeader);
        ::Log(enNormal, "%s ���̺귯���� �ʱ�ȭ �մϴ�.", gszProject);

		if( gpEmitterMergeMngr == NULL ) {
            ::Log(enError, "Init() �Լ��� ȣ������ �ʰ� Start() �Լ��� �����߽��ϴ�.!!");
		}
		else {
			gpEmitterMergeMngr->Init();

		}

	}

    /**
     * @brief     ���� ������ LOB �����͸� �Ǿ� ���� ������ �����ϰ� �Ѵ�.
     * @param     STR_LOBDATA * pLOBData
     * @return    void
     * @exception ���ܻ����� �Է����ְų� '�ش���� ����' ���� ���ּ���.
     * @author    ��ö�� (churlhee.jo@lignex1.com)
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
            ::Log(enError, "Init() �Լ��� ȣ������ �ʰ� Start() �Լ��� �����߽��ϴ� !!");
		}
		else {
			gpEmitterMergeMngr->Start();

			if( pLOBData->stLOBHeader.uiNumOfLOB > MAX_LOB_DATA || pLOBData->stLOBHeader.uiNumOfLOB == 0 ) {
                ::Log(enError, "LOB ������ ����[%d]�� �ʰ��ؼ� ������ �ߴ��մϴ�.", pLOBData->stLOBHeader.uiNumOfLOB);
			}
            else {

#if defined(_ELINT_) || defined(_XBAND_)
                ::Log(enNormal, "OP_INIT_ID[%ld] ���̴� ��Ž[%d]���� LOB ������ [%d]���� �����Ͽ� ó���մϴ�.", pLOBData->stLOBData[0].uiOpInitID, pLOBData->stLOBData[0].iCollectorID, pLOBData->stLOBHeader.uiNumOfLOB);
#else
                ::Log(enNormal, "OP_INIT_ID[%d] LOB ������ [%d]���� �����Ͽ� ó���մϴ�.", GetOpInitID(), pLOBData->stLOBHeader.uiNumOfLOB);
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
					Log( enError, "%d ��° LOB �������� ���� ������ �����ϴ� !!!" , i+1 );
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
     * @brief     �ĺ� ���̺귯���� ������ ������ �̸� ȣ���Ͽ� CED/EOB�� �ҷ������� �Ѵ�.
     * @return    void
     * @exception
     * @author    ��ö�� (churlhee.jo@lignex1.com)
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
            printf("\n Init() �Լ��� ȣ������ �ʰ� UpdateCEDEOBLibrary() �Լ��� �����߽��ϴ�.!!");
            Log(enError, "Init() �Լ��� ȣ������ �ʰ� UpdateCEDEOBLibrary() �Լ��� �����߽��ϴ�.!!");
        }
        return;
    }

    /**
     * @brief     ���̴� �м� ���̺귯���� ���� �մϴ�. ���α׷� ����� ȣ���ϸ� �˴ϴ�.
     * @return    void
     * @exception
     * @author    ��ö�� (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2021-10-28, 13:39
     * @warning
     */
    void RadarAnlAlgotirhm::Close()
    {

        if (g_pTheLog != NULL) {
            Log(enNormal, "���̴� �м� ���̺귯���� �����մϴ�....");
        }
        else {
            printf("\n ���̴� �м� ���̺귯���� �����մϴ�....");
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

#ifdef _POCKETSONATA_

	/**
     * @brief     ���� ����/�ĺ� �Լ��� ���� ���� ����� ������ ����Ѵ�. Start() �Ŀ� 
     * @param     std::vector<SRxLOBData> * pVecLOBData
     * @param     std::vector<SRxABTData> * pVecABTData
     * @param     std::vector<SRxAETData> * pVecAETData
     * @return    bool
     * @exception ���ܻ����� �Է����ְų� '�ش���� ����' ���� ���ּ���.
	 * @author    ��ö�� (churlhee.jo@lignex1.com)
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
     * @author    ��ö�� (churlhee.jo@lignex1.com)
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


