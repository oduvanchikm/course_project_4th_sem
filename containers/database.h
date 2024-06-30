#ifndef COURSE_PROJECT_DATABASE_H
#define COURSE_PROJECT_DATABASE_H
#include "pool.h"
#include "../enums/enums.h"
#include "../tree/b_tree.h"
#include "../comparator/comparer.h"
#include "../validate/errors.h"

class database
{

private:

    bool _restore;

    static database* _instance;
    std::vector<std::pair<allocator *, std::vector<value *> *> *> _vector;

    size_t _t;
    enums::mode _mode;

public:

    void set_restore(bool result)
    {
        _restore = result;
    }

    bool get_restore()
    {
        return _restore;
    }

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
        _vector = {};
    }

public:

    [[nodiscard]] size_t get_t() const
    {
        return _t;
    }

    void set_t(size_t t)
    {
        _t = t;
    }

public:

    void add_pool(std::string const& pool_name) const
    {
        try
        {
            logger_singleton::get_instance()->get_logger()->trace("add pool in database");
            _database_entrypoint->insert(pool_name, pool(_t));
        }
        catch(const std::exception& e)
        {
            throw std::logic_error("can't add pool");
        }
    }

    void delete_pool(std::string const& pool_name) const
    {
        try
        {
            _database_entrypoint->dispose(pool_name);
        }
        catch(const std::exception& e)
        {
            throw std::logic_error("can't delete pool");
        }
    }

    [[nodiscard]] pool& find_pool(std::string const& pool_name) const
    {
        try
        {
            logger_singleton::get_instance()->get_logger()->trace("find pool in database");
            return const_cast<pool &>(_database_entrypoint->obtain(pool_name));
        }
        catch(const std::exception& e)
        {
            throw std::logic_error("can't find pool");
        }
    }

public:

    void add_scheme(std::string const& pool_name, std::string const& scheme_name) const
    {
        try
        {
            logger_singleton::get_instance()->get_logger()->trace("add scheme in database");
            find_pool(pool_name).add_scheme(scheme_name);
        }
        catch (const pool_error &e)
        {
            std::string error = "pool '" + pool_name + "' not found";
            throw std::logic_error(error);
        }
        catch (std::exception const &e)
        {
            throw std::logic_error(e.what());
        }
    }

    void delete_scheme(std::string const& pool_name, std::string const& scheme_name) const
    {
        try
        {
            logger_singleton::get_instance()->get_logger()->trace("delete scheme in database");
            find_pool(pool_name).remove_scheme(scheme_name);
        }
        catch (const pool_error &e)
        {
            std::string error = "pool '" + pool_name + "' not found";
            throw std::logic_error(error);
        }
        catch (std::exception const &e)
        {
            throw std::logic_error(e.what());
        }
    }

    [[nodiscard]] scheme& find_scheme(std::string const& pool_name, std::string const& scheme_name) const
    {
        try
        {
            logger_singleton::get_instance()->get_logger()->trace("find scheme in database");
            return const_cast<scheme &>(find_pool(pool_name).find_scheme(scheme_name));
        }
        catch (const pool_error &e)
        {
            std::string error = "pool '" + pool_name + "' not found";
            throw std::logic_error(error);
        }
        catch (std::exception const &e)
        {
            throw std::logic_error(e.what());
        }
    }

