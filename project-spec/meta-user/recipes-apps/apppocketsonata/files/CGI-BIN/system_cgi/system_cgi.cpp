
#include <stdio.h>

#include "../../System/csysconfig.h"

int main(int argc, char *argv[])
{
    CSharedMemroy *pSharedMemory;

    STR_SYSCONFIG strConfig;

    minIni m_theMinIni;

    char szHomeDirectory[500];
    char szLogDirectory[500];

    int iValue;
    float fValue;

    // INI 파일 로딩하기
    strcpy( szHomeDirectory, INI_FOLDER /* getenv("HOME") */ );
    strcat( szHomeDirectory, INI_FILENAME );

    m_theMinIni.setfilename( szHomeDirectory );

    // 로그는 현재 홈 디렉토리에 저장한다.
    strcpy( szLogDirectory, QDECODER_LOG_FOLDER );
    strcat( szLogDirectory, QDECODER_LOG_FILENAME );
    //qErrorLog( szLogDirectory );

    // CGI 헤더를 보낸다.
    printf( "Content-type: text/html\n\n" );

    // 공유 메모리 설정
    pSharedMemory = new CSharedMemroy( _SHM_MEMORY_KEY );

    pSharedMemory->copyToLocalMemroy( & strConfig, sizeof(STR_SYSCONFIG) );


    // HTML 헤더를 보낸다.
    printf( "<html>" );

    printf( "<head>" );
    printf( "<meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\">" );
    printf( "<title>시스템 변수</title>" );
    printf( "</head>" );

    printf( "<body bgcolor=\"white\" text=\"black\" link=\"blue\" vlink=\"purple\" alink=\"red\">" );

    printf( "<ul>" );
    printf( "<h1><a href=\"/cgi-bin/system.cgi\"><img src=\"../graphics/img2.gif\" width=\"115\" height=\"87\" border=\"0\" alt=\"그냥 그림 입니다.\"></a> " );
    printf( "시스템 변수</h1>" );
    printf( "</ul>" );

    printf( "<hr color=\"#CC99FF\">" );
    printf( "<form method=\"get\" action=\"fetch.cgi\">" );


    printf( "<h2>보드ID 및 소프트웨어 버젼정보</h2>" );
    printf( "<p>&nbsp;&nbsp;&nbsp;&nbsp;보드ID: <input type=\"text\" name=\"query_boardid\" value=\"%d\" size=\"2\" maxlength=\"0\" style=\"background-color:yellow;\"> ", strConfig.enBoardID );
    printf( "&nbsp;&nbsp;&nbsp;버전:  <input type=\"text\" name=\"query_version\" value=\"%s\" size=\"4\" maxlength=\"0\" style=\"background-color:yellow;\"></p>" , strConfig.szProgramVersion );
    printf( "<h2>신호 분석</h2> " );
    iValue = m_theMinIni.geti( "ANAL" , "MIN_ANALPULSE" , _ANAL_MIN_PULSECOUNT_ );
    printf( "<p>&nbsp;&nbsp;&nbsp;&nbsp;최소 펄스 수: <input type=\"text\" name=\"query_minpulse\" value=\"%d\" size=\"2\" ></p>" ,iValue ); // strConfig.iMinAnalPulse );
    iValue = m_theMinIni.geti( "ANAL" , "DEFAULT_DELETE_TIMESEC" , _DEFAULT_DELETETIME_ );
    printf( "<p>&nbsp;&nbsp;&nbsp;&nbsp;신호 삭제 시간[초]: <input type=\"text\" name=\"query_deletetime\" value=\"%d\" size=\"2\">&nbsp;</p>", iValue );
    printf( "<h2>대역별 임계값</h2>" );
    fValue = m_theMinIni.getf( "RXTHRESHOLD" , "Band1" , _RXTHRESHOLD_BAND1_ );
    printf( "<p>&nbsp;&nbsp;&nbsp;&nbsp;CD밴드(0.5∼2 ㎓): <input type=\"text\" name=\"query_band1\" value=\"%.1f\" size=\"2\">㏈</p>", fValue );
    fValue = m_theMinIni.getf( "RXTHRESHOLD" , "Band2" , _RXTHRESHOLD_BAND2_ );
    printf( "<p>&nbsp;&nbsp;&nbsp;&nbsp;저대역(2∼6 ㎓): <input type=\"text\" name=\"query_band2\" value=\"%.1f\" size=\"2\">㏈</p>" , fValue );
    fValue = m_theMinIni.getf( "RXTHRESHOLD" , "Band3" , _RXTHRESHOLD_BAND3_ );
    printf( "<p>&nbsp;&nbsp;&nbsp;&nbsp;고대역1(6∼10 ㎓): <input type=\"text\" name=\"query_band3\" value=\"%.1f\" size=\"2\">㏈," , fValue );
    fValue = m_theMinIni.getf( "RXTHRESHOLD" , "Band4" , _RXTHRESHOLD_BAND4_ );
    printf( "고대역2(10∼14 ㎓):&nbsp;<input type=\"text\" name=\"query_band4\" value=\"%.1f\" size=\"2\">㏈," , fValue );
    fValue = m_theMinIni.getf( "RXTHRESHOLD" , "Band5" , _RXTHRESHOLD_BAND5_ );
    printf( "고대역3(14∼18 ㎓):&nbsp;<input type=\"text\" name=\"query_band5\" value=\"%.1f\" size=\"2\">㏈</p>" , fValue );

    printf( "<h2 align=\"left\"><input type=\"submit\" value=\"변경\" name=\"send\">" );
    printf( "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type=\"button\" name=\"formbutton1\" value=\"기본값으로...\"></p>" );
    printf( "</h2>" );

    printf( "</form>" );

    printf( "</body>" );
    printf( "</html>" );

    delete pSharedMemory;

    return 0;
}
