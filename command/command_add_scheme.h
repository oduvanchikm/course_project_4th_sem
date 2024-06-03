#ifndef COURSE_PROJECT_COMMAND_ADD_SCHEME_H
#define COURSE_PROJECT_COMMAND_ADD_SCHEME_H
#include "command.h"

class command_add_scheme final :
        public command
{

private:

    std::string _pool_name;
    std::string _scheme_name;

public:

    bool can_execute(std::string const& request) noexcept override
    {
        logger_singleton::get_instance()->get_logger()->trace("start can execute in command add scheme");

        std::istringstream string_with_commands(request);
        std::string command;
        string_with_commands >> command;

        if (command == "ADD_SCHEME")
        {
            std::string pool_name;
            std::string scheme_name;
            string_with_commands >> pool_name >> scheme_name;

            logger_singleton::get_instance()->get_logger()->information("pool name: " + pool_name + ", scheme name: " + scheme_name);

            _pool_name = pool_name;
            _scheme_name = scheme_name;

            logger_singleton::get_instance()->get_logger()->trace("finish can execute in command add scheme");

            return true;
        }
        else return false;
    }

    void execute(std::string const& request) noexcept override
    {
        logger_singleton::get_instance()->get_logger()->trace("execute has started in command add scheme");
        database::get_instance(3)->add_scheme(_pool_name, _scheme_name);

        if (database::get_instance(3)->get_mode() == enums::mode::file_system)
        {
            std::string scheme_directory_name = _pool_name + "/" + _scheme_name;

            if (!std::filesystem::exists(scheme_directory_name))
            {
                try
                {
                    std::filesystem::create_directory(scheme_directory_name);
                    logger_singleton::get_instance()->get_logger()->trace("directory " + scheme_directory_name + " has created");
                }
                catch (const std::exception& e)
                {
                    logger_singleton::get_instance()->get_logger()->error("error creating the directory " + scheme_directory_name);
                    std::cerr << "error creating the directory " + scheme_directory_name << e.what() << std::endl;
                }
            }
        }

        if (database::get_instance(3)->get_restore() == false)
        {
            file_save file;
            file.file_for_save("ADD_SCHEME " + _pool_name + " " + _scheme_name);
        }

        logger_singleton::get_instance()->get_logger()->trace("execute has finished in command add scheme");
    }
};


#endif //COURSE_PROJECT_COMMAND_ADD_SCHEME_H
