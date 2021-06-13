#include <stdio.h>

#ifdef __linux__
#include <termios.h>
#endif

#include <unistd.h>
#include <ctype.h>

#include "cprompt.h"
#include "../Utils/clog.h"
#include "curbit.h"
#include "ctaskmngr.h"

#ifdef _READLINE_
//#include <curses.h>
//#include <term.h>
//#include <readline/readline.h>
//#include <readline/history.h>

#include <readline/readline.h>
#include <readline/history.h>
#else

#endif

#define _DEBUG_

#define MAX_LIST        (100)
#define MAX_KETLINE     (1000)


// Clearing the shell using escape sequences
#define clear() printf("\033[H\033[J")

char CPrompt::m_szListOfOwnCmds[NOOFOWNCMDS][50] = { "urbit",
                                                     "md",
                                                     "mm",
                                                     "cls",
                                                     "setenv",
                                                     "help",
                                                     "quit",
                                                     "bye"
                                                     } ;

enum enCommand {
    // 타겟 명령어
    enURBIT=1,

    // 콘솔 명령어
    enMemoryDump,
    enMemoryModify,
    enClearScreen,
    enSetEnv,
    enHelp,
    enQuit,
    enBye
} ;


// 클래스 내의 정적 멤버변수 값 정의

CPrompt* CPrompt::m_pInstance = nullptr;

CPrompt::CPrompt( int iKeyId, char *pClassName, bool bArrayLanData ) : CThread( iKeyId, pClassName, bArrayLanData )
{
   LOGENTRY;

   Init();

}

/**
 * @brief CPrompt::~CPrompt
 */
CPrompt::~CPrompt()
{

}

/**
 * @brief CPrompt::Run
 * @param key
 */
void CPrompt::Run(key_t key)
{
    LOGENTRY;

    CThread::Run( key );
}


/**
 * @brief CPrompt::_routine
 */
void CPrompt::_routine()
{
    int execFlag = 0;
    char inputString[MAX_KETLINE];
    char *parsedArgs[MAX_LIST], *parsedArgsPiped[MAX_LIST];

    LOGENTRY;
    //STR_MessageData *pMsg = GetDataMessage();

    while( m_bWhileFlag ) {
        if( takeInput( inputString ) ) {
            continue;
        }

        execFlag = processString( inputString, parsedArgs, parsedArgsPiped );

    }

    LOGMSG( enDebug, "정상적으로 종료 처리 합니다..." );

    PROMPT->Stop();

}

/**
 * @brief CPrompt::Init
 */
void CPrompt::Init()
{
    m_bWhileFlag = true;
    m_uiDumpAddress = 0;
    m_uiModifyAddress = 0;
}

/**
 * @brief CPrompt::takeInput Function to take input
 * @param str
 * @return
 */
int CPrompt::takeInput(char* str)
{
    char *pbuff;

#ifdef _READLINE_
    pbuff = readline( "$> " );
    strcpy( str, pbuff );

#else
    printf( "\n$> " );
    fgets( str, 100, stdin );

#endif

    if (strlen(str) != 0 && str[0] != 0x0a ) {
#ifdef _READLINE_
        add_history( str );
#endif
        return 0;
    } else {
        return 1;
    }

}

