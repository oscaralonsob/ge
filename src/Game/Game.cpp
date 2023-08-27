#include "Game.h"

#include "../Common/GameEngine/AssetsLoader.hpp"
#include "../Common/GameEngine/LevelReader.hpp"
#include "../Common/GameEngine/UnitsLoader.hpp"

#include <SDL2/SDL_ttf.h>

Game::Game() {
}

Game::~Game() {
}

void Game::Initialize(bool debugMode) {
    isDebug = debugMode;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        return;
    }

    if (TTF_Init() != 0) {
        return;
    }

    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    windowWidth = displayMode.w;
    windowHeight = displayMode.h;

    window =
        SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         windowWidth, windowHeight, SDL_WINDOW_BORDERLESS);
    if (!window) {
        return;
    }

    renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        return;
    }
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    isRunning = true;

    camera.x = 0;
    camera.y = 0;
    camera.w = windowWidth;
    camera.h = windowHeight;

    if (isDebug) {
        ImGui::CreateContext();
        ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
        ImGui_ImplSDLRenderer2_Init(renderer);
    }

    eventBus = std::make_shared<EventBus>();
    assetStore = std::make_unique<AssetStore>(eventBus, renderer);
    registry = std::make_shared<Registry>(eventBus, assetStore);
}

void Game::ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {

        if (isDebug) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            ImGuiIO& io = ImGui::GetIO();

            int mouseX, mouseY;
            const int buttons = SDL_GetMouseState(&mouseX, &mouseY);

            io.MousePos = ImVec2(mouseX, mouseY);
            io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
            io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);
        }

        switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            eventBus->EmitEvent<KeyPressedEvent>(event.key.keysym.sym);
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                isRunning = false;
            }
            break;
        case SDL_KEYUP:
            eventBus->EmitEvent<KeyReleasedEvent>(event.key.keysym.sym);
            break;
        }
    }
}

// TODO: multiple levels for example
void Game::LoadLevel() {
    levelReader = std::make_shared<LevelReader>("Level1");
    AssetsLoader* assetsLoader =
        new AssetsLoader(eventBus, assetStore, levelReader);

    UnitsLoader* unitsLoader = new UnitsLoader(eventBus, registry, levelReader);

    assetsLoader->Load();
    unitsLoader->Load();

    registry->AddSystem<KeyboardMovementSystem>();
    registry->AddSystem<TargetMovementSystem>();
    registry->AddSystem<DamageSystem>();
    registry->AddSystem<CollisionSystem>();
    registry->AddSystem<MovementSystem>();
    registry->AddSystem<RenderMapSystem>();
    registry->AddSystem<RenderSystem>();
    registry->AddSystem<HealthBarRenderSystem>();
    registry->AddSystem<AnimationSystem>();
    registry->AddSystem<CameraMovementSystem>();
    registry->AddSystem<ProjectileEmitterSystem>();
    registry->AddSystem<ProjectileLifeCycleSystem>();
    registry->AddSystem<SpriteBorderOverlayRenderSystem>();
    registry->AddSystem<GUIWindowRenderSystem>();
    registry->AddSystem<GUITextLabelRenderSystem>();

    // TODO: should be necesary just once, not in every update
    eventBus->Reset();
    registry->GetSystem<DamageSystem>().SubscribeToEvents();
    registry->GetSystem<KeyboardMovementSystem>().SubscribeToEvents();
    registry->GetSystem<ProjectileEmitterSystem>().SubscribeToEvents();
    if (isDebug) {
        registry->AddSystem<LogSystem>();
        registry->AddSystem<LogMousePositionSystem>();
        registry->GetSystem<LogSystem>().SubscribeToEvents();
    }

    LoadTileMap();
}

// TODO: tilemap component?
void Game::LoadTileMap() {
    Entity map = registry->CreateEntity();
    std::vector<glm::vec2> mapVector(10, glm::vec2(-1, -1));
    int index = 0;
    std::ifstream myfile("./assets/tilemaps/jungle.map");
    std::string line;
    size_t pos = 0;
    std::string token;
    std::string delimiter = ",";
    int tileSize = 32;
    int x = 0;
    int y = 0;
    while (std::getline(myfile, line)) {
        x = 0;
        while ((pos = line.find(delimiter)) != std::string::npos) {
            token = line.substr(0, pos);
            line.erase(0, pos + delimiter.length());

            if (index == mapVector.size()) {
                mapVector.resize(mapVector.size() * 2, glm::vec2(-1, -1));
            }
            mapVector[index] = glm::vec2(std::stoi(token.substr(1, 2)),
                                         std::stoi(token.substr(0, 1)));
            index++;
            x++;
        }
        mapWidth = x * tileSize * 3;
        y++;
    }
    mapHeight = y * tileSize * 3;
    // TODO: add scale
    registry->AddComponent<MapComponent>(
        map, "tilemap", glm::vec2(tileSize, tileSize), mapVector, x - 1);
}

void Game::Setup() {
    LoadLevel();
}

void Game::Update() {
    // TODO: improve this...
    int timeTowait =
        MILISECONDS_PER_FRAME - (SDL_GetTicks() - milisecsPrevoiusFrame);
    if (timeTowait > 0 && timeTowait <= MILISECONDS_PER_FRAME) {
        SDL_Delay(timeTowait);
    }

    double deltaTime =
        (SDL_GetTicks() - milisecsPrevoiusFrame) / MILISENCOS_TO_SECONDS;
    milisecsPrevoiusFrame = SDL_GetTicks();

    // TODO: do not subscribe every time
    eventBus->Reset();
    registry->GetSystem<DamageSystem>().SubscribeToEvents();
    registry->GetSystem<KeyboardMovementSystem>().SubscribeToEvents();
    registry->GetSystem<ProjectileEmitterSystem>().SubscribeToEvents();
    registry->GetSystem<LogSystem>().SubscribeToEvents();

    // TODO: update in registry maybe?
    registry->GetSystem<CollisionSystem>().Update();
    registry->GetSystem<MovementSystem>().Update(deltaTime);
    registry->GetSystem<AnimationSystem>().Update(deltaTime);
    registry->GetSystem<CameraMovementSystem>().Update(camera, windowWidth,
                                                       windowHeight);
    registry->GetSystem<ProjectileEmitterSystem>().Update(deltaTime);
    registry->GetSystem<ProjectileLifeCycleSystem>().Update();
    registry->GetSystem<KeyboardMovementSystem>().Update();
    registry->GetSystem<TargetMovementSystem>().Update();

    registry->Update();
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    registry->GetSystem<RenderMapSystem>().Update(renderer, assetStore, camera);

    registry->GetSystem<RenderSystem>().Update(renderer, assetStore, camera);
    registry->GetSystem<HealthBarRenderSystem>().Update(renderer, assetStore,
                                                        camera);
    registry->GetSystem<SpriteBorderOverlayRenderSystem>().Update(renderer,
                                                                  camera);
    registry->GetSystem<GUITextLabelRenderSystem>().Update(renderer, assetStore,
                                                           camera);
    registry->GetSystem<GUIWindowRenderSystem>().Update(renderer, camera);
    if (isDebug) {
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        registry->GetSystem<LogSystem>().Update();
        registry->GetSystem<LogMousePositionSystem>().Update(camera);

        ImGui::Render();
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
    }

    SDL_RenderPresent(renderer);
}

void Game::Run() {
    Setup();
    while (isRunning) {
        ProcessInput();
        Update();
        Render();
    }
}

void Game::Destroy() {
    if (isDebug) {
        ImGui_ImplSDLRenderer2_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
