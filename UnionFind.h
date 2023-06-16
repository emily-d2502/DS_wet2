

#ifndef CPP_UNIONFIND_H
#define CPP_UNIONFIND_H

#include "Array.h"
#include "NodeUF.h"
#include "Record.h"



template<typename T>
class UnionFind {
public:
    Array<NodeUF<T>*> * records;


    explicit UnionFind(int n);
    ~UnionFind();
    NodeUF<T>* Makeset(T* record);

    T* ReturnObject(int id);

    T* stackBonA(T* A,T* B);


    T* Find(int Id);


    int SumHeight(T* record);
    void removeAllRecords();

};


template<typename T>
NodeUF<T>* UnionFind<T>::Makeset(T* record) {
    NodeUF<T>* tmp = new NodeUF<T>(record);
    record->setNode(tmp);
    records->push_back(tmp);
    tmp->_indHeight = 0;
    tmp->_stackHeight = record->copies();
    tmp->_column = record->id();
    return tmp;
}



template<typename T>
T* UnionFind<T>::stackBonA(T* A,T* B) {

    NodeUF<T>* HeadBase = A->UF_Node();
    while(HeadBase->_father)
        HeadBase = HeadBase->_father;

    NodeUF<T>* HeadStack = B->UF_Node();
    while(HeadStack->_father)
        HeadStack = HeadStack->_father;

    //Making changes based on the different sizes of the two teams.
    if (HeadBase->_size >= HeadStack->_size)
    {
        HeadStack->_father = HeadBase;
        HeadBase->_size += HeadStack->_size;
        return A;
    }
    else {

        HeadBase->_father = HeadStack;
        HeadStack->_size += HeadBase->_size;

        HeadStack->_column = HeadBase->_column;

        HeadStack->_stackHeight += HeadBase->_stackHeight;
        HeadBase->_stackHeight -= HeadStack->_stackHeight;



        return B;
    }
}


template<typename T>
T* UnionFind<T>::ReturnObject(int id){
    return (*records)[id]->_data;
}


template<typename T>
T* UnionFind<T>::Find(int Id) {

    NodeUF<T>* tmp1 = (*records)[Id];
    NodeUF<T>* tmp2 = tmp1;


    int sumHeights = 0;
    // = tmp1->_data->get_ind_heght^^^????

    if(tmp1->_size != 0)
    {
        sumHeights += tmp1->_stackHeight;
    }

    tmp1 = tmp1->_father;
    while(tmp1 && tmp1->_father)
    {
        sumHeights += tmp1->_stackHeight;
        tmp1 = tmp1->_father;
    }

    while(tmp2->_father)
    {
        NodeUF<T>* next = tmp2->_father;

        if(tmp2->_size == 0)
        {
            tmp2->_indHeight = sumHeights;

            //move node
            tmp2->_father = tmp1;
        }
        else
        {
            sumHeights -= tmp2->_stackHeight;
            tmp2->_stackHeight = sumHeights;

            //move node
            tmp2->_father = tmp1;
        }
        tmp2 = next;
    }
    return tmp2->_data;
}




template<typename T>
int UnionFind<T>::SumHeight(T* record) {
    NodeUF<T>* RecordNode = (*records)[record->id()];
    int SumHeight = RecordNode->_indHeight;

    if(RecordNode->_size != 0)
    {
        SumHeight += RecordNode->_stackHeight;
    }

    NodeUF<T>* fatherNode = RecordNode->_father;
    while (fatherNode)
    {
        SumHeight += fatherNode->_stackHeight;
        fatherNode = fatherNode->_father;
    }
    return SumHeight;
}

template<typename T>
void UnionFind<T>::removeAllRecords(){
    for (int i = 0; i < records->size(); i++)
    {
        (*records)[i]->_data->zeroBuys();
        delete (*records)[i]->_data;
        delete (*records)[i];
        // kill the records themselves as well as UFnode
    }
    delete records;
}

template<typename T>
UnionFind<T>::UnionFind(int n) : records(n) {}


template<typename T>
UnionFind<T>::~UnionFind() {
    delete records;
}

#endif //CPP_UNIONFIND_H
