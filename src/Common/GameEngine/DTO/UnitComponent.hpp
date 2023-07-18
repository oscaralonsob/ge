#ifndef UNITCOMPONENT_HPP
#define UNITCOMPONENT_HPP

#include <limits>
#include <sol/sol.hpp>
#include <string>

struct UnitComponent {
    std::string type;
    std::vector<std::pair<std::string, std::string>> values;

    UnitComponent(std::string t, sol::table table) {
        type = t;

        for (const auto& pair : table) {
            sol::object key = pair.first;
            sol::object value = pair.second;

            values.push_back(
                std::pair(key.as<std::string>(), value.as<std::string>()));
        }
    }
};

#endif