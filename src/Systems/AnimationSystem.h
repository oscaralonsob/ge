#ifndef ANIMATIONSYSTEM_H
#define ANIMATIONSYSTEM_H

#include "../Components/AnimationComponent.h"
#include "../Components/SpriteComponent.h"
#include "../ECS/System.h"

class AnimationSystem : public System {
public:
    AnimationSystem(Registry* registry, std::shared_ptr<Logger> logger)
        : System(registry, logger) {
        RequireComponent<AnimationComponent>();
        RequireComponent<SpriteComponent>();
    }

    // TODO: cpp file pls
    void Update(double deltaTime) {
        for (Entity entity : GetSystemEntities()) {
            AnimationComponent& animationComponent =
                registry->GetComponent<AnimationComponent>(entity);
            SpriteComponent& spriteComponent =
                registry->GetComponent<SpriteComponent>(entity);

            animationComponent.animationFrame +=
                deltaTime * animationComponent.frameRate;
            animationComponent.currentFrame =
                (int)(animationComponent.animationFrame) %
                animationComponent.numFrames;

            spriteComponent.offset.x = animationComponent.currentFrame;
        }
    }
};

#endif