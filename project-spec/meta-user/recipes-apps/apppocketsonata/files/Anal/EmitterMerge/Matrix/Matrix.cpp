/*!
 * @file      Matrix.cpp
 * @brief     행렬 계산을 편리하게 계산하기 위한 클래스
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희
 * @date      2014-10-08 오전 8:50 
 * @warning   
 */


#include "stdafx.h"

#include "Matrix.h"
#include "../../SigAnal/_Define.h"
#include "../../INC/OS.h"

#include "../IsNumber.h"

#define MAX_ITEMS           (1000)

/**
 * @brief     객체를 생성한다.
 * @return    
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-04, 13:11
 * @warning
 */
CMatrix::CMatrix()
{
	//printf("Executing constructor CMatrix() ...\n");
	// create a CMatrix object without content
	p = NULL;
	m_uiRows = 0;
	m_uiCols = 0;
}

/**
 * @brief     객체를 소멸 처리를 한다.
 * @param     const unsigned int row_count
 * @param     const unsigned int column_count
 * @return    
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-04, 13:11
 * @warning
 */
CMatrix::CMatrix(const unsigned int row_count, const unsigned int column_count)
{
	// create a CMatrix object with given number of rows and columns
	p = NULL;

	m_uiRows = min( MAX_ITEMS, row_count );
	m_uiCols = min( MAX_ITEMS, column_count );

	p = new double*[m_uiRows];
	for (unsigned int r = 0; r < m_uiRows; r++)
	{
		p[r] = new double[m_uiCols];

		// initially fill in zeros for all values in the CMatrix;
		for (unsigned int c = 0; c < m_uiCols; c++)
		{
			p[r][c] = 0;
		}
	}

}

/**
 * @brief     CMatrix 값을 입력받아 동일한 값으로 설정한다.
 * @param     const CMatrix & a
 * @return    
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-04, 13:11
 * @warning
 */
CMatrix::CMatrix(const CMatrix& a)
{
    unsigned int uia_rows, uia_cols;

	m_uiRows = min( MAX_ITEMS, a.m_uiRows );
	m_uiCols = min( MAX_ITEMS, a.m_uiCols );

    uia_rows = min( MAX_ITEMS, a.m_uiRows );
    uia_cols = min( MAX_ITEMS, a.m_uiCols );
	p = new double*[uia_rows];

	/*! \debug  신뢰성: 메모리 할당하지 않으면 NULL 리턴함.
			\author 조철희 (churlhee.jo@lignex1.com)
			\date 	2015-10-5 17:12:29
	*/
	for(unsigned int r = 0; r < uia_rows ; r++ ) {
		p[r] = new double[uia_cols];

		/*! \debug  신뢰성: 메모리 할당하지 않으면 NULL 리턴함.
				\author 조철희 (churlhee.jo@lignex1.com)
				\date 	2015-10-5 17:14:53
		*/
// 		    if( p[r] == NULL ) {
// 			    for( int i=0 ; i < r ; ++ i ) {
// 				    if( p[r] != NULL ) delete p[r];
// 			    }
// 			    if( p != NULL ) delete p;
// 			    return;
// 		    }

		// copy the values from the CMatrix a
		for (unsigned int c = 0; c < uia_cols ; c++) {
            if( a.p != NULL && a.p[r] != NULL ) {
			    p[r][c] = a.p[r][c];
            }
		}
    }
}

/**
 * @brief     지정한 원소 값을 리턴한다.
 * @param     const unsigned int r
 * @param     const unsigned int c
 * @return    double&
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-04, 13:11
 * @warning
 */
double& CMatrix::operator()(const unsigned int r, const unsigned int c)
{
	if (p != NULL && r > 0 && r <= m_uiRows && c > 0 && c <= m_uiCols)
	{
		return p[r-1][c-1];
	}
	else
	{
		throw Exception("Subscript out of range");
	}
}

/**
 * @brief     행령의 지정한 위치의 원소값을 리턴한다.
 * @param     const unsigned int r
 * @param     const unsigned int c
 * @return    double
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-25 09:20:29
 * @warning
 */
