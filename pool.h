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

    void gg()
    {
        std::cout << "gg" << std::endl;
    }

    pool()
    {
        _pool = new b_tree<std::string, scheme>(3, key_comparer());
    }

public:

    void add_scheme(std::string const &scheme_name) const
    {
        try
        {
            _pool->insert(scheme_name, std::move(scheme()));
        }
        catch (const std::exception& e)
        {
            std::cout << e.what() << std::endl;
            std::cout << "[ERROR][POOL.H] scheme with name: " << scheme_name << " not found" << std::endl;
        }
    }

    [[nodiscard]] scheme read_scheme(std::string const &scheme_name) const
    {
       return _pool->obtain(scheme_name);
    }

    void remove_scheme(std::string const & scheme_name) const
    {
        try
        {
            _pool->dispose(scheme_name);
        }
        catch (const std::exception& e)
        {
            std::cout << e.what() << std::endl;
            std::cout << "[ERROR][POOL.H] scheme with name: " << scheme_name << " can't delete" << std::endl;
        }
    }

public:

    pool(pool const &other)
    {
        this->_pool = other._pool;
    }

    pool &operator=(pool const &other)
    {
        if (this != &other)
        {
            delete this->_pool;
            this->_pool = other._pool;
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
