#pragma once

#define _MULTI_BEAM_

#ifdef _SQLITE_
#include "../../SQLite/SQLiteCpp.h"


#else
#include "../../ELINTOP/ODBC/mssql.h"
#include "../../ELINTOP/ODBC/odbccore.h"
#endif

#include "../../Anal/OFP_Main.h"

#include "ELGMIMsgDefn.h"
#include "../Identify/Identify.h"
#include "ELThreat.h"
#include "LOBClustering.h"
#include "ELEnvironVariableMngr.h"

#include "ElintRsltDataTypedb.h"

#ifdef _WIN32
#include "../TASK/Task.h"
#else
#endif

// 최대 후보 갯수
#define MAX_MERGE_CANDIDATE_LEVEL											(100)

// 유사도 임계값 정의
#define	THRESHOLD_OF_MIN_CANDIDATE_LEVEL	(200000)
#define	PE_CANDIDATE_LEVEL			(float) (50000.)

#define H0000_SIZE				(10)

#define TOTAL_UNDEF_ID_NUMBER			(100000)			// 미식별 총 갯수

// 위치 산출 에러
#define	PE_EFFECTIVE_DOA                (float) (0.5)					// UDIV(0.5, DEF_OF_RES_AOA)	// 0.5도
#define	PE_EFFECTIVE_LATLONG			(float) (0.0002)			//(2)												// 2초

// GetEffectiveDOADiff1() 유효 백분율
#define DOADIFF_RATIO1                  (60)		// 단위: 백분율

// GetEffectiveDOADiff2() 유효 백분율
#define DOADIFF_RATIO2                  (90)		// 단위: 백분율

#define DOADIFF_RATIO1_BY_RATIO2		( FDIV( ( DOADIFF_RATIO1 * DOADIFF_RATIO2 ), 10000. ) )

// 위치 산출하기 위한 비행 자세 정보
#define LOW_ROLLANGLE                   (-10)		// 단위 : 도
#define HIGH_ROLLANGLE                  (10)		// 단위 : 도
#define LOW_PITCHANGLE                  (-3)		// 단위 : 도
#define HIGH_PITCHANGLE                 (6)			// 단위 : 도

// LOB 제원 검증 (IsValidLOB)
#define VALID_MEANPRI                   (100000.0)		// 100 ms
#define VALID_JITTERRATION              (55.0)

//
#define MAX_LOB_FOR_INHIBIT_PE			(20)

enum enELControlLOB { APPEND_LOB=0, REMOVE_LOB };


// typedef struct {
// 	SRxABTData ABTdata;
// 	SELABTDATA_EXT ABTExt;
// 	SELEXTDB ExtDB;
// 
// } SEL_INSERTDB_ABT;
// 
// typedef struct {
// 	SELAETDATA AETdata;
// 	SELAETDATA_EXT AETExt;
// 	SELEXTDB ExtDB;
// 
// } SEL_INSERTDB_AET;

// typedef struct {
// 	char szTaskID[LENGTH_OF_TASK_ID];
// 	char szTaskName[SIZE_OF_TASK_NAME];
// 
// } SEL_STaskID2Name;


/**
* [식별자 : CLS-GMU-EL-L-SAC]
*
* [추적성 : SRS-G-SAFR-005]
*
* @class	CELEmitterMergeMngr
* @brief	위협 관리 클래스
*
* (1) 클래스 설명
* - 본 클래스는 항공 또는 지상의 LOB 데이터로부터 방사체, 빔을 관리 및 식별해주는 클래스이다.
*
* (2) 설계결정사항
* - 빔 병합, LOB 클러스터링을 처리한다.
*
* (3) 제한 및 예외처리
* - 해당사항 없음
*/
class CELEmitterMergeMngr : public CLOBClustering, public SQLite::Database
{
private:
    bool m_bDBThread;

    static int m_CoInstance;									///< 위협 관리 객체 갯수
    static UINT m_nSeqNum;										///< DB 테이블 번호

    CELSignalIdentifyAlg *m_pIdentifyAlg;		///< CED/EOb 신호 식별 객체

    CELThreat *m_pAETThreat;									///< 생성할때 위협(방사체) 관리 포인터
    CELThreat *m_pABTThreat;									///< 생성할때 위협(빔) 관리 포인터

    CELThreat *m_pUpdateAETThreat;						///< 병합된 AET 방사체 위협 포인터
    CELThreat *m_pUpdateABTThreat;						///< 병합된 ABT 방사체 위협 포인터

