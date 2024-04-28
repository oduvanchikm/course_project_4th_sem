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

    void gg() {
        std::cout << "gg" << std::endl;
    }

    pool()
    {
        _pool = new b_tree<std::string, scheme>(3, key_comparer());
    }

public:

    void add_scheme(std::string const& scheme_name)
    {
        _pool->insert(scheme_name, std::move(scheme()));
    }

public:

    pool(pool const &other) : _pool(other._pool)
    {

    }



    pool &operator=(pool const &other)
    {
        if (this == &other)
        {
            return *this;
        }

        delete this->_pool;
    }

    pool(pool&& other) noexcept
    {
        this->_pool = other._pool;
//        this->_allocator = other._allocator;
//        this->_tree_type = other._tree_type;

        other._pool = nullptr;
//        other._allocator = nullptr;
//        other._tree_type = tree_type::RED_BLACK_TREE;
    }

    pool &operator=(pool const &&other)
    {

    }

};

#endif //COURSE_PROJECT_POOL_H
