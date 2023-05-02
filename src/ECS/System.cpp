#include "System.h"
#include "Component.h"

void System::AddEntityToSystem(Entity entity) {
    entities.push_back(entity);
}

void System::RemoveEntityFromSystem(Entity entity) {
    entities.erase(std::remove_if(entities.begin(), entities.end(), [&entity](Entity other) {
        return entity == other;
    }), entities.end());
}

std::vector<Entity> System::GetSystemEntities() const {
    return entities;
}

const Signature& System::GetComponentSignature() const {
    return componentSignature;
}

template <typename T> 
void System::RequireComponent() {
    const int componentId = Component<T>::GetId();
    componentSignature.set(componentId);
}

//TODO: look for tpp files
template void System::RequireComponent<TransformComponent>();
template void System::RequireComponent<RigidBodyComponent>();
template void System::RequireComponent<SpriteComponent>();