// Help command builtin
void CPrompt::openHelp( int iArg )
{
    int i;
    char buffer[100];

    switch( iArg ) {
        case enURBIT :
            puts( "\n urbit [데이터] 데이터 값을 입력으로 URBIT를 수행합니다." );
            puts( "\n\t\t [데이터] 데이터는 숫자 입력이며 0 부터 시작한다." );
            break;

        case enMemoryDump :
            puts( "\n md 시작_어드레스_값 [종료_어드레스_값], [데이터_크기] 형식으로 입력하여 시작 어드레스 값을 시작으로 메모리 값을 16진수로 표시합니다.");
            puts( "\n\t\t 시작_어드레스_값 : 시작 어드레스를 나타낸다.");
            puts( "\n\t\t 종료_어드레스_값 : 종료 어드레스를 나타낸다.");
            puts( "\n\t\t 데이터_크기 : 전시할 비트를 표시하며 1, 2, 4, 8 등으로 정할 수 있다.");
            break;

        case enMemoryModify :
            puts( "\n mm 시작_어드레스_값, [데이터_크기] 형식으로 입력하여 시작 어드레스 값을 시작으로 메모리 값을 16진수로 표시합니다.");
            puts( "\n\t\t 시작_어드레스_값 : 시작 어드레스를 나타낸다.");
            puts( "\n\t\t 데이터_크기 : 전시할 비트를 표시하며 1, 2, 4, 8 등으로 정할 수 있다.");
            break;

        case enClearScreen :
            puts( "\n cls 콘솔의 화면을 깨끗하게 지웁니다.");
            break;

        default :
            puts("\n 디버깅용 프로그램 쉘 입니다. 백 그라운드에서는 다른 프로세스가 실행되어 정상 운용이 되며 이 쉘을 통해서 간단 명령을 수행할 수 있습니다."
                "\n 2020년 Copyright(c) @ 조철희"
                "\n\nList of Commands supported:" );
            for( i=0 ; i < NOOFOWNCMDS ; ++i ) {
                sprintf( buffer, ">%s", m_szListOfOwnCmds[i] );
                puts( buffer );
            }
            break;

    }

    return;
}

/**
 * @brief Function to execute builtin commands
 * @param parsed
 * @return
 */
int CPrompt::ownCmdHandler(char** parsed)
{
    int i, switchOwnArg = 0;
    char* username;

    UINT uiData, uiData2;

    for (i = 0; i < NOOFOWNCMDS; i++) {
        if (strcmp(parsed[0], m_szListOfOwnCmds[i]) == 0) {
            switchOwnArg = i + 1;
            break;
        }
    }

    switch (switchOwnArg) {
    case enURBIT :
        if( parsed[1] == 0 ) {
            uiData = 0;
        }
        else {
            uiData = atoi( parsed[1] );
        }
        URBit( uiData );
        break;

    case enMemoryDump :
        if( parsed[1] == 0 && m_uiDumpAddress == 0 ) {
            openHelp( switchOwnArg );
        }
        else {
            if( parsed[1] != NULL ) {
                uiData = atoi( parsed[1] );
            }
            else {
                uiData = m_uiDumpAddress;
            }
            MemoryDump( uiData );
        }
        break;

    case enMemoryModify :
        if( parsed[1] == 0 ) {
            openHelp( switchOwnArg );
        }
        else {
            if( parsed[1] != NULL ) {
                uiData = atoi( parsed[1] );
            }
            else {
                uiData = m_uiModifyAddress;
            }

            if( parsed[2] != NULL ) {
                uiData2 = atoi( parsed[2] );
            }
            else {
                uiData2 = 1;
            }
            MemoryModify( uiData, uiData2 );
        }
        return 1;
    case enClearScreen :
        if( parsed[1] != 0 ) {
            openHelp( switchOwnArg );
        }
        else {
            clear();
        }
        break;

    case enHelp :
        openHelp();
        return 1;

    case enSetEnv :
        username = getenv("USER");
        printf("\nHello %s.\nMind that this is "
            "not a place to play around."
            "\nUse help to know more..\n",
            username);
        return 1;

    case enQuit :
    case enBye :
        printf( "\n program exit...\n" );
        m_bWhileFlag = false;
        QMsgSnd( TMNGR->GetKeyId(), enTHREAD_REQ_SHUTDOWN );
        break;

    default:
        openHelp();
        break;
    }

    return 0;
}

// function for finding pipe
int CPrompt::parsePipe(char* str, char** strpiped)
{
#ifdef __linux__
    int i;
    for (i = 0; i < 2; i++) {
        strpiped[i] = strsep(&str, "|");
        if (strpiped[i] == NULL)
            break;
    }

    if (strpiped[1] == NULL)
        return 0; // returns zero if no pipe is found.
    else {
        return 1;
    }
#else
    return 0;

#endif

}

