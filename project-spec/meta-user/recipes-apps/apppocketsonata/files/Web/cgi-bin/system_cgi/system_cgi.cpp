
#include <stdio.h>

#include "../../../System/csysconfig.h"

int main(int argc, char *argv[])
{
    CSharedMemroy *pSharedMemory;

    STR_SYSCONFIG strConfig;

    // 공유 메모리 설정
    pSharedMemory = new CSharedMemroy( _SHM_MEMORY_KEY );

    pSharedMemory->copyToLocalMemroy( & strConfig, sizeof(STR_SYSCONFIG) );

    // CGI 헤더를 보낸다.
    printf( "Content-type: text/html\n\n" );

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
    printf( "<p>&nbsp;&nbsp;&nbsp;&nbsp;보드ID: <input type=\"text\" name=\"query_boardid\" value=\"%d\" size=\"4\"> ", strConfig.enBoardID );
    printf( "&nbsp;&nbsp;&nbsp;버전:  <input type=\"text\" name=\"query_version\" size=\"7\"></p>" );
    printf( "<h2>신호 분석</h2> " );
    printf( "<p>&nbsp;&nbsp;&nbsp;&nbsp;최소 펄스 수: <input type=\"text\" name=\"query_minpulse\" value=\"\" size=\"4\"></p>" );
    printf( "<h2>대역별 임계값</h2>" );
    printf( "<p>&nbsp;&nbsp;&nbsp;&nbsp;CD밴드(0.5∼2 ㎓): <input type=\"text\" name=\"query_cd\" value=\"\" size=\"7\">㏈</p>" );
    printf( "<p>&nbsp;&nbsp;&nbsp;&nbsp;저대역(2∼6 ㎓): <input type=\"text\" name=\"query_26\" size=\"7\">㏈</p>" );
    printf( "<p>&nbsp;&nbsp;&nbsp;&nbsp;고대역1(6∼10 ㎓): <input type=\"text\" name=\"query_610\" value=\"\" size=\"7\">㏈, ");
    printf( "고대역2(10∼14 ㎓):&nbsp;<input type=\"text\" name=\"query_1014\" value=\"\" size=\"7\">㏈, " );
    printf( "고대역3(14∼18 ㎓):&nbsp;<input type=\"text\" name=\"query_1418\" value=\"\" size=\"7\">㏈</p>" );


/*
 *     printf( "<p>&nbsp;&nbsp;&nbsp;&nbsp;플레폼: <input type=\"text\" name=\"query_platform\" value=\"%s\" size=\"4\">" , theGrDisp->GetAircraftType() );
    printf( "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;버전: <input type=\"text\" name=\"query_version\" value=\"%s\" size=\"7\">" , theGrDisp->GetVersion() );
    printf( "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;초기 문구: <input type=\"text\" name=\"query_warmup_message\" value=\"%s\" size=\"7\"></p>" , theGrDisp->GetWarmUpMessage() );

  */

    printf( "<h2 align=\"left\"><input type=\"submit\" value=\"변경\" name=\"send\"></h2>" );

    printf( "</form>" );

    printf( "</body>" );
    printf( "</html>" );

    delete pSharedMemory;

    return 0;
}
