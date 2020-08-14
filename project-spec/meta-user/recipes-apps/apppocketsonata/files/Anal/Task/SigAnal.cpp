// SigAnal.cpp: implementation of the CSigAnal class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#ifdef _WIN32
//#include "../../A50SigAnal/stdafx.h"

#endif

#include "../OFP_Main.h"

#include "SigAnal.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSigAnal::CSigAnal( char *pTaskName )
{
	strcpy_s( m_taskName, pTaskName );

	MallocBuffer();
	InitTask();
	InitVar();

}

CSigAnal::~CSigAnal()
{
	delete m_theNewSigAnal;
	//delete m_theKnownSigAnal;
	//delete m_theScanSigAnal;
	delete m_theSysPara;

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CSigAnal::InitVar
		\author   조철희
		\return   void
		\version  0.0.28
		\date     2008-06-21 11:50:16
		\warning
*/
void CSigAnal::InitVar()
{
	m_eAnalMode = NORMAL_MDOE;

	m_theNewSigAnal->InitVar( m_eAnalMode );
	//m_theKnownSigAnal->InitVar();
	//m_theScanSigAnal->InitVar();

	// m_thePdwFilter = theGetPdw->GetPdwFilter();

	m_eAnalMode = (enum ANALYSIS_MODE) theIni->ReadInt( "System", "AnalMode", NORMAL_MDOE );

	
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CSigAnal::InitTask
		\author   조철희
		\return   void
		\version  0.0.27
		\date     2008-06-09 12:08:09
		\warning
*/
void CSigAnal::InitTask()
{


}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CSigAnal::MallocBuffer
		\author   조철희
		\return   void
		\version  0.0.30
		\date     2008-07-17 13:24:25
		\warning
*/
void CSigAnal::MallocBuffer()
{
	m_theNewSigAnal = new CNewSigAnal( NEW_COLLECT_PDW );
	if( m_theNewSigAnal == NULL ) {
		PrintErr( ( "\n [W] 메모리 부족입니다. CNewSigAnal 객체를 생성할 수 없습니다 !" ) );
	}

// 	m_theKnownSigAnal = new CKnownSigAnal( KWN_COLLECT_PDW );
// 	if( m_theNewSigAnal == NULL ) {
// 		PrintErr( ( "\n [W] 메모리 부족입니다. CKnownSigAnal 객체를 생성할 수 없습니다 !" ) );
// 	}
// 
// 	m_theScanSigAnal = new CScanSigAnal( SCN_COLLECT_PDW );
// 	if( m_theNewSigAnal == NULL ) {
// 		PrintErr( ( "\n [W] 메모리 부족입니다. CScanSigAnal 객체를 생성할 수 없습니다 !" ) );
// 	}
// 
 	m_theSysPara = new CSysPara();
 	if( m_theSysPara == NULL ) {
 		PrintErr( ( "\n [W] 메모리 부족입니다. m_theSysPara 객체를 생성할 수 없습니다 !" ) );
 	}

}


//////////////////////////////////////////////////////////////////////////
/*! \brief    CSigAnal::Run
		\author   조철희
		\return   void
		\version  0.0.26
		\date     2008-06-09 10:45:50
		\warning
*/
void CSigAnal::Run()
{
#ifdef _WIN32
	bool bRslt = true;
	SQMsg stMsg;

	while (IsRunning() == TRUE) {
		m_cond.Wait(); // 시그널을 기다리는 중이다. 

		bRslt = GetMsgFromQ(stMsg);

		if (bRslt)
		{
			ParseMessage(&stMsg);			//
		}
		else // 큐에 더 이상 메시지가 없다는 이야기다.
		{
			m_cond.LIGResetEvent();
		}
	}

#else
	STR_QUEUE_MESSAGE *pQMsg;

	pQMsg = ( STR_QUEUE_MESSAGE * ) GetQueueMessage();

	for( ;; ) {
		ReceiveMessage();

		if( TRUE == ParseMessage() ) {
			
		}

	}
#endif

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CSigAnal::ParseMessage
		\author   조철희
		\return   BOOL
		\version  0.0.26
		\date     2008-06-09 11:06:27
		\warning
*/
BOOL CSigAnal::ParseMessage()
{
	STR_QUEUE_MESSAGE *pQMsg;

	pQMsg = ( STR_QUEUE_MESSAGE * ) GetQueueMessage();

	switch( pQMsg->opCode ) {
		case REQ_POWER_ON_INIT :
			InitVar();
			break;

		case REQ_START_ANAL :
			StartAnal( (enum ANAL) pQMsg->address1, pQMsg->opData, (enum BAND_INFO) pQMsg->address2 );
			SendAetMessage( (enum ANAL) pQMsg->address1 );
			break;

		case REQ_RELOAD_UDF :
		case REQ_KEY_PFM :
		case REQ_STOP_ANAL :
			StopAnal();
			break;

		default :
			PrintErr( ( "\n [W] 잘못된 메시지[0x%x]를 수신했습니다." , pQMsg->opCode ) );
			return FALSE;
	}

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CSigAnal::StartAnal
		\author   조철희
		\param    Anal 인자형태 enum ANAL
		\param    noFilter 인자형태 int
		\param    nBand 인자형태 enum BAND_INFO
		\return   void
		\version  0.0.26
		\date     2008-06-09 11:07:53
		\warning
*/
void CSigAnal::StartAnal( enum ANAL Anal, int noFilter, enum BAND_INFO nBand )
{
	//int noEMT;
	STR_MANAET *pManAet;

	m_nBand = nBand;

	theGetPdwTask->SetColStat( Anal, noFilter, ON_ANALYSIS );

	//m_pPDWData = m_thePdwFilter->GetPDWData( Anal, noFilter );
	switch( Anal ) {
		case NEW_ANAL :
			//m_theNewSigAnal->Start( & m_stPDWData );
			break;

		case KWN_ANAL :
			//noEMT = m_thePdwFilter->GetNoEMT( Anal, noFilter );
			//Printf( "\n Known SigAnal[%d, T%d]" , noEMT, noFilter );
			// 
			// pManAet = theManAet->GetManAet( noEMT );

			/*! \bug  에미터가 삭제(에미터 변경의 병합 판단하에 에미터 삭제 결정) 되었으면 추적 분석 요청을 중지한다.
			    \date 2009-10-06 18:19:54, 조철희
			*/
			if( pManAet->aet.noEMT != _spInvAET ) {
				//m_theKnownSigAnal->Start( m_pPDWData, pManAet );

				// 스캔 분석=Steady, Conical 을 분석한다.
				//ScanSigAnal();
			}
			else {
				//Printf( "\n Ignore the Signal Analysis[%d]..." , noEMT );
			}

			//theGetPdw->m_thePdwFilter->ClearCollectingPdw( Anal, noFilter );
			break;

		case SCN_ANAL :
			//noEMT = m_thePdwFilter->GetNoEMT( Anal, noFilter );
			//Printf( "\n Scan SigAnal[%d, T%d]" , noEMT, noFilter );

			//pManAet = theManAet->GetManAet( noEMT );
			//m_theScanSigAnal->Start( m_pPDWData, pManAet );

			//theGetPdw->m_thePdwFilter->ClearCollectingPdw( Anal, noFilter );
			break;

	}

	theGetPdwTask->SetColStat( Anal, noFilter, ANALYSIS_END );

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CSigAnal::SendAetMessage
		\author   조철희
		\param    Anal 인자형태 enum ANAL
		\return   void
		\version  0.0.30
		\date     2008-07-16 17:27:10
		\warning
*/
void CSigAnal::SendAetMessage( enum ANAL Anal )
{
	int i, coAet;
	SRxLOBData *pNewLOB;
	//STR_UPDAET *pUpdAet;
	STR_QUEUE_AET_MESSAGE interQMsg;

	switch( Anal ) {
		case NEW_ANAL :
			if( GetAnalMode() == SIMUL_MODE ) {
				m_theNewSigAnal->RunSimul( m_nBand );
			}

			interQMsg.opCode = REQ_NEW_AET;
			pNewLOB = m_theNewSigAnal->GetLOB();
			coAet = m_theNewSigAnal->GetCoAet();

			if( coAet != 0 ) {
				for( i=0 ; i < coAet ; ++i, ++pNewLOB) {
					SendSystemLog( REQ_AET_DETAIL, pNewLOB, m_theNewSigAnal->GetEmitter() );

					memcpy( & interQMsg.stLOB, pNewLOB, sizeof( SRxLOBData ) );
					//theManAet->SendMessage( & interQMsg );
				}
			}
			else {
				// Printf( "\n None Emitter !" );
			}
			break;

// 		case KWN_ANAL :
// 			coAet = m_theKnownSigAnal->GetCoUpdAet();
// 			interQMsg.opData = m_theKnownSigAnal->GetNoEMT();
// 
// 			if( GetAnalMode() == SIMUL_MODE ) {
// 				m_theKnownSigAnal->Simul();
// 
// 				interQMsg.opCode = REQ_LST_AET;
// 				//theManAet->SendMessage( & interQMsg );
// 			}
// 			else {
// 				if( coAet == 0 ) {
// 					interQMsg.opCode = REQ_LST_AET;
// 					Printf( "\n Send Lost[%d]" , interQMsg.opData );
// 				}
// 				else {
// 					interQMsg.opCode = REQ_UPD_AET;
// 					pUpdAet = m_theKnownSigAnal->GetUpdAet();
// 					memcpy( & interQMsg.aet, pUpdAet, sizeof( STR_UPDAET ) );
// 				}
// 
// 				//theManAet->SendMessage( & interQMsg );
// 
// 				interQMsg.opCode = REQ_NEW_AET;
// 				pNewAet = m_theKnownSigAnal->GetNewAet();
// 				coAet = m_theKnownSigAnal->GetCoNewAet();
// 				if( coAet != 0 ) {
// 					for( i=0 ; i < coAet ; ++i, ++pNewAet ) {
// 						SendSystemLog( REQ_AET_DETAIL, pNewAet, m_theKnownSigAnal->GetEmitter() );
// 
// 						memcpy( & interQMsg.aet, pNewAet, sizeof( STR_NEWAET ) );
// 						//theManAet->SendMessage( & interQMsg );
// 					}
// 				}
// 			}
// 			break;
// 
// 		case SCN_ANAL :
// 			interQMsg.opCode = REQ_UPD_SCN;
// 			interQMsg.opData = m_theScanSigAnal->GetNoEMT();
// 			//pUpdAet = m_theScanSigAnal->GetUpdAet();
// 
// 			Printf( "\n pUpdAet->aet.as.stat[%d], Scan[%d], Type[%d]" , pUpdAet->aet.as.stat, pUpdAet->aet.as.prd, pUpdAet->aet.as.type );
// 
// 			memcpy( & interQMsg.aet, pUpdAet, sizeof( STR_NEWAET ) );
// 			//theManAet->SendMessage( & interQMsg );
// 			break;
	}
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CSigAnal::DISP_FineAet
		\author   조철희
		\param    pManAet 인자형태 STR_MANAET *
		\return   void
		\version  0.0.35
		\date     2008-08-08 23:31:37
		\warning
*/
void CSigAnal::DISP_FineAet( STR_MANAET *pManAet )
{
	return;
	m_theNewSigAnal->DISP_FineAet( pManAet );

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CSigAnal::DISP_HexFineAet
		\author   조철희
		\param    pNewAet 인자형태 STR_NEWAET *
		\return   void
		\version  0.0.33
		\date     2008-07-24 11:52:06
		\warning
*/
void CSigAnal::DISP_HexFineAet( STR_NEWAET *pNewAet )
{
	//m_theNewSigAnal->DISP_HexFineAet( pNewAet );

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CSigAnal::StopAnal
		\author   조철희
		\return   void
		\version  0.0.41
		\date     2008-08-24 16:05:48
		\warning
*/
void CSigAnal::StopAnal()
{
	EmptyQueue();
	InitVar();

	// WaitEchoMessage( OS_ONE_MILLISEC(10) );
	SendEchoMessage();

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CSigAnal::ScanSigAnal
		\author   조철희
		\return   void
		\version  0.0.51
		\date     2008-10-11 14:00:56
		\warning
*/
void CSigAnal::ScanSigAnal()
{
// 	int coAet;
// 
// 	STR_UPDAET *pUpdAet;
// 
// 	coAet = m_theKnownSigAnal->GetCoUpdAet();
// 	if( coAet != 0 ) {
// 		pUpdAet = m_theKnownSigAnal->GetUpdAet();
// 		// STR_EMITTER *pEmitter = m_theKnownSigAnal->GetEmitter();
// 		// STR_PULSE_TRAIN_SEG *pSeg = m_theKnownSigAnal->GetPulseSeg();
// 		// m_theScanSigAnal->Start( m_pPDWData, pEmitter, pSeg, pUpdAet );
// 
// 		m_theScanSigAnal->Start( m_pPDWData, pUpdAet );
// 	}
	
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CSigAnal::SendSystemLog
		\author   조철희
		\param    opData 인자형태 int
		\param    pNewAet 인자형태 STR_NEWAET *
		\return   void
		\version  0.0.59
		\date     2008-11-28 11:46:00
		\warning
*/
void CSigAnal::SendSystemLog( int opData, SRxLOBData *pLOB, STR_EMITTER *pEmitter )
{
	//int i, pdw_count;

	//PDWINDEX *pPDWIndex;

	//_PDW *pPdw;
	//UNI_PG_PDW *pLogPdw;

// 	if( ( TRUE || theGrDisp->GetMark() ) && GetAnalMode() == NORMAL_MDOE ) {
// 		m_logMsg.opCode = REQ_ADD_SYSTEMLOG;
// 
// 		// 로그 구조체에 데이터를 저장한다.
// 		m_logMsg.log.opCode = opData;
// 		
// 		// 에미터 정보를 저장한다.
// 		memcpy( & m_logMsg.log.u.aetDet.aet, pNewAet, sizeof( STR_NEWAET ) );
// 
// 		pdw_count = pEmitter->pdw.count;
// 		pPDWIndex = pEmitter->pdw.pIndex;
// 		pPdw = m_pPDWData->pPdw;
// 		pLogPdw = & m_logMsg.log.u.aetDet.pdw[0];
// 		for( i=0 ; i < pdw_count && i < MAX_LOG_PDW ; ++i ) {
// 			pLogPdw->word[0] = pPdw->word[0];
// 			pLogPdw->word[1] = pPdw->word[1];
// 			pLogPdw->word[2] = pPdw->word[2];
// 			pLogPdw->word[3] = pPdw->word[3];
// 
// 			++pPDWIndex;
// 			++pLogPdw;
// 		}
// 
// 		m_logMsg.log.dSize = sizeof( STR_NEWAET ) + sizeof( UNI_PG_PDW ) * (i+1);
// 		m_logMsg.log.log_time = time(NULL);
// 		
// 		theCtrlCMDS->SendMessage( & m_logMsg );
// 	}

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CSigAnal::GetAnalMode
		\author   조철희
		\return   enum ANALYSIS_MODE
		\version  0.1.114
		\date     2009-11-13 15:36:03
		\warning
*/
enum ANALYSIS_MODE CSigAnal::GetAnalMode()
{
#ifdef _WIN32
	// return SIMUL_MODE;
#endif

	return m_eAnalMode;
}


/**
  * @brief		메시지를 해석하여 처리함수를 호출한다.
  * @param		SQMsg * psqMsg
  * @return		성공시 true, 실패시 false
*/
BOOL CSigAnal::ParseMessage(SQMsg *psqMsg)
{

	switch (psqMsg->uiOpcode) {
		case REQ_STEP_ANAL:
			Start(psqMsg);
			break;

		default:
			PrintErr(("\n [W] 잘못된 메시지[0x%x]를 수신했습니다.", psqMsg->uiOpcode));
			return FALSE;
	}

	return TRUE;
}

/**
  * @brief		분석 시작을 수행한다.
  * @param		SQMsg * psqMsg
  * @return		성공시 true, 실패시 false
*/
void CSigAnal::Start( SQMsg *psqMsg )
{

	//m_stPDWData.count = psqMsg->x.stPDWData.count;
	//memcpy(m_stPDWData.aucTaskID, psqMsg->x.stPDWData.aucTaskID, LENGTH_OF_TASK_ID );
	//memcpy(m_stPDWData.stPDW, psqMsg->x.stPDWData.stPDW, sizeof(_PDW)* m_stPDWData.count );
	memcpy( & m_stPDWData, & psqMsg->x.stPDWData, sizeof(STR_PDWDATA) );
	m_theNewSigAnal->Start( & m_stPDWData );

	SendMessageToLOBMngrTask();

}

/**
  * @brief		LOB 데이터를 LOB 위협 관리 메니저로 메시지를 전달한다.
  * @return 	void
*/
void CSigAnal::SendMessageToLOBMngrTask()
{
	//int i;
	SRxLOBHeader *pLOBHeader;
	SRxLOBData *pLOBData;

	SRxLOBData *pLOBDATA;

	int nCoAET=m_theNewSigAnal->GetCoAet();

	m_SendQMsg.uiOpcode = RX_LOBDATA;
	m_SendQMsg.usSize = sizeof( SRxLOBHeader ) + sizeof( SRxLOBData ) * nCoAET;

	pLOBHeader = ( SRxLOBHeader * ) & m_SendQMsg.x.buf[0];
	pLOBHeader->iNumOfLOB = nCoAET;

	//
	pLOBDATA = m_theNewSigAnal->GetLOB();
	pLOBData = ( SRxLOBData * ) & m_SendQMsg.x.buf[sizeof(SRxLOBHeader)];
	memcpy( pLOBData, pLOBDATA, sizeof(SRxLOBData)*nCoAET );
	memcpy( pLOBData->aucTaskID, m_stPDWData.aucTaskID, sizeof(pLOBData->aucTaskID) );

	if( gstbSimulator == true ) {
		theLOBMngrTask->SendMessage( & m_SendQMsg );
	}
	else {
		// SendLan
	}

}

// void CSigAnal::MakeLOBDataFromAET( SRxLOBData *pLOBData )
// {
// 	int i;
// 	int nCoAET=m_theNewSigAnal->GetCoAet();
// 	STR_EMITTER *pNewAet=m_theNewSigAnal->GetEmitter();
// 
// 	for( i=0 ; i < nCoAET ; ++i ) {
// 		pLOBData->uiLOBID = 0;
// 		pLOBData->uiABTID = 0;
// 		pLOBData->uiAETID = 0;
// 
// 		pLOBData->tiContactTime = time(NULL);
// 		pLOBData->tiContactTimems = 1;
// 

// // 		pLOBData->fMeanDOA;										// [0.1도]
// 		pLOBData->fMaxDOA;
// 		pLOBData->fMinDOA;

// 
// 		++ pLOBData;
// 	}
// 
// }
