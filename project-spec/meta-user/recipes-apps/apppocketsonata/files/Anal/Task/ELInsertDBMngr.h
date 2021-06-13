/**
 * @file      ELInsertDB.h
 * @brief     
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-03-08, 오후 8:35 
 * @warning   
 */


#pragma once

#ifdef _WIN32
#include "Task.h"
#else
#include "../../Utils/cthread.h"

#endif

#ifdef _SQLITE_
//#include "../../SQLite/SQLiteCpp.h"

#else
#include "../../ELINTOP/ODBC/mssql.h"
#include "../../ELINTOP/ODBC/odbccore.h"

#endif

// Insert DB 관련 정의
enum INSERT_DB_OPCODE { CMDCODE_INSERTDB_LOBDATA_=0x10,
												CMDCODE_INSERTDB_ABTDATA_,
												CMDCODE_INSERTDB_AETDATA_,

												CMDCODE_INSERTDB_FLUSH_,

												CMDCODE_INSERTDB_DISPLAY_ } ;

#define MAX_QUEUE_SIZE_OF_INSERTDBMNGR_				(100)

#define _INSERT_LOB_BY_PSS										(0x10)


/**
* [식별자 : CLS-GMU-EL-L-SAC]
*
* [추적성 : SRS-G-SAFR-005]
*
* @class	CELInsertDBMngr
* @brief	위협 관리 DB 관련 클래스
*
* (1) 클래스 설명
* - 본 클래스는 항공 또는 지상의 LOB 데이터로부터 방사체, 빔을 관리 및 식별한 최종 결과를 DB에 기록하기 위한 클래스이다.
*
* (2) 설계결정사항
* - 빔 병합, LOB 클러스터링을 처리한다.
*
* (3) 제한 및 예외처리
* - 해당사항 없음
*/
class CELInsertDBMngr : /* public CTask, */ public SQLite::Database
{
private:
	CELInsertDBMngr(char *pTaskName);
	virtual ~CELInsertDBMngr(void);
	
private:
	static CELInsertDBMngr* m_pInstance;
#ifdef _SQLITE_
#else
	CODBCDatabase m_theMyODBC;
#endif


private:
 	UINT m_nBInsertLOB;										///< 
 	UINT m_nWInsertLOB;										///<

private: 
 	int m_nArrayLOB;																		///< LOB 정보 개수
 	int m_nArrayLOB_Position;														///< LOB 엘리먼트 개수
 	int m_nArrayABT;																		///< 빔 정보 개수
 	int m_nArrayABT_Position;														///< 빔 엘리먼트 개수
 	int m_nArrayAET;																		///< 방사체 정보 개수
                                                                                                        ///< 방사체 세부 정보

public:
	static CELInsertDBMngr *GetUniqueInstance();
	static void ReleaseInstance();
	class Cleanup
	{
	public:
		~Cleanup();
	};

 	void InitFromExternalRequest( SQMsg& i_stMsg );
 	static CELInsertDBMngr* getInstance();
	inline void Timer() { }
	void Run();
	BOOL ParseMessage( SQMsg *psqMsg );
// 	void Receive(unsigned int i_uiOpcode, unsigned short i_usSize, unsigned short i_usOperatorID, void *i_pvData,  bool i_bServer = false, bool i_bReplay = false );	
// 	void UserReceive(unsigned int i_uiOpcode, unsigned short i_usSize, unsigned short i_usOperatorID, void *i_pvData,  bool i_bServer = false, bool i_bReplay = false, int nLink=0 );	
// 	void UserReceive( SQMsg *pstMsg );
// 	virtual BOOL Finalize() {
// 		ReleaseInstance();
// 		return TRUE;
// 	};
// 
 	// 쓰레드 제어
 	bool WaitUntilQueueEmpty();
 
 	void Init();

private:	
	// 사용자 관련 메시지 처리
 	void ProcThreatInitializeMsgData();
// 
// 	// LOB 관련 메시지 처리
 	void ProcessLOBDataMsg( SQMsg *pstMsg );
 	void ProcessABTDataMsg( SQMsg *pstMsg );
 	void ProcessEmitterDataMsg( SQMsg *pstMsg );
 	void ProcessDisplayDataMsg( SQMsg *pstMsg );
 	void ProcessInsertDBMsg( SQMsg *pstMsg );
 
// 	// 큐 관련 메시지
// 	void CheckQueueMsg();
// 
 	//bool InsertToDB_Position( SRxLOBData *pLOBData );
 	//bool InsertToDB_Position( SRxLOBData *pHeader, SELABTDATA *pData, SELABTDATA_EXT *pExt, SELEXTDB *pExtDB, int iDataType );
 	//bool InsertToDB_ABT( SRxLOBData *pLOBData );
// 	bool InsertToDB_AET( SRxLOBData *pHeader, SELAETDATA *pData, SELAETDATA_EXT *pExt, SELEXTDB *pExtDB );
 	//bool InsertToDB_LOB( SRxLOBData *pLOBHeader );

protected:
	//virtual void ProcessMsg(SQMsg& i_stMsg); // 재정의

public:
// 	void UpdateLOBID( SRxLOBDataGroup *pSRxLOBDataGroup );
// 
// 	int GetListItemsOfLOB();

};

#define GP_MGR_INSERTDB CELInsertDBMngr::getInstance()

