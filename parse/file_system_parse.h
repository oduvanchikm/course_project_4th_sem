#ifndef COURSE_PROJECT_FILE_SYSTEM_PARSE_H
#define COURSE_PROJECT_FILE_SYSTEM_PARSE_H
#include "../containers/database.h"
#include "../containers/pool.h"
#include "../containers/scheme.h"
#include "../containers/collection.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>
#include <vector>
#include "../logger/logger_guardant.h"
#include "../command/command_add_pool.h"
#include "../command/command_delete_pool.h"
#include "../command/command_add_scheme.h"
#include "../command/command_delete_scheme.h"
#include "../command/command_add_collection.h"
#include "../command/command_delete_collection.h"
#include "../command/command.h"

class file_system_parse
{

public:

    file_system_parse() = default;

public:

    std::tuple<long, long, std::string, std::string, std::string, int> serialization(std::ifstream& input_file,
                                        logger* logger)
    {
        logger->trace("[serialization] start serialization");

        std::tuple<long, long, std::string, std::string, std::string, int> result;

        if (!input_file.is_open())
        {
            logger->error("[serialization] error with opening file");
        }

        std::string name;
        std::string date;
        std::string address;
        int id_oder;

        std::streampos position = input_file.tellg();
        input_file >> name >> date >> address;
        std::cout << name << " " << date << " " << address << std::endl;

        std::streampos new_position = input_file.tellg();

        input_file >> id_oder;
        std::cout << id_oder << std::endl;

        long size_id_oder = (std::to_string(id_oder)).size();

        std::cout << size_id_oder << std::endl;

        long data_size = static_cast<long>(new_position - position) + size_id_oder;

        std::get<0>(result) = position;
        std::get<1>(result) = data_size;
        std::get<2>(result) = name;
        std::get<3>(result) = date;
        std::get<4>(result) = address;
        std::get<5>(result) = id_oder;

        return result;
    }

    value_in_memory_cache deserialization(std::ifstream& input_file, long position, long size, logger* logger)
    {
        logger->trace("[deserialization] start deserialization");

        input_file.seekg(position);

        char* buffer = new char[size];
        input_file.read(buffer, size);

        std::string serialized_data(buffer, size);
        std::istringstream iss(serialized_data);
        std::string name, date, address, id_oder;
        iss >> name >> date >> address >> id_oder;

        delete[] buffer;

        value_in_memory_cache value_memory;

        value_memory._name_buyer = name;
        value_memory._date = date;
        value_memory._address = address;
        value_memory._id_order = std::stoi(id_oder);

        return value_memory;
    }

