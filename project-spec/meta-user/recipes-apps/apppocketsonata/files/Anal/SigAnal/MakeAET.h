// MakeAET.h: interface for the CMakeAET class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAKEAET_H__D3ED692F_6704_4688_B28C_7FEB2AEACEB9__INCLUDED_)
#define AFX_MAKEAET_H__D3ED692F_6704_4688_B28C_7FEB2AEACEB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "_SigAnal.h"

#ifdef __cplusplus

//##ModelId=452B0C550390
class CMakeAET
{
private:
	char m_Comma[50];

public:
	//##ModelId=452B0C55039A
	UINT *m_pParam;
	//##ModelId=452B0C55039B
	int m_CoEmitter;
	//##ModelId=452B0C55039C
	int m_nAnalEmitter;
	//##ModelId=452B0C5503A4
	int m_CoAet;
	//##ModelId=452B0C5503A5
	int m_CoMakeAet;

protected:
	STR_PDWPARAM *m_pPdwParam;

	//##ModelId=452B0C5503CF
	STR_EMITTER *m_pEmitter;
	// MAX_AET 개수는 펄스열 개수에 의한 최대 개수이고
	// +1 한 값은 MakeUpAET()에서 버퍼로 사용하기 위한 것이다.
	//##ModelId=452B0C5503C8
	//STR_NEWAET m_Aet[ MAX_AET+1 ];
	//##ModelId=452B0C5503A6
	int m_nMaxPdw;
	//##ModelId=452B0C5503AE
	int m_nCoPdw;
	//##ModelId=452B0C5503AF
	UINT m_CoAnalPdw;
	//##ModelId=452B0C5503C3
	STR_PULSE_TRAIN_SEG *m_pSeg;

public:
	void ConvertRealFreq( STR_FRQ *pFrq );
	void ReMakeEmitter();
	void DiscardEmitter();
	void SetCWParameter( STR_NEWAET *pNewAet );
	int CalMaxChannel( STR_PDWINDEX *pPdw );

	void DISP_HexFineAet( STR_NEWAET *pNewAet );

	char * Comma( char *pString );
	void PrintAllEmitter();
	UINT CalOverlapSpace( int hgh1, int low1, int hgh2, int low2 );
	//BOOL CompMeanDiff(int x, int y, int thresh);
	//BOOL CompMeanDiff64(_TOA x, _TOA y, _TOA thresh);
	//##ModelId=452B0C5503E0
	inline int GetMakeAet() { return m_CoMakeAet; }

	//##ModelId=452B0C560002
	inline int GetCoAnalPdw() { return m_CoAnalPdw; }
	inline void SetCoAnalPdw(UINT coAnalPdw ) { m_CoAnalPdw=coAnalPdw; }
	//##ModelId=452B0C560003
	inline int GetCoAet() { return m_CoAet; }
	inline void SetCoAet( UINT coAet ) { m_CoAet = coAet; }

	//##ModelId=452B0C560004
	virtual int CalcAoaMeanByHistAoa( STR_PDWINDEX *pSrcIndex )=0;
	//##ModelId=452B0C56000C
	virtual int GetColPdw()=0;
	//##ModelId=452B0C56000E
	virtual int CalcPAMean(PDWINDEX *pPdwIndex, int count )=0;
	//##ModelId=452B0C560012
	virtual int VerifyPW( PDWINDEX *pPdwIndex, int count )=0;
	//##ModelId=452B0C560019
	virtual void MarkToPdwIndex( PDWINDEX *pPdwIndex, int count, int mark_type )=0;
	//##ModelId=452B0C560021
	virtual void SaveEmitterPdwFile(STR_EMITTER *pEmitter, int index )=0;
	//##ModelId=452B0C56002A
	virtual int GetCoSeg()=0;
	//##ModelId=452B0C56002C
	virtual int GetCoEmitter()=0;
	//##ModelId=452B0C56002E
	virtual STR_PULSE_TRAIN_SEG *GetPulseSeg()=0;
	//##ModelId=452B0C560034
	virtual STR_EMITTER *GetEmitter()=0;
	//##ModelId=452B0C560036
	virtual UINT CalcFreqMedian( STR_PULSE_TRAIN_SEG *pSeg )=0;
	virtual STR_PDWPARAM* GetPdwParam()=0;

	//##ModelId=452B0C560039
	void MakeAoaHistoInPdwIdxArr();
	//##ModelId=452B0C56003A
	UINT CalcAoaMean_GSKIMF_200505_6( STR_EMITTER *pEmitter );
	//##ModelId=452B0C56003F
	void MarkToEmitterPdwIndex( STR_EMITTER *pEmitter, int type ) { MarkToPdwIndex( pEmitter->pdw.pIndex, pEmitter->pdw.count, type ); }
	//##ModelId=452B0C560042
	void MakeExtInfoInSeg( STR_EXT *pExt, STR_EMITTER *pEmitter );
	//##ModelId=452B0C56004A
	void MakeAOAInfoInSeg(STR_MINMAX *pAoa, STR_EMITTER *pEmitter);
	//##ModelId=452B0C560052
	void MakePAInfoInSeg(STR_MINMAX *pPa, STR_EMITTER *pEmitter);
	//##ModelId=452B0C560055
	void MakePWInfoInSeg(STR_MINMAX *pPw, STR_EMITTER *pEmitter);
	//##ModelId=452B0C56005D
	void MakePRIInfoInSeg(STR_PRI *pPri, STR_EMITTER *pEmitter);
	//##ModelId=452B0C560060
	void MakeFrqInfoInSeg( STR_FRQ *pFrq, STR_EMITTER *pEmitter );
	int MakeDIInfoInSeg( STR_EMITTER *pEmitter);


	//##ModelId=452B0C560071
	void MakeAET();
	//##ModelId=452B0C560072
	void Init(void);
	//##ModelId=452B0C560074
	CMakeAET( int coMaxPdw=NSP_MAX_PDW );
	//##ModelId=452B0C56007B
	virtual ~CMakeAET();

public:
	//SRxLOBData m_Aet[MAX_AET+1];

	//##ModelId=452B0C560068
	virtual void MakeAETfromEmitter( STR_EMITTER *pEmitter, int idxEmitter )=0;
	virtual void DISP_FineAet( SRxLOBData *pLOBData )=0;
	virtual SRxLOBData *GetLOBData()=0;

};

#endif

#endif // !defined(AFX_MAKEAET_H__D3ED692F_6704_4688_B28C_7FEB2AEACEB9__INCLUDED_)
