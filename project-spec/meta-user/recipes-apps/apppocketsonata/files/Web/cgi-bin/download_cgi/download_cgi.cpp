
#ifdef ENABLE_FASTCGI
#include "fcgi_stdio.h"
#else
#include <stdio.h>
#endif
#include <stdlib.h>
#include <stdbool.h>
#include "../Qdecoder/qdecoder.h"

int main(int argc, char *argv[])
{


#ifdef ENABLE_FASTCGI
    while(FCGI_Accept() >= 0) {
#endif
    qentry_t *req = qcgireq_parse(NULL, Q_CGI_ALL);
    if( qcgires_download(req, "download.cgi", "text/plain") < 0 ) {
        // CGI 헤더를 보낸다.
        printf( "Content-type: text/html\n\n" );
    }
#ifdef ENABLE_FASTCGI
    }
#endif
    return 0;
}
