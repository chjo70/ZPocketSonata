#pragma once

#ifndef APINETMEM_H
#define APINETMEM_H

#include <cstdlib>

#define API_NET_MEM_MAJOR_VERSION 0
#define API_NET_MEM_MINOR_VERSION 2

namespace ApiNetMem
{
	//commands
	#define GET_VERSION		0
	#define GET_PARAMS		1
	#define READ_PAGE		2
	#define LOCK_PAGE		3
	#define UNLOCK_PAGE		4
	#define UPDATE_PAGE		5
	
	//return codes
	#define NO_SUCH_PAGE	100
	#define PAGE_NOT_LOCKED	101
	
	//errors
	#define SERVER_DISCONNECTED					0
	#define NO_SERVER_CONNECTION				1
	#define NO_PAGES_INIT						2
	#define CLIENT_DISCONNECTED					3
	#define NO_COMPATIBLE_SERVER_VERSIONS		4
	
	
	//Just count... the data attribute doesn't include
	#define SIZEOF_NETMEM_COMMAND 13
	
	char * GetErrorMessage(int code);
	
	struct NetMemCommand
	{
		NetMemCommand(){data=0;}
		unsigned char type;
		long offset;
		long length;
		long version;
		unsigned char * data;
		~NetMemCommand(){if (data)free(data);}
	};
	

};
#endif
