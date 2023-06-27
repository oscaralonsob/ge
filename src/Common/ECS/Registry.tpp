template <typename T, typename... TArgs>
void Registry::AddComponent(Entity entity, TArgs&&... args) {
    const int componentId = Component<T>::GetId();
    const int entityId = entity.GetId();

    if (componentId >= static_cast<int>(componentPools.size())) {
        componentPools.resize(componentId + 1, nullptr);
    }

    if (!componentPools[componentId]) {
        std::shared_ptr<Pool<T>> newComponentPool = std::make_shared<Pool<T>>();
        componentPools[componentId] = newComponentPool;
    }

    std::shared_ptr<Pool<T>> componentPool =
        std::static_pointer_cast<Pool<T>>(componentPools[componentId]);

    T newComponent(std::forward<TArgs>(args)...);

    componentPool->Set(entityId, newComponent);

    entityComponentSignatures[entityId].set(componentId);

    eventBus->EmitEvent<LogRequestEvent>(
        "Component id = " + std::to_string(componentId) +
        " was added to entity id = " + std::to_string(entityId));
}

template <typename T>
void Registry::RemoveComponent(Entity entity) {
    const int componentId = Component<T>::GetId();
    const int entityId = entity.GetId();

    entityComponentSignatures[entityId].set(componentId, false);

    std::shared_ptr<Pool<T>> componentPool =
        std::static_pointer_cast<Pool<T>>(componentPools[componentId]);
    componentPool->Remove(entityId);
}

template <typename T>
bool Registry::HasComponent(Entity entity) const {
    const int componentId = Component<T>::GetId();
    const int entityId = entity.GetId();

    return entityComponentSignatures[entityId].test(componentId);
}

template <typename T>
T& Registry::GetComponent(Entity entity) const {
    const int componentId = Component<T>::GetId();
    const int entityId = entity.GetId();

    return std::static_pointer_cast<Pool<T>>(componentPools[componentId])
        ->Get(entityId);
}

template <typename T>
void Registry::AddSystem() {
    std::shared_ptr<T> newSystem =
        std::make_shared<T>(shared_from_this(), eventBus);
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
T& Registry::GetSystem() const {
    auto system = systems.find(std::type_index(typeid(T)));
    return *(std::static_pointer_cast<T>(system->second));
}