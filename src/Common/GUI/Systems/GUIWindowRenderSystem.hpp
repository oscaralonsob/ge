#ifndef GUITEXTWINDOWRENDERSYSTEM_HPP
#define GUITEXTWINDOWRENDERSYSTEM_HPP

#include "../../AssetStore/AssetStore.hpp"
#include "../../ECS/System.hpp"
#include "../Components/GUIWindowComponent.hpp"

class GUIWindowRenderSystem : public System {
public:
    GUIWindowRenderSystem(std::shared_ptr<Registry> registry,
                          std::shared_ptr<EventBus> eventBus,
                          std::shared_ptr<AssetStore> assetStore)
        : System(registry, eventBus, assetStore) {
        RequireComponent<GUIWindowComponent>();
    }

    void Update(SDL_Renderer* renderer, const SDL_Rect& camera);
};

#endif