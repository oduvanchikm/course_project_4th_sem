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

    void gg()
    {
        std::cout << "gg" << std::endl;
    }

    scheme()
    {
        _scheme = new b_tree<std::string, collection>(3, key_comparer());
    }

public:

    void add_collection(std::string const& name_collection) const
    {
        _scheme->insert(name_collection, std::move(collection()));
    }

    void remove_collection(std::string const & name_collection) const
    {
        _scheme->dispose(name_collection);
    }


public:

    scheme(scheme const &other)
    {
        this->_scheme = other._scheme;
    }

    scheme &operator=(scheme const &other)
    {
        if (this != &other)
        {
            delete this->_scheme;
            this->_scheme = other._scheme;
        }

        return *this;
    }

    scheme(scheme &&other) noexcept
    {
        this->_scheme = other._scheme;
        other._scheme = nullptr;
    }

    scheme &operator=(scheme &&other) noexcept
    {
        if (this != &other)
        {
            delete this->_scheme;
            this->_scheme = other._scheme;
            other._scheme = nullptr;
        }

        return *this;
    }
};
#endif //COURSE_PROJECT_SCHEME_H
