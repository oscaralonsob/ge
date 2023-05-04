#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <SDL2/SDL.h>
#include "../ECS/System.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"

class RenderSystem: public System {
    public:
        RenderSystem() {
            RequireComponent<TransformComponent>();
            RequireComponent<SpriteComponent>();
        }

        //TODO: cpp file pls
        void Update(SDL_Renderer* renderer) {
            for (Entity entity: GetSystemEntities()) {
                TransformComponent& transform = entity.GetRegistry()->GetComponent<TransformComponent>(entity);
                const SpriteComponent& sprite = entity.GetRegistry()->GetComponent<SpriteComponent>(entity);

                SDL_Rect obj = {
                    static_cast<int>(transform.position.x), 
                    static_cast<int>(transform.position.y), 
                    static_cast<int>(sprite.size.x), 
                    static_cast<int>(sprite.size.y)
                };

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(renderer, &obj);
            }
        }
};

#endif