#ifndef TARGETMOVEMENTSYSTEM_HPP
#define TARGETMOVEMENTSYSTEM_HPP

#include "../../Common/ECS/System.hpp"
#include "../../Common/Physics/Components/RigidBodyComponent.hpp"
#include "../../Common/Physics/Components/TransformComponent.hpp"
#include "../Components/TargetMovementComponent.hpp"

class TargetMovementSystem : public System {
public:
    TargetMovementSystem(std::shared_ptr<Registry> registry,
                         std::shared_ptr<EventBus> eventBus,
                         std::shared_ptr<AssetStore> assetStore)
        : System(registry, eventBus, assetStore) {
        RequireComponent<TargetMovementComponent>();
        RequireComponent<RigidBodyComponent>();
        RequireComponent<TransformComponent>();
    }

    void Update();
};

#endif