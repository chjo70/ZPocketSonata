/*
 *
 *
* Placeholder PetaLinux user application.
*
* Replace this with your application code

* Copyright (C) 2013 - 2016  Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person
* obtaining a copy of this software and associated documentation
* files (the "Software"), to deal in the Software without restriction,
* including without limitation the rights to use, copy, modify, merge,
* publish, distribute, sublicense, and/or sell copies of the Software,
* and to permit persons to whom the Software is furnished to do so,
* subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in this
* Software without prior written authorization from Xilinx.
*
*/

#include <iostream>

using namespace std;

#define _MAIN_GLOBALS_

#include <signal.h>
#include <cassert>

#include "cmain.h"
#include "./Thread/ctaskmngr.h"
#include "./Utils/clog.h"
#include "./Utils/cmultiserver.h"
#include "./Utils/csingleserver.h"
#include "./Utils/csingleclient.h"
#include "./Thread/creclan.h"
#include "./Thread/cprompt.h"
#include "./Thread/curbit.h"
#include "./Thread/cpulsetrk.h"
#include "./Thread/csignalcollect.h"
#include "./Thread/cjamtech.h"
#include "./Thread/ccgi.h"
#include "./Thread/cusercollect.h"

#include "./System/csysconfig.h"

extern void usrAppStart();

void signalHandler(int signo);

////////////////////////////////////////////////////////////////////////////////////////
// 아래에 타스크 관련 클래스를 정의합니다.
//CMySocket g_theZYNQSocket( g_iKeyId++, (char *)"CZYNQSocket" );
//CMySocket g_theCCUSocket( g_iKeyId++, (char *)"CCCUSocket" );
//CMySocket g_thePMCSocket( g_iKeyId++, (char *)"CPMCSocket" );

CMultiServer *g_pTheZYNQSocket;
CSingleClient *g_pTheCCUSocket;
CSingleClient *g_pThePMCSocket;

/**
 * @brief 시작 프로그램 입니다.
 */
void usrAppStart()
{
    LOGMSG( enNormal, "------------------------------------------------------------------------" );
    LOGMSG( enNormal, " ZZZZZZZZ    PPPPPPPP   OOOOO    CCCCCC  KK    KK   EEEEEEE  TTTTTTTTT" );
    LOGMSG( enNormal, "      ZZ     PP    PP  OO   OO  CC       KK  KK     EE          TT" );
    LOGMSG( enNormal, "    ZZ       PPPPPPPP  OO   OO  CC       KKKK       EEEEEEE     TT" );
    LOGMSG( enNormal, "  ZZ         PP        OO   OO  CC       KK  KK     EE          TT" );
    LOGMSG1( enNormal, " ZZZZZZZZ    PP         OOOOO    CCCCCC  KK    KK   EEEEEEE     TT  Ver %s" , PROGRAM_VERSION );
    LOGMSG( enNormal, "-------------------------------------------------------------------------" );

    LOGENTRY;
    _ShowProgramTitle();

    signal( SIGINT, signalHandler);
    signal( SIGABRT, signalHandler);
    signal( SIGHUP, signalHandler);
    signal( SIGTERM, signalHandler);
    signal( SIGSTOP, signalHandler);

    // 1. 쓰레드 관리 쓰레드를 호출한다.
    TMNGR->Run( _MSG_TMNGR_KEY );

    // 2. 운용 관련 쓰레드를 호출한다.
    URBIT->Run( _MSG_URBIT_KEY );

    // 3. 분석 및 재밍 관련 쓰레드를 호출한다.
    PULTRK->Run( _MSG_PULTRK_KEY );
    JAMTEC->Run( _MSG_JAMTEC_KEY );

    // 4. ZYNQ 보드 및 CCU 장치의 랜 처리 쓰레드를 호출한다.
    RECZYNQ->Run( _MSG_RECZYNQ_KEY );
    RECCCU->Run( _MSG_RECCCU_KEY );

    // 6. 브라우저의 CGI 메시지를 처리한다.
    CGI->Run( _MSG_ZCGI_KEY );

    // 7. 사용자 수집 함수 메시지를 처리한다.
    UCOL->Run( _MSG_USERCOL_KEY );

    // 8. 마지막으로 랜 송신 및 수신 쓰레드를 호출한다.
    g_pTheZYNQSocket = new CMultiServer( g_iKeyId++, (char *)"CZYNQSocket", PORT );
    g_pTheZYNQSocket->Run( _MSG_ZYNQ_KEY );
    if( GP_SYSCFG->GetBoardID() == enMaster ) {
        g_pTheCCUSocket = new CSingleClient( g_iKeyId++, (char *)"CCCUSocket", CCU_PORT, GP_SYSCFG->GetPrimeServerOfNetwork() );
        g_pTheCCUSocket->Run( _MSG_CCU_KEY );

        //g_pThePMCSocket = new CSingleClient( g_iKeyId++, (char *)"CPMCSocket", PMC_PORT, PMC_SERVER );
        //g_pThePMCSocket->Run( _MSG_CCU_KEY );
    }

    // 9. 마지막으로 키 입력 처리를 호출한다.
#ifndef _DAEMON_
    PROMPT->Run( _MSG_PROMPT_KEY );
#endif

    while( g_Loop ) {
        sleep(10);
    }
    //pause();
    printf( "\n 종료 처리 시작 합니다." );


    // 분석 관련 쓰레드를 종료 한다.

    PROMPT->ReleaseInstance();

    delete g_pTheCCUSocket;

    delete g_pTheZYNQSocket;

    UCOL->ReleaseInstance();

    CGI->ReleaseInstance();

    RECZYNQ->ReleaseInstance();
    RECCCU->ReleaseInstance();

    JAMTEC->ReleaseInstance();
    PULTRK->ReleaseInstance();

    URBIT->ReleaseInstance();

    // 마지막 타스크 관리자 쓰레드를 종료 한다.
    TMNGR->ReleaseInstance();


    LOGMSG( enDebug, "[usrAppStart] 를 종료 처리 합니다..." );

    exit(0);

}

