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
        containers/database.h
        containers/pool.h
        containers/scheme.h
        containers/collection.h
        main.cpp
        parse/wb.h
        comparator/comparer.h
        parse/input_file_parse.h
        logger/client_logger_builder.h
        logger/client_logger.h
        logger/client_logger_builder.cpp
        logger/client_logger.cpp
        allocators/allocator_guardant.cpp
        logger/logger_builder.cpp
        enums/allocator_types.h
        allocators/allocator_with_fit_mode.h
        logger/logger.h
        logger/logger.h
        logger/logger.h
        logger/logger.h
        enums/enums.h
        allocators/allocator_sorted_list.cpp
        allocators/allocator_global_heap.cpp
        allocators/allocator_buddies_system.cpp
        allocators/allocator_boundary_tags.cpp
        dialog/dialog.h
)
