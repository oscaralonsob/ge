#ifndef DAMAGESYSTEM_H
#define DAMAGESYSTEM_H

#include "../Common/ECS/System.hpp"
#include "../Common/Physics/Components/BoxColliderComponent.hpp"
#include "../Common/Physics/Events/CollisionEvent.hpp"
#include "../Components/HealthComponent.h"
#include "../Events/EventBus.h"
#include "../Projectile/Components/ProjectileComponent.hpp"

#include <SDL2/SDL.h>
#include <memory>

class DamageSystem : public System {
public:
    DamageSystem(Registry* registry, std::shared_ptr<EventBus> eventBus)
        : System(registry, eventBus) {
        RequireComponent<BoxColliderComponent>();
    }

    void SubscribeToEvents() {
        eventBus->SubscribeToEvent<CollisionEvent>(this,
                                                   &DamageSystem::OnCollision);
    }

    // TODO: cpp file pls
    void OnCollision(CollisionEvent& event) {
        if (registry->EntityBelongToGroup(event.b, "Projectiles") &&
            registry->EntityHasTag(event.a, "Player")) {
            OnCollisionProjectileWithPlayer(event.b, event.a);
        }

        if (registry->EntityBelongToGroup(event.a, "Projectiles") &&
            registry->EntityHasTag(event.b, "Player")) {
            OnCollisionProjectileWithPlayer(event.a, event.b);
        }

        if (registry->EntityBelongToGroup(event.b, "Projectiles") &&
            registry->EntityBelongToGroup(event.a, "Enemies")) {
            OnCollisionProjectileWithEnemies(event.b, event.a);
        }

        if (registry->EntityBelongToGroup(event.a, "Projectiles") &&
            registry->EntityBelongToGroup(event.b, "Enemies")) {
            OnCollisionProjectileWithEnemies(event.a, event.b);
        }
    }

    // TODO: cpp file pls
    void Update() {
    }

    void OnCollisionProjectileWithPlayer(Entity projectile, Entity player) {
        ProjectileComponent projectileComponent =
            registry->GetComponent<ProjectileComponent>(projectile);

        if (!projectileComponent.isFriendly) {
            HealthComponent& healthComponent =
                registry->GetComponent<HealthComponent>(player);
            healthComponent.currentHealth -= projectileComponent.hitDamage;

            if (healthComponent.currentHealth <= 0) {
                registry->KillEntity(player);
            }

            registry->KillEntity(projectile);
        }
    }

    void OnCollisionProjectileWithEnemies(Entity projectile, Entity enemy) {
        ProjectileComponent projectileComponent =
            registry->GetComponent<ProjectileComponent>(projectile);

        if (projectileComponent.isFriendly) {
            HealthComponent& healthComponent =
                registry->GetComponent<HealthComponent>(enemy);
            healthComponent.currentHealth -= projectileComponent.hitDamage;

            if (healthComponent.currentHealth <= 0) {
                registry->KillEntity(enemy);
            }

            registry->KillEntity(projectile);
        }
    }
};

#endif