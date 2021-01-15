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


#include "./SigAnal/_Macro.h"

#ifdef _MIDAS_

#include "./SigAnal/_Struct.h"
#else
#include "./INC/TaskMsg.h"

#include "./SigAnal/_Type.h"
#include "./SigAnal/_Struct.h"

#include "./SigAnal/cencdec.h"

#include "./Identify/ELUtil.h"

#endif




//////////////////////////////////////////////////////////////////////////
// 전역 변수



//////////////////////////////////////////////////////////////////////////
//

#ifdef _ELINT_
#define LOCAL_DATA_DIRECTORY                    "\\\\192.168.0.41\\Files\\EPDW"
#define LOCAL_DATA_DIRECTORY_2                  "C:\\기타\\EPDW"

#define PDW_EXT									"EPDW"

#elif defined(_POCKETSONATA_)
#define LOCAL_DATA_DIRECTORY_2                  "/var/log/PPDW"

#define PDW_EXT									"zpdw"
#define MIDAS_EXT								"midas"

#define PDW_TYPE                                "pdw"
#define IQ_TYPE                                 "iq"

#else
#define LOCAL_DATA_DIRECTORY                    "\\\\192.168.0.41\\Files\\EPDW"
#define LOCAL_DATA_DIRECTORY_2                  "C:\\기타\\EPDW"

#define PDW_EXT									"XPDW"
#endif





#define CTRL_X									(24)
#define CTRL_Z									(26)

#define REBOOT									CTRL_X


#endif // !defined(AFX_OFP_MAIN_H__F88C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_)
