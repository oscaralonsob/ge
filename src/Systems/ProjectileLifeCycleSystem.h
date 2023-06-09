#ifndef PROJECTILELIFECYCLESYSTEM_H
#define PROJECTILELIFECYCLESYSTEM_H

#include "../Components/ProjectileComponent.h"
#include "../ECS/System.h"

#include <SDL2/SDL.h>

class ProjectileLifeCycleSystem : public System {
public:
    ProjectileLifeCycleSystem(Registry* registry,
                              std::shared_ptr<Logger> logger)
        : System(registry, logger) {
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