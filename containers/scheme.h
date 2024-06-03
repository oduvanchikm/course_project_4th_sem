#ifndef COURSE_PROJECT_SCHEME_H
#define COURSE_PROJECT_SCHEME_H
#include "database.h"
#include "collection.h"
#include "../tree/associative_container.h"
#include "../tree/b_tree.h"
#include "../comparator/comparer.h"

class scheme
{

private:

    associative_container<std::string, collection> *_scheme;
    size_t _t;

public:

    associative_container<std::string, collection>* get_scheme()
    {
        return _scheme;
    }

    explicit scheme(size_t t) :
            _t(t),
            _scheme(new b_tree<std::string, collection>(t, key_comparer()))
    {

    }

public:

    void add_collection(std::string const& name_collection, allocator_types type,
                        allocator_with_fit_mode::fit_mode fit_mode, allocator* allocator_database) const
    {
        try
        {
            _scheme->insert(name_collection, collection(allocator_database, _t, fit_mode, type));
        }
        catch (std::exception const &e)
        {
            throw std::logic_error(e.what());
        }
    }

    void remove_collection(std::string const& name_collection) const
    {
        try
        {
            _scheme->dispose(name_collection);
        }
        catch (std::exception const &e)
        {
            throw std::logic_error(e.what());
        }
    }

    [[nodiscard]] collection& find_collection(std::string const& name_collection) const
    {
        try
        {
            return const_cast<collection&>(_scheme->obtain(name_collection));
        }
        catch (std::exception const &e)
        {
            throw std::logic_error(e.what());
        }
    }


public:

    ~scheme()
    {
        delete _scheme;
    }

    scheme(scheme const &other)
    {
        _t = other._t;
        _scheme = new b_tree<std::string, collection>(*dynamic_cast<b_tree<std::string, collection>*>(other._scheme));
    }

    scheme &operator=(scheme const &other)
    {
        if (this != &other)
        {
            _t = other._t;
            delete this->_scheme;
            _scheme =  new b_tree<std::string, collection>(*dynamic_cast<b_tree<std::string, collection>*>(other._scheme));
        }
        return *this;
    }

    scheme(scheme &&other) noexcept:
        _scheme(other._scheme)
    {
        _t = other._t;
        other._scheme = nullptr;
    }

    scheme &operator=(scheme &&other) noexcept
    {
        if(this != &other)
        {
            _t = other._t;
            delete this->_scheme;
            _scheme = other._scheme;
            other._scheme = nullptr;
        }
        return *this;
    }
};

#endif //COURSE_PROJECT_SCHEME_H