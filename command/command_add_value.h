#ifndef COURSE_PROJECT_COMMAND_ADD_VALUE_H
#define COURSE_PROJECT_COMMAND_ADD_VALUE_H
#include "command.h"
#include "../containers/database.h"

class command_add_value final :
        public command
{

private:

    database* _db;
    tdata _initial_version;

public:

    explicit command_add_value(tdata &&initial_version) :
            _initial_version(initial_version)
    {

    }

public:

    void execute(bool &data_exists, std::optional<tdata> &data_to_modify) const override
    {
        if (data_exists)
        {
            throw std::logic_error("attempt to insert already existent data");
        }

        if (data_to_modify.has_value())
        {
            data_to_modify.value() = _initial_version;
        }

        data_exists = true;
    }
};

#endif //COURSE_PROJECT_COMMAND_ADD_VALUE_H
