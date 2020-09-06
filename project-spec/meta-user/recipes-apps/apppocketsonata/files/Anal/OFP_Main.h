// Globals.h: interface for the Main Class
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OFP_MAIN_H__F88C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_)
#define AFX_OFP_MAIN_H__F88C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_

#include "./INC/OS.h"


#include "./INC/Macros.h"
#include "./INC/defines.h"
#include "./INC/PDW.h"
#include "./INC/structs.h"

#include "./INC/ErrorMsg.h"
#include "./INC/TaskMsg.h"


//////////////////////////////////////////////////////////////////////////
// 메크로 선언
//
#include "./SigAnal/_Type.h"
#include "./SigAnal/_Macro.h"
#include "./SigAnal/_Struct.h"

#include "./Identify/ELUtil.h"


// 기본 클래스 헤더 파일 추가함.
//#include "./TASK/ManTsk.h"
//#include "./TASK/LogDebug.h"
//#include "./TASK/GetPdw.h"
//#include "./TASK/SigAnal.h"
//#include "./TASK/LOBMngr.h"

//#include "Ini.h"


//#include "./COMMON/common.h"

//#include "./INC/Globals.h"



//////////////////////////////////////////////////////////////////////////
// 전역 변수



//////////////////////////////////////////////////////////////////////////
//
//#define DATA_DIRECTORY						"Z:\\기타\\EPDW"
#ifdef _ELINT_
#define LOCAL_DATA_DIRECTORY                    "\\\\192.168.0.41\\Files\\EPDW"
#define LOCAL_DATA_DIRECTORY_2                  "C:\\기타\\EPDW"

#define PDW_EXT									"EPDW"

#elif defined(_POCKETSONATA_)
#define LOCAL_DATA_DIRECTORY                    "/var/log/PPDW"
#define LOCAL_DATA_DIRECTORY_2                  "/var/log/PPDW"

#define PDW_EXT									"ppdw"

#else
#define LOCAL_DATA_DIRECTORY                    "\\\\192.168.0.41\\Files\\EPDW"
#define LOCAL_DATA_DIRECTORY_2                  "C:\\기타\\EPDW"

#define PDW_EXT									"XPDW"
#endif





#define CTRL_X									(24)
#define CTRL_Z									(26)

#define REBOOT									CTRL_X


#endif // !defined(AFX_OFP_MAIN_H__F88C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_)
