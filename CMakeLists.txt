cmake_minimum_required(VERSION 3.4)
project(boostGeometryDemo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


include_directories(geometryPrimitives)
set(SOURCE_FILES main.cpp geometryPrimitives/point/instantion.cpp geometryPrimitives/box/instantion.cpp Spatial/SpatialContainer.cpp)
add_executable(boostGeometryDemo ${SOURCE_FILES})