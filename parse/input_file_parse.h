#ifndef COURSE_PROJECT_INPUT_FILE_PARSE_H
#define COURSE_PROJECT_INPUT_FILE_PARSE_H
#include "../containers/database.h"
#include "../containers/pool.h"
#include "../containers/scheme.h"
#include "../containers/collection.h"
#include "../command/command.h"
#include "../command/command_add_value.h"
#include "../command/command_delete_value.h"
#include "../command/command_find_between_value.h"
#include "../command/command_find_value.h"
#include "../command/command_update_value.h"
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>

class input_file_parse
{

public:

    input_file_parse() = default;

public:

    void parse_input_file(std::ifstream& input_file, database* data_base_parse, logger* log)
    {
        log->trace("[input_file_parse] start parse input file method");

        std::fstream output_file_with_scheme_data("output_file.txt");

        if (!output_file_with_scheme_data.is_open())
        {
            std::cout << "error with opening file" << std::endl;
        }

        std::string line;

        while (input_file >> line)
        {
            std::cout << line << std::endl;

            if (line == "ADD_POOL")
            {
                log->debug("[command_add_value] find ADD_POOL function");

                std::string pool_name;

                input_file >> pool_name;
                std::cout << line << " " << pool_name << std::endl;

                try
                {
                    data_base_parse->add_pool(pool_name);
                    log->debug("[command_add_value] the pool has been added successfully");
                }
                catch(const std::exception& error)
                {
                    log->error("[command_add_value] error with add pool");
                }
            }
            else if (line == "DELETE_POOL")
            {
                log->debug("[delete_pool] find DELETE_POOL function");

                std::string pool_name;

                input_file >> pool_name;
                std::cout << line << " " << pool_name << std::endl;

                try
                {
                    data_base_parse->delete_pool(pool_name);
                    log->debug("[delete_pool] the pool has been deleted successfully");
                }
                catch(const std::exception& error)
                {
                    log->error("[delete_pool] error with delete pool");
                }
            }
            else if (line == "ADD_SCHEME")
            {
                log->debug("[add_scheme] find ADD_SCHEME function");

                std::string pool_name;
                std::string scheme_name;

                input_file >> pool_name >> scheme_name;
                std::cout << line << " " << pool_name << " " << scheme_name << std::endl;

                try
                {
                    data_base_parse->add_scheme(pool_name, scheme_name);
                    log->debug("[add_scheme] the scheme has been added successfully");
                }
                catch(const std::exception& error)
                {
                    log->error("[add_scheme] error with add scheme");
                }
            }
            else if (line == "DELETE_SCHEME")
            {
                log->debug("[delete_scheme] find DELETE_SCHEME function");

                std::string pool_name;
                std::string scheme_name;

                input_file >> pool_name >> scheme_name;
                std::cout << line << " " << scheme_name << std::endl;

                try
                {
                    data_base_parse->delete_scheme(pool_name, scheme_name);
                    log->debug("[delete_scheme] the scheme has been deleted successfully");
                }
                catch(const std::exception& error)
                {
                    log->error("[delete_scheme] error with deleted scheme");
                }
            }
            else if (line == "ADD_COLLECTION")
            {
                log->debug("[add_collection] find ADD_COLLECTION function");

                std::string pool_name;
                std::string scheme_name;
                std::string collection_name;

                std::string allocator_type;
                std::string allocator_fit_mode;

                allocator* allocator_database;
                allocator_types type;
                allocator_with_fit_mode::fit_mode fit_mode;

                input_file >> pool_name >> scheme_name >> collection_name >> allocator_fit_mode >> allocator_type;

                log->debug(line + " " + pool_name + " " + scheme_name + " " + collection_name + " " + allocator_fit_mode + " " + allocator_type);

                if (allocator_fit_mode == "the_best_fit")
                {
                    fit_mode = allocator_with_fit_mode::fit_mode::the_best_fit;
                }
                else if (allocator_fit_mode == "the_worst_fit")
                {
                    fit_mode = allocator_with_fit_mode::fit_mode::the_worst_fit;
                }
                else if (allocator_fit_mode == "first_fit")
                {
                    fit_mode = allocator_with_fit_mode::fit_mode::first_fit;
                }
                else
                {
                    log->error("[add_collection] wrong allocator fit mode");
                }

                if (allocator_type == "sorted_list")
                {
                    type = allocator_types::SORTED_LIST;
                }
                else if (allocator_type == "global_heap")
                {
                    type = allocator_types::GLOBAL_HEAP;
                }
                else if (allocator_type == "buddie_system")
                {
                    type = allocator_types::BUDDIE_SYSTEM;
                }
                else if (allocator_type == "boundary_tags")
                {
                    type = allocator_types::BOUNDARY_TAGS;
                }
                else
                {
                    log->error("[add_collection] wrong allocator type");
                }

                try
                {
                    data_base_parse->add_collection(pool_name, scheme_name, collection_name, type, fit_mode);
                    log->debug("[add_collection] the collection has been added successfully");
                }
                catch(const std::exception& error)
                {
                    std::cout << error.what() << std::endl;
                    log->error("[add_collection] error with add collection");
                }

            }
            else if (line == "DELETE_COLLECTION")
            {
                log->debug("[delete_collection] find DELETE_COLLECTION function");

                std::string pool_name;
                std::string scheme_name;
                std::string collection_name;

                input_file >> pool_name >> scheme_name >> collection_name;
                std::cout << line << " " << pool_name << " " << scheme_name << " " << collection_name << std::endl;

                try
                {
                    data_base_parse->delete_collection(pool_name, scheme_name, collection_name);
                    log->debug("[delete_collection] the collection has been deleted successfully");
                }
                catch (const std::exception& error)
                {
                    std::cout << error.what() << std::endl;
                    log->error("[delete_collection] error with delete collection");
                }
            }
            else if (line == "ADD_VALUE")
            {
                log->trace("[add_value] find ADD_VALUE function");

//                 info about buyer: key - id_buyer, value - name, date, address, id_oder

                std::string pool_name;
                std::string scheme_name;
                std::string collection_name;

                int id_buyer;
                std::string name;
                std::string date;
                std::string address;
                int id_oder;

                input_file >> pool_name >> scheme_name >> collection_name >> id_buyer >> name >> date >> address >> id_oder;
                log->debug(pool_name + " " +  scheme_name + " " + collection_name + " " + std::to_string(id_buyer) + " " + name + " " + date + " " + address + " " + std::to_string(id_oder));

                output_file_with_scheme_data << scheme_name << " " << id_buyer << " " << name << " " << date << " " << address << " " << id_oder << std::endl;

                try
                {
//                    command* command_parse_memory_cache = new command_add_value(tdata);
                    // TODO
                    data_base_parse->add_value(pool_name, scheme_name, collection_name, id_buyer, name, date, address, id_oder);
                    std::cout << "[add_value] value has added" << std::endl;
                    log->trace("[add_value] value has added");
                }
                catch (const std::exception& error)
                {
                    std::cout << error.what() << std::endl;
                    log->error("[add_value] error with add value");
                }
            }
            else if (line == "UPDATE_VALUE")
            {
                log->debug("[update_value] find UPDATE_VALUE function");

//                 info about buyer: key - id_buyer, value - name, date, address, id_oder

                std::string pool_name;
                std::string scheme_name;
                std::string collection_name;
                int id_buyer;
                std::string name;
                std::string date;
                std::string address;
                int id_order;

                input_file >> pool_name >> scheme_name >> collection_name >> id_buyer >> name >> date >> address >> id_order;
                log->debug(pool_name + " " +  scheme_name + " " + collection_name + " " + std::to_string(id_buyer) + " " + name + " " + date + " " + address + " " + std::to_string(id_order));

//                change_value_for_update_command(scheme_name, id_buyer, name, date, address, id_order, output_file_with_scheme_data);

                try
                {
                    data_base_parse->update_value(pool_name, scheme_name, collection_name, id_buyer, name, date, address, id_order);
                    log->debug("[update_value] value has updated");
                }
                catch (const std::exception& error)
                {
                    std::cout << error.what() << std::endl;
                    log->error("[update_value] error with update value");
                }
            }
            else if (line == "FIND_VALUE")
            {
                log->debug("[find_value] find FIND_VALUE function");

//                 info about buyer: key - id_buyer, value - name, date, address, id_oder

                std::string pool_name;
                std::string scheme_name;
                std::string collection_name;
                int id_buyer;
                std::string name;
                std::string date;
                std::string address;
                int id_oder;

                input_file >> pool_name >> scheme_name >> collection_name >> id_buyer >> name >> date >> address >> id_oder;
                log->debug(pool_name + " " +  scheme_name + " " + collection_name + " " + std::to_string(id_buyer) + " " + name + " " + date + " " + address + " " + std::to_string(id_oder));

                try
                {
                    data_base_parse->obtain_value(pool_name, scheme_name, collection_name, key(id_buyer));
                    log->debug("[find_value] value has found");
                }
                catch (const std::exception& error)
                {
                    std::cout << error.what() << std::endl;
                    log->error("[find_value] error with find_value");
                }
            }
            else if (line == "DELETE_VALUE")
            {
                log->debug("[delete_value] find DELETE_VALUE function");

//                 info about buyer: key - id_buyer, value - name, date, address, id_oder

                std::string pool_name;
                std::string scheme_name;
                std::string collection_name;
                int id_buyer;
                std::string name;
                std::string date;
                std::string address;
                int id_oder;

                input_file >> pool_name >> scheme_name >> collection_name >> id_buyer >> name >> date >> address >> id_oder;
                log->debug(pool_name + " " +  scheme_name + " " + collection_name + " " + std::to_string(id_buyer) + " " + name + " " + date + " " + address + " " + std::to_string(id_oder));

                try
                {
                    data_base_parse->delete_value(pool_name, scheme_name, collection_name, id_buyer);
                    log->debug("[delete_value] value has deleted");
                }
                catch (const std::exception& error)
                {
                    std::cout << error.what() << std::endl;
                    log->error("[delete_value] error with delete value");
                }
            }
            else if (line == "FIND_BETWEEN_VALUE")
            {
                log->debug("[find_between_value] find FIND_BETWEEN_VALUE function");

//                 info about buyer: key - id_buyer, value - name, date, address, id_oder

                std::string pool_name;
                std::string scheme_name;
                std::string collection_name;
                int id_buyer;
                std::string name;
                std::string date;
                std::string address;
                int id_oder;

                input_file >> pool_name >> scheme_name >> collection_name >> id_buyer >> name >> date >> address >> id_oder;
                log->debug(pool_name + " " +  scheme_name + " " + collection_name + " " + std::to_string(id_buyer) + " " + name + " " + date + " " + address + " " + std::to_string(id_oder));

//                try
//                {
//
//                }
//                catch (const std::exception& error)
//                {
//                    std::cout << error.what() << std::endl;
//                    log->error("[find_between_value] error with find between value");
//                }
            }
            else if (line == "FIND_VALUE_S_I")
            {
                log->debug("[find_value_s_i] find FIND_VALUE_S_I function");

                std::string pool_name;
                std::string scheme_name;

                input_file >> pool_name >> scheme_name;
                std::cout << pool_name << " " << scheme_name << std::endl;

                std::streampos original_position = output_file_with_scheme_data.tellg();

                std::string current_scheme_name;
                int current_id_buyer;
                std::string current_name;
                std::string current_date;
                std::string current_address;
                int current_id_order;

                bool found = false;

                output_file_with_scheme_data.seekg(0);

                while (output_file_with_scheme_data >> current_scheme_name >> current_id_buyer >> current_name >> current_date >> current_address >> current_id_order)
                {
                    if (current_scheme_name == scheme_name)
                    {
                        found = true;
                        std::cout << current_scheme_name << " " << scheme_name << " " << current_id_buyer << " " << current_name << " " << current_address << " " << current_date << " " << current_id_order << std::endl;
                    }
                }

                output_file_with_scheme_data.clear();
                output_file_with_scheme_data.seekg(original_position);

                if (!found)
                {
                    std::cout << "not found" << std::endl;
                }
            }
        }
    }

public:

