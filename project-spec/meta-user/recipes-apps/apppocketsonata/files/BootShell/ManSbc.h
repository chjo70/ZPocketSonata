// ManSbc.h: interface for the CManSbc class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#ifdef _MSC_VER
#include <intsafe.h>

#endif


#include "Macros.h"

#include "../Utils/cudpserver.h"

//#include "BootShell.h"

//#include "../System/csysconfig.h"

//#include "../OFP/COMMON/common.h"
#define DRAM_SIZE			(0)

// 내부 메모리의 운용 프로그램 구조체 정의
typedef struct {
	// 롬화  회수
	UINT coWrite;
	// 버젼 정보 - 시간
	time_t update_time;
	// 운용 프로그램 사이즈
	UINT filesize;
	// 파일명
	char filename[50];
	// 프로그램 시작 포인터
	char *pComFlashProgram;

} STR_PRG_INFO ;

enum enWhatDrvAPP {
    enDownloadApp = 0,
    enTffsApp

};




//////////////////////////////////////////////////////////////////////
// NFS 드라이브 정의
// NFS 호스트 경로에 d:/rawdata 를 export 해야 합니다.
#define NFS_DRIVE                       "/d/rawdata"



//////////////////////////////////////////////////////////////////////
// TFTP 프로토콜 정의

#define TFTP_SERVER_IP				    DEFAULT_SNTP_SERVER_IP  // "150.150.49.228"
#define TFTP_MODE						((char*) "binary" )
#define	DOWNLOAD_FILENAME				"vxworks"

// 지역 로컬 시간 정의
// 서울 기준
#define SEOUL_LOCAL_TIME				(9)

#ifdef _NETMEM_	
#include "../NetMem/client/NetworkMemory.h"

#endif



class CManSbc
{
private :
	unsigned int m_uiBoardID;

	STR_PRG_INFO m_ProgInfo;

    // CSysConfig *g_pTheSysConfig;

    CUDPServer *m_pUDPServer;


#ifdef _NETMEM_	
    STR_NETMEM m_strMemory;

    NetworkMemory *m_pTheNetMem;
    NetMemCommand m_netCommand;

#endif    

private:
	void Time2DateTime( UINT *pDate, UINT *pTime, time_t now_sec );
	time_t GetLastAccessTime( char *pFileName );
	int IsFile( char *pFileName );

	void VMEBusSystemReset();

	UINT GetTime( char *pTime );
	UINT GetDate( char *pDate );

	inline STR_PRG_INFO *GetProgInfo() { return & m_ProgInfo; }

	void SetRtcClock( UINT date, UINT time );
	void SetTimeBySNMP();
	bool CopyToRamdrive( STR_PRG_INFO *pComPrgInfo, char *pFileName );
	long DiskFreeSpace( char *szDiskName );


    //////////////////////////////////////////////////////////////////////////
    //
	bool CreateRamDisk( char *szDiskName, int bytesPerBlk, int blksPerTrack, int nBlocks );
    bool CreateTffsDisk( char *szDiskName );
	bool CreateAtaDisk( char *szDiskName );
	UCHAR Getche( int sec );
	UCHAR Getche2( int sec );

    bool DownloadfromTftp(char *tftpfilename, char *ramfilename );
    int CopyToFile( const char *src_file, const char *dest_file );

public:
	UCHAR GetCommand();
    void InstallWeb();
    void DownloadApp();
    void DownloadAndROMWriteApp();
    void RunApp( enWhatDrvAPP enApp );

    void InitDataBase();
    void PCIConfigSetting();
    void MountDrive();

    void ShowNetMemory();

	CManSbc();
	virtual ~CManSbc();

};


