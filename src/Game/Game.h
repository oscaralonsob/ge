#ifndef GAME_H
#define GAME_H

#include "../../libs/glm/glm.hpp"
#include "../Common/AssetStore/AssetStore.hpp"
#include "../Common/Camera/Components/CameraFollowComponent.hpp"
#include "../Common/Camera/Systems/CameraMovementSystem.hpp"
#include "../Common/Debug/Systems/LogMousePositionSystem.hpp"
#include "../Common/Debug/Systems/LogSystem.hpp"
#include "../Common/ECS/Registry.hpp"
#include "../Common/Events/EventBus.hpp"
#include "../Common/GUI/Components/GUITextLabelComponent.hpp"
#include "../Common/GUI/Components/GUIWindowComponent.hpp"
#include "../Common/GUI/Systems/GUITextLabelRenderSystem.hpp"
#include "../Common/GUI/Systems/GUIWindowRenderSystem.hpp"
#include "../Common/Physics/Components/BoxColliderComponent.hpp"
#include "../Common/Physics/Components/RigidBodyComponent.hpp"
#include "../Common/Physics/Components/TransformComponent.hpp"
#include "../Common/Physics/Systems/CollisionSystem.hpp"
#include "../Common/Physics/Systems/MovementSystem.hpp"
#include "../Common/Render/Components/AnimationComponent.hpp"
#include "../Common/Render/Components/HealthBarComponent.hpp"
#include "../Common/Render/Components/SpriteBorderOverlayComponent.hpp"
#include "../Common/Render/Components/SpriteComponent.hpp"
#include "../Common/Render/Systems/AnimationSystem.hpp"
#include "../Common/Render/Systems/HealthBarRenderSystem.hpp"
#include "../Common/Render/Systems/RenderSystem.hpp"
#include "../Common/Render/Systems/SpriteBorderOverlayRenderSystem.hpp"
#include "../Enemy/Systems/TargetMovementSystem.hpp"
#include "../Player/Components/KeyboardControllerComponent.hpp"
#include "../Player/Events/KeyPressedEvent.hpp"
#include "../Player/Systems/KeyboardMovementSystem.hpp"
#include "../Projectile/Components/ProjectileEmitterComponent.hpp"
#include "../Projectile/Systems/ProjectileEmitterSystem.hpp"
#include "../Projectile/Systems/ProjectileLifeCycleSystem.hpp"
#include "../Systems/DamageSystem.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fstream>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl.h>
#include <imgui/imgui_sdl.h>
#include <iostream>

const double MILISENCOS_TO_SECONDS = 1000.0f;
const int FPS = 30;
const int MILISECONDS_PER_FRAME = MILISENCOS_TO_SECONDS / FPS;

class Game {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Rect camera;
    bool isRunning;
    bool isDebug;
    int milisecsPrevoiusFrame;

    std::shared_ptr<Registry> registry;
    std::shared_ptr<AssetStore> assetStore;
    std::shared_ptr<EventBus> eventBus;
    std::shared_ptr<class LevelReader> levelReader;

    void ProcessInput();
    void Setup();
    void LoadLevel();
    void LoadTileMap();
    void Update();
    void Render();

public:
    Game();
    ~Game();

    static int mapWidth;
    static int mapHeight;
    static int windowWidth;
    static int windowHeight;

    void Initialize(bool debugMode);
    void Run();
    void Destroy();
};

#endif