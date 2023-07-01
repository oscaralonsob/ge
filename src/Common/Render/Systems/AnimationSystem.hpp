#ifndef ANIMATIONSYSTEM_HPP
#define ANIMATIONSYSTEM_HPP

#include "../../ECS/System.hpp"
#include "../Components/AnimationComponent.hpp"
#include "../Components/SpriteComponent.hpp"

class AnimationSystem : public System {
public:
    AnimationSystem(std::shared_ptr<Registry> registry,
                    std::shared_ptr<EventBus> eventBus,
                    std::shared_ptr<AssetStore> assetStore)
        : System(registry, eventBus, assetStore) {
        RequireComponent<AnimationComponent>();
        RequireComponent<SpriteComponent>();
    }

    void Update(double deltaTime);
};

#endif