/**
 * @brief signalHandler
 * @param signo
 */
void signalHandler( int signo )
{

    printf( "\n SIGNO[%d] Handler\n" , signo );

    if( signo == 2 ) {
        g_Loop = false;
        exit(0);
    }

}

/**
 * @brief ParsingArgument
 * @param iArgc
 * @param iArgv
 */
void ParsingArgument( int iArgc, char *iArgv[] )
{

    if( iArgc >= 2 ) {
        -- iArgc;
        ++ iArgv;
        while(iArgc--) {
            g_enBoardId = (ENUM_BoardID) atoi( *iArgv );
            // cout << *iArgv++ << endl;
        }
        if( g_enBoardId == enMaster ) {
            LOGMSG1( enDebug, "마스터[%d]로 설정합니다." , g_enBoardId );
        }
        else {
            LOGMSG1( enDebug, "슬레이브[%d]로 설정합니다." , g_enBoardId );
        }
    }
    else {
        LOGMSG( enDebug, "프로그램 아큐먼트가 입력되지 않아서 기본 마스터로 설정합니다." );
        g_enBoardId = enMaster;
    }
}

void cleanup_handler(void *arg )
{
    printf("cleanup \n");
    // close your socket
}

void *execute_on_thread(void *arg)
{
    pthread_cleanup_push(cleanup_handler, NULL);
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

    while(1)
    {
        //sleep(1);
        printf("Running\n");
        //thread stuff
    }

    pthread_cleanup_pop(1);

    return (void *) 0;
}


/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{

    /////////////////////////////////////////////////////////////////////////////////
    // 아규먼트를 파싱하여 프로그램을 설정합니다.
    ParsingArgument( argc, argv );


#ifdef _DAEMON_
    pid_t pid;

    pid = fork();

    // fork() 가 실패하면 프로그램을 종료한다.
    if( pid < 0 ) {
        exit(0);
    }
    // 부모프로세스를 종료한다.
    else if( pid != 0 ) {
        exit(0);
    }

    // 터미널 종료시 signal의 영향을 받지 않는다.
    signal( SIGHUP, SIG_IGN );
    //close( 0 );
    //close( 1 );
    //close( 2 );

    chdir( "/" );
    // 새로운 세션의 리더가 된다.
    setsid();
#endif

    usrAppStart();

    /*
    pthread_t tid;
    pthread_create(&tid,NULL,execute_on_thread,NULL);

    sleep(10);

    if (!pthread_cancel(tid))
    {
        pthread_join(tid, NULL);
    }
    else
    {
        perror("pthread_cancel");
    }
    */

	return 0;
}

