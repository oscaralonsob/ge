#include "CameraMovementSystem.hpp"

#include "../../../Game/Game.h"
#include "../../ECS/Registry.hpp"

#include <SDL2/SDL.h>

void CameraMovementSystem::Update(SDL_Rect& camera, const int mapWidth,
                                  const int mapHeight, const int windowWidth,
                                  const int windowHeight) {
    for (Entity entity : GetSystemEntities()) {
        TransformComponent& transformComponent =
            registry->GetComponent<TransformComponent>(entity);

        if (transformComponent.position.x + (camera.w / 2) < mapWidth) {
            camera.x = transformComponent.position.x - windowWidth / 2;
        }

        if (transformComponent.position.y + (camera.h / 2) < mapHeight) {
            camera.y = transformComponent.position.y - windowHeight / 2;
        }

        camera.x = camera.x < 0 ? 0 : camera.x;
        camera.y = camera.y < 0 ? 0 : camera.y;
        camera.x = camera.x > camera.w ? camera.w : camera.x;
        camera.y = camera.y > camera.h ? camera.h : camera.y;
    }
}