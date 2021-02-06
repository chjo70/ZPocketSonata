#include <string.h>
#include <memory.h>
#include <pwd.h>
#include <sys/types.h>

#ifdef ENABLE_FASTCGI
#include "fcgi_stdio.h"
#else
#include <stdio.h>
#endif

#include <stdlib.h>
#include <stdbool.h>

#define _MAIN_GLOBALS_

#include "../../Anal/INC/system.h"

#include "../../Thread/ccgi.h"

#include "../Qdecoder/qDecoder.h"

#include "../../Anal/Collect/ccollectbank/ccollectbank.h"
#include "../../Anal/Collect/DataFile/DataFile.h"

#include "../../System/csysconfig.h"

#define S_DEFFILEMODE   (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

#define TABLE_COLS      (12)
char szTableCols[TABLE_COLS][30] = { "번호", "사용 여부", "모드", "수집개수", "누적 개수/회수", "채널 수집개수", "채널 수집시간[초]", "채널 방위[도]", "채널 주파수[MHz]", "채널 펄스폭[ns]", "채널 세기[dBm]", "빔 번호" } ;

#define MAX_TITLE      (4)
char szTitle[MAX_TITLE][30] = { "탐지", "추적", "스캔", "사용자" } ;
int iCoChannels[MAX_TITLE] = { DETECT_CHANNEL, TRACK_CHANNEL, SCAN_CHANNEL, USER_CHANNEL } ;


key_t gstSndMsgKeyID=0;
key_t gstRcvMsgKeyID=0;

CSharedMemroy *gstpSharedMemory;

STR_SYSCONFIG gstrConfig;

void PreviousPage();
void SendReqSpectrumData();
void InitReceivedMsg( key_t key );
void WaitUntilReceivedMsg();

int main(int argc, char *argv[])
{
    int i;
    bool bShared;

    char szLogDirectory[100];

    // 공유 메모리 설정
    gstpSharedMemory = new CSharedMemroy( _SHM_MEMORY_KEY );

    bShared = gstpSharedMemory->copyToLocalMemroy( & gstrConfig, sizeof(STR_SYSCONFIG) );

    // 로그는 현재 홈 디렉토리에 저장한다.
    strcpy( szLogDirectory, QDECODER_LOG_FOLDER );
    strcat( szLogDirectory, QDECODER_LOG_FILENAME );
    qErrorLog( szLogDirectory );

    qErrorPrint( "CGI Process Start ========================================" );

    qDecoder();
    qContentType( "text/html" );

    gstSndMsgKeyID = msgget( _MSG_ZCGI_KEY, S_DEFFILEMODE | IPC_CREAT );

    InitReceivedMsg( _MSG_CGI_KEY );

    if( gstSndMsgKeyID != -1 && gstRcvMsgKeyID != -1 ) {
        // CGI->Run( _MSG_CGI_KEY );

        SendReqSpectrumData();
        WaitUntilReceivedMsg();

        // 헤더 파일을 전시한다. 아래 파일은 support.html 에 있는
        qCatFile( (char *) "../support.header.qDecoder" );

        // 헤더 파일을 전시한다. 아래 파일은 support.html 에 있는
        qCatFile( (char *) "../chart.header.qDecoder" );

        if( bShared == true ) {
            float fXValue;

            struct tm *pTm;
            time_t timer;

            timer = time( NULL );
            pTm = localtime( &timer );

            printf( "<body>\r\n" );
            printf( "<div style=\"width:100%;\"><canvas id=\"canvas\"></canvas></div>\r\n" );
            printf( "<script>\r\n" );
            printf( "   var config = {\r\n" );
            printf( "           type: 'line',\r\n" );
            printf( "           data: {\r\n" );

            //printf( "               labels: ['0.5', '1.0', '1.5', '2', '2.5', '3.0', '3.5', '4.0'],\r\n" );
            printf( "               labels: [" );
            for( fXValue=(2*MIN_FREQ_MHZ+COLHISTO_WIDTH_MHZ)/2000. ; fXValue < (float) ( MAX_FREQ_MHZ-(COLHISTO_WIDTH_MHZ) ) / 1000. ; fXValue += (COLHISTO_WIDTH_MHZ/1000.) ) {
                printf( "'%.2f'," , fXValue );
            }
            printf( "'%.1f'],\r\n" , fXValue );

            printf( "               datasets: [{\r\n" );
            printf( "                   label: '최근',\r\n" );
            printf( "                   steppedLine: 'middle',\r\n" );
            printf( "                   fill: false,\r\n" );
            printf( "                   backgroundColor: window.chartColors.blue,\r\n" );
            printf( "                   borderColor: window.chartColors.blue,\r\n" );

            //printf( "                   data: [0, 10, 10, 10, 100, 1,0]\r\n" );
            printf( "               data: [" );
            unsigned char (*pSharedColHisto)[COLHISTO_CELLS] = gstrConfig.ucColHisto;
            for( i=0 ; i < COLHISTO_CELLS-1 ; ++i ) {
                printf( "'%d'," , pSharedColHisto[0][i] );
            }
            printf( "'%d'],\r\n" , pSharedColHisto[0][i] );

            printf( "               }]\r\n" );
            printf( "           },\r\n" );

            printf( "           options: {\r\n" );
            printf( "               title: {\r\n" );
            printf( "                   display: true,\r\n" );
            printf( "                   text: '탐지 스펙트럼(%02d시 %02d분 %02d초)'\r\n", pTm->tm_hour, pTm->tm_min, pTm->tm_sec );
            printf( "               },\r\n" );

            qCatFile( (char *) "../chart.option.qDecoder" );

            printf( "       };\r\n" );

            qCatFile( (char *) "../chart.onload.qDecoder" );

            printf( "</script>\r\n" );
            printf( "</body>\r\n" );
        }
        else {

        }

        //CGI->ReleaseInstance();
    }
    else {
        qError( "운용 소프트웨어가 실해되지 않았습니다." );
    }


    //PreviousPage();

    qErrorPrint( "CGI Process End =========================================" );

    qFree();

    delete gstpSharedMemory;

    return 0;
}

