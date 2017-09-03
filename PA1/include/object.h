#ifndef OBJECT_H
#define OBJECT_H

#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>

#include "graphics_headers.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/color4.h>
#include <glm/gtx/vector_angle.hpp>

using namespace Assimp;

class Object {
public:
    Object();
    ~Object();
    void Init(const std::string& filename);
    void Update(unsigned int dt);
    void Render();
    void LoadVerticiesFromFile(const std::string& filename);

    glm::mat4 GetModel();

private:
    glm::mat4 model;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    GLuint VBO;
    GLuint IBO;
};

#endif /* OBJECT_H */
