#ifndef COURSE_PROJECT_INPUT_FILE_PARSE_H
#define COURSE_PROJECT_INPUT_FILE_PARSE_H
#include "database.h"
#include "pool.h"
#include "scheme.h"
#include "collection.h"
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
        std::cout << "[input_file_parse] start parse input file method" << std::endl;

        std::string line;
        while (input_file >> line)
        {
            std::cout << line << std::endl;

            if (line == "ADD_POOL")
            {
                log->debug("[add_pool] find ADD_POOL function");
                std::cout << "[add_pool] find ADD_POOL function" << std::endl;

                std::string pool_name;

                input_file >> pool_name;
                std::cout << line << " " << pool_name << std::endl;

                try
                {
                    data_base_parse->add_pool(pool_name);
                    log->debug("[add_pool] the pool has been added successfully");
                    std::cout << "[add_pool] the pool has been added successfully" << std::endl;
                }
                catch(const std::exception& error)
                {
                    log->error("[add_pool] error with add pool");
                    std::cout << "[add_pool] error with add pool" << std::endl;
                }
            }
            else if (line == "DELETE_POOL")
            {
                log->debug("[delete_pool] find DELETE_POOL function");
                std::cout << "[delete_pool] find DELETE_POOL function" << std::endl;

                std::string pool_name;

                input_file >> pool_name;
                std::cout << line << " " << pool_name << std::endl;

                try
                {
                    data_base_parse->delete_pool(pool_name);
                    log->debug("[delete_pool] the pool has been deleted successfully");
                    std::cout << "[delete_pool] the pool has been deleted successfully" << std::endl;
                }
                catch(const std::exception& error)
                {
                    log->error("[delete_pool] error with delete pool");
                    std::cout << "[delete_pool] error with delete pool" << std::endl;
                }
            }
            else if (line == "ADD_SCHEME")
            {
                log->debug("[add_scheme] find ADD_SCHEME function");
                std::cout << "[add_scheme] find ADD_SCHEME function" << std::endl;

                std::string pool_name;
                std::string scheme_name;

                input_file >> pool_name >> scheme_name;
                std::cout << line << " " << scheme_name << std::endl;

                try
                {
                    data_base_parse->add_scheme(pool_name, scheme_name);
                    log->debug("[add_scheme] the scheme has been added successfully");
                    std::cout << "[add_scheme] the scheme has been added successfully" << std::endl;
                }
                catch(const std::exception& error)
                {
                    log->error("[add_scheme] error with add scheme");
                    std::cout << "[add_scheme] error with add scheme" << std::endl;
                }
            }
            else if (line == "DELETE_SCHEME")
            {
                log->debug("[delete_scheme] find DELETE_SCHEME function");
                std::cout << "[delete_scheme] find DELETE_SCHEME function" << std::endl;

                std::string pool_name;
                std::string scheme_name;

                input_file >> pool_name >> scheme_name;
                std::cout << line << " " << scheme_name << std::endl;

                try
                {
                    data_base_parse->delete_scheme(pool_name, scheme_name);
                    log->debug("[delete_scheme] the scheme has been deleted successfully");
                    std::cout << "[delete_scheme] the scheme has been deleted successfully" << std::endl;
                }
                catch(const std::exception& error)
                {
                    log->error("[delete_scheme] error with deleted scheme");
                    std::cout << "[delete_scheme] error with deleted scheme" << std::endl;
                }
            }
            else if (line == "ADD_COLLECTION")
            {
                log->debug("[add_collection] find ADD_COLLECTION function");
                std::cout << "[add_collection] find ADD_COLLECTION function" << std::endl;

                std::string pool_name;
                std::string scheme_name;
                std::string collection_name;

                input_file >> pool_name >> scheme_name >> collection_name;
                std::cout << line << " " << pool_name << " " << scheme_name << " " << collection_name << std::endl;

                try
                {
                    data_base_parse->add_collection(pool_name, scheme_name, collection_name);
                    log->debug("[add_collection] the collection has been added successfully");
                    std::cout << "[add_collection] the collection has been added successfully" << std::endl;
                }
                catch(const std::exception& error)
                {
                    log->error("[add_collection] error with add collection");
                    std::cout << "[add_collection] error with add collection" << std::endl;
                }

            }
            else if (line == "DELETE_COLLECTION")
            {
                log->debug("[delete_collection] find DELETE_COLLECTION function");
                std::cout << "[delete_collection] find DELETE_COLLECTION function" << std::endl;

                std::string pool_name;
                std::string scheme_name;
                std::string collection_name;

                input_file >> pool_name >> scheme_name >> collection_name;
                std::cout << line << " " << pool_name << " " << scheme_name << " " << collection_name << std::endl;

                try
                {
                    data_base_parse->delete_collection(pool_name, scheme_name, collection_name);
                    log->debug("[delete_collection] the collection has been deleted successfully");
                    std::cout << "[delete_collection] the collection has been deleted successfully" << std::endl;
                }
                catch(const std::exception& error)
                {
                    log->error("[delete_collection] error with delete collection");
                    std::cout << "[delete_collection] error with delete collection" << std::endl;
                }
            }
            else if (line == "ADD_VALUE")
            {
                log->debug("[add_value] find ADD_VALUE function");
                std::cout << "[add_value] find ADD_VALUE function" << std::endl;

//                 info about buyer: key - id_buyer, value - name, date, address, id_oder

                std::string pool_name;
                std::string scheme_name;
                std::string collection_name;

                input_file >> pool_name >> scheme_name >> collection_name;

//                std::string name;
//                std::string date;
//                std::string address;
//                int id_buyer;
//                int id_oder;
//                std::string path_filename = "database_input.txt";
//
//                input_file >> pool_name >> scheme_name >> collection_name >> id_buyer >> id_oder >> name >> date >> address;
//                std::cout << line << " " << pool_name << " " << scheme_name << " " << collection_name << " " << id_buyer << " " << id_oder << " " << name << " " << date << " " << address << std::endl;
//
//                // find pos id_oder
//
//                std::pair<long, long> information_for_file_system = read_byte_number(input_file, id_oder);
//
//                std::cout << "hello debil" << std::endl;
//
//                std::cout << "position: " << information_for_file_system.first << " size: " << information_for_file_system.second << std::endl;

            }
            else if (line == "UPDATE_VALUE")
            {
                log->debug("[update_value] find UPDATE_VALUE function");
                std::cout << "[update_value] find UPDATE_VALUE function" << std::endl;

                std::string pool_name;
                std::string scheme_name;
                std::string collection_name;

                input_file >> pool_name >> scheme_name >> collection_name;
            }
            else if (line == "FIND_VALUE")
            {
                log->debug("[find_value] find FIND_VALUE function");
                std::cout << "[find_value] find FIND_VALUE function" << std::endl;

                std::string pool_name;
                std::string scheme_name;
                std::string collection_name;

                input_file >> pool_name >> scheme_name >> collection_name;
            }
            else if (line == "DELETE_VALUE")
            {
                log->debug("[delete_value] find DELETE_VALUE function");
                std::cout << "[delete_value] find DELETE_VALUE function" << std::endl;

                std::string pool_name;
                std::string scheme_name;
                std::string collection_name;

                input_file >> pool_name >> scheme_name >> collection_name;
            }
            else if (line == "FIND_BETWEEN_VALUE")
            {
                log->debug("[find_between_value] find FIND_BETWEEN_VALUE function");
                std::cout << "[find_between_value] find FIND_BETWEEN_VALUE function" << std::endl;

                std::string pool_name;
                std::string scheme_name;
                std::string collection_name;

                input_file >> pool_name >> scheme_name >> collection_name;
            }
        }
    }

