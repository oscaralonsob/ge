#ifndef ASSETSLOADER_HPP
#define ASSETSLOADER_HPP

#include <SDL2/SDL.h>
#include <memory>

class AssetsLoader {
private:
    std::shared_ptr<class EventBus> eventBus;
    std::shared_ptr<class AssetStore> assetStore;
    std::shared_ptr<class LevelReader> levelReader;

public:
    AssetsLoader(std::shared_ptr<EventBus> eventBus,
                 std::shared_ptr<AssetStore> assetStore,
                 std::shared_ptr<LevelReader> levelReader);
    ~AssetsLoader() = default;

    void Load();
};

#endif