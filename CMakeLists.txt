cmake_minimum_required (VERSION 3.0) 

PROJECT(calibration)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g -O0")

FIND_PACKAGE(OpenCV 4.0.0 REQUIRED)

MESSAGE("OpenCv version: ${OpenCV_VERSION}")
MESSAGE("CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
MESSAGE("OpenCv include dirs: ${OpenCV_INCLUDE_DIRS}")

include_directories(${OpenCV_INCLUDE_DIRS}) 

link_directories(${OpenCV_LIB_DIR})

# SET(SRC main.cpp )
set(SRC calibrate.cpp CameraCalibrator.cpp)
ADD_EXECUTABLE(${PROJECT_NAME} ${SRC})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${OpenCV_LIBS}) 

