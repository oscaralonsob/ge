#include "Entity.h"

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

Registry* Entity::GetRegistry() const {
    return registry;
}