public:

    // TODO file_system

    std::pair<long, long> read_byte_number(std::ifstream& input_file, int id_oder)
    {
        std::pair<long, long> information_for_file_system;

        input_file.seekg(0, std::ios::end);
        long position = input_file.tellg();
        information_for_file_system.first = position;

        long size_value = std::to_string(id_oder).size();
        information_for_file_system.second = size_value;

        return information_for_file_system;
    }

    void parse_input_file_for_file_system(std::ifstream& input_file, database* data_base_parse, logger* log)
    {
        log->trace("[input_file_parse] start parse input file method");
        std::cout << "[input_file_parse] start parse input file method" << std::endl;

        std::string base_directory_name = "data_base";

        if (!std::filesystem::exists(base_directory_name))
        {
            try
            {
                std::filesystem::create_directory(base_directory_name);
                log->trace("directory 'data_base' has created");
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
                std::cout << "[add_pool] find add_pool" << std::endl;

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
                    std::cout << "[add_pool] the pool has been added successfully" << std::endl;
                }
                catch(const std::exception& error)
                {
                    log->error("[add_pool] error with add pool");
                    std::cout << "[add_pool] error with add pool" << std::endl;
                }
            }
            else if (line == "DELETE_POOL")
            {
                log->trace("[delete_pool] find delete_pool");
                std::cout << "[delete_pool] find delete_pool" << std::endl;

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
                    std::cout << "[add_pool] the pool has been deleted successfully" << std::endl;
                }
                catch(const std::exception& error)
                {
                    log->error("[add_pool] error with add pool");
                    std::cout << "[add_pool] error with add pool" << std::endl;
                }
            }
            else if (line == "ADD_SCHEME")
            {
                log->trace("[add_scheme] find add_scheme");
                std::cout << "[add_scheme] find add_scheme" << std::endl;

                std::string pool_name;
                std::string scheme_name;
                input_file >> pool_name >> scheme_name;

                std::cout << "pool_name: " << pool_name << " scheme_name: " << scheme_name << std::endl;

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

                try
                {
                    data_base_parse->add_scheme(pool_name, scheme_name);
                    log->debug("[add_scheme] the scheme has been added successfully");
                    std::cout << "[add_scheme] the scheme has been added successfully" << std::endl;
                }
                catch(const std::exception& error)
                {
                    log->error("[add_scheme] error with add scheme");
                    std::cout << "[add_scheme] error with add scheme" << std::endl;
                }
            }
            else if (line == "DELETE_SCHEME")
            {
                log->trace("[delete_scheme] find delete_scheme");
                std::cout << "[delete_scheme] find delete_scheme" << std::endl;

                std::string pool_name;
                std::string scheme_name;
                input_file >> pool_name >> scheme_name;

                std::cout << "pool_name: " << pool_name << " scheme_name: " << scheme_name << std::endl;

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

                try
                {
                    data_base_parse->delete_scheme(pool_name, scheme_name);
                    log->debug("[add_scheme] the scheme has been deleted successfully");
                    std::cout << "[add_scheme] the scheme has been deleted successfully" << std::endl;
                }
                catch(const std::exception& error)
                {
                    log->error("[add_scheme] error with delete scheme");
                    std::cout << "[add_scheme] error with delete scheme" << std::endl;
                }
            }
            else if (line == "ADD_COLLECTION")
            {
                log->trace("[add_collection] find add_collection");
                std::cout << "[add_collection] find add_collection" << std::endl;

                std::string pool_name;
                std::string scheme_name;
                std::string collection_name;

                input_file >> pool_name >> scheme_name >> collection_name;

                std::cout << "pool_name: " << pool_name << " scheme_name: " << scheme_name << " collection_name: " << collection_name << std::endl;

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

                try
                {
                    data_base_parse->add_collection(pool_name, scheme_name, collection_name);
                    log->debug("[add_collection] the collection has been added successfully");
                    std::cout << "[add_collection] the collection has been added successfully" << std::endl;
                }
                catch(const std::exception& error)
                {
                    log->error("[add_collection] error with add collection");
                    std::cout << "[add_collection] error with add collection" << std::endl;
                }
            }
            else if (line == "DELETE_COLLECTION")
            {
                log->trace("[delete_collection] find delete_collection");
                std::cout << "[delete_collection] find delete_collection" << std::endl;

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
                    std::cout << "[delete_collection] the collection has been deleted successfully" << std::endl;
                }
                catch(const std::exception& error)
                {
                    log->error("[delete_collection] error with add collection");
                    std::cout << "[delete_collection] error with add collection" << std::endl;
                }
            }
            else if (line == "ADD_VALUE")
            {
                log->trace("[add_value] find add_value");
                std::cout << "[add_value] find add_value" << std::endl;

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

                std::pair<long, long> first_byte_and_size = read_byte_number(input_file, id_oder);

                try
                {
                    data_base_parse->add_value(pool_name, scheme_name, collection_name, id_buyer, value_file_name, first_byte_and_size);
                    log->debug("[add_value] the value has been added successfully");
                    std::cout << "[add_value] the value has been added successfully" << std::endl;
                }
                catch(const std::exception& error)
                {
                    log->error("[add_value] error with add value");
                    std::cout << "[add_value] error with add value" << std::endl;
                }
            }
            else if (line == "UPDATE_VALUE")
            {
                std::string pool_name;
                std::string scheme_name;
                std::string collection_name;

                input_file >> pool_name >> scheme_name >> collection_name;

            }
            else if (line == "FIND_VALUE")
            {
                std::string pool_name;
                std::string scheme_name;
                std::string collection_name;

                input_file >> pool_name >> scheme_name >> collection_name;

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
