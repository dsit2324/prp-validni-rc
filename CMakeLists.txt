cmake_minimum_required(VERSION 3.31)
project(validni_rc)

set(CMAKE_CXX_STANDARD 20)

add_executable(validni_rc main.cpp rc.cpp rc.h)
