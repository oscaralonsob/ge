#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <SDL2/SDL.h>
#include <memory>
#include "../ECS/System.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"

class RenderSystem: public System {
    public:
        RenderSystem(Registry* registry): System(registry) {
            RequireComponent<TransformComponent>();
            RequireComponent<SpriteComponent>();
        }

        //TODO: cpp file pls
        void Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetStore) {
            for (Entity entity: GetSystemEntities()) {
                TransformComponent& transform = GetRegistry()->GetComponent<TransformComponent>(entity);
                const SpriteComponent& sprite = GetRegistry()->GetComponent<SpriteComponent>(entity);

                SDL_Rect srcRect = {
                    static_cast<int>(sprite.offset.x * sprite.size.x), 
                    static_cast<int>(sprite.offset.y * sprite.size.y), 
                    static_cast<int>(sprite.size.x), 
                    static_cast<int>(sprite.size.y)
                };

                SDL_Rect dstRect = {
                    static_cast<int>(transform.position.x), 
                    static_cast<int>(transform.position.y), 
                    static_cast<int>(sprite.size.x * transform.scale.x), 
                    static_cast<int>(sprite.size.y * transform.scale.y)
                };

                SDL_RenderCopyEx(
                    renderer,
                    assetStore->GetTexture(sprite.textureId),
                    &srcRect,
                    &dstRect,
                    transform.rotation,
                    NULL,
                    SDL_FLIP_NONE
                );
            }
        }
};

#endif