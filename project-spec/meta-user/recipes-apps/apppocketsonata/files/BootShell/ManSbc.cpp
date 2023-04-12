// ManSbc.cpp: implementation of the CManSbc class.
//
//////////////////////////////////////////////////////////////////////

#include <taskLib.h>
#include <ioLib.h>
#include <private/iosLibP.h>
#include <envLib.h>
#include <sysLib.h>
#include <symbol.h>
#include <symLib.h>
#include <sysSymTbl.h>
#include <loadLib.h>
#include <taskLib.h>
#include <usrLib.h>
#include <tftpLib.h>
#include <ifLib.h>

#include <xbdBlkDev.h>
#include <dosFsLib.h>
#include <usrFsLib.h>

//#include <ramDiskCbio.h>
#include <ramDrv.h>
#include <tffs/tffsDrv.h>

#include <types/vxTypesOld.h>
#include <tyLib.h>

#include <nfs/nfsCommon.h>

#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include <sntpcLib.h>

#include <dirent.h>

#include "prjParams.h"
#include "private/timeP.h"

#include "ManSbc.h"
//#include "ManFlash.h"
#include "BootShell.h"

#include "./pciDiag.h"

#include "./Untar/FileTar.h"

#ifdef __cplusplus
extern "C" {
#endif

BOOT_PARAMS stBootParams;

IMPORT time_t sysRtcTimeGet (void);
IMPORT TIMELOCALE * __loctime;

void Formatting();

extern STATUS sysTffsFormat (void);

#ifdef __cplusplus
}
#endif

extern CFileTar *theFileTar;
extern BOOT_PARAMS stBootParams;

void Formatting()
{

}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CManSbc::CManSbc()
{
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
    //PCIConfigSetting();

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
	char cChar;
	int stdInFd, numReady;
	struct timeval tclSelectTimeout;
	fd_set readFds;
	int save_options;

	TY_DEV_ID pTyDev;
	RING_ID ringId;
	char  ccc;

    int tShell_priority;

    char buffer[200];

    taskPriorityGet( 0, & tShell_priority );
    //printf( "\n tShell_priority priority[%d]" , tShell_priority );

	stdInFd = ioTaskStdGet( taskNameToId( (char *) "tShell0" ), 0 );

	/* Save options */
	save_options = ioctl(stdInFd,FIOGETOPTIONS,0); /* current console */
	// printf( "\n save_options[%x], new_option[%x]" , save_options, OPT_TERMINAL & ~OPT_LINE & ~OPT_ECHO );
	ioctl(stdInFd, FIOSETOPTIONS, OPT_TERMINAL & ~OPT_LINE & ~OPT_ECHO );

	/* Enter raw mode */
	// ioctl (stdInFd, FIOSETOPTIONS, OPT_TERMINAL & ~OPT_LINE & ~OPT_ECHO );

	tclSelectTimeout.tv_sec = (long) sec;
	tclSelectTimeout.tv_usec = (long) 0;

	FD_ZERO( & readFds );
	FD_SET( stdInFd, & readFds);

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

	numReady = select( FD_SETSIZE, & readFds, NULL, NULL, & tclSelectTimeout );

	//printf( "\n numReady[%d]\n" , numReady );

	/*! \bug  tty ISR callback 에서 ring buffer 에 enqueue 함으로서, rdSyncSema 에
						wakeup 된 shell task 가 schedule 되기 전에, 역시 select  에서 wakeup
						되어 running 중인  user task 에서 ring buffer 의  1 char 를 읽어 온
						후(원래는 tShell 로 pass 될 예정),  rx callback(tyIRd) 을 호출함으로,
						다시 ring buffer 에 enqueue 후, 그 아래 read API 에서 char return 을
						받을 수 있도록 하였읍니다.
	    \date 2007-03-07 11:19:24, 조철희
	*/
	//pTyDev = ( TY_DEV_ID ) iosFdValue( stdInFd );

	//ringId = pTyDev->rdBuf;
	//rngBufGet( pTyDev->rdBuf, & ccc, 2 );

	//ioctl( stdInFd, FIORFLUSH, 0 );

	if( numReady > 0 ) {
		//tyIRd( pTyDev, cChar );
	    //printf( "\n cChar[%d]\n" , cChar );

		read( stdInFd, & cChar, 1 );           /* read the key just hit */
		//printf( "\n cChar[%d]\n");
	}

	/* Leave raw mode */
	ioctl( stdInFd, FIOSETOPTIONS, save_options );
	ioctl( stdInFd, FIOFLUSH, 0 );

    //WhereIs;
    //printf( "\n cChar = %d" , cChar );


#ifdef INCLUDE_SHELL
	// taskPrioritySet( taskNameToId( (char *) "tShell0" ), tShell_priority );
	taskResume( taskID );
#endif

	return (UCHAR) cChar;

}

