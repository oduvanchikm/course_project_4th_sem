#ifndef COURSE_PROJECT_COMMAND_FIND_TIME_VALUE_H
#define COURSE_PROJECT_COMMAND_FIND_TIME_VALUE_H
#include "command.h"
#include "../chain__of_resposibility/request_with_command.h"
#include "../chain__of_resposibility/request_with_command_chain.h"


class command_find_time_value final :
        public command
{
private:

    std::string _pool_name;
    std::string _scheme_name;
    std::string _collection_name;
    std::string _time;
    std::string _date;

public:

    bool can_execute(std::string const& request) noexcept override
    {
        logger_singleton::get_instance()->get_logger()->trace("start can_execute add value");

        std::istringstream string_with_commands(request);
        std::string command;
        string_with_commands >> command;

        if (command == "FIND_VALUE_IN_TIME")
        {
            std::string pool_name;
            std::string scheme_name;
            std::string collection_name;
            std::string time;
            std::string date;

            string_with_commands >> pool_name >> scheme_name >> collection_name >> date >> time;

            _pool_name = pool_name;
            _scheme_name = scheme_name;
            _collection_name = collection_name;
            _time = time;
            _date = date;

            return true;
        }
        else return false;
    }

    void execute(std::string const& request) noexcept override
    {
        logger_singleton::get_instance()->get_logger()->trace("start execute add value");
        file_save file;

        std::ifstream file_time("time_log.txt");
        if (!file_time.is_open())
        {
            throw file_error("error with opening file");
        }

        if (database::get_instance(3)->get_restore() == false)
        {
            file.file_for_save(
                    "FIND_VALUE_IN_TIME " + _pool_name + " " + _scheme_name + " " + _collection_name + " " + _date +
                    " " + _time);
        }

        logger_singleton::get_instance()->get_logger()->trace("execute command update value, memory cache mode");

        std::string line;
        logger_singleton::get_instance()->get_logger()->information("all version: ");

        while (std::getline(file_time, line))
        {
            std::istringstream string_line(line);
            std::string date;
            std::string time;
            string_line >> date >> time;

            if (time == _time && date == _date)
            {
                logger_singleton::get_instance()->get_logger()->information(line);
            }
        }

        logger_singleton::get_instance()->get_logger()->information("end");

        file_time.close();
    }

};

#endif //COURSE_PROJECT_COMMAND_FIND_TIME_VALUE_H
