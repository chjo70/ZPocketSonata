#include <string.h>
#include <memory.h>
#include <pwd.h>
#include <sys/types.h>

#ifdef ENABLE_FASTCGI
#include "fcgi_stdio.h"
#else
#include <stdio.h>
#endif
#include <stdlib.h>
#include <stdbool.h>


#include "../../Anal/INC/system.h"

#include "../Qdecoder/qDecoder.h"

void PreviousPage();

static char *gpFileData, *gpSavepath, *gpFilename;
static char gszUploadfiles[500];

static int _clear_savedir(char *dir) {
#ifdef _WIN32
    long hFile;
    char buffer[1024];
    char filepath[1024];
    struct _finddata_t c_file;

    sprintf( buffer, ".\\%s\\*.*" , dir );
    hFile = _findfirst( buffer, & c_file );
    if( hFile == -1 ) {
        return 0;
    }

    while( _findnext(hFile, & c_file ) == 0 ) {
    if(!strcmp(c_file.name, ".") || !strcmp(c_file.name, "..")) continue;

    sprintf(filepath, "%s/%s", dir, c_file.name );
    unlink(filepath);
    }

    _findclose( hFile );

    if(rmdir(dir) != 0) return 0;

    return 1;
#else
    DIR *dp;
    struct  dirent *dirp;
    char filepath[1024];
    struct stat stBuf;

    /* open upload folder */

    qErrorPrint( "Delete dir[%s]" , dir );

    if((dp = opendir(dir)) == NULL) {
        printf( "\n Delete dir[%s]" , dir );
        return unlink(dir);
    }

    while((dirp = readdir(dp)) != NULL) {
        if(!strcmp(dirp->d_name, ".") || !strcmp(dirp->d_name, "..")) continue;

        sprintf(filepath, "%s/%s", dir, dirp->d_name);

        if( lstat( filepath, & stBuf ) == -1 ) {
            continue;
        }

        if( S_ISDIR( stBuf.st_mode )) {
            if( _clear_savedir(filepath) == -1 )  {
                return -1;
            }
        }
        else if( S_ISREG( stBuf.st_mode ) || S_ISLNK( stBuf.st_mode) ) {
            //printf( "\n Delete filepath[%s]" , filepath );
            if( unlink(filepath) == -1 ) {
                return -1;
            }
        }

    }
    closedir(dp);

    return rmdir( dir );

#endif

}

enum ENUM_UPLOAD {
    enCEDEOB_File=0,
    enImage_File,
    enINI_File,

    enUPLOAD_FILES,
} ;

/**
 * @brief ProcessUpload
 * @param enUpload
 */
bool ProcessUpload( ENUM_UPLOAD enUpload )
{
    bool bRet=false;
    int iRet;
    struct passwd *pHome;
    char szNewpath[200];
    char szExecute[200];

    switch( enUpload ) {
        case enCEDEOB_File :
            // 파일명 변경하기
            sprintf( szNewpath, "%s%s", CEDEOB_SQLITE_FOLDER, CEDEOB_SQLITE_FILENAME);
            if( rename( gpSavepath, szNewpath) == -1 ) {
                printf("Can not move uploaded file %s-%s.", gpSavepath, szNewpath );
            }

            // 권한 변경
#if 0
            pHome = getpwnam( HOME_ID );
            printf( "\n pHome->pw_uid[%d]" , pHome->pw_uid );
            if( chown( szNewpath, pHome->pw_uid, pHome->pw_gid ) == -1 ) {
                qError("Can not change owner file. %s", szNewpath );
            }
#else
            if( chmod( szNewpath, 0666 ) == -1 ) {
                printf( "Can not change mode..." );
            }

            sprintf( szExecute, "sudo chown %s:%s %s" , HOME_ID, HOME_ID, szNewpath );
            iRet = system( szExecute );
            if( iRet == 0 ) {
                //printf( "CEDEOB 파일을 업로드 했습니다" );
                strcat( gszUploadfiles, "CEDEOB/" );
                bRet = true;
            }
            else {
                //qError( "/etc/sudoers 에 www-data 권한을 추가하세요.", szExecute, iRet );
                //qError( "Can not execute %s[%d].", szExecute, iRet );
            }
#endif
            break;

        case enImage_File :
#ifdef __ZYNQ_BOARD__
            sprintf( szExecute, "/usr/bin/unzip -d %s -oq %s" , SD_CARD, gpSavepath );
#else
            sprintf( szExecute, "/usr/bin/unzip -d %s -oq %s" , SD_CARD, gpSavepath );
#endif
            iRet = system( szExecute );
            if( iRet == 0 ) {
                sprintf( szNewpath, "%s/image.ub", SD_CARD );
                sprintf( szExecute, "sudo chown %s:%s %s" , HOME_ID, HOME_ID, szNewpath );
                iRet = system( szExecute );
                if( iRet != 0 ) {
                    printf( "업로드 할 파일이 잘못 됐습니다[%s]." , szExecute );
                }
                else {
                    sprintf( szNewpath, "%s/u-boot.bin", SD_CARD );
                    sprintf( szExecute, "sudo chown %s:%s %s" , HOME_ID, HOME_ID, szNewpath );
                    iRet = system( szExecute );

                    if( iRet != 0 ) {
                        printf( "업로드 할 파일이 잘못 됐습니다[%s]." , szExecute );
                    }
                    else {
                        //printf( "운용 소프트웨어 파일을 업로드 했습니다 !!!\r\n" );
                        strcat( gszUploadfiles, "운용 소프트웨어/" );
                        bRet = true;
                    }
                }
            }
            break;

        case enINI_File :
            // 파일명 변경하기
            sprintf( szNewpath, "%s%s", INI_FOLDER, INI_FILENAME );
            if( rename( gpSavepath, szNewpath) == -1 ) {
                printf("Can not move uploaded file %s-%s.", gpSavepath, szNewpath );
            }

            // 권한 변경
#if 0
            pHome = getpwnam( HOME_ID );
            printf( "\n pHome->pw_uid[%d]" , pHome->pw_uid );
            if( chown( szNewpath, pHome->pw_uid, pHome->pw_gid ) == -1 ) {
                qError("Can not change owner file. %s", szNewpath );
            }
#else
            if( chmod( szNewpath, 0666 ) == -1 ) {
                printf( "Can not change mode..." );
            }

            // 소유권 변경
            sprintf( szExecute, "sudo chown %s:%s %s" , HOME_ID, HOME_ID, szNewpath );
            iRet = system( szExecute );
            if( iRet == 0 ) {
                //printf( "CEDEOB 파일을 업로드 했습니다" );
                strcat( gszUploadfiles, "INI/" );
                bRet = true;
            }

#endif
            break;

        default :
            break;

    }

    return bRet;
}

