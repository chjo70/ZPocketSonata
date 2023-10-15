/*
 * BootShellMain.c
 *
 *  Created on: Apr 13, 2021
 *      Author: ELS
 */

//#include "pch.h"

#include <stdarg.h>

#ifdef __VXWORKS__
#include <bootLib.h>
#include <private/adrSpaceLibP.h>

#include <vxWorks.h>
#if defined(PRJ_BUILD)
#include "prjParams.h"
#endif /* defined PRJ_BUILD */


#ifdef _PCI
#include "pciDiag.h"

#endif


#include <ioLib.h>
#include <vxLib.h>
#include <sysLib.h>
#include <taskLib.h>

#include <time.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

#include <nfs/nfsCommon.h>

#endif

#include "BootShellMain.h"

#ifdef __cplusplus
extern "C" {
#endif
void _TRACE( char *format, ... );

#ifdef __cplusplus
}
#endif

#ifdef __VXWORKS__
STATUS usrBootLineCrack (char * bootString, BOOT_PARAMS *pParams);

extern BOOT_PARAMS g_stBootParams;

#elif defined(_MSC_VER)
#define TRACE _TRACE

#endif



// GoAhead 시작 함수 정의
int websvxmain(int argc, char **argv);
int ipftps_authenticate_user_callback();

void Main()
{

    printf("\n");

    //////////////////////////////////////////////////////////////////////////
    LoadBootParameter();

    printf( "\n 소형 전자전장비(APECS-II) 자체개발, 부트 쉘 프로그램, %s, 전자전 연구소, 2021., 2022., 2023." , VERSION );

#ifdef __VXWORKS__
    printf( "\n 컴파일 날짜 : %s\n\n" , creationDate );

#else
    printf( "\n\n" );

#endif

#ifdef __VXWORKS__
	taskSpawn( (char *) "tBootShell", tPRI_BOOTSHEL, VX_STDIO | VX_SUPERVISOR_MODE | VX_FP_TASK | VX_ALTIVEC_TASK, 64000, (FUNCPTR) BootShellMain, 0,0,0,0,0,0,0,0,0,0 );

#ifdef WEBS
	taskSpawn( ( char * ) "tHttpd", tPRI_HTTPDAEMON, VX_STDIO | VX_SUPERVISOR_MODE | VX_FP_TASK | VX_ALTIVEC_TASK, 64000, (FUNCPTR) websvxmain, 0,0,0,0,0,0,0,0,0,0 );
#endif

#elif _MSC_VER
    BootShellMain();
    websvxmain( 0, NULL );

#endif

}

#ifdef WIN
// int main()
// {
//     Main();
//     return 0;
//
// }
#endif



/**
 * @brief		부투 페라미터 값을 출력 합니다.
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2009-07-29 16:02:14
 * @warning
 */
void LoadBootParameter()
{
#ifdef __VXWORKS__
	// boot parameter 를 읽어온다.
	char *bootString=(char *) BOOT_LINE_ADRS;

    //printf( "\n BOOT_LINE_ADRS=%p" , bootString );
	if( ( bootString != NULL ) && ( *bootString != EOS ) ) {
		strcpy( (char *) BOOT_LINE_ADRS, bootString );
    }

    /* interpret boot command */
	STATUS stat = usrBootLineCrack( BOOT_LINE_ADRS, & g_stBootParams );
	if( stat != OK ) {
		printf( "\n [W] 부트 페라미터값이 잘못 설정되었습니다 !" );
	}
    else {
        //printf( "Host IP Address : [%s]" , stBootParams.had );

        if( strcmp( DEFAULT_SNTP_SERVER_IP, g_stBootParams.had) != 0 ) {
            printf( "\n 배터리 DRAM이 장착이 안 되어서, uBoot 쉘에서 bootParameter 설정 값을 아래와 같이 직접 작업을 해야 합니다 !!!" );
            printf( "\n setenv bootargs \"memac(0,0)host:vxWorks h=$serverip e=$ipaddr:ffffff00 g=$gatewayip u=t2080 pw=1234 f=0x408 tn=t2080 tn=t2080\" ");
        }

    }
#endif

}

int ipftps_authenticate_user_callback()
{
    printf( "AAAA" );
    return 1;

}
