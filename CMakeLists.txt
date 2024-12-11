cmake_minimum_required(VERSION 3.16)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

project(Mazecast C)
add_executable(mazecast src/main.c src/game.c)
target_include_directories(mazecast PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Set the default build type to release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Set the compiler for each platform
if(UNIX)
    set(CMAKE_C_COMPILER gcc)
elseif(WIN32)
    set(CMAKE_C_COMPILER clang)
endif()

# Compiler flags
set(CMAKE_C_FLAGS_DEBUG "-g -O0")
set(CMAKE_C_FLAGS_RELEASE "-O3")

# Set output directories
set(RUNTIME_OUTPUT_DIR "${CMAKE_BINARY_DIR}/build")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${RUNTIME_OUTPUT_DIR}/debug")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${RUNTIME_OUTPUT_DIR}/release")
