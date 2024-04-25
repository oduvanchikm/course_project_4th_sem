#ifndef COURSE_PROJECT_DATABASE_H
#define COURSE_PROJECT_DATABASE_H
#include "pool.h"
#include "include/b_tree.h"
#include "allocators/allocator_buddies_system.h"

class data_base {

private:
    static data_base* _instance;

public:
    static data_base* get_instance() {

        if (_instance == nullptr)
        {
            _instance = new data_base();
        }

        return _instance;
    }

private:
    search_tree<std::string, pool> *_database_entrypoint;

public:
    data_base() {

        std::less<std::string> _compare;
        _database_entrypoint = new b_tree<std::string, pool>(3);

        _instance = this;
    }


public:
    void add_pool(
            std::string const& pool_name)
            {

        _database_entrypoint->insert(pool_name, std::move(pool()));

    }

    void add_sheme(std::string const& pool_name, std::string const& name_scheme) {


            pool pool_tree = const_cast<pool&>(_database_entrypoint->obtain(pool_name));

            //TODO: Exeption ?!

            pool_tree.add_scheme(name_scheme);

    }

    void add_collection();

    void remove_pool();

    void remove_sheme();

    void remove_collection();

    void update_data();




public:
    ~data_base()
    {
        delete _database_entrypoint;
    }
    data_base(data_base const&) = delete;
    data_base(data_base&&) = delete;
    data_base& operator=(data_base const&) = delete;
    data_base& operator=(data_base&&) = delete;
};


#endif //COURSE_PROJECT_DATABASE_H
