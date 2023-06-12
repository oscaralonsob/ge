#ifndef LOGMOUSEPOSITIONSYSTEM_HPP
#define LOGMOUSEPOSITIONSYSTEM_HPP

#include "../../Common/ECS/System.hpp"
#include "../../Events/EventBus.h"

#include <SDL2/SDL.h>
#include <imgui/imgui.h>
#include <memory>

class LogMousePositionSystem : public System {
public:
    LogMousePositionSystem(Registry* registry,
                           std::shared_ptr<EventBus> eventBus)
        : System(registry, eventBus) {
    }

    void Update(const SDL_Rect& camera) {
        if (!ImGui::Begin("Mouse")) {
            ImGui::End();
            return;
        }
        ImGui::Text("Map coordinates (x=%.1f, y=%.1f)",
                    ImGui::GetIO().MousePos.x + camera.x,
                    ImGui::GetIO().MousePos.y + camera.y);
        ImGui::End();
    }
};

#endif