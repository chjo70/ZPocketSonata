/**

    @file      ManSbc.cpp
    @brief	   SBC 관련 함수 모음 입니다.
    @details   ~
    @author    조철희
    @date      17.04.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

#include "pch.h"


#include <stdio.h>

#ifdef __VXWORKS__
#include <pingLib.h>
#include <taskLib.h>
#include <ioLib.h>
#include <private/iosLibP.h>
#include <envLib.h>
#include <sysLib.h>
#include <symbol.h>
#include <symLib.h>
#include <sysSymTbl.h>
#include <loadLib.h>
#include <usrLib.h>
#include <tftpLib.h>
#include <ifLib.h>
#include <rebootLib.h>
#include "moduleLib.h"

#include <xbdBlkDev.h>
#include <dosFsLib.h>
#include <usrFsLib.h>

//#include <ramDiskCbio.h>
#include <ramDrv.h>
#include <tffs/tffsDrv.h>

#include <types/vxTypesOld.h>
#include <tyLib.h>

#include <nfs/nfsCommon.h>
#include <dirent.h>

#include <sntpcLib.h>

#include "prjParams.h"
#include "private/timeP.h"

#include "./pciDiag.h"

#elif defined(_MSC_VER)
#include <io.h>

#endif

#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include "ManSbc.h"
//#include "ManFlash.h"

#include "BootShell.h"


#include "./Untar/FileTar.h"

#include "../System/csysconfig.h"

#include "../Anal/INC/PDW.h"

#ifdef __cplusplus
extern "C" {
#endif

    bool g_bSNTP;

#ifdef __VXWORKS__
BOOT_PARAMS g_stBootParams;


IMPORT time_t sysRtcTimeGet( void );
IMPORT TIMELOCALE *__loctime;

#endif


extern STATUS sysTffsFormat (void);

#ifdef __cplusplus
}
#endif

extern CFileTar *g_theFileTar;

extern CManSbc *g_theManSbc;

extern CSysConfig *g_pTheSysConfig;


CUDPServer *CManSbc::m_pUDPServer=NULL;


#ifdef __VXWORKS__

/**
 * @brief     KeyboardHandler
 * @param     int i
 * @param     int ch
 * @return    unsigned int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-05 12:53:35
 * @warning
 */
BOOL CManSbc::KeyboardHandler( int i, int ch )
{
    BOOL bRet = FALSE;

    if( ch == REBOOT ) {
        //TRACE( "\n\n\n reboting...", 0, 0, 0, 0, 0, 0 );

        // m_pUDPServer->SendAllUDPServer();

#if 1
        // logMsg( "\n send reboot message to the taskMngr...", 0, 0, 0, 0, 0, 0 );
        //g_theManSbc->m_pUDPServer->SendAllUDPServer();
        //taskDelay( 10 );
//         for( int i = 0; i < 1000; ++i ) {
//             for( int j = 0; j < 1000; ++j );
//         }
        reboot( BOOT_CLEAR );
#else
        reboot( BOOT_CLEAR );

#endif

        bRet = TRUE;
    }
    //else if( ch == CTRL_Z ) {
    //         if( m_Log == FALSE ) {
    //             ConsoleStandardOut();
    //         }
    //         else {
    //             ConsoleStandardFile();
    //         }
    //
    //         m_Log = !m_Log;
    //         return TRUE;
    //}
    else {
        // printf( "\n ch[%d]", ch );
    }

    return bRet;

}

#endif

/**
 * @brief     CManSbc
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-05-30 09:25:28
 * @warning
 */
CManSbc::CManSbc()
{

    m_uiBoardID = 0;

    m_bPCIeInit[0] = false;
    m_bPCIeInit[1] = false;

#ifdef _NETMEM_
    m_pTheNetMem = new NetworkMemory( (char *) "127.0.0.1", NET_MEM_PORT );

    m_netCommand.offset = 0;
    m_netCommand.data = ( unsigned char * ) malloc( sizeof( struct STR_NETMEM ) );
#endif

#ifdef __VXWORKS__
    STATUS status;

	// VMEBusSystemReset();

    sysClkRateSet( TICK_COUNT );
    if( sysClkRateGet() != TICK_COUNT ) {
        printf( "\n [W] 토네이도의 Component에서 tick count를 100 으로 설정하세요." );
    }
    else {
        sysClkRateSet( TICK_COUNT );		// 1초당 100 tick 을 수행함.
    }

    // SNTP 를 이용해서 현재 시간을 읽어온다.
    // SetTimeBySNMP();

    //////////////////////////////////////////////////////////////////////////
    // NFS 드라이브 마운트
    // MountDrive();

    //////////////////////////////////////////////////////////////////////////
    // 기타 드라이브 생성
    MakeDrive();

    //////////////////////////////////////////////////////////////////////////
    // PCI 초기화
    // 로직과 PCI 버스간이 아직 동기화 되지 않아서 늦게 호출하도록 합니다.
    PCIConfigSetting();


	//memcpy( & m_ProgInfo, (char *) FLASH_PRGINFO_ADRS, sizeof( STR_PRG_INFO ) );
	//printf( "\n FLASH_PRGINFO_ADRS[%x]" , FLASH_PRGINFO_ADRS );
/*

	if( FALSE == CreateRamDisk( LOGDISK, 1024, 14336, 14336 ) ) {
		printf( "\n[W] 로그용 램드스크가 생성하지를 못했습니다." );
		WhereIs;
	}
*/

	// boot parameter 를 읽어온다.
	//char *bootString=BOOT_LINE_ADRS;
	//if( ( bootString != NULL ) && ( *bootString != EOS ) )
		//strcpy( BOOT_LINE_ADRS, bootString );

  /* interpret boot command */
	//if( usrBootLineCrack( BOOT_LINE_ADRS, & stBootParams ) != OK ) {
		//PrintErr( ( "\n [W] 부트 페라미터값이 잘못 설정되었습니다 !" ) );
		//return;
	//}
	//*/

	// 시간 함수의 환경 변수를 설정한다.
	// InitSystemVariable();

    // IP address 설정


#endif

#ifdef _NETMEM_
    // NET 커맨드 옵셋 설정
    m_netCommand.offset = m_uiBoardID;

    // 넷 메모리에 보드 ID 저장
    m_strMemory.uiSBCID = m_uiBoardID;

    //
    memcpy( m_netCommand.data, & m_strMemory, sizeof( m_strMemory ) );
    m_pTheNetMem->UpdatePage( & m_netCommand );

#endif

#ifdef __VXWORKS__
    char szHostname[100];

    // SBC 에 Host명을 기입
    sprintf( szHostname, "SBC_%d", m_uiBoardID );
    //sethostname( szHostname, strlen( szHostname ) );

#endif

    KeyboardHooking();

}

