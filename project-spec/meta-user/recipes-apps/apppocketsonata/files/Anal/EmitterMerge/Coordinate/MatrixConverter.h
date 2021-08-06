/********************************************************
 @file      MatrixConverter.h
 @author    정준우 (junwoo.jung@lignex1.com)
 @brief     SBAS 매트릭스 처리 클래스
 @detail    SBAS 매트릭스 처리 클래스
            매트릭스 덧셈, 뺄셈, 곱셈, 역행렬 등 연산
 @version   0.1.0a
 @date      2014/07/23
 @history
  - 2014/07/04 정준우 프로젝트 생성
  - 2014/07/15 정준우 기본적인 행렬 덧셈, 뺄셈, 곱셈, 역행렬 완성
  - 2014/07/22 정준우 Least Sqaure 연산 메소드 추가
  - 2014/07/23 정준우 Least Sqaure 연산에서 메모리 누수 버그 수정
  - 2014/07/28 정준우 Norm 연산 메소드 추가
  - 2014/07/29 정준우 Enhanced Kalman Filter용 Matrix 연산 추가 구현 (MatrixExp 등)
 @Copyright copyright by LIG Nex1 Co. Ltd
********************************************************/
#ifndef _MATRIX_CONVERTER_H_
#define _MATRIX_CONVERTER_H_

#include <math.h>
#include <malloc.h>

#define MAX_SVID_NUM 3000

class CMatrixConverter
{
///멤버변수
public:

protected:
    // int m_cols;
    // int m_rows;
    // double **m_MatrixOutput;

private:
///멤버함수


public:
    CMatrixConverter(void);
    virtual ~CMatrixConverter(void);

public:

    static BOOL MatrixDuplicate(double *matrix_in, double *matrix_out, int nRowInMat, int nColInMat);
    static BOOL MatrixTranspose(double *matrix_in, double *matrix_out, int nRowInMat, int nColInMat);
    
    static double MatrixNorm(double *matrix_in, int nRowInMat);
    static double MatrixNormLoo(double *matrix_in, int nRowInMat);
    static BOOL   MatrixIdentity(double *dpMatrix, int nRowInMat);
    static BOOL   MatrixIdentity(double *dpMatrix, int nRowInMat,double dScale);/// Identity 메소드 구현(특정값으로 scale)
    
    static BOOL MatrixScale(double *matrix_in, double *matrix_out, int nRowInMat, int nColInMat, double nScale);
    static BOOL MatrixLog2(double *matrix_in, double *matrix_out, int nRowInMat, int nColInMat);
    static BOOL MatrixSquare(double *matrix_in, double *matrix_out, int nRowInMat, int nColInMat);
    
    static BOOL MatrixAdd(double *matrix_fin, double *matrix_lin, double *matrix_out, int nRowInMat, int nColInMat);
    static BOOL MatrixSubstract(double *matrix_fin, double *matrix_lin, double *matrix_out, int nRowInMat, int nColInMat);
    static BOOL MatrixMultiply(double *matrix_fin, double *matrix_lin, double *matrix_out, int nRowFInMAt, int nColFInMat, int nColLInMat);
    
    static BOOL MatrixInverse(double *matrix_in, double *matrix_out, int nRowInMat, int nColInMat);
    static BOOL RInverse(double *matrix_in, double *matrix_out, int nRowInMat, int nColInMat);
    static BOOL LInverse(double *matrix_in, double *matrix_out, int nRowInMat, int nColInMat);
    static BOOL CInverse(double *matrix_in, double *matrix_out, int nRowInMat);

    static BOOL LeastSquare(double *matrix_fin, double *matrix_lin, double *matrix_out, int nRowFInMat, int nColFInMat, int nColLInMat);
    static BOOL HMatrix(double *matrix_fin, double *matrix_lin, double *matrix_out, int nRowFInMat, int nColFInMat);

    static BOOL MatrixExp(double *matrix_in, double *matrix_out, int nRowInMat, int nRowOutMat);

    static double MatrixElement(double *matrix_in, int nRowInMat, int nColInMat , int nReqRowInMat, int nReqColInMat);
    
    static double MatrixTrace(double *matrix_in,int nRowInMat);
    static double MatrixTrace(double *matrix_in,int nRowInMat, int nColInMat, int nRowFirstNum, int nRowEndNum,int nColFirstNum, int nColEndNum);

    static double GetMatrixElement(double *matrix_in, int nRowInMat, int nColInMat , int nReqRowInMat, int nReqColInMat);

    static BOOL MatrixReciprocal(double *matrix_in, double *matrix_out, int nRowInMat, int nColInMat);

    static BOOL MatrixOnes(double *dpMatrix, int nRowInMat,int nColInMat);
    static BOOL MatrixClear(double *matrix_in,int nRowInMat, int nColInMat);
    static double MatrixSum(double *matrix_in,int nRowInMat, int nColInMat);

    static BOOL MakeDiagMatrix(double *matrix_in,double *matrix_out,int nRowInMat);   ///정방 대각 행렬 생성 
    static BOOL GetDiagElementMat(double *matrix_in,double *matrix_out,int nRowInMat);   ///대각 요소만 추출 
    static BOOL GetSubMatrix(double *matrix_in,double *matrix_out, int nRowInMat, int nColInMat, int nRowFirstNum, int nRowEndNum,int nColFirstNum, int nColEndNum);  ///Get sub matrix
    static BOOL SetSubMatrix(double *matrix_in,double *matrix_out, int nRowInMat, int nColInMat, int nRowFirstNum, int nRowEndNum,int nColFirstNum, int nColEndNum);  ///Set sub matrix   

};

#endif // _MATRIX_CONVERTER_H_