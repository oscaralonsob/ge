#ifndef CAMERAMOVEMENTSYSTEM_HPP
#define CAMERAMOVEMENTSYSTEM_HPP

#include "../../ECS/System.hpp"
#include "../../Physics/Components/TransformComponent.hpp"
#include "../Components/CameraFollowComponent.hpp"

class CameraMovementSystem : public System {
public:
    CameraMovementSystem(std::shared_ptr<Registry> registry,
                         std::shared_ptr<EventBus> eventBus,
                         std::shared_ptr<AssetStore> assetStore)
        : System(registry, eventBus, assetStore) {
        RequireComponent<CameraFollowComponent>();
        RequireComponent<TransformComponent>();
    }

    void Update(class SDL_Rect& camera, const int mapWidth, const int mapHeight,
                const int windowWidth, const int windowHeight);
};

#endif