#ifndef COURSE_PROJECT_ERRORS_H
#define COURSE_PROJECT_ERRORS_H
#include "iostream"

class pool_error : public std::logic_error
{
public:

    pool_error(const std::string& msg) : std::logic_error(msg)
    {

    }
};

class scheme_error : public std::logic_error
{
public:

    scheme_error(const std::string& msg) : std::logic_error(msg)
    {

    }
};

class collection_error : public std::logic_error
{
public:

    collection_error(const std::string& msg) : std::logic_error(msg)
    {

    }
};

class value_error : public std::logic_error
{
public:

    value_error(const std::string& msg) : std::logic_error(msg)
    {

    }
};

class file_error : public std::logic_error
{
public:

    file_error(const std::string& msg) : std::logic_error(msg)
    {

    }
};


#endif //COURSE_PROJECT_ERRORS_H
