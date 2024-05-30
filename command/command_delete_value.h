#ifndef COURSE_PROJECT_COMMAND_DELETE_VALUE_H
#define COURSE_PROJECT_COMMAND_DELETE_VALUE_H
#include "command.h"
#include "../containers/database.h"

class command_delete_value final :
        public command
{

private:

    std::string _pool_name;
    std::string _scheme_name;
    std::string _collection_name;

    int _key;

public:

    command_delete_value()
    {

    }

    command_delete_value(std::string& pool_name, std::string& scheme_name, std::string& collection_name,
                         int key) :
                                _key(key),
                                _pool_name(pool_name),
                                _scheme_name(scheme_name),
                                _collection_name(collection_name)
    {

    }

    command_delete_value(std::string& pool_name, std::string& scheme_name, std::string& collection_name,
                         int key, std::string& name, std::string& date, std::string& address,
                         int id_order) :
                                _key(key),
                                _pool_name(pool_name),
                                _scheme_name(scheme_name),
                                _collection_name(collection_name)
    {

    }

public:

    bool can_execute(std::string const& request) noexcept override
    {
        logger_singleton::get_instance()->get_logger()->trace("start can_execute add value");

        std::istringstream string_with_commands(request);
        std::string command;
        string_with_commands >> command;

        if (command == "DELETE_VALUE")
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

            string_with_commands >> pool_name >> scheme_name >> collection_name >> id_buyer;

            _key = id_buyer;


            file_save << command << " " <<  pool_name << " " << scheme_name << " " << collection_name << " " << id_buyer;
            file_save.close();
        }
    }

    void execute(std::string const& request) noexcept override
    {
        logger_singleton::get_instance()->get_logger()->trace("start execute add value");
        database::get_instance(3)->delete_value(_pool_name, _scheme_name, _collection_name, _key);

        file_save file;
        file.file_for_save("DELETE_VALUE " + _pool_name + " " + _scheme_name + " " + _collection_name + " " + std::to_string(_key));

        logger_singleton::get_instance()->get_logger()->trace("finish execute add value");
    }
};

#endif //COURSE_PROJECT_COMMAND_DELETE_VALUE_H
