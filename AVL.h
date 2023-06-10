
#pragma once
#include <iostream>
#include "Node.h"
#include "Array.h"
#define NODE Node<T,K>

template<typename T, typename K = T>
class AVL {
public:
    AVL(bool memory = false);
    AVL(const AVL& other) = delete;
    AVL& operator=(const AVL& other) = delete;
    ~AVL();

    int size() const;
    T* max() const;
    T& find(const K& key);
    void insert(const K& key, T *data);
    ///
    void add(const K& key, int extra);
    ///

    void remove(const K& key);
    void inorder(T** const output) const;
    void print() const;

    template<typename Function>
    void apply(Function func);

    class KeyExists {};
    class KeyNotFound {};

private:
    int _size;
    NODE *_root;
    bool _memory;

    void rotations(NODE *v);
    NODE *closest_up(NODE *v);
    NODE *closest_down(NODE *v);
    NODE *insert(NODE *root, NODE *v);
    NODE *remove(NODE *root, const K& key);
    void inorder(NODE *p, Array<T*>& arr) const;
    void delete_tree(NODE *root);
    void print(const std::string& prefix, NODE *root, bool left) const;

    template<typename Function>
    void apply(NODE *root, Function func);
};

template<typename T, typename K>
AVL<T,K>::AVL(bool memory):
    _size(0),
    _root(nullptr),
    _memory(memory) {}

template<typename T, typename K>
AVL<T,K>::~AVL() {
    delete_tree(_root);
}

template<typename T, typename K>
int AVL<T,K>::size() const {
    return _size;
}


///
template<typename T, typename K>
void AVL<T,K>::add(const K& key, int extra) {
    if (_root == nullptr) {
        throw KeyNotFound();
    }

    NODE *p = _root;
    while(p != nullptr) {
        if (p->_key == key) {
            if ((&p == &(p->_father->_left)) || p == this->_root)
            {
                p->_extra+=extra;
            }
            if (p->_right != nullptr)
                p->_right->_extra -= extra;

        } else if (p->_key < key) {
            p = p->_right;
            if (p->_father == this->_root)
            {
                p->_father->_extra+=extra;
                continue;
            }
            else if  (&(p->_father) == &(p->_father->_father->_left))
                p->_father->_extra+=extra;
        } else {
            p = p->_left;
            if (p->_father == this->_root)
            {
                continue;
            }
            if (&(p->_father) == &(p->_father->_father->_right))
                p->_father->_extra-=extra;
        }
    }
    throw KeyNotFound();
}
///


template<typename T, typename K>
T& AVL<T,K>::find(const K& key) {
    if (_root == nullptr) {
        throw KeyNotFound();
    }

    NODE *p = _root;
    while(p != nullptr) {
        if (p->_key == key) {
            return *p->_data;
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
    NODE *v = new NODE(key, data, _memory);
    _root = insert(_root, v);
    ++_size;
}

template<typename T, typename K>
void AVL<T,K>::remove(const K& key) {
    _root = remove(_root, key);
    --_size;
}

template<typename T, typename K>
NODE *AVL<T,K>::insert(NODE *root, NODE *v) {
    if (!root) {
        return v;
    }
    if (v->_key > root->_key) {
        /////
        v->_father = root;
        /////
        root->_right = insert(root->_right, v);
    } else if (v->_key < root->_key) {
        ///
        v->_father = root;
        ///
        root->_left = insert(root->_left, v);
    } else {
        throw KeyExists();
    }
    root->_height = NODE::height(root); // O(1)
    rotations(root); // O(1)
    return root;
}

template<typename T, typename K>
NODE *AVL<T,K>::remove(NODE *root, const K& key) {
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
            NODE *tmp = root->only_child();
            ///
            tmp->_father = root->_father;
            ///
            delete root;
            return tmp;
        }
        NODE *new_root = closest_up(root);
        NODE::swap(new_root, root);
        root->_right = remove(root->_right, key);
    }
    root->_height = NODE::height(root); // O(1)
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
void AVL<T, K>::inorder(Node<T,K> *r, Array<T*>& arr) const {
    if (r == nullptr) {
        return;
    }
    inorder(r->_left, arr);
    arr.push_back(r->_data);
    inorder(r->_right, arr);
}



template<typename T, typename K>
void AVL<T,K>::rotations(NODE *v) {
    if (NODE::BF(v) == 2) {
        if (NODE::BF(v->_left) == -1) {
            NODE::lr_rotation(v);
        } else {
            NODE::ll_rotation(v);
        }
    } else if (NODE::BF(v) == -2) {
        if (NODE::BF(v->_right) == 1) {
            NODE::rl_rotation(v);
        } else {
            NODE::rr_rotation(v);
        }
    }
}

template<typename T, typename K>
NODE *AVL<T,K>::closest_up(NODE *v) {
    assert(v->_right);
    NODE *res = v->_right;
    while (res->_left) {
        res = res->_left;
    }
    return res;
}

template<typename T, typename K>
NODE *AVL<T,K>::closest_down(NODE *v) {
    assert(v->_left);
    NODE *res = v->_left;
    while (res->_right) {
        res = res->_right;
    }
    return res;
}

template<typename T, typename K>
T* AVL<T,K>::max() const {
    NODE* tmp = this->_root;
    if(this->_root == nullptr)
        return nullptr;
    while(tmp->_right) {
        tmp = tmp->_right;
    }
    return tmp->_data;
}

template<typename T, typename K>
void AVL<T,K>::delete_tree(NODE *root) {
    if (!root) {
        return;
    }
    delete_tree(root->_left);
    delete_tree(root->_right);
    delete root;
}

template<typename T, typename K>
template<typename Function>
void AVL<T,K>::apply(Function func) {
    apply(_root, func);
}

template<typename T, typename K>
template<typename Function>
void AVL<T,K>::apply(NODE *root, Function func) {
    if (!root) {
        return;
    }
    func(*(root->_data));
    apply(root->_left, func);
    apply(root->_right, func);
}

template<typename T, typename K>
void AVL<T,K>::print(const std::string& prefix, NODE *root, bool left) const {
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
