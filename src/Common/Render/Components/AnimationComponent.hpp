#ifndef ANIMATIONCOMPONENT_HPP
#define ANIMATIONCOMPONENT_HPP

#include <glm/glm.hpp>
#include <string>

struct AnimationComponent {
    int numFrames;
    int currentFrame;
    int frameRate;
    bool loop;
    double animationFrame;

    AnimationComponent(int numFrames = 1, int currentFrame = 1,
                       int frameRate = 1, bool loop = false) {
        this->numFrames = numFrames;
        this->currentFrame = currentFrame;
        this->frameRate = frameRate;
        this->loop = loop;
        this->animationFrame = 0;
    }
};

#endif
