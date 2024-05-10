#ifndef COURSE_PROJECT_LOGGER_FOR_USE_H
#define COURSE_PROJECT_LOGGER_FOR_USE_H
#include "logger.h"
#include "vector"
#include "logger/client_logger_builder.h"
#include "logger/client_logger.h"

class logger_for_use : public logger
{

private:

    logger* _logger_for_use;

public:

    static logger* create_logger(
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

public:

    ~logger_for_use()
    {
        delete _logger_for_use;
    }

    logger_for_use(logger_for_use const &other) = delete;

    logger_for_use(logger_for_use const &&other) = delete;

    logger_for_use &operator=(logger_for_use const &other) = delete;

    logger_for_use &operator=(logger_for_use const &&other) = delete;

public:

    logger* get_logger()
    {
        return _logger_for_use;
    }

    void delete_logger()
    {
        if (_logger_for_use)
        {
            delete _logger_for_use;
            _logger_for_use = nullptr;
        }
    }

};

#endif //COURSE_PROJECT_LOGGER_FOR_USE_H
