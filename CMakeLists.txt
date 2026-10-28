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

#Клиент
add_executable(FileClient
    client/main.cpp
    client/ClientWindow.h
    client/ClientWindow.cpp
)
target_link_libraries(FileClient PRIVATE Qt5::Widgets Qt5::Network)

#Сервер
add_executable(FileServer
    server/main.cpp
    server/ServerWindow.h
    server/ServerWindow.cpp
)
target_link_libraries(FileServer PRIVATE Qt5::Widgets Qt5::Network)