#ifndef PROJECTILEEMITTERSYSTEM_H
#define PROJECTILEEMITTERSYSTEM_H

#include "SDL2/SDL.h"
#include <glm/glm.hpp>
#include "../ECS/System.h"
#include "../Components/TransformComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/ProjectileComponent.h"

class ProjectileEmitterSystem: public System {
    public:
        ProjectileEmitterSystem(Registry* registry): System(registry) {
            RequireComponent<TransformComponent>();
            RequireComponent<ProjectileEmitterComponent>();
        }

        //TODO: cpp file pls
        //TODO: use delta time instead of sdl ticks again?
        void Update(double deltaTime) {
            int currentTicks = SDL_GetTicks();
            for (Entity entity: GetSystemEntities()) {
                const TransformComponent transformComponent = GetRegistry()->GetComponent<TransformComponent>(entity);
                ProjectileEmitterComponent& projectileEmitterComponent = GetRegistry()->GetComponent<ProjectileEmitterComponent>(entity);

                if (currentTicks - projectileEmitterComponent.lastEmissionTime > projectileEmitterComponent.projectileFrequency) {
                    Entity projectile = GetRegistry()->CreateEntity();
                    GetRegistry()->AddComponent<TransformComponent>(projectile, transformComponent.position, glm::vec2(1.0, 1.0), 0.0);
                    GetRegistry()->AddComponent<RigidBodyComponent>(projectile, projectileEmitterComponent.projectileVelocity);
                    GetRegistry()->AddComponent<SpriteComponent>(projectile, "bullet-image", 4, glm::vec2(3.0, 3.0));
                    GetRegistry()->AddComponent<BoxColliderComponent>(projectile, glm::vec2(3, 3), glm::vec2(0, 0));
                    GetRegistry()->AddComponent<ProjectileComponent>(projectile, projectileEmitterComponent.projectileDuration, projectileEmitterComponent.hitDamage, projectileEmitterComponent.isFriendly);

                    projectileEmitterComponent.lastEmissionTime = SDL_GetTicks();
                }
            }
        }
};

#endif