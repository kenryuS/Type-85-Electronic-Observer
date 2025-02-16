cmake_minimum_required(VERSION 3.19.1)

project(Type-85-Electronic-Observer VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

find_library(QCEFVIEW_LIBRARY NAMES QCefView PATHS ${CMAKE_SOURCE_DIR}/thirdparty/QCefView/linux/bin)

include_directories(
        ${CMAKE_SOURCE_DIR}/include
	${CMAKE_SOURCE_DIR}/forms/include
)

set(_SRC_FILES
        ${CMAKE_SOURCE_DIR}/src/main.cpp
	${CMAKE_SOURCE_DIR}/src/MainWindow.cpp
)

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
        add_executable(${PROJECT_NAME}
	        ${_SRC_FILES}
	)

	set_target_properties(${PROJECT_NAME}
	        PROPERTIES
		INSTALL_RPATH "$ORIGIN"
		BUILD_WITH_INSTALL_RPATH TRUE
	)

	target_link_libraries(${PROJECT_NAME}
	        PRIVATE
		"-Wl,--no-as-needed ${CMAKE_SOURCE_DIR}/thirdparty/QCefView/linux/bin/libcef.so"
		Qt6::Core
		Qt6::Widgets
		Qt6::Gui
		${QCEFVIEW_LIBRARY}
	)

	add_custom_command(TARGET ${PROJECT_NAME}
	        POST_BUILD

		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/thirdparty/QCefView/linux/bin
		$<TARGET_FILE_DIR:${PROJECT_NAME}>
	)
endif()
