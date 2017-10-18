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
#include <Magick++.h>

#include <fstream>
#include <string>
using namespace Assimp;

class Object {
public:
    Object();
    ~Object();
    bool Init(const std::string& filename);
    bool Init(const std::string& objFilename, const std::string& textureFilename);
    void Update(unsigned int dt);
    void Render();
    bool LoadVerticiesFromFile(const std::string& filename);
    bool LoadTextureData(const std::string& filename);

    glm::mat4 GetModel();
    void setModel(const glm::mat4& incomingMatrix);

    std::vector<Vertex> vertices;
private:
    glm::mat4 model;
    std::vector<unsigned int> indices;
    GLuint VBO;
    GLuint IBO;
    
    GLuint TBO;
    Magick::Blob blob;
    unsigned int m_texture_width, m_texture_height;

};

#endif /* OBJECT_H */
