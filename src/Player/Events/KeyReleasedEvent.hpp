#ifndef KEYRELEASEDEVENT_HPP
#define KEYRELEASEDEVENT_HPP

#include "../../Common/Events/Event.hpp"

#include <SDL2/SDL.h>

class KeyReleasedEvent : public Event {
public:
    SDL_Keycode symbol;
    KeyReleasedEvent(SDL_Keycode symbol) : symbol(symbol){};
};

#endif