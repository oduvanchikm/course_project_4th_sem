#include <iostream>
#include "containers/database.h"
#include "logger/client_logger_builder.h"
#include <cstring>
#include <string>
#include "command/command_add_pool.h"
#include "command/command_delete_pool.h"
#include "command/command_add_scheme.h"
#include "command/command_delete_scheme.h"
#include "command/command_add_collection.h"
#include "command/command_delete_collection.h"
#include "command/command_add_value.h"
#include "command/command_delete_value.h"
#include "command/command_update_value.h"
#include "command/command_find_value.h"
#include "command/command_find_between_value.h"
#include "command/command_find_time_value.h"

int main(int argc, char *argv[])
{
    if (argc != 3 && argc != 1)
    {
        std::cout << "error with number of arguments" << std::endl;
        return 1;
    }

    logger_singleton::get_instance()->get_logger()->log("start work database", logger::severity::trace);

    size_t t = 3;
    std::string operating_mode = argv[1];
    database::get_instance(t)->set_t(t);
    database *db = database::get_instance(t);

    request_handler_with_command_chain _chain;
    _chain
            .add_handler(new command_add_pool())
            .add_handler(new command_add_scheme())
            .add_handler(new command_add_collection())
            .add_handler(new command_add_value())
            .add_handler(new command_update_value())
            .add_handler(new command_find_value())
            .add_handler(new command_find_between_value())
            .add_handler(new command_find_time_value())
            .add_handler(new command_delete_value())
            .add_handler(new command_delete_collection())
            .add_handler(new command_delete_scheme())
            .add_handler(new command_delete_pool());

    if (operating_mode == "0")
    {
        db->set_mode(enums::mode::in_memory_cache);
        logger_singleton::get_instance()->get_logger()->log("in memory cache mode", logger::severity::trace);
    }
    else if (operating_mode == "1")
    {
        db->set_mode(enums::mode::file_system);
        logger_singleton::get_instance()->get_logger()->log("file system mode", logger::severity::trace);
    }
    else
    {
        logger_singleton::get_instance()->get_logger()->log("wrong mode operating", logger::severity::trace);
        return 1;
    }

    if (argc == 3)
    {
        std::string file_path = argv[2];
        std::cout << file_path << std::endl;

        if (!(db->validate_input_file_path(file_path)))
        {
            std::cerr << "error with file" << std::endl;
            delete db;
            return 1;
        }

        std::ifstream input_file(argv[2]);

        if (!input_file.is_open())
        {
            std::cerr << "error with opening file" << std::endl;
            delete db;
            return 1;
        }

        std::string command_string;

        if (db->get_mode() == enums::mode::file_system)
        {
            while (std::getline(input_file, command_string))
            {
                std::cout << command_string << std::endl;
                std::int64_t date_time_activity_started;

                if (!_chain.handle(command_string, date_time_activity_started))
                {
                    throw std::logic_error("wrong command or smth goes bad");
                }
            }
        }
        else
        {
            while (std::getline(input_file, command_string))
            {
                std::cout << command_string << std::endl;
                std::int64_t date_time_activity_started;

                if (!_chain.handle(command_string, date_time_activity_started))
                {
                    throw std::logic_error("wrong command or smth goes bad");
                }
            }
        }

        input_file.close();
    }
    else
    {
        std::string command_string;
        std::cout << "please enter a command: " << std::endl;

        while (std::getline(std::cin, command_string))
        {
            std::cout << command_string << std::endl;
            std::int64_t date_time_activity_started;

            if (!_chain.handle(command_string, date_time_activity_started))
            {
                throw std::logic_error("wrong command or smth goes bad");
            }
        }
    }

    std::string word;
    do
    {
        std::cout << "Do you want to save the data? Please write 'yes' or 'no':" << std::endl;
        std::cin >> word;

        if (word == "no")
        {
            std::cout << "Data will not be save" << std::endl;
            file_save file;
            file.clean_file();
        }
        else if (word == "yes" )
        {
            std::cout << "Data will be save" << std::endl;
        }
        else if (word != "yes" && word != "no")
        {
            std::cout << "You entered an invalid answer. Please try again." << std::endl;
        }

    } while (word != "yes" && word != "no");

    return 0;
}