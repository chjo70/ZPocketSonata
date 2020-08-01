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

#include "../Include/defines.h"

#define LENGTH_OF_CLASSNAME (20)

struct STR_MessageData {
    long mtype;

    // Opcode
    unsigned int opCode;
    //랜 송신시 이 값이 0 이 아니면 이 소켓 값으로 데이터를 전송한다.
    int iSocket;

    // 데이터
    int iLength;
    char szMessage[256];

} ;

/**
 * @brief The CThread class
 */
class CThread
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
    CThread( int iMsgKey, char *pClassName );
    ~CThread();

    void Run();
    void Run( void *(*Func)(void*) );
    int Pend();
    void Stop();
    int QMsgRcv();
    void QMsgSnd( key_t iKeyId, UINT uiOpCode, void *pData=NULL, int iByte=0 );
    void QMsgSnd( key_t iKeyId, STR_MessageData *pMessageData );

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
