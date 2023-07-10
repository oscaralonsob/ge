#include "AssetsLoader.hpp"

#include "../AssetStore/AssetStore.hpp"
#include "Asset.hpp"
#include "LevelReader.hpp"

AssetsLoader::AssetsLoader(std::shared_ptr<EventBus> eventBus,
                           std::shared_ptr<AssetStore> assetStore,
                           SDL_Renderer* renderer) {
    this->eventBus = eventBus;
    this->assetStore = assetStore;
    this->renderer = renderer;
    this->levelReader = new LevelReader("Level1");
}

void AssetsLoader::Load() {
    std::vector<Asset> assets = levelReader->GetAssets();

    for (const Asset& asset : assets) {
        if (asset.type == "texture") {
            assetStore->AddTexture(renderer, asset.id, asset.path);
        } else if (asset.type == "font") {
            assetStore->AddFont(asset.id, asset.path, asset.size);
        }
    }
}