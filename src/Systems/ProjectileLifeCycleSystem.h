#ifndef PROJECTILELIFECYCLESYSTEM_H
#define PROJECTILELIFECYCLESYSTEM_H

#include <SDL2/SDL.h>
#include "../ECS/System.h"
#include "../Components/ProjectileComponent.h"

class ProjectileLifeCycleSystem: public System {
    public:
        ProjectileLifeCycleSystem(Registry* registry): System(registry) {
            RequireComponent<ProjectileComponent>();
        }

        //TODO: cpp file pls
        void Update() {
            for (Entity entity: GetSystemEntities()) {
                ProjectileComponent& projectileComponet = GetRegistry()->GetComponent<ProjectileComponent>(entity);

                if ((int)SDL_GetTicks() - projectileComponet.startTime > projectileComponet.projectileDuration) { 
                    GetRegistry()->KillEntity(entity);
                }
            }
        }
};

#endif