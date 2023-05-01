#include "Registry.h"

Registry::Registry(std::shared_ptr<Logger> l) {
    logger = l;
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

    if (componentId >= static_cast<int>(componentPools.size())) {
        componentPools.resize(componentId + 1, nullptr);
    }

    if (!componentPools[componentId]) {
        std::shared_ptr<Pool<T>> newComponentPool = std::make_shared<Pool<T>>();
        componentPools[componentId] = newComponentPool;
    }

    std::shared_ptr<Pool<T>> componentPool = std::static_pointer_cast<Pool<T>>(componentPools[componentId]);

    if (componentId >= componentPool->GetSize()) {
        componentPool->Resize(numEntities);
    }

    T newComponent(std::forward<TArgs>(args)...);

    componentPool->Set(entityId, newComponent);

    entityComponentSignatures[entityId].set(componentId);

    logger->Log("Component id = " + std::to_string(componentId) + " was added to entity id = " + std::to_string(entityId));
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
    std::shared_ptr<T> newSystem = std::make_shared<T>(std::forward<TArgs>(args)...);
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

//TODO: look for tpp files
template void Registry::AddComponent<TransformComponent, glm::vec2, glm::vec2, double>(Entity entity, glm::vec2&& pos, glm::vec2&& scale, double&& rotation);
template void Registry::AddComponent<RigidBodyComponent, glm::vec2>(Entity entity, glm::vec2&&);

template class Component<TransformComponent>;
template class Component<RigidBodyComponent>;

template class Pool<TransformComponent>;
template class Pool<RigidBodyComponent>;