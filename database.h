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

public:

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

public:

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

public:

//    info about buyer: key - id_buyer, value - name, date, address, id_oder

    void add_value(
            std::string const& pool_name,
            std::string const& scheme_name,
            std::string const& collection_name,
            int id_buyer,
            std::string& name,
            std::string& date,
            std::string& address,
            int id_oder)
    {
        find_pool(pool_name).find_scheme(scheme_name)
                            .find_collection(collection_name)
                            .add_value(id_buyer, id_oder, name, address, date);
    }

    // path_file, start_value_bytes, size_value

    void add_value(
            std::string const& pool_name,
            std::string const& scheme_name,
            std::string const& collection_name,
            int id_buyer,
            std::string &path_file,
            std::pair<long, long> first_byte_and_size)
//            long start_value_bytes,
//            long size_value)
    {
        long start_value_bytes = first_byte_and_size.first;
        long size_value = first_byte_and_size.second;

        find_pool(pool_name).find_scheme(scheme_name)
                            .find_collection(collection_name)
                            .add_value(id_buyer, path_file, start_value_bytes, size_value);
    }

    void update_value(
            std::string const& pool_name,
            std::string const& scheme_name,
            std::string const& collection_name,
            int id_buyer,
            std::string& name,
            std::string& date,
            std::string& address,
            int id_oder)
    {
        find_pool(pool_name).find_scheme(scheme_name)
                            .find_collection(collection_name)
                            .update_value(id_buyer, id_oder, name, address, date);
    }

    void update_value(
            std::string const& pool_name,
            std::string const& scheme_name,
            std::string const& collection_name,
            int id_buyer,
            std::string &path_file,
            std::pair<long, long> first_byte_and_size)
//            long start_value_bytes,
//            long size_value)
    {
        long start_value_bytes = first_byte_and_size.first;
        long size_value = first_byte_and_size.second;

        find_pool(pool_name).find_scheme(scheme_name)
                            .find_collection(collection_name)
                            .update_value(id_buyer, path_file, start_value_bytes, size_value);
    }

    value* obtain_value(
            std::string const& pool_name,
            std::string const& scheme_name,
            std::string const& collection_name,
            int id_buyer)
    {
        return find_pool(pool_name).find_scheme(scheme_name)
                                    .find_collection(collection_name)
                                    .find_value(id_buyer);
    }

    void delete_value(
            std::string const& pool_name,
            std::string const& scheme_name,
            std::string const& collection_name,
            int id_buyer)
    {
        return find_pool(pool_name).find_scheme(scheme_name)
                                    .find_collection(collection_name)
                                    .delete_value(id_buyer);
    }

//    std::vector<typename associative_container<key, value>::key_value_pair> obtain_between_value(
//            std::string const& pool_name,
//            std::string const& scheme_name,
//            std::string const& collection_name,
//            key const &lower_bound,
//            key const &upper_bound,
//            bool lower_bound_inclusive,
//            bool upper_bound_inclusive)
//    {
//        find_pool(pool_name).find_scheme(scheme_name).find_collection(collection_name);
//    }


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

    enums::mode get_mode(enums::mode mode_database)
    {
        return _mode = mode_database;
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
