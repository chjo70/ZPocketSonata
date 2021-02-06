#include <string.h>
#include <memory.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>

#ifdef ENABLE_FASTCGI
#include "fcgi_stdio.h"
#else
#include <stdio.h>
#endif
#include <stdlib.h>
#include <stdbool.h>


#include "../../Include/system.h"

#include "../../Anal/INC/system.h"

#include "../../Thread/ccgi.h"

#include "../Qdecoder/qDecoder.h"

enum EN_BIT_CASE {
    enIBIT = 0,
    enCBIT,
    enSBIT,
    enUBIT,

    enMAX_BIT
};

int g_iKeyId=1;
key_t gstMsgKeyID=0;
bool m_bMainLoop=true;

#define S_DEFFILEMODE   (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

/**
 * @brief StrCmp
 * @param pszCompare
 * @return
 */
int StrCmp( char *pszCompare )
{
    int i, iSwitch=-1;

    const char szCompared[enMAX_BIT][100] = { "IBIT", "CBIT", "SBIT", "UBIT" } ;

    for( i=0 ; i < enMAX_BIT ; ++i ) {
        if( strcmp( szCompared[i], pszCompare ) == 0 ) {
            iSwitch = i;
            break;
        }
    }

    return iSwitch;

}


/**
 * @brief DownloadFile
 * @param enDownloadCase
 */
void RunBIT( int iSwitch )
{
    char szSQLiteFileName[100];

    STR_MessageData sndMsg;

    sndMsg.mtype = 1;
    sndMsg.iSocket = 0;
    sndMsg.uiArrayLength = 0;
    sndMsg.iArrayIndex = -1;

    qErrorPrint( "RunBIT[%d]" , iSwitch );
    printf( "RunBIT[%d]" , iSwitch );
    switch( (EN_BIT_CASE) iSwitch ) {
        case enIBIT :
        case enCBIT :
        case enUBIT :
            sndMsg.uiOpCode = enCGI_REQ_IBIT;
            sndMsg.uiDataLength = sizeof(UNI_ES_IBIT);
            if( msgsnd( gstMsgKeyID, (void *) & sndMsg, sizeof(STR_MessageData)-sizeof(long), IPC_NOWAIT) < 0 ) {
                qError( "msgsnd 실패" );
                m_bMainLoop = false;
                qErrorPrint( "메시지 송신 에러!!!" );
            }
            else {
                qErrorPrint( "정상적으로 메시지 송신!!!" );
            }
            break;

        default :
            qError( "아직 미지원 되고 있습니다. 조만간 구현해 놓을께요.~~~" );
            m_bMainLoop = false;
            break;
    }
}

int main(int argc, char *argv[])
{
    int iSwitch, iDelay;

    char *pList;

    char szLogDirectory[100];

    // 로그는 현재 홈 디렉토리에 저장한다.
    strcpy( szLogDirectory, QDECODER_LOG_FOLDER );
    strcat( szLogDirectory, QDECODER_LOG_FILENAME );
    qErrorLog( szLogDirectory );

    qDecoderSetUploadBase( "/home/chjo70", 24 * 60 * 60 );

    qErrorPrint( "CGI Process Start ========================================" );

    if( ( pList = qValueFirst(  "formradio" )) == NULL ) {
        //qErrorPrint( "자체점검할 항목을 선택하지 않았습니다." );

        //qError( "자체점검할 항목을 선택하지 않았습니다." );
        //PreviousPage();
    }
    else {
        qContentType( "text/html" );

        CGI->Run( _MSG_CGI_KEY );

        gstMsgKeyID = msgget( _MSG_ZCGI_KEY, S_DEFFILEMODE | IPC_CREAT );

        iSwitch = StrCmp( pList );

        RunBIT( iSwitch );

    }

    qErrorPrint( "EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE" );

    qFree();

    return 0;
}
