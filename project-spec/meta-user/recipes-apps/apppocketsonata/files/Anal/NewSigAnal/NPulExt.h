// NPulExt.h: interface for the NPulExt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNPULEXT_H__67019449_CA11_45F2_931C_8A44867F010E__INCLUDED_)
#define AFX_CNPULEXT_H__67019449_CA11_45F2_931C_8A44867F010E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../SigAnal/PulExt.h"

#ifdef __cplusplus

class CNewSigAnal;


//##ModelId=452B0C55000A
//////////////////////////////////////////////////////////////////////
/*!	\brief	클래스명 CNPulExt

						펄스열 추출 클래스
		\author 조철희
		\date   2007-06-29 11:15:00
*/
class CNPulExt : public CPulExt
{
public:
	UINT m_CoPulseTrains;

protected:
	//##ModelId=452B0C550015
	CNewSigAnal *m_pNewSigAnal;			///< 최상위 분석 클래스의 포인터

	ENUM_BANDWIDTH m_enBandWidth;

public:
	int GetCoPdw();
	//##ModelId=452B0C550019
	inline void DiscardPulseTrain() { CPulExt::DiscardPulseTrain(); }
	//##ModelId=452B0C55001A
	inline void SetRefEndSeg() { CPulExt::SetRefEndSeg(); }
	//##ModelId=452B0C55001F
	inline void CleanPulseTrains() { CPulExt::CleanPulseTrains(); }
	//##ModelId=452B0C550020
	inline void SetRefStartSeg() { CPulExt::SetRefStartSeg(); }
	//##ModelId=452B0C550021
	inline void GetStartEndPriLevel() { CPulExt::GetStartEndPriLevel(); }
	inline void MarkStablePulseTrain() { CPulExt::MarkStablePulseTrain(); }
	inline void MakeCWPulseTrain() { CPulExt::MakeCWPulseTrain(); }

	//##ModelId=452B0C550022
	void Init();
	//##ModelId=452B0C550023
	//void PulseExtract();
    void PulseExtract( vector<SRadarMode *> *pVecMatchRadarMode );
	//##ModelId=452B0C550029
	STR_DTOA_HISTOGRAM *GetDtoaHist();
	//##ModelId=452B0C55002A
	void MakeDtoaHistogram( PDWINDEX *pPdwIndex, unsigned int uiCount, STR_MINMAX_TOA *pRange );
	//##ModelId=452B0C550033
	void CalPRIRange( STR_PULSE_TRAIN_SEG *pSeg, _TOA priMean, UINT dtoa_count );
	//##ModelId=452B0C550037
	void MarkToPdwIndex( PDWINDEX *pPdwIndex, unsigned int uiCount, USHORT usMarkType);
	//##ModelId=452B0C550040
	STR_PDWINDEX *GetFrqAoaGroupedPdwIndex();
	UINT CheckHarmonic(_TOA priMean1, _TOA priMean2, _TOA uiThreshold );
	void ExtractPulseTrainByLibrary( vector<SRadarMode *> *pVecMatchRadarMode );
    int GetPulseStat();
    void ClearAllMark();

	//##ModelId=452B0C550041
    CNPulExt( void *pParent, unsigned int uiCoMaxPdw );
	//##ModelId=452B0C550048
	virtual ~CNPulExt();

};

#endif

#endif // !defined(AFX_CNPULEXT_H__67019449_CA11_45F2_931C_8A44867F010E__INCLUDED_)
