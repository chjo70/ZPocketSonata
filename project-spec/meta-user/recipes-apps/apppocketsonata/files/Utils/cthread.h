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
#include "../Anal/INC/system.h"

#include "../Utils/carraymsgdata.h"

#define LENGTH_OF_CLASSNAME (30)

#define THREAD_STANDARD_FUNCTION(A)    \
void Run( key_t key=IPC_PRIVATE ); \
virtual void _routine();    \
virtual const char *ChildClassName() { return m_szClassName; } \
static A* GetInstance() { \
    if(m_pInstance == NULL) { \
        m_pInstance = new A( g_iKeyId++, (char*) #A, true ); \
    } \
    return m_pInstance; } \
static void ReleaseInstance() { \
    if(m_pInstance) { \
        delete m_pInstance; \
        m_pInstance = NULL; \
    } } \
static bool IsThereInstance() { \
    bool bRet = true; \
    if(m_pInstance == NULL) { \
        bRet = false; \
    } \
    return bRet; }

// 오직 CTaskMngr 에서만 사용하는 정의문 입니다.
#define THREAD_STANDARD_FUNCTION_2(A )    \
void Run( key_t key=IPC_PRIVATE ); \
virtual void _routine();    \
virtual const char *ChildClassName() { return m_szClassName; } \
static A* GetInstance() { \
    if(m_pInstance == NULL) { \
        char szSQLiteFileName[100]; \
        strcpy( szSQLiteFileName, CEDEOB_SQLITE_FOLDER ); \
        strcat( szSQLiteFileName, CEDEOB_SQLITE_FILENAME ); \
        m_pInstance = new A( g_iKeyId++, (char*) #A, true, (char*) szSQLiteFileName ); \
    } \
    return m_pInstance; } \
static void ReleaseInstance() { \
    if(m_pInstance) { \
        delete m_pInstance; \
        m_pInstance = NULL; \
    } } \
static bool IsThereInstance() { \
    bool bRet = true; \
    if(m_pInstance == NULL) { \
        bRet = false; \
    } \
    return bRet; }


#pragma pack(push, 1)


/**
 * @brief 수집 쓰레드 정보
 */
struct STR_COLLECTINFO {
    unsigned int uiCh;
    unsigned int uiTotalPDW;

    // 방사체 번호
    unsigned int uiAETID;
    // 빔 번호
    unsigned int uiABTID;


} ;

// 수집한 데이터에서 분석한 LOB 헤더 정보
struct STR_ANALINFO {
    unsigned int uiBand;
    unsigned int uiTotalLOB;

    // 수집한 채널 정보
    unsigned int uiCh;

    // 방사체 번호
    unsigned int uiAETID;
    // 빔 번호
    unsigned int uiABTID;

} ;


/**
 * @brief 메시지 데이터 구조체
 */
union UNI_MSG_DATA {
    unsigned int uiData;
    time_t tiNow;

    STR_COLLECTINFO strCollectInfo;
    STR_ANALINFO strAnalInfo;

    char szData[32];
} ;

/**
 * @brief 쓰레드간의 메시지 데이터 구조체 정의
 */
struct STR_MessageData {
    long mtype;

    // Opcode
    unsigned int uiOpCode;

    // Src/Dest
    unsigned char ucSrcDest;

    //랜 송신시 이 값이 0 이 아니면 이 소켓 값으로 데이터를 전송한다.
    int iSocket;

    // 데이터 길이
    unsigned int uiDataLength;

    // 데이터 영역 이다.
    UNI_MSG_DATA x;

    // CArrayData 클래스 사용시 인덱스 값을 의미함. 0 보다 작은 값은 CArrayData 를 사용하지 않은 것이다.
    int iArrayIndex;
    unsigned int uiArrayLength;

} ;

/**
 * @brief The CThread class
 */
class CThread : public CArrayMsgData
{
private:
    pthread_t m_MainThread;
    key_t m_MsgKeyID;
    STR_MessageData m_RcvMsg;
    STR_MessageData m_SndMsg;

    char *m_pszRecvData;
    char m_szRecvData[_MAX_LANDATA];

    static int m_iCoThread;
    static int m_iCoMsgQueue;

protected:
    char m_szClassName[LENGTH_OF_CLASSNAME];

private:
    void DisplayMsg( bool bSend, const char *pszClassName=NULL );

public:
    CThread( int iMsgKey, char *pClassName, bool bArrayLanData=false );
    ~CThread();

    void Run( key_t key=IPC_PRIVATE );
    void Run( void *(*Func)(void*), key_t key=IPC_PRIVATE );
    int Pend();
    void Stop();
    void Stop2();
    int QMsgRcv( int iFlag=0 );
    void QMsgSnd( unsigned int uiOpCode, void *pArrayMsgData, unsigned int uiLength, void *pData=NULL, unsigned int uiDataLength=0, const char *pszClassName=NULL );
    void QMsgSnd( key_t iKeyId, UINT uiOpCode, void *pData=NULL, int iByte=0 );
    void QMsgSnd( STR_MessageData *pMessageData, void *pArrayMsgData=NULL );
    void QMsgSnd( unsigned int uiOpCode, void *pData, unsigned int uiDataLength );
    void QMsgSnd( unsigned int uiOpCode, const char *pszClassName=NULL );

    inline key_t GetKeyId() { return m_MsgKeyID; }

    inline STR_MessageData *GetDataMessage() { return & m_RcvMsg; }
    inline int GetCoThread() { return m_iCoThread; }
    inline int GetCoMsgQueue() { return m_iCoMsgQueue; }
    inline void *GetRecvData() { return m_pszRecvData; }

    static void TCleanUpHandler(void *arg );
    static void *CallBack( void *pArg );

    virtual void _routine() { }
    virtual const char *ChildClassName() { return NULL; }

    //pthread_create(&thread,NULL,thread_routine, NULL);
};

#pragma pack(pop)

#endif // CTHREAD_H
