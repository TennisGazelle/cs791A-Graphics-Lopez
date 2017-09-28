#ifndef OBJECT_H
#define OBJECT_H

#include <cstdlib>
#include <vector>
#include "graphics_headers.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/color4.h>
#include <glm/gtx/vector_angle.hpp>

#include <fstream>
#include <string>
using namespace Assimp;
using namespace std;

class Object {
public:
    Object();
    ~Object();
    bool Init(const std::string& filename);
    void Update(unsigned int dt);
    void Render();
    bool LoadVerticiesFromFile(const std::string& filename);

    glm::mat4 GetModel();

    std::vector<Vertex> vertices;
    glm::mat4 model;
private:
    std::vector<unsigned int> indices;
    GLuint VBO;
    GLuint IBO;
};

#endif /* OBJECT_H */
