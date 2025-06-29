cmake_minimum_required(VERSION 3.15)
project(GoatChess)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES arm64)

add_compile_options(-O3 -march=native -ffast-math)

file(GLOB SOURCES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB HEADERS CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.h")
file(GLOB MODULES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.cppm")

add_executable(chessengine ${SOURCES} ${HEADERS})

target_include_directories(chessengine PRIVATE "${CMAKE_SOURCE_DIR}/src")