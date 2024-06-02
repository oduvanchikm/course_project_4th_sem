#ifndef COURSE_PROJECT_COMMAND_UPDATE_VALUE_H
#define COURSE_PROJECT_COMMAND_UPDATE_VALUE_H
#include "command.h"
#include "../chain__of_resposibility/request_with_command.h"
#include "../chain__of_resposibility/request_with_command_chain.h"

class command_update_value final :
        public command
{

private:

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

    bool can_execute(std::string const& request) noexcept override
    {
        logger_singleton::get_instance()->get_logger()->trace("start can_execute add value");

        std::istringstream string_with_commands(request);
        std::string command;
        string_with_commands >> command;

        if (command == "UPDATE_VALUE")
        {
            std::string pool_name;
            std::string scheme_name;
            std::string collection_name;
            int id_buyer;

            std::string name;
            std::string address;
            std::string date;
            int id_order;

            string_with_commands >> pool_name >> scheme_name >> collection_name >> id_buyer >> name >> date >> address >> id_order;

            _pool_name = pool_name;
            _scheme_name = scheme_name;
            _collection_name = collection_name;
            _name = name;
            _date = date;
            _address = address;
            _key = id_buyer;
            _id_order = id_order;

            return true;
        }
        else return false;
    }

    void execute(std::string const& request) noexcept override
    {
        logger_singleton::get_instance()->get_logger()->trace("start execute update value");
        file_save file;

        if (database::get_instance(3)->get_mode() == enums::mode::file_system)
        {
            std::string command = "UPDATE_VALUE";
            std::pair<long, long> result = file.file_for_save_with_serialization(command, _pool_name, _scheme_name, _collection_name,
                                                                                 std::to_string(_key), _name, _date, _address, std::to_string(_id_order));
            _position = result.first;
            _size = result.second;

            std::string value_file_name = _pool_name + "/" + _scheme_name + "/" + _collection_name + "/" + std::to_string(_key) + ".txt";

            try
            {
                std::ofstream file_other(value_file_name, std::ios::trunc);
                if (file_other.is_open())
                {
                    file_other << _name << " " << _date << " " << _address << " " << _id_order << std::endl;
                }
                else
                {
                    logger_singleton::get_instance()->get_logger()->error("[update_value] error opening the file" + value_file_name);
                }

                logger_singleton::get_instance()->get_logger()->trace("[update_value] file " + value_file_name + " has created");
                database::get_instance(3)->update_value(_pool_name, _scheme_name, _collection_name, _key, _position, _size);
                logger_singleton::get_instance()->get_logger()->debug("[add_value] the value has been added successfully");
            }
            catch(const std::exception& error)
            {
                logger_singleton::get_instance()->get_logger()->error("[update_value] error with add value");
            }
        }
        else
        {
            file.file_for_save("UPDATE_VALUE " + _pool_name + " " + _scheme_name + " " + _collection_name + " " + std::to_string(_key) +
                               " " + _name + " " + _date + " " + _address + " " + std::to_string(_id_order));

            logger_singleton::get_instance()->get_logger()->trace("execute command update value, memory cache mode");
            database::get_instance(3)->update_value(_pool_name, _scheme_name, _collection_name, _key,
                                                 _name, _date, _address, _id_order);
        }

        command* new_command = new command_update_value();
        request_with_command handler(new_command);

        handler.write_time_to_file(request);

        logger_singleton::get_instance()->get_logger()->trace("finish execute update value");
    }
};

#endif //COURSE_PROJECT_COMMAND_UPDATE_VALUE_H
