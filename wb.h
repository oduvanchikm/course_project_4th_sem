#ifndef COURSE_PROJECT_WB_H
#define COURSE_PROJECT_WB_H
#include <iostream>

class value
{
public:

    int id_order;
    std::string first_name;
    std::string second_name;
    std::string address;
    double rating;
};

class value_filesystem final :
        public value
{

};

class value_in_memory_cash final :
        public value
{

};

class key
{
public:

    int id;
};


#endif //COURSE_PROJECT_WB_H
