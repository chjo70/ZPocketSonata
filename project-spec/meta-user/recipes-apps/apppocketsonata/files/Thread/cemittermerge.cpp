#include "cemittermerge.h"

#define _DEBUG_


// 클래스 내의 정적 멤버변수 값 정의
CEmitterMerge* CEmitterMerge::pInstance = nullptr;

CEmitterMerge::CEmitterMerge( int iKeyId, char *pClassName, bool bArrayLanData ) : CThread( iKeyId, pClassName, bArrayLanData )
{
   LOGENTRY;

   //Init();

}

/**
 * @brief CEmitterMerge::~CEmitterMerge
 */
CEmitterMerge::~CEmitterMerge()
{

}

/**
 * @brief CEmitterMerge::Run
 */
void CEmitterMerge::Run()
{
    LOGENTRY;

    CThread::Run();

}

/**
 * @brief CEmitterMerge::_routine
 */
void CEmitterMerge::_routine()
{
    LOGENTRY;
    bool bWhile=true;

    while( bWhile ) {
        sleep(1);
    }
}

