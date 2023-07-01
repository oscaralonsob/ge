#ifndef COLLISIONSYSTEM_HPP
#define COLLISIONSYSTEM_HPP

#include "../../ECS/System.hpp"
#include "../Components/BoxColliderComponent.hpp"
#include "../Components/TransformComponent.hpp"

class CollisionSystem : public System {
public:
    CollisionSystem(std::shared_ptr<Registry> registry,
                    std::shared_ptr<EventBus> eventBus,
                    std::shared_ptr<AssetStore> assetStore)
        : System(registry, eventBus, assetStore) {
        RequireComponent<TransformComponent>();
        RequireComponent<BoxColliderComponent>();
    }

    void Update();
};

#endif