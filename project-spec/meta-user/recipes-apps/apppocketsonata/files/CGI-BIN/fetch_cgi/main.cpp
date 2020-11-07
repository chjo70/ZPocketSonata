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


#include "../../Thread/ccgi.h"

#include "../../Anal/INC/system.h"

#include "../Qdecoder/qDecoder.h"

#include "../../MinIni/minIni.h"

void PreviousPage();

key_t gstMsgKeyID=0;

int main(int argc, char *argv[])
{
    int iValue;
    char *value;

    char szLogDirectory[100];
    char szINIDirectory[100];

    STR_MessageData sndMsg;

    minIni m_theMinIni;

    // 로그는 현재 홈 디렉토리에 저장한다.
    strcpy( szLogDirectory, QDECODER_LOG_FOLDER );
    strcat( szLogDirectory, QDECODER_LOG_FILENAME );
    qErrorLog( szLogDirectory );

    // INI 파일 로딩하기
    strcpy( szINIDirectory, INI_FOLDER /* getenv("HOME") */ );
    strcat( szINIDirectory, INI_FILENAME );

    m_theMinIni.setfilename( szINIDirectory );

    qContentType( "text/html" );
    qDecoder();

    // 최소 펄스 수
    if(!(value = qValue("query_minpulse"))) value = "";
    //qErrorPrint( "value = %s, %d" , value, atoi(value) );
    if( true != m_theMinIni.put( "ANAL" , "MIN_ANALPULSE" , atoi(value) ) ) {
        qErrorPrint( "INI 파일 권한을 확인해 주세요... 이 파일의 other 사용자 권한을 write 하게 해주세요." );
    }

    sndMsg.uiOpCode = enCGI_FETCH;
    sndMsg.uiDataLength = 0;
    if( msgsnd( gstMsgKeyID, (void *) & sndMsg, sizeof(STR_MessageData)-sizeof(long), IPC_NOWAIT) < 0 ) {
        qErrorPrint( "메시지 송신 에러!!!" );
    }

    PreviousPage();

    qErrorPrint( "EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE" );

    qFree();

    return 0;
}

void PreviousPage()
{
  printf( "<html><head>" );
  printf( "<script language='JavaScript'>\n");
  printf( "setTimeout(function() {" );
  printf( "history.back()} , 500);" );
  printf( "</script>\n" );
  printf( "</head></html>" );

}
