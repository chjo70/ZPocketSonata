#pragma once
#include "LIGThread.h"
#include "LIGCondition.h"
#include "LIGCondition.h"

#ifdef _WIN32
#include "Task.h"
#else
#include "../../Utils/cthread.h"
#endif

#include <queue>
using namespace std;

#define HEADER_BYTE_OF_SQMSG (sizeof(unsigned int)*2+sizeof(unsigned short)*2+sizeof(bool)*5)



/**
 * [식별자 : CLS-GMU-EL-L-MQT]
 *
 * [추적성 : SRS-G-SCFR-007]
 *
 * @class    CELMsgQThread
 * @brief  지상 ELINT / 항공 ELINT 사이의 송수신 메시지를 스레드 처리하기 위한 클래스
 *
 * (1) 클래스 설명
 * -    지상 ELINT / 항공 ELINT 사이의 송수신 메시지를 스레드 처리하기 위한 클래스
 *
 * (2) 설계결정사항
 * - 해당사항없음
 *
 * (3) 제한 및 예외처리
 * - 해당사항없음
 */
class CELMsgQThread : public LIGThread
{
public:
	
	/**
	* @brief       생성자함수
	* @param       void   
	* @return         
	*/
	CELMsgQThread(void);
	
	/**
	* @brief       소멸자함수
	* @param       void   
	* @return         
	*/
	virtual ~CELMsgQThread(void);

protected:
	virtual void Run(); // LIGThread 멤버함수 재정의 (스레드 실행시 호출되는 함수 임)
	virtual void ProcessMsg(SQMsg& i_stMsg); // 재정의
	bool GetMsgFromQ(SQMsg& i_stMsg);
	void PushMsg(SQMsg& i_stMsg);
	void DeleteAllQData();

	inline unsigned int GetMsgQSize() { return m_queMsg.size(); }
	void PrintTheMsgQueue();

protected:
	std::queue<SQMsg> m_queMsg;	
	LIGCondition m_cond;
	//LIGLock m_QLock;		
};

// class CELMsgQThreadExt : public LIGThread
// {
// public:
// 	CELMsgQThreadExt(void);
// 	virtual ~CELMsgQThreadExt(void);
// 
// protected:
// 	virtual void Run(); // LIGThread 멤버함수 재정의 (스레드 실행시 호출되는 함수 임)
// 	virtual void ProcessMsgExt(SQMsg& i_stMsg); // 재정의
// 	bool GetMsgFromQExt(SQMsg& i_stMsg);
// 	void PushMsgExt(SQMsg& i_stMsg);
// 	void DeleteAllQDataExt();
// 	void SetMyThreadAffinity();
// 
// protected:
// 	bool m_bThreadAffinityMask; 
// 	std::queue<SQMsg> m_queMsg;	
// 	//LIGCondition m_cond;
// 	//LIGLock m_QLock;		
// };

// class CELMsgQThreadExtSec : public LIGThread
// {
// public:
//   CELMsgQThreadExtSec(void);
//   virtual ~CELMsgQThreadExtSec(void);
// 
// protected:
//   virtual void Run(); // LIGThread 멤버함수 재정의 (스레드 실행시 호출되는 함수 임)
//   virtual void ProcessMsgExtSec(SQMsg& i_stMsg); // 재정의
//   bool GetMsgFromQExtSec(SQMsg& i_stMsg);
//   void PushMsgExtSec(SQMsg& i_stMsg);
//   void DeleteAllQDataExtSec();
//   void SetMyThreadAffinity();
// 
// protected:
//   bool m_bThreadAffinityMask; 
//   std::queue<SQMsg> m_queMsg;	
//   //LIGCondition m_cond;
//   //LIGLock m_QLock;		
// };
// 
