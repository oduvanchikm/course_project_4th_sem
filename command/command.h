#ifndef COURSE_PROJECT_COMMAND_H
#define COURSE_PROJECT_COMMAND_H

#include <iostream>
#include <optional>
#include "../containers/wb.h"

class command
{

public:

    virtual ~command() = default;

public:

    virtual void execute(
            bool &data_exists,
            std::optional<tdata> &data_to_modify) const = 0;
};


#endif //COURSE_PROJECT_COMMAND_H
