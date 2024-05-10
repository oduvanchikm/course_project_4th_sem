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

//size_t space_size,
//allocator *parent_allocator = nullptr,
//logger *logger = nullptr,
//allocator_with_fit_mode::fit_mode allocate_fit_mode

class collection
{

public:

    associative_container<key, value*> *_data;
//    allocator* _allocator_data_base;
//    allocator_types _type_of_allocator;


public:

    explicit collection() :
            _data(new b_tree<key, value*>(3, key_comparer()))
//            _type_of_allocator(type)
    {
//        switch (_type_of_allocator)
//        {
//            case allocator_types::GLOBAL_HEAP:
//                _allocator_data_base = new allocator_global_heap(nullptr);
//                break;

//            case allocator_types::SORTED_LIST:
//                _allocator_data_base = new allocator_sorted_list(nullptr);
//                break;
//
//            case allocator_types::BOUNDARY_TAGS:
//                _allocator_data_base = new allocator_boundary_tags(nullptr);
//                break;
//
//            case allocator_types::BUDDIE_SYSTEM:
//                _allocator_data_base = new allocator_buddies_system(nullptr);
//                break;
//        }
    }

public:

    void add_value(key& key_collection, value* value_collection) const
    {
        _data->insert(key_collection, value_collection);
    }

    void delete_value(key const &key_collection) const
    {
        _data->dispose(key_collection);
    }

    const value* find_value(key const &key_collection) const
    {
        try
        {
            const value* value_collection = _data->obtain(key_collection);
            return value_collection;
        }
        catch (std::exception const& ex)
        {
            throw std::logic_error("Can't get value");
        }
    }

    void update_value(key const &key_collection, value* value_collection_new) const
    {
        value* value_collection = _data->obtain(key_collection);
        delete value_collection;

        _data->insert(key_collection, value_collection_new);
    }

    const value* find_value_between(key const &key_collection) const
    {
        // TODO write this in b tree
    }


public:

    ~collection()
    {
        delete _data;
    }

    collection(collection const &other) :
            _data(new b_tree<key, value*>(*dynamic_cast<b_tree<key, value*>*>(other._data)))
//            _allocator_data_base(other._allocator_data_base)
    {

    }

    collection &operator=(collection const &other)
    {
        if (this != &other)
        {
            delete this->_data;

//            if (this->_allocator_data_base != other._allocator_data_base)
//            {
//                delete this->_allocator_data_base;
//                this->_allocator_data_base = other._allocator_data_base;
//            }

            this->_data = new b_tree<key, value*>(*dynamic_cast<b_tree<key, value*>*>(other._data));;
        }

        return *this;
    }

    collection(collection &&other) noexcept
    {
        this->_data = other._data;
        other._data = nullptr;

//        this->_allocator_data_base = other._allocator_data_base;
//        other._allocator_data_base = nullptr;
    }

    collection &operator=(collection &&other) noexcept
    {
        if (this != &other)
        {
            delete this->_data;
            this->_data = other._data;
            other._data = nullptr;

//            delete this->_allocator_data_base;
//            this->_allocator_data_base = other._allocator_data_base;
//            other._allocator_data_base = nullptr;
        }

        return *this;
    }
};

#endif //COURSE_PROJECT_COLLECTION_H
