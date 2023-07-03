#include "LogSystem.hpp"

#include "../../Events/EventBus.hpp"
#include "../Events/LogRequestEvent.hpp"

void LogSystem::SubscribeToEvents() {
    eventBus->SubscribeToEvent<LogRequestEvent>(this, &LogSystem::LogRequested);
}

void LogSystem::LogRequested(LogRequestEvent& event) {
    AddLog(event.message.c_str());
}

void LogSystem::Update() {
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