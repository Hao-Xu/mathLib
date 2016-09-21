// r4Tensor.h
//   4th order tensor stored in 4 dimension array.
// History:
// 2016/09/14  Hao Xu  First release

#ifndef R4TENSOR_H
#define R4TENSOR_H

#include <stdexcept>
#include "errInfo.h"

#define _CHECKBOUNDS_ 1

using namespace std;

template<class T>
class r4Tensor {
public:
    r4Tensor();
    r4Tensor(int m, int n, int k, int l);
    r4Tensor(int m, int n, int k, int l, const T &a);
    r4Tensor(int m, int n, int k, int l, const T *a);
    r4Tensor(const r4Tensor &rhs);
    typedef T value_type;
    inline T*** operator[](const int i);
    inline const T*** operator[](const int i) const;
    inline int dim1() const;
    inline int dim2() const;
    inline int dim3() const;
    inline int dim4() const;
    
    ~r4Tensor();

private:
    int mm, nn, kk, ll;
    T ****v;
};


template<class T>
r4Tensor<T>::r4Tensor():mm(0), nn(0), kk(0), ll(0), v(NULL) {}

template<class T>
r4Tensor<T>::r4Tensor(int m, int n, int k, int l):mm(m), nn(n), kk(k), ll(l),
                      v(new T***[m]) {
    int  i, j, p;
    v[0] = new T**[m*n];
    v[0][0] = new T*[m*n*k];
    v[0][0][0] = new T[m*n*k*l];
/*
    for (p=1; p<k; p++) {
        v[0][0][p] = v[0][0][p-1] + l;  
    }
    for (j=1; j<n; j++) {
        v[0][j] = v[0][j-1] + k;  
        v[0][j][0] = v[0][j-1][0] + k*l;  
        for (p=1; p<k; p++) {
            v[0][j][p] = v[0][j][p-1] + l;
        }
    }
    for (i=1; i<m; i++) {
        v[i] = v[i-1] + n;  
        v[i][0] = v[i-1][0] + n*k;  
        v[i][0][0] = v[i-1][0][0] + n*k*l;  
        for (p=1; p<k; p++) {v[i][0][p] = v[i][0][p-1] + l;}  
        for (j=1; j<n; j++) {
            v[i][j] = v[i][j-1] + k;
            v[i][j][0] = v[i][j-1][0] + k*l;
            for (p=1; p<k; p++) {
                v[i][j][p] = v[i][j][p-1] + l;
            }         
        }
    }
*/
    for (i=0;i<m;i++){
        if (i<m-1) {
            v[i+1] = v[i] + n;
            v[i+1][0] = v[i][0] + n*k;
            v[i+1][0][0] = v[i][0][0] + n*k*l;
        }
        for (j=0;j<n;j++){
            if (j<n-1) {
                v[i][j+1] = v[i][j] + k;
                v[i][j+1][0] = v[i][j][0] + k*l;
            }
            for (p=0;p<k;p++){
                if (p<k-1) { v[i][j][p+1] = v[i][j][p] + l;}
            }
        }
    }
}

template<class T>
r4Tensor<T>::r4Tensor(int m, int n, int k, int l, const T &a):
             mm(m), nn(n), kk(k), ll(l), v(new T***[m]) {
    int  i, j, p, q;
   
    v[0] = new T**[m*n];
    v[0][0] = new T*[m*n*k];
    v[0][0][0] = new T[m*n*k*l];

/*
    for (p=1; p<k; p++) {
        v[0][0][p] = v[0][0][p-1] + l;  
    }
    for (j=1; j<n; j++) {
        v[0][j] = v[0][j-1] + k;  
        v[0][j][0] = v[0][j-1][0] + k*l;  
        for (p=1; p<k; p++) {
            v[0][j][p] = v[0][j][p-1] + l;
        }
    }
    for (i=1; i<m; i++) {
        v[i] = v[i-1] + n;  
        v[i][0] = v[i-1][0] + n*k;  
        v[i][0][0] = v[i-1][0][0] + n*k*l;  
        for (p=1; p<k; p++) v[i][0][p] = v[i][0][p-1] + l;  
        for (j=1; j<n; j++) {
            v[i][j] = v[i][j-1] + k;
            v[i][j][0] = v[i][j-1][0] + k*l;
            for (p=1; p<k; p++) {
                v[i][j][p] = v[i][j][p-1] + l;
            }         
        }
    }
*/
    for (i=0;i<m;i++){
        if (i<m-1) {
            v[i+1] = v[i] + n;
            v[i+1][0] = v[i][0] + n*k;
            v[i+1][0][0] = v[i][0][0] + n*k*l;
        }
        for (j=0;j<n;j++){
            if (j<n-1) {
                v[i][j+1] = v[i][j] + k;
                v[i][j+1][0] = v[i][j][0] + k*l;
            }
            for (p=0;p<k;p++){
                if (p<k-1) { v[i][j][p+1] = v[i][j][p] + l;}
            }
        }
    }

    for (i=0; i<m; i++) {
        for (j=0; j<n; j++) {
            for (p=0; p<k; p++) {
                for (q=0; q<l; q++) {
                    v[i][j][p][q] = a;  
                }
            }
        }
    }
}

