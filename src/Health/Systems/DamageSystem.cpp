#include "DamageSystem.hpp"

#include "../../Common/ECS/Registry.hpp"
#include "../../Common/ECS/System.hpp"
#include "../../Common/Events/EventBus.hpp"
#include "../../Common/Physics/Components/BoxColliderComponent.hpp"
#include "../../Common/Physics/Events/CollisionEvent.hpp"
#include "../../Projectile/Components/ProjectileComponent.hpp"
#include "../Components/DamageComponent.hpp"
#include "../Components/HealthComponent.hpp"
#include "../Components/HitPointComponent.hpp"

#include <SDL2/SDL.h>
#include <memory>

void DamageSystem::SubscribeToEvents() {
    eventBus->SubscribeToEvent<CollisionEvent>(this,
                                               &DamageSystem::OnCollision);
}

void DamageSystem::OnCollision(CollisionEvent& event) {
    if (CheckCollision(event.a, event.b)) {
        ReduceHitPoints(event.a);
        ReduceHitPoints(event.b);
        ResolveCollision(event.a, event.b);
        ResolveCollision(event.b, event.a);
    }
}

bool DamageSystem::CheckCollision(Entity entityA, Entity entityB) {
    // TODO: group of groups
    bool collision =
        registry->EntityBelongToGroup(entityA, "EnemyProjectiles") &&
        registry->EntityBelongToGroup(entityB, "Ally");
    collision = collision ||
                (registry->EntityBelongToGroup(entityA, "Ally") &&
                 registry->EntityBelongToGroup(entityB, "EnemyProjectiles"));
    collision = collision ||
                (registry->EntityBelongToGroup(entityA, "AllyProjectiles") &&
                 registry->EntityBelongToGroup(entityB, "Enemies"));
    collision = collision ||
                (registry->EntityBelongToGroup(entityA, "Enemies") &&
                 registry->EntityBelongToGroup(entityB, "AllyProjectiles"));

    return collision;
}

void DamageSystem::ReduceHitPoints(Entity entity) {
    if (registry->HasComponent<HitPointComponent>(entity)) {
        HitPointComponent& hitPointComponent =
            registry->GetComponent<HitPointComponent>(entity);
        hitPointComponent.currentHitPoint -= 1;
        if (hitPointComponent.currentHitPoint <= 0) {
            registry->KillEntity(entity);
        }
    }
}

void DamageSystem::ResolveCollision(Entity entityA, Entity entityB) {
    if (!registry->HasComponent<DamageComponent>(entityA)) {
        return;
    }

    if (!registry->HasComponent<HealthComponent>(entityB)) {
        return;
    }

    const DamageComponent damageComponent =
        registry->GetComponent<DamageComponent>(entityA);
    HealthComponent& healthComponent =
        registry->GetComponent<HealthComponent>(entityB);
    healthComponent.currentHealth -= damageComponent.damage;
    if (healthComponent.currentHealth <= 0) {
        registry->KillEntity(entityB);
    }
}