cmake_minimum_required(VERSION 3.6)
project(TecnicasDeProgramacionConcurrentesTP2)

set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wpedantic -Wextra -pthread" )
set ( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -DNDEBUG" )
set ( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g -ggdb -O0 -fprofile-arcs -ftest-coverage" )
set ( CMAKE_CXX_LINKER_FLAGS_DEBUG "${CMAKE_CXX_LINKER_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage -pthread" )

if ( NOT CMAKE_BUILD_TYPE )
    set ( CMAKE_BUILD_TYPE Debug )
endif ()

set(SOURCE_FILES main.cpp)
add_executable(TecnicasDeProgramacionConcurrentesTP2 ${SOURCE_FILES})

# Permite que el compilador vea los include
include_directories ( ${PROJECT_SOURCE_DIR}/utils )

# Donde estan las librerias
add_subdirectory ( utils )

target_link_libraries ( ${PROJECT_NAME} utils )
