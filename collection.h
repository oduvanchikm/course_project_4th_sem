#ifndef COURSE_PROJECT_COLLECTION_H
#define COURSE_PROJECT_COLLECTION_H

#include "wb.h"
#include "include/search_tree.h"
#include "include/b_tree.h"
#include "comparer.h"

class collection
{

public:

    associative_container<std::string, int> *_data;

public:

    void gg() {
        std::cout << "gg" << std::endl;
    }

public:
    collection() {
        _data = new b_tree<std::string, int>(3, key_comparer());
    }


public:
    collection(collection const &other)
    {

    }

    collection &operator=(collection const &other)
    {
        if (this == &other)
        {
            return *this;
        }

        delete this->_data;
    }

    collection(collection  &&other)
    {
        this->_data = other._data;
        other._data = nullptr;


    }

    collection &operator=(collection const &&other)
    {

    }
};

#endif //COURSE_PROJECT_COLLECTION_H
