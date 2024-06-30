#ifndef COURSE_PROJECT_FILE_SAVE_H
#define COURSE_PROJECT_FILE_SAVE_H
#include <iostream>
#include <fstream>
#include "../logger/logger_singleton.h"
#include "../containers/database.h"
//
class file_save
{

private:

    std::string _file_name;

public:

    file_save() = default;

public:

    file_save(file_save const& other) = delete;

    file_save(file_save const&& other) = delete;

    file_save& operator=(file_save const& other) = delete;

    file_save& operator=(file_save const&& other) = delete;

public:

    void file_for_save(std::string const& request)
    {
        logger_singleton::get_instance()->get_logger()->trace("hello");
        _file_name = "file_save.txt";

        std::ofstream file_save(_file_name, std::ios::app);

        if (!file_save.is_open())
        {
            logger_singleton::get_instance()->get_logger()->error("error with opening file for saving data");
            throw file_error("error with opening file");
        }

        file_save << request << std::endl;
        file_save.close();
    }

    std::pair<long, long> file_for_save_with_serialization(std::string const& command, std::string const& pool_name, std::string const& scheme_name,
                                          std::string const& collection_name, std::string const& key,
                                          std::string const& name, std::string const& date, std::string const& address,
                                          std::string const& id_order)
    {
        logger_singleton::get_instance()->get_logger()->trace("hello");
        std::pair<long, long> result;
        _file_name = "file_save.txt";

        std::ofstream file_save(_file_name, std::ios::app);

        if (!file_save.is_open())
        {
            logger_singleton::get_instance()->get_logger()->error("error with opening file for saving data");
            throw file_error("error with opening file");
        }

        file_save << command << " " << pool_name << " " << scheme_name << " " << collection_name << " " << key << " ";

        std::streampos position_first = file_save.tellp();
        logger_singleton::get_instance()->get_logger()->information("first position: " + std::to_string(position_first));

        file_save << name << " " << date << " " << address << " ";

        std::streampos new_position = file_save.tellp();

        logger_singleton::get_instance()->get_logger()->information("last position: " + std::to_string(new_position));

        file_save << id_order;
        std::cout << id_order << std::endl;

        long size_id_oder = (id_order.size());

        long data_size = static_cast<long>(new_position - position_first) + size_id_oder;

        logger_singleton::get_instance()->get_logger()->information("size: " + std::to_string(data_size));

        result.first = position_first;
        result.second = data_size;

        file_save.close();

        return result;
    }

    value_in_memory_cache deserialization(std::string const& pool_name, std::string const& scheme_name,
                                          std::string const& collection_name, std::string const& key,
                                          long position, long size)
    {
        logger_singleton::get_instance()->get_logger()->trace("start deserialization method");
        _file_name = "file_save.txt";
        logger_singleton::get_instance()->get_logger()->trace("file name: " + _file_name);

        std::ifstream file_save(_file_name);

        if (!file_save.is_open())
        {
            logger_singleton::get_instance()->get_logger()->error("error with opening file for saving data");
            throw file_error("error with opening file");
        }

        file_save.seekg(position);

        char* buffer = new char[size];
        file_save.read(buffer, size);

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

    void clean_file()
    {
        std::ofstream ofs;
        _file_name = "file_save.txt";
        ofs.open(_file_name, std::ofstream::out | std::ofstream::trunc);
        ofs.close();
    }


};

#endif //COURSE_PROJECT_FILE_SAVE_H
