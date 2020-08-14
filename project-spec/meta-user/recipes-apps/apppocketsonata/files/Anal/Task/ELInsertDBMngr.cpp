/**
 * @file      ELInsertDB.cpp
 * @brief     
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-03-08, 오후 8:34 
 * @warning   
 */


#include "stdafx.h"

#include "ELInsertDBMngr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#define CRTDBG_MAP_ALLOC
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define WAIT_QUEUE					(1000)

CELInsertDBMngr* CELInsertDBMngr::m_pInstance = nullptr;

//////////////////////////////////////////////////////////////////////////
/*!
* @brief		생성자로서 위협 관리, LOB 서비스 등의 객체를 할당하고 처리할 메시지를 등록한다.
* @return   리턴값 없음
* @version   0.0.1
* @author    조철희 (jeongnam.lee@lignex1.com)
* @date      2015-07-08 오후 3:37 
* @warning   
*/
CELInsertDBMngr::CELInsertDBMngr(char *pTaskName) : CMSSQL( & m_theMyODBC )
{
	strcpy_s( m_taskName, pTaskName );

	CMSSQL::Init();

 	m_nArrayLOB = _spZero;
// 	m_nArrayLOB_Position = _spZero;
 	m_nArrayABT = _spZero;
// 	m_nArrayABT_Position = _spZero;
 	m_nArrayAET = _spZero;
 
// 
// 	if( m_bIsSimulator == true || GP_MGR_TEST_PARAM->IsPOSN() == false || GP_MGR_TEST_PARAM->IsPSS() == true ) {
// 		m_pArrayLOB = new SELArrLOB;
// 		m_pArrayABT = new SELArrABT;
// 		m_pArrayAET = new SELArrAET;
// 
// 		memset( m_pArrayLOB, 0, sizeof(SELArrLOB) );
// 		memset( m_pArrayABT, 0, sizeof(SELArrABT) );
// 		memset( m_pArrayAET, 0, sizeof(SELArrAET) );
// 
// 		m_pArrayLOB_Position = new SELArrLOBABT_Position;
// 		m_pArrayABT_Position = new SELArrLOBABT_Position;
// 	}
// 	else {
// 		m_pArrayLOB = NULL;
// 		m_pArrayABT = NULL;
// 		m_pArrayAET = NULL;
// 
// 		m_pArrayLOB_Position = NULL;
// 		m_pArrayABT_Position = NULL;
// 	}
// 
 	Init();

}

/**
 * @brief     초기화 한다.
 * @param     void
 * @return    void
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2018-05-10, 오전 11:08 
 * @warning   
 */
void CELInsertDBMngr::Init()
{
	m_bDangerOfQueueBufferFull = false;

 	m_nBInsertLOB = 0;
 	m_nWInsertLOB = 0;
}

/**
 * @brief     객체 삭제 처리 한다.
 * @param     void
 * @return    CELInsertDBMngr *
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2018-05-10, 오전 11:08 
 * @warning   
 */
// CELInsertDBMngr* CELInsertDBMngr::GetUniqueInstance()
// {
// 	if (m_pInstance==nullptr)
// 		m_pInstance = new CELInsertDBMngr();	
// 	return m_pInstance;	
// }


//////////////////////////////////////////////////////////////////////////
/*!
* @brief     소멸자로서 처리할 메시지를 제거하고 리스트 목록을 제거한다.
* @return    리턴값 없음
* @version   0.0.1
* @author    조철희 (churlhee.jo@lignex1.com)
* @date      2015-07-08 오후 3:37 
* @warning   
*/
CELInsertDBMngr::~CELInsertDBMngr(void)
{	

// 	DeleteAllQData(); // 남아있던 msg q 를 모두 비운다.
// 
// 	delete m_pArrayLOB;
// 	delete m_pArrayABT;
// 	delete m_pArrayAET;
// 
// 	delete m_pArrayLOB_Position;
// 	delete m_pArrayABT_Position;

	m_theMyODBC.Close();

	TRACE("[매니저 종료] CELInsertDBMngr \n ");
}

//////////////////////////////////////////////////////////////////////////
/*!
* @brief     싱글턴 객체를 내부에서 자체적으로 delete 하기위한 내부 class 소멸자
* @return    리턴값 없음
* @version   0.0.1
* @author    조철희 (churlhee.jo@lignex1.com)
* @date      2016-03-28 오후 5:28 
* @warning   
*/
CELInsertDBMngr::Cleanup::~Cleanup()
{
	ReleaseInstance();
}


//////////////////////////////////////////////////////////////////////////
/*!
* @brief     싱글턴 객체 매니저 얻어오는 함수
* @return    객체 포인터
* @version   0.0.1
* @author    조철희 (churlhee.jo@lignex1.com)
* @date      2015-07-08 오후 3:37 
* @warning   
*/
CELInsertDBMngr* CELInsertDBMngr::getInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new CELInsertDBMngr( "InsertDB" );
		static Cleanup cleanup;
	}
	return m_pInstance;	
}

//////////////////////////////////////////////////////////////////////////
/*!
* @brief     싱글턴 객체를 HEAP에서 해제해 주기 위한 함수. 외부호출임.
* @return    리턴값 없음
* @version   0.0.1
* @author    조철희 (churlhee.jo@lignex1.com)
* @date      2015-07-08 오후 3:38 
* @warning   
*/
void CELInsertDBMngr::ReleaseInstance()
{
	if( m_pInstance != NULL ) {
		delete m_pInstance;
		m_pInstance = NULL;
	}

}

/**
* @brief     객체와 관련된 변수 등을 초기호한다.
* @return    void
* @author    조철희 (churlhee.jo@lignex1.com)
* @version   0.0.1
* @date      2016-07-23, 오전 10:29 
* @warning   
*/
void CELInsertDBMngr::InitFromExternalRequest( SQMsg& i_stMsg )
{
	// UserReceive( & i_stMsg );

	// 다른 객체들도 초기화 할 것이 있으면 아래에 추가한다.

}

