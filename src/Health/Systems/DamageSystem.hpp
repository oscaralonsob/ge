#ifndef DAMAGESYSTEM_H
#define DAMAGESYSTEM_H

#include "../../Common/ECS/System.hpp"
#include "../../Common/Events/EventBus.hpp"
#include "../../Common/Physics/Events/CollisionEvent.hpp"

#include <memory>

// TODO: create HealthComponent (with health or hit points or maybe other (like
// 1,2,3)) and also create damageComponent to divide the damage from the
// projectile that only moves and kills the component
class DamageSystem : public System {
public:
    DamageSystem(std::shared_ptr<Registry> registry,
                 std::shared_ptr<EventBus> eventBus,
                 std::shared_ptr<AssetStore> assetStore)
        : System(registry, eventBus, assetStore) {
    }

    void SubscribeToEvents();

private:
    void OnCollision(CollisionEvent& event);
    bool CheckCollision(Entity entityA, Entity entityB);
    void ResolveCollision(Entity entityA, Entity entityB);
    void ReduceHitPoints(Entity entity);
};

#endif