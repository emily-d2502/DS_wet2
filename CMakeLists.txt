cmake_minimum_required(VERSION 3.22)
project(DS_wet2local2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(DS_wet2local2
        Array.h
        Tree.h
        Customer.cpp
        Customer.h
        HashTable.h
        mainWet2.cpp
        NodeTree.h
        AVL.h
        Node.h
        NodeUF.h
        Record.cpp
        Record.h
        recordsCompany.cpp
        recordsCompany.h
        UnionFind.h
        utilesWet2.h)
