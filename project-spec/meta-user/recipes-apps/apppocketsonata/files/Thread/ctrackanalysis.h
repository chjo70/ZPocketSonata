﻿#ifndef CTRACKANALYSIS_H
#define CTRACKANALYSIS_H

#include "../Utils/cthread.h"
#include "../Utils/clog.h"

#include "../Anal/SigAnal/SysPara.h"
#include "../Anal/KnownSigAnal/KnownSigAnal.h"


/**
*
* @brief	  PDW 데이터를 입력으로 추적 분석을 수행합니다.
* @details	  펄스 내 분석 기능을 수행한다
* @author    조철희 (churlhee.jo@lignex1.com)
* @version   1.0.0
* @date      2023-01-16 10:54:00
* @warning
*
*/
class CTrackAnalysis : public CThread
{
private:
    CSysPara *m_pTheSysPara;														///< 신호 분석 관련 시스템 변수를 저장하는 변수 입니다.
    CKnownSigAnal *m_pTheKnownSigAnal;												///< 추적 신호 분석을 처리하는 객체 입니다.

public:
    STR_MessageData *m_pMsg;														///< CThread 에서 사용하는 단일 메시지 데이터 포인터 입니다.

private:
    void AnalysisStart();															///< 입력 PDW 데이터로 추적 분석을 수행합니다.

public:
    CTrackAnalysis( int iThreadPriority, const char *pThreadName=NULL, bool bArrayLanData=false );	///< 초기 멤버 변수값 등을 설정하는 객체 생성자 입니다.
    virtual ~CTrackAnalysis(void);													///< 메모리 해지 등을 처리하고 객체를 소멸합니다.

    void Run( key_t key=IPC_PRIVATE );												///< CThread 클래스의 Run() 함수를 호출하여 쓰레드를 생성하게 합니다.
    void _routine();														///< 쓰레드에서 서버 또는 클라이언트를 실행하게 한다.
    STR_MessageData *GetParentMessage() { return m_pMsg; }                  ///< 메시지 데이터를 리턴 합니다.

    const char *GetThreadName() { return m_szThreadName; }

    void InitTrackAnalysis();

};

#endif // CTRACKANALYSIS_H
