#include "EventBus.h"

EventBus::EventBus(std::shared_ptr<Logger> l) {
    logger = l;
}

EventBus::~EventBus() {
    this->logger->Log("Event bus destroyed");
}

void EventBus::Reset() {
    subscribers.clear();
}