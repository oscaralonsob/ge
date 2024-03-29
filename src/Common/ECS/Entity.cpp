#include "Entity.hpp"

Entity::Entity(int id) : id(id) {
}

int Entity::GetId() const {
    return id;
}

bool Entity::operator==(const Entity& other) const {
    return id == other.id;
}

bool Entity::operator!=(const Entity& other) const {
    return id != other.id;
}

bool Entity::operator>(const Entity& other) const {
    return id > other.id;
}

bool Entity::operator<(const Entity& other) const {
    return id < other.id;
}