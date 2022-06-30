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
    //##ModelId=452B0C5500B7
    CNewSigAnal *m_pNewSigAnal;

public:
    void Init();
    
	int GetColPdw();

    CNGroup( void *pParent, unsigned int uiCoMaxPdw );
    virtual ~CNGroup();

};

#endif

#endif // !defined(AFX_CNGROUP_H__C151E4E3_35C0_46B2_B18E_7E053F694757__INCLUDED_)
