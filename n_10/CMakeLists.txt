cmake_minimum_required(VERSION 3.28)
project(n_10 C)

set(CMAKE_C_STANDARD 11)

add_executable(n_10
        check/check.c
        configuration/configuration.c
        gets/gets.c
        interpreter/interpreter.c
        operations/operations.c
        string/string.c
        variables/variables.c
        main.c)
