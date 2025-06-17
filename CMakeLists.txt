cmake_minimum_required(VERSION 3.31)
project(TinyTracer)

set(CMAKE_CXX_STANDARD 20)

add_executable(TinyTracer
        main.cpp
        src/vec3.h
)

add_executable(test_vec3
        src/test_vec3.cpp
)