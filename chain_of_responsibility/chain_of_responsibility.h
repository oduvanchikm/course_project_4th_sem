#ifndef COURSE_PROJECT_CHAIN_OF_RESPONSIBILITY_H
#define COURSE_PROJECT_CHAIN_OF_RESPONSIBILITY_H
#include "chain_of_responsibility_handler.h"
#include "../command/command.h"

class chain_of_responsibility final
{

private:

    logger* _logger;

    chain_of_responsibility_handler* _first_handler;
    chain_of_responsibility_handler* _last_handler;

public:

    chain_of_responsibility(logger* logger) :
            _first_handler(nullptr), _last_handler(nullptr), _logger(logger)
    {

    }

public:

    ~chain_of_responsibility()
    {
        while (_first_handler != nullptr)
        {
            _last_handler = _first_handler;
            _first_handler = _first_handler->_next_handler;
            delete _last_handler;
        }
    }

    chain_of_responsibility(chain_of_responsibility const &other) = delete;

    chain_of_responsibility(chain_of_responsibility &&other) noexcept = delete;

    chain_of_responsibility &operator=(chain_of_responsibility const &other) = delete;

    chain_of_responsibility &operator=(chain_of_responsibility &&other) noexcept = delete;

public:

    bool handle(std::string const &request) const noexcept
    {
        if (_first_handler == nullptr)
        {
            return false;
        }

        return _first_handler->handle(request);
    }

public:

    chain_of_responsibility& add_handler(command *cmd)
    {
        _logger->trace("add handler start");
        std::int64_t date_time_activity_started = 0;

        _last_handler = _first_handler == nullptr
                ? _first_handler = new chain_of_responsibility_handler(cmd, date_time_activity_started)
                : _last_handler->_next_handler = new chain_of_responsibility_handler(cmd, date_time_activity_started);

        return *this;
    }

//public:
//
//    void insert(std::string const& request)
//    {
//        std::int64_t current_date_time = 0;
//        handle(request, current_date_time);
//        add_handler(new command_add_value(request));
//    }
//
//    value* obtain(std::int64_t date_time_of_activity)
//    {
//        std::string request;
//
//        handle(request, date_time_of_activity);
//
//        command_find_value* obtain_command = new command_find_value(date_time_of_activity);
//        add_handler(obtain_command);
//
//        return obtain_command->get_result();
//    }
//
//    void update(std::string const& request)
//    {
//        std::int64_t current_date_time = 0;
//        handle(request, current_date_time);
//
//        add_handler(new command_update_value(std::move(request)));
//    }
//
//    void dispose(std::string const& request)
//    {
//        std::int64_t current_date_time = 0;
//        handle(request, current_date_time);
//        add_handler(new command_delete_value(request));
//    }
};

#endif //COURSE_PROJECT_CHAIN_OF_RESPONSIBILITY_H
