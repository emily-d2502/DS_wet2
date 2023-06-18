#ifndef UNION_FIND_H
#define UNION_FIND_H

typedef int Set;
#define EMPTY -1

template<class T>
class UnionFind {
public:
    UnionFind(int n);
    UnionFind(const UnionFind& other) = delete;
    UnionFind& operator=(const UnionFind& other) = delete;
    ~UnionFind();

//
    int SumHeight(int id);

    T* ReturnObject(int id);

    int stackBonA(int A,int B);


    void removeAllobjects();

//

    Set MakeSet(int member,T* object);
    Set Find(int member);
    Set Union(Set p, Set q);

private:
    int *_fullHeight;
    int *_size;
    int *_parent;
    Array<T> _objects;
};

template<class T>
UnionFind<T>::UnionFind(int n) : _objects(Array<T>(n)) {
    _fullHeight = new int[n];
    _size = new int[n];
    _parent = new int[n];
    for (int i = 0; i < n; ++i) {
        _size[i] = EMPTY;
        _parent[i] = EMPTY;
    }
}

template<class T>
UnionFind<T>::~UnionFind() {
    delete[] _fullHeight;
    delete[] _size;
    delete[] _parent;
}

template<class T>
Set UnionFind<T>::MakeSet(int member, T* object) {
    _fullHeight[member] = object->copies();
    _size[member] = 1;
    _objects[member] = *object;
    return member;
}

template<class T>
Set UnionFind<T>::Find(int member) {
    int sumHeights = (_objects[member]).getHeight();
    int root = member;
    while (_parent[root] != EMPTY) {
        sumHeights += _objects[root].getHeight();
        root = _parent[root];
    }
    int node = member;
    while (_parent[node] != EMPTY) {
        int old_parent = _parent[node];
        int subtract = _objects[node].getHeight();
        _objects[node].setHeight(sumHeights);
        sumHeights -= subtract;
        _parent[node] = root;
        node = old_parent;
    }
    return root;
}

template<class T>
Set UnionFind<T>::Union(Set p, Set q) {
    Set *l = &q;
    Set *s = &p;
    if (_size[p] >= _size[q]) {
        l = &p;
        s = &q;
    }
    _parent[*s] = *l;
    _size[*l] += _size[*s];
    _fullHeight[*l] += _fullHeight[*s];
    _fullHeight[*s] = 0;
    _size[*s] = EMPTY;
    return *l;
}

template<typename T>
int UnionFind<T>::SumHeight(int id) {
    int SumHeight = _objects[id].getHeight();

    int father = _parent[id];
    while (father != EMPTY)
    {
        SumHeight += _objects[father].getHeight();
        father = _parent[father];
    }
    return SumHeight;
}

template<typename T>
T* UnionFind<T>::ReturnObject(int id){
    return &_objects[id];
}

template<typename T>
void UnionFind<T>::removeAllobjects(){
    for (int i = 0; i < _objects.size(); i++)
    {
        _objects[i].zeroBuys();
    }
//    delete _objects;
}


template<typename T>
int UnionFind<T>::stackBonA(int A,int B) {

    if(_size[A] >= _size[B])
    {
        _objects[B].setHeight(_objects[B].getHeight() + _fullHeight[A]);
        _objects[B].setHeight(_objects[B].getHeight() - _objects[A].getHeight());
        Union(A,B);
        return A;
    }
    else {
        _objects[B].setColumn(_objects[A].getColumn());
        _objects[B].setHeight(_objects[B].getHeight() + _fullHeight[A]);
        _objects[A].setHeight(_objects[A].getHeight() - _objects[B].getHeight());
        Union(A,B);
        return B;
    }

}

#endif // UNION_FIND_H