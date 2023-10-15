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

class CSGroup : public CGroup
{
protected:
	CScanSigAnal *m_pScanSigAnal;

public:
	void MakeOneGroup();
	unsigned int GetColPdw();

	CSGroup( void *pParent, unsigned int uicoMaxPdw);
	virtual ~CSGroup();

#ifdef _LOG_ANALTYPE_
    bool GetLogAnalType();
#endif


};

#endif

#endif // !defined(AFX_SGROUP_H__6DB8B3F2_58AE_4C3F_99C3_B35E033FD6BD__INCLUDED_)
