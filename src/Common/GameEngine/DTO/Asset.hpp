#ifndef ASSET_HPP
#define ASSET_HPP

#include <limits>
#include <sol/sol.hpp>
#include <string>

struct Asset {
    std::string type;
    std::string id;
    std::string path;
    int size; // TODO: CC - not all assets hace size so maybe we need different
              // assets types, let's see

    Asset(sol::table table) {
        type = table["type"];
        id = table["id"];
        path = table["path"];
        size = table["size"] ?: 0;
    }
};

#endif