    SEnvironVariable *m_pSEnvironVariable;			///< 시스템 설정값 환경 포인터

    std::vector<STR_LOBS> *m_pVecLOBs;

    UINT m_uiLOBID;														///< LOB 번호
    UINT m_uiAETID;														///< 방사체 번호
    UINT m_uiABTID;														///< 빔 번호

    CGeoCoordConv m_theGeoCoordConv;

    // 위협 관리 관련 멤버 변수
    UELTHREAT *m_pUniThreat;									///< 슬레이브 연동기에서 갖고 올 DB 테이블 번호

    CELThreat *m_pTheThreatRoot;							///< 위협 노드 중에서 ROOT 노드

    // 신호 병합 관련 멥머 함수
    vector<SELMERGE_CANDIDATE> m_vecCanOfMergeLOB;		///< 병합시 후보 LOB 번호

    SRxLOBData *m_pLOBData;											///< 항공기에서 수신한 LOB 헤더 데이터 포인터
    SRxLOBHeader *m_pLOBHeader;									///< 항공기에서 수신한 LOB 메시지 데이터 포인터

    SRxABTData *m_pABTData;
    SELABTDATA_EXT *m_pABTExtData;

    SLOBOtherInfo *m_pLOBOtherInfo;						///< LOB 복사시 위협 정보 데이터 포인터

    SELLOBDATA_EXT m_LOBDataExt;							///< LOB 추가 정보
    SELLOBDATA_EXT m_ABTDataExt;							///< 빔 추가 정보

    // 미식별 관련 ELNOT 만들기
    char m_szH0000[H0000_SIZE];								///< 미식별 ELNOT 정보

    int m_iH000;															///< 미식별 번호
    unsigned short *m_pABTtoH000;								///< 미 식별 번호 테이블

    // 방사체/빔 병합처리 멤버 변수 정의
    CELThreat *m_pMergeThreatAET;								///< 변경할 방사체 위협
    CELThreat *m_pMergeThreatABT;							///< 변경할 빔 위협
    CELThreat *m_pDeleteThreatAET;							///< 삭제할 방사체 위협
    CELThreat *m_pDeleteThreatABT;							///< 삭제할 빔 위협

    UINT m_uiMergeAETID;												///< 변경할 방사체 번호
    UINT m_uiMergeABTID;											///< 변경할 빔 번호
    UINT m_uiMergeAETSeqNum;										///< 변경할 SeqNum 번호
    UINT m_uiDeleteAETID;											///< 삭제할 방사체 번호
    UINT m_uiDeleteABTID;											///< 삭제할 빔 번호
    UINT m_uiDeleteAETSeqNum;										///< 삭제할 SeqNum 번호

    SRxABTData *m_pMergeABTData;							///< 변경할 빔 위협에 대한 ABT 데이터 포인터
    SELABTDATA_EXT *m_pMergeABTExtData;				///< 변경할 빔 위협에 대한 ABT 확장 데이터 포인터
    SRxABTData *m_pDeleteABTData;							///< 삭제할 빔 위협에 대한 ABT 데이터 포인터
    SELABTDATA_EXT *m_pDeleteABTExtData;			///< 삭제할 빔 위협에 대한 ABT 확장 데이터 포인터

    SRxAETData *m_pMergeAETData;							///< 변경할 빔 위협에 대한 AET 데이터 포인터
    SELAETDATA_EXT *m_pMergeAETExtData;				///< 변경할 빔 위협에 대한 AET 확장 데이터 포인터
    SRxAETData *m_pDeleteAETData;							///< 삭제할 빔 위협에 대한 AET 데이터 포인터
    SELAETDATA_EXT *m_pDeleteAETExtData;			///< 삭제할 빔 위협에 대한 AET 확장 데이터 포인터

    int *m_piCandidate;													///< 식별 후보 데이터 포인터
    int m_nLoadCEDEOBLibrary;										///< CEDEOB 로드 여부 플레그(카운트로 0이 아닐때 로드한다.)

#ifdef _SQLITE_
    char *m_pszSQLString;
#elif defined(_MSSQL_)
    CODBCDatabase m_theMyODBC;
#else
#endif


