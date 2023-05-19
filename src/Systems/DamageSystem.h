#ifndef DAMAGESYSTEM_H
#define DAMAGESYSTEM_H

#include <SDL2/SDL.h>
#include <memory>
#include "../ECS/System.h"
#include "../Events/EventBus.h"
#include "../Events/CollisionEvent.h"
#include "../Components/BoxColliderComponent.h"

class DamageSystem: public System {
    public:
        DamageSystem(Registry* registry): System(registry) {
            RequireComponent<BoxColliderComponent>();
        }

        void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
            eventBus->SubscribeToEvent<CollisionEvent>(this, &DamageSystem::OnCollision);
        }

        //TODO: cpp file pls
        void OnCollision(CollisionEvent& event) {
            GetRegistry()->logger->Log("Collision event subscribed with entity " + std::to_string(event.a.GetId()) + " and entity " + std::to_string(event.b.GetId()));
            GetRegistry()->KillEntity(event.a);
            GetRegistry()->KillEntity(event.b);
        }

        //TODO: cpp file pls
        void Update() {
            
        }
};

#endif