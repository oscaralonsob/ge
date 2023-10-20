#include "TargetMovementSystem.hpp"

#include "../../Common/ECS/Registry.hpp"
#include "../../Physics2D/Vec2.hpp"

using namespace ge::physics2d;

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

        Vec2 calculatedVelocity =
            targetTransformComponent.position - transformComponent.position;

        calculatedVelocity = calculatedVelocity.Normalize();

        rigidBodyComponent.velocity =
            calculatedVelocity * targetMovementComponent.velocity;
    }
}