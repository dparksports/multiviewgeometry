cmake_minimum_required(VERSION 3.17)
project(mvg6)

set(CMAKE_CXX_STANDARD 17)

find_package( OpenCV REQUIRED )
set(SOURCE_FILES projection_matrix.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

#add_executable(mvg62 projection_matrix.cpp)
