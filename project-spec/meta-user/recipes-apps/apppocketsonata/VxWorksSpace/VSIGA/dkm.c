/* includes */

#include "vxWorks.h"

#include <stdio.h>

void usrAppStart( int iArgc, char *iArgv[] );

void start(void) 
{
    int iArgc=2;
    char szArgv[10] = "-i3";
    char *iArgv[5];

    /* szArgv 값은 문자열로 하드우에어 ID 값이 들어가야 합니다.			*/
    iArgv[0] = NULL;
    iArgv[1] = szArgv;
    iArgv[2] = NULL;
    iArgv[3] = NULL;
	
	printf( "Starting..." );
	
	usrAppStart( iArgc, iArgv );
	
}

