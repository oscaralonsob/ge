#include "RenderMapSystem.hpp"

#include "../../ECS/Registry.hpp"
#include "../../ECS/System.hpp"
#include "../../Physics/Components/TransformComponent.hpp"
#include "../Components/SpriteComponent.hpp"

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <memory>

void RenderMapSystem::Update(SDL_Renderer* renderer,
                             const std::shared_ptr<AssetStore> assetStore,
                             const SDL_Rect& camera) {
    for (Entity entity : GetSystemEntities()) {
        MapComponent& mapComponent =
            registry->GetComponent<MapComponent>(entity);

        int x = 0;
        int y = 0;
        for (glm::vec2 tile : mapComponent.tiles) {
            SDL_Rect srcRect = {
                static_cast<int>(tile.x * mapComponent.tileSize.x),
                static_cast<int>(tile.y * mapComponent.tileSize.y),
                static_cast<int>(mapComponent.tileSize.x),
                static_cast<int>(mapComponent.tileSize.y)};
            SDL_Rect dstRect = {
                static_cast<int>(x * mapComponent.tileSize.x * 3 - camera.x),
                static_cast<int>(y * mapComponent.tileSize.y * 3 - camera.y),
                static_cast<int>(mapComponent.tileSize.x * 3),
                static_cast<int>(mapComponent.tileSize.y * 3)};

            SDL_RenderCopyEx(renderer,
                             assetStore->GetTexture(mapComponent.textureId),
                             &srcRect, &dstRect, 0.0, NULL, SDL_FLIP_NONE);
            x++;
            if (x >= mapComponent.width) {
                x = 0;
                y++;
            }
        }
    }
}