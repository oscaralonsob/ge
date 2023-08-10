#ifndef PROJECTILEEMITTERSYSTEM_HPP
#define PROJECTILEEMITTERSYSTEM_HPP

#include "../../Common/ECS/System.hpp"
#include "../../Common/Physics/Components/RigidBodyComponent.hpp"
#include "../../Common/Physics/Components/TransformComponent.hpp"
#include "../../Player/Events/KeyPressedEvent.hpp"
#include "../Components/ProjectileEmitterComponent.hpp"

class ProjectileEmitterSystem : public System {
public:
    ProjectileEmitterSystem(std::shared_ptr<Registry> registry,
                            std::shared_ptr<EventBus> eventBus,
                            std::shared_ptr<AssetStore> assetStore)
        : System(registry, eventBus, assetStore) {
        RequireComponent<TransformComponent>();
        RequireComponent<ProjectileEmitterComponent>();
    }

    void SubscribeToEvents();
    void OnKeyPressed(const KeyPressedEvent& event);
    void Update(const double deltaTime);
    void CreateProjectile(
        const TransformComponent transformComponent,
        const ProjectileEmitterComponent& projectileEmitterComponent,
        const RigidBodyComponent& rigidBodyComponent);
};

#endif