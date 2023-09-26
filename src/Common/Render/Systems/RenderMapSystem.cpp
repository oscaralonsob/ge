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

        glm::vec2 tileSize =
            glm::vec2(mapComponent.tileSize.x * transformComponent.scale.x,
                      mapComponent.tileSize.y * transformComponent.scale.y);
        glm::vec2 numberOfTileToDraw =
            glm::vec2(camera.w / tileSize.x, camera.h / tileSize.y);
        glm::vec2 initialPosition =
            transformComponent.position * transformComponent.scale;
        glm::vec2 initialTileToDraw =
            glm::vec2((int)initialPosition.x % (int)tileSize.x,
                      (int)initialPosition.y % (int)tileSize.y);

        glm::vec2 nextPosition = initialPosition;
        glm::vec2 nextTileToDraw = initialTileToDraw;

        for (int y = 0; y < numberOfTileToDraw.y; y++) {
            for (int x = 0; x < numberOfTileToDraw.x; x++) {
                glm::vec2 tile =
                    mapComponent
                        .tiles[(int)nextTileToDraw.x % mapComponent.width +
                               ((int)nextTileToDraw.y % mapComponent.width) *
                                   mapComponent.width];

                SDL_Rect srcRect = {
                    static_cast<int>(tile.x * mapComponent.tileSize.x),
                    static_cast<int>(tile.y * mapComponent.tileSize.y),
                    static_cast<int>(mapComponent.tileSize.x),
                    static_cast<int>(mapComponent.tileSize.y)};
                SDL_Rect dstRect = {static_cast<int>(nextPosition.x - camera.x),
                                    static_cast<int>(nextPosition.y - camera.y),
                                    static_cast<int>(tileSize.x),
                                    static_cast<int>(tileSize.y)};

                SDL_RenderCopyEx(renderer,
                                 assetStore->GetTexture(mapComponent.textureId),
                                 &srcRect, &dstRect, 0.0, NULL, SDL_FLIP_NONE);

                nextTileToDraw.x++;
                nextPosition.x += tileSize.x;
            }
            nextPosition.x = initialPosition.x;
            nextTileToDraw.x = initialTileToDraw.x;
            nextTileToDraw.y++;
            nextPosition.y += tileSize.y;
        }
    }
}