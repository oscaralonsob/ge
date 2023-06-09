#ifndef HEALTHBARRENDERSYSTEM_H
#define HEALTHBARRENDERSYSTEM_H

#include "../Components/HealthBarComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/TransformComponent.h"
#include "../ECS/System.h"

#include <SDL2/SDL.h>

class HealthBarRenderSystem : public System {
public:
    HealthBarRenderSystem(Registry* registry, std::shared_ptr<Logger> logger,
                          std::shared_ptr<EventBus> eventBus)
        : System(registry, logger, eventBus) {
        RequireComponent<TransformComponent>();
        RequireComponent<HealthComponent>();
        RequireComponent<HealthBarComponent>();
    }

    // TODO: cpp file pls
    void Update(SDL_Renderer* renderer,
                const std::unique_ptr<AssetStore>& assetStore,
                SDL_Rect& camera) {
        for (Entity entity : GetSystemEntities()) {
            TransformComponent& transform =
                registry->GetComponent<TransformComponent>(entity);
            HealthComponent health =
                registry->GetComponent<HealthComponent>(entity);
            HealthBarComponent& healthBar =
                registry->GetComponent<HealthBarComponent>(entity);

            SDL_Color color = {0, 255, 0};
            std::string healthStr = std::to_string(health.currentHealth);
            double healthPerc = health.currentHealth * 100 / health.maxHealth;

            switch (static_cast<int>(healthPerc)) {
            case 0 ... 24:
                color = {255, 0, 0};
                break;
            case 25 ... 49:
                color = {255, 140, 0};
            }

            SDL_Surface* surface =
                TTF_RenderText_Blended(assetStore->GetFont(healthBar.assetId),
                                       healthStr.c_str(), color);
            SDL_Texture* texture =
                SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);

            int labelWidth = 0;
            int labelHeight = 0;

            SDL_QueryTexture(texture, NULL, NULL, &labelWidth, &labelHeight);

            SDL_Rect dstRect = {
                static_cast<int>(transform.position.x - camera.x),
                static_cast<int>(transform.position.y - camera.y - 25),
                labelWidth, labelHeight};

            SDL_RenderCopy(renderer, texture, NULL, &dstRect);

            SDL_Rect healthBarRect = {
                static_cast<int>(transform.position.x - camera.x),
                static_cast<int>(transform.position.y - camera.y - 10),
                static_cast<int>(20 * healthPerc / 100), static_cast<int>(3)};

            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
            SDL_RenderFillRect(renderer, &healthBarRect);

            SDL_DestroyTexture(texture);
        }
    }
};

#endif