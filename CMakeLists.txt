cmake_minimum_required(VERSION 3.17)
project(mvg4)

set(CMAKE_CXX_STANDARD 17)

find_package( OpenCV REQUIRED )
set(SOURCE_FILES main.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )

find_package (Eigen3 3.3 REQUIRED NO_MODULE)
target_link_libraries (${PROJECT_NAME} Eigen3::Eigen)

add_executable(mvg5 main.cpp)
