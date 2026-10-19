cmake_minimum_required(VERSION 3.16)
project(QtVsCodeDemo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(QtVsCodeDemo
    main.cpp
    StateButton.h
    StateButton.cpp
    resources.qrc
)

target_link_libraries(QtVsCodeDemo PRIVATE Qt5::Widgets)

