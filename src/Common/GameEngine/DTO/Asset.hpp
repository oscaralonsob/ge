#ifndef ASSET_HPP
#define ASSET_HPP

#include <string>

struct Asset {
    std::string type;
    std::string id;
    std::string path;
    int size; // TODO: CC - not all assets hace size so maybe we need different
              // assets types, let's see

    Asset(std::string type = "", std::string id = "", std::string path = "",
          int size = 8)
        : type(type), id(id), path(path), size(size) {
    }
};

#endif