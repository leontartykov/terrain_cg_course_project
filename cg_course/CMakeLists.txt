cmake_minimum_required(VERSION 3.5)

project(bmstu_cg_course_project LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(${PROJECT_NAME}
    main.cpp

    interface/mainwindow.cpp
    interface/mainwindow.h
    interface/mainwindow.ui
    interface/screen.hpp

    perlin/perlin.cpp
    perlin/perlin.hpp

    geometry/point.cpp
    geometry/point.hpp
    geometry/point.h)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)