    //SQMsg m_sqMsg;														///< 수신 쓰레드와 매니저 간의 메시지 구조체

// 	int m_nInsertDB;													///< DB 테이블에 삽입할 레코드 개수
// 
// 	bool m_bGenNewEmitter;										///< 사용자 방사체 생성 플레그
// 	UINT m_nAETIDFromGenNewEmitter;						///< 강제 방사체 생성시의 방사체 번호
// 	char m_szELNOTFromGenNewEmitter[_MAX_ELNOT_STRING_SIZE_];		///< 강제 방사체 생성시의 ELNOT
// 
// 	std::vector<SEL_STaskID2Name> m_VecTaskID2NameTable;				///< 과제ID별 과제명을 관리하긱 위한 테이블 
// 
// 	//////////////////////////////////////////////////////////////////////////
// #ifndef _THREAD_DB_
// 	int m_nArrayLOB;													///< LOB 레코드를 삽입할 개수
// 	SELArrLOB m_ArrayLOB;											///< LOB 레코드를 삽입할 데이터
// 
// 	int m_nArrayLOB_Position;									///< LOB의 주파수 및 PRI 레빌 개수
// 	SELArrLOBABT_Position m_ArrayLOB_Position;///< LOB의 주파수 및 PRI 레빌 값 데이터
// 
// 	int m_nArrayABT;													///< 빔 레코드를 삽입할 개수
// 	SELArrABT m_ArrayABT;											///< 빔 레코드를 삽입할 데이터
// 
// 	int m_nArrayABT_Position;									///< 빔 주파수 및 PRI 레빌 개수
// 	SELArrLOBABT_Position m_ArrayABT_Position;///< 빔 주파수 및 PRI 레빌 값 데이터
// 
// 	int m_nArrayAET;													///< 방사체 레코드를 삽입할 개수
// 	SELArrAET m_ArrayAET;											///< 방사체 레코드를 삽입할 데이터
// 
// #endif
// 	//////////////////////////////////////////////////////////////////////////
// 


public:
    UINT m_nGetSeqNum;												///< 슬레이브 연동기에서 갖고 올 DB 테이블 번호

    std::vector<SRxLOBData> m_VecLOBData;
    std::vector<SRxABTData> m_VecABTData;
    std::vector<SRxAETData> m_VecAETData;


private:
    void LoadCEDLibrary( char *aucTaskID, float fMinFreq, float fMaxFreq );
// 
// 	void UpdateLOBData( bool bIsFilteredLOB );
// 	void DeleteAETABTRecord( int iLinkNum, SRxLOBDataGroup *pLOBDataGroup );
    void DeleteAllAETABTRecord( SRxLOBData *pLOBData );
// 	void MakeIDInfo( STR_CEDEOBID_INFO *pIdInfo, STR_CEDEOBID_INFO *pLOBIdInfo );
// 
    void ResetABT();

    PlatformCode::EnumPlatformCode CheckPlatform( SRxABTData *pABTData );

