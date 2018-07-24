cmake_minimum_required(VERSION 3.0)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(EXTRA_LANG CXX)
endif()

project(skynet-sensor C ${EXTRA_LANG})

if(CMAKE_CROSSCOMPILING)
    set(CMAKE_C_FLAGS "--std-c11 -mstm8 --opt-code-size")
    add_definitions(-DSTM8S103)
    add_subdirectory(stm8s-stdperiph)
else()
    set(CMAKE_C_FLAGS "-std=c11")
    set(CMAKE_CXX_FLAGS "-std=c++11")
    add_subdirectory(googletest)
    add_subdirectory(toolkit)
endif()

add_subdirectory(src)

