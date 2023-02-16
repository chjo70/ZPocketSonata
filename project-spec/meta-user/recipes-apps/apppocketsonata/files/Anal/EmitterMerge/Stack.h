/*!
  \file     stack.h
  \brief    
	\version  0.0.1
*/


#if !defined(AFX_STACK_H__29DC8683_3FE7_43C5_8E0E_04A359DC3DD6__INCLUDED_)
#define AFX_STACK_H__29DC8683_3FE7_43C5_8E0E_04A359DC3DD6__INCLUDED_

#ifdef __cplusplus

#ifndef __VXWORKS__
#include <memory.h>
#endif

#include "../SigAnal/_Type.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////////
// 스택 관련 템플릿 클래스

template <class T>
class Stack
{
	int nelems;
	int top;
	T *v;

public:
	void Print();
	void Init( unsigned int nElemt );
	unsigned int Count();
	bool Push( T );
	bool Remove( T );
	bool Pop( T *element );
	void Reset();
	inline T *GetData() { return v; }

	Stack(int nElems=10);
	~Stack();
//	Stack( const Stack & );
	Stack &operator=( const Stack & );
};

template <class T>
Stack<T>::Stack(int nElems)
{
	top = -1;
	v = new T[nelems = nElems];
	if( v == 0 ) {
		throw "out of memory";
	}
}



/*
template <class T>
Stack<T>::Stack( const Stack<T> &s )
{
	v = new T[nelems = s.nelems];
	if( v == 0 ) {
		throw "out of memory";
	}
	if( s.top > -1 ) {
		for( top = 0; top <= s.top; top++ ) {
			v[top] = s.v[top];
		}
		top--;
	}
}
*/

template <class T>
Stack<T>::~Stack()
{
	delete[] v;
}

template <class T>
void Stack<T>::Init(unsigned int nElemt)
{
	top = -1;

	if( v )
		delete[] v;
	v = new T[nelems = nElemt];
	if( v == 0 ) {
		throw "out of memory";
	}
}

template <class T>
void Stack<T>::Reset()
{
	int i;

	top = -1;

	for( i=0 ; i < nelems ; ++i )
		v[i] = -1;

}

template <class T>
void Stack<T>::Print()
{
	int i;

	printf( "\n Stack[%d]:" , top+1 );
	for( i=0 ; i <= top ; ++i )
		printf( "[%d]" , v[i] );
}

template <class T>
bool Stack<T>::Push( T element )
{
	top++;
	if( top >= nelems ) {
		// throw "out of memory";
/*
		T *new_buffer = new T[nelems += 10];
		if( new_buffer == 0 ) {
			throw "out of memory";
		}
		for( int i = 0; i < top; i++ ) {
			new_buffer[i] = v[i];
		}
		delete[] v;
		v = new_buffer;
*/
		-- top;
		return false;
	}
	else {
		v[top] = element;
		return true;
	}
}


template <class T>
bool Stack<T>::Pop( T *element )
{
	if( top < 0 ) {
		return false;
		// throw "pop on empty stack";
	}
	*element = v[top--];
	return true;
}

template <class T>
bool Stack<T>::Remove( T element )
{
	bool bRet;
	T x;

	if( Pop( & x ) == false )
		return false;

	if( x == element ) {
		return true;
	}
	else {
		bRet = Remove( element );
		Push( x );
		return bRet;
	}

}

template <class T>
unsigned int Stack<T>::Count()
{
	return top + 1;
}

template <class T>
Stack<T>& Stack<T> ::operator=( const Stack<T> &s )
{
	delete[] v;
	v = new T[nelems = s.nelems];
	if( v == 0 ) {
		throw "out of memory";
	}
	if( s.top > -1 ) {
		for( top = 0; top <= s.top; top++ ) {
			v[top] = s.v[top];
		}
		top--;
	}
	return *this;
}


//////////////////////////////////////////////////////////////////////////
// �걧

#define	MAX_OF_QUEUE_SIZE				(1000000)

