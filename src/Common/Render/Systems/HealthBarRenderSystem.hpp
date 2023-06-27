#ifndef HEALTHBARRENDERSYSTEM_HPP
#define HEALTHBARRENDERSYSTEM_HPP

#include "../../../Components/HealthComponent.h"
#include "../../AssetStore/AssetStore.hpp"
#include "../../ECS/System.hpp"
#include "../../Physics/Components/TransformComponent.hpp"
#include "../Components/HealthBarComponent.hpp"

#include <SDL2/SDL.h>

class HealthBarRenderSystem : public System {
public:
    HealthBarRenderSystem(std::shared_ptr<Registry> registry,
                          std::shared_ptr<EventBus> eventBus)
        : System(registry, eventBus) {
        RequireComponent<TransformComponent>();
        RequireComponent<HealthComponent>();
        RequireComponent<HealthBarComponent>();
    }

    // TODO: cpp file pls
    void Update(SDL_Renderer* renderer,
                const std::unique_ptr<AssetStore>& assetStore,
                SDL_Rect& camera);
};

#endif