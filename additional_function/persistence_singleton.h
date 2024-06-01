#ifndef COURSE_PROJECT_PERSISTENCE_SINGLETON_H
#define COURSE_PROJECT_PERSISTENCE_SINGLETON_H
#include <map>
#include <vector>
#include <iostream>
//#include <../command/command.h>

//class persistence_singleton
//{
//
//private:
//
//    static persistence_singleton* _persistence_instance;
//
//public:
//
//    std::map<std::int64_t, std::vector<std::pair<std::string, value*>>>* _persistence_entrypoint;
//
//public:
//
//    static persistence_singleton* get_instance()
//    {
//        if (_persistence_instance == nullptr)
//        {
//            _persistence_instance = new persistence_singleton();
//        }
//
//        return _persistence_instance;
//    }
//
//public:
//
//    std::int64_t get_time()
//    {
//        auto now = std::chrono::system_clock::now();
//        return std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
//    }
//
//public:
//
//    persistence_singleton()
//    {
//        _persistence_instance = this;
//        _persistence_entrypoint = new std::map<std::int64_t, std::vector<std::pair<std::string, value*>>>;
//    }
//
//public:
//
//    ~persistence_singleton()
//    {
//        delete _persistence_entrypoint;
//    }
//
//    persistence_singleton(persistence_singleton const& other) = delete;
//
//    persistence_singleton(persistence_singleton const&& other) = delete;
//
//    persistence_singleton& operator=(persistence_singleton const& other) = delete;
//
//    persistence_singleton& operator=(persistence_singleton const&& other) = delete;
//
//};
//
//persistence_singleton* persistence_singleton::_persistence_instance = nullptr;

#endif //COURSE_PROJECT_PERSISTENCE_SINGLETON_H
