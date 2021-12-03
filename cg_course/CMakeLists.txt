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

    driver/perlin/perlin.cpp
    driver/perlin/perlin.hpp

    driver/geometry/point/point.cpp
    driver/geometry/point/point.hpp
    driver/geometry/point/point.h

    driver/geometry/figure/figure.h
    driver/geometry/figure/figure.cpp

    driver/geometry/polygon/polygon.h
    driver/geometry/polygon/polygon.hpp
    driver/geometry/polygon/polygon.cpp

    driver/geometry/grid/grid.h
    driver/geometry/grid/grid.hpp
    driver/geometry/grid/grid.cpp

    driver/geometry/line/line.h
    driver/geometry/line/line.hpp
    driver/geometry/line/line.cpp

    driver/geometry/matrix/matrix.h
    driver/geometry/matrix/matrix.hpp
    driver/geometry/matrix/matrix.cpp

    driver/request/request.cpp
    driver/request/request.hpp
    driver/request/request.h

    driver/transform/transform.cpp
    driver/transform/transform.hpp
    driver/transform/transform.h

    driver/landscape/landscape.cpp
    driver/landscape/landscape.hpp
    driver/landscape/landscape.h

    driver/invisible/zbuffer.cpp
    driver/invisible/zbuffer.hpp
    driver/invisible/zbuffer.h

    driver/geometry/matrix/matrix.cpp
    driver/geometry/matrix/matrix.hpp
    driver/geometry/matrix/matrix.h

    driver/color/color.h
    driver/color/color.hpp
    driver/color/color.cpp

    driver/light/light.h
    driver/light/light.hpp
    driver/light/light.cpp

    driver/geometry/vector/vector.h
    driver/geometry/vector/vector_2.hpp
    driver/geometry/vector/vector_2.cpp
    driver/geometry/vector/vector_3.hpp
    driver/geometry/vector/vector_3.cpp

    driver/camera/camera.h
    driver/camera/camera.hpp
    driver/camera/camera.cpp
    )

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)
