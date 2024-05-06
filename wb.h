#ifndef COURSE_PROJECT_WB_H
#define COURSE_PROJECT_WB_H
#include <iostream>

class value
{
public:

//    int _id_order;
//    std::string _first_name;
//    std::string _second_name;
//    std::string _address;
//    double _rating;
};

class value_file_system final :
        public value
{
public:

    std::string path_file;
    int start_value_bytes;


};

class value_in_memory_cash final :
        public value
{
public:

    int _id_order;
    std::string _first_name;
    std::string _second_name;
    std::string _address;
    double _rating;

};

class key
{
public:

    int _id;
};


#endif //COURSE_PROJECT_WB_H
