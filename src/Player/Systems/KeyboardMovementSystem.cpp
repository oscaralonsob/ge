#include "KeyboardMovementSystem.hpp"

#include "../../Common/ECS/Registry.hpp"

void KeyboardMovementSystem::SubscribeToEvents() {
    eventBus->SubscribeToEvent<KeyPressedEvent>(
        this, &KeyboardMovementSystem::OnKeyPressed);
    eventBus->SubscribeToEvent<KeyReleasedEvent>(
        this, &KeyboardMovementSystem::OnKeyReleased);
}

void KeyboardMovementSystem::OnKeyPressed(KeyPressedEvent& event) {
    SwitchFlags(event.symbol, true);
}

void KeyboardMovementSystem::OnKeyReleased(KeyReleasedEvent& event) {
    SwitchFlags(event.symbol, false);
}

void KeyboardMovementSystem::Update() {
    for (Entity entity : GetSystemEntities()) {
        const KeyboardControllerComponent keyboardControllerComponent =
            registry->GetComponent<KeyboardControllerComponent>(entity);
        RigidBodyComponent& rigidBodyComponent =
            registry->GetComponent<RigidBodyComponent>(entity);

        glm::vec2 calculatedVelocity = glm::vec2(0.0, 0.0);

        if (isUpBeingPressed) {
            calculatedVelocity += glm::vec2(0.0, -1.0);
        }

        if (isRightBeingPressed) {
            calculatedVelocity += glm::vec2(1.0, 0.0);
        }

        if (isDownBeingPressed) {
            calculatedVelocity += glm::vec2(0.0, 1.0);
        }

        if (isLeftBeingPressed) {
            calculatedVelocity += glm::vec2(-1.0, 0.0);
        }

        rigidBodyComponent.velocity =
            keyboardControllerComponent.velocity * calculatedVelocity;
    }
}

void KeyboardMovementSystem::SwitchFlags(SDL_Keycode symbol, bool isPressed) {
    if (symbol == SDLK_UP) {
        isUpBeingPressed = isPressed;
    }

    if (symbol == SDLK_RIGHT) {
        isRightBeingPressed = isPressed;
    }

    if (symbol == SDLK_DOWN) {
        isDownBeingPressed = isPressed;
    }

    if (symbol == SDLK_LEFT) {
        isLeftBeingPressed = isPressed;
    }
}