#ifndef CARRAYMSGDATA_H
#define CARRAYMSGDATA_H


#define SIZE_OF_MSGDATA_ARRAY           (32)            // 128 -> 64

#define ARARAY_MARK_UPPER              (0x4F)
#define ARARAY_MARK_LOWER              (0xF4)

// 랜 데이터 비교 횟수 이후 에러 통보
#define MAX_TRY_MARK                    (20)

class CArrayMsgData
{
private:
    unsigned char m_ucPushIndex;
    unsigned char m_ucPopIndex;

    bool m_bArrayLanData;

    unsigned char *m_pszArray[SIZE_OF_MSGDATA_ARRAY];

public:
    CArrayMsgData( bool bArrayLanData );
    virtual ~CArrayMsgData();

    int PushLanData( void *pData, unsigned int uiLength );
    void PopLanData( void *pData, int iIndex, unsigned int uiLength );

    virtual void Sleep( unsigned int mssleep )=0;
    virtual char *GetThreadName()=0;

    virtual void SendTaskMngr( unsigned int uiErrorCode, const char *pszThreadName=NULL )=0;

private:
    void Alloc();
    void Free();
    void SetMark( int iIndex );

public:
    void Init();


};

#endif // CARRAYMSGDATA_H
