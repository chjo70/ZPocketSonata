#ifndef CURBIT_H
#define CURBIT_H


#include "../Utils/cthread.h"
#include "../Utils/clog.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
// 아래는 이 쓰레드에서 사용하는 클래스를 정의합니다.
//#include "../Utils/cgpio.h"

#define _AXI_DATATEST_          (0xAABBEEF0)

#define URBIT_TIMER             (2*60)                  // 2분 마다 자체점검 수행

#define SNTP_TIMER              (60*60*4)               // 4시간 마다 시간 동기화

/**
 *
 * @brief	  신호분석 CSC의 자체점검을 담당합니다.
 * @details	  신호분석 연동 제어 기능을 수행한다
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-01-16 10:54:00
 * @warning
 *
 */
class CUrBit : public CThread
{
private:
    int m_nBoardID;																	///< 보드 ID 입니다.

    LogType m_enLogType;

    unsigned int m_uiCoURBITTimer;

#ifdef __ZYNQ_BOARD__
    CGPIO m_theGPIO;
#endif

    STR_BIT m_stBIT;

    //UNI_ES_IBIT m_stESIbit;														///< 초기자체점검 결과 저장소 입니다.
    //STR_ES_CBIT m_stESCbit;														///< 연속자체점검 결과 저장소 입니다.

    std::string m_strSQLiteFileName;
    std::string m_strSQLiteFolder;

public:
    STR_MessageData *m_pMsg;														///< 수신 메시지 데이터를 임시 저장하기 위한 저장소 입니다.
    UNI_LAN_DATA *m_pLanData;                                                       ///<

private:
    void Init();																	///< 메모리를 할당하고 변수를 초기화한다.
    void InitHW();																	///< SBC 및 관련 CCA 구성품들을 초기화 합니다.

    void RunIBit( bool bCGIRunning );												///< 초기 자체점검을 수행합니다.
    void RunCBit( bool bCGIRunning );												///< 연속 자체점검을 수행합니다.
    void RunUBit( bool bCGIRunning );												///< 장치 자체점검을 수행합니다.
    void InitIBit();

    void RunTimer();

    void CheckSBCTemp();
    void CheckTasks();
    void CheckDatabase();

#ifdef __ZYNQ_BOARD__
    // 모듈 자체점검 함수
    bool RunAXIBusBIT();
#endif

public:
    CUrBit( int iKeyId, const char *pClassName=NULL, bool bArrayLanData=false );			///< 초기 멤버 변수값 등을 설정하는 객체 생성자 입니다.
    virtual ~CUrBit();																///< 종료 메시지와 메모리 해지를 처리하는 객체 소먈자 입니다.

    //THREAD_STANDARD_FUNCTION( CUrBit );

    void Run( key_t key=IPC_PRIVATE );												///< CThread 클래스의 Run() 함수를 호출하여 쓰레드를 생성하게 합니다.

    void _routine();														///< 쓰레드에서 서버 또는 클라이언트를 실행하게 한다.
    const char *GetThreadName() { return m_szThreadName; }						///< 쓰레드명을 리턴합니다.
    STR_MessageData *GetParentMessage() { return m_pMsg; }                  ///< 메시지 데이터를 리턴 합니다.

};

#endif // CURBIT_H
