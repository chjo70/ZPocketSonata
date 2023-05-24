// KGroup.h: interface for the CKGroup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KGROUP_H__FF64B37F_60B2_45B6_BB37_664C7324E6C7__INCLUDED_)
#define AFX_KGROUP_H__FF64B37F_60B2_45B6_BB37_664C7324E6C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../SigAnal/Group.h"

#include "KnownSigAnal.h"

#ifdef __cplusplus

class CKnownSigAnal;

class CKGroup : public CGroup
{
protected:
	CKnownSigAnal *m_pKnownSigAnal;

public:
    CKGroup( void *pParent, unsigned int uiCoMaxPdw );
    virtual ~CKGroup();

    void Init();

	unsigned int GetColPdw();
	void MakeFreqAoaPwGroup() { CGroup::MakeFreqAoaPwGroup( & m_GrStat[m_nStat] ); }
	bool MakeKnownGroup();

    //inline unsigned int GetFrqAoaGroupedPdwIndex() { return CGroup::m_uiCoFrqAoaPwIdx; }

};

#endif

#endif // !defined(AFX_KGROUP_H__FF64B37F_60B2_45B6_BB37_664C7324E6C7__INCLUDED_)
