cmake_minimum_required(VERSION 3.16)
project(ksptst)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

include_directories(.)

add_executable(ksptst
        a.out
        main.cpp include/ScanDirectory.h src/ScanDirectory.cpp include/Search.h src/Search.cpp src/Timer.cpp include/Timer.h)
