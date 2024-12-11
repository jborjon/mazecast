cmake_minimum_required(VERSION 3.20)
project(Mazecast C)
set(CMAKE_C_STANDARD 99)

add_executable(mazecast src/main.c src/game.c)
target_include_directories(mazecast PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Set the default build to release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler flags
set(CMAKE_C_FLAGS_DEBUG "-g -O0")
set(CMAKE_C_FLAGS_RELEASE "-O3")

# Set the compiler for each platform
if(UNIX)
    set(CMAKE_C_COMPILER gcc)
elseif(WIN32)
set(CMAKE_C_COMPILER clang)
endif()

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/debug")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/release")
