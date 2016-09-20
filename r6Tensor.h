// r6Tensor.h
//   6th order tensor stored in 3 dimension array.
// History:
// 2016/09/13  Hao Xu  First release

#ifndef R6TENSOR_H
#define R6TENSOR_H

#include <stdexcept>
#include "errInfo.h"

#define _CHECKBOUNDS_ 1

using namespace std;

template<class T>
class r6Tensor {
public:
    r6Tensor();
    r6Tensor(int m, int n, int k, int l, int u, int w);
    r6Tensor(int m, int n, int k, int l, int u, int w, const T &a);
    //r6Tensor(int m, int n, int k, int l, int u, int w, const T *a);
    //r6Tensor(const r6Tensor &rhs);
    typedef T value_type;
    inline T***** operator[](const int i);
    inline const T***** operator[](const int i) const;
    inline int dim1() const;
    inline int dim2() const;
    inline int dim3() const;
    inline int dim4() const;
    inline int dim5() const;
    inline int dim6() const;
    
    ~r6Tensor();

private:
    int mm, nn, kk, ll, uu, ww;
    T ******v;
};


template<class T>
r6Tensor<T>::r6Tensor():mm(0), nn(0), kk(0), ll(0), uu(0), ww(0), v(NULL) {}

template<class T>
r6Tensor<T>::r6Tensor(int m, int n, int k, int l, int u, int w): mm(m), nn(n), kk(k), ll(l), uu(u), ww(w), 
                      v(new T*****[m]) {
    int  i, j, p, q, r;
    v[0] = new T****[m*n];
    v[0][0] = new T***[m*n*k];
    v[0][0][0] = new T**[m*n*k*l];
    v[0][0][0][0] = new T*[m*n*k*l*u];
    v[0][0][0][0][0] = new T[m*n*k*l*u*w];
    for (r=1; r<u; r++) {
        v[0][0][0][0][r] = v[0][0][0][0][r-1] + w;  
    }
    for (q=1; q<l; q++) {
        v[0][0][0][q] = v[0][0][0][q-1] + u;  
        v[0][0][0][q][0] = v[0][0][0][q-1][0] + u*w;
        for (r=1; r<u; r++) {
            v[0][0][0][q][r] = v[0][0][0][q][r-1] + w;  
        }  
    }
    for (p=1; p<k; p++) {
        v[0][0][p] = v[0][0][p-1] + l;
        v[0][0][p][0] = v[0][0][p-1][0] + l*u;
        v[0][0][p][0][0] = v[0][0][p-1][0][0] + l*u*w;
        for (r=1; r<u; r++) {
            v[0][0][p][0][r] = v[0][0][p][0][r-1] + w;  
        }  
        for (q=1; q<l; q++) {
            v[0][0][p][q] = v[0][0][p][q-1] + u;  
            v[0][0][p][q][0] = v[0][0][p][q-1][0] + u*w;
            for (r=1; r<u; r++) {
                v[0][0][p][q][r] = v[0][0][p][q][r-1] + w;  
            }  
        }
    }
    for (j=1; j<n; j++) {
        v[0][j] = v[0][j-1] + k;
        v[0][j][0] = v[0][j-1][0] + k*l;
        v[0][j][0][0] = v[0][j-1][0][0] + k*l*u;
        v[0][j][0][0][0] = v[0][j-1][0][0][0] + k*l*u*w;
        for (r=1; r<u; r++) {
            v[0][j][0][0][r] = v[0][j][0][0][r-1] + w;  
        }  
        for (q=1; q<l; q++) {
            v[0][j][0][q] = v[0][j][0][q-1] + u;  
            v[0][j][0][q][0] = v[0][j][0][q-1][0] + u*w;
            for (r=1; r<u; r++) {
                v[0][j][0][q][r] = v[0][j][0][q][r-1] + w;  
            }  
        }
        for (p=1; p<k; p++) {
            v[0][j][p] = v[0][j][p-1] + l;
            v[0][j][p][0] = v[0][j][p-1][0] + l*u;
            v[0][j][p][0][0] = v[0][j][p-1][0][0] + l*u*w;
            for (r=1; r<u; r++) {
                v[0][j][p][0][r] = v[0][j][p][0][r-1] + w;  
            }  
            for (q=1; q<l; q++) {
                v[0][j][p][q] = v[0][j][p][q-1] + u;  
                v[0][j][p][q][0] = v[0][j][p][q-1][0] + u*w;
                for (r=1; r<u; r++) {
                    v[0][j][p][q][r] = v[0][j][p][q][r-1] + w;  
                }  
            }
        }
    }
    for (i=1; i<m; i++) {
        v[i] = v[i-1] + n;
        v[i][0] = v[i-1][0] + n*k;
        v[i][0][0] = v[i-1][0][0] + n*k*l;
        v[i][0][0][0] = v[i-1][0][0][0] + n*k*l*u;
        v[i][0][0][0][0] = v[i-1][0][0][0][0] + n*k*l*u*w;
        for (r=1; r<u; r++) {
            v[i][0][0][0][r] = v[i][0][0][0][r-1] + w;  
        }  
        for (q=1; q<l; q++) {
            v[i][0][0][q] = v[i][0][0][q-1] + u;  
            v[i][0][0][q][0] = v[i][0][0][q-1][0] + u*w;
            for (r=1; r<u; r++) {
                v[i][0][0][q][r] = v[i][0][0][q][r-1] + w;  
            }  
        }
        for (p=1; p<k; p++) {
            v[i][0][p] = v[i][0][p-1] + l;
            v[i][0][p][0] = v[i][0][p-1][0] + l*u;
            v[i][0][p][0][0] = v[i][0][p-1][0][0] + l*u*w;
            for (r=1; r<u; r++) {
                v[i][0][p][0][r] = v[i][0][p][0][r-1] + w;  
            }  
            for (q=1; q<l; q++) {
                v[i][0][p][q] = v[i][0][p][q-1] + u;  
                v[i][0][p][q][0] = v[i][0][p][q-1][0] + u*w;
                for (r=1; r<u; r++) {
                    v[i][0][p][q][r] = v[i][0][p][q][r-1] + w;  
                }  
            }
        }
        for (j=1; j<n; j++) {
            v[i][j] = v[i][j-1] + k;
            v[i][j][0] = v[i][j-1][0] + k*l;
            v[i][j][0][0] = v[i][j-1][0][0] + k*l*u;
            v[i][j][0][0][0] = v[i][j-1][0][0][0] + k*l*u*w;
            for (r=1; r<u; r++) {
                v[i][j][0][0][r] = v[i][j][0][0][r-1] + w;  
            }  
            for (q=1; q<l; q++) {
                v[i][j][0][q] = v[i][j][0][q-1] + u;  
                v[i][j][0][q][0] = v[i][j][0][q-1][0] + u*w;
                for (r=1; r<u; r++) {
                    v[i][j][0][q][r] = v[i][j][0][q][r-1] + w;  
                }  
            }
            for (p=1; p<k; p++) {
                v[i][j][p] = v[i][j][p-1] + l;
                v[i][j][p][0] = v[i][j][p-1][0] + l*u;
                v[i][j][p][0][0] = v[i][j][p-1][0][0] + l*u*w;
                for (r=1; r<u; r++) {
                    v[i][j][p][0][r] = v[i][j][p][0][r-1] + w;  
                }  
                for (q=1; q<l; q++) {
                    v[i][j][p][q] = v[i][j][p][q-1] + u;  
                    v[i][j][p][q][0] = v[i][j][p][q-1][0] + u*w;
                    for (r=1; r<u; r++) {
                        v[i][j][p][q][r] = v[i][j][p][q][r-1] + w;  
                    }  
                }
            }
        }
    }
}

