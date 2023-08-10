#ifndef HEALTHBARRENDERSYSTEM_HPP
#define HEALTHBARRENDERSYSTEM_HPP

#include "../../../Health/Components/HealthComponent.hpp"
#include "../../AssetStore/AssetStore.hpp"
#include "../../ECS/System.hpp"
#include "../../Physics/Components/TransformComponent.hpp"
#include "../Components/HealthBarComponent.hpp"

#include <SDL2/SDL.h>

class HealthBarRenderSystem : public System {
public:
    HealthBarRenderSystem(std::shared_ptr<Registry> registry,
                          std::shared_ptr<EventBus> eventBus,
                          std::shared_ptr<AssetStore> assetStore)
        : System(registry, eventBus, assetStore) {
        RequireComponent<TransformComponent>();
        RequireComponent<HealthComponent>();
        RequireComponent<HealthBarComponent>();
    }

    // TODO: asset store is already in system wtf
    void Update(SDL_Renderer* renderer,
                const std::shared_ptr<AssetStore> assetStore,
                const SDL_Rect& camera);
};

#endif