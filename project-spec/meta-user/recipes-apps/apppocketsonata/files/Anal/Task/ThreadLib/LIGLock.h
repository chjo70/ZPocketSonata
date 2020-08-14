/**
* @file			LIGLock.h
* @date			2010/10/22
* @author		Jang, MinKi(Greg) / Revised by Lee, JeongNam 
* @brief		
* @remarks		Critical Section Lock을 Scoped Lock으로 간편하게 이용
*/

#ifndef _LIGLOCK_H_
#define _LIGLOCK_H_

#include <windows.h>
#include <stdio.h>

/**
 * @class    LIGLock
 * @brief   임계영역 설정 클래스
 *
 * (1) 클래스 설명
 * -   임계영역 설정 클래스
 *
 * (2) 설계결정사항
 * - 임계영역에 대해서 Enter/Leave 를 자동으로 할 수 있도록 Wrapping 관리
 *
 * (3) 제한 및 예외처리
 * - 해당사항없음
 */
class LIGLock
{
public:
	/**
	* @brief     생성자 함수
	*/
	LIGLock();
	/**
	* @brief     소멸자 함수
	*/
    virtual ~LIGLock();

	/**
	* @brief		임계영역을 보호하기 위한 lock 함수	
	*/
    void lock();

	/**
	* @brief		임계영역을 보호를 해지하기 위한 unlock 함수	
	*/
    void unlock();
	
	/**
	* @brief		trylock 함수
	* @return		true : lock 성공, false : lock 실패(이미 lock걸려 있음)
	*/
   // bool trylock();

private:
	 CRITICAL_SECTION m_cs;
};

/**
* @class		ScopedLock
* @date			2010/10/22
* @author		Jang, MinKi(Greg)
* @brief			Scoped Lock Class
* @remarks		{} 사이에서 자동 unlock
*/

/**
 * @class    ScopedLock
 * @brief   괄호 스콥 {} 사이에서 자동 unlock을 해주기 위한 wrapping 클래스
 *
 * (1) 클래스 설명
 * -    괄호 스콥 {} 사이에서 자동 unlock을 해주기 위한 wrapping 클래스
 *
 * (2) 설계결정사항
 * - 자동 unlock이 가능하도록 관리
 *
 * (3) 제한 및 예외처리
 * - 해당사항없음
 */
class ScopedLock
{
    LIGLock *lockPtr;

public:
	/**
	* @brief     생성자 함수
	*/
	explicit ScopedLock(LIGLock *lockPtr2) : lockPtr(lockPtr2)	{	lock();	}

	/**
	* @brief     소멸자 함수
	*/
    ~ScopedLock()	{	unlock(); }

	/**
	* @brief     lock 처리 함수
	*/
    void lock()		{	lockPtr->lock();	}
    
	/**
	* @brief     unlock 처리 함수
	*/
	void unlock() 	{ 	lockPtr->unlock();	}
};

#endif 
