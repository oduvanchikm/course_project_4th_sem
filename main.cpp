
#include <iostream>
#include "database.h"


int main() {

    data_base *db = new data_base();

    db->add_pool("gg");


    pool pl = db->_database_entrypoint->obtain("gg");
    pl.add_scheme("aboba");
    scheme sc = pl._pool->obtain("aboba");
    sc.gg();
    sc.add_collection(std::string("lol"));
//    //sc.gg();
//   collection cl = sc._scheme->obtain("lol");
//    cl.gg();

//    pool pl1 = db->_database_entrypoint->obtain("gg2");
//    pl1.gg();
//    pool pl2 = db->_database_entrypoint->obtain("gg3");
//    pl2.gg();

    delete db;

    return 0;
}