#include <iostream>
#include "containers/database.h"
#include "parse/input_file_parse.h"
#include "logger/client_logger_builder.h"
#include <cstring>

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cout << "error with number of arguments" << std::endl;
        return 1;
    }

    size_t t = 3;
    database* db = new database(t);

    logger_builder* builder = new client_logger_builder();

    logger *constructed_logger = builder
            ->add_console_stream(logger::severity::information)
            ->add_console_stream(logger::severity::debug)
            ->add_console_stream(logger::severity::error)
            ->add_file_stream("log.txt", logger::severity::information)
            ->add_file_stream("log.txt", logger::severity::debug)
            ->add_file_stream("log.txt", logger::severity::error)
            ->build();

    std::string operating_mode = argv[2];
    enums::mode operating_mode_enum;

    if (operating_mode == "0")
    {
        operating_mode_enum = enums::mode::in_memory_cache;
        constructed_logger->trace("operating mode is memory cache");
        std::cout << "operating mode is memory cache" << std::endl;
    }
    else if (operating_mode == "1")
    {
        operating_mode_enum = enums::mode::file_system;
        constructed_logger->trace("operating mode is file_system");
        std::cout << "operating mode is file_system" << std::endl;
    }
    else
    {
        constructed_logger->error("wrong mode operating");
        std::cout << "wrong mode operating" << std::endl;
        return 1;
    }

//    std::cout << "Dialog with user has started\nPlease choose an action:\n"
//                 "1) Enter commands in a file - please enter 'file'\n"
//                 "2) Enter commands in console - please enter 'console'\n"
//                 "3) Exit - please enter exit" << std::endl;
//
//    char* command;
//
//    std::cin >> command;

//    while(true)
//    {
//        if (strcmp(command, "file") == 0)
//        {
    std::string file_path = argv[1];
    if (!(db->validate_input_file_path(file_path)))
    {
        std::cerr << "error with file" << std::endl;
        return 1;
    }

    std::ifstream input_file(argv[1]);

    if (!input_file.is_open())
    {
        std::cerr << "error with opening file" << std::endl;
        return 1;
    }

    // 0 - memory cache, 1 - file system

    input_file_parse parse;

    if (operating_mode_enum == db->get_mode(enums::mode::file_system))
    {
        constructed_logger->trace("get file system operating mode");
        parse.parse_input_file_for_file_system(input_file, db, constructed_logger);
    }
    else
    {
        constructed_logger->trace("get memory cache operating mode");
        parse.parse_input_file(input_file, db, constructed_logger);
    }
//        }
//        else if (command == "console")
//        {
//
//        }
//        else if (command == "exit")
//        {
//
//        }
//        else
//        {
//            std::cout << "you enter wrong command" << std::endl;
//            break;
//        }
//    }

    delete constructed_logger;
    delete db;


    return 0;
}