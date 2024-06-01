#ifndef COURSE_PROJECT_COMMAND_H
#define COURSE_PROJECT_COMMAND_H
#include <iostream>
#include "../containers/wb.h"
#include "../containers/database.h"
#include "../validate/validate_parameters.h"
#include <filesystem>
#include <fstream>
#include "../logger/logger_singleton.h"

class command
{

public:

    virtual ~command() = default;

public:

    virtual bool can_execute(std::string const&) noexcept = 0;

    virtual void execute(std::string const&) noexcept = 0;
};


#endif //COURSE_PROJECT_COMMAND_H
