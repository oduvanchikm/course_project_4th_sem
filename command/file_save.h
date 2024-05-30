#ifndef COURSE_PROJECT_FILE_SAVE_H
#define COURSE_PROJECT_FILE_SAVE_H
#include <iostream>
#include <fstream>
#include "../logger/logger_singleton.h"

class file_save
{

private:

    std::string _file_name;

public:

    file_save() = default;
    ~file_save() = default;

public:

    file_save(file_save const& other) = delete;

    file_save(file_save const&& other) = delete;

    file_save& operator=(file_save const& other) = delete;

    file_save& operator=(file_save const&& other) = delete;

public:

    void file_for_save(std::string const& request)
    {
        logger_singleton::get_instance()->get_logger()->trace("hello");
        _file_name = "file_save.txt";

        std::cout << _file_name << std::endl;

        std::ofstream file_save(_file_name, std::ios::app);

        if (!file_save.is_open())
        {
            logger_singleton::get_instance()->get_logger()->error("error with opening file for saving data");
        }

        file_save << request << std::endl;
        file_save.close();
    }

    void clean_file()
    {
        std::ofstream ofs;
        ofs.open(_file_name, std::ofstream::out | std::ofstream::trunc);
        ofs.close();
    }
};

#endif //COURSE_PROJECT_FILE_SAVE_H
