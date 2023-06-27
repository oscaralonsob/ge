#ifndef BOXBORDEROVERLAYCOMPONENTRENDERSYSTEM_HPP
#define BOXBORDEROVERLAYCOMPONENTRENDERSYSTEM_HPP

#include "../../../Common/ECS/System.hpp"
#include "../../Physics/Components/TransformComponent.hpp"
#include "../Components/SpriteBorderOverlayComponent.hpp"
#include "../Components/SpriteComponent.hpp"

#include <SDL2/SDL.h>
#include <memory>

class SpriteBorderOverlayRenderSystem : public System {
public:
    SpriteBorderOverlayRenderSystem(std::shared_ptr<Registry> registry,
                                    std::shared_ptr<EventBus> eventBus)
        : System(registry, eventBus) {
        RequireComponent<TransformComponent>();
        RequireComponent<SpriteComponent>();
        RequireComponent<SpriteBorderOverlayComponent>();
    }

    void Update(SDL_Renderer* renderer, SDL_Rect& camera);
};

#endif