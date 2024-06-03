#ifndef COURSE_PROJECT_POOL_H
#define COURSE_PROJECT_POOL_H
#include "database.h"
#include "scheme.h"
#include "../tree/search_tree.h"
#include "../comparator/comparer.h"

class pool final
{

private:

    search_tree<std::string, scheme>* _pool;
    size_t _t;

public:

    search_tree<std::string, scheme>* get_pool()
    {
        return _pool;
    }

    explicit pool(size_t t) :
            _t(t),
            _pool(new b_tree<std::string, scheme>(t, key_comparer()))
    {

    }


public:

    void add_scheme(std::string const &scheme_name) const
    {
        try
        {
            _pool->insert(scheme_name, scheme(_t));
        }
        catch (std::exception const &e)
        {
            throw std::logic_error(e.what());
        }
    }

    [[nodiscard]] scheme& find_scheme(std::string const &scheme_name) const
    {
        try
        {
            return const_cast<scheme&>(_pool->obtain(scheme_name));
        }
        catch (std::exception const &e)
        {
            throw std::logic_error(e.what());
        }
    }

    void remove_scheme(std::string const & scheme_name) const
    {
        try
        {
            _pool->dispose(scheme_name);
        }
        catch (std::exception const &e)
        {
            throw std::logic_error(e.what());
        }
    }

public:

    ~pool()
    {
        delete _pool;
    }

    pool(pool const &other) :
            _pool(new b_tree<std::string, scheme>(*dynamic_cast<b_tree<std::string, scheme>*>(other._pool)))
    {
        _t = other._t;
    }

    pool &operator=(pool const &other)
    {
        if (this != &other)
        {
            _t = other._t;
            delete this->_pool;
            this->_pool = new b_tree<std::string, scheme>(*dynamic_cast<b_tree<std::string, scheme>*>(other._pool));
        }

        return *this;
    }

    pool(pool&& other) noexcept
    {
        _t = other._t;
        this->_pool = other._pool;
        other._pool = nullptr;
    }

    pool &operator=(pool &&other) noexcept
    {
        if (this != &other)
        {
            _t = other._t;
            delete this->_pool;
            this->_pool = other._pool;
            other._pool = nullptr;
        }

        return *this;
    }
};

#endif //COURSE_PROJECT_POOL_H