double CMatrix::Get(const unsigned int r, const unsigned int c) const
{
	if (p != NULL && r > 0 && r <= m_uiRows && c > 0 && c <= m_uiCols)
	{
		return p[r-1][c-1];
	}
	else
	{
		throw Exception("Subscript out of range");
	}
}

/**
 * @brief     대입자 연산을 수행한다.
 * @param     const CMatrix & a
 * @return    CMatrix&
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-04, 13:11
 * @warning
 */
CMatrix& CMatrix::operator= (const CMatrix& a)
{
    unsigned int uia_rows, uia_cols;

	if( m_uiRows != 0 ) {
		CleanMatrix();
	}

	m_uiRows = _min( MAX_ITEMS, a.m_uiRows );
	m_uiCols = _min( MAX_ITEMS, a.m_uiCols );

    uia_rows = _min( MAX_ITEMS, a.m_uiRows );
    uia_cols = _min( MAX_ITEMS, a.m_uiCols );
	p = new double*[uia_rows];

	/*! \debug  신뢰성: 메모리 할당하지 않으면 NULL 리턴함.
			\author 조철희 (churlhee.jo@lignex1.com)
			\date 	2015-10-5 17:12:29
	*/
	//if( p == NULL ) 
	//	return *this;

	for (unsigned int r = 0; r < uia_rows ; r++) {
		p[r] = new double[uia_cols];

		/*! \debug  신뢰성: 메모리 할당하지 않으면 NULL 리턴함.
				\author 조철희 (churlhee.jo@lignex1.com)
				\date 	2015-10-5 17:14:53
		*/
// 		if( p[r] == NULL ) {
// 			for( unsigned int i=0 ; i < r ; ++ i ) {
// 				if( p[r] != NULL ) delete p[r];
// 			}
// 			if( p != NULL ) delete p;
// 			return *this;
// 		}

		// copy the values from the CMatrix a
		for (unsigned int c = 0; c < uia_cols ; c++) {
            if( a.p != NULL && a.p[r] != NULL ) {
			    p[r][c] = a.p[r][c];
            }
		}
	}
	return *this;
}

/**
 * @brief     더하기 행렬을 연산한다.
 * @param     const double v
 * @return    CMatrix&
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-04, 13:46
 * @warning
 */
CMatrix& CMatrix::Add(const double v)
{
	for (unsigned int r = 0; r < m_uiRows; r++) {
		for (unsigned int c = 0; c < m_uiCols; c++) {
            if( p[r] != NULL ) {
			    p[r][c] += v;
            }
		}
	}
	return *this;
}

/**
 * @brief     행렬 빼기 연산을 수행한다.
 * @param     const double v
 * @return    CMatrix::CMatrix&
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-25 09:50:07
 * @warning
 */
CMatrix& CMatrix::Subtract(const double v)
{
	return Add(-v);
}

/**
 * @brief     행렬 곱셈을 수행한다.
 * @param     const double v
 * @return    CMatrix::CMatrix&
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-25 09:50:21
 * @warning
 */
CMatrix& CMatrix::Multiply(const double v)
{
	for (unsigned int r = 0; r < m_uiRows; r++)
	{
		for (unsigned int c = 0; c < m_uiCols; c++)
		{
			p[r][c] *= v;
		}
	}
	return *this;
}

/**
 * @brief     행렬 나누기 연산을 수행한다.
 * @param     const double v
 * @return    CMatrix::CMatrix&
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-25 09:50:31
 * @warning
 */
CMatrix& CMatrix::Divide(const double v)
{
	return Multiply(1/v);
}

/**
 * @brief     행렬 더하기 연산을 수행한다.
 * @param     const CMatrix & a
 * @param     const CMatrix & b
 * @return    CMatrix
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-25 09:50:44
 * @warning
 */
CMatrix operator+(const CMatrix& a, const CMatrix& b)
{
	// check if the dimensions match
    CMatrix res(a.m_uiRows, a.m_uiCols);

	if (a.m_uiRows == b.m_uiRows && a.m_uiCols == b.m_uiCols)
	{
		for (unsigned int r = 0; r < a.m_uiRows; r++)
		{
			for (unsigned int c = 0; c < a.m_uiCols; c++)
			{
				res.p[r][c] = a.p[r][c] + b.p[r][c];
			}
		}
		//return res;
	}
	else
	{
		// give an error
		throw Exception("Dimensions does not match");
	}

	// return an empty CMatrix (this never happens but just for safety)
	return res; // CMatrix();
}

