/**

    @file      Hopping.h
    @brief
    @details   ~
    @author    조철희
    @date      14.06.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

#pragma once

#include "_SigAnal.h"

#include "../../Utils/clog.h"
#include "../../Utils/ccommonutils.h"

#include <vector>
#include <algorithm>

// enum ENUM_HOPPINGDWELL {
//     enFREQ_HOPPING=0,
//     enPRI_DWELL
// };

/**

    @class   CHopping
    @brief   호핑 분석 관련 클래스 입니다.
    @details ~

**/
class CHopping
{
protected:
    DEFINE_ANAL_PVAR_

public:

private:
    unsigned int m_uiMaxPdw;

    ENUM_HOPPINGDWELL m_enHoppingDwell;

    // 분석 결과
    unsigned int m_uiHoppingLevel;
    unsigned int m_uiSteps[MAX_STAGGER_LEVEL_POSITION];

    unsigned int m_uiMargin;
    unsigned int m_uiFixedFreqMargin;
    unsigned m_uiStableMargin;

    unsigned int m_uiCoData;

    int *m_piDiffY;
    unsigned int *m_puiDataY;
    _TOA *m_ptDataX;

    UINT m_SamplingTime;

    unsigned int m_coCanPeak;
    int *m_pCanPeak;

    float *m_pAcf;
    unsigned int m_CoAcf;

    unsigned int m_uiStartSample;
    unsigned int m_uiCoSample;
    int *m_piSampleData;
    unsigned int *m_puiSampleDataY;
    _TOA *m_pSampleToa;

    int m_iPeriod;
    float m_fPeriod;

    std::vector<SHoppingDwell> m_vecHopping;

private:
    void CalcHoppingStepByNonPeriod();

    unsigned int CalcHoppingDwellStepByNonPeriod( STR_EMITTER *pEmitter );
    void RemoveRepeatableDwell( SHoppingDwell *pstHopping );
    bool IsRepeatable( SHoppingDwell *pstHopping, unsigned int uiStart, unsigned int uiSteps );


    unsigned int CalcHoppingStepByNonPeriod2( STR_EMITTER *pEmitter );


    void DifferentialY( STR_EMITTER *pEmitter );
    void CalcSamplingTime( STR_EMITTER *pEmitter );


    void SamplingFREQProcess( STR_EMITTER *pEmitter, ENUM_SAMPLING_OPTION enSamplingOption );
    void SamplingDTOAProcess( STR_EMITTER *pEmitter, ENUM_SAMPLING_OPTION enSamplingOption );

    void AutoCorerelation();
    void FindPeriod();

    unsigned int CalcHoppingStepByPeriod();
    void CalcHoppingStep();
    void MakeHoppingEmitter( STR_EMITTER *pEmitter );

    void HoppingAnalysis( STR_EMITTER *pEmitter );


public:
    CHopping( void *pParent, unsigned int uiCoMaxPdw );
    virtual ~CHopping(  );

    void MakeFREQ( STR_EMITTER *pEmitter );
    void MakeDTOA( STR_EMITTER *pEmitter );

    void HoppingAnalysis( STR_EMITTER *pEmitter, ENUM_HOPPINGDWELL enHoppingDwell );
    bool IsHopping( unsigned int uiMargin );

};


