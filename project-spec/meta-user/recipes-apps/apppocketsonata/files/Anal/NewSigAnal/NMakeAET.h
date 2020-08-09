// NMakeAET.h: interface for the NMakeAET class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNMAKEAET_H__B714AED9_7308_450E_8042_4AC14DA832CB__INCLUDED_)
#define AFX_CNMAKEAET_H__B714AED9_7308_450E_8042_4AC14DA832CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../SigAnal/MakeAET.h"

//////////////////////////////////////////////////////////////////////////
// 타 장비의 위협 구조체를 정의한다.
#include "../EmitterMerge/ELMsgDefn.h"

//////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

class CNewSigAnal;

//##ModelId=452B0C550051
class CNMakeAET : public CMakeAET
{
protected:
	//##ModelId=452B0C55005C
	CNewSigAnal *m_pNewSigAnal;
	ENUM_BANDWIDTH m_enBandWidth;
	
public:
	void MarkAllAetToPdwIndex();
	//##ModelId=452B0C550060
	void Init();
	//##ModelId=452B0C550061
	void MakeAET();
	//##ModelId=452B0C550065
	int CalcAoaMeanByHistAoa( STR_PDWINDEX *pSrcIndex );
	//##ModelId=452B0C550067
	int GetColPdw();
	//##ModelId=452B0C550068
	int CalcPAMean(PDWINDEX *pPdwIndex, int count );
	//##ModelId=452B0C550079
	int VerifyPW( PDWINDEX *pPdwIndex, int count );
	//##ModelId=452B0C55007C
	void MarkToPdwIndex( PDWINDEX *pPdwIndex, int count, int mark_type );
	//##ModelId=452B0C550085
	void SaveEmitterPdwFile(STR_EMITTER *pEmitter, int index );
	//##ModelId=452B0C55008E
	int GetCoSeg();
	//##ModelId=452B0C550097
	int GetCoEmitter();
	//##ModelId=452B0C550098
	STR_PULSE_TRAIN_SEG *GetPulseSeg();
	//##ModelId=452B0C550099
	STR_EMITTER *GetEmitter();
	//##ModelId=452B0C55009A
	UINT CalcFreqMedian( STR_PULSE_TRAIN_SEG *pSeg );
	STR_PDWPARAM* GetPdwParam();

	//##ModelId=452B0C5500A2
	CNMakeAET( void *pParent, int coMaxPdw=NSP_MAX_PDW );
	//##ModelId=452B0C5500A5
	virtual ~CNMakeAET();

	// 타 장비 관련 위협 데이터를 생성한다.
public:
	int m_CoMakeLOB;

	SRxLOBData m_LOBData[ MAX_AET+1 ];

	void DISP_FineAet( SRxLOBData *pManAet );
	void MakeAETfromEmitter( STR_EMITTER *pEmitter, int idxEmitter );
	inline SRxLOBData *GetLOBData() { return & m_LOBData[0]; }

};

#endif

#endif // !defined(AFX_CNMAKEAET_H__B714AED9_7308_450E_8042_4AC14DA832CB__INCLUDED_)
