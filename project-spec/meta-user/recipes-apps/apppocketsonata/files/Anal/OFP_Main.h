// Globals.h: interface for the Main Class
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OFP_MAIN_H__F88C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_)
#define AFX_OFP_MAIN_H__F88C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_

#include "./INC/OS.h"


#include "./INC/Macros.h"
#include "../include/Defines.h"
#include "./INC/PDW.h"
#include "./INC/Structs.h"
#include "./INC/ErrorMsg.h"

#include "./SigAnal/_Macro.h"
#include "./Collect/DataFile/DataFile.h"
#include "./SigAnal/_Struct.h"

#include "./EmitterMerge/IsNumber.h"




//////////////////////////////////////////////////////////////////////////
// 전역 변수



//////////////////////////////////////////////////////////////////////////
//

#if defined(_ELINT_)
#define LOCAL_DATA_DIRECTORY                    "\\\\192.168.0.41\\Files\\EPDW"
#define LOCAL_DATA_DIRECTORY_2                  "C:\\기타\\EPDW"

#define PDW_EXT									".epdw"


#elif defined(_XBAND_)
#define LOCAL_DATA_DIRECTORY                    "\\\\192.168.0.41\\Files\\EPDW"
#define LOCAL_DATA_DIRECTORY_2                  "C:\\기타\\EPDW"

#define PDW_EXT									".xpdw"


#elif defined(_POCKETSONATA_)
#define PDW_EXT									".zpdw"
#define MIDAS_EXT								"midas"

#define PDW_TYPE                                "pdw"
#define IQ_TYPE                                 "iq"

#elif defined(_701_)
#define PDW_EXT									".7pdw"
#define MIDAS_EXT								"midas"

#define PDW_TYPE                                "pdw"
#define IQ_TYPE                                 "iq"

#else
#define LOCAL_DATA_DIRECTORY                    "\\\\192.168.0.41\\Files\\SPDW"
#define LOCAL_DATA_DIRECTORY_2                  "C:\\기타\\SPDW"

#define PDW_EXT									".spdw"
#endif





#define CTRL_X									(24)
#define CTRL_Z									(26)

#define REBOOT									CTRL_X


#endif // !defined(AFX_OFP_MAIN_H__F88C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_)