public:

    void add_collection(std::string const& pool_name, std::string const& scheme_name,
                        std::string const& collection_name, allocator_types
                         type, allocator_with_fit_mode::fit_mode fit_mode)
    {
        try
        {
            logger_singleton::get_instance()->get_logger()->trace("add collection in database");
            scheme &scheme_db = const_cast<scheme &>(find_pool(pool_name).find_scheme(scheme_name));
            allocator* allocator_database;

            switch (type)
            {
                case allocator_types::BOUNDARY_TAGS:
                    allocator_database = new allocator_boundary_tags(5000, nullptr, nullptr, fit_mode);
                    break;

                case allocator_types::BUDDIE_SYSTEM:
                    allocator_database = new allocator_buddies_system(54, nullptr, nullptr, fit_mode);
                    break;

                case allocator_types::SORTED_LIST:
                    allocator_database = new allocator_sorted_list(5000, nullptr, nullptr, fit_mode);
                    break;

                case allocator_types::GLOBAL_HEAP:
                    allocator_database = new allocator_global_heap();
                    break;
            }

            std::vector<value*>* vector = new std::vector<value*>{};
            std::pair<allocator*, std::vector<value*>*>* pair = new std::pair<allocator*, std::vector<value*>*>(allocator_database, vector);
            _vector.push_back(pair);

            scheme_db.add_collection(collection_name, type, fit_mode, pair);
        }
        catch (const pool_error &e)
        {
            std::string error = "pool '" + pool_name + "' not found";
            throw std::logic_error(error);
        }
        catch (const scheme_error &e)
        {
            std::string error = "scheme '" + scheme_name + "' not found in pool '" + pool_name + "'";
            throw std::logic_error(error);
        }
        catch (std::exception const &e)
        {
            throw std::logic_error(e.what());
        }
    }

    void delete_collection(std::string const& pool_name, std::string const& scheme_name,
                           std::string const& collection_name) const
    {
        try
        {
            logger_singleton::get_instance()->get_logger()->trace("delete collection in database");
            find_scheme(pool_name, scheme_name).remove_collection(collection_name);
        }
        catch (const pool_error &e)
        {
            std::string error = "pool '" + pool_name + "' not found";
            throw std::logic_error(error);
        }
        catch (const scheme_error &e)
        {
            std::string error = "scheme '" + scheme_name + "' not found in pool '" + pool_name + "'";
            throw std::logic_error(error);
        }
        catch (std::exception const &e)
        {
            throw std::logic_error(e.what());
        }
    }

    [[nodiscard]] collection& find_collection(std::string const& pool_name, std::string const& scheme_name,
                                std::string const& collection_name) const
    {
        try
        {
            logger_singleton::get_instance()->get_logger()->trace("find collection in database");
            return const_cast<collection&>((find_scheme(pool_name, scheme_name)).find_collection(collection_name));
        }
        catch (const pool_error &e)
        {
            std::string error = "pool '" + pool_name + "' not found";
            throw std::logic_error(error);
        }
        catch (const scheme_error &e)
        {
            std::string error = "scheme '" + scheme_name + "' not found in pool '" + pool_name + "'";
            throw std::logic_error(error);
        }
        catch (std::exception const &e)
        {
            throw std::logic_error(e.what());
        }
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
            int id_oder) const
    {
        try
        {
            logger_singleton::get_instance()->get_logger()->trace("add value in database in memory cache");
            find_pool(pool_name).find_scheme(scheme_name)
                    .find_collection(collection_name)
                    .add_value(id_buyer, name, date, address, id_oder);
        }
        catch (const pool_error &e)
        {
            std::string error = "pool '" + pool_name + "' not found";
            throw std::logic_error(error);
        }
        catch (const scheme_error &e)
        {
            std::string error = "scheme '" + scheme_name + "' not found in pool '" + pool_name + "'";
            throw std::logic_error(error);
        }
        catch (const collection_error &e)
        {
            std::string error = "collection '" + collection_name + "' not found in scheme '" + scheme_name + "' in pool '" + pool_name + "'";
            throw std::logic_error(error);
        }
        catch (std::exception const &e)
        {
            throw std::logic_error(e.what());
        }
    }

    // path_file, start_value_bytes, size_value

    void add_value(
            std::string const& pool_name,
            std::string const& scheme_name,
            std::string const& collection_name,
            int id_buyer,
            long start_value_bytes,
            long size_value) const
    {
        try
        {
            logger_singleton::get_instance()->get_logger()->trace("add value in database for file system");
            find_pool(pool_name).find_scheme(scheme_name)
                    .find_collection(collection_name)
                    .add_value(id_buyer, start_value_bytes, size_value);
        }
        catch (const pool_error &e)
        {
            std::string error = "pool '" + pool_name + "' not found";
            throw std::logic_error(error);
        }
        catch (const scheme_error &e)
        {
            std::string error = "scheme '" + scheme_name + "' not found in pool '" + pool_name + "'";
            throw std::logic_error(error);
        }
        catch (const collection_error &e)
        {
            std::string error = "collection '" + collection_name + "' not found in scheme '" + scheme_name + "' in pool '" + pool_name + "'";
            throw std::logic_error(error);
        }
        catch (std::exception const &e)
        {
            throw std::logic_error(e.what());
        }
    }

    void update_value(
            std::string const& pool_name,
            std::string const& scheme_name,
            std::string const& collection_name,
            int id_buyer,
            std::string& name,
            std::string& date,
            std::string& address,
            int id_oder) const
    {
        try
        {
            logger_singleton::get_instance()->get_logger()->trace("update value in database in memory cache");
            find_pool(pool_name).find_scheme(scheme_name)
                    .find_collection(collection_name)
                    .update_value(id_buyer, id_oder, name, address, date);
        }
        catch (const pool_error &e)
        {
            std::string error = "pool '" + pool_name + "' not found";
            throw std::logic_error(error);
        }
        catch (const scheme_error &e)
        {
            std::string error = "scheme '" + scheme_name + "' not found in pool '" + pool_name + "'";
            throw std::logic_error(error);
        }
        catch (const collection_error &e)
        {
            std::string error = "collection '" + collection_name + "' not found in scheme '" + scheme_name + "' in pool '" + pool_name + "'";
            throw std::logic_error(error);
        }
        catch (std::exception const &e)
        {
            throw std::logic_error(e.what());
        }
    }

    void update_value(
            std::string const& pool_name,
            std::string const& scheme_name,
            std::string const& collection_name,
            int id_buyer,
            long start_value_bytes,
            long size_value) const
    {
        try
        {
            logger_singleton::get_instance()->get_logger()->trace("update value in database for file system");
            find_pool(pool_name).find_scheme(scheme_name)
                    .find_collection(collection_name)
                    .update_value(id_buyer, start_value_bytes, size_value);
        }
        catch (const pool_error &e)
        {
            std::string error = "pool '" + pool_name + "' not found";
            throw std::logic_error(error);
        }
        catch (const scheme_error &e)
        {
            std::string error = "scheme '" + scheme_name + "' not found in pool '" + pool_name + "'";
            throw std::logic_error(error);
        }
        catch (const collection_error &e)
        {
            std::string error = "collection '" + collection_name + "' not found in scheme '" + scheme_name + "' in pool '" + pool_name + "'";
            throw std::logic_error(error);
        }
        catch (std::exception const &e)
        {
            throw std::logic_error(e.what());
        }
    }

    [[nodiscard]] value* obtain_value(
            std::string const& pool_name,
            std::string const& scheme_name,
            std::string const& collection_name,
            key key_value) const
    {
        try
        {
            logger_singleton::get_instance()->get_logger()->trace("obtain value in database");
            return find_pool(pool_name).find_scheme(scheme_name)
                    .find_collection(collection_name)
                    .find_value(key_value);
        }
        catch (const pool_error &e)
        {
            std::string error = "pool '" + pool_name + "' not found";
            throw std::logic_error(error);
        }
        catch (const scheme_error &e)
        {
            std::string error = "scheme '" + scheme_name + "' not found in pool '" + pool_name + "'";
            throw std::logic_error(error);
        }
        catch (const collection_error &e)
        {
            std::string error = "collection '" + collection_name + "' not found in scheme '" + scheme_name + "' in pool '" + pool_name + "'";
            throw std::logic_error(error);
        }
        catch (std::exception const &e)
        {
            throw std::logic_error(e.what());
        }
    }

    [[nodiscard]] value* obtain_value(
            std::string const& pool_name,
            std::string const& scheme_name,
            std::string const& collection_name,
            int id_buyer) const
    {
        try
        {
            logger_singleton::get_instance()->get_logger()->trace("obtain value in database");
            return find_pool(pool_name).find_scheme(scheme_name)
                    .find_collection(collection_name)
                    .find_value(key(id_buyer));
        }
        catch (const pool_error &e)
        {
            std::string error = "pool '" + pool_name + "' not found";
            throw std::logic_error(error);
        }
        catch (const scheme_error &e)
        {
            std::string error = "scheme '" + scheme_name + "' not found in pool '" + pool_name + "'";
            throw std::logic_error(error);
        }
        catch (const collection_error &e)
        {
            std::string error = "collection '" + collection_name + "' not found in scheme '" + scheme_name + "' in pool '" + pool_name + "'";
            throw std::logic_error(error);
        }
        catch (std::exception const &e)
        {
            throw std::logic_error(e.what());
        }
    }

    void delete_value(
            std::string const& pool_name,
            std::string const& scheme_name,
            std::string const& collection_name,
            int id_buyer) const
    {
        try
        {
            logger_singleton::get_instance()->get_logger()->trace("delete value");
            find_pool(pool_name).find_scheme(scheme_name)
                    .find_collection(collection_name)
                    .delete_value(id_buyer);
        }
        catch (const pool_error &e)
        {
            std::string error = "pool '" + pool_name + "' not found";
            throw std::logic_error(error);
        }
        catch (const scheme_error &e)
        {
            std::string error = "scheme '" + scheme_name + "' not found in pool '" + pool_name + "'";
            throw std::logic_error(error);
        }
        catch (const collection_error &e)
        {
            std::string error = "collection '" + collection_name + "' not found in scheme '" + scheme_name + "' in pool '" + pool_name + "'";
            throw std::logic_error(error);
        }
        catch (std::exception const &e)
        {
            throw std::logic_error(e.what());
        }
    }

    std::vector<value*> obtain_between_value(
            std::string const& pool_name,
            std::string const& scheme_name,
            std::string const& collection_name,
            key &lower_bound,
            key &upper_bound,
            bool lower_bound_inclusive,
            bool upper_bound_inclusive) const
    {
        try
        {
            logger_singleton::get_instance()->get_logger()->trace("obtain between value");
            return find_pool(pool_name).find_scheme(scheme_name)
                                .find_collection(collection_name)
                                .obtain_between(lower_bound, upper_bound,
                                                lower_bound_inclusive,
                                                upper_bound_inclusive);
        }
        catch (const pool_error &e)
        {
            std::string error = "pool '" + pool_name + "' not found";
            throw std::logic_error(error);
        }
        catch (const scheme_error &e)
        {
            std::string error = "scheme '" + scheme_name + "' not found in pool '" + pool_name + "'";
            throw std::logic_error(error);
        }
        catch (const collection_error &e)
        {
            std::string error = "collection '" + collection_name + "' not found in scheme '" + scheme_name + "' in pool '" + pool_name + "'";
            throw std::logic_error(error);
        }
        catch (std::exception const &e)
        {
            throw std::logic_error(e.what());
        }
    }

    std::vector<value*> obtain_between_value(
            std::string const& pool_name,
            std::string const& scheme_name,
            std::string const& collection_name,
            int lower_bound,
            int upper_bound,
            bool lower_bound_inclusive,
            bool upper_bound_inclusive) const
    {
        try
        {
            logger_singleton::get_instance()->get_logger()->trace("obtain between value");
            return find_pool(pool_name).find_scheme(scheme_name)
                    .find_collection(collection_name)
                    .obtain_between(key(lower_bound), key(upper_bound),
                                    lower_bound_inclusive,
                                    upper_bound_inclusive);
        }
        catch (const pool_error &e)
        {
            std::string error = "pool '" + pool_name + "' not found";
            throw std::logic_error(error);
        }
        catch (const scheme_error &e)
        {
            std::string error = "scheme '" + scheme_name + "' not found in pool '" + pool_name + "'";
            throw std::logic_error(error);
        }
        catch (const collection_error &e)
        {
            std::string error = "collection '" + collection_name + "' not found in scheme '" + scheme_name + "' in pool '" + pool_name + "'";
            throw std::logic_error(error);
        }
        catch (std::exception const &e)
        {
            throw std::logic_error(e.what());
        }
    }

public:

    ~database()
    {
        if (!_vector.empty())
        {
            for (auto *each : _vector)
            {
                allocator *allocator_database = each->first;
                for (value *each1 : *(each->second))
                {
                    if (get_mode() == enums::mode::file_system)
                    {
                        allocator_database->deallocate(reinterpret_cast<value_file_system *>(each1));
                    }
                    else
                    {
                        allocator_database->deallocate(reinterpret_cast<value_in_memory_cache *>(each1));
                    }
                }
                delete allocator_database;
                delete each->second;
                delete each;
            }
        }
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