cmake_minimum_required(VERSION 3.22)
project(DataStructures_spring2023_Wet2Test)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(DataStructures_spring2023_Wet2Test
        Array.h
        AVL.h
        Customer.cpp
        Customer.h
        HashTable.h
        macros.h
        mainWet2.cpp
        Node.h
        NodeTree.h
        NodeUF.h
        Record.cpp
        Record.h
        recordsCompany.cpp
        recordsCompany.h
        Tree.h
        UnionFind.h
        utilesWet2.h)
