#ifndef COURSE_PROJECT_COMMAND_DELETE_POOL_H
#define COURSE_PROJECT_COMMAND_DELETE_POOL_H
#include "command.h"
//
class command_delete_pool final :
        public command
{

private:

    std::string _pool_name;

public:

    command_delete_pool() = default;

public:

    bool can_execute(std::string const& request) noexcept override
    {
        logger_singleton::get_instance()->get_logger()->trace("start can_execute delete pool");

        std::istringstream string_with_commands(request);
        std::string command;
        string_with_commands >> command;

        if (command == "DELETE_POOL")
        {
            std::string pool_name;
            string_with_commands >> pool_name;

            logger_singleton::get_instance()->get_logger()->information("pool name: " + pool_name);
            _pool_name = pool_name;

            return true;
        }
        else return false;
    }

    void execute(std::string const& request) noexcept override
    {
        logger_singleton::get_instance()->get_logger()->trace("start execute delete pool");
        database::get_instance(3)->delete_pool(_pool_name);

        if (database::get_instance(3)->get_mode() == enums::mode::file_system)
        {
            std::string pool_directory_name = _pool_name;

            if (std::filesystem::exists(pool_directory_name))
            {
                try
                {
                    std::filesystem::remove_all(pool_directory_name);
                    logger_singleton::get_instance()->get_logger()->trace("directory " + pool_directory_name + " has deleted");
                }
                catch (const std::exception &e)
                {
                    logger_singleton::get_instance()->get_logger()->error("error deleting the directory " + pool_directory_name);
                    std::cerr << "error deleting the directory " + pool_directory_name << e.what() << std::endl;
                }
            }
        }

        if (database::get_instance(3)->get_restore() == false)
        {
            file_save file;
            file.file_for_save("DELETE_POOL " + _pool_name);
        }

        logger_singleton::get_instance()->get_logger()->trace("finish execute delete pool");
    }
};

#endif //COURSE_PROJECT_COMMAND_DELETE_POOL_H
