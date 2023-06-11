#ifndef LOGSYSTEM_HPP
#define LOGSYSTEM_HPP

#include "../../ECS/System.h"
#include "../../Events/EventBus.h"
#include "../Events/LogRequestEvent.hpp"

#include <SDL2/SDL.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl.h>
#include <imgui/imgui_sdl.h>
#include <memory>

class LogSystem : public System {
private:
    ImGuiTextBuffer Buf;

    void AddLog(const char* fmt) {
        Buf.append(fmt);
        Buf.append("\n");
    }

public:
    LogSystem(Registry* registry, std::shared_ptr<EventBus> eventBus)
        : System(registry, eventBus) {
    }

    void SubscribeToEvents() {
        eventBus->SubscribeToEvent<LogRequestEvent>(this,
                                                    &LogSystem::LogRequested);
    }

    // TODO: cpp file pls
    void LogRequested(LogRequestEvent& event) {
        AddLog(event.message.c_str());
    }

    void Update() {
        if (!ImGui::Begin("Log")) {
            ImGui::End();
            return;
        }

        ImGui::BeginChild("scrolling", ImVec2(0, 0), false,
                          ImGuiWindowFlags_HorizontalScrollbar);
        ImGui::TextUnformatted(Buf.begin());

        ImGui::EndChild();
        ImGui::End();
    }
};

#endif