cmake_minimum_required(VERSION 3.22)
project(DS_wet2local)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(DS_wet2local
        Array.h
        AVL.h
        macros.h
        mainWet2.cpp
        HashTable.h
        Customer.h
        Customer.cpp
        Record.h
        Record.cpp
        Node.h
        recordsCompany.cpp
        recordsCompany.h
        UnionFind.h
        NodeUF.h
        utilesWet2.h)
