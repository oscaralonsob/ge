#include "UnitsLoader.hpp"

#include "../../Enemy/Components/TargetMovementComponent.hpp"
#include "../../Health/Components/HealthComponent.hpp"
#include "../../Physics2D/Vec2.hpp"
#include "../../Player/Components/KeyboardControllerComponent.hpp"
#include "../../Projectile/Components/ProjectileEmitterComponent.hpp"
#include "../AssetStore/AssetStore.hpp"
#include "../Camera/Components/CameraFollowComponent.hpp"
#include "../ECS/Registry.hpp"
#include "../Physics/Components/BoxColliderComponent.hpp"
#include "../Physics/Components/RigidBodyComponent.hpp"
#include "../Physics/Components/TransformComponent.hpp"
#include "../Render/Components/HealthBarComponent.hpp"
#include "../Render/Components/SpriteComponent.hpp"
#include "DTO/Unit.hpp"
#include "DTO/UnitComponent.hpp"
#include "LevelReader.hpp"

using namespace ge::physics2d;

UnitsLoader::UnitsLoader(std::shared_ptr<EventBus> eventBus,
                         std::shared_ptr<Registry> registry,
                         std::shared_ptr<LevelReader> levelReader)
    : eventBus(eventBus), registry(registry), levelReader(levelReader) {
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
        Vec2 pos;
        Vec2 size;
        double rotation;

        rotation = std::stod(unitComponent.values.at("rotation"));
        pos.x = std::stod(unitComponent.values.at("position.x"));
        pos.y = std::stod(unitComponent.values.at("position.y"));
        size.x = std::stod(unitComponent.values.at("size.x"));
        size.y = std::stod(unitComponent.values.at("size.y"));

        registry->AddComponent<TransformComponent>(unit, pos, size, rotation);
    } else if (unitComponent.type == "rigidbody") {
        Vec2 velocity;

        velocity.x = std::stod(unitComponent.values.at("velocity.x"));
        velocity.y = std::stod(unitComponent.values.at("velocity.y"));

        registry->AddComponent<RigidBodyComponent>(unit, velocity);
    } else if (unitComponent.type == "cameraFollow") {
        registry->AddComponent<CameraFollowComponent>(unit);
    } else if (unitComponent.type == "keyboardController") {
        float velocity = std::stod(unitComponent.values.at("velocity"));

        registry->AddComponent<KeyboardControllerComponent>(unit, velocity);
    } else if (unitComponent.type == "health") {
        int max = std::stoi(unitComponent.values.at("max"));
        int current = std::stoi(unitComponent.values.at("current"));

        registry->AddComponent<HealthComponent>(unit, max, current);
    } else if (unitComponent.type == "healthBar") {
        std::string font = unitComponent.values.at("font");

        registry->AddComponent<HealthBarComponent>(unit, font);
    } else if (unitComponent.type == "boxCollider") {
        Vec2 size;
        Vec2 offset;

        size.x = std::stod(unitComponent.values.at("size.x"));
        size.y = std::stod(unitComponent.values.at("size.y"));
        offset.x = std::stod(unitComponent.values.at("offset.x"));
        offset.y = std::stod(unitComponent.values.at("offset.y"));

        registry->AddComponent<BoxColliderComponent>(unit, size, offset);
    } else if (unitComponent.type == "projectileEmitter") {
        Vec2 projectileVelocity;
        int projectileFrequency;
        int projectileDuration;
        int hitDamage;
        bool isFriendly;

        projectileVelocity.x =
            std::stod(unitComponent.values.at("projectileVelocity.x"));
        projectileVelocity.y =
            std::stod(unitComponent.values.at("projectileVelocity.y"));
        projectileFrequency =
            std::stoi(unitComponent.values.at("projectileFrequency"));
        projectileDuration =
            std::stoi(unitComponent.values.at("projectileDuration"));
        hitDamage = std::stoi(unitComponent.values.at("hitDamage"));
        isFriendly = unitComponent.values.at("isFriendly") == "1";

        registry->AddComponent<ProjectileEmitterComponent>(
            unit, projectileVelocity, projectileFrequency, projectileDuration,
            hitDamage, isFriendly);
    } else if (unitComponent.type == "targetMovement") {
        float velocity = std::stod(unitComponent.values.at("velocity"));
        std::string tag = unitComponent.values.at("tag");

        registry->AddComponent<TargetMovementComponent>(unit, velocity, tag);
    } // TODO: add the map renderer
}