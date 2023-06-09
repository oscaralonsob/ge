#include "Registry.h"

Registry::Registry(std::shared_ptr<Logger> l,
                   std::shared_ptr<EventBus> eventBus) {
    logger = l;
    this->eventBus = eventBus;
}

Entity Registry::CreateEntity() {
    int entityId;

    if (freeIds.empty()) {
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
    for (Entity entity : entitiesToBeAdded) {
        AddEntityToSystems(entity);
    }
    entitiesToBeAdded.clear();

    for (Entity entity : entitiesToBeRemoved) {
        RemoveEntityFromSystems(entity);
        entityComponentSignatures[entity.GetId()].reset();

        for (auto pool : componentPools) {
            if (pool) {
                pool->RemoveEntityFromPool(entity.GetId());
            }
        }

        freeIds.push_back(entity.GetId());

        RemoveTagFromEntity(entity);
        RemoveEntityFromGroup(entity);
    }
    entitiesToBeRemoved.clear();
}

void Registry::AddEntityToSystems(Entity entity) {
    const int entityId = entity.GetId();

    const Signature& entityComponentSignature =
        entityComponentSignatures[entityId];

    for (auto& system : systems) {
        const Signature& sytemComponentSignature =
            system.second->GetComponentSignature();

        bool isInterested =
            (entityComponentSignature & sytemComponentSignature) ==
            sytemComponentSignature;

        if (isInterested) {
            system.second->AddEntityToSystem(entity);
        }
    }
}

void Registry::RemoveEntityFromSystems(Entity entity) {
    for (auto& system : systems) {
        system.second->RemoveEntityFromSystem(entity);
    }
}

void Registry::AddTagToEntity(Entity entity, const std::string& tag) {
    entitiesPerTag.emplace(tag, entity);
    tagPerEntites.emplace(entity.GetId(), tag);
}

bool Registry::EntityHasTag(Entity entity, const std::string& tag) const {
    if (tagPerEntites.find(entity.GetId()) == tagPerEntites.end()) {
        return false;
    }

    return entitiesPerTag.find(tag)->second == entity;
}

Entity Registry::GetEntityByTag(const std::string& tag) {
    return entitiesPerTag.at(tag); // TODO: make sure exists?
}

void Registry::RemoveTagFromEntity(Entity entity) {
    auto taggedEntity = tagPerEntites.find(entity.GetId());
    if (taggedEntity != tagPerEntites.end()) {
        std::string tag = taggedEntity->second;
        entitiesPerTag.erase(tag);
        tagPerEntites.erase(taggedEntity);
    }
}

void Registry::AddGroupToEntity(Entity entity, const std::string& group) {
    entitiesPerGroup.emplace(group,
                             std::set<Entity>()); // TODO: creates a group???
    entitiesPerGroup[group].emplace(entity);
    groupPerEntites.emplace(entity.GetId(), group);
}

bool Registry::EntityBelongToGroup(Entity entity,
                                   const std::string& group) const {
    if (entitiesPerGroup.find(group) == entitiesPerGroup.end()) {
        return false;
    }

    auto setOfEntites = entitiesPerGroup.at(group);
    return setOfEntites.find(entity.GetId()) != setOfEntites.end();
}

std::vector<Entity> Registry::GetEntityByGroup(const std::string& group) {
    if (entitiesPerGroup.find(group) == entitiesPerGroup.end()) {
        return std::vector<Entity>();
    }

    std::set<Entity>& setOfEntites = entitiesPerGroup.at(group);
    return std::vector<Entity>(setOfEntites.begin(), setOfEntites.end());
}

void Registry::RemoveEntityFromGroup(Entity entity) {
    auto groupedEntity = groupPerEntites.find(entity.GetId());
    if (groupedEntity != groupPerEntites.end()) {
        auto group = entitiesPerGroup.find(groupedEntity->second);
        if (group != entitiesPerGroup.end()) {
            auto entityInGroup = group->second.find(entity);
            if (entityInGroup != group->second.end()) {
                group->second.erase(entityInGroup);
            }
        }
        groupPerEntites.erase(groupedEntity);
    }
}
