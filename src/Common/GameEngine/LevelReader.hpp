#ifndef LEVELREADER_HPP
#define LEVELREADER_HPP

#include "Asset.hpp"

#include <limits>
#include <sol/sol.hpp>
#include <string>
#include <vector>

class LevelReader {
private:
    sol::state lua;

public:
    LevelReader(std::string file);
    ~LevelReader();

    void GetSystems();
    std::vector<Asset> GetAssets();
    void GetEntities();
};

#endif