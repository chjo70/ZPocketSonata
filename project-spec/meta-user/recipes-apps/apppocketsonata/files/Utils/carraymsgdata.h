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

#include "clock.h"

#include "../Include/system.h"


//#define SIZE_OF_MSGDATA_ARRAY           (5) // (CO_TRACK_CHANNEL+CO_DETECT_CHANNEL+CO_SCAN_CHANNEL)            // 128 -> 64
#define SIZE_OF_MSGDATA_ARRAY           (CO_TRACK_CHANNEL+CO_DETECT_CHANNEL+CO_SCAN_CHANNEL)            // 128 -> 64

#define ARARAY_MARK_UPPER              (0x4F)
#define ARARAY_MARK_LOWER              (0xF4)

// 랜 데이터 비교 횟수 이후 에러 통보
#define MAX_TRY_MARK                    (20)

class CArrayMsgData
{
private:
    unsigned char m_ucPushIndex;

    bool m_bArrayLanData;

    unsigned char *m_pszArray[SIZE_OF_MSGDATA_ARRAY];

    CLock m_theLock;

#ifdef __VXWORKS__
    sem_t m_mutex;

#endif

public:
    CArrayMsgData( bool bArrayLanData );
    virtual ~CArrayMsgData();

    int PushLanData( void *pData, unsigned int uiLength );
    void PopLanData( void *pData, int iIndex, unsigned int uiLength );

    void PrintDebug( unsigned int ucPushIndex );

    void Clear();

    virtual void msSleep( unsigned int mssleep )=0;
    virtual void ShowTaskMessae( int iLevel, bool bLog ) = 0;
    virtual const char *GetThreadName() = 0;

    virtual void SendTaskMngr( unsigned int uiErrorCode, const char *pszThreadName=NULL )=0;

private:
    void Alloc();
    void Free();
    void SetMark( int iIndex, bool bLog=false );

public:
    void Init();

    //_DEFINE_LOG_VIRTUAL_FUNCTION

};


