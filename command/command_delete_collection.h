#ifndef COURSE_PROJECT_COMMAND_DELETE_COLLECTION_H
#define COURSE_PROJECT_COMMAND_DELETE_COLLECTION_H
#include "command.h"

class command_delete_collection final :
        public command
{

private:

//    logger_guardant* _logger_guardant_command;
    logger* _logger;
    std::string _pool_name;
    std::string _scheme_name;
    std::string _collection_name;

public:

    command_delete_collection()
    {

    }

    command_delete_collection(std::string& pool_name, std::string& scheme_name,
                                std::string& collection_name, logger* log) :
                                    _logger(log),
                                    _scheme_name(scheme_name),
                                    _pool_name(pool_name),
                                    _collection_name(collection_name)
    {

    }

public:

    bool can_execute(std::string const& request) noexcept override
    {
        _logger->trace("start can_execute delete scheme");

        std::istringstream string_with_commands(request);
        std::string command;
        string_with_commands >> command;

        if (command == "DELETE_COLLECTION")
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

            string_with_commands >> pool_name >> scheme_name >> collection_name;

            _logger->information("pool name: " + pool_name + ", scheme name: " + scheme_name +
                                                                ", collection name: " + collection_name);
            _pool_name = pool_name;
            _scheme_name = scheme_name;
            _collection_name = collection_name;

            file_save << command << " " <<  pool_name << " " << scheme_name << " " << collection_name << std::endl;
            file_save.close();
        }

        return true;
    }

    void execute(std::string const& request) noexcept override
    {
        _logger->trace("start execute delete collection");
        database::get_instance(3)->delete_collection(_pool_name, _scheme_name, _collection_name);
        _logger->trace("finish execute delete collection");
    }
};

#endif //COURSE_PROJECT_COMMAND_DELETE_COLLECTION_H
