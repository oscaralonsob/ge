#include "UnitsLoader.hpp"

#include "../AssetStore/AssetStore.hpp"
#include "DTO/Unit.hpp"
#include "LevelReader.hpp"

UnitsLoader::UnitsLoader(std::shared_ptr<EventBus> eventBus,
                         std::shared_ptr<AssetStore> assetStore,
                         std::shared_ptr<LevelReader> levelReader) {
    this->eventBus = eventBus;
    this->assetStore = assetStore;
    this->levelReader = levelReader;
}

void UnitsLoader::Load() {
    std::vector<Unit> units = levelReader->GetUnits();

    for (Unit unit : units) {
        printf("%s\n", unit.name.c_str());
    }
}