#include "ctrackanalysis.h"
#include "../Utils/clog.h"

#include "../Utils/csingleserver.h"
#include "../Utils/cmultiserver.h"

#define _DEBUG_

extern CMultiServer *g_pTheZYNQSocket;
extern CSingleServer *g_pTheCCUSocket;

// 클래스 내의 정적 멤버변수 값 정의
CTrackAnalysis* CTrackAnalysis::pInstance = nullptr;

/**
 * @brief CTrackAnalysis::CTrackAnalysis
 * @param iKeyId
 * @param pClassName
 */
CTrackAnalysis::CTrackAnalysis( int iKeyId, char *pClassName ) : CThread( iKeyId, pClassName )
{

}


/**
 * @brief CTrackAnalysis::~CTrackAnalysis
 */
CTrackAnalysis::~CTrackAnalysis(void)
{

}


/**
 * @brief CTrackAnalysis::Run
 */
void CTrackAnalysis::Run()
{
    LOGENTRY;

    CThread::Run();

}

/**
 * @brief CTrackAnalysis::_routine
 */
void CTrackAnalysis::_routine()
{

}
