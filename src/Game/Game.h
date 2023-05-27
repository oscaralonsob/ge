#ifndef GAME_H
#define GAME_H

#include "../../libs/glm/glm.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <fstream>
#include "../Logger/Logger.h"
#include "../ECS/Registry.h"
#include "../Events/EventBus.h"
#include "../Events/KeyPressedEvent.h"
#include "../AssetStore/AssetStore.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/KeyboardControllerComponent.h"
#include "../Components/CameraFollowComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/HealthComponent.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/AnimationSystem.h"
#include "../Systems/CollisionSystem.h"
#include "../Systems/DamageSystem.h"
#include "../Systems/KeyboardMovementSystem.h"
#include "../Systems/ProjectileEmitterSystem.h"
#include "../Systems/ProjectileLifeCycleSystem.h"

const double MILISENCOS_TO_SECONDS = 1000.0f;
const int FPS = 30;
const int MILISECONDS_PER_FRAME = MILISENCOS_TO_SECONDS / FPS;

class Game {
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Rect camera;
        bool isRunning;
        int milisecsPrevoiusFrame;

        std::unique_ptr<Registry> registry;
        std::unique_ptr<AssetStore> assetStore;
        std::unique_ptr<EventBus> eventBus;
        std::shared_ptr<Logger> logger;

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

        void Initialize();
        void Run();
        void Destroy();

};

#endif