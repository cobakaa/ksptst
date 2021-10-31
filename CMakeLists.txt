cmake_minimum_required(VERSION 3.16)
project(ksptst)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(ksptst
        a.out
        main.cpp ScanDirectory.h ScanDirectory.cpp Search.h Search.cpp)
