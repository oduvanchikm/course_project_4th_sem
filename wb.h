#ifndef COURSE_PROJECT_WB_H
#define COURSE_PROJECT_WB_H
#include <iostream>

// info about buyer: key - id_buyer, value - name, date, address, id_oder

class value
{

public:

    value() = default;
};

class value_file_system final :
        public value
{

public:

    std::string _path_file;
    long _start_value_bytes;
    long _string_size;

    value_file_system(std::string& path_file, long start_value_bytes, long string_size) :
            _start_value_bytes(start_value_bytes),
            _string_size(string_size),
            _path_file(path_file)
    {

    }

    ~value_file_system()
    {

    }

    value_file_system(value_file_system const &other) :
            _start_value_bytes(other._start_value_bytes),
            _string_size(other._start_value_bytes),
            _path_file(other._path_file)
    {

    }

    value_file_system& operator=(value_file_system const &other)
    {
        if (this != &other)
        {
            _start_value_bytes = other._start_value_bytes;
            _string_size = other._start_value_bytes;
            _path_file = other._path_file;
        }

        return *this;
    }

    value_file_system(value_file_system const &&other) :
            _start_value_bytes(other._start_value_bytes),
            _string_size(other._start_value_bytes),
            _path_file(other._path_file)
    {

    }

    value_file_system& operator=(value_file_system const &&other)
    {
        if (this != &other)
        {
            _start_value_bytes = other._start_value_bytes;
            _string_size = other._start_value_bytes;
            _path_file = other._path_file;
        }

        return *this;
    }
};

class value_in_memory_cash final : public value
{
public:

    int _id_order;
    std::string _address;
    std::string _name_buyer;
    std::string _date;

    value_in_memory_cash(int id_order, std::string& address, std::string& name_buyer, std::string& date) :
            _id_order(id_order),
            _address(address),
            _name_buyer(name_buyer),
            _date(date)
    {

    }

    ~value_in_memory_cash()
    {
    }

    value_in_memory_cash(const value_in_memory_cash& other) :
            _id_order(other._id_order),
            _address(other._address),
            _name_buyer(other._name_buyer),
            _date(other._date)
    {

    }

    value_in_memory_cash& operator=(const value_in_memory_cash& other)
    {
        if (this != &other)
        {
            _id_order = other._id_order;
            _address = other._address;
            _name_buyer = other._name_buyer;
            _date = other._date;
        }

        return *this;
    }

    value_in_memory_cash(value_in_memory_cash&& other) noexcept :
            _id_order(other._id_order),
            _address(std::move(other._address)),
            _name_buyer(std::move(other._name_buyer)),
            _date(std::move(other._date))
    {

    }

    value_in_memory_cash& operator=(value_in_memory_cash&& other) noexcept
    {
        if (this != &other)
        {
            _id_order = other._id_order;
            _address = std::move(other._address);
            _name_buyer = std::move(other._name_buyer);
            _date = std::move(other._date);
        }

        return *this;
    }
};


class key
{

public:

    int _id_buyer;
};


#endif //COURSE_PROJECT_WB_H