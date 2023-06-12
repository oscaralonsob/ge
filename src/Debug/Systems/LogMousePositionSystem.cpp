#include "LogMousePositionSystem.hpp"

#include <SDL2/SDL.h>
#include <imgui/imgui.h>

void LogMousePositionSystem::Update(const SDL_Rect& camera) {
    if (!ImGui::Begin("Mouse")) {
        ImGui::End();
        return;
    }
    ImGui::Text("Map coordinates (x=%.1f, y=%.1f)",
                ImGui::GetIO().MousePos.x + camera.x,
                ImGui::GetIO().MousePos.y + camera.y);
    ImGui::End();
}
