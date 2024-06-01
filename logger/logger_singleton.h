#ifndef COURSE_PROJECT_LOGGER_SINGLETON_H
#define COURSE_PROJECT_LOGGER_SINGLETON_H

#include "logger.h"
#include "logger_builder.h"
#include "client_logger_builder.h"
#include "client_logger.h"

class logger_singleton {

private:

    static logger_singleton *_logger_singleton;
    logger *_logger;

public:

    static logger_singleton *get_instance() {
        if (_logger_singleton == nullptr) {
            _logger_singleton = new logger_singleton("log.txt");
        }

        return _logger_singleton;
    }

private:

    logger_singleton(std::string const &logger_file_path) {
        logger_builder *builder = new client_logger_builder();

        logger *constructed_logger = builder
                ->add_console_stream(logger::severity::information)
                ->add_console_stream(logger::severity::debug)
                ->add_console_stream(logger::severity::error)
                ->add_console_stream(logger::severity::trace)
                ->add_file_stream("log.txt", logger::severity::information)
                ->add_file_stream("log.txt", logger::severity::debug)
                ->add_file_stream("log.txt", logger::severity::error)
                ->add_file_stream("log.txt", logger::severity::trace)
                ->build();

        _logger = builder->build();
        delete builder;
    }

public:

    logger *get_logger() const noexcept {
        return _logger;
    }

public:

    ~logger_singleton() {
        delete _logger;
    }

    logger_singleton(logger_singleton const &other) = delete;

    logger_singleton(logger_singleton const &&other) = delete;

    logger_singleton &operator=(logger_singleton const &other) = delete;

    logger_singleton &operator=(logger_singleton const &&other) = delete;

};

logger_singleton *logger_singleton::_logger_singleton = nullptr;

#endif //COURSE_PROJECT_LOGGER_SINGLETON_H
