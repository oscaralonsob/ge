#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "../libs/glm/glm.hpp" //TODO: fix <> and ""
#include "../libs/imgui/imgui.h"

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);

    glm::vec2 velocity = glm::vec2(5.0, 2.0);
    
    std::cout << "Hello, world!" << std::endl;
    return 0;
}
