cmake_minimum_required(VERSION 3.16)
project(histogram_equalization)

set(CMAKE_CXX_STANDARD 14)

add_executable(histogram_equalization main.cpp)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
set(SOURCE_FILES main.cpp)
file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})