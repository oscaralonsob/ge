#include "GUIWindowRenderSystem.hpp"

#include "../../../Common/ECS/Registry.hpp"

#include <SDL2/SDL.h>
#include <memory>

void GUIWindowRenderSystem::Update(SDL_Renderer* renderer, SDL_Rect& camera) {
    for (Entity entity : GetSystemEntities()) {
        GUIWindowComponent& window =
            registry->GetComponent<GUIWindowComponent>(entity);

        SDL_Rect dstRect = {static_cast<int>(window.position.x -
                                             (window.isFixed ? 0 : camera.x)),
                            static_cast<int>(window.position.y -
                                             (window.isFixed ? 0 : camera.y)),
                            static_cast<int>(window.size.x),
                            static_cast<int>(window.size.y)};

        SDL_SetRenderDrawColor(renderer, window.color.r, window.color.g,
                               window.color.b, window.color.a);
        SDL_RenderFillRect(renderer, &dstRect);
    }
}