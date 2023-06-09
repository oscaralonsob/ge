#ifndef LOGREQUESTEVENT_HPP
#define LOGREQUESTEVENT_HPP

#include "../../Events/Event.h"

#include <SDL2/SDL.h>
#include <string>

class LogRequestEvent : public Event {
private:
    const std::string LOG = "LOG";
    const std::string GREY = "\033[1;90m";
    const std::string END = "\033[0m";

public:
    std::string message;
    LogRequestEvent(std::string message) : message(message){};
};

#endif