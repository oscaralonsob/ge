#include "MovementSystem.hpp"

#include "../../ECS/Registry.hpp"

void MovementSystem::Update(const double deltaTime) {
    for (Entity entity : GetSystemEntities()) {
        TransformComponent& transform =
            registry->GetComponent<TransformComponent>(entity);
        const RigidBodyComponent& rigidBody =
            registry->GetComponent<RigidBodyComponent>(entity);

        transform.position.x += rigidBody.velocity.x * deltaTime;
        transform.position.y += rigidBody.velocity.y * deltaTime;
    }
}