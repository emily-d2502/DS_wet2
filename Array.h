
#pragma once
#include <iostream>

template<typename T>
class Array {
private:
    T* _base;
    T* _top;
    int _size;

public:
    Array(int n);
    ~Array();
    Array(const Array& arr);
    Array& operator=(const Array& arr);

    int size() const;
    void push_back(const T& t);
    T& operator[](int i);
    const T& operator[](int i) const;
    void copy(T* const output) const;

    class OutOfRange {};
};

template<typename T>
Array<T>::Array(int n):
    _base(new T[n]),
    _top(_base),
    _size(n) {}

template<typename T>
Array<T>::~Array() {
    delete[] _base;
}

template<typename T>
Array<T>::Array(const Array<T>& arr):
    _base(new T[arr._size]),
    _top(_base),
    _size(arr._size) {
    for (int i = 0; i < arr.size(); ++i) {
        *_top++ = arr._base[i];
    }
}

template<typename T>
Array<T>& Array<T>::operator=(const Array<T>& arr) {
    if (this == &arr) {
        return *this;
    }
    T *tmp = new T[arr._size];
    try {
        for (int i = 0; i < arr.size(); ++i) {
            tmp[i] = arr._base[i];
        }
    } catch (...) {
        delete[] tmp;
        return *this;
    }
    _base = tmp;
    _size = arr._size;
    _top = _base + arr.size();
    return *this;
}


template<typename T>
int Array<T>::size() const {
    return _top - _base;
}

template<typename T>
void Array<T>::push_back(const T &t) {
    if (_top - _base > _size) {
        throw OutOfRange();
    }
    *_top++ = t;
}

template<typename T>
T &Array<T>::operator[](int i) {
    if (i < 0 || i >= _size) {
        throw OutOfRange();
    }
    return _base[i];
}

template<typename T>
const T &Array<T>::operator[](int i) const {
    if (i < 0 || i >= _size) {
        throw OutOfRange();
    }
    return _base[i];
}

template<class T>
std::ostream& operator<<(std::ostream& os, const Array<T>& r) {
    for (int i = 0; i < r.size(); ++i) {
        os << r[i] << " ";
    }
    return os;
}

template<class T>
void Array<T>::copy(T* const output) const {
    for (int i = 0; i < size(); ++i) {
        output[i] = _base[i];
    }
}
