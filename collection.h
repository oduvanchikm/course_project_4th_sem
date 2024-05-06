#ifndef COURSE_PROJECT_COLLECTION_H
#define COURSE_PROJECT_COLLECTION_H
#include "wb.h"
#include "include/search_tree.h"
#include "include/b_tree.h"
#include "comparer.h"

class collection
{

public:

    associative_container<key, value*> *_data;
    allocator* _allocator_data_base;

public:

    explicit collection(allocator* allocator_data_base = nullptr) :
            _data(new b_tree<key, value*>(3, key_comparer_new())),
            _allocator_data_base(allocator_data_base)
    {

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

    [[nodiscard]] const value* find_value(key const &key_collection) const
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

    [[nodiscard]] const value* find_value_between(key const &key_collection) const
    {
        // TODO write this in b tree
    }


public:

    ~collection()
    {
        delete _data;
    }

    collection(collection const &other) :
            _data(new b_tree<key, value*>(*reinterpret_cast<b_tree<key, value*>*>(other._data))),
            _allocator_data_base(other._allocator_data_base)
    {

    }

    collection &operator=(collection const &other)
    {
        if (this != &other)
        {
            delete this->_data;

            if (this->_allocator_data_base != other._allocator_data_base)
            {
                delete this->_allocator_data_base;
                this->_allocator_data_base = other._allocator_data_base;
            }

            this->_data = new b_tree<key, value*>(*reinterpret_cast<b_tree<key, value*>*>(other._data));;
        }

        return *this;
    }

    collection(collection &&other) noexcept
    {
        this->_data = other._data;
        other._data = nullptr;

        this->_allocator_data_base = other._allocator_data_base;
        other._allocator_data_base = nullptr;
    }

    collection &operator=(collection &&other) noexcept
    {
        if (this != &other)
        {
            delete this->_data;
            this->_data = other._data;
            other._data = nullptr;

            delete this->_allocator_data_base;
            this->_allocator_data_base = other._allocator_data_base;
            other._allocator_data_base = nullptr;
        }

        return *this;
    }
};

#endif //COURSE_PROJECT_COLLECTION_H
