#include "UnitsLoader.hpp"

#include "../AssetStore/AssetStore.hpp"
#include "../ECS/Registry.hpp"
#include "../Physics/Components/RigidBodyComponent.hpp"
#include "../Physics/Components/TransformComponent.hpp"
#include "../Render/Components/SpriteComponent.hpp"
#include "DTO/Unit.hpp"
#include "DTO/UnitComponent.hpp"
#include "LevelReader.hpp"

UnitsLoader::UnitsLoader(std::shared_ptr<EventBus> eventBus,
                         std::shared_ptr<Registry> registry,
                         std::shared_ptr<LevelReader> levelReader) {
    this->eventBus = eventBus;
    this->registry = registry;
    this->levelReader = levelReader;
}

void UnitsLoader::Load() {
    std::vector<Unit> units = levelReader->GetUnits();

    for (Unit unit : units) {
        Entity entity = registry->CreateEntity();

        if (unit.group != "") {
            registry->AddGroupToEntity(entity, unit.group);
        }

        if (unit.tag != "") {
            registry->AddTagToEntity(entity, unit.tag);
        }

        for (UnitComponent unitComponent : unit.components) {
            LoadComponent(entity, unitComponent);
        }
    }
}

// TODO: create factory, one per component pls
void UnitsLoader::LoadComponent(Entity unit, UnitComponent unitComponent) {
    if (unitComponent.type == "sprite") {
        registry->AddComponent<SpriteComponent>(
            unit, unitComponent.values.at("texture"), 1, glm::vec2(32.0, 32.0),
            glm::vec2(0.0, 0.0), false);
    } else if (unitComponent.type == "transform") {
        glm::vec2 pos;
        glm::vec2 size;
        double rotation;

        rotation = std::stod(unitComponent.values.at("rotation"));
        pos.x = std::stod(unitComponent.values.at("position.x"));
        pos.y = std::stod(unitComponent.values.at("position.y"));
        size.x = std::stod(unitComponent.values.at("size.x"));
        size.y = std::stod(unitComponent.values.at("size.y"));

        registry->AddComponent<TransformComponent>(unit, pos, size, rotation);
    } else if (unitComponent.type == "rigidbody") {
        glm::vec2 velocity;

        velocity.x = std::stod(unitComponent.values.at("velocity.x"));
        velocity.y = std::stod(unitComponent.values.at("velocity.y"));

        registry->AddComponent<RigidBodyComponent>(unit, velocity);
    }
}