#include "AssetsLoader.hpp"

#include "../AssetStore/AssetStore.hpp"
#include "DTO/Asset.hpp"
#include "LevelReader.hpp"

AssetsLoader::AssetsLoader(std::shared_ptr<EventBus> eventBus,
                           std::shared_ptr<AssetStore> assetStore,
                           std::shared_ptr<LevelReader> levelReader) {
    this->eventBus = eventBus;
    this->assetStore = assetStore;
    this->levelReader = levelReader;
}

void AssetsLoader::Load() {
    std::vector<Asset> assets = levelReader->GetAssets();

    for (Asset asset : assets) {
        if (asset.type == "texture") {
            assetStore->AddTexture(asset.id, asset.path);
        } else if (asset.type == "font") {
            assetStore->AddFont(asset.id, asset.path, asset.size);
        }
    }
}