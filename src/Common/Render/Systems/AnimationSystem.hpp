#ifndef ANIMATIONSYSTEM_HPP
#define ANIMATIONSYSTEM_HPP

#include "../../ECS/System.hpp"
#include "../Components/AnimationComponent.hpp"
#include "../Components/SpriteComponent.hpp"

class AnimationSystem : public System {
public:
    AnimationSystem(Registry* registry, std::shared_ptr<EventBus> eventBus)
        : System(registry, eventBus) {
        RequireComponent<AnimationComponent>();
        RequireComponent<SpriteComponent>();
    }

    void Update(double deltaTime);
};

#endif