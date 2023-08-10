#include "System.hpp"

System::System(std::shared_ptr<Registry> registry,
               std::shared_ptr<EventBus> eventBus,
               std::shared_ptr<AssetStore> assetStore)
    : registry(registry), eventBus(eventBus), assetStore(assetStore) {
}

void System::AddEntityToSystem(Entity entity) {
    entities.push_back(entity);
}

void System::RemoveEntityFromSystem(Entity entity) {
    entities.erase(std::remove_if(entities.begin(), entities.end(),
                                  [&entity](Entity other) {
                                      return entity == other;
                                  }),
                   entities.end());
}

std::vector<Entity> System::GetSystemEntities() const {
    return entities;
}

const Signature& System::GetComponentSignature() const {
    return componentSignature;
}
