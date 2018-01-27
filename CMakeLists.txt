cmake_minimum_required(VERSION 2.8)
set(CMAKE_BUILD_TYPE Release)
project(music-player-simulator)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
set(EXECUTABLE music-player-simulator)

add_compile_options(-std=c++14 -Wall)

file(
    GLOB
    sources
    src/*
)

include_directories(includes)

add_executable(
    ${EXECUTABLE}
    src/main.cpp
    ${sources}
)