/**
 * @brief		~CManSbc
 * @return
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2021/04/15 12:21:08
 * @warning
 */
CManSbc::~CManSbc()
{

#ifdef _NETMEM_
    delete m_pTheNetMem;

#endif

#ifdef _MSC_VER
    delete m_pUDPServer;

#endif

}

/**
 * @brief     MakeDrive
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-09-12 16:09:02
 * @warning
 */
void CManSbc::MakeDrive()
{
    // 램 드라이브를 생성 합니다.
    if( FALSE == CreateRamDisk( RAMDRV, 1024, 20000, 20000 ) ) { // 14336, 14336, 22000
        printf( "\n[W] Application/UDF용 램 디스크가 생성하지 못했습니다." );
        WhereIs;
    }

    // TFFS 드라이브를 생성 합니다.
    if( FALSE == CreateTffsDisk( TFFSDRV ) ) {
        printf( "\n[W] Application/UDF용 롬 디스크가 생성하지 못했습니다." );
        WhereIs;
    }
    else {

    }

#ifdef ATADRV
    // ATA 드라이브를 생성 합니다.
    if( FALSE == CreateAtaDisk( (char *) ATADRV ) ) {
        printf( "\n[W] Application/UDF용 롬 디스크가 생성하지 못했습니다." );
        WhereIs;
    }
    else {

    }
#endif

}

/**
 * @brief     GetIPAddress
 * @param     char * pszIPAddress
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-04 11:35:51
 * @warning
 */
void CManSbc::GetIPAddress( char *pszIPAddress )
{

    pszIPAddress[0] = 0;

#ifdef __VXWORKS__
    ifAddrGet( ( char * ) "memac0", pszIPAddress );

#else
    char name[255];
    PHOSTENT hostinfo;
    CString strIpAddress = "";

    if( gethostname( name, sizeof( name ) ) == 0 ) {
        if( ( hostinfo = gethostbyname( name ) ) != NULL ) {
            strIpAddress = inet_ntoa( *( struct in_addr * ) *hostinfo->h_addr_list );
            strcpy( pszIPAddress, ( LPSTR ) ( LPCTSTR ) strIpAddress );
        }

    }

#endif

}

/**
 * @brief		GetCommand
 * @return		UCHAR
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2021/04/15 12:21:01
 * @warning
 */
UCHAR CManSbc::GetCommand()
{
    UCHAR uRet = RUN_APP;
    UCHAR key;

    unsigned int uiTFFSBoot;

#if 0
    key = Getche( KEYBOARD_TIMEOUT );

#else

    while( true ) {
        Sleep( 1 );
        printf( "." );
        key = m_pUDPServer->GetKey();
        if( key >= KEY_TIMEOUT ) {
            break;
        }
    }

#endif

    printf( "\nGetche key[%d;%1c]", key, key );

    switch( tolower( key ) ) {
        case 'w':
            WhereIs;
            uRet = INSTALL_WEB;
            break;

        case '!':
            WhereIs;
            uRet = WRITE_APP_FLASH;
            break;

        case 'z':
            uRet = DOWNLOAD_UTEST_PROG;
        case 'x':
            uRet = WRITE_UTEST_PROG;
        case 'c':
            uRet = RUN_UTEST_PROG;

        case 'n':
            uRet = WRITE_BOOT_PROG;
            break;

        case '0':
            uRet = DOWNLOAD_APP;
            break;

        case 'd':
            uRet = DEBUG_APP;
            break;

        case '1':
            uRet = RUN_APP;
            WhereIs;
            break;

        default:
            /*! \bug  명령어 디버깅용으로 사용함.
                    \date 2008-07-03 10:42:35, 조철희
            */
            uiTFFSBoot = g_pTheSysConfig->GetTFFSBoot();

            g_pTheSysConfig->SetTFFSBoot( uiTFFSBoot );

            if( uiTFFSBoot == RUN_APP ) {
                uRet = RUN_APP;
            }
            else {
                uRet = DOWNLOAD_APP;
            }
            break;
    }

	return uRet;

}

/**
 * @brief     Getche2
 * @param     int sec
 * @return    UCHAR
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-09-03 14:19:51
 * @warning
 */
