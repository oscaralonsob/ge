#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include "../../../Components/TransformComponent.h"
#include "../../AssetStore/AssetStore.hpp"
#include "../../ECS/System.hpp"
#include "../Components/SpriteComponent.hpp"

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
                SDL_Rect& camera);
};

#endif