/**
 * @brief SendReqSpectrumData
 */
void SendReqSpectrumData()
{
    STR_MessageData sndMsg;

    sndMsg.mtype = 1;
    sndMsg.iSocket = 0;
    sndMsg.uiArrayLength = 0;
    sndMsg.iArrayIndex = -1;

    sndMsg.uiOpCode = enCGI_REQ_SPECTRUM;
    sndMsg.uiDataLength = 0;
    if( msgsnd( gstSndMsgKeyID, (void *) & sndMsg, sizeof(STR_MessageData)-sizeof(long), IPC_NOWAIT) < 0 ) {
        qError( "msgsnd 실패" );
        qErrorPrint( "메시지 송신 에러!!!" );
    }
    else {
        qErrorPrint( "정상적으로 메시지 송신!!!" );
    }
}

void WaitUntilReceivedMsg()
{
    STR_MessageData strRcvMsg;

    //int iMsgRcv = msgrcv( gstRcvMsgKeyID, (void *) & strRcvMsg, sizeof(STR_MessageData)-sizeof(long), 1 /* (1 >> 1)*/, iFlag );

    sleep( 1 );
    gstpSharedMemory->copyToLocalMemroy( & gstrConfig, sizeof(STR_SYSCONFIG) );

}

void InitReceivedMsg( key_t key )
{
    gstRcvMsgKeyID = msgget( key, S_DEFFILEMODE | IPC_CREAT );
    if (gstRcvMsgKeyID != -1 ) {
        msgctl( gstRcvMsgKeyID, IPC_RMID, 0 );
    }

    gstRcvMsgKeyID = msgget( key, S_DEFFILEMODE | IPC_CREAT );
    if (gstRcvMsgKeyID == -1 ) {
        perror("msgget error : ");
        exit(0);
    }
    else {
        LOGMSG1( enDebug, "\t 큐 ID[%d]를 생성합니다." , gstRcvMsgKeyID );
    }
}

void PreviousPage()
{
    printf( "<html><head>" );
    printf( "<script language='JavaScript'>\n");
    printf( "setTimeout(function() {" );
    printf( "history.back()} , 100);" );
    printf( "</script>\n" );
    printf( "</head></html>" );

}
