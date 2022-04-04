/*
A simple CMatrix class
c++ code
Author: Jos de Jong, Nov 2007. Updated March 2010

With this class you can:
  - create a 2D CMatrix with custom size
  - get/set the cell values
  - use operators +, -, *, /
  - use functions Ones(), Zeros(), Diag(), Det(), Inv(), Size()
  - print the content of the CMatrix

Usage:
  you can create a CMatrix by:
    CMatrix A;
    CMatrix A = CMatrix(rows, cols);
    CMatrix A = B;

  you can get and set CMatrix elements by:
    A(2,3) = 5.6;    // set an element of Matix A
    value = A(3,1);   // get an element of CMatrix A
    value = A.get(3,1); // get an element of a constant CMatrix A
    A = B;        // copy content of CMatrix B to CMatrix A

  you can apply operations with matrices and doubles:
    A = B + C;
    A = B - C;
    A = -B;
    A = B * C;
    A = B / C;

  the following functions are available:
    A = Ones(rows, cols);
    A = Zeros(rows, cols);
    A = Diag(n);
    A = Diag(B);
    d = Det(A);
    A = Inv(B);
    cols = A.GetCols();
    rows = A.GetRows();
    cols = Size(A, 1);
    rows = Size(A, 2);

  you can quick-print the content of a CMatrix in the console with:
    A.Print();
*/

#pragma once

#include <cstdlib>
#include <cstdio>
#include <math.h>

#define PAUSE {printf("Press \"Enter\" to continue\n"); fflush(stdin); getchar(); fflush(stdin);}

// Declarations
class CMatrix;
//double Det(const CMatrix& a);
//CMatrix Diag(const int n);
//CMatrix Diag(const CMatrix& v);
//CMatrix Inv(const CMatrix& a);
//CMatrix Ones(const int rows, const int cols);
//int Size(const CMatrix& a, const int i);
//CMatrix Zeros(const int rows, const int cols);


/*
 * a simple exception class
 * you can create an exeption by entering
 *   throw Exception("...Error description...");
 * and get the error message from the data msg for displaying:
 *   err.msg
 */
class Exception
{
public:
  const char* msg;
  Exception(const char* arg)
   : msg(arg)
  {
  }
};

class CMatrix
{
public:
  // constructor
  CMatrix();
  // constructor
  CMatrix(const unsigned int row_count, const unsigned int column_count);
  // assignment operator
  CMatrix(const CMatrix& a);

  // index operator. You can use this class like myCMatrix(col, row)
  // the indexes are one-based, not zero based.
  double& operator()(const unsigned int r, const unsigned int c);

  // index operator. You can use this class like myCMatrix.get(col, row)
  // the indexes are one-based, not zero based.
  // use this function get if you want to read from a const CMatrix
  double get(const unsigned int r, const unsigned int c) const;
  
  // assignment operator
  CMatrix& operator= (const CMatrix& a); 

  // add a double value (elements wise)
  CMatrix& Add(const double v);

  // subtract a double value (elements wise)
  CMatrix& Subtract(const double v);

  // multiply a double value (elements wise)
  CMatrix& Multiply(const double v);

  // divide a double value (elements wise)
  CMatrix& Divide(const double v);
  
  // addition of CMatrix with CMatrix
  friend CMatrix operator+(const CMatrix& a, const CMatrix& b);
  
  // addition of CMatrix with double
  friend CMatrix operator+ (const CMatrix& a, const double b);
  
  // addition of double with CMatrix
  friend CMatrix operator+ (const double b, const CMatrix& a);
 
  // subtraction of CMatrix with CMatrix
  friend CMatrix operator- (const CMatrix& a, const CMatrix& b);
  
  // subtraction of CMatrix with double
  friend CMatrix operator- (const CMatrix& a, const double b);
  
  // subtraction of double with CMatrix
  friend CMatrix operator- (const double b, const CMatrix& a);
  
  // operator unary minus
  friend CMatrix operator- (const CMatrix& a);  

  // operator multiplication
  friend CMatrix operator* (const CMatrix& a, const CMatrix& b);
  
  // multiplication of CMatrix with double
  friend CMatrix operator* (const CMatrix& a, const double b);
  
  // multiplication of double with CMatrix
  friend CMatrix operator* (const double b, const CMatrix& a);
  
  // division of CMatrix with CMatrix
  friend CMatrix operator/ (const CMatrix& a, const CMatrix& b);
  
  // division of CMatrix with double
  friend CMatrix operator/ (const CMatrix& a, const double b);
 
  // division of double with CMatrix
  friend CMatrix operator/ (const double b, const CMatrix& a);
 
  /**
   * returns the minor from the given CMatrix where
   * the selected row and column are removed
   */
  CMatrix Minor(const unsigned int row, const unsigned int col) const;

