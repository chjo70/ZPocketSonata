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

#define MAX_ITEMS           (1000)

/**
 * @brief     CMatrix
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
	uiRows = 0;
	uiCols = 0;
}

// constructor
/**
 * @brief     CMatrix
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

	uiRows = _min( MAX_ITEMS, row_count );
	uiCols = _min( MAX_ITEMS, column_count );

	p = new double*[uiRows];
	for (unsigned int r = 0; r < uiRows; r++)
	{
		p[r] = new double[uiCols];

		// initially fill in zeros for all values in the CMatrix;
		for (unsigned int c = 0; c < uiCols; c++)
		{
			p[r][c] = 0;
		}
	}

}

// assignment operator
/**
 * @brief     CMatrix
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

	uiRows = _min( MAX_ITEMS, a.uiRows );
	uiCols = _min( MAX_ITEMS, a.uiCols );

    uia_rows = _min( MAX_ITEMS, a.uiRows );
    uia_cols = _min( MAX_ITEMS, a.uiCols );
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

// index operator. You can use this class like myCMatrix(col, row)
// the indexes are one-based, not zero based.
/**
 * @brief     operator()
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
	if (p != NULL && r > 0 && r <= uiRows && c > 0 && c <= uiCols)
	{
		return p[r-1][c-1];
	}
	else
	{
		throw Exception("Subscript out of range");
	}
}

// index operator. You can use this class like myCMatrix.get(col, row)
// the indexes are one-based, not zero based.
// use this function get if you want to read from a const CMatrix
double CMatrix::get(const unsigned int r, const unsigned int c) const
{
	if (p != NULL && r > 0 && r <= uiRows && c > 0 && c <= uiCols)
	{
		return p[r-1][c-1];
	}
	else
	{
		throw Exception("Subscript out of range");
	}
}

/**
 * @brief     CMatrix
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

	if( uiRows != 0 ) {
		CleanMatrix();
	}

	uiRows = _min( MAX_ITEMS, a.uiRows );
	uiCols = _min( MAX_ITEMS, a.uiCols );

    uia_rows = _min( MAX_ITEMS, a.uiRows );
    uia_cols = _min( MAX_ITEMS, a.uiCols );
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
 * @brief     add a double value (elements wise)
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
	for (unsigned int r = 0; r < uiRows; r++) {
		for (unsigned int c = 0; c < uiCols; c++) {
            if( p[r] != NULL ) {
			    p[r][c] += v;
            }
		}
	}
	return *this;
}

// subtract a double value (elements wise)
CMatrix& CMatrix::Subtract(const double v)
{
	return Add(-v);
}

// multiply a double value (elements wise)
CMatrix& CMatrix::Multiply(const double v)
{
	for (unsigned int r = 0; r < uiRows; r++)
	{
		for (unsigned int c = 0; c < uiCols; c++)
		{
			p[r][c] *= v;
		}
	}
	return *this;
}

// divide a double value (elements wise)
CMatrix& CMatrix::Divide(const double v)
{
	return Multiply(1/v);
}

// addition of CMatrix with CMatrix
CMatrix operator+(const CMatrix& a, const CMatrix& b)
{
	// check if the dimensions match
    CMatrix res(a.uiRows, a.uiCols);

	if (a.uiRows == b.uiRows && a.uiCols == b.uiCols)
	{
		for (unsigned int r = 0; r < a.uiRows; r++)
		{
			for (unsigned int c = 0; c < a.uiCols; c++)
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

// addition of CMatrix with double
CMatrix operator+ (const CMatrix& a, const double b)
{
	CMatrix res = a;
	res.Add(b);
	return res;
}
// addition of double with CMatrix
CMatrix operator+ (const double b, const CMatrix& a)
{
	CMatrix res = a;
	res.Add(b);
	return res;
}

// subtraction of CMatrix with CMatrix
CMatrix operator- (const CMatrix& a, const CMatrix& b)
{
    CMatrix res(a.uiRows, a.uiCols);

	// check if the dimensions match
	if (a.uiRows == b.uiRows && a.uiCols == b.uiCols)
	{

		for (unsigned int r = 0; r < a.uiRows; r++)
		{
			for (unsigned int c = 0; c < a.uiCols; c++)
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

// subtraction of CMatrix with double
CMatrix operator- (const CMatrix& a, const double b)
{
	CMatrix res = a;
	res.Subtract(b);
	return res;
}
// subtraction of double with CMatrix
CMatrix operator- (const double b, const CMatrix& a)
{
	CMatrix res = -a;
	res.Add(b);
	return res;
}

// operator unary minus
CMatrix operator- (const CMatrix& a)
{
	CMatrix res(a.uiRows, a.uiCols);

	for (unsigned int r = 0; r < a.uiRows; r++)
	{
		for (unsigned int c = 0; c < a.uiCols; c++)
		{
			res.p[r][c] = -a.p[r][c];
		}
	}

	return res;
}

// operator multiplication
CMatrix operator* (const CMatrix& a, const CMatrix& b)
{
    CMatrix res(a.uiRows, b.uiCols);

	// check if the dimensions match
	if (a.uiCols == b.uiRows)
	{	
		for (unsigned int r = 0; r < a.uiRows; r++)
		{
			for (unsigned int c_res = 0; c_res < b.uiCols; c_res++)
			{
				for (unsigned int c = 0; c < a.uiCols; c++)
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

// multiplication of CMatrix with double
CMatrix operator* (const CMatrix& a, const double b)
{
	CMatrix res = a;
	res.Multiply(b);
	return res;
}
// multiplication of double with CMatrix
CMatrix operator* (const double b, const CMatrix& a)
{
	CMatrix res = a;
	res.Multiply(b);
	return res;
}

// division of CMatrix with CMatrix
CMatrix operator/ (const CMatrix& a, const CMatrix& b)
{
	// check if the dimensions match: must be square and equal sizes
	/*! \bug  	중복 비교로 판단문 제거함.
	    \author 조철희 (churlhee.jo@lignex1.com)
	    \date 	2014-01-22 14:55:36
	*/
	// if (a.uiRows == a.uiCols && a.uiRows == a.uiCols && b.uiRows == b.uiCols)
    CMatrix res(a.uiRows, a.uiCols);

	if (a.uiRows == a.uiCols && b.uiRows == b.uiCols && a.uiRows == b.uiRows )
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

