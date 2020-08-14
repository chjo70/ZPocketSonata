/**
* @file			LIGLock.h
* @date			2010/10/22
* @author		Jang, MinKi(Greg) / Revised by Lee, JeongNam 
* @brief		
* @remarks		Critical Section Lock�� Scoped Lock���� �����ϰ� �̿�
*/

#ifndef _LIGLOCK_H_
#define _LIGLOCK_H_

#include <windows.h>
#include <stdio.h>

/**
 * @class    LIGLock
 * @brief   �Ӱ迵�� ���� Ŭ����
 *
 * (1) Ŭ���� ����
 * -   �Ӱ迵�� ���� Ŭ����
 *
 * (2) �����������
 * - �Ӱ迵���� ���ؼ� Enter/Leave �� �ڵ����� �� �� �ֵ��� Wrapping ����
 *
 * (3) ���� �� ����ó��
 * - �ش���׾���
 */
class LIGLock
{
public:
	/**
	* @brief     ������ �Լ�
	*/
	LIGLock();
	/**
	* @brief     �Ҹ��� �Լ�
	*/
    virtual ~LIGLock();

	/**
	* @brief		�Ӱ迵���� ��ȣ�ϱ� ���� lock �Լ�	
	*/
    void lock();

	/**
	* @brief		�Ӱ迵���� ��ȣ�� �����ϱ� ���� unlock �Լ�	
	*/
    void unlock();
	
	/**
	* @brief		trylock �Լ�
	* @return		true : lock ����, false : lock ����(�̹� lock�ɷ� ����)
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
* @remarks		{} ���̿��� �ڵ� unlock
*/

/**
 * @class    ScopedLock
 * @brief   ��ȣ ���� {} ���̿��� �ڵ� unlock�� ���ֱ� ���� wrapping Ŭ����
 *
 * (1) Ŭ���� ����
 * -    ��ȣ ���� {} ���̿��� �ڵ� unlock�� ���ֱ� ���� wrapping Ŭ����
 *
 * (2) �����������
 * - �ڵ� unlock�� �����ϵ��� ����
 *
 * (3) ���� �� ����ó��
 * - �ش���׾���
 */
class ScopedLock
{
    LIGLock *lockPtr;

public:
	/**
	* @brief     ������ �Լ�
	*/
	explicit ScopedLock(LIGLock *lockPtr2) : lockPtr(lockPtr2)	{	lock();	}

	/**
	* @brief     �Ҹ��� �Լ�
	*/
    ~ScopedLock()	{	unlock(); }

	/**
	* @brief     lock ó�� �Լ�
	*/
    void lock()		{	lockPtr->lock();	}
    
	/**
	* @brief     unlock ó�� �Լ�
	*/
	void unlock() 	{ 	lockPtr->unlock();	}
};

#endif 
