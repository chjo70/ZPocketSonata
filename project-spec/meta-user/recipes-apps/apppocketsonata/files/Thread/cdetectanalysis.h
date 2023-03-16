#ifndef CDETECTANALYSIS_H
#define CDETECTANALYSIS_H

#include "../Include/system.h"
#include "../Utils/cthread.h"

#include "../Anal/SigAnal/SysPara.h"
#include "../Anal/NewSigAnal/NewSigAnal.h"


/**
*
* @brief	  PDW 데이터를 입력으로 탐지 분석을 수행합니다.
* @details	  펄스 내 분석 기능을 수행한다
* @author    조철희 (churlhee.jo@lignex1.com)
* @version   1.0.0
* @date      2023-01-16 10:54:00
* @warning
*
*/
class CDetectAnalysis : public CThread
{
private:
    UNI_LAN_DATA m_uniLanData;							///< 랜 메시지 데이터 입니다.

    CSysPara *m_pTheSysPara;							///< 신호 분석 관련 시스템 변수를 저장하는 변수 입니다.
    CNewSigAnal *m_pTheNewSigAnal;						///< 탐지 신호 분석을 처리하는 객체 입니다.

    STR_PDWDATA m_PDWData;								///< 입력 PDW 데이터가 저장된 데이터 저장소 입니다.

public:
    STR_MessageData *m_pMsg;							///< CThread 에서 사용하는 단일 메시지 데이터 포인터 입니다.

public:
    CDetectAnalysis( int iKeyId, const char *pClassName=NULL, bool bArrayLanData=false );		///< 초기 멤버 변수값등을 설정하는 객체 생성자 입니다.	
    virtual ~CDetectAnalysis(void);														///< 종료 메시지와 메머리 해지를 처리하는 객체 소먈자 입니다.

    void InitDetectAnalysis();                                                            

    void Run( key_t key=IPC_PRIVATE );													///< CThread 클래스의 Run() 함수를 호출하여 쓰레드를 생성하게 합니다.

    void MakePDWData();																	///< 신호 분석하기 위해 PDW 데이터를 파싱하여 분석에 용이하도록 변환합니다.

    void _routine();															        ///< 쓰레드에서 서버 또는 클라이언트를 실행하게 한다.
    char *GetThreadName() { return m_szThreadName; }							        ///< 쓰레드명을 리턴합니다.
    STR_MessageData *GetParentMessage() { return m_pMsg; }                              ///< 메시지 데이터를 리턴 합니다.

private:
    void AnalysisStart();																///< 입력 PDW 데이터로 신호 분석을 수행합니다.


};



#endif // CDETECTANALYSIS_H
