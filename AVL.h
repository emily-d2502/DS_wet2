
#ifndef AVL_H
#define AVL_H

#include <iostream>
#include "Node.h"
#include "Array.h"
#define NODEAVL Node<T,K>

template<typename T, typename K = T>
class AVL {
public:
    AVL(bool memory = false);
    AVL(const AVL& other) = delete;
    AVL& operator=(AVL& other);
    ~AVL();

    bool &memory();
    int size() const;
    T* max() const;
    T* find(const K& key);
    void insert(const K& key, T *data);
    void remove(const K& key);
    void inorder(K* const output) const;
    void inorder(T** const output) const;
    void print() const;

    template<typename Function>
    void apply(Function func);

    class KeyExists {};
    class KeyNotFound {};

private:
    int _size;
    NODEAVL *_root;
    bool _memory;

    void rotations(NODEAVL *v);
    NODEAVL *closest_up(NODEAVL *v);
    NODEAVL *closest_down(NODEAVL *v);
    NODEAVL *insert(NODEAVL *root, NODEAVL *v);
    NODEAVL *remove(NODEAVL *root, const K& key);
    void inorder(NODEAVL *p, Array<K>& arr) const;
    void inorder(NODEAVL *p, Array<T*>& arr) const;
    void delete_tree(NODEAVL *root, bool memory);
    void print(const std::string& prefix, NODEAVL *root, bool left) const;

    template<typename Function>
    void apply(NODEAVL *root, Function func);
};

template<typename T, typename K>
AVL<T,K>::AVL(bool memory):
    _size(0),
    _root(nullptr),
    _memory(memory) {}

template<typename T, typename K>
AVL<T,K>& AVL<T,K>::operator=(AVL<T,K>& other) {
    if (this == &other) {
        return *this;
    }

    delete_tree(_root);
    _size = other._size;
    _root = other._root;
    _memory = other._memory;

    other._size = 0;
    other._root = nullptr;
    return *this;
}

template<typename T, typename K>
AVL<T,K>::~AVL() {
    delete_tree(_root, _memory);
}

template<typename T, typename K>
int AVL<T,K>::size() const {
    return _size;
}

template<typename T, typename K>
bool &AVL<T,K>::memory() {
    return _memory;
}

template<typename T, typename K>
T* AVL<T,K>::find(const K& key) {
    if (_root == nullptr) {
        throw KeyNotFound();
    }

    NODEAVL *p = _root;
    while(p != nullptr) {
        if (p->_key == key) {
            return p->_data;
        } else if (p->_key < key) {
            p = p->_right;
        } else {
            p = p->_left;
        }
    }
    throw KeyNotFound();
}

template<typename T, typename K>
void AVL<T,K>::insert(const K& key, T *data) {
    NODEAVL *v = new NODEAVL(key, data, _memory);
    _root = insert(_root, v);
    ++_size;
}

template<typename T, typename K>
void AVL<T,K>::remove(const K& key) {
    _root = remove(_root, key);
    --_size;
}

template<typename T, typename K>
NODEAVL *AVL<T,K>::insert(NODEAVL *root, NODEAVL *v) {
    if (!root) {
        return v;
    }
    if (v->_key > root->_key) {
        root->_right = insert(root->_right, v);
    } else if (v->_key < root->_key) {
        root->_left = insert(root->_left, v);
    } else {
        throw KeyExists();
    }
    root->_height = NODEAVL::height(root); // O(1)
    rotations(root); // O(1)
    return root;
}

template<typename T, typename K>
NODEAVL *AVL<T,K>::remove(NODEAVL *root, const K& key) {
    if (!root) {
        throw KeyNotFound();
    }
    if (key > root->_key) {
        root->_right = remove(root->_right, key);
    } else if (key < root->_key) {
        root->_left = remove(root->_left, key);
    } else {
        if (root->leaf()) {
            delete root;
            return nullptr;
        }
        if (root->children() == 1) {
            NODEAVL *tmp = root->only_child();
            delete root;
            return tmp;
        }
        NODEAVL *new_root = closest_up(root);
        NODEAVL::swap(new_root, root);
        root->_right = remove(root->_right, key);
    }
    root->_height = NODEAVL::height(root); // O(1)
    rotations(root); // O(1)
    return root;
}

template<typename T, typename K>
void AVL<T, K>::inorder(T** output) const {
    Array<T*> tmp(_size);
    inorder(_root, tmp);
    tmp.copy(output);
}


template<typename T, typename K>
void AVL<T, K>::inorder(Node<T,K> *r, Array<K>& arr) const {
    if (r == nullptr) {
        return;
    }
    inorder(r->_left, arr);
    arr.push_back(r->_key);
    inorder(r->_right, arr);
}

template<typename T, typename K>
void AVL<T, K>::inorder(K* output) const {
    Array<K> tmp(_size);
    inorder(_root, tmp);
    tmp.copy(output);
}


template<typename T, typename K>
void AVL<T, K>::inorder(Node<T,K> *r, Array<T*>& arr) const {
    if (r == nullptr) {
        return;
    }
    inorder(r->_left, arr);
    arr.push_back(r->_data);
    inorder(r->_right, arr);
}



template<typename T, typename K>
void AVL<T,K>::rotations(NODEAVL *v) {
    if (NODEAVL::BF(v) == 2) {
        if (NODEAVL::BF(v->_left) == -1) {
            NODEAVL::lr_rotation(v);
        } else {
            NODEAVL::ll_rotation(v);
        }
    } else if (NODEAVL::BF(v) == -2) {
        if (NODEAVL::BF(v->_right) == 1) {
            NODEAVL::rl_rotation(v);
        } else {
            NODEAVL::rr_rotation(v);
        }
    }
}

template<typename T, typename K>
NODEAVL *AVL<T,K>::closest_up(NODEAVL *v) {
    assert(v->_right);
    NODEAVL *res = v->_right;
    while (res->_left) {
        res = res->_left;
    }
    return res;
}

template<typename T, typename K>
NODEAVL *AVL<T,K>::closest_down(NODEAVL *v) {
    assert(v->_left);
    NODEAVL *res = v->_left;
    while (res->_right) {
        res = res->_right;
    }
    return res;
}

template<typename T, typename K>
T* AVL<T,K>::max() const {
    NODEAVL* tmp = this->_root;
    if(this->_root == nullptr)
        return nullptr;
    while(tmp->_right) {
        tmp = tmp->_right;
    }
    return tmp->_data;
}

template<typename T, typename K>
void AVL<T,K>::delete_tree(NODEAVL *root, bool memory) {
    if (!root) {
        return;
    }
    delete_tree(root->_left, memory);
    delete_tree(root->_right, memory);
    root->_memory = memory;
    delete root;
}

template<typename T, typename K>
template<typename Function>
void AVL<T,K>::apply(Function func) {
    apply(_root, func);
}

template<typename T, typename K>
template<typename Function>
void AVL<T,K>::apply(NODEAVL *root, Function func) {
    if (!root) {
        return;
    }
    func(*(root->_data));
    apply(root->_left, func);
    apply(root->_right, func);
}

template<typename T, typename K>
void AVL<T,K>::print(const std::string& prefix, NODEAVL *root, bool left) const {
    if (!root) {
        return;
    }
    std::cout << prefix << (left ? "├──" : "└──" );
    std::cout << "(" << root->_key << ", " << *root->_data << ")" << std::endl;

    print(prefix + (left ? "│   " : "    "), root->_left, true);
    print(prefix + (left ? "│   " : "    "), root->_right, false);
}

template<typename T, typename K>
void AVL<T,K>::print() const {
    print("", _root, false);
}

#endif // AVL_H
