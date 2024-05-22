#ifndef COURSE_PROJECT_VALIDATE_PARAMETERS_H
#define COURSE_PROJECT_VALIDATE_PARAMETERS_H
#include <iostream>
#include <cstring>

class validate_parameters
{
private:

    std::string _t_string;

public:

    std::string get_t_string()
    {
        return _t_string;
    }

    validate_parameters(std::string t_string) :
            _t_string(t_string)
    {

    }

public:

    static bool validate_t(std::string const& t)
    {
        for (char symbol : t)
        {
            if (symbol < '1' || symbol > '9')
            {
                return false;
            }
        }
        return true;
    }

public:

    static bool validate_file_system_or_memory_cache(std::string const &p)
    {
        for (char symbol : p)
        {
            if (symbol == '1' || symbol == '0')
            {
                return true;
            }
        }

        return false;
    }

    static bool validate_file_for_file_system(const std::string &input_value)
    {
        for (char symbol : input_value)
        {
            if (!std::isalnum(symbol) && symbol != '_')
            {
                return false;
            }
        }

        return true;
    }

public:

    validate_parameters(validate_parameters const &other) = delete;

    validate_parameters(validate_parameters const &&other) = delete;

    validate_parameters& operator=(validate_parameters const &other) = delete;

    validate_parameters& operator=(validate_parameters const &&other) = delete;

    ~validate_parameters() = default;
};

#endif //COURSE_PROJECT_VALIDATE_PARAMETERS_H
