#include "Game.h"

Game::Game() {
    logger = std::make_shared<Logger>();;
    registry = std::make_unique<Registry>(logger);
    assetStore = std::make_unique<AssetStore>(logger);
    isRunning = false;
    logger->Log("Game constructor called");
}

Game::~Game() {
    logger->Log("Game destructor called");
}

void Game::Initialize() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        logger->Err("Error initializing SDL");
        return;
    }

    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    windowWidth = displayMode.w;
    windowHeight = displayMode.h;

    window = SDL_CreateWindow(
        "Game", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        windowWidth, 
        windowHeight,
        SDL_WINDOW_BORDERLESS
    );
    if (!window) {
        logger->Err("Error creating SDL window");
        return;
    }

    renderer = SDL_CreateRenderer(
        window, 
        -1, 
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (!renderer) {
        logger->Err("Error creating SDL renderer");
        return;
    }
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    isRunning = true;
}

void Game::ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                isRunning = false;
            }
            break;
        }
    }
}

//TODO: multiple levels for example
void Game::LoadLevel() {
    registry->AddSystem<MovementSystem>();
    registry->AddSystem<RenderSystem>();    
    
    LoadTileMap();

    assetStore->AddTexture(renderer, "tank-image", "./assets/images/tank-panther-right.png");
    assetStore->AddTexture(renderer, "truck-image", "./assets/images/truck-ford-right.png");

    Entity tank = registry->CreateEntity();
    registry->AddComponent<TransformComponent>(tank, glm::vec2(10.0, 1.0), glm::vec2(1.0, 1.0), 0.0);
    registry->AddComponent<RigidBodyComponent>(tank, glm::vec2(0.0, 10.0));
    registry->AddComponent<SpriteComponent>(tank, "tank-image", glm::vec2(32.0, 32.0));

    Entity truck = registry->CreateEntity();
    registry->AddComponent<TransformComponent>(truck, glm::vec2(10.0, .0), glm::vec2(1.0, 1.0), 0.0);
    registry->AddComponent<RigidBodyComponent>(truck, glm::vec2(10.0, 0.0));
    registry->AddComponent<SpriteComponent>(truck, "truck-image", glm::vec2(32.0, 32.0), glm::vec2(0.0, 0.0));
}

//TODO: tilemap component?
void Game::LoadTileMap() {
    assetStore->AddTexture(renderer, "tilemap-image", "./assets/tilemaps/jungle.png");

    assetStore->AddTexture(renderer, "tilemap", "./assets/tilemaps/jungle.png");
    std::ifstream myfile("./assets/tilemaps/jungle.map");
    std::string line;
    size_t pos = 0;
    std::string token;
    std::string delimiter = ",";
    int tileSize = 32;
    int x = 0;
    int y = 0;
    while (std::getline(myfile, line))
    {
        while ((pos = line.find(delimiter)) != std::string::npos) {
            token = line.substr(0, pos);
            line.erase(0, pos + delimiter.length());
            Entity tile = registry->CreateEntity();
            registry->AddComponent<TransformComponent>(tile, glm::vec2(x*tileSize, y*tileSize), glm::vec2(1.0, 1.0), 0.0);
            registry->AddComponent<SpriteComponent>(
                tile, 
                "tilemap", 
                glm::vec2(tileSize, tileSize), 
                glm::vec2(std::stoi(token.substr(1,2)), std::stoi(token.substr(0,1)))
            );
            x++;
        }
        x = 0;
        y++;
    }

}

void Game::Setup() {
    LoadLevel();
}

void Game::Update() {
    //TODO: improve this...
    int timeTowait = MILISECONDS_PER_FRAME - (SDL_GetTicks() - milisecsPrevoiusFrame);
    if (timeTowait > 0 && timeTowait <= MILISECONDS_PER_FRAME) {
        SDL_Delay(timeTowait);
    }
    
    double deltaTime = (SDL_GetTicks() - milisecsPrevoiusFrame) / MILISENCOS_TO_SECONDS;
    milisecsPrevoiusFrame = SDL_GetTicks();

    //TODO: update in registry maybe?
    registry->GetSystem<MovementSystem>().Update(deltaTime);

    registry->Update();
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    registry->GetSystem<RenderSystem>().Update(renderer, assetStore);

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
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

