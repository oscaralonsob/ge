#ifndef GAME_H
#define GAME_H

#include "../../libs/glm/glm.hpp"
#include "../Common/AssetStore/AssetStore.hpp"
#include "../Common/ECS/Registry.hpp"
#include "../Common/GUI/Components/GUITextLabelComponent.hpp"
#include "../Common/GUI/Systems/GUITextLabelRenderSystem.hpp"
#include "../Components/AnimationComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/CameraFollowComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/KeyboardControllerComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"
#include "../Debug/Systems/LogMousePositionSystem.hpp"
#include "../Debug/Systems/LogSystem.hpp"
#include "../Events/EventBus.h"
#include "../Events/KeyPressedEvent.h"
#include "../Systems/AnimationSystem.h"
#include "../Systems/CollisionSystem.h"
#include "../Systems/DamageSystem.h"
#include "../Systems/HealthBarRenderSystem.h"
#include "../Systems/KeyboardMovementSystem.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/ProjectileEmitterSystem.h"
#include "../Systems/ProjectileLifeCycleSystem.h"
#include "../Systems/RenderSystem.h"
#include "../World/Tile/Components/SpriteBorderOverlayComponent.hpp"
#include "../World/Tile/Systems/SpriteBorderOverlayRenderSystem.hpp"

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

    std::unique_ptr<Registry> registry;
    std::unique_ptr<AssetStore> assetStore;
    std::shared_ptr<EventBus> eventBus;

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