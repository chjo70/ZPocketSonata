#include "ApiNetMem.h"

namespace ApiNetMem
{

    char * GetErrorMessage(int code)
    {
        static int noMessages=5;
        static char messages[5][50]={	"Server disconnected",
                                    "Unable to connect to server",
                                    "Pages initialisation error",
                                    "Client disconnected",
                                    "No compatible server API version"};
        if (code>=noMessages || code<0) return NULL;
        return messages[code];
    };

};

