//
// Created by Adi on 24/12/2022.
//

#ifndef TEA_CPP_UNIONFIND_H
#define TEA_CPP_UNIONFIND_H

#include "Array.h"
#include "NodeUF.h"
#include "Record.h"



template<typename T>
class UnionFind {
public:
    Array<NodeUF<T*>> records;


    explicit UnionFind();
    NodeUF<T>* Makeset(T* record);


    T* stackBonA(T* A,T* B);


    T* Find(int Id);


    int SumHeight(T* record);
    void removeAllRecords();

};

template<typename T>
NodeUF<T>* UnionFind<T>::Makeset(T* record) {
    NodeUF<T>* tmp = records.push_back(record);
    tmp->_size = 1;
    tmp->_height = 0;
    return tmp;
}


template<typename T>
T* UnionFind<T>::stackBonA(T* A,T* B) {

    NodeUF<T>* HeadBase = A->node();
    while(HeadBase->_father)
        HeadBase = HeadBase->_father;

    NodeUF<T>* HeadStack = B->node();
    while(HeadStack->_father)
        HeadStack = HeadStack->_father;

    //Making changes base on the different sizes of the two teams.
    if (HeadBase->_size >= HeadStack->_size)
    {
        HeadStack->_father = HeadBase;
        HeadBase->_size += HeadStack->_size;
        //
        HeadStack->_size = 0;
        //
        //changes in stackheight for smaller team
//        B->set_gamesPlayedToUpdate(-(A-> get_gamesPlayedToUpdate()));
        return A;
    }
    else {

        HeadBase->_father = HeadStack;
        HeadStack->_size += HeadBase->_size;

        // we are changing here the team id and so it could fuck up the process of finding the team later in the trees,
//        HeadStack->_size = 0;

        B->set_tea_id(A->get_tea_id());

        //changes in set_gamesPlayedToUpdate for smaller team
//        A->set_gamesPlayedToUpdate(-B->get_gamesPlayedToUpdate());
//
        return B;
    }
}


template<typename T>
T* UnionFind<T>::Find(int Id) {

    NodeUF<T>* tmp1 = records[Id];
    NodeUF<T>* tmp2 = tmp1;

    T * recordPointer = tmp1->_data;

    int sumHeights = 0;
    // = tmp1->_data->get_ind_heght^^^????

    if(tmp1->_size != 0)
    {
        sumHeights += tmp1->_stackHeight;
    }

    tmp1 = tmp1->_father;
    while(tmp1 && tmp1->_father)
    {
        sumHeights += tmp1->_stackHeight();
        tmp1 = tmp1->_father;
    }

    while(tmp2->_father)
    {
        NodeUF<T>* next = tmp2->_father;

        if(tmp2->_size == 0)
        {
            tmp2->set_indHeight(sumHeights);

            //move node
            tmp2->_father = tmp1;
        }
        else
        {
            sumHeights -= tmp2->_sumHeights();
            tmp2->set_stackHeight(sumHeights);

            //move node
            tmp2->_father = tmp1;
        }
        tmp2 = next;
    }

    return recordPointer;
}




template<typename T>
int UnionFind<T>::SumHeight(T* record) {
    NodeUF<T>* RecordNode = records[record->_id()];
    int SumHeight = RecordNode->_indHeight();

    if(RecordNode->_size != 0)
    {
        SumHeight += RecordNode->_stackHeight();
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
    for (int i = 0; i < records.size(); i++)
    {
        delete records[i];
        //doesnt kill the records themelves right now^
    }
    delete records;
}

template<typename T>
UnionFind<T>::UnionFind() {

}


#endif //TEA_CPP_UNIONFIND_H
