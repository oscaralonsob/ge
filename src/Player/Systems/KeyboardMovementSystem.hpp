#ifndef KEYBOARDMOVEMENTSYSTEM_HPP
#define KEYBOARDMOVEMENTSYSTEM_HPP

#include "../../Common/ECS/System.hpp"
#include "../../Common/Physics/Components/RigidBodyComponent.hpp"
#include "../Components/KeyboardControllerComponent.hpp"
#include "../Events/KeyPressedEvent.hpp"
#include "../Events/KeyReleasedEvent.hpp"

class KeyboardMovementSystem : public System {
private:
    bool isUpBeingPressed = false;
    bool isDownBeingPressed = false;
    bool isRightBeingPressed = false;
    bool isLeftBeingPressed = false;

    void SwitchFlags(SDL_Keycode symbol, bool isPressed);

public:
    KeyboardMovementSystem(std::shared_ptr<Registry> registry,
                           std::shared_ptr<EventBus> eventBus,
                           std::shared_ptr<AssetStore> assetStore)
        : System(registry, eventBus, assetStore) {
        RequireComponent<KeyboardControllerComponent>();
        RequireComponent<RigidBodyComponent>();
    }

    void SubscribeToEvents();
    void OnKeyPressed(KeyPressedEvent& event);
    void OnKeyReleased(KeyReleasedEvent& event);
    void Update();
};

#endif