    // 초기화 및 기타 관련 함수
    void AllocMemory();
    void FreeMemory();

// 	// 위협 관리
    void NextAETID();
    void NextABTID();
    void RecoverThreat();
    inline void NextSeqNum( bool bLink2=false ) { if( bLink2 == true ) ++ m_nGetSeqNum; else ++ m_nSeqNum; }
//
    void ClearLOBs( int nIndex );
    void AppendLOBs( int nIndex, enELControlLOB enControlLOB=APPEND_LOB );
    void AppendLOBs( std::vector<STR_LOBS> *pVecLOBs, bool bNormalMethod=true );
    void RemoveLOBs( std::vector<STR_LOBS> *pVecLOBs );
//
// 	// DB 관련 함수
    void InsertAET( CELThreat *pTheThreat, bool bUpdateDB=false, bool bEnable=true, UINT nSeqNum=m_nSeqNum, UINT uiAETID=0, bool bDirectDB=false );
    void InsertABT( CELThreat *pTheThreat, bool bUpdateDB=false, bool bEnable=true, UINT nSeqNum=m_nSeqNum, UINT uiAETID=0, UINT uiABTID=0, SELMERGE_CANDIDATE *pMergeCandidate=NULL );
    void InsertLOB( SELLOBDATA_EXT *pExt, bool i_bIsFilteredLOB=false );
// 	void GetPolizationFromLOB( int *pPolization, int nLinkNum, int nAETID, int nABTID );
// 	//void CalStatisticsFromABT( SRxABTData *pABTData );
//
// 	//
    bool ManageThreat( SELLOBDATA_EXT *pLOBDataExt, bool i_bCheckLOBMerge );
    bool CreateThreat( SELLOBDATA_EXT *pThreatDataExt, bool bCluster=false, bool bDBInsert=true, UINT nSeqNum=m_nSeqNum, UINT uiAETID=0, UINT uiABTID=0, SELMERGE_CANDIDATE *pMergeCandidate=NULL, bool bOnlyMakeAET=false );
// 	//CELThreat *CreateThreat( CELThreat *pThreat );
// 	//void MoveThreat( CELThreat *pMovedThreatABT, CELThreat *pDestThreatABT );
// 	//void CopyThreat( CELThreat *pDestThreatAET, CELThreat *pDestThreatABT, CELThreat *pSourceThreatAET, CELThreat *pSourceThreatABT );
//
    bool CompMergeLOB( SELLOBDATA_EXT *pThreatDataExt, bool bLinkComp );
    bool CompEmitterInfo( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData );
    CELThreat *UpdateThreat( SELLOBDATA_EXT *pThreatDataExt, bool bLOBCluster=false, vector<SELMERGE_CANDIDATE> *pIVecCanOfMergeLOB=NULL, bool bDBInsert=true, UINT nSeqNum=m_nSeqNum, CELThreat *pSourceThreatAET=NULL, CELThreat *pSourceThreatABT=NULL, bool bRunCluster=true, bool bRunPE=true, bool bGenNewEmitter=false );
    E_BEAM_EMITTER_STAT IsDeleteThreat( CELThreat *pTheThreat );
    int SelectTheDeletedABT( CELThreat *pTheThreat );
    bool WhichOfOldThreat( CELThreat *pTheThreat1, CELThreat *pTheThreat2 );
    int DeleteThreat( CELThreat *pTheThreat, bool bDeleteAllABT=false );
    bool DeleteThreat( CELThreat *pTheAETThreat, CELThreat *pTheABTThreat );
    bool RemoveThreat( CELThreat *pTheThreat );
    void LOBPreSetting( SRxLOBHeader* pLOBHeader, SRxLOBData* pLOBData, SLOBOtherInfo *pLOBOtherInfo );

    void SetIDLOBData( UINT nAETID, UINT nABTID, UINT nLOBID );
    void CreateAETThreat( CELThreat *pAETThreat, CELThreat *pABTThreat, SRxLOBData *pLOBData, SELLOBDATA_EXT *pThreatDataExt );
    void CreateABTThreat( CELThreat *pThreat, SRxLOBHeader *pLOBHeader, SRxLOBData *pLOBData, SELLOBDATA_EXT *pThreatDataExt, bool bCluster );
    void SetupDateTime( SELLOBDATA_EXT *pThreatDataExt );
    //void AddThreatInfo( E_EMITTER_OPCODE eOpcode=E_EO_NOT_AVAILABLE, int nCoLOB=1, bool bIsFISINTTask=false, UINT uiSeqNum=m_nSeqNum, bool bApplySearchFilter=true );
    void AddThreatInfo( SELLOBValidity *pSELLOBValidity, E_EMITTER_OPCODE enOpcode, bool bIsFISINTTask, bool bApplySearchFilter=true );
    void AddThreatInfo( SELEmitterEdited *pSELEmitterEdited=NULL, E_EMITTER_OPCODE eOpcode=E_EO_NOT_AVAILABLE, int nCoLOB=1, bool bIsFISINTTask=false, UINT uiSeqNum=m_nSeqNum, bool bApplySearchFilter=true );

    void SortMergeCandidate();
    bool DecideMergeCandidate();
//
// 	void GetAirGPSTime( time_t *pNow, int nLink );
//
// 	//
    inline SRxABTData *GetABTData( int nIndex ) { return & ( (m_pUniThreat + nIndex)->uniABT.stABTData); }
    inline SELABTDATA_EXT *GetABTExtData( int nIndex ) { return & ( (m_pUniThreat + nIndex)->uniABT.stABTExtData); }
    inline SRxAETData *GetAETData( int nIndex ) { return & ( (m_pUniThreat + nIndex)->uniAET.stAETData); }
    inline SELAETDATA_EXT *GetAETExtData( int nIndex ) { return & ( (m_pUniThreat + nIndex)->uniAET.stAETExtData); }

// 	// 빔 병합
    void ManageABTs( bool bMerge );
    bool IsSeperatedAET();
    void UpdateMergedLOBDB( bool bMerge );
    void UpdateMergedABTDB( bool bMerge );
    void UpdateMergedAETDB( bool bMerge );
    bool IsSelectAET( SRxAETData *pAETData, SRxAETData *pMatchAETData );
    void SelectUpdateAndDeleteABT( CELThreat *pMovedThreatABT, CELThreat *pDestThreatABT );
    void SelectCreateAndDeleteABT();