int main(int argc, char *argv[])
{
    bool bRet;
    bool bPageError=true;
    ENUM_UPLOAD enUpload;
    long lFilelength;

    char szMultiPart[100];
    char szLogDirectory[100];

    // 로그는 현재 홈 디렉토리에 저장한다.
    strcpy( szLogDirectory, QDECODER_LOG_FOLDER );
    strcat( szLogDirectory, QDECODER_LOG_FILENAME );
    qErrorLog( szLogDirectory );

    qErrorPrint( "=======================================" );
    qDecoderSetUploadBase( QDECODER_UPLOAD_FOLDER, 24 * 60 * 60 );

    qDecoder();
    qContentType( "text/html" );

    //printf("You entered: <b>%s</b>\n", qValueDefault("", "text"));

    gszUploadfiles[0] = 0;

    for( enUpload=enCEDEOB_File ; enUpload < enUPLOAD_FILES ; enUpload = (ENUM_UPLOAD) ( (int) enUpload + 1 ) ) {
        sprintf( szMultiPart, "upload_%d.length" , enUpload+1 );
        lFilelength = qlValue( szMultiPart );
        qErrorPrint( "filelength[%ld]", lFilelength );

        if( lFilelength != 0 ) {
            sprintf( szMultiPart, "upload_%d" , enUpload+1 );
            gpFileData = qValue( szMultiPart);
            sprintf( szMultiPart, "upload_%d.savepath" , enUpload+1 );
            gpSavepath = qValue( szMultiPart );
            sprintf( szMultiPart, "upload_%d.filename" , enUpload+1 );
            gpFilename = qValue( szMultiPart );

            //qErrorPrint( "Upload the [%s] file..." , szMultiPart );

            qErrorPrint( "Upload the filename[%s]", gpSavepath );

            bRet = ProcessUpload( enUpload );

            if( bRet == false ) {
                break;
            }

            //printf( "File Info.[%s%s]\n", pSavepath, pFilename );
            //sprintf( newpath, "%s/%s", pSavepath, pFilename);
            //if(rename(savepath, newpath) == -1) qError("Can not move uploaded file. %s-%s", savepath, newpath);

            // 실제 플레쉬 롬에 저장한다.
            //theBootShell->WriteIntoFlash( filedata, UDF_1_Bank );

            //ReLoadUDF();

            bPageError = false;
        }
    }

    if( bPageError == true ) {
        qError( "업로드할 파일을 선택하지 않았습니다. 찾아보기 버튼을 클릭하여 하나를 선택해주세요..." );
    }
    else {
        if( bRet == true ) {
            qAlert( "성공적으로 파일[%s]을 업로드 했습니다. !!!" , gszUploadfiles );
        }
    }

    _clear_savedir( upload_savedir );

    PreviousPage();

    qErrorPrint( "EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE" );

    qFree();

    return 0;
}

void PreviousPage()
{
  printf( "<html><head>" );
  printf( "<script language='JavaScript'>\n");
  printf( "setTimeout(function() {" );
  printf( "history.back()} , 100);" );
  printf( "</script>\n" );
  printf( "</head></html>" );

}
