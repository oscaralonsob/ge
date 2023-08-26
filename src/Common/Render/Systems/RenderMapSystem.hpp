#ifndef RENDERMAPSYSTEM_HPP
#define RENDERMAPSYSTEM_HPP

#include "../../AssetStore/AssetStore.hpp"
#include "../../ECS/System.hpp"
#include "../Components/MapComponent.hpp"

#include <SDL2/SDL.h>
#include <memory>

class RenderMapSystem : public System {
public:
    RenderMapSystem(std::shared_ptr<Registry> registry,
                    std::shared_ptr<EventBus> eventBus,
                    std::shared_ptr<AssetStore> assetStore)
        : System(registry, eventBus, assetStore) {
        RequireComponent<MapComponent>();
    }

    void Update(SDL_Renderer* renderer,
                const std::shared_ptr<AssetStore> assetStore,
                const SDL_Rect& camera);
};

#endif