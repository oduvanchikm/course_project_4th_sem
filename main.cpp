#include <iostream>
#include "containers/database.h"
#include "logger/client_logger_builder.h"
#include <cstring>
#include <string>
//#include "parse/input_file_parse.h"
//#include "parse/file_system_parse.h"
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
#include "../logger/logger_singleton.h"
#include "command/command_find_between_value.h"

int main(int argc, char *argv[]) {
    if (argc != 3 && argc != 2) {
        std::cout << "error with number of arguments" << std::endl;
        return 1;
    }

    logger_singleton::get_instance()->get_logger()->log("start work database", logger::severity::trace);

    size_t t = 3;
    std::string operating_mode = argv[1];
    database *db = database::get_instance(t);

//    chain_of_responsibility _chain(constructed_logger);
    request_handler_with_command_chain _chain;
    _chain
            .add_handler(new command_add_pool())
            .add_handler(new command_add_scheme())
            .add_handler(new command_add_collection())
            .add_handler(new command_add_value())
            .add_handler(new command_update_value())
            .add_handler(new command_find_value())
            .add_handler(new command_find_between_value())
            .add_handler(new command_delete_value())
            .add_handler(new command_delete_collection())
            .add_handler(new command_delete_scheme())
            .add_handler(new command_delete_pool());

    if (operating_mode == "0") {
        db->set_mode(enums::mode::in_memory_cache);
        logger_singleton::get_instance()->get_logger()->log("in memory cache mode", logger::severity::trace);
    } else if (operating_mode == "1") {
        db->set_mode(enums::mode::file_system);
        logger_singleton::get_instance()->get_logger()->log("file system mode", logger::severity::trace);
    } else {
        logger_singleton::get_instance()->get_logger()->log("wrong mode operating", logger::severity::trace);
        return 1;
    }

    logger *logger = nullptr;

    if (argc == 3) {
        std::string file_path = argv[2];
        std::cout << file_path << std::endl;

        if (!(db->validate_input_file_path(file_path))) {
            std::cerr << "error with file" << std::endl;
            delete db;
            return 1;
        }

        std::ifstream input_file(argv[2]);

        if (!input_file.is_open()) {
            std::cerr << "error with opening file" << std::endl;
            delete db;
            return 1;
        }

        std::string command_string;

        if (db->get_mode() == enums::mode::file_system) {
            while (std::getline(input_file, command_string)) {
                std::cout << command_string << std::endl;
                if (!_chain.handle(command_string)) {
                    throw std::logic_error("wrong command or smth goes bad");
                }
            }
        } else {
//            input_file_parse file;
//            file.parse_input_file(input_file, db, logger);
            while (std::getline(input_file, command_string)) {
                std::cout << command_string << std::endl;
                if (!_chain.handle(command_string)) {
                    throw std::logic_error("wrong command or smth goes bad");
                }
            }
        }
        input_file.close();
    } else {
        std::string command_string;
        while (std::getline(std::cin, command_string)) {
//            if (db->get_mode() == enums::mode::file_system)
//            {
//                file_system_parse file_system;
//                file_system.parse_input_file_for_file_system(command_string, db, constructed_logger);
//            }
//            else
//            {
//                while (std::getline(command_string, command_string))
//                {
//                    db->
//                }
//            }
        }
    }


    delete db;
    return 0;
}