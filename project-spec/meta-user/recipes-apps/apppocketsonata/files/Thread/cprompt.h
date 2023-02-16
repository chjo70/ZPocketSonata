#ifndef CPROMPT_H
#define CPROMPT_H

//#include "../Utils/clog.h"

//#include "../Include/system.h"
#include "../Utils/cthread.h"

#define NOOFOWNCMDS             (8)



class CPrompt : public CThread
{
private:
    static CPrompt *m_pInstance;
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
    CPrompt( int iKeyId, char *pClassName=NULL, bool bArrayLanData=false );
    virtual ~CPrompt();

    THREAD_STANDARD_FUNCTION( CPrompt )

};


#define PROMPT     CPrompt::GetInstance()

#endif // CPROMPT_H