    void parse_input_file_for_file_system(std::ifstream& input_file, database* data_base_parse, logger* constructed_logger)
    {
        if (constructed_logger != nullptr)
        {
            constructed_logger->trace("[input_file_parse] start parse input file method");
        }

        std::string base_directory_name = "data_base";

        if (!std::filesystem::exists(base_directory_name))
        {
            try
            {
                std::filesystem::create_directory(base_directory_name);
                constructed_logger->trace("directory " + base_directory_name + " has created");
            }
            catch (const std::exception& e)
            {
                constructed_logger->error("error creating the directory");
                std::cerr << "error creating the directory" << e.what() << std::endl;
            }
        }

        std::string line;

        while (input_file >> line)
        {
            std::cout << line << std::endl;

            if (line == "ADD_POOL")
            {
                if (constructed_logger != nullptr)
                {
                    constructed_logger->trace("[command_add_value] find command_add_value");
                }

                std::string pool_name;
                input_file >> pool_name;

                if (constructed_logger != nullptr)
                {
                    constructed_logger->information("pool name: " + pool_name);
                }

                std::string pool_directory_name = base_directory_name + "/" + pool_name;

                if (!std::filesystem::exists(pool_directory_name))
                {
                    try
                    {
                        std::filesystem::create_directory(pool_directory_name);
                        if (constructed_logger != nullptr)
                        {
                            constructed_logger->trace(
                                    "[command_add_value] directory " + pool_directory_name + " has created");
                        }
                    }
                    catch (const std::exception &e)
                    {
                        if (constructed_logger != nullptr)
                        {
                            constructed_logger->error(
                                    "[command_add_value] error creating the directory " + pool_directory_name);
                        }
                        std::cerr << "[command_add_value] error creating the directory " + pool_directory_name
                                  << e.what() << std::endl;
                    }
                }

                command* new_command = new command_add_pool(pool_name, constructed_logger);
                new_command->execute(line);
            }
            else if (line == "DELETE_POOL")
            {
                constructed_logger->trace("[delete_pool] find delete_pool");

                std::string pool_name;
                input_file >> pool_name;

                constructed_logger->information("pool name: " + pool_name);

                std::string pool_directory_name = base_directory_name + "/" + pool_name;

                if (std::filesystem::exists(pool_directory_name))
                {
                    try
                    {
                        std::filesystem::remove_all(pool_directory_name);
                        constructed_logger->trace("directory " + pool_directory_name + " has deleted");
                    }
                    catch (const std::exception &e)
                    {
                        constructed_logger->error("error deleting the directory " + pool_directory_name);
                        std::cerr << "error deleting the directory " + pool_directory_name << e.what() << std::endl;
                    }
                }

                command* new_command = new command_delete_pool(pool_name, constructed_logger);
                new_command->execute(line);
            }
            else if (line == "ADD_SCHEME")
            {
                constructed_logger->trace("[add_scheme] find add_scheme");

                std::string pool_name;
                std::string scheme_name;
                input_file >> pool_name >> scheme_name;

                constructed_logger->information("pool name: " + pool_name + ", scheme_name: " + scheme_name);

                std::string scheme_directory_name = base_directory_name + "/" + pool_name + "/" + scheme_name;

                if (!std::filesystem::exists(scheme_directory_name))
                {
                    try
                    {
                        std::filesystem::create_directory(scheme_directory_name);
                        constructed_logger->trace("directory " + scheme_directory_name + " has created");
                    }
                    catch (const std::exception& e)
                    {
                        constructed_logger->error("error creating the directory " + scheme_directory_name);
                        std::cerr << "error creating the directory " + scheme_directory_name << e.what() << std::endl;
                    }
                }

                command* new_command = new command_add_scheme(pool_name, scheme_name, constructed_logger);
                new_command->execute(line);
            }
            else if (line == "DELETE_SCHEME")
            {
                constructed_logger->trace("[delete_scheme] find delete_scheme");

                std::string pool_name;
                std::string scheme_name;
                input_file >> pool_name >> scheme_name;

                constructed_logger->information("pool_name: " + pool_name + " scheme_name: " + scheme_name);

                std::string scheme_directory_name = base_directory_name + "/" + pool_name + "/" + scheme_name;

                if (std::filesystem::exists(scheme_directory_name))
                {
                    try
                    {
                        std::filesystem::remove_all(scheme_directory_name);
                        constructed_logger->trace("directory " + scheme_directory_name + " has deleted");
                    }
                    catch (const std::exception& e)
                    {
                        constructed_logger->error("error deleting the directory " + scheme_directory_name);
                        std::cerr << "error deleting the directory " + scheme_directory_name << e.what() << std::endl;
                    }
                }

                command* new_command = new command_delete_scheme(pool_name, scheme_name, constructed_logger);
                new_command->execute(line);
            }
            else if (line == "ADD_COLLECTION")
            {
                constructed_logger->trace("[add_collection] find add_collection");

                std::string pool_name;
                std::string scheme_name;
                std::string collection_name;

                std::string allocator_type;
                std::string allocator_fit_mode;

                allocator* allocator_database;
                allocator_types type;
                allocator_with_fit_mode::fit_mode fit_mode;

                input_file >> pool_name >> scheme_name >> collection_name >> allocator_fit_mode >> allocator_type;

                constructed_logger->information(line + " " + pool_name + " " + scheme_name + " " + collection_name + " " + allocator_fit_mode + " " + allocator_type);

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
                    constructed_logger->error("[add_collection] wrong allocator fit mode");
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
                    constructed_logger->error("[add_collection] wrong allocator type");
                }

                std::string collection_directory_name = base_directory_name + "/" + pool_name + "/" + scheme_name + "/" + collection_name;

                if (!std::filesystem::exists(collection_directory_name))
                {
                    try
                    {
                        std::filesystem::create_directory(collection_directory_name);
                        constructed_logger->trace("directory " + collection_directory_name + " has created");
                    }
                    catch (const std::exception& e)
                    {
                        constructed_logger->error("error creating the directory " + collection_directory_name);
                        std::cerr << "error creating the directory " + collection_directory_name << e.what() << std::endl;
                    }
                }

                command* new_command = new command_add_collection(pool_name, scheme_name,
                                                              collection_name, type, fit_mode, constructed_logger);
                new_command->execute(line);
            }
            else if (line == "DELETE_COLLECTION")
            {
                constructed_logger->trace("[delete_collection] find delete_collection");

                std::string pool_name;
                std::string scheme_name;
                std::string collection_name;

                input_file >> pool_name >> scheme_name >> collection_name;

                constructed_logger->information("pool name: " + pool_name + " scheme_name: " + scheme_name + " collection_name: " + collection_name);

                std::string collection_directory_name = base_directory_name + "/" + pool_name + "/" + scheme_name + "/" + collection_name;

                if (std::filesystem::exists(collection_directory_name))
                {
                    try
                    {
                        std::filesystem::remove_all(collection_directory_name);
                        constructed_logger->trace("directory " + collection_directory_name + " has deleted");
                    }
                    catch (const std::exception& e)
                    {
                        constructed_logger->error("error deleting the directory " + collection_directory_name);
                        std::cerr << "error deleting the directory " + collection_directory_name << e.what() << std::endl;
                    }
                }

                command* new_command = new command_delete_collection(pool_name, scheme_name,
                                                                  collection_name, constructed_logger);
                new_command->execute(line);
            }
            else if (line == "ADD_VALUE")
            {
                constructed_logger->trace("[add_value] find add_value");

                std::string pool_name;
                std::string scheme_name;
                std::string collection_name;
                int id_buyer;

                input_file >> pool_name >> scheme_name >> collection_name >> id_buyer;
                std::tuple<long, long, std::string, std::string, std::string, int> result = serialization(input_file, constructed_logger);

                long position = std::get<0>(result);
                long size = std::get<1>(result) + 1;
                std::string name = std::get<2>(result);
                std::string date = std::get<3>(result);
                std::string address = std::get<4>(result);
                int id_oder = std::get<5>(result);

                constructed_logger->information(pool_name + " " + scheme_name + " " + collection_name + " " + std::to_string(id_buyer) + " " + name + " " + date + " " + address + " " + std::to_string(id_oder));
                std::string value_file_name = base_directory_name + "/" + pool_name + "/" + scheme_name + "/" + collection_name + "/" + std::to_string(id_buyer) + ".txt";

                try
                {
                    std::ofstream file(value_file_name);
                    if (file.is_open())
                    {
                        file << name << " " << date << " " << address << " " << id_oder << std::endl;
                    }
                    else
                    {
                        constructed_logger->error("[add_value] error opening the file" + value_file_name);
                    }

                    constructed_logger->trace("[add_value] file " + value_file_name + " has created");
                    command* new_command = new command_add_value(pool_name, scheme_name, collection_name, id_buyer, position, size, constructed_logger);
                    new_command->execute(line);
                    constructed_logger->debug("[add_value] the value has been added successfully");
                }
                catch(const std::exception& error)
                {
                    constructed_logger->error("[add_value] error with add value");
                }
            }
            else if (line == "UPDATE_VALUE")
            {
                constructed_logger->trace("[update_value] find update_value");

                std::string pool_name;
                std::string scheme_name;
                std::string collection_name;
                int id_buyer;

                input_file >> pool_name >> scheme_name >> collection_name >> id_buyer;
                std::tuple<long, long, std::string, std::string, std::string, int> result = serialization(input_file, constructed_logger);

                long position = std::get<0>(result);
                long size = std::get<1>(result) + 1;
                std::string name = std::get<2>(result);
                std::string date = std::get<3>(result);
                std::string address = std::get<4>(result);
                int id_oder = std::get<5>(result);

                constructed_logger->information(pool_name + " " + scheme_name + " " + collection_name + " " + std::to_string(id_buyer) + " " + name + " " + date + " " + address + " " + std::to_string(id_oder));
                std::string value_file_name = base_directory_name + "/" + pool_name + "/" + scheme_name + "/" + collection_name + "/" + std::to_string(id_buyer) + ".txt";

                try
                {
                    std::ofstream file(value_file_name);
                    if (file.is_open())
                    {
                        file << name << " " << date << " " << address << " " << id_oder << std::endl;
                    }
                    else
                    {
                        constructed_logger->error("[update_value] error opening the file" + value_file_name);
                    }

                    constructed_logger->trace("[update_value] file " + value_file_name + " has created");
                    command* new_command = new command_update_value(pool_name, scheme_name, collection_name, id_buyer, position, size, constructed_logger);
                    new_command->execute(line);
                    constructed_logger->debug("[update_value] the value has been updated successfully");
                }
                catch(const std::exception& error)
                {
                    constructed_logger->error("[update_value] error with update value");
                }

            }
            else if (line == "FIND_VALUE")
            {
                constructed_logger->trace("[find_value] find find_value");

                std::string pool_name;
                std::string scheme_name;
                std::string collection_name;
                int id_buyer;

                std::string line;
                std::getline(input_file, line);

                if (!line.empty())
                {
                    line = line.substr(0, line.size() - 1);
                }

                std::istringstream line_stream(line);

                line_stream >> pool_name >> scheme_name >> collection_name >> id_buyer;
                std::cout << pool_name << " " << scheme_name << " " << collection_name << " " << id_buyer << std::endl;

                try
                {
                    command* new_command = new command_find_value(pool_name, scheme_name, collection_name, id_buyer, constructed_logger);
                    new_command->execute(line);
                    value* result = reinterpret_cast<command_find_value*>(new_command)->get_result();

                    std::cout << "RESULT " << result << std::endl;

                    value_file_system* value_file = reinterpret_cast<value_file_system*>(result);
                    std::streampos original_position = input_file.tellg();

                    value_in_memory_cache value_memory = deserialization(input_file, value_file->_start_value_bytes, value_file->_string_size, constructed_logger);
                    input_file.seekg(original_position);

                    constructed_logger->information("[find_value] name: " + value_memory._name_buyer + ", date: " + value_memory._date + ", address: " + value_memory._address + ", id_oder: " + std::to_string(value_memory._id_order));
                }
                catch (const std::exception& e)
                {
                    constructed_logger->error("[find_value] error with find value");
                }
            }
            else if (line == "DELETE_VALUE")
            {
                std::string pool_name;
                std::string scheme_name;
                std::string collection_name;
                int id_buyer;

                std::string id_buyer_string = std::to_string(id_buyer);

                input_file >> pool_name >> scheme_name >> collection_name >> id_buyer;

                std::string value_file_name = base_directory_name + "/" + pool_name + "/" + scheme_name + "/" + collection_name + "/" + id_buyer_string + ".txt";

                if (std::remove(value_file_name.c_str()) != 0)
                {
                    constructed_logger->error("error deleting the file: " + value_file_name);
                    std::cerr << "error deleting the file: " << value_file_name << std::endl;
                }
                else
                {
                    constructed_logger->trace("file has deleted successfully: " + value_file_name);
                    std::cout << "file has deleted successfully: " << value_file_name << std::endl;
                }

                command* new_command = new command_delete_value(pool_name, scheme_name, collection_name,
                                                                id_buyer, constructed_logger);
                new_command->execute(line);
            }
            else if (line == "FIND_BETWEEN_VALUE")
            {
                std::string pool_name;
                std::string scheme_name;
                std::string collection_name;

                input_file >> pool_name >> scheme_name >> collection_name;

            }
        }
    }

public:

    ~file_system_parse() = default;

    file_system_parse(file_system_parse const &other) = delete;

    file_system_parse(file_system_parse const &&other) = delete;

    file_system_parse& operator=(file_system_parse const &other) = delete;

    file_system_parse& operator=(file_system_parse const &&other) = delete;
};

#endif //COURSE_PROJECT_FILE_SYSTEM_PARSE_H
