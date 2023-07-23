#include "TargetMovementSystem.hpp"

#include "../../Common/ECS/Registry.hpp"

void TargetMovementSystem::Update() {
    for (Entity entity : GetSystemEntities()) {
        const TargetMovementComponent targetMovementComponent =
            registry->GetComponent<TargetMovementComponent>(entity);
        RigidBodyComponent& rigidBodyComponent =
            registry->GetComponent<RigidBodyComponent>(entity);
        const TransformComponent transformComponent =
            registry->GetComponent<TransformComponent>(entity);

        Entity targetEntity =
            registry->GetEntityByTag(targetMovementComponent.tag);

        const TransformComponent targetTransformComponent =
            registry->GetComponent<TransformComponent>(targetEntity);

        glm::vec2 calculatedVelocity =
            targetTransformComponent.position - transformComponent.position;

        calculatedVelocity = glm::normalize(calculatedVelocity);

        rigidBodyComponent.velocity =
            targetMovementComponent.velocity * calculatedVelocity;
    }
}