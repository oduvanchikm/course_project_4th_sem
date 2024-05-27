#ifndef COURSE_PROJECT_COMMAND_ADD_VALUE_H
#define COURSE_PROJECT_COMMAND_ADD_VALUE_H
#include "command.h"

class command_add_value final :
        public command
{

private:

//    logger_guardant* _logger_guardant_command;

    logger* _logger;

    std::string _pool_name;
    std::string _scheme_name;
    std::string _collection_name;

    std::string _name;
    std::string _address;
    std::string _date;
    int _key;
    int _id_order;

    long _position;
    long _size;

public:

    command_add_value()
    {

    }

    command_add_value(std::string& pool_name, std::string& scheme_name, std::string& collection_name,
                      int key, long position, long size, logger* logger_command) :
                            _logger(logger_command),
                            _key(key),
                            _position(position),
                            _size(size),
                            _pool_name(pool_name),
                            _scheme_name(scheme_name),
                            _collection_name(collection_name)
    {

    }

    command_add_value(std::string& pool_name, std::string& scheme_name, std::string& collection_name,
                      int key, std::string& name, std::string& date, std::string& address,
                      int id_order, logger* logger_command) :
                            _logger(logger_command),
                            _key(key),
                            _address(address),
                            _date(date),
                            _name(name),
                            _id_order(id_order),
                            _pool_name(pool_name),
                            _scheme_name(scheme_name),
                            _collection_name(collection_name)
    {

    }

public:

    bool can_execute(std::string const& request) noexcept override
    {
        _logger->trace("start can_execute add value");

        std::istringstream string_with_commands(request);
        std::string command;
        string_with_commands >> command;

        if (command == "ADD_VALUE")
        {
            std::ofstream file_save(FILE_SAVE, std::ios::app);
            if (!file_save.is_open())
            {
                _logger->error("error with opening file for saving data");
                return false;
            }

            std::string pool_name;
            std::string scheme_name;
            std::string collection_name;
            int id_buyer;

            std::string name;
            std::string address;
            std::string date;
            int id_order;

            if (database::get_instance(3)->get_mode() == enums::mode::file_system)
            {
                string_with_commands >> pool_name >> scheme_name >> collection_name >> id_buyer;

                _name = name;
                _date = date;
                _address = address;
                _key = id_buyer;
                _id_order = id_order;

                string_with_commands >> name >> date >> address >> id_order;
            }
            else
            {
                string_with_commands >> pool_name >> scheme_name >> collection_name >> id_buyer >> name >> date >> address >> id_order;

                _name = name;
                _date = date;
                _address = address;
                _key = id_buyer;
                _id_order = id_order;
            }

            file_save << command << " " <<  pool_name << " " << scheme_name << " " << collection_name << " " << id_buyer << " " << name << " " << date << " " << address << " " << std::to_string(id_order) << std::endl;
            file_save.close();
        }
    }

    void execute(std::string const& request) noexcept override
    {
        _logger->trace("start execute add value");

        if (database::get_instance(3)->get_mode() == enums::mode::file_system)
        {
            database::get_instance(3)->add_value(_pool_name, _scheme_name, _collection_name, _key, _position, _size);
        }
        else
        {
            database::get_instance(3)->add_value(_pool_name, _scheme_name, _collection_name, _key,
                           _name, _date, _address, _id_order);
        }

        _logger->trace("finish execute add value");
    }
};

#endif //COURSE_PROJECT_COMMAND_ADD_VALUE_H
