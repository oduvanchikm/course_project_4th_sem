#ifndef COURSE_PROJECT_COLLECTION_H
#define COURSE_PROJECT_COLLECTION_H
#include "wb.h"
#include "../enums/enums.h"
#include "../tree/associative_container.h"
#include "../tree/b_tree.h"
#include "../comparator/comparer.h"
#include "../enums/allocator_types.h"
#include "allocator.h"
#include "allocator_guardant.h"
#include "allocator_with_fit_mode.h"
#include "allocator_global_heap.h"
#include "allocator_sorted_list.h"
#include "allocator_boundary_tags.h"
#include "allocator_buddies_system.h"
#include "../flyweight/flyweight_string.h"
#include "../flyweight/flyweight_fabric.h"

class collection
{

private:

    associative_container<key, value*> *_data;
    std::pair<allocator*, std::vector<value*>*>* _allocator_pair;
    allocator_with_fit_mode::fit_mode _fit_mode;
    size_t _t;
    allocator_types _type;

public:

    explicit collection(std::pair<allocator*, std::vector<value*>*>* pair, size_t t, allocator_with_fit_mode::fit_mode fit_mode, allocator_types type) :
            _t(t),
            _fit_mode(fit_mode),
            _type(type),
            _allocator_pair(pair),
            _data(new b_tree<key, value*>(t, key_comparer()))
    {

    }

public:

    void add_value(key& key_collection, value* value_collection) const
    {
        try
        {
            _data->insert(key_collection, value_collection);
        }
        catch (const std::exception& e)
        {
            throw std::logic_error(e.what());
        }
    }

    void add_value(int id_buyer, value* value)
    {
        try
        {
            _data->insert(key(id_buyer), value);
        }
        catch (const std::exception& e)
        {
            throw std::logic_error(e.what());
        }
    }

    void add_value(int id_buyer, long start_value_bytes, long string_size)
    {
        auto* value_file = const_cast<value_file_system*>(reinterpret_cast<value_file_system*>(_allocator_pair->first->allocate(
                sizeof(value_file_system), 1)));

        value_file->_start_value_bytes = start_value_bytes;
        value_file->_string_size = string_size;

        try
        {
            _data->insert(key(id_buyer), dynamic_cast<value *>(value_file));
        }
        catch (const std::exception& e)
        {
            _allocator_pair->first->deallocate(value_file);
            throw std::logic_error(e.what());
        }

        _allocator_pair->second->push_back(reinterpret_cast<value*>(value_file));
    }

    void add_value(int id_buyer, std::string const& name, std::string const& date,
                   std::string const& address, int id_oder)
    {
        auto *value_memory = reinterpret_cast<value_in_memory_cache *>(
                _allocator_pair->first->allocate(sizeof(value_in_memory_cache), 1));

        value_memory->_id_order = id_oder;
        value_memory->_date = string_flyweight_factory::get_instance().get_string_flyweight(date)->get_value();
        value_memory->_address = string_flyweight_factory::get_instance().get_string_flyweight(name)->get_value();
        value_memory->_name_buyer = string_flyweight_factory::get_instance().get_string_flyweight(address)->get_value();

//        value_memory->_address = address;
//        value_memory->_name_buyer = name;

        try
        {
            _data->insert(key(id_buyer), dynamic_cast<value*>(value_memory));
        }
        catch (const std::exception& e)
        {
            _allocator_pair->first->deallocate(value_memory);
            throw std::logic_error(e.what());
        }

        _allocator_pair->second->push_back(reinterpret_cast<value*>(value_memory));
    }

    void update_value(key& key_collection, value* value_collection) const
    {
        try
        {
            _data->update(key_collection, value_collection);
        }
        catch (const std::exception& e)
        {
            throw std::logic_error(e.what());
        }
    }

    void update_value(int id_buyer, long start_value_bytes,
                      long string_size) const
    {
        auto* value_file = static_cast<value_file_system*>(reinterpret_cast<value*>(_allocator_pair->first->allocate(
                sizeof(value_file_system), 1)));

        value_file->_start_value_bytes = start_value_bytes;
        value_file->_string_size = string_size;

        try
        {
            _data->update(key(id_buyer), dynamic_cast<value*>(value_file));
        }
        catch (const std::exception& e)
        {
            _allocator_pair->first->deallocate(value_file);
            throw std::logic_error(e.what());
        }

        _allocator_pair->second->push_back(reinterpret_cast<value*>(value_file));

    }

