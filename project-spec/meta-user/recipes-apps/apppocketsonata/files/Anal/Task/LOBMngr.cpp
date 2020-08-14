// LOBMngr.cpp: implementation of the CLOBMngr class.
//
//////////////////////////////////////////////////////////////////////

// PC용 상위 클래스에 전달하기 위한 선언

#include "stdafx.h"

#ifdef _WIN32
#include <io.h>
#include <fcntl.h>

#else
#include <vxworks.h>

#include <ioLib.h>
#include <iv.h>
#include <intLib.h>
#include <sysLib.h>
#include <loglib.h>
#include <tftpLib.h>
#include <rebootLib.h>

#include "../../BootShell/ManSbc.h"

#endif


#include "../OFP_Main.h"

#include "LOBMngr.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLOBMngr::CLOBMngr( char *pTaskName )
{
	strcpy_s( m_taskName, pTaskName );

	//MallocBuffer();

	InitVar();
	//InitTask();

}

CLOBMngr::~CLOBMngr()
{
	delete m_pclsEmitterMergeMngr;
}

void CLOBMngr::InitVar()
{
	m_pclsEmitterMergeMngr = new CELEmitterMergeMngr( false );

}

/**
  * @brief		
  * @return 	void
*/
void CLOBMngr::Run()
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
/*! \brief    CLOBMngr::ParseMessage
		\author   조철희
		\return   BOOL
		\version  0.0.26
		\date     2008-05-27 11:53:11
		\warning
*/
BOOL CLOBMngr::ParseMessage( SQMsg *psqMsg )
{

	switch ( psqMsg->uiOpcode ) {
		case RX_LOBDATA:
			ProcessLOBDataMsg( psqMsg, false );
			break;

			// 위협 및 FETCH 삭제 처리 메시지
		case REQ_USERMSG:
// 			if( GP_MGR_TEST_PARAM->IsSimulatroMode() == false || true ) {
// 				ProcessLOBDataMsg(i_stMsg, true );
// 			}
			break;

		default :
			PrintErr(("\n [W] 잘못된 메시지[0x%x]를 수신했습니다.", psqMsg->uiOpcode));
			return FALSE;
	}
	
	return TRUE;
}

/**
  * @brief		
  * @param		SQMsg * psqMsg
  * @return 	void
*/
bool CLOBMngr::ProcessLOBDataMsg( SQMsg *psqMsg, bool bUserMsg )
{
	bool bRtn = true;

	SRxLOBHeader *pLOBHeader;
	SRxLOBData *pLOBData;

	pLOBHeader = ( SRxLOBHeader * ) psqMsg->x.buf;
	pLOBData = ( SRxLOBData * ) psqMsg->x.buf[sizeof(SRxLOBHeader)];

	int iNumOfLOB = pLOBHeader->iNumOfLOB;

	//PrintLOBData( & i_stMsg );

	// LOB 갯수 체크하여 강제 설정
	if( iNumOfLOB > MAX_LOB_ITEMS ) {
		pLOBHeader->iNumOfLOB = MAX_LOB_ITEMS;

		Printf( "[LOB] LOB 개수[%d]를 초과해서 수신했습니다.", iNumOfLOB );
	}

	if( ShouldProcAirMsg( psqMsg ) == true ) {
		ProcLOBMsgData( psqMsg, bUserMsg );
	}

	// DisplayLOBInfo( psqMsg,  (bUserMsg == false) && (m_bIsSimulator == false) && (m_bIsAirIndependentMode == false));

	return bRtn;
}

/**
  * @brief		
  * @param		SQMsg * psqMsg
  * @return 	bool
*/
bool CLOBMngr::ShouldProcAirMsg( SQMsg *psqMsg )
{
	return true;
}

/**
  * @brief		LOB 처리한다.
  * @param		SQMsg * psqMsg
  * @return 	void
*/
void CLOBMngr::ProcLOBMsgData( SQMsg *psqMsg, bool bUserMsg, bool bCheckDeleteThreat )
{
	bool bRtn = false; // , bProcMsgGrpEndian;

	//bool bIsMaster;

	DWORD dwTime;

	SRxLOBHeader *pstLOBHeader;
	SRxLOBData *pstLOBData; // , stLOBData;

	bool bIsResult = false;
	bool bIsFilteredLOB = false;

	pstLOBHeader = ( SRxLOBHeader * ) & psqMsg->x.buf[0];
	pstLOBData = ( SRxLOBData * ) & psqMsg->x.buf[sizeof(SRxLOBHeader)];

	// 삭제 처리 메시지가 아닐때 만 정상 위협 처리를 한다.
	if( bCheckDeleteThreat == false ) {
		if( pstLOBHeader->iNumOfLOB > _spZero ) {
			CheckQueueMsg();
		}

		for( int i=0 ; i < pstLOBHeader->iNumOfLOB ; ++i ) {
			dwTime = GetTickCount();

			// 3. LOB 필터 대상 여부 확인
			//bIsFilteredLOB = m_pclsLobFilterMngr->IsFilterOut(stLOBGrp, i_stMsg.nLinkNum);
			bIsFilteredLOB = false;

			// 4. 병합/식별/위치산출 처리. 필터링 대상이면 LOB정보만 DB에 저장하고 다른 처리는 하지 않는다.
			bIsResult = m_pclsEmitterMergeMngr->ManageThreat( pstLOBHeader, pstLOBData, bIsFilteredLOB );

			printf( "\n ***** ManageThreat 시간 : %d ms", (int)((GetTickCount() - dwTime) / 1));

		}

		dwTime = GetTickCount();

		{
			// 5. POSN 용 메시지 작성 및 전달
			//SendGMILobMsgToPos( & m_vecThreatInfo, & i_stMsg, m_bIsSimulator, i_stMsg.nLinkNum );

			// 6. 아래 DISPAY는 매번 표시하는 것 보다는 NEW/UPDATE/DELETE 등을 수행한 후 종합하여 중복 업데이트를 빼고 DISPLAY 하는 것이 좋을 듯함.
			//DisplayLOBInfo( & i_stMsg, m_bIsSimulator );
		}
	}
	else {
		// 8. 삭제 처리
 		// m_pclsEmitterMergeMngr->DeleteThreat( & m_vecThreatInfo, bIsMaster, i_stMsg.bIsReplay );
 
// 		if( m_vecThreatInfo.size() != (UINT)(0) ) {
// 			SendGMILobMsgToPos( & m_vecThreatInfo, & i_stMsg, m_bIsSimulator, _LINK1 );
// 			DisplayLOBInfo( & i_stMsg, m_bIsSimulator );
// 		}
	}

	return;
}

