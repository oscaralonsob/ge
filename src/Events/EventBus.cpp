#include "EventBus.h"

EventBus::EventBus() {
    EmitEvent<LogRequestEvent>("EventBus created");
}

EventBus::~EventBus() {
    EmitEvent<LogRequestEvent>("EventBus destroyed");
}

void EventBus::Reset() {
    subscribers.clear();
}