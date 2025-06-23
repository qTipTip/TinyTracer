cmake_minimum_required(VERSION 3.31)
project(TinyTracer)

set(CMAKE_CXX_STANDARD 20)

add_executable(TinyTracer
        main.cpp
)


target_include_directories(TinyTracer PRIVATE src)
