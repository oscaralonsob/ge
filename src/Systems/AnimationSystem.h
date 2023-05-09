#ifndef ANIMATIONSYSTEM_H
#define ANIMATIONSYSTEM_H

#include "../ECS/System.h"
#include "../Components/AnimationComponent.h"
#include "../Components/SpriteComponent.h"

class AnimationSystem: public System {
    public:
        AnimationSystem(Registry* registry): System(registry) {
            RequireComponent<AnimationComponent>();
            RequireComponent<SpriteComponent>();
        }

        //TODO: cpp file pls
        void Update(double deltaTime) {
            for (Entity entity: GetSystemEntities()) {
                AnimationComponent& animationComponent = GetRegistry()->GetComponent<AnimationComponent>(entity);
                SpriteComponent& spriteComponent = GetRegistry()->GetComponent<SpriteComponent>(entity);
                
                animationComponent.animationFrame += deltaTime * animationComponent.frameRate;
                animationComponent.currentFrame = (int)(animationComponent.animationFrame) % animationComponent.numFrames;

                spriteComponent.offset.x = animationComponent.currentFrame;
            }
        }
};

#endif