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

    bool can_execute(std::string const& request) noexcept override
    {
        logger_singleton::get_instance()->get_logger()->trace("start can_execute add value");

        std::istringstream string_with_commands(request);
        std::string command;
        string_with_commands >> command;

        if (command == "DELETE_VALUE")
        {
            std::string pool_name;
            std::string scheme_name;
            std::string collection_name;
            int id_buyer;
            string_with_commands >> pool_name >> scheme_name >> collection_name >> id_buyer;

            _pool_name = pool_name;
            _scheme_name = scheme_name;
            _collection_name = collection_name;
            _key = id_buyer;

            return true;
        }
        else return false;
    }

    void execute(std::string const& request) noexcept override
    {
        logger_singleton::get_instance()->get_logger()->trace("start execute add value");
        database::get_instance(3)->delete_value(_pool_name, _scheme_name, _collection_name, _key);

        std::string value_file_name = _pool_name + "/" + _scheme_name + "/" + _collection_name + "/" + std::to_string(_key) + ".txt";

        if (std::remove(value_file_name.c_str()) != 0)
        {
            logger_singleton::get_instance()->get_logger()->error("error deleting the file: " + value_file_name);
            std::cerr << "error deleting the file: " << value_file_name << std::endl;
        }
        else
        {
            logger_singleton::get_instance()->get_logger()->trace("file has deleted successfully: " + value_file_name);
            std::cout << "file has deleted successfully: " << value_file_name << std::endl;
        }

        file_save file;
        file.file_for_save("DELETE_VALUE " + _pool_name + " " + _scheme_name + " " + _collection_name + " " + std::to_string(_key));

        command* new_command = new command_delete_value();
        request_handler_with_command handler(new_command);

        handler.write_time_to_file(request);

        logger_singleton::get_instance()->get_logger()->trace("finish execute add value");
    }
};

#endif //COURSE_PROJECT_COMMAND_DELETE_VALUE_H
