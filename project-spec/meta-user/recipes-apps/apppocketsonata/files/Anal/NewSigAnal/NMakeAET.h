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

/**

    @class   CNMakeAET
    @brief   탐지 에미터 생성 관련 클래스 정의 입니다.
    @details ~

**/
class CNMakeAET : public CMakeAET
{
private:


protected:
	CNewSigAnal *m_pNewSigAnal;

public:
	void MarkAllAetToPdwIndex();
	void Init();
	void MakeAET( bool bDBInsert );
    void PrintAllAET();
	int CalcAoaMeanByHistAoa( STR_PDWINDEX *pSrcIndex );
	unsigned int GetColPdw();
	int CalcPAMean(PDWINDEX *pPdwIndex, unsigned int uiCount );
	int VerifyPW( PDWINDEX *pPdwIndex, unsigned int uiCount);
	void MarkToPDWIndex( PDWINDEX *pPdwIndex, unsigned int uiCount, PULSE_MARK enMarkType);
	void SaveEmitterPDWFile(STR_EMITTER *pEmitter, int iPLOBID, bool bSaveFile=false );
	unsigned int GetCoSeg();
	unsigned int GetCoEmitter();
	STR_PULSE_TRAIN_SEG *GetPulseSeg();
	STR_EMITTER *GetEmitter();
	UINT CalcFreqMedian( STR_PULSE_TRAIN_SEG *pSeg );
	STR_PDWPARAM* GetPdwParam();


    CNMakeAET( void *pParent, unsigned int uicoMaxPdw );
	virtual ~CNMakeAET();

	// 타 장비 관련 위협 데이터를 생성한다.
public:
	void DISP_FineLOB( SRxLOBData *pManAet );
	//void MakeLOBDatafromEmitter( STR_EMITTER *pEmitter, int idxEmitter );
    unsigned int IsStorePDW();
	void GetCollectTime( struct timespec *pTimeSpec );

    unsigned int GetPDWID();
    unsigned int GetOpInitID();

    void SetKnownIndexEmitter(unsigned int uiIndex, int iIdxEmitter) { }


#if defined(_ELINT_) || defined(_XBAND_)
    EN_RADARCOLLECTORID GetCollectorID();
    char *GetTaskID();
#endif

};

#endif

#endif // !defined(AFX_CNMAKEAET_H__B714AED9_7308_450E_8042_4AC14DA832CB__INCLUDED_)


