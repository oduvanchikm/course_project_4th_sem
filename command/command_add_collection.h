#ifndef COURSE_PROJECT_COMMAND_ADD_COLLECTION_H
#define COURSE_PROJECT_COMMAND_ADD_COLLECTION_H

#include "command.h"

class command_add_collection final :
        public command
{

private:

//    logger_guardant* _logger_guardant_command;
    logger* _logger;

    std::string _pool_name;
    std::string _scheme_name;
    std::string _collection_name;

    allocator_types _type;
    allocator_with_fit_mode::fit_mode _fit_mode;

public:

    command_add_collection()
    {

    }

    command_add_collection(std::string& pool_name, std::string& scheme_name,
                           std::string& collection_name, allocator_types type, allocator_with_fit_mode::fit_mode fit_mode,
                           logger* log) :
                                _logger(log),
                                _type(type),
                                _fit_mode(fit_mode),
                                _scheme_name(scheme_name),
                                _pool_name(pool_name),
                                _collection_name(collection_name)
    {

    }

public:

    bool can_execute(std::string const& request) noexcept override
    {
        _logger->trace("start can_execute add collection");

        std::istringstream string_with_commands(request);
        std::string command;
        string_with_commands >> command;

        if (command == "ADD_COLLECTION")
        {
            std::ofstream file_save(FILE_SAVE, std::ios::app);
            if (!file_save.is_open())
            {
                _logger->error("error with opening file for saving data");
                return false;
            }

            std::string pool_name;
            std::string scheme_name;
            std::string collection_name;

            std::string allocator_type;
            std::string allocator_fit_mode;

            allocator* allocator_database;
            allocator_types type;
            allocator_with_fit_mode::fit_mode fit_mode;

            string_with_commands >> pool_name >> scheme_name >> collection_name >> allocator_fit_mode >> allocator_type;

            _logger->information("pool name: " + pool_name + ", scheme name: " + scheme_name +
                                    ", collection name: " + collection_name + ", allocator fit mode: " + allocator_fit_mode +
                                    ", allocator type: " + allocator_type);

            if (allocator_fit_mode == "the_best_fit")
            {
                fit_mode = allocator_with_fit_mode::fit_mode::the_best_fit;
            }
            else if (allocator_fit_mode == "the_worst_fit")
            {
                fit_mode = allocator_with_fit_mode::fit_mode::the_worst_fit;
            }
            else if (allocator_fit_mode == "first_fit")
            {
                fit_mode = allocator_with_fit_mode::fit_mode::first_fit;
            }
            else
            {
                _logger->error("[add_collection] wrong allocator fit mode");
            }

            if (allocator_type == "sorted_list")
            {
                type = allocator_types::SORTED_LIST;
            }
            else if (allocator_type == "global_heap")
            {
                type = allocator_types::GLOBAL_HEAP;
            }
            else if (allocator_type == "buddie_system")
            {
                type = allocator_types::BUDDIE_SYSTEM;
            }
            else if (allocator_type == "boundary_tags")
            {
                type = allocator_types::BOUNDARY_TAGS;
            }
            else
            {
                _logger->error("[add_collection] wrong allocator type");
            }

            _pool_name = pool_name;
            _scheme_name = scheme_name;
            _collection_name = collection_name;
            _type = type;
            _fit_mode = fit_mode;

            file_save << command << " " << pool_name << " " << scheme_name << " " << allocator_type << " " << allocator_fit_mode << std::endl;
            file_save.close();
        }

        return true;
    }

    void execute(std::string const& request) noexcept override
    {
        _logger->trace("start execute add collection");
        database::get_instance(3)->add_collection(_pool_name, _scheme_name, _collection_name, _type, _fit_mode);
        _logger->trace("finish execute add collection");
    }
};

#endif //COURSE_PROJECT_COMMAND_ADD_COLLECTION_H
