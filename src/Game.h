#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

class Game {
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        bool isRunning;
        int windowWidth;
        int windowHeight;

        void ProcessInput();
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