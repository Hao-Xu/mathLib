// r3Tensor.h
//   6th order tensor stored in 3 dimension array.
// History:
// 2016/09/13  Hao Xu  First release

#ifndef R3TENSOR_H
#define R3TENSOR_H

using namespace std;

template<class T>
class r3Tensor {
public:
    r3Tensor();
    r3Tensor(int m, int n, int k);
    r3Tensor(int m, int n, int k, const T &a);
    r3Tensor(int m, int n, int k, const T *a);
    r3Tensor(const r3Tensor &rhs);
    typedef T value_type;
    inline T** operator[](const int i);
    inline const T** operator[](const int i) const;
    inline int dim1() const;
    inline int dim2() const;
    inline int dim3() const;
    
    ~r3Tensor();

private:
    int mm, nn, kk;
    T ***v;
};


template<class T>
r3Tensor<T>::r3Tensor():mm(0), nn(0), kk(0), v(NULL) {}

template<class T>
r3Tensor<T>::r3Tensor(int m, int n, int k):mm(m), nn(n), kk(k), 
                      v(new T**[m]) {
    int  i, j;
    v[0] = new T*[m*n];
    v[0][0] = new T[m*n*k];
    for (j=1; j<n; j++) {
        v[0][j] = v[0][j-1] + k;  
    }
    for (i=1; i<m; i++) {
        v[i] = v[i-1] + n;  
        v[i][0] = v[i-1][0] + n*k;  
        for (j=1; j<n; j++) {
            v[i][j] = v[i][j-1] + k;  
        }
    }
}

template<class T>
r3Tensor<T>::r3Tensor(int m, int n, int k, const T &a):
             mm(m), nn(n), kk(k), v(new T**[m]) {
    int  i, j, p;
    v[0] = new T*[m*n];
    v[0][0] = new T[m*n*k];
    for (j=1; j<n; j++) {
        v[0][j] = v[0][j-1] + k;  
    }
    for (i=1; i<m; i++) {
        v[i] = v[i-1] + n;  
        v[i][0] = v[i-1][0] + n*k;  
        for (j=1; j<n; j++) {
            v[i][j] = v[i][j-1] + k;  
        }
    }
    for (i=0; i<m; i++) {
        for (j=0; j<n; j++) {
            for (p=0; p<k; p++) {
                v[i][j][p] = a;  
            }
        }
    }
}

template<class T>
r3Tensor<T>::r3Tensor(int m, int n, int k, const T *a):
             mm(m), nn(n), kk(k), v(new T**[m]) {
    int  i, j, p;
    v[0] = new T*[m*n];
    v[0][0] = new T[m*n*k];
    for (j=1; j<n; j++) {
        v[0][j] = v[0][j-1] + k;  
    }
    for (i=1; i<m; i++) {
        v[i] = v[i-1] + n;  
        v[i][0] = v[i-1][0] + n*k;  
        for (j=1; j<n; j++) {
            v[i][j] = v[i][j-1] + k;  
        }
    }
    for (i=0; i<m; i++) {
        for (j=0; j<n; j++) {
            for (p=0; p<k; p++) {
                v[i][j][p] =  *a++;  
            }
        }
    }
}


template<class T>
r3Tensor<T>::r3Tensor(const r3Tensor &rhs):
             mm(rhs.mm), nn(rhs.nn), kk(rhs.kk), v(new T**[mm]) {
    int  i, j, p;
    v[0] = new T*[mm*nn];
    v[0][0] = new T[mm*nn*kk];
    for (j=1; j<nn; j++) {
        v[0][j] = v[0][j-1] + kk;  
    }
    for (i=1; i<mm; i++) {
        v[i] = v[i-1] + nn;  
        v[i][0] = v[i-1][0] + nn*kk;  
        for (j=1; j<nn; j++) {
            v[i][j] = v[i][j-1] + kk;  
        }
    }
    for (i=0; i<mm; i++) {
        for (j=0; j<nn; j++) {
            for (p=0; p<kk; p++) {
                v[i][j][p] = rhs[i][j][p]; 
            }
        }
    }

}

template<class T>
inline int r3Tensor<T>::dim1() const {
    return mm;
}

template<class T>
inline int r3Tensor<T>::dim2() const {
    return nn;
}

template<class T>
inline int r3Tensor<T>::dim3() const {
    return kk;
}

template <class T>
r3Tensor<T>::~r3Tensor()
{
    if (v != NULL) {
        delete[] (v[0][0]);
        delete[] (v[0]);
        delete[] (v);
    }
}


template <class T>
inline T** r3Tensor<T>::operator[](const int i) {
#ifdef _CHECKBOUNDS_
if (i<0 || i>=mm) {
        throw("NRmatrix subscript out of bounds");
}
#endif
        return v[i];
}

template <class T>
inline const T** r3Tensor<T>::operator[](const int i) const {
#ifdef _CHECKBOUNDS_
if (i<0 || i>=mm) {
        throw("NRmatrix subscript out of bounds");
}
#endif
        return v[i];
}

#endif /* R3TENSOR_H */
