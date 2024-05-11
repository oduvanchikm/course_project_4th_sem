#ifndef COURSE_PROJECT_DATABASE_H
#define COURSE_PROJECT_DATABASE_H
#include "pool.h"
#include "include/b_tree.h"
#include "include/binary_search_tree.h"
#include "include/associative_container.h"
#include "comparer.h"
#include "logger/logger_guardant.h"
#include "logger/logger.h"
#include "logger/client_logger.h"
#include "logger/client_logger_builder.h"

class database
{

private:

    static database* _instance;

public:

    size_t _t;

    associative_container<std::string, pool> *_database_entrypoint;

// public:
//    enum class search_tree_variant
//    {
//        b_tree
//    };

public:

    static database* get_instance(size_t t)
    {

        if (_instance == nullptr)
        {
            _instance = new database(t);
        }

        return _instance;
    }

public:

    database(size_t t) :
        _t(t),
        _database_entrypoint(new b_tree<std::string, pool>(t, key_comparer()))
    {
        _instance = this;
    }

public:

    void add_pool(std::string const& pool_name) const
    {
        _database_entrypoint->insert(pool_name, std::move(pool(_t)));
        std::cout << "add pool" << std::endl;
    }

    void delete_pool(std::string const& pool_name) const
    {
        _database_entrypoint->dispose(pool_name);
    }

public:

    ~database()
    {
        delete _database_entrypoint;
    }

    database(database const &other) noexcept = delete;

    database(database const &&other) noexcept = delete;

    database &operator=(database &other) = delete;

    database &operator=(database &&other) = delete;

};

database* database::_instance = nullptr;


#endif //COURSE_PROJECT_DATABASE_H
