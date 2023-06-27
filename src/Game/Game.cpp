#include "Game.h"

#include "../Systems/CameraMovementSystem.h"

int Game::windowWidth;
int Game::windowHeight;
int Game::mapWidth;
int Game::mapHeight;

Game::Game() {
    eventBus = std::make_shared<EventBus>();
    registry = std::make_shared<Registry>(eventBus);
    assetStore = std::make_unique<AssetStore>(eventBus);
    isRunning = false;
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
        ImGuiSDL::Initialize(renderer, windowWidth, windowHeight);
    }
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
    registry->AddSystem<KeyboardMovementSystem>();
    registry->AddSystem<DamageSystem>();
    registry->AddSystem<CollisionSystem>();
    registry->AddSystem<MovementSystem>();
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

    assetStore->AddTexture(renderer, "tank-image",
                           "./assets/images/tank-panther-right.png");
    assetStore->AddTexture(renderer, "truck-image",
                           "./assets/images/truck-ford-right.png");
    assetStore->AddTexture(renderer, "bullet-image",
                           "./assets/images/bullet.png");
    assetStore->AddTexture(renderer, "hero-image", "./assets/images/hero.png");
    assetStore->AddFont("charriot-font", "./assets/fonts/charriot.ttf", 32);
    assetStore->AddFont("charriot-font-mini", "./assets/fonts/charriot.ttf",
                        12);

    Entity tank = registry->CreateEntity();
    registry->AddGroupToEntity(tank, "Enemies");
    registry->AddComponent<TransformComponent>(tank, glm::vec2(100.0, 1.0),
                                               glm::vec2(1.0, 1.0), 0.0);
    registry->AddComponent<RigidBodyComponent>(tank, glm::vec2(0.0, 0.0));
    registry->AddComponent<SpriteComponent>(tank, "tank-image", 1,
                                            glm::vec2(32.0, 32.0),
                                            glm::vec2(0.0, 0.0), false);
    registry->AddComponent<BoxColliderComponent>(tank, glm::vec2(32.0, 32.0));
    registry->AddComponent<HealthComponent>(tank, 100, 100);
    registry->AddComponent<ProjectileEmitterComponent>(
        tank, glm::vec2(100.0, 100.0), 1000, 10000, 10, false);

    Entity truck = registry->CreateEntity();
    registry->AddGroupToEntity(truck, "Enemies");
    registry->AddComponent<TransformComponent>(truck, glm::vec2(10.0, 1.0),
                                               glm::vec2(1.0, 1.0), 0.0);
    registry->AddComponent<RigidBodyComponent>(truck, glm::vec2(0.0, 0.0));
    registry->AddComponent<SpriteComponent>(truck, "truck-image", 1,
                                            glm::vec2(32.0, 32.0),
                                            glm::vec2(0.0, 0.0), false);
    registry->AddComponent<BoxColliderComponent>(truck, glm::vec2(32.0, 32.0));
    registry->AddComponent<HealthComponent>(truck, 100, 100);

    Entity hero = registry->CreateEntity();
    registry->AddTagToEntity(hero, "Player");
    registry->AddComponent<TransformComponent>(hero, glm::vec2(10.0, 1.0),
                                               glm::vec2(1.0, 1.0), 0.0);
    registry->AddComponent<RigidBodyComponent>(hero, glm::vec2(0.0, 0.0));
    registry->AddComponent<SpriteComponent>(hero, "hero-image", 2,
                                            glm::vec2(32.0, 32.0),
                                            glm::vec2(0.0, 0.0), false);
    registry->AddComponent<KeyboardControllerComponent>(hero, 100.0);
    registry->AddComponent<CameraFollowComponent>(hero);
    registry->AddComponent<ProjectileEmitterComponent>(
        hero, glm::vec2(100.0, 100.0), 1000, 10000, 10, true);
    registry->AddComponent<HealthComponent>(hero, 100, 100);
    registry->AddComponent<BoxColliderComponent>(hero, glm::vec2(32.0, 32.0));
    registry->AddComponent<HealthBarComponent>(hero, "charriot-font-mini");

    Entity GUIWindow = registry->CreateEntity();
    registry->AddComponent<GUIWindowComponent>(
        GUIWindow, glm::vec2(200.0, 200.0), glm::vec2(100.0, 500.0));

    Entity GUIViewLabel = registry->CreateEntity();
    registry->AddComponent<GUITextLabelComponent>(
        GUIViewLabel, glm::vec2(100.0, 100.0), glm::vec2(100.0, 100.0),
        "Text test", "charriot-font");
}

// TODO: tilemap component?
void Game::LoadTileMap() {
    assetStore->AddTexture(renderer, "tilemap", "./assets/tilemaps/jungle.png");
    std::ifstream myfile("./assets/tilemaps/jungle.map");
    std::string line;
    size_t pos = 0;
    std::string token;
    std::string delimiter = ",";
    int tileSize = 32;
    int x = 0;
    int y = 0;
    while (std::getline(myfile, line)) {
        while ((pos = line.find(delimiter)) != std::string::npos) {
            token = line.substr(0, pos);
            line.erase(0, pos + delimiter.length());
            Entity tile = registry->CreateEntity();
            registry->AddGroupToEntity(tile, "tiles");
            registry->AddComponent<TransformComponent>(
                tile, glm::vec2(x * tileSize * 3.0, y * tileSize * 3.0),
                glm::vec2(3.0, 3.0), 0.0);
            registry->AddComponent<SpriteComponent>(
                tile, "tilemap", 0, glm::vec2(tileSize, tileSize),
                glm::vec2(std::stoi(token.substr(1, 2)),
                          std::stoi(token.substr(0, 1))));
            registry->AddComponent<SpriteBorderOverlayComponent>(tile);
            x++;
        }
        mapWidth = x * tileSize * 3;
        x = 0;
        y++;
    }
    mapHeight = y * tileSize * 3;
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
    registry->GetSystem<CameraMovementSystem>().Update(camera);
    registry->GetSystem<ProjectileEmitterSystem>().Update(deltaTime);
    registry->GetSystem<ProjectileLifeCycleSystem>().Update();
    registry->GetSystem<KeyboardMovementSystem>().Update();

    registry->Update();
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    registry->GetSystem<RenderSystem>().Update(renderer, assetStore, camera);
    registry->GetSystem<HealthBarRenderSystem>().Update(renderer, assetStore,
                                                        camera);
    registry->GetSystem<SpriteBorderOverlayRenderSystem>().Update(renderer,
                                                                  camera);
    registry->GetSystem<GUITextLabelRenderSystem>().Update(renderer, assetStore,
                                                           camera);
    registry->GetSystem<GUIWindowRenderSystem>().Update(renderer, camera);
    if (isDebug) {
        ImGui::NewFrame();

        registry->GetSystem<LogSystem>().Update();
        registry->GetSystem<LogMousePositionSystem>().Update(camera);

        ImGui::Render();
        ImGuiSDL::Render(ImGui::GetDrawData());
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
        ImGuiSDL::Deinitialize();
        ImGui::DestroyContext();
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
