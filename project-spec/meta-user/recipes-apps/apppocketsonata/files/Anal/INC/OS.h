// TaskMsg.h: interface for the Ÿ��ũ ���� �޽��� ����
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OS_H__F88C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_)
#define AFX_OS_H__F88C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _WIN32
#include <types/vxTypesOld.h>

#include "prjParams.h"

#else
#define RING_ID					UINT
#define SEM_ID					UINT
#define IMPORT					extern
#define MSG_Q_ID				UINT
#define WAIT_FOREVER		0
#define VX_FP_TASK			0
#define timer_t					UINT
#define CLOCK_REALTIME	0
#define MODULE					char
#define NO_WAIT					0

//#define UDF_RAMDISK_FILENAME	"c:\\tftpboot\\udf_1.udf"
#define UDF_RAMDISK_FILENAME	"C:\\LMS\\EidFiles\\udf_1.udf"

#endif

#endif // !defined(AFX_OS_H__F88C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_)
