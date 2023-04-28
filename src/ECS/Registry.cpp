#include "Registry.h"

Registry::Registry() {
    logger = new Logger();
}

Entity Registry::CreateEntity() {
    int entityId = numEntities++;

    Entity entity(entityId);
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

template <typename T, typename ...TArgs> 
void Registry::AddComponent(Entity entity, TArgs&& ...args) {
    const int componentId = Component<T>::GetId();
    const int entityId = entity.GetId();

    if (componentId >= componentPools.size()) {
        componentPools.resize(componentId + 1, nullptr);
    }

    if (!componentPools[componentId]) {
        Pool<T>* newComponentPool = new Pool<T>();
        componentPools[componentId] = newComponentPool;
    }

    Pool<T>* componentPool = componentPools[componentId];

    if (componentId >= componentPool->GetSize()) {
        componentPool->Resize(numEntities);
    }

    T newComponent(std::forward<TArgs>(args)...);

    componentPool->Set(entityId, newComponent);

    entityComponentSignatures[entityId].set(componentId);
}

template <typename T> 
void Registry::RemoveComponent(Entity entity) {
    const int componentId = Component<T>::GetId();
    const int entityId = entity.GetId();

    entityComponentSignatures[entityId].set(componentId, false);
}

template <typename T> 
bool Registry::HasComponent(Entity entity) const {
    const int componentId = Component<T>::GetId();
    const int entityId = entity.GetId();

    return entityComponentSignatures[entityId].test(componentId);
}

template <typename T, typename ...TArgs> 
void Registry::AddSystem(TArgs&& ...args) {
    T* newSystem = new T(std::forward<TArgs>(args)...);

    systems.insert(std::make_pair(std::type_index(typeid(T)), newSystem));
}

template <typename T> 
void Registry::RemoveSystem() {
    systems.erase(systems.find(std::type_index(typeid(T))));
}

template <typename T> 
bool Registry::HasSystem() const {
    return systems.find(std::type_index(typeid(T))) != systems.end();
}

template <typename T> 
T Registry::GetSystem() {
    auto system = systems.find(std::type_index(typeid(T)));
    return *(std::static_pointer_cast<T>(system->second));
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