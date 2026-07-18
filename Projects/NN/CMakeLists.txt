cmake_minimum_required(VERSION 3.14)

project(NN)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# IMPORTANT: enable modern Python detection
set(PYBIND11_FINDPYTHON ON)

find_package(pybind11 CONFIG REQUIRED)

pybind11_add_module(NN
    src/binding.cpp
)

target_include_directories(NN PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)