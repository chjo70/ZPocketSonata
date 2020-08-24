// KColPdw.h: interface for the CKColPdw class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KCOLPDW_H__92EF869E_FC78_41EC_B749_344B33D38443__INCLUDED_)
#define AFX_KCOLPDW_H__92EF869E_FC78_41EC_B749_344B33D38443__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "KVar.h"

//##ModelId=452B0C5300B6
class CKColPdw  
{
protected:
	//##ModelId=452B0C5300BC
	int m_nMaxPdw;

public:
	//##ModelId=452B0C5300C6
	BOOL GetFifo( UINT *phase );
	//##ModelId=452B0C5300C8
	int GetOnePdw( TNEW_PDW *pNewPdw );
	//##ModelId=452B0C5300CA
	BOOL ReadFifo( UINT *phase );
	//##ModelId=452B0C5300D1
	int ReadOnePdw( TNEW_PDW *pNewPdw );
	
	//##ModelId=452B0C5300D3
	int Collect();
	//##ModelId=452B0C5300D4
	void Init();
	//##ModelId=452B0C5300D5
	CKColPdw( int coMaxPdw );
	//##ModelId=452B0C5300DB
	virtual ~CKColPdw();

};

#endif // !defined(AFX_KCOLPDW_H__92EF869E_FC78_41EC_B749_344B33D38443__INCLUDED_)
