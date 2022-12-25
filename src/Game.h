#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

const double MILISENCOS_TO_SECONDS = 1000.0f;
const int FPS = 30;
const int MILISECONDS_PER_FRAME = MILISENCOS_TO_SECONDS / FPS;

class Game {
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        bool isRunning;
        int milisecsPrevoiusFrame;
        int windowWidth;
        int windowHeight;

        void ProcessInput();
        void Setup();
        void Update();
        void Render();
    public:
        Game();
        ~Game();

        void Initialize();
        void Run();
        void Destroy();

};

#endif