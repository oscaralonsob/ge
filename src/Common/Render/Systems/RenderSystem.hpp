#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include "../../AssetStore/AssetStore.hpp"
#include "../../ECS/System.hpp"
#include "../../Physics/Components/TransformComponent.hpp"
#include "../Components/SpriteComponent.hpp"

#include <SDL2/SDL.h>
#include <memory>

class RenderSystem : public System {
public:
    RenderSystem(std::shared_ptr<Registry> registry,
                 std::shared_ptr<EventBus> eventBus)
        : System(registry, eventBus) {
        RequireComponent<TransformComponent>();
        RequireComponent<SpriteComponent>();
    }

    // TODO: cpp file pls
    void Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetStore,
                SDL_Rect& camera);
};

#endif