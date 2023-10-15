/**

    @file      carraymsgdata.h
    @brief
    @details   ~
    @author    Cool Guy
    @date      5.09.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

#pragma once


#ifdef __linux__
#include <sys/msg.h>
#include <sys/ipc.h>
#include <regex.h>
#include <semaphore.h>
#elif defined(__VXWORKS__)
#include <semaphore.h>

#endif



#define SIZE_OF_MSGDATA_ARRAY           (32)            // 128 -> 64

#define ARARAY_MARK_UPPER              (0x4F)
#define ARARAY_MARK_LOWER              (0xF4)

// 랜 데이터 비교 횟수 이후 에러 통보
#define MAX_TRY_MARK                    (20)

//#include "cthread.h"

class CArrayMsgData
{
private:
    unsigned char m_ucPushIndex;
    //unsigned char m_ucPopIndex;

    bool m_bArrayLanData;

    unsigned char *m_pszArray[SIZE_OF_MSGDATA_ARRAY];

#if _MSC_VER
    CCriticalSection m_cs;

#elif defined(__VXWORKS__)
    sem_t m_mutex;

#elif defined(__linux__)
    sem_t m_mutex;

#else
#endif


public:
    CArrayMsgData( bool bArrayLanData );
    virtual ~CArrayMsgData();

    int PushLanData( void *pData, unsigned int uiLength );
    void PopLanData( void *pData, int iIndex, unsigned int uiLength );

    void PrintDebug( unsigned int ucPushIndex );

    void Lock()
    {
#ifdef _MSC_VER
        m_cs.Lock();

#else
        sem_wait( & m_mutex );
#endif

    }

    void UnLock()
    {
#ifdef _MSC_VER
        m_cs.Unlock();

#else
        sem_post( & m_mutex );
#endif
    }

    virtual void msSleep( unsigned int mssleep )=0;
    virtual void ShowTaskMessae( int iLevel ) = 0;
    virtual char *GetThreadName() = 0;

    virtual void SendTaskMngr( unsigned int uiErrorCode, const char *pszThreadName=NULL )=0;

private:
    void Alloc();
    void Free();
    void SetMark( int iIndex );

public:
    void Init();

    //_DEFINE_LOG_VIRTUAL_FUNCTION

};


