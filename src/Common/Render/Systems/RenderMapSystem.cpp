#include "RenderMapSystem.hpp"

#include "../../ECS/Registry.hpp"
#include "../../ECS/System.hpp"
#include "../../Physics/Components/TransformComponent.hpp"
#include "../Components/SpriteComponent.hpp"

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <memory>

// TODO: move with camera somehow (not follow camera but draw new parts)
void RenderMapSystem::Update(SDL_Renderer* renderer,
                             const std::shared_ptr<AssetStore> assetStore,
                             const SDL_Rect& camera) {
    for (Entity entity : GetSystemEntities()) {
        const MapComponent& mapComponent =
            registry->GetComponent<MapComponent>(entity);
        const TransformComponent& transformComponent =
            registry->GetComponent<TransformComponent>(entity);

        int currentX = transformComponent.position.x - camera.w / 2 -
                       mapComponent.tileSize.x * transformComponent.scale.x;
        int currentY = transformComponent.position.y - camera.h / 2 -
                       mapComponent.tileSize.y * transformComponent.scale.y;
        int maxX =
            camera.w / 2 + mapComponent.tileSize.x * transformComponent.scale.x;
        int maxY =
            camera.h / 2 + mapComponent.tileSize.y * transformComponent.scale.y;
        int indexX = 0;
        int indexY = 0;

        while (currentY < maxY) {
            while (currentX < maxX) {
                glm::vec2 tile =
                    mapComponent.tiles[indexX + indexY * mapComponent.width];

                SDL_Rect srcRect = {
                    static_cast<int>(tile.x * mapComponent.tileSize.x),
                    static_cast<int>(tile.y * mapComponent.tileSize.y),
                    static_cast<int>(mapComponent.tileSize.x),
                    static_cast<int>(mapComponent.tileSize.y)};
                SDL_Rect dstRect = {
                    static_cast<int>(currentX - camera.x),
                    static_cast<int>(currentY - camera.y),
                    static_cast<int>(mapComponent.tileSize.x *
                                     transformComponent.scale.x),
                    static_cast<int>(mapComponent.tileSize.y *
                                     transformComponent.scale.y)};

                SDL_RenderCopyEx(renderer,
                                 assetStore->GetTexture(mapComponent.textureId),
                                 &srcRect, &dstRect, 0.0, NULL, SDL_FLIP_NONE);

                currentX +=
                    mapComponent.tileSize.x * transformComponent.scale.x;
                indexX = indexX >= mapComponent.width ? 0 : indexX + 1;
            }
            indexX = 0;
            currentX = transformComponent.position.x - camera.w / 2 -
                       mapComponent.tileSize.x * transformComponent.scale.x;
            indexY = indexY >= mapComponent.width ? 0 : indexY + 1;
            currentY += mapComponent.tileSize.y * transformComponent.scale.y;
        }
    }
}