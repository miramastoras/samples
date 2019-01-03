cmake_minimum_required(VERSION 3.8)
project(homework6_2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        cmake-build-debug/cmake_install.cmake
        cmake-build-debug/CMakeCache.txt
        cmake-build-debug/Homework__6_2_Read_Lines_Skeleton_Code
        cmake-build-debug/Homework__6_2_Read_Lines_Skeleton_Code.cbp
        cmake-build-debug/Makefile
        CMakeLists.txt
        main.c
        Makefile
        read_lines.c
        read_lines.h)

set(GCC_ENABLE_WARNINGS "-O1 -Wall -Werror -Wno-unused-result")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_ENABLE_WARNINGS}")
add_executable(homework6_2 ${SOURCE_FILES})