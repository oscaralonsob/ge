#include "Registry.h"

Registry::Registry(std::shared_ptr<Logger> l) {
    logger = l;
}

Entity Registry::CreateEntity() {
    int entityId = numEntities++;

    //TODO: parameter??
    Entity entity(entityId, this);

    entitiesToBeAdded.insert(entity);

    if (entityId >= static_cast<int>(entityComponentSignatures.size())) {
        entityComponentSignatures.resize(entityId + 1);
    }

    logger->Log("Entity created with id: " + std::to_string(entityId));

    return entity;
}

void Registry::Update() {
    for (Entity entity: entitiesToBeAdded) {
        AddEntityToSystems(entity);
    }
    entitiesToBeAdded.clear();

    //TODO: Remove entites from entitiesToBeRemoved
}

void Registry::AddEntityToSystems(Entity entity) {
    const int entityId = entity.GetId();

    const Signature& entityComponentSignature = entityComponentSignatures[entityId];

    for(auto& system: systems) {
        const Signature& sytemComponentSignature = system.second->GetComponentSignature();

        bool isInterested = (entityComponentSignature & sytemComponentSignature) == sytemComponentSignature;

        if (isInterested) { 
            system.second->AddEntityToSystem(entity);
        }
    }
}