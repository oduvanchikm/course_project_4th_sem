#ifndef COURSE_PROJECT_FLYWEIGHT_STRING_H
#define COURSE_PROJECT_FLYWEIGHT_STRING_H
#include "iostream"

class string_flyweight
{
private:

    std::string _value;

public:

    std::string const* get_value()
    {
        return &_value;
    }

    void set_value(const std::string& value)
    {
        _value = value;
    }
};

#endif //COURSE_PROJECT_FLYWEIGHT_STRING_H
