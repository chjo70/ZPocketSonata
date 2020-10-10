#include <memory.h>

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
    qcgires_setcontenttype(req, "text/html");

    printf("Your order : ");

    qentobj_t obj;
    memset((void *)&obj, 0, sizeof(obj)); // must be cleared before call


    while (req->getnext(req, &obj, "formradio", false) == true) {
        printf("<b>%s</b> \n", (char *)obj.data);
    }

    if( qcgires_download(req, "copycgi.sh", 0 ) < 0 ) {
        // CGI 헤더를 보낸다.
        printf( "Content-type: text/html\n\n" );
    }

    req->free(req);

#ifdef ENABLE_FASTCGI
    }
#endif
    return 0;
}