    void UpdateAETStat( SELAETDATA_EXT *pAETExtData, bool bGenNewEmitter=false );

// 	// 업데이트 처리 관련 함수 (ABT)
    bool UpdateABT( CELThreat *pThreat, SELLOBDATA_EXT *pLOBDataExt, bool bRunCluster=true, bool bRunPE=true, bool bGenNewEmitter=false );
    void UpdateDOAInfo( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData );
    void UpdatePulseInfo( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData );
    void UpdateFreqInfo( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData );
    void UpdatePRIInfo( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData );
    float CalcJitterRatio( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData );
    void UpdatePWInfo( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData );
    void UpdatePAInfo( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData );
// 	void UpdateScanInfo( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData );
// 	void UpdateIntraInfo( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData );
    void UpdateIDInfo( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData );
    void UpdatePEInfo( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData, int nIndex, bool bLOBValidityApplied=false, bool bRunCluster=true, bool bRunPE=true );
    void UpdateABT( CELThreat *pTheABTThreat, SELAETDATA *pAETData=NULL );
    void UpdateSeenTime( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData );
    void UpdateSignalInfo( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData );

    void PushPEInfoOfABTData( SELABTDATA_EXT *pABTExtData, SRxABTData *pABTData );

// 	void UpdateABT();
//
// 	// 업데이트 처리 관련 함수 (AET)
    void UpdateAET( CELThreat *pTheAETThreat, CELThreat *pTheABTThreat, bool bGenNewEmitter=false, bool bMergeABT=false );
    void UpdateDOAInfo( SRxAETData *pAETData, SELAETDATA_EXT *pAETExtData, SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData );
    void UpdateFreqInfo( SRxAETData *pAETData, SELAETDATA_EXT *pAETExtData, SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData );
    void UpdatePRIInfo( SRxAETData *pAETData, SELAETDATA_EXT *pAETExtData, SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData );
    void UpdatePWInfo( SRxAETData *pAETData, SELAETDATA_EXT *pAETExtData, SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData );
    void UpdatePAInfo( SRxAETData *pAETData, SELAETDATA_EXT *pAETExtData, SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData );
    void UpdatePEInfo( SRxAETData *pAETData, SELAETDATA_EXT *pAETExtData, CELThreat *pTheAETThreat, SRxABTData *pManABTData=NULL );
    void UpdateIDInfo( SRxAETData *pAETData, SELAETDATA_EXT *pAETExtData, CELThreat *pTheAETThreat );
    void UpdateSeenTime( SRxAETData *pAETData, SELAETDATA_EXT *pAETExtData, SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData );
    void UpdateSeenTime( SRxAETData *pUpdateAETData, SELAETDATA_EXT *pUpdateAETExtData, SELAETDATA *pDeleteAETData, SELAETDATA_EXT *pDeleteAETExtData );
// 	void UpdateAETABTInfo( CELThreat *pTheAETThreat, CELThreat *pTheABTThreat, SELEmitterEdited *pSELEmitterEdited, bool bDBUpdate );
// 	void UpdateAETABTInfo( SELEmitterEdited *pSELEmitterEdited, bool bDBUpdate );
//
// 	// 방사체 관련 수정시 관련 함수
    void ConvertAET2ABT( SRxABTData *pABTData, SELAETDATA *pAETData );
    void UpdateAET( CELThreat *pTheAETThreat );
    void UpdateAET( CELThreat *pTheAETThreat, SELLOBValidity *pSELLOBValidity );
//
// 	// 빔 유효성 업데이트시 관련 함수
    bool UpdateBeamValidity( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData, int nIndex, bool bCheckBeamValidity=true );
    void UpdateBeamValidity( SRxAETData *pAETData, SELAETDATA_EXT *pAETExtData, CELThreat *pTheAETThreat );
    bool IsValidity( int nCoBeamValidity, int iEmmgNumOfMinLobToBeam, float fCEP, float fEobIndfRangeKM, float fMajorAxis, float fMinorAxis, float fDist );
    void UpdateABT( CELThreat *pTheAETThreat, SELLOBValidity *pSELLOBValidity );
    bool CheckValidityByAllLOB( std::vector<STR_LOBS> *pVecLOBs, SRxABTData /*STR_POSITION_ESTIMATION*/ *pABTData );
    void PrintAllValidityByAllLOB( std::vector<STR_LOBS> *pVecLOBs, SRxABTData *pABTData );

// 	//////////////////////////////////////////////////////////////////////////
// 	// LOB 병합 비교 관련 함수
    bool CompMergeLOB( SELMERGE_CANDIDATE *pMergeCandidate, CELThreat *pThreatABT, SELLOBDATA_EXT *pThreatDataExt, bool bLinkComp );
// 	bool CompLinkNum( SELABTDATA_EXT *pABTData );
    bool CompTaskType( SELABTDATA_EXT *pABTExtData, bool bMerge=false );
    bool CompIDInfo( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData );
    bool CompSigType( SRxABTData *pABTData );
    bool CompDist( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData );
// 	bool CompDist( SRxABTData *pRefABTData, SELABTDATA_EXT *pRefABTExtData, SRxABTData *pCmpABTData, SELABTDATA_EXT *pCmpABTExtData );
    bool CompPINNum( SRxABTData *pRefABTData, SELABTDATA_EXT *pRefABTExtData, SRxABTData *pCmpABTData, SELABTDATA_EXT *pCmpABTExtData );
// 	bool IsCompareIDInfo( SRxABTData *pRefABTData, SELABTDATA_EXT *pRefABTExtData, SRxABTData *pCmpABTData, SELABTDATA_EXT *pCmpABTExtData );
    bool IsComparePINInfo( SRxABTData *pRefABTData, SELABTDATA_EXT *pRefABTExtData, SRxABTData *pCmpABTData, SELABTDATA_EXT *pCmpABTExtData );
    bool CompELNOT( SRxABTData *pRefABTData, SELABTDATA_EXT *pRefABTExtData, SRxABTData *pCmpABTData, SELABTDATA_EXT *pCmpABTExtData );
// 	bool CompIntraType( SRxABTData *pABTData );
    bool CompFreqType( SRxABTData *pABTData );
    int CompFreqRange( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData );
    bool CompPRIType( SRxABTData *pABTData );
    int CompPRIRange( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData );
// 	int CompPWType( SRxABTData *pABTData );
// 	bool CompScanType( SRxABTData *pABTData );
// 	enum FREQ_BAND CalcFreqBand( int iFreq );
// 	bool CompInOutDiff( int x, int y, int threshIn, int threshOut );
// 	bool CompFreqPosition( SRxABTData *pABTData );
// 	bool CompCEDFreqPosition();
// 	bool CompCEDPRIPosition();
    bool CompPRIPosition( SRxABTData *pABTData );
    int CompPWRange( SRxABTData *pABTData );
// 	int CompScanRange( SRxABTData *pABTData );
    float CompDistRange( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData );
    int CompValid( SRxABTData *pABTData );
    bool CompELNOTInfo( SELMERGE_CANDIDATE *pMergeCandidate, SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData );
    bool CompIDELNOTInfo( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData );
//
// 	//////////////////////////////////////////////////////////////////////////
// 	// ABT 간 병합
//
// 	// 재연모드 관련 함수
// 	//void GetThreatInfo();
//
// 	// 통계 함수
    float CalcMean( float fMean1, int iCount1, float fMean2, int iCount2 );
    int CalcMean( int iMean1, int iCount1, int iMean2, int iCount2 );
//	int CalcMean( int iMean, int iCount, int iElement );
// 	float CalcMean( float iMean1, int iCount1, float iMean2, int iCount2 );
// 	int CalcDeviation( int iDev1, int iCount1, int iDev2, int iCount2 );
// 	void CalcPositionMean( int *pPRISeq, int iCount1, int *pLOBSeq, int iCount2, int iPositionCount );
//
    // 신호 식별
    void IdentifyLOB( SRxLOBData *pLOBData );
    void IdentifyABT( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData );
    bool CouldIdentify( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData );
    void IdentifyAET( SRxAETData *pAETData, SELAETDATA_EXT *pAETExtData, CELThreat *pTheAETThreat );
    void ReIdentifyLOB( CELThreat *pTheABTThreat );
// 	char *GetElintNotation( SRadarMode *pRadarMode, int iABTID, int iLOBID, EnumLibType enLibType, bool bGround );
//
// 	// CELThreat 관련 인라인 함수
    CELThreat *GetNextThreat( CELThreat *pThreatAET );
    CELThreat *GetHeaderThreat( CELThreat *pThreatAET );
//
// 	// 미식별 ELNOT 관련 함수
// 	void MakeH000( char *pszH000, unsigned int nABTID );
    void IncH0000( int coRadarModeIndex );
//
// 	// DB 업데이트
// 	void UpdateReportTimeToEmitterDB( SELAETDATA *pAETData, SELAETDATA_EXT *pAETExtData );
// 	void UpdateReportTimeToEmitterDB( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData );
// 	void UpdateReportTimeToEmitterDB( UINT uiAETID, time_t *pFirstReportedTime, time_t *pFinalReportedTime );
// 	void UpdateReportTimeToEmitterDB( UINT uiAETID, UINT uiABTID, time_t *pFirstReportedTime, time_t *pFinalReportedTime );
// 	void UpdateAlertTimeToEmitterDB( SELAETDATA *pAETData, SELAETDATA_EXT *pAETExtData );
// 	void UpdateAlertTimeToEmitterDB( SRxABTData *pAETData, SELABTDATA_EXT *pAETExtData );
    void UpdateEmitterStatusToEmitterDB( SRxAETData *pAETData, SELAETDATA_EXT *pAETExtData );
    void UpdateBeamStatusToEmitterDB( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData );
//
// 	// 쓰레드에게 DB 정보 전달
// 	void SendInsertDBThread( UCHAR opCode, SRxLOBData *pHeader, SRxABTData *pData, SELABTDATA_EXT *pExt, SELEXTDB *pExtDB );
// 	void SendInsertDBThread( UCHAR opCode, SRxLOBData *pHeader, SRxLOBDataGroup *pData, SELLOBDATA_EXT *pExt, SELEXTDB *pExtDB, bool bLink2=false );
// 	void SendInsertDBThread( UCHAR opCode, SRxLOBData *pHeader, SELAETDATA *pData, SELAETDATA_EXT *pExt, SELEXTDB *pExtDB );
//
// 	// 기타 유틸
//
// 	// LOB 클러스터링을 위한 함수
// 	//void AddLOBPool( CELThreat *pMovedThreatABT, CELThreat *pDestThreatABT );
    bool CreateThreatFromLOBClustering( UINT uiABTID );
    void UpdateLOB();
    void ProcessTheLOBClustering( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData );
    void RunLOBClusteringResult();
// 	void UpdatePolization( SELABTDATA_EXT *pABTExtData );
//
    void InitLOB();