UCHAR CManSbc::Getche2( int sec )
{
	char cChar=0;
	fd_set rdfs;
	int numReady;
	struct timeval tclSelectTimeout;

	char buff[255] = { 0 };

	FD_ZERO( & rdfs );
	FD_SET( 0, & rdfs );

	tclSelectTimeout.tv_sec = (long) sec;
	tclSelectTimeout.tv_usec = (long) 0;

	numReady = select( 1, & rdfs, NULL, NULL, & tclSelectTimeout );

	if( numReady > 0 ) {
		fgets( buff, sizeof(buff), stdin );

		// len = strlen( buff ) - 1;
		printf( "\n cChar[%s]\n" , buff );
	}

	return cChar;

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CManSbc::Getche
    \author   조철희
    \param    sec 인자형태 int
    \return   UCHAR
    \version  0.0.1
    \date     2008-04-18 10:26:38
    \warning
*/
UCHAR CManSbc::Getche( int sec )
{
    char cChar;

#ifdef __VXWORKS__
	int stdInFd, numReady;
	struct timeval tclSelectTimeout;
    fd_set readFds;
    int save_options;

    TY_DEV_ID pTyDev;
    RING_ID ringId;
    char  ccc;

    int tShell_priority;

    char buffer[200];

    //taskPriorityGet( 0, &tShell_priority );
    //printf( "\n tShell_priority priority[%d]" , tShell_priority );

	stdInFd = ioTaskStdGet( taskNameToId( (char *) "tShell0" ), 0 );

	/* Save options */
    save_options = ioctl( stdInFd, FIOGETOPTIONS, 0 ); /* current console */
	// printf( "\n save_options[%x], new_option[%x]" , save_options, OPT_TERMINAL & ~OPT_LINE & ~OPT_ECHO );
	ioctl( stdInFd, FIOSETOPTIONS, OPT_TERMINAL & ~OPT_LINE & ~OPT_ECHO );

    /* Enter raw mode */
    // ioctl (stdInFd, FIOSETOPTIONS, OPT_TERMINAL & ~OPT_LINE & ~OPT_ECHO );

    tclSelectTimeout.tv_sec = ( long ) sec;
    tclSelectTimeout.tv_usec = ( long ) 0;

    FD_ZERO( & readFds );
    FD_SET( stdInFd, &readFds );

    cChar = 0;

#ifdef INCLUDE_SHELL
	TASK_ID taskID=taskNameToId( (char *) "tShell0" );
	taskSuspend( taskID );
	//int tShell_priority;

	//taskPriorityGet( taskNameToId( (char *) "tShell0" ), & tShell_priority );
    //printf( "\n tShell0 priority[%d]" , tShell_priority );
	//taskPrioritySet( taskNameToId( (char *) "tShell0" ), 255 );
#endif

    ioctl( stdInFd, FIORFLUSH, 0 );

    numReady = select( FD_SETSIZE, &readFds, NULL, NULL, &tclSelectTimeout );

    if( numReady > 0 ) {
        //tyIRd( pTyDev, cChar );
        //printf( "\n cChar[%d]\n" , cChar );

        read( stdInFd, & cChar, 1 );           /* read the key just hit */
		//printf( "\n cChar[%d]\n");
	}

	/* Leave raw mode */
	ioctl( stdInFd, FIOSETOPTIONS, save_options );
	ioctl( stdInFd, FIOFLUSH, 0 );


#ifdef INCLUDE_SHELL
	// taskPrioritySet( taskNameToId( (char *) "tShell0" ), tShell_priority );
	taskResume( taskID );
#endif


#else
    cChar = 0;

#endif

	return (UCHAR) cChar;
}

/**
 * @brief		CreateTffsDisk
 * @param		char * szDiskName
 * @return		bool
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2021/04/15 13:54:51
 * @warning
 */
bool CManSbc::CreateTffsDisk( char *szDiskName )
{
    long lFreeSpace;

    lFreeSpace = DiskFreeSpace( szDiskName );

    if( lFreeSpace >= 0 ) {
		printf( "\n\n\n [%s] 드라이브에 남은 공간이 [%4ld MByte] 있습니다.", szDiskName, lFreeSpace/1024/1024 );
    }
    else {
        //////////////////////////////////////////////////////////////////////////
        // 드라이브를 생성합니다.
        printf( "\n VxWorks 컴포넌트(VXBFLASH_CFG_STR)에 정의된 크기로 플레쉬 메모리를 포멧합니다...\n" );

        // 아래와 같이 수행이 안 되면 콘솔에서 아래와 같이 입력한다. 소요 시간은 약 6분 정도 입니다.
        // sysTffsFormat 0
        // usrTffsConfig 0,0, "/tffs0"
        // dosFsVolFormat "/tffs0"

        // sysTffsFormat 1
        // usrTffsConfig 1, 0, "/tffs1"
        // dosFsVolFormat "/tffs1"

        //usrTffsConfig( 0, 0, szDiskName );

        //dosFsVolFormat( szDiskName, DOS_OPT_DEFAULT, ( FORMAT_PTR) 0 );

        printf( "\n\n\n rebotting please...\n" );
        while( true );

    }

    return lFreeSpace != -1;

}

/**
 * @brief     CreateTffsDisk
 * @param     char * szDiskName
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-30 11:52:29
 * @warning
 */
bool CManSbc::CreateAtaDisk( char *szDiskName )
{
    long lFreeSpace;

    lFreeSpace = DiskFreeSpace( szDiskName );

    if( lFreeSpace >= 0 ) {
        printf( "\n\n\n [%s] 드라이브에 남은 공간이 [%ld MByte] 있습니다.", szDiskName, lFreeSpace/1024/1024 );
    }
    else {
        //printf( "\n\n\n rebotting please...\n" );
        //while( true );

    }

    return lFreeSpace != -1;

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CManSbc::CreateRamDisk
	\author   조철희
	\param    szDiskName 인자형태 char *
	\param    bytesPerBlk 인자형태 int
	\param    blksPerTrack 인자형태 int
	\param    nBlocks 인자형태 int
	\return   void
	\version  0.0.1
	\date     2008-04-18 10:41:18
	\warning
*/
bool CManSbc::CreateRamDisk( char *szDiskName, int bytesPerBlk, int blksPerTrack, int nBlocks )
{
#ifdef __VXWORKS__
    char szRamDevs[100];

	BLK_DEV *pBlkDev;
	DOS_VOL_DESC *pVolDesc;

	UINT ramdisk_address;

	//ramdisk_address = DRAM_SIZE - USER_RESERVED_MEM;
	ramdisk_address = 0;
	printf( "\n\n" );
	printf( "\nDRAM_SIZE[%x], USER_RESERVED_MEM[%x]" , DRAM_SIZE, USER_RESERVED_MEM );
	printf( "\nramdisk address[%8x]\n" , ramdisk_address );
	pBlkDev = ramDevCreate( (char *) ramdisk_address, bytesPerBlk, blksPerTrack, nBlocks, 0 );

	if( pBlkDev == NULL ) {
		printf( "\n [W] 램디스크 생성 실패..." );
		return false;
	}

    xbdBlkDevCreateSync( pBlkDev, szDiskName );

    sprintf( szRamDevs, "%s%s", szDiskName, RAMDRV_NO );

    dosFsVolFormat( szRamDevs, DOS_OPT_BLANK, (FORMAT_PTR) 0 );

	// VxWorks 에서 shell component 를 추가하지 않으면 에러가 발생함.
	long lFreeSpace;
	lFreeSpace = DiskFreeSpace( szRamDevs );
    printf( "\n\n\n [%s] 드라이브에 남은 공간이 [%ld MByte] 있습니다.", szDiskName, lFreeSpace/1024/1024 );

#endif

	return true;

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CManSbc::DiskFreeSpace
	\author   조철희
	\param    szDiskName 인자형태 char *
	\return   long
	\version  0.0.1
	\date     2008-04-18 10:51:38
	\warning
*/
long CManSbc::DiskFreeSpace( char *szDiskName )
{
	long lDiskFreeSpace=-1;

#ifdef __VXWORKS__
	struct statfs SStatFs;

	if( statfs( szDiskName, & SStatFs )==OK ) {
		lDiskFreeSpace = (long) ( (float) SStatFs.f_bsize * (float) SStatFs.f_bavail );
	}
	else {
		perror( "szDiskName" );
		printf( "\n [W] [%s] 드라이브가 잘못됐습니다. ", szDiskName );
	}
#endif

	return lDiskFreeSpace;
}

/**
 * @brief		SetTimeBySNMP
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2008-11-11 10:25:36
 * @warning
 */
bool CManSbc::SetTimeBySNMP()
{
    bool bRet = true;

    int iTry;
	UINT _date, _time;

	STATUS sntpc_status, settime_status;
	struct timespec tspec;

    g_bSNTP = false;

	// InitSystemVariable();
	putenv( (char *) "TIMEZONE=KST::-540.000000:000000" );

    printf( "\n\n##### SNTP 프로토콜을 사용해서 타임 서버[%s]로 SBC 현재 시간을 설정합니다.\n" , g_pTheSysConfig->GetCCUServerOfNetwork() );

    // 이놈의 vxworks 7은 왜 2번을 수행해야 얻어 오는지....
    if( true == CheckPing( g_pTheSysConfig->GetCCUServerOfNetwork() ) ) {
        iTry = 0;
        do {
#ifdef _MSC_VER
            sntpc_status = -1;
#else
            sntpc_status = sntpcTimeGet( g_pTheSysConfig->GetCCUServerOfNetwork(), 3 * OS_ONE_SEC, & tspec );
            //sntpc_status = sntpcTimeGet( g_pTheSysConfig->GetDebugServerOfNetwork(), 3 * OS_ONE_SEC, & tspec );
#endif
            printf( "*" );

            ++ iTry;

        } while( iTry <= TRY_GETSNTP && sntpc_status != OK );
    }

    if( sntpc_status != OK ) {
        printf( "\n\n##### SNTP 프로토콜을 사용해서 타임 서버[%s]로 SBC 현재 시간을 설정합니다.\n", g_pTheSysConfig->GetDebugServerOfNetwork() );
        iTry = 0;
        do {
#ifdef _MSC_VER
            sntpc_status = -1;
#else
            sntpc_status = sntpcTimeGet( g_pTheSysConfig->GetDebugServerOfNetwork(), 3 * OS_ONE_SEC, & tspec );
#endif
            printf( "*" );

            ++ iTry;

        } while( iTry <= TRY_GETSNTP && sntpc_status != OK );
    }

	if( sntpc_status != OK ) {

        printf( "\n" );
		printf( "\n [W] SNTPctimeGet failed...%s" , g_pTheSysConfig->GetRecentConnectionOfNetwork() );
		printf( "\n Returned sntpc_status: %i errno: %s", sntpc_status, strerror(errno) );
        printf( "\n" );

        // 현재 시간을 최근 운용모드 시작한 시간으로 설정 합니다.
        g_pTheSysConfig->GetPresentTime( & tspec );

		/*
        time_t result, recent_time=0;

        struct dirent *pLogEntry;
        DIR *pSystemLogDir;

		if( ( pSystemLogDir = opendir( SYSTEM_LOG_DIRECTORY ) ) != NULL ) {
			time_t entry_delete_time;

			while( ( pLogEntry = readdir( pSystemLogDir ) ) != NULL ) {
				if( OK == IsFile( pLogEntry->d_name ) ) {
					entry_delete_time = GetLastAccessTime( pLogEntry->d_name );

					if( recent_time < entry_delete_time || recent_time == 0 ) {
						recent_time = entry_delete_time;
						// printf( "\n pLogEntry->d_name[%s]" , pLogEntry->d_name );
					}
				}

			}
		}
		*/

		//_date = GetDate( creationDate );
		//_time = GetTime( creationDate+13 );
		//SetRtcClock( _date, _time );
		//result = GetRtcTime();

		//if( recent_time != 0 && result <= recent_time ) {
		//	Time2DateTime( & _date, & _time, recent_time );
		//	SetRtcClock( _date, _time );

		//	/* get current time from clock */
		//	result = GetRtcTime();
		//}

		// 부팅 시간을 고려해서 1분 정도 시간 지연을 해서 설정하게 한다.
		//result = sysRtcTimeGet();
		//tspec.tv_sec = result + BOOTING_TIME;
		//tspec.tv_nsec = 0;
		//settime_status = clock_settime( CLOCK_REALTIME, & tspec );

/*
		time_t now;
		struct tm *pLocalTime;
		now = time(NULL);
		pLocalTime = localtime( & now );
		printf( "%02d/%02d/%02d %02d:%02d:%02d, ", pLocalTime->tm_year%100, pLocalTime->tm_mon+1, pLocalTime->tm_mday, pLocalTime->tm_hour, pLocalTime->tm_min, pLocalTime->tm_sec );

		pLocalTime = gmtime( & now );
		printf( "%02d/%02d/%02d %02d:%02d:%02d", pLocalTime->tm_year%100, pLocalTime->tm_mon+1, pLocalTime->tm_mday, pLocalTime->tm_hour, pLocalTime->tm_min, pLocalTime->tm_sec );
*/

		//Time2DateTime( & date, & time, tspec.tv_sec );
		//SetRtcClock( date, time );
	}

#ifdef __VXWORKS__
	settime_status = clock_settime( CLOCK_REALTIME, & tspec );
	if( settime_status != OK ) {
		printf("\n [W] Clock_settime failed..." );
		printf("\n Returned settime_status: %i errno: %s", settime_status, strerror(errno) );
	}
	else {
        struct tm *pstTime;
        char buffer[100];

        g_bSNTP = true;

		// InitSystemVariable();
		//Time2DateTime( & _date, & _time, tspec.tv_sec );
		//SetRtcClock( _date, _time );
		time_t ti=time(NULL);

        pstTime = localtime( & ti );
        strftime( buffer, 100, "%Y-%m-%d %H:%M:%S", pstTime );

		printf( "완료[%s, %d].\n" , buffer, ti );
    }

#endif

    bRet = ( sntpc_status == OK );

    return bRet;

}

/**
 * @brief     AutoIPAddress
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-09-25 16:57:03
 * @warning
 */
void CManSbc::AutoIPAddress()
{

    if( m_uiBoardID != 0 ) {
        char szBuffer[200];
        int iFromAddress;

        iFromAddress = g_pTheSysConfig->GetSBCFromIP();

        sprintf( szBuffer, "192.168.0.%d", iFromAddress + m_uiBoardID - 1 );

#ifdef __VXWORKS__
        //ifMaskSet( (char *) "memac0", 0xffffff00 );
        ifAddrSet( (char *) "memac0", szBuffer );
        //ifAddrGet( (char *) "memac0", ip_addr );
#else


#endif
        printf( "\nSBC 의 IP 설정을 [%s]로 자동 설정합니다.\n\n", szBuffer );
    }
    else {
        printf( "\n IP 설정을 U-Boot에 설정된 값으로 설정합니다." );
    }

    // IP 변경 후 일정 시간 후에 네트워크를 설정 합니다.
    //Sleep( 5 );

}

/**
 * @brief     CreateUDPServer
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-09-25 16:58:04
 * @warning
 */
void CManSbc::CreateUDPServer()
{
    char szSelfIPAddress[100];

    GetIPAddress( szSelfIPAddress );

    // UDP 서버 포트
    m_pUDPServer = new CUDPServer( szSelfIPAddress, 3000 );

}

/**
 * @brief		InstallWeb
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2021/04/15 15:32:18
 * @warning
 */
void CManSbc::InstallWeb()
{
	STATUS stat;

    char szRamDrvFilename[100];
    char szSrcFilename[100], szDstFilename[100];

    printf( "\n" );
    // 백업
    // 라이브러리를 백업한다.
#if TOOL==diab
    printf( "\n\n 1. 백업을 수행 합니다..." );
#else
    printf( "\n\n 1. Backup the files..." );
#endif

    sprintf( szDstFilename, "%s%s/%s" , RAMDRV, RAMDRV_NO, SQLITE_DIRECTORY );
#ifdef __VXWORKS__
#if defined(__LP64__)
    mkdir( szDstFilename, 0666 );
#else
    mkdir( szDstFilename );
#endif
#endif

    sprintf( szSrcFilename, "%s/%s/%s" , ATADRV, SQLITE_DIRECTORY, CEDEOB_SQLITE_FILENAME );
    sprintf( szDstFilename, "%s%s/%s/%s" , RAMDRV, RAMDRV_NO, SQLITE_DIRECTORY, CEDEOB_SQLITE_FILENAME );
    stat = CopyToFile( szSrcFilename, szDstFilename );
    // INI 파일을 백업한다.
    sprintf( szDstFilename, "%s%s/%s" , RAMDRV, RAMDRV_NO, INI_DIRECTORY );
#ifdef __VXWORKS__
#if defined(__LP64__)
    mkdir( szDstFilename, 0666 );

#else
    mkdir( szDstFilename );
#endif
#endif
    sprintf( szSrcFilename, "%s/%s/%s" , ATADRV, INI_DIRECTORY, INI_FILENAME );
    sprintf( szDstFilename, "%s%s/%s/%s" , RAMDRV, RAMDRV_NO, INI_DIRECTORY, INI_FILENAME );
    stat = CopyToFile( szSrcFilename, szDstFilename );

    // 포멧 ...
    printf( "\n\n 2. TFFS 드라이브를 포멧합니다..." );

#if defined(__VXWORKS__) || defined(__linux__)
    dosFsVolFormat( TFFSDRV, DOS_OPT_DEFAULT, (FORMAT_PTR) 0 );
#endif

    // 압축된 파일을 추출합니다.
    printf( "\n\n 3. TAR 파일을 풉니다..." );
    sprintf( szRamDrvFilename, "%s%s/%s" , RAMDRV, RAMDRV_NO, WEB_FILENAME );

#if defined(__VXWORKS__) || defined(__linux__)
    char szRamDrvWebfolder[100];
    char sztffs0Webfolder[100];

    if( true == DownloadfromTftp( WEB_FILENAME, (char *) szRamDrvFilename, g_pTheSysConfig->GetDebugServerOfNetwork() ) ) {
        //sprintf( szRamDrvWebfolder, "%s%s" , RAMDRV, RAMDRV_NO );
        sprintf( szRamDrvWebfolder, "%s", ATADRV );
        printf("\n TAR 파일[%s]을 풀어서 설치합니다." , szRamDrvWebfolder );

        sprintf( sztffs0Webfolder, "%s" , ATADRV );
        g_theFileTar->UnTar( szRamDrvFilename, sztffs0Webfolder );

        unlink( szRamDrvFilename );
    }
    else {
        printf("\n [W] 웹 페이지를 설치하지 못했습니다." );

    }
#endif

    // 복구
    // 라이브러리
    /*
    printf( "\n\n 4. 복구을 수행 합니다..." );

    sprintf( szSrcFilename, "%s%s/%s/%s" , RAMDRV, RAMDRV_NO, SQLITE_FOLDER, CEDEOB_SQLITE_FILENAME );
    sprintf( szDstFilename, "%s/%s/%s" , TFFSDRV, SQLITE_FOLDER, CEDEOB_SQLITE_FILENAME );
    stat = CopyFile( szSrcFilename, szDstFilename );
    // INI 파일
    sprintf( szSrcFilename, "%s%s/%s/%s" , RAMDRV, RAMDRV_NO, INI_FOLDER, INI_FILENAME );
    sprintf( szDstFilename, "%s/%s/%s" , TFFSDRV, INI_FOLDER, INI_FILENAME );
    stat = CopyFile( szSrcFilename, szDstFilename );
    */

    printf( "\n\n\n\n ****** 설치 완료 했습니다. 재부팅하세요...******\n\n" );

}

/**
 * @brief		파일을 복사합니다.
 * @param		const char * src_file
 * @param		const char * dest_file
 * @return		int
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2022/12/14 18:51:05
 * @warning
 */
int CManSbc::CopyToFile( const char *src_file, const char *dest_file )
{
	printf( "\n" );
#ifdef __VXWORKS__
    STATUS stat = cp( src_file, dest_file );
	if( stat == OK ) {
		printf( "원본 파일(%s)을 대상 파일(%s)에 성공적으로 복사 했습니다.\n" , src_file, dest_file );
	}
	else {
		printf( "원본 파일(%s)을 대상 파일(%s)에 실패 했습니다.\n" , src_file, dest_file );
	}

    return stat;

#else
    printf( "\n원본 파일(%s)을 대상 파일(%s)에 성공적으로 복사 했습니다.\n", src_file, dest_file );

    return 0;

#endif

}

/**
 * @brief		랜으로 다운로드하여 운용 프로그램을 롬드라이브에 복사합니다.
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2021/04/19 16:55:31
 * @warning
 */
void CManSbc::DownloadAndROMWriteApp()
{
    char szImageFilename[100];

    sprintf( szImageFilename, "%s%s/%s" , ATADRV, IMAGE_FOLDER, APP_FILENAME );

    printf( "\n 운용 소프트웨어 이미지를 SATA 드라이브[%s]에 저장합니다.", szImageFilename );

#ifdef __VXWORKS__
    char *pTFTPIPAddress;

    pTFTPIPAddress = g_pTheSysConfig->GetDebugServerOfNetwork();
    if( true == DownloadfromTftp( APP_FILENAME, (char *) szImageFilename, pTFTPIPAddress ) ) {
    	printf("\n\n *** 운용 소프트웨어를 설치 완료 했습니다. ***" );

    }
    else {
        printf("\n [W] 운용 소프트웨어를 설치하지 못 했습니다 !!!" );

    }

#else
    printf( "\n\n *** 운용 소프트웨어를 설치 완료 했습니다. ***" );

#endif


}

/**
 * @brief		DownloadApp
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2021/04/19 16:55:31
 * @warning
 */
void CManSbc::DownloadApp()
{
    char szRAMDrvFilename[100];

    sprintf( szRAMDrvFilename, "%s%s/%s" , RAMDRV, RAMDRV_NO, APP_FILENAME );

    printf( "\n tftp 를 이용해서 App 프로그램을 램 드라이브[%s]에 설치 합니다..", szRAMDrvFilename );

#ifdef __VXWORKS__
    if( true == DownloadfromTftp( APP_FILENAME, (char *) szRAMDrvFilename, g_pTheSysConfig->GetDebugServerOfNetwork() ) ) {
    	//printf("\n\n *** 운용 소프트웨어를 메모리에 다운로드 완료 했습니다. ***" );
    }
    else {
        printf( "\n [W] 운용 소프트웨어를 메모리에 다운로드하지 못 했습니다 !!!\n\n" );
    }

#else
    printf( "\n\n *** 운용 소프트웨어를 메모리에 다운로드 완료 했습니다. ***" );

#endif


}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CBootShell::DownloadfromTftp
	\author   조철희
	\param    tftpfilename 인자형태 char *
	\param    ramfilename 인자형태 char *
	\return   bool
	\version  0.0.1
	\date     2008-04-18 10:58:31
	\warning
*/
bool CManSbc::DownloadfromTftp( char *tftpfilename, char *pFilename, char *pTFTPServerIP )
{
	bool bret=true;

#ifdef __VXWORKS__
	int iFdWrite;
	int	iStatus;

    TFTP_DESC *spTftpDesc;

	if ( (spTftpDesc = tftpInit() ) == NULL ) {
		WhereIs;
		return FALSE;
	}

    // tftpInfoShow( spTftpDesc );

	printf( "\n 호스트 IP     : [ %s ]", pTFTPServerIP );
	printf( "\n 롬 파일명     : [ %s ]", tftpfilename );

	/*	tftp 설정을 초기화 */
	if( ( tftpPeerSet (spTftpDesc, pTFTPServerIP, TFTP_PORT ) == ERROR ) ||
		( tftpModeSet (spTftpDesc, TFTP_MODE ) == ERROR ) ) {
		(void) tftpQuit (spTftpDesc);

        WhereIs;
		return FALSE;
	}

	/* 파일 Open */
    unlink( pFilename );

#if 1
	iFdWrite = open( pFilename, O_CREAT | O_RDWR | O_BINARY, 0666 );
    if (iFdWrite == ERROR) {
        PrintErr( ( "\n [W] 파일[%s] 에러입니다.", pFilename ) );
        return FALSE;
    }
#else
    iFdWrite = fopen( pFilename, "wb" );
    if( iFdWrite == NULL ) {
        PrintErr( ( "\n [W] 파일[%s] 에러입니다.", pFilename ) );
        return FALSE;
    }

#endif

	// printf( "\n spTftpDesc[%p], iFdWrite[%d], tftpfilename[%s]" , spTftpDesc, iFdWrite, tftpfilename );
	if(	( iStatus = tftpGet( spTftpDesc, tftpfilename, iFdWrite, TFTP_CLIENT ) ) == ERROR ) {
		bret = false;
		switch( errnoGet() ) {
			case S_tftpLib_INVALID_DESCRIPTOR :
				WhereIs;
				break;
			case S_tftpLib_UNKNOWN_HOST :
				WhereIs;
				break;

			case S_tftpLib_NOT_CONNECTED :
#if TOOL==diab
				printf( "\n Check the LAN cables...[%x]" , errnoGet() );
				printf( "\n Press any key for trying..." );
#else
				printf( "\n 랜 케이블을 확인하세요...[%x]" , errnoGet() );
				printf( "\n 키를 누르면 다시 한번 시도합니다." );
#endif
				GetCharX;
				break;

			case S_tftpLib_TIMED_OUT :
#if TOOL==diab
				//printf( "\n PC에 TFTPD을 실행시켜주세요...[%x]" , errnoGet() );
				printf( "\n Press any key for trying..." );
#else
				printf( "\n PC에 TFTPD을 실행시켜주세요...[%x]" , errnoGet() );
				printf( "\n 키를 누르면 다시 한번 시도합니다." );
#endif
				GetCharX;
				break;

			case S_tftpLib_TFTP_ERROR :
#if TOOL==diab
				//printf( "\n 다운로드할 파일명이 없습니다. !" );
				//printf( "\n tftp 의 경로명을 확인해주세요." );
#else
				printf( "\n 다운로드할 파일명이 없습니다. !" );
				printf( "\n tftp 의 경로명을 확인해주세요." );
#endif
				break;

			case 380002 :
#if TOOL==diab
				//printf( "\n 파일 용량이 너무 큽니다.[%x]" , errnoGet() );
				//printf( "\n 장치 개발자에게 문의하세요..." );
#else
				printf( "\n 파일 용량이 너무 큽니다.[%x]" , errnoGet() );
				printf( "\n 장치 개발자에게 문의하세요..." );
#endif
				GetCharX;
				break;

			case 0x43 :
#if TOOL==diab
				//printf( "\n 랜 케이블을 확인하거나 PC에 TFTPD을 실행시켜 주세요...[%x]" , errnoGet() );
				//printf( "\n 키를 누르면 다시 한번 시도합니다." );
#else
				printf( "\n 랜 케이블을 확인하거나 PC에 TFTPD을 실행시켜 주세요...[%x]" , errnoGet() );
				printf( "\n 키를 누르면 다시 한번 시도합니다." );
#endif
				GetCharX;
				break;

			default :
				printf( "\n errno[%x]" , errnoGet() );
				WhereIs;
				break;

		}

	}

#if 1
	close( iFdWrite );
#else
	fclose( iFdWrite );

#endif

	(void) tftpQuit( spTftpDesc );

	printf( "\n\n" );

#endif

	return bret;

}


//////////////////////////////////////////////////////////////////////////
/*! \brief    CBootShell::RunProcess
    \author   조철희
    \return   void
    \version  0.0.1
    \date     2008-04-18 11:25:39
    \warning
*/
void CManSbc::RunApp( enWhatDrvAPP enApp )
{
    char szDrvAppFilename[100];
    if( enApp == enDownloadApp ) {
        sprintf( szDrvAppFilename, "%s%s/%s", RAMDRV, RAMDRV_NO, APP_FILENAME );
    }
    else {
        sprintf( szDrvAppFilename, "%s%s/%s", ATADRV, IMAGE_FOLDER, APP_FILENAME );
    }

#ifdef __VXWORKS__
	SYM_TYPE symType;
	STATUS stResult;
	char *pSpawnFuncName;

	TASK_ID tID;

    MODULE *pModuleId;

	pModuleId = ld( ALL_SYMBOLS, 0, szDrvAppFilename );

	if( pModuleId == NULL ) {
		printf("\n File loading Error....[%s]" , szDrvAppFilename );
    }
	else {
		printf("\n Loading %s...\n\n", szDrvAppFilename );

		// Download한 함수 호출
#ifndef _WRS_CONFIG_LP64
		stResult = symFindByName( sysSymTbl, (char *) "start" , & pSpawnFuncName, & symType);

		if(stResult == OK) {
			tID = taskSpawn( APP_TASKNAME, tPRI_App, 0, 64000, (FUNCPTR) pSpawnFuncName, m_uiBoardID,0,0,0,0,0,0,0,0,0);
			if( tID == TASK_ID_NULL ) {
				printf( "\n [W] '%s' 타스크를 생성하지 못했습니다." , APP_TASKNAME );
            }
		}
		else {
			printf( "\n [W] 'start()' 함수를 찾을 수 없습니다.[%d]...\n" , stResult );
        }
#else
	    SYMBOL_DESC symbolDesc;     /* symFind( ) descriptor */

	    memset (&symbolDesc, 0, sizeof (SYMBOL_DESC));
	    symbolDesc.mask = SYM_FIND_BY_NAME;
	    symbolDesc.name = "start";
		stResult = symFind( sysSymTbl, & symbolDesc );

		if(stResult == OK) {
			//tID = taskSpawn( APP_TASKNAME, tPRI_App, 0, 64000, (FUNCPTR) symbolDesc.value, m_uiBoardID, 0,0,0,0,0,0,0,0,0 );
            tID = taskSpawn( APP_TASKNAME, tPRI_App, 0, 64000, ( FUNCPTR ) symbolDesc.value, m_uiBoardID, 0, 0, 0, 0, 0, 0, 0, 0, 0 );
			if( tID == TASK_ID_NULL ) {
				printf( "\n [W] '%s' 타스크를 생성하지 못했습니다." , APP_TASKNAME );
            }
		}
		else {
			printf( "\n [W] 'start()' 함수를 찾을 수 없습니다.[%d]...\n" , stResult );

        }

#endif

	}

    if( enApp == enDownloadApp ) {
        STATUS stResult;

        stResult = unlink( szDrvAppFilename );

        if( stResult != OK ) {
            printf("\n [W] [%s]을 삭제하지 못했습니다.." , szDrvAppFilename );

        }

    }


#else
    printf( "\n Loading %s...\n\n", szDrvAppFilename );

#endif

}

/**
 * @brief		InitDataBase
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2021/11/12 15:27:50
 * @warning
 */
void CManSbc::InitDataBase()
{
	/*
    STATUS stat;
    char szSrcSQLiteFilename[100];
    char szDstSQLiteFilename[100];

    sprintf( szSrcSQLiteFilename, "%s/%s/%s", TFFSDRV, SQLITE_FOLDER, SQLITE_BLK_FILENAME );
    sprintf( szDstSQLiteFilename, "%s%s/%s/%s", RAMDRV, RAMDRV_NO, SQLITE_FOLDER, SQLITE_FILENAME );
    stat = cp( szSrcSQLiteFilename, szDstSQLiteFilename );
    if( stat == ERROR ) {
    	printf( "\n 위협관리 데이터베이스 파일이 존재하지 않거나 복사 실패 했습니다 !!!" );
    }
    else {
    	printf( "\n 위협관리 데이터베이스 파일을 [%s]에 복사했습니다." , szDstSQLiteFilename );
    }	*/

}

/**
 * @brief		PCIConfigSetting
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/01/05 13:31:23
 * @warning
 */
void CManSbc::PCIConfigSetting()
{

#if defined(_PCI)

    TRACE( "\n\n" );

    if( PCIeMemInit( ) == ERROR ) {
        printf( "\n SBC 상에서 PCI 초기화를 수행하지 못했습니다. SBC 장착을 다시 해보거나 담당자에거 문의하세요..!" );
        while( true );
    }
    else {
        sPCIeMAP *pPCIeMap;

        pPCIeMap = GetPCIeMap();

//         printf( "\n 좌측 pPCIeMap->uiBaseAddress0[0x%x]" , pPCIeMap->memInfo[0].uiBaseAddress0 );
//         printf( "\n 좌측 pPCIeMap->uiBaseAddress0[0x%x]" , pPCIeMap->memInfo[0].uiBaseAddress1 );
//
//         printf( "\n 우측 pPCIeMap->uiBaseAddress0[0x%x]" , pPCIeMap->memInfo[1].uiBaseAddress0 );
//         printf( "\n 우측 pPCIeMap->uiBaseAddress0[0x%x]" , pPCIeMap->memInfo[1].uiBaseAddress1 );

        if( pPCIeMap->memInfo[0].uiBaseAddress0 == (unsigned int) -1 ) {
            printf( "\n 좌측 PCI 가 초기화 되지 않았습니다. 전면판의 램프를 확인하세요." );
        }
        else {
            m_bPCIeInit[0] = true;
        }

        if( pPCIeMap->memInfo[1].uiBaseAddress0 == ( unsigned int ) -1 ) {
            printf( "\n 우측 PCI 가 초기화 되지 않았습니다. 전면판의 램프를 확인하세요." );
        }
        else {
            m_bPCIeInit[1] = true;
        }

        // PCI 와 로직 간의 동기화 오류로 시간을 대기하고 호출하도록 합니다.
        Sleep( 5 );

	    // SBC 보드 ID 읽기
	    unsigned int uiPSBoardID;

        if( m_bPCIeInit[0] == true ) {
	        uiPSBoardID = PCIeLeftCtrlRead32( IBRDID );
        }
        else if( m_bPCIeInit[1] == true ) {
            uiPSBoardID = PCIeRightCtrlRead32( IBRDID );
        }
        else {
            uiPSBoardID = -1;
        }

	    uiPSBoardID = swapByteOrder( uiPSBoardID );

	    // 왜 이렇게 만들었을까요 ? 나도 모르지...
	    switch( uiPSBoardID ) {
            // 2~3GHz(좌), 0.5~2 GHz(우)
            case 8:
            case 9:
                m_uiBoardID = enPRC1;
                break;

            // 3~4.5 GHz(좌), 4.5~6GHz(우)
		    case 6 :
		    case 7 :
			    m_uiBoardID = enPRC2;
			    break;

            // 8~10GHz(좌), 6~8 GHz(우)
            case 0:
            case 1:
                m_uiBoardID = enPRC3;
                break;

            // 10~12 GHz(좌), 12~14GHz(우)
		    case 2:
            case 3:
                m_uiBoardID = enPRC4;
                break;

            // 16~18GHz(좌), 14~16 GHz(우)
            case 4:
            case 5:
                m_uiBoardID = enPRC5;
                break;

		    default:
			    m_uiBoardID = enPRC1;
			    break;
	    }

	    printf( "\n SBC Board ID : %d, PS Board ID : %d", m_uiBoardID, uiPSBoardID );
    }

	// Print_PCIeLeftCtrlRead32( 0x208 );
	// Print_PCIeRightCtrlRead32( 0x208 );

#else
    m_uiBoardID = 1;

#endif

}


/**
 * @brief		MountDrive
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/01/13 18:14:19
 * @warning
 */
void CManSbc::MountDrive()
{
#ifdef __VXWORKS__
	STATUS status;

	//printf( "\nHOST[%s:%s]" , g_stBootParams.hostName, g_stBootParams.had );
	nfsAuthUnixSet ( (char *) g_stBootParams.hostName, 0, 0, 0, (int *) 0 );

#if 1
    if( false == MountDrive( g_pTheSysConfig->GetCCUServerOfNetwork(), NFS_DRIVE ) ) {
        MountDrive( g_pTheSysConfig->GetDebugServerOfNetwork(), NFS_DRIVE );
    }

#else
    MountDrive( g_pTheSysConfig->GetDebugServerOfNetwork(), NFS_DRIVE );

#endif

#endif

}

/**
 * @brief     MountDrive
 * @param     char * pHostIPAddress
 * @param     char * pRemoteFileSystem
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-10-16 19:47:14
 * @warning
 */
bool CManSbc::MountDrive( char *pHostIPAddress, char *pRemoteFileSystem )
{
    bool bRet = true;

#ifdef __VXWORKS__
    STATUS status;

    printf( "\nNFS 드라이브[%s:%s]를 연결하려 합니다 !", pHostIPAddress, pRemoteFileSystem );

    if( true == CheckPing( pHostIPAddress ) ) {
        status = hostAdd( ( char * ) "NFS_HOST", pHostIPAddress );
        status = nfsMount( "NFS_HOST", pRemoteFileSystem, NFS_DRIVE );

        if( status == OK ) {
            printf( "\nNFS 드라이브[%s:%s]를 정상 연결했습니다 !", pHostIPAddress, pRemoteFileSystem );
        }
        else {
            printf( "\n[W] NFS 드라이브[%s:%s]를 마운트 하지 못 했습니다 !!!", pHostIPAddress, pRemoteFileSystem );
            WhereIs;

            bRet = false;
        }
    }
    else {
    	bRet = false;
    }
#endif

    return bRet;

}

/**
 * @brief     CheckHost
 * @param     char * pIPAddress
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-10-16 10:54:30
 * @warning
 */
bool CManSbc::CheckPing( char *pIPAddress )
{
#ifdef __VXWORKS__
    STATUS status = ping( pIPAddress, 1, 0 );
    return status == OK;
#else
    return true;

#endif
}

/**
 * @brief     ShowNetMemory
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-19 11:19:06
 * @warning
 */
void CManSbc::ShowNetMemory()
{
#ifdef _NETMEM_
    int i;
    NetMemCommand netCommand;
    STR_NETMEM *pNetMem;

    printf( "\n +------- NETMEMORY ----------------------------+" );

    for( i=0 ; i < enMAXPRC ; ++i ) {
        netCommand.offset = i;
        if( m_pTheNetMem->ReadPage( & netCommand ) ) {
            pNetMem = ( STR_NETMEM * ) netCommand.data;
            printf( "\n [#%d] SBCID[%d]", i, pNetMem->uiSBCID );
        }
        else {
            printf( "\n [#%d] NET 공유 에러 입니다.", i );
        }
    }
#endif

}

/**
 * @brief     CComHook
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-05 12:45:37
 * @warning
 */
void CManSbc::KeyboardHooking()
{
#ifdef __VXWORKS__
    int status;
    int stdinFd;

    stdinFd = ioTaskStdGet( 0, 0 );
    printf( "\n\n Key board hooking[%d]..." , stdinFd );

    status = ioctl( stdinFd, FIOPROTOHOOK, KeyboardHandler );
    if( status == ERROR ) {
        printf( "\n ioctl error !" );
    }

    status = ioctl( stdinFd, FIOPROTOARG, 1 );
    if( status == ERROR ) {
        printf( "\n ioctl error !" );
    }
#else
    printf( "\n\n Key board hooking..." );

#endif

}
