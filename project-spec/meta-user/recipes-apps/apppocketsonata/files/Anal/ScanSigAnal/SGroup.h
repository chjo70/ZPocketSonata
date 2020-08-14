// SGroup.h: interface for the CSGroup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SGROUP_H__6DB8B3F2_58AE_4C3F_99C3_B35E033FD6BD__INCLUDED_)
#define AFX_SGROUP_H__6DB8B3F2_58AE_4C3F_99C3_B35E033FD6BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../SigAnal/Group.h"

#ifdef __cplusplus

class CScanSigAnal;

//##ModelId=452B0C4403AC
class CSGroup : public CGroup  
{
protected:
	//##ModelId=452B0C4403B5
	CScanSigAnal *m_pScanSigAnal;

public:
	void MakeOneGroup();

	//##ModelId=452B0C4403B9
	int GetColPdw();
	//##ModelId=452B0C4403BD
	CSGroup( void *pParent, int coMaxPdw );
	//##ModelId=452B0C4403C0
	virtual ~CSGroup();

};

#endif

#endif // !defined(AFX_SGROUP_H__6DB8B3F2_58AE_4C3F_99C3_B35E033FD6BD__INCLUDED_)
