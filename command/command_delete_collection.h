#ifndef COURSE_PROJECT_COMMAND_DELETE_COLLECTION_H
#define COURSE_PROJECT_COMMAND_DELETE_COLLECTION_H
#include "command.h"
//
class command_delete_collection final :
        public command
{

private:

    std::string _pool_name;
    std::string _scheme_name;
    std::string _collection_name;

public:

    bool can_execute(std::string const& request) noexcept override
    {
        logger_singleton::get_instance()->get_logger()->trace("start can_execute delete scheme");

        std::istringstream string_with_commands(request);
        std::string command;
        string_with_commands >> command;

        if (command == "DELETE_COLLECTION")
        {
            std::string pool_name;
            std::string scheme_name;
            std::string collection_name;

            string_with_commands >> pool_name >> scheme_name >> collection_name;

            logger_singleton::get_instance()->get_logger()->information("pool name: " + pool_name + ", scheme name: " + scheme_name +
                                                                ", collection name: " + collection_name);
            _pool_name = pool_name;
            _scheme_name = scheme_name;
            _collection_name = collection_name;

            return true;
        }
        else return false;
    }

    void execute(std::string const& request) noexcept override
    {
        logger_singleton::get_instance()->get_logger()->trace("start execute delete collection");

        if (database::get_instance(3)->get_mode() == enums::mode::file_system)
        {
            std::string collection_directory_name = _pool_name + "/" + _scheme_name + "/" + _collection_name;

            if (std::filesystem::exists(collection_directory_name))
            {
                try
                {
                    std::filesystem::remove_all(collection_directory_name);
                    logger_singleton::get_instance()->get_logger()->trace("directory " + collection_directory_name + " has deleted");
                }
                catch (const std::exception& e)
                {
                    logger_singleton::get_instance()->get_logger()->error("error deleting the directory " + collection_directory_name);
                    std::cerr << "error deleting the directory " + collection_directory_name << e.what() << std::endl;
                }
            }
        }

        database::get_instance(3)->delete_collection(_pool_name, _scheme_name, _collection_name);

        if (database::get_instance(3)->get_restore() == false)
        {
            file_save file;
            file.file_for_save("DELETE_COLLECTION " + _pool_name + " " + _scheme_name + " " + _collection_name);
        }

        logger_singleton::get_instance()->get_logger()->trace("finish execute delete collection");
    }
};

#endif //COURSE_PROJECT_COMMAND_DELETE_COLLECTION_H
