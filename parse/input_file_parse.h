#ifndef COURSE_PROJECT_INPUT_FILE_PARSE_H
#define COURSE_PROJECT_INPUT_FILE_PARSE_H
#include "../containers/database.h"
#include "../containers/pool.h"
#include "../containers/scheme.h"
#include "../containers/collection.h"
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>

class input_file_parse
{

public:

    input_file_parse() = default;

public:

    void parse_input_file(std::ifstream& input_file, database* data_base_parse, logger* log)
    {
        log->trace("[input_file_parse] start parse input file method");

        std::string line;
        while (input_file >> line)
        {
            std::cout << line << std::endl;

            if (line == "ADD_POOL")
            {
                log->debug("[add_pool] find ADD_POOL function");

                std::string pool_name;

                input_file >> pool_name;
                std::cout << line << " " << pool_name << std::endl;

                try
                {
                    data_base_parse->add_pool(pool_name);
                    log->debug("[add_pool] the pool has been added successfully");
                }
                catch(const std::exception& error)
                {
                    log->error("[add_pool] error with add pool");
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

                try
                {
                    data_base_parse->add_value(pool_name, scheme_name, collection_name, id_buyer, name, date, address, id_oder);
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
                int id_oder;

                input_file >> pool_name >> scheme_name >> collection_name >> id_buyer >> name >> date >> address >> id_oder;
                log->debug(pool_name + " " +  scheme_name + " " + collection_name + " " + std::to_string(id_buyer) + " " + name + " " + date + " " + address + " " + std::to_string(id_oder));

                try
                {
                    data_base_parse->update_value(pool_name, scheme_name, collection_name, id_buyer, name, date, address, id_oder);
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
                    data_base_parse->obtain_value(pool_name, scheme_name, collection_name, id_buyer);
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

                try
                {

                }
                catch (const std::exception& error)
                {
                    std::cout << error.what() << std::endl;
                    log->error("[find_between_value] error with find between value");
                }
            }
        }
    }

public:

    // TODO file_system

    std::pair<long, long> serialization(std::ifstream& input_file, std::string name, int id_oder)
    {
//        std::pair<long, long> positions;
//
//        if (input_file.is_open())
//        {
//            std::string word;
//            long position = 0;
//            while (input_file >> word)
//            {
//                if (word == name)
//                {
//                    positions.first = position;
//                }
//                if (std::stoi(word) == id_oder)
//                {
//                    positions.second = position;
//                }
//                position = input_file.tellg();
//            }
//        }
//
//        return positions;

        std::pair<long, long> information_for_file_system;

//        input_file.seekg(0, std::ios::end); // to the end of file
        long position = input_file.tellg();
        information_for_file_system.first = position;

//        long size_value = std::to_string(id_oder).size();
//        information_for_file_system.second = size_value;

        return information_for_file_system;
    }

    value_in_memory_cash deserialization(long first_byte, long size_value, std::ifstream& input_file, value_in_memory_cash& buffer_memory)
    {
        input_file.seekg(first_byte, std::ios::beg);
        char* buffer = new char[size_value];

        input_file.read(buffer, size_value);

        for (int i = 0; i < size_value; ++i)
        {
            std::cout << buffer[i];
        }

        buffer_memory = *reinterpret_cast<value_in_memory_cash*>(buffer);

        delete[] buffer;

        return buffer_memory;
    }

    void parse_input_file_for_file_system(std::ifstream& input_file, database* data_base_parse, logger* log)
    {
        log->trace("[input_file_parse] start parse input file method");

        std::string base_directory_name = "data_base";

        if (!std::filesystem::exists(base_directory_name))
        {
            try
            {
                std::filesystem::create_directory(base_directory_name);
                log->trace("directory " + base_directory_name + " has created");
            }
            catch (const std::exception& e)
            {
                log->error("error creating the directory");
                std::cerr << "error creating the directory" << e.what() << std::endl;
            }
        }

        std::string line;
        while (input_file >> line)
        {
            std::cout << line << std::endl;

            if (line == "ADD_POOL")
            {
                log->trace("[add_pool] find add_pool");

                std::string pool_name;
                input_file >> pool_name;

                std::cout << pool_name << std::endl;

                try
                {
                    pool_name = data_base_parse->validate_path(pool_name);
                }
                catch (const std::logic_error& e)
                {
                    std::cerr << "error " << e.what() << std::endl;
                }

                std::string pool_directory_name = base_directory_name + "/" + pool_name;

                if (!std::filesystem::exists(pool_directory_name))
                {
                    try
                    {
                        std::filesystem::create_directory(pool_directory_name);
                        log->trace("[add_pool] directory " + pool_directory_name + " has created");
                    }
                    catch (const std::exception& e)
                    {
                        log->error("[add_pool] error creating the directory " + pool_directory_name);
                        std::cerr << "[add_pool] error creating the directory " + pool_directory_name << e.what() << std::endl;
                    }
                }

                try
                {
                    data_base_parse->add_pool(pool_name);
                    log->debug("[add_pool] the pool has been added successfully");
                }
                catch(const std::exception& error)
                {
                    log->error("[add_pool] error with add pool");
                }
            }
            else if (line == "DELETE_POOL")
            {
                log->trace("[delete_pool] find delete_pool");

                std::string pool_name;
                input_file >> pool_name;

                std::cout << pool_name << std::endl;

                try
                {
                    pool_name = data_base_parse->validate_path(pool_name);
                }
                catch (const std::logic_error& e)
                {
                    std::cerr << "error " << e.what() << std::endl;
                }

                std::string pool_directory_name = base_directory_name + "/" + pool_name;

                if (std::filesystem::exists(pool_directory_name))
                {
                    try
                    {
                        std::filesystem::remove_all(pool_directory_name);
                        log->trace("directory " + pool_directory_name + " has deleted");
                    }
                    catch (const std::exception& e)
                    {
                        log->error("error deleting the directory " + pool_directory_name);
                        std::cerr << "error deleting the directory " + pool_directory_name << e.what() << std::endl;
                    }
                }

                try
                {
                    data_base_parse->delete_pool(pool_name);
                    log->debug("[add_pool] the pool has been deleted successfully");
                }
                catch(const std::exception& error)
                {
                    log->error("[add_pool] error with add pool");
                }
            }
            else if (line == "ADD_SCHEME")
            {
                log->trace("[add_scheme] find add_scheme");

                std::string pool_name;
                std::string scheme_name;
                input_file >> pool_name >> scheme_name;

                std::cout << "pool_name: " << pool_name << " scheme_name: " << scheme_name << std::endl;

                try
                {
                    data_base_parse->add_scheme(pool_name, scheme_name);
                    log->debug("[add_scheme] the scheme has been added successfully");
                }
                catch(const std::exception& error)
                {
                    log->error("[add_scheme] error with add scheme");
                }

                try
                {
                    pool_name = data_base_parse->validate_path(pool_name);
                    scheme_name = data_base_parse->validate_path(scheme_name);
                }
                catch (const std::logic_error& e)
                {
                    std::cerr << "error " << e.what() << std::endl;
                }

                std::string scheme_directory_name = base_directory_name + "/" + pool_name + "/" + scheme_name;

                if (!std::filesystem::exists(scheme_directory_name))
                {
                    try
                    {
                        std::filesystem::create_directory(scheme_directory_name);
                        log->trace("directory " + scheme_directory_name + " has created");
                    }
                    catch (const std::exception& e)
                    {
                        log->error("error creating the directory " + scheme_directory_name);
                        std::cerr << "error creating the directory " + scheme_directory_name << e.what() << std::endl;
                    }
                }
            }
            else if (line == "DELETE_SCHEME")
            {
                log->trace("[delete_scheme] find delete_scheme");

                std::string pool_name;
                std::string scheme_name;
                input_file >> pool_name >> scheme_name;

                std::cout << "pool_name: " << pool_name << " scheme_name: " << scheme_name << std::endl;

                try
                {
                    data_base_parse->delete_scheme(pool_name, scheme_name);
                    log->debug("[add_scheme] the scheme has been deleted successfully");
                }
                catch(const std::exception& error)
                {
                    log->error("[add_scheme] error with delete scheme");
                }

                try
                {
                    pool_name = data_base_parse->validate_path(pool_name);
                    scheme_name = data_base_parse->validate_path(scheme_name);
                }
                catch (const std::logic_error& e)
                {
                    std::cerr << "error " << e.what() << std::endl;
                }

                std::string scheme_directory_name = base_directory_name + "/" + pool_name + "/" + scheme_name;

                if (std::filesystem::exists(scheme_directory_name))
                {
                    try
                    {
                        std::filesystem::remove_all(scheme_directory_name);
                        log->trace("directory " + scheme_directory_name + " has deleted");
                    }
                    catch (const std::exception& e)
                    {
                        log->error("error deleting the directory " + scheme_directory_name);
                        std::cerr << "error deleting the directory " + scheme_directory_name << e.what() << std::endl;
                    }
                }
            }
            else if (line == "ADD_COLLECTION")
            {
                log->trace("[add_collection] find add_collection");

                std::string pool_name;
                std::string scheme_name;
                std::string collection_name;

                input_file >> pool_name >> scheme_name >> collection_name;

                std::cout << "pool_name: " << pool_name << " scheme_name: " << scheme_name << " collection_name: " << collection_name << std::endl;

//                try
//                {
//                    data_base_parse->add_collection(pool_name, scheme_name, collection_name);
//                    log->debug("[add_collection] the collection has been added successfully");
//                }
//                catch(const std::exception& error)
//                {
//                    log->error("[add_collection] error with add collection");
//                }

                try
                {
                    pool_name = data_base_parse->validate_path(pool_name);
                    scheme_name = data_base_parse->validate_path(scheme_name);
                    collection_name = data_base_parse->validate_path(collection_name);
                }
                catch (const std::logic_error& e)
                {
                    std::cerr << "error " << e.what() << std::endl;
                }

                std::string collection_directory_name = base_directory_name + "/" + pool_name + "/" + scheme_name + "/" + collection_name;

                if (!std::filesystem::exists(collection_directory_name))
                {
                    try
                    {
                        std::filesystem::create_directory(collection_directory_name);
                        log->trace("directory " + collection_directory_name + " has created");
                    }
                    catch (const std::exception& e)
                    {
                        log->error("error creating the directory " + collection_directory_name);
                        std::cerr << "error creating the directory " + collection_directory_name << e.what() << std::endl;
                    }
                }
            }
            else if (line == "DELETE_COLLECTION")
            {
                log->trace("[delete_collection] find delete_collection");

                std::string pool_name;
                std::string scheme_name;
                std::string collection_name;

                input_file >> pool_name >> scheme_name >> collection_name;

                std::cout << "pool name: " << pool_name << " scheme_name: " << scheme_name << " collection_name: " << collection_name << std::endl;

                try
                {
                    pool_name = data_base_parse->validate_path(pool_name);
                    scheme_name = data_base_parse->validate_path(scheme_name);
                    collection_name = data_base_parse->validate_path(collection_name);
                }
                catch (const std::logic_error& e)
                {
                    std::cerr << "error " << e.what() << std::endl;
                }

                std::string collection_directory_name = base_directory_name + "/" + pool_name + "/" + scheme_name + "/" + collection_name;

                if (std::filesystem::exists(collection_directory_name))
                {
                    try
                    {
                        std::filesystem::remove_all(collection_directory_name);
                        log->trace("directory " + collection_directory_name + " has deleted");
                    }
                    catch (const std::exception& e)
                    {
                        log->error("error deleting the directory " + collection_directory_name);
                        std::cerr << "error deleting the directory " + collection_directory_name << e.what() << std::endl;
                    }
                }

                try
                {
                    data_base_parse->delete_collection(pool_name, scheme_name, collection_name);
                    log->debug("[delete_collection] the collection has been deleted successfully");
                }
                catch(const std::exception& error)
                {
                    log->error("[delete_collection] error with add collection");
                }
            }
            else if (line == "ADD_VALUE")
            {
                log->trace("[add_value] find add_value");

//                 info about buyer: key - id_buyer, value - name, date, address, id_oder
                std::string pool_name;
                std::string scheme_name;
                std::string collection_name;

                std::string name;
                std::string date;
                std::string address;
                int id_buyer; // it's key
                int id_oder;

                input_file >> pool_name >> scheme_name >> collection_name >> id_buyer >> name >> date >> address >> id_oder;

                std::string id_buyer_string = std::to_string(id_buyer);

                try
                {
                    pool_name = data_base_parse->validate_path(pool_name);
                    scheme_name = data_base_parse->validate_path(scheme_name);
                    collection_name = data_base_parse->validate_path(collection_name);
                    id_buyer_string = data_base_parse->validate_path(id_buyer_string);
                }
                catch (const std::logic_error& e)
                {
                    std::cerr << "error " << e.what() << std::endl;
                }

                std::cout << pool_name << " " << scheme_name << " " << collection_name << " " << id_buyer << " " << name << " " << date << " " << address << " " << id_oder << " " << std::endl;

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
                        log->error("error opening the file" + value_file_name);
                        std::cerr << "error opening the file " + value_file_name << std::endl;
                    }

                    log->trace("file " + value_file_name + " has created");
                }
                catch (const std::exception& e)
                {
                    log->error("error creating the file" + value_file_name);
                    std::cerr << "error creating the file " + value_file_name << e.what() << std::endl;
                }

                std::pair<long, long> first_byte_and_size = serialization(input_file, name, id_oder);
                std::cout << "first_byte: " << first_byte_and_size.first << " size: " << first_byte_and_size.second << std::endl;

//                try
//                {
//                    data_base_parse->add_value(pool_name, scheme_name, collection_name, id_buyer, value_file_name, first_byte_and_size);
//                    log->debug("[add_value] the value has been added successfully");
//                }
//                catch(const std::exception& error)
//                {
//                    log->error("[add_value] error with add value");
//                }
            }
            else if (line == "UPDATE_VALUE")
            {
                log->trace("[update_value] find update_value");

                std::string pool_name;
                std::string scheme_name;
                std::string collection_name;

                input_file >> pool_name >> scheme_name >> collection_name;

            }
            else if (line == "FIND_VALUE")
            {
                log->trace("[find_value] find find_value");

                std::string pool_name;
                std::string scheme_name;
                std::string collection_name;
                int id_buyer;

                input_file >> pool_name >> scheme_name >> collection_name >> id_buyer;

                std::string id_buyer_string = std::to_string(id_buyer);

                std::cout << pool_name << " " << scheme_name << " " << collection_name << " " << id_buyer << std::endl;

                try
                {
                    pool_name = data_base_parse->validate_path(pool_name);
                    scheme_name = data_base_parse->validate_path(scheme_name);
                    collection_name = data_base_parse->validate_path(collection_name);
                    id_buyer_string = data_base_parse->validate_path(id_buyer_string);
                }
                catch (const std::logic_error& e)
                {
                    std::cerr << "error " << e.what() << std::endl;
                }

                try
                {
                    std::cout << "hello world" << std::endl;

                }
                catch (const std::exception& e)
                {
                    log->error("[find_value] error with find value");
                }



            }
            else if (line == "DELETE_VALUE")
            {
                std::string pool_name;
                std::string scheme_name;
                std::string collection_name;

                input_file >> pool_name >> scheme_name >> collection_name;

//                if (std::remove(collection_file_name.c_str()) != 0)
//                {
//                    log->error("error deleting the file: " + collection_file_name);
//                    std::cerr << "error deleting the file: " << collection_file_name << std::endl;
//                }
//                else
//                {
//                    log->trace("file has deleted successfully: " + collection_file_name);
//                    std::cout << "file has deleted successfully: " << collection_file_name << std::endl;
//                }

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

    ~input_file_parse() = default;

    input_file_parse(input_file_parse const &other) = delete;

    input_file_parse(input_file_parse const &&other) = delete;

    input_file_parse& operator=(input_file_parse const &other) = delete;

    input_file_parse& operator=(input_file_parse const &&other) = delete;
};


#endif //COURSE_PROJECT_INPUT_FILE_PARSE_H
