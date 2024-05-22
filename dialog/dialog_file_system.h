#ifndef COURSE_PROJECT_DIALOG_FILE_SYSTEM_H
#define COURSE_PROJECT_DIALOG_FILE_SYSTEM_H
#include "../validate/validate_parameters.h"

class dialog_file_system
{
public:

    dialog_file_system() = default;

public:

    std::tuple<long, long, std::string, std::string, std::string, int> serialization_for_dialog(std::ifstream& input_file,
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

        return result;
    }

    value_in_memory_cash deserialization_for_dialog(std::ifstream& input_file, long position, long size, logger* log)
    {
        log->trace("[deserialization] start deserialization");

        std::cout << position << " " << size << std::endl;

        input_file.seekg(position);

        char* buffer = new char[size];
        input_file.read(buffer, size);

        std::string serialized_data(buffer, size);
        std::istringstream iss(serialized_data);
        std::string name, date, address, id_oder;
        iss >> name >> date >> address >> id_oder;

        delete[] buffer;

        value_in_memory_cash value_memory;

        value_memory._name_buyer = name;
        value_memory._date = date;
        value_memory._address = address;
        value_memory._id_order = std::stoi(id_oder);

        return value_memory;
    }

    void parse_input_file_for_file_system(std::ifstream& input_file, database* data_base_parse, logger* log)
    {
        log->trace("[input_file_parse] start parse input file method");

        std::string base_directory_name;

        std::cout << "Start parse input file\nPlease enter a directory name for data base: " << std::endl;
        std::cin >> base_directory_name;

        bool flag = validate_parameters::validate_file_for_file_system(base_directory_name);

        if (!flag)
        {
            while (!flag)
            {
                std::cout << "You entered the wrong directory name. Please enter another one: ";
                std::cin >> base_directory_name;

                flag = validate_parameters::validate_file_for_file_system(base_directory_name);

                if (flag)
                {
                    break;
                }
            }
        }

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

        std::cout << "You can enter these commands:\n"
                     "1) ADD_POOL and name pool\n"
                     "2) ADD_SCHEME and name pool + scheme name\n"
                     "3) ADD_COLLECTION and name pool + scheme name + collection name\n"
                     "4) ADD_VALUE and name pool + scheme name + collection name + key (id buyer) + values: name buyer, date oder, address pick-up point and id oder\n"
                     "5) DELETE_POOL and name pool\n"
                     "6) DELETE_SCHEME and name pool + scheme name\n"
                     "7) DELETE_COLLECTION and name pool + scheme name + collection name\n"
                     "8) DELETE_VALUE and name pool + scheme name + collection name + key (id buyer) - by the key (find a buyer), all values are deleted\n"
                     "9) UPDATE_VALUE and name pool + scheme name + collection name + key (id buyer) + values: name buyer, date oder, address pick-up point and id oder - you can chane value\n"
                     "10) FIND_VALUE and name pool + scheme name + collection name + key (id buyer)\n"
                     "11) FIND_BETWEEN_VALUE and name pool + scheme name + collection name + key (id buyer)\n" << std::endl;

        std::string line;
        std::cin >> line;

        if (line == "ADD_POOL")
        {
            log->trace("[command_add_value] find command_add_value");

            std::string pool_name;
            std::istringstream iss(line);

            iss >> pool_name;

            std::cout << pool_name << std::endl;

            try
            {
                pool_name = data_base_parse->validate_path(pool_name);
            }
            catch (const std::logic_error& e)
            {
                std::cerr << "error " << e.what() << std::endl;
            }

            std::string pool_directory_name;

            std::cout << "Please enter a pool directory name for data base: " << std::endl;
                std::cin >> base_directory_name;

            bool flag = validate_parameters::validate_file_for_file_system(base_directory_name);
            if (!flag)
            {
                while (!flag)
                {
                    std::cout << "You entered the wrong directory name. Please enter another one: ";
                    std::cin >> base_directory_name;

                    flag = validate_parameters::validate_file_for_file_system(base_directory_name);

                    if (flag)
                    {
                        break;
                    }
                }
            }


            if (!std::filesystem::exists(pool_directory_name))
            {
                try
                {
                    std::filesystem::create_directory(pool_directory_name);
                    log->trace("[command_add_value] directory " + pool_directory_name + " has created");
                }
                catch (const std::exception& e)
                {
                    log->error("[command_add_value] error creating the directory " + pool_directory_name);
                    std::cerr << "[command_add_value] error creating the directory " + pool_directory_name << e.what() << std::endl;
                }
            }

            try
            {
                data_base_parse->command_add_value(pool_name);
                log->debug("[command_add_value] the pool has been added successfully");
            }
            catch(const std::exception& error)
            {
                log->error("[command_add_value] error with add pool");
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
                log->debug("[command_add_value] the pool has been deleted successfully");
            }
            catch(const std::exception& error)
            {
                log->error("[command_add_value] error with add pool");
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
            std::tuple<long, long, std::string, std::string, std::string, int> result = serialization_for_dialog(input_file, log);

            long position = std::get<0>(result);
            long size = std::get<1>(result) + 1;
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
                    log->error("[add_value] error opening the file" + value_file_name);
                }

                log->trace("[add_value] file " + value_file_name + " has created");
                data_base_parse->add_value(pool_name, scheme_name, collection_name, id_buyer, value_file_name, position, size);
                log->debug("[add_value] the value has been added successfully");
            }
            catch(const std::exception& error)
            {
                log->error("[add_value] error with add value");
            }
        }
        else if (line == "UPDATE_VALUE")
        {
            log->trace("[update_value] find update_value");

            std::string pool_name;
            std::string scheme_name;
            std::string collection_name;
            int id_buyer;

            input_file >> pool_name >> scheme_name >> collection_name >> id_buyer;
            std::tuple<long, long, std::string, std::string, std::string, int> result = serialization_for_dialog(input_file, log);

            long position = std::get<0>(result);
            long size = std::get<1>(result) + 1;
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
                    log->error("[update_value] error opening the file" + value_file_name);
                }

