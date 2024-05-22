#ifndef COURSE_PROJECT_COMMAND_DISPOSE_VALUE_H
#define COURSE_PROJECT_COMMAND_DISPOSE_VALUE_H
#include "command.h"
#include "../containers/database.h"

class command_dispose_value final :
        public command
{

public:

    void execute(
            bool &data_exists,
            std::optional<tdata> &data_to_modify) const override
    {
        if (!data_exists)
        {
            throw std::logic_error("attempt to dispose non-existent data");
        }

        data_exists = false;
    }
};

#endif //COURSE_PROJECT_COMMAND_DISPOSE_VALUE_H
