cmake_minimum_required(VERSION 3.27)
project(MyKgmWasm)

set(CMAKE_CXX_STANDARD 11)

add_executable(MyKgmWasm main.cpp
        KgmCodec.cpp
        KgmCodec.h
        KgmUtils.h)
