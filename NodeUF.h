//
// Created by Adi on 25/12/2022.
//

#ifndef TEAM_CPP_NODEUF_H
#define TEAM_CPP_NODEUF_H

//#include "Team.h"


///////////////class NodeUF////////////////

template<typename T>
class NodeUF{
public:
    T* _data;
    int _size;
    int _indHeight;
    int _stackHeight;
    NodeUF* _father;

    explicit NodeUF(T* t) :
            _data(t),
            _size (0),
            _indHeight(0),
            _stackHeight(0),
            _father (nullptr){}

    NodeUF (const NodeUF& NodeUF) = default;
    ~NodeUF();
    NodeUF& operator=(const NodeUF& other) = default;
};


template<typename T>
NodeUF<T>::~NodeUF() {
    delete _data;
}



//////////////////end class NodeUF////////////////

#endif //TEAM_CPP_NODEUF_H
