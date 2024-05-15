#ifndef COURSE_PROJECT_COLLECTION_H
#define COURSE_PROJECT_COLLECTION_H
#include "../parse/wb.h"
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

class collection
{

private:

    associative_container<key, value*> *_data;
    allocator* _allocator_for_data_base;
    allocator_with_fit_mode::fit_mode _fit_mode;
    size_t _t;
    allocator_types _type;

public:

    explicit collection(allocator* allocator_for_data_base, size_t t, allocator_with_fit_mode::fit_mode fit_mode, allocator_types type) :
            _t(t),
            _fit_mode(fit_mode),
            _type(type),
            _allocator_for_data_base(allocator_for_data_base),
            _data(new b_tree<key, value*>(t, key_comparer(), allocator_for_data_base))
    {

    }

public:

    void add_value(key& key_collection, value* value_collection) const
    {
        _data->insert(key_collection, value_collection);
    }

    void add_value(int id_buyer, value* value)
    {
        _data->insert(key(id_buyer), value);
    }

    void add_value(int id_buyer, std::string& path_file, long start_value_bytes, long string_size)
    {
        value_file_system *value_file = reinterpret_cast<value_file_system *>(reinterpret_cast<value *>(_allocator_for_data_base
                    ->allocate(sizeof(value_file_system), 1)));

        std::cout << "hello debil" << std::endl;

        value_file->_start_value_bytes = start_value_bytes;
        value_file->_string_size = string_size;

        _data->insert(key(id_buyer), dynamic_cast<value *>(value_file));
    }

    void add_value(int id_buyer, std::string& name, std::string& date,
                   std::string& address, int id_oder)
    {
        value_in_memory_cash *value_memory = reinterpret_cast<value_in_memory_cash *>(
                _allocator_for_data_base->allocate(sizeof(value_in_memory_cash), 1));

        value_memory->_id_order = id_oder;
        value_memory->_address = address;
        value_memory->_date = date;
        value_memory->_name_buyer = name;

        _data->insert(key(id_buyer), dynamic_cast<value*>(value_memory));
    }

    void update_value(key& key_collection, value* value_collection) const
    {
        _data->update(key_collection, value_collection);
    }

    void update_value(int id_buyer, std::string& path_file, long start_value_bytes,
                      long string_size) const
    {
        auto* value_file = static_cast<value_file_system*>(reinterpret_cast<value*>(_allocator_for_data_base->allocate(
                sizeof(value_file_system), 1)));

        value_file->_start_value_bytes = start_value_bytes;
        value_file->_string_size = string_size;

        _data->update(key(id_buyer), dynamic_cast<value*>(value_file));
    }

    void update_value(int id_buyer, int id_oder, std::string& name,
                      std::string& address, std::string& date) const
    {
        value_in_memory_cash *value_memory = reinterpret_cast<value_in_memory_cash *>(
                _allocator_for_data_base->allocate(sizeof(value_in_memory_cash), 1));

        value_memory->_id_order = id_oder;
        value_memory->_address = address;
        value_memory->_date = date;
        value_memory->_name_buyer = name;

        _data->update(key(id_buyer), dynamic_cast<value*>(value_memory));
    }

    void delete_value(key const &key_collection) const
    {
        _data->dispose(key_collection);
    }

    void delete_value(int id_buyer) const
    {
        _data->dispose(key(id_buyer));
    }

    value* find_value(key const &key_collection) const
    {
        return _data->obtain(key_collection);
    }

    value* find_value(int id_buyer) const
    {

        return _data->obtain(key(id_buyer));
    }

//    const value* find_value_between(key const &key_collection) const
//    {
//        return _data->
//    }


public:

    ~collection()
    {
//        delete _data;
    }

    collection(collection const &other) :
            _data(new b_tree<key, value*>(*dynamic_cast<b_tree<key, value*>*>(other._data))),
            _allocator_for_data_base(other._allocator_for_data_base)
    {
        _t = other._t;
    }

    collection &operator=(collection const &other)
    {
        if (this != &other)
        {
            _t = other._t;

            delete this->_data;

            if (this->_allocator_for_data_base != other._allocator_for_data_base)
            {
                delete this->_allocator_for_data_base;
                this->_allocator_for_data_base = other._allocator_for_data_base;
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

        this->_allocator_for_data_base = other._allocator_for_data_base;
        other._allocator_for_data_base = nullptr;
    }

    collection &operator=(collection &&other) noexcept
    {
        if (this != &other)
        {
            _t = other._t;
            delete this->_data;
            this->_data = other._data;
            other._data = nullptr;

            delete this->_allocator_for_data_base;
            this->_allocator_for_data_base = other._allocator_for_data_base;
            other._allocator_for_data_base = nullptr;
        }

        return *this;
    }
};

#endif //COURSE_PROJECT_COLLECTION_H