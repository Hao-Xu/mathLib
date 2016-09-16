// arithmetic.h
//   Arithmetic functions.
// History:
// 2016/09/14  Hao Xu  First release

#ifndef ARITHMETIC_H
#define ARITHMETIC_H

//#include "../mathLib/r2Tensor.h"
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




#endif /* ARITHMETIC_H */
