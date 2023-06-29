#include "GUITextLabelRenderSystem.hpp"

#include "../../../Common/ECS/Registry.hpp"

#include <SDL2/SDL.h>
#include <memory>

void GUITextLabelRenderSystem::Update(
    SDL_Renderer* renderer, const std::shared_ptr<AssetStore> assetStore,
    SDL_Rect& camera) {
    for (Entity entity : GetSystemEntities()) {
        GUITextLabelComponent& textLabel =
            registry->GetComponent<GUITextLabelComponent>(entity);

        SDL_Surface* surface =
            TTF_RenderText_Blended(assetStore->GetFont(textLabel.assetId),
                                   textLabel.text.c_str(), textLabel.color);

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        int labelWidth = 0;
        int labelHeight = 0;

        SDL_QueryTexture(texture, NULL, NULL, &labelWidth, &labelHeight);

        SDL_Rect dstRect = {
            static_cast<int>(textLabel.position.x -
                             (textLabel.isFixed ? 0 : camera.x)),
            static_cast<int>(textLabel.position.y -
                             (textLabel.isFixed ? 0 : camera.y)),
            labelWidth, labelHeight};

        SDL_RenderCopy(renderer, texture, NULL, &dstRect);

        SDL_DestroyTexture(texture);
    }
}