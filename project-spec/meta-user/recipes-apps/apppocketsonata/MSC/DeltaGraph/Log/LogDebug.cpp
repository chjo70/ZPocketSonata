// LogDebug.cpp: implementation of the CLogDebug class.
//
//////////////////////////////////////////////////////////////////////

// PC�� ���� Ŭ������ �����ϱ� ���� ����

#include "stdafx.h"

#ifdef _WIN32

#include <io.h>
#include <fcntl.h>

#else

// ��Ÿ�� ���̺귯�� ���� ��� ����
#include <ioLib.h>
#include <stdio.h>
#include <stdarg.h>

// vxworks ���� ��� ����
#include <semLib.h>

#include "lsv70aDef.h"

#endif

//#include "../OFP_Main.h"

#include "LogDebug.h"

//////////////////////////////////////////////////////////////////////////
/*! \brief    Printf
		\author   ��ö��
		\param    format �������� char *
		\return   void
		\version  0.0.31
		\date     2008-07-19 02:01:00
		\warning
*/
int Printf( char *format, ... )
{
	char buffer[100];
	va_list	ap;

	va_start( ap, format );
	vsprintf( buffer, format, ap );
	va_end( ap );

	TRACE( buffer );

	//theLogDebug->DebugPrintf( buffer );

	return 0;
}

int WPrintf( char *format, ... )
{
	char buffer[100];
	va_list	ap;

	va_start( ap, format );
	vsprintf( buffer, format, ap );
	va_end( ap );

	//theLogDebug->DebugPrintf( buffer, TRUE );

	return 0;
}

void _LockPrint()
{
	//theLogDebug->LockPrint();
}

void _UnLockPrint()
{
	//theLogDebug->UnLockPrint();
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// CLogDebug::CLogDebug( char *pTaskName, int queue_size, int ring_size ) : CTask()
// {
// 	strcpy_s( m_taskName, pTaskName );
// 
// 	m_bDebugPrintf = TRUE;
// 	m_bLogPrintf = FALSE;
// 
// 	// �α� ���۴� 2000 ����Ʈ
// 	m_pScreenBuffer = new CCircularQueue<unsigned char>( ' ', 2000, BOOT_SCREEN_CAPTURE );
// 	printf( "\n BOOT_SCREEN_CAPTURE[%p]" , BOOT_SCREEN_CAPTURE );
// 
// #ifndef _WIN32
// 	m_semPrint = semBCreate( SEM_Q_PRIORITY | SEM_EVENTSEND_ERR_NOTIFY, SEM_FULL );
// 	if( NULL == m_semPrint ) {
// 		WhereIs;
// 		PrintErr( ( "\n [W] �������� �޽����� �������� ���߽��ϴ�." ) );
// 	}
// #endif
// 
// 	MakeScreenBuffer();
// }
// 
// CLogDebug::~CLogDebug()
// {
// 	delete m_pScreenBuffer;
// }
// 
// //////////////////////////////////////////////////////////////////////////
// /*! \brief    ����� Ŭ������ ���� �۾��� �Ѵ�.
// 		\author   ��ö��
// 		\return   void
// 		\version  0.0.1
// 		\date     2008-04-25 20:41:23
// 		\warning
// */
// void CLogDebug::Run()
// {
// 	return;
// }
// 
// //////////////////////////////////////////////////////////////////////////
// /*! \brief    CLogDebug::DebugPrintf
// 		\author   ��ö��
// 		\param    string �������� char *
// 		\param    bFlush �������� BOOL
// 		\version  0.0.30
// 		\date     2008-07-18 13:05:22
// 		\warning
// */
// void CLogDebug::DebugPrintf( char *string, BOOL bFlush )
// {
// #ifndef _WIN32
// 	/*! \bug  ������ ��ٸ� ��ſ� �������� ����ؼ� 10�� ������ �ο��ϰ� �ϴ� ���� ?
// 	    \date 2008-12-09 09:40:46, ��ö��
// 	*/
// 	semTake( m_semPrint, WAIT_FOREVER );
// #endif
// 
// 	if( m_bLogPrintf == TRUE ) {
// 		char *pString=string;
// 		// NVRAM�� �α� �޽��� �����ϱ�
// 		int string_length=strlen( string );
// 		for( int i=0 ; i < string_length ; ++i ) {
// 			m_pScreenBuffer->EnQueueList( *pString++ );
// 		}
// 	}
// 
// 	// �ø��� ��Ʈ�� �α� �޽��� ������
// 	if( m_bDebugPrintf == TRUE || bFlush == TRUE ) {
// 		printf( "%s" , string );
// 		// puts( string );
// 		/*
// 		char *pString=string;
// 		int string_length=strlen( string );
// 		for( int i=0 ; i < string_length ; ++i )
// 			putchar( *pString++ );
// 		*/
// 	}
// 
// #ifndef _WIN32
// 	semGive( m_semPrint );
// #endif
// }
// 
// //////////////////////////////////////////////////////////////////////////
// /*! \brief    CLogDebug::PrintScreenBuffer
// 		\author   ��ö��
// 		\return   void
// 		\version  0.0.68
// 		\date     2009-01-05 17:09:33
// 		\warning
// */
// void CLogDebug::PrintScreenBuffer()
// {
// 	unsigned char ch;
// 
// 	printf( "\n*Print the log message in the screen buffer..." );
// 	while( m_pScreenBuffer->DeQueueList( & ch ) ) {
// 		printf( "%1c" , ch );
// 	}
// }
// 
// //////////////////////////////////////////////////////////////////////////
// /*! \brief    CLogDebug::MakeScreenBuffer
// 		\author   ��ö��
// 		\return   void
// 		\version  0.0.71
// 		\date     2009-01-30 09:56:00
// 		\warning
// */
// void CLogDebug::MakeScreenBuffer( char *logfilename )
// {
// 	int iFdWrite;
// 	int iwrite;
// 	unsigned char ch;
// 	BOOL bLog=TRUE;
// 
// 	if( strcmp( logfilename, SCREEN_BUFFER_LOG_FILENAME ) != 0 )
// 		bLog = FALSE;
// 
// 	if( bLog ) printf( "\n*Make the log file before power-off" );
// 
// 	iFdWrite = open( logfilename, O_CREAT | O_RDWR, 644 );
// 	if( iFdWrite < 0 ) {
// 		if( bLog ) printf( "\n create error...[%d]" , iFdWrite );
// 	}
// 	else {
// 		// ���ۿ� �ִ� �����͸� ���� �ͼ� ����ϱ�
// 		while( m_pScreenBuffer->DeQueueList( & ch ) ) {
// 			// printf( "%1c" , ch );
// 			iwrite = write( iFdWrite, ( char *) & ch, 1 );
// 			if( iwrite != 1 ) {
// 				if( bLog ) printf( "\n error write...[%d, %d]" , iFdWrite, iwrite );
// 
// 				break;
// 			}
// 		}
// 
// 		_close( iFdWrite );
// 
// 		// �α� ������ �����ϰ� �Ѵ�.
// 		m_bLogPrintf = TRUE;
// 	}
// }