// division of CMatrix with double
CMatrix operator/ (const CMatrix& a, const double b)
{
	CMatrix res = a;
	res.Divide(b);
	return res;
}

// division of double with CMatrix
CMatrix operator/ (const double b, const CMatrix& a)
{
	CMatrix b_CMatrix(1, 1);
	b_CMatrix(1,1) = b;

	CMatrix res = b_CMatrix / a;
	return res;
}

/**
* returns the minor from the given CMatrix where
* the selected row and column are removed
*/
CMatrix CMatrix::Minor(const unsigned int row, const unsigned int col) const
{
	CMatrix res;
	if (row > 0 && row <= uiRows && col > 0 && col <= uiCols)
	{
		res = CMatrix(uiRows - 1, uiCols - 1);

		// copy the content of the CMatrix to the minor, except the selected
		for (unsigned int r = 1; r <= (uiRows - (row >= uiRows)); r++)
		{
			for (unsigned int c = 1; c <= (uiCols - (col >= uiCols)); c++)
			{
				res(r - (r > row), c - (c > col)) = p[r-1][c-1];
			}
		}
	}
	else
	{
		throw Exception("Index for minor out of range");
	}

	return res;
}

/*
* returns the size of the i-th dimension of the CMatrix.
* i.e. for i=1 the function returns the number of rows,
* and for i=2 the function returns the number of columns
* else the function returns 0
*/
unsigned int CMatrix::Size(const int i) const
{
    unsigned int uiRet=0;

	if (i == 1)
	{
		uiRet = uiRows;
	}
	else if (i == 2)
	{
		uiRet = uiCols;
	}
    else {
    }

	return uiRet;
}

