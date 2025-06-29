cmake_minimum_required(VERSION 3.23)  # 3.23+ for better module support
project(chessengine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES arm64)

add_compile_options(-O3 -march=native -ffast-math)
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "enabled")

file(GLOB SOURCES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB HEADERS CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.h")

add_executable(chessengine ${SOURCES} ${HEADERS}
        src/board.h
        src/moveGenerator.h)

target_include_directories(chessengine PRIVATE "${CMAKE_SOURCE_DIR}/src")