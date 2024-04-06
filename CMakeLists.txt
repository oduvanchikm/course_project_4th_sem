cmake_minimum_required(VERSION 3.28)
project(course_project)

set(CMAKE_CXX_STANDARD 14)

include_directories(allocators)

add_executable(course_project
        allocators/allocator.cpp
        allocators/allocator_buddies_system.cpp)
