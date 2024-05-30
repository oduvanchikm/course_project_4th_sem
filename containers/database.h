#ifndef COURSE_PROJECT_DATABASE_H
#define COURSE_PROJECT_DATABASE_H
#include "pool.h"
#include "../enums/enums.h"
#include "../tree/b_tree.h"
#include "../comparator/comparer.h"
#include "../chain_of_responsibility/chain_of_responsibility_handler.h"
#include "../chain_of_responsibility/chain_of_responsibility.h"
#include "../chain_of_responsibility/request_with_command_chain.h"
#include "../chain_of_responsibility/request_with_command.h"
#include "../chain_of_responsibility/handler.h"


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

    size_t get_t() const
    {
        return _t;
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
        pool& p = const_cast<pool&>(_database_entrypoint->obtain(pool_name));
        return p;
    }

public:

    void add_scheme(std::string const& pool_name, std::string const& scheme_name)
    {
        find_pool(pool_name).add_scheme(scheme_name);
    }

    void delete_scheme(std::string const& pool_name, std::string const& scheme_name) const
    {
        find_pool(pool_name).remove_scheme(scheme_name);
    }

    scheme& find_scheme(std::string const& pool_name, std::string const& scheme_name) const
    {
        scheme& s = const_cast<scheme&>(find_pool(pool_name).find_scheme(scheme_name));
        return s;
    }

public:

    void add_collection(std::string const& pool_name, std::string const& scheme_name,
                        std::string const& collection_name, allocator_types
                         type, allocator_with_fit_mode::fit_mode fit_mode)
    {
        scheme& scheme_db = const_cast<scheme&>(find_pool(pool_name).find_scheme(scheme_name));

        switch (type)
        {
            case allocator_types::BOUNDARY_TAGS:
                _allocator_database = new allocator_boundary_tags(2000, nullptr, nullptr, fit_mode);
                break;

            case allocator_types::BUDDIE_SYSTEM:
                _allocator_database = new allocator_buddies_system(24, nullptr, nullptr, fit_mode);
                break;

            case allocator_types::SORTED_LIST:
                _allocator_database = new allocator_sorted_list(2000, nullptr, nullptr, fit_mode);
                break;

            case allocator_types::GLOBAL_HEAP:
                _allocator_database = new allocator_global_heap();
                break;
        }

        scheme_db.add_collection(collection_name, type, fit_mode, _allocator_database);
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
            std::string const& name,
            std::string const& date,
            std::string const& address,
            int id_oder)
    {
        find_pool(pool_name).find_scheme(scheme_name)
                .find_collection(collection_name)
                .add_value(id_buyer, name, date, address, id_oder);
    }

    // path_file, start_value_bytes, size_value

    void add_value(
            std::string const& pool_name,
            std::string const& scheme_name,
            std::string const& collection_name,
            int id_buyer,
            long start_value_bytes,
            long size_value)
    {
        find_pool(pool_name).find_scheme(scheme_name)
                .find_collection(collection_name)
                .add_value(id_buyer, start_value_bytes, size_value);
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
            long start_value_bytes,
            long size_value)
    {
        find_pool(pool_name).find_scheme(scheme_name)
                .find_collection(collection_name)
                .update_value(id_buyer, start_value_bytes, size_value);
    }

    value* obtain_value(
            std::string const& pool_name,
            std::string const& scheme_name,
            std::string const& collection_name,
            key key_value)
    {
        return find_pool(pool_name).find_scheme(scheme_name)
                .find_collection(collection_name)
                .find_value(key_value);
    }

    value* obtain_value(
            std::string const& pool_name,
            std::string const& scheme_name,
            std::string const& collection_name,
            int id_buyer)
    {
        return find_pool(pool_name).find_scheme(scheme_name)
                .find_collection(collection_name)
                .find_value(key(id_buyer));
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

    enums::mode get_mode()
    {
        return this->_mode;
    }

    enums::mode set_mode(enums::mode mode)
    {
        _mode = mode;
    }

public:

    std::string& validate_path(std::string &sub_path)
    {
        for (char symbol : sub_path)
        {
            if (std::isalnum(symbol) && symbol == '_')
            {
                return sub_path;
            }
        }
        throw std::logic_error("path has invalid symbols");
    }

    bool validate_input_file_path(std::string &input_file_path)
    {
        std::string extension = ".txt";

        if (input_file_path.length() >= extension.length() &&
            input_file_path.compare(input_file_path.length() - extension.length(), extension.length(), extension) == 0)
        {
            return true;
        }

        return false;
    }

};

database* database::_instance = nullptr;


#endif //COURSE_PROJECT_DATABASE_H