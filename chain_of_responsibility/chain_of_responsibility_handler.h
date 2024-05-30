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

    [[nodiscard]] bool handle(std::string const &request) const noexcept
    {
//        std::cout << "request: " << request << std::endl;
//
//        if (_command_action->can_execute(request))
//        {
//            std::cout << "first beee" << std::endl;
//            _command_action->execute(request);
//            return true;
//        }
//
//        std::cout << "beee" << std::endl;
//
//        if (_next_handler != nullptr)
//        {
//            std::cout << "second beee" << std::endl;
//            return _next_handler->handle(request);
//        }
//
//        std::cout << "third beee" << std::endl;
//
//        return false;
        std::cout << "start handle in chain of responsibility handler" << std::endl;
//        if (date_time_target <= _date_time_activity_started)
//        {
//            return false;
//        }


        if (_command_action->can_execute(request))
        {
            _command_action->execute(request);
            return true;
        }
        else
        {
            if (this->_next_handler == nullptr)
            {
                return false;
            }

            return this->_next_handler->handle(request);
        }

//        if (!_command_action->can_execute(request))
//        {
//            std::cout << "error1" << std::endl;
//            if (this->_next_handler == nullptr)
//            {
//                std::cout << "error2" << std::endl;
//                return false;
//            }
//
//            return _next_handler->handle(request);
//        }
//
//        _command_action->execute(request);
//
        std::cout << "finish handle in chain of responsibility handler" << std::endl;
//
//        return true;
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
