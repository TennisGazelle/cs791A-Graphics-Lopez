//
// Created by daniellopez on 10/27/17.
//

#ifndef TUTORIAL_VERTEX_H
#define TUTORIAL_VERTEX_H

#include "graphics_headers.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
    glm::vec3 normal;
    glm::vec3 tangent;
    glm::vec2 uv;
    Vertex(const glm::vec3& v,
           const glm::vec3& c,
           const glm::vec3& n,
           const glm::vec3& t,
           const glm::vec2& u): position(v), color(c), normal(n), tangent(t), uv(u) {}
};

#endif //TUTORIAL_VERTEX_H