/**
 * @brief     행렬 더하기 연산을 수행한다.
 * @param     const CMatrix & a
 * @param     const double b
 * @return    CMatrix
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-25 09:51:00
 * @warning
 */
CMatrix operator+ (const CMatrix& a, const double b)
{
	CMatrix res = a;
	res.Add(b);
	return res;
}

/**
 * @brief     행렬에 모든 원소에 값을 더한다.
 * @param     const double b
 * @param     const CMatrix & a
 * @return    CMatrix
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-25 09:51:14
 * @warning
 */
CMatrix operator+ (const double b, const CMatrix& a)
{
	CMatrix res = a;
	res.Add(b);
	return res;
}

/**
 * @brief     행렬 뺴기 연산을 수행한다.
 * @param     const CMatrix & a
 * @param     const CMatrix & b
 * @return    CMatrix
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-25 09:51:32
 * @warning
 */
CMatrix operator- (const CMatrix& a, const CMatrix& b)
{
    CMatrix res(a.m_uiRows, a.m_uiCols);

	// check if the dimensions match
	if (a.m_uiRows == b.m_uiRows && a.m_uiCols == b.m_uiCols)
	{

		for (unsigned int r = 0; r < a.m_uiRows; r++)
		{
			for (unsigned int c = 0; c < a.m_uiCols; c++)
			{
				res.p[r][c] = a.p[r][c] - b.p[r][c];
			}
		}

	}
	else
	{
		// give an error
		throw Exception("Dimensions does not match");
	}

	// return an empty CMatrix (this never happens but just for safety)
	return res;
}

/**
 * @brief     행렬 빼기 연산을 수행한다.
 * @param     const CMatrix & a
 * @param     const double b
 * @return    CMatrix
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-25 09:51:52
 * @warning
 */
CMatrix operator- (const CMatrix& a, const double b)
{
	CMatrix res = a;
	res.Subtract(b);
	return res;
}

/**
 * @brief     원소에 빼기 연산을 수행한다.
 * @param     const double b
 * @param     const CMatrix & a
 * @return    CMatrix
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-25 09:52:05
 * @warning
 */
CMatrix operator- (const double b, const CMatrix& a)
{
	CMatrix res = -a;
	res.Add(b);
	return res;
}

/**
 * @brief     빼기 연산을 수행한다.
 * @param     const CMatrix & a
 * @return    CMatrix
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-25 09:55:55
 * @warning
 */
CMatrix operator- (const CMatrix& a)
{
	CMatrix res(a.m_uiRows, a.m_uiCols);

	for (unsigned int r = 0; r < a.m_uiRows; r++)
	{
		for (unsigned int c = 0; c < a.m_uiCols; c++)
		{
			res.p[r][c] = -a.p[r][c];
		}
	}

	return res;
}

/**
 * @brief     곱하기 연산을 수행한다.
 * @param     const CMatrix & a
 * @param     const CMatrix & b
 * @return    CMatrix
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-25 09:56:14
 * @warning
 */
CMatrix operator* (const CMatrix& a, const CMatrix& b)
{
    CMatrix res(a.m_uiRows, b.m_uiCols);

	// check if the dimensions match
	if (a.m_uiCols == b.m_uiRows)
	{	
		for (unsigned int r = 0; r < a.m_uiRows; r++)
		{
			for (unsigned int c_res = 0; c_res < b.m_uiCols; c_res++)
			{
				for (unsigned int c = 0; c < a.m_uiCols; c++)
				{
                    if( a.p != NULL ) {
					    res.p[r][c_res] += a.p[r][c] * b.p[c][c_res];
                    }
				}
			}
		}

	}
	else {
		// give an error
		throw Exception("Dimensions does not match");
	}

	// return an empty CMatrix (this never happens but just for safety)
	return res;
}

