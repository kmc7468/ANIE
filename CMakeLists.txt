cmake_minimum_required(VERSION 3.8.0)
project(ANIE CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(INCLUDE_DIR "./include")
set(SOURCE_DIR "./src")
set(OUTPUT_DIR "./bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

set(DYNAMIC_LINKING OFF CACHE BOOL "")
set(ARITHMETIC_TYPE "double" CACHE STRING "")

find_package(OpenCL REQUIRED)
include_directories(${OpenCL_INCLUDE_DIRS})

include_directories(${INCLUDE_DIR})
file(GLOB_RECURSE SOURCE_LIST ${SOURCE_DIR}/*.cpp)

add_definitions(-D__STDC_CONSTANT_MACROS)
add_definitions(-D__STDC_LIMIT_MACROS)

add_definitions(-DANIE_INTERNAL)
add_definitions(-DANIE_ARITHMETIC_TYPE=${ARITHMETIC_TYPE})

if(DYNAMIC_LINKING)
	add_definitions(-DANIE_DYNAMIC)
	add_library(${PROJECT_NAME} SHARED ${SOURCE_LIST})
else()
	add_library(${PROJECT_NAME} STATIC ${SOURCE_LIST})
endif()
target_link_libraries(${PROJECT_NAME} ${OpenCL_LIBRARIES})

install(DIRECTORY ${INCLUDE_DIR}/anie DESTINATION include)
install(TARGETS ${PROJECT_NAME} DESTINATION lib)