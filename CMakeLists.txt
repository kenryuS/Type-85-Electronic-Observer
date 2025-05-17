cmake_minimum_required(VERSION 3.21)

project(Type-85-Electronic-Observer VERSION 0.0.1 LANGUAGES CXX)

add_subdirectory(${CMAKE_SOURCE_DIR}/src/ui
    ${CMAKE_BINARY_DIR}/Type85-EO/ui
)
