#pragma once

#ifndef PORTABLE_SOCKET
#define PORTABLE_SOCKET

#ifdef WIN32
    #include <winsock2.h>
    #include <Ws2tcpip.h>
#else
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <unistd.h>
    #include <netdb.h>
    #include <arpa/inet.h>
#endif


#ifdef WIN32
	//REFACTOR
	static WSADATA *cucu;
    #define GetSocketError WSAGetLastError

    #define INIT_SOCKETS_LIB WSAStartup( MAKEWORD( 2, 2 ), cucu=new WSADATA() );
    #define RELEASE_SOCKETS_LIB delete (cucu);WSACleanup();

    #ifndef socklen_t
        typedef int socklen_t;
    #endif
#else
    #define closesocket close
    #define GetSocketError errno
    #define INIT_SOCKETS_LIB
    #define RELEASE_SOCKETS_LIB
    #define SOCKET_ERROR -1
#endif

#endif
