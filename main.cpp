#include <iostream>
#include "containers/database.h"
#include "parse/input_file_parse.h"
#include "logger/client_logger_builder.h"
#include <cstring>
#include <string>
//#include "dialog/dialog_file_system.h"
#include "validate/validate_parameters.h"
#include "parse/file_system_parse.h"

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cout << "error with number of arguments" << std::endl;
        return 1;
    }

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

    int flag = 1;

//    while(flag)
//    {
//        std::cout << "Dialog with user has started\nPlease choose an action:\n"
//                     "1) Enter commands in a file - please enter 'file'\n"
//                     "2) Enter commands in console - please enter 'console'\n"
//                     "3) Exit - please enter exit" << std::endl;
//
//        std::string command;
//
//        std::cin >> command;
//
//        if (command == "file")
//        {
            size_t t = 3;
            database *db = new database(t);

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

            if (operating_mode_enum == db->get_mode(enums::mode::file_system))
            {
                file_system_parse file_system;
                constructed_logger->trace("get file system operating mode");
                file_system.parse_input_file_for_file_system(input_file, db, constructed_logger);
            }
            else
            {
                input_file_parse parse;
                constructed_logger->trace("get memory cache operating mode");
                parse.parse_input_file(input_file, db, constructed_logger);
            }

            delete db;
//        }
//        else if (command == "console")
//        {
//            bool console = 1;
//            std::string t_string;
//            std::cout << "Please enter t parameter: " << std::endl;
//            std::cin >> t_string;
//
//            bool flag2 = validate_parameters::validate_t(t_string);
//
//            if (!flag2)
//            {
//                while (!flag2)
//                {
//                    std::cout << "You entered the wrong parameter. Please enter another one: ";
//                    std::cin >> t_string;
//
//                    flag2 = validate_parameters::validate_t(t_string);
//
//                    if (flag2)
//                    {
//                        break;
//                    }
//                }
//            }
//
//            int t = std::stoi(t_string);
//
//            database *db = new database(t);
//
//            std::string file_path = argv[1];
//
//            if (!(db->validate_input_file_path(file_path)))
//            {
//                std::cerr << "Error with file" << std::endl;
//                return 1;
//            }
//
//            std::ifstream input_file(argv[1]);
//
//            if (!input_file.is_open())
//            {
//                std::cerr << "Error with opening file" << std::endl;
//                return 1;
//            }
//
//            // 0 - memory cache, 1 - file system
//
//            std::cout << "Please choose an action:\n"
//                         "1) Data is stored in memory cache - enter 0\n"
//                         "2) Data is stored in file system - enter 1\n"
//                         "3) Exit - please enter exit" << std::endl;
//
//            std::string command_file_or_memory;
//
//            std::cin >> command_file_or_memory;
//
//            bool flag3 = validate_parameters::validate_file_system_or_memory_cache(command_file_or_memory);
//
//            if (!flag3)
//            {
//                while (!flag3)
//                {
//                    std::cout << "You entered the wrong parameter. Please enter another one: ";
//                    std::cin >> command_file_or_memory;
//
//                    flag3 = validate_parameters::validate_file_system_or_memory_cache(command_file_or_memory);
//
//                    if (flag3)
//                    {
//                        break;
//                    }
//                }
//            }

//            if (command_file_or_memory == "1")
//            {
//                dialog_file_system dialog_with_user;
//                constructed_logger->trace("get file system operating mode");
//                dialog_with_user.parse_input_file_for_file_system(input_file, db, constructed_logger);
//            }
//            else
//            {
//                dialog_file_system dialog_with_user;
//                constructed_logger->trace("get memory cache operating mode");
////                dialog_with_user.parse_input_file(input_file, db, constructed_logger, console);
//            }

//            delete db;
//        }
//        else if (command == "exit")
//        {
//            std::cout << "You enter exit" << std::endl;
//            flag = 0;
//        }
//        else
//        {
//            std::cout << "You enter wrong command\nPlease try again" << std::endl;
//        }
//    }

    delete constructed_logger;

    return 0;
}