#ifndef PROJECTILEEMITTERSYSTEM_H
#define PROJECTILEEMITTERSYSTEM_H

#include "../Components/BoxColliderComponent.h"
#include "../Components/ProjectileComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"
#include "../ECS/System.h"
#include "../Events/EventBus.h"
#include "../Events/KeyPressedEvent.h"
#include "SDL2/SDL.h"

#include <glm/glm.hpp>

class ProjectileEmitterSystem : public System {
public:
    ProjectileEmitterSystem(Registry* registry, std::shared_ptr<Logger> logger)
        : System(registry, logger) {
        RequireComponent<TransformComponent>();
        RequireComponent<ProjectileEmitterComponent>();
    }

    void SubscribeToEvents(std::shared_ptr<EventBus>& eventBus) {
        eventBus->SubscribeToEvent<KeyPressedEvent>(
            this, &ProjectileEmitterSystem::OnKeyPressed);
    }

    void OnKeyPressed(KeyPressedEvent& event) {
        if (event.symbol == SDLK_SPACE) {
            for (Entity entity : GetSystemEntities()) {
                if (!registry->HasComponent<CameraFollowComponent>(
                        entity)) { // TODO: group and tags
                    continue;
                }

                const TransformComponent transformComponent =
                    registry->GetComponent<TransformComponent>(entity);
                const RigidBodyComponent rigidBodyComponent =
                    registry->GetComponent<RigidBodyComponent>(entity);
                ProjectileEmitterComponent& projectileEmitterComponent =
                    registry->GetComponent<ProjectileEmitterComponent>(entity);

                CreateProjectile(transformComponent, projectileEmitterComponent,
                                 rigidBodyComponent);
            }
        }
    }

    // TODO: cpp file pls
    // TODO: use delta time instead of sdl ticks again?
    void Update(double deltaTime) {
        int currentTicks = SDL_GetTicks();
        for (Entity entity : GetSystemEntities()) {
            const TransformComponent transformComponent =
                registry->GetComponent<TransformComponent>(entity);
            const RigidBodyComponent rigidBodyComponent =
                registry->GetComponent<RigidBodyComponent>(entity);
            ProjectileEmitterComponent& projectileEmitterComponent =
                registry->GetComponent<ProjectileEmitterComponent>(entity);

            if (currentTicks - projectileEmitterComponent.lastEmissionTime >
                projectileEmitterComponent.projectileFrequency) {
                CreateProjectile(transformComponent, projectileEmitterComponent,
                                 rigidBodyComponent);
                projectileEmitterComponent.lastEmissionTime = SDL_GetTicks();
            }
        }
    }

    void
    CreateProjectile(const TransformComponent transformComponent,
                     ProjectileEmitterComponent& projectileEmitterComponent,
                     const RigidBodyComponent& rigidBodyComponent) {
        glm::vec2 projectileDirection = glm::vec2(0, 0);
        projectileDirection.x =
            (rigidBodyComponent.velocity.x > 0)
                ? projectileEmitterComponent.projectileVelocity.x
                : 0.0;
        projectileDirection.x =
            (rigidBodyComponent.velocity.x < 0)
                ? -projectileEmitterComponent.projectileVelocity.x
                : projectileDirection.x;
        projectileDirection.y =
            (rigidBodyComponent.velocity.y > 0)
                ? projectileEmitterComponent.projectileVelocity.y
                : 0.0;
        projectileDirection.y =
            (rigidBodyComponent.velocity.y < 0)
                ? -projectileEmitterComponent.projectileVelocity.y
                : projectileDirection.y;

        if (projectileDirection.x == projectileDirection.y &&
            projectileDirection.x == 0) {
            projectileDirection.x =
                projectileEmitterComponent.projectileVelocity.x;
        }

        Entity projectile = registry->CreateEntity();
        registry->AddGroupToEntity(projectile, "Projectiles");
        registry->AddComponent<TransformComponent>(
            projectile, transformComponent.position, glm::vec2(1.0, 1.0), 0.0);
        registry->AddComponent<RigidBodyComponent>(projectile,
                                                   projectileDirection);
        registry->AddComponent<SpriteComponent>(projectile, "bullet-image", 4,
                                                glm::vec2(3.0, 3.0));
        registry->AddComponent<BoxColliderComponent>(
            projectile, glm::vec2(3, 3), glm::vec2(0, 0));
        registry->AddComponent<ProjectileComponent>(
            projectile, projectileEmitterComponent.projectileDuration,
            projectileEmitterComponent.hitDamage,
            projectileEmitterComponent.isFriendly);
    }
};

#endif