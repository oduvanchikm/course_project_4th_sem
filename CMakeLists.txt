cmake_minimum_required(VERSION 3.28)
project(course_project)

set(CMAKE_CXX_STANDARD 17)

include_directories(allocators)

add_executable(course_project
        allocators/allocator.h
        allocators/allocator_guardant.h
        logger/logger.h
        logger/logger_builder.h
        logger/logger_guardant.h
        logger/logger.cpp
        logger/logger_builder.cpp
        logger/logger_guardant.cpp
        #        allocators/allocator_buddies_system.cpp
        include/associative_container.h
        include/search_tree.h
        include/b_tree.h
        include/binary_search_tree.h
        database.h
        pool.h
        scheme.h
        collection.h
        main.cpp
        wb.h
        comparer.h
        input_file_parse.h
        logger/client_logger_builder.h
        logger/client_logger.h
        logger/client_logger_builder.cpp
        logger/client_logger.cpp
        allocators/allocator_guardant.cpp
        logger/logger_builder.cpp)
