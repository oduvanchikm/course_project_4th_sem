

#ifndef COURSE_PROJECT_POOL_H
#define COURSE_PROJECT_POOL_H
#include "database.h"
#include "scheme.h"
#include "include/search_tree.h"
#include "include/b_tree.h"

class pool {

    search_tree<std::string, scheme>* _scheme;

public:
    pool() {
        _scheme = new b_tree<std::string, scheme>(3);
    }

public:
    void add_scheme(std::string scheme_name) {

        _scheme->insert(scheme_name, std::move(scheme()));

    }

public:

    pool(pool &) = default;

    pool& operator=(pool&) {

    }
    pool(pool&&) {

    }
    pool& operator=(pool&&) {

    }

};

#endif //COURSE_PROJECT_POOL_H
