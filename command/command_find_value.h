#ifndef COURSE_PROJECT_COMMAND_FIND_VALUE_H
#define COURSE_PROJECT_COMMAND_FIND_VALUE_H
#include "command.h"

class command_find_value final :
        public command
{

private:

    std::string _pool_name;
    std::string _scheme_name;
    std::string _collection_name;

    int _key;

    value* _result;

public:

    value* get_result() const
    {
        return _result;
    }

public:

    command_find_value()
    {

    }

    command_find_value(std::string& pool_name, std::string& scheme_name, std::string& collection_name,
                         int key) :
                                _key(key),
                                _pool_name(pool_name),
                                _scheme_name(scheme_name),
                                _collection_name(collection_name)
    {
        _result = nullptr;
    }

public:

    bool can_execute(std::string const& request) noexcept override
    {
        logger_singleton::get_instance()->get_logger()->trace("start can_execute add value");

        std::istringstream string_with_commands(request);
        std::string command;
        string_with_commands >> command;

        if (command == "FIND_VALUE")
        {
            std::ofstream file_save(FILE_SAVE, std::ios::app);
            if (!file_save.is_open())
            {
                logger_singleton::get_instance()->get_logger()->error("error with opening file for saving data");
                return false;
            }

            std::string pool_name;
            std::string scheme_name;
            std::string collection_name;
            int id_buyer;

            _key = id_buyer;

            file_save << command << " " <<  pool_name << " " << scheme_name << " " << collection_name << " " << id_buyer << std::endl;
            file_save.close();
        }
    }

    void execute(std::string const& request) noexcept override
    {
        logger_singleton::get_instance()->get_logger()->trace("start execute add value");
        _result = database::get_instance(3)->obtain_value(_pool_name, _scheme_name, _collection_name, _key);

        file_save file;
        file.file_for_save("FIND_VALUE " + _pool_name + " " + _scheme_name + " " + _collection_name + " " + std::to_string(_key));

        logger_singleton::get_instance()->get_logger()->trace("finish execute add value");
    }
};

#endif //COURSE_PROJECT_COMMAND_FIND_VALUE_H
