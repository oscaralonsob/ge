#ifndef UNIT_HPP
#define UNIT_HPP

#include <limits>
#include <sol/sol.hpp>
#include <string>

struct Unit {
    std::string name;

    Unit(sol::table table) {
        name = table["name"];
    }
};

#endif