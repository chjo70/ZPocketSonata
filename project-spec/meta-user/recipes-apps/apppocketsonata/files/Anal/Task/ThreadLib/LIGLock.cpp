#include "stdafx.h"
#include "LIGLock.h"

#if defined(WIN32)
static volatile bool is_WIN32_WINNT_above_0x0600 = false;
//void CheckWindowsVersion()
//{
//	if (is_WIN32_WINNT_above_0x0600 == false)
//	{
//		OSVERSIONINFO osvi;
//		ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
//		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
//
//		::GetVersionEx(&osvi);
//
//		if (osvi.dwMajorVersion >= 6) //Windows Server 2008, Windows 7, Windows vista 이상인 경우
//		{
//			is_WIN32_WINNT_above_0x0600 = true;
//		}
//	}
//}
#endif
LIGLock::LIGLock()		{	
	::InitializeCriticalSection(&m_cs);	
}
LIGLock::~LIGLock()		{	
	::DeleteCriticalSection(&m_cs);		
}
void LIGLock::lock()		{	
	::EnterCriticalSection(&m_cs);		
}
void LIGLock::unlock()	{	
	::LeaveCriticalSection(&m_cs);		
}
//bool LIGLock::trylock()	{	
//	return (::TryEnterCriticalSection(&m_cs) != 0) ? true/*lock이 안되어 있어서 lock 했음*/ : false;	}