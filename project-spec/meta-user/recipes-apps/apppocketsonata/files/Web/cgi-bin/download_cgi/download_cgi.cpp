#include <string.h>
#include <memory.h>

#ifdef ENABLE_FASTCGI
#include "fcgi_stdio.h"
#else
#include <stdio.h>
#endif
#include <stdlib.h>
#include <stdbool.h>


#include "../../../Anal/INC/system.h"

#include "../Qdecoder/qDecoder.h"

enum EN_DOWNLOAD_CASE {
    enCEDEOB = 0,
    enRAWDATA,
    enLOG,
    enSCREEN_DUMP,
    enINI,

    enMAX_DOWNLOAD
};

/**
 * @brief StrCmp
 * @param pszCompare
 * @return
 */
int StrCmp( char *pszCompare )
{
    int i, iSwitch=-1;

    const char szCompared[enMAX_DOWNLOAD][100] = { "CEDEOB", "RAWDATA", "LOG", "SCREEN_DUMP", "INI" } ;

    for( i=0 ; i < enMAX_DOWNLOAD ; ++i ) {
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
void DownloadFile( int iSwitch )
{
    char szSQLiteFileName[100];

    qErrorPrint( "DownloadFile[%d]" , iSwitch );
    switch( (EN_DOWNLOAD_CASE) iSwitch ) {
        case enCEDEOB :
            strcpy( szSQLiteFileName, "/home/chjo70" /* getenv("HOME") */ );
            strcat( szSQLiteFileName, CEDEOB_SQLITE_FILENAME );

            qErrorPrint( "DownloadFile[%s]" , szSQLiteFileName );
            qDownload( szSQLiteFileName );

            break;

        default :
            qError( "아직 미지원 되고 있습니다. 조만간 구현해 놓을께요.~~~" );
            break;
    }
}


int main(int argc, char *argv[])
{
    int iSwitch;

    char *pList;

    char szLogDirectory[100];

    // 로그는 현재 홈 디렉토리에 저장한다.
    strcpy( szLogDirectory, /* getenv("HOME")*/ "/var/log" );
    strcat( szLogDirectory, QDECODER_LOG_FILENAME );
    qErrorLog( szLogDirectory );

    if( ( pList = qValueFirst(  "formradio" )) == NULL ) {
        qError( "다운로드할 항목이 없습니다. 확인해 주세요." );
        //PreviousPage();
    }
    else {
        iSwitch = StrCmp( pList );

        DownloadFile( iSwitch );


/*
        if( strcmp( pList, "PDW" ) == 0 ) {
            Download( "PRGDISK:/col_all.pdw", "수신 PDW가 없어서 다운로드가 안 됩니다. 잠시 후에 재시도 하세요." );
        }
        else if( strcmp( pList, "UDF" ) == 0 ) {
            Download( UDF_FILE, "UDF가 아직 올라가지 않았습니다. 파일이 존재하지 않아서 다운로드가 안 됩니다." );
        }
        else if( strcmp( pList, "LOG" ) == 0 ) {
            Download( theCtrlCMDS->GetLogFilename(), "로깅 파일이 아직 생성하지 않았습니다. 잠시 후에 재시도 하세요." );
        }
        else if( strcmp( pList, "DUMP" ) == 0 ) {
            printf( "\n******************************************************" );
            theLogDebug->MakeScreenBuffer( SCREEN_BUFFER_TEMP_LOG_FILENAME );
            Download( SCREEN_BUFFER_TEMP_LOG_FILENAME, "덤프 파일이 없거나 메모리에 문제가 있을 수 있습니다." );
            unlink( SCREEN_BUFFER_TEMP_LOG_FILENAME );
        }
        else if( strcmp( pList, "OFF_DUMP" ) == 0 ) {
            Download( SCREEN_BUFFER_LOG_FILENAME, "덤프 파일이 없거나 메모리에 문제가 있을 수 있습니다." );
        }
        else if( strcmp( pList, "INI" ) == 0 ) {
            Download( INI_FILE, "시스템이 초기화가 되어 다운로드할 초기화 파일이 없습니다. 잠시 후에 재시도 하세요." );
        }
*/

    }

    /*
    while (pReq->getnext(pReq, &obj, "formradio", false) == true) {
        iSwitch = StrCmp( (char *) obj.data );

        //printf( "[%d]" , iSwitch );
        switch( iSwitch ) {
            case enCEDEOB :
                //DownloadFile( pReq, ( EN_DOWNLOAD_CASE ) iSwitch );
                break;

            default :
                break;

        }

    }   */

    return 0;
}
