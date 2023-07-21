#ifndef UNITCOMPONENT_HPP
#define UNITCOMPONENT_HPP

#include <limits>
#include <sol/sol.hpp>
#include <string>
#include <unordered_map>

struct UnitComponent {
    std::string type;
    std::unordered_map<std::string, std::string> values;

    UnitComponent(std::string t, sol::table table) {
        type = t;

        for (const auto& pair : table) {
            emplaceValue(pair);
        }
    }

private:
    void emplaceValue(std::pair<sol::object, sol::object> pair,
                      std::string prefix = "") {
        sol::object key = pair.first;
        sol::object value = pair.second;
        std::string index = key.as<std::string>();

        if (prefix != "") {
            index = prefix + "." + index;
        }

        if (value.get_type() == sol::type::table) {
            for (const auto& pair : value.as<sol::table>()) {
                emplaceValue(pair, index);
            }
        } else {
            values.emplace(index, value.as<std::string>());
        }
    }
};

#endif