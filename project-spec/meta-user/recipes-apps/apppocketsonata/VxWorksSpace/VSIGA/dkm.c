/* includes */

#ifdef __VXWORKS__


#include "vxWorks.h"

#include <time.h>
#include <stdio.h>

void usrAppStart( int iArgc, char *iArgv[] );

void start(_Vx_usr_arg_t arg1 )
{
    time_t rawtime;
    struct tm * timeinfo;
    
    int iArgc=2;
    char szArgv[10]; /* = "-i3";		*/
    char *iArgv[5];
    
    time( & rawtime );
    timeinfo = localtime ( & rawtime );
    printf( "\n프로그램 시작 실행 시간: %s\n\n", asctime( timeinfo ) );    

    printf( "\n*SBC ID[%d]\n" , arg1 );
    sprintf( szArgv, "-i%d", arg1 );

    /* szArgv 값은 문자열로 하드웨어 ID 값이 들어가야 합니다.			*/
    iArgv[0] = NULL;
    iArgv[1] = szArgv;
    iArgv[2] = NULL;
    iArgv[3] = NULL;

	usrAppStart( iArgc, iArgv );

}


#endif