/**
 * @brief     곱하기 연산을 수행한다.
 * @param     const CMatrix & a
 * @param     const double b
 * @return    CMatrix
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-25 10:00:56
 * @warning
 */
CMatrix operator* (const CMatrix& a, const double b)
{
	CMatrix res = a;
	res.Multiply(b);
	return res;
}

/**
 * @brief     행렬에 상수값을 곱한다.
 * @param     const double b
 * @param     const CMatrix & a
 * @return    CMatrix
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-25 10:01:12
 * @warning
 */
CMatrix operator* (const double b, const CMatrix& a)
{
	CMatrix res = a;
	res.Multiply(b);
	return res;
}

/**
 * @brief     행렬에 나누기 연산을 수행한다.
 * @param     const CMatrix & a
 * @param     const CMatrix & b
 * @return    CMatrix
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-25 10:01:38
 * @warning
 */
CMatrix operator/ (const CMatrix& a, const CMatrix& b)
{
	// check if the dimensions match: must be square and equal sizes
	/*! \bug  	중복 비교로 판단문 제거함.
	    \author 조철희 (churlhee.jo@lignex1.com)
	    \date 	2014-01-22 14:55:36
	*/
	// if (a.uiRows == a.uiCols && a.uiRows == a.uiCols && b.uiRows == b.uiCols)
    CMatrix res(a.m_uiRows, a.m_uiCols);

	if (a.m_uiRows == a.m_uiCols && b.m_uiRows == b.m_uiCols && a.m_uiRows == b.m_uiRows )
	{
		bool bret;

		res = a * Inv(b, &bret );

		// return res;
	}
	else
	{
		// give an error
		throw Exception("Dimensions does not match");
	}

	// return an empty CMatrix (this never happens but just for safety)
	return res; //CMatrix();
}

/**
 * @brief     행렬에 상수값을 나누어 연산을 수행한다.
 * @param     const CMatrix & a
 * @param     const double b
 * @return    CMatrix
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-25 10:01:52
 * @warning
 */
CMatrix operator/ (const CMatrix& a, const double b)
{
	CMatrix res = a;
	res.Divide(b);
	return res;
}

/**
 * @brief     행렬에 나누기 연산을 수행한다.
 * @param     const double b
 * @param     const CMatrix & a
 * @return    CMatrix
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-25 10:02:28
 * @warning
 */
CMatrix operator/ (const double b, const CMatrix& a)
{
	CMatrix b_CMatrix(1, 1);
	b_CMatrix(1,1) = b;

	CMatrix res = b_CMatrix / a;
	return res;
}

/**
 * @brief     행렬의 여인수 연산을 수행한다.
 * @param     const unsigned int row
 * @param     const unsigned int col
 * @return    CMatrix
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-25 10:02:45
 * @warning
 */
CMatrix CMatrix::Minor(const unsigned int row, const unsigned int col) const
{
	CMatrix res;
	if (row > 0 && row <= m_uiRows && col > 0 && col <= m_uiCols)
	{
		res = CMatrix(m_uiRows - 1, m_uiCols - 1);

		// copy the content of the CMatrix to the minor, except the selected
		for (unsigned int r = 1; r <= (UINT) (m_uiRows - (UINT) (row >= m_uiRows) ); r++)
		{
			for (unsigned int c = 1; c <= (m_uiCols - (UINT) (col >= m_uiCols) ); c++)
			{
				res(r - (UINT) (r > row), c - (UINT) (c > col)) = p[r-1][c-1];
			}
		}
	}
	else
	{
		throw Exception("Index for minor out of range");
	}

	return res;
}

/**
 * @brief     행렬의 크기를 리턴한다.
 * @param     const int i
 * @return    unsigned int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-25 10:03:31
 * @warning
 */
unsigned int CMatrix::Size(const int i) const
{
    unsigned int uiRet=0;

	if (i == 1)
	{
		uiRet = m_uiRows;
	}
	else if (i == 2)
	{
		uiRet = m_uiCols;
	}
    else {
    }

	return uiRet;
}

/**
 * @brief     행렬의 행 값을 리턴한다.
 * @return    unsigned int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-25 10:03:48
 * @warning
 */
