#ifndef COURSE_PROJECT_SCHEME_H
#define COURSE_PROJECT_SCHEME_H
#include "database.h"
#include "collection.h"
#include "include/associative_container.h"
#include "include/b_tree.h"
#include "comparer.h"

class scheme
{

private:

    associative_container<std::string, collection> *_scheme;
//    allocator* _allocator_data_base;

public:

    explicit scheme(allocator* allocator_data_base = nullptr) :
            _scheme(new b_tree<std::string, collection>(3, key_comparer()))
//            _allocator_data_base(allocator_data_base)
    {

    }
//
//    [[nodiscard]] allocator* get_allocator()
//    {
//        return _allocator_data_base;
//    }

public:

    void add_collection(std::string const& name_collection) const
    {
        _scheme->insert(name_collection, std::move(collection()));
    }

    void remove_collection(std::string const& name_collection) const
    {
        _scheme->dispose(name_collection);
    }

    [[nodiscard]] collection find_collection(std::string const& name_collection) const
    {
        return _scheme->obtain(name_collection);
    }


public:

    ~scheme()
    {
        delete _scheme;
    }

    scheme(scheme const &other) :
        _scheme(new b_tree<std::string, collection>(*reinterpret_cast<b_tree<std::string, collection>*>(other._scheme)))
//        _allocator_data_base(other._allocator_data_base)
    {

    }

    scheme &operator=(scheme const &other)
    {
        if (this != &other)
        {
            delete this->_scheme;

//            if (this->_allocator_data_base != other._allocator_data_base)
//            {
//                delete this->_allocator_data_base;
//                this->_allocator_data_base = other._allocator_data_base;
//            }

            this->_scheme = new b_tree<std::string, collection>(*reinterpret_cast<b_tree<std::string, collection>*>(other._scheme));
        }

        return *this;
    }

    scheme(scheme &&other) noexcept
    {
        this->_scheme = other._scheme;
        other._scheme = nullptr;
//
//        this->_allocator_data_base = other._allocator_data_base;
//        other._allocator_data_base = nullptr;
    }

    scheme &operator=(scheme &&other) noexcept
    {
        if (this != &other)
        {
            delete this->_scheme;
            this->_scheme = other._scheme;
            other._scheme = nullptr;
//
//            delete this->_allocator_data_base;
//            this->_allocator_data_base = other._allocator_data_base;
//            other._allocator_data_base = nullptr;
        }

        return *this;
    }
};
#endif //COURSE_PROJECT_SCHEME_H
