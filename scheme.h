#ifndef COURSE_PROJECT_SCHEME_H
#define COURSE_PROJECT_SCHEME_H
#include "database.h"
#include "collection.h"
#include "include/associative_container.h"
#include "include/b_tree.h"
#include "comparer.h"

class scheme
{

public:

    associative_container<std::string, collection> *_scheme;

public:

    void gg() {
        std::cout << "gg" << std::endl;
    }

    scheme()
    {
        _scheme = new b_tree<std::string, collection>(3, key_comparer());
    }


public:

    void add_collection(std::string const& name_collection)
    {
        _scheme->insert(name_collection, std::move(collection()));
    }

public:
    scheme(scheme const &other)
    {

    }

    scheme &operator=(scheme const &other)
    {
        if (this == &other)
        {
            return *this;
        }

        delete this->_scheme;
    }

    scheme(scheme  &&other)
    {
        this->_scheme = other._scheme;

        other._scheme = nullptr;
    }

    scheme &operator=(scheme const &&other)
    {

    }
};
#endif //COURSE_PROJECT_SCHEME_H