// function for parsing command words
void CPrompt::parseSpace(char* str, char** parsed)
{
#ifdef __linux__
    int i;

    for (i = 0; i < MAX_LIST; i++) {
        parsed[i] = strsep(&str, " ");

        if (parsed[i] == NULL)
            break;
        if (strlen(parsed[i]) == 0)
            i--;
    }
#endif

}

/**
 * @brief CPrompt::processString
 * @param str
 * @param parsed
 * @param parsedpipe
 * @return
 */
int CPrompt::processString(char* str, char** parsed, char** parsedpipe)
{
    char* strpiped[2];
    int piped = 0;

    piped = parsePipe(str, strpiped);

    if (piped) {
        parseSpace(strpiped[0], parsed);
        parseSpace(strpiped[1], parsedpipe);

    } else {

        parseSpace(str, parsed);
    }

    if (ownCmdHandler(parsed))
        return 0;
    else
        return 1 + piped;
}

/**
 * @brief CPrompt::MemoryDump
 * @param uiAddress
 */
void CPrompt::MemoryDump( UINT uiStartAddress, UINT uiEndAddress )
{
    int i, j;
    char *pAddress, *pData;

    int iLines;

#ifdef _DEBUG_
    char *pBuffer;
    pBuffer = pAddress = (char *) malloc( 16 * 1000 );
#else
    pAddress = (char *) uiStartAddress;
#endif

    if( uiEndAddress == 0 ) {
        uiEndAddress = uiStartAddress + ( 16 * 10 );
    }

    iLines = ( uiEndAddress - uiStartAddress ) / 16;
    printf( "\n Address\tData\t\t\t\t\tASCII" );
    for( i=0 ; i < iLines ; ++i ) {
        printf( "\n %08p" , (void *) pAddress );
        pData = pAddress;
        for( j=0 ; j < 16 ; ++j ) {
            printf( "%02x ", *pData++ );
        }
        pData = pAddress;
        for( j=0 ; j < 16 ; ++j ) {
            if( isprint( *pData ) )
                printf( "%1c", *pData++ );
            else
                printf( " " );
        }

        pAddress += 16;
    }

    m_uiDumpAddress = uiEndAddress + 1;

#ifdef _DEBUG_
    free( pBuffer );
#endif

}

/**
 * @brief CPrompt::MemoryModify
 * @param uiStartAddress
 * @param uiDataType
 */
void CPrompt::MemoryModify( UINT uiStartAddress, UINT uiDataType )
{
    char *pBuf;
    char *pAddress, *pData;

#ifdef _DEBUG_
    char *pBuffer;
    pBuffer = pAddress = (char *) malloc( 16 * 1000 );
#else
    pAddress = (char *) uiStartAddress;
#endif

    do {
        printf( "%08p %02x" , pAddress, *pAddress );
#ifdef _READLINE_
        pBuf = readline( " " );
#else
        fgets( pBuf, 100, stdin );
#endif

        if( *pBuf == '.' ) {
            break;
        }
        else if( *pBuf != 0 ) {
            // *pAddress = atoi( *pBuf );
            ++ pAddress;
            //printf( "\n" );
        }

    }
    while( true );

#ifdef _DEBUG_
    free( pBuffer );
#endif

}

/**
 * @brief CPrompt::URBit
 * @param uiData
 */
void CPrompt::URBit( UINT uiData )
{
    UINT *puiUnit;
    STR_MessageData sndMsg;

    puiUnit = (UINT *) & sndMsg.x.szData[0];

    sndMsg.mtype = 1;
    sndMsg.uiOpCode = enREQ_URBIT;
    sndMsg.iSocket = 0;

    *puiUnit = uiData;

#ifdef __linux__
    if( msgsnd( URBIT->GetKeyId(), (void *)& sndMsg, sizeof(STR_MessageData)-sizeof(long), IPC_NOWAIT) < 0 ) {
        perror( "msgsnd 실패" );
    }
    else {
        // DisplayMsg( & sndMsg );

    }
#endif

}