    void update_value(int id_buyer, int id_oder, std::string& name,
                      std::string& address, std::string& date) const
    {
        auto *value_memory = reinterpret_cast<value_in_memory_cache *>(
                _allocator_pair->first->allocate(sizeof(value_in_memory_cache), 1));

        value_memory->_id_order = id_oder;
        value_memory->_address = string_flyweight_factory::get_instance().get_string_flyweight(address)->get_value();
        value_memory->_date = string_flyweight_factory::get_instance().get_string_flyweight(date)->get_value();
        value_memory->_name_buyer = string_flyweight_factory::get_instance().get_string_flyweight(name)->get_value();

        try
        {
            _data->update(key(id_buyer), dynamic_cast<value*>(value_memory));
        }
        catch (const std::exception& e)
        {
            _allocator_pair->first->deallocate(value_memory);
            throw std::logic_error(e.what());
        }

        _allocator_pair->second->push_back(reinterpret_cast<value*>(value_memory));
    }

    void delete_value(key const &key_collection) const
    {
        try
        {
            _data->dispose(key_collection);
        }
        catch (const std::exception& e)
        {
            throw std::logic_error(e.what());
        }
    }

    void delete_value(int id_buyer) const
    {
        try
        {
            _data->dispose(key(id_buyer));

        }
        catch (const std::exception& e)
        {
            throw std::logic_error(e.what());
        }
    }

    [[nodiscard]] value* find_value(key const &key_collection) const
    {
        try
        {
            return _data->obtain(key_collection);
        }
        catch (const std::exception& e)
        {
            throw std::logic_error(e.what());
        }
    }

    [[nodiscard]] value* find_value(int id_buyer) const
    {
        try
        {
            return _data->obtain(key(id_buyer));
        }
        catch (const std::exception& e)
        {
            throw std::logic_error(e.what());
        }
    }

    [[nodiscard]] std::vector<value*> obtain_between(key min_bound, key max_bound,
                                bool is_inclusive_lower, bool is_inclusive_upper) const
    {
        try
        {
            b_tree<key, value *> *tree = reinterpret_cast<b_tree<key, value *> *>(_data);
            std::vector<associative_container<key, value *>::key_value_pair> res = tree->obtain_between(min_bound,
                                                                                                        max_bound,
                                                                                                        is_inclusive_lower,
                                                                                                        is_inclusive_upper);
            std::vector<value *> result;

            for (auto each: res)
            {
                result.push_back(each.value);
            }

            return result;
        }
        catch (const std::exception& e)
        {
            throw std::logic_error(e.what());
        }
    }


public:

    ~collection()
    {
        delete _data;
    }

    collection(collection const &other) :
            _data(new b_tree<key, value*>(*dynamic_cast<b_tree<key, value*>*>(other._data))),
            _allocator_pair(other._allocator_pair)
    {
        _t = other._t;
    }

    collection &operator=(collection const &other)
    {
        if (this != &other)
        {
            _t = other._t;

            delete this->_data;

            if (this->_allocator_pair != other._allocator_pair)
            {
                this->_allocator_pair = other._allocator_pair;
            }

            this->_data = new b_tree<key, value*>(*dynamic_cast<b_tree<key, value*>*>(other._data));;
        }

        return *this;
    }

    collection(collection &&other) noexcept
    {
        _t = other._t;
        this->_data = other._data;
        other._data = nullptr;

        this->_allocator_pair = other._allocator_pair;
        other._allocator_pair = nullptr;
    }

    collection &operator=(collection &&other) noexcept
    {
        if (this != &other)
        {
            _t = other._t;
            delete this->_data;
            this->_data = other._data;
            other._data = nullptr;

            delete this->_allocator_pair;
            this->_allocator_pair = other._allocator_pair;
            other._allocator_pair = nullptr;
        }

        return *this;
    }
};

#endif //COURSE_PROJECT_COLLECTION_H