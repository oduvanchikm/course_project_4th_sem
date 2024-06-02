#ifndef COURSE_PROJECT_COMMAND_H
#define COURSE_PROJECT_COMMAND_H
#include <iostream>
#include "file_save.h"
#include "../containers/wb.h"
#include "../containers/database.h"
#include "../validate/validate_parameters.h"
#include <filesystem>
#include <fstream>
#include "../logger/logger_singleton.h"
#include "file_save.h"
#include "../validate/errors.h"
#include <chrono>
#include "iostream"
#include "fstream"
#include <string>
#include <cstring>

class command
{

public:

    virtual ~command() = default;

public:

    virtual bool can_execute(std::string const&) noexcept = 0;

    virtual void execute(std::string const&) noexcept = 0;
};


#endif //COURSE_PROJECT_COMMAND_H
