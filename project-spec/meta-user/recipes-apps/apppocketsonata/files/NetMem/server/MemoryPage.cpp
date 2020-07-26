#include "../utils/PortableSocket.h"
#include "MemoryPage.h"

#include <iostream>
#include <cstring>

using namespace std;


MemoryPage::MemoryPage(int length, int version)
{
	data = (unsigned char *)malloc(length);
	this->length=length;
	lockerId=-1;
	this->version=version;
}

unsigned char * MemoryPage::Lock( int callerId)
{
	pageMutex.lock();
	lockerId=callerId;
	return data;
}

int MemoryPage::Read(unsigned char * rData)
{
	boost::mutex::scoped_lock tmpLock(rwMutex);
	memcpy(rData, this->data,length);
	return 1;
}

int MemoryPage::Unlock(unsigned char * newData, int callerId)
{
	//if we can lock it, that means that was not been previously locked, so get out
	if (pageMutex.try_lock())
	{
		pageMutex.unlock();
		return 0;
	}
	//REFACTOR here we can use something like own_lock()
	if (callerId!=lockerId) return 0;

	if(newData)	
	{
		boost::mutex::scoped_lock tmpLock(rwMutex);
		memcpy(this->data,newData,length);
		version++;
	}
	lockerId=-1;
	if (version < 0 ) version=1;
	pageMutex.unlock();

	return version;
}


/**
 * Update (lock-unlock) the page
 * if the newVersion negative, just increase the version
 */
int MemoryPage::Update(unsigned char * newData, int newVersion, int callerId)
{
	if (!pageMutex.try_lock())
	{
		//the page is locked, if the caller is the same with the locker, we permit the update
		//if not, just wait unlocking
		if (callerId!=lockerId)
		{
			pageMutex.lock();
		}
	}
	
	boost::mutex::scoped_lock tmpLock(rwMutex);
	if(newData)memcpy(this->data,newData,length);
	if (version>=0)version=newVersion;
	else version++;
	if (version < 0 ) version=1;
	pageMutex.unlock();
	return version;
}

MemoryPage::~MemoryPage()
{
	free(data);
}
