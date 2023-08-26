#ifndef MAPCOMPONENT_HPP
#define MAPCOMPONENT_HPP

#include <glm/glm.hpp>
#include <string>
#include <vector>

struct MapComponent {
    std::string textureId;
    glm::vec2 tileSize;
    std::vector<glm::vec2> tiles;
    int width;

    MapComponent(std::string textureId = "",
                 glm::vec2 tileSize = glm::vec2(0.0, 0.0),
                 std::vector<glm::vec2> tiles = {}, int width = 0) {
        this->textureId = textureId;
        this->tileSize = tileSize;
        this->tiles = tiles;
        this->width = width;
    }
};

#endif
