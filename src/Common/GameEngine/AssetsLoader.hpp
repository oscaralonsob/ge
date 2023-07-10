#ifndef ASSETSLOADER_HPP
#define ASSETSLOADER_HPP

#include <SDL2/SDL.h>
#include <memory>

class AssetsLoader {
private:
    std::shared_ptr<class EventBus> eventBus;
    std::shared_ptr<class AssetStore> assetStore;

    // TODO: Perf - this should be in assetStore, not here
    SDL_Renderer* renderer;

    // TODO: Perf - parameter
    class LevelReader* levelReader;

public:
    AssetsLoader(std::shared_ptr<EventBus> eventBus,
                 std::shared_ptr<AssetStore> assetStore,
                 SDL_Renderer* renderer);
    ~AssetsLoader() = default;

    void Load();
};

#endif