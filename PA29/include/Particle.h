//
// Created by Daniel Lopez on 11/3/17.
//

#ifndef TUTORIAL_PARTICLE_H
#define TUTORIAL_PARTICLE_H

#include "graphics_headers.h"

struct Particle {
    Particle() : type(0.0), position(glm::vec3()), velocity(glm::vec3()), lifetimeMillis(0) {}
    float type;
    glm::vec3 position;
    glm::vec3 velocity;
    float lifetimeMillis;
};

#endif //TUTORIAL_PARTICLE_H
