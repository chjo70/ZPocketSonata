#ifndef CURBIT_H
#define CURBIT_H


#include "../Include/system.h"
#include "../Utils/cthread.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
// 아래는 이 쓰레드에서 사용하는 클래스를 정의합니다.
#include "../Utils/cgpio.h"

#define _AXI_DATATEST_          (0xAABBEEF0)

/**
 * @brief 자체점검 쓰레드 입니다.
 */
class CUrBit : public CThread
{
private:
    int m_nBoardID;

#ifdef __ZYNQ_BOARD__
    CGPIO m_theGPIO;
#endif

    UNI_ES_IBIT m_stESIbit;
    STR_ES_CBIT m_stESCbit;

public:
    static CUrBit *m_pInstance;

    STR_MessageData *m_pMsg;

private:
    void Init();
    void InitHW();

    void RunIBit( bool bCGIRunning );
    void RunCBit( bool bCGIRunning );
    void RunUBit( bool bCGIRunning );
    void InitIBit();

#ifdef __ZYNQ_BOARD__
    // 모듈 자체점검 함수
    bool RunAXIBusBIT();
#endif

public:
    CUrBit( int iKeyId, char *pClassName=NULL, bool bArrayLanData=false );
    virtual ~CUrBit();

    THREAD_STANDARD_FUNCTION( CUrBit )
};

#define URBIT     CUrBit::GetInstance()

#endif // CURBIT_H
