#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "../Common/ECS/System.hpp"
#include "../Components/RigidBodyComponent.h"
#include "../Components/TransformComponent.h"

class MovementSystem : public System {
public:
    MovementSystem(Registry* registry, std::shared_ptr<EventBus> eventBus)
        : System(registry, eventBus) {
        RequireComponent<TransformComponent>();
        RequireComponent<RigidBodyComponent>();
    }

    // TODO: cpp file pls
    void Update(double deltaTime) {
        for (Entity entity : GetSystemEntities()) {
            TransformComponent& transform =
                registry->GetComponent<TransformComponent>(entity);
            const RigidBodyComponent& rigidBody =
                registry->GetComponent<RigidBodyComponent>(entity);

            transform.position.x += rigidBody.velocity.x * deltaTime;
            transform.position.y += rigidBody.velocity.y * deltaTime;
        }
    }
};

#endif