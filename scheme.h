//
// Created by mkgub on 25.04.2024.
//

#ifndef COURSE_PROJECT_SCHEME_H
#define COURSE_PROJECT_SCHEME_H
#include "database.h"
#include "collection.h"
#include "include/search_tree.h"
#include "include/b_tree.h"

class scheme {

private:
    search_tree<std::string, collection> *_collection;

public:
    scheme() {
        _collection = new b_tree<std::string, collection>(3);
    }


public:
    void add_collection(std::string name_collection ) {
        _collection->insert(name_collection, std::move(collection()));
    }
};
#endif //COURSE_PROJECT_SCHEME_H
