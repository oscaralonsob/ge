#ifndef GUITEXTWINDOWRENDERSYSTEM_HPP
#define GUITEXTWINDOWRENDERSYSTEM_HPP

#include "../../AssetStore/AssetStore.hpp"
#include "../../ECS/System.hpp"
#include "../Components/GUIWindowComponent.hpp"

class GUIWindowRenderSystem : public System {
public:
    GUIWindowRenderSystem(Registry* registry,
                          std::shared_ptr<EventBus> eventBus)
        : System(registry, eventBus) {
        RequireComponent<GUIWindowComponent>();
    }

    void Update(SDL_Renderer* renderer, SDL_Rect& camera);
};

#endif