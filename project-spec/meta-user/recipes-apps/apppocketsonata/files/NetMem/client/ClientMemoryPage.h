#pragma once
#ifndef CLIENTMEMORYPAGE_H
#define CLIENTMEMORYPAGE_H

#include "../utils/ApiNetMem.h"
using namespace ApiNetMem;

/**
 * This is the light version of a memory page, without the mutexes
 */
 
class ClientMemoryPage
{
public:
	ClientMemoryPage(int length, int offset, int version);
	~ClientMemoryPage();
	void SetData(NetMemCommand * newData);

	//REFACTOR - make this private
	unsigned char * data;
	int length;
	int version;
	int offset;
private:


	
};

#endif /*CLIENTMEMORYPAGE_H*/
