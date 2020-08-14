/**
* @file			LIGCondition.h
* @date			2010/10/22
* @author		Jang, MinKi(Greg), Revised by Lee, JeongNam
* @brief			Condition Variables
* @remarks		
*/

#ifndef LIGCondition_H
#define LIGCondition_H

//#include "LIGLock.h"

/**
 * @class    LIGCondition
 * @brief   Thread Event 관리를 위한 wrapping 클래스
 *
 * (1) 클래스 설명
 * -   Thread Event 관리를 위한 wrapping 클래스
 *
 * (2) 설계결정사항
 * - 윈도우의 Thread Event 함수 제공 및 관리
 *
 * (3) 제한 및 예외처리
 * - 해당사항없음
 */
class LIGCondition
{
public:
	/**
	* @brief     생성자 함수
	*/
	LIGCondition(bool isAutoCreate = false);
	/**
	* @brief     소멸자 함수
	*/
	~LIGCondition();

	/**
	* @brief		Thread Event 생성
	* @return		true : 이벤트 생성, false : 이미 Thread가 실행중이거나 이벤트가 생성된 경우
	* @remark		자동리셋, 언시그널상태가 기본
	*/

	/**
	* @brief     Thread Event 생성
	* @param     bManualReset		매뉴얼/자동 리셋 이벤트를 초기에 설정하도록 전달하는 데이터
	* @return    성공시 true, 실패시 false
	*/
	bool CreateLIGEvent(bool bManualReset = false);
	
	/**
	* @brief     Event 파괴 함수	
	* @return    성공시 true, 실패시 false
	*/
	//bool DestroyEvent();

	/**
	* @brief		Thread Event 가 발생될 때까지 dwMilliseconds 동안 대기 (Wait)
	* @param[in]	dwMilliseconds : -1(무한대기), 0~(숫자만큼 대기)
					unlock : 인자를 unlock 시키고 wait 후 빠져나올때 다시 lock
	* @return		true : 이벤트를 받았거나 대기시간 종료, false : Thread가 실행중이 아니거나 이벤트가 생성되어 있지 않은 경우
	*/

	/**
	* @brief     Thread Event 가 발생될 때까지 dwMilliseconds 동안 대기 (Wait)
	* @param    dwMilliseconds : -1(무한대기), 0~(숫자만큼 대기)	
	* @return    성공시 true, 실패시 false
	*/
    bool Wait(unsigned int dwMilliseconds = 0xffffffff);

	/**
	* @brief     Thread Event 가 발생될 때까지 dwMilliseconds 동안 대기 (Wait)
	* @param    unlock : 인자를 unlock 시키고 wait 후 빠져나올때 다시 lock
	* @param    dwMilliseconds : -1(무한대기), 0~(숫자만큼 대기)	
	* @return    성공시 true, 실패시 false
	*/
   // bool Wait(LIGLock* unlock, unsigned int dwMilliseconds = 0xffffffff);

	/**
	* @brief     Thread Event 발생 (Notify One)
	* @return    true : 이벤트 발생, false : Thread가 실행중이 아니거나 이벤트가 생성되어 있지 않은 경우
	*/
	bool LIGSetEvent(); 

	/**
	* @brief     핸들 유효성을 체크하는 함수
	* @return    true : 유효함, false : 유효하지 않음
	*/
	inline bool IsValidHandle() { return m_hEvent != NULL; }

	/**
	* @brief     Thread Event 발생 (Reset) (Notify One)
	* @return    true : 이벤트 발생, false : Thread가 실행중이 아니거나 이벤트가 생성되어 있지 않은 경우
	*/
	bool LIGResetEvent();

private:
	HANDLE m_hEvent; 
	volatile bool isInit;
	//LIGLock m_isInitLock; 
};

#endif 
