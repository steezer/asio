cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_BUILD_TYPE Release)

project(server VERSION 1.0.0)

aux_source_directory(. SRCS)
add_executable(server ${SRCS})