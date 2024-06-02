//#ifndef COURSE_PROJECT_REQUEST_HANDLER_WITH_COMMAND_CHAIN_H
//#include "handler.h"
//#include "request_handler_with_command.h"
//#include "../command/command.h"

//class request_handler_with_command_chain
//{
//
//private:
//
//    handler *_first_handler;
//    handler *_last_handler;
//
//public:
//
//    request_handler_with_command_chain() :
//            _first_handler(nullptr), _last_handler(nullptr)
//    {
//
//    }
//
//    ~request_handler_with_command_chain()
//    {
//        while(_first_handler != nullptr)
//        {
//            _last_handler = _first_handler;
//            _first_handler = _first_handler->_next_handler;
//            delete _last_handler;
//        }
//    }
//
//    request_handler_with_command_chain(request_handler_with_command_chain const& other) = delete;
//
//    request_handler_with_command_chain(request_handler_with_command_chain&& other) = delete;
//
//    request_handler_with_command_chain& operator=(request_handler_with_command_chain const& other) = delete;
//
//    request_handler_with_command_chain& operator=(request_handler_with_command_chain&& other) = delete;
//
//public:
//
//    [[nodiscard]] bool handle(std::string const& request, std::int64_t date_time_target) const noexcept
//    {
//        if(_first_handler == nullptr)
//        {
//            return false;
//        }
//
//        return _first_handler->handle(request, date_time_target);
//    }
//
//public:
//
//    request_handler_with_command_chain& add_handler(command* cmd)
//    {
//        _last_handler = _first_handler == nullptr
//                        ? _first_handler = new request_handler_with_command(cmd)
//                        : _last_handler->_next_handler = new request_handler_with_command(cmd);
//
//        return *this;
//    }
//};

//#endif //COURSE_PROJECT_REQUEST_HANDLER_WITH_COMMAND_CHAIN_H
