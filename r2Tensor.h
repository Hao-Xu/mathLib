// r2Tensor.h
//   4th order tensor stored in 2 dimension array.
// History:
// 2016/09/14  Hao Xu  First release

#ifndef R2TENSOR_H
#define R2TENSOR_H

#include <stdexcept>
#include "errInfo.h"

#define _CHECKBOUNDS_ 1

using namespace std;

template <class T>
class r2Tensor {
public:
	r2Tensor();
	r2Tensor(int m, int n);			// Zero-based array
	r2Tensor(int m, int n, const T &a);	//Initialize to constant
	r2Tensor(int m, int n, const T *a);	// Initialize to array
	r2Tensor(const r2Tensor &rhs);		// Copy constructor
	r2Tensor & operator=(const r2Tensor &rhs);	//assignment
	//typedef T value_type; // make T available externally
	inline T* operator[](const int i);	//subscripting: pointer to row i
	inline const T* operator[](const int i) const;
	inline int dim1() const;
	inline int dim2() const;
	void resize(int newm, int newn); // resize (contents not preserved)
	void assign(int newm, int newn, const T &a); // resize and assign a constant value
	~r2Tensor();
private:
	int mm, nn;
	T **v;
};

template <class T>
r2Tensor<T>::r2Tensor() : mm(0), nn(0), v(NULL) {}

template <class T>
r2Tensor<T>::r2Tensor(int m, int n) : mm(m), nn(n), v(m>0 ? new T*[m] : NULL)
{
	int i,nel=m*n;
	if (v) v[0] = nel>0 ? new T[nel] : NULL;
	for (i=1;i<m;i++) v[i] = v[i-1] + n;
}

template <class T>
r2Tensor<T>::r2Tensor(int m, int n, const T &a) : mm(m), nn(n), v(m>0 ? new T*[m] : NULL)
{
	int i,j,nel=m*n;
	if (v) v[0] = nel>0 ? new T[nel] : NULL;
	for (i=1; i< m; i++) v[i] = v[i-1] + n;
	for (i=0; i< m; i++) for (j=0; j<n; j++) v[i][j] = a;
}

template <class T>
r2Tensor<T>::r2Tensor(int m, int n, const T *a) : mm(m), nn(n), v(m>0 ? new T*[m] : NULL)
{
	int i,j,nel=m*n;
	if (v) v[0] = nel>0 ? new T[nel] : NULL;
	for (i=1; i< m; i++) v[i] = v[i-1] + n;
	for (i=0; i< m; i++) for (j=0; j<n; j++) v[i][j] = *a++;
}

template <class T>
r2Tensor<T>::r2Tensor(const r2Tensor &rhs) : mm(rhs.mm), nn(rhs.nn), v(mm>0 ? new T*[mm] : NULL)
{
	int i,j,nel=mm*nn;
	if (v) v[0] = nel>0 ? new T[nel] : NULL;
	for (i=1; i< mm; i++) v[i] = v[i-1] + nn;
	for (i=0; i< mm; i++) for (j=0; j<nn; j++) v[i][j] = rhs[i][j];
}

template <class T>
r2Tensor<T> & r2Tensor<T>::operator=(const r2Tensor<T> &rhs)
// postcondition: normal assignment via copying has been performed;
//		if matrix and rhs were different sizes, matrix
//		has been resized to match the size of rhs
{
	if (this != &rhs) {
		int i,j,nel;
		if (mm != rhs.mm || nn != rhs.nn) {
			if (v != NULL) {
				delete[] (v[0]);
				delete[] (v);
			}
			mm=rhs.mm;
			nn=rhs.nn;
			v = mm>0 ? new T*[mm] : NULL;
			nel = mm*nn;
			if (v) v[0] = nel>0 ? new T[nel] : NULL;
			for (i=1; i< mm; i++) v[i] = v[i-1] + nn;
		}
		for (i=0; i< mm; i++) for (j=0; j<nn; j++) v[i][j] = rhs[i][j];
	}
	return *this;
}

template <class T>
inline T* r2Tensor<T>::operator[](const int i)	//subscripting: pointer to row i
{
#ifdef _CHECKBOUNDS_
if (i<0 || i>=mm) {
	throwout("r2Tensor subscript out of bounds");
}
#endif
	return v[i];
}

template <class T>
inline const T* r2Tensor<T>::operator[](const int i) const
{
#ifdef _CHECKBOUNDS_
if (i<0 || i>=mm) {
	throwout("r2Tensor subscript out of bounds");
}
#endif
	return v[i];
}

template <class T>
inline int r2Tensor<T>::dim1() const
{
	return mm;
}

template <class T>
inline int r2Tensor<T>::dim2() const
{
	return nn;
}

template <class T>
void r2Tensor<T>::resize(int newm, int newn)
{
	int i,nel;
	if (newm != mm || newn != nn) {
		if (v != NULL) {
			delete[] (v[0]);
			delete[] (v);
		}
		mm = newm;
		nn = newn;
		v = mm>0 ? new T*[mm] : NULL;
		nel = mm*nn;
		if (v) v[0] = nel>0 ? new T[nel] : NULL;
		for (i=1; i< mm; i++) v[i] = v[i-1] + nn;
	}
}

template <class T>
void r2Tensor<T>::assign(int newm, int newn, const T& a)
{
	int i,j,nel;
	if (newm != mm || newn != nn) {
		if (v != NULL) {
			delete[] (v[0]);
			delete[] (v);
		}
		mm = newm;
		nn = newn;
		v = mm>0 ? new T*[mm] : NULL;
		nel = mm*nn;
		if (v) v[0] = nel>0 ? new T[nel] : NULL;
		for (i=1; i< mm; i++) v[i] = v[i-1] + nn;
	}
	for (i=0; i< mm; i++) for (j=0; j<nn; j++) v[i][j] = a;
}

template <class T>
r2Tensor<T>::~r2Tensor()
{
	if (v != NULL) {
		delete[] (v[0]);
		delete[] (v);
	}
}


#endif /* R2TENSOR_H */
