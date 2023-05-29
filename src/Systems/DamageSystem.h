#ifndef DAMAGESYSTEM_H
#define DAMAGESYSTEM_H

#include <SDL2/SDL.h>
#include <memory>
#include "../ECS/System.h"
#include "../Events/EventBus.h"
#include "../Events/CollisionEvent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/ProjectileComponent.h"
#include "../Components/HealthComponent.h"

class DamageSystem: public System {
    public:
        DamageSystem(Registry* registry): System(registry) {
            RequireComponent<BoxColliderComponent>();
        }

        void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
            eventBus->SubscribeToEvent<CollisionEvent>(this, &DamageSystem::OnCollision);
        }

        //TODO: cpp file pls
        void OnCollision(CollisionEvent& event) {           
            if (GetRegistry()->EntityBelongToGroup(event.b, "Projectiles") && GetRegistry()->EntityHasTag(event.a, "Player")){
                OnCollisionProjectileWithPlayer(event.b, event.a);
            }

            if (GetRegistry()->EntityBelongToGroup(event.a, "Projectiles") && GetRegistry()->EntityHasTag(event.b, "Player")){
                OnCollisionProjectileWithPlayer(event.a, event.b);
            }

            if (GetRegistry()->EntityBelongToGroup(event.b, "Projectiles") && GetRegistry()->EntityBelongToGroup(event.a, "Enemies")){
               OnCollisionProjectileWithEnemies(event.b, event.a);
            }

            if (GetRegistry()->EntityBelongToGroup(event.a, "Projectiles") && GetRegistry()->EntityBelongToGroup(event.b, "Enemies")){
                OnCollisionProjectileWithEnemies(event.a, event.b);
            }
        }

        //TODO: cpp file pls
        void Update() {
            
        }

        void OnCollisionProjectileWithPlayer(Entity projectile, Entity player) {
            ProjectileComponent projectileComponent = GetRegistry()->GetComponent<ProjectileComponent>(projectile);

            if (!projectileComponent.isFriendly) {
                HealthComponent& healthComponent = GetRegistry()->GetComponent<HealthComponent>(player);
                healthComponent.currentHealth -= projectileComponent.hitDamage;

                if (healthComponent.currentHealth <= 0) {
                    GetRegistry()->KillEntity(player);
                }

                GetRegistry()->KillEntity(projectile);
            }
        }

        void OnCollisionProjectileWithEnemies(Entity projectile, Entity enemy) {
            ProjectileComponent projectileComponent = GetRegistry()->GetComponent<ProjectileComponent>(projectile);

            if (projectileComponent.isFriendly) {
                HealthComponent& healthComponent = GetRegistry()->GetComponent<HealthComponent>(enemy);
                healthComponent.currentHealth -= projectileComponent.hitDamage;

                if (healthComponent.currentHealth <= 0) {
                    GetRegistry()->KillEntity(enemy);
                }

                GetRegistry()->KillEntity(projectile);
            }
        }
};

#endif