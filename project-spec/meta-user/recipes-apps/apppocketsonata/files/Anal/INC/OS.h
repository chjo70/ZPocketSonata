// TaskMsg.h: interface for the 타스크 간의 메시지 정의
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OS_H__F88C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_)
#define AFX_OS_H__F88C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_

#ifdef _VXWORKS_
#include <types/vxTypesOld.h>
#include "prjParams.h"

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

#elif defined(_GNUCC__)
#define WAIT_FOREVER		0
#endif

#endif // !defined(AFX_OS_H__F88C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_)