// returns the number of rows
int CMatrix::GetRows() const
{
	return uiRows;
}

// returns the number of columns
int CMatrix::GetCols() const
{
	return uiCols;
}

// print the contents of the CMatrix
void CMatrix::Print() const
{
#ifdef _MSC_VER	
	if (p != NULL)
	{
		TRACE0("[");
		for (unsigned int r = 0; r < uiRows; r++)
		{
			if (r > 0)
			{
				TRACE0(" ");
			}
			for (unsigned int c = 0; c < uiCols-1; c++)
			{
				TRACE1("%.6f, ", p[r][c]);
			}
			if (r < uiRows-1)
			{
				TRACE1("%.6f;\n", p[r][uiCols-1]);
			}
			else
			{
				TRACE1("%.6f]\n", p[r][uiCols-1]);
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


// destructor
CMatrix::~CMatrix()
{
	// clean up allocated memory
	CleanMatrix();

}

void CMatrix::CleanMatrix()
{
	for (unsigned int r = 0; r < uiRows; r++)
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

/*
* i.e. for i=1 the function returns the number of rows,
* and for i=2 the function returns the number of columns
* else the function returns 0
*/
int CMatrix::Size(const CMatrix& a, const int i)
{
	return a.Size(i);
}


/**
* returns a CMatrix with size cols x rows with ones as values
*/
CMatrix CMatrix::Ones(const int rows, const int cols)
{
	CMatrix res = CMatrix(rows, cols);

	for (int r = 1; r <= rows; r++)
	{
		for (int c = 1; c <= cols; c++)
		{
			res(r, c) = 1;
		}
	}
	return res;
}

CMatrix CMatrix::Ident(const int rows, const int cols)
{
	CMatrix res = CMatrix(rows, cols);

	for (int r = 1; r <= rows; r++)
	{
		for (int c = 1; c <= cols; c++)
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
 * @brief     Transpose
 * @return    CMatrix
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-04, 13:35
 * @warning
 */
CMatrix CMatrix::Transpose()
{
    CMatrix res = CMatrix(uiCols, uiRows );

    for (unsigned int r = 1; r <= uiRows; r++) {
        for (unsigned int c = 1; c <= uiCols; c++) {
            if( p != NULL && p[r-1] != NULL ) {
                res(c, r) = p[r-1][c-1];
            }
        }
    }
    return res;
}


/**
* returns a CMatrix with size cols x rows with zeros as values
*/
/**
 * @brief     Zeros
 * @param     const int rows
 * @param     const int cols
 * @return    CMatrix
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-04, 13:35
 * @warning
 */
CMatrix CMatrix::Zeros(const int rows, const int cols)
{
	return CMatrix(rows, cols);
}


/**
* returns a diagonal CMatrix with size n x n with ones at the diagonal
* @param  v a vector
* @return a diagonal CMatrix with ones on the diagonal
*/
CMatrix Diag(const int n)
{
	CMatrix res = CMatrix(n, n);
	for (int i = 1; i <= n; i++)
	{
		res(i, i) = 1;
	}
	return res;
}

/**
 * @brief     Diag
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
		int rows = v.GetRows();
		res = CMatrix(rows, rows);

		// copy the values of the vector to the CMatrix
		for (int r=1; r <= rows; r++)
		{
			res(r, r) = v.get(r, 1);
		}
	}
	else if (v.GetRows() == 1)
	{
		// the given CMatrix is a vector 1 x n
		int cols = v.GetCols();
		res = CMatrix(cols, cols);

		// copy the values of the vector to the CMatrix
		for (int c=1; c <= cols; c++)
		{
			res(c, c) = v.get(1, c);
		}
	}
	else
	{
		throw Exception("Parameter for diag must be a vector");
	}
	return res;
}

/*
* returns the determinant of CMatrix a
*/
double Det(const CMatrix& a)
{
	double d = 0;    // value of the determinant
	int rows = a.GetRows();
	/*! \bug  	Redundant Condition 의 경우, 항상 True거나 False로 판단되는 경우 발생함. Thread 바디로 무한루프를 사용하거나, OS자체적으로 제공하는 FOREVER 매크로 등을 사용한다면, False Alarm 처리 가능함. 그 이외의 경우라면 조치가 필요함 -> 코드실행률에 영향을 미침.
	    \author 조철희 (churlhee.jo@lignex1.com)
	    \date 	2014-02-03 13:28:21
	*/
	//int cols = a.GetRows();
	int cols = a.GetCols();

	if (rows == cols)
	{
		// this is a square CMatrix
		if (rows == 1)
		{
			// this is a 1 x 1 CMatrix
			d = a.get(1, 1);
		}
		else if (rows == 2)
		{
			// this is a 2 x 2 CMatrix
			// the determinant of [a11,a12;a21,a22] is det = a11*a22-a21*a12
			d = a.get(1, 1) * a.get(2, 2) - a.get(2, 1) * a.get(1, 2);
		}
		else
		{
			// this is a CMatrix of 3 x 3 or larger
			for (int c = 1; c <= cols; c++)
			{
				CMatrix M = a.Minor(1, c);
				//d += pow(-1, 1+c) * a(1, c) * Det(M);
				d += (c%2 + c%2 - 1) * a.get(1, c) * Det(M); // faster than with pow()
			}
		}
	}
	else
	{
		throw Exception("CMatrix must be square");
	}
	return d;
}

// swap two values
void Swap(double& a, double& b)
{
	double temp = a;
	a = b;
	b = temp;
}

/*
* returns the inverse of CMatrix a
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

	int rows = a.GetRows();
	/*! \bug  	col 값을 row 값으로 잘못 사용함.
	    \author 조철희 (churlhee.jo@lignex1.com)
	    \date 	2014-02-03 13:32:45
	*/
	//int cols = a.GetRows();
	int cols = a.GetCols();

	d = Det(a);
	if (rows == cols && d != 0)
	{
		// this is a square CMatrix
		if (rows == 1)
		{
			// this is a 1 x 1 CMatrix
			res = CMatrix(rows, cols);
			res(1, 1) = 1 / a.get(1, 1);
		}
		else if (rows == 2)
		{
			// this is a 2 x 2 CMatrix
			res = CMatrix(rows, cols);
			res(1, 1) = a.get(2, 2);
			res(1, 2) = -a.get(1, 2);
			res(2, 1) = -a.get(2, 1);
			res(2, 2) = a.get(1, 1);
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

			for (int c = 1; c <= cols; c++)
			{
				// element (c, c) should be non zero. if not, swap content
				// of lower rows
				int r;
				for (r = c; r <= rows && ai(r, c) == 0; r++)
				{
				}
				if (r != c)
				{
					// swap rows
					for (int s = 1; s <= cols; s++)
					{
						Swap(ai(c, s), ai(r, s));
						Swap(res(c, s), res(r, s));
					}
				}

				// eliminate non-zero values on the other rows at column c
				for (int r = 1; r <= rows; r++)
				{
					if(r != c)
					{
						// eleminate value at column c and row r
						if (ai(r, c) != 0)
						{
							double f = - ai(r, c) / ai(c, c);

							// add (f * row c) to row r to eleminate the value
							// at column c
							for (int s = 1; s <= cols; s++)
							{
								ai(r, s) += f * ai(c, s);
								res(r, s) += f * res(c, s);
							}
						}
					}
					else
					{
						// make value at (c, c) one,
						// divide each value on row r with the value at ai(c,c)
						double f = ai(c, c);
						for (int s = 1; s <= cols; s++)
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
			return res;
			// throw Exception("Determinant of CMatrix is zero");
		}
	}

	*pRet = true;
	return res;
}

