#ifndef COURSE_PROJECT_COMMAND_ADD_COLLECTION_H
#define COURSE_PROJECT_COMMAND_ADD_COLLECTION_H
#include "command.h"

class command_add_collection final :
        public command
{

private:

    std::string _pool_name;
    std::string _scheme_name;
    std::string _collection_name;

    allocator_types _type;
    allocator_with_fit_mode::fit_mode _fit_mode;
    std::string _all_type_string;
    std::string _all_fit_mode_string;

public:

    bool can_execute(std::string const& request) noexcept override
    {
        logger_singleton::get_instance()->get_logger()->trace("start can_execute add collection");

        std::istringstream string_with_commands(request);
        std::string command;
        string_with_commands >> command;

        if (command == "ADD_COLLECTION")
        {
            std::string pool_name;
            std::string scheme_name;
            std::string collection_name;

            std::string allocator_type;
            std::string allocator_fit_mode;

            allocator* allocator_database;
            allocator_types type;
            allocator_with_fit_mode::fit_mode fit_mode;

            string_with_commands >> pool_name >> scheme_name >> collection_name >> allocator_fit_mode >> allocator_type;
            std::cout << "op " << pool_name << " " << scheme_name << " " << collection_name << " " << allocator_fit_mode << " " << allocator_type << std::endl;

            logger_singleton::get_instance()->get_logger()->information("pool name: " + pool_name + ", scheme name: " + scheme_name +
                                    ", collection name: " + collection_name + ", allocator fit mode: " + allocator_fit_mode +
                                    ", allocator type: " + allocator_type);

            if (allocator_type == "sorted_list")
            {
                _type = allocator_types::SORTED_LIST;
            }
            else if (allocator_type == "global_heap")
            {
                _type = allocator_types::GLOBAL_HEAP;
            }
            else if (allocator_type == "buddie_system")
            {
                _type = allocator_types::BUDDIE_SYSTEM;
            }
            else if (allocator_type == "boundary_tags")
            {
                _type = allocator_types::BOUNDARY_TAGS;
            }
            else
            {
                logger_singleton::get_instance()->get_logger()->error("[add_collection] wrong allocator type");
            }

            if (allocator_fit_mode == "the_best_fit")
            {
                _fit_mode = allocator_with_fit_mode::fit_mode::the_best_fit;
            }
            else if (allocator_fit_mode == "the_worst_fit")
            {
               _fit_mode = allocator_with_fit_mode::fit_mode::the_worst_fit;
            }
            else if (allocator_fit_mode == "first_fit")
            {
                _fit_mode = allocator_with_fit_mode::fit_mode::first_fit;
            }
            else
            {
                logger_singleton::get_instance()->get_logger()->error("[add_collection] wrong allocator fit mode");
            }

            _pool_name = pool_name;
            _scheme_name = scheme_name;
            _collection_name = collection_name;
            _all_type_string = allocator_type;
            _all_fit_mode_string = allocator_fit_mode;

            return true;
        }
        else return false;
    }

    void execute(std::string const& request) noexcept override
    {
        logger_singleton::get_instance()->get_logger()->trace("start execute add collection");
        database::get_instance(3)->add_collection(_pool_name, _scheme_name, _collection_name, _type, _fit_mode);

        if (database::get_instance(3)->get_mode() == enums::mode::file_system)
        {
            std::string collection_directory_name = _pool_name + "/" + _scheme_name + "/" + _collection_name;

            if (!std::filesystem::exists(collection_directory_name))
            {
                try
                {
                    std::filesystem::create_directory(collection_directory_name);
                    logger_singleton::get_instance()->get_logger()->trace("directory " + collection_directory_name + " has created");
                }
                catch (const std::exception& e)
                {
                    logger_singleton::get_instance()->get_logger()->error("error creating the directory " + collection_directory_name);
                    std::cerr << "error creating the directory " + collection_directory_name << e.what() << std::endl;
                }
            }
        }

        if (database::get_instance(3)->get_restore() == false)
        {
            file_save file;
            std::string res = "ADD_COLLECTION " + _pool_name + " " + _scheme_name + " " + _collection_name + " " +
                              _all_fit_mode_string + " " + _all_type_string;
            std::cout << res << std::endl;
            // mode, type
            file.file_for_save(res);
        }

        logger_singleton::get_instance()->get_logger()->trace("finish execute add collection");
    }
};

#endif //COURSE_PROJECT_COMMAND_ADD_COLLECTION_H
