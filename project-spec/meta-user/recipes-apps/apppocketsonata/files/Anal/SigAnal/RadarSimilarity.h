/*****************************************************************************************

    @file      CRadarSimilarity.h
    @brief     두 위협의 비교를 수행 합니다.
    @details   ~
    @author    조철희
    @date      22.10.2023
    @copyright © LIGNex1, 2023. All right reserved.

*****************************************************************************************/

#pragma once

//#include "./INC/AetIPL.h"
#include "../EmitterMerge/ELMsgDefn.h"
#include "../EmitterMerge/ELEnvironVariableMngr.h"


class CRadarSimilarity {

private:
    float m_fFixedFreqMargin;
    float m_fStableMargin;

    SEnvironVariable *m_pSEnvironVariable;

public:
    CRadarSimilarity( SEnvironVariable *pSEnvironVariable, float fFixedFreqMargin, float m_fStableMargin );
    ~CRadarSimilarity();

    bool CompSigTypeMargin( SRxABTData *pABTData, SRxLOBData *pLOBData );
    bool CompMOPTypeMargin( SRxABTData *pABTData, SRxLOBData *pLOBData );
    bool CompFreqMargin( SRxABTData *pABTData, SRxLOBData *pLOBData );
    bool CompPRIMargin( SRxABTData *pABTData, SRxLOBData *pLOBData );

};

