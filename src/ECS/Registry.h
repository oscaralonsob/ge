#ifndef REGISTRY_H
#define REGISTRY_H

#include "../Common/ECS/Component.hpp"
#include "../Common/ECS/Entity.hpp"
#include "../Common/ECS/IPool.hpp"
#include "../Common/ECS/Pool.hpp"
#include "../Common/ECS/System.hpp"
#include "../Debug/Events/LogRequestEvent.hpp"
#include "../Events/EventBus.h"

#include <deque>
#include <memory>
#include <set>
#include <typeindex>
#include <unordered_map>
#include <vector>

class Registry {
private:
    int numEntities = 0;

    std::vector<std::shared_ptr<IPool>> componentPools;

    std::vector<Signature> entityComponentSignatures;

    std::unordered_map<std::type_index, std::shared_ptr<System>> systems;

    std::set<Entity> entitiesToBeAdded;
    std::set<Entity> entitiesToBeRemoved;

    std::unordered_map<std::string, Entity> entitiesPerTag;
    std::unordered_map<int, std::string> tagPerEntites;

    std::unordered_map<std::string, std::set<Entity>> entitiesPerGroup;
    std::unordered_map<int, std::string> groupPerEntites;

    std::deque<int> freeIds;

    std::shared_ptr<EventBus> eventBus;

public:
    Registry(std::shared_ptr<EventBus> eventBus);
    ~Registry() = default;

    Entity CreateEntity();
    void KillEntity(Entity entity);

    void Update();

    template <typename T, typename... TArgs>
    void AddComponent(Entity entity, TArgs&&... args);
    template <typename T>
    void RemoveComponent(Entity entity);
    template <typename T>
    bool HasComponent(Entity entity) const;
    template <typename T>
    T& GetComponent(Entity entity) const;

    template <typename T, typename... TArgs>
    void AddSystem(TArgs&&... args);
    template <typename T>
    void RemoveSystem();
    template <typename T>
    bool HasSystem() const;
    template <typename T>
    T& GetSystem() const;

    void AddEntityToSystems(Entity entity);
    void RemoveEntityFromSystems(Entity entity);

    void AddTagToEntity(Entity entity, const std::string& tag);
    bool EntityHasTag(Entity entity, const std::string& tag) const;
    Entity GetEntityByTag(const std::string& tag);
    void RemoveTagFromEntity(Entity entity);

    void AddGroupToEntity(Entity entity, const std::string& group);
    bool EntityBelongToGroup(Entity entity, const std::string& group) const;
    std::vector<Entity> GetEntityByGroup(const std::string& group);
    void RemoveEntityFromGroup(Entity entity);
};

#include "Registry.tpp"

#endif