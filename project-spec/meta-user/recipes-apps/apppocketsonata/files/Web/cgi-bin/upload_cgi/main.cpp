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


#include "../../../Anal/INC/system.h"

#include "../Qdecoder/qDecoder.h"

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
            printf( "\n Delete filepath[%s]" , filepath );
            if( unlink(filepath) == -1 ) {
                return -1;
            }
        }

    }
    closedir(dp);

    return rmdir( dir );

#endif


}

void PreviousPage();


int main(int argc, char *argv[])
{
    int iSwitch;
    long lFilelength;

    char *pSavepath, *pFilename;

    char newpath[1024];
    char szLogDirectory[100];

    // 로그는 현재 홈 디렉토리에 저장한다.
    strcpy( szLogDirectory, QDECODER_LOG_FOLDER );
    strcat( szLogDirectory, QDECODER_LOG_FILENAME );
    qErrorLog( szLogDirectory );

    qErrorPrint( "=======================================" );
    qDecoderSetUploadBase( "/home/chjo70", 24 * 60 * 60 );

    qContentType( "text/html" );
    qDecoder();
    //printf("You entered: <b>%s</b>\n", qValueDefault("", "text"));

    lFilelength = qlValue( "cedeob_binary.length" );
    qErrorPrint( "filelength[%ld]\n", lFilelength );

    if( lFilelength != 0 ) {
        qErrorPrint( "Upload...CEDEOB" );

        pSavepath = qValue( "cedeob_binary.savepath" );
        pFilename = qValue( "cedeob_binary.filename" );

        printf( "upload_savedir[%s]\n", upload_savedir );

        PreviousPage();

        //printf( "File Info.[%s%s]\n", pSavepath, pFilename );
        //sprintf( newpath, "%s/%s", pSavepath, pFilename);
        //if(rename(savepath, newpath) == -1) qError("Can not move uploaded file. %s-%s", savepath, newpath);

        // 실제 플레쉬 롬에 저장한다.
        //theBootShell->WriteIntoFlash( filedata, UDF_1_Bank );

        //ReLoadUDF();
        //_clear_savedir( upload_savedir );

    }
    else {
        qError( "업로드할 파일을 선택하지 않았습니다. 찾아보기 버튼을 클릭하여 하나를 선택해주세요..." );
    }

    qErrorPrint( "EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE" );

    qFree();

    return 0;
}

void PreviousPage()
{
  printf( "<html><head>" );
  printf( "<script language='JavaScript'>\n");
  printf( "setTimeout(function() {" );
  printf( "history.back()} , 2000);" );
  printf( "</script>\n" );
  printf( "</head></html>" );

}
