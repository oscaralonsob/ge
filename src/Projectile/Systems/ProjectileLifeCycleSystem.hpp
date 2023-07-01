#ifndef PROJECTILELIFECYCLESYSTEM_HPP
#define PROJECTILELIFECYCLESYSTEM_HPP

#include "../../Common/ECS/System.hpp"
#include "../Components/ProjectileComponent.hpp"

#include <SDL2/SDL.h>

class ProjectileLifeCycleSystem : public System {
public:
    ProjectileLifeCycleSystem(std::shared_ptr<Registry> registry,
                              std::shared_ptr<EventBus> eventBus,
                              std::shared_ptr<AssetStore> assetStore)
        : System(registry, eventBus, assetStore) {
        RequireComponent<ProjectileComponent>();
    }

    void Update();
};

#endif