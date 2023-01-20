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

public:
    CEmitterMerge( int iKeyId, const char *pClassName, bool bArrayLanData );				///< 초기 멤버 변수값등을 설정하는 객체 생성자 입니다.
    virtual ~CEmitterMerge(void);															///< 종료 메시지와 메머리 해지를 처리하는 객체 소먈자 입니다.

    inline CELEmitterMergeMngr *GetEmitterMergeMngr() { return m_pTheEmitterMergeMngr; }	///< 객체 포인터를 리턴합니다.

    void Run( key_t key=IPC_PRIVATE );														///< CThread 클래스의 Run() 함수를 호출하여 쓰레드를 생성하게 합니다.
    virtual void _routine();																///< 쓰레드에서 서버 또는 클라이언트를 실행하게 한다.
    virtual char *GetThreadName() { return m_szThreadName; }								///< 쓰레드명을 리턴합니다.

private:
    void InitData();																		///< 멤버 변수를 초기화합니다. 
    void MergeEmitter();																	///< 병합 에미터를 처리합니다.
    void DeleteThreat();																	///< 위협 삭제 처리를 수행합니다.

    // 수집 쓰레드에 추적/스캔 요청을 전송한다.
    void RequestTrackCollect( SRxLOBData *pLOBData );										///< LOB 데이터 기반으로 추적 수집을 설정합니다.
    void RequestTrackReCollect();															///< 추적 중인 LOB에 대해서 수집을 재설정합니다.
    void RequestScanCollect( SRxLOBData *pLOBData );										///< LOB 데이터 기반으로 스캔 수집을 설정합니다.
    void RequestScanReCollect();															///< 스캔 중인 LOB에 대해서 재설정하여 스캔 분석을 수행하도록 합니다.

    void ReloadLibrary();																	///< CED/EOB를 재로딩합니다.

    void SendNewUpd();																		///< 신규/추적/소실 LOB 데이터를 랜으로 전달합니다.
    void SendDelete( unsigned int uiAETID );												///< 삭제 LOB 데이터를 랜으로 전달합니다.
    void SendLan( unsigned int uiOpcode, void *pData, unsigned int uiDataSize, SELABTDATA_EXT *pABTExtData );	///< 연결된 서버에 데이터를 송신한다.

};


#endif // CEMITTERMERGE_H