unsigned int CMatrix::GetRows() const
{
	return m_uiRows;
}

/**
 * @brief     행렬의 열 값을 리턴한다.
 * @return    unsigned int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-25 10:04:14
 * @warning
 */
unsigned int CMatrix::GetCols() const
{
	return m_uiCols;
}

/**
 * @brief     행렬 값을 프린트한다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-25 10:04:32
 * @warning
 */
void CMatrix::Print() const
{
#ifdef _MSC_VER	
	if (p != NULL)
	{
		TRACE0("[");
		for (unsigned int r = 0; r < m_uiRows; r++)
		{
			if (r > 0)
			{
				TRACE0(" ");
			}
			for (unsigned int c = 0; c < m_uiCols-1; c++)
			{
				TRACE1("%.6f, ", p[r][c]);
			}
			if (r < m_uiRows-1)
			{
				TRACE1("%.6f;\n", p[r][m_uiCols-1]);
			}
			else
			{
				TRACE1("%.6f]\n", p[r][m_uiCols-1]);
			}
		}
	}
	else
	{
		// CMatrix is empty
		TRACE0("[ ]\n");
	}
#endif	
}


/**
 * @brief     행렬 소멸자를 처리한다.
 * @return    
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-25 10:06:37
 * @warning
 */
CMatrix::~CMatrix()
{
	// clean up allocated memory
	CleanMatrix();

}

/**
 * @brief     행렬 값의 메모리를 해지한다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-25 10:06:52
 * @warning
 */
void CMatrix::CleanMatrix()
{
	for (unsigned int r = 0; r < m_uiRows; r++)
	{
		/*! \debug  신뢰성: 메모리 할당된 영역 체크하여 해지하게 함.
				\author 조철희 (churlhee.jo@lignex1.com)
				\date 	2015-10-5 17:09:41
		*/
        if( p != NULL && p[r] != NULL ) { delete p[r]; }
	}

	/*! \debug  신뢰성: 메모리 할당된 영역 체크하여 해지하게 함.
			\author 조철희 (churlhee.jo@lignex1.com)
			\date 	2015-10-5 17:09:41
	*/
	if( p != NULL ) delete p;
	p = NULL;
}

/**
 * @brief     행렬의 크기를 리턴한다.
 * @param     const CMatrix & a
 * @param     const int i
 * @return    unsigned int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-25 10:07:05
 * @warning
 */
unsigned int CMatrix::Size(const CMatrix& a, const int i)
{
	return a.Size(i);
}


/**
 * @brief     Ones 행렬로 설정한다.
 * @param     const unsigned int uiRows
 * @param     const unsigned int uiCols
 * @return    CMatrix
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-08 10:33:03
 * @warning
 */
CMatrix CMatrix::Ones(const unsigned int uiRows, const unsigned int uiCols)
{
	CMatrix res = CMatrix(uiRows, uiCols);

	for (unsigned int r = 1; r <= uiRows; r++)
	{
		for (unsigned int c = 1; c <= uiCols; c++)
		{
			res(r, c) = 1;
		}
	}
	return res;
}

/**
 * @brief     I 행렬로 설정한다.
 * @param     const unsigned int uiRows
 * @param     const unsigned int uiCols
 * @return    CMatrix
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-25 10:18:42
 * @warning
 */
CMatrix CMatrix::Ident(const unsigned int uiRows, const unsigned int uiCols)
{
	CMatrix res = CMatrix(uiRows, uiCols);

	for (unsigned int r = 1; r <= uiRows; r++)
	{
		for (unsigned int c = 1; c <= uiCols; c++)
		{
			if( r == c) {
				res(r, c) = 1;
            }
			else {
				res(r, c) = 0;
            }
		}
	}
	return res;
}

/**
 * @brief     Transpose 행렬을 수행한다.
 * @return    CMatrix
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-04, 13:35
 * @warning
 */
CMatrix CMatrix::Transpose()
{
    CMatrix res = CMatrix(m_uiCols, m_uiRows );

    for (unsigned int r = 1; r <= m_uiRows; r++) {
        for (unsigned int c = 1; c <= m_uiCols; c++) {
            if( p != NULL && p[r-1] != NULL ) {
                res(c, r) = p[r-1][c-1];
            }
        }
    }
    return res;
}

