#ifndef UNIT_HPP
#define UNIT_HPP

#include "UnitComponent.hpp"

#include <limits>
#include <sol/sol.hpp>
#include <string>

struct Unit {
    std::string name;
    std::string tag;
    std::string group;
    std::vector<UnitComponent> components;

    Unit(sol::table table) {
        name = table["name"];
        tag = table["tag"];
        group = table["group"];

        components = setUnitComponents(table["components"]);
    }

    std::vector<UnitComponent> setUnitComponents(sol::table table) {
        std::vector<UnitComponent> components;

        for (const auto& pair : table) {
            sol::object key = pair.first;
            sol::object value = pair.second;

            components.push_back(UnitComponent(key.as<std::string>(), value));
        }

        return std::vector<UnitComponent>();
    }
};

#endif