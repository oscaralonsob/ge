#include "ProjectileEmitterSystem.hpp"

#include "../../Common/ECS/Registry.hpp"
#include "../../Common/Events/EventBus.hpp"
#include "../../Common/Physics/Components/BoxColliderComponent.hpp"
#include "../../Common/Render/Components/SpriteComponent.hpp"
#include "../../Health/Components/DamageComponent.hpp"
#include "../../Health/Components/HitPointComponent.hpp"
#include "../../Physics2D/Vec2.hpp"
#include "../Components/ProjectileComponent.hpp"

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

using namespace ge::physics2d;

void ProjectileEmitterSystem::SubscribeToEvents() {
    eventBus->SubscribeToEvent<const KeyPressedEvent>(
        this, &ProjectileEmitterSystem::OnKeyPressed);
}

void ProjectileEmitterSystem::OnKeyPressed(const KeyPressedEvent& event) {
    if (event.symbol == SDLK_SPACE) {
        for (Entity entity : GetSystemEntities()) {
            if (entity.GetId() != registry->GetEntityByTag("Player")
                                      .GetId()) { // TODO: group and tags
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

void ProjectileEmitterSystem::Update(const double deltaTime) {
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

void ProjectileEmitterSystem::CreateProjectile(
    const TransformComponent transformComponent,
    const ProjectileEmitterComponent& projectileEmitterComponent,
    const RigidBodyComponent& rigidBodyComponent) {
    std::string groupPrefix = "";
    Vec2 projectileDirection = Vec2(0, 0);

    if (projectileEmitterComponent.isFriendly) {
        groupPrefix = "Ally";
    } else {
        groupPrefix = "Enemy";
    }

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
        projectileDirection.x = projectileEmitterComponent.projectileVelocity.x;
    }

    Entity projectile = registry->CreateEntity();
    registry->AddGroupToEntity(projectile, groupPrefix + "Projectiles");
    registry->AddComponent<TransformComponent>(
        projectile, transformComponent.position, Vec2(1.0, 1.0), 0.0);
    registry->AddComponent<RigidBodyComponent>(projectile, projectileDirection);
    registry->AddComponent<SpriteComponent>(projectile, "bullet-image", 4,
                                            glm::vec2(3.0, 3.0));
    registry->AddComponent<BoxColliderComponent>(projectile, Vec2(3, 3),
                                                 Vec2(0, 0));
    registry->AddComponent<ProjectileComponent>(
        projectile, projectileEmitterComponent.projectileDuration,
        projectileEmitterComponent.hitDamage);
    registry->AddComponent<DamageComponent>(
        projectile, projectileEmitterComponent.hitDamage);
    registry->AddComponent<HitPointComponent>(projectile, 1, 1);
}