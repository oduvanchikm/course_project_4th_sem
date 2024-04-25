cmake_minimum_required(VERSION 3.28)
project(course_project)

set(CMAKE_CXX_STANDARD 17)

include_directories(allocators)

add_executable(course_project
#        allocators/allocator.cpp
#        allocators/allocator_buddies_system.cpp
        include/associative_container.h
        include/search_tree.h
        include/b_tree.h
        database.h
        pool.h
        scheme.h
        collection.h
        main.cpp)
