#include "Entity.h"
#include "Registry.h"

Entity::Entity(int id, Registry* registry) {
    this->id = id;
    this->registry = registry;
} 

int Entity::GetId() const {
    return id;
} 

bool Entity::operator ==(const Entity& other) const {
    return id == other.id;
}

bool Entity::operator !=(const Entity& other) const { 
    return id != other.id; 
}

bool Entity::operator >(const Entity& other) const { 
    return id > other.id; 
}

bool Entity::operator <(const Entity& other) const { 
    return id < other.id; 
}

template <typename T, typename ...TArgs> 
void Entity::AddComponent(TArgs&& ...args) {
    registry->AddComponent<T>(*this, std::forward<TArgs>(args)...);
}

template <typename T> 
void Entity::RemoveComponent() {
    registry->RemoveComponent<T>(*this);
}

template <typename T> 
bool Entity::HasComponent() const {
    return registry->HasComponent<T>(*this);
}

template <typename T> 
T& Entity::GetComponent() const {
    return registry->GetComponent<T>(*this);
}

//TODO: look for tpp files
template void Entity::AddComponent<TransformComponent, glm::vec2, glm::vec2, double>(glm::vec2&& pos, glm::vec2&& scale, double&& rotation);
template void Entity::AddComponent<RigidBodyComponent, glm::vec2>(glm::vec2&&);
