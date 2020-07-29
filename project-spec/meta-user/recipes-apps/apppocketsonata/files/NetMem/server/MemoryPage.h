#pragma once
#ifndef MEMORYPAGE_H
#define MEMORYPAGE_H

//#include "sqlite/sqlite3.h"
#include <boost/thread/mutex.hpp>

class MemoryPage
{
public:
	MemoryPage(int length, int version);
	~MemoryPage();
	unsigned char * Lock(int callerId);
	int Unlock(unsigned char * data, int callerId);
	int Read(unsigned char * rData);
	int Update(unsigned char * newData, int newVersion, int callerId);
	int version;
	unsigned char * data;

    boost::mutex pageMutex;
    boost::mutex rwMutex;
	int length;
	int lockerId;
	
};

#endif /*MEMORYPAGE_H*/
