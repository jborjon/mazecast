cmake_minimum_required(VERSION 3.16)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

project(Mazecast C)
add_executable(mazecast)

set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
target_include_directories(mazecast PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_sources(mazecast
    PRIVATE
        ${SRC_DIR}/main.c
        ${SRC_DIR}/game.c
        ${SRC_DIR}/utils.c
)

# Link the SDL3 library
find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3)
target_link_libraries(mazecast PRIVATE SDL3::SDL3)

# Set the default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
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
