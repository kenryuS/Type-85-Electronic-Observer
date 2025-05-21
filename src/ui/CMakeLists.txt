cmake_minimum_required(VERSION 3.21)

project(observer_ui VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Widgets
    Gui
    WebEngineCore
    WebEngineWidgets
    LinguistTools
)

qt_standard_project_setup(
    I18N_SOURCE_LANGUAGE en
    I18N_TRANSLATED_LANGUAGES ja
)

qt_add_translations(
    TARGETS observer_ui
    TS_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/assets/trans
)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/ui
)

set(_FORMS_FILES
    ${CMAKE_SOURCE_DIR}/forms/MainWindow.ui
)

file(GLOB _SRC_FILES_UI "*.cpp")
file(GLOB _INCLUDE_FILES_UI "${CMAKE_SOURCE_DIR}/include/ui/*.hpp")

add_compile_definitions("DEBUG=$<CONFIG:Debug>")

qt_add_executable(
    ${PROJECT_NAME}

    ${_SRC_FILES_UI}
    ${_INCLUDE_FILES_UI}
)

qt_wrap_cpp(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/BrowserWidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MainWindow.cpp
)

qt_add_ui(
    ${PROJECT_NAME}
    SOURCES ${_FORMS_FILES}
    INCLUDE_PREFIX ui
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Gui
    Qt6::WebEngineCore
    Qt6::WebEngineWidgets
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
