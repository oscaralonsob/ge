#include "CollisionSystem.hpp"

#include "../../ECS/Registry.hpp"
#include "../Events/CollisionEvent.hpp"

void CollisionSystem::Update(std::shared_ptr<EventBus>& eventBus) {
    std::vector<Entity> entities = GetSystemEntities();
    for (std::vector<Entity>::iterator i = entities.begin();
         i != entities.end(); i++) {
        Entity aEntity = *i;
        TransformComponent& aTransformComponent =
            registry->GetComponent<TransformComponent>(aEntity);
        BoxColliderComponent& aBoxColliderComponent =
            registry->GetComponent<BoxColliderComponent>(aEntity);

        double aMinX =
            aTransformComponent.position.x + aBoxColliderComponent.offset.x;
        ;
        double aMinY =
            aTransformComponent.position.y + aBoxColliderComponent.offset.y;
        double aMaxX = aMinX + aBoxColliderComponent.size.x;
        double aMaxY = aMinY + aBoxColliderComponent.size.y;

        for (std::vector<Entity>::iterator j = i + 1; j != entities.end();
             j++) {
            Entity bEntity = *j;

            TransformComponent& bOtherTransformComponent =
                registry->GetComponent<TransformComponent>(bEntity);
            BoxColliderComponent& bOtherBoxColliderComponent =
                registry->GetComponent<BoxColliderComponent>(bEntity);

            double bMinX = bOtherTransformComponent.position.x +
                           bOtherBoxColliderComponent.offset.x;
            ;
            double bMinY = bOtherTransformComponent.position.y +
                           bOtherBoxColliderComponent.offset.y;
            double bMaxX = bMinX + bOtherBoxColliderComponent.size.x;
            double bMaxY = bMinY + bOtherBoxColliderComponent.size.y;

            bool collisionX = (bMinX <= aMaxX && bMinX >= aMinX) ||
                              (bMaxX <= aMaxX && bMaxX >= aMinX);
            bool collisionY = (bMinY <= aMaxY && bMinY >= aMinY) ||
                              (bMaxY <= aMaxY && bMaxY >= aMinY);

            if (collisionX && collisionY) {
                eventBus->EmitEvent<CollisionEvent>(aEntity, bEntity);
            }
        }
    }
}