// NPulExt.h: interface for the NPulExt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNPULEXT_H__67019449_CA11_45F2_931C_8A44867F010E__INCLUDED_)
#define AFX_CNPULEXT_H__67019449_CA11_45F2_931C_8A44867F010E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../Utils/clog.h"

#include "../SigAnal/PulExt.h"

#ifdef __cplusplus

class CNewSigAnal;


//////////////////////////////////////////////////////////////////////
/*!	\brief	클래스명 CNPulExt

						펄스열 추출 클래스
		\author 조철희
		\date   2007-06-29 11:15:00
*/
class CNPulExt : public CPulExt
{
private:
    unsigned int m_uiCoFrqAoaPwIdx;

public:


protected:
	CNewSigAnal *m_pNewSigAnal;			///< 최상위 분석 클래스의 포인터


public:
    CNPulExt( void *pParent, unsigned int uiCoMaxPdw, const char *pThreadName=NULL );
    virtual ~CNPulExt();

	unsigned int GetCoPdw();

	inline void DropPulseTrain() { CPulExt::DropPulseTrain(); }
	inline void SetRefEndSeg() { CPulExt::SetRefEndSeg(); }
	inline void CleanPulseTrains() { CPulExt::CleanPulseTrains(); }
	inline void SetRefStartSeg() { CPulExt::SetRefStartSeg(); }
	inline void GetStartEndPriLevel() { CPulExt::GetStartEndPriLevel(); }
	//inline void MarkStablePulseTrain() { CPulExt::MarkStablePulseTrain(); }
	inline void MakeCWPulseTrain() { CPulExt::MakeCWPulseTrain(); }

	void Init();
    void PulseExtract( vector<SRadarMode *> *pVecMatchRadarMode );
	STR_DTOA_HISTOGRAM *GetDtoaHist();
	void MakeDtoaHistogram( PDWINDEX *pPdwIndex, unsigned int uiCount, STR_MINMAX_TOA *pRange );
	void CalPRIRange( STR_PULSE_TRAIN_SEG *pSeg, _TOA priMean, UINT dtoa_count );
    void MarkToPDWIndex( PDWINDEX *pPdwIndex, unsigned int uiCount, PULSE_MARK enMarkType );

	STR_PDWINDEX *GetFrqAoaGroupedPdwIndex();
	UINT CheckHarmonic(_TOA priMean1, _TOA priMean2, _TOA uiThreshold );
	void ExtractPulseTrainByLibrary( vector<SRadarMode *> *pVecMatchRadarMode );
    void ClearAllMark();

#ifdef _LOG_ANALTYPE_
    bool IsLogAnalType( LogType enLogType );
#endif

};

#endif

#endif // !defined(AFX_CNPULEXT_H__67019449_CA11_45F2_931C_8A44867F010E__INCLUDED_)
