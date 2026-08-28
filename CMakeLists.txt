cmake_minimum_required(VERSION 3.15)

# compiler
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_C_COMPILER "clang")

#set(CMAKE_CXX_COMPILER "g++")
#set(CMAKE_C_COMPILER "gcc")

# project
set(PROJECT_NAME "app")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PROJECT_VERSION "1.0.0")
project(${PROJECT_NAME} VERSION ${PROJECT_VERSION})

#####################################################################
# test project
#####################################################################

set(EXE_NAME "app")
set(EXE_SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(EXE_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include")

file(GLOB_RECURSE EXE_SOURCE_LIST "${EXE_SOURCE_PATH}/*")


add_executable(${EXE_NAME} ${EXE_SOURCE_LIST})
target_include_directories(${EXE_NAME} PRIVATE "${EXE_INCLUDE_PATH}")



target_link_libraries(${EXE_NAME} PRIVATE "raylib")
target_link_libraries(${EXE_NAME} PRIVATE "LDtkLoader")
target_link_libraries(${EXE_NAME} PRIVATE "GL")
target_link_libraries(${EXE_NAME} PRIVATE "m")
target_link_libraries(${EXE_NAME} PRIVATE "pthread")
target_link_libraries(${EXE_NAME} PRIVATE "dl")
target_link_libraries(${EXE_NAME} PRIVATE "rt")
target_link_libraries(${EXE_NAME} PRIVATE "X11")

