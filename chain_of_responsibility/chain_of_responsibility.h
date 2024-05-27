#ifndef COURSE_PROJECT_CHAIN_OF_RESPONSIBILITY_H
#define COURSE_PROJECT_CHAIN_OF_RESPONSIBILITY_H
#include "chain_of_responsibility_handler.h"
#include "../command/command_find_value.h"
#include "../command/command_find_between_value.h"
#include "../command/command_add_value.h"
#include "../command/command_delete_value.h"

class chain_of_responsibility final
{

private:

    chain_of_responsibility_handler* _first_handler;
    chain_of_responsibility_handler* _last_handler;

public:

    chain_of_responsibility() : _first_handler(nullptr), _last_handler(nullptr)
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

    bool handle(std::string const &request,
                std::int64_t date_time_target) const noexcept
    {
        if (_first_handler == nullptr)
        {
            return false;
        }

        return _first_handler->handle(request, date_time_target);
    }

public:

    void add_handler(command *cmd)
    {
        std::int64_t date_time_activity_started = 0;

        auto *added_handler = new chain_of_responsibility_handler(cmd, date_time_activity_started);

        if (_last_handler == nullptr)
        {
            _first_handler = _last_handler = added_handler;
        }
        else
        {
            _last_handler->_next_handler = added_handler;
            _last_handler = added_handler;
        }
    }

public:

    void insert(std::string const& request)
    {
        std::int64_t current_date_time = 0;
        handle(request, current_date_time);

        add_handler(new command_add_value());
    }

    value* obtain(std::int64_t date_time_of_activity)
    {
        bool data_exists;
        tdata data_to_modify;
        auto data_to_modify_optional = std::make_optional(data_to_modify);

        handle(date_time_of_activity);

        return data_exists
               ? std::make_optional(std::move(data_to_modify))
               : std::optional<tdata>();
    }

    void update(tdata const &data, std::string const &update_expression)
    {
        bool data_exists = false;
        std::optional<tdata> empty_optional;

        std::int64_t current_date_time = 0;
        handle(data_exists, empty_optional, current_date_time);

        if (!data_exists)
        {
            throw std::logic_error("attempt to add data update handler while data not exists");
        }

        add_handler(new update_command(update_expression));
    }

    void dispose(tdata const &data)
    {
        bool data_exists = false;
        std::optional<tdata> empty_optional;

        std::int64_t current_date_time = 0;
        handle(data_exists, empty_optional, current_date_time);

        if (!data_exists)
        {
            throw std::logic_error("attempt to add data dispose handler while data not exists");
        }

        add_handler(new dispose_command);
    }
};

#endif //COURSE_PROJECT_CHAIN_OF_RESPONSIBILITY_H
