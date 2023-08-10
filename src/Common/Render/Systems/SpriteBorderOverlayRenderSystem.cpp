#include "SpriteBorderOverlayRenderSystem.hpp"

#include "../../ECS/Registry.hpp"

void SpriteBorderOverlayRenderSystem::Update(SDL_Renderer* renderer,
                                             const SDL_Rect& camera) {
    for (auto entity : GetSystemEntities()) {
        const auto transform =
            registry->GetComponent<TransformComponent>(entity);
        const auto sprite = registry->GetComponent<SpriteComponent>(entity);
        const auto spriteBorder =
            registry->GetComponent<SpriteBorderOverlayComponent>(entity);

        // TODO: this can be something global? not calcualted every time
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        mouseX += camera.x;
        mouseY += camera.y;

        float spriteSizeX = sprite.size.x * transform.scale.x;
        float spriteSizeY = sprite.size.y * transform.scale.y;

        if (transform.position.x < mouseX &&
            transform.position.x + spriteSizeX > mouseX &&
            transform.position.y < mouseY &&
            transform.position.y + spriteSizeY > mouseY) {

            SDL_Rect colliderRect = {
                static_cast<int>(transform.position.x - camera.x),
                static_cast<int>(transform.position.y - camera.y),
                static_cast<int>(spriteSizeX), static_cast<int>(spriteSizeY)};
            SDL_SetRenderDrawColor(renderer, spriteBorder.color.r,
                                   spriteBorder.color.g, spriteBorder.color.b,
                                   255);
            SDL_RenderDrawRect(renderer, &colliderRect);
        }
    }
}