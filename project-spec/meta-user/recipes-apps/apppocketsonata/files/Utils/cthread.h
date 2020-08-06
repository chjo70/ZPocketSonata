#ifndef CTHREAD_H
#define CTHREAD_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <regex.h>

#include "../Include/system.h"

#include "../Utils/carraymsgdata.h"

#define LENGTH_OF_CLASSNAME (20)

#pragma pack(push, 1)

/**
 * @brief 쓰레드간의 메시지 데이터 구조체 정의
 */
struct STR_MessageData {
    long mtype;

    // Opcode
    unsigned char ucOpCode;

    // Src/Dest
    unsigned char ucSrcDest;

    //랜 송신시 이 값이 0 이 아니면 이 소켓 값으로 데이터를 전송한다.
    int iSocket;

    // 데이터 길이
    unsigned int uiLength;

    // CArrayData 클래스 사용시 인덱스 값을 의미함. 0 보다 작은 값은 CArrayData 를 사용하지 않은 것이다.
    int iArrayIndex;

    char szMessage[128];

} ;

#pragma pack(pop)

/**
 * @brief The CThread class
 */
class CThread : public CArrayMsgData
{
private:
    pthread_t m_MainThread;
    key_t m_MsgKeyID;
    STR_MessageData m_Msg;

    static int m_iCoThread;
    static int m_iCoMsgQueue;

protected:
    char m_szClassName[LENGTH_OF_CLASSNAME];

public:
    CThread( int iMsgKey, char *pClassName, bool bArrayLanData=false );
    ~CThread();

    void Run();
    void Run( void *(*Func)(void*) );
    int Pend();
    void Stop();
    int QMsgRcv( int iFlag=0 );
    void QMsgSnd( UINT uiOpCode, void *pData, int iByte );
    void QMsgSnd( key_t iKeyId, UINT uiOpCode, void *pData=NULL, int iByte=0 );
    void QMsgSnd( STR_MessageData *pMessageData, void *pArrayMsgData=NULL );

    inline key_t GetKeyId() { return m_MsgKeyID; }

    inline STR_MessageData *GetDataMessage() { return & m_Msg; }
    inline int GetCoThread() { return m_iCoThread; }
    inline int GetCoMsgQueue() { return m_iCoMsgQueue; }

    static void *CallBack( void *pArg );

    virtual void _routine() { }
    virtual const char *ChildClassName() { return NULL; }

    //pthread_create(&thread,NULL,thread_routine, NULL);
};

#endif // CTHREAD_H
