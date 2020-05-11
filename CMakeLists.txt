cmake_minimum_required (VERSION 3.17)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED YES)

project (ofs)

include_directories(src)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

find_package(Freetype REQUIRED)
find_package(fmt REQUIRED)

add_subdirectory(src)
