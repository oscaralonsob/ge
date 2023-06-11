#ifndef CAMERAMOVEMENTSYSTEM_H
#define CAMERAMOVEMENTSYSTEM_H

#include "../Components/CameraFollowComponent.h"
#include "../Components/TransformComponent.h"
#include "../ECS/System.h"

#include <SDL2/SDL.h>

class CameraMovementSystem : public System {
public:
    CameraMovementSystem(Registry* registry, std::shared_ptr<EventBus> eventBus)
        : System(registry, eventBus) {
        RequireComponent<CameraFollowComponent>();
        RequireComponent<TransformComponent>();
    }

    // TODO: cpp file pls
    void Update(SDL_Rect& camera) {
        for (Entity entity : GetSystemEntities()) {
            TransformComponent& transformComponent =
                registry->GetComponent<TransformComponent>(entity);

            if (transformComponent.position.x + (camera.w / 2) <
                Game::mapWidth) {
                camera.x =
                    transformComponent.position.x - Game::windowWidth / 2;
            }

            if (transformComponent.position.y + (camera.h / 2) <
                Game::mapHeight) {
                camera.y =
                    transformComponent.position.y - Game::windowHeight / 2;
            }

            camera.x = camera.x < 0 ? 0 : camera.x;
            camera.y = camera.y < 0 ? 0 : camera.y;
            camera.x = camera.x > camera.w ? camera.w : camera.x;
            camera.y = camera.y > camera.h ? camera.h : camera.y;
        }
    }
};

#endif