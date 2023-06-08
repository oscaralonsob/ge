#ifndef RENDERENGINEGUISYSTEM_H
#define RENDERENGINEGUISYSTEM_H

#include "../Components/BoxColliderComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"
#include "../ECS/System.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl.h>
#include <imgui/imgui_sdl.h>

class RenderEngineGUISystem : public System {
public:
    RenderEngineGUISystem(Registry* registry, std::shared_ptr<Logger> logger)
        : System(registry, logger) {
    }

    // TODO: cpp file pls
    void Update() {
        ImGui::NewFrame();

        if (ImGui::Begin("Spawn enemies")) {
            static int enemyXPos, enemyYPos;
            ImGui::InputInt("Enemy X position", &enemyXPos);
            ImGui::InputInt("Enemy y position", &enemyYPos);

            if (ImGui::Button("Spawn")) {
                Entity tank = registry->CreateEntity();
                registry->AddGroupToEntity(tank, "Enemies");
                registry->AddComponent<TransformComponent>(
                    tank, glm::vec2(enemyXPos, enemyYPos), glm::vec2(1.0, 1.0),
                    0.0);
                registry->AddComponent<RigidBodyComponent>(tank,
                                                           glm::vec2(0.0, 0.0));
                registry->AddComponent<SpriteComponent>(
                    tank, "tank-image", 1, glm::vec2(32.0, 32.0),
                    glm::vec2(0.0, 0.0), false);
                registry->AddComponent<BoxColliderComponent>(
                    tank, glm::vec2(32.0, 32.0));
                registry->AddComponent<HealthComponent>(tank, 100, 100);
                registry->AddComponent<ProjectileEmitterComponent>(
                    tank, glm::vec2(100.0, 100.0), 1000, 10000, 10, false);
            }
        }
        ImGui::End();

        ImGui::Render();
        ImGuiSDL::Render(ImGui::GetDrawData());
    }
};

#endif