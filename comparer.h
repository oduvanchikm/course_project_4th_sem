
#ifndef COURSE_PROJECT_COMPARER_H
#define COURSE_PROJECT_COMPARER_H
#include <iostream>
class key_comparer final
{

public:

    int operator()(
            int first,
            int second)
    {
        return first - second;
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

};
#endif //COURSE_PROJECT_COMPARER_H