template<class T>
r6Tensor<T>::r6Tensor(int m, int n, int k, int l, int u, int w, const T &a):
             mm(m), nn(n), kk(k), ll(l), uu(u), ww(w), v(new T*****[m]) {
    int  i, j, p, q, r, s;
    v[0] = new T****[m*n];
    v[0][0] = new T***[m*n*k];
    v[0][0][0] = new T**[m*n*k*l];
    v[0][0][0][0] = new T*[m*n*k*l*u];
    v[0][0][0][0][0] = new T[m*n*k*l*u*w];

/*
    for (r=1; r<u; r++) {
        v[0][0][0][0][r] = v[0][0][0][0][r-1] + w;  
    }
    for (q=1; q<l; q++) {
        v[0][0][0][q] = v[0][0][0][q-1] + u;  
        v[0][0][0][q][0] = v[0][0][0][q-1][0] + u*w;
        for (r=1; r<u; r++) {
            v[0][0][0][q][r] = v[0][0][0][q][r-1] + w;  
        }  
    }
    for (p=1; p<k; p++) {
        v[0][0][p] = v[0][0][p-1] + l;
        v[0][0][p][0] = v[0][0][p-1][0] + l*u;
        v[0][0][p][0][0] = v[0][0][p-1][0][0] + l*u*w;
        for (r=1; r<u; r++) {
            v[0][0][p][0][r] = v[0][0][p][0][r-1] + w;  
        }  
        for (q=1; q<l; q++) {
            v[0][0][p][q] = v[0][0][p][q-1] + u;  
            v[0][0][p][q][0] = v[0][0][p][q-1][0] + u*w;
            for (r=1; r<u; r++) {
                v[0][0][p][q][r] = v[0][0][p][q][r-1] + w;  
            }  
        }
    }
    for (j=1; j<n; j++) {
        v[0][j] = v[0][j-1] + k;
        v[0][j][0] = v[0][j-1][0] + k*l;
        v[0][j][0][0] = v[0][j-1][0][0] + k*l*u;
        v[0][j][0][0][0] = v[0][j-1][0][0][0] + k*l*u*w;
        for (r=1; r<u; r++) {
            v[0][j][0][0][r] = v[0][j][0][0][r-1] + w;  
        }  
        for (q=1; q<l; q++) {
            v[0][j][0][q] = v[0][j][0][q-1] + u;  
            v[0][j][0][q][0] = v[0][j][0][q-1][0] + u*w;
            for (r=1; r<u; r++) {
                v[0][j][0][q][r] = v[0][j][0][q][r-1] + w;  
            }  
        }
        for (p=1; p<k; p++) {
            v[0][j][p] = v[0][j][p-1] + l;
            v[0][j][p][0] = v[0][j][p-1][0] + l*u;
            v[0][j][p][0][0] = v[0][j][p-1][0][0] + l*u*w;
            for (r=1; r<u; r++) {
                v[0][j][p][0][r] = v[0][j][p][0][r-1] + w;  
            }  
            for (q=1; q<l; q++) {
                v[0][j][p][q] = v[0][j][p][q-1] + u;  
                v[0][j][p][q][0] = v[0][j][p][q-1][0] + u*w;
                for (r=1; r<u; r++) {
                    v[0][j][p][q][r] = v[0][j][p][q][r-1] + w;  
                }  
            }
        }
    }
    for (i=1; i<m; i++) {
        v[i] = v[i-1] + n;
        v[i][0] = v[i-1][0] + n*k;
        v[i][0][0] = v[i-1][0][0] + n*k*l;
        v[i][0][0][0] = v[i-1][0][0][0] + n*k*l*u;
        v[i][0][0][0][0] = v[i-1][0][0][0][0] + n*k*l*u*w;
        for (r=1; r<u; r++) {
            v[i][0][0][0][r] = v[i][0][0][0][r-1] + w;  
        }  
        for (q=1; q<l; q++) {
            v[i][0][0][q] = v[i][0][0][q-1] + u;  
            v[i][0][0][q][0] = v[i][0][0][q-1][0] + u*w;
            for (r=1; r<u; r++) {
                v[i][0][0][q][r] = v[i][0][0][q][r-1] + w;  
            }  
        }
        for (p=1; p<k; p++) {
            v[i][0][p] = v[i][0][p-1] + l;
            v[i][0][p][0] = v[i][0][p-1][0] + l*u;
            v[i][0][p][0][0] = v[i][0][p-1][0][0] + l*u*w;
            for (r=1; r<u; r++) {
                v[i][0][p][0][r] = v[i][0][p][0][r-1] + w;  
            }  
            for (q=1; q<l; q++) {
                v[i][0][p][q] = v[i][0][p][q-1] + u;  
                v[i][0][p][q][0] = v[i][0][p][q-1][0] + u*w;
                for (r=1; r<u; r++) {
                    v[i][0][p][q][r] = v[i][0][p][q][r-1] + w;  
                }  
            }
        }
        for (j=1; j<n; j++) {
            v[i][j] = v[i][j-1] + k;
            v[i][j][0] = v[i][j-1][0] + k*l;
            v[i][j][0][0] = v[i][j-1][0][0] + k*l*u;
            v[i][j][0][0][0] = v[i][j-1][0][0][0] + k*l*u*w;
            for (r=1; r<u; r++) {
                v[i][j][0][0][r] = v[i][j][0][0][r-1] + w;  
            }  
            for (q=1; q<l; q++) {
                v[i][j][0][q] = v[i][j][0][q-1] + u;  
                v[i][j][0][q][0] = v[i][j][0][q-1][0] + u*w;
                for (r=1; r<u; r++) {
                    v[i][j][0][q][r] = v[i][j][0][q][r-1] + w;  
                }  
            }
            for (p=1; p<k; p++) {
                v[i][j][p] = v[i][j][p-1] + l;
                v[i][j][p][0] = v[i][j][p-1][0] + l*u;
                v[i][j][p][0][0] = v[i][j][p-1][0][0] + l*u*w;
                for (r=1; r<u; r++) {
                    v[i][j][p][0][r] = v[i][j][p][0][r-1] + w;  
                }  
                for (q=1; q<l; q++) {
                    v[i][j][p][q] = v[i][j][p][q-1] + u;  
                    v[i][j][p][q][0] = v[i][j][p][q-1][0] + u*w;
                    for (r=1; r<u; r++) {
                        v[i][j][p][q][r] = v[i][j][p][q][r-1] + w;  
                    }  
                }
            }
        }
    }
*/
    for (i=0;i<m;i++){
        if (i<m-1) {
            v[i+1] = v[i] + n;
            v[i+1][0] = v[i][0] + n*k;
            v[i+1][0][0] = v[i][0][0] + n*k*l;
            v[i+1][0][0][0] = v[i][0][0][0] + n*k*l*u;
            v[i+1][0][0][0][0] = v[i][0][0][0][0] + n*k*l*u*w;
        }
        for (j=0;j<n;j++){
            if (j<n-1) {
                v[i][j+1] = v[i][j] + k;
                v[i][j+1][0] = v[i][j][0] + k*l;
                v[i][j+1][0][0] = v[i][j][0][0] + k*l*u;
                v[i][j+1][0][0][0] = v[i][j][0][0][0] + k*l*u*w;
            }
            for (p=0;p<k;p++){
                if (p<k-1) { 
                    v[i][j][p+1] = v[i][j][p] + l;
                    v[i][j][p+1][0] = v[i][j][p][0] + l*u;
                    v[i][j][p+1][0][0] = v[i][j][p][0][0] + l*u*w;
                }
                for (q=0;q<l;q++){
                    if (q<l-1) {
                        v[i][j][p][q+1] = v[i][j][p][q] + u;
                        v[i][j][p][q+1][0] = v[i][j][p][q][0] + u*w;
                    }
                    for (r=0;r<u;r++){
                        if (r<u-1) {v[i][j][p][q][r+1]=v[i][j][p][q][r]+w;}  
                    }
                }
            }
        }
    }


    for (i=0; i<m; i++) {
        for (j=0; j<n; j++) {
            for (p=0; p<k; p++) {
            for (q=0; q<l; q++) {
            for (r=0; r<u; r++) {
            for (s=0; s<w; s++) {
                v[i][j][p][q][r][s] = a;  
            }}}}
        }
    }
}
/*
template<class T>
r6Tensor<T>::r6Tensor(int m, int n, int k, int l, int u, int w, const T *a):
             mm(m), nn(n), kk(k), ll(l), uu(u), ww(w), v(new T*****[m]) {
    int  i, j, p;
    v[0] = new T****[m*n];
    v[0][0] = new T***[m*n*k];
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
r6Tensor<T>::r6Tensor(const r6Tensor &rhs):
             mm(rhs.mm), nn(rhs.nn), kk(rhs.kk), ll(rhs.ll), uu(rhs.uu), ww(rhs.ww), v(new T*****[mm]) {
    int  i, j, p;
    v[0] = new T****[mm*nn];
    v[0][0] = new T***[mm*nn*kk];
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
                for (q=0; q<ll; q++) {
                    for (r=0; r<uu; r++) {
                        for (s=0; s<ww; s++) {
                            v[i][j][p][q][r][s] = rhs[i][j][p][q][r][s];
                        }
                    }
                }
            }
        }
    }

}
*/
template<class T>
inline int r6Tensor<T>::dim1() const {
    return mm;
}

