#ifndef KEYBOARDMOVEMENTSYSTEM_H
#define KEYBOARDMOVEMENTSYSTEM_H

#include <SDL2/SDL.h>
#include <memory>
#include "../ECS/System.h"
#include "../Events/EventBus.h"
#include "../Events/KeyPressedEvent.h"
#include "../Components/KeyboardControllerComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/RigidBodyComponent.h"

class KeyboardMovementSystem: public System {
    public:
        KeyboardMovementSystem(Registry* registry, std::shared_ptr<Logger> logger): System(registry, logger) {
            RequireComponent<KeyboardControllerComponent>();
            RequireComponent<SpriteComponent>();
            RequireComponent<RigidBodyComponent>();
        }

        void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
            eventBus->SubscribeToEvent<KeyPressedEvent>(this, &KeyboardMovementSystem::OnKeyPressed);
        }

        //TODO: cpp file pls
        void OnKeyPressed(KeyPressedEvent& event) {
            if (event.symbol != SDLK_UP && event.symbol != SDLK_RIGHT && event.symbol != SDLK_DOWN && event.symbol != SDLK_LEFT) {
                return;
            }

            std::string keySymbol(1, event.symbol);
            for (Entity entity: GetSystemEntities()) {
                const KeyboardControllerComponent keyboardControllerComponent = registry->GetComponent<KeyboardControllerComponent>(entity);
                SpriteComponent& spriteComponent = registry->GetComponent<SpriteComponent>(entity);
                RigidBodyComponent& rigidBodyComponent = registry->GetComponent<RigidBodyComponent>(entity);

                switch (event.symbol){
                    case SDLK_UP:
                        rigidBodyComponent.velocity = keyboardControllerComponent.upVelocity;
                        spriteComponent.offset = glm::vec2(0.0, 0.0);
                        break;
                    case SDLK_RIGHT:
                        rigidBodyComponent.velocity = keyboardControllerComponent.rightVelocity;
                        spriteComponent.offset = glm::vec2(0.0, 1.0);
                        break;
                    case SDLK_DOWN:
                        rigidBodyComponent.velocity = keyboardControllerComponent.downVelocity;
                        spriteComponent.offset = glm::vec2(0.0, 2.0);
                        break;
                    case SDLK_LEFT:
                        rigidBodyComponent.velocity = keyboardControllerComponent.leftVelocity;
                        spriteComponent.offset = glm::vec2(0.0, 3.0);
                        break;
                    default:
                        break;
                }
            }
        }

        //TODO: cpp file pls
        void Update() {
            
        }
};

#endif