/**
 * @brief     0 행렬로 만든다.
 * @param     const int rows
 * @param     const int cols
 * @return    CMatrix
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-04, 13:35
 * @warning
 */
CMatrix CMatrix::Zeros(const unsigned int uiRows, const unsigned int uiCols)
{
	return CMatrix(uiRows, uiCols);
}

/**
 * @brief     N차원 Diag 행렬을 생성한다.
 * @param     const int n
 * @return    CMatrix
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-25 10:19:46
 * @warning
 */
CMatrix Diag(const unsigned int n)
{
	CMatrix res = CMatrix(n, n);
	for (unsigned int i = 1; i <= n; i++)
	{
		res(i, i) = 1;
	}
	return res;
}

/**
 * @brief     행렬의 Diag 행렬을 수행한다.
 * @param     const CMatrix & v
 * @return    a diagonal CMatrix with the given vector v on the diagonal
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-04, 13:35
 * @warning
 */
CMatrix Diag(const CMatrix& v)
{
	CMatrix res;
	if (v.GetCols() == 1)
	{
		// the given CMatrix is a vector n x 1
		unsigned int rows = v.GetRows();
		res = CMatrix(rows, rows);

		// copy the values of the vector to the CMatrix
		for (unsigned int r=1; r <= rows; r++)
		{
			res(r, r) = v.Get(r, 1);
		}
	}
	else if (v.GetRows() == 1)
	{
		// the given CMatrix is a vector 1 x n
		unsigned int cols = v.GetCols();
		res = CMatrix(cols, cols);

		// copy the values of the vector to the CMatrix
		for (unsigned int c=1; c <= cols; c++)
		{
			res(c, c) = v.Get(1, c);
		}
	}
	else
	{
		throw Exception("Parameter for diag must be a vector");
	}
	return res;
}

/**
 * @brief     행렬의 Determinant 연산을 수행한다.
 * @param     const CMatrix & a
 * @return    double
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-25 10:21:01
 * @warning
 */
double Det(const CMatrix& a)
{
	double d = 0;    // value of the determinant
	unsigned int rows = a.GetRows();
	/*! \bug  	Redundant Condition 의 경우, 항상 True거나 False로 판단되는 경우 발생함. Thread 바디로 무한루프를 사용하거나, OS자체적으로 제공하는 FOREVER 매크로 등을 사용한다면, False Alarm 처리 가능함. 그 이외의 경우라면 조치가 필요함 -> 코드실행률에 영향을 미침.
	    \author 조철희 (churlhee.jo@lignex1.com)
	    \date 	2014-02-03 13:28:21
	*/
	//int cols = a.GetRows();
	unsigned int cols = a.GetCols();

	if (rows == cols)
	{
		// this is a square CMatrix
		if (rows == 1)
		{
			// this is a 1 x 1 CMatrix
			d = a.Get(1, 1);
		}
		else if (rows == 2)
		{
			// this is a 2 x 2 CMatrix
			// the determinant of [a11,a12;a21,a22] is det = a11*a22-a21*a12
			d = a.Get(1, 1) * a.Get(2, 2) - a.Get(2, 1) * a.Get(1, 2);
		}
		else
		{
			// this is a CMatrix of 3 x 3 or larger
			for (unsigned int c = 1; c <= cols; c++)
			{
				CMatrix M = a.Minor(1, c);
				//d += pow(-1, 1+c) * a(1, c) * Det(M);
				d += (c%2 + c%2 - 1) * a.Get(1, c) * Det(M); // faster than with pow()
			}
		}
	}
	else
	{
		throw Exception("CMatrix must be square");
	}
	return d;
}

/**
 * @brief     행렬을 Swap 연산을 수행한다.
 * @param     double & a
 * @param     double & b
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-25 10:21:19
 * @warning
 */
void Swap(double& a, double& b)
{
	double temp = a;
	a = b;
	b = temp;
}

