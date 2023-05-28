/**

    @file      ManSbc.cpp
    @brief	   SBC 관련 함수 모음 입니다.
    @details   ~
    @author    조철희
    @date      17.04.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

#include "pch.h"

#ifdef __VXWORKS__
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

#endif

//#include <io.h>
#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include "ManSbc.h"
//#include "ManFlash.h"

#include "BootShell.h"


#include "./Untar/FileTar.h"

//#include "../Anal/INC/OS.h"
//#include "../Anal/INC/System.h"

#include "../Anal/INC/PDW.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __VXWORKS__
BOOT_PARAMS g_stBootParams;

bool g_bSNTP;


IMPORT time_t sysRtcTimeGet( void );
IMPORT TIMELOCALE *__loctime;

#endif

void Formatting();

extern STATUS sysTffsFormat (void);

#ifdef __cplusplus
}
#endif

extern CFileTar *theFileTar;


void Formatting()
{

}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CManSbc::CManSbc()
{
    m_uiBoardID = 0;

#ifdef _NETMEM_
    m_pTheNetMem = new NetworkMemory( (char *) "127.0.0.1", NET_MEM_PORT );

    m_netCommand.offset = 0;
    m_netCommand.data = ( unsigned char * ) malloc( sizeof( STR_NETMEM ) );
#endif

#ifdef __VXWORKS__
    STATUS status;

    char ip_addr[100];

	// VMEBusSystemReset();

    //ifMaskSet( "memac0" , 0xffffff00 );
    //ifAddrSet( "memac0" , "192.168.1.50" );
    ifAddrGet( (char *) "memac0", ip_addr );

    //#error	"network device 명을 알아서 위와 같이 설정해야함."

    //////////////////////////////////////////////////////////////////////////
    //
    // printf( "\n IP Address\t: [%s]\n" , ip_addr );
    sysClkRateSet( TICK_COUNT );
    if( sysClkRateGet() != TICK_COUNT ) {
        printf( "\n [W] 토네이도의 Component에서 tick count를 100 으로 설정하세요." );
    }
    else {
        sysClkRateSet( TICK_COUNT );		// 1초당 100 tick 을 수행함.
    }

    // SNTP 를 이용해서 현재 시간을 읽어온다.
    SetTimeBySNMP();

    //////////////////////////////////////////////////////////////////////////
    // PCI 초기화
    PCIConfigSetting();

    //////////////////////////////////////////////////////////////////////////
    // NFS 드라이브 마운트
    MountDrive();

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
    if( FALSE == CreateAtaDisk( ATADRV ) ) {
        printf( "\n[W] Application/UDF용 롬 디스크가 생성하지 못했습니다." );
        WhereIs;
    }
    else {

    }
#endif


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

    m_pUDPServer = new CUDPServer( 3000 );

    m_pUDPServer->Run();

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
    UCHAR key, uRet=RUN_APP;

    key = Getche( KEYBOARD_TIMEOUT );
    printf( "\nGetche key[%d]" , key );

	switch( tolower( key ) ) {
		case 'w' :
			uRet = INSTALL_WEB;
            break;

		case '1' :
			WhereIs;
			uRet = WRITE_APP_FLASH;
            break;

		case 'z' :
			uRet = DOWNLOAD_UTEST_PROG;
		case 'x' :
			uRet = WRITE_UTEST_PROG;
		case 'c' :
			uRet = RUN_UTEST_PROG;

		case 'n' :
			uRet = WRITE_BOOT_PROG;
            break;

		case '0' :
            uRet = DOWNLOAD_APP;
            break;

		case 'd' :
            uRet = DEBUG_APP;
            break;

		default :
			// printf( "\n stBootParams[%s]" , stBootParams.bootDev );

			/*! \bug  명령어 디버깅용으로 사용함.
					\date 2008-07-03 10:42:35, 조철희
			*/
			//if( strcmp( stBootParams.bootDev, "fei" ) == 0 )
			uRet = DOWNLOAD_APP;

			break;
			//;

	}

	return uRet;

}

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
    char cChar=0;

	int stdInFd, numReady;
	struct timeval tclSelectTimeout;
    fd_set original_socket;
    fd_set original_stdin;
	fd_set readFds;
    fd_set writeFds;

    int numfd;

    unsigned int address_length;

    struct sockaddr_in server_address, client_address;

#ifdef __VXWORKS__
    int tShell_priority;

    taskPriorityGet( 0, & tShell_priority );

	stdInFd = ioTaskStdGet( taskNameToId( (char *) "tShell0" ), 0 );

