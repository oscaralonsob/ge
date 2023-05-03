#ifndef ENTITY_H
#define ENTITY_H

//TODO: this is not needed once we change to tpp files
#include "../Components/RigidBodyComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"

class Entity {
    private:
        int id;
        class Registry* registry;

    public:
        Entity(int id, Registry* registry);
        int GetId() const;

        bool operator ==(const Entity& other) const;
        bool operator !=(const Entity& other) const;
        bool operator <(const Entity& other) const;
        bool operator >(const Entity& other) const;

        template <typename T, typename ...TArgs> void AddComponent(TArgs&& ...args);
        template <typename T> void RemoveComponent();
        template <typename T> bool HasComponent() const;
        template <typename T> T& GetComponent() const;
};

#endif