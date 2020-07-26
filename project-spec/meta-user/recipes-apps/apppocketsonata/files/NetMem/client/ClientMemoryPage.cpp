#include "../utils/PortableSocket.h"
#include "ClientMemoryPage.h"

#include <iostream>
#include <cstring>

using namespace std;
using namespace ApiNetMem;

ClientMemoryPage::ClientMemoryPage(int length, int offset, int version)
{
	this->length = length;
	this->version = version;
	this->offset = offset;
	data = (unsigned char *)malloc(length);
}

ClientMemoryPage::~ClientMemoryPage()
{
	free(data);
}

void ClientMemoryPage::SetData(NetMemCommand * newData)
{
	memcpy(data, newData->data, length);
	this->version=newData->version;
	this->offset = newData->offset;
}
