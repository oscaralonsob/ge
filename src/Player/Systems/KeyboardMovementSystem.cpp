#include "KeyboardMovementSystem.hpp"

#include "../../Common/ECS/Registry.hpp"
#include "../../Physics2D/Vec2.hpp"

using namespace ge::physics2d;

void KeyboardMovementSystem::SubscribeToEvents() {
    eventBus->SubscribeToEvent<const KeyPressedEvent>(
        this, &KeyboardMovementSystem::OnKeyPressed);
    eventBus->SubscribeToEvent<const KeyReleasedEvent>(
        this, &KeyboardMovementSystem::OnKeyReleased);
}

void KeyboardMovementSystem::OnKeyPressed(const KeyPressedEvent& event) {
    SwitchFlags(event.symbol, true);
}

void KeyboardMovementSystem::OnKeyReleased(const KeyReleasedEvent& event) {
    SwitchFlags(event.symbol, false);
}

void KeyboardMovementSystem::Update() {
    for (Entity entity : GetSystemEntities()) {
        const KeyboardControllerComponent keyboardControllerComponent =
            registry->GetComponent<KeyboardControllerComponent>(entity);
        RigidBodyComponent& rigidBodyComponent =
            registry->GetComponent<RigidBodyComponent>(entity);

        Vec2 calculatedVelocity = Vec2(0.0, 0.0);

        if (isUpBeingPressed) {
            calculatedVelocity = calculatedVelocity + Vec2(0.0, -1.0);
        }

        if (isRightBeingPressed) {
            calculatedVelocity = calculatedVelocity + Vec2(1.0, 0.0);
        }

        if (isDownBeingPressed) {
            calculatedVelocity = calculatedVelocity + Vec2(0.0, 1.0);
        }

        if (isLeftBeingPressed) {
            calculatedVelocity = calculatedVelocity + Vec2(-1.0, 0.0);
        }

        rigidBodyComponent.velocity =
            calculatedVelocity * keyboardControllerComponent.velocity;
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