//#ifndef COURSE_PROJECT_REQUEST_HANDLER_WITH_COMMAND_H
//#define COURSE_PROJECT_REQUEST_HANDLER_WITH_COMMAND_H
//#include "../validate/errors.h"
//#include "handler.h"
//#include <chrono>
//#include <fstream>
//#include <iostream>
//#include <ctime>
//#include <sstream>
//#include "../command/command.h"

//class request_handler_with_command
//        : public handler
//{
//
//private:
//
//    command* _target_action;
//
//    std::int64_t _date_time_activity_started;
//
//public:
//
//    [[nodiscard]] std::int64_t get_time_and_date() const
//    {
//        return _date_time_activity_started;
//    }
//
//public:
//
//    explicit request_handler_with_command(command* target_action) :
//                _target_action(target_action),
//                _date_time_activity_started(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count())
//    {
//
//    }
//
//    ~request_handler_with_command() override
//    {
//        delete _target_action;
//    }
//
//    request_handler_with_command(request_handler_with_command const& other) = delete;
//
//    request_handler_with_command(request_handler_with_command&& other) = delete;
//
//    request_handler_with_command& operator=(request_handler_with_command const& other) = delete;
//
//    request_handler_with_command& operator=(request_handler_with_command const&& other) = delete;
//
//public:
//
//    bool handle(std::string const& request, std::int64_t date_time_target) final
//    {
//        if (date_time_target <= _date_time_activity_started)
//        {
//            return false;
//        }
//
//        if (!_target_action->can_execute(request))
//        {
//            if(handler::_next_handler == nullptr)
//            {
//                return false;
//            }
//
//            return handler::_next_handler->handle(request, date_time_target);
//        }
//
//        _target_action->execute(request);
//
//        return true;
//    }
//
//public:
//
//    void write_time_to_file(std::string const& request) const
//    {
//        std::cout << "fuck" << std::endl;
//        std::string first_word;
//        std::istringstream iss(request);
//        iss >> first_word;
//
//        std::time_t time = _date_time_activity_started / 1000;
//        std::tm* tm_info = std::localtime(&time);
//        char buffer[80];
//        std::strftime(buffer, 80, "[%Y-%m-%d %H:%M:%S]", tm_info);
//        std::string formatted_time(buffer);
//
//        std::cout << first_word << std::endl;
//
//        std::ofstream file("time_log.txt", std::ios::app);
//
//        if (!file.is_open())
//        {
//            throw file_error("error with open file");
//        }
//
//        if (first_word == "ADD_VALUE" && first_word == "UPDATE_VALUE" && first_word == "FIND_VALUE" &&
//                first_word == "FIND_BETWEEN_VALUE" && first_word == "FIND_VALUE")
//        {
//            file << formatted_time << " " << request << std::endl;
//        }
//
//        file.close();
//    }
//};

//#endif //COURSE_PROJECT_REQUEST_HANDLER_WITH_COMMAND_H