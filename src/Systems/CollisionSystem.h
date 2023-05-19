#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "../ECS/System.h"
#include "../Components/TransformComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Events/CollisionEvent.h"

class CollisionSystem: public System {
    public:
        CollisionSystem(Registry* registry): System(registry) {
            RequireComponent<TransformComponent>();
            RequireComponent<BoxColliderComponent>();
        }

        //TODO: cpp file pls
        //TODO: I don't like passing this all the time, feels innecesary
        void Update(std::unique_ptr<EventBus>& eventBus) {
            std::vector<Entity> entities = GetSystemEntities();
            for (std::vector<Entity>::iterator i = entities.begin(); i != entities.end(); i++) {
                Entity aEntity = *i;
                TransformComponent& aTransformComponent = GetRegistry()->GetComponent<TransformComponent>(aEntity);
                BoxColliderComponent& aBoxColliderComponent = GetRegistry()->GetComponent<BoxColliderComponent>(aEntity);

                double aMinX = aTransformComponent.position.x + aBoxColliderComponent.offset.x;;
                double aMinY = aTransformComponent.position.y + aBoxColliderComponent.offset.y;
                double aMaxX = aMinX + aBoxColliderComponent.size.x;
                double aMaxY = aMinY + aBoxColliderComponent.size.y;

                for (std::vector<Entity>::iterator j = i + 1; j != entities.end(); j++) {
                    Entity bEntity = *j;
                    
                    TransformComponent& bOtherTransformComponent = GetRegistry()->GetComponent<TransformComponent>(bEntity);
                    BoxColliderComponent& bOtherBoxColliderComponent = GetRegistry()->GetComponent<BoxColliderComponent>(bEntity);
                    
                    double bMinX = bOtherTransformComponent.position.x + bOtherBoxColliderComponent.offset.x;;
                    double bMinY = bOtherTransformComponent.position.y + bOtherBoxColliderComponent.offset.y;
                    double bMaxX = bMinX + bOtherBoxColliderComponent.size.x;
                    double bMaxY = bMinY + bOtherBoxColliderComponent.size.y;

                    bool collisionX = (bMinX <= aMaxX && bMinX >= aMinX) || (bMaxX <= aMaxX && bMaxX >= aMinX);
                    bool collisionY = (bMinY <= aMaxY && bMinY >= aMinY) || (bMaxY <= aMaxY && bMaxY >= aMinY);

                    if (collisionX && collisionY) {
                        eventBus->EmitEvent<CollisionEvent>(aEntity, bEntity);
                    }
                }
            }
        }
};

#endif