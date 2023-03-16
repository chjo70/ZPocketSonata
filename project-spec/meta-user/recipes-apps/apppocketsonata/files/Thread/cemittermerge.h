/*!
 * \class classname
 *
 * \brief 
 *
 * \author chjo7_hns3pqr
 * \date 2월 2022
 */

#ifndef CEMITTERMERGE_H
#define CEMITTERMERGE_H

#include "../Include/system.h"
#include "../Utils/cthread.h"

#include "../Anal/EmitterMerge/ELEmitterMergeMngr.h"



/**
*
* @brief	  식별/위협 관리를 처리하는 클래스 입니다.
* @details	  신호분석 연동 제어 기능을 수행한다
* @author    조철희 (churlhee.jo@lignex1.com)
* @version   1.0.0
* @date      2023-01-16 10:54:00
* @warning
*
*/

#ifdef _MSSQL_
class CEmitterMerge : public CThread, public CMSSQL
#else
class CEmitterMerge : public CThread
#endif
{
private:
    STR_ANALINFO m_strAnalInfo;										///< 쓰레드 간의 메시지 에서 이 쓰레드에서 사용할 메시지의 데이터 저장소 입니다.

#ifdef _MSSQL_
    CODBCDatabase m_theMyODBC;
#endif

    bool m_bScanInfo;												///< 스캔 분석 여부 플레그 입니다.
#ifdef __VXWORKS__
	// 32 -> 16비트 강제 packed 구조체 정의
    alignas(16) UNI_LAN_DATA m_uniLanData;							///< 랜 메시지 데이터 입니다.
#else
    UNI_LAN_DATA m_uniLanData;										///< 랜 메시지 데이터 입니다.
#endif

    CELEmitterMergeMngr *m_pTheEmitterMergeMngr;					///< 식별/위협을 처리하는 클래스 입니다.

    SLOBOtherInfo m_sLOBOtherInfo;									///< 식별/위협을 처리하는 추가 페라미터 변수 모음 입니다.


public:
    STR_MessageData *m_pMsg;										///< CThread 에서 사용하는 단일 메시지 데이터 포인터 입니다.

private:
    void Init();
    void InitEmitterMerge();
    void MergeEmitter();
    void DeleteThreat();

    // 수집 쓰레드에 추적/스캔 요청을 전송한다.
    void RequestTrackCollect( SRxLOBData *pLOBData );
    void RequestTrackReCollect();
    void RequestScanCollect( SRxLOBData *pLOBData );
    void RequestScanReCollect();

    void ReloadLibrary();

    void SendNewUpd();
    void SendDelete( unsigned int uiAETID );
    void SendLan( unsigned int uiOpcode, void *pData, unsigned int uiDataSize, SELABTDATA_EXT *pABTExtData );

public:
    CEmitterMerge( int iKeyId, const char *pClassName, bool bArrayLanData );				
    virtual ~CEmitterMerge(void);															

    inline CELEmitterMergeMngr *GetEmitterMergeMngr() { return m_pTheEmitterMergeMngr; }	///< 객체 포인터를 리턴합니다.

    void Run( key_t key=IPC_PRIVATE );														
    void _routine();																
    char *GetThreadName() { return m_szThreadName; }								///< 쓰레드명을 리턴합니다.			
    STR_MessageData *GetParentMessage() { return m_pMsg; }                          ///< 메시지 데이터를 리턴 합니다.


};


#endif // CEMITTERMERGE_H
