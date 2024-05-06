#ifndef COURSE_PROJECT_COLLECTION_H
#define COURSE_PROJECT_COLLECTION_H
#include "wb.h"
#include "include/search_tree.h"
#include "include/b_tree.h"
#include "comparer.h"

class collection
{

public:

    associative_container<key, value> *_data;

//    associative_container<std::string, int> *_data;

public:

    void gg()
    {
        std::cout << "gg" << std::endl;
    }

public:

    collection()
    {
        _data = new b_tree<key, value>(3, key_comparer_new());
    }

public:

    void add_value(key& key_value) const
    {
        _data->insert(key_value, std::move(value()));
    }


public:

    collection(collection const &other)
    {
        this->_data = other._data;
    }

    collection &operator=(collection const &other)
    {
        if (this != &other)
        {
            delete this->_data;
            this->_data = other._data;
        }

        return *this;
    }

    collection(collection &&other) noexcept
    {
        this->_data = other._data;
        other._data = nullptr;
    }

    collection &operator=(collection &&other) noexcept
    {
        if (this != &other)
        {
            delete this->_data;
            this->_data = other._data;
            other._data = nullptr;
        }

        return *this;
    }
};

#endif //COURSE_PROJECT_COLLECTION_H
