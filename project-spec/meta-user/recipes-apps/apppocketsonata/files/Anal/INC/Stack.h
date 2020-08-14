/*!
  \file     stack.h
  \brief    
	\version  0.0.1
*/

#if !defined(AFX_STACK_H__29DC8683_3FE7_43C5_8E0E_04A359DC3DD6__INCLUDED_)
#define AFX_STACK_H__29DC8683_3FE7_43C5_8E0E_04A359DC3DD6__INCLUDED_

#ifdef __cplusplus

//////////////////////////////////////////////////////////////////////////
// 스택 

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
// 큐

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
	unsigned int Count();
	BOOL Push( T );
	BOOL Pop( T *element );
	void Reset();

	Queue(int nElems=10);
	~Queue();
	Queue &operator=( const Queue & );
};

template <class T>
Queue<T>::Queue(int nElems)
{
	head = tail = 0;
	v = new T[nelems = nElems];
	if( v == 0 ) {
		throw "out of memory";
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
	int i;
	head = tail = 0;

	if( v )
		delete[] v;
	v = new T[nelems = nElemt+1];

	//Reset();
	for( i=0 ; i < nelems ; ++i )
		v[i] = -1;


	if( v == 0 ) {
		throw "out of memory";
	}
}

template <class T>
void Queue<T>::Reset()
{
	int i;

	head = tail = 0;
	for( i=0 ; i < nelems ; ++i )
		v[i] = -1;

}

template <class T>
BOOL Queue<T>::Push( T element )
{
	if ( (tail+1) % nelems != head) {
		v[tail++]=element;
		tail %= nelems;
		return true;
	}
	else
		return false;

}

template <class T>
BOOL Queue<T>::Pop( T *element )
{
	if( tail != head ) {
		*element = v[head];
		v[head] = -1;
		++head;
		head %= nelems;
		return true;
	}
	else {
		return false;
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

//////////////////////////////////////////////////////////////////////////
// 원형 큐

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

	// 사전에 저장된 크기가 달리되어 있을 때,
	// 즉, 처음 작업을 할 때만 기록한다.
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
	//큐가 다 찬 상태면, false를 리턴
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