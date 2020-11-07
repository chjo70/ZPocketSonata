
#include <stdio.h>

#include "../../System/csysconfig.h"

int main(int argc, char *argv[])
{
    CSharedMemroy *pSharedMemory;

    STR_SYSCONFIG strConfig;

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
    printf( "<p>&nbsp;&nbsp;&nbsp;&nbsp;최소 펄스 수: <input type=\"text\" name=\"query_minpulse\" value=\"%d\" size=\"2\" ></p>", strConfig.iMinAnalPulse );
    printf( "<h2>대역별 임계값</h2>" );
    printf( "<p>&nbsp;&nbsp;&nbsp;&nbsp;CD밴드(0.5∼2 ㎓): <input type=\"text\" name=\"query_cd\" value=\"%.1f\" size=\"2\">㏈</p>", strConfig.fRxThreshold[0] );
    printf( "<p>&nbsp;&nbsp;&nbsp;&nbsp;저대역(2∼6 ㎓): <input type=\"text\" name=\"query_26\" value=\"%.1f\" size=\"2\">㏈</p>" , strConfig.fRxThreshold[1] );
    printf( "<p>&nbsp;&nbsp;&nbsp;&nbsp;고대역1(6∼10 ㎓): <input type=\"text\" name=\"query_610\" value=\"%.1f\" size=\"2\">㏈," , strConfig.fRxThreshold[2] );
    printf( "고대역2(10∼14 ㎓):&nbsp;<input type=\"text\" name=\"query_1014\" value=\"%.1f\" size=\"2\">㏈," , strConfig.fRxThreshold[2] );
    printf( "고대역3(14∼18 ㎓):&nbsp;<input type=\"text\" name=\"query_1418\" value=\"%.1f\" size=\"2\">㏈</p>" , strConfig.fRxThreshold[2] );

    printf( "<h2 align=\"left\"><input type=\"submit\" value=\"변경\" name=\"send\"></h2>" );

    printf( "</form>" );

    printf( "</body>" );
    printf( "</html>" );

    delete pSharedMemory;

    return 0;
}
