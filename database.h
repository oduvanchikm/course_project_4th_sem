#ifndef COURSE_PROJECT_DATABASE_H
#define COURSE_PROJECT_DATABASE_H
#include "pool.h"
#include "include/b_tree.h"
#include "include/binary_search_tree.h"
#include "include/associative_container.h"
#include "comparer.h"
#include "logger/logger_guardant.h"
#include "logger.h"
#include "logger/client_logger.h"
#include "logger/client_logger_builder.h"

class data_base
{

private:

    static data_base* _instance;
//    logger* logger_logger;
//    bool is_file_system;

public:

    associative_container<std::string, pool> *_database_entrypoint;

public:

    static data_base* get_instance()
    {

        if (_instance == nullptr)
        {
            _instance = new data_base();
        }

        return _instance;
    }

public:

    data_base()
    {
        _database_entrypoint = new b_tree<std::string, pool>(3, key_comparer());
//        logger_logger = create_logger(std::vector<std::pair<std::string, logger::severity>>{{"/wsl.localhost/Ubuntu/home/passwd/course_project/course_project_4th_sem/log_file.txt", logger::severity::debug}});
        _instance = this;
    }

public:

    void add_pool(std::string const& pool_name) const
    {
        _database_entrypoint->insert(pool_name, std::move(pool()));
        std::cout << "add pool" << std::endl;
    }

    void delete_pool(std::string const& pool_name) const
    {
        _database_entrypoint->dispose(pool_name);
    }

public:

    ~data_base()
    {
        delete _database_entrypoint;
    }

    data_base(data_base const &other) noexcept = delete;

    data_base(data_base const &&other) noexcept = delete;

    data_base &operator=(data_base &other) = delete;

    data_base &operator=(data_base &&other) = delete;

public:

//    logger *create_logger(
//            std::vector<std::pair<std::string, logger::severity>> const &output_file_streams_setup,
//            bool use_console_stream = true,
//            logger::severity console_stream_severity = logger::severity::debug)
//    {
//        logger_builder *logger_builder_instance = new client_logger_builder;
//
//        if (use_console_stream)
//        {
//            logger_builder_instance->add_console_stream(console_stream_severity);
//        }
//
//        for (auto &output_file_stream_setup: output_file_streams_setup)
//        {
//            logger_builder_instance->add_file_stream(output_file_stream_setup.first, output_file_stream_setup.second);
//        }
//
//        logger *logger_instance = logger_builder_instance->build();
//
//        delete logger_builder_instance;
//
//        return logger_instance;
//    }
//
//    void log_with_guard(std::string const &message, logger::severity severity) const
//    {
//        if (logger_logger != nullptr)
//        {
//            logger_logger->log(message, severity);
//        }
//    }
};

data_base* data_base::_instance = nullptr;


#endif //COURSE_PROJECT_DATABASE_H