template <class T>
class Queue
{
private:
	int nelems;
	int head;
	int tail;
	T *v;

public:
	void Print();
	void Init(unsigned int nElemt);
	int Count();
	bool Push( T );
	T *PushAt();
	T *GetPointerByIndex( UINT i );
	bool Pop( T *element );
	T *Pop();
	void Reset();

	void Copy( Queue *pSrc );

	Queue(int nElems=10);
	~Queue();
	Queue &operator=( const Queue & );
};

template <class T>
Queue<T>::Queue(int nElems)
{
	head = 0;
	tail = 0;

	/*! \debug  �떊猶곗꽦: �긽�븳媛� �꽕�젙
			\author 議곗쿋�씗 (churlhee.jo@lignex1.com)
			\date 	2015-10-6 16:00:58
	*/
	if( nElems < MAX_OF_QUEUE_SIZE ) {
		nelems = nElems;	
		v = new T[(UINT)nelems];
// 		if( v == 0 ) { //DTEC_NullPointCheck
// 			printf( "out of memory" );
// 		}
	}
    else {
        v = NULL;
    }

}

template <class T>
Queue<T>::~Queue()
{
	delete[] v;
}

template <class T>
void Queue<T>::Init(unsigned int nElemt)
{
	head = 0;
	tail = 0;

	if( v != NULL ) {
		delete[] v;
        v = NULL;
	}
	nelems = (int) nElemt + 1;
	if( nelems < MAX_OF_QUEUE_SIZE ) {
		v = new T[(UINT)nelems];

		memset( v, 0, sizeof(T)*(UINT) nelems );

// 		if( v == 0 ) {
// 			printf( "out of memory" );
// 		}
	}
}

template <class T>
void Queue<T>::Reset()
{

	head = 0;
    tail = 0;
	memset( v, 0, sizeof(T)*(UINT)nelems );

}

template <class T>
int Queue<T>::Count()
{
	int icount;

	icount = tail - head;
	if( icount < 0 ) {
		icount = icount + nelems;
	}

	return icount;
}

template <class T>
bool Queue<T>::Push( T element )
{
	bool bRet=false;
	if ( v != NULL && nelems != 0 && (tail+1) % nelems != head) {
		v[tail++]=element;
		tail %= nelems;
		bRet = true;
	}

	return bRet;

}

template <class T>
T *Queue<T>::PushAt()
{
	T *p=NULL;

	if ( v != NULL && nelems != 0 && (tail+1) % nelems != head) {
		p = & v[tail++];
		tail %= nelems;
	}

	return p;

}

template <class T>
T *Queue<T>::GetPointerByIndex( UINT i )
{
	UINT index=0;
	T *pRet=NULL;

	if( nelems != 0 ) {
		index = (UINT) head + i;
		index %= (UINT) nelems;
	}

	//return & v[index];
	pRet = & v[(UINT) index];
	return pRet;
}

template <class T>
bool Queue<T>::Pop( T *element )
{
	bool bRet=false;
	if( tail != head && nelems != 0 ) {
		if( v != NULL && element != NULL ) {
			*element = v[head];
		}
		// v[head] = -1;
		++head;
		head %= nelems;
		bRet = true;
	}
    else {
        //memset( element, 0, sizeof(T) );
    }

	return bRet;
}

template <class T>
T* Queue<T>::Pop()
{
	T *pT;

	if( tail != head ) {
		pT = & v[head];

		// v[head] = -1;
		++head;
		head %= nelems;
		return pT;
	}
	else {
		return NULL;
	}
}

template <class T>
void Queue<T>::Print()
{
	int i;

	printf( "\n Queue[%d]:" , nelems );
	for( i=0 ; i < nelems ; ++i )
		printf( "[%d]" , v[i] );
}


template <class T>
void Queue<T>::Copy( Queue *pQue )
{
	memcpy( v, pQue->v, sizeof(T)*(UINT) nelems );

	nelems = pQue->nelems;
	head = pQue->head;
	tail = pQue->tail;

}

//////////////////////////////////////////////////////////////////////////
// �썝�삎 �걧

