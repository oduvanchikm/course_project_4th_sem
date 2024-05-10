#include <iostream>
#include "database.h"
#include "input_file_parse.h"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "error with number of arguments" << std::endl;
        return 1;
    }

    data_base *db = new data_base();

    logger_builder* builder = new client_logger_builder();

    logger *constructed_logger = builder
            ->add_console_stream(logger::severity::information)
            ->add_console_stream(logger::severity::debug)
            ->add_console_stream(logger::severity::error)
            ->build();

    std::ifstream input_file(argv[1]);

    if (!input_file.is_open())
    {
        std::cerr << "error with opening file" << std::endl;
        return 0;
    }

    std::cout << "uch" << std::endl;

    input_file_parse parse;



    parse.parse_input_file(input_file, db);

    std::cout << "hhh" << std::endl;




//    db->add_pool("gg");
//
//    pool pl = db->_database_entrypoint->obtain("gg");
//    pl.add_scheme("aboba");
//    scheme sc = pl._pool->obtain("aboba");
//    sc.gg();
//    sc.add_collection(std::string("lol"));
//    sc.gg();
//    collection cl = sc._scheme->obtain("lol");
//    cl.gg();

//    pool pl1 = db->_database_entrypoint->obtain("gg2");
//    pl1.gg();
//    pool pl2 = db->_database_entrypoint->obtain("gg3");
//    pl2.gg();

    delete db;

    return 0;
}