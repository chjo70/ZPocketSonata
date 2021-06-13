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

//##ModelId=452B0C53008A
class CKGroup : public CGroup  
{
protected:
	//##ModelId=452B0C5300A0
	CKnownSigAnal *m_pKnownSigAnal;

public:
	//##ModelId=452B0C5300A8
	int GetColPdw();
	//##ModelId=452B0C5300A9
	void MakeFreqAoaPwGroup() { CGroup::MakeFreqAoaPwGroup( & m_GrStat[m_nStat] ); }
	//##ModelId=452B0C5300AA
	BOOL MakeGroup();
	//##ModelId=452B0C5300AB
	int GetMaxPdw();
	//##ModelId=452B0C5300AC
    CKGroup( void *pParent, int coMaxPdw );
	//##ModelId=452B0C5300B4
	virtual ~CKGroup();

};

#endif

#endif // !defined(AFX_KGROUP_H__FF64B37F_60B2_45B6_BB37_664C7324E6C7__INCLUDED_)