template <typename T>
class CCircularQueue 
{
private:
	bool *pbFool;
	bool *pbEmpty;
	int *pNQueueCount;
	int *pRear;
	int *pFront;

public:
	bool DeQueueList( T *pEnlist );
	bool EnQueueList( T Enlist );
	void SetFool( bool state );
	bool IsFool();
	void SetEmpty( bool state );
	bool IsEmpty();
	void clearQueue();
 
	T *pQueueDataList;
	T initValue;
	CCircularQueue( T init, unsigned int size, T *pBuffer );
	virtual ~CCircularQueue();

};

template <typename T>
CCircularQueue<T>::CCircularQueue( T init, unsigned int size, T *pBuffer )
{
	pQueueDataList = pBuffer + ( 2*sizeof(int) + 3*sizeof(int) );
	pbFool = ( bool * ) & pBuffer[0];
	pbEmpty = ( bool * ) & pBuffer[4];
	pNQueueCount = ( int * ) & pBuffer[8];
	pRear = ( int * ) & pBuffer[12];
	pFront = ( int * ) & pBuffer[16];

	initValue = init;

	// �궗�쟾�뿉 ���옣�맂 �겕湲곌� �떖由щ릺�뼱 �엳�쓣 �븣,
	// 利�, 泥섏쓬 �옉�뾽�쓣 �븷 �븣留� 湲곕줉�븳�떎.
	if( *pNQueueCount != (int) size ) {
		*pFront = 0;
		*pRear  = 0;
		*pbFool = false;
		*pbEmpty = true;

		*pNQueueCount = size;
	}

	// clearQueue();

}

template <typename T>
CCircularQueue<T>::~CCircularQueue()
{

}

template <typename T>
void CCircularQueue<T>::clearQueue()
{
	for( int nCount =0; nCount<*pNQueueCount ; nCount++) {
		pQueueDataList[nCount] = initValue;
  }

}

template <typename T>
bool CCircularQueue<T>::IsEmpty()
{ 
	return *pbEmpty;
}

template <typename T>
void CCircularQueue<T>::SetEmpty( bool state )
{
	*pbEmpty = state;
}

template <typename T>
bool CCircularQueue<T>::IsFool()
{
	return *pbFool;
}

template <typename T>
void CCircularQueue<T>::SetFool( bool state )
{
	*pbFool = state;
}

template <typename T>
bool CCircularQueue<T>::EnQueueList( T Enlist )
{
	//�걧媛� �떎 李� �긽�깭硫�, false瑜� 由ы꽩
	if( IsFool() == false ) {
		pQueueDataList[*pFront] = Enlist;
		++ (*pFront);
		*pFront = *pFront % *pNQueueCount; 
  
		if( *pFront == *pRear )
			SetFool(true);
		else
			SetFool(false);
  
		SetEmpty(false);

		return true;
	}
	else {
		pQueueDataList[*pFront] = Enlist;

		++ (*pFront);
		*pFront = *pFront % *pNQueueCount;

		return false;
	}
 
}

template <typename T>
bool CCircularQueue<T>::DeQueueList( T *pBuffer )
{
	if( IsEmpty() == false ) {
		T strReturnList;

		if( IsFool() == true ) {
			*pRear = *pFront + 1;

			strReturnList = pQueueDataList[*pRear];
			pQueueDataList[*pRear] = initValue;
			++ (*pRear);
			*pRear = *pRear % *pNQueueCount;

			SetFool( false );

		}
		else {
			strReturnList = pQueueDataList[*pRear];
			pQueueDataList[*pRear] = initValue;
			++ (*pRear);
			*pRear = *pRear % *pNQueueCount;

			if( *pFront == *pRear ) 
				SetEmpty( true );
			else
				SetEmpty( false );
		}

		*pBuffer = strReturnList;
		return true;
	}
	else {
		return false;
	}

}


#endif

#endif // !defined(AFX_STACK_H__29DC8683_3FE7_43C5_8E0E_04A359DC3DD6__INCLUDED_)
