// r1Tensor.h
//   1 dimension array storage.
// History:
// 2016/09/14  Hao Xu  First release

#ifndef R1TENSOR_H
#define R1TENSOR_H

#include <stdexcept>
#include "errInfo.h"

#define _CHECKBOUNDS_ 1

using namespace std;

template <class T>
class r1Tensor {
private:
	int nn;	// size of array. upper index is nn-1
	T *v;
public:
	r1Tensor();
	explicit r1Tensor(int n);		// Zero-based array
	r1Tensor(int n, const T &a);	//initialize to constant value
	r1Tensor(int n, const T *a);	// Initialize to array
	r1Tensor(const r1Tensor &rhs);	// Copy constructor
	r1Tensor & operator=(const r1Tensor &rhs);	//assignment
	typedef T value_type; // make T available externally
	inline T & operator[](const int i);	//i'th element
	inline const T & operator[](const int i) const;
	inline int size() const;
	void resize(int newn); // resize (contents not preserved)
	void assign(int newn, const T &a); // resize and assign a constant value
	~r1Tensor();
};

// r1Tensor definitions

template <class T>
r1Tensor<T>::r1Tensor() : nn(0), v(NULL) {}

template <class T>
r1Tensor<T>::r1Tensor(int n) : nn(n), v(n>0 ? new T[n] : NULL) {}

template <class T>
r1Tensor<T>::r1Tensor(int n, const T& a) : nn(n), v(n>0 ? new T[n] : NULL)
{
	for(int i=0; i<n; i++) v[i] = a;
}

template <class T>
r1Tensor<T>::r1Tensor(int n, const T *a) : nn(n), v(n>0 ? new T[n] : NULL)
{
	for(int i=0; i<n; i++) v[i] = *a++;
}

template <class T>
r1Tensor<T>::r1Tensor(const r1Tensor<T> &rhs) : nn(rhs.nn), v(nn>0 ? new T[nn] : NULL)
{
	for(int i=0; i<nn; i++) v[i] = rhs[i];
}

template <class T>
r1Tensor<T> & r1Tensor<T>::operator=(const r1Tensor<T> &rhs)
// postcondition: normal assignment via copying has been performed;
//		if vector and rhs were different sizes, vector
//		has been resized to match the size of rhs
{
	if (this != &rhs)
	{
		if (nn != rhs.nn) {
			if (v != NULL) delete [] (v);
			nn=rhs.nn;
			v= nn>0 ? new T[nn] : NULL;
		}
		for (int i=0; i<nn; i++)
			v[i]=rhs[i];
	}
	return *this;
}

template <class T>
inline T & r1Tensor<T>::operator[](const int i)	//subscripting
{
#ifdef _CHECKBOUNDS_
if (i<0 || i>=nn) {
	throwout("r1Tensor subscript out of bounds");
}
#endif
	return v[i];
}

template <class T>
inline const T & r1Tensor<T>::operator[](const int i) const	//subscripting
{
#ifdef _CHECKBOUNDS_
if (i<0 || i>=nn) {
	throwout("r1Tensor subscript out of bounds");
}
#endif
	return v[i];
}

template <class T>
inline int r1Tensor<T>::size() const
{
	return nn;
}

template <class T>
void r1Tensor<T>::resize(int newn)
{
	if (newn != nn) {
		if (v != NULL) delete[] (v);
		nn = newn;
		v = nn > 0 ? new T[nn] : NULL;
	}
}

template <class T>
void r1Tensor<T>::assign(int newn, const T& a)
{
	if (newn != nn) {
		if (v != NULL) delete[] (v);
		nn = newn;
		v = nn > 0 ? new T[nn] : NULL;
	}
	for (int i=0;i<nn;i++) v[i] = a;
}

template <class T>
r1Tensor<T>::~r1Tensor()
{
	if (v != NULL) delete[] (v);
}

#endif /* R1TENSOR_H */

