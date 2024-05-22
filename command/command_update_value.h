#ifndef COURSE_PROJECT_COMMAND_UPDATE_VALUE_H
#define COURSE_PROJECT_COMMAND_UPDATE_VALUE_H
#include "../containers/database.h"
#include "command.h"

class command_update_value final :
        public command
{

private:

    std::string _update_expression;

public:

    explicit command_update_value(std::string const &update_expression) :
        _update_expression(update_expression)
    {

    }

public:

    void execute(bool &data_exists,
            std::optional<tdata> &data_to_modify) const override
    {
        if (!data_exists)
        {
            throw std::logic_error("attempt to modify non-existent data");
        }

        if (data_to_modify.has_value())
        {

        }
    }
};

#endif //COURSE_PROJECT_COMMAND_UPDATE_VALUE_H
