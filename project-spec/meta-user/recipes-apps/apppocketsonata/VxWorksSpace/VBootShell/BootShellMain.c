/*
 * BootShellMain.c
 *
 *  Created on: Apr 13, 2021
 *      Author: ELS
 */


#include <bootLib.h>
#include <private/adrSpaceLibP.h>

#include <vxWorks.h>
#if defined(PRJ_BUILD)
#include "prjParams.h"
#endif /* defined PRJ_BUILD */

#include <time.h>

#include <ioLib.h>
#include <vxWorks.h>
#include <ifLib.h>
#include <vxLib.h>
#include <sysLib.h>
#include <taskLib.h>
#include <string.h>
#include <stdio.h>

#include "BootShellMain.h"

extern BOOT_PARAMS stBootParams;

// GoAhead 시작 함수 정의
int websvxmain(int argc, char **argv);

void Main()
{
    char ip_addr[100];
    
    time_t rawtime;  
    struct tm * timeinfo;

    LoadBootParameter();
	
#ifdef LIGNEX1
    // 순서에 중요
    ifMaskSet( "memac0" , 0xffffff00 );
    ifAddrSet( "memac0" , "192.168.10.50" );

    ifAddrGet( "memac0", ip_addr );

    sysClkRateSet( TICK_COUNT );		// 1초당 100 tick 을 수행함.

#else

#error	"network device 명을 알아서 위와 같이 설정해야함."

#endif
	
    printf( "\n IP addr[%s]" , ip_addr );
    if( sysClkRateGet() != 100 ) {
#ifdef TOOL==diab    		
        printf( "\n [W] In the Workbench, please set up the tick count is 100." );
#else
        printf( "\n [W] 토네이도의 Component에서 tick count를 100 으로 설정하세요." );
#endif        
    }
	
#ifdef TOOL==diab
    printf( "\n Pocket ES System, Boot Shell Program, %s, EW Lab., 2021." , VERSION );
    printf( "\n Compile Version : %s" , creationDate );
#else
    printf( "\n 소형 전자전장비 자체개발, 부트 쉘 프로그램, %s, 전자전 연구소, 2021." , VERSION );
    printf( "\n 컴파일 날짜 : %s" , creationDate );   
    
#endif
    
    time( & rawtime );
    timeinfo = localtime ( & rawtime );
#ifdef TOOL==diab    
    printf ( "\n Execution Time : %s\n", asctime (timeinfo) );
#else
    printf ( "\n 실행 시간: %s\n", asctime (timeinfo) );
#endif

    //BootShellMain();
    
	taskSpawn( "tBootShell", tPRI_BOOTSHEL, VX_STDIO|VX_SUPERVISOR_MODE, 64000, (FUNCPTR) BootShellMain, 0,0,0,0,0,0,0,0,0,0 );
    
#ifdef WEBS
	taskSpawn( "tHttpd", tPRI_HTTPDAEMON, VX_STDIO|VX_SUPERVISOR_MODE, 64000, (FUNCPTR) websvxmain, 0,0,0,0,0,0,0,0,0,0 );
#endif    
	
}


//////////////////////////////////////////////////////////////////////////
/*! \brief    LoadBootParameter
		\author   조철희
		\return   void
		\version  0.0.80
		\date     2009-07-29 16:02:14
		\warning
*/
void LoadBootParameter()
{

	// boot parameter 를 읽어온다.
	char *bootString=(char *) BOOT_LINE_ADRS;
	if( ( bootString != NULL ) && ( *bootString != EOS ) )
		strcpy( (char *) BOOT_LINE_ADRS, bootString );

  /* interpret boot command */
	if( usrBootLineCrack( BOOT_LINE_ADRS, & stBootParams ) != OK ) {
		printf( "\n [W] 부트 페라미터값이 잘못 설정되었습니다 !" );
		return;
	}
}


