#ifndef COURSE_PROJECT_COMMAND_ADD_POOL_H
#define COURSE_PROJECT_COMMAND_ADD_POOL_H
#include "command.h"
#include "../containers/database.h"
#include "file_save.h"
#include <filesystem>
//
class command_add_pool final :
        public command
{

private:

    std::string _pool_name;

public:

    command_add_pool() = default;

public:

    bool can_execute(std::string const& request) noexcept override
    {
        logger_singleton::get_instance()->get_logger()->trace("can_execute has started in command_add_pool");

        std::istringstream string_with_commands(request);
        std::string command;
        string_with_commands >> command;

        if (command == "ADD_POOL")
        {
            std::string pool_name;
            string_with_commands >> pool_name;
            logger_singleton::get_instance()->get_logger()->information("pool name: " + pool_name);

            _pool_name = pool_name;

            logger_singleton::get_instance()->get_logger()->trace("can_execute has finished in command add pool");
            return true;
        }
        else return false;
    }

    void execute(std::string const& request) noexcept override
    {
        logger_singleton::get_instance()->get_logger()->trace("execute has started in command add pool");
        database::get_instance(3)->add_pool(_pool_name);

        if (database::get_instance(3)->get_mode() == enums::mode::file_system)
        {
            std::string pool_directory_name = _pool_name;

            if (!std::filesystem::exists(pool_directory_name))
            {
                try
                {
                    std::filesystem::create_directory(pool_directory_name);
                    logger_singleton::get_instance()->get_logger()->trace(
                            "[command_add_pool] directory " + pool_directory_name + " has created");
                }
                catch (const std::exception &e)
                {
                    logger_singleton::get_instance()->get_logger()->error(
                            "[command_add_pool] error creating the directory " + pool_directory_name);
                    std::cerr << "[command_add_value] error creating the directory " + pool_directory_name + " "
                              << e.what() << std::endl;
                }
            }
        }

        if (database::get_instance(3)->get_restore() == false)
        {
            file_save file;
            file.file_for_save("ADD_POOL " + _pool_name);
        }

        logger_singleton::get_instance()->get_logger()->trace("execute has finished in command add pool");
    }
};

#endif //COURSE_PROJECT_COMMAND_ADD_POOL_H
