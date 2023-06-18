
#ifndef TREE_H
#define TREE_H

#include <iostream>
#include "NodeTree.h"
#include "Array.h"
#define NODE NodeTree<K>

template<typename K>
class Tree {
public:
    Tree();
    Tree(const Tree& other) = delete;
    Tree& operator=(Tree& other);
    ~Tree();

    int size() const;
    void insert(const K& key);
    void remove(const K& key);
    void print() const;

    double prizeSum(const K& key);
    NODE *find(const K& key);
    void add(K key, double extra);

    template<typename Function>
    void apply(Function func);

    class KeyExists {};
    class KeyNotFound {};

private:
    int _size;
    NODE *_root;

    void rotations(NODE *v);
    NODE *closest_up(NODE *v);
    NODE *closest_down(NODE *v);
    NODE *insert(NODE *root, NODE *v);
    NODE *remove(NODE *root, const K& key);

    void delete_tree(NODE *root);

    template<typename Function>
    void apply(NODE *root, Function func);
};

template<typename K>
Tree<K>::Tree():
    _size(0),
    _root(nullptr) {}

template<typename K>
Tree<K>& Tree<K>::operator=(Tree<K>& other) {
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

template<typename K>
Tree<K>::~Tree() {
    delete_tree(_root);
}

template<typename K>
int Tree<K>::size() const {
    return _size;
}

template<typename K>
NODE * Tree<K>::find(const K& key) {
    if (_root == nullptr) {
        throw KeyNotFound();
    }

    NODE *p = _root;
    while(p != nullptr) {
        if (p->_key == key) {
            return p;
        } else if (p->_key < key) {
            p = p->_right;
        } else {
            p = p->_left;
        }
    }
    throw KeyNotFound();
}

template<typename K>
double Tree<K>::prizeSum(const K& key) {
    if (_root == nullptr) {
        return 0;
    }

    NODE *p = _root;
    double sum = _root->_extra;
    while(p != nullptr) {
        if (p->_key == key) {
            return sum;
        } else if (p->_key < key) {
            p = p->_right;
            if(p == nullptr)
                continue;
            sum += p->_extra;
        } else {
            p = p->_left;
            if(p == nullptr)
                continue;
            sum += p->_extra;
        }
    }
    return sum;
}

template< typename K>
void Tree<K>::insert(const K& key) {
    NODE *v = new NODE(key);
    _root = insert(_root, v);
    ++_size;
}

///
template<typename K>
void Tree<K>::add(K key, double extra) {
    if (_root == nullptr) {
        return;
    }

    NODE *p = _root;
    while(p != nullptr) {
        if (p->_key == key) {
            if (p == this->_root || (p == (p->_father->_left)))
            {
                p->_extra+=extra;
            }
            if (p->_right != nullptr)
                p->_right->_extra -= extra;
            return;
        } else if (p->_key < key) {
            NODE * father = p;
            p = p->_right;
            if (father == this->_root || p == nullptr)
            {
                father->_extra+=extra;
                continue;
            }
            else if  ((father) == (father->_father->_left))
                father->_extra+=extra;
        } else {
            NODE * father = p;
            p = p->_left;
            if (father == this->_root || father == nullptr)
            {
                continue;
            }
            if ((father) == (father->_father->_right))
                father->_extra -= extra;
        }
    }
}

template<typename K>
void Tree<K>::remove(const K& key) {
    _root = remove(_root, key);
    --_size;
}

template<typename K>
NODE *Tree<K>::insert(NODE *root, NODE *v) {
    if (!root) {
        return v;
    }
    if (v->_key > root->_key) {
        v->_father = root;
        root->_right = insert(root->_right, v);
    } else if (v->_key < root->_key) {
        v->_father = root;
        root->_left = insert(root->_left, v);
    } else {
        throw KeyExists();
    }
    root->_height = NODE::height(root); // O(1)
    rotations(root); // O(1)
    return root;
}

template<typename K>
NODE *Tree<K>::remove(NODE *root, const K& key) {
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
            tmp->_father = root->_father;
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



template<typename K>
void Tree<K>::rotations(NODE *v) {
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

template<typename K>
NODE *Tree<K>::closest_up(NODE *v) {
    assert(v->_right);
    NODE *res = v->_right;
    while (res->_left) {
        res = res->_left;
    }
    return res;
}

template<typename K>
NODE *Tree<K>::closest_down(NODE *v) {
    assert(v->_left);
    NODE *res = v->_left;
    while (res->_right) {
        res = res->_right;
    }
    return res;
}


template<typename K>
void Tree<K>::delete_tree(NODE *root) {
    if (!root) {
        return;
    }
    delete_tree(root->_left);
    delete_tree(root->_right);
    delete root;
}

template<typename K>
template<typename Function>
void Tree<K>::apply(Function func) {
    apply(_root, func);
}

template<typename K>
template<typename Function>
void Tree<K>::apply(NODE *root, Function func) {
    if (!root) {
        return;
    }
    func(*(root->_data));
    apply(root->_left, func);
    apply(root->_right, func);
}

#endif // TREE_H
