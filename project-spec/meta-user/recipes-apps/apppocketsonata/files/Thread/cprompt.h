#ifndef CPROMPT_H
#define CPROMPT_H

#include "../Include/system.h"
#include "../Utils/cthread.h"

#define NOOFOWNCMDS             (8)



class CPrompt : public CThread
{
private:
    static CPrompt *pInstance;
    //static char m_szClassName[LENGTH_OF_CLASSNAME];
    bool m_bWhileFlag;

    static char m_szListOfOwnCmds[NOOFOWNCMDS][50];

    UINT m_uiDumpAddress;
    UINT m_uiModifyAddress;


private:
    void Init();

    int takeInput(char* str);
    void openHelp( int iArg=-1 );
    int ownCmdHandler(char** parsed);
    void parseSpace(char* str, char** parsed);
    int parsePipe(char* str, char** strpiped);
    int processString(char* str, char** parsed, char** parsedpipe);
    int CPromptparsePipe(char* str, char** strpiped);


    // 내부 명령어 처리
    void MemoryDump( UINT uiStartAddress, UINT uiEndAddress=0 );
    void MemoryModify( UINT uiStartAddress, UINT uiDataType=1 );

    // 외부 명령어 처리
    void URBit( UINT uiData );

public:
    CPrompt( int iKeyId, char *pClassName=NULL );
    virtual ~CPrompt();

    void ReleaseInstance();

    virtual void _routine();
    virtual const char *ChildClassName() { return m_szClassName; }

    static CPrompt* GetInstance()
    { // 게으른 초기화
        if(pInstance == NULL) {
            pInstance = new CPrompt( g_iKeyId++, (char *)"CPrompt" );
        }
        return pInstance;
    }


};


#define PROMPT     CPrompt::GetInstance()

#endif // CPROMPT_H
