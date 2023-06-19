#ifndef KEYBOARDMOVEMENTSYSTEM_HPP
#define KEYBOARDMOVEMENTSYSTEM_HPP

#include "../../Common/ECS/System.hpp"
#include "../../Components/RigidBodyComponent.h"
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
    KeyboardMovementSystem(Registry* registry,
                           std::shared_ptr<EventBus> eventBus)
        : System(registry, eventBus) {
        RequireComponent<KeyboardControllerComponent>();
        RequireComponent<RigidBodyComponent>();
    }

    void SubscribeToEvents();
    void OnKeyPressed(KeyPressedEvent& event);
    void OnKeyReleased(KeyReleasedEvent& event);
    void Update();
};

#endif