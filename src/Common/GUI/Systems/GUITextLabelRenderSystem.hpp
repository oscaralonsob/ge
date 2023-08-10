#ifndef GUITEXTLABELRENDERSYSTEM_HPP
#define GUITEXTLABELRENDERSYSTEM_HPP

#include "../../AssetStore/AssetStore.hpp"
#include "../../ECS/System.hpp"
#include "../Components/GUITextLabelComponent.hpp"

class GUITextLabelRenderSystem : public System {
public:
    GUITextLabelRenderSystem(std::shared_ptr<Registry> registry,
                             std::shared_ptr<EventBus> eventBus,
                             std::shared_ptr<AssetStore> assetStore)
        : System(registry, eventBus, assetStore) {
        RequireComponent<GUITextLabelComponent>();
    }

    void Update(SDL_Renderer* renderer,
                const std::shared_ptr<AssetStore> assetStore,
                const SDL_Rect& camera);
};

#endif