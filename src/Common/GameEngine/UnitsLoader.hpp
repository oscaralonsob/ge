#ifndef UNITSLOADER_HPP
#define UNITSLOADER_HPP

#include <SDL2/SDL.h>
#include <memory>

class UnitsLoader {
private:
    std::shared_ptr<class EventBus> eventBus;
    std::shared_ptr<class AssetStore> assetStore;
    std::shared_ptr<class LevelReader> levelReader;

public:
    UnitsLoader(std::shared_ptr<EventBus> eventBus,
                std::shared_ptr<AssetStore> assetStore,
                std::shared_ptr<LevelReader> levelReader);
    ~UnitsLoader() = default;

    void Load();
};

#endif