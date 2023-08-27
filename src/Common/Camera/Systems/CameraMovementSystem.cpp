#include "CameraMovementSystem.hpp"

#include "../../ECS/Registry.hpp"

#include <SDL2/SDL.h>

void CameraMovementSystem::Update(SDL_Rect& camera, const int windowWidth,
                                  const int windowHeight) {
    for (Entity entity : GetSystemEntities()) {
        TransformComponent& transformComponent =
            registry->GetComponent<TransformComponent>(entity);

        camera.x = transformComponent.position.x - windowWidth / 2;
        camera.y = transformComponent.position.y - windowHeight / 2;
    }
}