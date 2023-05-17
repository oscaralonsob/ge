#include "Registry.h"

Registry::Registry(std::shared_ptr<Logger> l) {
    logger = l;
}

Entity Registry::CreateEntity() {
    int entityId;

    if (freeIds.empty()){
        entityId = numEntities++;

        if (entityId >= static_cast<int>(entityComponentSignatures.size())) {
            entityComponentSignatures.resize(entityId + 1);
        }
    } else {
        entityId = freeIds.front();
        freeIds.pop_front();
    } 

    Entity entity(entityId);

    entitiesToBeAdded.insert(entity);


    logger->Log("Entity created with id: " + std::to_string(entityId));

    return entity;
}

void Registry::KillEntity(Entity entity) {
    entitiesToBeRemoved.insert(entity);
    logger->Log("Entity destroyed with id: " + std::to_string(entity.GetId()));
}

void Registry::Update() {
    for (Entity entity: entitiesToBeAdded) {
        AddEntityToSystems(entity);
    }
    entitiesToBeAdded.clear();

    for (Entity entity: entitiesToBeRemoved) {
        RemoveEntityFromSystems(entity);
        entityComponentSignatures[entity.GetId()].reset();

        freeIds.push_back(entity.GetId());
    }
    entitiesToBeRemoved.clear();
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

void Registry::RemoveEntityFromSystems(Entity entity) {
    for(auto& system: systems) {
        system.second->RemoveEntityFromSystem(entity);
    }
}