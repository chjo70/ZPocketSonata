/*
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


#define _MAIN_GLOBALS_

#include <signal.h>

#include "cmain.h"
#include "clog.h"
#include "mysocket.h"
#include "creclan.h"
#include "cprompt.h"

extern void usrAppStart();

void signalHandler(int signo);


////////////////////////////////////////////////////////////////////////////////////////
// 아래에 타스크 관련 클래스를 정의합니다.
CMySocket g_theMySocket( g_iKeyId++ );




/**
 * @brief usrAppStart
 */
void usrAppStart()
{
    LOGMSG( enNormal, "\n\n" );

    LOGENTRY;
    LOGMSG2( enNormal, "[%s:%s] 프로그램을 구동합니다.", PROGRAM_NAME, PROGRAM_VERSION );

    signal( SIGINT, signalHandler);
    signal( SIGABRT, signalHandler);
    signal( SIGHUP, signalHandler);
    signal( SIGTERM, signalHandler);
    signal( SIGSTOP, signalHandler);

    //
    MAIN->Run();

    g_theMySocket.Run();
    RECLAN->Run();
    PROMPT->Run();

    pause();

    while( true ) {
        sleep( 10000000 );
    }

}

void signalHandler( int signo )
{

  if( msgctl( MAIN->GetKeyId(), IPC_RMID, 0) == -1) { // msqid 메시지 큐 삭제
      perror("msgctl failed");
      exit(1);
   }

  if( msgctl( RECLAN->GetKeyId(), IPC_RMID, 0) == -1) { // msqid 메시지 큐 삭제
      perror("msgctl failed");
      exit(1);
   }

  if( msgctl( g_theMySocket.GetKeyId(), IPC_RMID, 0) == -1) { // msqid 메시지 큐 삭제
      perror("msgctl failed");
      exit(1);
   }

   printf( "\n SIGNO[%d] Handler\n" , signo );
   exit(0);

}


// 클래스 내의 정적 멤버변수 값 정의
char CMain::m_szClassName[LENGTH_OF_CLASSNAME] = { "CMain" };
CMain* CMain::pInstance = nullptr;

/**
 * @brief CMain::CMain
 */
CMain::CMain( int iKeyId ) : CThread( iKeyId )
{
    LOGENTRY;

}

/**
 * @brief CMain::Init
 */
void CMain::Init()
{
    LOGENTRY;

    //STR_MessageData sndMsg;

    //CThread theThread1(10), theThread2(11);

    /*

    theThread1.Run( thread_routine );
    theThread2.Run( thread_routine );

    sndMsg.mtype = 1;
    sndMsg.x.opCode = 0x1234;

    int i=0;

    printf("\ntid:%lx\n",pthread_self());
    while( true ){
        printf("main:%d\n",i);
        i++;
        sleep(1);

        if(msgsnd( theThread1.GetKeyId(), (void *)& sndMsg, sizeof(STR_MessageData)-sizeof(long), IPC_NOWAIT) <0)
        {
            perror("msg snd error" );
            printf("KeyID[%d]\n", theThread1.GetKeyId() );

        }
        if(msgsnd( theThread2.GetKeyId(), (void *)& sndMsg, sizeof(STR_MessageData)-sizeof(long), IPC_NOWAIT) <0)
        {
            perror("msg snd error" );
            printf("KeyID[%d]\n", theThread2.GetKeyId() );
        }

        //theThread1.Pend();
        //theThread1.Stop();

    }

    */

}

/**
 * @brief CMain::Run
 */
void CMain::Run()
{
    LOGENTRY;

    CThread::Run();

}

/**
 * @brief CMain::_routine
 */
void CMain::_routine()
{
    LOGENTRY;

    while( true ) {
        if( QMsgRcv() == -1 ) {
            perror( "error ");
        }
    }

}