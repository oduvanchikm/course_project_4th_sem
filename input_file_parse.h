#ifndef COURSE_PROJECT_INPUT_FILE_PARSE_H
#define COURSE_PROJECT_INPUT_FILE_PARSE_H
#include "database.h"
#include "pool.h"
#include "scheme.h"
#include "collection.h"
#include <fstream>
#include <string>
#include <sstream>

class input_file_parse
{
private:

    logger* log;

public:

    logger *create_logger(
            std::vector<std::pair<std::string, logger::severity>> const &output_file_streams_setup,
            bool use_console_stream = true,
            logger::severity console_stream_severity = logger::severity::debug)
    {
        logger_builder *logger_builder_instance = new client_logger_builder;

        if (use_console_stream)
        {
            logger_builder_instance->add_console_stream(console_stream_severity);
        }

        for (auto &output_file_stream_setup: output_file_streams_setup)
        {
            logger_builder_instance->add_file_stream(output_file_stream_setup.first, output_file_stream_setup.second);
        }

        logger *logger_instance = logger_builder_instance->build();

        delete logger_builder_instance;

        return logger_instance;
    }

    void log_with_guard(std::string const &message, logger::severity severity) const
    {
        if (log != nullptr)
        {
            log->log(message, severity);
        }
    }

public:

//    std::string pool_name;
//    std::string scheme_name;
//    std::string collection_name;
//    pool _pool_key;
//    scheme _scheme_key;
//    collection _collection_key;

public:

    input_file_parse()
    {
        log = create_logger(std::vector<std::pair<std::string, logger::severity>>{{"log_file.txt", logger::severity::debug}});
    }

public:

    void parse_input_file(std::ifstream& input_file, data_base* data_base_parse)
    {
        log->trace("[input_file_parse] start parse input file method");
        std::cout << "[input_file_parse] start parse input file method" << std::endl;

        std::string line;
        while (input_file >> line)
        {
            std::cout << line << std::endl;

            if (line == "ADD_POOL")
            {
                log_with_guard("[add_pool] find ADD_POOL function", logger::severity::debug);
                std::cout << "[add_pool] find ADD_POOL function" << std::endl;

                std::string pool_name;

                input_file >> pool_name;
                std::cout << line << " " << pool_name << std::endl;

                try
                {
                    data_base_parse->add_pool(pool_name);
                    log_with_guard("[add_pool] the pool has been added successfully", logger::severity::debug);
                    std::cout << "[add_pool] the pool has been added successfully" << std::endl;
                }
                catch(const std::exception& error)
                {
                    log_with_guard("[add_pool] error with add pool", logger::severity::error);
                    std::cout << "[add_pool] error with add pool" << std::endl;
                }
            }
            else if (line == "DELETE_POOL")
            {
                log_with_guard("[delete_pool] find DELETE_POOL function", logger::severity::debug);
                std::cout << "[delete_pool] find DELETE_POOL function" << std::endl;

                std::string pool_name;

                input_file >> pool_name;
                std::cout << line << " " << pool_name << std::endl;

                try
                {
                    data_base_parse->delete_pool(pool_name);
                    log_with_guard("[delete_pool] the pool has been deleted successfully", logger::severity::debug);
                    std::cout << "[delete_pool] the pool has been deleted successfully" << std::endl;
                }
                catch(const std::exception& error)
                {
                    log_with_guard("[delete_pool] error with delete pool", logger::severity::error);
                    std::cout << "[delete_pool] error with delete pool" << std::endl;
                }
            }
            else if (line == "ADD_SCHEME")
            {
                log_with_guard("[add_scheme] find ADD_SCHEME function", logger::severity::debug);
                std::cout << "[add_scheme] find ADD_SCHEME function" << std::endl;

                std::string pool_name;
                std::string scheme_name;

                input_file >> pool_name >> scheme_name;
                std::cout << line << " " << scheme_name << std::endl;

                pool& _pool_key = const_cast<pool&>(data_base_parse->_database_entrypoint->obtain(pool_name));

                try
                {
                    _pool_key.add_scheme(pool_name);
                    log_with_guard("[add_scheme] the scheme has been added successfully", logger::severity::debug);
                    std::cout << "[add_scheme] the scheme has been added successfully" << std::endl;
                }
                catch(const std::exception& error)
                {
                    log_with_guard("[add_scheme] error with add scheme", logger::severity::error);
                    std::cout << "[add_scheme] error with add scheme" << std::endl;
                }
            }
            else if (line == "DELETE_SCHEME")
            {
                log_with_guard("[delete_scheme] find DELETE_SCHEME function", logger::severity::debug);
                std::cout << "[delete_scheme] find DELETE_SCHEME function" << std::endl;

                std::string pool_name;
                std::string scheme_name;

                input_file >> pool_name >> scheme_name;
                std::cout << line << " " << scheme_name << std::endl;

                pool& _pool_key = const_cast<pool&>(data_base_parse->_database_entrypoint->obtain(pool_name));

                try
                {
                    _pool_key.remove_scheme(scheme_name);
                    log_with_guard("[delete_scheme] the scheme has been deleted successfully", logger::severity::debug);
                    std::cout << "[delete_scheme] the scheme has been deleted successfully" << std::endl;
                }
                catch(const std::exception& error)
                {
                    log_with_guard("[delete_scheme] error with deleted scheme", logger::severity::error);
                    std::cout << "[delete_scheme] error with deleted scheme" << std::endl;
                }
            }
            else if (line == "ADD_COLLECTION")
            {
                log_with_guard("[add_collection] find ADD_COLLECTION function", logger::severity::debug);
                std::cout << "[add_collection] find ADD_COLLECTION function" << std::endl;

                std::string pool_name;
                std::string scheme_name;
                std::string collection_name;

                input_file >> pool_name >> scheme_name >> collection_name;
                std::cout << line << " " << pool_name << " " << scheme_name << " " << collection_name << std::endl;

                pool& _pool_key = const_cast<pool&>(data_base_parse->_database_entrypoint->obtain(pool_name));
                std::cout << "find _pool_key" << std::endl;

                std::cout << "scheme name " << scheme_name << std::endl;

                auto& _scheme_key = const_cast<scheme&>(_pool_key._pool->obtain(scheme_name));

                std::cout << "find _scheme_key" << std::endl;

                try
                {
                    _scheme_key.add_collection(collection_name);
                    log_with_guard("[add_collection] the collection has been added successfully", logger::severity::debug);
                    std::cout << "[add_collection] the collection has been added successfully" << std::endl;
                }
                catch(const std::exception& error)
                {
                    log_with_guard("[add_collection] error with add collection", logger::severity::error);
                    std::cout << "[add_collection] error with add collection" << std::endl;
                }

            }
            else if (line == "DELETE_COLLECTION")
            {
                log_with_guard("[delete_collection] find DELETE_COLLECTION function", logger::severity::debug);
                std::cout << "[delete_collection] find DELETE_COLLECTION function" << std::endl;

//                input_file >> pool_name >> scheme_name >> collection_name;
//                std::cout << line << " " << collection_name << std::endl;
//
//                _pool_key = data_base_parse->_database_entrypoint->obtain(pool_name);
//                _scheme_key = _pool_key._pool->obtain(scheme_name);
//
//                try
//                {
//                    _scheme_key.remove_collection(scheme_name);
//                    log_with_guard("[delete_collection] the collection has been deleted successfully", logger::severity::debug);
//                    std::cout << "[delete_collection] the collection has been deleted successfully" << std::endl;
//                }
//                catch(const std::exception& error)
//                {
//                    log_with_guard("[delete_collection] error with delete collection", logger::severity::error);
//                    std::cout << "[delete_collection] error with delete collection" << std::endl;
//                }
            }
            else if (line == "ADD_VALUE")
            {
                log_with_guard("[add_value] find ADD_VALUE function", logger::severity::debug);
                std::cout << "[add_value] find ADD_VALUE function" << std::endl;
            }
            else if (line == "UPDATE_VALUE")
            {
                log_with_guard("[update_value] find UPDATE_VALUE function", logger::severity::debug);
                std::cout << "[update_value] find UPDATE_VALUE function" << std::endl;
            }
            else if (line == "FIND_VALUE")
            {
                log_with_guard("[find_value] find FIND_VALUE function", logger::severity::debug);
                std::cout << "[find_value] find FIND_VALUE function" << std::endl;
            }
            else if (line == "DELETE_VALUE")
            {
                log_with_guard("[delete_value] find DELETE_VALUE function", logger::severity::debug);
                std::cout << "[delete_value] find DELETE_VALUE function" << std::endl;
            }
            else if (line == "FIND_BETWEEN_VALUE")
            {
                log_with_guard("[find_between_value] find FIND_BETWEEN_VALUE function", logger::severity::debug);
                std::cout << "[find_between_value] find FIND_BETWEEN_VALUE function" << std::endl;
            }
        }
    }

public:

    ~input_file_parse() = default;


};


#endif //COURSE_PROJECT_INPUT_FILE_PARSE_H
