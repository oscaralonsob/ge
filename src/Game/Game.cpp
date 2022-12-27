#include <SDL2/SDL_image.h>
#include "../../libs/glm/glm.hpp"
#include "Game.h"

Game::Game() {
    logger = new Logger();
    isRunning = false;
    logger->Log("Game constructor called");
}

Game::~Game() {
    logger->Log("Game destructor called");
    delete logger;
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

//TODO: remove
glm::vec2 playerPosition;
glm::vec2 playerVelocity;

void Game::Setup() {
    milisecsPrevoiusFrame = SDL_GetTicks();
    playerPosition = glm::vec2(10, 10);
    playerVelocity = glm::vec2(100, 50);
}

void Game::Update() {
    //TODO: improve this...
    int timeTowait = MILISECONDS_PER_FRAME - (SDL_GetTicks() - milisecsPrevoiusFrame);
    if (timeTowait > 0 && timeTowait <= MILISECONDS_PER_FRAME) {
        SDL_Delay(timeTowait);
    }
    
    double deltaTime = (SDL_GetTicks() - milisecsPrevoiusFrame) / MILISENCOS_TO_SECONDS;
    milisecsPrevoiusFrame = SDL_GetTicks();

    //TODO update game objects
    playerPosition.x += playerVelocity.x * deltaTime;
    playerPosition.y += playerVelocity.y * deltaTime;
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    //Draw a silly player
    SDL_Rect destination = {
        static_cast<int>(playerPosition.x), 
        static_cast<int>(playerPosition.y), 
        32, 
        32
    };
    SDL_Surface* surface = IMG_Load("./assets/images/tank-tiger-right.png");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(
        renderer, 
        texture, 
        NULL, // Full rect (image)
        &destination //Place where the texture will be drawn
    );
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

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

