#ifndef MOVEMENTSYSTEM_HPP
#define MOVEMENTSYSTEM_HPP

#include "../../ECS/System.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TransformComponent.hpp"

class MovementSystem : public System {
public:
    MovementSystem(std::shared_ptr<Registry> registry,
                   std::shared_ptr<EventBus> eventBus,
                   std::shared_ptr<AssetStore> assetStore)
        : System(registry, eventBus, assetStore) {
        RequireComponent<TransformComponent>();
        RequireComponent<RigidBodyComponent>();
    }

    void Update(const double deltaTime);
};

#endif