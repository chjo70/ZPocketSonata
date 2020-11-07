#ifndef CEMITTERMERGE_H
#define CEMITTERMERGE_H

#include "../Utils/clog.h"

#include "../Include/system.h"
#include "../Utils/cthread.h"

#include "../Anal/EmitterMerge/ELEmitterMergeMngr.h"

class CEmitterMerge : public CThread
{
private:
    UNI_LAN_DATA m_uniLanData;
    CELEmitterMergeMngr *m_pTheEmitterMergeMngr;

    SLOBOtherInfo m_sLOBOtherInfo;				///< 타체계연동 변수

public:
    static CEmitterMerge *m_pInstance;

    STR_MessageData *m_pMsg;

public:
    CEmitterMerge( int iKeyId, char *pClassName, bool bArrayLanData );
    virtual ~CEmitterMerge(void);

    THREAD_STANDARD_FUNCTION( CEmitterMerge )

private:
    void InitData();
    void MergeEmitter();

    void ReloadLibrary();

    void SendNewUpd();
    void SendLost( unsigned int uiAETID );
    void SendDelete( unsigned int uiAETID );

};

#define EMTMRG          CEmitterMerge::GetInstance()
#define EMTMRG_RELEASE  CEmitterMerge::ReleaseInstance()
#define EMTMRG_IS       CEmitterMerge::IsThereInstance()

#endif // CEMITTERMERGE_H
