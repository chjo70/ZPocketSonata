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

#include "../../System/csysconfig.h"

#ifndef S_DEFFILEMODE
#define S_DEFFILEMODE   (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)
#endif


void PreviousPage();

key_t gstMsgKeyID=_MSG_ZCGI_KEY;

int main(int argc, char *argv[])
{
    int iValue, i;
    char *pValue;

    float fValue;

    char szLogDirectory[100];
    char szINIDirectory[100];

    char szQuery[100];

    CSharedMemroy *pSharedMemory;
    STR_SYSCONFIG strConfig;

    STR_MessageData sndMsg;

    minIni m_theMinIni;

    key_t iMsgKeyID;

    // 공유 메모리 설정
    pSharedMemory = new CSharedMemroy( _SHM_MEMORY_KEY );

    pSharedMemory->copyToLocalMemroy( & strConfig, sizeof(STR_SYSCONFIG) );

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
    if(!(pValue = qValue( (char *) "query_minpulse"))) pValue = 0;
    iValue = atoi(pValue);
    if( true != m_theMinIni.put( "ANAL" , "MIN_ANALPULSE" , iValue ) ) {
        qErrorPrint( "INI 파일 권한을 확인해 주세요... 이 파일의 other 사용자 권한을 write 하게 해주세요." );
    }
    else {
        strConfig.iMinAnalPulse = iValue;
    }
    qErrorPrint( "MIN_ANALPULSE=%d" , iValue );
    printf( "\n MIN_ANALPULSE=%d" , iValue );

    // 신호 삭제 시간
    if(!(pValue = qValue( (char *) "query_deletetime"))) pValue = 0;
    iValue = atoi(pValue);
    if( true != m_theMinIni.put( "ANAL" , "DEFAULT_DELETE_TIMESEC" , iValue ) ) {
        qErrorPrint( "INI 파일 권한을 확인해 주세요... 이 파일의 other 사용자 권한을 write 하게 해주세요." );
    }
    else {
        strConfig.iEmitterDeleteTime = iValue;
    }
    qErrorPrint( "DEFAULT_DELETE_TIMESEC=%d" , iValue );
    printf( "\n DEFAULT_DELETE_TIMESEC=%d" , iValue );

    // 대역
    for( i=1 ; i <= 5 ; ++i ) {
        sprintf( szQuery, "query_band%d" , i );
        if(!(pValue = qValue( (char *) szQuery))) pValue = 0;
        fValue = atof(pValue);

        sprintf( szQuery, "Band%d" , i );
        if( true != m_theMinIni.put( "RXTHRESHOLD" , szQuery , fValue ) ) {
            qErrorPrint( "INI 파일 권한을 확인해 주세요... 이 파일의 other 사용자 권한을 write 하게 해주세요." );
        }
        else {
            strConfig.fRxThreshold[i-1] = fValue;
        }
        qErrorPrint( "Band%d=%.1f" , i, fValue );
        printf( "\n Band%d=%.1f" , i, fValue );
    }

    if( false == pSharedMemory->copyToSharedMemroy( & strConfig ) ) {
        qErrorPrint( "운용 프로그램이 실행되지 않아서 바로 반영은 안 되나 INI 파일을 수정했습니다 !!!" );
        qError( "운용 프로그램이 실행되지 않아서 바로 반영은 안 되나 INI 파일을 수정했습니다 !!!" );
    }

    // 운용 프로그램에게 메시지 전송
    //sndMsg.mtype = 1;
    //sndMsg.uiOpCode = enCGI_FETCH;
    //sndMsg.uiDataLength = 0;
    //iMsgKeyID = msgget( gstMsgKeyID, S_DEFFILEMODE | IPC_CREAT );

    //qErrorPrint( "iMsgKeyID=%d" , iMsgKeyID );
    //if( msgsnd( iMsgKeyID, (void *) & sndMsg, sizeof(STR_MessageData)-sizeof(long), IPC_NOWAIT) < 0 ) {
    //    qErrorPrint( "운용 프로그램이 실행되지 않아서 바로 반영은 안 되나 INI 파일을 수정했습니다 !!!" );
    //    qError( "운용 프로그램이 실행되지 않아서 바로 반영은 안 되나 INI 파일을 수정했습니다 !!!" );
    //}

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
