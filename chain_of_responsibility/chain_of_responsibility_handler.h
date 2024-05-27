#ifndef COURSE_PROJECT_CHAIN_OF_RESPONSIBILITY_HANDLER_H
#define COURSE_PROJECT_CHAIN_OF_RESPONSIBILITY_HANDLER_H
#include "../command/command.h"

class chain_of_responsibility_handler
{
    friend class chain_of_responsibility;

private:

    std::int64_t _date_time_activity_started;
    command *_command_action;
    chain_of_responsibility_handler *_next_handler;

public:

    chain_of_responsibility_handler(command *command_action,
                                    std::int64_t date_time_activity_started) :
                                        _command_action(command_action),
                                        _date_time_activity_started(date_time_activity_started),
                                        _next_handler(nullptr)
    {

    }

public:

    bool handle(std::string const &request,
                std::int64_t date_time_target) const noexcept
    {
        if (date_time_target <= _date_time_activity_started)
        {
            return false;
        }

        if (!_command_action->can_execute(request))
        {
            if (_next_handler == nullptr)
            {
                return false;
            }

            return _next_handler->handle(request, date_time_target);
        }

        _command_action->execute(request);

        return true;
    }

public:

    ~chain_of_responsibility_handler() noexcept
    {
        delete _command_action;
    }

    chain_of_responsibility_handler(chain_of_responsibility_handler const &other) = delete;

    chain_of_responsibility_handler(chain_of_responsibility_handler &&other) noexcept = delete;

    chain_of_responsibility_handler &operator=(chain_of_responsibility_handler const &other) = delete;

    chain_of_responsibility_handler &operator=(chain_of_responsibility_handler &&other) noexcept = delete;

};

#endif //COURSE_PROJECT_CHAIN_OF_RESPONSIBILITY_HANDLER_H
