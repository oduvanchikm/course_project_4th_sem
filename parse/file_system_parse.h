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

class file_system_parse
{

public:

    file_system_parse() = default;

public:

    std::tuple<long, long, std::string, std::string, std::string, int> serialization(std::ifstream& input_file,
                                        logger* log)
    {
        log->trace("[serialization] start serialization");

        std::tuple<long, long, std::string, std::string, std::string, int> result;

        if (!input_file.is_open())
        {
            log->error("[serialization] error with opening file");
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

        std::cout << "size: " << data_size << std::endl;
        std::cout << "first byte: " << position << std::endl;
        std::cout << "last byte: " << new_position << std::endl;

        return result;
    }

    std::string deserialization(std::ifstream& input_file, long position, logger* log)
    {
        log->trace("[deserialization] start deserialization");

        std::string file_name;
        input_file.seekg(position);
        input_file.read(reinterpret_cast<char*>(&file_name), sizeof(file_name));

        input_file.close();

        return file_name;
    }

//    void deserialization(long first_byte, long size_value, std::ifstream& input_file)
//    {
//        input_file.seekg(first_byte, std::ios::beg);
//        char* buffer = new char[size_value];
//
//        input_file.read(buffer, 4);
//
//        for (int i = 0; i < 4; ++i)
//        {
//            std::cout << buffer[i];
//        }

//        buffer_memory = *reinterpret_cast<value_in_memory_cash*>(buffer);
//
//        delete[] buffer;
//
//        return buffer_memory;
//    }

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
                    log->error("[add_collection] error with add collection");
                }

//                try
//                {
//                    pool_name = data_base_parse->validate_path(pool_name);
//                    scheme_name = data_base_parse->validate_path(scheme_name);
//                    collection_name = data_base_parse->validate_path(collection_name);
//                }
//                catch (const std::logic_error& e)
//                {
//                    std::cerr << "error " << e.what() << std::endl;
//                }

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

//                try
//                {
//                    pool_name = data_base_parse->validate_path(pool_name);
//                    scheme_name = data_base_parse->validate_path(scheme_name);
//                    collection_name = data_base_parse->validate_path(collection_name);
//                }
//                catch (const std::logic_error& e)
//                {
//                    std::cerr << "error " << e.what() << std::endl;
//                }

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

                std::string pool_name;
                std::string scheme_name;
                std::string collection_name;
                int id_buyer;

                input_file >> pool_name >> scheme_name >> collection_name >> id_buyer;
                std::tuple<long, long, std::string, std::string, std::string, int> result = serialization(input_file, log);

                long position = std::get<0>(result);
                long size = std::get<1>(result);
                std::string name = std::get<2>(result);
                std::string date = std::get<3>(result);
                std::string address = std::get<4>(result);
                int id_oder = std::get<5>(result);

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

//                deserialization(first_byte_and_size.first, first_byte_and_size.second, input_file);

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

    ~file_system_parse() = default;

    file_system_parse(file_system_parse const &other) = delete;

    file_system_parse(file_system_parse const &&other) = delete;

    file_system_parse& operator=(file_system_parse const &other) = delete;

    file_system_parse& operator=(file_system_parse const &&other) = delete;
};

#endif //COURSE_PROJECT_FILE_SYSTEM_PARSE_H
