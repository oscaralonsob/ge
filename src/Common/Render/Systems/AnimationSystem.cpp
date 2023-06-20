#include "AnimationSystem.hpp"

#include "../../ECS/Registry.hpp"
#include "../../ECS/System.hpp"
#include "../Components/AnimationComponent.hpp"
#include "../Components/SpriteComponent.hpp"

void AnimationSystem::Update(double deltaTime) {
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