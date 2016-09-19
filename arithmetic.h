// arithmetic.h
//   Arithmetic functions.
// History:
// 2016/09/14  Hao Xu  First release

#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "../mathLib/r1Tensor.h"
#include "../mathLib/r2Tensor.h"
using namespace std;

template<class T>
inline T SQR(const T a) {return a*a;}

template<class T>
inline const T &MAX(const T &a, const T &b)
        {return b > a ? (b) : (a);}

template<class T>
inline const T &MIN(const T &a, const T &b)
        {return b < a ? (b) : (a);}

template<class T>
inline T SIGN(const T &a, const T &b)
	{return b >= 0 ? (a >= 0 ? a : -a) : (a >= 0 ? -a : a);}

template<class T>
inline void SWAP(T &a, T &b) {T dum=a; a=b; b=dum;}

template<class T>
void vectorToTensor(const r1Tensor<T> &vector, r2Tensor<T> &tensor, const double & Fact) {
    int ntens = vector.size();
    int m = 3;
    tensor = 0;

    tensor[0][0] = vector[0];
    tensor[1][1] = vector[1];
    tensor[2][2] = vector[2];
    tensor[0][1] = vector[3]*Fact;
    tensor[1][0] = tensor[0][1];
 
    tensor[1][2] = vector[4]*Fact;
    tensor[2][1] = tensor[1][2]; 
    tensor[0][2] = vector[5]*Fact;
    tensor[2][0] = tensor[0][2]; 

    tensor[1][2] = 0.; 
    tensor[2][1] = 0.; 
    tensor[0][2] = 0.; 
    tensor[2][0] = 0.; 

}

template<class T>
void Aik_Bkj(const r1Tensor<T> &A, const r1Tensor<T> &B, r1Tensor<T> &C) {

    C[0] = A[0] * B[0] + A[3] * B[3] + A[5] * B[5];
    C[1] = A[3] * B[3] + A[1] * B[1] + A[4] * B[4];
    C[2] = A[5] * B[5] + A[4] * B[4] + A[2] * B[2];
    C[3] = 0.5 * (A[0] * B[3] + A[3] * B[1] + A[5] * B[4]+
                  A[3] * B[0] + A[1] * B[3] + A[4] * B[5]);
    C[4] = 0.5 * (A[3] * B[5] + A[1] * B[4] + A[4] * B[2]+
                  A[5] * B[3] + A[4] * B[1] + A[2] * B[4]);
    C[5] = 0.5 * (A[0] * B[5] + A[3] * B[4] + A[5] * B[2]+
                  A[5] * B[0] + A[4] * B[3] + A[2] * B[5]);

}


#endif /* ARITHMETIC_H */