template<class T>
r4Tensor<T>::r4Tensor(int m, int n, int k, int l, const T *a):
             mm(m), nn(n), kk(k), ll(l), v(new T***[m]) {
    int  i, j, p, q;
    v[0] = new T**[m*n];
    v[0][0] = new T*[m*n*k];
    v[0][0][0] = new T[m*n*k*l];
    for (p=1; p<k; p++) {
        v[0][0][p] = v[0][0][p-1] + l;  
    }
    for (j=1; j<n; j++) {
        v[0][j] = v[0][j-1] + k;  
        v[0][j][0] = v[0][j-1][0] + k*l;  
        for (p=1; p<k; p++) {
            v[0][j][p] = v[0][j][p-1] + l;
        }
    }
    for (i=1; i<m; i++) {
        v[i] = v[i-1] + n;  
        v[i][0] = v[i-1][0] + n*k;  
        v[i][0][0] = v[i-1][0][0] + n*k*l;  
        for (p=1; p<k; p++) v[i][0][p] = v[i][0][p-1] + l;  
        for (j=1; j<n; j++) {
            v[i][j] = v[i][j-1] + k;
            v[i][j][0] = v[i][j-1][0] + k*l;
            for (p=1; p<k; p++) {
                v[i][j][p] = v[i][j][p-1] + l;
            }         
        }
    }
    for (i=0; i<m; i++) {
        for (j=0; j<n; j++) {
            for (p=0; p<k; p++) {
                for (q=0; q<l; q++) {
                    v[i][j][p][q] =  *a++;  
                }
            }
        }
    }
}


template<class T>
r4Tensor<T>::r4Tensor(const r4Tensor &rhs):
             mm(rhs.mm), nn(rhs.nn), kk(rhs.kk), ll(rhs.ll), v(new T***[mm]) {
    int  i, j, p, q;
    v[0] = new T**[mm*nn];
    v[0][0] = new T*[mm*nn*kk];
    v[0][0][0] = new T[mm*nn*kk*ll];
    for (p=1; p<kk; p++) {
        v[0][0][p] = v[0][0][p-1] + ll;  
    }
    for (j=1; j<nn; j++) {
        v[0][j] = v[0][j-1] + kk;  
        v[0][j][0] = v[0][j-1][0] + kk*ll;  
        for (p=1; p<kk; p++) {
            v[0][j][p] = v[0][j][p-1] + ll;
        }
    }
    for (i=1; i<mm; i++) {
        v[i] = v[i-1] + nn;  
        v[i][0] = v[i-1][0] + nn*kk;  
        v[i][0][0] = v[i-1][0][0] + nn*kk*ll;  
        for (p=1; p<kk; p++) v[i][0][p] = v[i][0][p-1] + ll;  
        for (j=1; j<nn; j++) {
            v[i][j] = v[i][j-1] + kk;
            v[i][j][0] = v[i][j-1][0] + kk*ll;
            for (p=1; p<kk; p++) {
                v[i][j][p] = v[i][j][p-1] + ll;
            }         
        }
    }
    for (i=0; i<mm; i++) {
        for (j=0; j<nn; j++) {
            for (p=0; p<kk; p++) {
                for (q=0; q<ll; q++) {
                    v[i][j][p][q] = rhs[i][j][p][q]; 
                }
            }
        }
    }

}

template<class T>
inline int r4Tensor<T>::dim1() const {
    return mm;
}

template<class T>
inline int r4Tensor<T>::dim2() const {
    return nn;
}

template<class T>
inline int r4Tensor<T>::dim3() const {
    return kk;
}

template<class T>
inline int r4Tensor<T>::dim4() const {
    return ll;
}


template <class T>
r4Tensor<T>::~r4Tensor()
{
    if (v != NULL) {
        delete[] (v[0][0][0]);
        delete[] (v[0][0]);
        delete[] (v[0]);
        delete[] (v);
    }
}


template <class T>
inline T*** r4Tensor<T>::operator[](const int i) {
#ifdef _CHECKBOUNDS_
if (i<0 || i>=mm) {
        throwout("r4Tensor subscript out of bounds");
}
#endif
        return v[i];
}

template <class T>
inline const T*** r4Tensor<T>::operator[](const int i) const {
#ifdef _CHECKBOUNDS_
if (i<0 || i>=mm) {
        throwout("r4Tensor subscript out of bounds");
}
#endif
        return v[i];
}

#endif /* R4TENSOR_H */
