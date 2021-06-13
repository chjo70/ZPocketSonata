// BootShell.cpp: implementation of the CBootShell class.
//
//////////////////////////////////////////////////////////////////////

#include <time.h>
#include <ctype.h>
#include <stdio.h>

#include <ioLib.h>
#include <errnoLib.h>
#include <sysSymTbl.h>
#include <loadLib.h>
#include <usrLib.h>
#include <cacheLib.h>

#include <iv.h>
#include <sysLib.h>
#include <intLib.h>
#include <arch/ppc/vxPpcLib.h>
//#include "lsv70a.h"

#include <rebootLib.h>
//#include <usrConfig.h>

#include "prjParams.h"

#include "ManSbc.h"
//#include "ManFlash.h"

#include "./Untar/FileTar.h"

#include "BootShell.h"

//////////////////////////////////////////////////////////////////////////
// 전역 변수 및 객체 정의
CManSbc *theManSbc=0;
//CManFlash *theManFlash=0;
CBootShell *theBootShell=0;
CFileTar *theFileTar=0;

#ifdef __cplusplus
extern "C" {
#endif

IMPORT int USER_FLASH_Unlock();
IMPORT BOOT_PARAMS stBootParams;
void re();

void GetKey();


#ifdef __cplusplus
}
#endif



//////////////////////////////////////////////////////////////////////////
/*! \brief    BootShellMain
		\author   조철희
		\return   void
		\version  0.0.1
		\date     2008-04-18 09:58:51
		\warning
*/
void BootShellMain()
{
    
    theFileTar = new CFileTar;
    if( theFileTar == NULL ) {
        PrintErr( ( "\n [W] 기본 메모리가 부족합니다 !" ) );
        WhereIs;
    }

	theManSbc = new CManSbc;
	if( theManSbc == NULL ) {
		PrintErr( ( "\n [W] 기본 메모리가 부족합니다 !" ) );
		WhereIs;
	}

	theBootShell = new CBootShell;
	if( theBootShell == NULL ) {
		PrintErr( ( "\n [W] 기본 메모리가 부족합니다 !" ) ); 
		WhereIs;
	}

	theBootShell->Run();

    delete theFileTar;
    delete theBootShell;
    delete theManSbc;

}

void GetKey()
{
    int key;
    key = theManSbc->GetCommand();
    printf( "\n key=[%d]" , key );

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    Run
	\author   조철희
	\return   void
	\version  0.0.29
	\date     2008-07-10 16:03:52
	\warning
*/
void re()
{
	//theBootShell->Unload();
	//theBootShell->DeleteAllTask();
	//theBootShell->Run();
	// unld( )
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBootShell::CBootShell()
{


}

/**
 * @brief		~CBootShell
 * @return		
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2021/04/21 10:58:50
 * @warning		
 */
CBootShell::~CBootShell()
{

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CBootShell::Run
		\author   조철희
		\return   void
		\version  0.0.1
		\date     2008-04-18 09:59:26
		\warning
*/
void CBootShell::Run()
{
	UCHAR key;
	BOOL bRet;

	printf( "\n\n Get Command (Default=OFP Download/Run OFP in Flash) ? " );
	key = theManSbc->GetCommand();
    printf( "\n key=[%d]" , key );

    switch( key ) {
        case INSTALL_WEB :
            theManSbc->InstallWeb();
            break;

        case RUN_APP :
            theManSbc->RunApp( enTffsApp );
            break;

        case WRITE_APP_FLASH :
            theManSbc->DownloadApp();
            break;

        case DOWNLOAD_APP :
            theManSbc->DownloadApp();
            theManSbc->RunApp( enDownloadApp );
            break;

        default :
            break;
    }
    
}


