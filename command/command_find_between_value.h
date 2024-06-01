#ifndef COURSE_PROJECT_COMMAND_FIND_BETWEEN_VALUE_H
#define COURSE_PROJECT_COMMAND_FIND_BETWEEN_VALUE_H
#include "command.h"
#include "file_save.h"

class command_find_between_value final :
        public command
{

private:

    std::string _pool_name;
    std::string _scheme_name;
    std::string _collection_name;

    int _id_min;
    int _id_max;
    bool _is_inclusive_lower;
    bool _is_inclusive_upper;

public:

    bool can_execute(std::string const& request) noexcept override
    {
        logger_singleton::get_instance()->get_logger()->trace("start can_execute add value");

        std::istringstream string_with_commands(request);
        std::string command;
        string_with_commands >> command;

        if (command == "FIND_BETWEEN_VALUE")
        {
            std::string pool_name;
            std::string scheme_name;
            std::string collection_name;
            int id_min, id_max;
            bool is_inclusive_lower, is_inclusive_upper;

            string_with_commands >> pool_name >> scheme_name >> collection_name >> id_min >> id_max >> is_inclusive_lower >> is_inclusive_upper;

            _pool_name = pool_name;
            _scheme_name = scheme_name;
            _collection_name = collection_name;
            _id_max = id_max;
            _id_min = id_min;
            _is_inclusive_lower = is_inclusive_lower;
            _is_inclusive_upper = is_inclusive_upper;

            return true;
        }
        else return false;
    }

    void execute(std::string const& request) noexcept override
    {
        logger_singleton::get_instance()->get_logger()->trace("start execute find between value");
        std::vector<value*> vector = database::get_instance(3)->obtain_between_value(_pool_name, _scheme_name, _collection_name, _id_min, _id_max, _is_inclusive_lower, _is_inclusive_upper);
        file_save file;

        if (database::get_instance(3)->get_mode() == enums::mode::file_system)
        {
            std::vector<value*> vector = database::get_instance(3)->obtain_between_value(_pool_name, _scheme_name, _collection_name, _id_min, _id_max, _is_inclusive_lower, _is_inclusive_upper);
            logger_singleton::get_instance()->get_logger()->trace("Vector: < start >");

            for(value* each : vector)
            {
                for (unsigned int i = _id_min; i < _id_max; ++i)
                {
                    value_file_system* value_file = reinterpret_cast<value_file_system*>(each);

                    std::string file_path = _pool_name + "/" + _scheme_name + "/" + _collection_name + "/" + std::to_string(i) + ".txt";
                    value_in_memory_cache value_memory = file.deserialization(_pool_name, _scheme_name, _collection_name, std::to_string(i), value_file->_start_value_bytes, value_file->_string_size);

                    logger_singleton::get_instance()->get_logger()->information("[find_value] name: " + value_memory._name_buyer + ", date: " + value_memory._date + ", address: " + value_memory._address + ", id_oder: " + std::to_string(value_memory._id_order));
                }
            }

            logger_singleton::get_instance()->get_logger()->trace("Vector: < end >");
        }
        else
        {
            key data_key_min(_id_min);
            key data_key_max(_id_max);

            std::vector<value*> vector = database::get_instance(3)->obtain_between_value(_pool_name, _scheme_name, _collection_name, _id_min, _id_max, _is_inclusive_lower, _is_inclusive_upper);
            logger_singleton::get_instance()->get_logger()->trace("Vector: < start >");

            for(value* each : vector)
            {
                value_in_memory_cache* value_memory = reinterpret_cast<value_in_memory_cache*>(each);
                logger_singleton::get_instance()->get_logger()->information("[find_value] name: " + value_memory->_name_buyer + ", date: " + value_memory->_date + ", address: " + value_memory->_address + ", id_oder: " + std::to_string(value_memory->_id_order));
            }
            logger_singleton::get_instance()->get_logger()->trace("Vector: < end >");
        }

        file.file_for_save("FIND_BETWEEN_VALUE " + _pool_name + " " + _scheme_name + " " + _collection_name + " " + std::to_string(_id_min) + " " + std::to_string(_id_max) + " " + std::to_string(_is_inclusive_lower) + " " + std::to_string(_is_inclusive_upper));

        command* new_command = new command_find_between_value();
        request_handler_with_command handler(new_command);

        handler.write_time_to_file(request);

        logger_singleton::get_instance()->get_logger()->trace("finish execute add value");
    }
};

#endif //COURSE_PROJECT_COMMAND_FIND_BETWEEN_VALUE_H
