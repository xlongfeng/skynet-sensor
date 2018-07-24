cmake_minimum_required(VERSION 3.0)

project(toolkit)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(
    ${skynet-sensor_SOURCE_DIR}/src)

find_package(Qt5 COMPONENTS Widgets SerialPort REQUIRED)

add_executable(toolkit
    ../src/stdio.c
    ../src/utility.c
    ../src/os_linux.c
    main.cpp
    mainwin.cpp
    mainwin.ui
    )

target_link_libraries(toolkit Qt5::Widgets Qt5::SerialPort)
