#ifndef HEALTHBARCOMPONENT_HPP
#define HEALTHBARCOMPONENT_HPP

#include <string>

struct HealthBarComponent {
    std::string assetId;

    HealthBarComponent(std::string assetId = "") {
        this->assetId = assetId;
    }
};

#endif