/**
 * @brief     행렬의 역행렬을 수행한다.
 * @param     const CMatrix & a
 * @param     bool * pRet
 * @return    CMatrix
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-25 10:21:40
 * @warning
 */
CMatrix Inv(const CMatrix& a, bool *pRet )
{
	CMatrix res;

	/*! \bug  	float 자료형에서 동등성 비교연산을 수행하지 말아야 한다.
	    \author 조철희 (churlhee.jo@lignex1.com)
	    \date 	2014-01-24 16:12:37
	*/
	// double d = 0;    // value of the determinant
	double d = (double) 0.0;    // value of the determinant

	unsigned int rows = a.GetRows();
	/*! \bug  	col 값을 row 값으로 잘못 사용함.
	    \author 조철희 (churlhee.jo@lignex1.com)
	    \date 	2014-02-03 13:32:45
	*/
	//int cols = a.GetRows();
	unsigned int cols = a.GetCols();

	d = Det(a);
	if (rows == cols && is_not_zero<double>(d) == true )
	{
		// this is a square CMatrix
		if (rows == 1)
		{
			// this is a 1 x 1 CMatrix
			res = CMatrix(rows, cols);
			res(1, 1) = 1 / a.Get(1, 1);
		}
		else if (rows == 2)
		{
			// this is a 2 x 2 CMatrix
			res = CMatrix(rows, cols);
			res(1, 1) = a.Get(2, 2);
			res(1, 2) = -a.Get(1, 2);
			res(2, 1) = -a.Get(2, 1);
			res(2, 2) = a.Get(1, 1);
			res = (1/d) * res;
		}
		else
		{
			// this is a CMatrix of 3 x 3 or larger
			// calculate inverse using gauss-jordan elimination
			//   http://mathworld.wolfram.com/CMatrixInverse.html
			//   http://math.uww.edu/~mcfarlat/inverse.htm
			res = Diag(rows);   // a diagonal CMatrix with ones at the diagonal
			CMatrix ai = a;    // make a copy of CMatrix a

			for (unsigned int c = 1; c <= cols; c++)
			{
				// element (c, c) should be non zero. if not, swap content
				// of lower rows
				unsigned int r;
				for (r = c; r < rows && is_zero<double>(ai(r, c)) == true ; r++)
				{
				}
				if (r != c)
				{
					// swap rows
					for (unsigned int s = 1; s <= cols; s++)
					{
						double dSwap1, dSwap2;

						//Swap(ai(c, s), ai(r, s));
						dSwap1 = ai(c, s);
						dSwap2 = ai(r, s);
						ai(c, s) = dSwap2;
						ai(r, s) = dSwap1;

						//Swap(res(c, s), res(r, s));
						dSwap1 = res(c, s);
						dSwap2 = res(r, s);
						res(c, s) = dSwap2;
						res(r, s) = dSwap1;
					}
				}

				// eliminate non-zero values on the other rows at column c
				for ( r = 1; r <= rows; r++)
				{
					if(r != c)
					{
						// eleminate value at column c and row r
						if ( is_not_zero<double>(ai(r, c)) == true) 
						{
							double f; // = -ai(r, c) / ai(c, c);
							f = -ai(r, c);
							f = f / ai(c, c);

							// add (f * row c) to row r to eleminate the value
							// at column c
							for (unsigned int s = 1; s <= cols; s++)
							{
								double dTemp;

								//ai(r, s) += f * ai(c, s);
								dTemp = f * ai(c, s);
								ai(r, s) += dTemp;


								//res(r, s) += f * res(c, s);
								dTemp = f * res(c, s);
								res(r, s) += dTemp;
							}
						}
					}
					else
					{
						// make value at (c, c) one,
						// divide each value on row r with the value at ai(c,c)
						double f = ai(c, c);
						for (unsigned int s = 1; s <= cols; s++)
						{
							ai(r, s) /= f;
							res(r, s) /= f;
						}
					}
				}
			}
		}
	}
	else
	{
		if (rows != cols)
		{
			throw Exception("CMatrix must be square");
		}
		else
		{
			*pRet = false;
			//return res;
			// throw Exception("Determinant of CMatrix is zero");
		}
	}

	*pRet = true;
	return res;
}

