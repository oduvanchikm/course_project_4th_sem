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
        tree/associative_container.h
        tree/search_tree.h
        tree/b_tree.h
        tree/binary_search_tree.h
        containers/database.h
        containers/pool.h
        containers/scheme.h
        containers/collection.h
        main.cpp
        containers/wb.h
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
        dialog/dialog_file_system.h
        validate/validate_parameters.h
        parse/file_system_parse.h
        dialog/dialog_memory_cache.h
        containers/key_values.h
        command/command.h
        command/command_add_value.h
        command/command_find_value.h
        command/command_update_value.h
        command/command_update_value.h
        command/command_find_between_value.h
        command/command_dispose_value.h
        command/command_dispose_value.h
)