    bool IsValidLOB();
// 	bool IsValidRollAndPitch();

    bool NeedToRunPositionEstimation( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData, std::vector<STR_LOBS> *pVecLOBs );

// 	void GetTaskNameFromTable( char *acTaskName, char *aucTaskID );
//
    void UpdateEmitterBeamStatus( CELThreat *pThreatAET, E_BEAM_EMITTER_STAT enEmitterStat, bool bAddThreatInfo=false );

    void PushABTLANData( CELThreat *pTheThreat );
    void PushLOBLANData( SRxLOBData *pLOBData );
    void PushABTLANData( SRxABTData *pABTData );
    void PushAETLANData( SRxAETData *pAETData );


    // 쿠리 수행 함수
    int GetINTData( char *pSQLString );
    void InsertToDB_Position( SRxLOBData *pLOBData, SELLOBDATA_EXT *pExt );
    void InsertToDB_LOB( SRxLOBData *pLOBData, SELLOBDATA_EXT *pExt, bool bUpdateRadarMode=true );
    void InsertToDB_ABT( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData, bool bUpdateThreat=true );
    void InsertToDB_Position( SRxLOBData *pLOBData, SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData );
    void InsertToDB_AET( SRxAETData *pAETData, SELAETDATA_EXT *pAETExtData, SELEXTDB *pExtDB );
 
public:
    CELEmitterMergeMngr(void);
    virtual ~CELEmitterMergeMngr(void);
    void Init();
    void InitOfThreat();
    void InitDataFromDB();

