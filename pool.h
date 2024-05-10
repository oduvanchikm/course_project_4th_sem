#ifndef COURSE_PROJECT_POOL_H
#define COURSE_PROJECT_POOL_H
#include "database.h"
#include "scheme.h"
#include "include/binary_search_tree.h"
#include "comparer.h"

class pool
{

public:

    associative_container<std::string, scheme>* _pool;

public:

    explicit pool() :
            _pool(new b_tree<std::string, scheme>(3, key_comparer()))
    {

    }


public:

    void add_scheme(std::string const &scheme_name) const
    {
        _pool->insert(scheme_name, std::move(scheme()));
        std::cout << "scheme added uchu" << std::endl;
    }

    const scheme& find_scheme(std::string const &scheme_name) const
    {
       return _pool->obtain(scheme_name);
    }

    void remove_scheme(std::string const & scheme_name) const
    {
        _pool->dispose(scheme_name);
    }

public:

    ~pool()
    {
        delete _pool;
    }

    pool(pool const &other) :
            _pool(new b_tree<std::string, scheme>(*dynamic_cast<b_tree<std::string, scheme>*>(other._pool)))
    {
    }

    pool &operator=(pool const &other)
    {
        if (this != &other)
        {
            delete this->_pool;
            this->_pool = new b_tree<std::string, scheme>(*dynamic_cast<b_tree<std::string, scheme>*>(other._pool));
        }

        return *this;
    }

    pool(pool&& other) noexcept
    {
        this->_pool = other._pool;
        other._pool = nullptr;
    }

    pool &operator=(pool &&other) noexcept
    {
        if (this != &other)
        {
            delete this->_pool;
            this->_pool = other._pool;
            other._pool = nullptr;
        }

        return *this;
    }
};

#endif //COURSE_PROJECT_POOL_H
