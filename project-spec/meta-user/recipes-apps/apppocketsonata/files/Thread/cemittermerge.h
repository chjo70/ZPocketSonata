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

#ifdef _MSSQL_
class CEmitterMerge : public CThread, public CMSSQL
#else
class CEmitterMerge : public CThread
#endif
{
private:
    STR_ANALINFO m_strAnalInfo;

#ifdef _MSSQL_
    CODBCDatabase m_theMyODBC;
#endif

    bool m_bScanInfo;
#ifdef __VXWORKS__
    alignas(16) UNI_LAN_DATA m_uniLanData;		// 32 -> 16
#else
    UNI_LAN_DATA m_uniLanData;
#endif
    CELEmitterMergeMngr *m_pTheEmitterMergeMngr;

    SLOBOtherInfo m_sLOBOtherInfo;				///< 타체계연동 변수


public:
    STR_MessageData *m_pMsg;

public:
    CEmitterMerge( int iKeyId, char *pClassName, bool bArrayLanData );
    virtual ~CEmitterMerge(void);

    inline CELEmitterMergeMngr *GetEmitterMergeMngr() { return m_pTheEmitterMergeMngr; }

    void Run( key_t key=IPC_PRIVATE );
    virtual void _routine();
    virtual const char *GetThreadName() { return m_szThreadName; }

private:
    void InitData();
    void MergeEmitter();

    // 수집 쓰레드에 추적/스캔 요청을 전송한다.
    void RequestTrackCollect( SRxLOBData *pLOBData );
    void RequestTrackReCollect();
    void RequestScanCollect( SRxLOBData *pLOBData );
    void RequestScanReCollect();

    void ReloadLibrary();

    void SendNewUpd();
    void SendDelete( unsigned int uiAETID );
    void SendLan( unsigned int uiOpcode, void *pData, unsigned int uiDataSize, SELABTDATA_EXT *pABTExtData );

    void SetStartOfAnalScan();

};


#endif // CEMITTERMERGE_H
