#include <iostream>
#include "containers/database.h"
#include "parse/input_file_parse.h"
#include "logger/client_logger_builder.h"
#include <cstring>
#include <string>
#include "parse/file_system_parse.h"

int main(int argc, char* argv[])
{
    if (argc != 3 && argc != 2)
    {
        std::cout << "error with number of arguments" << std::endl;
        return 1;
    }

    logger_builder* builder = new client_logger_builder();

    logger *constructed_logger = builder
            ->add_console_stream(logger::severity::information)
            ->add_console_stream(logger::severity::debug)
            ->add_console_stream(logger::severity::error)
            ->add_console_stream(logger::severity::trace)
            ->add_file_stream("log.txt", logger::severity::information)
            ->add_file_stream("log.txt", logger::severity::debug)
            ->add_file_stream("log.txt", logger::severity::error)
            ->add_file_stream("log.txt", logger::severity::trace)
            ->build();


    size_t t = 3;
    std::string operating_mode = argv[1];
    database *db = database::get_instance(t);

    if (operating_mode == "0")
    {
        db->set_mode(enums::mode::in_memory_cache);
        if (constructed_logger != nullptr)
        {
            constructed_logger->trace("operating mode is memory cache");
        }
    }
    else if (operating_mode == "1")
    {
        db->set_mode(enums::mode::file_system);
        if (constructed_logger != nullptr)
        {
            constructed_logger->trace("operating mode is file_system");
        }
    }
    else
    {
        if (constructed_logger != nullptr)
        {
            constructed_logger->error("wrong mode operating");
        }
        return 1;
    }

    if (argc == 3)
    {
        std::string file_path = argv[2];

        if (!(db->validate_input_file_path(file_path)))
        {
            std::cerr << "error with file" << std::endl;
            delete constructed_logger;
            delete db;
            delete builder;
            return 1;
        }

        std::ifstream input_file(argv[2]);

        if (!input_file.is_open())
        {
            std::cerr << "error with opening file" << std::endl;
            delete constructed_logger;
            delete db;
            delete builder;
            return 1;
        }

        std::string command_string;
//        logger_guardant *logger = nullptr;

        if (db->get_mode() == enums::mode::file_system)
        {
            file_system_parse file_system;
            file_system.parse_input_file_for_file_system(input_file, db, constructed_logger);
        }
        else
        {
            while (std::getline(input_file, command_string))
            {

            }
        }

        input_file.close();
    }
    else
    {
        std::string command_string;
        while (std::getline(std::cin, command_string))
        {

        }
    }

    delete constructed_logger;
    delete db;
    delete builder;

    return 0;
}