#else
    stdInFd = _fileno( stdin );

#endif

    tclSelectTimeout.tv_sec = ( long ) 100; //  sec;
    tclSelectTimeout.tv_usec = ( long ) 0;


#ifdef __VXWORKS__
	/* Save options */
	int save_options = ioctl(stdInFd,FIOGETOPTIONS,0); /* current console */

	// printf( "\n save_options[%x], new_option[%x]" , save_options, OPT_TERMINAL & ~OPT_LINE & ~OPT_ECHO );
	ioctl(stdInFd, FIOSETOPTIONS, OPT_TERMINAL & ~OPT_LINE & ~OPT_ECHO );
#endif

    int socket_fd;

    if( ( socket_fd = socket( AF_INET, SOCK_DGRAM, 0 ) ) == -1 ) {
        printf( "[W] socket() 함수에서 소켓을 할당하지 못했습니다 !" );
    }

#ifdef _MSC_VER
    unsigned long nonblock_enabled = TRUE;
    ioctlsocket( socket_fd, FIONBIO, & nonblock_enabled );

#else
    int flags = fcntl( socket_fd, F_GETFL );
    flags |= O_NONBLOCK;

#endif

    // clear the set ahead of time
    FD_ZERO( &original_socket );
    FD_ZERO( &original_stdin );
	FD_ZERO( & readFds );
    FD_ZERO( & writeFds );

	// FD_SET( stdInFd, & readFds);
    FD_SET( socket_fd, & original_socket );
    FD_SET( socket_fd, & readFds );
    FD_SET( stdInFd, & original_stdin );
    FD_SET( 0, & writeFds );

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons( 5000 );
    server_address.sin_addr.s_addr = INADDR_ANY;

#ifdef _MSC_VER
    memset( ( char * ) &server_address.sin_zero, 0, sizeof( server_address.sin_zero ) );

#else
    bzero( &( server_address.sin_zero ), 8 );

#endif

    if( bind( socket_fd, ( struct sockaddr * ) &server_address, sizeof( server_address ) ) == -1 ) {
        printf( "[W] bind() 함수에서 IP 와 바인딩하지 못했습니다 !" );
    }

    address_length = sizeof( struct sockaddr );


#ifdef __VXWORKS__
#ifdef INCLUDE_SHELL
	TASK_ID taskID=taskNameToId( (char *) "tShell0" );
	taskSuspend( taskID );
	//int tShell_priority;

	//taskPriorityGet( taskNameToId( (char *) "tShell0" ), & tShell_priority );
    //printf( "\n tShell0 priority[%d]" , tShell_priority );
	//taskPrioritySet( taskNameToId( (char *) "tShell0" ), 255 );
#endif
    ioctl( stdInFd, FIORFLUSH, 0 );

#endif

    numfd = socket_fd + 1;

    readFds = original_socket;
    writeFds = original_stdin;

	// numReady = select( FD_SETSIZE, & readFds, NULL, NULL, & tclSelectTimeout );
    numReady = select( numfd, &readFds, NULL,/*NULL,*/ NULL, &tclSelectTimeout );

	if( numReady > 0 ) {
		read( stdInFd, & cChar, 1 );           /* read the key just hit */

		//printf( "\n cChar[%d]\n");
	}

#ifdef __VXWORKS__
	/* Leave raw mode */
	ioctl( stdInFd, FIOSETOPTIONS, save_options );
	ioctl( stdInFd, FIOFLUSH, 0 );

#endif


