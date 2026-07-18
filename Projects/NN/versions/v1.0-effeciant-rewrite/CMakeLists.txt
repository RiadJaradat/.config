cmake_minimum_required(VERSION 3.20)
project(NN VERSION 1.0 LANGUAGES CXX)

# Force the C++ standard to C++23 (or C++26 if your compiler fully supports it yet)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define your executable and source files
add_executable(NN src/main.cpp)

# Target the include directory for headers
target_include_directories(NN PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Apply elite production-level performance optimization flags
if(MSVC)
    # Optimizations for Windows Visual Studio Compiler
    target_compile_options(NN PRIVATE /O2 /fp:fast /arch:AVX2)
else()
    # Optimizations for G++ (GCC) and Clang
    target_compile_options(NN PRIVATE 
        -O3 
        -Ofast 
        -ffast-math 
        -march=native
    )
endif() 