
// Show.h : 클래스의 인터페이스
//

#pragma once

#include "../../Files/Anal/Collect/DataFile/DataFile.h"


class CShow
{
private:

public:
	CShow();
	virtual ~CShow();

	virtual void ShowGraph( ENUM_SUB_GRAPH enSubGraph=enSubMenu_1, int iFileIndex=0 )=0;
	
};