/**
 * @brief		CreateTffsDisk
 * @param		char * szDiskName
 * @return		BOOL
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2021/04/15 13:54:51
 * @warning
 */
BOOL CManSbc::CreateTffsDisk( char *szDiskName )
{
    long lFreeSpace;

    lFreeSpace = DiskFreeSpace( szDiskName );

    if( lFreeSpace >= 0 ) {
        printf( "\n\n\n Free space in the [%s] drive = %ld Byte\n" , szDiskName, lFreeSpace );
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
BOOL CManSbc::CreateRamDisk( char *szDiskName, int bytesPerBlk, int blksPerTrack, int nBlocks )
{
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
	printf( "\n Free space in the [%s] drive = %ld Byte" , szDiskName, lFreeSpace );

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
	long lDiskFreeSpace;
	struct statfs SStatFs;

	if( statfs( szDiskName, & SStatFs )==OK ) {
		lDiskFreeSpace = SStatFs.f_bsize * SStatFs.f_bavail;
	}
	else {
		lDiskFreeSpace= -1;
	}

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
    int iTry;
	UINT _date, _time;

	STATUS sntpc_status, settime_status;
	struct timespec tspec;

	// InitSystemVariable();
	putenv( (char *) "TIMEZONE=KST::-540.000000:000000" );

    printf( "\n\n ##### SNTP 프로토콜을 사용해서 시간을 설정합니다..." );
    // 이놈의 vxworks 7은 왜 2번을 수행해야 얻어 오는지....
    iTry = 0;
    do {
        sntpc_status = sntpcTimeGet( stBootParams.had, 3*OS_ONE_SEC, & tspec );
        printf( "SNTP를[%s:%d] 요청..." , stBootParams.had, sntpc_status );
        ++ iTry;
    } while( iTry <= TRY_GETSNTP && sntpc_status != OK );

	if( sntpc_status != OK ) {
		time_t result, recent_time=0;

		DIR *pSystemLogDir;
		struct dirent *pLogEntry;

		printf( "\n [W] SNTPctimeGet failed...%s" , stBootParams.had );
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
			// InitSystemVariable();
			//Time2DateTime( & _date, & _time, tspec.tv_sec );
			//SetRtcClock( _date, _time );
			time_t ti=time(NULL);

            pstTime = localtime( & ti );
            strftime( buffer, 100, "%Y-%m-%d %H:%M:%S[%ld]", pstTime );

			printf( "완료[%s, %d].\n" , buffer, ti );
        }
	}

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
    char szRamDrvWebfolder[100];
    char sztffs0Webfolder[100];

    char szSrcFilename[100], szDstFilename[100];

    printf( "\n" );
    // 백업
    // 라이브러리를 백업한다.
#if TOOL==diab
    printf( "\n\n 1. 백업을 수행 합니다..." );
#else
    printf( "\n\n 1. Backup the files..." );
#endif

    sprintf( szDstFilename, "%s%s/%s" , RAMDRV, RAMDRV_NO, SQLITE_FOLDER );
    mkdir( szDstFilename );
    sprintf( szSrcFilename, "%s/%s/%s" , TFFSDRV, SQLITE_FOLDER, CEDEOB_SQLITE_FILENAME );
    sprintf( szDstFilename, "%s%s/%s/%s" , RAMDRV, RAMDRV_NO, SQLITE_FOLDER, CEDEOB_SQLITE_FILENAME );
    stat = CopyFile( szSrcFilename, szDstFilename );
    // INI 파일을 백업한다.
    sprintf( szDstFilename, "%s%s/%s" , RAMDRV, RAMDRV_NO, INI_FOLDER );
    mkdir( szDstFilename );
    sprintf( szSrcFilename, "%s/%s/%s" , TFFSDRV, INI_FOLDER, INI_FILENAME );
    sprintf( szDstFilename, "%s%s/%s/%s" , RAMDRV, RAMDRV_NO, INI_FOLDER, INI_FILENAME );
    stat = CopyFile( szSrcFilename, szDstFilename );

    // 포멧 ...
    printf( "\n\n 2. TFFS 드아리브를 포멧합니다..." );

    dosFsVolFormat( TFFSDRV, DOS_OPT_DEFAULT, (FORMAT_PTR) 0 );

    // 압축된 파일을 추출합니다.
    printf( "\n\n 3. TAR 파일을 풉니다..." );
    sprintf( szRamDrvFilename, "%s%s/%s" , RAMDRV, RAMDRV_NO, WEB_FILENAME );
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
int CManSbc::CopyFile( const char *src_file, const char *dest_file )
{
	STATUS stat;

	printf( "\n" );
	stat = cp( src_file, dest_file );
	if( stat == OK ) {
		printf( "원본 파일(%s)을 대상 파일(%s)에 성공적으로 복사 했습니다.\n" , src_file, dest_file );
	}
	else {
		printf( "원본 파일(%s)을 대상 파일(%s)에 실패 했습니다.\n" , src_file, dest_file );
	}

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

    if( true == DownloadfromTftp( APP_FILENAME, (char *) szTffsDrvFilename ) ) {
    	printf("\n\n *** 운용 소프트웨어를 설치 완료 했습니다. ***" );

    }
    else {
        printf("\n [W] 운용 소프트웨어를 설치하지 못 했습니다 !!!" );

    }


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
    if( true == DownloadfromTftp( APP_FILENAME, (char *) szRAMDrvFilename ) ) {
    	printf("\n\n *** 운용 소프트웨어를 설치 완료 했습니다. ***" );
    }
    else {
        printf("\n [W] 운용 소프트웨어를 설치하지 못 했습니다 !!!" );
    }


}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CBootShell::DownloadfromTftp
	\author   조철희
	\param    tftpfilename 인자형태 char *
	\param    ramfilename 인자형태 char *
	\return   BOOL
	\version  0.0.1
	\date     2008-04-18 10:58:31
	\warning
*/
BOOL CManSbc::DownloadfromTftp( char *tftpfilename, char *pFilename )
{
	bool bret;

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
	SYM_TYPE symType;
	STATUS stResult;
	char *pSpawnFuncName;

	TASK_ID tID;

    char szDrvAppFilename[100];

    MODULE *m_pModuleId;

    if( enApp == enDownloadApp ) {
        sprintf( szDrvAppFilename, "%s%s/%s", RAMDRV, RAMDRV_NO, APP_FILENAME );
    }
    else {
        sprintf( szDrvAppFilename, "%s/%s", TFFSDRV, APP_FILENAME );
    }

	m_pModuleId = ld( ALL_SYMBOLS, 0, szDrvAppFilename );

	if( m_pModuleId == NULL ) {
		printf("\n File loading Error....[%s]" , szDrvAppFilename );
    }
	else {
		printf("\n Loading %s...\n\n", szDrvAppFilename );

		// Download한 함수 호출
#ifndef _WRS_CONFIG_LP64
		stResult = symFindByName( sysSymTbl, (char *) "start" , & pSpawnFuncName, & symType);

		if(stResult == OK) {
			tID = taskSpawn( APP_TASKNAME, tPRI_App, 0, 64000, (FUNCPTR) pSpawnFuncName,0,0,0,0,0,0,0,0,0,0);
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
#if TOOL==diab
				//printf( "\n [W] '%s' 타스크를 생성하지 못했습니다." , APP_TASKNAME );
#else
				printf( "\n [W] '%s' 타스크를 생성하지 못했습니다." , APP_TASKNAME );
#endif
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

	/*
    if( PCIeMemInit( ) == ERROR ) {
        printf( "\n ERROR! PCIe BAR Initialize !" );
    }
    */

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
	STATUS status;

	printf( "\nHOST[%s:%s]" , stBootParams.hostName, stBootParams.had );
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

}
