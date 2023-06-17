
#pragma once
#include <assert.h>
#define MAX(n,m)      \
((n) > (m) ? (n) : (m))

#define GENERIC_FRIEND_CLASS(x) \
template<typename>    \
friend class x

template<typename K>
class NodeTree {
public:
    NodeTree(const K& key, bool memory = false);
    NodeTree(const NodeTree&) = delete;
    NodeTree& operator=(const NodeTree&) = delete;
    ~NodeTree();
    static void swap(NodeTree *v, NodeTree *u);

private:
    GENERIC_FRIEND_CLASS(Tree);

    K _key;
//    T* _data;
    NodeTree *_left;
    NodeTree *_right;
    ///
    NodeTree *_father;
    double _extra;
    ///

    int _height;
    bool _memory;
    bool leaf();
    int children();
    NodeTree *only_child();

    static int BF(NodeTree *v);
    static int height(NodeTree *v);
    static void rr_rotation(NodeTree *v);
    static void ll_rotation(NodeTree *v);
    static void lr_rotation(NodeTree *v);
    static void rl_rotation(NodeTree *v);
};

template<typename K>
NodeTree<K>::NodeTree(const K& key, bool memory):
    _key(key),
//    _data(data),
    _left(nullptr),
    _right(nullptr),
        //
    _father(nullptr),
    _extra(0),
        //
    _height(0),
    _memory(memory) {}

template<typename K>
NodeTree<K>::~NodeTree() {
    if (_memory) {
//        delete _data;
    }
}

template<typename K>
void NodeTree<K>::swap(NodeTree *v, NodeTree *u) {

    double tmp = u->_extra;
    u->_extra = v->_extra;
    v->_extra = tmp;

    K temp_key = u->_key;
    u->_key = v->_key;
    v->_key = temp_key;
}

template<typename K>
bool NodeTree<K>::leaf() {
    return ((!_right) && (!_left));
}

template<typename K>
int NodeTree<K>::children() {
    if (_left && _right) {
        return 2;
    }
    if (_left || _right) {
        return 1;
    }
    return 0;
}

template<typename K>
NodeTree<K> *NodeTree<K>::only_child() {
    assert(children() == 1);
    return (!_right) ? _left : _right;
}


template<typename K>
int NodeTree<K>::BF(NodeTree *v) {
    if (v->_left && v->_right) {
        return v->_left->_height - v->_right->_height;
    }
    if (v->_right) {
        return - v->_right->_height - 1;
    }
    if (v->_left) {
        return v->_left->_height + 1;
    }
    return 0;
}


template<typename K>
int NodeTree<K>::height(NodeTree *v) {
    if (v->_left && v->_right) {
        return MAX(v->_left->_height, v->_right->_height) + 1;
    }
    if (v->_right) {
        return v->_right->_height + 1;
    }
    if (v->_left) {
        return v->_left->_height + 1;
    }
    return 0;
}


template<typename K>
void NodeTree<K>::rr_rotation(NodeTree *v) {
    std::cerr<< "rr";
    NodeTree *u = v->_right;

    double oldUExtra = u->_extra;
    ///
    if (v->_left){
        v->_left->_father= u;
    }

    if (u->_right){
        u->_right->_father= v;
    }
    //

    swap(u,v);

    v->_right = u->_right;
    u->_right = u->_left;
    u->_left = v->_left;
    v->_left = u;

    //
    v->_extra += u->_extra;
    u->_extra = -oldUExtra;
    if (u->_right){
        u->_right->_extra += oldUExtra;
    }
    //


    u->_height = height(u);
    v->_height = height(v);
}


template<typename K>
void NodeTree<K>::ll_rotation(NodeTree *v) {
    std::cerr<< "ll";
    NodeTree *u = v->_left;

    double oldUExtra = u->_extra;


    ///
    if (u->_left){
        u->_left->_father= v;
    }
    if (v->_right){
        v->_right->_father= u;
    }
    //


    swap(u,v);

    v->_left = u->_left;
    u->_left = u->_right;
    u->_right = v->_right;
    v->_right = u;

    //
    v->_extra += u->_extra;
    u->_extra = -oldUExtra;
    if (u->_left){
        u->_left->_extra += oldUExtra;
    }
    //

    u->_height = height(u);
    v->_height = height(v);
}

template<typename K>
void NodeTree<K>::lr_rotation(NodeTree *v) {
    rr_rotation(v->_left);
    ll_rotation(v);
    v->_height = height(v);
}

template<typename K>
void NodeTree<K>::rl_rotation(NodeTree *v) {
    ll_rotation(v->_right);
    rr_rotation(v);
    v->_height = height(v);
}

