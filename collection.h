#ifndef COURSE_PROJECT_COLLECTION_H
#define COURSE_PROJECT_COLLECTION_H
#include "wb.h"
#include "include/search_tree.h"
#include "include/b_tree.h"
#include "comparer.h"
#include "allocators/allocator_types.h"
#include "allocators/allocator.h"
#include "allocators/allocator_guardant.h"
#include "allocators/allocator_with_fit_mode.h"
#include "allocators/allocator_global_heap.h"
#include "allocators/allocator_sorted_list.h"
#include "allocators/allocator_boundary_tags.h"
#include "allocators/allocator_buddies_system.h"

class collection
{

private:

    associative_container<key, value*> *_data;
    allocator* _allocator_for_data_base;
    size_t _t;

public:

    explicit collection(allocator* allocator_for_data_base, size_t t) :
            _t(t),
            _data(new b_tree<key, value*>(t, key_comparer())),
            _allocator_for_data_base(allocator_for_data_base)

    {

    }

public:

    void add_value(key& key_collection, value* value_collection) const
    {
        _data->insert(key_collection, value_collection);
    }

    void add_value(int id_buyer, std::string& path_file, long start_value_bytes, long string_size)
    {
        auto* value_file = static_cast<value_file_system*>(reinterpret_cast<value*>(_allocator_for_data_base->allocate(
                sizeof(value_file_system), 1)));

        value_file->_path_file = path_file;
        value_file->_start_value_bytes = start_value_bytes;
        value_file->_string_size = string_size;

        _data->insert(*reinterpret_cast<key*>(id_buyer), dynamic_cast<value*>(value_file));
    }

    void add_value(int id_buyer, int id_oder, std::string& name,
                   std::string& address, std::string& date)
    {
        auto* value_memory = static_cast<value_in_memory_cash*>(reinterpret_cast<value*>(_allocator_for_data_base->allocate(
                sizeof(value_in_memory_cash), 1)));

        value_memory->_id_order = id_oder;
        value_memory->_address = address;
        value_memory->_date = date;
        value_memory->_name_buyer = name;

        _data->insert(*reinterpret_cast<key*>(id_buyer), dynamic_cast<value*>(value_memory));
    }

    void delete_value(key const &key_collection) const
    {
        _data->dispose(key_collection);

//        _allocator_for_data_base->deallocate()
    }

    const value* find_value(key const &key_collection) const
    {
        return _data->obtain(key_collection);
    }

    void update_value(key const &key_collection, value* value_collection_new) const
    {
        _data->update(key_collection, value_collection_new);
    }

//    const value* find_value_between(key const &key_collection) const
//    {
//        return _data->
//    }


public:

    ~collection()
    {
        delete _data;
    }

    collection(collection const &other) :
            _data(new b_tree<key, value*>(*dynamic_cast<b_tree<key, value*>*>(other._data))),
            _allocator_for_data_base(other._allocator_for_data_base)
    {

    }

    collection &operator=(collection const &other)
    {
        if (this != &other)
        {
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
        this->_data = other._data;
        other._data = nullptr;

        this->_allocator_for_data_base = other._allocator_for_data_base;
        other._allocator_for_data_base = nullptr;
    }

    collection &operator=(collection &&other) noexcept
    {
        if (this != &other)
        {
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
