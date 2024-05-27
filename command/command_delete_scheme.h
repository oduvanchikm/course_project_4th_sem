#ifndef COURSE_PROJECT_COMMAND_DELETE_SCHEME_H
#define COURSE_PROJECT_COMMAND_DELETE_SCHEME_H
#include "command.h"

class command_delete_scheme final :
        public command
{

private:

//    logger_guardant* _logger_guardant_command;
    logger* _logger;
    std::string _pool_name;
    std::string _scheme_name;

public:

    command_delete_scheme()
    {

    }

    command_delete_scheme(std::string& pool_name, std::string& scheme_name, logger* log) :
                        _pool_name(pool_name),
                        _logger(log),
                        _scheme_name(scheme_name)
    {

    }

public:

    bool can_execute(std::string const& request) noexcept override
    {
        if (_logger != nullptr)
        {
            _logger->trace("start can_execute delete scheme");
        }

        std::istringstream string_with_commands(request);
        std::string command;
        string_with_commands >> command;

        if (command == "DELETE_SCHEME")
        {
            std::ofstream file_save(FILE_SAVE, std::ios::app);
            if (!file_save.is_open())
            {
                if (_logger != nullptr)
                {
                    _logger->error("error with opening file for saving data");
                }
                return false;
            }

            std::string pool_name;
            std::string scheme_name;
            string_with_commands >> pool_name >> scheme_name;

            if (_logger != nullptr)
            {
                _logger->information("pool name: " + pool_name + ", scheme name: " + scheme_name);
            }
            _pool_name = pool_name;

            file_save << command << " " <<  pool_name << " " << scheme_name << std::endl;
            file_save.close();
        }

        return true;
    }

    void execute(std::string const& request) noexcept override
    {
        if (_logger != nullptr)
        {
            _logger->trace("start execute delete scheme");
        }

        database::get_instance(3)->delete_scheme(_pool_name, _scheme_name);

        if (_logger != nullptr)
        {
            _logger->trace("finish execute delete scheme");
        }

    }
};

#endif //COURSE_PROJECT_COMMAND_DELETE_SCHEME_H