  /*
   * returns the size of the i-th dimension of the CMatrix.
   * i.e. for i=1 the function returns the number of rows,
   * and for i=2 the function returns the number of columns
   * else the function returns 0
   */
  unsigned int Size(const int i) const;
 
  // returns the number of rows
  int GetRows() const;

  // returns the number of columns
  int GetCols() const;

  // print the contents of the CMatrix
  void Print() const;
  
public:
  // destructor
  ~CMatrix();

  void CleanMatrix();

  int Size(const CMatrix& a, const int i);
  CMatrix Ones(const int rows, const int cols);
  CMatrix Zeros(const int rows, const int cols);
  CMatrix Ident(const int rows, const int cols);
  
  CMatrix Transpose();
  

private:
  unsigned int uiRows;
  unsigned int uiCols;
  double** p;     // pointer to a CMatrix with doubles
};


 CMatrix Inv(const CMatrix& a, bool *pRet);
 double Det(const CMatrix& a);
 CMatrix Diag(const int n);
 CMatrix Diag(const CMatrix& v);
 void Swap(double& a, double& b);


 /*
 int main(int argc, char *argv[])
{
  // below some demonstration of the usage of the CMatrix class
  try
  {
    // create an empty CMatrix of 3x3 (will initially contain zeros)
    int cols = 3;
    int rows = 3;
    CMatrix A = CMatrix(cols, rows);

    // fill in some values in CMatrix a
    int count = 0;
    for (int r = 1; r <= rows; r++)
    {
      for (int c = 1; c <= cols; c++)
      {
        count ++;
        A(r, c) = count;
      }
    }

    // adjust a value in the CMatrix (indexes are one-based)
    A(2,1) = 1.23;

    // read a value from the CMatrix (indexes are one-based)
    double centervalue = A(2,2);
    printf("centervalue = %f \n", centervalue);
    printf("\n");

    // print the whole CMatrix
    printf("A = \n");
    A.Print();
    printf("\n");

    CMatrix B = Ones(rows, cols) + Diag(rows);
    printf("B = \n");
    B.Print();
    printf("\n");

    CMatrix B2 = CMatrix(rows, 1);    // a vector
    count = 1;
    for (int r = 1; r <= rows; r++)
    {
      count ++;
      B2(r, 1) = count * 2;
    }
    printf("B2 = \n");
    B2.Print();
    printf("\n");

    CMatrix C;
    C = A + B;
    printf("A + B = \n");
    C.Print();
    printf("\n");

    C = A - B;
    printf("A - B = \n");
    C.Print();
    printf("\n");

    C = A * B2;
    printf("A * B2 = \n");
    C.Print();
    printf("\n");

    // create a diagonal CMatrix
    CMatrix E = Diag(B2);
    printf("E = \n");
    E.Print();
    printf("\n");

    // calculate determinant
    CMatrix D = CMatrix(2, 2);
    D(1,1) = 2;
    D(1,2) = 4;
    D(2,1) = 1;
    D(2,2) = -2;
    printf("D = \n");
    D.Print();
    printf("Det(D) = %f\n\n", Det(D));

    printf("A = \n");
    A.Print();
    printf("\n");
    printf("Det(A) = %f\n\n", Det(A));

    CMatrix F;
    F = 3 - A ;
    printf("3 - A = \n");
    F.Print();
    printf("\n");

    // test inverse
    CMatrix G = CMatrix(2, 2);
    G(1, 1) = 1;
    G(1, 2) = 2;
    G(2, 1) = 3;
    G(2, 2) = 4;
    printf("G = \n");
    G.Print();
    printf("\n");
    CMatrix G_inv = Inv(G);
    printf("Inv(G) = \n");
    G_inv.Print();
    printf("\n");

    CMatrix A_inv = Inv(A);
    printf("Inv(A) = \n");
    A_inv.Print();
    printf("\n");

    CMatrix A_A_inv = A * Inv(A);
    printf("A * Inv(A) = \n");
    A_A_inv.Print();
    printf("\n");

    CMatrix B_A = B / A;
    printf("B / A = \n");
    B_A.Print();
    printf("\n");

    CMatrix A_3 = A / 3;
    printf("A / 3 = \n");
    A_3.Print();
    printf("\n");

    rows = 2;
    cols = 5;
    CMatrix H = CMatrix(rows, cols);
    for (int r = 1; r <= rows; r++)
    {
      for (int c = 1; c <= cols; c++)
      {
        count ++;
        H(r, c) = count;
      }
    }
    printf("H = \n");
    H.Print();
    printf("\n");
  }
  catch (Exception err)
  {
    printf("Error: %s\n", err.msg);
  }
  catch (...)
  {
    printf("An error occured...\n");
  }

  printf("\n");
  PAUSE;

  return EXIT_SUCCESS;
}
*/