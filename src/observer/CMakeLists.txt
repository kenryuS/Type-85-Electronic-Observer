cmake_minimum_required(VERSION 3.21)

project(observer VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS
    Core
)

qt_standard_project_setup()

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/observer
)

file(GLOB _SRC_FILES_OBSERVER "*.cpp")
file(GLOB _INCLUDE_FILES_OBSERVER "${CMAKE_SOURCE_DIR}/include/observer/*.hpp")

add_compile_definitions("DEBUG=$<CONFIG:Debug>")

qt_add_executable(
    ${PROJECT_NAME}

    ${_SRC_FILES_OBSERVER}
    ${_INCLUDE_FILES_OBSERVER}
)

qt_wrap_cpp(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/lib.cpp
)

