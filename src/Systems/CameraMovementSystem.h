#ifndef CAMERAMOVEMENTSYSTEM_H
#define CAMERAMOVEMENTSYSTEM_H

#include <SDL2/SDL.h>
#include "../ECS/System.h"
#include "../Components/CameraFollowComponent.h"
#include "../Components/TransformComponent.h"

class CameraMovementSystem: public System {
    public:
        CameraMovementSystem(Registry* registry): System(registry) {
            RequireComponent<CameraFollowComponent>();
            RequireComponent<TransformComponent>();
        }

        //TODO: cpp file pls
        void Update(SDL_Rect& camera) {
            for (Entity entity: GetSystemEntities()) {
                TransformComponent& transformComponent = GetRegistry()->GetComponent<TransformComponent>(entity);

                if (transformComponent.position.x + (camera.w/2) < Game::mapWidth) {
                    camera.x = transformComponent.position.x - Game::windowWidth /2;
                }

                if (transformComponent.position.y + (camera.h/2) < Game::mapHeight) {
                    camera.y = transformComponent.position.y - Game::windowHeight /2;
                }

                camera.x = camera.x < 0 ? 0 : camera.x;
                camera.y = camera.y < 0 ? 0 : camera.y;
                camera.x = camera.x > camera.w ? camera.w : camera.x;
                camera.y = camera.y > camera.h ? camera.h : camera.y;
            }
        }
};

#endif