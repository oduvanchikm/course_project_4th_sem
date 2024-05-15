#include <iostream>
#include "containers/database.h"
#include "parse/input_file_parse.h"
#include "logger/client_logger_builder.h"
#include <cstring>
#include "dialog/dialog.h"
#include <string>
#include "validate/validate_parameters.h"

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

    std::cout << "Dialog with user has started\nPlease choose an action:\n"
                 "1) Enter commands in a file - please enter 'file'\n"
                 "2) Enter commands in console - please enter 'console'\n"
                 "3) Exit - please enter exit" << std::endl;

    std::string command;

    std::cin >> command;

    if (command == "file")
    {
        size_t t = 3;
        database* db = new database(t);

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

        delete db;
    }
    else if (command == "console")
    {
        std::string t_string;
        std::cout << "Please enter t parameter:" << std::endl;
        std::cin >> t_string;

        bool result = validate_parameters::validate_t(t_string);

        while (!result)
        {
            std::cout << "Please enter t parameter:" << std::endl;
            std::cin >> t_string;

            result = validate_parameters::validate_t(t_string);

            if (result)
            {
                std::cout << "Your t parameter: " << t_string << std::endl;
            }
            else
            {
                std::cout << "You entered a wrong t parameter. Please try again." << std::endl;
            }
        }

        size_t t = std::stoul(t_string);

        database* db = new database(t);

        std::cout << "Please choose an action:\n"
                     "1) Data is stored in memory cache - enter 0\n"
                     "2) Data is stored in file system - enter 1\n"
                     "3) Exit - please enter exit" << std::endl;

        std::string command_file_or_memory;

        std::cin >> command_file_or_memory;

        bool new_parameter = validate_parameters::validate_file_system_or_memory_cache(command_file_or_memory);

        while (!new_parameter)
        {
            std::cout << "Please choose an action:\n"
                         "1) Data is stored in memory cache - enter 0\n"
                         "2) Data is stored in file system - enter 1\n"
                         "3) Exit - please enter exit" << std::endl;

            std::cin >> command_file_or_memory;

            new_parameter = validate_parameters::validate_file_system_or_memory_cache(command_file_or_memory);

            if (new_parameter)
            {
                std::cout << "Your action: " << t_string << std::endl;
            }
            else
            {
                std::cout << "You entered a wrong action. Please try again." << std::endl;
            }
        }

        if (command_file_or_memory == "1")
        {
            dialog dialog_with_user;
        }
        else
        {
            dialog dialog_with_user;
        }

        delete db;
    }
    else if (command == "exit")
    {
        std::cout << "you enter exit" << std::endl;
    }
    else
    {
        std::cout << "you enter wrong command" << std::endl;
    }

    delete constructed_logger;

    return 0;
}