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
    allocator* _allocator_data_base;



public:

    explicit pool(allocator* allocator_data_base = nullptr) :
            _pool(new b_tree<std::string, scheme>(3, key_comparer())),
            _allocator_data_base(allocator_data_base)
    {

    }

public:

    [[nodiscard]] allocator* get_allocator() const
    {
        return _allocator_data_base;
    }

public:

    void add_scheme(std::string const &scheme_name) const
    {
        _pool->insert(scheme_name, std::move(scheme()));
    }

    [[nodiscard]] scheme read_scheme(std::string const &scheme_name) const
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
        _pool(new b_tree<std::string, scheme>(*reinterpret_cast<b_tree<std::string, scheme>*>(other._pool))),
        _allocator_data_base(other._allocator_data_base)
    {

    }

    pool &operator=(pool const &other)
    {
        if (this != &other)
        {
            delete this->_pool;

            if (this->_allocator_data_base != other._allocator_data_base)
            {
                delete this->_allocator_data_base;
                this->_allocator_data_base = other._allocator_data_base;
            }

            this->_pool = new b_tree<std::string, scheme>(*reinterpret_cast<b_tree<std::string, scheme>*>(other._pool));
        }

        return *this;
    }

    pool(pool&& other) noexcept
    {
        this->_pool = other._pool;
        other._pool = nullptr;

        this->_allocator_data_base = other._allocator_data_base;
        other._allocator_data_base = nullptr;
    }

    pool &operator=(pool &&other) noexcept
    {
        if (this != &other)
        {
            delete this->_pool;
            this->_pool = other._pool;
            other._pool = nullptr;

            delete this->_allocator_data_base;
            this->_allocator_data_base = other._allocator_data_base;
            other._allocator_data_base = nullptr;
        }

        return *this;
    }
};

#endif //COURSE_PROJECT_POOL_H