#ifdef INCLUDE_SHELL
	// taskPrioritySet( taskNameToId( (char *) "tShell0" ), tShell_priority );
	taskResume( taskID );
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
		printf( "\n\n\n [%s] 드라이브에 남은 공간이 [%ld KByte] 있습니다.", szDiskName, lFreeSpace );
    }
    else {
        //////////////////////////////////////////////////////////////////////////
        // 드라이브를 생성합니다.
        printf( "\n VxWorks 컴포넌트(VXBFLASH_CFG_STR)에 정의된 크기로 플레쉬 메모리를 포멧합니다...\n" );

        // 아래와 같이 수행이 안 되면 콘솔에서 아래와 같이 입력한다. 소요 시간은 약 6분 정도 입니다.
        // sysTffsFormat
        // usrTffsConfig 0,0, "/tffs0"
        // dosFsVolFormat

        //sysTffsFormat();

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
        printf( "\n\n\n [%s] 드라이브에 남은 공간이 [%ld KByte] 있습니다.", szDiskName, lFreeSpace );
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
    printf( "\n\n\n [%s] 드라이브에 남은 공간이 [%ld KByte] 있습니다.", szDiskName, lFreeSpace );

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
		lDiskFreeSpace = (long) ( (float) SStatFs.f_bsize * (float) SStatFs.f_bavail / (float) 1024. );
	}
	else {
		perror( "szDiskName" );
		printf( "\n [W] 드라이브가 잘못됐습니다. " );
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
void CManSbc::SetTimeBySNMP()
{
#ifdef __VXWORKS__
    int iTry;
	UINT _date, _time;

	STATUS sntpc_status, settime_status;
	struct timespec tspec;

    g_bSNTP = false;

	// InitSystemVariable();
	putenv( (char *) "TIMEZONE=KST::-540.000000:000000" );

    printf( "\n\n ##### SNTP 프로토콜을 사용해서 시간을 설정합니다..." );
    // 이놈의 vxworks 7은 왜 2번을 수행해야 얻어 오는지....
    iTry = 0;
    do {
        sntpc_status = sntpcTimeGet( g_stBootParams.had, 3*OS_ONE_SEC, & tspec );
        printf( "SNTP를[%s:%d] 요청..." , g_stBootParams.had, sntpc_status );
        ++ iTry;
    } while( iTry <= TRY_GETSNTP && sntpc_status != OK );

	if( sntpc_status != OK ) {
		time_t result, recent_time=0;

		DIR *pSystemLogDir;
		struct dirent *pLogEntry;

		printf( "\n [W] SNTPctimeGet failed...%s" , g_stBootParams.had );
		printf( "\n Returned sntpc_status: %i errno: %s", sntpc_status, strerror(errno) );

		/*
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
	else {
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
            strftime( buffer, 100, "%Y-%m-%d %H:%M:%S[%ld]", pstTime );

			printf( "완료[%s, %d].\n" , buffer, ti );
        }
	}

#endif

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
    mkdir( szDstFilename );
#endif

    sprintf( szSrcFilename, "%s/%s/%s" , TFFSDRV, SQLITE_DIRECTORY, CEDEOB_SQLITE_FILENAME );
    sprintf( szDstFilename, "%s%s/%s/%s" , RAMDRV, RAMDRV_NO, SQLITE_DIRECTORY, CEDEOB_SQLITE_FILENAME );
    stat = CopyToFile( szSrcFilename, szDstFilename );
    // INI 파일을 백업한다.
    sprintf( szDstFilename, "%s%s/%s" , RAMDRV, RAMDRV_NO, INI_DIRECTORY );
#ifdef __VXWORKS__
    mkdir( szDstFilename );
#endif
    sprintf( szSrcFilename, "%s/%s/%s" , TFFSDRV, INI_DIRECTORY, INI_FILENAME );
    sprintf( szDstFilename, "%s%s/%s/%s" , RAMDRV, RAMDRV_NO, INI_DIRECTORY, INI_FILENAME );
    stat = CopyToFile( szSrcFilename, szDstFilename );

    // 포멧 ...
    printf( "\n\n 2. TFFS 드아리브를 포멧합니다..." );

#if defined(__VXWORKS__) || defined(__linux__)
    dosFsVolFormat( TFFSDRV, DOS_OPT_DEFAULT, (FORMAT_PTR) 0 );
#endif

    // 압축된 파일을 추출합니다.
    printf( "\n\n 3. TAR 파일을 풉니다..." );
    sprintf( szRamDrvFilename, "%s%s/%s" , RAMDRV, RAMDRV_NO, WEB_FILENAME );

#if defined(__VXWORKS__) || defined(__linux__)
    char szRamDrvWebfolder[100];
    char sztffs0Webfolder[100];

    if( true == DownloadfromTftp( WEB_FILENAME, (char *) szRamDrvFilename ) ) {
        sprintf( szRamDrvWebfolder, "%s%s" , RAMDRV, RAMDRV_NO );
        printf("\n TAR 파일[%s]을 풀어서 설치합니다." , szRamDrvWebfolder );

        sprintf( sztffs0Webfolder, "%s" , TFFSDRV );
        theFileTar->UnTar( szRamDrvFilename, sztffs0Webfolder );

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
    char szTffsDrvFilename[100];

    sprintf( szTffsDrvFilename, "%s/%s" , TFFSDRV, APP_FILENAME );

    printf( "\n Installing the App program in the drive[%s]...", szTffsDrvFilename );

#ifdef __VXWORKS__
    if( true == DownloadfromTftp( APP_FILENAME, (char *) szTffsDrvFilename ) ) {
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
    if( true == DownloadfromTftp( APP_FILENAME, (char *) szRAMDrvFilename ) ) {
    	printf("\n\n *** 운용 소프트웨어를 설치 완료 했습니다. ***" );
    }
    else {
        printf("\n [W] 운용 소프트웨어를 설치하지 못 했습니다 !!!" );
    }
#else
    printf( "\n\n *** 운용 소프트웨어를 설치 완료 했습니다. ***" );

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
bool CManSbc::DownloadfromTftp( char *tftpfilename, char *pFilename )
{
	bool bret=true;

#ifdef __VXWORKS__
	int	iFdWrite;
	int	iStatus;

    TFTP_DESC *spTftpDesc;

	if ( (spTftpDesc = tftpInit() ) == NULL ) {
		WhereIs;
		return FALSE;
	}

	bret = true;

#if TOOL==diab
	printf( "\n Host IP  : [ %s ]", TFTP_SERVER_IP );
	printf( "\n ROM Fle  : [ %s ]", tftpfilename );
#else
	printf( "\n 호스트 IP  : [ %s ]", TFTP_SERVER_IP );
	printf( "\n 롬 파일명  : [ %s ]", tftpfilename );
#endif

	/*	tftp 설정을 초기화 */
	if( ( tftpPeerSet (spTftpDesc, TFTP_SERVER_IP, TFTP_PORT ) == ERROR ) ||
		( tftpModeSet (spTftpDesc, TFTP_MODE ) == ERROR ) ) {
		(void) tftpQuit (spTftpDesc);
		return FALSE;
	}

	/* 파일 Open */
    unlink( pFilename );

	iFdWrite = open( pFilename, O_CREAT | O_RDWR, 0644 );
    if (iFdWrite == ERROR) {
        PrintErr( ( "\n [W] 파일[%s] 에러입니다.", pFilename ) );
        return FALSE;
    }

	//printf( "\n spTftpDesc[%p], iFdWrite[%d], tftpfilename[%s]" , spTftpDesc, iFdWrite, tftpfilename );
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

	close( iFdWrite );
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
        sprintf( szDrvAppFilename, "%s/%s", TFFSDRV, APP_FILENAME );
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
			tID = taskSpawn( APP_TASKNAME, tPRI_App, 0, 64000, (FUNCPTR) symbolDesc.value,0,0,0,0,0,0,0,0,0,0);
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

    if( PCIeMemInit( ) == ERROR ) {
        printf( "\n ERROR! PCIe BAR Initialize !" );
    }

	// SBC 보드 ID 읽기
	unsigned int uiPSBoardID;
	uiPSBoardID = PCIeLeftCtrlRead32( 0x208 );
	uiPSBoardID = swapByteOrder( uiPSBoardID );

	// 왜 이렇게 만들었을까요 ? 나도 모르지...
	switch( uiPSBoardID ) {
        case 8:
            m_uiBoardID = 1;
            break;

		case 6 :
		case 7 :
			m_uiBoardID = 2;
			break;

        case 0:
        case 1:
            m_uiBoardID = 3;
            break;

		case 2:
        case 3:
            m_uiBoardID = 4;
            break;

        case 4:
        case 5:
            m_uiBoardID = 5;
            break;

		default:
			m_uiBoardID = 1;
			break;
	}

	printf( "\n SBC Board ID : %d, PS Board ID : %d", m_uiBoardID, uiPSBoardID );

	// Print_PCIeLeftCtrlRead32( 0x208 );
	// Print_PCIeRightCtrlRead32( 0x208 );

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

	printf( "\nHOST[%s:%s]" , g_stBootParams.hostName, g_stBootParams.had );
	nfsAuthUnixSet ( (char *) "host", 0, 0, 0, (int *) 0 );

    // 호스트명 추가
    //status = hostAdd( "NFSDRV", stBootParams.had );
    status = OK;

    if( status == OK ) {
        status = nfsMount( "host", NFS_DRIVE, NFS_DRIVE );
        if( status == OK ) {
            printf( "\nNFS 드라이브[%s]를 정상 연결했습니다 !", NFS_DRIVE );
        }
        else {
            printf( "\n[W] 마운트를 하지 못 했습니다 !!!" );
            WhereIs;
        }
    }
    else {
        printf( "\n[W] 호스트명을 등록하지 못 했습니다 !!!" );
        WhereIs;
    }
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
