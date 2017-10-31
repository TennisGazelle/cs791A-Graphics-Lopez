#ifndef OBJECT_H
#define OBJECT_H

#include <cstdlib>
#include <vector>
#include "graphics_headers.h"
#include "Vertex.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/color4.h>
#include <glm/gtx/vector_angle.hpp>
#include <Magick++.h>

#include <fstream>
#include <string>
using namespace Assimp;

class Object {
public:
    Object();
    ~Object();
    bool Init(const std::string& filename);
    void Update(unsigned int dt);
    void Render();
    bool LoadVerticiesFromFile(const std::string& filename);
    void SetTextureID(const std::string& textID);

    glm::mat4 GetModel();
    void setModel(const glm::mat4& incomingMatrix);

    std::vector<Vertex> vertices;
private:
    glm::mat4 model;
    std::vector<unsigned int> indices;
    GLuint VBO;
    GLuint IBO;
    std::string textureID;

};

#endif /* OBJECT_H */
