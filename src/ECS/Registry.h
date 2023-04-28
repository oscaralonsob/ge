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

class Registry {
    private:
        int numEntities = 0;

        std::vector<IPool*> componentPools;

        std::vector<Signature> entityComponentSignatures;

        std::unordered_map<std::type_index, System*> systems;

        std::set<Entity> entitiesToBeAdded;
        std::set<Entity> entitiesToBeRemoved;


        Logger* logger; 
        //TODO: duplicated logger, static? dependency injection?

    public:
        Registry();

        Entity CreateEntity();
        //TODO: void KillEntity(Entity entity);
        void Update();

        template <typename T, typename ...TArgs> void AddComponent(Entity entity, TArgs&& ...args);
        template <typename T> void RemoveComponent(Entity entity);
        template <typename T> bool HasComponent(Entity entity) const;

        template <typename T, typename ...TArgs> void AddSystem(TArgs&& ...args);
        template <typename T> void RemoveSystem();
        template <typename T> bool HasSystem() const;
        template <typename T> T GetSystem();

        void AddEntityToSystems(Entity entity);
};

#endif