                log->trace("[update_value] file " + value_file_name + " has created");
                data_base_parse->update_value(pool_name, scheme_name, collection_name, id_buyer, value_file_name, position, size);
                log->debug("[update_value] the value has been updated successfully");
            }
            catch(const std::exception& error)
            {
                log->error("[update_value] error with update value");
            }

        }
        else if (line == "FIND_VALUE")
        {
            log->trace("[find_value] find find_value");
            std::cout << "find find_value" << std::endl;

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
                value_file_system* value_file = reinterpret_cast<value_file_system*>(data_base_parse->obtain_value(pool_name, scheme_name, collection_name, key(id_buyer)));
                std::cout << "ohh nooo" << std::endl;
                std::streampos original_position = input_file.tellg();
                value_in_memory_cash value_memory = deserialization_for_dialog(input_file, value_file->_start_value_bytes, value_file->_string_size, log);
                input_file.seekg(original_position);
                log->information("[find_value] name: " + value_memory._name_buyer + ", date: " + value_memory._date + ", address: " + value_memory._address + ", id_oder: " + std::to_string(value_memory._id_order));
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
            int id_buyer;

            std::string id_buyer_string = std::to_string(id_buyer);

            input_file >> pool_name >> scheme_name >> collection_name >> id_buyer;

            std::string value_file_name = base_directory_name + "/" + pool_name + "/" + scheme_name + "/" + collection_name + "/" + id_buyer_string + ".txt";

            try
            {
                data_base_parse->obtain_value(pool_name, scheme_name, collection_name, key(id_buyer));
            }
            catch (const std::exception& e)
            {
                log->error("[find_value] error with find value");
            }

            if (std::remove(value_file_name.c_str()) != 0)
            {
                log->error("error deleting the file: " + value_file_name);
                std::cerr << "error deleting the file: " << value_file_name << std::endl;
            }
            else
            {
                log->trace("file has deleted successfully: " + value_file_name);
                std::cout << "file has deleted successfully: " << value_file_name << std::endl;
            }
        }
        else if (line == "FIND_BETWEEN_VALUE")
        {
            std::string pool_name;
            std::string scheme_name;
            std::string collection_name;

            input_file >> pool_name >> scheme_name >> collection_name;

        }
    }

public:

    ~dialog_file_system() = default;

    dialog_file_system(dialog_file_system const& other) = delete;

    dialog_file_system(dialog_file_system const&& other) = delete;

    dialog_file_system& operator=(dialog_file_system const& other) = delete;

    dialog_file_system& operator=(dialog_file_system const&& other) = delete;
};

#endif //COURSE_PROJECT_DIALOG_FILE_SYSTEM_H
