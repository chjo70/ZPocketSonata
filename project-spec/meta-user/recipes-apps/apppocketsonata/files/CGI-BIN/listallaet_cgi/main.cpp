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

#include "../Qdecoder/qDecoder.h"

#include "../../Anal/Collect/ccollectbank/ccollectbank.h"
#include "../../Anal/Collect/DataFile/DataFile.h"

#include "../../System/csysconfig.h"


#define TABLE_COLS      (11)
char szTableCols[TABLE_COLS][30] = { "번호", "최초 접촉", "최근 접촉", "위협도", "ELNOT", "신호형태", "방위[도]", "주파수[MHz]", "PRI[us]", "펄스폭[ns]", "채널 세기[dBm]" } ;


void PreviousPage();

int main(int argc, char *argv[])
{
    int i, j;
    bool bShared;

    char szLogDirectory[100];

    STR_SYSCONFIG strConfig;

    CSharedMemroy *pSharedMemory;

    // 공유 메모리 설정
    pSharedMemory = new CSharedMemroy( _SHM_MEMORY_KEY );

    bShared = pSharedMemory->copyToLocalMemroy( & strConfig, sizeof(STR_SYSCONFIG) );

    // 로그는 현재 홈 디렉토리에 저장한다.
    strcpy( szLogDirectory, QDECODER_LOG_FOLDER );
    strcat( szLogDirectory, QDECODER_LOG_FILENAME );
    qErrorLog( szLogDirectory );

    qErrorPrint( "=======================================" );
    qDecoderSetUploadBase( QDECODER_UPLOAD_FOLDER, 24 * 60 * 60 );

    qDecoder();
    qContentType( "text/html" );

    // 헤더 파일을 전시한다. 아래 파일은 support.html 에 있는
    qCatFile( (char *) "../support.header" );

    if( bShared == true ) {
        printf( "<p style=\"line-height:150%; margin-top:0; margin-bottom:0;\"</p>" );

        ///////////////////////////////////////////////////////////////////////////////////////////////////
        printf( "<p align=\"center\"><b>활성 방사체/빔 정보(1)</b></p>" );
        printf( "<table class=\"table-style-two\" align=\"center\">" );

        // 테이블 헤더
        printf( "<thead><tr>" );
        for( j=0 ; j < TABLE_COLS ; ++j ) {
            printf( "<th><p align=\"center\">%s</th>", szTableCols[j] );
        }
        printf( "</tr></thead>" );

        // 채널 상태 전시
        printf( "<tbody>" );


        printf( "</tr></thead></table>" );

        // 재시도 자동 타이머를 설정하는화면 이다.
        qCatFile( (char *) "../support.refresh" );
    }


    //PreviousPage();

    qErrorPrint( "EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE" );

    qFree();

    delete pSharedMemory;

    return 0;
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