BOOL CELInsertDBMngr::ParseMessage( SQMsg *psqMsg )
{
	CheckQueueMsg();

	switch( psqMsg->uiOpcode )
	{
	case CMDCODE_INSERTDB_LOBDATA_: 
		ProcessLOBDataMsg( psqMsg );
		break;

	case CMDCODE_INSERTDB_ABTDATA_: 
		ProcessABTDataMsg( psqMsg );
		break;

	case CMDCODE_INSERTDB_AETDATA_:
		//ProcessEmitterDataMsg( psqMsg );
		break;

	case CMDCODE_INSERTDB_DISPLAY_:
		//ProcessDisplayDataMsg( psqMsg );
		break;

	case CMDCODE_INSERTDB_FLUSH_ :
		//ProcessInsertDBMsg( & i_stMsg );
		break;

		// 사용자 메시지 처리
		// 	case CMDCODE_EL_POS_TO_GMI :
		// 		{
		// 			SElintUserMsg *pstUserMsg;
		// 
		// 			pstUserMsg = ( SElintUserMsg * ) i_stMsg.buf;
		// 
		// 			switch( pstUserMsg->nSubCommand )
		// 			{
		// 				case SUBCMDCODE_EL_THREAT_INITIALIZE :
		// 					ProcThreatInitializeMsgData();
		// 					break;
		// 
		// 				default :
		// 					break;
		// 
		// 			}
		// 		}
		// 		break;

	default :
		Printf("\n [W] 잘못된 메시지[0x%x]를 수신했습니다.", psqMsg->uiOpcode );
		return FALSE;
	}

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
/*!
* @brief     메시지 수신 함수. Worker Thread 처리를 위해 queue에 넣고 바로 리턴한다.
* @param     i_uiOpcode 수신 메시지의 opcode
* @param     i_usSize 수신 메시지의 데이터 길이
* @param     i_usOperatorID 운용자 ID
* @param     *i_pvData 수신 메시지의 데이터 포인터
* @param     i_bServer 연동기 여부 플레그
* @param     i_bReplay 재연 여부 플레그
* @return    리턴값 없음
* @version   0.0.1
* @author    조철희 (churlhee.jo@lignex1.com)
* @date      2015-07-08 오후 3:38 
* @warning   
*/
// void CELInsertDBMngr::Receive(unsigned int i_uiOpcode, unsigned short i_usSize, unsigned short i_usOperatorID, void *i_pvData,  bool i_bServer, bool i_bReplay )
// {
// 	SQMsg stMsg;
// 
// 	stMsg.uiOpcode				= i_uiOpcode;
// 	stMsg.usSize					= i_usSize;
// 	stMsg.usOperatorId		= i_usOperatorID;
// 	stMsg.nLinkNum			= GetLinkNum(i_usOperatorID);
// 	stMsg.bIsServer			= i_bServer;
// 	stMsg.bIsReplay			= i_bReplay;
// 	// stMsg.bIsFromPosition	= false;
// 	//stMsg.bIsServer			= i_bServer;
// 
// 	memcpy(stMsg.buf, i_pvData, i_usSize);
// 
// 	PushMsg(stMsg); // 쓰레드 처리를 위해 큐에 집어넣고 빠지기.
// 
// 	m_cond.LIGSetEvent();
// }

/**
* @brief     사용자 수신 처리 메시지 처리를 위한 함수
* @param     i_uiOpcode 수신 메시지의 opcode
* @param     i_usSize 수신 메시지의 데이터 길이
* @param     i_usOperatorID 운용자 ID
* @param     *i_pvData 수신 메시지의 데이터 포인터
* @param     i_bServer 연동기 여부 플레그
* @param     i_bReplay 재연 여부 플레그
* @param     nLink 링크 번호
* @return    리턴값 없음
* @author    조철희 (churlhee.jo@lignex1.com)
* @version   0.0.1
* @date      2016-04-15, 오후 6:14 
* @warning   
*/
// void CELInsertDBMngr::UserReceive(unsigned int i_uiOpcode, unsigned short i_usSize, unsigned short i_usOperatorID, void *i_pvData,  bool i_bServer, bool i_bReplay, int nLink )
// {
// 	SQMsg stMsg;
// 	stMsg.uiOpcode				= i_uiOpcode;
// 	stMsg.usSize					= i_usSize;
// 	stMsg.usOperatorId		= i_usOperatorID;
// 
// 	// 연동기 1/2 번에서 사용자 메시지를 처리하기 위한 함수
// 	stMsg.nLinkNum			= nLink;
// 
// 	stMsg.bIsServer			= i_bServer;
// 	stMsg.bIsReplay			= i_bReplay;
// 
// 	memcpy(stMsg.buf, i_pvData, i_usSize);
// 
// 	PushMsg(stMsg); // 쓰레드 처리를 위해 큐에 집어넣고 빠지기.
// 	m_cond.LIGSetEvent();
// 	
// }

/**
* @brief     다른 수신 처리 Mngr()간의 통신을 위한 함수
* @param     *pstMsg 사용자 메시지의 데이터367 포인터
* @return    리턴값 없음 
* @author    조철희 (churlhee.jo@lignex1.com)
* @version   0.0.1
* @date      2016-06-03, 오후 9:45 
* @warning   
*/
// void CELInsertDBMngr::UserReceive( SQMsg *pstMsg )
// {
// 	PushMsg(*pstMsg); // 쓰레드 처리를 위해 큐에 집어넣고 빠지기.
// 	m_cond.LIGSetEvent();
// 	
// }

void CELInsertDBMngr::Run()
{
#ifdef _WIN32
	bool bRslt = true;
	SQMsg stMsg;

	while( IsRunning() == TRUE) {
		m_cond.Wait(); // 시그널을 기다리는 중이다. 

		bRslt = GetMsgFromQ(stMsg);

		if(bRslt)
		{
			ParseMessage( & stMsg );			//
		}
		else // 큐에 더 이상 메시지가 없다는 이야기다.
		{
			m_cond.LIGResetEvent();
		}				
	}

#else
	for( ;; ) {
		ReceiveMessage();

		if( TRUE == ParseMessage() ) {

		}
	}
#endif

}

//////////////////////////////////////////////////////////////////////////
/*!
* @brief     메시지 처리함수 (쓰레드 함수)
* @param     i_stMsg 수신 메시지의 데이터 포인터
* @return    리턴값 없음
* @version   0.0.1
* @author    조철희 (churlhee.jo@lignex1.com)
* @date      2015-07-08 오후 3:39 
* @warning   
*/
// void CELInsertDBMngr::ProcessMsg(SQMsg& i_stMsg)
// {
// 
// 	// replay mode 상태를 멤버 변수에 저장함. 자체 삭제 메시지를 구현하기 위해서 사용함.
// 	/*! \todo   재현 모드일 때 ELINT한테 알려주는 함수가 필요함. 현재는 메시지를 통해서 설정하는 것으로 함.
// 	\author 조철희 (churlhee.jo@lignex1.com)
// 	\date 	2016-05-22 23:09:51
// 	*/
// 
// 	CheckQueueMsg();
// 
// 	switch(i_stMsg.uiOpcode)
// 	{
// 	case CMDCODE_INSERTDB_LOBDATA_: 
// 		//ProcessLOBDataMsg( & i_stMsg );
// 		break;
// 	case CMDCODE_INSERTDB_BEAMDATA_: 
// 		//ProcessBeamDataMsg( & i_stMsg );
// 		break;
// 	case CMDCODE_INSERTDB_EMITTERDATA_:
// 		//ProcessEmitterDataMsg( & i_stMsg );
// 		break;
// 
// 	case CMDCODE_INSERTDB_DISPLAY_:
// 		//ProcessDisplayDataMsg( & i_stMsg );
// 		break;
// 
// 	case CMDCODE_INSERTDB_FLUSH_ :
// 		//ProcessInsertDBMsg( & i_stMsg );
// 		break;

	// 사용자 메시지 처리
// 	case CMDCODE_EL_POS_TO_GMI :
// 		{
// 			SElintUserMsg *pstUserMsg;
// 
// 			pstUserMsg = ( SElintUserMsg * ) i_stMsg.buf;
// 
// 			switch( pstUserMsg->nSubCommand )
// 			{
// 				case SUBCMDCODE_EL_THREAT_INITIALIZE :
// 					ProcThreatInitializeMsgData();
// 					break;
// 
// 				default :
// 					break;
// 
// 			}
// 		}
// 		break;
// 
// 	default:
// 		{ //DTEC_Else
// 		}
// 		break;
// 	}	
// }

/**
 * @brief     위협 관리 초기화 메시지 처리한다.
 * @return    void
*/
void CELInsertDBMngr::ProcThreatInitializeMsgData()
{
	//DeleteAllQData();

}

/**
 * @brief     LOB 데이터를 내부 저장소에 저장한다.
 * @param     SQMsg * pstMsg
 * @return    void
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-11-01, 오후 7:40 
 * @warning   
 */
void CELInsertDBMngr::ProcessLOBDataMsg( SQMsg *pstMsg )
{
 	SRxLOBData *pLOBData;
	SELLOBDATA_EXT *pExt;

	pLOBData = & pstMsg->x.stLOBDataExt.stLOBData;
	pExt = & pstMsg->x.stLOBDataExt.stLOBDataExt;

	TRACE( "\nProcessLOBDataMsg" );

	// PRI 레벨값 저장
	if( pLOBData->iPRIPositionCount >= _spTwo ) {
		InsertToDB_Position( pLOBData, pExt );
	}

	// LOB 데이터 저장
	InsertToDB_LOB( pLOBData, pExt, true );

 	++ m_nBInsertLOB;

}

/**
 * @brief     빔 데이터를 내부 저장소에 복사한다.
 * @param     SQMsg * pstMsg
 * @return    void
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-11-01, 오후 7:40 
 * @warning   
 */
void CELInsertDBMngr::ProcessABTDataMsg( SQMsg *pstMsg )
{
	SRxLOBData *pLOBData;
	SRxABTData *pABTData;
	SELABTDATA_EXT *pABTDataExt;

	TRACE( "\nProcessABTDataMsg" );

	pLOBData = & pstMsg->x.stABTDataExt.stLOBData;
	pABTData = & pstMsg->x.stABTDataExt.stABTData;
	pABTDataExt = & pstMsg->x.stABTDataExt.stABTDataExt;

	// PRI 레벨값 저장
	if( pABTData->iPRIPositionCount != 0 ) {
		InsertToDB_Position( pLOBData, pABTData, pABTDataExt );
	}

	InsertToDB_ABT( pABTData, pABTDataExt, true );

}

/**
 * @brief     방사체 데이터를 내부 저장소에 복사한다.
 * @param     SQMsg * pstMsg
 * @return    void
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-11-01, 오후 7:40 
 * @warning   
 */
void CELInsertDBMngr::ProcessEmitterDataMsg( SQMsg *pstMsg )
{
// 	int nSize=0;
// 	SRxLOBData *pSRxLOBData;
// 	SELAETDATA *pSELAETDATA;
// 	SELAETDATA_EXT *pSELAETDATA_EXT;
// 	SELEXTDB *pSELEXTDB;
// 
// 	pSRxLOBData = ( SRxLOBData * ) & pstMsg->buf[nSize];
// 	nSize += sizeof(SRxLOBData);
// 	pSELAETDATA = ( SELAETDATA * ) & pstMsg->buf[nSize];
// 	nSize += sizeof(SELAETDATA);
// 	pSELAETDATA_EXT = ( SELAETDATA_EXT * ) & pstMsg->buf[nSize];
// 	nSize += sizeof(SELAETDATA_EXT);
// 	pSELEXTDB = ( SELEXTDB * ) & pstMsg->buf[nSize];
// 
// 	_CALL_MEM_DB( InsertToDB_AET( pSRxLOBData, pSELAETDATA, pSELAETDATA_EXT, pSELEXTDB ) )
	//TRACE( "\n*InsertDB_AET: #%d, A%d" , pSELEXTDB->uiSeqNum, pSELAETDATA->uiAETID );
}

/**
 * @brief     ProcessDisplayDataMsg
 * @param     SQMsg * pstMsg
 * @return    void
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-11-02, 오전 11:03 
 * @warning   
 */
void CELInsertDBMngr::ProcessDisplayDataMsg( SQMsg *pstMsg )
{
// 	bool bRtn;
// 	UINT uiOpcode = MakeOPCode(CMDCODE_EL_RX_LOBDATA, DEVICECODE_AEE, DEVICECODE_GMEO);
// 
// 	bRtn = CGRCommIF::GetInstance()->SendToPOSN( uiOpcode, pstMsg->usSize, pstMsg->usOperatorId, pstMsg->buf, pstMsg->bIsReplay );
// 	if( bRtn == false ) {
// 		LogPrint( "\n ProcessDisplayDataMsg SendToPOSN 에러 발생 !!!!!!!!![%d]", bRtn );
// 	}
}

/**
 * @brief     내부 쓰레드에 작업 큐가 비울때까지 대기한다. 횟수는 100 번 시도한다.
 * @param     void
 * @return    void
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-11-01, 오후 10:31 
 * @warning   
 */
bool CELInsertDBMngr::WaitUntilQueueEmpty()
{
	bool bRet=true;
	int nLoop=0;

#ifdef _THREAD_DB_
	//while( GetMsgQSize() != 0 && ( m_nArrayLOB != _spZero && m_nArrayABT != _spZero && m_nArrayAET != _spZero && m_nArrayABT_Position != _spZero && m_nArrayLOB_Position != _spZero ) ) {
	while( GetMsgQSize() != 0 || ( m_nBInsertLOB != m_nWInsertLOB ) ) {
		Sleep( 20 );

		if( nLoop > WAIT_QUEUE ) {
			break;
		}

		++ nLoop;
	}

	if( nLoop < WAIT_QUEUE ) {
		m_nBInsertLOB = 0;
		m_nWInsertLOB = 0;
	}
#endif

	// 대기 시간에 Over 된 경우에 아래 메시지를 출력한다.
	if( nLoop > WAIT_QUEUE ) {
// 		UINT nQueueSize=GetMsgQSize();
// 		if( nQueueSize != 0 ) {
// 			//GP_MGR_LOG.ELSetCommonSysLog( E_TYPE_MSG, E_WARNING_MAJOR, enumGMEO_DEVICE, enumGMEI_DEVICE, "Insert DB에 아직 기록을 못했습니다. 큐 사이즈[%d]를 비우지 못했습니다." , nQueueSize );
// 			bRet = false;
// 		}
	}

	return bRet;

}

/**
 * @brief     큐 메시지 크기를 체크한다.
 * @param     void
 * @return    void
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-11-02, 오전 11:04 
 * @warning   
 */
// void CELInsertDBMngr::CheckQueueMsg()
// {
// 	UINT qSize;
// 
// 	qSize = GetMsgQSize();
// 	if( qSize > MAX_QUEUE_SIZE_OF_INSERTDBMNGR_ ) {
// 		m_bDangerOfQueueBufferFull = true;
// 		GP_MGR_LOG.ELSetCommonSysLog( E_TYPE_MSG, E_WARNING_MAJOR, enumGMEO_DEVICE, enumGMEI_DEVICE, "CELInsertDBMngr에서 큐 사이즈[%d] 를 초과하고 있습니다." , qSize );
// 	}
// 	else {
// 		m_bDangerOfQueueBufferFull = false;
// 	}
// 
// }

/**
 * @brief     LOBID를 업데이트 한다.
 * @param     void
 * @return    void
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-09-24, 오후 7:53 
 * @warning   
 */
// void CELInsertDBMngr::UpdateLOBID( SRxLOBDataGroup *pSRxLOBDataGroup )
// {
// 	if( pSRxLOBDataGroup->uiLOBID == 0 ) {
// 		pSRxLOBDataGroup->uiLOBID = m_uiGndLOBId;
// 		//GP_MGR_LOG.ELSetCommonSysLog( E_TYPE_MSG, E_WARNING_NONE, enumGMEO_DEVICE, enumGMEI_DEVICE, "신규 LOB 추가로 LOB 번호[%d]를 생성 합니다." , m_uiGndLOBId );
// 
// 		++ m_uiGndLOBId;
// 	}
// 
// }

/**
 * @brief     GetListItemsOfLOB
 * @param     void
 * @return    int
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-09-25, 오전 11:45 
 * @warning   
 */
// int CELInsertDBMngr::GetListItemsOfLOB()
// {
// 	return GP_MGR_TEST_PARAM->GetListItemsOfLOB();
// }

/**
 * @brief     빔 엘리머트 정보를 내부 저장소에 저장한다.
 * @param     SRxLOBData * pHeader
 * @param     SELABTDATA * pData
 * @param     SELABTDATA_EXT * pExt
 * @param     SELEXTDB * pExtDB
 * @param     int iDataType
 * @return    bool
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2018-01-16, 오전 11:19 
 * @warning   
 */
// bool CELInsertDBMngr::InsertToDB_Position( SRxLOBData *pHeader, SELABTDATA *pData, SELABTDATA_EXT *pExt, SELEXTDB *pExtDB, int iDataType )
// {
// 	bool bRet=true;
// 	char szTaskID[LENGTH_OF_TASK_ID+10];
// 
// 	if( m_nArrayABT_Position < MAX_SIZE_OF_ARRAY_INSERT*4 ) {
// 		m_pArrayABT_Position->uiSeqNum[m_nArrayABT_Position] = pExtDB->uiSeqNum;
// 
// 		m_pArrayABT_Position->iLinkNum[m_nArrayABT_Position] = (UINT) pExtDB->iLinkNum;
// 		strcpy_s( m_pArrayABT_Position->szMissionID[m_nArrayABT_Position], (char *) pExtDB->acMissionID );
// 
// 		memset( szTaskID, 0, sizeof(szTaskID) );
// 		memcpy( szTaskID, (char *) pHeader->aucTaskID, LENGTH_OF_TASK_ID );
// 		strcpy_s( m_pArrayABT_Position->szTaskID[m_nArrayABT_Position], szTaskID );
// 		// strcpy_s( m_pArrayABT_Position->szTaskID[m_nArrayABT_Position], (char *) pHeader->aucTaskID );
// 		//m_pArrayABT_Position->szTaskID[m_nArrayABT_Position][LENGTH_OF_TASK_ID] = NULL;
// 
// 		m_pArrayABT_Position->uiLOBID[m_nArrayABT_Position] = 0;
// 		m_pArrayABT_Position->uiABTID[m_nArrayABT_Position] = pData->uiABTID;
// 		m_pArrayABT_Position->uiAETID[m_nArrayABT_Position] = pData->uiAETID;
// 
// 		m_pArrayABT_Position->iDataType[m_nArrayABT_Position] = (UINT) iDataType;
// 
// 		switch( iDataType ) {
// 		case E_EN_FREQ_DATA_ELEMENT_TYPE :
// 			m_pArrayABT_Position->iPositionCount[m_nArrayABT_Position] = (UINT) pData->freqDInfo.iPositionCount;
// 
// 			m_pArrayABT_Position->iSeq01[m_nArrayABT_Position] = pData->freqDInfo.iSeq[ 0];
// 			m_pArrayABT_Position->iSeq02[m_nArrayABT_Position] = pData->freqDInfo.iSeq[ 1];
// 			m_pArrayABT_Position->iSeq03[m_nArrayABT_Position] = pData->freqDInfo.iSeq[ 2];
// 			m_pArrayABT_Position->iSeq04[m_nArrayABT_Position] = pData->freqDInfo.iSeq[ 3];
// 			m_pArrayABT_Position->iSeq05[m_nArrayABT_Position] = pData->freqDInfo.iSeq[ 4];
// 			m_pArrayABT_Position->iSeq06[m_nArrayABT_Position] = pData->freqDInfo.iSeq[ 5];
// 			m_pArrayABT_Position->iSeq07[m_nArrayABT_Position] = pData->freqDInfo.iSeq[ 6];
// 			m_pArrayABT_Position->iSeq08[m_nArrayABT_Position] = pData->freqDInfo.iSeq[ 7];
// 			m_pArrayABT_Position->iSeq09[m_nArrayABT_Position] = pData->freqDInfo.iSeq[ 8];
// 			m_pArrayABT_Position->iSeq10[m_nArrayABT_Position] = pData->freqDInfo.iSeq[ 9];
// 			m_pArrayABT_Position->iSeq11[m_nArrayABT_Position] = pData->freqDInfo.iSeq[10];
// 			m_pArrayABT_Position->iSeq12[m_nArrayABT_Position] = pData->freqDInfo.iSeq[11];
// 			m_pArrayABT_Position->iSeq13[m_nArrayABT_Position] = pData->freqDInfo.iSeq[12];
// 			m_pArrayABT_Position->iSeq14[m_nArrayABT_Position] = pData->freqDInfo.iSeq[13];
// 			m_pArrayABT_Position->iSeq15[m_nArrayABT_Position] = pData->freqDInfo.iSeq[14];
// 			m_pArrayABT_Position->iSeq16[m_nArrayABT_Position] = pData->freqDInfo.iSeq[15];
// 			m_pArrayABT_Position->iSeq17[m_nArrayABT_Position] = pData->freqDInfo.iSeq[16];
// 			m_pArrayABT_Position->iSeq18[m_nArrayABT_Position] = pData->freqDInfo.iSeq[17];
// 			m_pArrayABT_Position->iSeq19[m_nArrayABT_Position] = pData->freqDInfo.iSeq[18];
// 			m_pArrayABT_Position->iSeq20[m_nArrayABT_Position] = pData->freqDInfo.iSeq[19];
// 			m_pArrayABT_Position->iSeq21[m_nArrayABT_Position] = pData->freqDInfo.iSeq[20];
// 			m_pArrayABT_Position->iSeq22[m_nArrayABT_Position] = pData->freqDInfo.iSeq[21];
// 			m_pArrayABT_Position->iSeq23[m_nArrayABT_Position] = pData->freqDInfo.iSeq[22];
// 			m_pArrayABT_Position->iSeq24[m_nArrayABT_Position] = pData->freqDInfo.iSeq[23];
// 			m_pArrayABT_Position->iSeq25[m_nArrayABT_Position] = pData->freqDInfo.iSeq[24];
// 			m_pArrayABT_Position->iSeq26[m_nArrayABT_Position] = pData->freqDInfo.iSeq[25];
// 			m_pArrayABT_Position->iSeq27[m_nArrayABT_Position] = pData->freqDInfo.iSeq[26];
// 			m_pArrayABT_Position->iSeq28[m_nArrayABT_Position] = pData->freqDInfo.iSeq[27];
// 			m_pArrayABT_Position->iSeq29[m_nArrayABT_Position] = pData->freqDInfo.iSeq[28];
// 			m_pArrayABT_Position->iSeq30[m_nArrayABT_Position] = pData->freqDInfo.iSeq[29];
// 			m_pArrayABT_Position->iSeq31[m_nArrayABT_Position] = pData->freqDInfo.iSeq[30];
// 			m_pArrayABT_Position->iSeq32[m_nArrayABT_Position] = pData->freqDInfo.iSeq[31];
// 			m_pArrayABT_Position->iSeq33[m_nArrayABT_Position] = pData->freqDInfo.iSeq[32];
// 			m_pArrayABT_Position->iSeq34[m_nArrayABT_Position] = pData->freqDInfo.iSeq[33];
// 			m_pArrayABT_Position->iSeq35[m_nArrayABT_Position] = pData->freqDInfo.iSeq[34];
// 			m_pArrayABT_Position->iSeq36[m_nArrayABT_Position] = pData->freqDInfo.iSeq[35];
// 			m_pArrayABT_Position->iSeq37[m_nArrayABT_Position] = pData->freqDInfo.iSeq[36];
// 			m_pArrayABT_Position->iSeq38[m_nArrayABT_Position] = pData->freqDInfo.iSeq[37];
// 			m_pArrayABT_Position->iSeq39[m_nArrayABT_Position] = pData->freqDInfo.iSeq[38];
// 			m_pArrayABT_Position->iSeq40[m_nArrayABT_Position] = pData->freqDInfo.iSeq[39];
// 			m_pArrayABT_Position->iSeq41[m_nArrayABT_Position] = pData->freqDInfo.iSeq[40];
// 			m_pArrayABT_Position->iSeq42[m_nArrayABT_Position] = pData->freqDInfo.iSeq[41];
// 			m_pArrayABT_Position->iSeq43[m_nArrayABT_Position] = pData->freqDInfo.iSeq[42];
// 			m_pArrayABT_Position->iSeq44[m_nArrayABT_Position] = pData->freqDInfo.iSeq[43];
// 			m_pArrayABT_Position->iSeq45[m_nArrayABT_Position] = pData->freqDInfo.iSeq[44];
// 			m_pArrayABT_Position->iSeq46[m_nArrayABT_Position] = pData->freqDInfo.iSeq[45];
// 			m_pArrayABT_Position->iSeq47[m_nArrayABT_Position] = pData->freqDInfo.iSeq[46];
// 			m_pArrayABT_Position->iSeq48[m_nArrayABT_Position] = pData->freqDInfo.iSeq[47];
// 			m_pArrayABT_Position->iSeq49[m_nArrayABT_Position] = pData->freqDInfo.iSeq[48];
// 			m_pArrayABT_Position->iSeq50[m_nArrayABT_Position] = pData->freqDInfo.iSeq[49];
// 			m_pArrayABT_Position->iSeq51[m_nArrayABT_Position] = pData->freqDInfo.iSeq[50];
// 			m_pArrayABT_Position->iSeq52[m_nArrayABT_Position] = pData->freqDInfo.iSeq[51];
// 			m_pArrayABT_Position->iSeq53[m_nArrayABT_Position] = pData->freqDInfo.iSeq[52];
// 			m_pArrayABT_Position->iSeq54[m_nArrayABT_Position] = pData->freqDInfo.iSeq[53];
// 			m_pArrayABT_Position->iSeq55[m_nArrayABT_Position] = pData->freqDInfo.iSeq[54];
// 			m_pArrayABT_Position->iSeq56[m_nArrayABT_Position] = pData->freqDInfo.iSeq[55];
// 			m_pArrayABT_Position->iSeq57[m_nArrayABT_Position] = pData->freqDInfo.iSeq[56];
// 			m_pArrayABT_Position->iSeq58[m_nArrayABT_Position] = pData->freqDInfo.iSeq[57];
// 			m_pArrayABT_Position->iSeq59[m_nArrayABT_Position] = pData->freqDInfo.iSeq[58];
// 			m_pArrayABT_Position->iSeq60[m_nArrayABT_Position] = pData->freqDInfo.iSeq[59];
// 			m_pArrayABT_Position->iSeq61[m_nArrayABT_Position] = pData->freqDInfo.iSeq[60];
// 			m_pArrayABT_Position->iSeq62[m_nArrayABT_Position] = pData->freqDInfo.iSeq[61];
// 			m_pArrayABT_Position->iSeq63[m_nArrayABT_Position] = pData->freqDInfo.iSeq[62];
// 			m_pArrayABT_Position->iSeq64[m_nArrayABT_Position] = pData->freqDInfo.iSeq[63];
// 
// 			++ m_nArrayABT_Position;
// 			break;
// 
// 		case E_EN_PRI_DATA_ELEMENT_TYPE :
// 			m_pArrayABT_Position->iPositionCount[m_nArrayABT_Position] = (UINT) pData->priDInfo.iPositionCount;
// 
// 			m_pArrayABT_Position->iSeq01[m_nArrayABT_Position] = pData->priDInfo.iSeq[ 0];
// 			m_pArrayABT_Position->iSeq02[m_nArrayABT_Position] = pData->priDInfo.iSeq[ 1];
// 			m_pArrayABT_Position->iSeq03[m_nArrayABT_Position] = pData->priDInfo.iSeq[ 2];
// 			m_pArrayABT_Position->iSeq04[m_nArrayABT_Position] = pData->priDInfo.iSeq[ 3];
// 			m_pArrayABT_Position->iSeq05[m_nArrayABT_Position] = pData->priDInfo.iSeq[ 4];
// 			m_pArrayABT_Position->iSeq06[m_nArrayABT_Position] = pData->priDInfo.iSeq[ 5];
// 			m_pArrayABT_Position->iSeq07[m_nArrayABT_Position] = pData->priDInfo.iSeq[ 6];
// 			m_pArrayABT_Position->iSeq08[m_nArrayABT_Position] = pData->priDInfo.iSeq[ 7];
// 			m_pArrayABT_Position->iSeq09[m_nArrayABT_Position] = pData->priDInfo.iSeq[ 8];
// 			m_pArrayABT_Position->iSeq10[m_nArrayABT_Position] = pData->priDInfo.iSeq[ 9];
// 			m_pArrayABT_Position->iSeq11[m_nArrayABT_Position] = pData->priDInfo.iSeq[10];
// 			m_pArrayABT_Position->iSeq12[m_nArrayABT_Position] = pData->priDInfo.iSeq[11];
// 			m_pArrayABT_Position->iSeq13[m_nArrayABT_Position] = pData->priDInfo.iSeq[12];
// 			m_pArrayABT_Position->iSeq14[m_nArrayABT_Position] = pData->priDInfo.iSeq[13];
// 			m_pArrayABT_Position->iSeq15[m_nArrayABT_Position] = pData->priDInfo.iSeq[14];
// 			m_pArrayABT_Position->iSeq16[m_nArrayABT_Position] = pData->priDInfo.iSeq[15];
// 			m_pArrayABT_Position->iSeq17[m_nArrayABT_Position] = pData->priDInfo.iSeq[16];
// 			m_pArrayABT_Position->iSeq18[m_nArrayABT_Position] = pData->priDInfo.iSeq[17];
// 			m_pArrayABT_Position->iSeq19[m_nArrayABT_Position] = pData->priDInfo.iSeq[18];
// 			m_pArrayABT_Position->iSeq20[m_nArrayABT_Position] = pData->priDInfo.iSeq[19];
// 			m_pArrayABT_Position->iSeq21[m_nArrayABT_Position] = pData->priDInfo.iSeq[20];
// 			m_pArrayABT_Position->iSeq22[m_nArrayABT_Position] = pData->priDInfo.iSeq[21];
// 			m_pArrayABT_Position->iSeq23[m_nArrayABT_Position] = pData->priDInfo.iSeq[22];
// 			m_pArrayABT_Position->iSeq24[m_nArrayABT_Position] = pData->priDInfo.iSeq[23];
// 			m_pArrayABT_Position->iSeq25[m_nArrayABT_Position] = pData->priDInfo.iSeq[24];
// 			m_pArrayABT_Position->iSeq26[m_nArrayABT_Position] = pData->priDInfo.iSeq[25];
// 			m_pArrayABT_Position->iSeq27[m_nArrayABT_Position] = pData->priDInfo.iSeq[26];
// 			m_pArrayABT_Position->iSeq28[m_nArrayABT_Position] = pData->priDInfo.iSeq[27];
// 			m_pArrayABT_Position->iSeq29[m_nArrayABT_Position] = pData->priDInfo.iSeq[28];
// 			m_pArrayABT_Position->iSeq30[m_nArrayABT_Position] = pData->priDInfo.iSeq[29];
// 			m_pArrayABT_Position->iSeq31[m_nArrayABT_Position] = pData->priDInfo.iSeq[30];
// 			m_pArrayABT_Position->iSeq32[m_nArrayABT_Position] = pData->priDInfo.iSeq[31];
// 			m_pArrayABT_Position->iSeq33[m_nArrayABT_Position] = pData->priDInfo.iSeq[32];
// 			m_pArrayABT_Position->iSeq34[m_nArrayABT_Position] = pData->priDInfo.iSeq[33];
// 			m_pArrayABT_Position->iSeq35[m_nArrayABT_Position] = pData->priDInfo.iSeq[34];
// 			m_pArrayABT_Position->iSeq36[m_nArrayABT_Position] = pData->priDInfo.iSeq[35];
// 			m_pArrayABT_Position->iSeq37[m_nArrayABT_Position] = pData->priDInfo.iSeq[36];
// 			m_pArrayABT_Position->iSeq38[m_nArrayABT_Position] = pData->priDInfo.iSeq[37];
// 			m_pArrayABT_Position->iSeq39[m_nArrayABT_Position] = pData->priDInfo.iSeq[38];
// 			m_pArrayABT_Position->iSeq40[m_nArrayABT_Position] = pData->priDInfo.iSeq[39];
// 			m_pArrayABT_Position->iSeq41[m_nArrayABT_Position] = pData->priDInfo.iSeq[40];
// 			m_pArrayABT_Position->iSeq42[m_nArrayABT_Position] = pData->priDInfo.iSeq[41];
// 			m_pArrayABT_Position->iSeq43[m_nArrayABT_Position] = pData->priDInfo.iSeq[42];
// 			m_pArrayABT_Position->iSeq44[m_nArrayABT_Position] = pData->priDInfo.iSeq[43];
// 			m_pArrayABT_Position->iSeq45[m_nArrayABT_Position] = pData->priDInfo.iSeq[44];
// 			m_pArrayABT_Position->iSeq46[m_nArrayABT_Position] = pData->priDInfo.iSeq[45];
// 			m_pArrayABT_Position->iSeq47[m_nArrayABT_Position] = pData->priDInfo.iSeq[46];
// 			m_pArrayABT_Position->iSeq48[m_nArrayABT_Position] = pData->priDInfo.iSeq[47];
// 			m_pArrayABT_Position->iSeq49[m_nArrayABT_Position] = pData->priDInfo.iSeq[48];
// 			m_pArrayABT_Position->iSeq50[m_nArrayABT_Position] = pData->priDInfo.iSeq[49];
// 			m_pArrayABT_Position->iSeq51[m_nArrayABT_Position] = pData->priDInfo.iSeq[50];
// 			m_pArrayABT_Position->iSeq52[m_nArrayABT_Position] = pData->priDInfo.iSeq[51];
// 			m_pArrayABT_Position->iSeq53[m_nArrayABT_Position] = pData->priDInfo.iSeq[52];
// 			m_pArrayABT_Position->iSeq54[m_nArrayABT_Position] = pData->priDInfo.iSeq[53];
// 			m_pArrayABT_Position->iSeq55[m_nArrayABT_Position] = pData->priDInfo.iSeq[54];
// 			m_pArrayABT_Position->iSeq56[m_nArrayABT_Position] = pData->priDInfo.iSeq[55];
// 			m_pArrayABT_Position->iSeq57[m_nArrayABT_Position] = pData->priDInfo.iSeq[56];
// 			m_pArrayABT_Position->iSeq58[m_nArrayABT_Position] = pData->priDInfo.iSeq[57];
// 			m_pArrayABT_Position->iSeq59[m_nArrayABT_Position] = pData->priDInfo.iSeq[58];
// 			m_pArrayABT_Position->iSeq60[m_nArrayABT_Position] = pData->priDInfo.iSeq[59];
// 			m_pArrayABT_Position->iSeq61[m_nArrayABT_Position] = pData->priDInfo.iSeq[60];
// 			m_pArrayABT_Position->iSeq62[m_nArrayABT_Position] = pData->priDInfo.iSeq[61];
// 			m_pArrayABT_Position->iSeq63[m_nArrayABT_Position] = pData->priDInfo.iSeq[62];
// 			m_pArrayABT_Position->iSeq64[m_nArrayABT_Position] = pData->priDInfo.iSeq[63];
// 
// 			++ m_nArrayABT_Position;
// 			break;
// 
// 		case E_EN_PPG_PRIDIFF_ELEMENT_TYPE :
// 			m_pArrayABT_Position->iPositionCount[m_nArrayABT_Position] = (UINT) pData->pulseDInfo.iPulsePerGrp;
// 
// 			m_pArrayABT_Position->iSeq01[m_nArrayABT_Position] = pData->pulseDInfo.iPRIPGSeq[ 0];
// 			m_pArrayABT_Position->iSeq02[m_nArrayABT_Position] = pData->pulseDInfo.iPRIPGSeq[ 1];
// 			m_pArrayABT_Position->iSeq03[m_nArrayABT_Position] = pData->pulseDInfo.iPRIPGSeq[ 2];
// 			m_pArrayABT_Position->iSeq04[m_nArrayABT_Position] = pData->pulseDInfo.iPRIPGSeq[ 3];
// 			m_pArrayABT_Position->iSeq05[m_nArrayABT_Position] = pData->pulseDInfo.iPRIPGSeq[ 4];
// 			m_pArrayABT_Position->iSeq06[m_nArrayABT_Position] = pData->pulseDInfo.iPRIPGSeq[ 5];
// 			m_pArrayABT_Position->iSeq07[m_nArrayABT_Position] = pData->pulseDInfo.iPRIPGSeq[ 6];
// 			m_pArrayABT_Position->iSeq08[m_nArrayABT_Position] = pData->pulseDInfo.iPRIPGSeq[ 7];
// 			m_pArrayABT_Position->iSeq09[m_nArrayABT_Position] = pData->pulseDInfo.iPRIPGSeq[ 8];
// 			m_pArrayABT_Position->iSeq10[m_nArrayABT_Position] = pData->pulseDInfo.iPRIPGSeq[ 9];
// 			m_pArrayABT_Position->iSeq11[m_nArrayABT_Position] = pData->pulseDInfo.iPRIPGSeq[10];
// 			m_pArrayABT_Position->iSeq12[m_nArrayABT_Position] = pData->pulseDInfo.iPRIPGSeq[11];
// 			m_pArrayABT_Position->iSeq13[m_nArrayABT_Position] = pData->pulseDInfo.iPRIPGSeq[12];
// 			m_pArrayABT_Position->iSeq14[m_nArrayABT_Position] = pData->pulseDInfo.iPRIPGSeq[13];
// 			m_pArrayABT_Position->iSeq15[m_nArrayABT_Position] = pData->pulseDInfo.iPRIPGSeq[14];
// 			m_pArrayABT_Position->iSeq16[m_nArrayABT_Position] = pData->pulseDInfo.iPRIPGSeq[15];
// 			m_pArrayABT_Position->iSeq17[m_nArrayABT_Position] = pData->pulseDInfo.iPRIPGSeq[16];
// 			m_pArrayABT_Position->iSeq18[m_nArrayABT_Position] = pData->pulseDInfo.iPRIPGSeq[17];
// 			m_pArrayABT_Position->iSeq19[m_nArrayABT_Position] = pData->pulseDInfo.iPRIPGSeq[18];
// 			m_pArrayABT_Position->iSeq20[m_nArrayABT_Position] = pData->pulseDInfo.iPRIPGSeq[19];
// 			m_pArrayABT_Position->iSeq21[m_nArrayABT_Position] = pData->pulseDInfo.iPRIPGSeq[20];
// 			m_pArrayABT_Position->iSeq22[m_nArrayABT_Position] = pData->pulseDInfo.iPRIPGSeq[21];
// 			m_pArrayABT_Position->iSeq23[m_nArrayABT_Position] = pData->pulseDInfo.iPRIPGSeq[22];
// 			m_pArrayABT_Position->iSeq24[m_nArrayABT_Position] = pData->pulseDInfo.iPRIPGSeq[23];
// 			m_pArrayABT_Position->iSeq25[m_nArrayABT_Position] = pData->pulseDInfo.iPRIPGSeq[24];
// 			m_pArrayABT_Position->iSeq26[m_nArrayABT_Position] = pData->pulseDInfo.iPRIPGSeq[25];
// 			m_pArrayABT_Position->iSeq27[m_nArrayABT_Position] = pData->pulseDInfo.iPRIPGSeq[26];
// 			m_pArrayABT_Position->iSeq28[m_nArrayABT_Position] = pData->pulseDInfo.iPRIPGSeq[27];
// 			m_pArrayABT_Position->iSeq29[m_nArrayABT_Position] = pData->pulseDInfo.iPRIPGSeq[28];
// 			m_pArrayABT_Position->iSeq30[m_nArrayABT_Position] = pData->pulseDInfo.iPRIPGSeq[29];
// 			m_pArrayABT_Position->iSeq31[m_nArrayABT_Position] = pData->pulseDInfo.iPRIPGSeq[30];
// 			m_pArrayABT_Position->iSeq32[m_nArrayABT_Position] = pData->pulseDInfo.iPRIPGSeq[31];
// 
// 			++ m_nArrayABT_Position;
// 			break;
// 
// 		case E_EN_PPG_PADIFF_DATA_ELEMENT_TYPE :
// 			m_pArrayABT_Position->iPositionCount[m_nArrayABT_Position] = (UINT) pData->pulseDInfo.iPulsePerGrp;
// 
// 			m_pArrayABT_Position->iSeq01[m_nArrayABT_Position] = pData->pulseDInfo.iPAPGSeq[ 0];
// 			m_pArrayABT_Position->iSeq02[m_nArrayABT_Position] = pData->pulseDInfo.iPAPGSeq[ 1];
// 			m_pArrayABT_Position->iSeq03[m_nArrayABT_Position] = pData->pulseDInfo.iPAPGSeq[ 2];
// 			m_pArrayABT_Position->iSeq04[m_nArrayABT_Position] = pData->pulseDInfo.iPAPGSeq[ 3];
// 			m_pArrayABT_Position->iSeq05[m_nArrayABT_Position] = pData->pulseDInfo.iPAPGSeq[ 4];
// 			m_pArrayABT_Position->iSeq06[m_nArrayABT_Position] = pData->pulseDInfo.iPAPGSeq[ 5];
// 			m_pArrayABT_Position->iSeq07[m_nArrayABT_Position] = pData->pulseDInfo.iPAPGSeq[ 6];
// 			m_pArrayABT_Position->iSeq08[m_nArrayABT_Position] = pData->pulseDInfo.iPAPGSeq[ 7];
// 			m_pArrayABT_Position->iSeq09[m_nArrayABT_Position] = pData->pulseDInfo.iPAPGSeq[ 8];
// 			m_pArrayABT_Position->iSeq10[m_nArrayABT_Position] = pData->pulseDInfo.iPAPGSeq[ 9];
// 			m_pArrayABT_Position->iSeq11[m_nArrayABT_Position] = pData->pulseDInfo.iPAPGSeq[10];
// 			m_pArrayABT_Position->iSeq12[m_nArrayABT_Position] = pData->pulseDInfo.iPAPGSeq[11];
// 			m_pArrayABT_Position->iSeq13[m_nArrayABT_Position] = pData->pulseDInfo.iPAPGSeq[12];
// 			m_pArrayABT_Position->iSeq14[m_nArrayABT_Position] = pData->pulseDInfo.iPAPGSeq[13];
// 			m_pArrayABT_Position->iSeq15[m_nArrayABT_Position] = pData->pulseDInfo.iPAPGSeq[14];
// 			m_pArrayABT_Position->iSeq16[m_nArrayABT_Position] = pData->pulseDInfo.iPAPGSeq[15];
// 			m_pArrayABT_Position->iSeq17[m_nArrayABT_Position] = pData->pulseDInfo.iPAPGSeq[16];
// 			m_pArrayABT_Position->iSeq18[m_nArrayABT_Position] = pData->pulseDInfo.iPAPGSeq[17];
// 			m_pArrayABT_Position->iSeq19[m_nArrayABT_Position] = pData->pulseDInfo.iPAPGSeq[18];
// 			m_pArrayABT_Position->iSeq20[m_nArrayABT_Position] = pData->pulseDInfo.iPAPGSeq[19];
// 			m_pArrayABT_Position->iSeq21[m_nArrayABT_Position] = pData->pulseDInfo.iPAPGSeq[20];
// 			m_pArrayABT_Position->iSeq22[m_nArrayABT_Position] = pData->pulseDInfo.iPAPGSeq[21];
// 			m_pArrayABT_Position->iSeq23[m_nArrayABT_Position] = pData->pulseDInfo.iPAPGSeq[22];
// 			m_pArrayABT_Position->iSeq24[m_nArrayABT_Position] = pData->pulseDInfo.iPAPGSeq[23];
// 			m_pArrayABT_Position->iSeq25[m_nArrayABT_Position] = pData->pulseDInfo.iPAPGSeq[24];
// 			m_pArrayABT_Position->iSeq26[m_nArrayABT_Position] = pData->pulseDInfo.iPAPGSeq[25];
// 			m_pArrayABT_Position->iSeq27[m_nArrayABT_Position] = pData->pulseDInfo.iPAPGSeq[26];
// 			m_pArrayABT_Position->iSeq28[m_nArrayABT_Position] = pData->pulseDInfo.iPAPGSeq[27];
// 			m_pArrayABT_Position->iSeq29[m_nArrayABT_Position] = pData->pulseDInfo.iPAPGSeq[28];
// 			m_pArrayABT_Position->iSeq30[m_nArrayABT_Position] = pData->pulseDInfo.iPAPGSeq[29];
// 			m_pArrayABT_Position->iSeq31[m_nArrayABT_Position] = pData->pulseDInfo.iPAPGSeq[30];
// 			m_pArrayABT_Position->iSeq32[m_nArrayABT_Position] = pData->pulseDInfo.iPAPGSeq[31];
// 
// 			++ m_nArrayABT_Position;
// 			break;
// 
// 		default:
// 			{//DTEC_Else
// 			}
// 			break;
// 		}
// 	}
// 	else {
// 		GP_MGR_LOG.ELSetCommonSysLog( E_TYPE_MSG, E_WARNING_CRITICAL, enumGMEO_DEVICE, enumGMEI_DEVICE, "빔 엘리먼트 ARRAY 버퍼 개수가 초과 됐숩니다. ARRAY 버퍼 개수를 늘려야 합니다." );
// 	}
// 
// 	return bRet;
// }

/**
 * @brief     방사체 각 구조체에 있는 데이터를 내부 저장소에 기록한다.
 * @param     SRxLOBData * pHeader
 * @param     SELAETDATA * pData
 * @param     SELAETDATA_EXT * pExt
 * @param     SELEXTDB * pExtDB
 * @return    bool
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2018-01-16, 오후 12:02 
 * @warning   
 */
// bool CELInsertDBMngr::InsertToDB_AET( SRxLOBData *pHeader, SELAETDATA *pData, SELAETDATA_EXT *pExt, SELEXTDB *pExtDB )
// {
// 	bool bRet=true;

// 	if( m_nArrayAET < MAX_SIZE_OF_ARRAY_INSERT ) {
// 		m_pArrayAET->uiSeqNum[m_nArrayAET] = pExtDB->uiSeqNum;
// 
// 		strcpy_s( m_pArrayAET->acMissionID[m_nArrayAET], pExtDB->acMissionID );
// 		strcpy_s( m_pArrayAET->acMissionName[m_nArrayAET], pExtDB->acMissionName );
// 
// 		if( pExtDB->uiAETID == 0 ) {
// 			m_pArrayAET->uiAETID[m_nArrayAET] = pData->uiAETID;
// 		}
// 		else {
// 			m_pArrayAET->uiAETID[m_nArrayAET] = pData->uiAETID;
// 		}
// 
// 		m_pArrayAET->iTaskType[m_nArrayAET] = pExt->iTaskType;
// 
// 		m_pArrayAET->iRadarModeIndex[m_nArrayAET] = pExtDB->iRadarModeIndex;
// 		m_pArrayAET->iThreatIndex[m_nArrayAET] = pExtDB->iThreatIndex;
// 
// 		strcpy_s( m_pArrayAET->szIdInfo[m_nArrayAET], pExtDB->szIdInfo );
// 		strcpy_s( m_pArrayAET->szPrimaryELNOT[m_nArrayAET], pExtDB->szPrimaryELNOT );
// 		strcpy_s( m_pArrayAET->szPrimaryModeCode[m_nArrayAET], pExtDB->szPrimaryModeCode );
// 		strcpy_s( m_pArrayAET->szNickName[m_nArrayAET], pExtDB->szNickName );
// 		strcpy_s( m_pArrayAET->szFunctioncode[m_nArrayAET], pExtDB->szFunctioncode );
// 		m_pArrayAET->iRadarPriority[m_nArrayAET] = pExtDB->iRadarPriority;
// 		m_pArrayAET->iPinNumber[m_nArrayAET] = pExtDB->iPinNumber;
// 
// 		strcpy_s( m_pArrayAET->szKoreaSiteName[m_nArrayAET], pExtDB->szKoreaSiteName );
// 		strcpy_s( m_pArrayAET->szBENumber[m_nArrayAET], pExtDB->szBENumber );
// 		strcpy_s( m_pArrayAET->szThreatFunctionCode[m_nArrayAET], pExtDB->szThreatFunctionCode );
// 		m_pArrayAET->iThreatPriority[m_nArrayAET] = pExtDB->iThreatPriority;
// 		m_pArrayAET->iThreatDistance[m_nArrayAET] = pExtDB->iThreatDistance;
// 		m_pArrayAET->iEquipNumber[m_nArrayAET] = pExtDB->iEquipNumber;
// 
// 		m_pArrayAET->nCoLOB[m_nArrayAET] = pData->nCoLOB;
// 		m_pArrayAET->nCoABT[m_nArrayAET] = pData->nCoABT;
// 
// 		ELDecoder::MakeTimeString( m_pArrayAET->szFirstSeenTime[m_nArrayAET], (time_t) pData->firstSeenTime, pData->firstSeenMillisec );
// 		ELDecoder::MakeTimeString( m_pArrayAET->szLastSeenTime[m_nArrayAET], (time_t) pData->lastSeenTime, pData->lastSeenMillisec );
// 
// 		m_pArrayAET->bValidity[m_nArrayAET] = pData->bValidity;
// 
// 		m_pArrayAET->freqInfoMean[m_nArrayAET] = pData->freqInfo.iMean;
// 		m_pArrayAET->freqInfoMax[m_nArrayAET] = pData->freqInfo.iMax;
// 		m_pArrayAET->freqInfoMin[m_nArrayAET] = pData->freqInfo.iMin;
// 		m_pArrayAET->freqInfoDeviation[m_nArrayAET] = pData->freqInfo.iDeviation;
// 
// 		m_pArrayAET->priInfoMean[m_nArrayAET] = pData->priInfo.iMean;
// 		m_pArrayAET->priInfoMax[m_nArrayAET] = pData->priInfo.iMax;
// 		m_pArrayAET->priInfoMin[m_nArrayAET] = pData->priInfo.iMin;
// 		m_pArrayAET->priInfoDeviation[m_nArrayAET] = pData->priInfo.iDeviation;
// 
// 		m_pArrayAET->pwInfoMean[m_nArrayAET] = pData->pwInfo.iMean;
// 		m_pArrayAET->pwInfoMax[m_nArrayAET] = pData->pwInfo.iMax;
// 		m_pArrayAET->pwInfoMin[m_nArrayAET] = pData->pwInfo.iMin;
// 		m_pArrayAET->pwInfoDeviation[m_nArrayAET] = pData->pwInfo.iDeviation;
// 
// 		m_pArrayAET->paInfoMean[m_nArrayAET] = pData->paInfo.iMean;
// 		m_pArrayAET->paInfoMax[m_nArrayAET] = pData->paInfo.iMax;
// 		m_pArrayAET->paInfoMin[m_nArrayAET] = pData->paInfo.iMin;
// 		m_pArrayAET->paInfoDeviation[m_nArrayAET] = pData->paInfo.iDeviation;
// 
// 		m_pArrayAET->peInfoenValid[m_nArrayAET] = pData->peInfo.enValid;
// 		m_pArrayAET->peInfoenLatitude[m_nArrayAET] = pData->peInfo.iLatitude;
// 		m_pArrayAET->peInfoenLongitude[m_nArrayAET] = pData->peInfo.iLongitude;
// 		m_pArrayAET->peInfoenAltidude[m_nArrayAET] = pData->peInfo.iAltidude;
// 		m_pArrayAET->peInfoenCEP[m_nArrayAET] = pData->peInfo.iCEP;
// 		m_pArrayAET->peInfoenMajorAxis[m_nArrayAET] = pData->peInfo.iMajorAxis;
// 		m_pArrayAET->peInfoenMinorAxis[m_nArrayAET] = pData->peInfo.iMinorAxis;
// 		m_pArrayAET->peInfoenTheta[m_nArrayAET] = pData->peInfo.iTheta;
// 
// 		ELDecoder::MakeTimeString( m_pArrayAET->szFirstReportedTime[m_nArrayAET], (time_t) pData->firstReportedTime, 0 );
// 		ELDecoder::MakeTimeString( m_pArrayAET->szFinalReportedTime[m_nArrayAET], (time_t) pData->finalReportedTime, 0 );
// 		ELDecoder::MakeTimeString( m_pArrayAET->szFinalAlarmTime[m_nArrayAET], (time_t) pData->finalAlarmTime, 0 );
// 
// 		m_pArrayAET->iIsManualEdited[m_nArrayAET] = pExtDB->bIsManualEdited;
// 		m_pArrayAET->iLinkNum[m_nArrayAET] = pExtDB->iLinkNum;
// 		m_pArrayAET->iManualPosEstPreferred[m_nArrayAET] = pExt->bManualPosEstPreferred;
// 		m_pArrayAET->peInfoManualLatitude[m_nArrayAET] = pData->peInfo.iManualLatitude;
// 		m_pArrayAET->peInfoManualLongitude[m_nArrayAET] = pData->peInfo.iManualLongitude;
// 
// 		m_pArrayAET->enBeamEmitterStat[m_nArrayAET] = pExt->enBeamEmitterStat;
// 		
// 		++ m_nArrayAET;
// 	}
// 	else {
// 		GP_MGR_LOG.ELSetCommonSysLog( E_TYPE_MSG, E_WARNING_CRITICAL, enumGMEO_DEVICE, enumGMEI_DEVICE, "방사체 ARRAY 버퍼 개수가 초과 됐숩니다. ARRAY 버퍼 개수를 늘려야 합니다." );
// 	}

// 	return bRet;
// }

/**
 * @brief     방사체/빔/LOB 데이터를 DB에 기록한다.
 * @param     void
 * @return    void
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2018-01-16, 오전 11:23 
 * @warning   
 */
void CELInsertDBMngr::ProcessInsertDBMsg( SQMsg *pstMsg )
{
	// 0. ABT 메모리 DB Insert 하게 함.
//  	if( m_nArrayLOB != 0 ) {
//  		_CALL_DB( InsertLOBArrDB( *m_pArrayLOB, m_nArrayLOB ) )
//  	}
//  
//  	if( m_nArrayLOB_Position != 0 ) {
//  		_CALL_DB( InsertLOBPositionArrDB( *m_pArrayLOB_Position, m_nArrayLOB_Position ) )
//  	}
// 
// 	// 1. ABT 메모리 DB Insert 하게 함.
// 	if( m_nArrayABT != 0 ) {
// 		_CALL_DB( InsertABTArrDB( *m_pArrayABT, m_nArrayABT ) )
// 	}
// 
// 	if( m_nArrayABT_Position != 0 ) {
// 		_CALL_DB( InsertABTPositionArrDB( *m_pArrayABT_Position, m_nArrayABT_Position ) )
// 	}
// 
// 	// 2. AET 메모리 DB Insert 하게 함.
//  	if( m_nArrayAET != 0 ) {
//  		_CALL_DB( InsertAETArrDB( *m_pArrayAET, m_nArrayAET ) )
//  	}
// 
// 	m_nWInsertLOB = m_nWInsertLOB + (UINT) m_nArrayLOB; 
// 
// 	// 3. AET/ABT 삭제 처리
// 	// 	if( m_nDeleteAETABT != 0 ) {
// 	// 		_CALL_DB( DeleteAETABTArrDB( m_ArrayDelAETABT, m_nDeleteAETABT ) );
// 	// 	}
// 	memset( m_pArrayLOB, 0, sizeof(SELArrLOB) );
// 	memset( m_pArrayABT, 0, sizeof(SELArrABT) );
// 	memset( m_pArrayAET, 0, sizeof(SELArrAET) );
// 
// 	m_nArrayLOB = _spZero;
// 	m_nArrayLOB_Position = _spZero;
// 
// 	m_nArrayABT = _spZero;
// 	m_nArrayABT_Position = _spZero;
// 
// 	m_nArrayAET = _spZero;

	//m_nDeleteAETABT = _spZero;

}

