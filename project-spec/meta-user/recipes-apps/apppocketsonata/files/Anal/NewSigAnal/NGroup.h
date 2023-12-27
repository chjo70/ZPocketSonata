// NGroup.h: interface for the NGroup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNGROUP_H__C151E4E3_35C0_46B2_B18E_7E053F694757__INCLUDED_)
#define AFX_CNGROUP_H__C151E4E3_35C0_46B2_B18E_7E053F694757__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../SigAnal/Group.h"

#ifdef __cplusplus

class CNewSigAnal;

class CNGroup : public CGroup
{
protected:
    CNewSigAnal *m_pNewSigAnal;

public:
    CNGroup( void *pParent, unsigned int uiCoMaxPdw, const char *pThreadName=NULL );
    virtual ~CNGroup();

    void Init();

	unsigned int GetCoPDW();
    unsigned int GetColPDW();

#ifdef _LOG_ANALTYPE_
    bool IsLogAnalType( LogType enLogType );
#endif


};

#endif

#endif // !defined(AFX_CNGROUP_H__C151E4E3_35C0_46B2_B18E_7E053F694757__INCLUDED_)
