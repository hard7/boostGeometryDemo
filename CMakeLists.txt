cmake_minimum_required(VERSION 3.4)
project(boostGeometryDemo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic-errors")


include_directories(geometryPrimitives .)
set(SOURCE_FILES main.cpp geometryPrimitives/impl/instantion.cpp Spatial/impl/Container.cpp Spatial/impl/Component.cpp)
add_executable(boostGeometryDemo ${SOURCE_FILES})