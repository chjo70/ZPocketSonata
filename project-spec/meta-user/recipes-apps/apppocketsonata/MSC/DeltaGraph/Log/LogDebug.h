// LogDebug.h: interface for the CLogDebug class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGDEBUG_H__09A83AF4_4079_4FE7_ABD2_A7CB4D82ACB6__INCLUDED_)
#define AFX_LOGDEBUG_H__09A83AF4_4079_4FE7_ABD2_A7CB4D82ACB6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _WIN32
#include <semLib.h>


#define BOOT_SCREEN_CAPTURE			((unsigned char *) (NV_BOOT_BASE|0x1000))
#else

#define BOOT_SCREEN_CAPTURE			((unsigned char *) & m_buffer[0] )
#endif



//#include "./INC/Stack.h"




#ifdef __cplusplus
extern "C" {
#endif

int Printf( char *format, ... );
int WPrintf( char *format, ... );
void _LockPrint();
void _UnLockPrint();

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus

// class CLogDebug : public CTask
// {
// private:
// 	BOOL m_bLogPrintf;
// 	BOOL m_bDebugPrintf;
// 	SEM_ID m_semPrint;
// 
// 	CCircularQueue<unsigned char> *m_pScreenBuffer;
// 
// #ifdef _WIN32
// 	unsigned char m_buffer[10000];
// 
// #endif
// 
// public:
// 	inline void Timer() { }
// 
// #ifdef _WIN32
// 	inline void LockPrint() {  }
// 	inline void UnLockPrint() { }
// #else
// 	inline void LockPrint() { semTake( m_semPrint, WAIT_FOREVER ); }
// 	inline void UnLockPrint() { semGive( m_semPrint ); }
// #endif
// 
// 	inline void LogOnDebugPrint() { m_bDebugPrintf = TRUE; }
// 	inline void LogOffDebugPrint() { m_bDebugPrintf = FALSE; }
// 	inline void LogToggleDebugPrint() { if( m_bDebugPrintf == TRUE ) LogOffDebugPrint(); else LogOnDebugPrint(); }
// 
// 	void MakeScreenBuffer( char *logfilename=SCREEN_BUFFER_LOG_FILENAME );
// 	void PrintScreenBuffer();
// 	void DebugPrintf( char *string, BOOL bFlush=FALSE );
// 	void Run();
// 	inline BOOL ParseMessage(SQMsg *psqMsg ) { return FALSE; }
// 
// 	CLogDebug( char *pTaskName, int queue_size, int ring_size );
// 	virtual ~CLogDebug();
// 
// };

#endif

#endif // !defined(AFX_LOGDEBUG_H__09A83AF4_4079_4FE7_ABD2_A7CB4D82ACB6__INCLUDED_)
