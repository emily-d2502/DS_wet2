cmake_minimum_required(VERSION 3.22)
project(DS_wet2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(DS_wet2
        mainWet2.cpp
        recordsCompany.cpp
        recordsCompany.h
        AVL.h
        Node.h
        Array.h
        macros.h
        utilesWet2.h)
