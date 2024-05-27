#ifndef COURSE_PROJECT_COMMAND_H
#define COURSE_PROJECT_COMMAND_H
#define FILE_SAVE "file_save_data.txt"
#include <iostream>
#include <optional>
#include "../containers/wb.h"
#include "../containers/database.h"
#include "../validate/validate_parameters.h"
#include <filesystem>
#include <fstream>

class command
{

public:

    virtual ~command() = default;

public:

    virtual bool can_execute(std::string const&) noexcept = 0;

    virtual void execute(std::string const&) noexcept = 0;
};


#endif //COURSE_PROJECT_COMMAND_H
