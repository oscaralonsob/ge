#ifndef PROJECTILELIFECYCLESYSTEM_H
#define PROJECTILELIFECYCLESYSTEM_H

#include "../Common/ECS/System.hpp"
#include "../Components/ProjectileComponent.h"

#include <SDL2/SDL.h>

class ProjectileLifeCycleSystem : public System {
public:
    ProjectileLifeCycleSystem(Registry* registry,
                              std::shared_ptr<EventBus> eventBus)
        : System(registry, eventBus) {
        RequireComponent<ProjectileComponent>();
    }

    // TODO: cpp file pls
    void Update() {
        for (Entity entity : GetSystemEntities()) {
            ProjectileComponent& projectileComponet =
                registry->GetComponent<ProjectileComponent>(entity);

            if ((int)SDL_GetTicks() - projectileComponet.startTime >
                projectileComponet.projectileDuration) {
                registry->KillEntity(entity);
            }
        }
    }
};

#endif