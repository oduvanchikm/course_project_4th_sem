#ifndef COURSE_PROJECT_DATABASE_H
#define COURSE_PROJECT_DATABASE_H
#include "pool.h"
#include "scheme.h"
#include "collection.h"
#include "enums.h"
#include "include/search_tree.h"
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
    allocator* _allocator_database;

    size_t _t;
    enums::mode _mode;

public:

    b_tree<std::string, pool> *_database_entrypoint;

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
        _database_entrypoint->insert(pool_name, pool(_t));
    }

    void delete_pool(std::string const& pool_name) const
    {
        _database_entrypoint->dispose(pool_name);
    }

    pool& find_pool(std::string const& pool_name) const
    {
        return const_cast<pool&>(_database_entrypoint->obtain(pool_name));
    }

    void add_scheme(std::string const& pool_name, std::string const& scheme_name)
    {
        (find_pool(pool_name)).add_scheme(scheme_name);
    }

    void delete_scheme(std::string const& pool_name, std::string const& scheme_name) const
    {
        (find_pool(pool_name)).remove_scheme(scheme_name);
    }

    scheme& find_scheme(std::string const& pool_name, std::string const& scheme_name) const
    {
        return const_cast<scheme&>((find_pool(pool_name)).find_scheme(scheme_name));
    }

    void add_collection(std::string const& pool_name, std::string const& scheme_name,
                        std::string const& collection_name)
    {
        (find_scheme(pool_name, scheme_name)).add_collection(collection_name);
    }

    void delete_collection(std::string const& pool_name, std::string const& scheme_name,
                           std::string const& collection_name) const
    {
        (find_scheme(pool_name, scheme_name)).remove_collection(collection_name);
    }

    collection& find_collection(std::string const& pool_name, std::string const& scheme_name,
                                std::string const& collection_name) const
    {
        return const_cast<collection&>((find_scheme(pool_name, scheme_name)).find_collection(collection_name));
    }

//    void add_value(std::string const& pool_name, std::string const& scheme_name,
//                        std::string const& collection_name, allocator_types type,
//                        allocator_with_fit_mode* fit_mode)
//    {
//        collection& _collection = const_cast<collection&>(find_collection(pool_name, scheme_name, collection_name));
//        allocator* allocator_database;
//
//        switch(type)
//        {
//            case allocator_types::BUDDIE_SYSTEM:
//                allocator_database = new allocator_buddies_system(15, nullptr, nullptr, fit_mode);
//                break;
//
//            case allocator_types::BOUNDARY_TAGS:
//                allocator_database = new allocator_boundary_tags(1500, nullptr, nullptr, fit_mode);
//                break;
//
//            case allocator_types::SORTED_LIST:
//                allocator_database = new allocator_sorted_list(1500, nullptr, nullptr, fit_mode);
//                break;
//
//            case allocator_types::GLOBAL_HEAP:
//                allocator_database = new allocator_global_heap();
//                break;
//        }
//    }

    void add_value(
            std::string const& pool_name,
            std::string const& scheme_name,
            std::string const& collection_name,
            key const &key_value,
            value const &value_value)
    {
        find_pool(pool_name).find_scheme(scheme_name).find_collection(collection_name);
    }

    void add_value(
            std::string const& pool_name,
            std::string const& scheme_name,
            std::string const& collection_name,
            key const &key_value,
            value &&value_value)
    {
        find_pool(pool_name).find_scheme(scheme_name).find_collection(collection_name);
    }

    void update_value(
            std::string const& pool_name,
            std::string const& scheme_name,
            std::string const& collection_name,
            key const &key_value,
            value const &value_value)
    {
        find_pool(pool_name).find_scheme(scheme_name).find_collection(collection_name);
    }

    void update_value(
            std::string const& pool_name,
            std::string const& scheme_name,
            std::string const& collection_name,
            key const &key_value,
            value &&value_value)
    {
        find_pool(pool_name).find_scheme(scheme_name).find_collection(collection_name);
    }

//    value &obtain_value(
//            std::string const& pool_name,
//            std::string const& scheme_name,
//            std::string const& collection_name,
//            key const &key_value)
//    {
//        return find_pool(pool_name).find_scheme(scheme_name).find_collection(collection_name).
//    }
//
//    value dispose_value(
//            std::string const& pool_name,
//            std::string const& scheme_name,
//            std::string const& collection_name,
//            key const &key)
//    {
//        return find_pool(pool_name).find_scheme(scheme_name).find_collection(collection_name);
//    }

    std::vector<typename associative_container<key, value>::key_value_pair> obtain_between_value(
            std::string const& pool_name,
            std::string const& scheme_name,
            std::string const& collection_name,
            key const &lower_bound,
            key const &upper_bound,
            bool lower_bound_inclusive,
            bool upper_bound_inclusive)
    {
        find_pool(pool_name).find_scheme(scheme_name).find_collection(collection_name);
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

public:

    void *set_mode(enums::mode mode_database)
    {
        _mode = mode_database;
        return this;
    }

private:

    database& validate_path(std::string const &subpath)
    {

    }

    database& validate_file_name(std::string const &file_name)
    {

    }

};

database* database::_instance = nullptr;


#endif //COURSE_PROJECT_DATABASE_H
