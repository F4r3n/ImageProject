#ifndef VECTOR_H
#define VECTOR_H

#include <QVector>

template <typename T>
class Vector :public QVector<T> {

public:
    Vector():QVector<T>(){}
    Vector(unsigned int t):QVector<T>(t){}
};
template <typename T>
Vector<T> operator+(const Vector<T> &a,const Vector<T> &b);

template <typename T>
Vector<T> operator*(const Vector<T> &a,const Vector<T> &b);

template <typename T>
Vector<T> multiply(const Vector<T> &a,T b);

template <typename T>
Vector<T> operator+(const Vector<T> &a,const Vector<T> &b){
    Vector<T> v(a.size());
    for(int i=0;i<a.size();i++) {
        v[i]= a[i]+b[i];
    }
    return v;
}

template <typename T>
Vector<T> operator*(const Vector<T> &a,const Vector<T> &b){
   Vector<T> v(a.size());
    for(int i=0;i<a.size();i++) {
        v[i]= a[i]*b[i];
    }
    return v;
}

template <typename T>
Vector<T> multiply(const Vector<T> &a,T b) {
    Vector<T> v(a.size());
    for(int i=0;i<a.size();i++) {
        v[i]= a[i]*b;
    }
    return v;
}

#endif // VECTOR_H
