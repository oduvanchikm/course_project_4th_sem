#ifndef COURSE_PROJECT_SCHEME_H
#define COURSE_PROJECT_SCHEME_H
#include "database.h"
#include "collection.h"
#include "include/associative_container.h"
#include "include/b_tree.h"
#include "comparer.h"


class scheme
{

private:

    associative_container<std::string, collection> *_scheme;

public:

    explicit scheme() :
            _scheme(new b_tree<std::string, collection>(3, key_comparer()))
    {

    }

public:

    void add_collection(std::string const& name_collection) const
    {
        _scheme->insert(name_collection, std::move(collection()));
        std::cout << "add collection" << std::endl;
    }

    void remove_collection(std::string const& name_collection) const
    {
        _scheme->dispose(name_collection);
    }

    const collection& find_collection(std::string const& name_collection) const
    {
        return _scheme->obtain(name_collection);
    }


public:

    ~scheme()
    {
        delete _scheme;
    }

    scheme(scheme const &other) :
        _scheme(new b_tree<std::string, collection>(*dynamic_cast<b_tree<std::string, collection>*>(other._scheme)))
    {

    }

    scheme &operator=(scheme const &other)
    {
        if (this != &other)
        {
            delete this->_scheme;

            this->_scheme = new b_tree<std::string, collection>(*dynamic_cast<b_tree<std::string, collection>*>(other._scheme));
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
