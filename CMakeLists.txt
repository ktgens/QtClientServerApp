cmake_minimum_required(VERSION 3.16)
project(QtVsCodeDemo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

if(WIN32)
    set(CMAKE_PREFIX_PATH "C:/Qt/5.15.0/msvc2019_64")
endif()

find_package(Qt5 COMPONENTS Widgets Network REQUIRED)

add_executable(QtVsCodeDemo
    main.cpp
    StateButton.h
    StateButton.cpp
    resources.qrc
)

target_link_libraries(QtVsCodeDemo PRIVATE Qt5::Widgets)

