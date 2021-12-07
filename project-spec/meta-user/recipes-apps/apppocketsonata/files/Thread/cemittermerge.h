#ifndef CEMITTERMERGE_H
#define CEMITTERMERGE_H

//#include "../Utils/clog.h"

#include "../Include/system.h"
#include "../Utils/cthread.h"

#include "../Anal/EmitterMerge/ELEmitterMergeMngr.h"

class CEmitterMerge : public CThread
{
private:
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

    void TrackFail();
    void ScanFail();

    void ReloadLibrary();

    void SendNewUpd();
    void SendDelete( unsigned int uiAETID );
    void SendLan( unsigned int uiOpcode, void *pData, unsigned int uiDataSize, SELABTDATA_EXT *pABTExtData );

    void SetStartOfAnalScan();



};


#endif // CEMITTERMERGE_H