    void Start();
    void UpdateCEDEOBLibrary();

    CELEmitterMergeMngr( bool bDBThread, const char *pFileName );
    bool ManageThreat( SRxLOBHeader* pLOBHeader, SRxLOBData* pLOBData, SLOBOtherInfo *pLOBOtherInfo, bool i_bIsFilteredLOB=false, bool i_bCheckLOBMerge=false );
    UINT DeleteThreat();
    bool CheckDeleteAET( CELThreat *pThreatAET, CELThreat *pDeleteAET );
    void DeleteThreat( std::vector<SThreatFamilyInfo> *pVecDelThreatInfo, bool bIsMaster, bool bIsReplay );
    void FetchLOBData( std::vector<SRxLOBHeader> *pVecLOBHeader, std::vector<SRxLOBData> *pVecLOBData, UINT uiABTID=0, SRxLOBDataAndGroupIdArray *pSRxLOBDataAndGroupIdArray=NULL );

// 	void FetchLOBData_LINK2( std::vector<SRxLOBData> *pVecLOBData, std::vector<SRxLOBDataGroup> *pVecLOBGrp, std::vector<int> *pVecLinkNum );
// 	//void FetchLOBData_LINK2( std::vector<SRxLOBData> *pVecLOBData, std::vector<SRxLOBDataGroup> *pVecLOBGrp );
// 	void UpdateMissionInfo();
// 	bool IsNotSamePreviousMissionID();
// 	void RemoveLOBs( SRxLOBData *pSRxLOBData, SRxLOBDataGroup *pSRxLOBDataGroup );
// 	bool UserDeleteThreat( int nAET );
// 	bool UserRemoveThreat( int nAET );

