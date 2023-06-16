#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "AVL.h"
#define CONTAINER AVL<T, int>

template<typename T>
class HashTable {
public:
    HashTable(int buckets = 2);
    ~HashTable();
    T& find(int key);
    void remove(int key);
    void insert(int key, T *data);

    int size() const;
    void get_all(T** output) const;

    template<typename Function>
    void apply(Function func);

    class KeyExists {};
    class KeyNotFound {};
private:
    int _size;
    int _buckets;
    CONTAINER *_table;

    void resize(int buckets);
    int hash_function(int key);

    template<typename S>
    friend std::ostream& operator<<(std::ostream& os, const HashTable<S>& h);
};

template<typename T>
HashTable<T>::HashTable(int buckets) {
    _size = 0;
    _buckets = buckets;
    _table = new CONTAINER[_buckets];
}

template<typename T>
HashTable<T>::~HashTable() {
    if (_buckets > 0) {
        delete[] _table;
    }
}

template<typename T>
void HashTable<T>::insert(int key, T *data) {
    int index = hash_function(key);
    try {
        _table[index].insert(key, data);
    } catch (const typename CONTAINER::KeyExists& e) {
        throw KeyExists();
    }
    ++_size;

    if (_size == _buckets) {
        resize(2 * _buckets);
    }
}

template<typename T>
void HashTable<T>::remove(int key) {
    int index = hash_function(key);
    try {
        _table[index].remove(key);
    } catch (const typename CONTAINER::KeyNotFound& e) {
        throw KeyNotFound();
    }
    --_size;

    if (4 * _size <= _buckets) {
        resize(_buckets / 2);
    }
}

template<typename T>
T& HashTable<T>::find(int key) {
    int index = hash_function(key);
    try {
        return _table[index].find(key);
    } catch (const typename CONTAINER::KeyNotFound& e) {
        throw KeyNotFound();
    }
}

template<typename T>
void HashTable<T>::resize(int buckets) {
    T **data;
    int *keys;
    CONTAINER *table = new CONTAINER[buckets];
    for (int i = 0; i < _buckets; ++i) {
        data = new T*[_table[i].size()];
        keys = new int[_table[i].size()];
        _table[i].inorder(data);
        _table[i].inorder(keys);
        for (int j = 0; j < _table[i].size(); ++j) {
            table[keys[j] % buckets].insert(keys[j], data[j]);
        }
        delete data;
        delete keys;
    }
    delete[] _table;
    _table = table;
    _buckets = buckets;
}

template<typename T>
int HashTable<T>::hash_function(int key) {
    return key % _buckets;
}

template<typename T>
int HashTable<T>::size() const {
    return _size;
}

template<typename T>
void HashTable<T>::get_all(T** output) const {
    int entry = 0;
    for (int i = 0; i < _buckets; ++i) {
        _table[i].inorder(output + entry);
        entry += _table[i].size();
    }
}

template<typename T>
template<typename Function>
void HashTable<T>::apply(Function func) {
    for (int i = 0; i < _buckets; ++i) {
        _table[i].apply(func);
    }
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const HashTable<T>& h) {
    for (int i = 0; i < h._buckets; ++i) {
        os << "[" << i << "]" << std::endl;
        h._table[i].print();
        os << std::endl;
    }
    return os;
}

#endif // HASH_TABLE_H