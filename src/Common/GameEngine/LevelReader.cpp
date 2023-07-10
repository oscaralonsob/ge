#include "LevelReader.hpp"

LevelReader::LevelReader(std::string file) {
    lua.open_libraries(sol::lib::base);
    std::string filePath = "./assets/config/" + file + ".lua";
    sol::load_result script = lua.load_file(filePath);

    if (!script.valid()) {
        sol::error err = script;
        std::cout << err.what();
        exit(1);
        // TODO: ffs exceptions man
    }

    lua.script_file(filePath);
}

LevelReader::~LevelReader() {
    lua_close(lua);
}

void LevelReader::GetSystems() {
}

std::vector<Asset> LevelReader::GetAssets() {
    std::vector<Asset> assets;
    sol::table level = lua["level"];
    sol::table table = level["assets"];

    sol::optional<sol::table> hasAsset = table;
    if (hasAsset == sol::nullopt) {
        return assets;
    }

    int i = 1;
    while (true) {
        sol::optional<sol::table> isValid = table[i];
        if (isValid == sol::nullopt) {
            break;
        }

        std::string type = table[i]["type"];

        std::string id = table[i]["id"];
        std::string path = table[i]["path"];
        int size = table[i]["size"] ?: 0;
        // TODO: Perf - push back is not tha efficient, but it does the work
        assets.push_back(Asset(type, id, path, size));
        i++;
    }
    return assets;
}

void LevelReader::GetEntities() {
}