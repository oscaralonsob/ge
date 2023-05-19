#ifndef KEYBOARDMOVEMENTSYSTEM_H
#define KEYBOARDMOVEMENTSYSTEM_H

#include <SDL2/SDL.h>
#include <memory>
#include "../ECS/System.h"
#include "../Events/EventBus.h"
#include "../Events/KeyPressedEvent.h"
#include "../Components/TransformComponent.h"

class KeyboardMovementSystem: public System {
    public:
        KeyboardMovementSystem(Registry* registry): System(registry) {
            RequireComponent<TransformComponent>();
        }

        void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
            eventBus->SubscribeToEvent<KeyPressedEvent>(this, &KeyboardMovementSystem::OnKeyPressed);
        }

        //TODO: cpp file pls
        void OnKeyPressed(KeyPressedEvent& event) {
            std::string keySymbol(1, event.symbol);
            GetRegistry()->logger->Log("KeyPressed event subscribed [" + keySymbol + "]");
        }

        //TODO: cpp file pls
        void Update() {
            
        }
};

#endif