#ifndef LOGMOUSEPOSITIONSYSTEM_HPP
#define LOGMOUSEPOSITIONSYSTEM_HPP

#include "../../Common/ECS/System.hpp"

class LogMousePositionSystem : public System {
public:
    LogMousePositionSystem(std::shared_ptr<Registry> registry,
                           std::shared_ptr<EventBus> eventBus,
                           std::shared_ptr<AssetStore> assetStore)
        : System(registry, eventBus, assetStore) {
    }

    void Update(const SDL_Rect& camera);
};

#endif