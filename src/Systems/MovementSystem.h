#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "../ECS/System.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"

class MovementSystem: public System {
    public:
        MovementSystem() {
            RequireComponent<TransformComponent>();
            RequireComponent<RigidBodyComponent>();
        }

        //TODO: cpp file pls
        void Update(double deltaTime) {
            for (Entity entity: GetSystemEntities()) {
                TransformComponent& transform = entity.GetComponent<TransformComponent>();
                const RigidBodyComponent& rigidBody = entity.GetComponent<RigidBodyComponent>();

                transform.position.x += rigidBody.velocity.x * deltaTime;
                transform.position.y += rigidBody.velocity.y * deltaTime;
            }
        }
};

#endif