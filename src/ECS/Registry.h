#ifndef REGISTRY_H
#define REGISTRY_H

#include <vector>
#include <set>
#include <typeindex>
#include <unordered_map>
#include <memory>

#include "IPool.h"
#include "Pool.h"
#include "Entity.h"
#include "System.h"
#include "Component.h"
#include "../Logger/Logger.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/TransformComponent.h"

class Registry {
    private:
        int numEntities = 0;

        std::vector<std::shared_ptr<IPool>> componentPools;

        std::vector<Signature> entityComponentSignatures;

        std::unordered_map<std::type_index, std::shared_ptr<System>> systems;

        std::set<Entity> entitiesToBeAdded;
        std::set<Entity> entitiesToBeRemoved;

        std::shared_ptr<Logger> logger; 

    public:
       Registry(std::shared_ptr<Logger> l);
       ~Registry() = default;

        Entity CreateEntity();
        //TODO: void KillEntity(Entity entity);
        void Update();

        template <typename T, typename ...TArgs> void AddComponent(Entity entity, TArgs&& ...args);
        template <typename T> void RemoveComponent(Entity entity);
        template <typename T> bool HasComponent(Entity entity) const;
        template <typename T> T& GetComponent(Entity entity) const;

        template <typename T, typename ...TArgs> void AddSystem(TArgs&& ...args);
        template <typename T> void RemoveSystem();
        template <typename T> bool HasSystem() const;
        template <typename T> T& GetSystem() const;

        void AddEntityToSystems(Entity entity);
};

#endif