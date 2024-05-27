#ifndef COURSE_PROJECT_HANDLER_H
#define COURSE_PROJECT_HANDLER_H

#include <iostream>

class handler
{
    friend class chain_of_responsibility;

protected:

    handler *_next_handler;

public:

    handler() : _next_handler(nullptr)
    {

    }

    virtual ~handler() = default;

public:

    virtual bool handle(std::string const &request) const noexcept = 0;

};

#endif //COURSE_PROJECT_HANDLER_H
