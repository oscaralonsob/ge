#include "ProjectileLifeCycleSystem.hpp"

#include "../../Common/ECS/Registry.hpp"

#include <SDL2/SDL.h>

void ProjectileLifeCycleSystem::Update() {
    for (Entity entity : GetSystemEntities()) {
        ProjectileComponent& projectileComponet =
            registry->GetComponent<ProjectileComponent>(entity);

        if ((int)SDL_GetTicks() - projectileComponet.startTime >
            projectileComponet.projectileDuration) {
            registry->KillEntity(entity);
        }
    }
}