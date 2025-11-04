cmake_minimum_required(VERSION 3.14)

project(snakeCPP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(
    SRC_FILES
    bonus.cpp
    main.cpp
    snake.cpp
    world.cpp
    widget.cpp
)
set(
    SRC_HEADERS
    bonus.hpp
    point.hpp
    snake.hpp
    timer.hpp
    world.hpp
    widget.hpp
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(${PROJECT_NAME} ${SRC_FILES} ${SRC_HEADERS})

target_compile_definitions(
    ${PROJECT_NAME}
    PRIVATE _CRT_SECURE_NO_WARNINGS
)


target_link_libraries(
    ${PROJECT_NAME}
)
