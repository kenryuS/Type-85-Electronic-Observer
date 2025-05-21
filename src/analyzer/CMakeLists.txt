cmake_minimum_required(VERSION 3.21)

project(kc-api-analyzer VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/analyzer
)

file(GLOB _SRC_FILES_OBSERVER "*.cpp")
file(GLOB _INCLUDE_FILES_OBSERVER "${CMAKE_SOURCE_DIR}/include/analyzer/*.hpp")

add_compile_definitions("DEBUG=$<CONFIG:Debug>")

add_library(
    ${PROJECT_NAME}

    SHARED

    ${_SRC_FILES_OBSERVER}
    ${_INCLUDE_FILES_OBSERVER}
)

