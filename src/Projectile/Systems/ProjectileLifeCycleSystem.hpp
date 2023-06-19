#ifndef PROJECTILELIFECYCLESYSTEM_HPP
#define PROJECTILELIFECYCLESYSTEM_HPP

#include "../../Common/ECS/System.hpp"
#include "../Components/ProjectileComponent.hpp"

#include <SDL2/SDL.h>

class ProjectileLifeCycleSystem : public System {
public:
    ProjectileLifeCycleSystem(Registry* registry,
                              std::shared_ptr<EventBus> eventBus)
        : System(registry, eventBus) {
        RequireComponent<ProjectileComponent>();
    }

    void Update();
};

#endif