template<class T>
inline int r6Tensor<T>::dim2() const {
    return nn;
}

template<class T>
inline int r6Tensor<T>::dim3() const {
    return kk;
}

template<class T>
inline int r6Tensor<T>::dim4() const {
    return ll;
}

template<class T>
inline int r6Tensor<T>::dim5() const {
    return uu;
}

template<class T>
inline int r6Tensor<T>::dim6() const {
    return ww;
}

template <class T>
r6Tensor<T>::~r6Tensor()
{
    if (v != NULL) {
        delete[] (v[0][0][0][0][0]);
        delete[] (v[0][0][0][0]);
        delete[] (v[0][0][0]);
        delete[] (v[0][0]);
        delete[] (v[0]);
        delete[] (v);
    }
}


template <class T>
inline T***** r6Tensor<T>::operator[](const int i) {
#ifdef _CHECKBOUNDS_
if (i<0 || i>=mm) {
        throwout("r6Tensor subscript out of bounds");
}
#endif
        return v[i];
}

template <class T>
inline const T***** r6Tensor<T>::operator[](const int i) const {
#ifdef _CHECKBOUNDS_
if (i<0 || i>=mm) {
        throwout("r6Tensor subscript out of bounds");
}
#endif
        return v[i];
}

#endif /* R6TENSOR_H */
