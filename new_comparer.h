#ifndef COURSE_PROJECT_NEW_COMPARER_H
#define COURSE_PROJECT_NEW_COMPARER_H
#include <iostream>

class second_key_comparer final
{

public:

    int operator()(
            key first,
            key second)
    {
        return  first. - second._id_person;
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

};

#endif //COURSE_PROJECT_NEW_COMPARER_H
