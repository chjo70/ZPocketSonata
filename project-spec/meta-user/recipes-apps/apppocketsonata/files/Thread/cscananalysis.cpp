#include "cscananalysis.h"
#include "../Utils/clog.h"

#include "../Utils/csingleserver.h"
#include "../Utils/cmultiserver.h"

#define _DEBUG_

extern CMultiServer *g_pTheZYNQSocket;
extern CSingleServer *g_pTheCCUSocket;

// 클래스 내의 정적 멤버변수 값 정의
CScanAnalysis* CScanAnalysis::pInstance = nullptr;

/**
 * @brief CScanAnalysis::CScanAnalysis
 * @param iKeyId
 * @param pClassName
 */
CScanAnalysis::CScanAnalysis( int iKeyId, char *pClassName ) : CThread( iKeyId, pClassName )
{

}


/**
 * @brief CScanAnalysis::~CScanAnalysis
 */
CScanAnalysis::~CScanAnalysis(void)
{

}


/**
 * @brief CScanAnalysis::Run
 */
void CScanAnalysis::Run()
{
    LOGENTRY;

    CThread::Run();

}

/**
 * @brief CScanAnalysis::_routine
 */
void CScanAnalysis::_routine()
{

}
