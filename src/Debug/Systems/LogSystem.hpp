#ifndef LOGSYSTEM_HPP
#define LOGSYSTEM_HPP

#include "../../Common/ECS/System.hpp"

#include <imgui/imgui.h>

class LogSystem : public System {
private:
    ImGuiTextBuffer Buf;

    void AddLog(const char* fmt) {
        Buf.append(fmt);
        Buf.append("\n");
    }

public:
    LogSystem(std::shared_ptr<Registry> registry,
              std::shared_ptr<EventBus> eventBus,
              std::shared_ptr<AssetStore> assetStore)
        : System(registry, eventBus, assetStore) {
    }

    void SubscribeToEvents();
    void LogRequested(LogRequestEvent& event);
    void Update();
};

#endif