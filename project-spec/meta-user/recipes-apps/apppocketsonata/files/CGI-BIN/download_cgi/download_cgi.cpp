#include <time.h>
#include <string.h>
#include <memory.h>
#include <sys/time.h>

#ifdef ENABLE_FASTCGI
#include "fcgi_stdio.h"
#else
#include <stdio.h>
#endif
#include <stdlib.h>
#include <stdbool.h>


#include "../../Anal/INC/system.h"

#include "../Qdecoder/qDecoder.h"

enum EN_DOWNLOAD_CASE {
    enCEDEOB = 0,
    enAET,
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

    const char szCompared[enMAX_DOWNLOAD][100] = { "CEDEOB", "AET", "RAWDATA", "LOG", "SCREEN_DUMP", "INI" } ;

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

    time_t timer;
    struct tm* t;

    qErrorPrint( "DownloadFile Value[%d]" , iSwitch );
    switch( (EN_DOWNLOAD_CASE) iSwitch ) {
        case enCEDEOB :
            strcpy( szSQLiteFileName, CEDEOB_SQLITE_FOLDER );
            strcat( szSQLiteFileName, CEDEOB_SQLITE_FILENAME );

            qErrorPrint( "DownloadFile[%s]" , szSQLiteFileName );
            qDownload( szSQLiteFileName );
            break;

        case enAET :
            strcpy( szSQLiteFileName, CEDEOB_SQLITE_FOLDER );
            strcat( szSQLiteFileName, EMITTER_SQLITE_FILENAME );

            qErrorPrint( "DownloadFile[%s]" , szSQLiteFileName );
            qDownload( szSQLiteFileName );
            break;

        case enLOG :
            strcpy( szSQLiteFileName, PROGRAM_LOG_FOLDER );
            timer = time( NULL );
            t = localtime(&timer);
            sprintf( & szSQLiteFileName[strlen(PROGRAM_LOG_FOLDER)], "/%d_%d_%d.log", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday );

            qErrorPrint( "DownloadFile[%s]" , szSQLiteFileName );
            qDownload( szSQLiteFileName );
            break;

        case enINI :
            strcpy( szSQLiteFileName, INI_FOLDER );
            strcat( szSQLiteFileName, INI_FILENAME );

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
    strcpy( szLogDirectory, QDECODER_LOG_FOLDER );
    strcat( szLogDirectory, QDECODER_LOG_FILENAME );
    qErrorLog( szLogDirectory );

    if( ( pList = qValueFirst( (char *) "formradio" )) == NULL ) {
        qError( "다운로드할 항목이 없습니다. 확인해 주세요." );
        //PreviousPage();
    }
    else {
        iSwitch = StrCmp( pList );

        DownloadFile( iSwitch );

    }

    return 0;
}
