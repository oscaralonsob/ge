#ifndef UNITSLOADER_HPP
#define UNITSLOADER_HPP

#include <SDL2/SDL.h>
#include <memory>

class UnitsLoader {
private:
    std::shared_ptr<class EventBus> eventBus;
    std::shared_ptr<class Registry> registry;
    std::shared_ptr<class LevelReader> levelReader;

    void LoadComponent(class Entity unit, class UnitComponent unitComponent);

public:
    UnitsLoader(std::shared_ptr<EventBus> eventBus,
                std::shared_ptr<Registry> registry,
                std::shared_ptr<LevelReader> levelReader);
    ~UnitsLoader() = default;

    void Load();
};

#endif