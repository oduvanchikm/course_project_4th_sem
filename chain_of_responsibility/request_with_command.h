#ifndef COURSE_PROJECT_REQUEST_WITH_COMMAND_H
#define COURSE_PROJECT_REQUEST_WITH_COMMAND_H
#include "handler.h"
#include "../command/command.h"

class request_handler_with_command : public handler
{
private:

    command* _target_action;

public:

    request_handler_with_command(command* target_action) : _target_action(target_action)
    {

    }
    ~request_handler_with_command()
    {
        delete _target_action;
    }

    request_handler_with_command(request_handler_with_command const&) = delete;
    request_handler_with_command(request_handler_with_command&&) = delete;
    request_handler_with_command& operator=(request_handler_with_command const&) = delete;
    request_handler_with_command& operator=(request_handler_with_command const&&) = delete;

public:

    bool handle(std::string const& request) override
    {
        if(!_target_action->can_execute(request))
        {
            if(handler::_next_handler == nullptr)
            {
                return false;
            }

            return handler::_next_handler->handle(request);
        }

        _target_action->execute(request);
        return true;
    }
};

#endif //COURSE_PROJECT_REQUEST_WITH_COMMAND_H
