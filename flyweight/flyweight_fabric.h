#ifndef COURSE_PROJECT_FLYWEIGHT_FABRIC_H
#define COURSE_PROJECT_FLYWEIGHT_FABRIC_H
#include <unordered_map>
#include <memory>
#include "flyweight_string.h"
//todo
class string_flyweight_factory
{

private:

    string_flyweight_factory()
    {

    };

    std::unordered_map<std::string, std::shared_ptr<string_flyweight>> _string_flyweights;

public:

    static string_flyweight_factory &get_instance()
    {
        static string_flyweight_factory instance;
        return instance;
    }

    std::shared_ptr<string_flyweight> get_string_flyweight(
            const std::string &value)
    {
        std::cout << "fly fly fly " << value << std::endl;
        auto it = _string_flyweights.find(value);

        if (it != _string_flyweights.end())
        {
            return it->second;
        }
        else
        {
            auto flyweight = std::make_shared<string_flyweight>();
            flyweight->set_value(value);
            _string_flyweights[value] = flyweight;

            return flyweight;
        }
    }

    void remove_string_flyweight(const std::string &value)
    {
        auto& factory = string_flyweight_factory::get_instance();
        auto it = factory._string_flyweights.find(value);

        if (it != factory._string_flyweights.end())
        {
            factory._string_flyweights.erase(it);
            std::cout << "string flyweight with value '" << value << "' has been removed from the map." << std::endl;
        }
        else
        {
            std::cout << "string flyweight with value '" << value << "' not found in the map." << std::endl;
        }
    }
};

#endif //COURSE_PROJECT_FLYWEIGHT_FABRIC_H
