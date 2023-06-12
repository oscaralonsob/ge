#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "../Common/ECS/System.hpp"
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"

#include <SDL2/SDL.h>
#include <memory>

class RenderSystem : public System {
public:
    RenderSystem(Registry* registry, std::shared_ptr<EventBus> eventBus)
        : System(registry, eventBus) {
        RequireComponent<TransformComponent>();
        RequireComponent<SpriteComponent>();
    }

    // TODO: cpp file pls
    void Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetStore,
                SDL_Rect& camera) {
        std::vector<Entity> sortedEntites = GetSystemEntities();
        std::sort(sortedEntites.begin(), sortedEntites.end(),
                  [this](const Entity entity1, const Entity entity2) -> bool {
                      return registry->GetComponent<SpriteComponent>(entity1) <
                             registry->GetComponent<SpriteComponent>(entity2);
                  });

        for (Entity entity : sortedEntites) {
            TransformComponent& transform =
                registry->GetComponent<TransformComponent>(entity);
            const SpriteComponent& sprite =
                registry->GetComponent<SpriteComponent>(entity);

            SDL_Rect srcRect = {
                static_cast<int>(sprite.offset.x * sprite.size.x),
                static_cast<int>(sprite.offset.y * sprite.size.y),
                static_cast<int>(sprite.size.x),
                static_cast<int>(sprite.size.y)};

            SDL_Rect dstRect = {
                static_cast<int>(transform.position.x -
                                 (sprite.isFixed ? 0 : camera.x)),
                static_cast<int>(transform.position.y -
                                 (sprite.isFixed ? 0 : camera.y)),
                static_cast<int>(sprite.size.x * transform.scale.x),
                static_cast<int>(sprite.size.y * transform.scale.y)};

            SDL_RenderCopyEx(renderer, assetStore->GetTexture(sprite.textureId),
                             &srcRect, &dstRect, transform.rotation, NULL,
                             SDL_FLIP_NONE);
        }
    }
};

#endif