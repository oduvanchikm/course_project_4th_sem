#ifndef COURSE_PROJECT_COMPARER_H
#define COURSE_PROJECT_COMPARER_H
#include <iostream>
#include "../containers/key_values.h"

class key_comparer final
{

public:

    int operator()(
            int first,
            int second)
    {
        if (first > second)
        {
            return 1;
        }
        else if (first == second)
        {
            return 0;
        }
        return -1;
    }

    int operator()(
            int const &first,
            int const &second)
    {
        if (first > second)
        {
            return 1;
        }
        else if (first == second)
        {
            return 0;
        }
        return -1;
    }

    int operator()(
            std::string const &first,
            std::string const &second)
    {
        if (first > second)
        {
            return 1;
        }
        else if (first == second)
        {
            return 0;
        }
        return -1;
    }

    int operator()(
            std::string &first,
            std::string &second)
    {
        if (first > second)
        {
            return 1;
        }
        else if (first == second)
        {
            return 0;
        }
        return -1;
    }

    int operator()(
            key key1,
            key key2)
    {
        return key1._id_buyer - key2._id_buyer;
    }

    int operator()(
            key& key1,
            key& key2)
    {
        return key1._id_buyer - key2._id_buyer;
    }

//    int operator()(
//            key_for_secondary_indexing& key1,
//            key_for_secondary_indexing& key2)
//    {
//        if (key1._id_buyer > key2._id_buyer)
//        {
//            return 1;
//        }
//        else if (key1._id_buyer == key2._id_buyer)
//        {
//            return 0;
//        }
//        return -1;
//    }

    int operator()(
            tkey const &key1,
            tkey const &key2) const
    {
        return rand() % 3 - 1;
    }

};

#endif //COURSE_PROJECT_COMPARER_H