    void change_value_for_update_command(const std::string& scheme_name, int id_buyer,
                                         const std::string& name, const std::string& date,
                                         const std::string& address, int id_order,
                                         std::fstream& output_file)
    {
        std::vector<std::string> lines;
        std::string line;

        std::string current_scheme_name;
        int current_id_buyer;
        std::string current_name;
        std::string current_date;
        std::string current_address;
        int current_id_order;

        std::streampos original_position;

        while (output_file >> current_scheme_name >> current_id_buyer >> current_name >> current_date >> current_address >> current_id_order)
        {
            original_position = output_file.tellg();
            std::cout << current_scheme_name << current_id_buyer << current_name << current_date << current_address << current_id_order << std::endl;

            if (current_scheme_name == scheme_name && current_id_buyer == id_buyer)
            {
                current_name = name;
                current_date = date;
                current_address = address;
                current_id_order = id_order;
            }
            else
            {
                break;
            }
        }

//        line = current_scheme_name + " " + std::to_string(current_id_buyer) + " " + current_name + " " + current_date + " " + current_address + " " + std::to_string(current_id_order) + "\n";
//        lines.push_back(line);
//
//        output_file.clear();
//        output_file.seekp(original_position);
//
//        for (const auto& l : lines)
//        {
//            output_file << l;
//        }
    }


public:

    ~input_file_parse() = default;

    input_file_parse(input_file_parse const &other) = delete;

    input_file_parse(input_file_parse const &&other) = delete;

    input_file_parse& operator=(input_file_parse const &other) = delete;

    input_file_parse& operator=(input_file_parse const &&other) = delete;
};


#endif //COURSE_PROJECT_INPUT_FILE_PARSE_H
