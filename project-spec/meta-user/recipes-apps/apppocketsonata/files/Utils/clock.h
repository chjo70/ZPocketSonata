/*****************************************************************************************

    @file      clock.h
    @brief
    @details   ~
    @author    조철희
    @date      6.11.2023
    @copyright © LIGNex1, 2023. All right reserved.

*****************************************************************************************/


#pragma once


#ifdef __linux__
#include <sys/msg.h>
#include <sys/ipc.h>
#include <regex.h>
#include <semaphore.h>
#elif defined(__VXWORKS__)
#include <semaphore.h>

#endif


class CLock
{
private:

#if _MSC_VER
    CCriticalSection m_cs;
    bool m_bLock;

#elif defined(__VXWORKS__)
    sem_t m_mutex;

#elif defined(__linux__)
    sem_t m_mutex;

#else
#endif


public:
    /**
     * @brief     CLock
     * @return
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-11-06 17:22:56
     * @warning
     */
    CLock() {
#ifdef _MSC_VER
        m_bLock = false;

#elif defined(__VXWORKS__)
        if( sem_init( & m_mutex, 1, 1 ) < 0 ) {
            perror( "세마포어 실패" );
        }
#elif defined(__linux__)
        if( sem_init( & m_mutex, 1, 1 ) < 0 ) {
            perror( "세마포어 실패" );
        }

#else


#endif
    }


    /**
     * @brief     ~CLock
     * @return
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-11-06 17:22:53
     * @warning
     */
    virtual ~CLock() {
#ifdef _MSC_VER

#else
        sem_destroy( & m_mutex );

#endif

    }

    /**
     * @brief     Lock
     * @return    void
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-11-06 17:16:45
     * @warning
     */
    void Lock()
    {
#ifdef _MSC_VER
        m_cs.Lock();
        m_bLock = true;
#else
        sem_wait( & m_mutex );
#endif

    }

    /**
     * @brief     UnLock
     * @return    void
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-11-06 17:16:50
     * @warning
     */
    void UnLock()
    {
#ifdef _MSC_VER
        m_cs.Unlock();
        m_bLock = false;
#else
        sem_post( & m_mutex );
#endif

    }

    /**
     * @brief     IsLock
     * @return    bool
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-11-06 17:52:36
     * @warning
     */
    bool IsLocked()
    {
        bool bRet=false;

#ifdef _MSC_VER
        bRet = m_bLock;

#else
        int iValue;

        sem_getvalue( & m_mutex, & iValue );
        //printf( "\n [VxWorks] iValue[%d]", iValue );

#endif

        return bRet;
    }

private:


public:



};


