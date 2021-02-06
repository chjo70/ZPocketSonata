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


#define TABLE_COLS      (12)
char szTableCols[TABLE_COLS][30] = { "번호", "사용 여부", "모드", "수집개수", "누적 개수/회수", "채널 수집개수", "채널 수집시간[초]", "채널 방위[도]", "채널 주파수[MHz]", "채널 펄스폭[ns]", "채널 세기[dBm]", "빔 번호" } ;

#define MAX_TITLE      (4)
char szTitle[MAX_TITLE][30] = { "탐지", "추적", "스캔", "사용자" } ;
int iCoChannels[MAX_TITLE] = { DETECT_CHANNEL, TRACK_CHANNEL, SCAN_CHANNEL, USER_CHANNEL } ;


void PreviousPage();
void ShowUpdatedPageTime();

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
    qCatFile( (char *) "../support.header.qDecoder" );


    if( bShared == true ) {
        ShowUpdatedPageTime();

        printf( "<p style=\"line-height:150%; margin-top:0; margin-bottom:0;\"</p>" );

        for( i=0 ; i < 4 ; ++i ) {
            ///////////////////////////////////////////////////////////////////////////////////////////////////
            printf( "<p align=\"center\"><b>%s 수집 채널(x%d)</b></p>", szTitle[i], iCoChannels[i] );
            printf( "<table class=\"table-style-two\" align=\"center\">" );

            // 테이블 헤더
            printf( "<thead><tr>" );
            for( j=0 ; j < TABLE_COLS ; ++j ) {
                printf( "<th><p align=\"center\">%s</th>", szTableCols[j] );
            }
            printf( "</tr></thead>" );

            // 채널 상태 전시
            printf( "<tbody>" );
            for( j=0 ; j < iCoChannels[i] ; ++j ) {
                STR_WINDOWCELL *pWindowCell;

                switch( i ) {
                    case 0 :
                        pWindowCell = & strConfig.strDetectWindowCell[j];
                        break;
                    case 1 :
                        pWindowCell = & strConfig.strTrackWindowCell[j];
                        break;
                    case 2 :
                        pWindowCell = & strConfig.strScanWindowCell[j];
                        break;
                    case 3 :
                        pWindowCell = & strConfig.strUserWindowCell[j];
                        break;
                }

                if( pWindowCell->bUse == false ) {
                    continue;
                }

                printf( "</tr>" );

                printf( "<td><p align=\"center\">%d</td>", j+1 );

                if( pWindowCell->bUse == true ) {
                    printf( "<td><p align=\"center\"><img src=\"../graphics/check01_blue.gif\" width=\"11\" height=\"11\" border=\"0\" align=\"center\"></td>" );
                }
                else {
                    printf( "<td><p align=\"center\"><img src=\"../graphics/x_red.gif\" width=\"11\" height=\"11\" border=\"0\" align=\"center\"></td>" );
                }

                switch( pWindowCell->enCollectMode ) {
                    case enUnused :
                        printf( "<td><p align=\"center\"><img src=\"../graphics/x_red.gif\" width=\"11\" height=\"11\" border=\"0\" alt=\"미사용\"></td>" );
                        break;
                    case enCollecting :
                        printf( "<td><p align=\"center\"><img src=\"../graphics/anipink02_pulse_down.gif\" width=\"11\" height=\"11\" border=\"0\" alt=\"수집중\"></td>" );
                        break;
                    case enCompleteCollection :
                        printf( "<td><p align=\"center\"><img src=\"../graphics/x_red.gif\" width=\"11\" height=\"11\" border=\"0\" alt=\"수집 완료\"></td>" );
                        break;
                    case enAnalysing :
                        printf( "<td><p align=\"center\"><img src=\"../graphics/words_rep_hot.gif\" width=\"11\" height=\"11\" border=\"0\" alt=\"분석 중\"></td>" );
                        break;
                }


                printf( "<td><p align=\"center\">%d</td>", pWindowCell->uiTotalPDW );

                // 누적 정보
                printf( "<td><p align=\"center\">%d / %d</td>", pWindowCell->uiAccumulatedCoPDW, pWindowCell->uiAccumulatedCoUsed );

                // 채널 정보
                printf( "<td><p align=\"center\">%d</td>", pWindowCell->uiMaxCoPDW );

                printf( "<td><p align=\"center\">%d.%d</td>", pWindowCell->uiMaxCollectTimesec, pWindowCell->uiMaxCollectTimems );

                printf( "<td><p align=\"center\">%.1f - %.1f</td>", AOACNV(pWindowCell->strAoa.iLow), AOACNV(pWindowCell->strAoa.iHigh) );
                printf( "<td><p align=\"center\">%.2f - %.2f</td>", FRQMhzCNV( 0, pWindowCell->strFreq.iLow), FRQMhzCNV( 0, pWindowCell->strFreq.iHigh ) );
                printf( "<td><p align=\"center\">%.2f - %.2f</td>", PWCNV(pWindowCell->strPW.iLow), PWCNV(pWindowCell->strPW.iHigh) );
                printf( "<td><p align=\"center\">%.2f - %.2f</td>", PACNV(pWindowCell->strPA.iLow), PACNV(pWindowCell->strPA.iHigh) );

                printf( "<td><p align=\"center\">%d</td>", pWindowCell->uiABTID );

                printf( "</tr>" );
            }
            printf( "</tbody>" );
            printf( "</table>\r\n" );
        }

        printf( "</tr></thead></table>" );        

        // 재시도 자동 타이머를 설정하는화면 이다.
        qCatFile( (char *) "../support.refresh.qDecoder" );
    }
    else {

    }

    //PreviousPage();

    qErrorPrint( "EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE" );

    qFree();

    delete pSharedMemory;

    return 0;
}

/**
 * @brief UpdateTimeOfPage
 */
void ShowUpdatedPageTime()
{
    struct tm *pTm;
    time_t timer;

    timer = time( NULL );
    pTm = localtime( &timer );

    printf( "<p align=\"right\"><font size=\"1\" color=\"#006633\"><b>업데이트 시간: %d년 %02d월 %02d일 %02d시 %02d분 %02d초</b></font></p>", pTm->tm_year + 1900, pTm->tm_mon + 1, pTm->tm_mday, pTm->tm_hour, pTm->tm_min, pTm->tm_sec );

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
