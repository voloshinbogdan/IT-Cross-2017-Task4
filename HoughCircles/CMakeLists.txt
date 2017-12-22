cmake_minimum_required(VERSION 2.8.11)

project(ImProc)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt5Widgets)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

qt5_wrap_ui(UIC_WRAPPERS main-window.ui)

add_executable(
	ImProc
	main.cpp
	main-window.cpp
	main-window.h
	worker-thread.cpp
	worker-thread.h
	${UIC_WRAPPERS})


target_link_libraries(ImProc Qt5::Widgets)
target_link_libraries(ImProc ${OpenCV_LIBS} )