    inline bool RemoveThreat( int nAET ) { return m_pTheThreatRoot->RemoveAET( nAET, m_pTheThreatRoot ); }
    inline bool RemoveThreat( int nAET, int nABT ) { return m_pTheThreatRoot->RemoveABT( nAET, nABT ); }

    char *GetELNOT( int iRadarModeIndex );
    char *GetRadarModeName( int iRadarModeIndex );

// 
// 	inline UINT GetAETIDFromGenNewEmitter() { return m_nAETIDFromGenNewEmitter; }
// 	inline char *GetELNOTFromGenNewEmitter() { return m_szELNOTFromGenNewEmitter; }
// 
// 	inline SRxLOBData *GetLOBData() { return m_pLOBData; }
// 	inline SRxLOBDataGroup *GetLOBDataGroup() { return m_pLOBDataGrp; }
// 	inline SELLOBDATA_EXT *GetLOBDataExt() { return & m_LOBDataExt; }
// 
// 	// 수동 변경 처리
// 	void UpdateEmitter( std::vector<SThreatFamilyInfo> *pvecThreatInfo, SELEmitterEdited *pSELEmitterEdited, int nLinkNum );
// 	void UpdateLOBValidity( std::vector<SThreatFamilyInfo> *pvecThreatInfo, SELLOBValidity *pSELLOBValidity, int nLinkNum );
// 	void UpdateBeam( std::vector<SThreatFamilyInfo> *pvecThreatInfo, SELEmitterEdited *pSELEmitterEdited, int nLinkNum );
// 
// 	void UpdateAlertTime( std::vector<SThreatFamilyInfo> *pvecThreatInfo, SELAlertTime *pSELAlertTime );
// 	void UpdateReportTime( SELEXTDB *pextDB );
// 	void UpdateReportTime( std::vector<SThreatFamilyInfo> *pvecThreatInfo, SELReportTime *pSELReportTime );
// 
// 	//float CalDistanceNM( SELDBGmiAbt *pAbt );
// 
// 	int GetEquipNumber( STR_CEDEOBID_INFO *pCEDEOBInfo );
// 
// 	void EnableToLoadCEDEOBLibrary() { ++ m_nLoadCEDEOBLibrary; }



    void ResetToLoadCEDEOBLibrary() { m_nLoadCEDEOBLibrary=_spOne; }
    void DisableToLoadCEDEOBLibrary();

    void GetGlobalSequenceNum();
    void PrintAllABTData();

    inline SRxABTData *GetABTData() { return m_pABTData; }
    inline SELABTDATA_EXT *GetABTExtData() { return m_pABTExtData; }
    inline unsigned int GetABTID() { return m_uiABTID; }
    inline unsigned int GetAETID() { return m_uiAETID; }

    SRxABTData *GetABTData( unsigned int uiAETID, unsigned int uiABTID );


};

